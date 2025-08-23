// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrDemoButton.pas' rev: 5.00

#ifndef VrDemoButtonHPP
#define VrDemoButtonHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
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

namespace Vrdemobutton
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrDemoButton;
class PASCALIMPLEMENTATION TVrDemoButton : public Vrcontrols::TVrCustomImageControl 
{
	typedef Vrcontrols::TVrCustomImageControl inherited;
	
private:
	Graphics::TBitmap* FBitmap;
	Graphics::TFont* FFontEnter;
	Graphics::TFont* FFontLeave;
	Vrtypes::TVrByteInt FBevelWidth;
	int FOutlineWidth;
	Graphics::TColor FOutlineColor;
	Graphics::TColor FShadowColor;
	Graphics::TColor FHighlightColor;
	Graphics::TColor FFocusColor;
	Vrtypes::TVrTextAlignment FTextAlignment;
	Graphics::TColor FDisabledTextColor;
	Vrclasses::TVrFont3D* FFont3D;
	bool FHasMouse;
	bool FFocused;
	bool Down;
	bool Pressed;
	void __fastcall SetBitmap(Graphics::TBitmap* Value);
	void __fastcall SetFontEnter(Graphics::TFont* Value);
	void __fastcall SetFontLeave(Graphics::TFont* Value);
	void __fastcall SetOutlineColor(Graphics::TColor Value);
	void __fastcall SetShadowColor(Graphics::TColor Value);
	void __fastcall SetHighlightColor(Graphics::TColor Value);
	HIDESBASE void __fastcall SetBevelWidth(Vrtypes::TVrByteInt Value);
	void __fastcall SetOutlineWidth(int Value);
	void __fastcall SetTextAlignment(Vrtypes::TVrTextAlignment Value);
	void __fastcall SetDisabledTextColor(Graphics::TColor Value);
	void __fastcall SetFocusColor(Graphics::TColor Value);
	void __fastcall SetFont3D(Vrclasses::TVrFont3D* Value);
	HIDESBASE void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall BitmapChanged(System::TObject* Sender);
	HIDESBASE void __fastcall DoMouseDown(int XPos, int YPos);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMDialogChar(Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDblClk(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMFocusChanged(Controls::TCMFocusChanged &Message);
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyUp(Word &Key, Classes::TShiftState Shift);
	
public:
	__fastcall virtual TVrDemoButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrDemoButton(void);
	
__published:
	__property Graphics::TFont* FontEnter = {read=FFontEnter, write=SetFontEnter};
	__property Graphics::TFont* FontLeave = {read=FFontLeave, write=SetFontLeave};
	__property Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property Graphics::TColor OutlineColor = {read=FOutlineColor, write=SetOutlineColor, default=0};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, default=-2147483632
		};
	__property Graphics::TColor HighlightColor = {read=FHighlightColor, write=SetHighlightColor, default=-2147483628
		};
	__property Vrtypes::TVrByteInt BevelWidth = {read=FBevelWidth, write=SetBevelWidth, default=2};
	__property int OutlineWidth = {read=FOutlineWidth, write=SetOutlineWidth, default=1};
	__property Vrtypes::TVrTextAlignment TextAlignment = {read=FTextAlignment, write=SetTextAlignment, 
		default=1};
	__property Graphics::TColor DisabledTextColor = {read=FDisabledTextColor, write=SetDisabledTextColor
		, default=-2147483645};
	__property Graphics::TColor FocusColor = {read=FFocusColor, write=SetFocusColor, default=16711680};
		
	__property Vrclasses::TVrFont3D* Font3D = {read=FFont3D, write=SetFont3D};
	__property Anchors ;
	__property BiDiMode ;
	__property Constraints ;
	__property Caption ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
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
	/* TWinControl.CreateParented */ inline __fastcall TVrDemoButton(HWND ParentWindow) : Vrcontrols::TVrCustomImageControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrdemobutton */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrdemobutton;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrDemoButton
