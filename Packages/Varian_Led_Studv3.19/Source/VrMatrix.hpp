// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrMatrix.pas' rev: 5.00

#ifndef VrMatrixHPP
#define VrMatrixHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrThreads.hpp>	// Pascal unit
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

namespace Vrmatrix
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrMatrixTextStyle { tsUpperCase, tsLowerCase, tsAsIs, tsProperCase };
#pragma option pop

#pragma option push -b-
enum TVrMatrixScrollDirection { sdRightToLeft, sdLeftToRight };
#pragma option pop

#pragma option push -b-
enum TVrMatrixLedStyle { ls9x13, ls14x20, ls19x27 };
#pragma option pop

class DELPHICLASS TVrMatrix;
class PASCALIMPLEMENTATION TVrMatrix : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FLeds;
	int FSpacing;
	AnsiString FOutString;
	Classes::TAlignment FAlignment;
	Vrclasses::TVrPalette* FPalette;
	TVrMatrixTextStyle FTextStyle;
	bool FAutoScroll;
	Vrclasses::TVrBevel* FBevel;
	TVrMatrixScrollDirection FScrollDirection;
	TVrMatrixLedStyle FLedStyle;
	bool FLedsVisible;
	bool FThreaded;
	Vrtypes::TVrOrientation FOrientation;
	Graphics::TColor FCurrColor;
	int FCharIndex;
	int FCharCount;
	Classes::TNotifyEvent FOnScrollDone;
	Graphics::TBitmap* Bitmap;
	Vrthreads::TVrTimer* FTimer;
	bool ScrollInit;
	bool Initialized;
	int FStartLed;
	Windows::TRect FImageRect;
	int __fastcall GetTimeInterval(void);
	void __fastcall SetLeds(int Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetOutString(AnsiString Value);
	void __fastcall SetAlignment(Classes::TAlignment Value);
	void __fastcall SetTextStyle(TVrMatrixTextStyle Value);
	void __fastcall SetAutoScroll(bool Value);
	void __fastcall SetTimeInterval(int Value);
	void __fastcall SetLedStyle(TVrMatrixLedStyle Value);
	void __fastcall SetLedsVisible(bool Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetThreaded(bool Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall PaletteModified(System::TObject* Sender);
	void __fastcall BevelChanged(System::TObject* Sender);
	void __fastcall TimerEvent(System::TObject* Sender);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall LoadBitmaps(void);
	void __fastcall DestroyBitmaps(void);
	void __fastcall UpdateLed(int Index, char Ch);
	void __fastcall UpdateLeds(bool Redraw);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Loaded(void);
	void __fastcall GetItemRect(int Index, Windows::TRect &R);
	void __fastcall CalcPaintParams(void);
	
public:
	__fastcall virtual TVrMatrix(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrMatrix(void);
	
__published:
	__property bool Threaded = {read=FThreaded, write=SetThreaded, default=1};
	__property int Leds = {read=FLeds, write=SetLeds, default=15};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=2};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=0};
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property TVrMatrixTextStyle TextStyle = {read=FTextStyle, write=SetTextStyle, default=0};
	__property bool AutoScroll = {read=FAutoScroll, write=SetAutoScroll, default=0};
	__property int TimeInterval = {read=GetTimeInterval, write=SetTimeInterval, default=500};
	__property TVrMatrixScrollDirection ScrollDirection = {read=FScrollDirection, write=FScrollDirection
		, default=0};
	__property TVrMatrixLedStyle LedStyle = {read=FLedStyle, write=SetLedStyle, default=1};
	__property bool LedsVisible = {read=FLedsVisible, write=SetLedsVisible, default=1};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property Classes::TNotifyEvent OnScrollDone = {read=FOnScrollDone, write=FOnScrollDone};
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Hint ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Text ;
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

}	/* namespace Vrmatrix */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrmatrix;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrMatrix
