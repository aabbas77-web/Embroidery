// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrCheckLed.pas' rev: 5.00

#ifndef VrCheckLedHPP
#define VrCheckLedHPP

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

namespace Vrcheckled
{
//-- type declarations -------------------------------------------------------
typedef Shortint TVrCheckInt;

class DELPHICLASS TVrCheckLed;
class PASCALIMPLEMENTATION TVrCheckLed : public Vrcontrols::TVrCustomImageControl 
{
	typedef Vrcontrols::TVrCustomImageControl inherited;
	
private:
	bool FChecked;
	Vrclasses::TVrPalette* FPalette;
	int FSpacing;
	int FMargin;
	Vrtypes::TVrImageTextLayout FLayout;
	TVrCheckInt FCheckWidth;
	TVrCheckInt FCheckHeight;
	Classes::TNotifyEvent FOnChange;
	bool MouseButtonDown;
	Windows::TRect ImageRect;
	Windows::TRect TextBounds;
	bool LastState;
	bool HasMouse;
	bool HasFocus;
	void __fastcall SetCheckWidth(TVrCheckInt Value);
	void __fastcall SetCheckHeight(TVrCheckInt Value);
	void __fastcall SetChecked(bool Value);
	void __fastcall SetLayout(Vrtypes::TVrImageTextLayout Value);
	void __fastcall SetMargin(int Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TMessage &Message);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Messages::TWMKillFocus &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	void __fastcall CalcPaintParams(bool Repaint);
	void __fastcall DrawGlyph(int Index, const Windows::TRect &R, Graphics::TCanvas* ACanvas);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall Keypress(char &Key);
	DYNAMIC void __fastcall Change(void);
	
public:
	__fastcall virtual TVrCheckLed(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCheckLed(void);
	
__published:
	__property TVrCheckInt CheckWidth = {read=FCheckWidth, write=SetCheckWidth, default=20};
	__property TVrCheckInt CheckHeight = {read=FCheckHeight, write=SetCheckHeight, default=13};
	__property bool Checked = {read=FChecked, write=SetChecked, default=0};
	__property Vrtypes::TVrImageTextLayout Layout = {read=FLayout, write=SetLayout, default=0};
	__property int Margin = {read=FMargin, write=SetMargin, default=-1};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=5};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Anchors ;
	__property BiDiMode ;
	__property Constraints ;
	__property Caption ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property Font ;
	__property ParentFont ;
	__property ParentBiDiMode ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopUpMenu ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrCheckLed(HWND ParentWindow) : Vrcontrols::TVrCustomImageControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrcheckled */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrcheckled;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrCheckLed
