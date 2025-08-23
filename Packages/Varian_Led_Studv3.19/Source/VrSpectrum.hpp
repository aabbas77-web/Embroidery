// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrSpectrum.pas' rev: 5.00

#ifndef VrSpectrumHPP
#define VrSpectrumHPP

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
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrspectrum
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrSpectrumBar;
class PASCALIMPLEMENTATION TVrSpectrumBar : public Vrclasses::TVrCollectionItem 
{
	typedef Vrclasses::TVrCollectionItem inherited;
	
private:
	int FPosition;
	void __fastcall SetPosition(int Value);
	
public:
	__fastcall virtual TVrSpectrumBar(Vrclasses::TVrCollection* Collection);
	__property int Position = {read=FPosition, write=SetPosition, nodefault};
public:
	#pragma option push -w-inl
	/* TVrCollectionItem.Destroy */ inline __fastcall virtual ~TVrSpectrumBar(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrSpectrumBars;
class DELPHICLASS TVrSpectrum;
class PASCALIMPLEMENTATION TVrSpectrum : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FColumns;
	int FMax;
	int FMin;
	Vrclasses::TVrBevel* FBevel;
	Vrclasses::TVrPalette* FPalette1;
	Vrclasses::TVrPalette* FPalette2;
	Vrclasses::TVrPalette* FPalette3;
	Vrtypes::TVrPercentInt FPercent1;
	Vrtypes::TVrPercentInt FPercent2;
	Graphics::TColor FMarkerColor;
	bool FMarkerVisible;
	bool FBarsVisible;
	int FTickHeight;
	int FSpacing;
	Windows::TRect FViewPort;
	int BarWidth;
	int Ticks;
	TVrSpectrumBars* Collection;
	int __fastcall GetCount(void);
	TVrSpectrumBar* __fastcall GetItem(int Index);
	int __fastcall GetPercentDone(int Position);
	void __fastcall SetColumns(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetMin(int Value);
	void __fastcall SetMarkerColor(Graphics::TColor Value);
	void __fastcall SetMarkerVisible(bool Value);
	void __fastcall SetTickHeight(int Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetPalette1(Vrclasses::TVrPalette* Value);
	void __fastcall SetPalette2(Vrclasses::TVrPalette* Value);
	void __fastcall SetPalette3(Vrclasses::TVrPalette* Value);
	void __fastcall SetPercent1(Vrtypes::TVrPercentInt Value);
	void __fastcall SetPercent2(Vrtypes::TVrPercentInt Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetBarsVisible(bool Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	
protected:
	void __fastcall CreateObjects(void);
	void __fastcall GetItemRect(int Index, Windows::TRect &R);
	void __fastcall UpdateBar(int Index);
	void __fastcall UpdateBars(void);
	virtual void __fastcall Paint(void);
	void __fastcall CalcPaintParams(void);
	
public:
	__fastcall virtual TVrSpectrum(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrSpectrum(void);
	void __fastcall Reset(int Value);
	__property int Count = {read=GetCount, nodefault};
	__property TVrSpectrumBar* Items[int Index] = {read=GetItem};
	
__published:
	__property Vrclasses::TVrPalette* Palette1 = {read=FPalette1, write=SetPalette1};
	__property Vrclasses::TVrPalette* Palette2 = {read=FPalette2, write=SetPalette2};
	__property Vrclasses::TVrPalette* Palette3 = {read=FPalette3, write=SetPalette3};
	__property Vrtypes::TVrPercentInt Percent1 = {read=FPercent1, write=SetPercent1, default=60};
	__property Vrtypes::TVrPercentInt Percent2 = {read=FPercent2, write=SetPercent2, default=25};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property int Columns = {read=FColumns, write=SetColumns, default=24};
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property Graphics::TColor MarkerColor = {read=FMarkerColor, write=SetMarkerColor, default=16777215
		};
	__property bool MarkerVisible = {read=FMarkerVisible, write=SetMarkerVisible, default=1};
	__property int TickHeight = {read=FTickHeight, write=SetTickHeight, default=1};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=1};
	__property bool BarsVisible = {read=FBarsVisible, write=SetBarsVisible, default=1};
	__property Color ;
	__property Anchors ;
	__property Constraints ;
	__property Cursor ;
	__property DragMode ;
	__property DragKind ;
	__property DragCursor ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDragOver ;
	__property OnDragDrop ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
};


class PASCALIMPLEMENTATION TVrSpectrumBars : public Vrclasses::TVrCollection 
{
	typedef Vrclasses::TVrCollection inherited;
	
private:
	TVrSpectrum* FOwner;
	HIDESBASE TVrSpectrumBar* __fastcall GetItem(int Index);
	
protected:
	virtual void __fastcall Update(Vrclasses::TVrCollectionItem* Item);
	
public:
	__fastcall TVrSpectrumBars(TVrSpectrum* AOwner);
	__property TVrSpectrumBar* Items[int Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TVrCollection.Destroy */ inline __fastcall virtual ~TVrSpectrumBars(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrspectrum */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrspectrum;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrSpectrum
