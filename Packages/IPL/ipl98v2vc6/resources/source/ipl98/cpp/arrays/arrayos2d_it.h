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

#ifndef _IPL98_ARRAYOS2DIT_H
#define _IPL98_ARRAYOS2DIT_H

#include<iostream>
#include<valarray>
#include<algorithm>
#include "array2d_it.h"

namespace ipl{ // use namespace if C++

/** Iterator class to access data from the class CArrayOS2D, last updated 4/2/2001.
	This class is not complete, only a few operators are overloaded. But it can
	be used as a basic iterator where the iterator is incremented with the ++
	operator. See example in CArrayOS2D class.
	This class is build	from the basic example in C++ Programming Language Third 
	Edition p. 672 by Bjarne Stroustrup. Some of the code has been moved inside the
	declaration of the class, since some compilers have problems inlining the code
	if it is not shown at that early point. 
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CArrayOS2DIterator ipl98/cpp/arrays/arrayos2d_it.h
	@see CArrayOS2DConstIterator
	@see CArrayOS2D
	@version 0.10,  by edr@mip.sdu.dk
	@author René Dencker Eriksen */
template<class T>
class CArrayOS2DIterator : public CArray2DIterator<T>
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
	CArrayOS2DIterator(valarray<T>* vv, slice ss, unsigned int SubIndexing, const CPoint2D<double>* Origo) : 
									CArray2DIterator<T>(vv,ss), m_SubIndexing(SubIndexing), m_Origo(Origo){}
	/// overloading = operator
	inline CArrayOS2DIterator& operator=(const CArrayOS2DIterator& It);
	/** Returns an iterator to the last element plus one in current row or column.
	@return Last element plus one. */
	inline CArrayOS2DIterator End() const;
	/** overloading ++ operator. Increments the pointer to data. */
	inline CArrayOS2DIterator& operator++() { m_Curr++; return *this; }
	/** overloading ++ operator. Increments the pointer to data. */
	inline CArrayOS2DIterator operator++(int) { CArrayOS2DIterator<T> t = *this; m_Curr++; return t; }
	/** overloading the dereference operator, typically used when iterating. */
	inline T& operator*(){return (*m_pData)[m_s.start()+m_Curr*m_s.stride()];}
	/** overloading [] operator. */
	inline T& operator[](double i) {return (*m_pData)[m_s.start()+(i+m_Origo->GetY())*m_SubIndexing*m_s.stride()];}
};

template<class T>
inline CArrayOS2DIterator<T> CArrayOS2DIterator<T>::End() const
{
	CArrayOS2DIterator<T> t = *this;
	t.m_Curr = m_s.size();
	return t;
}

template<class T>
inline CArrayOS2DIterator<T>& CArrayOS2DIterator<T>::operator=(const CArrayOS2DIterator<T>& It)
{
	CArray2DIterator<T>::operator=(It);
	m_SubIndexing=It.m_SubIndexing;
	m_Origo=It.m_Origo;
	return *this;
}

} // end namespace ipl

#endif //_IPL98_ARRAYOS2DIT_H
