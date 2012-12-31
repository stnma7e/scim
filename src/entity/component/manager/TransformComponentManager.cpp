#include "TransformComponentManager.h"
#include "../TransformComponent.h"

namespace scim
{

TransformComponentManager::TransformComponentManager() : ComponentManager(GameComponent::Transform)
{
	RegisterManager(this);
	toInitVec = new math::Vector3(0,0,0);
}

GameComponent* TransformComponentManager::CreateComponent(GameObject* owner)
{
	return new TransformComponent(owner, toInitVec);
}

}
