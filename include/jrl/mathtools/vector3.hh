/*
 * Copyright 2008, 2009, 2010, Olivier Stasse,
 *                             Florent Lamiraux,
 *                             Francois Keith,
 *                             Eiichi Yoshida,  CNRS/AIST
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

#ifndef JRL_MATHTOOLS_VECTOR3_HH
# define JRL_MATHTOOLS_VECTOR3_HH
# include <iostream>
# include <cmath>
# include <stdexcept>

# include <jrl/mathtools/fwd.hh>

namespace jrlMathTools
{
  /// Generic 3d vector.
  template <typename T>
  struct Vector3D
  {
    T m_x;
    T m_y;
    T m_z;

    /// \brief Default constructor: all fields are set to zero.
    inline Vector3D ()
    {
      m_x= 0.0;
      m_y=0.0;
      m_z=0.0;
    }

    inline Vector3D (const T x, const T y, const T z)
      : m_x (x), m_y (y), m_z (z)
    {}

    /// Assignment operator.
    inline Vector3D<T>& operator= (const Vector3D<T>& v)
    {
      if (&v == this)
	return *this;
      m_x = v.m_x;
      m_y = v.m_y;
      m_z = v.m_z;
      return *this;
    }

    /// \brief Unary operator -
    inline Vector3D<T> operator-() const
    {
      return Vector3D<T> (-m_x, -m_y, -m_z);
    }

    /// \brief Array operator.
    inline T& operator[](unsigned i)
    {
      if (i == 0)
	return m_x;
      else if (i == 1)
	return m_y;
      else if (i == 2)
	return m_z;
      throw std::logic_error("invalid index");
    }

    /// \brief Array operator.
    inline T operator[](unsigned i) const
    {
      if (i == 0)
	return m_x;
      else if (i == 1)
	return m_y;
      else if (i == 2)
	return m_z;
      throw std::logic_error("invalid index");
    }

    /// \brief Array operator.
    inline T& operator()(unsigned i)
    {
      return (*this)[i];
    }

    /// \brief Array operator.
    inline T operator()(unsigned i) const
    {
      return (*this)[i];
    }

    /// \brief Binary operator ==.
    inline bool operator==(const Vector3D<T>& v) const
    {
      return
	(v.m_x == m_x) &&
	(v.m_y == m_y) &&
	(v.m_z == m_z);
    }

    /// \brief Binary operator !=.
    inline bool operator!=(const Vector3D<T>& v) const
    {
      return 
	(v.m_x != m_x) ||
	(v.m_y != m_y) ||
	(v.m_z != m_z);
    }

    /// \brief Binary operator +.
    inline Vector3D<T> operator+ (const Vector3D<T>& v) const
    {
      Vector3D<T> vr;
      vr.m_x = m_x + v.m_x;
      vr.m_y = m_y + v.m_y;
      vr.m_z = m_z + v.m_z;
      return vr;
    }

    /// \brief Binary operator -.
    inline Vector3D<T> operator- (const Vector3D<T>& v) const
    {
      Vector3D<T> vr;
      vr.m_x = m_x - v.m_x;
      vr.m_y = m_y - v.m_y;
      vr.m_z = m_z - v.m_z;
      return vr;
    }

    /// \brief Binary operator +=.
    inline void operator+= (const Vector3D<T>& v)
    {
      m_x += v.m_x;
      m_y += v.m_y;
      m_z += v.m_z;
    }

    /// \brief Binary operator -=.
    inline void operator-= (const Vector3D<T>& v)
    {
      m_x -= v.m_x;
      m_y -= v.m_y;
      m_z -= v.m_z;
    }

    /// \brief Binary operator *.
    inline Vector3D<T> operator* (const T& t) const
    {
      Vector3D<T> vr;
      vr.m_x = m_x * t;
      vr.m_y = m_y * t;
      vr.m_z = m_z * t;
      return vr;
    }


    /// \brief Binary operator * : dot product.
    inline T operator* (const Vector3D<T>& v) const
    {
      T tr = m_x * v.m_x;
      tr += (m_y * v.m_y);
      tr += (m_z * v.m_z);
      return tr;
    }

    /// \brief Binary operator /.
    inline Vector3D<T> operator/ (const T& t) const
    {
      Vector3D<T> vr;
      vr.m_x = m_x / t;
      vr.m_y = m_y / t;
      vr.m_z = m_z / t;
      return vr;
    }

    /// \brief Binary operator *=.
    inline void operator*= (const T& t)
    {
      m_x = m_x * t;
      m_y = m_y * t;
      m_z = m_z * t;
    }

    /// \brief Binary operator /=.
    inline void operator/= (const T& t)
    {
      m_x = m_x / t;
      m_y = m_y / t;
      m_z = m_z / t;
    };


    /// \brief Normalize .
    inline void normalize ()
    {
      T in = static_cast<T> (1. / sqrt (m_x * m_x + m_y * m_y + m_z * m_z));
      m_x *= in;
      m_y *= in;
      m_z *= in;
    }

    /// \brief Get the norm.
    inline T norm () const
    {
      return static_cast<T> (sqrt (m_x * m_x + m_y * m_y + m_z * m_z));
    }

    /// \brief Check if the vector is set to zero.
    inline bool IsZero () const
    {
      return (m_x == T ()) && (m_y == T ()) && (m_z == T ());
    }

    /// \brief Get the norm squared.
    inline T normsquared () const
    {
      return m_x * m_x + m_y * m_y + m_z * m_z;
    }

    /// \brief Cross product.
    inline Vector3D<T> operator ^ (const Vector3D<T>& v2) const
    {
      Vector3D<T> vr;
      vr.m_x = m_y*v2.m_z - v2.m_y*m_z;
      vr.m_y = m_z*v2.m_x - v2.m_z*m_x;
      vr.m_z = m_x*v2.m_y - v2.m_x*m_y;
      return vr;
    }

    std::ostream& display (std::ostream& os) const
    {
      os << m_x << " " << m_y << " " << m_z << " ";
      return os;
    }
  };

  template <typename T>
  std::ostream& operator<< (std::ostream& os, const Vector3D<T>& v)
  {
    return v.display (os);
  }

} // end of namespace jrlMathTools.

#endif //! JRL_MATHTOOLS_VECTOR3_HH
