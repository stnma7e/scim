#ifndef TRANSFORMCOMPONENTMANAGER_H_
#define TRANSFORMCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include "../../../common/Singleton.h"

namespace scim
{

class TransformComponentManager: public ComponentManager, public Singleton<TransformComponentManager>
{
public:
	TransformComponentManager();

	virtual GameComponent* CreateComponent(GameObject* owner);
};

}
#endif
