/*
 * 
 * Copyright 2008, 2009, 2010, Olivier Stasse,
 *                             Florent Lamiraux,  CNRS/AIST
 *
 * This file is part of jrlMathTools.
 * jrlMathTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * jrlMathTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with jrlMathTools.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef JRLMATHTOOLS_VECTORN_H
#define JRLMATHTOOLS_VECTORN_H

#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/vector_proxy.hpp"

#include "boost/version.hpp"


/*
  Avoid conflict with MatrixAbstractLayer
*/
#ifndef _MATRIX_ABSTRACT_LAYER_H_
namespace boost_ublas = boost::numeric::ublas;

#if BOOST_VERSION >= 104000
#include "boost/numeric/ublas/detail/raw.hpp"
namespace traits=boost_ublas::raw;
#define MRAWDATA(x) x.data().begin()
#define VRAWDATA(x) x.data().begin()
#else
#include "boost/numeric/bindings/traits/ublas_matrix.hpp"
namespace traits = boost::numeric::bindings::traits;
#define MRAWDATA(x) traits::matrix_storage(x)
#define VRAWDATA(x) traits::vector_storage(x)
#endif 

//namespace lapack = boost::numeric::bindings::lapack;

typedef boost_ublas::vector<double> vectorN;
#endif

#endif
