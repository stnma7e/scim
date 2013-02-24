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
		TRANSFORM,
		RENDER
	};
protected:
	GameObject* m_owner;
	Type m_type;
	GameComponent(GameObject* owner, Type type);
public:
	virtual ~GameComponent() { }
	Type GetType() const { return m_type; }
};

}
#endif
