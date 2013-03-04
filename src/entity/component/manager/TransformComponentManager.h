#ifndef TRANSFORMCOMPONENTMANAGER_H_
#define TRANSFORMCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include "../../../common/Singleton.h"
#include "../../../math/Vec3.h"

namespace scim
{

class TransformComponentManager: public ComponentManager, public Singleton<TransformComponentManager>
{
	friend class Singleton<TransformComponentManager>;

	math::Vec3 toInitVec;

	TransformComponentManager();
public:
	virtual GameComponent* CreateComponent(const XMLNode& compRoot, GameObject* owner);

	virtual bool Init();
	virtual void OnUpdate(F64 dtime);
	virtual void Shutdown();
};

}
#endif
