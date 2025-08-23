// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrPaletteDlg.pas' rev: 5.00

#ifndef VrPaletteDlgHPP
#define VrPaletteDlgHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrClasses.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
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

namespace Vrpalettedlg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrPaletteDlg;
class PASCALIMPLEMENTATION TVrPaletteDlg : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TButton* OkButton;
	Stdctrls::TButton* CancelButton;
	Stdctrls::TGroupBox* GroupBox1;
	Extctrls::TShape* Shape1;
	Extctrls::TShape* Shape2;
	Extctrls::TShape* Shape3;
	Extctrls::TShape* Shape4;
	Extctrls::TShape* Shape5;
	Extctrls::TShape* Shape6;
	Extctrls::TShape* Shape7;
	Extctrls::TShape* Shape8;
	Extctrls::TShape* Shape9;
	Extctrls::TShape* Shape10;
	Extctrls::TShape* Shape11;
	Extctrls::TShape* Shape12;
	Stdctrls::TRadioButton* RadioButton1;
	Stdctrls::TButton* Button3;
	Stdctrls::TRadioButton* RadioButton2;
	Stdctrls::TRadioButton* RadioButton3;
	Stdctrls::TRadioButton* RadioButton4;
	Stdctrls::TRadioButton* RadioButton5;
	Stdctrls::TRadioButton* RadioButton6;
	Dialogs::TColorDialog* ColorDialog;
	Stdctrls::TLabel* Label7;
	Extctrls::TShape* Shape13;
	Stdctrls::TButton* Button4;
	Stdctrls::TLabel* Label8;
	Extctrls::TShape* Shape14;
	Stdctrls::TButton* Button5;
	void __fastcall Button4Click(System::TObject* Sender);
	void __fastcall Button5Click(System::TObject* Sender);
	void __fastcall Button3Click(System::TObject* Sender);
	void __fastcall RadioButton1Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CancelButtonClick(System::TObject* Sender);
	void __fastcall OkButtonClick(System::TObject* Sender);
	
private:
	Vrclasses::TVrPalette* FCurPalette;
	Graphics::TColor FOrgColorHigh;
	Graphics::TColor FOrgColorLow;
	int FPaletteIndex;
	void __fastcall SetPalette(Vrclasses::TVrPalette* Value);
	
public:
	__property Vrclasses::TVrPalette* EditorPalette = {write=SetPalette};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TVrPaletteDlg(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TVrPaletteDlg(Classes::TComponent* AOwner, int 
		Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TVrPaletteDlg(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrPaletteDlg(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrpalettedlg */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrpalettedlg;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrPaletteDlg
