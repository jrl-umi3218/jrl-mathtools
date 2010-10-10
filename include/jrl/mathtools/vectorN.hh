/*
 *
 * Copyright 2008, 2009, 2010, Olivier Stasse,
 *                             Florent Lamiraux,  CNRS/AIST
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
 *
 */

#ifndef JRL_MATHTOOLS_VECTORN_H
# define JRL_MATHTOOLS_VECTORN_H

# include <boost/numeric/ublas/vector.hpp>
# include <boost/numeric/ublas/vector_proxy.hpp>

# include <boost/version.hpp>

// Avoid namespace/type conflicts with the MatrixAbstractLayer.
# ifndef _MATRIX_ABSTRACT_LAYER_H_
#  include <boost/numeric/ublas/detail/raw.hpp>
#  define MRAWDATA(x) x.data().begin()
#  define VRAWDATA(x) x.data().begin()

namespace boost_ublas = boost::numeric::ublas;
namespace traits=boost_ublas::raw;
typedef boost_ublas::vector<double> vectorN;
# endif //! _MATRIX_ABSTRACT_LAYER_H_

#endif //! JRL_MATHTOOLS_VECTORN_H
