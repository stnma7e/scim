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
	static GOid GetNextGOid() { return nextGOid++; }
private:
	static GOid nextGOid;

	GOid		m_id;
	const char* m_type;
	ComponentCollection* m_compColl;
public:

	const GOid& GetID() const { return m_id; }
	const char* GetType() const { return m_type; }
	ComponentCollection* GetComponentCollection() const { return m_compColl; }
};

}
#endif
