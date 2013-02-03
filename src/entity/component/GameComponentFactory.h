#ifndef GAMECOMPONENTFACTORY_H_
#define GAMECOMPONENTFACTORY_H_

#include <map>

#include "../../common/Singleton.h"
#include "GameComponent.h"
#include "manager/ComponentManager.h"

namespace scim
{

class GameComponentFactory: public Singleton<GameComponentFactory>
{
	friend class Singleton<GameComponentFactory>;
protected:
	GameComponentFactory();
private:
	std::map<GameComponent::Type, ComponentManager*> mangMap;
public:
	GameComponent* CreateComponent(GameComponent::Type type, GameObject* owner);
	friend void ComponentManager::RegisterManager(ComponentManager* toReg);
};

}
#endif
