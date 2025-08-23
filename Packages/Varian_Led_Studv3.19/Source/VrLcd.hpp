// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrLcd.pas' rev: 5.00

#ifndef VrLcdHPP
#define VrLcdHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <VrConst.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrlcd
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrNumStyle { ns13x24, ns11x20, ns7x13, ns12x17, ns5x7 };
#pragma option pop

#pragma option push -b-
enum TVrNumAlignment { naLeftJustify, naCenter, naRightJustify };
#pragma option pop

class DELPHICLASS TVrCustomNum;
class PASCALIMPLEMENTATION TVrCustomNum : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FValue;
	int FDigits;
	int FMax;
	int FMin;
	int FSpacing;
	TVrNumStyle FStyle;
	bool FLeadingZero;
	Vrclasses::TVrPalette* FPalette;
	TVrNumAlignment FAlignment;
	bool FZeroBlank;
	bool FAutoSize;
	Classes::TNotifyEvent FOnChange;
	Graphics::TBitmap* Bitmap;
	int ImageWidth;
	int ImageHeight;
	bool BelowZero;
	void __fastcall SetDigits(int Value);
	void __fastcall SetValue(int Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetStyle(TVrNumStyle Value);
	void __fastcall SetLeadingZero(bool Value);
	void __fastcall SetAlignment(TVrNumAlignment Value);
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetMin(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetZeroBlank(bool Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	
protected:
	virtual void __fastcall LoadBitmaps(void);
	void __fastcall DrawNum(int Num, int X, int Y);
	void __fastcall ChangeSize(int NewWidth, int NewHeight);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Change(void);
	DYNAMIC void __fastcall RequestAlign(void);
	__property int Digits = {read=FDigits, write=SetDigits, default=4};
	__property int Value = {read=FValue, write=SetValue, default=0};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=2};
	__property TVrNumStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property bool LeadingZero = {read=FLeadingZero, write=SetLeadingZero, default=0};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property TVrNumAlignment Alignment = {read=FAlignment, write=SetAlignment, default=1};
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=0};
	__property int Max = {read=FMax, write=SetMax, default=9999};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property bool ZeroBlank = {read=FZeroBlank, write=SetZeroBlank, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
public:
	__fastcall virtual TVrCustomNum(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCustomNum(void);
};


class DELPHICLASS TVrNum;
class PASCALIMPLEMENTATION TVrNum : public TVrCustomNum 
{
	typedef TVrCustomNum inherited;
	
__published:
	__property Digits ;
	__property Value ;
	__property Spacing ;
	__property Style ;
	__property LeadingZero ;
	__property Palette ;
	__property Alignment ;
	__property AutoSize ;
	__property Max ;
	__property Min ;
	__property ZeroBlank ;
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
	__property OnChange ;
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
	/* TVrCustomNum.Create */ inline __fastcall virtual TVrNum(Classes::TComponent* AOwner) : TVrCustomNum(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TVrCustomNum.Destroy */ inline __fastcall virtual ~TVrNum(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TVrClockType { ctRealTime, ctElapsed, ctCustom };
#pragma option pop

class DELPHICLASS TVrClock;
class PASCALIMPLEMENTATION TVrClock : public TVrCustomNum 
{
	typedef TVrCustomNum inherited;
	
private:
	Vrtypes::TVrHoursInt FHours;
	Vrtypes::TVrMinutesInt FMinutes;
	Vrtypes::TVrSecondsInt FSeconds;
	TVrClockType FClockType;
	bool FActive;
	bool FShowSeconds;
	bool FBlink;
	bool FBlinkVisible;
	bool FThreaded;
	Vrtypes::TVrHoursChangeEvent FOnHoursChanged;
	Vrtypes::TVrMinutesChangeEvent FOnMinutesChanged;
	Vrtypes::TVrSecondsChangeEvent FOnSecondsChanged;
	Vrthreads::TVrTimer* FTimer;
	System::TDateTime ElapsedTime;
	Graphics::TBitmap* Seperator;
	void __fastcall SetHours(Vrtypes::TVrHoursInt Value);
	void __fastcall SetMinutes(Vrtypes::TVrMinutesInt Value);
	void __fastcall SetSeconds(Vrtypes::TVrSecondsInt Value);
	void __fastcall SetActive(bool Value);
	void __fastcall SetClockType(TVrClockType Value);
	void __fastcall SetShowSeconds(bool Value);
	void __fastcall SetBlink(bool Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall OnTimerEvent(System::TObject* Sender);
	
protected:
	virtual void __fastcall LoadBitmaps(void);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall HoursChanged(void);
	virtual void __fastcall MinutesChanged(void);
	virtual void __fastcall SecondsChanged(void);
	
public:
	__fastcall virtual TVrClock(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrClock(void);
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property Vrtypes::TVrHoursInt Hours = {read=FHours, write=SetHours, default=0};
	__property Vrtypes::TVrMinutesInt Minutes = {read=FMinutes, write=SetMinutes, default=0};
	__property Vrtypes::TVrSecondsInt Seconds = {read=FSeconds, write=SetSeconds, default=0};
	__property TVrClockType ClockType = {read=FClockType, write=SetClockType, default=0};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property bool ShowSeconds = {read=FShowSeconds, write=SetShowSeconds, default=0};
	__property bool Blink = {read=FBlink, write=SetBlink, default=0};
	__property Transparent ;
	__property Vrtypes::TVrHoursChangeEvent OnHoursChanged = {read=FOnHoursChanged, write=FOnHoursChanged
		};
	__property Vrtypes::TVrMinutesChangeEvent OnMinutesChanged = {read=FOnMinutesChanged, write=FOnMinutesChanged
		};
	__property Vrtypes::TVrSecondsChangeEvent OnSecondsChanged = {read=FOnSecondsChanged, write=FOnSecondsChanged
		};
	__property Palette ;
	__property Spacing ;
	__property Style ;
	__property AutoSize ;
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


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrlcd */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrlcd;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrLcd
