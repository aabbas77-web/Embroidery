// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrBitmapsDlg.pas' rev: 5.00

#ifndef VrBitmapsDlgHPP
#define VrBitmapsDlgHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrDeskTop.hpp>	// Pascal unit
#include <VrShadow.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <ExtDlgs.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
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

namespace Vrbitmapsdlg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrBitmapListDialog;
class PASCALIMPLEMENTATION TVrBitmapListDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TPanel* Panel1;
	Stdctrls::TListBox* ListBox;
	Dialogs::TSaveDialog* SaveDialog;
	Dialogs::TOpenDialog* OpenDialog;
	Extdlgs::TOpenPictureDialog* OpenPictureDialog;
	Vrshadow::TVrShadowButton* VrShadowButton1;
	Vrshadow::TVrShadowButton* VrShadowButton2;
	Vrshadow::TVrShadowButton* VrShadowButton3;
	Vrshadow::TVrShadowButton* VrShadowButton4;
	Vrshadow::TVrShadowButton* VrShadowButton5;
	Vrshadow::TVrShadowButton* VrShadowButton6;
	Vrshadow::TVrShadowButton* VrShadowButton7;
	Vrshadow::TVrShadowButton* VrShadowButton8;
	Vrshadow::TVrShadowButton* VrShadowButton9;
	Vrdesktop::TVrDeskTop* VrDeskTop1;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall ButtonAddClick(System::TObject* Sender);
	void __fastcall ListBoxDrawItem(Controls::TWinControl* Control, int Index, const Windows::TRect &Rect
		, Windows::TOwnerDrawState State);
	void __fastcall ButtonDeleteClick(System::TObject* Sender);
	void __fastcall ButtonClearClick(System::TObject* Sender);
	void __fastcall ButtonLoadClick(System::TObject* Sender);
	void __fastcall ButtonSaveClick(System::TObject* Sender);
	void __fastcall ButtonMoveUpClick(System::TObject* Sender);
	void __fastcall ButtonMoveDownClick(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall VrShadowButton9Click(System::TObject* Sender);
	
private:
	void __fastcall BitmapsChanged(System::TObject* Sender);
	
public:
	Vrclasses::TVrBitmaps* Bitmaps;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TVrBitmapListDialog(Classes::TComponent* AOwner)
		 : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TVrBitmapListDialog(Classes::TComponent* AOwner
		, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TVrBitmapListDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrBitmapListDialog(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrbitmapsdlg */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrbitmapsdlg;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrBitmapsDlg
