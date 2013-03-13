SET (prefix ${ROOT_PATH}/src)

INCLUDE_DIRECTORIES (
	${ROOT_PATH}/dep/lfw-2.7.7/include
	${ROOT_PATH}/dep/glew-1.9.0/include
	${ROOT_PATH}/dep/glm
	${ROOT_PATH}/dep/xmlParser
	${ROOT_PATH}/dep/unittest-cpp/src
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
	entity/component/manager/ComponentManager
	entity/component/manager/RenderComponentManager
	event/EventManager
	graphics/RenderFramework
	graphics/Mesh
	graphics/Scene
	res/ResourceManager
	math/Vec3
	math/Plane
	math/Frustum
	math/MatrixStack
)
SET (PROJ_SOURCES
)
SET (PROJ_HEADERS
	common/Types
	common/Singleton
	common/Logger
	event/GameEvent
	event/events/CreateGameObjectEvent
	event/events/ShutdownGameEvent
)
SET (PROJ_TESTS
	testMain
	res/test/TestResourceManager
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
FOREACH (test IN ITEMS ${PROJ_TESTS})
	SET (TESTS ${TESTS} ${prefix}/${test}.cpp)
ENDFOREACH (test)

ADD_LIBRARY(${sbdir} ${SRCS} ${HEADERS})
ADD_EXECUTABLE (run${sbdir} ${ROOT_PATH}/src/main.cpp)
ADD_EXECUTABLE (test${sbdir} ${TESTS})

ADD_LIBRARY(xmlParser ${ROOT_PATH}/dep/xmlParser/xmlParser.cpp)

ADD_LIBRARY(unitTest++ STATIC IMPORTED)
SET_TARGET_PROPERTIES(unitTest++ PROPERTIES IMPORTED_LOCATION ${ROOT_PATH}/dep/unittest-cpp/libUnitTest++.a)
TARGET_LINK_LIBRARIES(test${sbdir} unitTest++)

SET (LINK_LIBS
	glfw
	GLEW
	GL
	xmlParser
)
FOREACH (lib ${LINK_LIBS})
	TARGET_LINK_LIBRARIES (${sbdir} ${lib})
ENDFOREACH (lib)

TARGET_LINK_LIBRARIES(run${sbdir} ${sbdir})
TARGET_LINK_LIBRARIES(test${sbdir} ${sbdir})
