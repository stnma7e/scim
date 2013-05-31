#include "input/GLFWWindowManager.h"
#include "input/InputTools.h"
#include "event/EventManager.h"
#include "event/events/ShutdownGameEvent.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glfw3.h>

namespace scim
{

extern EventManager* g_eventManager;

GLFWWindowManager::GLFWWindowManager(const char* windowName, I32 width, I32 height, bool fullscreen)
{
	if (glfwInit() != GL_TRUE)
		return;

	if (!fullscreen)
	{
		m_window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	} else 
	{		
		m_window = glfwCreateWindow(width, height, windowName, glfwGetPrimaryMonitor(), NULL);
	}
	glfwMakeContextCurrent(m_window);
	glfwSetInputMode(m_window, GLFW_CURSOR_MODE, GLFW_CURSOR_CAPTURED);
}
GLFWWindowManager::~GLFWWindowManager()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void GLFWWindowManager::CollectInputs()
{
	Input inpt = {SCIM_KEY_NONE, SCIM_KEY_NONE, 0.0f,0.0f, 0,0};

	glfwPollEvents();

	glfwGetWindowSize(m_window, &inpt.window_w, &inpt.window_h);
	glfwGetCursorPos(m_window, &inpt.mousePosX, &inpt.mousePosY);

	if (glfwWindowShouldClose(m_window))
	{
		g_eventManager->QueueEvent(new ShutdownGameEvent(1.0f, "GLFWWindow received close event"));
	}
	for (size_t i = GLFW_KEY_A; i <= GLFW_KEY_Z; ++i)
	{
		if (glfwGetKey(m_window, i) == GLFW_PRESS)
		{
			GetKeypressAndUpdate(i, &inpt);
		}
	}
	// poll arrow keys
	{
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			inpt.specialKeys = inpt.specialKeys | SCIM_KEY_UP;
		}if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			inpt.specialKeys = inpt.specialKeys | SCIM_KEY_DOWN;
		}if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			inpt.specialKeys = inpt.specialKeys | SCIM_KEY_LEFT;
		}if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			inpt.specialKeys = inpt.specialKeys | SCIM_KEY_RIGHT;
		}
	}
	if (glfwGetKey(m_window, GLFW_KEY_ESC) == GLFW_PRESS)
	{
		inpt.specialKeys = inpt.specialKeys | SCIM_KEY_ESC;
	}

	m_collectedInputs = inpt;
}
void GLFWWindowManager::PreRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLFWWindowManager::PostRender()
{
	glfwSwapBuffers(m_window);
}

}
