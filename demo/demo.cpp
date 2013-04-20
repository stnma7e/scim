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

	std::string deerFile = ResourceManager::GetFileContents<std::string>("entity/deer.xml");
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
		{
			log::emit<logging::Error>() << "Failed to queue event" << log::endl;
		}
	}

	size_t numMesh = 2;
	std::vector<glm::mat4> matList(numMesh);

	for (size_t i = 0; i < matList.size(); ++i)
	{
		matList[i] = glm::scale(matList[i], glm::vec3(0.25, 0.25, 0.25));
		matList[i] = matList[i] = glm::translate(matList[i], glm::vec3(5, 5, 5));
	}
	for (size_t i = 1; i < matList.size(); ++i)
	{
		matList[i] = glm::translate(matList[i], glm::vec3(i + 1, i + 1, i + 1));
	}

	AssimpMesh* asMesh = MeshTools::GetMesh<AssimpMesh>("cube");
	// AssimpMesh* asMesh2 = MeshTools::GetMesh<AssimpMesh>("house");
	AssimpMesh* mesh = MeshTools::GetMesh<AssimpMesh>("plane");

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

		for (size_t i = 0; i < matList.size(); i += 2)
		{
			if (asMesh)
			{
				mesh->Render((*RenderFramework::GetCamToClipMatrix()) * matList[i]);
			}
			if (mesh)
			{
				asMesh->Render((*RenderFramework::GetCamToClipMatrix()) * matList[i + 1]);
			}
		}

		RenderFramework::PostRender();

		g_currentScene->UpdateNodes();
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
