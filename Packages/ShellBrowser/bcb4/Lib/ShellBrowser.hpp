// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ShellBrowser.pas' rev: 4.00

#ifndef ShellBrowserHPP
#define ShellBrowserHPP

#pragma delphiheader begin
#pragma option push -w-
#include <ImgList.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <DirMon.hpp>	// Pascal unit
#include <AxCtrls.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <ShlObj.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
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
#define NO_WIN32_LEAN_AND_MEAN
#include <shlobj.hpp>
#define _WIN32_IE 0x0500

namespace Shellbrowser
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TJamShellFolder { SF_FILESYSTEMFOLDER, SF_BITBUCKET, SF_CONTROLS, SF_DESKTOP, SF_DESKTOPDIRECTORY, 
	SF_DRIVES, SF_FONTS, SF_NETHOOD, SF_NETWORK, SF_PERSONAL, SF_PRINTERS, SF_PROGRAMS, SF_RECENT, SF_SENDTO, 
	SF_STARTMENU, SF_STARTUP, SF_TEMPLATES, SF_FAVORITES, SF_COMMON_STARTMENU, SF_COMMON_STARTUP, SF_COMMON_DESKTOPDIRECTORY, 
	SF_APPDATA, SF_PRINTHOOD, SF_COMMON_FAVORITES, SF_INTERNET_CACHE, SF_COOKIES, SF_HISTORY };
#pragma option pop

__interface IShellIconOverlay;
typedef System::DelphiInterface<IShellIconOverlay> _di_IShellIconOverlay;
__interface IShellIconOverlay  : public IUnknown /* __guid="{7D688A70-C613-11D0-999B-00C04FD655E1}" */
	
{
	
public:
	virtual HRESULT __stdcall GetOverlayIndex(Shlobj::PItemIDList pidl, /* out */ int &pIndex) = 0 ;
	virtual HRESULT __stdcall GetOverlayIconIndex(Shlobj::PItemIDList pidl, /* out */ int &pIconIndex) = 0 
		;
};

typedef IContextMenu2 IContextMenu_2;
;

#pragma pack(push, 1)
struct TShellDetails
{
	int fmt;
	int cxChar;
	_STRRET str;
} ;
#pragma pack(pop)

typedef TShellDetails *PShellDetails;

#pragma pack(push, 4)
struct TSHColumnID
{
	GUID fmtid;
	unsigned pid;
} ;
#pragma pack(pop)

typedef TSHColumnID *PSHColumnID;

__interface IShellFolder2;
typedef System::DelphiInterface<IShellFolder2> _di_IShellFolder2;
__interface IShellFolder2  : public IShellFolder /* __guid="{93F2F68C-1D1B-11D3-A30E-00C04F79ABD1}" */
	
{
	
public:
	virtual HRESULT __stdcall EnumSearches(void * ppEnum) = 0 ;
	virtual HRESULT __stdcall GetDefaultColumn(unsigned dwReserved, unsigned &pSort, unsigned &pDisplay
		) = 0 ;
	virtual HRESULT __stdcall GetDefaultColumnState(unsigned iColumn, unsigned &pcsFlags) = 0 ;
	virtual HRESULT __stdcall GetDefaultSearchGUID(GUID &lpGUID) = 0 ;
	virtual HRESULT __stdcall GetDetailsEx(Shlobj::PItemIDList pidl, PSHColumnID pscid, const Variant pv
		) = 0 ;
	virtual HRESULT __stdcall GetDetailsOf(Shlobj::PItemIDList pidl, unsigned col, TShellDetails &info)
		 = 0 ;
	virtual HRESULT __stdcall MapNameToSCID(wchar_t * pwszName, TSHColumnID &pscid) = 0 ;
};

__interface IShellDetails;
typedef System::DelphiInterface<IShellDetails> _di_IShellDetails;
__interface IShellDetails  : public IUnknown 
{
	
public:
	virtual HRESULT __stdcall GetDetailsOf(Shlobj::PItemIDList pidl, unsigned col, TShellDetails &info)
		 = 0 ;
	virtual HRESULT __stdcall ColumnClick(unsigned col) = 0 ;
};

typedef void __fastcall (__closure *TOnContextMenuSelectEvent)(const AnsiString command, bool &execute
	);

class DELPHICLASS TShellBrowser;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TShellBrowser : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FDirectory;
	_ITEMIDLIST *FFolderIdList;
	_di_IShellFolder FShellFolder;
	_ITEMIDLIST *FItemIDList;
	_ITEMIDLIST *FAbsoluteIdList;
	_di_IEnumIDList Objects;
	bool FFileSystemOnly;
	Classes::TStringList* FMultiObjects;
	int FSortDirection;
	int FLastColSorted;
	Classes::TStrings* FFilter;
	_di_IContextMenu2 ActiveIContextMenu;
	Menus::TPopupMenu* ActiveDelphiContextMenu;
	_di_IShellDetails Ishd;
	_di_IShellFolder2 IShF2;
	bool TriedIshd;
	_WIN32_FIND_DATAA FindData;
	Controls::TWndMethod OriginalWndProc;
	bool FileSystemFolder;
	int ColumnWidth[16];
	Classes::TNotifyEvent fOnRename;
	Classes::TNotifyEvent fOnFileChange;
	TOnContextMenuSelectEvent fOnContextMenuSelect;
	Dirmon::TDirMon* fDirMon;
	bool fInitialized;
	bool fReadOnly;
	void __fastcall GetPidlsFromMultiObjects(Shlobj::PItemIDList * pidls, const int pidls_Size);
	void __fastcall SendToWindowProc(Messages::TMessage &Message);
	bool __fastcall FilterMatch(void);
	
protected:
	void __fastcall SetDirectory(AnsiString Path);
	void __fastcall SetObjectName(AnsiString ObjName);
	void __fastcall SetItemIdList(Shlobj::PItemIDList IdList);
	void __fastcall SetFolderIdList(Shlobj::PItemIDList IdList);
	void __fastcall SetItemIdList2(unsigned IdList);
	void __fastcall SetFolderIdList2(unsigned IdList);
	void __fastcall SetShellfolder(_di_IShellFolder Folder);
	void __fastcall SetAbsoluteItemIdList(Shlobj::PItemIDList IdList);
	int __fastcall GetIconNumber(void);
	int __fastcall GetSelectedIconNumber(void);
	Shlobj::PItemIDList __fastcall GetItemIdList(void);
	Shlobj::PItemIDList __fastcall GetFolderIdList(void);
	unsigned __fastcall GetItemIdList2(void);
	unsigned __fastcall GetFolderIdList2(void);
	AnsiString __fastcall GetObjectName(void);
	bool __fastcall GetIShellDetails(void);
	AnsiString __fastcall GetDomain(void);
	Shlobj::PItemIDList __fastcall GetAbsoluteItemIdList(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	void __fastcall SetFilter(AnsiString aFilter);
	AnsiString __fastcall GetFilter(void);
	AnsiString __fastcall GetVersion(void);
	void __fastcall SetVersion(AnsiString s);
	void __fastcall SetOnFileChange(Classes::TNotifyEvent Event);
	void __fastcall FileChange(System::TObject* Sender);
	unsigned __fastcall GetWinHandle(void);
	__property unsigned WinHandle = {read=GetWinHandle, nodefault};
	
public:
	__fastcall virtual TShellBrowser(Classes::TComponent* AOwner);
	__fastcall virtual ~TShellBrowser(void);
	bool __fastcall Next(void);
	AnsiString __fastcall ShowContextMenu(const Windows::TPoint &lppt, Menus::TPopupMenu* M);
	bool __fastcall InvokeContextMenuCommand(AnsiString verb);
	bool __fastcall IsFolder(void);
	bool __fastcall HasSubFolders(void);
	bool __fastcall CanRename(void);
	bool __fastcall IsHidden(void);
	bool __fastcall IsLink(void);
	AnsiString __fastcall IsLinkToFolder(void);
	unsigned __fastcall GetAttributes(unsigned Attributes);
	bool __fastcall BrowseForFolder(AnsiString Msg);
	AnsiString __fastcall GetShellObjectName(void);
	bool __fastcall SelectParent(void);
	bool __fastcall BrowseObject(void);
	bool __fastcall FillListView(Comctrls::TListView* ListView, bool Details);
	void __fastcall HandleColumnClick(System::TObject* Sender, Comctrls::TListColumn* Column);
	void __fastcall RenameObject(AnsiString &NewName);
	bool __fastcall ShowNetConnectionDialog(void);
	bool __fastcall BrowseSpecialFolder(TJamShellFolder folder);
	__property int IconNumber = {read=GetIconNumber, nodefault};
	__property int SelectedIconNumber = {read=GetSelectedIconNumber, nodefault};
	int __fastcall GetDesktopIconIndex(void);
	int __fastcall GetOverlayIndex(void);
	AnsiString __fastcall GetDesktopName(void);
	__property Shlobj::PItemIDList FolderIdList = {read=GetFolderIdList, write=SetFolderIdList};
	__property Shlobj::PItemIDList ItemIdList = {read=GetItemIdList, write=SetItemIdList};
	__property Shlobj::PItemIDList AbsoluteItemIdList = {read=GetAbsoluteItemIdList, write=SetAbsoluteItemIdList
		};
	__property _di_IShellFolder ShellFolder = {read=FShellFolder, write=SetShellfolder};
	__property bool ReadOnly = {read=fReadOnly, write=fReadOnly, nodefault};
	TJamShellFolder __fastcall IsSpecialFolder(void);
	TJamShellFolder __fastcall IsSpecialObject(void);
	AnsiString __fastcall GetColumnText(int col, bool Header);
	Classes::TAlignment __fastcall GetColumnInfo(int col, int &Width);
	void __fastcall HandlePopupMessages(Messages::TMessage &Message);
	virtual void __fastcall Loaded(void);
	
__published:
	__property AnsiString Filter = {read=GetFilter, write=SetFilter};
	__property AnsiString Folder = {read=FDirectory, write=SetDirectory};
	__property AnsiString ObjectName = {read=GetObjectName, write=SetObjectName};
	__property bool FileSystemOnly = {read=FFileSystemOnly, write=FFileSystemOnly, nodefault};
	__property Classes::TStringList* MultiObjects = {read=FMultiObjects, write=FMultiObjects};
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
	__property Classes::TNotifyEvent OnRename = {read=fOnRename, write=fOnRename};
	__property Classes::TNotifyEvent OnFileChange = {read=fOnFileChange, write=SetOnFileChange};
	__property TOnContextMenuSelectEvent OnContextMenuSelect = {read=fOnContextMenuSelect, write=fOnContextMenuSelect
		};
};

#pragma pack(pop)

class DELPHICLASS EShellBrowserError;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION EShellBrowserError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EShellBrowserError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EShellBrowserError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EShellBrowserError(int Ident, Extended Dummy) : Sysutils::Exception(
		Ident, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EShellBrowserError(int Ident, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EShellBrowserError(const AnsiString Msg, int AHelpContext
		) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EShellBrowserError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EShellBrowserError(int Ident, int AHelpContext) : Sysutils::Exception(
		Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EShellBrowserError(int Ident, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Ident, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EShellBrowserError(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

#pragma option push -b-
enum TJamImageListSize { si_small, si_large };
#pragma option pop

class DELPHICLASS TJamSystemImageList;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TJamSystemImageList : public Imglist::TCustomImageList 
{
	typedef Imglist::TCustomImageList inherited;
	
private:
	TJamImageListSize fSize;
	
protected:
	void __fastcall SetSize(TJamImageListSize aSize);
	virtual void __fastcall WriteState(Classes::TWriter* Writer);
	bool __fastcall GetShareImages(void);
	void __fastcall SetShareImages(bool val);
	virtual void __fastcall ReadState(Classes::TReader* Reader);
	
public:
	void __fastcall SetImageListHandle(void);
	__fastcall virtual TJamSystemImageList(Classes::TComponent* AOwner);
	int __fastcall GetIndexFromExtension(AnsiString Extension);
	int __fastcall GetIndexFromFileName(AnsiString FileName);
	int __fastcall GetFolderIconNumber(void);
	int __fastcall GetSpecialFolderIcon(TJamShellFolder folder);
	
__published:
	__property bool ShareImages = {read=GetShareImages, write=SetShareImages, nodefault};
	__property TJamImageListSize Size = {read=fSize, write=SetSize, nodefault};
	__property DrawingStyle ;
	__property OnChange ;
public:
	#pragma option push -w-inl
	/* TCustomImageList.CreateSize */ inline __fastcall TJamSystemImageList(int AWidth, int AHeight) : 
		Imglist::TCustomImageList(AWidth, AHeight) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomImageList.Destroy */ inline __fastcall virtual ~TJamSystemImageList(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define JAM_COMPONENT_VERSION " V2.4"
#define SF_UNKNOWN (TJamShellFolder)(0)
#define SID_IShellIconOverlay "{7D688A70-C613-11D0-999B-00C04FD655E1}"
#define SID_IShellFolder2 "{93F2F68C-1D1B-11D3-A30E-00C04F79ABD1}"
static const Shortint SHCOLSTATE_ONBYDEFAULT = 0x10;
static const Word SHCOLSTATE_HIDDEN = 0x100;
static const Shortint NoOverlay = 0xffffffff;
static const Shortint ShareOverlay = 0x0;
static const Shortint LinkOverlay = 0x1;
static const Word WM_GETISHELLBROWSER = 0x407;
extern PACKAGE _di_IMalloc Allocator;
extern PACKAGE _di_IShellFolder Desktop;
extern PACKAGE _ITEMIDLIST *DesktopIdList;
extern PACKAGE _ITEMIDLIST *NetHoodIdList;
extern PACKAGE Word CF_IDLIST;
extern PACKAGE bool IsNT;
extern PACKAGE AnsiString __fastcall GetStringFromStrRet(Shlobj::PItemIDList IdList, const _STRRET &
	str);
extern PACKAGE void __fastcall FreeStrRet(const _STRRET &str);
extern PACKAGE Shlobj::PItemIDList __fastcall ConcatItemIdLists(Shlobj::PItemIDList ID1, Shlobj::PItemIDList 
	ID2);
extern PACKAGE Shlobj::PItemIDList __fastcall CopyItemIdList(Shlobj::PItemIDList ID);
extern PACKAGE unsigned __fastcall GetItemIdListCount(Shlobj::PItemIDList P);
extern PACKAGE Shlobj::PItemIDList __fastcall GetItemIdListPart(Shlobj::PItemIDList Pidl, unsigned idx
	);
extern PACKAGE bool __fastcall PidlsEqual(Shlobj::PItemIDList pidl1, Shlobj::PItemIDList pidl2);
extern PACKAGE Shlobj::PItemIDList __fastcall GetIdListFromPath(_di_IShellFolder Shlfolder, AnsiString 
	path);
extern PACKAGE AnsiString __fastcall GetFriendlyName(AnsiString fullpath);
extern PACKAGE AnsiString __fastcall GetMyDocumentsPath(void);
extern PACKAGE bool __fastcall EnableAutoComplete(Stdctrls::TEdit* Edit, bool FileSystem, bool URL);
	
extern PACKAGE void __fastcall Register(void);

}	/* namespace Shellbrowser */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Shellbrowser;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ShellBrowser
