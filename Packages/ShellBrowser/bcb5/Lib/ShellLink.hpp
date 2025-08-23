// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ShellLink.pas' rev: 5.00

#ifndef ShellLinkHPP
#define ShellLinkHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ShellBrowser.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <ShlObj.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Shelllink
{
//-- type declarations -------------------------------------------------------
struct TJAMPathChanged
{
	unsigned Msg;
	_ITEMIDLIST *PIDL;
	int Unused;
	int Result;
} ;

class DELPHICLASS TShellList;
class PASCALIMPLEMENTATION TShellList : public Classes::TList 
{
	typedef Classes::TList inherited;
	
protected:
	HWND __fastcall GetItem(int aIndex);
	void __fastcall SetItem(int aIndex, HWND newValue);
	
public:
	HIDESBASE void __fastcall Add(HWND Handle);
	HIDESBASE void __fastcall Remove(HWND Handle);
	__property HWND Items[int aIndex] = {read=GetItem, write=SetItem/*, default*/};
public:
	#pragma option push -w-inl
	/* TList.Destroy */ inline __fastcall virtual ~TShellList(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TShellList(void) : Classes::TList() { }
	#pragma option pop
	
};


class DELPHICLASS TJamShellLink;
class PASCALIMPLEMENTATION TJamShellLink : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TShellList* FList;
	bool FEnabled;
	Classes::TNotifyEvent FOnChange;
	
protected:
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(AnsiString s);
	
public:
	__fastcall virtual TJamShellLink(Classes::TComponent* AOwner);
	__fastcall virtual ~TJamShellLink(void);
	void __fastcall RegisterShellControl(HWND Handle);
	void __fastcall UnregisterShellControl(HWND Handle);
	void __fastcall PathChanged(Controls::TWinControl* Sender, Shlobj::PItemIDList PIDL);
	void __fastcall SelectAll(Controls::TWinControl* Sender);
	void __fastcall Refresh(Controls::TWinControl* Sender);
	void __fastcall SmartRefresh(Controls::TWinControl* Sender);
	void __fastcall GoUp(Controls::TWinControl* Sender);
	
__published:
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
};


//-- var, const, procedure ---------------------------------------------------
static const Word JAM_PATHCHANGED = 0x680;
static const Word JAM_SELECTALL = 0x681;
static const Word JAM_REFRESH = 0x682;
static const Word JAM_SMARTREFRESH = 0x683;
static const Word JAM_GOUP = 0x684;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Shelllink */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Shelllink;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ShellLink
