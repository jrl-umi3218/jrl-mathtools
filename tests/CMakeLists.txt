# Copyright 2008, 2009, 2010, Olivier Stasse,
#                             Florent Lamiraux,JRL, CNRS/AIST
#
# This file is part of jrl-mathtools.
# jrl-mathtools is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# jrl-mathtools is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Lesser Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with jrl-mathtools.  If not, see <http://www.gnu.org/licenses/>.

# Add Boost path to include directories.
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# Make Boost.Test generates the main function in test cases.
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

# JRL_MATHTOOLS_TEST(NAME)
# ------------------------
#
# Define a test named `NAME'.
#
MACRO(JRL_MATHTOOLS_TEST NAME)
  ADD_EXECUTABLE(${NAME} ${NAME}.cc)
  ADD_TEST(${NAME} ${RUNTIME_OUTPUT_DIRECTORY}/${NAME})

  # Link against LAPACK.
  TARGET_LINK_LIBRARIES(${NAME} ${LAPACK_LIBRARIES})

  # Link against Boost.
  TARGET_LINK_LIBRARIES(${NAME} ${Boost_LIBRARIES})
ENDMACRO(JRL_MATHTOOLS_TEST)

# Angle tests.
JRL_MATHTOOLS_TEST(angle)

# Vector tests.
JRL_MATHTOOLS_TEST(vector3)
JRL_MATHTOOLS_TEST(vector4)

# Matrix tests.

# Algorithm tests.
JRL_MATHTOOLS_TEST(pseudo-inverse)
JRL_MATHTOOLS_TEST(damped-inverse)
JRL_MATHTOOLS_TEST(optimized-JpJt)
