// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrRaster.pas' rev: 5.00

#ifndef VrRasterHPP
#define VrRasterHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
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

namespace Vrraster
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrRasterLed;
class PASCALIMPLEMENTATION TVrRasterLed : public Vrclasses::TVrCollectionItem 
{
	typedef Vrclasses::TVrCollectionItem inherited;
	
private:
	bool FActive;
	void __fastcall SetActive(bool Value);
	
public:
	__fastcall virtual TVrRasterLed(Vrclasses::TVrCollection* Collection);
	__property bool Active = {read=FActive, write=SetActive, nodefault};
public:
	#pragma option push -w-inl
	/* TVrCollectionItem.Destroy */ inline __fastcall virtual ~TVrRasterLed(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrRasterLeds;
class DELPHICLASS TVrCustomRaster;
#pragma option push -b-
enum TVrRasterStyle { rsRaised, rsLowered, rsNone, rsFlat };
#pragma option pop

class PASCALIMPLEMENTATION TVrCustomRaster : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Vrtypes::TVrColInt FColumns;
	Vrtypes::TVrRowInt FRows;
	Vrclasses::TVrPalette* FPalette;
	TVrRasterStyle FStyle;
	bool FPlainColors;
	bool FMultiSelect;
	int FSpacing;
	Vrclasses::TVrBevel* FBevel;
	Windows::TRect ViewPort;
	int CellXSize;
	int CellYSize;
	TVrRasterLeds* Collection;
	int __fastcall GetCount(void);
	TVrRasterLed* __fastcall GetItem(int Index);
	void __fastcall SetColumns(Vrtypes::TVrColInt Value);
	void __fastcall SetRows(Vrtypes::TVrRowInt Value);
	void __fastcall SetStyle(TVrRasterStyle Value);
	void __fastcall SetPlainColors(bool Value);
	void __fastcall SetMultiSelect(bool Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	void __fastcall SetActiveState(int Origin, bool State);
	
protected:
	void __fastcall CreateObjects(void);
	void __fastcall GetItemRect(int Index, Windows::TRect &R);
	void __fastcall CalcPaintParams(void);
	void __fastcall UpdateLed(int Index);
	void __fastcall UpdateLeds(void);
	virtual void __fastcall Paint(void);
	__property Vrtypes::TVrColInt Columns = {read=FColumns, write=SetColumns, default=5};
	__property Vrtypes::TVrRowInt Rows = {read=FRows, write=SetRows, default=5};
	__property TVrRasterStyle Style = {read=FStyle, write=SetStyle, default=1};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property bool PlainColors = {read=FPlainColors, write=SetPlainColors, default=1};
	__property bool MultiSelect = {read=FMultiSelect, write=SetMultiSelect, default=1};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=2};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	
public:
	__fastcall virtual TVrCustomRaster(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCustomRaster(void);
	__property int Count = {read=GetCount, nodefault};
	__property TVrRasterLed* Items[int Index] = {read=GetItem};
};


class PASCALIMPLEMENTATION TVrRasterLeds : public Vrclasses::TVrCollection 
{
	typedef Vrclasses::TVrCollection inherited;
	
private:
	TVrCustomRaster* FOwner;
	HIDESBASE TVrRasterLed* __fastcall GetItem(int Index);
	
protected:
	virtual void __fastcall Update(Vrclasses::TVrCollectionItem* Item);
	
public:
	__fastcall TVrRasterLeds(TVrCustomRaster* AOwner);
	__property TVrRasterLed* Items[int Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TVrCollection.Destroy */ inline __fastcall virtual ~TVrRasterLeds(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrRaster;
class PASCALIMPLEMENTATION TVrRaster : public TVrCustomRaster 
{
	typedef TVrCustomRaster inherited;
	
__published:
	__property Columns ;
	__property Rows ;
	__property Style ;
	__property Palette ;
	__property PlainColors ;
	__property MultiSelect ;
	__property Spacing ;
	__property Bevel ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property Cursor ;
	__property DragMode ;
	__property DragKind ;
	__property DragCursor ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property ShowHint ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnDragOver ;
	__property OnDragDrop ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TVrCustomRaster.Create */ inline __fastcall virtual TVrRaster(Classes::TComponent* AOwner) : TVrCustomRaster(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TVrCustomRaster.Destroy */ inline __fastcall virtual ~TVrRaster(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrraster */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrraster;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrRaster
