/*
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef DATAREADER_LISTENER_IMPL
#define DATAREADER_LISTENER_IMPL

#include <tests/Utils/DistributedConditionSet.h>

#include <dds/DCPS/LocalObject.h>

#include <dds/DdsDcpsSubscriptionC.h>

#include <set>

#ifndef ACE_LACKS_PRAGMA_ONCE
#  pragma once
#endif

class DataReaderListenerImpl
  : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener> {
public:
  DataReaderListenerImpl(DistributedConditionSet_rch dcs);

  virtual ~DataReaderListenerImpl();

  virtual void on_requested_deadline_missed(
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus& status);

  virtual void on_requested_incompatible_qos(
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus& status);

  virtual void on_liveliness_changed(
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus& status);

  virtual void on_subscription_matched(
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus& status);

  virtual void on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& status);

  virtual void on_data_available(
    DDS::DataReader_ptr reader);

  virtual void on_sample_lost(
    DDS::DataReader_ptr reader,
    const DDS::SampleLostStatus& status);

  bool is_valid() const;

private:
  typedef std::set<CORBA::Long> Counts;

  DistributedConditionSet_rch dcs_;
  DDS::DataReader_var reader_;
  Counts counts_;
  bool valid_;
};

#endif /* DATAREADER_LISTENER_IMPL  */
