// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrHyperLink.pas' rev: 5.00

#ifndef VrHyperLinkHPP
#define VrHyperLinkHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
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

namespace Vrhyperlink
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrHyperLink;
class PASCALIMPLEMENTATION TVrHyperLink : public Vrcontrols::TVrHyperLinkControl 
{
	typedef Vrcontrols::TVrHyperLinkControl inherited;
	
private:
	bool FAutoSize;
	Graphics::TFont* FFontEnter;
	Graphics::TFont* FFontLeave;
	Graphics::TColor FColorEnter;
	Graphics::TColor FColorLeave;
	Vrclasses::TVrTextOutline* FTextOutline;
	Classes::TAlignment FAlignment;
	Windows::TPoint FOrgSize;
	bool FHasMouse;
	bool FUpdateSize;
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetFontEnter(Graphics::TFont* Value);
	void __fastcall SetFontLeave(Graphics::TFont* Value);
	void __fastcall SetColorEnter(Graphics::TColor Value);
	void __fastcall SetColorLeave(Graphics::TColor Value);
	void __fastcall SetTextOutline(Vrclasses::TVrTextOutline* Value);
	void __fastcall SetAlignment(Classes::TAlignment Value);
	HIDESBASE void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall TextOutlineChanged(System::TObject* Sender);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	
protected:
	void __fastcall AdjustClientSize(void);
	virtual void __fastcall MouseEnter(void);
	virtual void __fastcall MouseLeave(void);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrHyperLink(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrHyperLink(void);
	
__published:
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=0};
	__property Graphics::TFont* FontEnter = {read=FFontEnter, write=SetFontEnter};
	__property Graphics::TFont* FontLeave = {read=FFontLeave, write=SetFontLeave};
	__property Graphics::TColor ColorEnter = {read=FColorEnter, write=SetColorEnter, default=16711680};
		
	__property Graphics::TColor ColorLeave = {read=FColorLeave, write=SetColorLeave, default=0};
	__property Vrclasses::TVrTextOutline* TextOutline = {read=FTextOutline, write=SetTextOutline};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=2};
	__property Transparent ;
	__property OnMouseEnter ;
	__property OnMouseLeave ;
	__property Align ;
	__property Anchors ;
	__property BiDiMode ;
	__property Constraints ;
	__property Caption ;
	__property DragCursor ;
	__property DragMode ;
	__property DragKind ;
	__property Enabled ;
	__property ParentShowHint ;
	__property ParentBiDiMode ;
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

}	/* namespace Vrhyperlink */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrhyperlink;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrHyperLink
