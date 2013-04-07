#include "GameComponentFactory.h"

#include <iostream>
#include <xmlParser.h>
#include <string.h>
#include <bitset>

namespace scim
{

GameComponentFactory::GameComponentFactory()
{
}

GameComponent* GameComponentFactory::CreateComponent(XMLNode& compNode, GameObject* owner)
{
	const char* strType = compNode.getAttribute("type");

	GameComponent::Type type;
	if (strcmp(strType, "transform") == 0)
		type = GameComponent::TRANSFORM;
	else if (strcmp(strType, "render") == 0)
		type = GameComponent::RENDER;

	std::map<GameComponent::Type, ComponentManager*>::iterator it = mangMap.find(type);
	if (it != mangMap.end())
		return it->second->CreateComponent(compNode, owner);
	else
	{
		std::cout << "no valid manager" << std::endl;
		return 0;
	}
}

}
