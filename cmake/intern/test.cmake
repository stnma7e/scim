SET (exname test_scim)

SET (PROJ_TESTS
	main
	res/TestResourceManager
)
FOREACH (test IN ITEMS ${PROJ_TESTS})
	SET (TESTS ${TESTS} ${ROOT_PATH}/test/${test}.cpp)
ENDFOREACH (test)

ADD_EXECUTABLE (${exname} ${TESTS})
TARGET_LINK_LIBRARIES(${exname} scim)

ADD_LIBRARY(unitTest++ STATIC IMPORTED)
SET_TARGET_PROPERTIES(unitTest++ PROPERTIES IMPORTED_LOCATION ${ROOT_PATH}/dep/unittest-cpp/libUnitTest++.a)
TARGET_LINK_LIBRARIES(${exname} unitTest++)
