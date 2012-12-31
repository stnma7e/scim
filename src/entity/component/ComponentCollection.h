#ifndef COMPONENTCOLLECTION_H_
#define COMPONENTCOLLECTION_H_

#include <map>

#include "GameComponent.h"

namespace scim
{

class ComponentCollection
{
private:
	std::map<GameComponent::Type, GameComponent*> compMap;
public:
	void AddComponent(GameComponent* gc);
	void RemoveComponent(GameComponent::Type type);
	GameComponent* GetComponent(GameComponent::Type type);
};

}
#endif
