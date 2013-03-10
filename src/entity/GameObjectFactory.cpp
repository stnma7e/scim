#include "GameObjectFactory.h"
#include "component/GameComponentFactory.h"
#include "component/ComponentCollection.h"
#include "../graphics/Scene.h"

#include <xmlParser.h>
#include <iostream>

namespace scim
{

extern Scene* g_scene;

GameObjectFactory::GameObjectFactory()
{
}

GameObject* GameObjectFactory::CreateObject(XMLNode& breedNode)
{
	SceneNode sceneNode = g_scene->CreateNode(0); // parent node is root
	GameObject* go = new GameObject(GameObject::GetNextGOid(), breedNode.getAttribute("type"), sceneNode);
	GameComponentFactory* fact = &GameComponentFactory::GetInstance();

	for (int i = 0; i < breedNode.nChildNode("component"); ++i)
	{
		XMLNode compNode = breedNode.getChildNode("component", i);

		GameComponent* gc = fact->CreateComponent(compNode, go);
		if (gc)
		{
			go->GetComponentCollection()->AddComponent(gc);
		}
		else
			return NULL;
	}

	return go;
}

}
