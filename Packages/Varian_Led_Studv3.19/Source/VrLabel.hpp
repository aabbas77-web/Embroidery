// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrLabel.pas' rev: 5.00

#ifndef VrLabelHPP
#define VrLabelHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Vrlabel
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrLabelStyle { lsNone, lsRaised, lsLowered, lsShadow };
#pragma option pop

class DELPHICLASS TVrLabel;
class PASCALIMPLEMENTATION TVrLabel : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Classes::TAlignment FAlignment;
	bool FAutoSize;
	Stdctrls::TTextLayout FLayout;
	Graphics::TColor FColorHighlight;
	Graphics::TColor FColorShadow;
	TVrLabelStyle FStyle;
	int FShadowDepth;
	Graphics::TBitmap* FBitmap;
	Vrtypes::TVrTextAngle FAngle;
	double FRad;
	Windows::TPoint FTextSize;
	void __fastcall SetAlignment(Classes::TAlignment Value);
	void __fastcall SetColorHighlight(Graphics::TColor Value);
	void __fastcall SetColorShadow(Graphics::TColor Value);
	void __fastcall SetStyle(TVrLabelStyle Value);
	void __fastcall SetLayout(Stdctrls::TTextLayout Value);
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetShadowDepth(int Value);
	void __fastcall SetBitmap(Graphics::TBitmap* Value);
	void __fastcall SetAngle(Vrtypes::TVrTextAngle Value);
	void __fastcall BitmapChanged(System::TObject* Sender);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	
protected:
	void __fastcall AdjustLabelSize(void);
	void __fastcall GetLayoutCoords(int &X, int &Y);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrLabel(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrLabel(void);
	
__published:
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=2};
	__property Graphics::TColor ColorHighlight = {read=FColorHighlight, write=SetColorHighlight, default=16777215
		};
	__property Graphics::TColor ColorShadow = {read=FColorShadow, write=SetColorShadow, default=8421504
		};
	__property TVrLabelStyle Style = {read=FStyle, write=SetStyle, default=1};
	__property Stdctrls::TTextLayout Layout = {read=FLayout, write=SetLayout, default=1};
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=0};
	__property int ShadowDepth = {read=FShadowDepth, write=SetShadowDepth, default=2};
	__property Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property Vrtypes::TVrTextAngle Angle = {read=FAngle, write=SetAngle, default=0};
	__property Transparent ;
	__property Align ;
	__property Anchors ;
	__property BiDiMode ;
	__property Constraints ;
	__property Color ;
	__property Caption ;
	__property Font ;
	__property DragCursor ;
	__property DragMode ;
	__property DragKind ;
	__property ParentColor ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property ParentBiDiMode ;
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

}	/* namespace Vrlabel */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrlabel;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrLabel
