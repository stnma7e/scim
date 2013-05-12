#include "input/NetworkInputHandler.h"

namespace scim
{

void NetworkInputHandler::CollectInputs()
{
	I32 len = m_socket->Recieve(m_curData.data, (U32)sizeof(m_curData));

	// use data to log events
}

}