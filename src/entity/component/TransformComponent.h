#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "GameComponent.h"
#include "../../math/Vec3.h"

namespace scim
{

class TransformComponent: public scim::GameComponent
{
private:
	math::Vec3 locVec;
public:
	TransformComponent(GameObject* owner, math::Vec3 initVec);
};

}
#endif
