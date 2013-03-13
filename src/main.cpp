#include "entity/GameObjectFactory.h"
#include "entity/component/GameComponent.h"
#include "entity/component/manager/RenderComponentManager.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"
#include "graphics/Scene.h"
#include "event/EventManager.h"
#include "common/Logger.h"
#include "event/events/CreateGameObjectEvent.h"
#include "event/events/ShutdownGameEvent.h"

#include <iostream>
#include <string>
#include <stdio.h>

using namespace scim;

bool init();
void shutdown();
void shutdown_delegate(GameEvent*);
void doGOStuff(GameEvent*);

bool stopFlag;

namespace scim
{
	RenderFramework* 			g_renderFramework;
	RenderComponentManager*		g_renderComponentManager;
	Scene*						g_scene;
	EventManager*				g_eventManager;
}

int main(int argc, char* argv[])
{
	RenderFramework r;
	RenderComponentManager rcm;
	Scene sc;
	EventManager em;

	g_renderFramework = &r;
	g_renderComponentManager = &rcm;
	g_scene = &sc;
	g_eventManager = &em;

	for (size_t i = 1; i < 1024; ++i)
	{
		g_scene->CreateNode(i);
	}

	if (!init())
	{
		shutdown();
		logger::LogError("initialization failed");
		return 1;
	}

	stopFlag = false;

	std::string deerFile = ResourceManager::GetInstance().GetFileContents(ResourceManager::GetInstance().FindFileOrThrow(("entity/deer.xml")));
	XMLResults* res = NULL;
	XMLNode deerNode = XMLNode::parseString(deerFile.c_str(), "breed", res);
	if (res)
	{
		logger::LogError("invalid XML resource");
		shutdown();
		return 1;
	}

	g_eventManager->AddListener(doGOStuff, 0);
	g_eventManager->AddListener(shutdown_delegate, 1);

	for (int i = 0; i < 0x2; i++)
	{
		// GameObject* go = GameObjectFactory::GetInstance().CreateObject(deerNode);
		// if (go)
		// {
		// 	if (go->GetID() % 0x1 == 0)
		// 	{
		// 		std::cout << "id: " << go->GetID() << ", type: " << go->GetType() << std::endl;
		// 	}
		// 	else
		// 	{
		// 	}
		// }
		// else
		// 	logger::LogError("invalid game object");

		GameObject* go;
		if (!g_eventManager->QueueEvent(new CreateGameObjectEvent(1.0f, &go, deerNode)))
			logger::LogError("failed to queue event");
	}

	size_t i = 0;
	F64 oldTime = glfwGetTime();
	while (!stopFlag)
	{
		g_renderFramework->OnUpdate();
		g_renderFramework->PreRender();

		g_renderComponentManager->OnUpdate(glfwGetTime());

		g_renderFramework->PostRender();

		g_scene->UpdateNodes();
		g_eventManager->OnUpdate(0.01f);

		if (i % 100 == 0)
		{
			std::cout << glfwGetTime() - oldTime << std::endl;
			oldTime = glfwGetTime();
		}
		++i;
	}

	shutdown();

	std::cout << std::endl << "exit." << std::endl;

	return 0;
}
bool init()
{
	bool success = true;

	success &= g_renderComponentManager->Init();
	success &= g_renderFramework->Init();

	return success;
}
void shutdown_delegate(GameEvent* evt)
{
	logger::LogInfo(((ShutdownGameEvent*)evt)->GetShutdownString());
	stopFlag = true;
	delete evt;
}
void shutdown()
{
	g_renderFramework->Shutdown();
	g_renderComponentManager->Shutdown();
}

void doGOStuff(GameEvent* evt)
{
	CreateGameObjectEvent* creEvt = (CreateGameObjectEvent*)evt;
	GameObject** p_go = creEvt->GetPointerToAssign();
	*p_go = GameObjectFactory::GetInstance().CreateObject((XMLNode&)*creEvt->GetRootNode());
	delete evt;
}
