#include "GameObject.h"
#include "component/ComponentCollection.h"

namespace scim
{

GOid GameObject::nextGOid = 0;

GameObject::GameObject(GOid id, const char* type, const SceneNode sceneNode) : m_id(id), m_type(type), m_sceneNode(sceneNode)
{
	m_compColl = new ComponentCollection;
}

}
