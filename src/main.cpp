#include "entity/component/GameComponent.h"
#include "entity/component/manager/RenderComponentManager.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"
#include "graphics/Scene.h"
#include "event/EventManager.h"
#include "event/events/CreateGameObjectEvent.h"
#include "event/events/ShutdownGameEvent.h"

#include <iostream>
#include <string>
#include <stdio.h>

#include <logging/logging.h>

using namespace scim;
using namespace logging;

bool init();
void shutdown();
void shutdown_delegate(GameEvent*);

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
		log::emit<logging::Error>() << "Initialization failed" << log::endl;
		return 1;
	}

	stopFlag = false;

	std::string deerFile = ResourceManager::GetInstance().GetFileContents(ResourceManager::GetInstance().FindFileOrThrow(("entity/deer.xml")));
	XMLResults* res = NULL;
	XMLNode deerNode = XMLNode::parseString(deerFile.c_str(), "breed", res);
	if (res)
	{
		log::emit<logging::Error>() << "Invalid XML resource" << log::endl;
		shutdown();
		return 1;
	}

	g_eventManager->AddListener(GameObjectTools::CreateGameObject, 0);
	g_eventManager->AddListener(shutdown_delegate, 1);

	const int numObjs = 3;
	GameObject* go[numObjs];

	for (int i = 0; i < numObjs; ++i)
	{
		if (!g_eventManager->TriggerEvent(new CreateGameObjectEvent(1.0f, &go[i], deerNode)))
			log::emit<logging::Error>() << "Failed to queue event" << log::endl;
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
			for (int i = 0; i < numObjs; ++i)
			{
				log::emit<logging::Info>() << "id: " << go[i]->GetID() << ", type: " << go[i]->GetType() << log::endl;
			}
		}
		++i;
	}

	for (int i = 0; i < numObjs; ++i)
	{
		delete go[i];
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
	log::emit<logging::Info>() << ((ShutdownGameEvent*)evt)->GetShutdownString() << log::endl;
	stopFlag = true;
	delete evt;
}
void shutdown()
{
	g_renderFramework->Shutdown();
	g_renderComponentManager->Shutdown();
}
