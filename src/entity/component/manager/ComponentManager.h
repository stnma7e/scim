#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "../GameComponent.h"

class ComponentCollection;

namespace scim
{

class ComponentManager
{
private:
	ComponentCollection* compColl;
protected:
	GameComponent::Type m_type;
public:
	ComponentManager(GameComponent::Type type);
	virtual ~ComponentManager() { }

	GameComponent::Type GetType() const { return m_type; }

	virtual GameComponent* CreateComponent(GameObject* owner) = 0;
	void RegisterManager(ComponentManager* toReg);
};

}
#endif
