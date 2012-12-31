#include "GameComponentFactory.h"

#include <iostream>

namespace scim
{

GameComponentFactory::GameComponentFactory()
{
}

GameComponent* GameComponentFactory::CreateComponent(GameComponent::Type type, GameObject* owner)
{
	std::map<GameComponent::Type, ComponentManager*>::iterator it = mangMap.find(type);
	if (it != mangMap.end())
		return it->second->CreateComponent(owner);
	else
	{
		std::cout << "no valid manager" << std::endl;
		return 0;
	}
}

}
