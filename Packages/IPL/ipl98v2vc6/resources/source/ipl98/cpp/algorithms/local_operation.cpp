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

#include "local_operation.h"
#include "../../kernel_c/algorithms/kernel_local_operation.h"
#include "../../kernel_c/kernel_history.h"

namespace ipl{

CLocalOperation::CLocalOperation()
{
}

CLocalOperation::~CLocalOperation()
{
}

bool CLocalOperation::DrawHistogram(CStdImage &Source, CStdImage &Dest)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCLocalOperation::DrawHistogram()",ipl_HistoryIndent);
	Source.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	bool ReturnValue=k_DrawHistogram(Source.GetTImagePtr(),Dest.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CLocalOperation::DrawHistogram() failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
	/* remove the history line added to source above */
	if (&Source!=&Dest)
		Source.m_History.RemoveLastLine();
#endif
	return ReturnValue;
}

bool CLocalOperation::EqualizeHistogram(CStdImage &Source, CStdImage &Dest)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCLocalOperation::EqualizeHistogram()",ipl_HistoryIndent);
	Source.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	bool ReturnValue=k_EqualizeHistogram(Source.GetTImagePtr(), Dest.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CLocalOperation::EqualizeHistogram() failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
	/* remove the history line added to source above */
	if (&Source!=&Dest)
		Source.m_History.RemoveLastLine();
#endif
	return ReturnValue;
}

bool CLocalOperation::NonlinearCopyToByte(CStdImage &Source, float gamma,
	int Min,int Max,CStdImage &Dest)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCLocalOperation::NonlinearCopyToByte() CStdImage as source "
		"gamma=%f, Min=%d, Max=%d",ipl_HistoryIndent,gamma,Min,Max);
	Source.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	bool ReturnValue=k_NonlinearCopyByteToByte(Source.GetTImagePtr(),gamma,Min,Max,Dest.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CLocalOperation::NonlinearCopyToByte() failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
	/* remove the history line added to source above */
	if (&Source!=&Dest)
		Source.m_History.RemoveLastLine();
#endif
	return ReturnValue;
}

bool CLocalOperation::NonlinearCopyToByte(CIntImage &Source, float gamma,
	int Min,int Max,CStdImage &Dest)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCLocalOperation::NonlinearCopyToByte() CIntImage as source "
		"gamma=%f, Min=%d, Max=%d",ipl_HistoryIndent,gamma,Min,Max);
	Source.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	bool ReturnValue=k_NonlinearCopyIntToByte(Source.GetTIntImagePtr(),gamma,Min,Max,Dest.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CLocalOperation::NonlinearCopyToByte() failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
	/* remove the history line added to source above */
	Source.m_History.RemoveLastLine();
#endif
	return ReturnValue;
}

bool CLocalOperation::NonlinearCopyToByte(CFloatImage &Source,
	float gamma, float Min, float Max,CStdImage &Dest)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCLocalOperation::NonlinearCopyToByte() CFloatImage as source "
		"gamma=%f, Min=%d, Max=%d",ipl_HistoryIndent,gamma,Min,Max);
	Source.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	bool ReturnValue=k_NonlinearCopyFloatToByte(Source.GetTFloatImagePtr(),gamma,Min,Max,Dest.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CLocalOperation::NonlinearCopyToByte() failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
	/* remove the history line added to source above */
	Source.m_History.RemoveLastLine();
#endif
	return ReturnValue;
}

bool CLocalOperation::NonlinearCopyToByte(CComplexImage &Source,COMPLEXCHOISE mode,
	float gamma, float Min,float Max,CStdImage &Dest)
{
#ifdef IPL_ADD_HISTORY
	/* add comment to history */
	TString History;
	k_InitString(&History);
	k_SprintfString(&History,"%sCLocalOperation::NonlinearCopyToByte() CComplexImage as source "
		"gamma=%f, Min=%d, Max=%d",ipl_HistoryIndent,gamma,Min,Max);
	Source.m_History.AppendIPL(History.pChars);
	k_EmptyString(&History);
	k_IplStartHistoryMacro();
#endif
	bool ReturnValue=k_NonlinearCopyComplexToByte(Source.GetTComplexImagePtr(),mode,gamma,Min,Max,Dest.GetTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CLocalOperation::NonlinearCopyToByte() failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
#ifdef IPL_ADD_HISTORY
	/* end history appending (remove a leading '\t' character) */
	k_IplStopHistoryMacro();
	/* remove the history line added to source above */
	Source.m_History.RemoveLastLine();
#endif
	return ReturnValue;
}

} // end ipl namespace
