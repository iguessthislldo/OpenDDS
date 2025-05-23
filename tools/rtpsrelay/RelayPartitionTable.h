#ifndef RTPSRELAY_RELAY_PARTITION_TABLE_H_
#define RTPSRELAY_RELAY_PARTITION_TABLE_H_

#include "RelayStatisticsReporter.h"

#include <dds/rtpsrelaylib/PartitionIndex.h>
#include <dds/rtpsrelaylib/Utility.h>

#include <dds/DCPS/GuidConverter.h>

#include <ace/Thread_Mutex.h>

namespace RtpsRelay {

using AddressSet = std::set<ACE_INET_Addr>;
using SlotKey = std::pair<std::string, size_t>;

struct SlotKeyHash {
  std::size_t operator()(const SlotKey& slot_key) const
  {
    return std::hash<std::string>()(slot_key.first) ^ std::hash<std::size_t>()(slot_key.second);
  }
};

class RelayPartitionTable {
public:
  explicit RelayPartitionTable(RelayStatisticsReporter& relay_stats_reporter)
    : address_count_(0)
    , complete_(relay_to_address_, relay_stats_reporter)
  {}

  void insert(const std::string& relay_id,
              const std::string& name,
              const ACE_INET_Addr& address)
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);

    const auto pair = relay_to_address_[relay_id].insert(std::make_pair(name, address));
    if (pair.second) {
      ++address_count_;
      relay_stats_reporter().relay_partition_addresses(address_count_);
    } else {
      pair.first->second = address;
    }
  }

  void remove(const std::string& relay_id,
              const std::string& name)
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);

    const auto pos1 = relay_to_address_.find(relay_id);
    if (pos1 != relay_to_address_.end()) {
      pos1->second.erase(name);
      if (pos1->second.empty()) {
        relay_to_address_.erase(pos1);
      }
      --address_count_;
      relay_stats_reporter().relay_partition_addresses(address_count_);
    }
  }

  void complete_insert(const SlotKey& slot_key,
                       const StringSequence& partitions)
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);

    complete_.insert(slot_key, partitions);
  }

  void lookup(AddressSet& address_set, const StringSet& partitions, const std::string& name) const
  {
    ACE_GUARD(ACE_Thread_Mutex, g, mutex_);

    complete_.lookup(address_set, partitions, name);
  }

private:
  using NameToAddress = std::unordered_map<std::string, ACE_INET_Addr>;
  using RelayToAddress = std::unordered_map<std::string, NameToAddress>;
  RelayToAddress relay_to_address_;
  size_t address_count_;

  struct Map {
    Map(const RelayToAddress& relay_to_address, RelayStatisticsReporter& relay_stats_reporter)
      : relay_to_address_(relay_to_address)
      , relay_stats_reporter_(relay_stats_reporter)
    {}

    void insert(const SlotKey& slot_key,
                const StringSequence& partitions)
    {
      StringSet parts(partitions.begin(), partitions.end());

      const auto& x = relay_to_partitions_[slot_key];

      std::vector<std::string> to_add;
      std::set_difference(parts.begin(), parts.end(), x.begin(), x.end(), std::back_inserter(to_add));

      std::vector<std::string> to_remove;
      std::set_difference(x.begin(), x.end(), parts.begin(), parts.end(), std::back_inserter(to_remove));

      if (to_add.empty() && to_remove.empty()) {
        relay_stats_reporter_.relay_partition_slots(relay_to_partitions_.size());
        // No change.
        return;
      }

      const auto r = relay_to_partitions_.insert(std::make_pair(slot_key, StringSet()));
      r.first->second.insert(to_add.begin(), to_add.end());
      for (const auto& part : to_add) {
        partition_index_.insert(part, slot_key.first);
      }
      for (const auto& part : to_remove) {
        r.first->second.erase(part);
        partition_index_.remove(part, slot_key.first);
      }
      if (r.first->second.empty()) {
        relay_to_partitions_.erase(r.first);
      }
      relay_stats_reporter_.relay_partition_index_nodes(partition_index_.size());
      relay_stats_reporter_.relay_partition_index_cache(partition_index_.cache_size());
      relay_stats_reporter_.relay_partition_slots(relay_to_partitions_.size());
    }

    void lookup(AddressSet& address_set, const StringSet& partitions, const std::string& name) const
    {
      for (const auto& partition : partitions) {
        StringSet relay_ids;
        partition_index_.lookup(partition, relay_ids);
        for (const auto& relay_id : relay_ids) {
          const auto pos2 = relay_to_address_.find(relay_id);
          if (pos2 != relay_to_address_.end()) {
            const auto pos3 = pos2->second.find(name);
            if (pos3 != pos2->second.end()) {
              address_set.insert(pos3->second);
            }
          }
        }
      }
      relay_stats_reporter_.relay_partition_index_cache(partition_index_.cache_size());
    }

    const RelayToAddress& relay_to_address_;
    RelayStatisticsReporter& relay_stats_reporter_;

    PartitionIndex<StringSet, Identity> partition_index_;

    using RelayToPartitions = std::unordered_map<SlotKey, StringSet, SlotKeyHash>;
    RelayToPartitions relay_to_partitions_;
  };

  RelayStatisticsReporter& relay_stats_reporter() { return complete_.relay_stats_reporter_; }

  Map complete_;
  mutable ACE_Thread_Mutex mutex_;
};

}

#endif // RTPSRELAY_RELAY_PARTITION_TABLE_H_
