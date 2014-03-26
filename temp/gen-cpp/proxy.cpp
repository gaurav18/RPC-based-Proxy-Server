#include "proxy.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Proxy::init() {
    // Caching policy in place: NOT_SET, RANDOM, FIFO, or TBD
    const CachePolicy policy = RANDOM;
    
    // Maximum cache size to store. Example: 2MB = 1024 * 1024 * 2 chars
    const int cache_size = 2097152;
    
    // Initialize cache
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
            curl_easy_setopt(this->_curl_handle, CURLOPT_WRITEDATA, &readBuffer);
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