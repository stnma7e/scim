#ifndef GLFWWINDOWMANAGER_H_
#define GLFWWINDOWMANAGER_H_

#include "IWindowManager.h"

#include <GL/glfw3.h>

namespace scim
{

class GLFWWindowManager : public IWindowManager
{
	GLFWwindow* m_window;
public:
	GLFWWindowManager(const char* windowName, I32 width, I32 height, bool fullscreen);
	~GLFWWindowManager();

	virtual void CollectInputs() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

	GLFWwindow* GetWindow() const 
	{
		return m_window;
	}
};

}

#endif