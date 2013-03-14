#ifndef RENDERFRAMEWORK_H_
#define RENDERFRAMEWORK_H_

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <string>

namespace scim
{

class RenderFramework
{
	friend class RenderComponent;

	bool running;
	static bool isResized;

	static U16 window_w;
	static U16 window_h;
	const char* window_title;


	GLuint theProgram;
	GLuint m_VAO;

	GLuint modelToCamUnf;
	GLuint camToClipUnf;

	glm::mat4 camToClipMatx;

	void InitProgram();
	GLuint MakeShader(GLenum type, const std::string &strShader);
	void OnResize(int width, int height);

	static void GLFWCALL ResizeCallback(int width, int height);
public:
	RenderFramework();

	bool Init();
	void OnUpdate();
	void PreRender();
	void PostRender();
	void Shutdown();

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	GLuint LinkProgram(GLuint program, GLuint shaderOne, GLuint shaderTwo);

	GLuint GetProgram() const { return theProgram; }
};

}
#endif
