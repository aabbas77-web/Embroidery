// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrSpinner.pas' rev: 5.00

#ifndef VrSpinnerHPP
#define VrSpinnerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <ImgList.hpp>	// Pascal unit
#include <Commctrl.hpp>	// Pascal unit
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

namespace Vrspinner
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrSpinButtonType { stUp, stDown, stLeft, stRight };
#pragma option pop

class DELPHICLASS TVrSpinner;
class DELPHICLASS TVrTimerSpinButton;
class DELPHICLASS TVrSpinButton;
class PASCALIMPLEMENTATION TVrSpinButton : public Vrcontrols::TVrGraphicControl 
{
	typedef Vrcontrols::TVrGraphicControl inherited;
	
private:
	TVrSpinButtonType FBtnType;
	Vrclasses::TVrPalette* FPalette;
	Controls::TImageList* ImageList;
	Graphics::TBitmap* Bitmap;
	bool MouseBtnDown;
	void __fastcall SetBtnType(TVrSpinButtonType Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	bool __fastcall InControl(int X, int Y);
	
protected:
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	virtual void __fastcall LoadBitmaps(void);
	Windows::TRect __fastcall ImageRect();
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Click(void);
	void __fastcall DoClick(void);
	__property TVrSpinButtonType BtnType = {read=FBtnType, write=SetBtnType, default=0};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property Color ;
	__property ParentColor ;
	__property Enabled ;
	
public:
	__fastcall virtual TVrSpinButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrSpinButton(void);
};


#pragma option push -b-
enum VrSpinner__3 { tbFocusRect, tbAllowTimer };
#pragma option pop

typedef Set<VrSpinner__3, tbFocusRect, tbAllowTimer>  TTimeBtnState;

class PASCALIMPLEMENTATION TVrTimerSpinButton : public TVrSpinButton 
{
	typedef TVrSpinButton inherited;
	
private:
	Vrthreads::TVrTimer* FRepeatTimer;
	TTimeBtnState FTimeBtnState;
	void __fastcall TimerExpired(System::TObject* Sender);
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	
public:
	__fastcall virtual ~TVrTimerSpinButton(void);
	__property TTimeBtnState TimeBtnState = {read=FTimeBtnState, write=FTimeBtnState, nodefault};
public:
		
	#pragma option push -w-inl
	/* TVrSpinButton.Create */ inline __fastcall virtual TVrTimerSpinButton(Classes::TComponent* AOwner
		) : TVrSpinButton(AOwner) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TVrSpinner : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
private:
	TVrTimerSpinButton* FUpButton;
	TVrTimerSpinButton* FDownButton;
	TVrTimerSpinButton* FFocusedButton;
	Controls::TWinControl* FFocusControl;
	Vrtypes::TVrOrientation FOrientation;
	Vrclasses::TVrPalette* FPalette;
	Classes::TNotifyEvent FOnUpClick;
	Classes::TNotifyEvent FOnDownClick;
	TVrTimerSpinButton* __fastcall CreateButton(TVrSpinButtonType BtnType);
	void __fastcall BtnClick(System::TObject* Sender);
	void __fastcall BtnMouseDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall SetFocusBtn(TVrTimerSpinButton* Btn);
	void __fastcall ChangeSize(int &W, int &H);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Messages::TWMKillFocus &Message);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	
public:
	__fastcall virtual TVrSpinner(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrSpinner(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	
__published:
	__property Controls::TWinControl* FocusControl = {read=FFocusControl, write=FFocusControl};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property Classes::TNotifyEvent OnDownClick = {read=FOnDownClick, write=FOnDownClick};
	__property Classes::TNotifyEvent OnUpClick = {read=FOnUpClick, write=FOnUpClick};
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrSpinner(HWND ParentWindow) : Controls::TWinControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word InitRepeatPause = 0x190;
static const Shortint RepeatPause = 0x64;

}	/* namespace Vrspinner */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrspinner;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrSpinner
