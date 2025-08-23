// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ShellStrings.pas' rev: 5.00

#ifndef ShellStringsHPP
#define ShellStringsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Shellstrings
{
//-- type declarations -------------------------------------------------------
struct ShellStrings__1
{
	AnsiString Title;
	Classes::TAlignment Alignment;
	int Width;
} ;

typedef ShellStrings__1 ShellStrings__2[4];

//-- var, const, procedure ---------------------------------------------------
#define strNewFolder "New Folder"
extern PACKAGE ShellStrings__1 ColData[4];
#define strKB "KB"

}	/* namespace Shellstrings */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Shellstrings;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ShellStrings
