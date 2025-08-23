// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrDigit.pas' rev: 5.00

#ifndef VrDigitHPP
#define VrDigitHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrdigit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrDigit;
class PASCALIMPLEMENTATION TVrDigit : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FValue;
	Byte FValueBinary;
	Vrclasses::TVrPalette* FPalette;
	bool FActiveOnly;
	Graphics::TColor FOutlineColor;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetValue(int Value);
	void __fastcall SetValueBinary(Byte Value);
	void __fastcall SetActiveOnly(bool Value);
	void __fastcall SetOutlineColor(Graphics::TColor Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	
protected:
	DYNAMIC void __fastcall Change(void);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrDigit(Classes::TComponent* AOwner);
	
__published:
	__property int Value = {read=FValue, write=SetValue, default=0};
	__property Byte ValueBinary = {read=FValueBinary, write=SetValueBinary, default=125};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property bool ActiveOnly = {read=FActiveOnly, write=SetActiveOnly, default=0};
	__property Transparent ;
	__property Graphics::TColor OutlineColor = {read=FOutlineColor, write=SetOutlineColor, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Align ;
	__property DragCursor ;
	__property Anchors ;
	__property DragKind ;
	__property DragMode ;
	__property Color ;
	__property Constraints ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopUpMenu ;
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
public:
	#pragma option push -w-inl
	/* TVrGraphicImageControl.Destroy */ inline __fastcall virtual ~TVrDigit(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrdigit */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrdigit;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrDigit
