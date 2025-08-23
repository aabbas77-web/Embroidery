// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrFormShape.pas' rev: 5.00

#ifndef VrFormShapeHPP
#define VrFormShapeHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
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

namespace Vrformshape
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrRgnData;
class PASCALIMPLEMENTATION TVrRgnData : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FSize;
	_RGNDATA *FBuffer;
	void __fastcall SetSize(int Value);
	
public:
	__fastcall virtual ~TVrRgnData(void);
	__property int Size = {read=FSize, write=SetSize, nodefault};
	__property Windows::PRgnData Buffer = {read=FBuffer, write=FBuffer};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TVrRgnData(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


class DELPHICLASS TVrFormShape;
class PASCALIMPLEMENTATION TVrFormShape : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Graphics::TBitmap* FMask;
	TVrRgnData* FRgnData;
	HRGN FRgn;
	Graphics::TColor __fastcall GetMaskColor(void);
	void __fastcall SetMask(Graphics::TBitmap* Value);
	void __fastcall SetMaskColor(Graphics::TColor Value);
	void __fastcall UpdateMask(void);
	void __fastcall UpdateRegion(void);
	void __fastcall ReadMask(Classes::TStream* Reader);
	void __fastcall WriteMask(Classes::TStream* Writer);
	MESSAGE void __fastcall WMEraseBkgnd(Messages::TWMEraseBkgnd &Message);
	
protected:
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall SetParent(Controls::TWinControl* Value);
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	
public:
	__fastcall virtual TVrFormShape(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrFormShape(void);
	
__published:
	__property Graphics::TBitmap* Mask = {read=FMask, write=SetMask};
	__property Graphics::TColor MaskColor = {read=GetMaskColor, write=SetMaskColor, nodefault};
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Hint ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
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

}	/* namespace Vrformshape */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrformshape;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrFormShape
