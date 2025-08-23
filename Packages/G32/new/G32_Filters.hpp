// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'G32_Filters.pas' rev: 5.00

#ifndef G32_FiltersHPP
#define G32_FiltersHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <G32_ByteMaps.hpp>	// Pascal unit
#include <G32_Blend.hpp>	// Pascal unit
#include <G32.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace G32_filters
{
//-- type declarations -------------------------------------------------------
typedef Byte TLUT8[256];

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall AlphaToGrayscale(G32::TBitmap32* Dst, G32::TBitmap32* Src);
extern PACKAGE void __fastcall IntensityToAlpha(G32::TBitmap32* Dst, G32::TBitmap32* Src);
extern PACKAGE void __fastcall Invert(G32::TBitmap32* Dst, G32::TBitmap32* Src);
extern PACKAGE void __fastcall InvertRGB(G32::TBitmap32* Dst, G32::TBitmap32* Src);
extern PACKAGE void __fastcall ColorToGrayscale(G32::TBitmap32* Dst, G32::TBitmap32* Src);
extern PACKAGE void __fastcall ApplyLUT(G32::TBitmap32* Dst, G32::TBitmap32* Src, const Byte * LUT);
	

}	/* namespace G32_filters */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace G32_filters;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// G32_Filters
