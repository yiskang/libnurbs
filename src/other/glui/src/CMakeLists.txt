include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${CMAKE_CURRENT_BINARY_DIR}/../include
	${GLUT_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR_GL}
	)

SET(GLUI_C_SRCS
	glui_img_checkbox_0.c
	glui_img_checkbox_0_dis.c
	glui_img_checkbox_1.c
	glui_img_checkbox_1_dis.c
	glui_img_downarrow.c
	glui_img_leftarrow.c
	glui_img_listbox_down.c
	glui_img_listbox_up.c
	glui_img_listbox_up_dis.c
	glui_img_radiobutton_0.c
	glui_img_radiobutton_0_dis.c
	glui_img_radiobutton_1.c
	glui_img_radiobutton_1_dis.c
	glui_img_rightarrow.c
	glui_img_spindown_0.c
	glui_img_spindown_1.c
	glui_img_spindown_dis.c
	glui_img_spinup_0.c
	glui_img_spinup_1.c
	glui_img_spinup_dis.c
	glui_img_uparrow.c
	)

SET(GLUI_SRCS
	algebra3.cpp  
	arcball.cpp 
#  glui_bitmap_img_data.cpp  
	glui_button.cpp  
	glui_checkbox.cpp  
	glui_column.cpp  
	glui_control.cpp  
	glui_edittext.cpp
	glui_filebrowser.cpp
	glui_listbox.cpp  
	glui_mouse_iaction.cpp  
	glui_node.cpp  
	glui_panel.cpp  
	glui_radio.cpp  
	glui_rollout.cpp  
	glui_rotation.cpp  
	glui_rotation.cpp 
	glui_separator.cpp  
	glui_spinner.cpp  
	glui_translation.cpp   
	glui_window.cpp  
	quaternion.cpp 
	viewmodel.cpp 
	glui_bitmaps.cpp  
	glui_statictext.cpp  
	glui.cpp  
	glui_add_controls.cpp  
	glui_commandline.cpp  
	glui_list.cpp  
	glui_scrollbar.cpp  
	glui_string.cpp 
	glui_textbox.cpp  
	glui_tree.cpp  
	glui_treepanel.cpp
	)

add_library(glui SHARED ${GLUI_C_SRCS} ${GLUI_SRCS})
target_link_libraries(glui ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
install(TARGETS glui DESTINATION lib)
