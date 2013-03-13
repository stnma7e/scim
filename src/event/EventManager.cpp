#include "EventManager.h"

#include <iostream>
#include <GL/glfw.h>

namespace scim
{

bool EventManager::AddListener(const EventListenerDelegate& eventDelegate, EventType type)
{
	DelegateList& eventListenerList = m_delegateMap[type]; // will find or create entry

	for (DelegateList::iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	{
		if (eventDelegate == (*it))
		{
			std::cout << "WARN: attempting to double-register delegate" << std::endl;
			return false;
		}
	}

	eventListenerList.push_back(eventDelegate);
	return true;
}
bool EventManager::RemoveListener(const EventListenerDelegate& eventDelegate, EventType type)
{
	bool success = false;

	DelegateMap::iterator findIt = m_delegateMap.find(type);
	if (findIt != m_delegateMap.end())
	{
		DelegateList& listeners = findIt->second;
		for (DelegateList::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				success = true;
				break;
			}
		}
	}

	return success;
}
bool EventManager::TriggerEvent(GameEvent* pEvent)
{
	bool processed = false;

	DelegateMap::iterator findIt = m_delegateMap.find(pEvent->GetType());
	if (findIt != m_delegateMap.end())
	{
		const DelegateList& eventListenerList = findIt->second;
		for (DelegateList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			listener(pEvent);

			processed = true;
		}
	}

	return processed;
}
bool EventManager::QueueEvent(GameEvent* pEvent)
{
	DelegateMap::iterator findIt = m_delegateMap.find(pEvent->GetType());
	if (findIt != m_delegateMap.end())
	{
		m_eventQueue.push_back(pEvent);
		return true;
	}

	return false;
}
bool EventManager::AbortEvent(const EventType inType, bool allOfType)
{
	bool success = false;

	DelegateMap::iterator findIt = m_delegateMap.find(inType);
	if (findIt != m_delegateMap.end())
	{
		EventQueue::iterator it = m_eventQueue.begin();

		while (it != m_eventQueue.end())
		{
			EventQueue::iterator thisIt = it;
			++it;

			if ((*thisIt)->GetType() == inType)
			{
				m_eventQueue.erase(thisIt);
				success = true;

				if (!allOfType)
					break;
			}
		}
	}

	return success;
}
bool EventManager::OnUpdate(F64 maxSeconds)
{
	F64 curTime = glfwGetTime();
	while ((glfwGetTime() - curTime) < maxSeconds)
	{
		EventQueue::iterator it = m_eventQueue.begin();
		if (it != m_eventQueue.end())
		{
			std::cout << "event type: " << (*it)->GetType() << std::endl;
			TriggerEvent(*it);
			m_eventQueue.erase(it);
		}
		else
			return true;
	}
	if (m_eventQueue.empty())
		return true;
	else
		return false;
}

}
