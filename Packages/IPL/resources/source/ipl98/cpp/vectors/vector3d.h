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

#ifndef _IPL98_VECTOR3D_H
#define _IPL98_VECTOR3D_H

#include "../../../points/point3d.h"
#include <iostream>

namespace ipl{ // use namespace if C++

/** CVector3D template class with 3-dimensional vectors,
	last updated 12/7/2001.
	This class is inherited from the CPoint3D class, this
	version adds some new vector methods such as calculations
	of angle, projections, dot product etc.
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CVector3D ipl98/cpp/vectors/vector3d.h
	@version 0.3,  by edr@mip.sdu.dk
	@author René Dencker Eriksen
	@see CPoint3D */
template<class T>
class CVector3D : public CPoint3D<T>
{
	public: // attributes
	private: // attributes
	public: // methods
		 /// default constructor, init to zero
		CVector3D();
		/// constr. with init. of point
		CVector3D(T x,T y,T z);
		/// copy constructor with template conversion
		template<class POLY> inline CVector3D(const CVector3D<POLY>& V3D){m_x=V3D.GetX();m_y=V3D.GetY();m_z=V3D.GetZ();}
		/// copy constructor of CPoint3D with template conversion
		template<class POLY> inline CVector3D(const CPoint3D<POLY>& P3D){m_x=P3D.GetX();m_y=P3D.GetY();m_z=P3D.GetZ();}

		/// cast to POLY in mixed expressions
		template<class POLY> operator CVector3D<POLY>(){return CVector3D<POLY>(m_x,m_y,m_z);}

		/**@name overloading assignment operators */
		//@{
		/// overloading = operator with template conversion
		template<class POLY> inline CVector3D<T>& operator=(const CVector3D<POLY>& V3D){m_x=V3D.GetX();m_y=V3D.GetY();m_z=V3D.GetZ();return *this;};
		/// overloading += operator with template conversion
		template<class POLY> inline CVector3D<T>& operator+=(const CVector3D<POLY>& V3D){m_x+=V3D.GetX();m_y+=V3D.GetY();m_z+=V3D.GetZ();return *this;};
		/// overloading -= operator with template conversion
		template<class POLY> inline CVector3D<T>& operator-=(const CVector3D<POLY>& V3D){m_x-=V3D.GetX();m_y-=V3D.GetY();m_z-=V3D.GetZ();return *this;};
		/** overloading *= operator with template conversion
			 @param Factor Multiply each dimension with this value */
		template<class POLY> inline CVector3D<T>& operator*=(const POLY& Factor){m_x*=Factor;m_y*=Factor;m_z*=Factor;return *this;}
		/** overloading /= operator with template conversion
			 @param Factor Divide each dimension with this value */
		template<class POLY> inline CVector3D<T>& operator/=(const POLY& Factor){m_x/=Factor;m_y/=Factor;m_z/=Factor;return *this;}
		//@}
		/**@name overloading comparison operators */
		//@{
		/// overloading == operator with template conversion
		template<class POLY> inline bool operator==(const CVector3D<POLY>& V3D) const{return ((m_x==V3D.GetX()) && (m_y==V3D.GetY()) && (m_z==V3D.GetZ()));}
		/// overloading != operator with template conversion
		template<class POLY> inline bool operator!=(const CVector3D<T>& V3D) const{return ((m_x!=V3D.GetX()) || (m_y!=V3D.GetY()) || (m_z!=V3D.GetZ()));}
		//@}
		/**@name overloading arithmetic operators */
		//@{
		/// overloading + operator with template conversion
		template<class POLY> inline CVector3D<T> operator+(const CVector3D<POLY>& V3D) const{return CVector3D<T>(m_x+V3D.GetX(),m_y+V3D.GetY(),m_z+V3D.GetZ());}
		/// overloading - operator with template conversion
		template<class POLY> inline CVector3D<T> operator-(const CVector3D<POLY>& V3D) const{return CVector3D<T>(m_x-V3D.GetX(),m_y-V3D.GetY(),m_z-V3D.GetZ());}
		/** overloading * operator used for dot product. If you want the dot product
			of two vectors of different types with an implicit type cast, use the method
			GetDot. Trying to implement this dot product with template conversion gives
			an ambiguity with the * operator when used for scaling the vector.
			@param Vector Calculate dot product with this parameter.
			@see GetDot */
		inline T operator*(const CVector3D<T>& Vector) const {return (m_x*Vector.GetX()+m_y*Vector.GetY()+m_z*Vector.GetZ());}
		/** overloading * operator with template conversion
			 @param Factor Multiply each dimension with this value */
		template<class POLY> inline CVector3D<T> operator*(const POLY& Factor) const {return CVector3D<T>(m_x*Factor,m_y*Factor,m_z*Factor);}
		/** overloading / operator with template conversion
			 @param Factor Divide each dimension with this value */
		template<class POLY> inline CVector3D<T> operator/(const POLY& Factor) const {return CVector3D<T>(m_x/Factor,m_y/Factor,m_z/Factor);}
		//@}
		
		/** a friend method overloading the * operator, makes it possible to write f*V3D,
			where f is a factor of type T and V3D is of type CVector3D<V>. For some reason
			this cannot be converted as other operators, i.e. f and V3D must contain same types. */
		friend CVector3D<T> operator*(const T& Factor,const CVector3D<T>& V3D);
		
		
		/** Returns the dot product between this vector and the parameter Vector.
			@param Vector Calculate dot product with this parameter.
			@return Dot product between the two vectors. */
		template<class POLY> inline T GetDot(const POLY& Vector) const {return (m_x*Vector.GetX()+m_y*Vector.GetY()+m_z*Vector.GetZ());}
		/** Returns modulus, that is sqrt(x*x+y*y+z*z). Calls the base class GetDist().
			@return Modulus. */
		inline double GetModulus() const;
		/** Returns the angle in radians in the X-Y plane compared to the vector (1;0). Range is [0,PI].
			Another version of this method with angle between supplied vector and this
			vector is available.
			@return Angle in radians, range [0,PI] */
		inline T GetXYAngle() const;
		/** Returns the angle in radians between this vector and the X-Y plane. Range is [0,PI].
			@return Angle in radians, range [0,PI] */
		inline T GetZAngle() const;
		/** Returns the angle in radians between this vector and the supplied vector.
			Range is [0,PI]. Other methods are available for angle in X-Y plane and angle
			between vector and .X-Y plane.
			@return Angle in radians, range [0,PI]
			@see GetXYAngle
			@see GetZAngle */
		template<class POLY> inline double GetAngle(const CVector3D<POLY>& Vec) const {T p=GetDot(Vec)/(GetModulus()*Vec.GetModulus());return atan2(sqrt(1-p*p),p);}
		/** Returns the projection of this vector on the supplied vector.
			@param Vec Vector to project this vector onto.
			@return Projected vector. */
		template<class POLY> inline CVector3D<T> GetProjection(const CVector3D<POLY>& Vec) const {return Vec*GetDot(Vec)/(Vec.GetX()*Vec.GetX()+Vec.GetY()*Vec.GetY()+Vec.GetZ()*Vec.GetZ());}
		/** Returns the cross product of this vector and the supplied vector.
			@param Vec Vector to calculate cross product with.
			@return Cross product of this vector and supplied vector. */
		template<class POLY> inline CVector3D<T> GetCross(const CVector3D<POLY>& Vec) const {return CVector3D<T>(m_y*Vec.m_z-m_z*Vec.m_y, m_z*Vec.m_x-m_x*Vec.m_z, m_x*Vec.m_y-m_y*Vec.m_x);}
		/** Returns true, if vector is a zero-vector.
			@return True, if vector is a zero-vector. */
		inline bool IsZero() const;
		/** Returns true, if vectors are parallel with each other.
			@param Vec Vector to compare with.
			@return True, if vectors are parallel. */
		template<class POLY> inline bool IsParallel(const CVector3D<POLY>& Vec) const{return GetDeterminant(Vec)==0;}
		/** Returns true, if vectors are orthogonal to each other.
			@param Vec Vector to compare with.
			@return True, if vectors are orthogonal to each other. */
		template<class POLY> inline bool IsOrthogonal(const CVector3D<POLY>& Vec) const{return GetDot(Vec)==0;}
		/** Normalizes the vector, i.e. length is one after this operation.
			If this vector is a null vector, nothing is done.
			@return False, if this vector is a null vector. */
		inline bool Normalize(){T L=GetModulus();if (L!=0){m_x/=L;m_y/=L;m_z/=L;return true;}else{return false;}}
};

/////////////////////////////////////////////////
//// Inline methods
/////////////////////////////////////////////////

template <class T>
inline T CVector3D<T>::GetXYAngle() const
{
	return atan2(m_y, m_x);
}

template <class T>
inline T CVector3D<T>::GetZAngle() const
{
	 return atan2(m_z,sqrt(m_x*m_x + m_y*m_y));
}

template <class T>
inline double CVector3D<T>::GetModulus() const
{
	return sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
}

template <class T>
inline bool CVector3D<T>::IsZero() const
{
	return ((m_x==T(0)) && (m_y==T(0)) && (m_z==T(0)));
}

template <class T>
CVector3D<T> operator*(const T& Factor,const CVector3D<T>& V3D)
{
	return CVector3D<T>(V3D.GetX()*Factor,V3D.GetY()*Factor,V3D.GetZ()*Factor);
}

#include "vector3d.cpp"

} // end namespace ipl

#endif //_IPL98_VECTOR3D_H


