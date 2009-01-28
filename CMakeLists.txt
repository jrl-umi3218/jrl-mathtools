# Olivier Stasse, JRL, CNRS/AIST
# Creation: 30/10/2008
# History:
#
# Copyright CNRS/AIST
cmake_minimum_required(VERSION 2.6)

enable_language(CXX)

# Debug mode for cmake.
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Set version
SET(PROJECT_VERSION 1.1)

# name of the project
SET(PROJECT_NAME jrlMathTools)
project(${PROJECT_NAME})

SET(CMAKE_INSTALL_PREFIX $ENV{ROBOTPKG_PATH})

# Prepare the documentation
# -------------------------
INCLUDE(FindDoxygen)
IF(DOXYGEN_FOUND)
  MESSAGE(STATUS "Doxygen found")
  add_subdirectory(doc)
ENDIF(DOXYGEN_FOUND)

# Prepare description file for pkg-config.
#-----------------------------------------

SET(install_pkg_prefix "\${prefix}")
SET(install_pkg_exec_prefix "\${exec_prefix}")
SET(install_pkg_libdir "\${libdir}")
SET(install_pkg_include_dir "\${includedir}")

# Install the file in the appropriate place.
SET(install_libdir_pkgconfig ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
CONFIGURE_FILE(${jrlMathTools_SOURCE_DIR}/jrlMathTools.pc.cmake
	       ${jrlMathTools_BINARY_DIR}/jrlMathTools.pc )

SET(jrlMathTools_HEADERS
    ./include/jrlMathTools/jrlConstants.h
    ./include/jrlMathTools/angle.h
    ./include/jrlMathTools/vector3.h
    ./include/jrlMathTools/vector4.h
    ./include/jrlMathTools/matrix3x3.h
    ./include/jrlMathTools/matrix4x4.h
)

#----------------------------------------------------
# Install procedure for the header files
#----------------------------------------------------
INSTALL(FILES ${jrlMathTools_HEADERS}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/jrlMathTools
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)

INSTALL(FILES ${jrlMathTools_BINARY_DIR}/jrlMathTools.pc
	DESTINATION ${install_libdir_pkgconfig}
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)





