#ifndef GAMEEVENT_H_
#define GAMEEVENT_H_

namespace scim
{

typedef U32 EventType;

class GameEvent
{
	const F32 m_timeStamp;
	const EventType m_type;
public:
	GameEvent(const U32 eventType, const F32 timestamp = 0.0f) : m_timeStamp(timestamp), m_type(eventType) { }
	virtual ~GameEvent() { }

	//
	virtual EventType GetType() { return m_type; }
};

}
#endif
