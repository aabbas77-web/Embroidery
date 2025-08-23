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

#ifndef _IPL98_IMAGECOLUMNIT1BP_H
#define _IPL98_IMAGECOLUMNIT1BP_H

#include "ipl98_types.h"
#include "../kernel_c/image/kernel_functions.h"

namespace ipl{ // use namespace if C++

/** Iterator class to access data from the class CImage2D, last updated 10/10/2001.
	This class is not complete, only a few operators are overloaded. But it can
	be used as a basic iterator where the iterator is incremented with the ++
	operator.
	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CImageColumnIterator1bp ipl98/cpp/image_column_it_1bp.h
	@see CImageRowIterator1bp
	@see CImage
	@version 0.20,  by edr@mip.sdu.dk
	@author René Dencker Eriksen */
class CImageColumnIterator1bp
{
	/** Since a pixel for 1 b/p images is not a generic type nor a class, this intermediate
		type is needed in order to give the correct iterator interface to the programmer.
		Effort has been made to make it possible for compilers to optimize the code, at present
		it has been tested with the Visual C++ 6.0 compiler, and efficiency is indeed preserved. */
	class CIntermediateType
	{
		/// Pointer to the CImageColumnIterator1bp::m_pCurrByte member, set by constructor
		UINT8** m_ppCurrByte;
		/// Pointer to the CImageColumnIterator1bp::m_PixelIndexInByte member, set by constructor
		int* m_pPixelIndexInByte;
		public:
		/// Constructor
		inline CIntermediateType(int* pCurr, UINT8** ppBegin):m_pPixelIndexInByte(pCurr),m_ppCurrByte(ppBegin){}
		/// overloading = operator
		inline CIntermediateType& operator=(const CIntermediateType& Obj)
		{
			*m_ppCurrByte=*Obj.m_ppCurrByte;*m_pPixelIndexInByte=*Obj.m_pPixelIndexInByte;return *this;
		}
		/** overloading = operator with UINT32 as r-value. This is necessary when the CImageColumnIterator1bp
			iterator is used as l-value like this: 
			\verbatim
			*it = UINT32(Color);
			\endverbatim */
		inline CIntermediateType& operator=(UINT32 Color){
			(Color ? (*(*m_ppCurrByte+(*m_pPixelIndexInByte>>3)) |= (0x80>>(*m_pPixelIndexInByte%8))) : 
					(*(*m_ppCurrByte+(*m_pPixelIndexInByte>>3)) &= (0xff7f>>((*m_pPixelIndexInByte%8)))));
			return *this;
		};
		/** overloading operator() (function operator). This is necessary when the CImageColumnIterator1bp
			iterator is used as l-value like this: 
			\verbatim
			UINT32 Color = *it;
			\endverbatim
			*it is converted to the UINT32 Color value at the current position by this 
			operator overloading. */
		inline operator UINT32()
		{
			return ((*(*m_ppCurrByte+(*m_pPixelIndexInByte>>3))) & (0x80>>(*m_pPixelIndexInByte%8)) )!=0;
		}
		/** Called when CImageColumnIterator1bp::operator[] is used. */
		inline const UINT32 operator[](UINT32 i)
		{
			return ((*(*m_ppCurrByte+((*m_pPixelIndexInByte+i)>>3))) & (0x80>>((*m_pPixelIndexInByte+i)%8)) )!=0;
		}
	};
protected: // attributes
	/// Pointer to TImage structure of the image to be iterated
	const TImage* m_pTImg;
	/** Pixel index in actual byte containing the column for iteration, i.e. the column 
		index mod 8 since one byte contains 8 pixels. When iterating a column, this value 
		stays constant. Set by constructor. */
    int m_PixelIndexInByte;
	/** Pointer to byte containing the pixel value for actual index, using this in conjunction
		wiht m_PixelIndexInByte makes it possible to extract the actual pixel. Updated when operator ++ is used. */
	UINT8* m_pCurrByte;
	/// Counter for last element+1 in actual row
	UINT8* m_pEnd;
	/** Since a pixel for 1 b/p images is not a generic type nor a class, this intermediate
		type is needed in order to give the correct iterator interface to the programmer */
	CIntermediateType m_IntermediateType;
public:
	/** Constructor
		@param ColumnIndex Index of actual row, without origo and ROI.
		@param StartIndex Index to start iteration from in actual row, without origo and ROI.
		@param MaxIndex Max index + 1, where iteration should end, used to set the return value 
			for End(), without origo and ROI.
		@param pTImg Pointer to a TImage structure, a member of class CImage. */
	inline CImageColumnIterator1bp(UINT32 ColumnIndex, UINT32 StartIndex, UINT32 MaxIndex, const TImage* pTImg);
	/// overloading = operator
	inline CImageColumnIterator1bp& operator=(const CImageColumnIterator1bp& It);
	/** Returns an iterator to the last element plus one in current row or column.
		@return Last element plus one. */
	inline CImageColumnIterator1bp End() const;
	/** overloading ++ operator. Increments the pointer to data. 
		Note: the postfix operator++ is not implemented in this class since the resulting
		code cannot be optimized. Using that operator would remove the point of using this 
		iterator class. */
	inline CImageColumnIterator1bp& operator++() {m_pCurrByte-=m_pTImg->ByteWidth; return *this; }
	/** overloading the dereference operator, typically used when iterating. */
	inline CIntermediateType& operator*(){return m_IntermediateType;}
	/** overloading [] operator. */
	inline const UINT32 operator[](UINT32 i) {return m_IntermediateType[i];}
	/** overloading == operator.
		@return true, if iterator p and q points to same element in same column. */
	inline friend bool operator==(const CImageColumnIterator1bp& p, const CImageColumnIterator1bp& q);
	/** overloading != operator.
		@return true, if iterator p and q points to different elements. */
	inline friend bool operator!=(const CImageColumnIterator1bp& p, const CImageColumnIterator1bp& q);
	/** overloading < operator.
		@return true, if iterator p and q points to same column and p has row index < q's row index. */
	inline friend bool operator< (const CImageColumnIterator1bp& p, const CImageColumnIterator1bp& q);
};

inline CImageColumnIterator1bp::CImageColumnIterator1bp(UINT32 ColumnIndex, UINT32 StartIndex, UINT32 MaxIndex,
															const TImage* pTImg):
		m_pTImg(pTImg), m_PixelIndexInByte(ColumnIndex%8),
		m_pCurrByte(pTImg->ppAllScanLines[StartIndex]+(ColumnIndex>>3)), m_IntermediateType(&m_PixelIndexInByte,&m_pCurrByte),
		m_pEnd(m_pCurrByte-pTImg->ByteWidth*(MaxIndex-StartIndex))
{
}


inline CImageColumnIterator1bp& CImageColumnIterator1bp::operator=(const CImageColumnIterator1bp& It)
{
	m_pTImg = It.m_pTImg;
	m_PixelIndexInByte  = It.m_PixelIndexInByte;
	m_pCurrByte = It.m_pCurrByte;
	m_pEnd   = It.m_pEnd;
	m_IntermediateType = It.m_IntermediateType;
	return *this;
}

inline CImageColumnIterator1bp CImageColumnIterator1bp::End() const
{
	CImageColumnIterator1bp t = *this;
	t.m_pCurrByte = m_pEnd;
	return t;
}

inline bool operator==(const CImageColumnIterator1bp& p, const CImageColumnIterator1bp& q)
{
	return (p.m_pCurrByte==q.m_pCurrByte);
}

inline bool operator!=(const CImageColumnIterator1bp& p, const CImageColumnIterator1bp& q)
{
	return !(p==q);
}

inline bool operator<(const CImageColumnIterator1bp& p, const CImageColumnIterator1bp& q)
{
	return (p.m_pCurrByte<q.m_pCurrByte);
}

} // end namespace ipl

#endif //_IPL98_IMAGECOLUMNIT1BP_H
