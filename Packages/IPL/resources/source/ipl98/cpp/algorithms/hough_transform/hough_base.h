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

#ifndef _IPL98_HOUGHBASE_H
#define _IPL98_HOUGHBASE_H

#include "parameter2d.h"
#include "../../std_image.h"
#include "../../image.h"
#include <vector>

namespace ipl {

using std::vector;

/** CHoughBase class
    Base class for all hough transform classes. All hough transform classes are derived from it.
    This class provides types and methods utilized in the different transformation techniques.

	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CHoughBase ipl98/cpp/algorithms/hough_base.h
    @author Qinyin Zhou <qinyin@mip.sdu.dk>
    @version 0.99
*/
class CHoughBase {
public:
	/** The PARAMETERTYPE defines which type of parameterization method should be used to describe a 
       line shape. Used by SHT, RHT, ProbHT, and ProbRHT. Normally set to NORMAL_PARAM.
       Slope intercept parametrization (y=ax+b, with singularity problem) or 
       normal parametrization (r=x cos(th)+y sin(th)) can be selected. */
	typedef enum {
		SLOPE_PARAM,         // slope intercept parametrization
		NORMAL_PARAM         // normal parametrization
	} PARAMETERTYPE;
	
	/** The ORIGINTYPE defines the location and orientation of the coordinate system of the source image.
       The best case is CENTER_UP where the origo is located at the center of the image with y-axis pointing upwards. 
       This feature compilicates the algorithm with axis conversion but makes the algorithm 
       mathematically more easy to understand. */
	typedef enum { 
		LEFT_UPPER, 
		CENTER_UP,
		CENTER_DOWN
	} ORIGINTYPE;
	
	/** The PEAKDETECTIONTYPE defines with strategy to use when finding a peak in a parameter space. 
       Need to choose when performing SHT or ProbSHT.
       The BUTTERFLY method is the most approved method to take. */
	typedef enum {
		BUTTERFLY,
		DIFFUSION,
		ITERATION,
		LOCALMAXIMA
	} PEAKDETECTIONTYPE;
	
	/** The PARAMETERSPACETYPE defines which of the two parameter space implementation should be utilized 
       when performing RHT and ProbRHT. QUANTIZATION_SPACE uses a full nxn space to collect the votes.
       SPARCE_SPACE used a 1D-array-list structure to store un-zero cells and saves space. */
	typedef enum {
		QUANTIZATION_SPACE,
		SPARSE_SPACE
	} PARAMETERSPACETYPE;
	
	/** Scale a Hough space converted image to a grayscale image. 
       The pixels in the image are scaled by pi/max(pi) ratio.
		 @param Source Input and output image.
	*/
	static void ScaleHoughImage(CStdImage& Source);
	
	/** Draws a line described by normal parameterization in an image.
		@param img Image object for addition of a new shape.
		@parameter Parameter of the line object.
	*/
	static void DrawLine(CImage& img, const CParameter2D<float>& parameter);
	
	/** Computer intersection points of a line with the perimeter (normal) of the image.
		@param img Image object.
		@param p Parameter of the line.
	*/
	static vector<int> ComputeIntersectionPoints(const CImage& img, const CParameter2D<float>& p);
	
};

} // end namespace ipl

#endif _IPL98_HOUGHBASE_H
