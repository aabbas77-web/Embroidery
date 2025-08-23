// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrImageLed.pas' rev: 5.00

#ifndef VrImageLedHPP
#define VrImageLedHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
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

namespace Vrimageled
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrImageType { itSound, itCD, itPlug, itMike, itPlayMedia, itSpeaker, itNote, itPlayBack, itFrequency, 
	itRecord, itRewind, itReplay };
#pragma option pop

class DELPHICLASS TVrImageLed;
class PASCALIMPLEMENTATION TVrImageLed : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	bool FActive;
	TVrImageType FImageType;
	Vrclasses::TVrPalette* FPalette;
	bool FBlink;
	bool FInverted;
	bool FThreaded;
	Graphics::TBitmap* Bitmap;
	Vrthreads::TVrTimer* FTimer;
	Classes::TNotifyEvent FOnChange;
	int __fastcall GetTimeInterval(void);
	void __fastcall SetImageType(TVrImageType Value);
	void __fastcall SetActive(bool Value);
	void __fastcall SetTimeInterval(int Value);
	void __fastcall SetBlink(bool Value);
	void __fastcall SetInverted(bool Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall OnTimerEvent(System::TObject* Sender);
	
protected:
	void __fastcall LoadBitmaps(void);
	void __fastcall DestroyBitmaps(void);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Change(void);
	
public:
	__fastcall virtual TVrImageLed(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrImageLed(void);
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property bool Blink = {read=FBlink, write=SetBlink, default=0};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property TVrImageType ImageType = {read=FImageType, write=SetImageType, default=0};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property int TimeInterval = {read=GetTimeInterval, write=SetTimeInterval, default=1000};
	__property bool Inverted = {read=FInverted, write=SetInverted, default=0};
	__property Transparent ;
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
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

}	/* namespace Vrimageled */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrimageled;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrImageLed
