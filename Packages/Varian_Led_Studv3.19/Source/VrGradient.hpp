// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrGradient.pas' rev: 5.00

#ifndef VrGradientHPP
#define VrGradientHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
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

namespace Vrgradient
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrCustomGradient;
class PASCALIMPLEMENTATION TVrCustomGradient : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Graphics::TColor FStartColor;
	Graphics::TColor FEndColor;
	int FColorWidth;
	Vrtypes::TVrOrientation FOrientation;
	bool FFormDrag;
	void __fastcall SetColorWidth(int Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetStartColor(Graphics::TColor Value);
	void __fastcall SetEndColor(Graphics::TColor Value);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Msg);
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	__property int ColorWidth = {read=FColorWidth, write=SetColorWidth, default=1};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property Graphics::TColor StartColor = {read=FStartColor, write=SetStartColor, default=65280};
	__property Graphics::TColor EndColor = {read=FEndColor, write=SetEndColor, default=0};
	__property bool FormDrag = {read=FFormDrag, write=FFormDrag, default=0};
	
public:
	__fastcall virtual TVrCustomGradient(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCustomGradient(void);
};


class DELPHICLASS TVrGradient;
class PASCALIMPLEMENTATION TVrGradient : public TVrCustomGradient 
{
	typedef TVrCustomGradient inherited;
	
__published:
	__property StartColor ;
	__property EndColor ;
	__property ColorWidth ;
	__property Orientation ;
	__property FormDrag ;
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
public:
	#pragma option push -w-inl
	/* TVrCustomGradient.Create */ inline __fastcall virtual TVrGradient(Classes::TComponent* AOwner) : 
		TVrCustomGradient(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TVrCustomGradient.Destroy */ inline __fastcall virtual ~TVrGradient(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrgradient */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrgradient;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrGradient
