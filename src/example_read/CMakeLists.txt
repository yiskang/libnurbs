set(ON_EXAMPLE_READ_SRCS
		  example_read.cpp
		  )

# Ideally, we should only need ZLIB here
include_directories(
		  ${ZLIB_INCLUDE_DIRS}
		  )

add_executable(example_read ${ON_EXAMPLE_READ_SRCS})
target_link_libraries(example_read openNURBS ${OPENNURBS_LINKLIBRARIES})
