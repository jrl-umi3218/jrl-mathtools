# Copyright 2008, 2009, 2010, Olivier Stasse, 
#                             Florent Lamiraux,JRL, CNRS/AIST
#
# This file is part of jrlMathTools.
# jrlMathTools is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# jrlMathTools is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Lesser Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with jrlMathTools.  If not, see <http://www.gnu.org/licenses/>.
#

INCLUDE(CTest)

SET(${PROJECT_NAME}_test_CXXFLAGS "-I${PROJECT_SOURCE_DIR}/include/ ${${PROJECT_NAME}_CFLAGS}")

if(WIN32)
	set(WIN32_CXXFLAGS "-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE")
	set(${PROJECT_NAME}_test_CXXFLAGS "${${PROJECT_NAME}_test_CXXFLAGS} ${WIN32_CXXFLAGS}")
endif(WIN32)

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
