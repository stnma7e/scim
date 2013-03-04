#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "GameComponent.h"
#include "../GameObject.h"
#include "../../graphics/Mesh.h"

#include <GL/glew.h>
#include <GL/glfw.h>
#include <xmlParser.h>

namespace scim
{

class RenderComponent: public GameComponent
{
	GLuint m_VBO;
	static I8 plusOne;
	I8 m_plusOne;
	Mesh* m_mesh;
public:
	RenderComponent(GameObject* owner, const XMLNode& compNode);

	bool Init();
	void Render();
	bool Shutdown();

	GLuint GetVBO() const { return m_VBO; }
};

}
#endif
