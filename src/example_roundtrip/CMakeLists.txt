set(ON_EXAMPLE_ROUNDTRIP_SRCS
		  example_roundtrip.cpp
		  )

# Ideally, we should only need ZLIB here
include_directories(
		  ${ZLIB_INCLUDE_DIRS}
		  )

add_executable(example_roundtrip ${ON_EXAMPLE_ROUNDTRIP_SRCS})
target_link_libraries(example_roundtrip openNURBS ${OPENNURBS_LINKLIBRARIES})
