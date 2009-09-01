/*
  Copyright JRL AIST-CNRS

  Authors: Florent Lamiraux, Nicolas Mansard
*/

#ifndef JRLMATHTOOLS_MATRIXNXP_H
#define JRLMATHTOOLS_MATRIXNXP_H

/*
  Avoid conflict with MatrixAbstractLayer
*/
#ifndef _MATRIX_ABSTRACT_LAYER_H_
namespace boost_ublas = boost::numeric::ublas;
namespace traits = boost::numeric::bindings::traits;
namespace lapack = boost::numeric::bindings::lapack;

typedef boost_ublas::matrix<double> matrixNxP;
#endif

extern "C"
{
  void dgesvd_(char const* jobu, char const* jobvt,
	       int const* m, int const* n, double* a, int const* lda,
	       double* s, double* u, int const* ldu,
	       double* vt, int const* ldvt,
	       double* work, int const* lwork, int* info);
}

class vectorN;

namespace jrlMathTools {

  static const bool AUTORESIZE = true;
  static const bool CHECKRESIZE = true;

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
  virtual Matrix& 
    pseudoInverse(const matrixNxP& matrix,
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
};

#endif
