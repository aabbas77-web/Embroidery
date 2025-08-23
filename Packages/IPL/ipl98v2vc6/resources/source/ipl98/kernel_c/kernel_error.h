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

#ifndef _IPL98_KERNEL_ERROR_H
#define _IPL98_KERNEL_ERROR_H

#include "../ipl98_setup.h" /* always include the setup file */
#include "kernel_string.h"

#ifdef _IPL98_USING_CPP
namespace ipl{ /* use namespace if C++ */
extern "C" { /* prevent name mangling for C functions */
#endif

/** @defgroup errorhandling Error and warning handling by IPL98.
	Kernel ANSI C error/warning functions, Last updated 3/23/1999.
	These functions are part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	@version 0.85
	@author René Dencker Eriksen (edr@mip.sdu.dk)
    @{ */

/** The three values IPL_ERROR, IPL_WARNING and IPL_NORMAL denotes what type of message should
	be produced.
	@see k_ShowMessage */
typedef enum {IPL_ERROR, IPL_WARNING, IPL_NORMAL} IPL_MESSAGETYPE;

/** defines the maximum size of the "fmt"-string
	given as argument to k_ShowMessage() */
#define MAX_MESSAGE_SIZE 400

/** This function should be used by all messages produced by the ANSI C part of IPL98. In the
	header file "ipl98.h" you can decide which error messages should be produced by the three
	definitions "DISABLE_IPL_ERROR", "DISABLE_IPL_WARNING" and "DISABLE_IPL_NORMAL". By default these
	constants are not defined. To remove path/file information and line information look at
	the explanation to k_AddFileAndLine(). To change the output (default is to stdout) to
	another stream edit the bottom source code in this function (in the file kernel_error.c).
	@param MsgType (IPL_MESSAGETYPE) Three types of messages can be handled: IPL_ERROR, IPL_WARNING and IPL_NORMAL.
		In case of IPL_ERROR or IPL_WARNING, the given string "pLineAndFile" is appended to the resulting
		message and either "IPL_ERROR" or "IPL_WARNING" is inserted in front of the message. In case of
		"IPL_NORMAL" no appending the parameter "fmt" is done.
	@param pLineAndFile (TString*) This parameter should be initialised with a call to the
		function k_AddFileAndLine() found in the string section.
	@param fmt (char*) Control format string exactly as the one given to "printf" in C.
		Must be followed by the corresponding arguments as in a "printf"-specification.
	@see k_AddFileAndLine */
void k_ShowMessage(IPL_MESSAGETYPE MsgType, const TString* pLineAndFile,char* fmt, ...);

/*@}*/ /* end group "errorhandling" */

#ifdef _IPL98_USING_CPP
} /* end of extern "C" */
} /* end namespace ipl */
#endif

#endif /* _IPL98_KERNEL_ERROR_H */
