set(ON_EXAMPLE_BREP_SRCS
		  example_brep.cpp
		  )

# Ideally, we should only need ZLIB here
include_directories(
		  ${ZLIB_INCLUDE_DIRS}
		  )

add_executable(example_brep ${ON_EXAMPLE_BREP_SRCS})
target_link_libraries(example_brep openNURBS ${OPENNURBS_LINKLIBRARIES})
