#ifndef GAMEOBJECTFACTORY_H_
#define GAMEOBJECTFACTORY_H_

#include "../common/Singleton.h"
#include "GameObject.h"
#include "component/GameComponent.h"

namespace scim
{

class GameObjectFactory: public Singleton<GameObjectFactory>
{
	friend class Singleton<GameObjectFactory>;
protected:
	GameObjectFactory();
public:
	GameObject* CreateObject(const char* type, I8 numComps, GameComponent::Type compList[]);
};

}
#endif
