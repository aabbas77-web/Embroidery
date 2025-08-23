/********************************************************************
   The Image Processing Library 98 - IPL98
   Copyright (C) by René Dencker Eriksen - edr@mip.sdu.dk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation. Only
   addition is, that if the library is used in proprietary software
   it must be stated that IPL98 was used.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   More details can be found in the file licence.txt distributed
   with this library.
*********************************************************************/

#include "equation_solver.h"

namespace ipl{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CEquationSolver::CEquationSolver()
{

}


CEquationSolver::~CEquationSolver()
{

}


vector<float> CEquationSolver::LinearSolve(CArray2D<float>& A, vector<float>& b) {
   vector<unsigned int> index; // changed from int to unsigned int by edr
   this->LUDecomp(A,index);
   return this->LUSolve(A,index,b);
}


vector<float> CEquationSolver::CholeskyLinearSolve(CArray2D<float>& A, vector<float>& b) {
   int n = b.size();
   vector<float> p, x;
   p.resize(n);
   x.resize(n);
   this->CholeskyDecomp(A, p);
   return this->CholeskySolve(A,p,b,x);
}


void CEquationSolver::LUDecomp(CArray2D<float>& a, vector<unsigned int>& index) {
   int i, imax = 0, j, k;
   int n = a.GetHeight();
   double big, dum, sum, temp;
   vector<float> vv; vv.resize(n);
   index.resize(n);

   for (i=0; i<n; i++) index[i] = i;

   for (i=0; i<n; i++) {
      big = 0.0;
      for (j=0; j<n; j++) {
         if ((temp = abs(a[i][j])) > big) big = temp;
      }
      if (big == 0.0) {
         printf("Singular matrix in LU decompisition.\n");
      }
      vv[i] = 1.0 / big;
   }
   for (j=0; j<n; j++) {
      for (i=0; i<j; i++) {
         sum = a[i][j];
         for (k=0; k<i; k++) sum -= a[i][k] * a[k][j];
         a[i][j] = sum;
      }
      big = 0.0;
      for (i=j; i<n; i++) {
         sum = a[i][j];
         for (k=0; k<j; k++) sum -= a[i][k] * a[k][j];
         a[i][j] = sum;
         if ((dum = vv[i] * abs(sum)) >= big) {
            big = dum;
            imax = i;
         }
      }
      if (j != imax) { 
         for (k=0; k<n; k++) {
            dum = a[imax][k];
            a[imax][k] = a[j][k];
            a[j][k] = dum;
         }
         vv[imax] = vv[j];
      }
      index[j] = imax;
      if (a[j][j] == 0.0) a[j][j] = (float) 1.0e-20;
      if (j != n-1) {
         dum = 1.0/(a[j][j]);
         for (i=j+1; i<n; i++) a[i][j] *= dum;
      }
   }
}     


vector<float> CEquationSolver::LUSolve(CArray2D<float>& a, vector<unsigned int>& index, vector<float>& b) {
   int i, ii=0, ip, j;
   int n = a.GetHeight();
   float sum;

   // Forward substitution.
   for (i=0; i<n; i++) {
      ip = index[i];
      sum = b[ip];
      b[ip] = b[i];
      if (ii == 0) 
         for (j=ii; j<=i-1; j++) sum -= a[i][j] * b[j];
      else if (sum == 0.0f) ii = i;
      b[i] = sum;
   }
   
   // Backward substitution.
   for (i=n-1; i>=0; i--) {
      sum = b[i];
      for (j = i+1; j<n; j++) sum -= a[i][j] * b[j];
      b[i] = sum / a[i][i];
   }
   return b;
}


void CEquationSolver::CholeskyDecomp(CArray2D<float>& a, vector<float>& p) {
   int i, j, k;
   double sum;
   int n = p.size();

   for (i=0; i<n; i++) {
      for (j=i; j<n; j++) {
         for (sum = a[i][j], k=i-1; k>=0; k--) {
            sum -= a[i][k] * a[j][k];
         }
         if (i == j) {
            if (sum <= 0.0) {
               printf("Cholesky decomposition failed.\n");
            }
            p[i] = (float) sqrt(sum);
         } else {
            a[j][i] = sum / p[i];
         }
      }
   }
}


vector<float> CEquationSolver::CholeskySolve(CArray2D<float>& a, vector<float>& p,
                                             vector<float>& b, vector<float>& x) {
   int i, k;
   double sum;
   int n=p.size();
      
   for (i=0; i<n; i++) {
      for (sum = b[i], k=i-1; k>=0; k--) {
         sum -= a[i][k] * x[k];
      }
      x[i] = sum / p[i];
   }
   for (i=n-1; i>=0; i--) {
      for (sum=x[i], k=i+1; k<n; k++) {
         sum -= a[k][i] * x[k];
      }
      x[i] = sum / p[i];
   }
   return x;
}

} // end namespace ipl
