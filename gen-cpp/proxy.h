#ifndef __PROXY_H
#define __PROXY_H

#include "cache.h"
#include <curl/curl.h>

class Proxy {
  private:
    Cache _cache;
    
    CURL* _curl_handle;
    CURLcode _curl_response;
  public:
    void init(common::CachePolicy policy, int cache_size);
    void restart_debug(common::CachePolicy policy, int cache_size);
    std::string fetch(std::string url);
    void dump_stats();
};

#endif // __PROXY_H
