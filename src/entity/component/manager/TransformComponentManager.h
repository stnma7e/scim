#ifndef TRANSFORMCOMPONENTMANAGER_H_
#define TRANSFORMCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include "../../../common/Singleton.h"
#include "../../../math/Vector3.h"

namespace scim
{

class TransformComponentManager: public ComponentManager, public Singleton<TransformComponentManager>
{
	math::Vector3* toInitVec;
public:
	TransformComponentManager();

	virtual GameComponent* CreateComponent(GameObject* owner);
};

}
#endif
