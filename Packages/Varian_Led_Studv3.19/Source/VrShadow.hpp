// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrShadow.pas' rev: 5.00

#ifndef VrShadowHPP
#define VrShadowHPP

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

namespace Vrshadow
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrShadowButtonStyle { ssRectangle, ssRoundRect };
#pragma option pop

#pragma option push -b-
enum TVrShadowDirection { sdTopLeft, sdTopRight, sdBottomLeft, sdBottomRight };
#pragma option pop

class DELPHICLASS TVrShadowBrush;
class PASCALIMPLEMENTATION TVrShadowBrush : public Graphics::TBrush 
{
	typedef Graphics::TBrush inherited;
	
public:
	__fastcall TVrShadowBrush(void);
	
__published:
	__property Color ;
public:
	#pragma option push -w-inl
	/* TBrush.Destroy */ inline __fastcall virtual ~TVrShadowBrush(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrShadowPen;
class PASCALIMPLEMENTATION TVrShadowPen : public Graphics::TPen 
{
	typedef Graphics::TPen inherited;
	
public:
	__fastcall TVrShadowPen(void);
	
__published:
	__property Color ;
public:
	#pragma option push -w-inl
	/* TPen.Destroy */ inline __fastcall virtual ~TVrShadowPen(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrShadowButton;
class PASCALIMPLEMENTATION TVrShadowButton : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FDepth;
	Graphics::TColor FShadowColor;
	Graphics::TColor FShadowOutline;
	TVrShadowBrush* FBrush;
	TVrShadowPen* FPen;
	TVrShadowButtonStyle FStyle;
	TVrShadowDirection FDirection;
	Vrtypes::TVrTextAlignment FTextAlign;
	bool Down;
	bool Pressed;
	Windows::TRect CurrentRect;
	void __fastcall SetBrush(TVrShadowBrush* Value);
	void __fastcall SetPen(TVrShadowPen* Value);
	void __fastcall SetDepth(int Value);
	void __fastcall SetShadowColor(Graphics::TColor Value);
	void __fastcall SetShadowOutline(Graphics::TColor Value);
	void __fastcall SetStyle(TVrShadowButtonStyle Value);
	void __fastcall SetDirection(TVrShadowDirection Value);
	void __fastcall SetTextAlign(Vrtypes::TVrTextAlignment Value);
	void __fastcall StyleChanged(System::TObject* Sender);
	void __fastcall AdjustBtnRect(Windows::TRect &Rect, int Offset);
	HIDESBASE void __fastcall DoMouseDown(int XPos, int YPos);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	MESSAGE void __fastcall CMDialogChar(Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDblClk(Messages::TWMMouse &Message);
	
protected:
	void __fastcall DrawButton(void);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Click(void);
	
public:
	__fastcall virtual TVrShadowButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrShadowButton(void);
	
__published:
	__property TVrShadowBrush* Brush = {read=FBrush, write=SetBrush};
	__property TVrShadowPen* Pen = {read=FPen, write=SetPen};
	__property int Depth = {read=FDepth, write=SetDepth, default=4};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, default=-2147483632
		};
	__property Graphics::TColor ShadowOutline = {read=FShadowOutline, write=SetShadowOutline, default=-2147483632
		};
	__property TVrShadowButtonStyle Style = {read=FStyle, write=SetStyle, default=1};
	__property TVrShadowDirection Direction = {read=FDirection, write=SetDirection, default=3};
	__property Vrtypes::TVrTextAlignment TextAlign = {read=FTextAlign, write=SetTextAlign, default=1};
	__property Transparent ;
	__property Anchors ;
	__property BiDiMode ;
	__property Constraints ;
	__property Caption ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property Font ;
	__property ParentBiDiMode ;
	__property ParentColor ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
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

}	/* namespace Vrshadow */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrshadow;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrShadow
