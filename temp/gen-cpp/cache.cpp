#include "cache.h"
#include <stdlib.h> // for rand

void Cache::init(CachePolicy p, int max_size) {
    if(p == NOT_SET || p == RANDOM || p == FIFO || p == TBD) {
        this->_policy = p;
        this->_size_max = max_size;
        this->_size_remaining = max_size;
    } else {
        printf("Error: Invalid cache policy selected!\n");
    }
}

int Cache::add(std::string url, std::string data) {
    // Check if we have enough room to add new entry
    int size = data.size();
    
    if(size > this->_size_max) {
        printf("Warning: Could not add page to cache, size greater than total cache max.\n");
        return 0;
    }

    switch(this->_policy) {
        case NOT_SET:
        // Never delete entries, keep adding indefinitely over max limit.
        // Yes, the size_remaining can go negative with this policy in place.
        // Nothing to do here, as no special deletion rules apply.
        break;

        case RANDOM:
        // Delete entries at random till we have enough free space
        int random_element;
        while(size > this->_size_remaining) {
            // Select random element
            random_element = rand() % this->_vector.size();
            // Increment size remaining
            this->_size_remaining += this->_cache_data[ this->_vector[random_element] ].size();
            // Remove from data structures
            this->_cache_data.erase(this->_vector[random_element]);
            this->_vector.erase(this->_vector.begin() + random_element);
        }
        // We have enough space now
        this->_vector.push_back(url);
        break;

        case FIFO:
        // Delete oldest entries till we have enough free space
        while(size > this->_size_remaining) {
            // Increment size remaining
            this->_size_remaining += this->_queue.front().size();
            // Remove from data structures
            this->_cache_data.erase(this->_queue.front());
            this->_queue.pop();
        }
        // We have enough space now
        this->_queue.push(url);
        break;

        case TBD:
        // TODO
        printf("Error: Third policy not yet implemented!\n");
        break;
        
        default:
        // No default case.
        break;
    }

    // If we reached this point, the appropriate cache policy was executed
    // Go ahead and update main cache data structure
    this->_size_remaining -= size;
    this->_cache_data[url] = data;
    return 1;
}

bool Cache::exists(std::string url) {
    // Returns 1 if found, 0 if not
    return this->_cache_data.count(url);
}

std::string Cache::fetch(std::string url) {
    return this->_cache_data[url];
}
