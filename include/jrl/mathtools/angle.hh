// Copyright (C) 2008-2013 LAAS-CNRS, JRL AIST-CNRS.
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

#ifndef JRL_MATHTOOLS_ANGLE_HH
# define JRL_MATHTOOLS_ANGLE_HH
# include <iostream>
# include <cmath>

# include <jrl/mathtools/fwd.hh>

# include <jrl/mathtools/constants.hh>
# include <jrl/mathtools/deprecated.hh>

namespace jrlMathTools
{
  inline double degreeToRadian (const double& x)
  {
    return x * M_PI / 180.;
  }

  inline double radianToDegree (const double& x)
  {
    return x * 180. / M_PI;
  }


  /// \brief This class implements simple computations on angles.
  ///
  /// All angles *MUST* be expressed in radian.
  ///
  /// Facilities are provided for degree/radian conversion for display/debugging only.
  class Angle
  {
  public:
    Angle ()
      : angle_ (0.)
    {}

    // \brief Constructor by value.
    Angle (const double& angle)
      : angle_ (0.)
    {
      set (angle);
    }

    /// \brief Copy Constructor.
    Angle (const Angle& angle)
      : angle_(angle.value ())
    {}

    /// \brief Trivial destructor.
    ~Angle ()
    {}

    /// \brief Named constructors.
    static Angle radian (const double& value)
    {
      return Angle (value);
    }

    static Angle degree (const double& value)
    {
      return Angle (degreeToRadian (value));
    }

    /// \brief Angle value.
    const double& value () const
    {
      return angle_;
    }

    /// \brief Return value in degrees (for output only!).
    double degree () const
    {
      return radianToDegree (value ());
    }

    /// \brief Cast into a double.
    operator const double& () const
    {
      return value ();
    }

    /// \brief Operator =.
    Angle& operator= (const Angle& angle)
    {
      if (&angle == this)
	return *this;
      set (angle.value ());
      return *this;
    }

    /// \brief Operator = with a double
    Angle& operator= (const double& value)
    {
      set (value);
      return *this;
    }

    /// Arithmetic operators overload
    /// \{
    Angle operator+ (const Angle& angle) const
    {
      return Angle (value () + angle.value ());
    }
    Angle operator- (const Angle& angle) const
    {
      return Angle (value () - angle.value ());
    }
    Angle& operator+= (const Angle& rhs)
    {
      set (value () + rhs.value ());
      return *this;
    }
    Angle& operator-= (const Angle& rhs)
    {
      set (value () - rhs.value ());
      return *this;
    }

    template <typename T>
    Angle operator+ (const T& angle) const
    {
      return Angle (value () + angle);
    }
    template <typename T>
    Angle operator- (const T& angle) const
    {
      return Angle (value () - angle);
    }
    template <typename T>
    Angle& operator+= (const T& rhs)
    {
      set (this->value () + rhs);
      return *this;
    }
    template <typename T>
    Angle& operator-= (const T& rhs)
    {
      set (this->value () - rhs.value ());
      return *this;
    }


    template <typename T>
    Angle operator* (const T& rhs) const
    {
      return Angle (angle_ * rhs);
    }
    template <typename T>
    Angle operator*= (const T& rhs) const
    {
      set (this->value () * rhs);
      return *this;
    }
    template <typename T>
    Angle operator/= (const T& rhs) const
    {
      set (this->value () / rhs);
      return *this;
    }
    /// \}

    /// \brief Interpolation between two angles
    /// \param alpha interpolation parameter between 0 and 1.
    /// \param angle second angle of interpolation.
    /// \return an angle between this one and angle along the shortest arc.
    /// \li if alpha = 0, return this angle,
    /// \li if alpha = 1, return angle.
    Angle
    interpolate (const double& alpha, const Angle& angle) const
    {
      Angle diffAngle = angle.value () - value ();
      return Angle(value () + alpha * diffAngle.value ());
    };

    /// \brief output to a stream.
    std::ostream& display (std::ostream& os) const
    {
      os << angle_;
      return os;
    }

    /// \brief Distance on unit circle.
    double distance (const Angle& angle) const
    {
      Angle diffAngle = *this - angle;
      return std::fabs (diffAngle.value ());
    }

    /// @}
  protected:

    /// \brief Set angle between -PI and PI.
    void setBetweenMinusAndPlusPI ()
    {
      while (angle_ < -M_PI)
	angle_ += 2. * M_PI;
      while (angle_ > M_PI)
	angle_ -= 2. * M_PI;
    }

    /// \brief Update angle value.
    void set (const double& value)
    {
      angle_ = value;
      setBetweenMinusAndPlusPI ();
    }

    /// \brief angular value.
    double angle_;
  };

  template <typename T>
  Angle operator* (const T& coef, const Angle& angle)
  {
    return Angle (coef * angle.value ());
  }

  inline double cos (const Angle& angle)
  {
    return std::cos (angle.value ());
  }

  inline double sin (const Angle& angle)
  {
    return std::sin (angle.value ());
  }

  inline double tan (const Angle& angle)
  {
    return std::tan (angle.value ());
  }

  inline std::ostream& display (std::ostream& os, const Angle& angle)
  {
    return angle.display (os);
  }
} // end of namespace jrlMathTools.

#endif //! JRL_MATHTOOLS_ANGLE_HH
