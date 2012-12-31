#include "TransformComponentManager.h"
#include "../TransformComponent.h"

namespace scim
{

TransformComponentManager::TransformComponentManager() : ComponentManager(GameComponent::Transform)
{
	RegisterManager(this);
}

GameComponent* TransformComponentManager::CreateComponent(GameObject* owner)
{
	return new TransformComponent(owner);
}

}
