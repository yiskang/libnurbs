include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../../include
	${CMAKE_CURRENT_BINARY_DIR}/../../include
	${OPENGL_INCLUDE_DIR_GL}
	)

SET(CallbackMaker_SRCS
	CallbackMaker.c 
	)

add_executable(CallbackMaker ${CallbackMaker_SRCS})
target_link_libraries(CallbackMaker freeglut)
