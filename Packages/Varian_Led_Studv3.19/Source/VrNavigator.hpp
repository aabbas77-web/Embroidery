// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrNavigator.pas' rev: 5.00

#ifndef VrNavigatorHPP
#define VrNavigatorHPP

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

namespace Vrnavigator
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrButtonType { btPower, btPlay, btPause, btStop, btPrev, btBack, btStep, btNext, btRecord, btEject 
	};
#pragma option pop

typedef Set<TVrButtonType, btPower, btEject>  TVrButtonSet;

#pragma option push -b-
enum TVrButtonState { mgEnabled, mgDisabled };
#pragma option pop

struct TVrNavButton
{
	bool Visible;
	bool Enabled;
	Graphics::TBitmap* Bitmaps[2];
} ;

class DELPHICLASS TVrMediaButton;
class PASCALIMPLEMENTATION TVrMediaButton : public Vrcontrols::TVrCustomImageControl 
{
	typedef Vrcontrols::TVrCustomImageControl inherited;
	
private:
	TVrButtonType FButtonType;
	Graphics::TColor FFocusColor;
	Graphics::TColor FBorderColor;
	Graphics::TBitmap* Bitmaps[2];
	bool Down;
	bool Pressed;
	Graphics::TColor MaskColor;
	bool HasFocus;
	void __fastcall SetButtonType(TVrButtonType Value);
	void __fastcall SetFocusColor(Graphics::TColor Value);
	void __fastcall SetBorderColor(Graphics::TColor Value);
	HIDESBASE void __fastcall DoMouseDown(int XPos, int YPos);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDblClk(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Messages::TWMKillFocus &Message);
	
protected:
	void __fastcall LoadBitmaps(void);
	void __fastcall DestroyBitmaps(void);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyUp(Word &Key, Classes::TShiftState Shift);
	
public:
	__fastcall virtual TVrMediaButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrMediaButton(void);
	
__published:
	__property TVrButtonType ButtonType = {read=FButtonType, write=SetButtonType, default=2};
	__property Graphics::TColor FocusColor = {read=FFocusColor, write=SetFocusColor, default=16711680};
		
	__property Graphics::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=0};
	__property Anchors ;
	__property Constraints ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrMediaButton(HWND ParentWindow) : Vrcontrols::TVrCustomImageControl(
		ParentWindow) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TVrClickEvent)(System::TObject* Sender, TVrButtonType Button);

class DELPHICLASS TVrNavigator;
class PASCALIMPLEMENTATION TVrNavigator : public Vrcontrols::TVrCustomImageControl 
{
	typedef Vrcontrols::TVrCustomImageControl inherited;
	
private:
	TVrButtonSet FVisibleButtons;
	TVrButtonSet FEnabledButtons;
	Vrclasses::TVrBevel* FBevel;
	Graphics::TColor FFocusColor;
	Graphics::TColor FBorderColor;
	int FSpacing;
	Vrtypes::TVrOrientation FOrientation;
	TVrClickEvent FOnButtonClick;
	Graphics::TBitmap* Bitmap;
	bool Pressed;
	bool Down;
	TVrButtonType CurrentButton;
	Windows::TRect ViewPort;
	int ButtonWidth;
	int ButtonHeight;
	TVrButtonType FocusedButton;
	TVrNavButton Buttons[10];
	int __fastcall VisibleButtonCount(void);
	void __fastcall SetVisibleButtons(TVrButtonSet Value);
	void __fastcall SetEnabledButtons(TVrButtonSet Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetFocusColor(Graphics::TColor Value);
	void __fastcall SetBorderColor(Graphics::TColor Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	HIDESBASE void __fastcall DoMouseDown(int XPos, int YPos);
	void __fastcall BevelChanged(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDblClk(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Messages::TWMKillFocus &Message);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Message);
	
protected:
	void __fastcall DoClick(TVrButtonType Button);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyUp(Word &Key, Classes::TShiftState Shift);
	void __fastcall LoadBitmaps(void);
	void __fastcall DestroyBitmaps(void);
	void __fastcall CalcPaintParams(void);
	void __fastcall GetButtonRect(TVrButtonType Btn, Windows::TRect &R);
	void __fastcall DrawButton(TVrButtonType Btn);
	void __fastcall SetFocusedButton(TVrButtonType Btn);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TVrNavigator(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrNavigator(void);
	DYNAMIC void __fastcall ButtonClick(TVrButtonType Button);
	
__published:
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=1};
	__property Graphics::TColor FocusColor = {read=FFocusColor, write=SetFocusColor, default=16711680};
		
	__property Graphics::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=0};
	__property TVrButtonSet VisibleButtons = {read=FVisibleButtons, write=SetVisibleButtons, default=1023
		};
	__property TVrButtonSet EnabledButtons = {read=FEnabledButtons, write=SetEnabledButtons, default=1023
		};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property TVrClickEvent OnButtonClick = {read=FOnButtonClick, write=FOnButtonClick};
	__property Color ;
	__property Anchors ;
	__property Constraints ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnContextPopup ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrNavigator(HWND ParentWindow) : Vrcontrols::TVrCustomImageControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define DefEnabledButtons (System::Set<TVrButtonType, btPower, btEject> () )
#define DefVisibleButtons (System::Set<TVrButtonType, btPower, btEject> () )

}	/* namespace Vrnavigator */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrnavigator;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrNavigator
