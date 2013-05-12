CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (PROJ_NAME scim)
PROJECT (${PROJ_NAME})

SET (ROOT_PATH ${CMAKE_SOURCE_DIR}/..)

IF (${CMAKE_GENERATOR} STREQUAL Ninja)
	SET (builderName ninja)
ELSEIF (${CMAKE_GENERATOR} STREQUAL Ninja)
	SET (builderName make)
ENDIF (${CMAKE_GENERATOR} STREQUAL Ninja)

#INCLUDE (ExternalProject)
#ExternalProject_Add(glew
#	SOURCE_DIR ${ROOT_PATH}/dep/glew-1.9.0
#	CONFIGURE_COMMAND ""
#	BUILD_COMMAND make
#	BUILD_IN_SOURCE 1
#	INSTALL_COMMAND ""
#)
#ExternalProject_Add(glfw_proj
#	SOURCE_DIR ${ROOT_PATH}/dep/glfw-2.7.7
#	CONFIGURE_COMMAND "./compile.sh"
#	BUILD_COMMAND make x11
#	BUILD_IN_SOURCE 1
#	INSTALL_COMMAND ""
#)

SET (SUBDIRS
	intern
)
FOREACH (sbdir ${SUBDIRS})
	ADD_SUBDIRECTORY (${sbdir})
ENDFOREACH (sbdir)
