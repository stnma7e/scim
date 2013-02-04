SET (prefix ${ROOT_PATH}/src)

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
	res/ResourceManager
	math/Vec3
	math/Plane
	math/Frustum
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
ADD_DEPENDENCIES(scim glew glfw_proj)

ADD_LIBRARY(xmlParser ${ROOT_PATH}/dep/xmlParser/xmlParser.cpp)

SET (LINK_LIBS
	glfw
	GLEW
	xmlParser
)
FOREACH (lib ${LINK_LIBS})
	TARGET_LINK_LIBRARIES (${sbdir} ${lib})
ENDFOREACH (lib)
