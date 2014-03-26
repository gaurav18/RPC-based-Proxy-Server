#!/usr/local/bin/thrift --gen cpp

namespace cpp rpc

service rpc_service {
  string fetch(1: string s),
  void restart_debug(1: i32 cache_policy, 2: i32 cache_size),
  void dump_stats(1: string batch_type)
}