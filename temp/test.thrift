#!/usr/local/bin/thrift --gen cpp

namespace cpp Test

service Something {
  string ping(1: string s)
}
