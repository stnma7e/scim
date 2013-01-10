#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>
#include <string>

#ifndef NDEBUG

#define DEBUG_PRINT(x) std::cout << x << std::endl

#define ASSERT(x) \
	if (x) { } \
	else \
	{ \
		exit(1); \
	}

#endif

#else

#define DEBUG_PRINT(x)

#endif
