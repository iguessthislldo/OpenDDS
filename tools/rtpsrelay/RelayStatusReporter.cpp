#include "RelayStatusReporter.h"

namespace RtpsRelay {

RelayStatusReporter::RelayStatusReporter(const Config& config,
                                         const GuidAddrSet& guid_addr_set,
                                         RelayStatusDataWriter_var writer,
                                         ACE_Reactor* reactor)
  : ACE_Event_Handler(reactor)
  , guid_addr_set_(guid_addr_set)
  , writer_(writer)
{
  relay_status_.relay_id(config.relay_id());

  if (config.publish_relay_status() != OpenDDS::DCPS::TimeDuration::zero_value) {
    this->reactor()->schedule_timer(this, 0, ACE_Time_Value(), config.publish_relay_status().value());
  }

};

int RelayStatusReporter::handle_timeout(const ACE_Time_Value& /*now*/, const void* /*token*/)
{
  relay_status_.admitting(guid_addr_set_.admitting());

  if (writer_->write(relay_status_, DDS::HANDLE_NIL) != DDS::RETCODE_OK) {
    ACE_ERROR((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: RelayStatusReporter::handle_timeout failed to write Relay Status\n")));
  }

  return 0;
}

}
