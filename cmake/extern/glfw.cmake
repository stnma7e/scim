INCLUDE (ExternalProject)

SET (CXX_LINKER_FLAGS ${CXX_LINKER_FLAGS} -lpthread)

ExternalProject_Add(glfw
	CMAKE_ARGS "-D glfw_LIBRARIES:${glfw_LIBRARIES} pthread=on"
	DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/dload/glfw
	GIT_REPOSITORY git://github.com/glfw/glfw.git
	BUILD_COMMAND ${builderName} glfw
	BUILD_IN_SOURCE 1
	INSTALL_DIR ${CMAKE_SOURCE_DIR}/install
)