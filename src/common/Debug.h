#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>
#include <string>

#ifdef DEBUG

#define DEBUG_PRINT(x) std::cout << x << std::endl

#endif

#else

#define DEBUG_PRINT(x) if(1)

#endif
