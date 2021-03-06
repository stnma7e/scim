#ifndef GAMECOMPONENTFACTORY_H_
#define GAMECOMPONENTFACTORY_H_

#include <map>
#include <xmlParser.h>

#include "common/Singleton.h"
#include "GameComponent.h"
#include "manager/ComponentManager.h"

namespace scim
{

class GameComponentFactory: public Singleton<GameComponentFactory>
{
	friend class Singleton<GameComponentFactory>;
protected:
	GameComponentFactory();
public:
	std::map<GameComponent::Type, ComponentManager*> mangMap;

	GameComponent* CreateComponent(XMLNode& compNode, GameObject* owner);
	friend void ComponentManager::RegisterManager(ComponentManager* toReg);
};

}
#endif
