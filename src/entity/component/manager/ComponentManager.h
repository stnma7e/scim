#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "../GameComponent.h"

#include <list>
#include <xmlParser.h>

namespace scim
{

typedef std::list<GameComponent*> ComponentList;

class ComponentManager
{
protected:
	GameComponent::Type m_type;
	ComponentList compList;
public:
	ComponentManager(GameComponent::Type type);
	virtual ~ComponentManager() { }

	GameComponent::Type GetType() const { return m_type; }

	virtual GameComponent* CreateComponent(const XMLNode& compRoot, GameObject* owner) = 0;
	void RegisterManager(ComponentManager* toReg);

	virtual bool Init() = 0;
	virtual void OnUpdate(F64 dtime) = 0;
	virtual void Shutdown() = 0;
};

}
#endif
