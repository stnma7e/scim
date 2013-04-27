#include "entity/component/manager/ComponentManager.h"
#include "entity/component/GameComponentFactory.h"
#include "entity/component/ComponentCollection.h"

#include <iostream>

namespace scim
{

ComponentManager::ComponentManager(GameComponent::Type type) : m_type(type)
{
}

void ComponentManager::RegisterManager(ComponentManager* toReg)
{
	GameComponentFactory* fact = &GameComponentFactory::GetInstance();
	std::map<GameComponent::Type, ComponentManager*>::iterator it = fact->mangMap.find(toReg->GetType());
	if (it == fact->mangMap.end())
	{
		std::cout << "no manager already present" << std::endl;
		std::pair<std::map<GameComponent::Type, ComponentManager*>::iterator, bool> done =
			fact->mangMap.insert(std::pair<GameComponent::Type, ComponentManager*>(toReg->GetType(), toReg));
		if (done.second)
			std::cout << "mang succesfully inserted: " << toReg->GetType() << std::endl;
		else
			std::cout << "mang not inserted: " << toReg->GetType() << std::endl;
	}
}

}
