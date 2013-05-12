// demo.cpp
// creates a window context, then loads a mesh, then renders

#include "entity/component/GameComponent.h"
#include "graphics/RenderFramework.h"
#include "entity/component/ComponentCollection.h"
#include "res/ResourceManager.h"
#include "graphics/Scene.h"
#include "event/EventManager.h"
#include "event/events/CreateGameObjectEvent.h"
#include "event/events/ShutdownGameEvent.h"
#include "graphics/XMLMesh.h"
#include "graphics/MeshTools.h"
#include "net/UnixSocket.h"
#include "input/InputTools.h"
#include "input/XWindowManager.h"
#include "input/NetworkInputHandler.h"

#include "ScimProtocol.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <errno.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <logging/logging.h>
#include <IL/il.h>
#include <GL/glfw3.h>

using namespace scim;
using namespace logging;

bool init();
void shutdown();
void shutdown_delegate(GameEvent*);

bool stopFlag;

namespace scim
{
	Scene*						g_currentScene;
	EventManager*				g_eventManager;
	IWindowManager* 			g_curWindow;
	ISocket*					g_authSocket;
	ISocket*					g_portalSocket;
	NetworkInputHandler*		g_netInputHandler;
}

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		printf("USAGE: %s\n", argv[0]);
		for (int i = 1; i < argc; ++i)
		{
			std::cout << "\tinvalid arg: \"" << argv[i] << "\"" << std::endl;
		}
		return 1;
	}

	UnixSocket asock("127.0.0.1", "13572");
	g_authSocket = &asock;

	std::string portalIP, portalPort;

	const size_t size = sizeof(Connect);
	Connect c =
	{
		0x0000,
		0x15,
		0xA,
		"svdelmerico@gmail.com",
		"gatorade12"
	};
	for (size_t i = 0; i < 1; ++i)
	{
		if (!g_authSocket->BlockSend((char*)&c, size))
		{
			printf("send failed\n");
			return 1;
		}
		char buf[501];
		memset(buf, 0, sizeof(buf));
		I32 len = g_authSocket->Recieve(buf, 500);
		if (len == -1)
		{
			U32 errsv = errno;
			if (errsv == 107)
				printf("no connection. is server down?\n");
			else if (errsv == 11)
				printf("nonblock no connection\n");
			else 
				printf("errno: %d\n", errsv);
			return 1;
		}
		printf("len: %d\n", len);
		printf("hex: ");
		for (I32 i = 0; i < len; ++i)
		{
			printf("%x ", buf[i]);
		}
		printf("\n");
		printf("str: %s\n", buf);
		U32 id = 0;
		if ((id = buf[0]))
		{
			printf("auth'd: %u\n", id);
			RequestPortal rqp =
			{
				0x0300,
				id
			};
			g_authSocket->BlockSend((char*)&rqp, sizeof(RequestPortal));

			const I32 bufSize = 501;
			char buf[bufSize];
			memset(buf, 0, sizeof(buf));
			I32 len = g_authSocket->Recieve(buf, 500);
			printf("hex: ");
			for (I32 i = 0; i < len; ++i)
			{
				printf("%x ", buf[i]);
			}
			puts("");
			printf("str: %s\n", buf);
			I32 ilen = 0;
			for (;;++ilen)
			{
				if (buf[ilen] == ' ')
				{
					buf[ilen] ='\0';
					break;
				}
			}
			portalIP.assign(buf, ilen+1);
			portalPort.assign(&buf[ilen+1], bufSize - (ilen + 1));
		}
	}

	Scene sc;
	EventManager em;
	UnixSocket psock(portalIP, portalPort);
	NetworkInputHandler nethndl(&psock);

	g_currentScene 		= &sc;
	g_eventManager 		= &em;
	g_portalSocket 		= &psock;
	g_netInputHandler 	= &nethndl;

	g_portalSocket->BlockSend((char*)&c, size);

	if (!init())
	{
		shutdown();
		log::emit<logging::Error>() << "Initialization failed" << log::endl;
		return 1;
	}

	stopFlag = false;

	std::string cubeFile = ResourceManager::GetFileContents<std::string>("entity/cube.xml");
	XMLResults* res = NULL;
	XMLNode cubeNode = XMLNode::parseString(cubeFile.c_str(), "breed", res);
	if (res)
	{
		log::emit<logging::Error>() << "Invalid XML resource" << log::endl;
		shutdown();
		return 1;
	}

	g_eventManager->AddListener(GameObjectTools::CreateGameObject, GameEvent::CREATE_GAMEOBJECT);
	g_eventManager->AddListener(shutdown_delegate, GameEvent::SHUTDOWN);

	const int numObjs = 1;
	GameObject* go[numObjs];

	try
	{
		for (int i = 0; i < numObjs; ++i)
		{
			if (!g_eventManager->TriggerEvent(new CreateGameObjectEvent(1.0f, &go[i], cubeNode)))
			{
				log::emit<logging::Error>() << "Failed to queue event" << log::endl;
			}
		}
	} catch (std::runtime_error& e)
	{
		log::emit<logging::Error>() << e.what() << log::endl;
	}

	size_t i = 0;
	size_t nFrames = 0;
	F64 oldTime = glfwGetTime();
	while (!stopFlag)
	{
		// Measure speed
		F64 currentTime = glfwGetTime();
		nFrames++;
		if ( currentTime - oldTime >= 1.0 ) // If last printf() was more than 1 sec ago
		{
			std::cout << (1000.0f / (F64)nFrames) << " ms/frame" << std::endl;
			nFrames = 0;
			oldTime += 1.0;
		}

		if (i % 100 == 0)
		{
			for (int i = 0; i < numObjs; ++i)
			{
				// log::emit<logging::Info>() << "id: " << go[i]->GetID() << ", type: " << go[i]->GetType() << log::endl;
				// glm::mat4* mat = g_scene->GetNode(go[i]->GetSceneNodeIndex()).wmat;
				// Scene::PrintMatrix(*mat);
			}

		}

		g_curWindow->CollectInputs();
		g_netInputHandler->CollectInputs();

		RenderFramework::OnUpdate(currentTime - oldTime);
		g_currentScene->UpdateNodes();
		g_curWindow->PreRender();

		g_currentScene->RenderNodes();

		g_curWindow->PostRender();
		g_eventManager->OnUpdate(0.01f);

		++i;
	}

	for (int i = 0; i < numObjs; ++i)
	{
		delete go[i];
	}

	shutdown();

	std::cout << std::endl << "exit." << std::endl;

	return 0;
}
bool init()
{
	bool success = true;

	success &= RenderFramework::Init();

	return success;
}
void shutdown_delegate(GameEvent* evt)
{
	log::emit<logging::Info>() << ((ShutdownGameEvent*)evt)->GetShutdownString() << log::endl;
	stopFlag = true;
	delete evt;
}
void shutdown()
{
	RenderFramework::Shutdown();
}
