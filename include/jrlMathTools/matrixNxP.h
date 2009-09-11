/*
  Copyright JRL AIST-CNRS

  Authors: Florent Lamiraux, Nicolas Mansard
*/

#ifndef JRLMATHTOOLS_MATRIXNXP_H
#define JRLMATHTOOLS_MATRIXNXP_H

#include "boost/numeric/ublas/matrix_proxy.hpp"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"
#include "boost/numeric/bindings/traits/ublas_matrix.hpp"

#include "jrlMathTools/vectorN.h"

typedef boost_ublas::matrix<double> matrixNxP;

extern "C"
{
  void dgesvd_(char const* jobu, char const* jobvt,
	       int const* m, int const* n, double* a, int const* lda,
	       double* s, double* u, int const* ldu,
	       double* vt, int const* ldvt,
	       double* work, int const* lwork, int* info);
}

namespace jrlMathTools {

  static const bool AUTORESIZE = true;
  static const bool CHECKRESIZE = true;

  void _resize(matrixNxP& mat1,const matrixNxP& mat2 )
  { if(AUTORESIZE) { 
      mat1.resize(mat2.size1(),mat2.size2()); 
    } 
  }

  void _resizeInv(matrixNxP& res, const matrixNxP& mat2)
  { 
    if(AUTORESIZE) { 
      res.resize(mat2.size2(), mat2.size1()); 
    } 
  }

  /** \brief Compute the pseudo-inverse of the matrix. 
   *  
   * By default, the function uses the dgesvd_ fortran routine. 
   * It should be provided by the host software. 
   */
  matrixNxP& pseudoInverse(const matrixNxP& matrix,
			   matrixNxP& outInverse,
			   const double threshold = 1e-6,
			   matrixNxP* Uref = NULL,
			   vectorN* Sref = NULL,
			   matrixNxP* Vref = NULL)
  {	
    unsigned int NR,NC;
    bool toTranspose;
    boost_ublas::matrix<double,boost_ublas::column_major> transpOrNot;
    if( matrix.size1()>matrix.size2() ) { 
      toTranspose=false ;  NR=matrix.size1(); NC=matrix.size2();
      transpOrNot=matrix;
      _resizeInv(outInverse,transpOrNot);
    } else {
      toTranspose=true; NR=matrix.size2(); NC=matrix.size1();
      transpOrNot = trans(matrix); 
      _resizeInv(outInverse,transpOrNot); // Resize the inv of the transpose.
    }

    boost_ublas::matrix<double,boost_ublas::column_major> U(NR,NR); 
    boost_ublas::matrix<double,boost_ublas::column_major> VT(NC,NC);	
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
	      traits::matrix_storage(transpOrNot), &lda,       
	      0, 0, &m, 0, &n, &vw, &lw, &linfo);    
      lw = int(vw)+5;                                 
       
      boost_ublas::vector<double> w(lw);		 
      dgesvd_(&Jobu, &Jobvt,&n,&m,
	      traits::matrix_storage(transpOrNot),
	      &lda,
	      traits::vector_storage(s),
	      traits::matrix_storage(U),
	      &lu,
	      traits::matrix_storage(VT),
	      &lvt,
	      traits::vector_storage(w),&lw,&linfo);
       
    }


    const unsigned int nsv = s.size();
    unsigned int rankJ = 0;
    boost_ublas::vector<double> sp(nsv);
    for( unsigned int i=0;i<nsv;++i )		
      if( fabs(s(i))>threshold ) { sp(i)=1/s(i); rankJ++; }
      else sp(i)=0.;		
    outInverse.clear();
    {
      double * pinv = traits::matrix_storage(outInverse);
      double * uptr;
      double * uptrRow;
      double * vptr;
      double * vptrRow = traits::matrix_storage(VT);
       
      double * spptr;
       
      for( unsigned int i=0;i<NC;++i ) {
	uptrRow = traits::matrix_storage(U);
	for( unsigned int j=0;j<NR;++j ) {
	  uptr = uptrRow;  vptr = vptrRow; 
	  spptr = traits::vector_storage( sp );
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





  matrixNxP dampedInverse(const matrixNxP& inMatrix,  
			  matrixNxP& invMatrix,
			  const double threshold = 1e-6,
			  matrixNxP* Uref = NULL,
			  vectorN* Sref = NULL,
			  matrixNxP* Vref = NULL)  
    {	
      unsigned int NR,NC;
      bool toTranspose;
      boost_ublas::matrix<double,boost_ublas::column_major> I;
      if( inMatrix.size1()>inMatrix.size2() )
	{ 
	  toTranspose=false ;  NR=inMatrix.size1(); NC=inMatrix.size2();
	  I=inMatrix; 
	  _resizeInv(invMatrix,inMatrix);
	}
      else 
	{
	  toTranspose=true; NR=inMatrix.size2(); NC=inMatrix.size1();
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
		  traits::matrix_storage(I), &lda,       
		  0, 0, &m, 0, &n, &vw, &lw, &linfo);    
	  lw = int(vw)+5;                                 
	 
	  boost_ublas::vector<double> w(lw);		 
	  dgesvd_(&Jobu, &Jobvt,&n,&m,
		  traits::matrix_storage(I),
		  &lda,
		  traits::vector_storage(s),
		  traits::matrix_storage(U),
		  &lu,
		  traits::matrix_storage(VT),
		  &lvt,
		  traits::vector_storage(w),&lw,&linfo);
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
	double * pinv = traits::matrix_storage(invMatrix);
	double * uptr;
	double * uptrRow;
	double * vptr;
	double * vptrRow = traits::matrix_storage(VT);
       
	double * spptr;
       
	for( unsigned int i=0;i<NC;++i )
	  {
	    uptrRow = traits::matrix_storage(U);
	    for( unsigned int j=0;j<NR;++j )
	      {
		uptr = uptrRow;  vptr = vptrRow; 
		spptr = traits::vector_storage( sp );
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


};

#endif
