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

#ifndef _IPL98_LINE3D_H
#define _IPL98_LINE3D_H

#include "../../../points/point3d.h"
#include "../vectors/vector3d.h"

namespace ipl{ // use namespace ipl

/** A class defining a 3 dimensional line by a 3D point and a
	direction vector, last updated 7/2/2001.
	The template type should be a floating point, i.e. type float or double.
	
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CLine3D ipl98/cpp/geometry/line3d.h
	@version 0.5,  by ivb@mip.sdu.dk and edr@mip.sdu.dk
	@author Ivar Balslev and René Dencker Eriksen */
template<class T>
class CLine3D
{
	private: // attributes
		/// Defines a point on line
		CPoint3D<T> m_P;
		/// defines the 3D direction of line
		CVector3D<T> m_Dir;
	public: // methods
		/// default constructor, line point defaults to (0,0,0) and direction to (1,0,0)
		CLine3D();
		/** Constructor defining the plane.
			@param P Point on line.
			@param Dir Direction of line, must not be a zero vector. */			
		CLine3D(const CPoint3D<T>& P, const CVector3D<T>& Dir);
		/// copy constructor
		CLine3D(const CLine3D<T>& Line3D);
		/** Overloading of assignment operator. All attributes are copied
			to the destination. */
		CLine3D<T>& operator=(const CLine3D<T>& Line3D);
		/** Returns the direction of the line.
			@return Direction of line. */
		inline const CVector3D<T>& GetDir() const;
		/** Returns the point used to define the line.
			@return Point used to define the line. */
		inline const CPoint3D<T>& GetPoint() const;
		/** Defines a line by given point P and direction Dir.
			@param P Point on line.
			@param Dir Direction of line.
			@return False, if Dir is a zero vector. In that case nothing is changed
				in this object. */
		bool Set(const CPoint3D<T>& P, const CVector3D<T>& Dir);
		/** Calculates the intersectino point for between line L1 and line L2.
			If they do not intersect the middle point for nearest intersection is 
			returned.
			@param PseudoIntersectionPoint Intersection point returned in this parameter.
			@param MinDistance The minimum distance between the two lines, if
				not 0, the returned intersection point is a pseudo intersection.
			@return False, if L1 and L2 are parallel.
			@version 0.1 */
		bool PseudoIntersect(const CLine3D<T>& L, CPoint3D<T> &PseudoIntersectionPoint, T& MinDistance);
};

template<class T>
inline const CVector3D<T>& CLine3D<T>::GetDir() const
{
	return m_Dir;
}

template<class T>
inline const CPoint3D<T>& CLine3D<T>::GetPoint() const
{
	return m_P;
}

#include "line3d.cpp"

} // end namespace ipl

#endif //_IPL98_LINE3D_H
