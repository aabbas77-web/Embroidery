// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'JAMControls.pas' rev: 4.00

#ifndef JAMControlsHPP
#define JAMControlsHPP

#pragma delphiheader begin
#pragma option push -w-
#include <Menus.hpp>	// Pascal unit
#include <ShlObj.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ShellBrowser.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Jamcontrols
{
//-- type declarations -------------------------------------------------------
typedef TOwnerDrawState TOwnerDrawState;
;

class DELPHICLASS TJamComboItem;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TJamComboItem : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString Caption;
	AnsiString DisplayName;
	int Indent;
	int IconNumber;
	bool IsDrive;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TJamComboItem(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TJamComboItem(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

class DELPHICLASS TJamFolderCombo;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TJamFolderCombo : public Stdctrls::TCustomComboBox 
{
	typedef Stdctrls::TCustomComboBox inherited;
	
private:
	Shellbrowser::TShellBrowser* FShellBrowser;
	Shellbrowser::TJamSystemImageList* FImageList;
	int mIndentPixels;
	bool FIncludeDrives;
	HIDESBASE MESSAGE void __fastcall CNDrawItem(Messages::TWMDrawItem &Message);
	HIDESBASE MESSAGE void __fastcall WMRButtonDown(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMDeleteItem(Messages::TWMDeleteItem &amsg);
	
protected:
	virtual void __fastcall DrawItem(int aIndex, const Windows::TRect &aRect, Stdctrls::TOwnerDrawState 
		aState);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DestroyWnd(void);
	bool __fastcall GetIncludeDrives(void);
	void __fastcall SetIncludeDrives(bool aIncludeDrives);
	AnsiString __fastcall GetVersion(void);
	void __fastcall SetVersion(AnsiString s);
	
public:
	__fastcall virtual TJamFolderCombo(Classes::TComponent* AOwner);
	__fastcall virtual ~TJamFolderCombo(void);
	int __fastcall InsertItem(int aIndex, AnsiString aCaption, AnsiString aDisplayName, int aIconNumber
		, int aIndent);
	int __fastcall AddComboItem(AnsiString aCaption, AnsiString aDisplayName, int aIconNumber, int aIndent
		);
	int __fastcall AddFolder(AnsiString Path, int Indent);
	bool __fastcall SelectFolder(AnsiString aFolder);
	
__published:
	__property bool IncludeDrives = {read=GetIncludeDrives, write=SetIncludeDrives, nodefault};
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
	__property Text ;
	__property Align ;
	__property Color ;
	__property Ctl3D ;
	__property DragMode ;
	__property DragCursor ;
	__property DropDownCount ;
	__property Enabled ;
	__property Font ;
	__property ImeMode ;
	__property ImeName ;
	__property ItemHeight ;
	__property MaxLength ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Sorted ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnChange ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnDrawItem ;
	__property OnDropDown ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TJamFolderCombo(HWND ParentWindow) : Stdctrls::TCustomComboBox(
		ParentWindow) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Jamcontrols */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Jamcontrols;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// JAMControls
