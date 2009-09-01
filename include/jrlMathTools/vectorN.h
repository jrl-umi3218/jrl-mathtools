/*
  Copyright JRL AIST-CNRS

  Authors: Florent Lamiraux
*/

#ifndef JRLMATHTOOLS_VECTORN_H
#define JRLMATHTOOLS_VECTORN_H

#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/vector_proxy.hpp"

/*
  Avoid conflict with MatrixAbstractLayer
*/
#ifndef _MATRIX_ABSTRACT_LAYER_H_
namespace boost_ublas = boost::numeric::ublas;
namespace traits = boost::numeric::bindings::traits;
namespace lapack = boost::numeric::bindings::lapack;

typedef boost_ublas::vector<double> vectorN;
#endif

#endif
