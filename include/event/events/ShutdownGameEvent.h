#ifndef SHUTDOWNGAMEEVENT_H_
#define SHUTDOWNGAMEEVENT_H_

#include "../GameEvent.h"

namespace scim
{

class ShutdownGameEvent: public GameEvent
{
	const char* m_shutdownString;
public:
	ShutdownGameEvent(const F32 timestamp, const char* shutdownString) : GameEvent(1, timestamp),
		m_shutdownString(shutdownString) { }

	const char* GetShutdownString() const { return m_shutdownString; }
};

}

#endif
