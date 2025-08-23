// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrLevelBar.pas' rev: 5.00

#ifndef VrLevelBarHPP
#define VrLevelBarHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
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

namespace Vrlevelbar
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrLevelBar;
class PASCALIMPLEMENTATION TVrLevelBar : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FMinValue;
	int FMaxValue;
	int FPosition;
	Vrtypes::TVrPercentInt FPercent1;
	Vrtypes::TVrPercentInt FPercent2;
	Vrclasses::TVrPalette* FPalette1;
	Vrclasses::TVrPalette* FPalette2;
	Vrclasses::TVrPalette* FPalette3;
	Vrclasses::TVrBevel* FBevel;
	Vrtypes::TVrOrientation FOrientation;
	int FSpacing;
	int FTickHeight;
	Vrtypes::TVrProgressStyle FStyle;
	Classes::TNotifyEvent FOnChange;
	Windows::TRect FViewPort;
	int FStep;
	int FTicks;
	int __fastcall GetPercentDone(void);
	void __fastcall SetMinValue(int Value);
	void __fastcall SetMaxValue(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetPalette1(Vrclasses::TVrPalette* Value);
	void __fastcall SetPalette2(Vrclasses::TVrPalette* Value);
	void __fastcall SetPalette3(Vrclasses::TVrPalette* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetTickHeight(int Value);
	void __fastcall SetPercent1(Vrtypes::TVrPercentInt Value);
	void __fastcall SetPercent2(Vrtypes::TVrPercentInt Value);
	void __fastcall SetStyle(Vrtypes::TVrProgressStyle Value);
	void __fastcall DrawHori(void);
	void __fastcall DrawVert(void);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	
protected:
	void __fastcall CalcPaintParams(void);
	virtual void __fastcall Paint(void);
	HIDESBASEDYNAMIC void __fastcall Changed(void);
	
public:
	__fastcall virtual TVrLevelBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrLevelBar(void);
	__property int PercentDone = {read=GetPercentDone, nodefault};
	
__published:
	__property int MaxValue = {read=FMaxValue, write=SetMaxValue, default=100};
	__property int MinValue = {read=FMinValue, write=SetMinValue, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property Vrtypes::TVrPercentInt Percent1 = {read=FPercent1, write=SetPercent1, default=60};
	__property Vrtypes::TVrPercentInt Percent2 = {read=FPercent2, write=SetPercent2, default=25};
	__property Vrclasses::TVrPalette* Palette1 = {read=FPalette1, write=SetPalette1};
	__property Vrclasses::TVrPalette* Palette2 = {read=FPalette2, write=SetPalette2};
	__property Vrclasses::TVrPalette* Palette3 = {read=FPalette3, write=SetPalette3};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=1};
	__property int TickHeight = {read=FTickHeight, write=SetTickHeight, default=1};
	__property Vrtypes::TVrProgressStyle Style = {read=FStyle, write=SetStyle, default=0};
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

}	/* namespace Vrlevelbar */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrlevelbar;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrLevelBar
