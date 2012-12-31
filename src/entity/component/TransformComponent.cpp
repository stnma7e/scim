#include "TransformComponent.h"

namespace scim
{

TransformComponent::TransformComponent(GameObject* owner, math::Vector3* initVec) :  GameComponent(owner, GameComponent::Transform)
{
	locVec = new math::Vector3(0,0,0);
}

}
