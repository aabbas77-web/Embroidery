// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrSlideShow.pas' rev: 5.00

#ifndef VrSlideShowHPP
#define VrSlideShowHPP

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

namespace Vrslideshow
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrTransitionEffect { StretchFromLeft, StretchFromRight, StretchFromTop, StretchFromBottom, StretchFromTopLeft, 
	StretchFromBottomRight, StretchFromXcenter, StretchFromYcenter, PushFromBottom, PushFromLeft, PushFromRight, 
	PushFromTop, SlideFromLeft, SlideFromRight, SlideFromTop, SlideFromBottom, SlideFromTopLeft, SlideFromBottomRight, 
	Zoom };
#pragma option pop

class DELPHICLASS TVrSlideShow;
class PASCALIMPLEMENTATION TVrSlideShow : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	bool FActive;
	Graphics::TBitmap* FImageOrg;
	Graphics::TBitmap* FImageNew;
	int FCurrentStep;
	int FSteps;
	bool FLoop;
	TVrTransitionEffect FTransition;
	bool FAnimateInit;
	Vrthreads::TVrTimer* FTimer;
	bool FThreaded;
	Classes::TNotifyEvent FOnNotify;
	double sglGrowX;
	double sglGrowY;
	int __fastcall GetInterval(void);
	void __fastcall SetActive(bool Value);
	void __fastcall SetInterval(int Value);
	void __fastcall SetImageOrg(Graphics::TBitmap* Value);
	void __fastcall SetImageNew(Graphics::TBitmap* Value);
	void __fastcall SetSteps(int Value);
	void __fastcall SetTransition(TVrTransitionEffect Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall TimerEvent(System::TObject* Sender);
	void __fastcall ImageChanged(System::TObject* Sender);
	
protected:
	void __fastcall CalcViewParams(void);
	virtual void __fastcall Paint(void);
	void __fastcall Step(void);
	
public:
	__fastcall virtual ~TVrSlideShow(void);
	__fastcall virtual TVrSlideShow(Classes::TComponent* AOwner);
	void __fastcall ExchangeImages(bool DoPaint);
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property int Interval = {read=GetInterval, write=SetInterval, nodefault};
	__property Graphics::TBitmap* ImageOrg = {read=FImageOrg, write=SetImageOrg};
	__property Graphics::TBitmap* ImageNew = {read=FImageNew, write=SetImageNew};
	__property int Steps = {read=FSteps, write=SetSteps, default=10};
	__property TVrTransitionEffect Transition = {read=FTransition, write=SetTransition, nodefault};
	__property bool Loop = {read=FLoop, write=FLoop, default=1};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property Classes::TNotifyEvent OnNotify = {read=FOnNotify, write=FOnNotify};
	__property Anchors ;
	__property Constraints ;
	__property Align ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Hint ;
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

}	/* namespace Vrslideshow */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrslideshow;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrSlideShow
