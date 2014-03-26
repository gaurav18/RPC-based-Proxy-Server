#ifndef __COMMON_H
#define __COMMON_H

// Common variables used by both server and client
namespace common {

    typedef int CachePolicy;
    typedef int CacheSize;

    // Cache Policy 
    const int NOT_SET = 0;            // No cache policy, cache everything indefinitely
    const int RANDOM = 1;             // Randomly delete older entries
    const int FIFO = 2;               // Delete oldest entries first
    const int LRU = 3;                // Delete least recent entries first

    // Cache Size
    const int ONE_MB = 1048576;       // 1024 * 1024
    const int TWO_MB = 2097152;       // 1024 * 1024 * 2
    const int THREE_MB = 3145728;     // 1024 * 1024 * 3

}

#endif // __COMMON_H
