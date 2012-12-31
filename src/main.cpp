#include "entity/GameObjectFactory.h"
#include "entity/component/GameComponent.h"
#include "entity/component/manager/TransformComponentManager.h"
#include "entity/component/ComponentCollection.h"

#include <iostream>

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

	for (int i = 0; i < 0x64; i++)
	{
		GameObject*  go = GameObjectFactory::GetInstance()->CreateObject(0, "deer", 1, deerComps);
		if (go)
		{
			if (go->GetID() % 0x1 == 0)
			{
				std::cout << "id: " << go->GetID() << ", type: " << go->GetType() << std::endl;
				GameComponent* gc = go->compColl->GetComponent(GameComponent::Transform);
				if (gc)
					std::cout << gc->GetType() << std::endl;
				else
					;
			}
			else
				;
		}
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
