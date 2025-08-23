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

#include "hough_base.h"
#include "../../ipl98_general_functions.h"

namespace ipl {

void CHoughBase::ScaleHoughImage(CStdImage& Source)
{
	int value, x, y, maxColorValue = 0;
	
	// color scaling to grayscale
	for (y=0; y<Source.GetHeight(); y++)
	{
		for (x=0; x<Source.GetWidth(); x++)
		{
			value = Source.GetPixelFast(x,y);
			if (value > maxColorValue) maxColorValue = value;         
		}
	}
	
	for (y=0; y<Source.GetHeight(); y++)
	{
		for (x=0; x<Source.GetWidth(); x++)
		{
			value = (int) (1.0*Source.GetPixelFast(x,y)/maxColorValue*255);
			Source.SetPixelFast(x,y,255-value);
		}
	}
}


void CHoughBase::DrawLine(CImage& img, const CParameter2D<float>& parameter)
{
	vector<int> points = ComputeIntersectionPoints(img, parameter);
	int dist = (int) sqrt(pow(points[0]-points[2],2.0)+pow(points[1]-points[3],2.0));
	
	points[0] += img.GetWidth()/2;
	points[1] = img.GetHeight()/2-points[1];
	points[2] += img.GetWidth()/2;
	points[3] = img.GetHeight()/2-points[3];
	
	CPoint2D<int> start((int) points[0], (int) points[1]);
	CPoint2D<int> end((int) points[2], (int) points[3]);
	// cout << start << " " << end << endl;
	img.DrawLine(start, end, 0);
}


vector<int> CHoughBase::ComputeIntersectionPoints(const CImage& img, const CParameter2D<float>& p)
{
	
	CPoint2D<int> origo((int) img.GetWidth()/2, (int) img.GetHeight()/2);
	CParameter2D<float>  left_line((float) 0.0f, -origo.GetX());
	CParameter2D<float> right_line((float) 0.0f,  origo.GetX());
	CParameter2D<float> upper_line((float) PI/2, -origo.GetY());
	CParameter2D<float> lower_line((float) PI/2,  origo.GetY());
	
	CPoint2D<float> left_intersection =  p.NormalLineIntersection(left_line);
	CPoint2D<float> right_intersection = p.NormalLineIntersection(right_line);
	CPoint2D<float> lower_intersection = p.NormalLineIntersection(lower_line);
	CPoint2D<float> upper_intersection = p.NormalLineIntersection(upper_line);
	CPoint2D<float> parallel(0.0f,0.0f);
	
	
	CPoint2D<float> p1, p2;
	
	int left = 2;
	if(left_intersection.GetY()>=-origo.GetY() && left_intersection.GetY()<=origo.GetY() && 
		left_intersection != parallel && left>0)
	{
		p1 = left_intersection;
		left--;
		// cout << "found LEFT" << endl;
	}
	if(right_intersection.GetY()>=-origo.GetY() && right_intersection.GetY()<=origo.GetY() && 
		right_intersection != parallel && left>0)
	{
		if (left == 2) {
			p1 = right_intersection;
		} else if (left == 1) {
			p2 = right_intersection;
		}
		left--;
		// cout << "found RIGHT" << endl;
	}
	if(lower_intersection.GetX()>=-origo.GetX() && lower_intersection.GetX()<=origo.GetX() && 
		lower_intersection != parallel && left>0)
	{
		if (left == 2) {
			p1 = lower_intersection;
		} else if (left == 1) {
			p2 = lower_intersection;
		}
		left--;
		// cout << "found LOWER" << endl;
	}
	if(upper_intersection.GetX()>=-origo.GetX() && upper_intersection.GetX()<=origo.GetX() && 
		upper_intersection != parallel && left>0)
	{
		p2 = upper_intersection;
		left--;
		// cout << "found UPPER" << endl;
	}
	
	vector<int> points;
	points.push_back((int) p1.GetX());
	points.push_back((int) p1.GetY());
	points.push_back((int) p2.GetX());
	points.push_back((int) p2.GetY());
	return points;
}

} // end namespace ipl
