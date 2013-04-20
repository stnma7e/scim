SET (libname scim)

SET (PROJ_SOURCE_PAIR
	entity/GameObject
	entity/GameObjectTools
	entity/component/GameComponent
	entity/component/GameComponentFactory
	entity/component/ComponentCollection
	entity/component/manager/ComponentManager
	event/EventManager
	graphics/RenderFramework
	graphics/IMesh
	graphics/XMLMesh
	graphics/AssimpMesh
	graphics/MeshTools
	graphics/Scene
	res/ResourceManager
)
SET (PROJ_SOURCES
)
SET (PROJ_HEADERS
	common/Types
	common/Singleton
	event/GameEvent
	event/events/CreateGameObjectEvent
	event/events/ShutdownGameEvent
)

FOREACH (src IN ITEMS ${PROJ_SOURCE_PAIR})
	SET (SRCS ${SRCS} ${ROOT_PATH}/src/${src}.cpp)
	SET (HEADERS ${HEADERS} ${ROOT_PATH}/src/${src}.h)
ENDFOREACH (src)
FOREACH (src IN ITEMS ${PROJ_SOURCES})
	SET (SRCS ${SRCS} ${ROOT_PATH}/src/${src}.cpp)
ENDFOREACH (src)
FOREACH (head IN ITEMS ${PROJ_HEADERS})
	SET (HEADERS ${HEADERS} ${ROOT_PATH}/include/${head}.h)
ENDFOREACH (head)

ADD_LIBRARY(${libname} ${SRCS} ${HEADERS})
ADD_LIBRARY(xmlParser ${ROOT_PATH}/dep/xmlParser/xmlParser.cpp)

SET (LINK_LIBS
	glfw
	GLEW
	GL
	xmlParser
	assimp
	IL
)
FOREACH (lib ${LINK_LIBS})
	TARGET_LINK_LIBRARIES (${libname} ${lib})
ENDFOREACH (lib)
