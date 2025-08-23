// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrArrow.pas' rev: 5.00

#ifndef VrArrowHPP
#define VrArrowHPP

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

namespace Vrarrow
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrArrowDirection { pdLeft, pdRight, pdUp, pdDown };
#pragma option pop

class DELPHICLASS TVrArrow;
class PASCALIMPLEMENTATION TVrArrow : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	TVrArrowDirection FDirection;
	Vrclasses::TVrPalette* FPalette;
	bool FActive;
	bool FTrackMouse;
	Graphics::TBitmap* Glyphs;
	Graphics::TBitmap* GlyphMask;
	bool HasMouse;
	Windows::TRect __fastcall ImageRect();
	bool __fastcall InControl(int X, int Y);
	void __fastcall SetActive(bool Value);
	void __fastcall SetDirection(TVrArrowDirection Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	
protected:
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall LoadBitmaps(void);
	virtual void __fastcall Paint(void);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	
public:
	__fastcall virtual TVrArrow(Classes::TComponent* Aowner);
	__fastcall virtual ~TVrArrow(void);
	
__published:
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property TVrArrowDirection Direction = {read=FDirection, write=SetDirection, default=2};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property bool TrackMouse = {read=FTrackMouse, write=FTrackMouse, default=0};
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

}	/* namespace Vrarrow */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrarrow;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrArrow
