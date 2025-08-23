// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrSwitch.pas' rev: 5.00

#ifndef VrSwitchHPP
#define VrSwitchHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
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

namespace Vrswitch
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrSwitchThumb;
class PASCALIMPLEMENTATION TVrSwitchThumb : public Vrcontrols::TVrCustomThumb 
{
	typedef Vrcontrols::TVrCustomThumb inherited;
	
protected:
	virtual int __fastcall GetImageIndex(void);
	
public:
	__fastcall virtual TVrSwitchThumb(Classes::TComponent* AOwner);
public:
	#pragma option push -w-inl
	/* TVrCustomThumb.Destroy */ inline __fastcall virtual ~TVrSwitchThumb(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TVrSwitchOption { soActiveClick, soMouseClip, soHandPoint };
#pragma option pop

typedef Set<TVrSwitchOption, soActiveClick, soHandPoint>  TVrSwitchOptions;

typedef Shortint TVrSwitchImageRange;

typedef Graphics::TBitmap* TVrSwitchImages[3];

class DELPHICLASS TVrSwitch;
class PASCALIMPLEMENTATION TVrSwitch : public Vrcontrols::TVrCustomControl 
{
	typedef Vrcontrols::TVrCustomControl inherited;
	
private:
	int FOffset;
	int FPositions;
	Vrtypes::TVrOrientation FOrientation;
	Vrclasses::TVrBevel* FBevel;
	Vrtypes::TVrProgressStyle FStyle;
	TVrSwitchOptions FOptions;
	Graphics::TColor FBorderColor;
	Graphics::TColor FFocusColor;
	Classes::TNotifyEvent FOnChange;
	int FHit;
	bool FFocused;
	bool FClipOn;
	Graphics::TBitmap* FDest;
	TVrSwitchThumb* FThumb;
	Graphics::TBitmap* FImages[3];
	Graphics::TBitmap* __fastcall GetImage(int Index);
	int __fastcall GetThumbStates(void);
	void __fastcall SetImage(int Index, Graphics::TBitmap* Value);
	void __fastcall SetThumbStates(int Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetOffset(int Value);
	void __fastcall SetPositions(int Value);
	void __fastcall SetStyle(Vrtypes::TVrProgressStyle Value);
	void __fastcall SetOptions(TVrSwitchOptions Value);
	void __fastcall SetBorderColor(Graphics::TColor Value);
	void __fastcall SetFocusColor(Graphics::TColor Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall BevelChanged(System::TObject* Sender);
	void __fastcall ImageChanged(System::TObject* Sender);
	void __fastcall UpdateThumbGlyph(void);
	void __fastcall AdjustControlSize(void);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Msg);
	HIDESBASE MESSAGE void __fastcall CMFocusChanged(Controls::TCMFocusChanged &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	
protected:
	void __fastcall LoadBitmaps(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Paint(void);
	void __fastcall CalcPaintParams(void);
	DYNAMIC void __fastcall Change(void);
	int __fastcall GetViewPortLength(void);
	int __fastcall GetValueByOffset(int Offset);
	int __fastcall GetOffsetByValue(int Value);
	void __fastcall SetThumbOffset(int Value, bool Update);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	void __fastcall ThumbMove(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	void __fastcall ThumbDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall ThumbUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	
public:
	__fastcall virtual TVrSwitch(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrSwitch(void);
	
__published:
	__property int Positions = {read=FPositions, write=SetPositions, default=4};
	__property int Offset = {read=FOffset, write=SetOffset, default=0};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property Graphics::TBitmap* VThumb = {read=GetImage, write=SetImage, index=0};
	__property Graphics::TBitmap* HThumb = {read=GetImage, write=SetImage, index=1};
	__property Graphics::TBitmap* Glyph = {read=GetImage, write=SetImage, index=2};
	__property int ThumbStates = {read=GetThumbStates, write=SetThumbStates, default=1};
	__property Vrtypes::TVrProgressStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property TVrSwitchOptions Options = {read=FOptions, write=SetOptions, default=7};
	__property Graphics::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=-2147483633
		};
	__property Graphics::TColor FocusColor = {read=FFocusColor, write=SetFocusColor, default=16711680};
		
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property ParentColor ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Taborder ;
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
	/* TWinControl.CreateParented */ inline __fastcall TVrSwitch(HWND ParentWindow) : Vrcontrols::TVrCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrswitch */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrswitch;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrSwitch
