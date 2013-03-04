#ifndef RENDERCOMPONENTMANAGER_H_
#define RENDERCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include "../../../common/Singleton.h"

namespace scim
{

class RenderComponentManager: public ComponentManager, public Singleton<RenderComponentManager>
{
	friend class Singleton<RenderComponentManager>;
	RenderComponentManager();

public:
	virtual GameComponent* CreateComponent(const XMLNode& compRoot, GameObject* owner);

	virtual bool Init();
	virtual void OnUpdate(F64 dtime);
	virtual void Shutdown();
};

}
#endif
