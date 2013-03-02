#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "GameEvent.h"
#include "../common/Singleton.h"
#include "IEventManager.h"

#include <map>
#include <list>

namespace scim
{

class EventManager: public Singleton<EventManager>, public IEventManager
{
	friend class Singleton<EventManager>;

	DelegateMap m_delegateMap;
	EventQueue m_eventQueue;
public:
	virtual bool AddListener(const EventListenerDelegate& eventDelegate, EventType type);
	virtual bool RemoveListener(const EventListenerDelegate& eventDelegate, EventType type);

	virtual bool TriggerEvent(GameEvent* pEvent);
	virtual bool QueueEvent(GameEvent* pEvent);
	virtual bool AbortEvent(const EventType inType, bool allOfType = false);

	virtual bool OnUpdate(U64 maxMillis = kINFINITE);
};

}
#endif
