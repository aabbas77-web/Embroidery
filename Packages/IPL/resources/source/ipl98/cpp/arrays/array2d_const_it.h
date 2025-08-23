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

#ifndef _IPL98_ARRAY2DCONSTIT_H
#define _IPL98_ARRAY2DCONSTIT_H

#include "../ipl98_types.h"
#include<iostream>
#include<valarray>
#include<algorithm>

namespace ipl{ // use namespace if C++

/** Iterator class to access data from the class CArray2D, last updated 4/2/2001.
	This class is not complete, only a few operators are overloaded. But it can
	be used as a basic iterator where the iterator is incremented with the ++
	operator. See example in CArray2D class.
	This class is build	from the basic example in C++ Programming Language Third 
	Edition p. 672 by Bjarne Stroustrup. Some of the code has been moved inside the
	declaration of the class, since some compilers have problems inlining the code
	if it is not shown at that early point. 
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CArray2DConstIterator ipl98/cpp/arrays/array2d_const_it.h
	@see CArray2DIterator
	@see CArray2D
	@version 0.10,  by edr@mip.sdu.dk
	@author René Dencker Eriksen */
template<class T>
class CArray2DConstIterator 
{
protected: // attributes
	valarray<T>* m_pData;
	slice m_s;
	UINT32 m_Curr;    // index of current element
public:
	/// Constructor
    CArray2DConstIterator(valarray<T>* vv, slice ss): m_pData(vv), m_s(ss), m_Curr(0){}
	/// overloading = operator
	inline CArray2DConstIterator& operator=(const CArray2DConstIterator& It);
	/** Returns an iterator to the last element plus one in current row or column.
		@return Last element plus one. */
    inline CArray2DConstIterator End() const;
	/** overloading ++ operator. Increments the pointer to data. */
    inline CArray2DConstIterator& operator++() { m_Curr++; return *this; }
	/** overloading ++ operator. Increments the pointer to data. */
    CArray2DConstIterator operator++(int) { CArray2DConstIterator t = *this; m_Curr++; return t; }
	/** overloading the dereference operator, typically used when iterating. */
	inline const T& operator*(){return (*m_pData)[m_s.start()+m_Curr*m_s.stride()];}
    /** overloading [] operator. */
    inline const T& operator[](UINT32 i) const { return (*m_pData)[m_s.start()+i*m_s.stride()]; }
	/** overloading == operator.
		@return true, if iterator p and q points to same element in same column. */
    friend bool operator==(const CArray2DConstIterator& p, const CArray2DConstIterator& q);
	/** overloading != operator.
		@return true, if iterator p and q points to different elements. */
    friend bool operator!=(const CArray2DConstIterator& p, const CArray2DConstIterator& q);
	/** overloading < operator.
		@return true, if iterator p and q points to same column and p has row index < q's row index. */
    friend bool operator< (const CArray2DConstIterator& p, const CArray2DConstIterator& q);
};

template<class T>
inline CArray2DConstIterator<T>& CArray2DConstIterator<T>::operator=(const CArray2DConstIterator<T>& It)
{
	m_pData=It.m_pData;
	m_s=It.m_s;
	m_Curr=It.m_Curr;
	return *this;
}

template<class T>
inline CArray2DConstIterator<T> CArray2DConstIterator<T>::End() const
{
	CArray2DConstIterator t = *this;
	t.m_Curr = m_s.size(); // index of one plus last element
	return t;
}

template<class T>
bool operator==(const CArray2DConstIterator<T>& p, const CArray2DConstIterator<T>& q)
{
	return p.m_Curr==q.m_Curr
		&& p.m_s.stride()==q.m_s.stride()
		&& p.m_s.start()==q.m_s.start();
}

template<class T>
bool operator!=(const CArray2DConstIterator<T>& p, const CArray2DConstIterator<T>& q)
{
	return !(p==q);
}

template<class T>
bool operator<(const CArray2DConstIterator<T>& p, const CArray2DConstIterator<T>& q)
{
	return p.m_Curr<q.m_Curr
		&& p.m_s.stride()==q.m_s.stride()
		&& p.m_s.start()==q.m_s.start();
}

} // end namespace ipl

#endif //_IPL98_ARRAY2DCONSTIT_H
