// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrAnalog.pas' rev: 5.00

#ifndef VrAnalogHPP
#define VrAnalogHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vranalog
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrAnalogClock;
class PASCALIMPLEMENTATION TVrAnalogClock : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	bool FActive;
	bool FSecondsIndicator;
	bool FHourMarks;
	Word FHours;
	Word FMinutes;
	Word FSeconds;
	Graphics::TBitmap* FGlyph;
	Graphics::TColor FHandsColor;
	Graphics::TColor FSecHandColor;
	Graphics::TColor FTickColor;
	int FTickWidth;
	Graphics::TColor FTickOutline;
	bool FThreaded;
	Vrtypes::TVrHoursChangeEvent FOnHoursChanged;
	Vrtypes::TVrMinutesChangeEvent FOnMinutesChanged;
	Vrtypes::TVrSecondsChangeEvent FOnSecondsChanged;
	Vrthreads::TVrTimer* FTimer;
	void __fastcall SetActive(bool Value);
	void __fastcall SetSecondsIndicator(bool Value);
	void __fastcall SetHourMarks(bool Value);
	void __fastcall SetGlyph(Graphics::TBitmap* Value);
	void __fastcall SetHandsColor(Graphics::TColor Value);
	void __fastcall SetSecHandColor(Graphics::TColor Value);
	void __fastcall SetTickColor(Graphics::TColor Value);
	void __fastcall SetTickWidth(int Value);
	void __fastcall SetTickOutline(Graphics::TColor Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall DrawHand(int XCenter, int YCenter, int Radius, int BackRadius, double Angle);
	void __fastcall OnTimerEvent(System::TObject* Sender);
	
protected:
	virtual void __fastcall Paint(void);
	virtual void __fastcall HoursChanged(void);
	virtual void __fastcall MinutesChanged(void);
	virtual void __fastcall SecondsChanged(void);
	
public:
	__fastcall virtual TVrAnalogClock(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrAnalogClock(void);
	__property Word Hours = {read=FHours, nodefault};
	__property Word Minutes = {read=FMinutes, nodefault};
	__property Word Seconds = {read=FSeconds, nodefault};
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property bool SecondsIndicator = {read=FSecondsIndicator, write=SetSecondsIndicator, default=1};
	__property bool HourMarks = {read=FHourMarks, write=SetHourMarks, default=1};
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property Graphics::TColor HandsColor = {read=FHandsColor, write=SetHandsColor, default=65280};
	__property Graphics::TColor SecHandColor = {read=FSecHandColor, write=SetSecHandColor, default=65280
		};
	__property Graphics::TColor TickColor = {read=FTickColor, write=SetTickColor, default=65280};
	__property int TickWidth = {read=FTickWidth, write=SetTickWidth, default=2};
	__property Graphics::TColor TickOutline = {read=FTickOutline, write=SetTickOutline, default=32768};
		
	__property Vrtypes::TVrHoursChangeEvent OnHoursChanged = {read=FOnHoursChanged, write=FOnHoursChanged
		};
	__property Vrtypes::TVrMinutesChangeEvent OnMinutesChanged = {read=FOnMinutesChanged, write=FOnMinutesChanged
		};
	__property Vrtypes::TVrSecondsChangeEvent OnSecondsChanged = {read=FOnSecondsChanged, write=FOnSecondsChanged
		};
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


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vranalog */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vranalog;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrAnalog
