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
 */

#ifndef JRL_MATHTOOLS_MATRIX3x3_HH
# define JRL_MATHTOOLS_MATRIX3x3_HH
# include <stdexcept>
# include <jrl/mathtools/fwd.hh>
# include <jrlMathTools/vector3.h>

namespace jrlMathTools
{
  /// \brief Generic 3x3 matrix.
  ///
  /// This matrix has been designed to be as simple and efficient as
  /// possible.
  template <typename T>
  struct Matrix3x3
  {
    /// \brief The data array.
    T m[9];

    /// Default constructor.
    Matrix3x3<T> ()
    {
      m[0]=T (); m[1] = T (); m[2]=T ();
      m[3]=T (); m[4] = T (); m[5]=T ();
      m[6]=T (); m[7] = T (); m[8]=T ();
    }

    /// \brief Constructor form a scalar.
    Matrix3x3<T> (const T x)
    {
      m[0]=x; m[1] = x; m[2]=x;
      m[3]=x; m[4] = x; m[5]=x;
      m[6]=x; m[7] = x; m[8]=x;
    }

    /// \brief Constructor from 9 scalars.
    explicit Matrix3x3<T> (
			   const T x0, const T x1, const T x2,
			   const T x3, const T x4, const T x5,
			   const T x6, const T x7, const T x8
			   )
    {
      m[0]=x0; m[1] = x1; m[2]=x2;
      m[3]=x3; m[4] = x4; m[5]=x5;
      m[6]=x6; m[7] = x7; m[8]=x8;
    }

    /// \brief Copy constructor.
    Matrix3x3<T> (const Matrix3x3<T>& v)
    {
      m[0] = v.m[0]; m[1] = v.m[1]; m[2] = v.m[2];
      m[3] = v.m[3]; m[4] = v.m[4]; m[5] = v.m[5];
      m[6] = v.m[6]; m[7] = v.m[7]; m[8] = v.m[8];
    }

    /// \brief Hybrid copy constructor.
    template <typename T2>
    Matrix3x3<T> (const Matrix3x3<T2>& v)
    {
      m[0] = v.m[0]; m[1] = v.m[1]; m[2] = v.m[2];
      m[3] = v.m[3]; m[4] = v.m[4]; m[5] = v.m[5];
      m[6] = v.m[6]; m[7] = v.m[7]; m[8] = v.m[8];
    }

    /// \brief i-th element considering the matrix as an array.
    inline T& operator[] (unsigned int i)
    {
      if (i >= 9)
	throw std::logic_error ("bad index");
      return m[i];
    }

    /// \brief i-th element considering the matrix as an array.
    inline const T& operator[] (unsigned int i) const
    {
      if (i >= 9)
	throw std::logic_error ("bad index");
      return m[i];
    }

    /// \brief Access by giving the (i,j) element.
    inline T& operator() (unsigned int i, unsigned int j)
    {
      if (i >= 3 || j >= 3)
	throw std::logic_error ("bad index");
      return m[3*i+j];
    }

    /// \brief Access by giving the (i,j) element.
    inline const T & operator() (unsigned int i, unsigned int j) const
    {
      if (i >= 3 || j >= 3)
	throw std::logic_error ("bad index");
      return m[3*i+j];
    }

    /// \brief Set to zero matrix.
    inline void setZero ()
    {
      m[0] = T (); m[1] = T (); m[2] = T ();
      m[3] = T (); m[4] = T (); m[5] = T ();
      m[6] = T (); m[7] = T (); m[8] = T ();
    }

    /// \brief Set to identity.
    inline void setIdentity()
    {
      m[0] = 1;    m[1] = T (); m[2] = T ();
      m[3] = T (); m[4] = 1;    m[5] = T ();
      m[6] = T (); m[7] = T (); m[8] = 1;
    }

    /// \brief Adition operator.
    Matrix3x3<T> operator+(const Matrix3x3<T> & B) const
    {
      Matrix3x3<T> A;
      A.m[0] = m[0] + B.m[0]; A.m[1] = m[1] + B.m[1]; A.m[2] = m[2] + B.m[2];
      A.m[3] = m[3] + B.m[3]; A.m[4] = m[4] + B.m[4]; A.m[5] = m[5] + B.m[5];
      A.m[6] = m[6] + B.m[6]; A.m[7] = m[7] + B.m[7]; A.m[8] = m[8] + B.m[8];
      return A;
    }

    /// \brief Substraction operator.
    Matrix3x3<T>  operator-(const Matrix3x3<T> &B) const
    {
      Matrix3x3<T> A;
      A.m[0] = m[0] - B.m[0]; A.m[1] = m[1] - B.m[1]; A.m[2] = m[2] - B.m[2];
      A.m[3] = m[3] - B.m[3]; A.m[4] = m[4] - B.m[4]; A.m[5] = m[5] - B.m[5];
      A.m[6] = m[6] - B.m[6]; A.m[7] = m[7] - B.m[7]; A.m[8] = m[8] - B.m[8];
      return A;
    }

    /// \brief Multiplication operator with another matrix.
    Matrix3x3<T>  operator* (const Matrix3x3<T> &B) const
    {
      Matrix3x3<T> A;
      A.m[0] = m[0] * B.m[0] + m[1] * B.m[3] + m[2] * B.m[6];
      A.m[1] = m[0] * B.m[1] + m[1] * B.m[4] + m[2] * B.m[7];
      A.m[2] = m[0] * B.m[2] + m[1] * B.m[5] + m[2] * B.m[8];
      A.m[3] = m[3] * B.m[0] + m[4] * B.m[3] + m[5] * B.m[6];
      A.m[4] = m[3] * B.m[1] + m[4] * B.m[4] + m[5] * B.m[7];
      A.m[5] = m[3] * B.m[2] + m[4] * B.m[5] + m[5] * B.m[8];
      A.m[6] = m[6] * B.m[0] + m[7] * B.m[3] + m[8] * B.m[6];
      A.m[7] = m[6] * B.m[1] + m[7] * B.m[4] + m[8] * B.m[7];
      A.m[8] = m[6] * B.m[2] + m[7] * B.m[5] + m[8] * B.m[8];
      return A;
    }

    void CeqthismulB (const Matrix3x3<T> &B, Matrix3x3<T> &C) const
    {
      C.m[0] = m[0] * B.m[0] + m[1] * B.m[3] + m[2] * B.m[6];
      C.m[1] = m[0] * B.m[1] + m[1] * B.m[4] + m[2] * B.m[7];
      C.m[2] = m[0] * B.m[2] + m[1] * B.m[5] + m[2] * B.m[8];
      C.m[3] = m[3] * B.m[0] + m[4] * B.m[3] + m[5] * B.m[6];
      C.m[4] = m[3] * B.m[1] + m[4] * B.m[4] + m[5] * B.m[7];
      C.m[5] = m[3] * B.m[2] + m[4] * B.m[5] + m[5] * B.m[8];
      C.m[6] = m[6] * B.m[0] + m[7] * B.m[3] + m[8] * B.m[6];
      C.m[7] = m[6] * B.m[1] + m[7] * B.m[4] + m[8] * B.m[7];
      C.m[8] = m[6] * B.m[2] + m[7] * B.m[5] + m[8] * B.m[8];
    }

    /// \brief Multiplication operator with a constant.
    Matrix3x3<T> operator * (const T& r) const
    {
      Matrix3x3<T> result;
      result.m[0] = m[0] * r;
      result.m[1] = m[1] * r;
      result.m[2] = m[2] * r;
      result.m[3] = m[3] * r;
      result.m[4] = m[4] * r;
      result.m[5] = m[5] * r;
      result.m[6] = m[6] * r;
      result.m[7] = m[7] * r;
      result.m[8] = m[8] * r;
      return result;
    }

# ifdef MAL_S3_VECTOR
    /// \brief Multiplication operator with a vector.
    MAL_S3_VECTOR (,T) operator *(const MAL_S3_VECTOR(,T)& v) const
    {
      MAL_S3_VECTOR (vr,T);
      vr[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
      vr[1] = m[3] * v[0] + m[4] * v[1] + m[5] * v[2];
      vr[2] = m[6] * v[0] + m[7] * v[1] + m[8] * v[2];
      return vr;
    }

    /// \brief Multiplication operator with a vector.
    void CeqthismulB (const MAL_S3_VECTOR(,T)& B, MAL_S3_VECTOR(,T)& C) const
      {
	C[0] = m[0] * B[0] + m[1] * B[1] + m[2] * B[2];
	C[1] = m[3] * B[0] + m[4] * B[1] + m[5] * B[2];
	C[2] = m[6] * B[0] + m[7] * B[1] + m[8] * B[2];
      }
# endif // MAL_S3_VECTOR

    /// \brief Transposition.
    Matrix3x3<T> Transpose () const
    {
      Matrix3x3<T> A;
      A.m[0] = m[0]; A.m[1] = m[3]; A.m[2] = m[6];
      A.m[3] = m[1]; A.m[4] = m[4]; A.m[5] = m[7];
      A.m[6] = m[2]; A.m[7] = m[5]; A.m[8] = m[8];
      return A;
    }

    /// \brief Transposition.
    void Transpose(Matrix3x3<T>& A) const
    {
      A.m[0] = m[0]; A.m[1] = m[3]; A.m[2] = m[6];
      A.m[3] = m[1]; A.m[4] = m[4]; A.m[5] = m[7];
      A.m[6] = m[2]; A.m[7] = m[5]; A.m[8] = m[8];
    }

    /// \brief Inversion.
    void Inversion(Matrix3x3<T>& A) const
    {
      T det = 1. / determinant ();
      A.m[0] = (m[4] * m[8] - m[5] * m[7]) * det;
      A.m[1] = (m[2] * m[7] - m[1] * m[8]) * det;
      A.m[2] = (m[1] * m[5] - m[2] * m[4]) * det;
      A.m[3] = ( m[5] * m[6] - m[3] * m[8] ) * det;
      A.m[4] = ( m[0] * m[8] - m[2] * m[6] ) * det;
      A.m[5] = ( m[2] * m[3] - m[0] * m[5] ) * det;
      A.m[6] = ( m[3] * m[7] - m[4] * m[6] ) * det;
      A.m[7] = ( m[1] * m[6] - m[0] * m[7] ) * det;
      A.m[8] = ( m[0] * m[4] - m[1] * m[3] ) * det;
    }

    /// \brief Determinant.
    T determinant() const
    {
      return m[0] * m[4] * m[8]
	+ m[1] * m[5] * m[6]
	+ m[2] * m[3] * m[7]
	- m[2] * m[4] * m[6]
	- m[0] * m[5] * m[7]
	- m[1] * m[3] * m[8];
    }

    /// \brief Fills with value.
    void Fill(T value)
    {
      m[0] = value;
      m[1] = value;
      m[2] = value;
      m[3] = value;
      m[4] = value;
      m[5] = value;
      m[6] = value;
      m[7] = value;
      m[8] = value;
    }

    /// \brief returns true if matrix is identity.
    bool IsIdentity () const
    {
      return
	((m[0] == 1) && (m[4] == 1) && (m[8] == 1) && (m[1] == T ())
	 && (m[2] == T ()) && (m[3] == T ()) && (m[5] == T ()) && (m[6] == T ())
	 && (m[7] == T ()));
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
    }

    /// \brief Local matrix subtraction.
    void operator -= (const Matrix3x3<T>& B)
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
    }

    /// \brief Local matrix multiplication.
    void operator *= (const Matrix3x3<T>& B)
    {
      Matrix3x3<T> temp(*this);
      m[0] = temp.m[0] * B.m[0] + temp.m[1] * B.m[3] + temp.m[2] * B.m[6];
      m[1] = temp.m[0] * B.m[1] + temp.m[1] * B.m[4] + temp.m[2] * B.m[7];
      m[2] = temp.m[0] * B.m[2] + temp.m[1] * B.m[5] + temp.m[2] * B.m[8];
      m[3] = temp.m[3] * B.m[0] + temp.m[4] * B.m[3] + temp.m[5] * B.m[6];
      m[4] = temp.m[3] * B.m[1] + temp.m[4] * B.m[4] + temp.m[5] * B.m[7];
      m[5] = temp.m[3] * B.m[2] + temp.m[4] * B.m[5] + temp.m[5] * B.m[8];
      m[6] = temp.m[6] * B.m[0] + temp.m[7] * B.m[3] + temp.m[8] * B.m[6];
      m[7] = temp.m[6] * B.m[1] + temp.m[7] * B.m[4] + temp.m[8] * B.m[7];
      m[8] = temp.m[6] * B.m[2] + temp.m[7] * B.m[5] + temp.m[8] * B.m[8];
    }

    /// \brief Matrix product with a scalar.
    void operator *= (const T& t)
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
    }

    inline std::ostream& display (std::ostream& os)
    {
      for(int i = 0; i < 3; ++i)
	{
	  for(int j = 0; j < 3; ++j)
	    os << m[i*3+j] << " ";
	  os << std::endl;
	}
      return os;
    }
  };

  template <typename T>
  inline std::ostream& operator<< (std::ostream& os, const Matrix3x3<T>& m)
  {
    return m.display (os);
  }

} // end of namespace jrlMathTools.

#endif //! JRL_MATHTOOLS_MATRIX3x3_HH
