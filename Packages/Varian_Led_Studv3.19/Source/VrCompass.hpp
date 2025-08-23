// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrCompass.pas' rev: 5.00

#ifndef VrCompassHPP
#define VrCompassHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrcompass
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrCompass;
class PASCALIMPLEMENTATION TVrCompass : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	Graphics::TBitmap* FBackImage;
	bool FAutoSize;
	int FHeading;
	int FNeedleLength;
	int FNeedleWidth;
	Graphics::TColor FNeedleColor;
	bool FNeedleTransparent;
	Graphics::TColor FCircleColor;
	int FCircleWidth;
	Graphics::TColor FCircleOutlineColor;
	int FCircleOutlineWidth;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetHeading(int Value);
	void __fastcall SetNeedleColor(Graphics::TColor Value);
	void __fastcall SetCircleWidth(int Value);
	void __fastcall SetCircleOutlineColor(Graphics::TColor Value);
	void __fastcall SetNeedleLength(int Value);
	void __fastcall SetNeedleWidth(int Value);
	void __fastcall SetCircleOutlineWidth(int Value);
	void __fastcall SetCircleColor(Graphics::TColor Value);
	void __fastcall SetBackImage(Graphics::TBitmap* Value);
	HIDESBASE void __fastcall SetAutoSize(bool Value);
	void __fastcall SetNeedleTransparent(bool Value);
	void __fastcall BackImageChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall Paint(void);
	void __fastcall AdjustClientRect(void);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	HIDESBASE virtual void __fastcall Changed(void);
	
public:
	__fastcall virtual TVrCompass(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCompass(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	
__published:
	__property int Heading = {read=FHeading, write=SetHeading, nodefault};
	__property int NeedleLength = {read=FNeedleLength, write=SetNeedleLength, default=40};
	__property int NeedleWidth = {read=FNeedleWidth, write=SetNeedleWidth, nodefault};
	__property int CircleOutlineWidth = {read=FCircleOutlineWidth, write=SetCircleOutlineWidth, nodefault
		};
	__property int CircleWidth = {read=FCircleWidth, write=SetCircleWidth, default=8};
	__property Graphics::TColor CircleOutlineColor = {read=FCircleOutlineColor, write=SetCircleOutlineColor
		, default=16711680};
	__property Graphics::TColor NeedleColor = {read=FNeedleColor, write=SetNeedleColor, default=255};
	__property Graphics::TColor CircleColor = {read=FCircleColor, write=SetCircleColor, default=8388608
		};
	__property Graphics::TBitmap* BackImage = {read=FBackImage, write=SetBackImage};
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=1};
	__property bool NeedleTransparent = {read=FNeedleTransparent, write=SetNeedleTransparent, default=0
		};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Transparent ;
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

}	/* namespace Vrcompass */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrcompass;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrCompass
