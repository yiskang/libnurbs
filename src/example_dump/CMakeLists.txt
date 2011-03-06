set(ON_EXAMPLE_DUMP_SRCS
		  example_dump.cpp
		  )

# Ideally, we should only need ZLIB here
include_directories(
		  ${ZLIB_INCLUDE_DIRS}
		  )

add_executable(example_dump ${ON_EXAMPLE_DUMP_SRCS})
target_link_libraries(example_dump openNURBS ${OPENNURBS_LINKLIBRARIES})
