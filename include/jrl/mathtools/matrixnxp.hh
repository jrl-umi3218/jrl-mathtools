/*
 * Copyright 2009, 2010, Olivier Stasse,
 *                       Florent Lamiraux, CNRS/AIST
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

#ifndef JRL_MATHTOOLS_MATRIXNXP_HH
# define JRL_MATHTOOLS_MATRIXNXP_HH

# include <boost/numeric/ublas/matrix_proxy.hpp>
# include <boost/numeric/ublas/matrix.hpp>
# include <boost/numeric/ublas/io.hpp>

# include <jrl/mathtools/fwd.hh>
# include <jrl/mathtools/vectorn.hh>

typedef boost_ublas::matrix<double> matrixNxP;

extern "C"
{
  void dgesvd_(char const* jobu, char const* jobvt,
	       int const* m, int const* n, double* a, int const* lda,
	       double* s, double* u, int const* ldu,
	       double* vt, int const* ldvt,
	       double* work, int const* lwork, int* info);
}

namespace jrlMathTools
{
  static const bool AUTORESIZE = true;
  static const bool CHECKRESIZE = true;

  void _resize (matrixNxP& mat1, const matrixNxP& mat2)
  {
    if(AUTORESIZE)
      mat1.resize(mat2.size1(),mat2.size2());
  }

  void _resizeInv (matrixNxP& res, const matrixNxP& mat2)
  {
    if(AUTORESIZE)
      res.resize(mat2.size2(), mat2.size1());
  }

  /// \brief Compute the pseudo-inverse of the matrix.
  ///
  /// By default, the function uses the dgesvd_ fortran routine.
  /// It should be provided by the host software.
  matrixNxP& pseudoInverse (const matrixNxP& matrix,
			    matrixNxP& outInverse,
			    const double threshold = 1e-6,
			    matrixNxP* Uref = 0,
			    vectorN* Sref = 0,
			    matrixNxP* Vref = 0)
  {
    unsigned int NR = 0, NC = 0;
    bool toTranspose = false;
    boost_ublas::matrix<double,boost_ublas::column_major> transpOrNot;

    if (matrix.size1 () > matrix.size2())
      {
	toTranspose = false;
	NR=matrix.size1();
	NC=matrix.size2();
	transpOrNot=matrix;
	_resizeInv(outInverse, transpOrNot);
      }
    else
      {
	toTranspose=true;
	NR=matrix.size2();
	NC=matrix.size1();
	transpOrNot = trans(matrix);
	_resizeInv(outInverse, transpOrNot); // Resize the inv of the transpose.
      }

    boost_ublas::matrix<double,boost_ublas::column_major> U (NR,NR);
    boost_ublas::matrix<double,boost_ublas::column_major> VT (NC,NC);
    boost_ublas::vector<double> s(std::min(NR,NC));
    char Jobu='A'; /* Compute complete U Matrix */
    char Jobvt='A'; /* Compute complete VT Matrix */
    char Lw; Lw='O'; /* Compute the optimal size for the working vector */

    {
      double vw;
      int lw=-1;

      int linfo; const int n=NR,m=NC;
      int lda = std::max(m,n);
      int lu = traits::leading_dimension(U); // NR
      int lvt = traits::leading_dimension(VT); // NC

      dgesvd_(&Jobu, &Jobvt, &m, &n,
	      MRAWDATA(transpOrNot), &lda,
	      0, 0, &m, 0, &n, &vw, &lw, &linfo);
      lw = int(vw)+5;

      boost_ublas::vector<double> w(lw);
      dgesvd_(&Jobu, &Jobvt,&n,&m,
	      MRAWDATA(transpOrNot),
	      &lda,
	      VRAWDATA(s),//vector_storage(s),
	      MRAWDATA(U),
	      &lu,
	      MRAWDATA(VT),
	      &lvt,
	      VRAWDATA(w),&lw,&linfo);

    }


    const unsigned int nsv = s.size();
    unsigned int rankJ = 0;
    boost_ublas::vector<double> sp(nsv);
    for( unsigned int i=0;i<nsv;++i )
      if( fabs(s(i))>threshold ) { sp(i)=1/s(i); rankJ++; }
      else sp(i)=0.;
    outInverse.clear();
    {
      double * pinv = MRAWDATA(outInverse);
      double * uptr;
      double * uptrRow;
      double * vptr;
      double * vptrRow = MRAWDATA(VT);

      double * spptr;

      for( unsigned int i=0;i<NC;++i ) {
	uptrRow = MRAWDATA(U);
	for( unsigned int j=0;j<NR;++j ) {
	  uptr = uptrRow;  vptr = vptrRow;
	  spptr = VRAWDATA(sp);
	  for( unsigned int k=0;k<rankJ;++k ) {
	    (*pinv) += (*vptr) * (*spptr) * (*uptr);
	    uptr+=NR; vptr++; spptr++;
	  }
	  pinv++; uptrRow++;
	}
	vptrRow += NC;
      }
    }
    if (toTranspose) {
      outInverse = trans(outInverse);
      if( Uref ) *Uref = VT;
      if( Vref ) *Vref = trans(U);
      if( Sref ) *Sref=s;
    } else {
      if( Uref ) *Uref = U;
      if( Vref ) *Vref = trans(VT);
      if( Sref ) *Sref=s;
    }
    return outInverse;
  }

  matrixNxP dampedInverse (const matrixNxP& inMatrix,
			   matrixNxP& invMatrix,
			   const double threshold = 1e-6,
			   matrixNxP* Uref = 0,
			   vectorN* Sref = 0,
			   matrixNxP* Vref = 0)
    {
      unsigned int NR,NC;
      bool toTranspose;
      boost_ublas::matrix<double,boost_ublas::column_major> I;

      if(inMatrix.size1() > inMatrix.size2())
	{
	  toTranspose=false ;
	  NR=inMatrix.size1();
	  NC=inMatrix.size2();
	  I=inMatrix;
	  _resizeInv(invMatrix,inMatrix);
	}
      else
	{
	  toTranspose=true;
	  NR=inMatrix.size2();
	  NC=inMatrix.size1();
	  I = trans(inMatrix);
	  _resize(invMatrix, inMatrix); // Resize the inv of the transpose.
	}

      boost_ublas::matrix<double,boost_ublas::column_major> U(NR,NR);
      boost_ublas::matrix<double,boost_ublas::column_major> VT(NC,NC);
      boost_ublas::vector<double> s(std::min(NR,NC));
      char Jobu='A'; /* Compute complete U Matrix */
      char Jobvt='A'; /* Compute complete VT Matrix */
      char Lw; Lw='O'; /* Compute the optimal size for the working vector */

      /* Get workspace size for svd. */
      {
	int lw=-1;
	{
	  double vw;

	  int linfo; const int n=NR,m=NC;
	  int lda = std::max(m,n);
	  int lu = traits::leading_dimension(U); // NR
	  int lvt = traits::leading_dimension(VT); // NC

	  dgesvd_(&Jobu, &Jobvt, &m, &n,
		  MRAWDATA(I), &lda,
		  0, 0, &m, 0, &n, &vw, &lw, &linfo);
	  lw = int(vw)+5;

	  boost_ublas::vector<double> w(lw);
	  dgesvd_(&Jobu, &Jobvt,&n,&m,
		  MRAWDATA(I),
		  &lda,
		  VRAWDATA(s),
		  MRAWDATA(U),
		  &lu,
		  MRAWDATA(VT),
		  &lvt,
		  VRAWDATA(w),&lw,&linfo);
	}

      }

      const unsigned int nsv = s.size();
      unsigned int rankJ = 0;
      boost_ublas::vector<double> sp(nsv);
      for( unsigned int i=0;i<nsv;++i )
	{
	  if( fabs(s(i))>threshold*.1 )   rankJ++;
	  sp(i)=s(i)/(s(i)*s(i)+threshold*threshold);
	}
      invMatrix.clear();
      {
	double * pinv = MRAWDATA(invMatrix);
	double * uptr;
	double * uptrRow;
	double * vptr;
	double * vptrRow = MRAWDATA(VT);

	double * spptr;

	for( unsigned int i=0;i<NC;++i )
	  {
	    uptrRow = MRAWDATA(U);
	    for( unsigned int j=0;j<NR;++j )
	      {
		uptr = uptrRow;  vptr = vptrRow;
		spptr = VRAWDATA(sp);
		for( unsigned int k=0;k<rankJ;++k )
		  {
		    (*pinv) += (*vptr) * (*spptr) * (*uptr);
		    uptr+=NR; vptr++; spptr++;
		  }
		pinv++; uptrRow++;
	      }
	    vptrRow += NC;
	  }
      }
      if(toTranspose) {
	invMatrix = trans(invMatrix);
	if(Uref) *Uref = VT;
	if(Vref) *Vref = trans(U);
	if(Sref) *Sref=s;
      } else {
	if(Uref) *Uref = U;
	if(Vref) *Vref = trans(VT);
	if(Sref) *Sref=s;
      }
      return invMatrix;
    }
} // end of namespace jrlMathTools.

#endif //! JRL_MATHTOOLS_MATRIXNXP_HH
