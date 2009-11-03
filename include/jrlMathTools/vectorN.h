/*
  Copyright JRL AIST-CNRS

  Authors: Florent Lamiraux
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

#if BOOST_VERSION == 104000
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
