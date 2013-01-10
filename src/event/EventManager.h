#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "../../ext/fast_delegate/FastDelegate.h"
#include "GameEvent.h"
#include "../common/Singleton.h"

#include <map>
#include <list>

namespace scim
{

typedef fastdelegate::FastDelegate1<GameEvent*> EventListenerDelegate;
typedef std::list<EventListenerDelegate> DelegateList;
typedef std::map<EventType, DelegateList> DelegateMap;
typedef std::list<GameEvent*> EventQueue;

class EventManager: public Singleton<EventManager>
{
	friend class Singleton<EventManager>;

	enum e_constants { kINFINITE = 0xffffffff };

	DelegateMap m_delegateMap;
	EventQueue m_eventQueue;
public:
	EventManager();

	//
	bool AddListener(const EventListenerDelegate& eventDelegate, EventType type);
	bool RemoveListener(const EventListenerDelegate& eventDelegate, EventType type);

	bool TriggerEvent(GameEvent* pEvent);
	bool QueueEvent(GameEvent* pEvent);
	bool AbortEvent(const EventType inType, bool allOfType = false);

	// bool Update(U64 maxMillis = kINFINITE);
};

}
#endif
