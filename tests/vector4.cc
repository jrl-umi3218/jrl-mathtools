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

#include <jrl/mathtools/vector4.hh>

#define BOOST_TEST_MODULE vector4

#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>

using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE (display)
{
  jrlMathTools::Vector4D<double> v (5., 4., 9., 10.);

  output_test_stream output;

  output << v;
  BOOST_CHECK (output.is_equal ("5 4 9 10"));

  v.display (output);
  BOOST_CHECK (output.is_equal ("5 4 9 10"));
}

// This is a custom numeric type used to check
// that the container can handle non-native types.
struct MyNumericType
{
public:
  MyNumericType (int i = 0)
    : i (i)
  {}

  bool operator== (const MyNumericType& mnt) const
  {
    return i == mnt.i;
  }

  int i;
};

std::ostream& operator<< (std::ostream& os, const MyNumericType& mnt)
{
  os << mnt.i;
  return os;
}


typedef boost::mpl::list<int, float, double> numericTypes_t;
typedef boost::mpl::list<int, float, double, MyNumericType> testTypes_t;

BOOST_AUTO_TEST_CASE_TEMPLATE (defaultConstructor, T, testTypes_t)
{
  jrlMathTools::Vector4D<T> v;

  BOOST_CHECK_EQUAL (v[0], T ());
  BOOST_CHECK_EQUAL (v[1], T ());
  BOOST_CHECK_EQUAL (v[2], T ());
  BOOST_CHECK_EQUAL (v[3], T ());
  BOOST_CHECK_THROW (v[4], std::logic_error);

  BOOST_CHECK_EQUAL (v (0), T ());
  BOOST_CHECK_EQUAL (v (1), T ());
  BOOST_CHECK_EQUAL (v (2), T ());
  BOOST_CHECK_EQUAL (v (3), T ());
  BOOST_CHECK_THROW (v (4), std::logic_error);

  BOOST_CHECK_EQUAL (v.m_x, T ());
  BOOST_CHECK_EQUAL (v.m_y, T ());
  BOOST_CHECK_EQUAL (v.m_z, T ());
  BOOST_CHECK_EQUAL (v.m_w, T ());
}

BOOST_AUTO_TEST_CASE (constructor)
{
  jrlMathTools::Vector4D<double> v (0., 1., 2., 3.);

  BOOST_CHECK_EQUAL (v[0], 0.);
  BOOST_CHECK_EQUAL (v[1], 1.);
  BOOST_CHECK_EQUAL (v[2], 2.);
  BOOST_CHECK_EQUAL (v[3], 3.);
  BOOST_CHECK_THROW (v[4], std::logic_error);

  BOOST_CHECK_EQUAL (v (0), 0.);
  BOOST_CHECK_EQUAL (v (1), 1.);
  BOOST_CHECK_EQUAL (v (2), 2.);
  BOOST_CHECK_EQUAL (v (3), 3.);
  BOOST_CHECK_THROW (v (4), std::logic_error);

  BOOST_CHECK_EQUAL (v.m_x, 0.);
  BOOST_CHECK_EQUAL (v.m_y, 1.);
  BOOST_CHECK_EQUAL (v.m_z, 2.);
  BOOST_CHECK_EQUAL (v.m_w, 3.);
}

BOOST_AUTO_TEST_CASE (equality)
{
  jrlMathTools::Vector4D<double> v1 (0., 1., 2., 3.);
  jrlMathTools::Vector4D<double> v2 (0., 1., 2., 3.);

  BOOST_CHECK (v1 == v2);

  ++v1[0];
  BOOST_CHECK (! (v1 == v2));
}

BOOST_AUTO_TEST_CASE (plus)
{
  jrlMathTools::Vector4D<double> v1 (0., 1., 2., 3.);
  jrlMathTools::Vector4D<double> v2 (3., 4., 5., 6.);

  jrlMathTools::Vector4D<double> vres (3., 5., 7., 9.);

  BOOST_CHECK_EQUAL (v1 + v2, vres);
  BOOST_CHECK_EQUAL (v2 + v1, vres);

  v1 += v2;
  BOOST_CHECK_EQUAL (v1, vres);
}

BOOST_AUTO_TEST_CASE (minus)
{
  jrlMathTools::Vector4D<double> v1 (0., 1., 2., 3.);
  jrlMathTools::Vector4D<double> v2 (3., 4., 5., 6.);

  jrlMathTools::Vector4D<double> vres (-3., -3., -3., -3.);

  BOOST_CHECK_EQUAL (v1 - v2, vres);
  BOOST_CHECK_EQUAL (-v2 + v1, vres);

  v1 -= v2;
  BOOST_CHECK_EQUAL (v1, vres);
}

BOOST_AUTO_TEST_CASE (times)
{
  jrlMathTools::Vector4D<double> v (1., 2., 3., 4.);
  jrlMathTools::Vector4D<double> vres (2., 4., 6., 8.);

  BOOST_CHECK_EQUAL (v * 2., vres);

  v *= 2.;
  BOOST_CHECK_EQUAL (v, vres);
}

BOOST_AUTO_TEST_CASE (divide)
{
  jrlMathTools::Vector4D<double> v (4., 3., 10., 12.);
  jrlMathTools::Vector4D<double> vres (2., 1.5, 5., 6.);

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
  jrlMathTools::Vector4D<double> v;
  BOOST_CHECK_EQUAL (v.norm (), 0.);

  jrlMathTools::Vector4D<double> v1 (4., 3., 10., 12.);
  BOOST_CHECK_CLOSE (v1.norm (), 16.401219466856727, 0.0001);
}

BOOST_AUTO_TEST_CASE (normsquared)
{
  jrlMathTools::Vector4D<double> v;
  BOOST_CHECK_EQUAL (v.normsquared (), 0.);

  jrlMathTools::Vector4D<double> v1 (4., 3., 10., 12.);
  BOOST_CHECK_CLOSE (v1.normsquared (), v1.norm () * v1.norm (), 0.0001);

  BOOST_CHECK_EQUAL (v1.normsquared (),
		     4. * 4. + 3. * 3. + 10. * 10. + 12. * 12.);
}
