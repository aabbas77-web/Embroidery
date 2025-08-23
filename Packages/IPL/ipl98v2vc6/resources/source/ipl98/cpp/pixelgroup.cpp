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

#include "pixelgroup.h"

namespace ipl{

CPixelGroup::CPixelGroup()
{
	// default constructor
	m_pGroup=new TPixelGroup;
	m_OwnGroup=true;
	k_InitGroup(m_pGroup);
}

CPixelGroup::CPixelGroup(TPixelGroup& TGroup)
{
	// constructor which takes an external TGroup as reference to data
	m_pGroup=&TGroup;
	m_OwnGroup=false;
}

CPixelGroup::CPixelGroup(unsigned int InitialSize, bool AllocateColors)
{
	m_pGroup=new TPixelGroup;
	m_OwnGroup=true;
	k_InitGroup(m_pGroup);
	if (AllocateColors==true)
	{
		k_AllocGroupAndColors(m_pGroup,InitialSize);
	}
	else
	{
		k_AllocGroup(m_pGroup,InitialSize);
	}
}

CPixelGroup::CPixelGroup(const CPixelGroup& SourceGroup)
{ 
	// copy constructor
	k_InitGroup(m_pGroup);
	*this=SourceGroup; // use assignment operator
}

CPixelGroup& CPixelGroup::operator=(const CPixelGroup& SourceGroup)
{
	// overloading of assignment operator
	if (this != &SourceGroup)
	{
		// ok to do assignment
		k_CopyGroup(GetTPixelGroupPtr(),SourceGroup.GetConstTPixelGroupPtr());
	}
	else
	{
		ostringstream ost;
		ost << "CPixelGroup::operator=() Cannot assign CPixelGroup to itself" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return *this;
}

CPixelGroup::~CPixelGroup()
{
	//destructor
	if(m_OwnGroup==true)
	{
		k_EmptyGroup(m_pGroup);
		delete m_pGroup;
	}
}

void CPixelGroup::Empty()
{
	k_EmptyGroup(m_pGroup);
}

CPoint2D<int> CPixelGroup::GetTop() const
{
	return CPoint2D<int>(m_pGroup->Top.x,m_pGroup->Top.y);
}

CPoint2D<int> CPixelGroup::GetBottom() const
{
	return CPoint2D<int>(m_pGroup->Bottom.x,m_pGroup->Bottom.y);
}

CPoint2D<int> CPixelGroup::GetLeft() const
{
	return CPoint2D<int>(m_pGroup->Left.x,m_pGroup->Left.y);
}

CPoint2D<int> CPixelGroup::GetRight() const
{
	return CPoint2D<int>(m_pGroup->Right.x,m_pGroup->Right.y);
}

COLORTYPE CPixelGroup::GetColorType() const
{
	return m_pGroup->Color;
}

bool CPixelGroup::ColorsAvailable() const
{
	if (m_pGroup->pColor!=NULL)
		return true;
	else
		return false;
}

const TPixelGroup* CPixelGroup::GetConstTPixelGroupPtr() const
{
	return m_pGroup;
}


TPixelGroup* CPixelGroup::GetTPixelGroupPtr()
{
	return m_pGroup;
}

void CPixelGroup::MoveTPixelGroupPtr(TPixelGroup* p)
{
	m_pGroup=p;
}

bool CPixelGroup::InsertPosition(INT16 x, INT16 y, unsigned int Index)
{
	bool returnValue=k_InsertPosInGroup(x,y,Index,m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::InsertPosition() Failed inserting position" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::InsertPosition(CPoint2D<INT16> Pos, unsigned int Index)
{
	bool returnValue=k_InsertPosInGroup(Pos.GetX(),Pos.GetY(),Index,m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::InsertPosition() Failed inserting position" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::InsertPositionColor(INT16 x, INT16 y, UINT32 Color, unsigned int Index)
{
	bool returnValue=k_InsertPosColorInGroup(x,y,Color,Index,m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::InsertPositionColor() Failed inserting position" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::InsertPositionColor(const CPoint2D<INT16>& Pos, UINT32 Color, unsigned int Index)
{
	bool returnValue=k_InsertPosColorInGroup(Pos.GetX(),Pos.GetY(),Color,Index,m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::InsertPositionColor() Failed inserting position" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::RemovePosition(unsigned int Index)
{
	bool returnValue=k_RemovePosFromGroup(Index,m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::RemovePosition() Failed removing position" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::RemovePositionSlow(unsigned int Index)
{
	bool returnValue=k_RemovePosFromGroupSlow(Index,m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::RemovePositionSlow() Failed removing position" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

unsigned int CPixelGroup::RemoveDuplicates()
{
	return k_RemoveDuplicatesFromGroup(m_pGroup);
}

void CPixelGroup::ReAllocPositions(unsigned int NewSize)
{
	k_ReAllocGroup(m_pGroup,NewSize);
}

void CPixelGroup::AdjustSizeOfPositions()
{
	k_AdjustSizeOfGroup(m_pGroup);
}

bool CPixelGroup::AllocColors()
{
	bool returnValue=k_AllocColorsGroup(m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::AllocColors() Failed allocating memory for color values or its allready allocated" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::AllocAndInitColors(UINT32 InitialValue)
{
	bool returnValue=k_AllocAndInitColorsGroup(InitialValue,m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::AllocAndInitColors() Failed allocating memory for color values or its allready allocated" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::AddColors(const CStdImage& Img)
{
	bool returnValue=k_AddColorsToGroup(Img.GetConstTImagePtr(),m_pGroup);
	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::AddColors() Failed adding colors" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

void CPixelGroup::RemoveColors()
{
	k_RemoveColors(m_pGroup);
}

bool CPixelGroup::CopyToImage(const CPalette* pPalette, UINT32 BackGround, CStdImage& Dest)
{
	bool returnValue;
	if (pPalette!=NULL)
		returnValue=k_CopyGroupToImage(pPalette->GetPalettePtr(), BackGround,Dest.GetTImagePtr(),m_pGroup);
	else
		returnValue=k_CopyGroupToImage(NULL, BackGround,Dest.GetTImagePtr(),m_pGroup);

	if (returnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::CopyToImage() Failed creating image" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return returnValue;
}

bool CPixelGroup::AddToImage(CStdImage& Dest,UINT32 Color)
{
	bool ReturnValue=k_AddGroupToImage(Dest.GetTImagePtr(), m_pGroup, Color);
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::AddToImage() Failed adding group to image" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return ReturnValue;
}

bool CPixelGroup::AddToImage(CStdImage& Dest)
{
	bool ReturnValue=k_AddGroupColorsToImage(Dest.GetTImagePtr(), m_pGroup);
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CPixelGroup::AddToImage() Failed adding group with colors to image" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return ReturnValue;
}

bool CPixelGroup::PosInGroup(const CPoint2D<INT16>& Pos,unsigned int& Index)
{	
	T2DInt p;
	p.x=Pos.GetX();
	p.y=Pos.GetY();	
	return k_PosInGroup(m_pGroup,p,&Index);
}

bool CPixelGroup::PosInGroup(INT16 x, INT16 y,unsigned int& Index)
{	
	T2DInt p;
	p.x=x;
	p.y=y;	
	return k_PosInGroup(m_pGroup,p,&Index);
}

bool CPixelGroup::PosInGroup(const CPoint2D<INT16>& Pos)
{	
	unsigned int Dummy;
	T2DInt p;
	p.x=Pos.GetX();
	p.y=Pos.GetY();	
	return k_PosInGroup(m_pGroup,p,&Dummy);
}

bool CPixelGroup::PosInGroup(INT16 x, INT16 y)
{
	unsigned int Dummy;
	T2DInt p;
	p.x=x;
	p.y=y;	
	return k_PosInGroup(m_pGroup,p,&Dummy);
}

void CPixelGroup::PrintInfo(bool PrintPositions,unsigned int PosPrLine)
{
	k_PrintGroupInfo(m_pGroup,PrintPositions,PosPrLine);
}

ostream& operator<<(ostream& s,const CPixelGroup& Group)
{
	s << "**************** PixelGroup info ********************\n" <<
		" Positions: Top=(" << Group.m_pGroup->Top.x << "," << Group.m_pGroup->Top.y <<
		") Bottom=(" << Group.m_pGroup->Bottom.x << "," << Group.m_pGroup->Bottom.y <<
		") Left=(" << Group.m_pGroup->Left.x << "," << Group.m_pGroup->Left.y <<
		") Right=(" << Group.m_pGroup->Right.x << "," << Group.m_pGroup->Right.y << ")\n";
	s << " Width=" << Group.GetWidth() << " Height=" << Group.GetHeight() << endl;
	s << " NumberOfPixels=" << Group.m_pGroup->NumberOfPixels << " AllocatedPixels=" <<
		Group.m_pGroup->AllocatedPixels << endl;
	return s;
}

void CPixelGroup::UpdateBoundaries()
{
	k_GroupUpdateBoundaries(m_pGroup);
}

bool CPixelGroup::AddOffset(const CPoint2D<INT16>& Offset)
{
	T2DInt p;
	p.x=Offset.GetX();
	p.y=Offset.GetY();	
	return k_GroupAddOffset(m_pGroup,p);
}

} // end ipl namespace
