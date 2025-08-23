// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrCalendar.pas' rev: 5.00

#ifndef VrCalendarHPP
#define VrCalendarHPP

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

namespace Vrcalendar
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrGridStyle { gsRaised, gsLowered, gsSingle };
#pragma option pop

class DELPHICLASS TVrCalendarGrid;
class PASCALIMPLEMENTATION TVrCalendarGrid : public Vrclasses::TVrPersistent 
{
	typedef Vrclasses::TVrPersistent inherited;
	
private:
	TVrGridStyle FStyle;
	Graphics::TColor FColor;
	Graphics::TColor FShadow3D;
	Graphics::TColor FHighlight3D;
	int FWidth;
	void __fastcall SetStyle(TVrGridStyle Value);
	void __fastcall SetColor(Graphics::TColor Value);
	void __fastcall SetShadow3D(Graphics::TColor Value);
	void __fastcall SetHighlight3D(Graphics::TColor Value);
	void __fastcall SetWidth(int Value);
	
public:
	__fastcall TVrCalendarGrid(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	
__published:
	__property TVrGridStyle Style = {read=FStyle, write=SetStyle, nodefault};
	__property Graphics::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property Graphics::TColor Highlight3D = {read=FHighlight3D, write=SetHighlight3D, nodefault};
	__property Graphics::TColor Shadow3D = {read=FShadow3D, write=SetShadow3D, nodefault};
	__property int Width = {read=FWidth, write=SetWidth, nodefault};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrCalendarGrid(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrCalendarItem;
class PASCALIMPLEMENTATION TVrCalendarItem : public Vrclasses::TVrCollectionItem 
{
	typedef Vrclasses::TVrCollectionItem inherited;
	
private:
	AnsiString FCaption;
	bool FActive;
	bool FVisible;
	void __fastcall SetActive(bool Value);
	void __fastcall SetCaption(const AnsiString Value);
	void __fastcall SetVisible(bool Value);
	
public:
	__fastcall virtual TVrCalendarItem(Vrclasses::TVrCollection* Collection);
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
public:
	#pragma option push -w-inl
	/* TVrCollectionItem.Destroy */ inline __fastcall virtual ~TVrCalendarItem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrCalendarItems;
class DELPHICLASS TVrCalendar;
#pragma option push -b-
enum TVrGridAlignment { gaUpperLeft, gaUpperRight, gaBottomLeft, gaBottomRight, gaCenter };
#pragma option pop

typedef void __fastcall (__closure *TVrCalendarDrawEvent)(System::TObject* Sender, Graphics::TCanvas* 
	Canvas, const Windows::TRect &Rect, int Index, bool State);

#pragma option push -b-
enum TVrCalendarOption { coActiveClick, coMouseClip, coTrackMouse };
#pragma option pop

typedef Set<TVrCalendarOption, coActiveClick, coTrackMouse>  TVrCalendarOptions;

class PASCALIMPLEMENTATION TVrCalendar : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Vrtypes::TVrRowInt FRows;
	Vrtypes::TVrColInt FColumns;
	TVrCalendarGrid* FGrid;
	Vrtypes::TVrDrawStyle FDrawStyle;
	TVrGridAlignment FAlignment;
	Vrclasses::TVrPalette* FPalette;
	int FFirstIndex;
	TVrCalendarDrawEvent FOnDraw;
	int FItemIndex;
	int FDigits;
	TVrCalendarOptions FOptions;
	Vrtypes::TVrOrientation FOrientation;
	int FNextStep;
	Vrclasses::TVrBevel* FBevel;
	Windows::TRect ViewPort;
	int SizeX;
	int SizeY;
	bool IsPressed;
	int TrackLast;
	int CurrIndex;
	TVrCalendarItems* Collection;
	void __fastcall SetRows(Vrtypes::TVrRowInt Value);
	void __fastcall SetColumns(Vrtypes::TVrColInt Value);
	void __fastcall SetDrawStyle(Vrtypes::TVrDrawStyle Value);
	void __fastcall SetAlignment(TVrGridAlignment Value);
	void __fastcall SetFirstIndex(int Value);
	void __fastcall SetDigits(int Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetNextStep(int Value);
	void __fastcall SetOptions(TVrCalendarOptions Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetGrid(TVrCalendarGrid* Value);
	int __fastcall GetCount(void);
	TVrCalendarItem* __fastcall GetItem(int Index);
	void __fastcall StyleChanged(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	
protected:
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	void __fastcall CreateObjects(void);
	void __fastcall CalcPaintParams(void);
	void __fastcall UpdateItem(int Index);
	void __fastcall UpdateItems(void);
	virtual void __fastcall Paint(void);
	void __fastcall GetItemRect(int Index, Windows::TRect &R);
	int __fastcall GetItemIndex(int X, int Y);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall Click(void);
	
public:
	__fastcall virtual TVrCalendar(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCalendar(void);
	void __fastcall Reset(void);
	__property int Count = {read=GetCount, nodefault};
	__property TVrCalendarItem* Items[int Index] = {read=GetItem};
	__property int ItemIndex = {read=FItemIndex, nodefault};
	
__published:
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property Vrtypes::TVrRowInt Rows = {read=FRows, write=SetRows, default=5};
	__property Vrtypes::TVrColInt Columns = {read=FColumns, write=SetColumns, default=5};
	__property TVrCalendarGrid* Grid = {read=FGrid, write=SetGrid};
	__property Vrtypes::TVrDrawStyle DrawStyle = {read=FDrawStyle, write=SetDrawStyle, default=1};
	__property TVrGridAlignment Alignment = {read=FAlignment, write=SetAlignment, default=4};
	__property int FirstIndex = {read=FFirstIndex, write=SetFirstIndex, default=1};
	__property int Digits = {read=FDigits, write=SetDigits, default=2};
	__property TVrCalendarOptions Options = {read=FOptions, write=SetOptions, default=0};
	__property int NextStep = {read=FNextStep, write=SetNextStep, default=1};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property TVrCalendarDrawEvent OnDraw = {read=FOnDraw, write=FOnDraw};
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property Enabled ;
	__property Font ;
	__property Cursor ;
	__property DragMode ;
	__property DragKind ;
	__property DragCursor ;
	__property ParentColor ;
	__property ParentFont ;
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
	__property OnEndDock ;
	__property OnDragDrop ;
	__property OnEndDrag ;
	__property OnStartDock ;
	__property OnStartDrag ;
};


class PASCALIMPLEMENTATION TVrCalendarItems : public Vrclasses::TVrCollection 
{
	typedef Vrclasses::TVrCollection inherited;
	
private:
	TVrCalendar* FOwner;
	HIDESBASE TVrCalendarItem* __fastcall GetItem(int Index);
	
protected:
	virtual void __fastcall Update(Vrclasses::TVrCollectionItem* Item);
	__property TVrCalendar* Owner = {read=FOwner};
	
public:
	__fastcall TVrCalendarItems(TVrCalendar* AOwner);
	__property TVrCalendarItem* Items[int Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TVrCollection.Destroy */ inline __fastcall virtual ~TVrCalendarItems(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrcalendar */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrcalendar;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrCalendar
