#include "RenderFramework.h"
#include "../res/ResourceManager.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <iostream>

namespace scim
{

RenderFramework::RenderFramework()
{
    running = 0;

    theProgram = 0;
    m_VAO = 0;

    window_w = 1024;
    window_h = 640;
    window_title = "Scim";

    offsetUnf = 0;
    perspMatUnf = 0;
}
bool RenderFramework::Init()
{
	if (glfwInit() != GL_TRUE)
		return 0;
    int glfwVers[3];
    glfwGetVersion(&glfwVers[0], &glfwVers[1], &glfwVers[2]);
    fprintf(stdout, "Status: Using GLFW %d.%d.%d\n", glfwVers[0], glfwVers[1], glfwVers[2]);

	if (!glfwOpenWindow(window_w, window_h, 0,0,0,0,0,0, GLFW_WINDOW))
		return 0;

    glfwSetWindowTitle(window_title);
    glfwSetWindowSizeCallback(RenderFramework::OnResize);

    fprintf(stdout, "Status: Using hardware accelerated graphics? %s\n", (glfwGetWindowParam(GLFW_ACCELERATED) ? "True" : "False"));
    fprintf(stdout, "Status: Refresh rate? %d\n", glfwGetWindowParam(GLFW_REFRESH_RATE));
    fprintf(stdout, "Status: OpenGL version? %d.%d\n", glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR), glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR));
    fprintf(stdout, "Status: Using debug version of OpenGL? %s\n", (glfwGetWindowParam(GLFW_OPENGL_DEBUG_CONTEXT) ? "True" : "False"));

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, (GLsizei) window_w, (GLsizei) window_h);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0f, 1.0f);

	InitProgram();

    offsetUnf = glGetUniformLocation(theProgram, "offset");

    perspMatUnf = glGetUniformLocation(theProgram, "perspectiveMatrix");

    m_Frustum.SetScale(0.5f);
    m_Frustum.SetNear(0.5f);
    m_Frustum.SetFar(5.0f);

    std::memset(thePerspMatx, 0, sizeof(float) * 16);

    thePerspMatx[0] = m_Frustum.GetScale();
    thePerspMatx[5] = m_Frustum.GetScale();
    thePerspMatx[10] = (m_Frustum.GetFar() + m_Frustum.GetNear()) / (m_Frustum.GetNear() - m_Frustum.GetFar());
    thePerspMatx[14] = (2 * m_Frustum.GetFar() * m_Frustum.GetNear()) / (m_Frustum.GetNear() - m_Frustum.GetFar());
    thePerspMatx[11] = -1.0f;

    glUseProgram(theProgram);
    glUniformMatrix4fv(perspMatUnf, 1, GL_FALSE, thePerspMatx);
    glUseProgram(0);

	printf("\n");
    m_programStatus = RUNNING;
	return 1;
}
void RenderFramework::OnUpdate(F64 dtime)
{
	running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
	if (!running)
		Shutdown();
}
void GLFWCALL RenderFramework::OnResize(int width, int height)
{ 
/*
    math::Frustum frustum = RenderFramework::GetInstance().m_Frustum;
    GLuint program = RenderFramework::GetInstance().theProgram;
    float* perspectiveMatrix = RenderFramework::GetInstance().thePerspMatx;
    GLuint perspectiveMatrixUnif = RenderFramework::GetInstance().perspMatUnf;

    perspectiveMatrix[0] = frustum.GetScale() * frustum.GetAspectRatio();
    perspectiveMatrix[5] = frustum.GetScale();

    glUseProgram(program);
    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
    glUseProgram(0);
*/
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

}
void RenderFramework::PreRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void RenderFramework::PostRender()
{
    glfwSwapBuffers();
}
void RenderFramework::Shutdown()
{
	glfwTerminate();
	m_programStatus = STOPPED;
}

void RenderFramework::InitProgram()
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    GLuint vert = LoadShader(GL_VERTEX_SHADER, "MatrixPerspective.v.glsl");
    GLuint frag = LoadShader(GL_FRAGMENT_SHADER, "StandardColors.f.glsl");

    theProgram = glCreateProgram();
    LinkProgram(theProgram, vert, frag);
}
GLuint RenderFramework::LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
{
    std::string strFilename = ResourceManager::GetInstance().FindFileOrThrow(strShaderFilename);
    std::ifstream shaderFile(strFilename.c_str());
    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();

    try
    {
        return MakeShader(eShaderType, shaderData.str());
    }
    catch(std::exception &e)
    {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }
}
GLuint RenderFramework::MakeShader(GLenum type, const std::string &strShader)
{
    GLint length = strShader.size();
    GLchar* source = (char*)strShader.c_str();
    GLuint shader;
    GLint shader_ok;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok)
    {
        std::fprintf(stderr, "Failed to compile %s:\n", strShader.c_str());
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
GLuint RenderFramework::LinkProgram(GLuint program, GLuint shaderOne, GLuint shaderTwo)
{
    glAttachShader(program, shaderOne);
    glAttachShader(program, shaderTwo);   

    glLinkProgram(program);

    glDetachShader(program, shaderOne);
    glDetachShader(program, shaderTwo);   
    return program;
}

}