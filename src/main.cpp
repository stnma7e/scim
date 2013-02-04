#include "entity/GameObjectFactory.h"
#include "entity/component/GameComponent.h"
#include "entity/component/manager/TransformComponentManager.h"
#include "entity/component/manager/RenderComponentManager.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"

#include <iostream>
#include <bitset>

using namespace scim;

bool init();
void shutdown();

GameComponent::Type deerComps[] =
{
	GameComponent::TRANSFORM,
	GameComponent::RENDER
};

int main(int argc, char* argv[])
{
	if (!init())
		return 1;

	XMLNode deerNode = XMLNode::parseFile("/home/sam/Dropbox/csim/res/breed/ball.xml").getChildNode("breed");

	for (int i = 0; i < 0x2; i++)
	{
		GameObject* go = GameObjectFactory::GetInstance().CreateObject(1, deerNode);
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
		else if (RenderFramework::GetInstance().GetStatus() == Program::STOPPED)
			break;
		else
			RenderFramework::GetInstance().Init();

		if (RenderComponentManager::GetInstance().GetStatus() == Program::RUNNING)
			RenderComponentManager::GetInstance().OnUpdate(glfwGetTime());
		else if (RenderComponentManager::GetInstance().GetStatus() == Program::STOPPED)
			break;
		else
			RenderComponentManager::GetInstance().Init();

		RenderFramework::GetInstance().PostRender();
	}

	shutdown();

	return 0;
}
bool init()
{
	if (!(TransformComponentManager::GetInstance().Init()
		&& RenderComponentManager::GetInstance().Init()
		&& RenderFramework::GetInstance().Init()))
	{
		return 0;
	}

	return 1;
}
void shutdown()
{
	RenderFramework::GetInstance().Shutdown();
	RenderComponentManager::GetInstance().Shutdown();
	TransformComponentManager::GetInstance().Shutdown();

	std::cout << std::endl << "exit." << std::endl;
}
