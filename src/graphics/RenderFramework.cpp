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

#include <glm/gtc/type_ptr.hpp>

namespace scim
{
    U16 RenderFramework::window_w = 1024;
    U16 RenderFramework::window_h = 640;
    bool RenderFramework::isResized = false;

RenderFramework::RenderFramework() : camToClipMatx(0.0f)
{
    running = 0;

    theProgram = 0;
    m_VAO = 0;

    window_title = "Scim";

    modelToCamUnf = 0;
    camToClipUnf = 0;
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
    glfwSetWindowSizeCallback(RenderFramework::ResizeCallback);

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

    modelToCamUnf = glGetUniformLocation(theProgram, "modelToCamMatx");
    camToClipUnf = glGetUniformLocation(theProgram, "camToClipMatx");

    m_Frustum.SetFOV(120.0f);
    m_Frustum.SetNear(0.5f);
    m_Frustum.SetFar(5.0f);

    F32 near = m_Frustum.GetNear();
    F32 far = m_Frustum.GetFar();
    F32 scale = m_Frustum.GetFOV();

    camToClipMatx[0].x = scale;
    camToClipMatx[1].y = scale;
    camToClipMatx[2].z = (far + near) / (near - far);
    camToClipMatx[2].w = (2 * far * near) / (near - far);
    camToClipMatx[3].z = -1.0f;

    glUseProgram(theProgram);
    glUniformMatrix4fv(camToClipUnf, 1, GL_FALSE, glm::value_ptr(camToClipMatx));
    glUseProgram(0);

	printf("\n");
    m_programStatus = RUNNING;
	return 1;
}
void RenderFramework::OnUpdate(F64 dtime)
{
	running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	if (!running)
		Shutdown();
    if(isResized)
        OnResize(window_w, window_h);
}
void GLFWCALL RenderFramework::ResizeCallback(int width, int height)
{
    isResized = true;

    window_w = width;
    window_h = height;
}
void RenderFramework::OnResize(int width, int height)
{ 
    camToClipMatx[0].x = m_Frustum.GetFOV() * (height / (float)width);
    camToClipMatx[1].y = m_Frustum.GetFOV();

    glUseProgram(theProgram);
    glUniformMatrix4fv(camToClipUnf, 1, GL_FALSE, glm::value_ptr(camToClipMatx));
    glUseProgram(0);

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    isResized = false;
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
    
    if (!(vert && frag))
    	Shutdown();

    theProgram = glCreateProgram();
    LinkProgram(theProgram, vert, frag);
}
GLuint RenderFramework::LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
{
    std::string shaderData = ResourceManager::GetInstance().GetFileContents(ResourceManager::GetInstance().FindFileOrThrow("graphics/shader/" + strShaderFilename));

    try
    {
	    GLuint shader_id = MakeShader(eShaderType, shaderData);
        

        return shader_id;
    }
    catch(std::exception &e)
    {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }
}
GLuint RenderFramework::MakeShader(GLenum eShaderType, const std::string &strShader)
{
    GLchar* source = (char*)strShader.c_str();
    GLuint shader;
    GLint shader_ok;
    const char* shad_type = eShaderType == 35633 ? "vertex shader" : (eShaderType == 35632 ? "fragment shader" : "unkown shader type");

    shader = glCreateShader(eShaderType);
    glShaderSource(shader, 1, (const GLchar**)&source, NULL); // fourth parameter assumes null-terminated string as this will
    glCompileShader(shader);                                  // happen with the conversion from std::string to c_str()

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok)
    { 
        std::fprintf(stderr, "Failed to compile %s\n", shad_type);
        GLint i;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &i);
        char logBuffer[i];
        glGetShaderInfoLog(shader, i, NULL, logBuffer);
        std::fprintf(stderr, "%s\n", logBuffer);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
GLuint RenderFramework::LinkProgram(GLuint program, GLuint shaderOne, GLuint shaderTwo)
{
    glAttachShader(program, shaderOne);
    glAttachShader(program, shaderTwo);

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "color");
    glLinkProgram(program);

    glDetachShader(program, shaderOne);
    glDetachShader(program, shaderTwo);   
    return program;
}

}
