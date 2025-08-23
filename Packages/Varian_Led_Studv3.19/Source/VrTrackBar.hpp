// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrTrackBar.pas' rev: 5.00

#ifndef VrTrackBarHPP
#define VrTrackBarHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <VrConst.hpp>	// Pascal unit
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

namespace Vrtrackbar
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrTrackBarOption { toActiveClick, toMouseClip, toHandPoint, toFixedPoints };
#pragma option pop

typedef Set<TVrTrackBarOption, toActiveClick, toFixedPoints>  TVrTrackBarOptions;

typedef Shortint TVrTrackBarImageRange;

typedef Graphics::TBitmap* TVrTrackBarImages[3];

class DELPHICLASS TVrTrackBarThumb;
class PASCALIMPLEMENTATION TVrTrackBarThumb : public Vrcontrols::TVrCustomThumb 
{
	typedef Vrcontrols::TVrCustomThumb inherited;
	
protected:
	virtual int __fastcall GetImageIndex(void);
	
public:
	__fastcall virtual TVrTrackBarThumb(Classes::TComponent* AOwner);
public:
	#pragma option push -w-inl
	/* TVrCustomThumb.Destroy */ inline __fastcall virtual ~TVrTrackBarThumb(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrTrackBar;
class PASCALIMPLEMENTATION TVrTrackBar : public Vrcontrols::TVrCustomImageControl 
{
	typedef Vrcontrols::TVrCustomImageControl inherited;
	
private:
	int FMin;
	int FMax;
	int FPosition;
	Vrtypes::TVrProgressStyle FStyle;
	Vrtypes::TVrOrientation FOrientation;
	TVrTrackBarOptions FOptions;
	int FFrequency;
	int FBorderWidth;
	Vrclasses::TVrBevel* FGutterBevel;
	int FGutterWidth;
	Graphics::TColor FGutterColor;
	Vrtypes::TVrTickMarks FTickMarks;
	Graphics::TColor FTickColor;
	int FScaleOffset;
	Classes::TNotifyEvent FOnChange;
	int FHit;
	bool FClipOn;
	bool FFocused;
	TVrTrackBarThumb* FThumb;
	Graphics::TBitmap* FImages[3];
	int __fastcall GetThumbStates(void);
	Graphics::TBitmap* __fastcall GetImage(int Index);
	void __fastcall SetMin(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetStyle(Vrtypes::TVrProgressStyle Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetOptions(TVrTrackBarOptions Value);
	void __fastcall SetFrequency(int Value);
	HIDESBASE void __fastcall SetBorderWidth(int Value);
	void __fastcall SetGutterWidth(int Value);
	void __fastcall SetGutterColor(Graphics::TColor Value);
	void __fastcall SetGutterBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetTickMarks(Vrtypes::TVrTickMarks Value);
	void __fastcall SetTickColor(Graphics::TColor Value);
	void __fastcall SetScaleOffset(int Value);
	void __fastcall SetThumbStates(int Value);
	void __fastcall SetImage(int Index, Graphics::TBitmap* Value);
	void __fastcall DrawScale(Graphics::TCanvas* Canvas, int Offset, int ThumbOffset, int RulerLength, 
		int PointsStep, int PointsHeight, int ExtremePointsHeight);
	void __fastcall UpdateThumbGlyph(void);
	void __fastcall GutterBevelChanged(System::TObject* Sender);
	void __fastcall ImageChanged(System::TObject* Sender);
	MESSAGE void __fastcall WMGetDlgCode(Messages::TWMNoParams &Msg);
	HIDESBASE MESSAGE void __fastcall CMFocusChanged(Controls::TCMFocusChanged &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall Loaded(void);
	virtual void __fastcall LoadBitmaps(void);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Change(void);
	int __fastcall GetRulerLength(void);
	int __fastcall GetValueByOffset(int Offset);
	int __fastcall GetOffsetByValue(int Value);
	void __fastcall SetThumbOffset(int Value, bool Update);
	DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	void __fastcall ThumbMove(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	void __fastcall ThumbDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall ThumbUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	
public:
	__fastcall virtual TVrTrackBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrTrackBar(void);
	
__published:
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property Vrtypes::TVrProgressStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property TVrTrackBarOptions Options = {read=FOptions, write=SetOptions, default=7};
	__property int Frequency = {read=FFrequency, write=SetFrequency, default=10};
	__property int BorderWidth = {read=FBorderWidth, write=SetBorderWidth, default=10};
	__property Vrclasses::TVrBevel* GutterBevel = {read=FGutterBevel, write=SetGutterBevel};
	__property int GutterWidth = {read=FGutterWidth, write=SetGutterWidth, default=9};
	__property Graphics::TColor GutterColor = {read=FGutterColor, write=SetGutterColor, default=0};
	__property Vrtypes::TVrTickMarks TickMarks = {read=FTickMarks, write=SetTickMarks, default=1};
	__property Graphics::TColor TickColor = {read=FTickColor, write=SetTickColor, default=0};
	__property int ThumbStates = {read=GetThumbStates, write=SetThumbStates, default=1};
	__property Graphics::TBitmap* VThumb = {read=GetImage, write=SetImage, index=0};
	__property Graphics::TBitmap* HThumb = {read=GetImage, write=SetImage, index=1};
	__property Graphics::TBitmap* Bitmap = {read=GetImage, write=SetImage, index=2};
	__property int ScaleOffset = {read=FScaleOffset, write=SetScaleOffset, default=5};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Enabled ;
	__property Color ;
	__property Cursor ;
	__property DragMode ;
	__property DragKind ;
	__property DragCursor ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnEnter ;
	__property OnExit ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnKeyDown ;
	__property OnKeyUp ;
	__property OnKeyPress ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnDragDrop ;
	__property OnEndDrag ;
	__property OnStartDock ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrTrackBar(HWND ParentWindow) : Vrcontrols::TVrCustomImageControl(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrtrackbar */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrtrackbar;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrTrackBar
