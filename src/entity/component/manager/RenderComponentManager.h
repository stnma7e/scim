#ifndef RENDERCOMPONENTMANAGER_H_
#define RENDERCOMPONENTMANAGER_H_

#include "ComponentManager.h"

namespace scim
{

class RenderComponentManager: public ComponentManager
{
public:
	RenderComponentManager();
	virtual GameComponent* CreateComponent(const XMLNode& compRoot, GameObject* owner);

	virtual bool Init();
	virtual void OnUpdate(F64 dtime);
	virtual void Shutdown();
};

}
#endif
