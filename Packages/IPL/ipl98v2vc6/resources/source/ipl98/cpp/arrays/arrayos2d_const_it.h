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

#ifndef _IPL98_ARRAYOS2DCONSTIT_H
#define _IPL98_ARRAYOS2DCONSTIT_H

#include<iostream>
#include<valarray>
#include<algorithm>
#include "array2d_const_it.h"

namespace ipl{ // use namespace if C++

/** Iterator class to access data from the class CArrayOS2D, last updated 10/10/2001.
	This class is not complete, only a few operators are overloaded. But it can
	be used as a basic iterator where the iterator is incremented with the ++
	operator. See example in CArrayOS2D class.
	This class is build	from the basic example in C++ Programming Language Third 
	Edition p. 672 by Bjarne Stroustrup. Some of the code has been moved inside the
	declaration of the class, since some compilers have problems inlining the code
	if it is not shown at that early point.
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CArrayOS2DConstIterator ipl98/cpp/arrays/arrayos2d_const_it.h
	@see CArrayOS2DIterator
	@see CArrayOS2D
	@version 0.20,  by edr@mip.sdu.dk
	@author René Dencker Eriksen */
template<class T>
class CArrayOS2DConstIterator : public CArray2DConstIterator<T>
{
private: // attributes
	/** The granularity of the array, see attribute m_SubIndexing in class CArrayOS2D
		for more info.
		@see CArrayOS2D */
	unsigned int m_SubIndexing;
	/** Reference to origo in the array, see m_Origo in class CArrayOS2D
		for more info.
		@see CArrayOS2D */
	const CPoint2D<double>* m_Origo;
public:
	/// Constructor
	CArrayOS2DConstIterator(valarray<T>* vv, slice ss, unsigned int SubIndexing, const CPoint2D<double>* Origo) : 
									CArray2DConstIterator<T>(vv,ss), m_SubIndexing(SubIndexing), m_Origo(Origo){}
	/// overloading = operator
	inline CArrayOS2DConstIterator& operator=(const CArrayOS2DConstIterator& It);
	/** Returns an iterator to the last element plus one in current row or column.
	@return Last element plus one. */
	inline CArrayOS2DConstIterator End() const;
	/** overloading ++ operator. Increments the pointer to data. */
	inline CArrayOS2DConstIterator& operator++() { m_Curr++; return *this; }
	/** overloading ++ operator. Increments the pointer to data. */
	CArrayOS2DConstIterator operator++(int) { CArrayOS2DConstIterator t = *this; m_Curr++; return t; }
	/** overloading [] operator. */
	inline const T& operator[](double i) const { return (*m_pData)[m_s.start()+(i+m_Origo->GetY())*m_SubIndexing*m_s.stride()]; }
};

template<class T>
inline CArrayOS2DConstIterator<T>& CArrayOS2DConstIterator<T>::operator=(const CArrayOS2DConstIterator<T>& It)
{
	CArray2DConstIterator<T>::operator=(It);
	m_SubIndexing=It.m_SubIndexing;
	m_Origo=It.m_Origo;
	return *this;
}

template<class T>
inline CArrayOS2DConstIterator<T> CArrayOS2DConstIterator<T>::End() const
{
	CArrayOS2DConstIterator<T> t = *this;
	t.m_Curr = m_s.size();
	return t;
}

} // end namespace ipl

#endif //_IPL98_ARRAYOS2DCONSTIT_H
