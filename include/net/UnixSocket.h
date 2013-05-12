#ifndef UNIXSOCKET_H_
#define UNIXSOCKET_H_

#include "net/ISocket.h"

#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

namespace scim
{

class UnixSocket : public ISocket
{
	U32 m_sockfd;
	struct addrinfo* m_servinfo;
public:
	UnixSocket(const std::string& destAddr, const std::string& portNumber);
	~UnixSocket();

	bool BlockSend(char* data, size_t length);
	I32 Recieve(void* buffer, U32 numBytes) const;
};

}

#endif