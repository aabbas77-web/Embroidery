// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrHotImage.pas' rev: 5.00

#ifndef VrHotImageHPP
#define VrHotImageHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrConst.hpp>	// Pascal unit
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

namespace Vrhotimage
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrHotRect;
class PASCALIMPLEMENTATION TVrHotRect : public Vrclasses::TVrPersistent 
{
	typedef Vrclasses::TVrPersistent inherited;
	
private:
	Graphics::TColor FColor;
	int FWidth;
	bool FVisible;
	void __fastcall SetColor(Graphics::TColor Value);
	void __fastcall SetWidth(int Value);
	void __fastcall SetVisible(bool Value);
	
public:
	__fastcall TVrHotRect(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	
__published:
	__property Graphics::TColor Color = {read=FColor, write=SetColor, default=65535};
	__property int Width = {read=FWidth, write=SetWidth, default=1};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrHotRect(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TVrHotImageDrawStyle { dsCenter, dsStretch };
#pragma option pop

class DELPHICLASS TVrHotImage;
class PASCALIMPLEMENTATION TVrHotImage : public Vrcontrols::TVrHyperLinkControl 
{
	typedef Vrcontrols::TVrHyperLinkControl inherited;
	
private:
	Graphics::TBitmap* FImageLeave;
	Graphics::TBitmap* FImageEnter;
	Graphics::TColor FColorEnter;
	Graphics::TColor FColorLeave;
	TVrHotImageDrawStyle FDrawStyle;
	Vrtypes::TVrTextAlignment FTextAlignment;
	TVrHotRect* FHotRect;
	bool FHasMouse;
	void __fastcall SetImageLeave(Graphics::TBitmap* Value);
	void __fastcall SetImageEnter(Graphics::TBitmap* Value);
	void __fastcall SetColorEnter(Graphics::TColor Value);
	void __fastcall SetColorLeave(Graphics::TColor Value);
	void __fastcall SetDrawStyle(TVrHotImageDrawStyle Value);
	void __fastcall SetTextAlignment(Vrtypes::TVrTextAlignment Value);
	void __fastcall SetHotRect(TVrHotRect* Value);
	void __fastcall BitmapChanged(System::TObject* Sender);
	void __fastcall HotRectChanged(System::TObject* Sender);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall MouseEnter(void);
	virtual void __fastcall MouseLeave(void);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrHotImage(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrHotImage(void);
	
__published:
	__property Graphics::TBitmap* ImageLeave = {read=FImageLeave, write=SetImageLeave};
	__property Graphics::TBitmap* ImageEnter = {read=FImageEnter, write=SetImageEnter};
	__property Graphics::TColor ColorEnter = {read=FColorEnter, write=SetColorEnter, default=16711680};
		
	__property Graphics::TColor ColorLeave = {read=FColorLeave, write=SetColorLeave, default=0};
	__property TVrHotImageDrawStyle DrawStyle = {read=FDrawStyle, write=SetDrawStyle, default=0};
	__property Vrtypes::TVrTextAlignment TextAlignment = {read=FTextAlignment, write=SetTextAlignment, 
		default=7};
	__property TVrHotRect* HotRect = {read=FHotRect, write=SetHotRect};
	__property Transparent ;
	__property OnMouseEnter ;
	__property OnMouseLeave ;
	__property Align ;
	__property Anchors ;
	__property BiDiMode ;
	__property Constraints ;
	__property Caption ;
	__property DragCursor ;
	__property DragMode ;
	__property DragKind ;
	__property Enabled ;
	__property Font ;
	__property ParentShowHint ;
	__property ParentBiDiMode ;
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

}	/* namespace Vrhotimage */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrhotimage;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrHotImage
