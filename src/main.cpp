// main.cpp
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
#include "input/InputTools.h"
#include "input/XWindowManager.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <errno.h>
#include <thread>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <IL/il.h>
#include <GL/glfw3.h>

using namespace scim;	

bool init();
void shutdown();
void shutdown_delegate(GameEvent*);

bool stopFlag;

namespace scim
{
	Scene*						g_currentScene;
	EventManager*				g_eventManager;
	IWindowManager* 			g_curWindow;
}

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		printf("USAGE: %s\n", argv[0]);
		for (int i = 1; i < argc; ++i)
		{
			std::cout << "\tinvalid arg: \"" << argv[i] << "\"" << std::endl;
		}
		return 1;
	}
	
	Scene sc;
	EventManager em;

	g_currentScene 		= &sc;
	g_eventManager 		= &em;

	if (!init())
	{
		shutdown();
		LOG_ERR("initialization failed");
		return 1;
	}

	stopFlag = false;

	std::string cubeFile = ResourceManager::GetFileContents("entity/cube.xml");
	XMLResults* res = NULL;
	XMLNode cubeNode = XMLNode::parseString(cubeFile.c_str(), "breed", res);
	if (res)
	{
		LOG_ERR("invalid XML resource");
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
				LOG_WARN("failed to trigger go create event");
			}
		}
	} catch (std::runtime_error& e)
	{
		LOG_ERR("%s", e.what());
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
				// glm::mat4* mat = g_scene->GetNode(go[i]->GetSceneNodeIndex()).wmat;
				// Scene::PrintMatrix(*mat);
			}

		}

		g_curWindow->CollectInputs();

		RenderFramework::OnUpdate(currentTime - oldTime);
		g_currentScene->UpdateNodes();
		g_curWindow->PreRender();

		g_currentScene->RenderNodes();

		g_curWindow->PostRender();
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
	LOG_ERR("%s", ((ShutdownGameEvent*)evt)->GetShutdownString());
	stopFlag = true;
	delete evt;
}
void shutdown()
{
	RenderFramework::Shutdown();
}
