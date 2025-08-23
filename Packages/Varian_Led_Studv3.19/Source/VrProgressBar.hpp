// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrProgressBar.pas' rev: 5.00

#ifndef VrProgressBarHPP
#define VrProgressBarHPP

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

namespace Vrprogressbar
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrProgressBar;
class PASCALIMPLEMENTATION TVrProgressBar : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Vrclasses::TVrBevel* FBevel;
	int FMin;
	int FMax;
	int FPosition;
	bool FPlainColors;
	Graphics::TColor FStartColor;
	Graphics::TColor FEndColor;
	bool FSmooth;
	Vrtypes::TVrOrientation FOrientation;
	int FStep;
	Windows::TRect ViewPort;
	Graphics::TBitmap* Bitmap;
	bool ColorUpdate;
	int __fastcall GetPercentDone(void);
	void __fastcall SetMin(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetStartColor(Graphics::TColor Value);
	void __fastcall SetEndColor(Graphics::TColor Value);
	void __fastcall SetPlainColors(bool Value);
	void __fastcall SetSmooth(bool Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall BevelChanged(System::TObject* Sender);
	
protected:
	void __fastcall CreateBitmap(const Windows::TRect &Rect);
	virtual void __fastcall Paint(void);
	void __fastcall DrawHori(void);
	void __fastcall DrawVert(void);
	
public:
	__fastcall virtual TVrProgressBar(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrProgressBar(void);
	void __fastcall StepIt(void);
	void __fastcall StepBy(int Delta);
	__property int PercentDone = {read=GetPercentDone, nodefault};
	
__published:
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=100};
	__property Graphics::TColor StartColor = {read=FStartColor, write=SetStartColor, default=8388608};
	__property Graphics::TColor EndColor = {read=FEndColor, write=SetEndColor, default=16776960};
	__property bool PlainColors = {read=FPlainColors, write=SetPlainColors, default=0};
	__property bool Smooth = {read=FSmooth, write=SetSmooth, default=0};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property int Step = {read=FStep, write=FStep, default=10};
	__property Align ;
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

}	/* namespace Vrprogressbar */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrprogressbar;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrProgressBar
