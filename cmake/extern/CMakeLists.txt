SET (SUBPROJ
	glfw
)
FOREACH (sbproj ${SUBPROJ})
	include (${sbproj}.cmake)
ENDFOREACH (sbproj)
