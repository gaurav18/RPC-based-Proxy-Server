#include "proxy.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Proxy::init(common::CachePolicy policy, int cache_size) {    
    // Initialize cache
    this->_cache.init(policy, cache_size);
    printf("\n\n> Proxy server initialized with cache policy %d and cache size %d\n\n", policy, cache_size);
}

void Proxy::restart_debug(common::CachePolicy policy, int cache_size) {
    // Flush all data in cache and reinitialize with new values
    this->_cache.flush();
    this->_cache.init(policy, cache_size);
}

std::string Proxy::fetch(std::string url) {
    // Check if url already exists in cache
    if(this->_cache.exists(url)) {
        // Found, return http data from cache
        return this->_cache.fetch(url);
    } else {
        // Not found, fetch http data
        std::string data;
        
        this->_curl_handle = curl_easy_init();
        if(this->_curl_handle) {
            curl_easy_setopt(this->_curl_handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(this->_curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(this->_curl_handle, CURLOPT_WRITEDATA, &data);
            this->_curl_response = curl_easy_perform(this->_curl_handle);
            curl_easy_cleanup(this->_curl_handle);
        }

        // Add to cache
        int result = this->_cache.add(url, data);

        // Return http data
        if(result == 1) {
            return data;
        } else {
            printf("Error adding entry to cache!\n");
        }
    }
}

void Proxy::dump_stats() {
    printf("TODO: Placeholder.\n");
}
