set(ON_EXAMPLE_WRITE_SRCS
		  ../example_userdata/example_ud.cpp
		  example_write.cpp
		  )

# Ideally, we should only need ZLIB here
include_directories(
		  ${ZLIB_INCLUDE_DIRS}
		  ${CMAKE_CURRENT_SOURCE_DIR}
		  )

add_executable(example_write ${ON_EXAMPLE_WRITE_SRCS})
target_link_libraries(example_write openNURBS ${OPENNURBS_LINKLIBRARIES})
