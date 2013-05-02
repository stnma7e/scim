INCLUDE_DIRECTORIES (
	${ROOT_PATH}/include
	${ROOT_PATH}/dep/glfw/include
	${ROOT_PATH}/dep/glew/include
	${ROOT_PATH}/dep/glm
	${ROOT_PATH}/dep/xmlParser
	${ROOT_PATH}/dep/unittest-cpp/src
	${ROOT_PATH}/dep/logging/include
	${ROOT_PATH}/dep/assimp-3.0.1270/include
	${ROOT_PATH}/dep/devil-1.7.8/include

)

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g3 -O0 -std=c++11")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include ${ROOT_PATH}/include/common/Types.h")
ENDIF ()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /Wextra")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /FI ${ROOT_PATH}/include/common/Types.h")
ENDIF()

SET (SUBPROJ
	scim
	demo
	test
)
FOREACH (sbproj ${SUBPROJ})
	include (${sbproj}.cmake)
ENDFOREACH (sbproj)
