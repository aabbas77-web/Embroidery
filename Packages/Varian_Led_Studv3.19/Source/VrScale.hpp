// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrScale.pas' rev: 5.00

#ifndef VrScaleHPP
#define VrScaleHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrscale
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrScale;
class PASCALIMPLEMENTATION TVrScale : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FMin;
	int FMax;
	int FTicks;
	Vrtypes::TVrOrientation FOrientation;
	int FDigits;
	bool FLeadingZero;
	Classes::TAlignment FAlignment;
	Stdctrls::TTextLayout FLayOut;
	Graphics::TColor FScaleColor;
	int FPeakLevel;
	Graphics::TColor FPeakColor;
	bool FShowSign;
	Vrtypes::TVrTickMarks FTickMarks;
	int FScaleOffset;
	int FItemSize;
	int FIncrement;
	void __fastcall SetMin(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetTicks(int Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetLeadingZero(bool Value);
	void __fastcall SetDigits(int Value);
	void __fastcall SetAlignment(Classes::TAlignment Value);
	void __fastcall SetScaleColor(Graphics::TColor Value);
	void __fastcall SetScaleOffset(int Value);
	void __fastcall SetPeakLevel(int Value);
	void __fastcall SetPeakColor(Graphics::TColor Value);
	void __fastcall SetLayout(Stdctrls::TTextLayout Value);
	void __fastcall SetShowSign(bool Value);
	void __fastcall SetTickMarks(Vrtypes::TVrTickMarks Value);
	void __fastcall ShowText(const AnsiString S, const Windows::TRect &R);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	
protected:
	void __fastcall DrawHori(void);
	void __fastcall DrawVert(void);
	virtual void __fastcall Paint(void);
	void __fastcall CalcPaintParams(void);
	AnsiString __fastcall FormatValue(int Value);
	
public:
	__fastcall virtual TVrScale(Classes::TComponent* AOwner);
	
__published:
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Ticks = {read=FTicks, write=SetTicks, default=5};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property bool LeadingZero = {read=FLeadingZero, write=SetLeadingZero, default=0};
	__property int Digits = {read=FDigits, write=SetDigits, default=3};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=2};
	__property Stdctrls::TTextLayout Layout = {read=FLayOut, write=SetLayout, default=1};
	__property Graphics::TColor ScaleColor = {read=FScaleColor, write=SetScaleColor, default=32768};
	__property int PeakLevel = {read=FPeakLevel, write=SetPeakLevel, default=80};
	__property Graphics::TColor PeakColor = {read=FPeakColor, write=SetPeakColor, default=65280};
	__property bool ShowSign = {read=FShowSign, write=SetShowSign, default=1};
	__property Vrtypes::TVrTickMarks TickMarks = {read=FTickMarks, write=SetTickMarks, default=0};
	__property int ScaleOffset = {read=FScaleOffset, write=SetScaleOffset, default=4};
	__property Transparent ;
	__property Color ;
	__property ParentColor ;
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Font ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TVrGraphicImageControl.Destroy */ inline __fastcall virtual ~TVrScale(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrscale */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrscale;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrScale
