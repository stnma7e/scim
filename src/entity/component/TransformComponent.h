#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "GameComponent.h"
#include "../../math/Vector3.h"

namespace scim
{

class TransformComponent: public scim::GameComponent
{
private:
	math::Vector3* locVec;
public:
	TransformComponent(GameObject* owner, math::Vector3* initVec);
};

}
#endif
