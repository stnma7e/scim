#include "entity/GameObjectTools.h"
#include "entity/GameObject.h"
#include "graphics/Scene.h"
#include "entity/component/GameComponent.h"
#include "entity/component/GameComponentFactory.h"
#include "event/events/CreateGameObjectEvent.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"
#include "graphics/MeshTools.h"

#include <xmlParser.h>

namespace scim
{

extern Scene* g_currentScene;

namespace GameObjectTools
{

	void CreateGameObject(GameEvent* evt)
	{
		CreateGameObjectEvent* creEvt = (CreateGameObjectEvent*)evt;
		GameObject** p_go = creEvt->GetPointerToAssign();
		const XMLNode* breedNode = creEvt->GetRootNode();
		const char* entityName = breedNode->getAttribute("type");

		AssimpMesh* mesh = MeshTools::GetMesh<AssimpMesh>(entityName);
		U32 sceneNodeIndex = g_currentScene->CreateNode(Scene::ROOT_NODE, mesh).index;
		GameObject* go = new GameObject(GameObject::GetNextGOid(), entityName, sceneNodeIndex);
		GameComponentFactory* fact = &GameComponentFactory::GetInstance();

		for (int i = 0; i < breedNode->nChildNode("component"); ++i)
		{
			XMLNode compNode = breedNode->getChildNode("component", i);

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
