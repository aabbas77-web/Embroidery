// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrDesign.pas' rev: 5.00

#ifndef VrDesignHPP
#define VrDesignHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrSystem.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
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

namespace Vrdesign
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrBitmapButton;
class PASCALIMPLEMENTATION TVrBitmapButton : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	bool FAutoSize;
	Graphics::TBitmap* FGlyph;
	Graphics::TBitmap* FMask;
	Vrtypes::TVrNumGlyphs FNumGlyphs;
	int FImageWidth;
	int FImageHeight;
	int FVIndent;
	int FHIndent;
	bool FHasMouse;
	Vrtypes::TVrTransparentMode FTransparentMode;
	bool Down;
	bool Pressed;
	bool __fastcall InControl(int X, int Y);
	void __fastcall SetGlyph(Graphics::TBitmap* Value);
	void __fastcall SetNumGlyphs(Vrtypes::TVrNumGlyphs Value);
	void __fastcall SetVIndent(int Value);
	void __fastcall SetHIndent(int Value);
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetTransparentMode(Vrtypes::TVrTransparentMode Value);
	void __fastcall GlyphChanged(System::TObject* Sender);
	HIDESBASE void __fastcall DoMouseDown(int XPos, int YPos);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	
protected:
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Paint(void);
	void __fastcall AdjustBounds(void);
	void __fastcall AdjustImageSize(void);
	Windows::TRect __fastcall DestRect();
	Windows::TRect __fastcall GetImageRect(int Index);
	Graphics::TColor __fastcall GetTransparentColor(void);
	
public:
	__fastcall virtual TVrBitmapButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrBitmapButton(void);
	
__published:
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property Vrtypes::TVrNumGlyphs NumGlyphs = {read=FNumGlyphs, write=SetNumGlyphs, default=1};
	__property int VIndent = {read=FVIndent, write=SetVIndent, default=2};
	__property int HIndent = {read=FHIndent, write=SetHIndent, default=2};
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=0};
	__property Vrtypes::TVrTransparentMode TransparentMode = {read=FTransparentMode, write=SetTransparentMode
		, default=1};
	__property Transparent ;
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property Hint ;
	__property ParentColor ;
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
};


class DELPHICLASS TVrBitmapImage;
class PASCALIMPLEMENTATION TVrBitmapImage : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	bool FAutoSize;
	bool FCenter;
	bool FStretch;
	int FImageIndex;
	Graphics::TBitmap* FBitmap;
	Vrsystem::TVrBitmapList* FBitmapList;
	Classes::TNotifyEvent FChangeEvent;
	Graphics::TBitmap* __fastcall GetBitmap(void);
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetCenter(bool Value);
	void __fastcall SetStretch(bool Value);
	void __fastcall SetImageIndex(int Value);
	void __fastcall SetBitmapList(Vrsystem::TVrBitmapList* Value);
	void __fastcall BitmapsChanged(System::TObject* Sender);
	
protected:
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	Windows::TRect __fastcall DestRect();
	void __fastcall AdjustBounds(void);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	
public:
	__fastcall virtual TVrBitmapImage(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrBitmapImage(void);
	
__published:
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=0};
	__property bool Center = {read=FCenter, write=SetCenter, default=1};
	__property bool Stretch = {read=FStretch, write=SetStretch, default=0};
	__property int ImageIndex = {read=FImageIndex, write=SetImageIndex, default=-1};
	__property Vrsystem::TVrBitmapList* BitmapList = {read=FBitmapList, write=SetBitmapList};
	__property Transparent ;
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Hint ;
	__property ParentColor ;
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


typedef Shortint TVrCounterDigits;

typedef int TVrCounterValue;

class DELPHICLASS TVrCounter;
class PASCALIMPLEMENTATION TVrCounter : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	TVrCounterValue FValue;
	TVrCounterDigits FDigits;
	bool FAutoSize;
	Graphics::TBitmap* FBitmap;
	int FSpacing;
	Windows::TPoint FDigitSize;
	bool FStretch;
	Classes::TNotifyEvent FOnChange;
	Graphics::TBitmap* FImage;
	void __fastcall SetValue(TVrCounterValue Value);
	void __fastcall SetDigits(TVrCounterDigits Value);
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetBitmap(Graphics::TBitmap* Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetStretch(bool Value);
	void __fastcall BitmapChanged(System::TObject* Sender);
	
protected:
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	void __fastcall CalcPaintParams(void);
	virtual void __fastcall Paint(void);
	HIDESBASE virtual void __fastcall Changed(void);
	
public:
	__fastcall virtual TVrCounter(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCounter(void);
	
__published:
	__property TVrCounterValue Value = {read=FValue, write=SetValue, default=0};
	__property TVrCounterDigits Digits = {read=FDigits, write=SetDigits, default=8};
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=1};
	__property Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=0};
	__property bool Stretch = {read=FStretch, write=SetStretch, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Transparent ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Hint ;
	__property ParentColor ;
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

}	/* namespace Vrdesign */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrdesign;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrDesign
