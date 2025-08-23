// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrGauge.pas' rev: 5.00

#ifndef VrGaugeHPP
#define VrGaugeHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrgauge
{
//-- type declarations -------------------------------------------------------
typedef Graphics::TBitmap* TVrGaugeImages[2];

class DELPHICLASS TVrGauge;
class PASCALIMPLEMENTATION TVrGauge : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FMax;
	int FMin;
	int FPosition;
	Vrtypes::TVrOrientation FOrientation;
	Vrclasses::TVrPalette* FPalette;
	int FTickHeight;
	int FSpacing;
	bool FSolidFill;
	Vrclasses::TVrBevel* FBevel;
	Vrtypes::TVrProgressStyle FStyle;
	bool FActiveClick;
	Classes::TNotifyEvent FOnChange;
	Windows::TRect FViewPort;
	int Step;
	int Ticks;
	Graphics::TBitmap* FImages[2];
	Windows::TPoint OrgSize;
	int __fastcall GetPercentDone(void);
	void __fastcall SetMax(int Value);
	void __fastcall SetMin(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetTickHeight(int Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetSolidFill(bool Value);
	void __fastcall SetStyle(Vrtypes::TVrProgressStyle Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall DrawHori(void);
	void __fastcall DrawVert(void);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	
protected:
	void __fastcall CreateBitmaps(void);
	void __fastcall DestroyBitmaps(void);
	void __fastcall CalcPaintParams(void);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Change(void);
	void __fastcall MoveTo(int X, int Y);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	
public:
	__fastcall virtual TVrGauge(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrGauge(void);
	__property int PercentDone = {read=GetPercentDone, nodefault};
	
__published:
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property int TickHeight = {read=FTickHeight, write=SetTickHeight, default=1};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=1};
	__property bool SolidFill = {read=FSolidFill, write=SetSolidFill, default=0};
	__property Vrtypes::TVrProgressStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property bool ActiveClick = {read=FActiveClick, write=FActiveClick, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
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

}	/* namespace Vrgauge */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrgauge;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrGauge
