#include "input/XWindowManager.h"
#include "input/InputTools.h"
#include "event/EventManager.h"
#include "event/events/ShutdownGameEvent.h"

#include <stdio.h>
#include <stdlib.h>

namespace scim
{

extern EventManager* g_eventManager;

XWindowManager::XWindowManager(const char* windowName, I32 width, I32 height, bool fullscreen)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

	dpy = XOpenDisplay(NULL);
	if(dpy == NULL)
	{
	    printf("\n\tcannot connect to X server\n\n");
	    return;
	}
	    
	root = DefaultRootWindow(dpy);
	vi = glXChooseVisual(dpy, 0, att);
	if(vi == NULL)
	{
	    printf("\n\tno appropriate visual found\n\n");
	    exit(0);
	} else
	{
	    printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
	}

	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(dpy, win);
	XStoreName(dpy, win, windowName);

	XSelectInput(dpy, win, m_inputMask);

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
}
XWindowManager::~XWindowManager()
{
	glXMakeCurrent(dpy, None, NULL);
	glXDestroyContext(dpy, glc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void XWindowManager::CollectInputs()
{
	XEvent xev;
	Input inpt =  { 0x00000000, 0x00000000, 0.0f, 0.0f, 0, 0 };
	while (XCheckWindowEvent(dpy, win, m_inputMask, &xev))
	{
		switch(xev.type)
		{
		case Expose:
			{
				glXSwapBuffers(dpy, win);
			}
			break;
		case ConfigureNotify:
			{
				XConfigureEvent xce = xev.xconfigure;
				inpt.window_w = xce.width;
				inpt.window_h = xce.height;
			}
			break;
		case KeyPress:
		case KeyRelease:
			{
				char string[25];
				KeySym keysym;
				I32 len = XLookupString(&xev.xkey, string, 25, &keysym, NULL);
				if (len > 0)
				{
					GetKeypressAndUpdate(string[0], &inpt);
				} else
				{
					switch (keysym)
					{
					case 0xff51:
						{
							inpt.specialKeys = inpt.specialKeys | SCIM_KEY_LEFT;
						}	
						break;
					case 0xff53:
						{
							inpt.specialKeys = inpt.specialKeys | SCIM_KEY_RIGHT;
						}	
						break;
					case 0xff52:
						{
							inpt.specialKeys = inpt.specialKeys | SCIM_KEY_UP;
						}	
						break;
					case 0xff54:
						{
							inpt.specialKeys = inpt.specialKeys | SCIM_KEY_DOWN;
						}	
						break;
					}
				}
			}
			break;
		case MotionNotify:
			{
				XMotionEvent xme = xev.xmotion;
				inpt.mousePosX = xme.x_root;
				inpt.mousePosY = xme.y_root;
			}
			break;
		}

		memset(&xev, 0, sizeof(xev));
	}

	m_collectedInputs = inpt;
}
void XWindowManager::PreRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void XWindowManager::PostRender()
{
	glXSwapBuffers(dpy, win);
}

}