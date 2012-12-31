#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "GameComponent.h"

namespace scim
{

class TransformComponent: public scim::GameComponent
{
public:
	TransformComponent(GameObject* owner);
};

}
#endif
