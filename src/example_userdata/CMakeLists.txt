set(ON_EXAMPLE_USERDATA_SRCS
		  example_ud.cpp
		  example_userdata.cpp
		  )

# Ideally, we should only need ZLIB here
include_directories(
		  ${ZLIB_INCLUDE_DIRS}
		  ${CMAKE_CURRENT_SOURCE_DIR}
		  )

add_executable(example_userdata ${ON_EXAMPLE_USERDATA_SRCS})
target_link_libraries(example_userdata openNURBS ${OPENNURBS_LINKLIBRARIES})
