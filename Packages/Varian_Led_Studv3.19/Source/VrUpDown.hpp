// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrUpDown.pas' rev: 5.00

#ifndef VrUpDownHPP
#define VrUpDownHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
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

namespace Vrupdown
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrUpDown;
class PASCALIMPLEMENTATION TVrUpDown : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Graphics::TBitmap* FGlyphsUp;
	Graphics::TBitmap* FGlyphsDown;
	Vrtypes::TVrNumGlyphs FNumGlyphs;
	Windows::TPoint FSizeUp;
	Windows::TPoint FSizeDown;
	Vrtypes::TVrOrientation FOrientation;
	bool FRepeatClick;
	Vrtypes::TVrMaxInt FRepeatPause;
	Classes::TNotifyEvent FOnUpClick;
	Classes::TNotifyEvent FOnDownClick;
	int FFocusIndex;
	bool FDown;
	int FDownIndex;
	bool FPressed;
	Vrthreads::TVrTimer* FRepeatTimer;
	void __fastcall SetGlyphsUp(Graphics::TBitmap* Value);
	void __fastcall SetGlyphsDown(Graphics::TBitmap* Value);
	void __fastcall SetNumGlyphs(Vrtypes::TVrNumGlyphs Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall GlyphsChanged(System::TObject* Sender);
	void __fastcall TimerExpired(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	
protected:
	void __fastcall AdjustGlyphs(void);
	virtual void __fastcall Paint(void);
	void __fastcall DrawGlyph(int GlyphIndex, Graphics::TBitmap* Glyphs, const Windows::TPoint &Size);
	virtual void __fastcall LoadBitmaps(void);
	void __fastcall Clicked(void);
	Windows::TRect __fastcall GetGlyphRect(int Index);
	int __fastcall GetGlyphIndex(int X, int Y);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	
public:
	__fastcall virtual TVrUpDown(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrUpDown(void);
	
__published:
	__property Graphics::TBitmap* GlyphsUp = {read=FGlyphsUp, write=SetGlyphsUp};
	__property Graphics::TBitmap* GlyphsDown = {read=FGlyphsDown, write=SetGlyphsDown};
	__property Vrtypes::TVrNumGlyphs NumGlyphs = {read=FNumGlyphs, write=SetNumGlyphs, default=4};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property bool RepeatClick = {read=FRepeatClick, write=FRepeatClick, default=1};
	__property Vrtypes::TVrMaxInt RepeatPause = {read=FRepeatPause, write=FRepeatPause, default=100};
	__property Classes::TNotifyEvent OnUpClick = {read=FOnUpClick, write=FOnUpClick};
	__property Classes::TNotifyEvent OnDownClick = {read=FOnDownClick, write=FOnDownClick};
	__property Transparent ;
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
	__property Visible ;
	__property OnContextPopup ;
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

}	/* namespace Vrupdown */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrupdown;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrUpDown
