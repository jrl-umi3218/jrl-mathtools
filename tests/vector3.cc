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

#include <jrl/mathtools/vector3.hh>

#define BOOST_TEST_MODULE vector3

#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

#include "common.hh"

using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE (display)
{
  jrlMathTools::Vector3D<double> v (5., 4., 9.);

  output_test_stream output;

  output << v;
  BOOST_CHECK (output.is_equal ("5 4 9 "));

  v.display (output);
  BOOST_CHECK (output.is_equal ("5 4 9 "));
}

typedef boost::mpl::list<int, float, double> numericTypes_t;
typedef boost::mpl::list<int, float, double, MyNumericType> testTypes_t;

BOOST_AUTO_TEST_CASE_TEMPLATE (defaultConstructor, T, testTypes_t)
{
  jrlMathTools::Vector3D<T> v;

  BOOST_CHECK_EQUAL (v[0], T ());
  BOOST_CHECK_EQUAL (v[1], T ());
  BOOST_CHECK_EQUAL (v[2], T ());
  BOOST_CHECK_THROW (v[3], std::logic_error);

  BOOST_CHECK_EQUAL (v (0), T ());
  BOOST_CHECK_EQUAL (v (1), T ());
  BOOST_CHECK_EQUAL (v (2), T ());
  BOOST_CHECK_THROW (v (3), std::logic_error);

  BOOST_CHECK_EQUAL (v.m_x, T ());
  BOOST_CHECK_EQUAL (v.m_y, T ());
  BOOST_CHECK_EQUAL (v.m_z, T ());

  BOOST_CHECK (v.IsZero ());
}

BOOST_AUTO_TEST_CASE (constructor)
{
  jrlMathTools::Vector3D<double> v (0., 1., 2.);

  BOOST_CHECK_EQUAL (v[0], 0.);
  BOOST_CHECK_EQUAL (v[1], 1.);
  BOOST_CHECK_EQUAL (v[2], 2.);
  BOOST_CHECK_THROW (v[3], std::logic_error);

  BOOST_CHECK_EQUAL (v (0), 0.);
  BOOST_CHECK_EQUAL (v (1), 1.);
  BOOST_CHECK_EQUAL (v (2), 2.);
  BOOST_CHECK_THROW (v (3), std::logic_error);

  BOOST_CHECK_EQUAL (v.m_x, 0.);
  BOOST_CHECK_EQUAL (v.m_y, 1.);
  BOOST_CHECK_EQUAL (v.m_z, 2.);
}

BOOST_AUTO_TEST_CASE (equality)
{
  jrlMathTools::Vector3D<double> v1 (0., 1., 2.);
  jrlMathTools::Vector3D<double> v2 (0., 1., 2.);

  BOOST_CHECK (v1 == v2);

  ++v1[0];
  BOOST_CHECK (! (v1 == v2));
}

BOOST_AUTO_TEST_CASE (inequality)
{
  jrlMathTools::Vector3D<double> v1 (0., 1., 2.);
  jrlMathTools::Vector3D<double> v2 (0., 1., 2.);

  BOOST_CHECK (! (v1 != v2));

  ++v1[0];
  BOOST_CHECK (v1 != v2);
}

BOOST_AUTO_TEST_CASE (plus)
{
  jrlMathTools::Vector3D<double> v1 (0., 1., 2.);
  jrlMathTools::Vector3D<double> v2 (3., 4., 5.);

  jrlMathTools::Vector3D<double> vres (3., 5., 7.);

  BOOST_CHECK_EQUAL (v1 + v2, vres);
  BOOST_CHECK_EQUAL (v2 + v1, vres);

  v1 += v2;
  BOOST_CHECK_EQUAL (v1, vres);
}

BOOST_AUTO_TEST_CASE (minus)
{
  jrlMathTools::Vector3D<double> v1 (0., 1., 2.);
  jrlMathTools::Vector3D<double> v2 (3., 4., 5.);

  jrlMathTools::Vector3D<double> vres (-3., -3., -3.);

  BOOST_CHECK_EQUAL (v1 - v2, vres);
  BOOST_CHECK_EQUAL (-v2 + v1, vres);

  v1 -= v2;
  BOOST_CHECK_EQUAL (v1, vres);
}

BOOST_AUTO_TEST_CASE (times)
{
  jrlMathTools::Vector3D<double> v (1., 2., 3.);
  jrlMathTools::Vector3D<double> vres (2., 4., 6.);

  BOOST_CHECK_EQUAL (v * 2., vres);

  v *= 2.;
  BOOST_CHECK_EQUAL (v, vres);
}

BOOST_AUTO_TEST_CASE (dot_product)
{
  jrlMathTools::Vector3D<double> v1 (0., 1., 2.);
  jrlMathTools::Vector3D<double> v2 (3., 4., 5.);

  BOOST_CHECK_EQUAL (v1 * v2, 0. * 3. + 1. * 4. + 2. * 5.);
}

BOOST_AUTO_TEST_CASE (divide)
{
  jrlMathTools::Vector3D<double> v (4., 3., 10.);
  jrlMathTools::Vector3D<double> vres (2., 1.5, 5.);

  BOOST_CHECK_EQUAL (v / 2., vres);

  v /= 2.;
  BOOST_CHECK_EQUAL (v, vres);
}

BOOST_AUTO_TEST_CASE (normalize)
{
  //FIXME.
}


BOOST_AUTO_TEST_CASE (norm)
{
  jrlMathTools::Vector3D<double> v;
  BOOST_CHECK_EQUAL (v.norm (), 0.);

  jrlMathTools::Vector3D<double> v1 (4., 3., 10.);
  BOOST_CHECK_CLOSE (v1.norm (), 11.1803399, 0.0001);
}

BOOST_AUTO_TEST_CASE (normsquared)
{
  jrlMathTools::Vector3D<double> v;
  BOOST_CHECK_EQUAL (v.normsquared (), 0.);

  jrlMathTools::Vector3D<double> v1 (4., 3., 10.);
  BOOST_CHECK_CLOSE (v1.normsquared (), v1.norm () * v1.norm (), 0.0001);

  BOOST_CHECK_EQUAL (v1.normsquared (), 4. * 4. + 3. * 3. + 10. * 10.);
}

BOOST_AUTO_TEST_CASE (cross_product)
{
  jrlMathTools::Vector3D<double> v1 (4., 3., 10.);
  jrlMathTools::Vector3D<double> v2 (12., 5., 2.);
  jrlMathTools::Vector3D<double> vres (-44., 112., -16.);

  BOOST_CHECK_EQUAL (v1 ^ v2, vres);
}
