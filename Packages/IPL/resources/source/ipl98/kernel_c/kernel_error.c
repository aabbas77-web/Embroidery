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

#include "kernel_error.h"
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef IPL98_ERRORS_TO_WINDOW
extern void AddIPL98ErrorHistory(const char* str);
#endif

#ifdef _IPL98_USING_CPP
namespace ipl{ /* use namespace if C++ */
extern "C" { /* prevent name mangling for C functions */
#endif

void k_ShowMessage(IPL_MESSAGETYPE MsgType, const TString* pLineAndFile,char* fmt, ...)
{
	TString StrOut;
	char* p;
	va_list args; /* argument pointer */
/* return if DISABLE is enabled and equals the given MsgType */
#ifdef DISABLE_IPL_ERROR
	if (MsgType==IPL_ERROR)
		return;
#elif defined DISABLE_IPL_WARNING
	if (MsgType==IPL_WARNING)
		return;
#endif
	k_InitString(&StrOut);
	p=(char*)malloc(sizeof(char)*MAX_MESSAGE_SIZE);

	va_start(args,fmt);
	if (vsprintf(p,fmt,args)>=MAX_MESSAGE_SIZE)
	{
		k_AddCharArrayToString("IPL_ERROR: k_ShowMessage() Error message to long "
			"- increase the MAX_MESSAGE_SIZE definition",&StrOut);
		k_AddFileAndLine(StrOut);
		fprintf(stderr,"%s\n",StrOut.pChars);
		assert(0);
	}
	else if (MsgType==IPL_ERROR)
	{
		k_AddCharArrayToString("IPL_ERROR: ",&StrOut);
		k_AddCharArrayToString(p,&StrOut);
		k_AddCharToString(' ',&StrOut);
		k_AddCharArrayToString(pLineAndFile->pChars,&StrOut);
	}
	else if (MsgType==IPL_WARNING)
	{
		k_AddCharArrayToString("IPL_WARNING: ",&StrOut);
		k_AddCharArrayToString(p,&StrOut);
		k_AddCharArrayToString(pLineAndFile->pChars,&StrOut);
	}
	else if (MsgType==IPL_NORMAL)
	{
		k_AddCharArrayToString(p,&StrOut);
	}
	else
	{
		/* should not be possible to get here! */
		k_AddCharArrayToString("Error: k_ShowMessage() unknown message type",&StrOut);
	}
	k_AddCharToString('\n',&StrOut);
	va_end(args);
	free(p);

	/***********************************************************
	 * To change the destination of error messages made by     *
	 * IPL98 replace the code below with your own              *
	 * The resulting string is accessed by "StrOut.pChars"     *
	 ***********************************************************/
	printf("%s",StrOut.pChars);
#ifdef IPL98_ERRORS_TO_WINDOW
	AddIPL98ErrorHistory(StrOut.pChars);
#endif

	/* Don't delete this line */
	k_EmptyString(&StrOut);

}

#ifdef _IPL98_USING_CPP
} /* end of extern "C" */
} /* end namespace ipl */
#endif
