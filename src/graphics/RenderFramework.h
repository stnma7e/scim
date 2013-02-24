#ifndef RENDERFRAMEWORK_H_
#define RENDERFRAMEWORK_H_

#include "../common/Singleton.h"
#include "../common/Program.h"
#include "../math/Frustum.h"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <string>

namespace scim
{

class RenderFramework: public Singleton<RenderFramework>, public Program
{
	friend class Singleton<RenderFramework>;
	friend class RenderComponent;
	RenderFramework();

	bool running;
	static bool isResized;

	static U16 window_w;
	static U16 window_h;
	const char* window_title;

	math::Frustum m_Frustum;

	GLuint theProgram;
	GLuint m_VAO;

	GLuint modelToCamUnf;
	GLuint camToClipUnf;

	glm::mat4 camToClipMatx;

	void InitProgram();
	GLuint MakeShader(GLenum type, const std::string &strShader);
	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	GLuint LinkProgram(GLuint program, GLuint shaderOne, GLuint shaderTwo);
	void OnResize(int width, int height);

	static void GLFWCALL ResizeCallback(int width, int height);
public:
	virtual bool Init();
	virtual void OnUpdate(F64 dtime);
	void PreRender();
	void PostRender();
	virtual void Shutdown();

	GLuint GetProgram() const { return theProgram; }
};

}
#endif
