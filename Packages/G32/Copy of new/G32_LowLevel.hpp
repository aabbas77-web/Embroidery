// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'G32_LowLevel.pas' rev: 5.00

#ifndef G32_LowLevelHPP
#define G32_LowLevelHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <G32.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace G32_lowlevel
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE G32::TColor32 __fastcall Clamp(int Value);
extern PACKAGE void __fastcall FillLongword(void *X, int Count, unsigned Value);
extern PACKAGE void __fastcall Swap(int &A, int &B);
extern PACKAGE void __fastcall TestSwap(int &A, int &B);
extern PACKAGE bool __fastcall TestClip(int &A, int &B, int Size);
extern PACKAGE int __fastcall Constrain(int Value, int Lo, int Hi);
extern PACKAGE int __fastcall SAR_4(int Value);
extern PACKAGE int __fastcall SAR_8(int Value);
extern PACKAGE int __fastcall SAR_9(int Value);
extern PACKAGE int __fastcall SAR_12(int Value);
extern PACKAGE int __fastcall SAR_16(int Value);
extern PACKAGE G32::TColor32 __fastcall ColorSwap(Graphics::TColor WinColor);
extern PACKAGE int __fastcall MulDiv(int Multiplicand, int Multiplier, int Divisor);

}	/* namespace G32_lowlevel */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace G32_lowlevel;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// G32_LowLevel
