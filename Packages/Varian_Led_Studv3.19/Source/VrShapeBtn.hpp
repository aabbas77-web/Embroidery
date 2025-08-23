// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrShapeBtn.pas' rev: 5.00

#ifndef VrShapeBtnHPP
#define VrShapeBtnHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrControls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
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

namespace Vrshapebtn
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrShapeBtn;
class PASCALIMPLEMENTATION TVrShapeBtn : public Vrcontrols::TVrGraphicControl 
{
	typedef Vrcontrols::TVrGraphicControl inherited;
	
private:
	bool FAutoSize;
	Graphics::TBitmap* FBitmap;
	Graphics::TBitmap* FBitmapUp;
	Graphics::TBitmap* FBitmapDown;
	Graphics::TBitmap* TempBitmap;
	void __fastcall AdjustBounds(void);
	Graphics::TColor __fastcall BevelColor(const Buttons::TButtonState AState, const bool TopLeft);
	void __fastcall BitmapChanged(System::TObject* Sender);
	void __fastcall Create3DBitmap(Graphics::TBitmap* Source, const Buttons::TButtonState AState, Graphics::TBitmap* 
		Target);
	void __fastcall SetBitmap(Graphics::TBitmap* Value);
	void __fastcall SetBitmapDown(Graphics::TBitmap* Value);
	void __fastcall SetBitmapUp(Graphics::TBitmap* Value);
	MESSAGE void __fastcall CMDialogChar(Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	MESSAGE void __fastcall CMSysColorChange(Messages::TMessage &Message);
	bool __fastcall PtInMask(const int X, const int Y);
	
protected:
	Buttons::TButtonState FState;
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall Click(void);
	virtual void __fastcall Paint(void);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	
public:
	__fastcall virtual TVrShapeBtn(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrShapeBtn(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	
__published:
	__property Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property Caption ;
	__property Enabled ;
	__property Font ;
	__property ShowHint ;
	__property Visible ;
	__property OnClick ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Vrshapebtn */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrshapebtn;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrShapeBtn
