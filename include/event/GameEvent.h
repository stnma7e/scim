#ifndef GAMEEVENT_H_
#define GAMEEVENT_H_

namespace scim
{

typedef U16 EventType;

class GameEvent
{
protected:
	const F32 m_timeStamp;
	const EventType m_type;
public:
	enum Type
	{
		CREATE_GAMEOBJECT,
		SHUTDOWN
	};

	GameEvent(const U32 eventType, const F32 timestamp = 0.0f) : m_timeStamp(timestamp), m_type(eventType) { }
	virtual ~GameEvent() { }

	virtual EventType GetType() { return m_type; }
};

}

#endif
