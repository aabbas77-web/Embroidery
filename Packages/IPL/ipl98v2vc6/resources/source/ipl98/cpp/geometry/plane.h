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

#ifndef _IPL98_PLANE_H
#define _IPL98_PLANE_H

#include "../../../points/point3d.h"
#include "../vectors/vector3d.h"
#include "line3d.h"

namespace ipl{ // use namespace ipl

/** Definines a plane by two vectors and a point. Contains several
	methods for intersection with lines and planes. The template type
	should be a floating point, i.e. type float or double.

	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CPlane ipl98/cpp/geometry/plane.h
	@version 0.5,  by ivb@mip.sdu.dk and edr@mip.sdu.dk
	@author Ivar Balslev and René Dencker Eriksen */
template<class T>
class CPlane
{
	private: // attributes
		/// Defines a point in plane
		CPoint3D<T> m_P;
		/// first direction vector defining one dimension
		CVector3D<T> m_DirA;
		/// second direction vector defining second dimension
		CVector3D<T> m_DirB;
	public: // methods
		/** Default constructor, plane point defaults to (0,0,0), the two directions
			to (1,0,0) and (0,1,0) */
		CPlane();
		/** Constructor defining the plane.
			@param P Point on plane.
			@param DirA Defines first direction dimension of plane.
			@param DirB Defines second direction dimension. */
		CPlane(const CPoint3D<T>& P, const CVector3D<T>& DirA, const CVector3D<T>& DirB);
		/// Copy constructor
		CPlane(const CPlane<T>& Plane);
		/** Overloading of assignment operator. All attributes are copied
			to the destination. */
		CPlane<T>& operator=(const CPlane<T>& Plane);

		/** Returns the first direction defining the plane.
			@return Direction defining first dimension of this plane. */
		inline const CVector3D<T>& GetDirA() const;
		/** Returns the second direction defining the plane.
			@return Direction defining second dimension of this plane. */
		inline const CVector3D<T>& GetDirB() const;
		/** Returns the point used to define the plane.
			@return Point used to define the plane. */
		inline const CPoint3D<T>& GetPoint() const;
		/** Returns a normal to the plane by calculating the cross product
			of the two directions defining the orientation of the plane.
			@return Normal to plane found as crossproduct 'm_DirA' x 'm_DirB'. */
		inline CVector3D<T> GetPlaneNormal() const;
		/** Calculates the line for intersection between this plane and plane P.
			@param P Plane to calculate intersection with.
			@param L Intersection line returned in this parameter.
			@return False, if the planes do not intersect, i.e. they are parallel */
		bool Intersect(const CPlane<T>& P, CLine3D<T> &L) const;
		
		/** Calculates the point for intersection between this plane and line L.
			@param L Line to calculate intersection with.
			@param Q Intersection point returned in this parameter.
			@return False, if the plane and line do not intersect, i.e. they are parallel */
		bool Intersect(const CLine3D<T>& L, CPoint3D<T>& Q) const;
};

template<class T>
inline const CVector3D<T>& CPlane<T>::GetDirA() const
{
	return m_DirA;
}

template<class T>
inline const CVector3D<T>& CPlane<T>::GetDirB() const
{
	return m_DirB;
}

template<class T>
inline const CPoint3D<T>& CPlane<T>::GetPoint() const
{
	return m_P;
}

template<class T>
inline CVector3D<T> CPlane<T>::GetPlaneNormal() const
{
	return m_DirA.GetCross(m_DirB);
}

#include "plane.cpp"

} // end namespace ipl

#endif //_IPL98_PLANE_H
