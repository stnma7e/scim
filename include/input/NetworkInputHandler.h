#ifndef NETWORKINPUTHANDLER_H_
#define NETWORKINPUTHANDLER_H_

#include "IInputHandler.h"

#ifdef WIN32
	#include "net/UnixSocket.h"
#else
	#include "net/UnixSocket.h"
#endif

namespace scim
{

struct NetInput
{
	char data[500];
};

class NetworkInputHandler : public IInputHandler
{
	const ISocket* m_socket;
	NetInput m_curData;
public:
	NetworkInputHandler(const ISocket* socket) : m_socket(socket) { }
	virtual void CollectInputs() override;
};

}

#endif