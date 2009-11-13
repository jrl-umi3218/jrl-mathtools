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

ADD_EXECUTABLE(testPseudoInverse testPseudoInverse.cpp)
SET_TARGET_PROPERTIES(testPseudoInverse
	              PROPERTIES
		      COMPILE_FLAGS "${${PROJECT_NAME}_test_CXXFLAGS}"
		      LINK_FLAGS "${${PROJECT_NAME}_test_LDFLAGS}"
)
ADD_TEST(pseudoInverse testPseudoInverse "")

ADD_EXECUTABLE(testDampedInverse testDampedInverse.cpp)
SET_TARGET_PROPERTIES(testDampedInverse
	              PROPERTIES
		      COMPILE_FLAGS "${${PROJECT_NAME}_test_CXXFLAGS}"
		      LINK_FLAGS "${${PROJECT_NAME}_test_LDFLAGS}"
)
ADD_TEST(dampedInverse testDampedInverse "")

ADD_EXECUTABLE(testOptimizedJpJt testOptimizedJpJt.cpp)
SET_TARGET_PROPERTIES(testOptimizedJpJt
	              PROPERTIES
		      COMPILE_FLAGS "${${PROJECT_NAME}_test_CXXFLAGS}"
		      LINK_FLAGS "${${PROJECT_NAME}_test_LDFLAGS}"
)
ADD_TEST(optimizedJpJt testOptimizedJpJt "")
