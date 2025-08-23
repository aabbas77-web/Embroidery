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

#ifndef _IPL98_SETUP_H
#define _IPL98_SETUP_H

/************************************************/
/************************************************/
/********      IPL98 Setup area          ********/
/************************************************/
/************************************************/

/** If __cplusplus is defined, we define _IPL98_USING_CPP. This causes
	all code in the kernel ANSI C part to be included into the ipl namespace.
	If your compiler for some reason doesn't (it should but not all do) define 
	the __cplusplus but you know it is a C++ compiler, just make sure that 
	_IPL98_USING_CPP will be defined here. */
#if __cplusplus == 1
#define _IPL98_USING_CPP
#endif

/** @defgroup setup Defines controlling the compilation of the IPL98 library
	Definitions for controlling the compilation, last updated 7/2/2002.
	This section controls various parts of the compilation of IPL98. Pay
	attention to the big-endian definition if compiling on sparch etc.

	@version 0.70
	@author René Dencker Eriksen (edr@mip.sdu.dk)
	@{ */

/* Define IPL_BIG_ENDIAN on Sparc machines (f.ex. SGI and SUN) */
/*#define IPL_BIG_ENDIAN*/

/* Enable or disable messages produced by IPL98 */
/*#define DISABLE_IPL_ERROR*/		/* comment this line in to disable all errors of type IPL_ERROR */
/*#define DISABLE_IPL_WARNING*/		/* comment this line in to disable all errors of type IPL_WARNING */
/*#define DISABLE_IPL_NORMAL*/		/* comment this line in to disable all messages of type IPL_NORMAL */

/* Enable or disable adding to history from the ANSI C 
   and C++ part of the library. To disable adding history 
   out comment the line "#define IPL_ADD_HISTORY". */
#define IPL_ADD_HISTORY

/*@}*/ /* end group "setup" */

#endif /* _IPL98_SETUP_H */
