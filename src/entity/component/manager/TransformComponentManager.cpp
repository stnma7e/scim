#include "TransformComponentManager.h"
#include "../TransformComponent.h"
#include "../ComponentCollection.h"

#include <iostream>
#include <stdio.h>

namespace scim
{

TransformComponentManager::TransformComponentManager() : ComponentManager(GameComponent::TRANSFORM), toInitVec(0,0,0)
{
	RegisterManager(this);
}
bool TransformComponentManager::Init()
{
	return TRUE;
}
void TransformComponentManager::OnUpdate(F64 dtime)
{

}
void TransformComponentManager::Shutdown()
{
/*	static int i = 0;
	fprintf(stdout, "begin: %d\n", *compList.begin());
	for (ComponentList::iterator it = compList.begin(); it != compList.end(); ++it)
	{
		// printf("comp %d: %d\n", i, *it);
		if (*it)
		{
			// delete (*it);
			// compList.erase(it); // FIX ME
		}
		++i;
	}
	printf("end: %d\n", *compList.end());
	printf("%s", "stop");*/
}
GameComponent* TransformComponentManager::CreateComponent(XMLNode& compRoot, GameObject* owner)
{
	TransformComponent* t = new TransformComponent(owner, toInitVec);
	compList.push_back(t);
	return t;
}

}
