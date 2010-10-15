/*! This is a very fast and simple implementation
 * of a 3D matrix class of double.
 *
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

 */

#ifndef JRL_MATHTOOLS_MATRIX4x4_HH
# define JRL_MATHTOOLS_MATRIX4x4_HH
# include <stdexcept>

# include <jrl/mathtools/fwd.hh>

# include <jrl/mathtools/vector4.hh>
# include <jrl/mathtools/matrix3x3.hh>

namespace jrlMathTools
{
  /// \brief Generic 4x4 matrix.
  template <typename T>
  struct Matrix4x4
  {
    /// \brief The data array.
    T m[16];

    /// \brief Defaut constructor.
    Matrix4x4<T> ()
    {
      m[0]  = T ();  m[1]  = T (); m[2]  = T (); m[3]  = T ();
      m[4]  = T ();  m[5]  = T (); m[6]  = T (); m[7]  = T ();
      m[8]  = T ();  m[9]  = T (); m[10] = T (); m[11] = T ();
      m[12] = T ();  m[13] = T (); m[14] = T (); m[15] = T ();
    }

    /// \brief Constructor form a scalar.
    Matrix4x4<T> (const T x)
    {
      for (int i = 0; i < 16; ++i)
	m[i] = x;
    }

    /// \brief Copy constructor.
    Matrix4x4<T> (const Matrix4x4<T>& v)
    {
      for(int i = 0; i < 16; ++i)
	m[i] = v.m[i];
    }

    /// \brief Hybrid copy constructor
    template <typename T2>
    Matrix4x4<T> (const Matrix4x4<T2>& v)
    {
      for(int i = 0; i < 16; ++i)
	m[i] = v.m[i];
    }

    /// \brief ith element considering the matrix as an array.
    inline T& operator[] (unsigned int i)
    {
      if (i >= 16)
	throw std::logic_error ("bad index");
      return m[i];
    }

    /// \brief ith element considering the matrix as an array.
    inline const T& operator[] (unsigned int i) const
    {
      if (i >= 16)
	throw std::logic_error ("bad index");
      return m[i];
    }

    /// \brief Access by giving the (i,j) element.
    inline T& operator() (unsigned int i, unsigned int j)
    {
      if (i >= 4 || j >= 4)
	throw std::logic_error ("bad index");
      return m[4*i+j];
    }

    /// \brief Access by giving the (i,j) element.
    inline T operator() (unsigned int i, unsigned int j) const
    {
      if (i >= 4 || j >= 4)
	throw std::logic_error ("bad index");
      return m[4*i+j];
    }

    /// \brief Set to zero matrix.
    inline void setZero(void)
    {
      for (int i = 0; i < 16; ++i)
	m[i] = 0.;
    }

    /// \brief Set to identity.
    void setIdentity ()
    {
      setZero ();
      m[0] = m[5] = m[10] = m[15] = 1.;
    }

    /// \brief Addition operator.
    Matrix4x4<T> operator+(const Matrix4x4<T>& B) const
    {
      Matrix4x4<T> A;
      A.m[0] = m[0] + B.m[0];
      A.m[1] = m[1] + B.m[1];
      A.m[2] = m[2] + B.m[2];
      A.m[3] = m[3] + B.m[3];

      A.m[4] = m[4] + B.m[4];
      A.m[5] = m[5] + B.m[5];
      A.m[6] = m[6] + B.m[6];
      A.m[7] = m[7] + B.m[7];

      A.m[8] = m[8] + B.m[8];
      A.m[9] = m[9] + B.m[9];
      A.m[10] = m[10] + B.m[10];
      A.m[11] = m[11] + B.m[11];

      A.m[12] = m[12] + B.m[12];
      A.m[13] = m[13] + B.m[13];
      A.m[14] = m[14] + B.m[14];
      A.m[15] = m[15] + B.m[15];

      return A;
    }

    /// \brief Substraction operator.
    Matrix4x4<T>  operator-(const Matrix4x4<T>& B) const
    {
      Matrix4x4<T> A;
      A.m[0] = m[0] - B.m[0];
      A.m[1] = m[1] - B.m[1];
      A.m[2] = m[2] - B.m[2];
      A.m[3] = m[3] - B.m[3];

      A.m[4] = m[4] - B.m[4];
      A.m[5] = m[5] - B.m[5];
      A.m[6] = m[6] - B.m[6];
      A.m[7] = m[7] - B.m[7];

      A.m[8] = m[8] - B.m[8];
      A.m[9] = m[9] - B.m[9];
      A.m[10] = m[10] - B.m[10];
      A.m[11] = m[11] - B.m[11];

      A.m[12] = m[12] - B.m[12];
      A.m[13] = m[13] - B.m[13];
      A.m[14] = m[14] - B.m[14];
      A.m[15] = m[15] - B.m[15];
      return A;
    };

    /// \brief Multiplication operator with another matrix.
    Matrix4x4<T> operator* (const Matrix4x4<T>& B) const
    {
      Matrix4x4<T> A;
      A.m[0] = m[0] * B.m[0] + m[1] * B.m[3] + m[2] * B.m[6];
      A.m[0] = m[0] * B.m[0] + m[1] * B.m[4] + m[2] * B.m[8] + m[3] * B.m[12];
      A.m[1] = m[0] * B.m[1] + m[1] * B.m[5] + m[2] * B.m[9] + m[3] * B.m[13];
      A.m[2] = m[0] * B.m[2] + m[1] * B.m[6] + m[2] * B.m[10] + m[3] * B.m[14];
      A.m[3] = m[0] * B.m[3] + m[1] * B.m[7] + m[2] * B.m[11] + m[3] * B.m[15];
      A.m[4] = m[4] * B.m[0] + m[5] * B.m[4] + m[6] * B.m[8] + m[7] * B.m[12];
      A.m[5] = m[4] * B.m[1] + m[5] * B.m[5] + m[6] * B.m[9] + m[7] * B.m[13];
      A.m[6] = m[4] * B.m[2] + m[5] * B.m[6] + m[6] * B.m[10] + m[7] * B.m[14];
      A.m[7] = m[4] * B.m[3] + m[5] * B.m[7] + m[6] * B.m[11] + m[7] * B.m[15];
      A.m[8] = m[8] * B.m[0] + m[9] * B.m[4] + m[10] * B.m[8] + m[11] * B.m[12];
      A.m[9] = m[8] * B.m[1] + m[9] * B.m[5] + m[10] * B.m[9] + m[11] * B.m[13];
      A.m[10] =
	m[8] * B.m[2] + m[9] * B.m[6] + m[10] * B.m[10] + m[11] * B.m[14];
      A.m[11] =
	m[8] * B.m[3] + m[9] * B.m[7] + m[10] * B.m[11] + m[11] * B.m[15];
      A.m[12] =
	m[12] * B.m[0] + m[13] * B.m[4] + m[14] * B.m[8] + m[15] * B.m[12];
      A.m[13] =
	m[12] * B.m[1] + m[13] * B.m[5] + m[14] * B.m[9] + m[15] * B.m[13];
      A.m[14] =
	m[12] * B.m[2] + m[13] * B.m[6] + m[14] * B.m[10] + m[15] * B.m[14];
      A.m[15] =
	m[12] * B.m[3] + m[13] * B.m[7] + m[14] * B.m[11] + m[15] * B.m[15];
      return A;
    }

    void  CeqthismulB (const Matrix4x4<T>& B, Matrix4x4<T>& C) const
    {
      C.m[0] = m[0] * B.m[0] + m[1] * B.m[4] + m[2] * B.m[8] + m[3] * B.m[12];
      C.m[1] = m[0] * B.m[1] + m[1] * B.m[5] + m[2] * B.m[9] + m[3] * B.m[13];
      C.m[2] = m[0] * B.m[2] + m[1] * B.m[6] + m[2] * B.m[10] + m[3] * B.m[14];
      C.m[3] = m[0] * B.m[3] + m[1] * B.m[7] + m[2] * B.m[11] + m[3] * B.m[15];
      C.m[4] = m[4] * B.m[0] + m[5] * B.m[4] + m[6] * B.m[8] + m[7] * B.m[12];
      C.m[5] = m[4] * B.m[1] + m[5] * B.m[5] + m[6] * B.m[9] + m[7] * B.m[13];
      C.m[6] = m[4] * B.m[2] + m[5] * B.m[6] + m[6] * B.m[10] + m[7] * B.m[14];
      C.m[7] = m[4] * B.m[3] + m[5] * B.m[7] + m[6] * B.m[11] + m[7] * B.m[15];
      C.m[8] = m[8] * B.m[0] + m[9] * B.m[4] + m[10] * B.m[8] + m[11] * B.m[12];
      C.m[9] = m[8] * B.m[1] + m[9] * B.m[5] + m[10] * B.m[9] + m[11] * B.m[13];
      C.m[10] =
	m[8] * B.m[2] + m[9] * B.m[6] + m[10] * B.m[10] + m[11] * B.m[14];
      C.m[11] =
	m[8] * B.m[3] + m[9] * B.m[7] + m[10] * B.m[11] + m[11] * B.m[15];
      C.m[12] =
	m[12] * B.m[0] + m[13] * B.m[4] + m[14] * B.m[8] + m[15] * B.m[12];
      C.m[13] =
	m[12] * B.m[1] + m[13] * B.m[5] + m[14] * B.m[9] + m[15] * B.m[13];
      C.m[14] =
	m[12] * B.m[2] + m[13] * B.m[6] + m[14] * B.m[10] + m[15] * B.m[14];
      C.m[15] =
	m[12] * B.m[3] + m[13] * B.m[7] + m[14] * B.m[11] + m[15] * B.m[15];
    }

    void  CeqthismulB (const Vector4D<T> &B, Vector4D<T> &C) const
    {
      C.m_x = m[0] * B.m_x + m[1] * B.m_y + m[2] * B.m_z + m[3] * B.m_w;
      C.m_y = m[4] * B.m_x + m[5] * B.m_y + m[6] * B.m_z + m[7] * B.m_w;
      C.m_z = m[8] * B.m_x + m[9] * B.m_y + m[10] * B.m_z + m[11] * B.m_w;
      C.m_w = m[12] * B.m_x + m[13] * B.m_y + m[14] * B.m_z + m[15] * B.m_w;
    }

    /// \brief Multiplication operator with another vector.
    Vector3D<T> operator* (const Vector3D<T>& B) const
    {
      Vector3D<T> C;
      C.m_x = m[0] * B.m_x + m[1] * B.m_y + m[2] * B.m_z + m[3];
      C.m_y = m[4] * B.m_x + m[5] * B.m_y + m[6] * B.m_z + m[7];
      C.m_z = m[8] * B.m_x + m[9] * B.m_y + m[10] * B.m_z + m[11];
      return C;
    }

    /// \brief Multiplication operator with a vector 4d.
    Vector4D<T> operator* (const Vector4D<T> &B) const
    {
      Vector4D<T> C;
      C.m_x = m[0] * B.m_x + m[1] * B.m_y + m[2] * B.m_z + m[3] * B.m_w;
      C.m_y = m[4] * B.m_x + m[5] * B.m_y + m[6] * B.m_z + m[7] * B.m_w;
      C.m_z = m[8] * B.m_x + m[9] * B.m_y + m[10] * B.m_z + m[11] * B.m_w;
      C.m_w = m[12] * B.m_x + m[13] * B.m_y + m[14] * B.m_z + m[15] * B.m_w;
      return C;
    }

    /// \brief Multiplication operator with a constant.
    Matrix4x4<T> operator* (const T& r) const
    {
      Matrix4x4<T> result;
      result.m[0] = m[0] * r;
      result.m[1] = m[1] * r;
      result.m[2] = m[2] * r;
      result.m[3] = m[3] * r;
      result.m[4] = m[4] * r;
      result.m[5] = m[5] * r;
      result.m[6] = m[6] * r;
      result.m[7] = m[7] * r;
      result.m[8] = m[8] * r;
      result.m[9] = m[9] * r;
      result.m[10] = m[10] * r;
      result.m[11] = m[11] * r;
      result.m[12] = m[12] * r;
      result.m[13] = m[13] * r;
      result.m[14] = m[14] * r;
      result.m[15] = m[15] * r;
      return result;
    }

    /// \brief Transposition
    Matrix4x4<T> Transpose() const
    {
      struct Matrix4x4 A;
      A.m[0]  = m[0];  A.m[1]  = m[4]; A.m[2]  = m[8];  A.m[3]  = m[12];
      A.m[4]  = m[1];  A.m[5]  = m[5]; A.m[6]  = m[9];  A.m[7]  = m[13];
      A.m[8]  = m[2];  A.m[9]  = m[6]; A.m[10] = m[10]; A.m[11] = m[14];
      A.m[12] = m[3];  A.m[13] = m[7]; A.m[14] = m[11]; A.m[15] = m[15];
      return A;
    };

    /// \brief Inversion
    void Inversion(Matrix4x4 &A) const
    {
      T det = 1. / determinant ();

      A.m[0]=m[6]*m[11]*m[13] - m[7]*m[10]*m[13] + m[7]*m[9]*m[14] - m[5]*m[11]*m[14] - m[6]*m[9]*m[15] +m[5]*m[10]*m[15];
      A.m[1]=m[3]*m[10]*m[13] - m[2]*m[11]*m[13] - m[3]*m[9]*m[14] + m[1]*m[11]*m[14] + m[2]*m[9]*m[15] -m[1]*m[10]*m[15];
      A.m[2]=m[2]*m[7]*m[13] - m[3]*m[6]*m[13] + m[3]*m[5]*m[14] - m[1]*m[7]*m[14] - m[2]*m[5]*m[15] + m[1]*m[6]*m[15];
      A.m[3]=m[3]*m[6]*m[9] - m[2]*m[7]*m[9] - m[3]*m[5]*m[10] + m[1]*m[7]*m[10] + m[2]*m[5]*m[11] - m[1]*m[6]*m[11];

      A.m[4]=m[7]*m[10]*m[12] -m[6]*m[11]*m[12] -m[7]*m[8]*m[14] + m[4]*m[11]*m[14] + m[6]*m[8]*m[15] - m[4]*m[10]*m[15];
      A.m[5]=m[2]*m[11]*m[12] -m[3]*m[10]*m[12] +m[3]*m[8]*m[14] - m[0]*m[11]*m[14] - m[2]*m[8]*m[15] + m[0]*m[10]*m[15];
      A.m[6]=m[3]*m[6]*m[12] - m[2]*m[7]*m[12] - m[3]*m[4]*m[14] + m[0]*m[7]*m[14] + m[2]*m[4]*m[15] - m[0]*m[6]*m[15];
      A.m[7]=m[2]*m[7]*m[8] - m[3]*m[6]*m[8] + m[3]*m[4]*m[10] - m[0]*m[7]*m[10] - m[2]*m[4]*m[11] + m[0]*m[6]*m[11];

      A.m[8]=m[5]*m[11]*m[12] - m[7]*m[9]*m[12] + m[7]*m[8]*m[13] - m[4]*m[11]*m[13] - m[5]*m[8]*m[15] + m[4]*m[9]*m[15];
      A.m[9]=m[0]*m[11]*m[13] + m[1]*m[8]*m[15] + m[3]*m[9]*m[12] - m[0]*m[9]*m[15] - m[1]*m[11]*m[12] - m[3]*m[8]*m[13];
      A.m[10]=m[1]*m[7]*m[12] - m[3]*m[5]*m[12] + m[3]*m[4]*m[13] - m[0]*m[7]*m[13] - m[1]*m[4]*m[15] + m[0]*m[5]*m[15];
      A.m[11]=m[3]*m[5]*m[8] - m[1]*m[7]*m[8] - m[3]*m[4]*m[9] + m[0]*m[7]*m[9] + m[1]*m[4]*m[11] - m[0]*m[5]*m[11];

      A.m[12]=m[6]*m[9]*m[12] - m[5]*m[10]*m[12] - m[6]*m[8]*m[13] + m[4]*m[10]*m[13] + m[5]*m[8]*m[14] - m[4]*m[9]*m[14];
      A.m[13]=m[1]*m[10]*m[12] - m[2]*m[9]*m[12] + m[2]*m[8]*m[13] - m[0]*m[10]*m[13] - m[1]*m[8]*m[14] + m[0]*m[9]*m[14];
      A.m[14]=m[2]*m[5]*m[12] - m[1]*m[6]*m[12] - m[2]*m[4]*m[13] + m[0]*m[6]*m[13] + m[1]*m[4]*m[14] - m[0]*m[5]*m[14];
      A.m[15]=m[1]*m[6]*m[8] - m[2]*m[5]*m[8] + m[2]*m[4]*m[9] - m[0]*m[6]*m[9] - m[1]*m[4]*m[10] + m[0]*m[5]*m[10];

      A = A * det;
    }

    /// \brief Inversion.
    Matrix4x4<T> Inversion ()
    {
      Matrix4x4 A;
      T det = 1. / determinant ();

      A[0] = m[6]*m[11]*m[13] - m[7]*m[10]*m[13] + m[7]*m[9]*m[14] - m[5]*m[11]*m[14] - m[6]*m[9]*m[15] + m[5]*m[10]*m[15];
      A[1] = m[3]*m[10]*m[13] - m[2]*m[11]*m[13] - m[3]*m[9]*m[14] + m[1]*m[11]*m[14] + m[2]*m[9]*m[15] - m[1]*m[10]*m[15];
      A[2] = m[2]*m[7]*m[13] - m[3]*m[6]*m[13] + m[3]*m[5]*m[14] - m[1]*m[7]*m[14] - m[2]*m[5]*m[15] + m[1]*m[6]*m[15];
      A[3] = m[3]*m[6]*m[9] - m[2]*m[7]*m[9] - m[3]*m[5]*m[10] + m[1]*m[7]*m[10] + m[2]*m[5]*m[11] - m[1]*m[6]*m[11];

      A[4] = m[7]*m[10]*m[12] -m[6]*m[11]*m[12] -m[7]*m[8]*m[14] + m[4]*m[11]*m[14] + m[6]*m[8]*m[15] - m[4]*m[10]*m[15];
      A[5] = m[2]*m[11]*m[12] -m[3]*m[10]*m[12] +m[3]*m[8]*m[14] - m[0]*m[11]*m[14] - m[2]*m[8]*m[15] + m[0]*m[10]*m[15];
      A[6] = m[3]*m[6]*m[12] - m[2]*m[7]*m[12] - m[3]*m[4]*m[14] + m[0]*m[7]*m[14] + m[2]*m[4]*m[15] - m[0]*m[6]*m[15];
      A[7] = m[2]*m[7]*m[8] - m[3]*m[6]*m[8] + m[3]*m[4]*m[10] - m[0]*m[7]*m[10] - m[2]*m[4]*m[11] + m[0]*m[6]*m[11];

      A[8] = m[5]*m[11]*m[12] - m[7]*m[9]*m[12] + m[7]*m[8]*m[13] - m[4]*m[11]*m[13] - m[5]*m[8]*m[15] + m[4]*m[9]*m[15];
      A[9] = m[0]*m[11]*m[13] + m[1]*m[8]*m[15] + m[3]*m[9]*m[12] - m[0]*m[9]*m[15] - m[1]*m[11]*m[12] - m[3]*m[8]*m[13];
      A[10] = m[1]*m[7]*m[12] - m[3]*m[5]*m[12] + m[3]*m[4]*m[13] - m[0]*m[7]*m[13] - m[1]*m[4]*m[15] + m[0]*m[5]*m[15];
      A[11] = m[3]*m[5]*m[8] - m[1]*m[7]*m[8] - m[3]*m[4]*m[9] + m[0]*m[7]*m[9] + m[1]*m[4]*m[11] - m[0]*m[5]*m[11];

      A[12] = m[6]*m[9]*m[12] - m[5]*m[10]*m[12] - m[6]*m[8]*m[13] + m[4]*m[10]*m[13] + m[5]*m[8]*m[14] - m[4]*m[9]*m[14];
      A[13] = m[1]*m[10]*m[12] - m[2]*m[9]*m[12] + m[2]*m[8]*m[13] - m[0]*m[10]*m[13] - m[1]*m[8]*m[14] + m[0]*m[9]*m[14];
      A[14] = m[2]*m[5]*m[12] - m[1]*m[6]*m[12] - m[2]*m[4]*m[13] + m[0]*m[6]*m[13] + m[1]*m[4]*m[14] - m[0]*m[5]*m[14];
      A[15] = m[1]*m[6]*m[8] - m[2]*m[5]*m[8] + m[2]*m[4]*m[9] - m[0]*m[6]*m[9] - m[1]*m[4]*m[10] + m[0]*m[5]*m[10];

      return A * det;
    }

    /// \brief Determinant.
    T determinant() const
    {
      return m[3] * m[6] * m[9] * m[12]-m[2] * m[7] * m[9] * m[12]-m[3] * m[5] * m[10] * m[12]+m[1] * m[7]* m[10] * m[12]+
	m[2] * m[5] * m[11] * m[12]-m[1] * m[6] * m[11] * m[12]-m[3] * m[6] * m[8] * m[13]+m[2] * m[7]* m[8] * m[13]+
	m[3] * m[4] * m[10] * m[13]-m[0] * m[7] * m[10] * m[13]-m[2] * m[4] * m[11] * m[13]+m[0] * m[6]*m[11]*m[13]+
	m[3] * m[5] * m[8] * m[14]-m[1] * m[7] * m[8] * m[14]-m[3] * m[4] * m[9] * m[14]+m[0] * m[7] * m[9] * m[14]+
	m[1] * m[4] * m[11] * m[14]-m[0] * m[5] * m[11] * m[14]-m[2] * m[5] * m[8] * m[15]+m[1] *m[6] * m[8] * m[15]+
	m[2] * m[4] * m[9] * m[15]-m[0] * m[6] * m[9] * m[15]-m[1] * m[4] * m[10] * m[15]+m[0] * m[5] * m[10] * m[15];
    }

    T trace() const
    {
      return m[0]+m[5]+m[10]+m[15];
    }

    /// \brief Self matrix addition.
    void operator += (const Matrix3x3<T>& B)
    {
      m[0] += B.m[0];
      m[1] += B.m[1];
      m[2] += B.m[2];
      m[3] += B.m[3];
      m[4] += B.m[4];
      m[5] += B.m[5];
      m[6] += B.m[6];
      m[7] += B.m[7];
      m[8] += B.m[8];
      m[9] += B.m[0];
      m[10] += B.m[10];
      m[11] += B.m[11];
      m[12] += B.m[12];
      m[13] += B.m[13];
      m[14] += B.m[14];
      m[15] += B.m[15];
    }


    /// \brief Local matrix subtraction.
    void operator -= (const Matrix4x4<T>& B)
    {
      m[0] -= B.m[0];
      m[1] -= B.m[1];
      m[2] -= B.m[2];
      m[3] -= B.m[3];
      m[4] -= B.m[4];
      m[5] -= B.m[5];
      m[6] -= B.m[6];
      m[7] -= B.m[7];
      m[8] -= B.m[8];
      m[9] -= B.m[9];
      m[10] -= B.m[10];
      m[11] -= B.m[11];
      m[12] -= B.m[12];
      m[13] -= B.m[13];
      m[14] -= B.m[14];
      m[15] -= B.m[15];
    }

    /// Local matrix multiplication.
    void operator *= (const Matrix4x4<T>& B)
    {
      Matrix4x4<T> temp (*this);
      m[0] = temp.m[0] * B.m[0] + temp.m[1] * B.m[4] + temp.m[2] * B.m[8] + temp.m[3] * B.m[12];
      m[1] = temp.m[0] * B.m[1] + temp.m[1] * B.m[5] + temp.m[2] * B.m[9] + temp.m[3] * B.m[13];
      m[2] = temp.m[0] * B.m[2] + temp.m[1] * B.m[6] + temp.m[2] * B.m[10] + temp.m[3] * B.m[14];
      m[3] = temp.m[0] * B.m[3] + temp.m[1] * B.m[7] + temp.m[2] * B.m[11] + temp.m[3] * B.m[15];
      m[4] = temp.m[4] * B.m[0] + temp.m[5] * B.m[4] + temp.m[6] * B.m[8] + temp.m[7] * B.m[12];
      m[5] = temp.m[4] * B.m[1] + temp.m[5] * B.m[5] + temp.m[6] * B.m[9] + temp.m[7] * B.m[13];
      m[6] = temp.m[4] * B.m[2] + temp.m[5] * B.m[6] + temp.m[6] * B.m[10] + temp.m[7] * B.m[14];
      m[7] = temp.m[4] * B.m[3] + temp.m[5] * B.m[7] + temp.m[6] * B.m[11] + temp.m[7] * B.m[15];
      m[8] = temp.m[8] * B.m[0] + temp.m[9] * B.m[4] + temp.m[10] * B.m[8] + temp.m[11] * B.m[12];
      m[9] = temp.m[8] * B.m[1] + temp.m[9] * B.m[5] + temp.m[10] * B.m[9] + temp.m[11] * B.m[13];
      m[10] = temp.m[8] * B.m[2] + temp.m[9] * B.m[6] + temp.m[10] * B.m[10] + temp.m[11] * B.m[14];
      m[11] = temp.m[8] * B.m[3] + temp.m[9] * B.m[7] + temp.m[10] * B.m[11] + temp.m[11] * B.m[15];
      m[12] = temp.m[12] * B.m[0] + temp.m[13] * B.m[4] + temp.m[14] * B.m[8] + temp.m[15] * B.m[12];
      m[13] = temp.m[12] * B.m[1] + temp.m[13] * B.m[5] + temp.m[14] * B.m[9] + temp.m[15] * B.m[13];
      m[14] = temp.m[12] * B.m[2] + temp.m[13] * B.m[6] + temp.m[14] * B.m[10] + temp.m[15] * B.m[14];
      m[15] = temp.m[12] * B.m[3] + temp.m[13] * B.m[7] + temp.m[14] * B.m[11] + temp.m[15] * B.m[15];
    }

    /// Local matrix multiplication.
    void operator *= (const T &t)
    {
      m[0] *= t;
      m[1] *= t;
      m[2] *= t;
      m[3] *= t;
      m[4] *= t;
      m[5] *= t;
      m[6] *= t;
      m[7] *= t;
      m[8] *= t;
      m[9] *= t;
      m[10] *= t;
      m[11] *= t;
      m[12] *= t;
      m[13] *= t;
      m[14] *= t;
      m[15] *= t;
    }

    inline std::ostream& display (std::ostream& os) const
    {
      for (int i = 0; i  <4; ++i)
	{
	  for(int j = 0; j < 4; ++j)
	    os << m[i*4+j] << " ";
	  os << std::endl;
	}
      return os;
    }
  };

  template <typename T>
  inline std::ostream& operator<< (std::ostream& os, const Matrix4x4<T>& m)
  {
    return m.display (os);
  }

} // end of namespace jrlMathTools.

#endif //! JRL_MATHTOOLS_MATRIX4x4_HH
