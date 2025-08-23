// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrBanner.pas' rev: 5.00

#ifndef VrBannerHPP
#define VrBannerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
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

namespace Vrbanner
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrBannerPixelMode { pmAuto, pmCustom };
#pragma option pop

#pragma option push -b-
enum TVrBannerDirection { bdRightToLeft, bdLeftToRight, bdTopToBottom, bdBottomToTop };
#pragma option pop

class DELPHICLASS TVrBanner;
class PASCALIMPLEMENTATION TVrBanner : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Graphics::TBitmap* FBitmap;
	Graphics::TBitmap* FRaster;
	int FPixelSize;
	Graphics::TColor FPixelColor;
	TVrBannerPixelMode FPixelMode;
	int FSpacing;
	int FIncrement;
	bool FAutoScroll;
	Vrclasses::TVrBevel* FBevel;
	TVrBannerDirection FDirection;
	bool FThreaded;
	Classes::TNotifyEvent FOnScrollDone;
	int FDstX;
	int FDstY;
	bool FScrollInit;
	bool Initialized;
	Vrthreads::TVrTimer* FTimer;
	int __fastcall GetTimeInterval(void);
	Graphics::TColor __fastcall GetPixelColor(void);
	void __fastcall SetBitmap(Graphics::TBitmap* Value);
	void __fastcall SetPixelSize(int Value);
	void __fastcall SetPixelColor(Graphics::TColor Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetTimeInterval(int Value);
	void __fastcall SetAutoScroll(bool Value);
	void __fastcall SetPixelMode(TVrBannerPixelMode Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall CreateRasterImage(void);
	void __fastcall TimerEvent(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CMColorChanged(Messages::TMessage &Message);
	
protected:
	void __fastcall Reset(void);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	void __fastcall Notify(void);
	void __fastcall BitmapChanged(System::TObject* Sender);
	int __fastcall StepSize(void);
	
public:
	__fastcall virtual TVrBanner(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrBanner(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property int PixelSize = {read=FPixelSize, write=SetPixelSize, default=2};
	__property Graphics::TColor PixelColor = {read=FPixelColor, write=SetPixelColor, default=8421504};
	__property TVrBannerPixelMode PixelMode = {read=FPixelMode, write=SetPixelMode, default=0};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=1};
	__property int TimeInterval = {read=GetTimeInterval, write=SetTimeInterval, default=50};
	__property bool AutoScroll = {read=FAutoScroll, write=SetAutoScroll, default=0};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property TVrBannerDirection Direction = {read=FDirection, write=FDirection, default=0};
	__property Classes::TNotifyEvent OnScrollDone = {read=FOnScrollDone, write=FOnScrollDone};
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

}	/* namespace Vrbanner */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrbanner;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrBanner
