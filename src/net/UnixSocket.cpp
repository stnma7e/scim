#include "net/UnixSocket.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

namespace scim
{

UnixSocket::UnixSocket(const std::string& destAddr, const std::string& portNumber)
{
	int status;
	int on = 1;
	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family 	= AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype	= SOCK_DGRAM; 	 // UDP sockets
	hints.ai_flags 		= AI_PASSIVE;    // fill in my IP for me

	if ((status = getaddrinfo(destAddr.c_str(), portNumber.c_str(), &hints, &m_servinfo)) != 0)
	{
	    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
	    exit(1);
	}

	m_sockfd = socket(m_servinfo->ai_family, m_servinfo->ai_socktype, m_servinfo->ai_protocol);

	if ((status = ioctl(m_sockfd, FIONBIO, (char *)&on)) < 0)
	{
		perror("ioctl() failed");
		close(m_sockfd);
		exit(1);
	}
}
UnixSocket::~UnixSocket()
{
	close (m_sockfd);
}

bool UnixSocket::BlockSend(char* data, size_t length)
{
	size_t loc;
	printf("sent hex: ");
	for (size_t i = 0; i < length; ++i)
	{
		printf("%x ", data[i]);
	}
	puts("");
	I32 bytes_sent = sendto(m_sockfd, data, length, 0, m_servinfo->ai_addr, m_servinfo->ai_addrlen);
	printf("bytes_sent: %x\n", bytes_sent);
	if (bytes_sent > 1)
	{
		while (bytes_sent < (I32)length)
		{
			loc += bytes_sent;
			data += loc;
			length -= loc;
			bytes_sent = sendto(m_sockfd, data, length, 0, m_servinfo->ai_addr, m_servinfo->ai_addrlen);
		}
	} else
	{
		I32 errsv = errno;
		printf("sending errno: %d\n", errsv);
		return false;
	}

	return true;
}
I32 UnixSocket::Recieve(void* buffer, U32 numBytes) const
{
	int status;
	struct pollfd ufds[1];
	ufds[0].fd = m_sockfd;
	ufds[0].events = POLLIN;
	status = poll(ufds, 1, 50);
	if (status == -1) 
	{
		perror("poll"); // error occurred in poll()
	}

	if (status)
	{
		struct sockaddr_storage their_addr;
		socklen_t addr_len = sizeof(their_addr);

		return recvfrom(m_sockfd, buffer, numBytes, 0, (sockaddr*)&their_addr, &addr_len);
	} else
	{
		return 0;
	}
}

}