#include "ComponentCollection.h"

namespace scim
{

void ComponentCollection::AddComponent(GameComponent* gc)
{
	std::map<GameComponent::Type, GameComponent*>::iterator it = compMap.find(gc->GetType());
	if (it != compMap.end())
		compMap.insert(std::pair<GameComponent::Type, GameComponent*>(gc->GetType(), gc));
}
void ComponentCollection::RemoveComponent(GameComponent::Type type)
{
	std::map<GameComponent::Type, GameComponent*>::iterator it = compMap.find(type);
	if (it != compMap.end())
		compMap.erase(it);
}
GameComponent* ComponentCollection::GetComponent(GameComponent::Type type)
{
	std::map<GameComponent::Type, GameComponent*>::iterator it = compMap.find(type);
	if (it != compMap.end())
		return it->second;
	else
		return 0;
}

}
