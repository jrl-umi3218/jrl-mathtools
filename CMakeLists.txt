# Copyright 2008, 2009, 2010, Olivier Stasse, JRL, CNRS/AIST
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
INCLUDE(cmake/cpack.cmake)

SET(PROJECT_NAME jrl-mathtools)
SET(PROJECT_VERSION 1.4.0.99)
SET(PROJECT_DESCRIPTION "JRL mathematical tools")
SET(PROJECT_URL "http://github.com/jrl-umi3218/jrl-cmakemodules")


SET(${PROJECT_NAME}_HEADERS
    include/jrl/mathtools/angle.hh
    include/jrl/mathtools/constants.hh
    include/jrl/mathtools/fwd.hh
    include/jrl/mathtools/io.hh
    include/jrl/mathtools/vector3.hh
    include/jrl/mathtools/vector4.hh
    include/jrl/mathtools/matrix3x3.hh
    include/jrl/mathtools/matrix4x4.hh
    include/jrl/mathtools/matrixNxP.hh
    include/jrl/mathtools/vectorN.hh
)

SETUP_PROJECT()
SETUP_PROJECT_CPACK()

# Requires Fortran support as Lapack needs it.
ENABLE_LANGUAGE(Fortran)

# Search for Boost.
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.40 COMPONENTS unit_test_framework REQUIRED)
SET(PKG_CONFIG_CFLAGS "${PKG_CONFIG_CFLAGS} -I${Boost_INCLUDE_DIR}")
SET(PKG_CONFIG_LIBS "${PKG_CONFIG_LIBS} ${LIBDIR_KW}${Boost_LIBRARY_DIRS}")

# Search for LAPACK.
FIND_PACKAGE(LAPACK REQUIRED)

# Deprecated headers
# These headers are installed to preserve includes retro-compatbility.
SET(DEPRECATED_HEADERS
    include/jrlMathTools/jrlConstants.h
    include/jrlMathTools/angle.h
    include/jrlMathTools/vector3.h
    include/jrlMathTools/vector4.h
    include/jrlMathTools/matrix3x3.h
    include/jrlMathTools/matrix4x4.h
    include/jrlMathTools/matrixNxP.h
    include/jrlMathTools/vectorN.h
)
INSTALL(FILES ${DEPRECATED_HEADERS}
  DESTINATION include/jrlMathTools
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
  )

# Install jrlMathTools.pc for retro-compatibility.
INSTALL(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
  DESTINATION "${PKG_CONFIG_DIR}"
  RENAME jrlMathTools.pc
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE)

ADD_SUBDIRECTORY(tests)

SETUP_PROJECT_FINALIZE()
