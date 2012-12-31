#include <iostream>

#include "entity/GameObjectFactory.h"
#include "entity/component/GameComponent.h"
#include "entity/component/manager/TransformComponentManager.h"

using namespace scim;

bool init();

int main(int argc, char* argv[])
{
	if (!init())
		return 1;

	GameComponent::Type deerComps[] =
	{
		GameComponent::Transform
	};

	for (int i = 0; i < 0x1; i++)
	{
		GameObject*  go = GameObjectFactory::GetInstance()->CreateObject(0, "deer", 1, deerComps);
		if (go)
			std::cout << "id: " << go->GetID() << ", type: " << go->GetType() << std::endl;
		else
			std::cout << "invalid go" << std::endl;
	}

	return 0;
}
bool init()
{
	TransformComponentManager::GetInstance();

	return 1;
}
