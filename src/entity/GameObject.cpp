#include "GameObject.h"
#include "component/ComponentCollection.h"

namespace scim
{

GOid GameObject::nextGOid = 0;

GameObject::GameObject(GOid id, const char* type) : m_id(id), m_type(type)
{
	compColl = new ComponentCollection;
}

}
