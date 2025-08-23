// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrTypes.pas' rev: 5.00

#ifndef VrTypesHPP
#define VrTypesHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrtypes
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EVrException;
class PASCALIMPLEMENTATION EVrException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EVrException(const AnsiString Msg) : Sysutils::Exception(Msg
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EVrException(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EVrException(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EVrException(int Ident, const System::TVarRec * Args
		, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EVrException(const AnsiString Msg, int AHelpContext) : 
		Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EVrException(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EVrException(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EVrException(System::PResStringRec ResStringRec, 
		const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EVrException(void) { }
	#pragma option pop
	
};


typedef SmallString<4>  TVrVersion;

typedef void __fastcall (__closure *TVrHoursChangeEvent)(System::TObject* Sender, Word Hours);

typedef void __fastcall (__closure *TVrMinutesChangeEvent)(System::TObject* Sender, Word Minutes);

typedef void __fastcall (__closure *TVrSecondsChangeEvent)(System::TObject* Sender, Word Seconds);

#pragma option push -b-
enum TVrDrawStyle { dsOwnerDraw, dsNormal };
#pragma option pop

typedef int TVrColInt;

typedef int TVrRowInt;

typedef Shortint TVrHoursInt;

typedef Shortint TVrMinutesInt;

typedef Shortint TVrSecondsInt;

typedef Shortint TVrPercentInt;

typedef int TVrMaxInt;

typedef Byte TVrByteInt;

typedef Shortint TVrNumGlyphs;

#pragma option push -b-
enum TVrTransparentMode { tmPixel, tmColor };
#pragma option pop

typedef Word TVrTextAngle;

#pragma option push -b-
enum TVrTextAlignment { vtaLeft, vtaCenter, vtaRight, vtaTopLeft, vtaTop, vtaTopRight, vtaBottomLeft, 
	vtaBottom, vtaBottomRight };
#pragma option pop

#pragma option push -b-
enum TVrShapeType { stRectangle, stSquare, stRoundRect, stRoundSquare, stEllipse, stCircle };
#pragma option pop

#pragma option push -b-
enum TVrImageTextLayout { ImageLeft, ImageRight, ImageTop, ImageBottom };
#pragma option pop

#pragma option push -b-
enum TVrOrientation { voVertical, voHorizontal };
#pragma option pop

#pragma option push -b-
enum TVrTickMarks { tmNone, tmBoth, tmBottomRight, tmTopLeft };
#pragma option pop

#pragma option push -b-
enum TVrProgressStyle { psBottomLeft, psTopRight };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int VrTextAlign[9];

}	/* namespace Vrtypes */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrtypes;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrTypes
