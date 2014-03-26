#ifndef __PROXY_H
#define __PROXY_H

#include "cache.h"
#include <curl/curl.h>

class ProxyServer {
  private:
    Cache _cache;
    
    CURL* _curl_handle;
    CURLcode _curl_response;
  public:
    void init();
    std::string fetch(std::string url);
};

#endif // __PROXY_H
