#include "RenderFramework.h"
#include "res/ResourceManager.h"
#include "event/events/ShutdownGameEvent.h"
#include "event/EventManager.h"

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
#include <glm/gtc/matrix_transform.hpp>
#include <logging/logging.h>

namespace scim
{
    U16 RenderFramework::window_w = 1024;
    U16 RenderFramework::window_h = 640;
    bool RenderFramework::isResized = false;

    extern EventManager* g_eventManager;

RenderFramework::RenderFramework() : camToClipMatx(0.0f)
{
    running = 0;
    isResized = true;

    theProgram = 0;
    m_VAO = 0;

    window_title = "Scim";

    modelToCamUnf = 0;
    camToClipUnf = 0;
}
bool RenderFramework::Init()
{
	if (glfwInit() != GL_TRUE)
		return false;

    int glfwVers[3];
    glfwGetVersion(&glfwVers[0], &glfwVers[1], &glfwVers[2]);
    logging::log::emit<logging::Info>() << "Using GLFW " << glfwVers[0] << '.' << glfwVers[1] << '.' << glfwVers[2] << logging::log::endl;

    glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

	if (!glfwOpenWindow(window_w, window_h, 0,0,0,0,0,0, GLFW_WINDOW))
		return false;

    glfwSetWindowTitle(window_title);
    glfwSetWindowSizeCallback(RenderFramework::ResizeCallback);

    logging::log::emit<logging::Info>() <<
        "Using hardware accelerated graphics? " << (glfwGetWindowParam(GLFW_ACCELERATED) ? "True" : "False") <<
        logging::log::endl;
    logging::log::emit<logging::Info>() <<
        "Refresh rate? " << glfwGetWindowParam(GLFW_REFRESH_RATE) << logging::log::endl;
    logging::log::emit<logging::Info>() <<
        "OpenGL version? " << glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR) << '.' <<
        glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR) << logging::log::endl;
    logging::log::emit<logging::Info>() <<
        "Using debug version of OpenGL? " << (glfwGetWindowParam(GLFW_OPENGL_DEBUG_CONTEXT) ? "True" : "False") <<
        logging::log::endl;

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      Shutdown();
      return false;
    }
    logging::log::emit<logging::Info>() << "Using GLEW " << (const char*)glewGetString(GLEW_VERSION) << logging::log::endl;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, (GLsizei) window_w, (GLsizei) window_h);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0f, 1.0f);

    lookAtMatrix = glm::lookAt(
        glm::vec3(4, 3,-3),     // where camera sits
        glm::vec3(0, 0, 0),     // looks at origin
        glm::vec3(0, 1, 0)      // head is up y-axis
    );

	printf("\n");
	return true;
}
void RenderFramework::OnUpdate()
{
	running = (!glfwGetKey(GLFW_KEY_ESC)) && glfwGetWindowParam(GLFW_OPENED);
	if (!running)
    {
        g_eventManager->QueueEvent(new ShutdownGameEvent(1.0f, "RenderFramework received 'ESC' keypress"));
    }
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
    camToClipMatx = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f) * lookAtMatrix;
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
}

GLuint RenderFramework::LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
{
    std::string shaderData = ResourceManager::GetFileContents(
        ResourceManager::FindFileOrThrow("graphics/shader/" + strShaderFilename));
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
    const GLchar* source = strShader.c_str();
    GLuint shader;
    GLint shader_ok;
    const char* shad_type = eShaderType == 35633 ? "vertex shader" : (eShaderType == 35632 ? "fragment shader" : "unkown shader type");

    shader = glCreateShader(eShaderType);
    glShaderSource(shader, 1, &source, NULL);   // fourth parameter assumes null-terminated string
    glCompileShader(shader);                    // this will happen with the conversion from std::string to c_str()

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok)
    {
        std::fprintf(stderr, "Failed to compile %s\n", shad_type);
        GLint i;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &i);
        std::vector<char> logBuffer(i);
        glGetShaderInfoLog(shader, i, NULL, &logBuffer[0]);
        std::fprintf(stderr, "%s\n", &logBuffer[0]);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
GLuint RenderFramework::LinkProgram(GLuint program, const std::vector<GLuint>& shaderList)
{
    for (size_t i = 0; i < shaderList.size(); ++i)
        glAttachShader(program, shaderList[i]);

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "color");
    glLinkProgram(program);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetProgramiv(program, GL_LINK_STATUS, &Result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, (int)1));
    glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    if (InfoLogLength > 1)
        logging::log::emit<logging::Error>() << &ProgramErrorMessage[0] << logging::log::endl;
    else
        logging::log::emit<logging::Info>() << "program linked successfully" << logging::log::endl;

    for (size_t i = 0; i < shaderList.size(); ++i)
    {
        // glDetachShader(program, shaderList[i]);
        // glDeleteShader(shaderList[i]);
    }

    return program;
}

}
