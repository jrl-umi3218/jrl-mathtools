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

#include <jrl/mathtools.hh>

#include <jrl/mathtools/angle.hh>

#define BOOST_TEST_MODULE angle

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE (display)
{
  jrlMathTools::Angle angle (0.5);

  output_test_stream output;

  output << angle;
  BOOST_CHECK (output.is_equal ("0.5"));
}

BOOST_AUTO_TEST_CASE (simple)
{
  jrlMathTools::Angle angle;
  BOOST_CHECK_EQUAL (angle.value (), 0.);
}

BOOST_AUTO_TEST_CASE (constructor)
{
  jrlMathTools::Angle angle (0.5);
  BOOST_CHECK_EQUAL (angle.value (), .5);

  angle = 2. * M_PI + 0.1;
  BOOST_CHECK_CLOSE (angle.value (), 0.1, 0.0001);
}

BOOST_AUTO_TEST_CASE (cast)
{
  jrlMathTools::Angle angle (0.5);
  double x = angle;
  BOOST_CHECK_EQUAL (x, angle.value ());
}

BOOST_AUTO_TEST_CASE (assignment)
{
  jrlMathTools::Angle angle (0.5);

  angle = jrlMathTools::Angle (2.);

  BOOST_CHECK_EQUAL (angle, 2.);
}

BOOST_AUTO_TEST_CASE (minus)
{
  jrlMathTools::Angle angle1 (5.);
  jrlMathTools::Angle angle2 (2.);

  BOOST_CHECK_EQUAL (angle1 - angle2, 3.);
}

BOOST_AUTO_TEST_CASE (plus)
{
  jrlMathTools::Angle angle1 (1.);
  jrlMathTools::Angle angle2 (1.5);

  BOOST_CHECK_EQUAL (angle1 + angle2, 2.5);
}

BOOST_AUTO_TEST_CASE (times)
{
  jrlMathTools::Angle angle (0.5);

  BOOST_CHECK_EQUAL (angle * 2., 1.);
  BOOST_CHECK_EQUAL (2. * angle, 1.);
}

BOOST_AUTO_TEST_CASE (interpolate)
{
  // FIXME: add missing test.
  BOOST_CHECK (true);
}

BOOST_AUTO_TEST_CASE (distance)
{
  // FIXME: add missing test.
  BOOST_CHECK (true);
}

BOOST_AUTO_TEST_CASE (angle_sin)
{
  jrlMathTools::Angle angle (0.5);

  BOOST_CHECK_EQUAL (sin (angle), std::sin (0.5));
}

BOOST_AUTO_TEST_CASE (angle_cos)
{
  jrlMathTools::Angle angle (0.5);

  BOOST_CHECK_EQUAL (cos (angle), std::cos (0.5));
}

BOOST_AUTO_TEST_CASE (angle_tan)
{
  jrlMathTools::Angle angle (0.5);

  BOOST_CHECK_EQUAL (tan (angle), std::tan (0.5));
}
