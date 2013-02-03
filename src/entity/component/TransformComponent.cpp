#include "TransformComponent.h"

namespace scim
{

TransformComponent::TransformComponent(GameObject* owner, math::Vec3 initVec) :  GameComponent(owner, GameComponent::TRANSFORM), locVec(initVec)
{
}

}
