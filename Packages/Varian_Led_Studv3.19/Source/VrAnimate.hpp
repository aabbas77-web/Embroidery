// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrAnimate.pas' rev: 5.00

#ifndef VrAnimateHPP
#define VrAnimateHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
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

namespace Vranimate
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrAnimate;
class PASCALIMPLEMENTATION TVrAnimate : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	bool FAutoSize;
	bool FStretch;
	Graphics::TBitmap* FBitmap;
	int FFrameCount;
	Vrthreads::TVrTimer* FTimer;
	bool FLoop;
	bool FActive;
	Vrtypes::TVrOrientation FOrientation;
	int FCurrentFrame;
	bool FThreaded;
	int FImageWidth;
	int FImageHeight;
	Classes::TNotifyEvent FOnNotify;
	int __fastcall GetInterval(void);
	void __fastcall SetInterval(int Value);
	void __fastcall SetBitmap(Graphics::TBitmap* Value);
	void __fastcall SetActive(bool Value);
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetStretch(bool Value);
	void __fastcall SetFrameCount(int Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetCurrentFrame(int Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall UpdateImage(void);
	void __fastcall BitmapChanged(System::TObject* Sender);
	void __fastcall TimerEvent(System::TObject* Sender);
	
protected:
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	virtual void __fastcall Loaded(void);
	void __fastcall AdjustBounds(void);
	virtual void __fastcall Paint(void);
	Windows::TRect __fastcall DestRect();
	Windows::TRect __fastcall GetImageRect(int Index);
	
public:
	__fastcall virtual TVrAnimate(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrAnimate(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	__property int CurrentFrame = {read=FCurrentFrame, write=SetCurrentFrame, nodefault};
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property int Interval = {read=GetInterval, write=SetInterval, default=150};
	__property int FrameCount = {read=FFrameCount, write=SetFrameCount, default=1};
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=0};
	__property bool Stretch = {read=FStretch, write=SetStretch, default=0};
	__property Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property bool Loop = {read=FLoop, write=FLoop, default=1};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property Classes::TNotifyEvent OnNotify = {read=FOnNotify, write=FOnNotify};
	__property Transparent ;
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

}	/* namespace Vranimate */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vranimate;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrAnimate
