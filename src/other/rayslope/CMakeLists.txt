CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	)

SET(rayslope_SRCS
	aabox.cpp
	ray.cpp
	slope.cpp
	slopeint_div.cpp
	slopeint_mul.cpp
	)

add_library(rayslope ${rayslope_SRCS})

