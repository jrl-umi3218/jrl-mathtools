// Copyright 2010 Thomas Moulard.
//
// This file is part of jrl-mathtools.
// jrl-mathtools is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// jrl-mathtools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License
// along with jrl-mathtools.  If not, see <http://www.gnu.org/licenses/>.

#include <jrl/mathtools/matrix3x3.hh>

#define BOOST_TEST_MODULE matrix3x3

#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include "common.hh"

using boost::test_tools::output_test_stream;

typedef boost::mpl::list<int, float, double> numericTypes_t;
typedef boost::mpl::list<int, float, double, MyNumericType> testTypes_t;

BOOST_AUTO_TEST_CASE_TEMPLATE (defaultConstructor, T, testTypes_t)
{
  jrlMathTools::Matrix3x3<T> m;

  for (unsigned i = 0; i < 9; ++i)
    BOOST_CHECK_EQUAL (m[i], T ());
  BOOST_CHECK_THROW (m[9], std::logic_error);

  for (unsigned i = 0; i < 3; ++i)
    for (unsigned j = 0; j < 3; ++j)
      BOOST_CHECK_EQUAL (m (i, j), T ());
  BOOST_CHECK_THROW (m (3, 3), std::logic_error);
}
