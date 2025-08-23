// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrJoypad.pas' rev: 5.00

#ifndef VrJoypadHPP
#define VrJoypadHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
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

namespace Vrjoypad
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrJoypadDirection { jdNone, jdUp, jdDown, jdLeft, jdRight };
#pragma option pop

#pragma option push -b-
enum TVrVisibleArrow { vaUp, vaDown, vaLeft, vaRight };
#pragma option pop

typedef Set<TVrVisibleArrow, vaUp, vaRight>  TVrVisibleArrows;

class DELPHICLASS TVrJoypad;
class PASCALIMPLEMENTATION TVrJoypad : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FSpacing;
	TVrJoypadDirection FDirection;
	TVrVisibleArrows FVisibleArrows;
	Vrclasses::TVrPalette* FPalette;
	int ImageWidth;
	int ImageHeight;
	Graphics::TBitmap* Bitmaps[2];
	void __fastcall SetSpacing(int Value);
	void __fastcall SetDirection(TVrJoypadDirection Value);
	void __fastcall SetVisibleArrows(TVrVisibleArrows Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	
protected:
	virtual void __fastcall LoadBitmaps(void);
	void __fastcall DestroyBitmaps(void);
	void __fastcall UpdateLed(TVrVisibleArrow Index, bool Active);
	void __fastcall UpdateLeds(void);
	virtual void __fastcall Paint(void);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	void __fastcall GetImageRect(TVrVisibleArrow Index, Windows::TRect &R);
	
public:
	__fastcall virtual TVrJoypad(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrJoypad(void);
	
__published:
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=4};
	__property TVrJoypadDirection Direction = {read=FDirection, write=SetDirection, default=0};
	__property TVrVisibleArrows VisibleArrows = {read=FVisibleArrows, write=SetVisibleArrows, default=15
		};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property Transparent ;
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
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

}	/* namespace Vrjoypad */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrjoypad;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrJoypad
