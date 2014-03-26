#ifndef __COMMON_H
#define __COMMON_H

namespace common {

	// Common enumerator used by both server and client
	enum CachePolicy { 
		NOT_SET,			// No cache policy, cache everything indefinitely
		RANDOM,				// Randomly delete older entries
		FIFO,				// Delete oldest entries first
		LRU					// Delete least recent entries first
	};

	enum CacheSize {
		ONE_MB = 1048576,	// 1024 * 1024
		TWO_MB = 2097152,	// 1024 * 1024 * 2
		THREE_MB = 3145728	// 1024 * 1024 * 3
	};

}

#endif // __COMMON_H
