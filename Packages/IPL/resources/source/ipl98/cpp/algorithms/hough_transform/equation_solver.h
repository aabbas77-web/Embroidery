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

#ifndef _IPL98_EQUATIONSOLVER_H
#define _IPL98_EQUATIONSOLVER_H

#include "../../arrays/array2d.h"
#include <vector>

namespace ipl{

using std::vector;

/** This class contains methods for solveing systems of linear equation.
	Used by the Hough classes.

	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CEquationSolver ipl98/cpp/algorithms/equation_solver.h
    @author Qinyin Zhou <qinyin@mip.sdu.dk>
    @version 0.30
*/
class CEquationSolver {
public:
   /** Default constructor.
   */
	CEquationSolver();

   /* Destructor
   */
	virtual ~CEquationSolver();

   /** Solve a system of linear equations Ax=b with LU decomposition technique.
       @param A Left hand side matrix.
       @param b Right hand side vector.
       @return The solution vector x.
   */
   vector<float> LinearSolve(CArray2D<float>& A, vector<float>& b);

   /** Solve a system of linear equations Ax=b with Cholesky decomposition technique.
       @param A Left hand side matrix.
       @param b Right hand side vector.
       @return The solution vector x.
   */
   vector<float> CholeskyLinearSolve(CArray2D<float>& A, vector<float>& b);

    /** Method calculating LU decomposition of a nxn matrix a.
        The method takes a matrix and stores the LU representation in the original matrix.
        The pivoting index is stored in the index vector.
        @param a Matrix a to be calculated. The result will be stored in a.
        @param index The pivot element index vector.
    */
   void LUDecomp(CArray2D<float>& A, vector<unsigned int>& index);

   /** Solve a system of linear equations with a LU decomposited matrix.
       @param A LU decomposited matrix.
       @param index Pivot vector of decomposition. Changed from int to unsigned int by edr
       @param b RHS vector.
       @return The solution, return x.
   */
   vector<float> LUSolve(CArray2D<float>& A, vector<unsigned int>& index, vector<float>& b);

   /** Performs Cholesky decomposition.
       @param a Matrix for decomposition.
       @param p Vector to store diagonal elements.
   */
   void CholeskyDecomp(CArray2D<float>& a, vector<float>& p);

   /** Solve a Cholesky decomposited matrix.
       @param a Matrix.
       @param p Diagonal vector.
       @param b Right hand side vector.
       @param x Result vector.
       @return The solution, return x.
   */
   vector<float> CholeskySolve(CArray2D<float>& a, vector<float>& p, vector<float>& b, vector<float>& x);

};

} // end namespace ipl

#endif _IPL98_EQUATIONSOLVER_H
