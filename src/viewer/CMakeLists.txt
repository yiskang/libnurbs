set(ON_VIEWER_SRCS
	viewer.cpp
	)

include_directories(
	${ZLIB_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIR}
	${GLUT_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../other/glui/include
	)

add_executable(on_viewer ${ON_VIEWER_SRCS})
target_link_libraries(on_viewer openNURBS ${OPENNURBS_LINKLIBRARIES}	${GLUT_glut_LIBRARY} glui)
