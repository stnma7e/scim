#ifndef IEVENTMANAGER_H_
#define IEVENTMANAGER_H_

#include <FastDelegate.h>
#include "GameEvent.h"

#include <map>
#include <list>

namespace scim
{

typedef fastdelegate::FastDelegate1<GameEvent*> EventListenerDelegate;
typedef std::list<EventListenerDelegate> DelegateList;
typedef std::map<EventType, DelegateList> DelegateMap;
typedef std::list<GameEvent*> EventQueue;

class IEventManager
{

public:
	enum e_constants { kINFINITE = 0xffffffff };

	virtual ~IEventManager() { }

	virtual bool AddListener(const EventListenerDelegate& eventDelegate, EventType type) = 0;
	virtual bool RemoveListener(const EventListenerDelegate& eventDelegate, EventType type) = 0;

	virtual bool TriggerEvent(GameEvent* pEvent) = 0;
	virtual bool QueueEvent(GameEvent* pEvent) = 0;
	virtual bool AbortEvent(const EventType inType, bool allOfType = false) = 0;

	virtual bool OnUpdate(F64 maxSeconds = kINFINITE) = 0;
};

}

#endif
