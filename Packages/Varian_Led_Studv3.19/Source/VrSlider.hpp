// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrSlider.pas' rev: 5.00

#ifndef VrSliderHPP
#define VrSliderHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <VrConst.hpp>	// Pascal unit
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

namespace Vrslider
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrSliderThumb;
class PASCALIMPLEMENTATION TVrSliderThumb : public Vrcontrols::TVrCustomThumb 
{
	typedef Vrcontrols::TVrCustomThumb inherited;
	
protected:
	virtual int __fastcall GetImageIndex(void);
	
public:
	__fastcall virtual TVrSliderThumb(Classes::TComponent* AOwner);
public:
	#pragma option push -w-inl
	/* TVrCustomThumb.Destroy */ inline __fastcall virtual ~TVrSliderThumb(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TVrSliderStyle { ssBottomLeft, ssTopRight };
#pragma option pop

#pragma option push -b-
enum TVrSliderOption { soActiveClick, soMouseClip, soHandPoint };
#pragma option pop

typedef Set<TVrSliderOption, soActiveClick, soHandPoint>  TVrSliderOptions;

typedef Shortint TVrSliderImageRange;

typedef Graphics::TBitmap* TVrSliderImages[4];

class DELPHICLASS TVrSlider;
class PASCALIMPLEMENTATION TVrSlider : public Vrcontrols::TVrCustomImageControl 
{
	typedef Vrcontrols::TVrCustomImageControl inherited;
	
private:
	int FMin;
	int FMax;
	int FPosition;
	Graphics::TColor FFocusColor;
	Graphics::TColor FBorderColor;
	Vrtypes::TVrOrientation FOrientation;
	TVrSliderStyle FStyle;
	Vrclasses::TVrPalette* FPalette;
	Vrclasses::TVrBevel* FBevel;
	int FTickHeight;
	int FSpacing;
	bool FSolidFill;
	TVrSliderOptions FOptions;
	Classes::TNotifyEvent FOnChange;
	Windows::TRect FViewPort;
	TVrSliderThumb* FThumb;
	bool FFocused;
	int FKeyIncrement;
	bool FClipOn;
	int FHit;
	int FIndent;
	int FStep;
	int FTicks;
	Graphics::TBitmap* FImages[4];
	int __fastcall Progress(void);
	Graphics::TBitmap* __fastcall GetThumbImage(int Index);
	int __fastcall GetThumbStates(void);
	void __fastcall SetMin(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetBorderColor(Graphics::TColor Value);
	void __fastcall SetFocusColor(Graphics::TColor Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetStyle(const TVrSliderStyle Value);
	void __fastcall SetThumbImage(int Index, Graphics::TBitmap* Value);
	void __fastcall SetTickHeight(int Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetSolidFill(bool Value);
	void __fastcall SetOptions(TVrSliderOptions Value);
	void __fastcall SetThumbStates(int Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall UpdateThumbGlyph(void);
	void __fastcall BevelChanged(System::TObject* Sender);
	void __fastcall ImageChanged(System::TObject* Sender);
	void __fastcall PaletteModified(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall CMFocusChanged(Controls::TCMFocusChanged &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Msg);
	
protected:
	void __fastcall DrawHori(void);
	void __fastcall DrawVert(void);
	virtual void __fastcall Paint(void);
	void __fastcall CalcPaintParams(void);
	DYNAMIC void __fastcall Change(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall LoadBitmaps(void);
	void __fastcall CreateViewPortImages(void);
	int __fastcall GetViewPortLength(void);
	void __fastcall SetThumbOffset(int Value, bool Update);
	int __fastcall GetValueByOffset(int Offset);
	int __fastcall GetOffsetByValue(int Value);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	void __fastcall ThumbMove(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	void __fastcall ThumbDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall ThumbUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	
public:
	__fastcall virtual TVrSlider(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrSlider(void);
	
__published:
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property Graphics::TColor FocusColor = {read=FFocusColor, write=SetFocusColor, default=16711680};
		
	__property Graphics::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=-2147483633
		};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property TVrSliderStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property Graphics::TBitmap* VThumb = {read=GetThumbImage, write=SetThumbImage, index=2};
	__property Graphics::TBitmap* HThumb = {read=GetThumbImage, write=SetThumbImage, index=3};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property bool SolidFill = {read=FSolidFill, write=SetSolidFill, default=0};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=1};
	__property int TickHeight = {read=FTickHeight, write=SetTickHeight, default=1};
	__property TVrSliderOptions Options = {read=FOptions, write=SetOptions, default=7};
	__property int ThumbStates = {read=GetThumbStates, write=SetThumbStates, default=1};
	__property int KeyIncrement = {read=FKeyIncrement, write=FKeyIncrement, default=5};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Anchors ;
	__property Constraints ;
	__property Enabled ;
	__property Color ;
	__property Cursor ;
	__property DragMode ;
	__property DragKind ;
	__property DragCursor ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnKeyDown ;
	__property OnKeyUp ;
	__property OnKeyPress ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnDragDrop ;
	__property OnEndDrag ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrSlider(HWND ParentWindow) : Vrcontrols::TVrCustomImageControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrslider */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrslider;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrSlider
