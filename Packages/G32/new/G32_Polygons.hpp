// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'G32_Polygons.pas' rev: 5.00

#ifndef G32_PolygonsHPP
#define G32_PolygonsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <G32_Blend.hpp>	// Pascal unit
#include <G32_LowLevel.hpp>	// Pascal unit
#include <G32.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace G32_polygons
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TPolyFillMode { pfAlternate, pfWinding };
#pragma option pop

class DELPHICLASS TPolygon32;
class PASCALIMPLEMENTATION TPolygon32 : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	bool FAntialiased;
	bool FClosed;
	TPolyFillMode FFillMode;
	DynamicArray<DynamicArray<G32::TFixedPoint > >  FNormals;
	DynamicArray<DynamicArray<G32::TFixedPoint > >  FPoints;
	
protected:
	void __fastcall BuildNormals(void);
	void __fastcall ClearNormals(void);
	
public:
	__fastcall virtual TPolygon32(void);
	__fastcall virtual ~TPolygon32(void);
	void __fastcall Add(const G32::TFixedPoint &P);
	void __fastcall Clear(void);
	TPolygon32* __fastcall Grow(const G32::TFixed Delta, float EdgeSharpness);
	void __fastcall Draw(G32::TBitmap32* Bitmap, G32::TColor32 OutlineColor, G32::TColor32 FillColor);
	void __fastcall DrawEdge(G32::TBitmap32* Bitmap, G32::TColor32 Color);
	void __fastcall DrawFill(G32::TBitmap32* Bitmap, G32::TColor32 Color);
	void __fastcall NewLine(void);
	void __fastcall Offset(const G32::TFixed Dx, const G32::TFixed Dy);
	TPolygon32* __fastcall Outline(void);
	__property bool Antialiased = {read=FAntialiased, write=FAntialiased, nodefault};
	__property bool Closed = {read=FClosed, write=FClosed, nodefault};
	__property TPolyFillMode FillMode = {read=FFillMode, write=FFillMode, nodefault};
	__property G32::TArrayOfArrayOfFixedPoint Normals = {read=FNormals, write=FNormals};
	__property G32::TArrayOfArrayOfFixedPoint Points = {read=FPoints, write=FPoints};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall PolylineTS(G32::TBitmap32* Bitmap, const G32::TArrayOfFixedPoint Points
	, G32::TColor32 Color, bool Closed);
extern PACKAGE void __fastcall PolylineAS(G32::TBitmap32* Bitmap, const G32::TArrayOfFixedPoint Points
	, G32::TColor32 Color, bool Closed);
extern PACKAGE void __fastcall PolylineXS(G32::TBitmap32* Bitmap, const G32::TArrayOfFixedPoint Points
	, G32::TColor32 Color, bool Closed);
extern PACKAGE void __fastcall PolyPolylineTS(G32::TBitmap32* Bitmap, const G32::TArrayOfArrayOfFixedPoint 
	Points, G32::TColor32 Color, bool Closed);
extern PACKAGE void __fastcall PolyPolylineAS(G32::TBitmap32* Bitmap, const G32::TArrayOfArrayOfFixedPoint 
	Points, G32::TColor32 Color, bool Closed);
extern PACKAGE void __fastcall PolyPolylineXS(G32::TBitmap32* Bitmap, const G32::TArrayOfArrayOfFixedPoint 
	Points, G32::TColor32 Color, bool Closed);
extern PACKAGE void __fastcall PolygonTS(G32::TBitmap32* Bitmap, const G32::TArrayOfFixedPoint Points
	, G32::TColor32 Color, TPolyFillMode Mode);
extern PACKAGE void __fastcall PolygonXS(G32::TBitmap32* Bitmap, const G32::TArrayOfFixedPoint Points
	, G32::TColor32 Color, TPolyFillMode Mode);
extern PACKAGE void __fastcall PolyPolygonTS(G32::TBitmap32* Bitmap, const G32::TArrayOfArrayOfFixedPoint 
	Points, G32::TColor32 Color, TPolyFillMode Mode);
extern PACKAGE void __fastcall PolyPolygonXS(G32::TBitmap32* Bitmap, const G32::TArrayOfArrayOfFixedPoint 
	Points, G32::TColor32 Color, TPolyFillMode Mode);

}	/* namespace G32_polygons */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace G32_polygons;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// G32_Polygons
