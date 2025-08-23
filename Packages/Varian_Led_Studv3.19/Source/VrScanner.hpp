// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrScanner.pas' rev: 5.00

#ifndef VrScannerHPP
#define VrScannerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
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

namespace Vrscanner
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrLedStyle { lsRaised, lsLowered, lsNone, lsFlat };
#pragma option pop

class DELPHICLASS TVrLedGroup;
class PASCALIMPLEMENTATION TVrLedGroup : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FSpacing;
	TVrLedStyle FStyle;
	bool FPlainColors;
	Classes::TNotifyEvent FOnChange;
	Vrclasses::TVrCollection* Collection;
	void __fastcall SetSpacing(int Value);
	void __fastcall SetStyle(TVrLedStyle Value);
	void __fastcall SetPlainColors(bool Value);
	
protected:
	DYNAMIC void __fastcall Change(void);
	
public:
	__fastcall virtual TVrLedGroup(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrLedGroup(void);
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=2};
	__property TVrLedStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property bool PlainColors = {read=FPlainColors, write=SetPlainColors, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


#pragma option push -b-
enum TVrScanDirection { sdBoth, sdLeftRight, sdRightLeft };
#pragma option pop

class DELPHICLASS TVrScannerLed;
class PASCALIMPLEMENTATION TVrScannerLed : public Vrclasses::TVrCollectionItem 
{
	typedef Vrclasses::TVrCollectionItem inherited;
	
private:
	bool FActive;
	void __fastcall SetActive(bool Value);
	
public:
	__fastcall virtual TVrScannerLed(Vrclasses::TVrCollection* Collection);
	__property bool Active = {read=FActive, write=SetActive, nodefault};
public:
	#pragma option push -w-inl
	/* TVrCollectionItem.Destroy */ inline __fastcall virtual ~TVrScannerLed(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrScannerLeds;
class DELPHICLASS TVrScanner;
class PASCALIMPLEMENTATION TVrScanner : public TVrLedGroup 
{
	typedef TVrLedGroup inherited;
	
private:
	int FLeds;
	Vrclasses::TVrPalette* FPalette;
	bool FActive;
	int FPosition;
	TVrScanDirection FDirection;
	bool FThreaded;
	bool ToLeft;
	int PrevPosition;
	Vrthreads::TVrTimer* FTimer;
	int __fastcall GetTimeInterval(void);
	void __fastcall SetLeds(int Value);
	void __fastcall SetActive(bool Value);
	void __fastcall SetTimeInterval(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall TimerEvent(System::TObject* Sender);
	void __fastcall PaletteModified(System::TObject* Sender);
	
protected:
	void __fastcall CreateItems(void);
	void __fastcall UpdateLed(int Index);
	void __fastcall UpdateLeds(void);
	void __fastcall UpdateLedState(void);
	virtual void __fastcall Paint(void);
	void __fastcall GetItemRect(int Index, Windows::TRect &R);
	
public:
	__fastcall virtual TVrScanner(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrScanner(void);
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property int Leds = {read=FLeds, write=SetLeds, default=7};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property TVrScanDirection Direction = {read=FDirection, write=FDirection, default=0};
	__property int TimeInterval = {read=GetTimeInterval, write=SetTimeInterval, default=100};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property Spacing ;
	__property Style ;
	__property PlainColors ;
	__property Transparent ;
	__property OnChange ;
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


class PASCALIMPLEMENTATION TVrScannerLeds : public Vrclasses::TVrCollection 
{
	typedef Vrclasses::TVrCollection inherited;
	
private:
	TVrScanner* FOwner;
	HIDESBASE TVrScannerLed* __fastcall GetItem(int Index);
	
protected:
	virtual void __fastcall Update(Vrclasses::TVrCollectionItem* Item);
	
public:
	__fastcall TVrScannerLeds(TVrScanner* AOwner);
	__property TVrScannerLed* Items[int Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TVrCollection.Destroy */ inline __fastcall virtual ~TVrScannerLeds(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrIndicatorLed;
class PASCALIMPLEMENTATION TVrIndicatorLed : public TVrScannerLed 
{
	typedef TVrScannerLed inherited;
	
private:
	Graphics::TColor FColorLow;
	Graphics::TColor FColorHigh;
	
public:
	__fastcall virtual TVrIndicatorLed(Vrclasses::TVrCollection* Collection);
	__property Graphics::TColor ColorLow = {read=FColorLow, write=FColorLow, nodefault};
	__property Graphics::TColor ColorHigh = {read=FColorHigh, write=FColorHigh, nodefault};
public:
	#pragma option push -w-inl
	/* TVrCollectionItem.Destroy */ inline __fastcall virtual ~TVrIndicatorLed(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrIndicatorLeds;
class DELPHICLASS TVrIndicator;
class PASCALIMPLEMENTATION TVrIndicator : public TVrLedGroup 
{
	typedef TVrLedGroup inherited;
	
private:
	int FPosition;
	int FMax;
	int FMin;
	int FLedsLow;
	int FLedsMedium;
	int FLedsHigh;
	Vrclasses::TVrPalette* FPalette1;
	Vrclasses::TVrPalette* FPalette2;
	Vrclasses::TVrPalette* FPalette3;
	int Leds;
	int __fastcall GetPercentDone(void);
	void __fastcall SetPosition(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetMin(int Value);
	void __fastcall SetLedsLow(int Value);
	void __fastcall SetLedsMedium(int Value);
	void __fastcall SetLedsHigh(int Value);
	void __fastcall SetPalette1(Vrclasses::TVrPalette* Value);
	void __fastcall SetPalette2(Vrclasses::TVrPalette* Value);
	void __fastcall SetPalette3(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	
protected:
	void __fastcall CreateItems(void);
	void __fastcall UpdateLed(int Index);
	void __fastcall UpdateLeds(void);
	void __fastcall UpdatePosition(void);
	virtual void __fastcall Paint(void);
	void __fastcall GetItemRect(int Index, Windows::TRect &R);
	
public:
	__fastcall virtual TVrIndicator(Classes::TComponent* AOwner);
	__property int PercentDone = {read=GetPercentDone, nodefault};
	
__published:
	__property Vrclasses::TVrPalette* Palette1 = {read=FPalette1, write=SetPalette1};
	__property Vrclasses::TVrPalette* Palette2 = {read=FPalette2, write=SetPalette2};
	__property Vrclasses::TVrPalette* Palette3 = {read=FPalette3, write=SetPalette3};
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property int LedsLow = {read=FLedsLow, write=SetLedsLow, default=3};
	__property int LedsMedium = {read=FLedsMedium, write=SetLedsMedium, default=2};
	__property int LedsHigh = {read=FLedsHigh, write=SetLedsHigh, default=2};
	__property Spacing ;
	__property Style ;
	__property PlainColors ;
	__property Transparent ;
	__property OnChange ;
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
public:
	#pragma option push -w-inl
	/* TVrLedGroup.Destroy */ inline __fastcall virtual ~TVrIndicator(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TVrIndicatorLeds : public Vrclasses::TVrCollection 
{
	typedef Vrclasses::TVrCollection inherited;
	
private:
	TVrIndicator* FOwner;
	HIDESBASE TVrIndicatorLed* __fastcall GetItem(int Index);
	
protected:
	virtual void __fastcall Update(Vrclasses::TVrCollectionItem* Item);
	
public:
	__fastcall TVrIndicatorLeds(TVrIndicator* AOwner);
	__property TVrIndicatorLed* Items[int Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TVrCollection.Destroy */ inline __fastcall virtual ~TVrIndicatorLeds(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrscanner */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrscanner;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrScanner
