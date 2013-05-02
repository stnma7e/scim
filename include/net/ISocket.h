#ifndef ISOCKET_H_
#define ISOCKET_H_

#include <string.h>

namespace scim
{

class ISocket
{
public:
	virtual ~ISocket() { }

	virtual bool Send(char* data, size_t length) = 0;
	virtual I32 Recieve(void* buffer, U32 numBytes) = 0;
};

}

#endif