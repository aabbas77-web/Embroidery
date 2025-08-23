// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrBlotter.pas' rev: 5.00

#ifndef VrBlotterHPP
#define VrBlotterHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
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

namespace Vrblotter
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TCustomVrBlotter;
class PASCALIMPLEMENTATION TCustomVrBlotter : public Vrcontrols::TVrCustomControl 
{
	typedef Vrcontrols::TVrCustomControl inherited;
	
private:
	bool FAutoSizeDocking;
	Vrclasses::TVrBevel* FBevel;
	bool FFullRepaint;
	bool FLocked;
	Graphics::TBitmap* FGlyph;
	void __fastcall SetGlyph(Graphics::TBitmap* Value);
	void __fastcall BevelChanged(System::TObject* Sender);
	void __fastcall GlyphChanged(System::TObject* Sender);
	MESSAGE void __fastcall CMIsToolControl(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMWindowPosChanged(Messages::TWMWindowPosMsg &Message);
	HIDESBASE MESSAGE void __fastcall CMDockClient(Controls::TCMDockClient &Message);
	
protected:
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual bool __fastcall CanAutoSize(int &NewWidth, int &NewHeight);
	virtual void __fastcall AdjustClientRect(Windows::TRect &Rect);
	virtual void __fastcall Paint(void);
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=FBevel};
	__property Color ;
	__property bool FullRepaint = {read=FFullRepaint, write=FFullRepaint, default=1};
	__property bool Locked = {read=FLocked, write=FLocked, default=0};
	__property ParentColor ;
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	
public:
	__fastcall virtual TCustomVrBlotter(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomVrBlotter(void);
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TCustomVrBlotter(HWND ParentWindow) : Vrcontrols::TVrCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TVrBlotter;
class PASCALIMPLEMENTATION TVrBlotter : public TCustomVrBlotter 
{
	typedef TCustomVrBlotter inherited;
	
public:
	__property DockManager ;
	
__published:
	__property Align ;
	__property Anchors ;
	__property AutoSize ;
	__property Bevel ;
	__property Glyph ;
	__property Color ;
	__property Constraints ;
	__property Ctl3D ;
	__property UseDockManager ;
	__property DockSite ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property FullRepaint ;
	__property Locked ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnCanResize ;
	__property OnClick ;
	__property OnConstrainedResize ;
	__property OnContextPopup ;
	__property OnDockDrop ;
	__property OnDockOver ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnGetSiteInfo ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnResize ;
	__property OnStartDock ;
	__property OnStartDrag ;
	__property OnUnDock ;
public:
	#pragma option push -w-inl
	/* TCustomVrBlotter.Create */ inline __fastcall virtual TVrBlotter(Classes::TComponent* AOwner) : TCustomVrBlotter(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomVrBlotter.Destroy */ inline __fastcall virtual ~TVrBlotter(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrBlotter(HWND ParentWindow) : TCustomVrBlotter(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrblotter */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrblotter;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrBlotter
