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

#ifndef _IPL98_IMAGECONSTROWIT24BP_H
#define _IPL98_IMAGECONSTROWIT24BP_H

#include "ipl98_types.h"
#include "../kernel_c/image/kernel_functions.h"

namespace ipl{ // use namespace if C++

/** Iterator class to access data from the class CImage2D, last updated 10/10/2001.
	This class is not complete, only a few operators are overloaded. But it can
	be used as a basic iterator where the iterator is incremented with the ++
	operator.
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CImageConstRowIterator24bp ipl98/cpp/image_const_row_it_24bp.h
	@see CImageRowIterator24bp
	@see CImage
	@version 0.20,  by edr@mip.sdu.dk
	@author René Dencker Eriksen */
class CImageConstRowIterator24bp
{
protected: // attributes
	/// Pointer to current element in actual row
    UINT8* m_pCurr;
	/// Pointer to last element+1 in actual row
	UINT8* m_pEnd;
public:
	/** Constructor
		@param pActualRow Absolute pointer to actual row.
		@param StartIndex Index to start iteration from in actual row, without origo and ROI.
		@param MaxIndex Max index + 1, where iteration should end, used to set the return value 
			for End(), without origo and ROI. */
	inline CImageConstRowIterator24bp(UINT8* pActualRow, UINT32 StartIndex, UINT32 MaxIndex);
	/// overloading = operator
	inline CImageConstRowIterator24bp& operator=(const CImageConstRowIterator24bp& It);
	/** Returns an iterator to the last element plus one in current row or column.
		@return Last element plus one. */
	inline CImageConstRowIterator24bp End() const;
	/** overloading ++ operator. Increments the pointer to data. */
	inline CImageConstRowIterator24bp& operator++() { m_pCurr+=3; return *this; }
	/** overloading ++ operator (postfix). Increments the pointer to data. */
	inline CImageConstRowIterator24bp operator++(int) { CImageConstRowIterator24bp t=*this; m_pCurr+=3; return t;}
	/** overloading the dereference operator, typically used when iterating. */
	inline UINT32 operator*(){return ((*((UINT32*)m_pCurr)) & 0xffffff);}
	/** overloading [] operator. */
	inline const UINT32 operator[](UINT32 i) {return (*(m_pCurr+i*3) & 0xffffff);}
	/** overloading == operator.
		@return true, if iterator p and q points to same element in same column. */
	inline friend bool operator==(const CImageConstRowIterator24bp& p, const CImageConstRowIterator24bp& q);
	/** overloading != operator.
		@return true, if iterator p and q points to different elements. */
	inline friend bool operator!=(const CImageConstRowIterator24bp& p, const CImageConstRowIterator24bp& q);
	/** overloading < operator.
		@return true, if iterator p and q points to same column and p has row index < q's row index. */
	inline friend bool operator< (const CImageConstRowIterator24bp& p, const CImageConstRowIterator24bp& q);
};

inline CImageConstRowIterator24bp::CImageConstRowIterator24bp(UINT8* pActualRow, UINT32 StartIndex, UINT32 MaxIndex):
		m_pEnd(pActualRow + MaxIndex*3), m_pCurr(pActualRow + StartIndex*3)
{
}


inline CImageConstRowIterator24bp& CImageConstRowIterator24bp::operator=(const CImageConstRowIterator24bp& It)
{
	m_pCurr = It.m_pCurr;
	m_pEnd  = It.m_pEnd;
	return *this;
}

inline CImageConstRowIterator24bp CImageConstRowIterator24bp::End() const
{
	CImageConstRowIterator24bp t = *this;
	t.m_pCurr = m_pEnd;
	return t;
}

inline bool operator==(const CImageConstRowIterator24bp& p, const CImageConstRowIterator24bp& q)
{
	return (p.m_pCurr==q.m_pCurr);
}

inline bool operator!=(const CImageConstRowIterator24bp& p, const CImageConstRowIterator24bp& q)
{
	return !(p==q);
}

inline bool operator<(const CImageConstRowIterator24bp& p, const CImageConstRowIterator24bp& q)
{
	return (p.m_pCurr<q.m_pCurr);
}

} // end namespace ipl

#endif //_IPL98_IMAGECONSTROWIT24BP_H
