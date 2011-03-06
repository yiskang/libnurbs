CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	)

add_library(libphash lookupa.c recycle.c perfhex.c perfect.c)
set_target_properties(libphash PROPERTIES PREFIX "")

add_executable(genphash main.c)
target_link_libraries(genphash libphash)

OPTION(PHASH_EXAMPLE_BUILD "Build phash example" OFF)

IF(PHASH_EXAMPLE_BUILD)
	ADD_CUSTOM_COMMAND(
		OUTPUT phash.c
		COMMAND genphash < ${CMAKE_CURRENT_SOURCE_DIR}/examples/samperf.txt
		DEPENDS genphash
		)

	add_executable(testhash ${CMAKE_CURRENT_BINARY_DIR}/phash.c testperf.c)
	target_link_libraries(testhash libphash)
ENDIF(PHASH_EXAMPLE_BUILD)
