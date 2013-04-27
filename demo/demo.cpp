// demo.cpp
// creates a window context, then loads a mesh, then renders

#include "entity/component/GameComponent.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"
#include "graphics/Scene.h"
#include "event/EventManager.h"
#include "event/events/CreateGameObjectEvent.h"
#include "event/events/ShutdownGameEvent.h"
#include "graphics/XMLMesh.h"
#include "graphics/MeshTools.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <logging/logging.h>
#include <IL/il.h>

using namespace scim;
using namespace logging;

bool init();
void shutdown();
void shutdown_delegate(GameEvent*);

bool stopFlag;

namespace scim
{
	Scene*						g_currentScene;
	EventManager*				g_eventManager;
}

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::cout << "USAGE: demo_scim" << std::endl;
		for (int i = 1; i < argc; ++i)
		{
			std::cout << "\tinvalid arg: \"" << argv[i] << "\"" << std::endl;
		}
		return 1;
	}

	Scene sc;
	EventManager em;

	g_currentScene = &sc;
	g_eventManager = &em;

	if (!init())
	{
		shutdown();
		log::emit<logging::Error>() << "Initialization failed" << log::endl;
		return 1;
	}

	stopFlag = false;

	std::string cubeFile = ResourceManager::GetFileContents<std::string>("entity/cube.xml");
	XMLResults* res = NULL;
	XMLNode cubeNode = XMLNode::parseString(cubeFile.c_str(), "breed", res);
	if (res)
	{
		log::emit<logging::Error>() << "Invalid XML resource" << log::endl;
		shutdown();
		return 1;
	}

	g_eventManager->AddListener(GameObjectTools::CreateGameObject, GameEvent::CREATE_GAMEOBJECT);
	g_eventManager->AddListener(shutdown_delegate, GameEvent::SHUTDOWN);

	const int numObjs = 1;
	GameObject* go[numObjs];

	try
	{
		for (int i = 0; i < numObjs; ++i)
		{
			if (!g_eventManager->TriggerEvent(new CreateGameObjectEvent(1.0f, &go[i], cubeNode)))
			{
				log::emit<logging::Error>() << "Failed to queue event" << log::endl;
			}
		}
	} catch (std::runtime_error& e)
	{
		log::emit<logging::Error>() << e.what() << log::endl;
	}

	size_t i = 0;
	size_t nFrames = 0;
	F64 oldTime = glfwGetTime();
	while (!stopFlag)
	{
		// Measure speed
		F64 currentTime = glfwGetTime();
		nFrames++;
		if ( currentTime - oldTime >= 1.0 ) // If last printf() was more than 1 sec ago
		{
			std::cout << (1000.0f / (F64)nFrames) << " ms/frame" << std::endl;
			nFrames = 0;
			oldTime += 1.0;
		}

		if (i % 100 == 0)
		{
			for (int i = 0; i < numObjs; ++i)
			{
				// log::emit<logging::Info>() << "id: " << go[i]->GetID() << ", type: " << go[i]->GetType() << log::endl;
				// glm::mat4* mat = g_scene->GetNode(go[i]->GetSceneNodeIndex()).wmat;
				// Scene::PrintMatrix(*mat);
			}

		}

		RenderFramework::OnUpdate(currentTime - oldTime);
		RenderFramework::PreRender();

		g_currentScene->UpdateNodes();
		g_currentScene->RenderNodes();

		RenderFramework::PostRender();
		g_eventManager->OnUpdate(0.01f);

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

	success &= RenderFramework::Init();

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
	RenderFramework::Shutdown();
}
