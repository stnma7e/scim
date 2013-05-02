#include "graphics/RenderFramework.h"
#include "res/ResourceManager.h"
#include "event/events/ShutdownGameEvent.h"
#include "event/EventManager.h"
#include "input/InputTools.h"
#include "input/GLFWWindowManager.h"

#include <string>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <glm/gtc/matrix_transform.hpp>
#include <logging/logging.h>
#include <IL/il.h>

#define INIT_WINW 1024
#define INIT_WINH 768

namespace scim
{
	extern EventManager* g_eventManager;
	extern IWindowManager* g_curWindow;

namespace
{
	const char* window_title = "Scim";

	glm::mat4 camToClipMatrix(0.0f);
	glm::mat4 lookAtMatrix(0.0f);

	GLuint MakeShader(GLenum eShaderType, const std::string &strShader)
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

	void ComputeMatricesFromInputs(F32 dtime)
	{
		static const F32 initialFoV = 45.0f;					// Initial Field of View
		static const F32 speed = 0.1f;							// 3 units / second
		static const F32 mouseSpeed = 0.001f;

		static glm::vec3 cameraPosition = glm::vec3(0, 0, 5);
		static F32 horizontalAngle = 3.14f; 					// horizontal angle : toward -Z
		static F32 verticalAngle = 0.0f; 						// vertical angle : 0, look at the horizon
		static I32 xpos, ypos;									// mouse positions
		static I32 window_w, window_h;

		const Input* inptStruct = g_curWindow->GetCollectedInput();

		xpos = inptStruct->mousePosX;
		ypos = inptStruct->mousePosY;
		window_w = inptStruct->window_w;
		window_h = inptStruct->window_h;
		
		horizontalAngle = 3.14f + mouseSpeed * F32(window_w / 2 - xpos);
		verticalAngle   = mouseSpeed * F32(window_h / 2 - ypos);

		glm::vec3 direction = glm::vec3(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);
		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);
		glm::vec3 up = glm::cross(right, direction);

		// Move forward
		if (inptStruct->specialKeys & SCIM_KEY_UP)
		{
			cameraPosition += direction * dtime * speed;
		};
		// Move backward
		if (inptStruct->specialKeys & SCIM_KEY_DOWN)
		{
			cameraPosition -= direction * dtime * speed;
		};
		// Strafe right
		if (inptStruct->specialKeys & SCIM_KEY_RIGHT)
		{
			cameraPosition += right * dtime * speed;
		};
		// Strafe left
		if (inptStruct->specialKeys & SCIM_KEY_LEFT)
		{
			cameraPosition -= right * dtime * speed;
		};

		lookAtMatrix = glm::lookAt(
			cameraPosition,
			cameraPosition + direction,
			up
		);
		float FoV = initialFoV - 5;

		camToClipMatrix = glm::perspective(FoV, (F32)window_w / (F32)window_h, 0.1f, 100.0f) * lookAtMatrix;

		glViewport(0, 0, (GLsizei)window_w, (GLsizei)window_w);
	}
}

namespace RenderFramework
{

bool Init()
{
	// DevIL image loading initialization
	{
		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);		// texture (0,0) is at lower left-hand corner
	}

	// GLFW window creation and OpenGL context initialization
	{
		g_curWindow = new GLFWWindowManager(window_title, INIT_WINW, INIT_WINH, false);
		if (!g_curWindow)
		{
			logging::log::emit<logging::Error>() << "glfw failed to open window" << logging::log::endl;
			return false;
		}
	}

	// GLEW OpenGL extension handling
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
		  /* Problem: glewInit failed, something is seriously wrong. */
		  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		  return false;
		}
		logging::log::emit<logging::Info>() << "Using GLEW " << (const char*)glewGetString(GLEW_VERSION) << logging::log::endl;
	}

	glClearColor(0.8f, 1.0f, 0.8f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei) INIT_WINW, (GLsizei) INIT_WINH);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);

	printf("\n");
	return true;
}
void OnUpdate(F64 dtime)
{
	if (g_curWindow->GetCollectedInput()->specialKeys & SCIM_KEY_ESC)
	{
		g_eventManager->QueueEvent(new ShutdownGameEvent(1.0f, "Window received 'ESC' keypress"));
	}

	// if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
		ComputeMatricesFromInputs(dtime);
}
void Shutdown()
{
	delete g_curWindow;
}

GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
{
	try
	{
		std::string shaderData = ResourceManager::GetFileContents<std::string>("graphics/shader/" + strShaderFilename);
		GLuint shader_id = MakeShader(eShaderType, shaderData);
		return shader_id;
	}
	catch(std::exception &e)
	{
		logging::log::emit<logging::Error>() << e.what() << logging::log::endl;
		return 0;
	}
}
bool LinkProgram(GLuint program, const std::vector<GLuint>& shaderList)
{
	for (size_t i = 0; i < shaderList.size(); ++i)
		glAttachShader(program, shaderList[i]);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "normal");
	glBindAttribLocation(program, 2, "color");
	glBindAttribLocation(program, 3, "uv");
	glLinkProgram(program);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, (int)1));
	glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	if (InfoLogLength > 1)
	{
		logging::log::emit<logging::Error>() << &ProgramErrorMessage[0] << logging::log::endl;
		return false;
	}

	for (size_t i = 0; i < shaderList.size(); ++i)
	{
	    glDetachShader(program, shaderList[i]);
	    glDeleteShader(shaderList[i]);
	}

	return true;
}

const glm::mat4* GetCamToClipMatrix()
{
	return &camToClipMatrix;
}

}

}
