#ifndef RENDERFRAMEWORK_H_
#define RENDERFRAMEWORK_H_

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace scim
{

namespace RenderFramework
{
	enum AttributeLocations
	{
		VERTEX_POSITION = 0,
		NORMAL_POSITION = 1,
		VERTEX_COLOR 	= 2,
		TEXTURE_UV		= 3
	};

	bool Init();
	void OnUpdate(F64 dtime);
	void PreRender();
	void PostRender();
	void Shutdown();
	void OnResize(int width, int height);

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	bool LinkProgram(GLuint program, const std::vector<GLuint>& shaderList);

	const glm::mat4* GetCamToClipMatrix();
}

}
#endif
