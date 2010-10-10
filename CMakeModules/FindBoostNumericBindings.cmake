# Copyright 2009, 2010, Florent Lamiraux, JRL, CNRS/AIST
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
# GNU Lesser General Public License for more details.
# You should have received a copy of the GNU Lesser General Public License
# along with jrl-mathtools.  If not, see <http://www.gnu.org/licenses/>.
#
#
# - Find the Boost NumericBindings includes and libraries.

#
# Look into path specified by configuration variable BOOSTNUMERICBINDINGS_DIR
# If BOOSTNUMERICBINDINGS_DIR is not given at configuration,
# look into path specified by environment variable 
# BOOSTNUMERICBINDINGS_ROOT

SET(BOOSTNUMERICBINDINGS_INCLUDE_PATH_DESCRIPTION "Directory containing the boost bindings for lapack")

IF(BOOSTNUMERICBINDINGS_DIR)
  SET(BOOSTNUMERICBINDINGS_DIR_SEARCH ${BOOSTNUMERICBINDINGS_DIR}/include)
ELSE(BOOSTNUMERICBINDINGS_DIR)
  SET(BOOSTNUMERICBINDINGS_DIR_SEARCH $ENV{BOOSTNUMERICBINDINGS_ROOT})
ENDIF(BOOSTNUMERICBINDINGS_DIR)

IF(BOOSTNUMERICBINDINGS_DIR_SEARCH)
  FILE(TO_CMAKE_PATH ${BOOSTNUMERICBINDINGS_DIR_SEARCH} BOOSTNUMERICBINDINGS_DIR_SEARCH)
ENDIF(BOOSTNUMERICBINDINGS_DIR_SEARCH)

IF(WIN32)
  SET(BOOSTNUMERICBINDINGS_DIR_SEARCH
    ${BOOSTNUMERICBINDINGS_DIR_SEARCH}
    C:/boost-sandbox/include
    D:/boost-sandbox/include
  )
ENDIF(WIN32)

#
# Look for an installation.
#
SET(BoostNumericBindings_FOUND 0)

FIND_PATH(BoostNumericBindings_INCLUDE_DIR NAMES boost/numeric/bindings/traits/config.hpp PATH_SUFFIXES ${SUFFIX_FOR_PATH} PATHS

  # Look in other places.
  ${BOOSTNUMERICBINDINGS_DIR_SEARCH}

  # Help the user find it if we cannot.
  DOC "The ${BOOSTNUMERICBINDINGS_INCLUDE_PATH_DESCRIPTION}"
)

SET(BoostNumericBindings_FOUND 1)


