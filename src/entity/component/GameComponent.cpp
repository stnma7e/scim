#include "GameComponent.h"

namespace scim
{

GameComponent::GameComponent(GameObject* owner, Type type) : m_owner(owner), m_type(type)
{
}

}
