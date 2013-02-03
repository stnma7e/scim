#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "GameComponent.h"
#include "../GameObject.h"

#include "GL/glew.h"
#include "GL/glfw.h"

namespace scim
{

class RenderComponent: public GameComponent
{
	GLuint m_VBO;
	static char plusOne;
	char m_plusOne;

	const float vertData[288] = {
		 0.25f,  0.25f, -1.25f, 1.0f,
		 0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,

		 0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,

		 0.25f,  0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,
		 0.25f, -0.25f, -2.75f, 1.0f,

		 0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,

		-0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,

		-0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,

		 0.25f,  0.25f, -1.25f, 1.0f,
		 0.25f, -0.25f, -2.75f, 1.0f,
		 0.25f, -0.25f, -1.25f, 1.0f,

		 0.25f,  0.25f, -1.25f, 1.0f,
		 0.25f,  0.25f, -2.75f, 1.0f,
		 0.25f, -0.25f, -2.75f, 1.0f,

		 0.25f,  0.25f, -2.75f, 1.0f,
		 0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,

		 0.25f,  0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,

		 0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,
		 0.25f, -0.25f, -1.25f, 1.0f,

		 0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,




		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,

		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,

		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
	};
public:
	RenderComponent(GameObject* owner, const float vertData[]);

	bool Init();
	void Render();
	bool Shutdown();

	GLuint GetVBO() const { return m_VBO; }
};

}
#endif
