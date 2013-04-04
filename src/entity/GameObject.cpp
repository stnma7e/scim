#include "GameObject.h"
#include "component/ComponentCollection.h"

namespace scim
{

GOid GameObject::nextGOid = 0;

GameObject::GameObject(GOid id, const char* type, U32 sceneNodeIndex) : m_id(id), m_type(type), m_sceneNodeIndex(sceneNodeIndex)
{
	m_compColl = new ComponentCollection;
}

}
