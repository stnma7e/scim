SET (exname demo_scim)

ADD_EXECUTABLE (${exname} ${ROOT_PATH}/demo/demo.cpp)
TARGET_LINK_LIBRARIES(${exname} scim)
