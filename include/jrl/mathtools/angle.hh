/*
 * Copyright 2008, 2009, 2010, Florent Lamiraux,
 *                             Francois Keith, CNRS/AIST
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

#ifndef JRL_MATHTOOLS_ANGLE_HH
# define JRL_MATHTOOLS_ANGLE_HH
# include <iostream>
# include <cmath>

# include <jrl/mathtools/fwd.hh>

# include <jrl/mathtools/constants.hh>
# include <jrl/mathtools/deprecated.hh>

namespace jrlMathTools
{
  /// \brief This class implements simple computations on angles.
  class Angle
  {
  public:
    Angle ()
      : attAngle (0.)
    {}

    // \brief Constructor by value.
    Angle (const double& angle)
      : attAngle(angle)
    {
      setBetweenMinusAndPlusPI ();
    }

    /// \brief Copy Constructor.
    Angle (const Angle& angle)
      : attAngle(angle.attAngle)
    {}

    /// \brief Angle value.
    inline const double& value () const
    {
      return attAngle;
    }

    /// \brief Cast into a double.
    inline operator const double& () const
    {
      return attAngle;
    }

    /// \brief Operator = with a double
    inline Angle& operator=(const double& value)
    {
      attAngle = value;
      setBetweenMinusAndPlusPI();
      return *this;
    }

    /// \brief Difference between two angles
    inline Angle operator-(const Angle& angle) const
    {
      return Angle (attAngle - angle.attAngle);
    }

    /// \brief Sum of two angles.
    inline Angle operator+(const Angle& angle) const
    {
      return Angle (attAngle + angle.attAngle);
    }

    /// \brief Multiplication of an angle by a real number.
    inline Angle operator* (const double& coef)
    {
      return Angle (coef * attAngle);
    };

    /// \brief Interpolation between two angles
    /// \param alpha interpolation parameter between 0 and 1.
    /// \param angle second angle of interpolation.
    /// \return an angle between this one and angle along the shortest arc.
    /// \li if alpha = 0, return this angle,
    /// \li if alpha = 1, return angle.
    inline Angle
    interpolate (const double& alpha, const Angle& angle) const
    {
      Angle diffAngle = angle.attAngle - attAngle;
      return Angle(attAngle+alpha*diffAngle.attAngle);
    };

    /// \brief output to a stream.
    inline std::ostream& display (std::ostream& os) const
    {
      os << attAngle;
      return os;
    }

    /// \brief Distance on unit circle.
    inline double distance (const Angle& angle) const
    {
      Angle diffAngle = *this - angle;
      return fabs(diffAngle.attAngle);
    }

    /// @}
  protected:

    /// \brief Set angle between -PI and PI.
    inline void setBetweenMinusAndPlusPI ()
    {
      while (attAngle < -M_PI)
	attAngle += 2*M_PI;
      while (attAngle > M_PI)
	attAngle -= 2*M_PI;
    }

    /// \brief angular value.
    double attAngle;
  };

  inline Angle operator* (const double& coef, const Angle& angle)
  {
    return Angle (coef * angle.value ());
  }

  inline double cos(const Angle& angle)
  {
    return std::cos (angle.value ());
  }
  
  inline double sin(const Angle& angle)
  {
    return std::sin (angle.value ());
  }
  
  inline double tan(const Angle& angle)
  {
    return std::tan (angle.value ());
  }

  inline std::ostream& display (std::ostream& os, const Angle& angle)
  {
    return angle.display (os);
  }

} // end of namespace jrlMathTools.

#endif //! JRL_MATHTOOLS_ANGLE_HH
