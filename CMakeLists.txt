# Copyright 2008, 2009, 2010, Olivier Stasse, JRL, CNRS/AIST
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
# Creation: 30/10/2008
#

cmake_minimum_required(VERSION 2.6)

enable_language(CXX)
enable_language(Fortran)

# Debug mode for cmake.
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Set version
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 4)
set(CPACK_PACKAGE_VERSION_PATCH 0)

SET(PROJECT_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.99)

# name of the project
SET(PROJECT_NAME jrlMathTools)
project(${PROJECT_NAME})

IF(WIN32)
  SET(LIBDIR_KW "/LIBPATH:")
  SET(LIBINCLUSION_KW "")
ENDIF(WIN32)

IF(UNIX)
  SET(LIBDIR_KW "-L")
  SET(LIBINCLUSION_KW "-l")
ENDIF(UNIX)

ENABLE_TESTING()

# where are use-specific cmake modules
SET(CMAKE_MODULE_PATH ${${PROJECT_NAME}_SOURCE_DIR}/CMakeModules)

# Prepare the documentation
# -------------------------
OPTION(GENERATE_DOC 1 "Generate html documentation")
IF (GENERATE_DOC)
  INCLUDE(FindDoxygen)
  IF(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen found")
	ADD_SUBDIRECTORY(doc)
  ENDIF(DOXYGEN_FOUND)
ENDIF (GENERATE_DOC)

# Looking for LAPACK
# -------------------
INCLUDE(FindLAPACK)

# Looking for boost.
# -------------------------
INCLUDE(FindBoost)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE( Boost 1.33.1 )

IF(LAPACK_FOUND)
  IF(Boost_FOUND)
    MESSAGE(STATUS "Boost has been found")
    SET(${PROJECT_NAME}_CFLAGS "-I${Boost_INCLUDE_DIR} ")
    SET(${EXPORT_CFLAGS} "-I${Boost_INCLUDE_DIR}")
	SET(${PROJECT_NAME}_LDFLAGS "")
	SET(EXPORT_LDFLAGS "")
	foreach(boost_lib_dir ${Boost_LIBRARY_DIRS})
	  SET(${PROJECT_NAME}_LDFLAGS 
	    "${${PROJECT_NAME}_LDFLAGS} ${LIBDIR_KW}${boost_lib_dir} ")
	  SET(EXPORT_LDFLAGS 
	    "${EXPORT_LDFLAGS} ${LIBDIR_KW}${boost_lib_dir} ")
	endforeach(boost_lib_dir)
	foreach(lapack_lib ${LAPACK_LIBRARIES})
	  SET(${PROJECT_NAME}_LDFLAGS 
	    "${${PROJECT_NAME}_LDFLAGS} ${lapack_lib} ")
	  SET($EXPORT_LDFLAGS 
	    "${EXPORT_LDFLAGS} ${lapack_lib} ")
	endforeach(lapack_lib)
	IF (WIN32)
	  SET(${PROJECT_NAME}_CFLAGS 
	    "${${PROJECT_NAME}_CFLAGS} -DBOOST_NUMERIC_BINDINGS_USE_CLAPACK" )
	  SET(EXPORT_CFLAGS 
	    "${EXPORT_CFLAGS} -DBOOST_NUMERIC_BINDINGS_USE_CLAPACK" )

	  IF (NOT ${Boost_VERSION} LESS 104000)
	    OPTION(FORCE_COMPILATION_WITH_BOOST "Force the compilation wit" OFF)
	    IF(NOT FORCE_COMPILATION_WITH_BOOST )
	      MESSAGE (FATAL_ERROR "It is most likely that the Visual studio compilers cl.exe and rc.exe will crash due to Boost 1.40 or higher "
		  "(this issue has been observed in Windows XP/Vista for Visual studio 8 2005, 9 2008, 10 beta)\n"
		  "If you want to use this version anyway, please switch the macro FORCE_COMPILATION_WITH_BOOST to ON "
		  "and please note that a patch consists in commenting the lines 522 to 531 and 696 to 705 of the file boost/numeric/ublas/detail/raw.hpp"
		  )
	    ENDIF(NOT FORCE_COMPILATION_WITH_BOOST)
	  ENDIF (NOT ${Boost_VERSION} LESS 104000)
	ENDIF (WIN32)

  ELSE(Boost_FOUND)
    # TO DO : find vnl...
  ENDIF(Boost_FOUND)

ENDIF(LAPACK_FOUND)

# --- BOOST NUMERIC BINDINGS-------------------------------------

IF(${Boost_VERSION} LESS 104000)
  INCLUDE(${CMAKE_MODULE_PATH}/FindBoostNumericBindings.cmake)
  MESSAGE(STATUS "BoostNumericBindings_INCLUDE_DIR=${BoostNumericBindings_INCLUDE_DIR}")
  INCLUDE_DIRECTORIES(${BoostNumericBindings_INCLUDE_DIR})
  SET(${PROJECT_NAME}_CFLAGS 
    "${${PROJECT_NAME}_CFLAGS} -I${BoostNumericBindings_INCLUDE_DIR}"
    )
  SET(EXPORT_CFLAGS "${EXPORT_CFLAGS} -I${BoostNumericBindings_INCLUDE_DIR}")
ENDIF(${Boost_VERSION} LESS 104000)

MESSAGE(STATUS "Cflags :" ${${PROJECT_NAME}_CFLAGS} )
MESSAGE(STATUS "Ldflags :" ${${PROJECT_NAME}_LDFLAGS} )

# Prepare description file for pkg-config.
#-----------------------------------------

SET(install_pkg_prefix "\${prefix}")
SET(install_pkg_exec_prefix "\${exec_prefix}")
SET(install_pkg_libdir "\${libdir}")
SET(install_pkg_datarootdir "\${datarootdir}")
SET(install_pkg_include_dir "\${includedir}")

# Install the file in the appropriate place.
SET(install_libdir_pkgconfig lib/pkgconfig)
CONFIGURE_FILE(${jrlMathTools_SOURCE_DIR}/jrlMathTools.pc.cmake
	       ${jrlMathTools_BINARY_DIR}/jrlMathTools.pc )

SET(jrlMathTools_HEADERS
    ./include/jrlMathTools/jrlConstants.h
    ./include/jrlMathTools/angle.h
    ./include/jrlMathTools/vector3.h
    ./include/jrlMathTools/vector4.h
    ./include/jrlMathTools/matrix3x3.h
    ./include/jrlMathTools/matrix4x4.h
    ./include/jrlMathTools/matrixNxP.h
    ./include/jrlMathTools/vectorN.h
)

#----------------------------------------------------
# Install procedure for the header files
#----------------------------------------------------
INSTALL(FILES ${jrlMathTools_HEADERS}
	DESTINATION include/jrlMathTools
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

INSTALL(FILES ${jrlMathTools_BINARY_DIR}/jrlMathTools.pc
	DESTINATION ${install_libdir_pkgconfig}
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

#-----------------
# Uninstall target 
#-----------------
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

ADD_SUBDIRECTORY(unitTesting)

#----------------
# Package part
#----------------
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "JRL Math Tools- Provides small size matrices efficient implementation")
set(CPACK_PACKAGE_VENDOR "JRL CNRS/AIST")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Olivier Stasse (olivier.stasse@aist.go.jp)")

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set(CPACK_SOURCE_IGNORE_FILES
"~$"
"^${PROJECT_SOURCE_DIR}/build/"
"^${PROJECT_SOURCE_DIR}/.git/"
)
set(
CPACK_SOURCE_PACKAGE_FILE_NAME
"jrlmathtools-src-${PROJECT_VERSION}"
CACHE INTERNAL "tarball basename"
)
set(CPACK_PACKAGE_NAME "jrlmathtools")
set(CPACK_BINARY_DEB "ON")
set(CPACK_GENERATOR TGZ)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/share/openrobots")
#message("CPACK_SOURCE_IGNORE_FILES = ${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)



