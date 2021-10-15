#ifndef RTPSRELAY_GUID_ADDR_SET_H_
#define RTPSRELAY_GUID_ADDR_SET_H_

#include "ParticipantStatisticsReporter.h"
#include "RelayStatisticsReporter.h"

#include <dds/rtpsrelaylib/Utility.h>

#include <dds/DCPS/TimeTypes.h>

namespace RtpsRelay {

typedef std::map<AddrPort, OpenDDS::DCPS::MonotonicTimePoint> AddrSet;

struct AddrSetStats {
  bool allow_rtps;
  AddrSet spdp_addr_set;
  AddrSet sedp_addr_set;
  AddrSet data_addr_set;
  ParticipantStatisticsReporter spdp_stats_reporter;
  ParticipantStatisticsReporter sedp_stats_reporter;
  ParticipantStatisticsReporter data_stats_reporter;
  OpenDDS::DCPS::Message_Block_Shared_Ptr spdp_message;
  OpenDDS::DCPS::MonotonicTimePoint first_spdp;
  OpenDDS::DCPS::MonotonicTimePoint session_start;
#ifdef OPENDDS_SECURITY
  std::string common_name;
#endif

  AddrSetStats(const OpenDDS::DCPS::GUID_t& guid,
               const OpenDDS::DCPS::MonotonicTimePoint& a_session_start)
    : allow_rtps(false)
    , spdp_stats_reporter(rtps_guid_to_relay_guid(guid), "SPDP")
    , sedp_stats_reporter(rtps_guid_to_relay_guid(guid), "SEDP")
    , data_stats_reporter(rtps_guid_to_relay_guid(guid), "DATA")
    , session_start(a_session_start)
  {}

  bool empty() const
  {
    return spdp_addr_set.empty() && sedp_addr_set.empty() && data_addr_set.empty();
  }

  AddrSet* select_addr_set(Port port)
  {
    switch (port) {
    case SPDP:
      return &spdp_addr_set;
    case SEDP:
      return &sedp_addr_set;
    case DATA:
      return &data_addr_set;
    }

    return 0;
  }

  ParticipantStatisticsReporter* select_stats_reporter(Port port)
  {
    switch (port) {
    case SPDP:
      return &spdp_stats_reporter;
    case SEDP:
      return &sedp_stats_reporter;
    case DATA:
      return &data_stats_reporter;
    }

    return 0;
  }
};

class RelayHandler;

class GuidAddrSet {
public:
  typedef std::unordered_map<OpenDDS::DCPS::GUID_t, AddrSetStats, GuidHash> GuidAddrSetMap;

  GuidAddrSet(const Config& config,
              RelayStatisticsReporter& relay_stats_reporter)
    : config_(config)
    , relay_stats_reporter_(relay_stats_reporter)
  {}

  void spdp_vertical_handler(RelayHandler* spdp_vertical_handler)
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);
    spdp_vertical_handler_ = spdp_vertical_handler;
  }

  void sedp_vertical_handler(RelayHandler* sedp_vertical_handler)
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);
    sedp_vertical_handler_ = sedp_vertical_handler;
  }

  void data_vertical_handler(RelayHandler* data_vertical_handler)
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);
    data_vertical_handler_ = data_vertical_handler;
  }

  void process_expirations(const OpenDDS::DCPS::MonotonicTimePoint& now);

  OpenDDS::DCPS::MonotonicTimePoint get_first_spdp(const OpenDDS::DCPS::GUID_t& guid);

  void remove(const OpenDDS::DCPS::GUID_t& guid,
              const OpenDDS::DCPS::MonotonicTimePoint& now);

  void remove_pending(const OpenDDS::DCPS::GUID_t& guid)
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);
    pending_.erase(guid);
  }

  bool admitting() const
  {
    ACE_GUARD_RETURN(ACE_Thread_Mutex, g, mutex_, false);
    return admitting_i();
  }

  OpenDDS::DCPS::TimeDuration get_session_time(const OpenDDS::DCPS::GUID_t& guid,
                                               const OpenDDS::DCPS::MonotonicTimePoint& now)
  {
    GuidAddrSet::Proxy proxy(*this);
    return proxy.get_session_time(guid, now);
  }

  using CreatedAddrSetStats = std::pair<bool, AddrSetStats&>;

  class Proxy {
  public:
    Proxy(GuidAddrSet& gas)
      : gas_(gas)
    {
      gas_.mutex_.acquire();
    }

    ~Proxy()
    {
      gas_.mutex_.release();
    }

    GuidAddrSetMap::iterator find(const OpenDDS::DCPS::GUID_t& guid)
    {
      return gas_.guid_addr_set_map_.find(guid);
    }

    GuidAddrSetMap::const_iterator end()
    {
      return gas_.guid_addr_set_map_.end();
    }

    CreatedAddrSetStats find_or_create(const OpenDDS::DCPS::GUID_t& guid,
                                       const OpenDDS::DCPS::MonotonicTimePoint& now)
    {
      return gas_.find_or_create(guid, now);
    }

    ParticipantStatisticsReporter&
    record_activity(const AddrPort& remote_address,
                    const OpenDDS::DCPS::MonotonicTimePoint& now,
                    const OpenDDS::DCPS::GUID_t& src_guid,
                    MessageType msg_type,
                    const size_t& msg_len,
                    RelayHandler& handler)
    {
      return gas_.record_activity(remote_address, now, src_guid, msg_type, msg_len, handler);
    }

    ParticipantStatisticsReporter&
    participant_statistics_reporter(const OpenDDS::DCPS::GUID_t& guid,
                                    const OpenDDS::DCPS::MonotonicTimePoint& now,
                                    Port port)
    {
      return *find_or_create(guid, now).second.select_stats_reporter(port);
    }

    bool ignore_rtps(bool from_application_participant,
                     const OpenDDS::DCPS::GUID_t& guid,
                     const OpenDDS::DCPS::MonotonicTimePoint& now,
                     bool& admitted)
    {
      return gas_.ignore_rtps(from_application_participant, guid, now, admitted);
    }

    OpenDDS::DCPS::TimeDuration get_session_time(const OpenDDS::DCPS::GUID_t& guid,
                                                 const OpenDDS::DCPS::MonotonicTimePoint& now)
    {
      const auto it = find(guid);
      return it == end() ? OpenDDS::DCPS::TimeDuration::zero_value :
        (now - it->second.session_start);
    }

  private:
    GuidAddrSet& gas_;
    OPENDDS_DELETED_COPY_MOVE_CTOR_ASSIGN(Proxy)
  };

private:
  CreatedAddrSetStats find_or_create(const OpenDDS::DCPS::GUID_t& guid,
                                     const OpenDDS::DCPS::MonotonicTimePoint& now)
  {
    auto it = guid_addr_set_map_.find(guid);
    const bool create = it == guid_addr_set_map_.end();
    if (create) {
      const auto it_bool_pair =
        guid_addr_set_map_.insert(std::make_pair(guid, AddrSetStats(guid, now)));
      it = it_bool_pair.first;
    }
    return CreatedAddrSetStats(create, it->second);
  }

  ParticipantStatisticsReporter&
  record_activity(const AddrPort& remote_address,
                  const OpenDDS::DCPS::MonotonicTimePoint& now,
                  const OpenDDS::DCPS::GUID_t& src_guid,
                  MessageType msg_type,
                  const size_t& msg_len,
                  RelayHandler& handler);

  bool admitting_i() const
  {
    return pending_.size() < config_.max_pending();
  }

  bool ignore_rtps(bool from_application_participant,
                   const OpenDDS::DCPS::GUID_t& guid,
                   const OpenDDS::DCPS::MonotonicTimePoint& now,
                   bool& admitted);

  void remove_i(const OpenDDS::DCPS::GUID_t& guid,
                GuidAddrSetMap::iterator it,
                const OpenDDS::DCPS::MonotonicTimePoint& now);

  const Config& config_;
  RelayStatisticsReporter& relay_stats_reporter_;
  RelayHandler* spdp_vertical_handler_;
  RelayHandler* sedp_vertical_handler_;
  RelayHandler* data_vertical_handler_;
  GuidAddrSetMap guid_addr_set_map_;
  typedef std::list<std::pair<OpenDDS::DCPS::MonotonicTimePoint, GuidAddr> > ExpirationGuidAddrQueue;
  ExpirationGuidAddrQueue expiration_guid_addr_queue_;
  GuidSet pending_;
  typedef std::list<std::pair<OpenDDS::DCPS::MonotonicTimePoint, OpenDDS::DCPS::GUID_t> > PendingExpirationQueue;
  PendingExpirationQueue pending_expiration_queue_;
  mutable ACE_Thread_Mutex mutex_;
};

}

#endif /* RTPSRELAY_GUID_ADDR_SET_H_ */
