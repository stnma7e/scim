#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

namespace scim
{

typedef U64 GOid;

class ComponentCollection;

class GameObject
{
	friend class GameObjectFactory;
protected:
	GameObject(GOid id, const char* type);
private:
	static GOid nextGOid;

	GOid		m_id;
	const char* m_type;
public:
	ComponentCollection* compColl;

	//
	static GOid GetNextGOid() { return nextGOid++; }
	GOid GetID() const { return m_id; }
	const char* GetType() const { return m_type; }
};

}
#endif
