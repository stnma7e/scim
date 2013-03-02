SET (prefix ${ROOT_PATH}/src)

INCLUDE_DIRECTORIES (
	${ROOT_PATH}/dep/lfw-2.7.7/include
	${ROOT_PATH}/dep/glew-1.9.0/include
	${ROOT_PATH}/dep/glm
	${ROOT_PATH}/dep/xmlParser
)
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g3 -O0 -std=c++11")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include ${prefix}/common/Types.h")
ENDIF ()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /Wextra")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /FI ${prefix}/common/Types.h")
ENDIF()

SET (PROJ_SOURCE_PAIR
	entity/GameObject
	entity/GameObjectFactory
	entity/component/GameComponent
	entity/component/GameComponentFactory
	entity/component/ComponentCollection
	entity/component/RenderComponent
	entity/component/TransformComponent
	entity/component/manager/ComponentManager
	entity/component/manager/RenderComponentManager
	entity/component/manager/TransformComponentManager
	event/EventManager
	graphics/RenderFramework
	graphics/Mesh
	res/ResourceManager
	math/Vec3
	math/Plane
	math/Frustum
	math/MatrixStack
)
SET (PROJ_SOURCES
	main
)
SET (PROJ_HEADERS
	event/GameEvent
	common/Types
	common/Singleton
	common/Program
)

FOREACH (src IN ITEMS ${PROJ_SOURCE_PAIR})
	SET (SRCS ${SRCS} ${prefix}/${src}.cpp)
	SET (HEADERS ${HEADERS} ${prefix}/${src}.h)
ENDFOREACH (src)
FOREACH (src IN ITEMS ${PROJ_SOURCES})
	SET (SRCS ${SRCS} ${prefix}/${src}.cpp)
ENDFOREACH (src)
FOREACH (head IN ITEMS ${PROJ_HEADERS})
	SET (HEADERS ${HEADERS} ${prefix}/${head}.h)
ENDFOREACH (head)

ADD_EXECUTABLE (scim ${SRCS} ${HEADERS})
# ADD_DEPENDENCIES(scim glew glfw_proj)

ADD_LIBRARY(xmlParser ${ROOT_PATH}/dep/xmlParser/xmlParser.cpp)

SET (LINK_LIBS
	glfw
	GLEW
	GL
	xmlParser
)
FOREACH (lib ${LINK_LIBS})
	TARGET_LINK_LIBRARIES (${sbdir} ${lib})
ENDFOREACH (lib)
