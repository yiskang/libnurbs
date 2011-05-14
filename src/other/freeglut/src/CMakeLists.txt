include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${CMAKE_CURRENT_BINARY_DIR}/../include
	${OPENGL_INCLUDE_DIR_GL}
	)

SET(FREEGLUT_SRCS
	freeglut_callbacks.c 
	freeglut_cursor.c 
	freeglut_display.c 
	freeglut_ext.c 
	freeglut_font.c 
	freeglut_glutfont_definitions.c 
	freeglut_font_data.c 
	freeglut_stroke_roman.c 
	freeglut_stroke_mono_roman.c 
	freeglut_gamemode.c 
	freeglut_geometry.c 
	freeglut_init.c 
	freeglut_input_devices.c 
	freeglut_spaceball.c 
	freeglut_joystick.c 
	freeglut_main.c 
	freeglut_menu.c 
	freeglut_misc.c 
	freeglut_overlay.c 
	freeglut_state.c 
	freeglut_structure.c 
	freeglut_teapot.c 
	freeglut_videoresize.c 
	freeglut_window.c
	)

add_library(freeglut SHARED ${FREEGLUT_SRCS})
target_link_libraries(freeglut ${M_LIBRARY} ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
install(TARGETS freeglut DESTINATION lib)
