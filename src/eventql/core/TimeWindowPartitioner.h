/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <eventql/util/stdtypes.h>
#include <eventql/util/option.h>
#include <eventql/util/UnixTime.h>
#include <eventql/util/duration.h>
#include <eventql/util/SHA1.h>
#include <eventql/core/TablePartitioner.h>
#include <eventql/core/TableConfig.pb.h>

using namespace stx;

namespace zbase {

struct TimeseriesPartition {
  UnixTime time_begin;
  UnixTime time_limit;
  SHA1Hash partition_key;
};

class TimeWindowPartitioner : public TablePartitioner {
public:

  TimeWindowPartitioner(const String& table_name);

  TimeWindowPartitioner(
      const String& table_name,
      const TimeWindowPartitionerConfig& config);

  static SHA1Hash partitionKeyFor(
      const String& table_name,
      UnixTime time,
      Duration window_size);

  static Vector<SHA1Hash> listPartitions(
      const String& table_name,
      UnixTime from,
      UnixTime until,
      Duration window_size);

  static Vector<TimeseriesPartition> partitionsFor(
      const String& table_name,
      UnixTime from,
      UnixTime until,
      Duration window_size);

  Vector<SHA1Hash> listPartitions(
      UnixTime from,
      UnixTime until);

  Vector<TimeseriesPartition> partitionsFor(
      UnixTime from,
      UnixTime until);

  SHA1Hash partitionKeyFor(const String& partition_key) const override;

  Vector<SHA1Hash> listPartitions(
      const Vector<csql::ScanConstraint>& constraints) const override;

protected:
  String table_name_;
  TimeWindowPartitionerConfig config_;
};

}