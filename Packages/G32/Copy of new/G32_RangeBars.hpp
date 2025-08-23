// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'G32_RangeBars.pas' rev: 5.00

#ifndef G32_RangeBarsHPP
#define G32_RangeBarsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
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

namespace G32_rangebars
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TRBDirection { drLeft, drUp, drRight, drDown };
#pragma option pop

#pragma option push -b-
enum TRBMouseInfo { miNone, miBtnLeft, miBtnRight, miHandle, miLeftSp, miRightSp };
#pragma option pop

#pragma option push -b-
enum TRBBackgnd { bgPattern, bgSolid, bgMix };
#pragma option pop

typedef void __fastcall (__closure *TRBGetSizeEvent)(System::TObject* Sender, int &Size);

class DELPHICLASS TArrowBar;
class PASCALIMPLEMENTATION TArrowBar : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	TRBBackgnd FBackgnd;
	Forms::TFormBorderStyle FBorderStyle;
	int FButtonSize;
	bool FFramed;
	Graphics::TBitmap* FGlyphMax;
	Graphics::TBitmap* FGlyphMin;
	Graphics::TColor FHandleColor;
	Forms::TScrollBarKind FKind;
	bool FShowArrows;
	bool FShowHandleGrip;
	Classes::TNotifyEvent FOnChange;
	Classes::TNotifyEvent FOnUserChange;
	HIDESBASE MESSAGE void __fastcall CMColorChanged(Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Msg);
	void __fastcall SetBackgnd(TRBBackgnd Value);
	void __fastcall SetButtonSize(int Value);
	void __fastcall SetBorderStyle(Forms::TBorderStyle Value);
	void __fastcall SetFramed(bool Value);
	void __fastcall SetGlyphMax(Graphics::TBitmap* Value);
	void __fastcall SetGlyphMin(Graphics::TBitmap* Value);
	void __fastcall SetHandleColor(Graphics::TColor Value);
	void __fastcall SetKind(Forms::TScrollBarKind Value);
	void __fastcall SetShowArrows(bool Value);
	void __fastcall SetShowHandleGrip(bool Value);
	
protected:
	bool GenChange;
	TRBMouseInfo MouseInfo;
	Graphics::TBitmap* Pattern;
	Extctrls::TTimer* Timer;
	bool TimerFirst;
	int StoredX;
	int StoredY;
	float PosBeforeDrag;
	virtual void __fastcall DoChange(void);
	virtual void __fastcall DoDrawButton(const Windows::TRect &R, bool Pushed, TRBDirection Direction, 
		bool Enabled);
	virtual void __fastcall DoRebuildPattern(void);
	int __fastcall GetButtonSize(void);
	Windows::TRect __fastcall GetClientBoundary();
	HIDESBASE virtual bool __fastcall GetEnabled(void);
	virtual TRBMouseInfo __fastcall GetMouseInfo(int X, int Y);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	virtual void __fastcall TimerHandler(System::TObject* Sender);
	
public:
	__fastcall virtual TArrowBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TArrowBar(void);
	virtual void __fastcall Paint(void);
	__property Color ;
	__property TRBBackgnd Backgnd = {read=FBackgnd, write=SetBackgnd, default=0};
	__property Forms::TBorderStyle BorderStyle = {read=FBorderStyle, write=SetBorderStyle, default=0};
	__property int ButtonSize = {read=FButtonSize, write=SetButtonSize, default=0};
	__property bool Framed = {read=FFramed, write=SetFramed, default=1};
	__property Graphics::TBitmap* GlyphMin = {read=FGlyphMin, write=SetGlyphMin};
	__property Graphics::TBitmap* GlyphMax = {read=FGlyphMax, write=SetGlyphMax};
	__property Graphics::TColor HandleColor = {read=FHandleColor, write=SetHandleColor, default=-2147483632
		};
	__property Forms::TScrollBarKind Kind = {read=FKind, write=SetKind, default=0};
	__property bool ShowArrows = {read=FShowArrows, write=SetShowArrows, default=1};
	__property bool ShowHandleGrip = {read=FShowHandleGrip, write=SetShowHandleGrip, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnUserChange = {read=FOnUserChange, write=FOnUserChange};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TArrowBar(HWND ParentWindow) : Controls::TCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TCustomRangeBar;
class PASCALIMPLEMENTATION TCustomRangeBar : public TArrowBar 
{
	typedef TArrowBar inherited;
	
private:
	bool FCentered;
	float FIncrement;
	float FPosition;
	float FRange;
	float FWindow;
	bool __fastcall IsIncrementStored(void);
	bool __fastcall IsPositionStored(void);
	bool __fastcall IsRangeStored(void);
	bool __fastcall IsWindowStored(void);
	void __fastcall SetIncrement(float Value);
	void __fastcall SetPosition(float Value);
	void __fastcall SetRange(float Value);
	void __fastcall SetWindow(float Value);
	
protected:
	float OldSize;
	void __fastcall AdjustPosition(void);
	virtual void __fastcall DoDrawHandle(const Windows::TRect &R, bool Pushed, bool IsHorz);
	virtual float __fastcall DoGetWindowSize(void);
	virtual bool __fastcall GetEnabled(void);
	Windows::TRect __fastcall GetHandleRect();
	virtual TRBMouseInfo __fastcall GetMouseInfo(int X, int Y);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall TimerHandler(System::TObject* Sender);
	
public:
	__fastcall virtual TCustomRangeBar(Classes::TComponent* AOwner);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Resize(void);
	void __fastcall SetParams(float NewRange, float NewWindow);
	__property bool Centered = {read=FCentered, write=FCentered, nodefault};
	__property float Increment = {read=FIncrement, write=SetIncrement, stored=IsIncrementStored};
	__property float Position = {read=FPosition, write=SetPosition, stored=IsPositionStored};
	__property float Range = {read=FRange, write=SetRange, stored=IsRangeStored};
	__property float Window = {read=FWindow, write=SetWindow, stored=IsWindowStored};
public:
	#pragma option push -w-inl
	/* TArrowBar.Destroy */ inline __fastcall virtual ~TCustomRangeBar(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TCustomRangeBar(HWND ParentWindow) : TArrowBar(ParentWindow
		) { }
	#pragma option pop
	
};


class DELPHICLASS TRangeBar;
class PASCALIMPLEMENTATION TRangeBar : public TCustomRangeBar 
{
	typedef TCustomRangeBar inherited;
	
__published:
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property Backgnd ;
	__property BorderStyle ;
	__property ButtonSize ;
	__property Enabled ;
	__property Framed ;
	__property GlyphMax ;
	__property GlyphMin ;
	__property HandleColor ;
	__property Increment ;
	__property Kind ;
	__property Range ;
	__property Visible ;
	__property Window ;
	__property ShowArrows ;
	__property ShowHandleGrip ;
	__property Position ;
	__property OnChange ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;
	__property OnUserChange ;
public:
	#pragma option push -w-inl
	/* TCustomRangeBar.Create */ inline __fastcall virtual TRangeBar(Classes::TComponent* AOwner) : TCustomRangeBar(
		AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TArrowBar.Destroy */ inline __fastcall virtual ~TRangeBar(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TRangeBar(HWND ParentWindow) : TCustomRangeBar(ParentWindow
		) { }
	#pragma option pop
	
};


class DELPHICLASS TCustomGaugeBar;
class PASCALIMPLEMENTATION TCustomGaugeBar : public TArrowBar 
{
	typedef TArrowBar inherited;
	
private:
	int FHandleSize;
	int FLargeChange;
	int FMax;
	int FMin;
	int FPosition;
	int FSmallChange;
	void __fastcall SetHandleSize(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetMin(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetLargeChange(int Value);
	void __fastcall SetSmallChange(int Value);
	
protected:
	void __fastcall AdjustPosition(void);
	Windows::TRect __fastcall GetHandleRect();
	int __fastcall GetHandleSize(void);
	virtual TRBMouseInfo __fastcall GetMouseInfo(int X, int Y);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall TimerHandler(System::TObject* Sender);
	
public:
	__fastcall virtual TCustomGaugeBar(Classes::TComponent* AOwner);
	virtual void __fastcall Paint(void);
	__property int HandleSize = {read=FHandleSize, write=SetHandleSize, default=0};
	__property int LargeChange = {read=FLargeChange, write=SetLargeChange, default=1};
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, nodefault};
	__property int SmallChange = {read=FSmallChange, write=SetSmallChange, default=1};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property OnUserChange ;
public:
	#pragma option push -w-inl
	/* TArrowBar.Destroy */ inline __fastcall virtual ~TCustomGaugeBar(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TCustomGaugeBar(HWND ParentWindow) : TArrowBar(ParentWindow
		) { }
	#pragma option pop
	
};


class DELPHICLASS TGaugeBar;
class PASCALIMPLEMENTATION TGaugeBar : public TCustomGaugeBar 
{
	typedef TCustomGaugeBar inherited;
	
__published:
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property Backgnd ;
	__property BorderStyle ;
	__property ButtonSize ;
	__property Enabled ;
	__property Framed ;
	__property GlyphMax ;
	__property GlyphMin ;
	__property HandleColor ;
	__property HandleSize ;
	__property Kind ;
	__property LargeChange ;
	__property Max ;
	__property Min ;
	__property ShowArrows ;
	__property ShowHandleGrip ;
	__property SmallChange ;
	__property Visible ;
	__property Position ;
	__property OnChange ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;
	__property OnUserChange ;
public:
	#pragma option push -w-inl
	/* TCustomGaugeBar.Create */ inline __fastcall virtual TGaugeBar(Classes::TComponent* AOwner) : TCustomGaugeBar(
		AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TArrowBar.Destroy */ inline __fastcall virtual ~TGaugeBar(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TGaugeBar(HWND ParentWindow) : TCustomGaugeBar(ParentWindow
		) { }
	#pragma option pop
	
};


class DELPHICLASS TArrowBarAccess;
class PASCALIMPLEMENTATION TArrowBarAccess : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TArrowBar* FMaster;
	TArrowBar* FSlave;
	TRBBackgnd __fastcall GetBackgnd(void);
	Forms::TBorderStyle __fastcall GetBorderStyle(void);
	int __fastcall GetButtonSize(void);
	Graphics::TColor __fastcall GetColor(void);
	bool __fastcall GetFramed(void);
	Graphics::TColor __fastcall GetHandleColor(void);
	bool __fastcall GetShowArrows(void);
	bool __fastcall GetShowHandleGrip(void);
	void __fastcall SetBackgnd(TRBBackgnd Value);
	void __fastcall SetBorderStyle(Forms::TBorderStyle Value);
	void __fastcall SetButtonSize(int Value);
	void __fastcall SetColor(Graphics::TColor Value);
	void __fastcall SetFramed(bool Value);
	void __fastcall SetHandleColor(Graphics::TColor Value);
	void __fastcall SetShowArrows(bool Value);
	void __fastcall SetShowHandleGrip(bool Value);
	
public:
	__property TArrowBar* Master = {read=FMaster, write=FMaster};
	__property TArrowBar* Slave = {read=FSlave, write=FSlave};
	
__published:
	__property Graphics::TColor Color = {read=GetColor, write=SetColor, nodefault};
	__property TRBBackgnd Backgnd = {read=GetBackgnd, write=SetBackgnd, default=0};
	__property Forms::TBorderStyle BorderStyle = {read=GetBorderStyle, write=SetBorderStyle, default=0}
		;
	__property int ButtonSize = {read=GetButtonSize, write=SetButtonSize, default=0};
	__property bool Framed = {read=GetFramed, write=SetFramed, default=1};
	__property Graphics::TColor HandleColor = {read=GetHandleColor, write=SetHandleColor, default=-2147483632
		};
	__property bool ShowArrows = {read=GetShowArrows, write=SetShowArrows, default=1};
	__property bool ShowHandleGrip = {read=GetShowHandleGrip, write=SetShowHandleGrip, nodefault};
public:
		
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TArrowBarAccess(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TArrowBarAccess(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace G32_rangebars */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace G32_rangebars;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// G32_RangeBars
