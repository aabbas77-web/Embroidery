// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrSysUtils.pas' rev: 5.00

#ifndef VrSysUtilsHPP
#define VrSysUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Forms.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrsysutils
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall SolveForX(int Y, int Z);
extern PACKAGE int __fastcall SolveForY(int X, int Z);
extern PACKAGE void __fastcall FreeObject(System::TObject* AObject);
extern PACKAGE int __fastcall MinIntVal(int X, int Y);
extern PACKAGE int __fastcall MaxIntVal(int X, int Y);
extern PACKAGE bool __fastcall InRange(int Value, int X, int Y);
extern PACKAGE void __fastcall AdjustRange(int &Value, int X, int Y);
extern PACKAGE int __fastcall Percent(int a, int b);
extern PACKAGE int __fastcall WidthOf(const Windows::TRect &R);
extern PACKAGE int __fastcall HeightOf(const Windows::TRect &R);
extern PACKAGE void __fastcall AllocateBitmaps(Graphics::TBitmap* * Items, const int Items_Size);
extern PACKAGE void __fastcall DeallocateBitmaps(Graphics::TBitmap* * Items, const int Items_Size);
extern PACKAGE int __fastcall Color2RGB(Graphics::TColor Color);
extern PACKAGE void __fastcall DrawGradient(Graphics::TCanvas* Canvas, const Windows::TRect &Rect, Graphics::TColor 
	StartColor, Graphics::TColor TargetColor, Vrtypes::TVrOrientation Orientation, int LineWidth);
extern PACKAGE void __fastcall DrawShape(Graphics::TCanvas* Canvas, Vrtypes::TVrShapeType Shape, int 
	X, int Y, int W, int H);
extern PACKAGE void __fastcall CalcTextBounds(Graphics::TCanvas* Canvas, const Windows::TRect &Client
	, Windows::TRect &TextBounds, const AnsiString Caption);
extern PACKAGE void __fastcall DrawButtonText(Graphics::TCanvas* Canvas, const AnsiString Caption, const 
	Windows::TRect &TextBounds, bool Enabled);
extern PACKAGE void __fastcall ClearBitmapCanvas(const Windows::TRect &R, Graphics::TBitmap* Bitmap, 
	Graphics::TColor Color);
extern PACKAGE Graphics::TBitmap* __fastcall CreateDitherPattern(Graphics::TColor Light, Graphics::TColor 
	Face);
extern PACKAGE void __fastcall CalcImageTextLayout(Graphics::TCanvas* Canvas, const Windows::TRect &
	Client, const Windows::TPoint &Offset, const AnsiString Caption, Vrtypes::TVrImageTextLayout Layout
	, int Margin, int Spacing, const Windows::TPoint &ImageSize, Windows::TPoint &ImagePos, Windows::TRect 
	&TextBounds);
extern PACKAGE void __fastcall DrawOutline3D(Graphics::TCanvas* Canvas, Windows::TRect &Rect, Graphics::TColor 
	TopColor, Graphics::TColor BottomColor, int Width);
extern PACKAGE void __fastcall DrawFrame3D(Graphics::TCanvas* Canvas, Windows::TRect &Rect, Graphics::TColor 
	TopColor, Graphics::TColor BottomColor, int Width);
extern PACKAGE void __fastcall CopyParentImage(Controls::TControl* Control, Graphics::TCanvas* Dest)
	;
extern PACKAGE Classes::TComponent* __fastcall GetOwnerControl(Classes::TComponent* Component);
extern PACKAGE void __fastcall SetCanvasTextAngle(Graphics::TCanvas* Canvas, Word Angle);
extern PACKAGE void __fastcall CanvasTextOutAngle(Graphics::TCanvas* Canvas, int X, int Y, Word Angle
	, const AnsiString Text);
extern PACKAGE Windows::TPoint __fastcall GetTextSize(Graphics::TCanvas* Canvas, const AnsiString Text
	);
extern PACKAGE void __fastcall Draw3DText(Graphics::TCanvas* Canvas, int X, int Y, const AnsiString 
	Text, Graphics::TColor HighEdge, Graphics::TColor LowEdge);
extern PACKAGE void __fastcall DrawShadowTextExt(Graphics::TCanvas* Canvas, int X, int Y, const AnsiString 
	Text, Graphics::TColor ShadowColor, int SX, int SY);
extern PACKAGE void __fastcall StretchPaintOnText(Graphics::TCanvas* Dest, const Windows::TRect &DestRect
	, int X, int Y, const AnsiString Text, Graphics::TBitmap* Bitmap, Word Angle);
extern PACKAGE void __fastcall DrawOutlinedText(Graphics::TCanvas* Canvas, int X, int Y, const AnsiString 
	Text, Graphics::TColor Color, int Depth);
extern PACKAGE void __fastcall DrawRasterPattern(Graphics::TCanvas* Canvas, const Windows::TRect &Rect
	, Graphics::TColor ForeColor, Graphics::TColor BackColor, int PixelSize, int Spacing);
extern PACKAGE void __fastcall StretchPaintOnRasterPattern(Graphics::TCanvas* Dest, const Windows::TRect 
	&Rect, Graphics::TBitmap* Image, Graphics::TColor ForeColor, Graphics::TColor BackColor, int PixelSize
	, int Spacing);
extern PACKAGE void __fastcall BitmapToLCD(Graphics::TBitmap* Dest, Graphics::TBitmap* Source, Graphics::TColor 
	ForeColor, Graphics::TColor BackColor, int PixelSize, int Spacing);
extern PACKAGE void __fastcall DrawTiledBitmap(Graphics::TCanvas* Canvas, const Windows::TRect &Rect
	, Graphics::TBitmap* Glyph);
extern PACKAGE Windows::TRect __fastcall BitmapRect(Graphics::TBitmap* Bitmap);
extern PACKAGE void __fastcall ChangeBitmapColor(Graphics::TBitmap* Bitmap, Graphics::TColor FromColor
	, Graphics::TColor ToColor);
extern PACKAGE void __fastcall DrawBitmap(Graphics::TCanvas* Canvas, const Windows::TRect &DestRect, 
	Graphics::TBitmap* Bitmap, const Windows::TRect &SourceRect, bool Transparent, Graphics::TColor TransColor
	);

}	/* namespace Vrsysutils */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrsysutils;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrSysUtils
