#ifndef XWINDOWMANAGER_H_
#define XWINDOWMANAGER_H_

#include "IWindowManager.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace scim
{

class XWindowManager : public IWindowManager
{
	Display*                dpy;
	Window                  root;
	XVisualInfo*            vi;
	Colormap                cmap;
	XSetWindowAttributes    swa;
	Window                  win;
	GLXContext              glc;
	XWindowAttributes       gwa;

	const int m_inputMask = ExposureMask|StructureNotifyMask|ButtonPressMask|KeyPressMask|PointerMotionMask;
public:
	XWindowManager(const char* windowName, I32 width, I32 height, bool fullscreen);
	~XWindowManager();

	virtual void CollectInputs() override;
	virtual void PreRender() override;
	virtual void PostRender() override;
};

}

#endif