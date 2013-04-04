#include "entity/component/GameComponent.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"
#include "graphics/Scene.h"
#include "event/EventManager.h"
#include "event/events/CreateGameObjectEvent.h"
#include "event/events/ShutdownGameEvent.h"
#include "graphics/Mesh.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>

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
	Scene*						g_scene;
	EventManager*				g_eventManager;
}

int main(int argc, char* argv[])
{
	RenderFramework r;
	Scene sc;
	EventManager em;

	g_renderFramework = &r;
	g_scene = &sc;
	g_eventManager = &em;

	if (!init())
	{
		shutdown();
		log::emit<logging::Error>() << "Initialization failed" << log::endl;
		return 1;
	}

	stopFlag = false;

	std::string deerFile = ResourceManager::GetFileContents(ResourceManager::FindFileOrThrow(("entity/deer.xml")));
	XMLResults* res = NULL;
	XMLNode deerNode = XMLNode::parseString(deerFile.c_str(), "breed", res);
	if (res)
	{
		log::emit<logging::Error>() << "Invalid XML resource" << log::endl;
		shutdown();
		return 1;
	}

	std::stringstream meshName;
	meshName << "graphics/mesh/" << deerNode.getChildNode("mesh").getAttribute("name") << ".mesh";
	std::string meshSource = ResourceManager::GetFileContents(ResourceManager::FindFileOrThrow(meshName.str()));
	XMLResults* res2 = NULL;
	XMLNode meshNode = XMLNode::parseString(meshSource.c_str(), "mesh", res);
	if (res2)
	{
		log::emit<logging::Error>() << "Invalid mesh resource" << log::endl;
	}
	Mesh mesh(meshNode);

	g_eventManager->AddListener(GameObjectTools::CreateGameObject, 0);
	g_eventManager->AddListener(shutdown_delegate, 1);

	const int numObjs = 3;
	GameObject* go[numObjs];

	for (int i = 0; i < numObjs; ++i)
	{
		if (!g_eventManager->TriggerEvent(new CreateGameObjectEvent(1.0f, &go[i], deerNode)))
			log::emit<logging::Error>() << "Failed to queue event" << log::endl;
	}

	size_t i;
	size_t nFrames = 0;
	F64 oldTime = glfwGetTime();
	while (!stopFlag)
	{
		// Measure speed
		F64 currentTime = glfwGetTime();
		nFrames++;
		if ( currentTime - oldTime >= 1.0 ) // If last printf() was more than 1 sec ago
		{
			printf("%f ms/frame\n", 1000.0/double(nFrames));
			nFrames = 0;
			oldTime += 1.0;
		}

		if (i % 100 == 0)
		{
			for (int i = 0; i < numObjs; ++i)
			{
				log::emit<logging::Info>() << "id: " << go[i]->GetID() << ", type: " << go[i]->GetType() << log::endl;
				glm::mat4* mat = g_scene->GetNode(go[i]->GetSceneNodeIndex()).wmat;
				Scene::PrintMatrix(*mat);
			}

		}

		g_renderFramework->OnUpdate();
		g_renderFramework->PreRender();

		mesh.Render(glm::mat4(1));

		g_renderFramework->PostRender();

		g_scene->UpdateNodes();
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
}
