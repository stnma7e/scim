#include "RenderComponentManager.h"
#include "../RenderComponent.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <stdio.h>

namespace scim
{

RenderComponentManager::RenderComponentManager() : ComponentManager(GameComponent::RENDER)
{
	RegisterManager(this);
}
bool RenderComponentManager::Init()
{
	m_programStatus = RUNNING;

	return true;
}
void RenderComponentManager::OnUpdate(F64 dtime)
{
	std::for_each(compList.begin(), compList.end(), [](GameComponent* n)
		{
			((RenderComponent*)n)->Render();
		});
}
void RenderComponentManager::Shutdown()
{
	m_programStatus = STOPPED;
}

GameComponent* RenderComponentManager::CreateComponent(const XMLNode& compRoot, GameObject* owner)
{
	RenderComponent* t = new RenderComponent(owner, compRoot);
	if (t->Init())
	{
		compList.push_back(t);
		return t;
	} else
		return NULL;
}

}
