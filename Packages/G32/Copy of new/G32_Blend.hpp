// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'G32_Blend.pas' rev: 5.00

#ifndef G32_BlendHPP
#define G32_BlendHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <G32.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace G32_blend
{
//-- type declarations -------------------------------------------------------
typedef G32::TColor32 __fastcall (*TCombineReg)(G32::TColor32 X, G32::TColor32 Y, G32::TColor32 W);

typedef void __fastcall (*TCombineMem)(G32::TColor32 F, G32::TColor32 &B, G32::TColor32 W);

typedef G32::TColor32 __fastcall (*TBlendReg)(G32::TColor32 F, G32::TColor32 B);

typedef void __fastcall (*TBlendMem)(G32::TColor32 F, G32::TColor32 &B);

typedef G32::TColor32 __fastcall (*TBlendRegEx)(G32::TColor32 F, G32::TColor32 B, G32::TColor32 M);

typedef void __fastcall (*TBlendMemEx)(G32::TColor32 F, G32::TColor32 &B, G32::TColor32 M);

typedef void __fastcall (*TBlendLine)(G32::PColor32 Src, G32::PColor32 Dst, int Count);

typedef void __fastcall (*TBlendLineEx)(G32::PColor32 Src, G32::PColor32 Dst, int Count, G32::TColor32 
	M);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool MMX_ACTIVE;
extern PACKAGE TCombineReg CombineReg;
extern PACKAGE TCombineMem CombineMem;
extern PACKAGE TBlendReg BlendReg;
extern PACKAGE TBlendMem BlendMem;
extern PACKAGE TBlendRegEx BlendRegEx;
extern PACKAGE TBlendMemEx BlendMemEx;
extern PACKAGE TBlendLine BlendLine;
extern PACKAGE TBlendLineEx BlendLineEx;
extern PACKAGE void __fastcall EMMS(void);
extern PACKAGE G32::TColor32 __fastcall ColorAdd(G32::TColor32 C1, G32::TColor32 C2);
extern PACKAGE G32::TColor32 __fastcall ColorSub(G32::TColor32 C1, G32::TColor32 C2);
extern PACKAGE G32::TColor32 __fastcall ColorModulate(G32::TColor32 C1, G32::TColor32 C2);
extern PACKAGE G32::TColor32 __fastcall ColorMax(G32::TColor32 C1, G32::TColor32 C2);
extern PACKAGE G32::TColor32 __fastcall ColorMin(G32::TColor32 C1, G32::TColor32 C2);
extern PACKAGE G32::TColor32 __fastcall Lighten(G32::TColor32 C, int Amount);

}	/* namespace G32_blend */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace G32_blend;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// G32_Blend
