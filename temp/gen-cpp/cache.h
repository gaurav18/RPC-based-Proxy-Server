#ifndef __CACHE_H
#define __CACHE_H

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

enum CachePolicy { NOT_SET, RANDOM, FIFO, TBD };

class Cache {
  private:
    // Our main hashmap data structure with O(1) lookup
    // Maps url -> page_data
    std::unordered_map<std::string, std::string> _cache_data;
    
    // A queue of URL strings to determine position in cache queue
    // Used for FIFO elimination
    std::queue<std::string> _queue;

    // A vector of URL strings to fetch a random key from
    // Used for Random elimination
    std::vector<std::string> _vector;

    // Current policy
    CachePolicy _policy = NOT_SET;

    // Variables for controlling cache size (in bytes / num of chars)
    int _size_max = 0;
    int _size_remaining = 0;
  public:
    void init(CachePolicy p, int max_size);
    bool ready();
    int add(std::string url, std::string data);
    bool exists(std::string url);
    std::string fetch(std::string url);
};

#endif // __CACHE_H
