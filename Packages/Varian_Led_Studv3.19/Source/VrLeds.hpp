// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrLeds.pas' rev: 5.00

#ifndef VrLedsHPP
#define VrLedsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
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

namespace Vrleds
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrLedType { ltRounded, ltRectangle, ltLargeRect };
#pragma option pop

#pragma option push -b-
enum TVrLedDrawStyle { dsDesign, dsCustom };
#pragma option pop

class DELPHICLASS TVrCustomLed;
class PASCALIMPLEMENTATION TVrCustomLed : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	TVrLedType FLedType;
	Vrclasses::TVrPalette* FPalette;
	bool FActive;
	int FSpacing;
	int FMargin;
	Vrtypes::TVrImageTextLayout FLayout;
	Graphics::TBitmap* FGlyphs;
	TVrLedDrawStyle FDrawStyle;
	Classes::TNotifyEvent FOnChange;
	Windows::TRect FImageRect;
	Windows::TRect FTextBounds;
	Graphics::TBitmap* FBitmap;
	void __fastcall SetActive(bool Value);
	void __fastcall SetLedType(TVrLedType Value);
	void __fastcall SetLayout(Vrtypes::TVrImageTextLayout Value);
	void __fastcall SetMargin(int Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetGlyphs(Graphics::TBitmap* Value);
	void __fastcall SetDrawStyle(TVrLedDrawStyle Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall GlyphsChanged(System::TObject* Sender);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall LoadBitmaps(void);
	virtual void __fastcall Paint(void);
	void __fastcall CalcPaintParams(void);
	HIDESBASEDYNAMIC void __fastcall Changed(void);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property TVrLedType LedType = {read=FLedType, write=SetLedType, default=0};
	__property Vrtypes::TVrImageTextLayout Layout = {read=FLayout, write=SetLayout, default=0};
	__property int Margin = {read=FMargin, write=SetMargin, default=-1};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=5};
	__property Graphics::TBitmap* Glyphs = {read=FGlyphs, write=SetGlyphs};
	__property TVrLedDrawStyle DrawStyle = {read=FDrawStyle, write=SetDrawStyle, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
public:
	__fastcall virtual TVrCustomLed(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCustomLed(void);
};


class DELPHICLASS TVrLed;
class PASCALIMPLEMENTATION TVrLed : public TVrCustomLed 
{
	typedef TVrCustomLed inherited;
	
__published:
	__property Active ;
	__property Palette ;
	__property LedType ;
	__property Layout ;
	__property Margin ;
	__property Spacing ;
	__property Transparent ;
	__property DrawStyle ;
	__property Glyphs ;
	__property OnChange ;
	__property Align ;
	__property Anchors ;
	__property BiDiMode ;
	__property Constraints ;
	__property Caption ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Font ;
	__property Hint ;
	__property ParentBiDiMode ;
	__property ParentColor ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
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
	/* TVrCustomLed.Create */ inline __fastcall virtual TVrLed(Classes::TComponent* AOwner) : TVrCustomLed(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TVrCustomLed.Destroy */ inline __fastcall virtual ~TVrLed(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TVrUserLedDrawEvent)(System::TObject* Sender, Graphics::TCanvas* 
	Canvas, const Windows::TRect &Rect);

class DELPHICLASS TVrUserLed;
class PASCALIMPLEMENTATION TVrUserLed : public Vrcontrols::TVrGraphicControl 
{
	typedef Vrcontrols::TVrGraphicControl inherited;
	
private:
	Vrclasses::TVrBevel* FBevel;
	Vrclasses::TVrPalette* FPalette;
	bool FActive;
	Graphics::TColor FOutlineColor;
	int FOutlineWidth;
	Vrtypes::TVrDrawStyle FDrawStyle;
	Classes::TNotifyEvent FOnChange;
	TVrUserLedDrawEvent FOnDraw;
	void __fastcall SetActive(bool Value);
	void __fastcall SetOutlineColor(Graphics::TColor Value);
	void __fastcall SetOutlineWidth(int Value);
	void __fastcall SetDrawStyle(Vrtypes::TVrDrawStyle Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	
protected:
	DYNAMIC void __fastcall Change(void);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrUserLed(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrUserLed(void);
	
__published:
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property Graphics::TColor OutlineColor = {read=FOutlineColor, write=SetOutlineColor, default=0};
	__property int OutlineWidth = {read=FOutlineWidth, write=SetOutlineWidth, default=0};
	__property Vrtypes::TVrDrawStyle DrawStyle = {read=FDrawStyle, write=SetDrawStyle, default=1};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TVrUserLedDrawEvent OnDraw = {read=FOnDraw, write=FOnDraw};
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Hint ;
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
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrleds */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrleds;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrLeds
