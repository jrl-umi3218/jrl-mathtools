/*
 * Copyright 2008, 2009, 2010, Francois Keith, CNRS/AIST
 *
 * This file is part of jrl-mathtools.
 * jrl-mathtools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * jrl-mathtools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with jrl-mathtools.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JRL_MATHTOOLS_CONSTANTS_H
# define JRL_MATHTOOLS_CONSTANTS_H

# include <cmath>

// It happens on some platform (Microsoft Windows, for instance) that
// M_PI is not defined as it should be. This header fix this issue and
// make sure that the contant is available.
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif // !M_PI

#endif // !JRL_MATHTOOLS_CONSTANTS_H
