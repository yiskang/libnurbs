set(ON_EXAMPLE_GL_SRCS
		  example_gl.cpp
		  )

find_package(GLUT)

include_directories(
		  ${ZLIB_INCLUDE_DIRS}
		  ${OPENGL_INCLUDE_DIR}
		  ${GLUT_INCLUDE_DIR}
		  )

add_executable(example_gl ${ON_EXAMPLE_GL_SRCS})
target_link_libraries(example_gl openNURBS ${OPENNURBS_LINKLIBRARIES} ${GLUT_glut_LIBRARY})
