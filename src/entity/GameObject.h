#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "../graphics/Scene.h"

namespace scim
{

typedef U64 GOid;

class ComponentCollection;

class GameObject
{
	friend class GameObjectFactory;
protected:
	GameObject(GOid id, const char* type, const SceneNode sceneNode);
	static GOid GetNextGOid() { return nextGOid++; }
private:
	static GOid nextGOid;

	GOid		m_id;
	const char* m_type;
	ComponentCollection* m_compColl;

	SceneNode 	m_sceneNode;
public:

	const GOid& GetID() const { return m_id; }
	const char* GetType() const { return m_type; }
	ComponentCollection* GetComponentCollection() const { return m_compColl; }
	const SceneNode* GetSceneNode() const { return &m_sceneNode; }
};

}

#endif
