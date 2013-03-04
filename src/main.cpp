#include "entity/GameObjectFactory.h"
#include "entity/component/GameComponent.h"
#include "entity/component/manager/TransformComponentManager.h"
#include "entity/component/manager/RenderComponentManager.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"

#include <iostream>

using namespace scim;

bool init();
void shutdown();

int main(int argc, char* argv[])
{
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

	while (1)
	{
		if (RenderFramework::GetInstance().GetStatus() == Program::RUNNING)
		{
			RenderFramework::GetInstance().OnUpdate(glfwGetTime());
			RenderFramework::GetInstance().PreRender();
		}
		else // RenderFramework::GetInstance().GetStatus() == Program::STOPPED
			break;

		if (RenderComponentManager::GetInstance().GetStatus() == Program::RUNNING)
		{
			RenderComponentManager::GetInstance().OnUpdate(glfwGetTime());
		}
		else // RenderComponentManager::GetInstance().GetStatus() == Program::STOPPED
			break;

		RenderFramework::GetInstance().PostRender();
	}

	shutdown();

	return 0;
}
bool init()
{
	bool success = true;

	success &= TransformComponentManager::GetInstance().Init();
	success &= RenderComponentManager::GetInstance().Init();
	success &= RenderFramework::GetInstance().Init();

	return success;
}
void shutdown()
{
	RenderFramework::GetInstance().Shutdown();
	RenderComponentManager::GetInstance().Shutdown();
	TransformComponentManager::GetInstance().Shutdown();

	std::cout << std::endl << "exit." << std::endl;
}
