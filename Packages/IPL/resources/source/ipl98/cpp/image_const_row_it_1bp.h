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

#ifndef _IPL98_IMAGECONSTROWIT1BP_H
#define _IPL98_IMAGECONSTROWIT1BP_H

#include "ipl98_types.h"
#include "../kernel_c/image/kernel_functions.h"

namespace ipl{ // use namespace if C++

/** Iterator class to access data from the class CImage2D, last updated 10/10/2001.
	This class is not complete, only a few operators are overloaded. But it can
	be used as a basic iterator where the iterator is incremented with the ++
	operator.
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CImageConstRowIterator1bp ipl98/cpp/image_const_row_it_1bp.h
	@see CImageRowIterator1bp
	@see CImage
	@version 0.20,  by edr@mip.sdu.dk
	@author René Dencker Eriksen */
class CImageConstRowIterator1bp
{
protected: // attributes
	/// Counter for current element in actual row
    unsigned int m_Curr;
	/// Pointer to start element in actual row
	UINT8* m_Begin;
	/// Counter for last element+1 in actual row
	unsigned int m_End;
public:
	/** Constructor
		@param pActualRow Absolute pointer to actual row.
		@param StartIndex Index to start iteration from in actual row, without origo and ROI.
		@param MaxIndex Max index + 1, where iteration should end, used to set the return value 
			for End(), without origo and ROI. */
	inline CImageConstRowIterator1bp(UINT8* pActualRow, UINT32 StartIndex, UINT32 MaxIndex);
	/// overloading = operator
	inline CImageConstRowIterator1bp& operator=(const CImageConstRowIterator1bp& It);
	/** Returns an iterator to the last element plus one in current row or column.
		@return Last element plus one. */
	inline CImageConstRowIterator1bp End() const;
	/** overloading ++ operator. Increments the pointer to data. */
	inline CImageConstRowIterator1bp& operator++() { m_Curr++; return *this; }
	/** overloading ++ operator (postfix). Increments the pointer to data. */
	inline CImageConstRowIterator1bp operator++(int) { CImageConstRowIterator1bp t=*this; m_Curr++; return t;}
	/** overloading the dereference operator, typically used when iterating. */
	inline UINT32 operator*(){return ( (*(m_Begin+(m_Curr>>3))) & (0x80>>(m_Curr%8)) )!=0;}
	/** overloading [] operator. */
	inline const UINT32 operator[](UINT32 i){return ( (*(m_Begin+((m_Curr+i)>>3))) & (0x80>>((m_Curr+i)%8)) )!=0;}
	/** overloading == operator.
		@return true, if iterator p and q points to same element in same column. */
	inline friend bool operator==(const CImageConstRowIterator1bp& p, const CImageConstRowIterator1bp& q);
	/** overloading != operator.
		@return true, if iterator p and q points to different elements. */
	inline friend bool operator!=(const CImageConstRowIterator1bp& p, const CImageConstRowIterator1bp& q);
	/** overloading < operator.
		@return true, if iterator p and q points to same column and p has row index < q's row index. */
	inline friend bool operator< (const CImageConstRowIterator1bp& p, const CImageConstRowIterator1bp& q);
};

inline CImageConstRowIterator1bp::CImageConstRowIterator1bp(UINT8* pActualRow, UINT32 StartIndex, UINT32 MaxIndex):
		m_End(MaxIndex), m_Curr(StartIndex%8), m_Begin(pActualRow+(StartIndex>>3))
{
}

inline CImageConstRowIterator1bp& CImageConstRowIterator1bp::operator=(const CImageConstRowIterator1bp& It)
{
	m_Curr  = It.m_Curr;
	m_Begin = It.m_Begin;
	m_End   = It.m_End;
	return *this;
}

inline CImageConstRowIterator1bp CImageConstRowIterator1bp::End() const
{
	CImageConstRowIterator1bp t = *this;
	t.m_Curr = m_End;
	return t;
}

inline bool operator==(const CImageConstRowIterator1bp& p, const CImageConstRowIterator1bp& q)
{
	return (p.m_Curr==q.m_Curr);
}

inline bool operator!=(const CImageConstRowIterator1bp& p, const CImageConstRowIterator1bp& q)
{
	return !(p==q);
}

inline bool operator<(const CImageConstRowIterator1bp& p, const CImageConstRowIterator1bp& q)
{
	return (p.m_Curr<q.m_Curr);
}

} // end namespace ipl

#endif //_IPL98_IMAGECONSTROWIT1BP_H
