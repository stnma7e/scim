#include "entity/GameObjectFactory.h"
#include "entity/component/GameComponent.h"
#include "entity/component/manager/TransformComponentManager.h"
#include "entity/component/ComponentCollection.h"
#include "event/EventManager.h"

#include <iostream>

using namespace scim;

bool init();
void shutdown();

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
		{
			if (go->GetID() % 0x1 == 0)
			{
				std::cout << "id: " << go->GetID() << ", type: " << go->GetType() << std::endl;
			}
			else
			{
			}
		}
		else
			std::cout << "invalid go" << std::endl;
	}

	shutdown();

	return 0;
}
bool init()
{
	TransformComponentManager::GetInstance();
	EventManager::GetInstance();

	return 1;
}
void shutdown()
{

}
