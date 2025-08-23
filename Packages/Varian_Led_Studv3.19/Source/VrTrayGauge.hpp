// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrTrayGauge.pas' rev: 5.00

#ifndef VrTrayGaugeHPP
#define VrTrayGaugeHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrSystem.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
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

namespace Vrtraygauge
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrTrayGaugeStyle { gsSingle, gsDual };
#pragma option pop

class DELPHICLASS TVrTrayGauge;
class PASCALIMPLEMENTATION TVrTrayGauge : public Vrsystem::TVrCustomTrayIcon 
{
	typedef Vrsystem::TVrCustomTrayIcon inherited;
	
private:
	int FMin;
	int FMax;
	int FPosition;
	Classes::TNotifyEvent FOnChange;
	Vrclasses::TVrPalette* FPalette;
	TVrTrayGaugeStyle FStyle;
	AnsiString ResName;
	Controls::TImageList* ImageList;
	Graphics::TBitmap* Bitmap;
	void __fastcall SetMin(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetStyle(TVrTrayGaugeStyle Value);
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	void __fastcall UpdateTrayIcon(void);
	void __fastcall PaletteModified(System::TObject* Sender);
	
protected:
	virtual void __fastcall Loaded(void);
	void __fastcall LoadBitmaps(void);
	int __fastcall IconIndex(void);
	void __fastcall Change(void);
	
public:
	__fastcall virtual TVrTrayGauge(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrTrayGauge(void);
	
__published:
	__property Vrclasses::TVrPalette* Palette = {read=FPalette, write=SetPalette};
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property TVrTrayGaugeStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Visible ;
	__property Enabled ;
	__property Hint ;
	__property ShowHint ;
	__property PopupMenu ;
	__property HideTaskBtn ;
	__property LeftBtnPopup ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnMouseMove ;
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrtraygauge */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrtraygauge;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrTrayGauge
