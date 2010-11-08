/*
 * Copyright 2008, 2009, 2010, Olivier Stasse,
 *                             Florent Lamiraux,
 *                             Francois Keith,  CNRS/AIST
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

#ifndef JRL_MATHTOOLS_VECTOR4_HH
# define JRL_MATHTOOLS_VECTOR4_HH
# include <cmath>
# include <iostream>
# include <stdexcept>

# include <jrl/mathtools/fwd.hh>

namespace jrlMathTools
{
  /// \brief Generic 4D vector.
  template <typename T>
  struct Vector4D
  {
    T m_x;
    T m_y;
    T m_z;
    T m_w;

    /// Default constructor: all fields are set to zero.
    inline Vector4D ()
      : m_x (),
	m_y (),
	m_z (),
	m_w ()
    {}

    explicit Vector4D<T> (const T& x,
			  const T& y,
			  const T& z,
			  const T& w)
    : m_x (x),
      m_y (y),
      m_z (z),
      m_w (w)
    {}

    /// \brief Assignement operator.
    inline Vector4D<T> operator= (const Vector4D<T>& v)
    {
      m_x = v.m_x;
      m_y = v.m_y;
      m_z = v.m_z;
      m_w = v.m_w;
      return *this;
    }


    /// \brief Unary operator -.
    inline Vector4D<T> operator- ()
    {
      return Vector4D<T> (-m_x, -m_y, -m_z, -m_w);
    }

    /// \brief Array operator.
    inline T& operator[] (unsigned i)
    {
      if (i == 0)
	return m_x;
      else if (i == 1)
	return m_y;
      else if (i == 2)
	return m_z;
      else if (i == 3)
	return m_w;
      throw std::logic_error ("invalid index");
    }

    /// \brief Array operator.
    inline const T& operator[](unsigned i) const
    {
      if (i == 0)
	return m_x;
      else if (i == 1)
	return m_y;
      else if (i == 2)
	return m_z;
      else if (i == 3)
	return m_w;
      throw std::logic_error ("invalid index");
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
    inline bool operator==(const Vector4D<T>& v) const
    {
      return
	(v.m_x==m_x) &&
	(v.m_y==m_y) &&
	(v.m_z==m_z) &&
	(v.m_w==m_w);
    }

    /// \brief Binary operator +.
    inline Vector4D<T> operator+ (const Vector4D<T>& v) const
    {
      Vector4D<T> vr;
      vr.m_x = m_x + v.m_x;
      vr.m_y = m_y + v.m_y;
      vr.m_z = m_z + v.m_z;
      vr.m_w = m_w + v.m_w;
      return vr;
    }

    /// \brief Binary operator -.
    inline Vector4D<T> operator- (const Vector4D<T>& v) const
    {
      Vector4D<T> vr;
      vr.m_x = m_x - v.m_x;
      vr.m_y = m_y - v.m_y;
      vr.m_z = m_z - v.m_z;
      vr.m_w = m_w - v.m_w;
      return vr;
    }

    /// \brief Binary operator +=.
    inline void operator+= (const Vector4D<T>& v)
    {
      m_x += v.m_x;
      m_y += v.m_y;
      m_z += v.m_z;
      m_w += v.m_w;
    }

    /// \brief Binary operator -=.
    inline void operator-= (const Vector4D<T>& v)
    {
      m_x -= v.m_x;
      m_y -= v.m_y;
      m_z -= v.m_z;
      m_w -= v.m_w;
    }

    /// \brief Binary operator *.
    inline Vector4D<T> operator* (const T& t) const
    {
      Vector4D<T> vr;
      vr.m_x = m_x * t;
      vr.m_y = m_y * t;
      vr.m_z = m_z * t;
      vr.m_w = m_w * t;
      return vr;
    }


    /// \brief Binary operator /.
    inline Vector4D<T> operator/ (const T& t) const
    {
      Vector4D<T> vr;
      vr.m_x = m_x / t;
      vr.m_y = m_y / t;
      vr.m_z = m_z / t;
      vr.m_w = m_w / t;
      return vr;
    }

    /// \brief Binary operator *=.
    inline void operator*= (const T& t)
    {
      m_x = m_x * t;
      m_y = m_y * t;
      m_z = m_z * t;
      m_w = m_w * t;
    }

    /// \brief Binary operator /=.
    inline void operator/= (const T& t)
    {
      m_x = m_x / t;
      m_y = m_y / t;
      m_z = m_z / t;
      m_w = m_w / t;
    }


    /// \brief Normalize.
    inline void normalize ()
    {
      T in = static_cast<T>
	(1. / sqrt (m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));
      m_x *= in;
      m_y *= in;
      m_z *= in;
      m_w *= in;
    }

    /// \brief Get the norm.
    inline T norm() const
    {
      return
	static_cast<T> (sqrt (m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));
    }

    /// \brief Get the norm squared.
    inline T normsquared() const
    {
      return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
    }


    inline std::ostream& display (std::ostream& os) const
    {
      os << m_x << " " << m_y << " " << m_z << " " << m_w;
      return os;
    }
  };

  template <typename T>
  inline std::ostream& operator<< (std::ostream& os, const Vector4D<T>& v)
  {
    return v.display (os);
  }

} // end of namespace jrlMathTools.

#endif //! JRL_MATHTOOLS_VECTOR4_HH
