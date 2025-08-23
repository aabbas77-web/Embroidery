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

#ifndef _IPL98_LINE2D_H
#define _IPL98_LINE2D_H

#include "../../../points/point2d.h"
#include "../vectors/vector2d.h"

namespace ipl{ // use namespace ipl

/** A class defining a 2 dimensional line by a 2D point and a 
	direction vector, last updated 7/2/2001.
	The template type should be a floating point, i.e. type float or double.
	To iterate a line in an image use CGraphics::Line() instead, to draw a line
	in an image see CStdImage::DrawLine().

	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CLine2D ipl98/cpp/geometry/line2d.h
	@version 0.5,  by ivb@mip.sdu.dk and edr@mip.sdu.dk
	@author Ivar Balslev and René Dencker Eriksen */
template<class T>
class CLine2D
{
	public: // attributes
		/// Defines a point on line
		CPoint2D<T> m_P;
		/// defines the 2D direction of line
		CVector2D<T> m_Dir;
	public: // methods
		/// Default constructor, line point defaults to (0,0) and direction to (1,0)
		CLine2D();
		/** Constructor defining a line by given point P and direction Dir.
			Note: User must ensure the values are valid, i.e. Dir is not a zero vector.
			@param P Point on line.
			@param Dir Direction of line. */
		CLine2D(CPoint2D<T> P, CVector2D<T> Dir);
		/// copy constructor
		CLine2D(const CLine2D<T>& Line2D);
		/** Overloading of assignment operator. All attributes are copied
			to the destination. */
		CLine2D<T>& operator=(const CLine2D<T>& Line2D);
		/** Returns the direction of the line.
			@return Direction of line. */
		inline const CVector2D<T>& GetDir() const;
		/** Returns the point used to define the line.
			@return Point used to define the line. */
		inline const CPoint2D<T>& GetPoint() const;
		/** Calculates the intersection between line L1 and line L2, if the
			lines does not intersect, the middle point on the line defined
			by the two closest points on each line is returned in Q.
			@return False, if the lines does not intersect */
		bool Intersect(const CLine2D<T>& L, CPoint2D<T>& Q);
		/** Defines a line by given point P and direction Dir.
			@param P Point on line.
			@param Dir Direction of line.
			@return False, if Dir is a zero vector. In that case nothing is changed
				in this object. */
		bool Set(const CPoint2D<T>& P, const CVector2D<T>& Dir);
};

template<class T>
inline const CVector2D<T>& CLine2D<T>::GetDir() const
{
	return m_Dir;
}

template<class T>
inline const CPoint2D<T>& CLine2D<T>::GetPoint() const
{
	return m_P;
}

#include "line2d.cpp"

} // end namespace ipl

#endif //_IPL98_LINE2D_H
