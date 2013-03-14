#include "GameObjectTools.h"
#include "GameObject.h"
#include "graphics/Scene.h"
#include "component/GameComponent.h"
#include "component/GameComponentFactory.h"
#include "event/events/CreateGameObjectEvent.h"
#include "component/ComponentCollection.h"

#include <xmlParser.h>

namespace scim
{

extern Scene* g_scene;

namespace GameObjectTools
{

	void CreateGameObject(GameEvent* evt)
	{
		CreateGameObjectEvent* creEvt = (CreateGameObjectEvent*)evt;
		GameObject** p_go = creEvt->GetPointerToAssign();

		XMLNode breedNode = *creEvt->GetRootNode();
		SceneNode sceneNode = g_scene->CreateNode(Scene::ROOT_NODE);
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
				*p_go = NULL;
		}

		*p_go = go;

		delete evt;
	}

}

}
