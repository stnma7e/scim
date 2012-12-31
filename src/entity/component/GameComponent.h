#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "../GameObject.h"

namespace scim
{

class GameComponent
{
public:
	enum Type
	{
		Transform
	};
protected:
	GameObject* m_owner;
	Type m_type;
public:
	GameComponent(GameObject* owner, Type type);
	virtual ~GameComponent() { }
	Type GetType() const { return m_type; }
};

}
#endif
