include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${GLUT_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR_GL}
	)

add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)
add_executable(example3 example3.cpp)
add_executable(example4 example4.cpp)
add_executable(example5 example5.cpp)
add_executable(example6 example6.cpp)
target_link_libraries(example1 ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY} glui)
target_link_libraries(example2 ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY} glui)
target_link_libraries(example3 ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY} glui)
target_link_libraries(example4 ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY} glui)
target_link_libraries(example5 ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY} glui)
target_link_libraries(example6 ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_glut_LIBRARY} glui)
