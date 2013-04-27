#ifndef CREATEGAMEOBJECTEVENT_H_
#define CREATEGAMEOBJECTEVENT_H_

#include "../GameEvent.h"

#include <xmlParser.h>

namespace scim
{

class CreateGameObjectEvent: public GameEvent
{
	GameObject** m_pointerToBeAssigned;
	const std::string m_entityName;
	const XMLNode m_rootNode;
public:
	CreateGameObjectEvent(const F32 timestamp, GameObject** pointerToBeAssigned, const XMLNode& rootNode) : GameEvent(CREATE_GAMEOBJECT, timestamp),
		m_pointerToBeAssigned(pointerToBeAssigned),
		m_rootNode(rootNode) { }

	GameObject** GetPointerToAssign() const { return m_pointerToBeAssigned; }
	const XMLNode* GetRootNode() const { return &m_rootNode; }
};

}

#endif
