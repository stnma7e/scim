#include "entity/GameObjectFactory.h"
#include "entity/component/GameComponent.h"
#include "entity/component/manager/RenderComponentManager.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"
#include "graphics/Scene.h"

#include <iostream>
#include <stdio.h>

using namespace scim;

bool init();
void shutdown();

namespace scim
{
	RenderFramework* 			g_renderFramework;
	RenderComponentManager*		g_renderComponentManager;
	Scene*						g_scene;
}

int main(int argc, char* argv[])
{
	RenderFramework r;
	g_renderFramework = &r;
	RenderComponentManager rcm;
	g_renderComponentManager = &rcm;
	Scene sc;
	g_scene = &sc;

	for (size_t i = 1; i < 1024; ++i)
	{
		g_scene->CreateNode(i);
	}
	std::cout << "done" << std::endl << std::endl;

	if (!init())
		return 1;

	std::string deerFile = ResourceManager::GetInstance().GetFileContents(ResourceManager::GetInstance().FindFileOrThrow(("entity/deer.xml")));
	XMLResults* res = NULL;
	XMLNode deerNode = XMLNode::parseString(deerFile.c_str(), "breed", res);
	if (res)
	{
		std::cout << "Error: invalid XML resource" << std::endl;
		shutdown();
		return 1;
	}

	for (int i = 0; i < 0x2; i++)
	{
		GameObject* go = GameObjectFactory::GetInstance().CreateObject(deerNode);
		if (go)
		{
			if (go->GetID() % 0x1 == 0)
			{
				std::cout << "id: " << go->GetID() << ", type: " << go->GetType() << std::endl;
			}
			else
			{
			}
		}
		else
			std::cout << "invalid go" << std::endl;
	}

	U64 i = 0;
	F64 oldTime = glfwGetTime();
	while (1)
	{
		g_renderFramework->OnUpdate(glfwGetTime());
		g_renderFramework->PreRender();

		// RenderComponentManager::GetInstance().OnUpdate(glfwGetTime());

		g_renderFramework->PostRender();

		if (i == 1)
		{
			std::cout << glfwGetTime() - oldTime << std::endl;
			oldTime = glfwGetTime();
			break;
		}
		g_scene->UpdateNodes();
		++i;
	}

	shutdown();

	return 0;
}
bool init()
{
	bool success = true;

	success &= g_renderComponentManager->Init();
	success &= g_renderFramework->Init();

	return success;
}
void shutdown()
{
	g_renderFramework->Shutdown();
	g_renderComponentManager->Shutdown();

	std::cout << std::endl << "exit." << std::endl;
}
