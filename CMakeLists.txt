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
SET(PROJECT_VERSION 1.2.99)

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

# Prepare the documentation
# -------------------------
OPTION(GENERATE_DOC 0 "Generate html documentation")
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
FIND_PACKAGE( Boost 1.33.1 COMPONENTS thread )

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
	ENDIF (WIN32)

  ELSE(Boost_FOUND)
    # TO DO : find vnl...
  ENDIF(Boost_FOUND)

ENDIF(LAPACK_FOUND)

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
    ./include/jrlMathTools/matrixNxP.h
    ./include/jrlMathTools/vectorN.h
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





