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

#include "byte_image.h"
#include "../kernel_c/byte_image/b_kernel_functions.h"
#include "../kernel_c/kernel_history.h"

namespace ipl{

CByteImage::CByteImage()
{
	// default constructor
	kB_InitImage(&m_Image); // always initialise m_Image in constr.
	kB_EmptyImage(&m_Image); // start with empty
	m_Pal.SetPalettePtr(&m_Image.Pal); // initialise the palette class
	m_ROIActive=false;
}

CByteImage::CByteImage(UINT32 Width,UINT32 Height, UINT32 Color)
{
	//constr. for empty image
	kB_InitImage(&m_Image); // always initialise m_Image in constr.
	kB_AllocImage(Width,Height,&m_Image);
	m_ppPixel=m_Image.ppMatrix;
	m_Pal.SetPalettePtr(&m_Image.Pal);
	m_ROIActive=false;
	if (Color!=0)
		Flush(Color);
}

CByteImage::CByteImage(const CByteImage& SourceImage)
{
	// copy constructor
	kB_InitImage(&m_Image); // always initialise m_Image in constr.
	*this=SourceImage; // use assignment operator
}

CByteImage::~CByteImage()
{ //destructor
	kB_EmptyImage(&m_Image);
}

CByteImage& CByteImage::operator=(const CStdImage& SourceImage)
{
	// overloading of assignment operator
	if (SourceImage.GetBits()!=8)
	{
		ostringstream ost;
		ost << "CByteImage::operator=() Right hand side of '='-operator must be 8 b/p "
			"(current is " << SourceImage.GetBits() << " b/p)" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return *this;
	}
	CStdImage::operator=(SourceImage);
	m_ppPixel=m_Image.ppMatrix;
	return *this;
}

CByteImage& CByteImage::operator=(const CByteImage& SourceImage)
{
	// overloading of assignment operator
	if (this != &SourceImage)
	{
		// ok to do assignment
		// no copying if source is empty
		if (SourceImage.GetOrigin()!=EMPTY)
		{
#ifdef IPL_ADD_HISTORY
			k_IplStartHistoryMacro();
#endif
			/* call kernel function */
			kB_CopyImage(&m_Image,SourceImage.GetConstTImagePtr());
			/* set pointers */
			m_Pal.SetPalettePtr(&m_Image.Pal);
			m_History.SetTextPtr(&m_Image.History);
			m_ppPixel=m_Image.ppMatrix;
			/* copy ROI */
			m_ROIActive=SourceImage.m_ROIActive;
			if (m_ROIActive==true)
			{
				m_ROIUpperLeft=SourceImage.m_ROIUpperLeft;
				m_ROILowerRight=SourceImage.m_ROILowerRight;
			}
#ifdef IPL_ADD_HISTORY
			/* this is a really bad hack! Removing the last line added by the C code from
			   this objects history, inserting the C++ line and appending the just removed
			   line again. This assumes that only one line is added by the C code. */
			string HistoryTemp;
			TString History;
			k_InitString(&History);
			/* end history appending (remove a leading '\t' character) */
			k_IplStopHistoryMacro();
			k_SprintfString(&History,"%sCByteImage::operator=",ipl_HistoryIndent);
			m_History.GetItem(m_History.TotalItems()-1,HistoryTemp);
			m_History.RemoveLastLine();
			m_History.AppendIPL(History.pChars);
			int k=HistoryTemp.find_first_of("\t");
			m_History.AppendIPL(HistoryTemp.substr(k,HistoryTemp.size()-1-k));
			k_EmptyString(&History);
#endif
		}
		else
		{
			kB_EmptyImage(&m_Image); // empty image in all cases
		}

	}
	else
	{
		ostringstream ost;
		ost << "CByteImage::operator=() Cannot assign CByteImage to itself" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return *this;
}

bool CByteImage::Alloc(UINT32 Width, UINT32 Height, UINT16 Bits, UINT32 Color)
{
	bool ReturnValue;
	if (Bits!=8)
	{
		ostringstream ost;
		ost << "CByteImage::Alloc() The parameter Bits must be 8 (current is " << Bits << ")" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		ReturnValue=false;
	}
	else
	{
		ReturnValue=kB_AllocImage(Width,Height,&m_Image);
		if (ReturnValue==false)
		{
			ostringstream ost;
			ost << "CByteImage::Alloc() Failed allocating image" << IPLAddFileAndLine;
			CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		}
		else
		{
			if (Color!=0)
				Flush(Color);
		}
		m_ppPixel=m_Image.ppMatrix;
		m_ROIActive=false;
	}
	return ReturnValue;
}

bool CByteImage::Alloc(UINT32 Width, UINT32 Height)
{
	bool ReturnValue=kB_AllocImage(Width,Height,&m_Image);
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CByteImage::Alloc() Failed allocating image" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	m_ppPixel=m_Image.ppMatrix;
	m_ROIActive=false;
	return ReturnValue;
}

bool CByteImage::AllocFast(UINT32 Width, UINT32 Height, UINT16 Bits)
{
	bool ReturnValue;
	if (Bits!=8)
	{
		ostringstream ost;
		ost << "CByteImage::AllocFast() The parameter Bits must be 8 (current is " << Bits << ")" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		ReturnValue=false;
	}
	else
	{
		ReturnValue=kB_AllocImageFast(Width,Height,&m_Image);
		if (ReturnValue==false)
		{
			ostringstream ost;
			ost << "CByteImage::AllocFast() Failed allocating image" << IPLAddFileAndLine;
			CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		}
		m_ppPixel=m_Image.ppMatrix;
		m_ROIActive=false;
	}
	return ReturnValue;
}

bool CByteImage::AllocFast(UINT32 Width, UINT32 Height)
{
	bool ReturnValue=kB_AllocImageFast(Width,Height,&m_Image);
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CByteImage::AllocFast() Failed allocating image" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	m_ppPixel=m_Image.ppMatrix;
	m_ROIActive=false;
	return ReturnValue;
}

bool CByteImage::CopySubImage(CStdImage& SourceImage,int xmin,int ymin,
				  int xmax, int ymax)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history, done by adding to source and removing later (hack) */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCByteImage::CopySubImage(xmin=%d,ymin=%d,xmax=%d,ymax=%d) Source image file info: %s",
		ipl_HistoryIndent,xmin,ymin,xmax,ymax,SourceImage.GetConstTImagePtr()->FileInfo.PathAndFileName);
	SourceImage.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	/* call base class method */
	bool ReturnValue=kB_CopySubImage(xmin,ymin,xmax,ymax,&m_Image,SourceImage.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CByteImage::CopySubImage() Failed copying subimage" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	else
		m_ROIActive=false;

	m_ppPixel=m_Image.ppMatrix;
#ifdef IPL_ADD_HISTORY
	if (&SourceImage!=this)
	{
		/* remove the history just added to the source image */
		SourceImage.m_History.RemoveLastLine();
	}
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
#endif
	return ReturnValue;
}

bool CByteImage::CopySubImage(CStdImage& SourceImage,const CPoint2D<int>& UpperLeft,
		  const CPoint2D<int>& LowerRight)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history, done by adding to source and removing later (hack) */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCByteImage::CopySubImage(UpperLeft=(%d,%d),LowerLeft=(%d,%d)) Source image file info: %s",
		ipl_HistoryIndent,UpperLeft.GetX(),UpperLeft.GetY(),LowerRight.GetX(),LowerRight.GetY(),SourceImage.GetConstTImagePtr()->FileInfo.PathAndFileName);
	SourceImage.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	/* call base class method */
	bool ReturnValue=kB_CopySubImage(UpperLeft.GetX(),UpperLeft.GetY(),LowerRight.GetX(),
					LowerRight.GetY(),&m_Image,SourceImage.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CByteImage::CopySubImage() Failed copying subimage" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	m_ppPixel=m_Image.ppMatrix;	
#ifdef IPL_ADD_HISTORY
	if (&SourceImage!=this)
	{
		/* remove the history just added to the source image */
		SourceImage.m_History.RemoveLastLine();
	}
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
#endif
	return ReturnValue;
}

bool CByteImage::SetBorder(UINT16 Size, UINT32 Color)
{
	// Set the size of image border
	bool returnValue=CStdImage::SetBorder(Size,Color);
	m_ppPixel=m_Image.ppMatrix;	
	return returnValue;
}

bool CByteImage::SetBorderSize(UINT16 Size)
{
	bool returnValue=CStdImage::SetBorderSize(Size);
	m_ppPixel=m_Image.ppMatrix;	
	return returnValue;
}

bool CByteImage::Load(const char* pPathAndFileName)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	CText TempHistory;
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCByteImage::Load(%s)",ipl_HistoryIndent,pPathAndFileName);
	TempHistory.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	/* call kernel function */
	bool ReturnValue=k_Load(pPathAndFileName,&m_Image);
	if (ReturnValue==true)
	{
		if (m_Image.Bits != 8)
		{
			ostringstream ost;
			ost << "CByteImage::Load() Source is " << m_Image.Bits << 
				" b/p - can only load 8 b/p (may be changed in future versions)" << IPLAddFileAndLine;
			CError::ShowMessage(IPL_ERROR,ost.str().c_str());
			k_EmptyImage(&m_Image); // empty loaded image
			ReturnValue=false;
		}
		else
		{	
			// set the matrix "pointer" for a byte image
			kB_SetImageMatrix(&m_Image);
			m_ppPixel=m_Image.ppMatrix;
			m_Pal.SetPalettePtr(&m_Image.Pal);
			m_ROIActive=false;
#ifdef IPL_ADD_HISTORY
			/* append the new created history in k_Load to the temporary history and
			   copy the temporary history back to this objects history */
			TempHistory.AddDate(false);
			TempHistory.AddTime(false);
			bool AddDate=m_History.AddDate(false);
			bool AddTime=m_History.AddTime(false);
			TempHistory.AppendCText(m_History);
			m_History=TempHistory;
			m_History.AddDate(AddDate);
			m_History.AddTime(AddTime);
#endif
		}
	}
	else
	{
		ostringstream ost;
		ost << "CByteImage::Load(\"" << pPathAndFileName << "\") Failed loading image" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
#endif
	return ReturnValue;
}

bool CByteImage::Load(const string& PathAndFileName)
{
	return Load(PathAndFileName.c_str());
}

bool CByteImage::Save(const char* pPathAndFileName)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCStdImage::Save(%s)",ipl_HistoryIndent,pPathAndFileName);
	m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	/* call kernel function */
	bool ReturnValue=k_Save(pPathAndFileName,&m_Image);
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CByteImage::Save(\"" << pPathAndFileName << "\") Failed saving image" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
#ifdef IPL_ADD_HISTORY
		/* remove the history line added above */
		m_History.RemoveLastLine();
#endif
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
#endif
	return ReturnValue;
}

bool CByteImage::Save(const string& PathAndFileName)
{
	return Save(PathAndFileName.c_str());
}

bool CByteImage::CopyConvert(UINT16 Bits,CStdImage& SourceImage)
{
	if (Bits!=8)
	{
		ostringstream ost;
		ost << "CByteImage::CopyConvert() Bits must be 8 instead of " << Bits << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	/* add comment to history, done by adding to source and removing later (hack) */
#ifdef IPL_ADD_HISTORY
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCByteImage::CopyConvert() From %d b/p to %d b/p, source image file info: %s",
		ipl_HistoryIndent,SourceImage.GetBits(),Bits,SourceImage.GetConstTImagePtr()->FileInfo.PathAndFileName);
	SourceImage.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	/* call kernel function */
	bool ReturnValue=k_CopyConvert(Bits,&m_Image,SourceImage.GetConstTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CByteImage::CopyConvert() Failed copying subimage" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	if (&SourceImage!=this)
	{
		/* remove the history just added to the source image */
		SourceImage.m_History.RemoveLastLine();
	}
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
#endif
	return ReturnValue;
}

void CByteImage::PrintInfo() const
{
	kB_PrintImageInfo(&m_Image);
	// write ROI information
	if (ROIActive()==true)
	{
		cout << " ROI: " << GetROIUpperLeft() << " -> " << GetROILowerRight() << endl;
	}
	else
		cout << " ROI inactive" << endl;
}

void CByteImage::PrintOrigin() const
{
	k_PrintOrigin(m_Image.Origin);
}

ostream& operator<<(ostream& s,const CByteImage& Img)
{
	s << "**************** ByteImage info ********************\n" << 
		" Width=" << Img.GetWidth() << " Height=" << Img.GetHeight() <<
		" ByteWidth=" << Img.GetLineByteWidth() << " SizeImage=" <<
		(Img.GetConstTImagePtr())->TotalSize << " Bits=8 (always!)" <<
		"\n PalEntries=" << Img.m_Pal.GetNumberOfEntries() << " BorderSize=" <<
		Img.GetBorderSize() << " Origo=(0,0) (always!)" << " Origin=";
	
	char* OriginStr;
	k_GetOriginString((Img.GetConstTImagePtr())->Origin,&OriginStr);

	s << OriginStr << endl;
	free(OriginStr);
	// write ROI information
	if (Img.ROIActive()==true)
	{
		s << " ROI: " << Img.GetROIUpperLeft() << " -> " << Img.GetROILowerRight() << endl;
	}
	else
		s << " ROI inactive" << endl;

	// write file information
	const TFileInfo* FileInfo=&(Img.GetConstTImagePtr())->FileInfo;
	if (FileInfo->FileName!=NULL)
	{
		s << " File name: " << FileInfo->FileName;
	}
	else
	{
		s << " File name: Not available";
	}
	if (FileInfo->PathName!=NULL)
	{
		s << " File path: " << FileInfo->PathName;
	}
	else
	{
		s << " File path: Not available";
	}

	return s;
}


} // end ipl namespace
