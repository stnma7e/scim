#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>

#ifdef NDEBUG
	#define DEBUG(M, ...)
#else
	#define DEBUG(M, ...) fprintf(stderr, "[DEBUG] %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define LOG_ERR(M, ...) 	fprintf(stderr, "[ERROR] %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(M, ...) 	fprintf(stderr, "[WARN] %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(M, ...) 	fprintf(stderr, "[INFO] %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif
