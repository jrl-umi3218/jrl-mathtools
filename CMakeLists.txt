# Copyright (C) 2008-2013 LAAS-CNRS, JRL AIST-CNRS.
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

# Requires at least CMake 2.6 to configure the package.
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/lapack.cmake)
INCLUDE(cmake/cpack.cmake)

SET(PROJECT_NAME jrl-mathtools)
SET(PROJECT_DESCRIPTION "JRL mathematical tools")
SET(PROJECT_URL "http://github.com/jrl-umi3218/jrl-mathtools")

SET(${PROJECT_NAME}_HEADERS
    include/jrl/mathtools/angle.hh
    include/jrl/mathtools/constants.hh
    include/jrl/mathtools/fwd.hh
    include/jrl/mathtools/io.hh
    include/jrl/mathtools/vector3.hh
    include/jrl/mathtools/vector4.hh
    include/jrl/mathtools/matrix3x3.hh
    include/jrl/mathtools/matrix4x4.hh
    include/jrl/mathtools/matrixnxp.hh
    include/jrl/mathtools/vectorn.hh
)

SETUP_PROJECT()

# Search for dependencies.
SEARCH_FOR_BOOST()
SEARCH_FOR_LAPACK()

ADD_SUBDIRECTORY(tests)

SETUP_PROJECT_FINALIZE()
SETUP_PROJECT_CPACK()
