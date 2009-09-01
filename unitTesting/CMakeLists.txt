#
# Copyright JRL AIST-CNRS
#
# Authors: Olivier Stasse, Florent Lamiraux
#

INCLUDE(CTest)

SET(${PROJECT_NAME}_test_CXXFLAGS "-I${PROJECT_SOURCE_DIR}/include/ ${${PROJECT_NAME}_CFLAGS}")

# For the test, we link with the library corresponding to the src,  which is not installed yet
SET(${PROJECT_NAME}_test_LDFLAGS "${${PROJECT_NAME}_LDFLAGS}")

MESSAGE(STATUS " unitTesting: ${${PROJECT_NAME}_test_CXXFLAGS}")
MESSAGE(STATUS " unitTesting: ${${PROJECT_NAME}_test_LDFLAGS}")

ADD_EXECUTABLE(testpseudoinverse testpseudoinverse.cpp)
SET_TARGET_PROPERTIES(testpseudoinverse
	              PROPERTIES
		      COMPILE_FLAGS ${${PROJECT_NAME}_test_CXXFLAGS}
		      LINK_FLAGS ${${PROJECT_NAME}_test_LDFLAGS}
)

ADD_TEST(pseudoinverse testpseudoinverse "")
