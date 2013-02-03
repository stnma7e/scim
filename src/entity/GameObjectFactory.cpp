#include "GameObjectFactory.h"
#include "component/GameComponentFactory.h"
#include "component/ComponentCollection.h"

namespace scim
{

GameObjectFactory::GameObjectFactory()
{
}

GameObject* GameObjectFactory::CreateObject(const char* type, I8 numComps, GameComponent::Type compList[])
{
	GameObject* go = new GameObject(GameObject::GetNextGOid(), type);
	GameComponentFactory* fact = &GameComponentFactory::GetInstance();

	for (int i = 0; i < numComps; i++)
	{
		GameComponent* gc = fact->CreateComponent(compList[i], go);
		if (gc)
		{
			go->compColl->AddComponent(gc);
		}
		else
			return 0;
	}

	return go;
}

}
