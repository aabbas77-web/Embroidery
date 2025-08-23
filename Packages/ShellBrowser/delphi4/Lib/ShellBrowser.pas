unit ShellBrowser;

// TShellBrowser is a Delphi component, which allows easy browsing through the
// shell name space of Windows 95/NT. For every object it can show the explorer
// context menu, the properties dialog, the correct icon, etc. So it is easy to
// add typical Win95 functions to your application and you can build an explorer
// like application with only a few lines of code.
//
// Author: Joachim Marder, JAM Software
// E-mail: marder@jam-software.com
// Copyright (c) 1997-2000 by Joachim Marder
//

interface
{$R ShellBrowser.res}
{$BOOLEVAL OFF}
{$I VER.INC}
{$IFDEF _CPPB_4_UP}
  {$HPPEMIT '#define NO_WIN32_LEAN_AND_MEAN' }
  {$HPPEMIT '#include <shlobj.hpp>' }
  {$HPPEMIT '#define _WIN32_IE 0x0500' }
{$ENDIF}

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ShellApi, Menus, ComCtrls, Shlobj, ActiveX, AxCtrls, DirMon, StdCtrls
{$ifdef _VCL_4_UP}
  ,ImgList
{$endif}
  ;

{$IFDEF _CPPB_3_UP}
  {$ObjExportAll On}
{$ENDIF}


const
  JAM_COMPONENT_VERSION = ' V2.4';

type
  TJamShellFolder = (SF_FILESYSTEMFOLDER, SF_BITBUCKET, SF_CONTROLS, SF_DESKTOP,
                     SF_DESKTOPDIRECTORY, SF_DRIVES, SF_FONTS, SF_NETHOOD, SF_NETWORK,
                     SF_PERSONAL, SF_PRINTERS, SF_PROGRAMS, SF_RECENT, SF_SENDTO,
                     SF_STARTMENU, SF_STARTUP, SF_TEMPLATES, SF_FAVORITES,
                     SF_COMMON_STARTMENU, SF_COMMON_STARTUP, SF_COMMON_DESKTOPDIRECTORY,
                     SF_APPDATA, SF_PRINTHOOD
                     {$ifdef _VCL_4_UP}
                     , SF_COMMON_FAVORITES, SF_INTERNET_CACHE, SF_COOKIES, SF_HISTORY
                     {$endif}
                   );

const  SF_UNKNOWN = SF_FILESYSTEMFOLDER;

{$ifndef _VCL_40_UP}
  // IShellIconOverlay interface not present in the header files of VCL3
  SID_IShellIconOverlay    = '{7D688A70-C613-11D0-999B-00C04FD655E1}';
type
  IShellIconOverlay = interface(IUnknown)
    [SID_IShellIconOverlay]
    function GetOverlayIndex(pidl: PItemIDList; out pIndex: Integer): HResult; stdcall;
    function GetOverlayIconIndex(pidl: PItemIDList; out pIconIndex: Integer): HResult; stdcall;
  end;
{$endif}

const
{$ifdef _VCL_35_UP}
  // Define some interfaces
  {$EXTERNALSYM IID_IShellDetails}
  {$EXTERNALSYM IID_IDataObject}
  {$EXTERNALSYM IID_IDropTarget}
  {$EXTERNALSYM IID_IDropSource}
  {$EXTERNALSYM IID_IShellFolder2}
  {$EXTERNALSYM IID_IPersistFile}
  {$EXTERNALSYM IID_IShellIconOverlay}
  {$EXTERNALSYM HDropFormatEtc}
{$endif}
  IID_IDataObject:    TGUID = (D1:$0000010E;D2:$0000;D3:$0000;D4:($C0,$00,$00,$00,$00,$00,$00,$46));
  IID_IDropTarget:    TGUID = (D1:$00000122;D2:$0000;D3:$0000;D4:($C0,$00,$00,$00,$00,$00,$00,$46));
  IID_IDropSource:    TGUID = (D1:$00000121;D2:$0000;D3:$0000;D4:($C0,$00,$00,$00,$00,$00,$00,$46));
  IID_IShellDetails:  TGUID = (D1:$000214EC;D2:$0000;D3:$0000;D4:($C0,$00,$00,$00,$00,$00,$00,$46));
  IID_IShellFolder2:  TGUID = (D1:$93f2f68c;D2:$1d1b;D3:$11d3;D4:($a3,$0e,$00,$c0,$4f,$79,$ab,$d1));
  IID_IPersistFile:   TGUID = (D1:$0000010B;D2:$0000;D3:$0000;D4:($C0,$00,$00,$00,$00,$00,$00,$46));
  IID_IShellIconOverlay:TGUID= SID_IShellIconOverlay;


  HDropFormatEtc: TFormatEtc = (cfFormat: CF_HDROP;
    ptd: nil; dwAspect: DVASPECT_CONTENT; lindex: -1; tymed: TYMED_HGLOBAL);

type
{$ifdef _DELPHI_3}
  IContextMenu_2 = interface(IContextMenu) // The definition in Delphi 3 is wrong
    [SID_IContextMenu2]
    function HandleMenuMsg(uMsg: UINT; wparam, lparam: UINT): HResult; stdcall;
  end;
{$else}
  IContextMenu_2 = IContextMenu2;
{$endif}

{$ifndef _VCL_6_UP}
const
  SID_IShellFolder2        = '{93F2F68C-1D1B-11D3-A30E-00C04F79ABD1}';
  // Some constants for IShellFolders.GetDefaultColumnState
  SHCOLSTATE_ONBYDEFAULT  = $00000010;   // should on by default in details view
  SHCOLSTATE_HIDDEN       = $00000100;   // not displayed in the UI
type
  TShellDetails = packed record
    fmt: Integer; // Alignment
    cxChar: Integer; // Default width
    str: TStrRet;  // Column caption
  end;
  PShellDetails = ^TShellDetails;

  TSHColumnID = record
    fmtid: TGUID;
    pid:   DWORD;
  end;
  PSHColumnID = ^TSHColumnID;

  IShellFolder2 = interface(IShellFolder)
    [SID_IShellFolder2]
    function EnumSearches(ppEnum: Pointer): HResult; stdcall;
    function GetDefaultColumn(dwReserved: DWORD; var pSort: ULONG; var pDisplay: ULONG): HResult; stdcall;
    function GetDefaultColumnState(iColumn: UINT; var pcsFlags: DWORD): HResult; stdcall;
    function GetDefaultSearchGUID(var lpGUID: TGUID): HResult; stdcall;
    function GetDetailsEx(pidl: PItemIdList; pscid: PSHColumnID; pv: Variant): HResult; stdcall;
    function GetDetailsOf(pidl: PItemIdList; col: UINT; var info: TShellDetails): HResult; stdcall;
    function MapNameToSCID(pwszName: PWideChar; var pscid: TSHColumnID): Hresult; stdcall;
  end;//IShellFolder2
{$endif}

type
  IShellDetails = interface(IUnknown)
    function GetDetailsOf( pidl: PItemIdList;  col: UINT;  var info: TShellDetails ): HResult; stdcall;
    function ColumnClick( col: UINT ): HResult; stdcall;
  end;

//////////////////////////////// SHELLBROWSER //////////////////////////////////
  TOnContextMenuSelectEvent = procedure(const command: String; var execute: Boolean) of object;

  TShellBrowser = class(TComponent)
  private
    { Property variables }
    FDirectory     : String;       // Path of the current folder
    FFolderIdList  : PItemIdList;  // Absolute ItemIdList of the current folder
    FShellFolder   : IShellFolder; // IShellFolder Interface of the current folder
    FItemIDList    : PItemIDList;  // Relative ItemIdList of the active object
    FAbsoluteIdList: PItemIdList;  // Cache for the absolute IdList of the currebt object
    Objects        : IEnumIdList;  // For Enumerating Objects in a Folder
    FFileSystemOnly: Boolean;      // Show Only file system objects
    FMultiObjects  : TStringList;  // StringList for Multiple objects
    FSortDirection : Integer;      // Sort direction for HandleColumnClick
    FLastColSorted : Integer;      // Last Column Sorted by HandleColumnClick
    FFilter        : TStrings;     // Filter for the visible files, e.g. *.doc
    ActiveIContextMenu: IContextMenu_2; // For handling submenus of the context menu
    ActiveDelphiContextMenu: TPopupMenu; // dto
    Ishd           : IShellDetails;    // IShellDetails interface for the current folder
    IShF2          : IShellFolder2;    // IShellFolder2 interface (including IShellDetails intertface in Win2000 and later
    TriedIshd      : Boolean;
    FindData       : TWin32FindData;
    OriginalWndProc: TWndMethod;
    FileSystemFolder: Boolean;      // For FillListView
    ColumnWidth    : Array [0..15] of Integer;
    fOnRename      : TNotifyEvent;
    fOnFileChange  : TNotifyEvent;
    fOnContextMenuSelect: TOnContextMenuSelectEvent;
    fDirMon        : TDirMon;
    fInitialized   : Boolean;       // Component Initialized?
    fReadOnly      : Boolean;

    procedure GetPidlsFromMultiObjects(var pidls: Array of PItemIdList);
    procedure SendToWindowProc(var Message: TMessage);
    function  FilterMatch: Boolean;

  protected
    procedure SetDirectory(Path: String);
    procedure SetObjectName(ObjName: String);
    procedure SetItemIdList(IdList: PItemIdList);
    procedure SetFolderIdList(IdList: PItemIdList);
    procedure SetItemIdList2(IdList: DWORD);
    procedure SetFolderIdList2(IdList: DWORD);
    procedure SetShellfolder(Folder: IShellfolder);
    procedure SetAbsoluteItemIdList(IdList: PItemIdList);
    function  GetIconNumber: Integer;
    function  GetSelectedIconNumber: Integer;
    function  GetItemIdList: PItemIdList;
    function  GetFolderIdList: PItemIdList;
    function  GetItemIdList2: DWORD;
    function  GetFolderIdList2: DWORD;
    function  GetObjectName: string;
    function  GetIShellDetails: Boolean;
    function  GetDomain: String;
    function  GetAbsoluteItemIdList: PItemIdList;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetFilter(aFilter: String);
    function  GetFilter: String;
    function  GetVersion: String;
    procedure SetVersion(s: String);
    procedure SetOnFileChange(Event: TNotifyEvent);
    procedure FileChange(Sender: TObject);
    function  GetWinHandle: THandle;
    property  WinHandle: THandle read GetWinHandle;

  public
    // Constructor of TShellBrowser
    constructor Create(AOwner: TComponent); override;
    // Destructor of TShellBrowser
    destructor  Destroy; override;
    // Enumerate the next object in the current folder
    function  Next: Boolean;
    // Shows the context menu for the current object at Point lppt of the screen
    function  ShowContextMenu(lppt: TPoint; M: TPopUpMenu): String;
    // Invokes a command of the context menu of the current object
    function  InvokeContextMenuCommand(verb: String): Boolean;
    // Returns, if the current object is a folder
    function  IsFolder: Boolean;
    // Returns, if the current object is a folder which has subfolders
    function  HasSubFolders: Boolean;
    // Returns, if the current object can be renamed
    function  CanRename: Boolean;
    // Returns, if the current object is a hidden object
    function IsHidden: Boolean;
    // Returns True, if the current object is a link
    function IsLink: Boolean;
    // Returns the target path, if the current object is a link to a folder, emtpy string otherwise
    function IsLinkToFolder: String;
    // Get Attributes of the current object
    function GetAttributes(Attributes: UINT): UINT;
    // Displays the windows BrowseForFolder Dialog
    function  BrowseForFolder(Msg: String): Boolean;
    // Gets the well formatted shell name of the current object
    function  GetShellObjectName: String;
    // Selects the parent folder of the current folder
    function  SelectParent: Boolean;
    // Browses into the current object
    function  BrowseObject: Boolean;
    // Fills a ListView with data of the current folder
    function  FillListView(ListView: TListView; Details: Boolean): Boolean;
    // Handles a Column Click on a ListView Column, Called autimatically if FillListView was Calles
    procedure HandleColumnClick(Sender: TObject; Column: TListColumn);
    // Renames the current object
    procedure RenameObject(var NewName: String);
    // Shows the net connection dialog. which allows thr user to connect a network drive
    function  ShowNetConnectionDialog: Boolean;
    // Allows you to select special (non file system) folders
    function BrowseSpecialFolder(folder: TJamShellFolder): Boolean;
    // Number of the icon for the current file in the system image list
    property IconNumber  : Integer read GetIconNumber;
    property SelectedIconNumber: Integer read GetSelectedIconNumber;
    // Returns the icon index of the desktop icon
    function  GetDesktopIconIndex: Integer;
    // Returns the overlay index of the current object;
    function GetOverlayIndex: Integer;
    // Returns the language dependant name of the Desktop
    function  GetDesktopName: String;
    // ItemIdList of the current Folder
    property FolderIdList: PItemIdList read GetFolderIdList write SetFolderIdList;
    // ItemIdList of the current object
    property ItemIdList : PItemIDList read GetItemIdList write SetItemIdList;
    // Absolute ItemIdList of the current object
    property AbsoluteItemIdList: PItemIDList read GetAbsoluteItemIdList write SetAbsoluteItemIdList;
    // IShellFolder interface for the current folder
    property ShellFolder : IShellfolder read FShellFolder write SetShellFolder;
    // Set this property to True to prevent operations like 'delete', 'cut', 'paste'
    property ReadOnly: Boolean read fReadOnly write fReadOnly;
    // Returns a TShellFolder constant if the current Folder is a special folder, SF_UNKNOWN otherwise
    function IsSpecialFolder: TJamShellFolder;
    // Returns a TShellFolder constant if the current Object is a special folder, SF_UNKNOWN otherwise
    function IsSpecialObject: TJamShellFolder;
    // Returns the Text which should appear in column col of a ListView
    function GetColumnText(col: Integer; Header: Boolean): String;
    // Returns the Alignment and size of column col
    function GetColumnInfo(col: Integer; var Width: Integer): TAlignment;
    // Handles messages of popup messages, neccessary to show Send To submenu correct
    procedure HandlePopupMessages(var Message: TMessage);
    // made public for internal use
    procedure Loaded; override;


  published
    property Filter      : String read GetFilter write SetFilter;
    // Path of the current folder
    property Folder      : String read FDirectory write SetDirectory;
    // Name of the current object in Folder
    property ObjectName  : String read GetObjectName write SetObjectName;
    // Show only file system objects or not
    property FileSystemOnly: Boolean read FFileSystemOnly write FFileSystemOnly;
    // Handles operations for multiple objects
    property MultiObjects: TStringList read FMultiObjects write FMultiObjects;
    // Version information for this component
    property Version     : String read GetVersion write SetVersion stored false;
    // OnRename Event is fired if the user selected the "Rename" menu item from the context menu
    property OnRename: TNotifyEvent read fOnRename write fOnRename;
    // ONFileChange event occurs, if a file name change occured in the current directory
    property OnFileChange: TNotifyEvent read fOnFileChange write SetOnFileChange;
    // This event occurs when the user has selected an item of the context menu
    property OnContextMenuSelect: TOnContextMenuSelectEvent read fOnContextMenuSelect write fOnContextMenuSelect;
  end;

  EShellBrowserError = class(Exception);


  TJamImageListSize = (si_small, si_large);

{$ifdef _VCL_4_UP}
  TJamSystemImageList = class(TCustomImageList)
{$else}  // Under Delphi 3 we must derive from TImageList
  TJamSystemImageList = class(TImageList)
{$endif}
  private
    fSize: TJamImageListSize;
  protected
    procedure SetSize(aSize: TJamImageListSize);
    procedure WriteState(Writer: TWriter); override;
    function  GetShareImages: Boolean;
    procedure SetShareImages(val: Boolean);
    procedure ReadState(Reader: TReader); override;
  public
    procedure SetImageListHandle;
    constructor Create(AOwner: TComponent); override;
    function GetIndexFromExtension(Extension: String): Integer;
    function GetIndexFromFileName(FileName: String): Integer;
    function GetFolderIconNumber: Integer;
    function GetSpecialFolderIcon(folder: TJamShellFolder): Integer;
  published
    property ShareImages: Boolean read GetShareImages  write SetShareImages nodefault;
    property Size: TJamImageListSize read fSize write SetSize;
    property DrawingStyle;
    property OnChange;
  end;

const

  // Overlay Indexes
  NoOverlay = -1;
  ShareOverlay = 0;
  LinkOverlay = 1;

{$ifndef _VCL_4_UP}
  SFGAO_HIDDEN = $00080000;  // Missing in Delphi 3 and C++ Builder 3
{$endif}

  WM_GETISHELLBROWSER = (WM_USER+7);

var
  Allocator : IMalloc;          // Memory allocator of the shell
  Desktop   : IShellFolder;     // IShellFolder Interface of the Desktop
  DesktopIdList  : PItemIdList; // Absolute ItemIdList of the Desktop folder
  NetHoodIdList : PItemIdList;  // Fully qualified ItemIdList of the Net Hood
  CF_IDLIST: TClipFormat;       // Registered clipboard format for ItemIdLists
  IsNT      : Boolean;          // True if the current operating system is Windows NT or later

  function  GetIdListFromPath(Shlfolder: IShellfolder; path: string): PItemIdList;
  function  ConcatItemIdLists(ID1, ID2: PItemIDList): PItemIDList;
  function  CopyItemIdList(ID: PItemIDList): PItemIdList;
  function  GetItemIdListCount(P: PItemIdList): Cardinal;
  function  GetItemIdListPart(Pidl: PItemIdList; idx: Cardinal): PItemIdList;
  function  GetFriendlyName(fullpath: String): String;
  function  PidlsEqual(pidl1, pidl2 : PItemIdList): Boolean;
  function  GetMyDocumentsPath: String;
  function  GetStringFromStrRet(IdList: PItemIdList; str: TStrRet): String;//For internal use
  function  EnableAutoComplete(Edit: TEdit; FileSystem: Boolean; URL: Boolean): Boolean;
  procedure FreeStrRet(const str: TStrRet);// For internal use
  procedure Register;


implementation /////////////////////////////////////////////////////////////////////////////////////

uses ShellStrings, CommCtrl;

const
{$ifdef _VCL_4_UP}
  SpecialFolders : Array [0..26] of Integer =
{$else}
  SpecialFolders : Array [0..22] of Integer =
{$endif}
    (CSIDL_DRIVES, CSIDL_BITBUCKET,
     CSIDL_CONTROLS, CSIDL_DESKTOP, CSIDL_DESKTOPDIRECTORY, CSIDL_DRIVES,
     CSIDL_FONTS, CSIDL_NETHOOD, CSIDL_NETWORK, CSIDL_PERSONAL,
     CSIDL_PRINTERS, CSIDL_PROGRAMS, CSIDL_RECENT, CSIDL_SENDTO,
     CSIDL_STARTMENU, CSIDL_STARTUP, CSIDL_TEMPLATES, CSIDL_FAVORITES,
     CSIDL_COMMON_STARTMENU, CSIDL_COMMON_STARTUP,
     CSIDL_COMMON_DESKTOPDIRECTORY, CSIDL_APPDATA, CSIDL_PRINTHOOD
     {$ifdef _VCL_4_UP}
     , CSIDL_COMMON_FAVORITES, CSIDL_INTERNET_CACHE, CSIDL_COOKIES, CSIDL_HISTORY
     {$endif}
    );

type TShAutoCompleteFunc = function(hwndEdit: HWND; dwFlags: dWord): LongInt; stdcall;

var fShAutoComplete: TShAutoCompleteFunc = nil;


function GetStringFromStrRet(IdList: PItemIdList; str: TStrRet): String;
begin
  case str.uType of
    STRRET_CSTR:
      Result := str.cstr;
    STRRET_OFFSET:
      if Assigned(IdList) then
        SetString(Result, PChar(UINT(IdList)+str.uOffset), StrLen(PChar(UINT(IdList)+str.uOffset)));
    STRRET_WSTR:
        Result := WideCharToString(str.pOleStr);
  end;
end;//GetStringFromStrRet

procedure FreeStrRet(const str: TStrRet);
begin
  if (str.uType = STRRET_WSTR) and Assigned(str.pOleStr) then
    //CoTaskMemFree(str.pOleStr);
    Allocator.Free(str.pOleStr);
end;//FreeStrRet

// Allocates the memory for a new ItemIdList
function CreatePIDL(Size: UINT): PItemIDList;
begin
  Result := Allocator.Alloc(Size);
  if Result <> NIL then
    FillChar(Result^, Size, #0);
end;

// Calculates the size of an ItemIdList
function GetPidlSize(pidl: PITEMIDLIST): integer;
begin
  Result := 0;
  if pidl <> nil then begin
    Inc(Result, SizeOf(pidl^.mkid.cb));
    while pidl^.mkid.cb <> 0 do begin
      Inc(Result, pidl^.mkid.cb);
      Inc(longint(pidl), pidl^.mkid.cb);
    end;
  end;
end;

// Concatenates two ItemIdLists, e.g. to make an absolute ItemIdList
function ConcatItemIdLists(ID1, ID2: PItemIDList): PItemIDList;
var S1, S2: UINT;
begin
  //if (ID2 = NIL) then begin Result := ID1; exit end;
  if (ID1 <> NIL) then
    S1 := GetPIDLSize(ID1) - SizeOf(ID1.mkid.cb)
  else
    S1 := 0;
  S2 := GetPidlSize(ID2);

  Result := CreatePIDL(S1 + S2);
  if Result <> NIL then begin
    if (ID1 <> NIL) then
      Move(ID1^, Result^, S1);
    if (ID2 <> NIL) then
      Move(ID2^, PChar(Result)[S1], S2);
  end;
end;//ConcatPIDLs

// Copys an ItemIdList into new memeory
function CopyItemIdList(ID: PItemIDList): PItemIdList;
var S: UINT;
begin
  if not Assigned(ID) then begin Result:=nil; exit end;
  S := GetPIDLSize(ID);
  Result := CreatePIDL(S);
  If Assigned(Result) then
    Move(ID^, Result^, S);
end;

// returns the number of elements in the gicen ItemIDList;
function GetItemIdListCount(P: PItemIdList): Cardinal;
begin
  result := 0;
  if (p = nil) then Exit;
  while PWord(p)^ <> 0 do
  begin
    Inc( PByte(p), PWord(p)^ );
    Inc( result );
  end;
end; {TPTIdListArray.GetCount}

// Retuens the part idx of the given ItemIdList
function GetItemIdListPart(Pidl: PItemIdList; idx: Cardinal): PItemIdList;
var p: Pointer;
    curidx: Cardinal;
begin
  p := Pidl;
  curidx := 0;
  while (PWord(p)^ <> 0) and (curidx <> idx) do
  begin
    Inc( PByte(p), PWord(p)^ );
    Inc( curidx );
  end;

  if (curidx = idx) then
  begin
    Result := Allocator.Alloc( PWord(p)^ + 2 );
    Move( p^, Result^, PWord(p)^ );
    PWord( UINT(Result) + PWord(p)^ )^ := 0;
  end
  else
    Result := nil;
end;//GetItemIdListPart

// Returns whether two ItemIdLists are equal or not
// This function uses undocumented stuff and was reported to fail for ItemIdLists
// of folders on network drives sometimes
function PidlsEqual(pidl1, pidl2 : PItemIdList): Boolean;
var i       : Integer;
    pByte1,
    pByte2  : ^Byte;
begin
  Result := False;
  if pidl1^.mkid.cb <> pidl2^.mkid.cb then exit;
  pByte1 := @(pidl1^.mkid.abID[0]);
  pByte2 := @(pidl2^.mkid.abID[0]);
  for i := 0 to pidl1^.mkid.cb-3 do begin  // -1 instead -3 doesn't work. Why?
    if pByte1^ <> pByte2^ then exit;
    Inc(pByte1);
    Inc(pByte2);
  end;//for
  Result := True;
end;//PidlsEqual


// Returns an ItemIDList for the specified path, relative to th specified ShellFolder
function GetIdListFromPath(Shlfolder: IShellfolder; path: string): PItemIdList;
var szOleChar: Array [0..MAX_PATH] of widechar;
    ulEaten,
    ulAttribs: ULONG;
    lpifq    : PItemIDList;
    hr       : HRESULT;
begin
  if not Assigned(ShlFolder) then ShlFolder := Desktop;
  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, PChar(path), -1, @szOleChar, sizeof(szOleChar));
  hr := ShlFolder.ParseDisplayName(0, nil, @szOleChar, ulEaten, lpifq, ulAttribs);
  if hr=NOERROR then Result := lpifq
  else Result := nil;
end;//GetIdListFromPath


function GetFriendlyName(fullpath: String): String;
var tmp1: array[0..MAX_PATH] of WideChar;
    tmp2: array[0..MAX_PATH] of Char;
    IdList: PItemIdList;
    eaten: ULONG;
    Attributes: ULONG;
begin
  Result := fullpath;
  StringToWideChar(fullpath, tmp1, High(tmp1));
  if Desktop.ParseDisplayName(0, nil, tmp1, eaten, IdList, Attributes) <> S_OK then exit;
  SHGetPathFromIdList(IdList, @tmp2[0]);
  Result := tmp2;
end;

function TestForSpecialFolder(pidl_1: PItemIdList): TJAmShellFolder;
var pidl_2: PItemIdList;
    f     : TJamShellFolder;
    hr    : HResult;
begin
  Result := SF_UNKNOWN;
  for f:= SF_BITBUCKET to SF_PRINTHOOD do
    try
      if SHGetSpecialFolderLocation(0, SpecialFolders[Ord(f)], pidl_2)=NOERROR then begin
        hr := DeskTop.CompareIds(0, pidl_1, pidl_2);
        if hr=0 then begin
          Result := f;
          break;//for
        end;
        Allocator.Free(pidl_2);
      end;//if
    except
    end;
end;

function GetMyDocumentsPath: String;
var pidl: PItemIdList;
    path: array [0..MAX_PATH] of char;
begin
  Result := '';
  if SHGetSpecialFolderLocation(0, CSIDL_PERSONAL, pidl)=NOERROR then begin
    if SHGetPathFromIdList(pidl, @path[0]) then
      Result := path;
  end;//if
end;//GetMyDocumentsPAth

function IsDrive(path: String): Boolean;
begin
  Result := (Length(path) in [2..3]) and (path[2] = ':')
end;//IsDrive

function FileOrFolderExists(path: String): Boolean;
var h: THandle;
    f: TWin32FindData;
begin
  h := FindFirstFile(PChar(path), f);
  if (h = INVALID_HANDLE_VALUE) and not ISDrive(path) then
    Result := False
  else begin
    Result := True;
    Windows.FindClose(h);
  end;
end;//FileOrFolderExists

function EnableAutoComplete(Edit: TEdit; FileSystem: Boolean; URL: Boolean): Boolean;
const
  SHACF_DEFAULT = $0;
  SHACF_FILESYSTEM  = $1;
  SHACF_URLHISTORY  = $2;
  SHACF_URLMRU  = $4;
  SHACF_URLALL = (SHACF_URLHISTORY Or SHACF_URLMRU);
  SHACF_USETAB = $8;
  SHACF_AUTOSUGGEST_FORCE_ON = $10000000;
  SHACF_AUTOSUGGEST_FORCE_OFF = $20000000;
  SHACF_AUTOAPPEND_FORCE_ON = $40000000;
  SHACF_AUTOAPPEND_FORCE_OFF = $80000000;
var flags: DWord;
begin
  Result := False;
  flags := 0;
  if FileSystem then flags := flags or SHACF_FILESYSTEM;
  if URL then flags := flags or SHACF_URLALL;
  if flags=0 then flags := SHACF_AUTOSUGGEST_FORCE_OFF or SHACF_AUTOAPPEND_FORCE_OFF or SHACF_FILESYSTEM or SHACF_URLALL
  else flags := flags or SHACF_USETAB;
  if Assigned(fShAutoComplete) then
    Result := fSHAutoComplete(Edit.Handle, flags) = 0;
end;//EnableAutoComplete

/////////////////////// TShellBrowser /////////////////////////////////////

// Constructor of TShellBrowser
constructor TShellBrowser.Create(AOwner: TComponent);
begin
  Inherited Create(AOwner);
  fInitialized    := False;
  fFileSystemOnly := False;
  Objects         := nil;
  FItemIdList     := nil;
  FFolderIdList   := nil;
  FShellFolder    := nil;
  OriginalWndProc := nil;
  FileSystemFolder:=False;
  FLastColSorted := -1;
  MultiObjects   := TStringList.Create;
  FFilter        := TStringList.Create;
  FFilter.Add('*');
  Folder := '';
  fReadOnly := False;
end;


destructor TShellBrowser.Destroy;
begin
  if Assigned(FItemIdList) then Allocator.Free(FItemIdList);
  if Assigned(FFolderIdList) then Allocator.Free(FFolderIdList);
  MultiObjects.Free;
  FFilter.Free;
  Allocator._Release;
  if (Owner is TForm) and Assigned(OriginalWndProc) then (Owner as TForm).WindowProc := OriginalWndProc;
  Inherited;
end;


procedure TShellBrowser.Loaded;
begin
  Inherited;
  if Owner is TForm then begin
    OriginalWndProc:= (Owner as TForm).WindowProc;
    (Owner as TForm).WindowProc := SendToWindowProc;
  end;
  fInitialized := True;
end;//Loaded

// Get a valid window handle
function TShellBrowser.GetWinHandle: THandle;
begin
  if (Owner is TWinControl) and fInitialized then
    Result := TWinControl(Owner).Handle
  else
    Result := Application.Handle;
end;//GetWinHandle

procedure TShellBrowser.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
end;

// Retrieve the well formatted shell name for the current object
function TShellBrowser.GetShellObjectName: String;
var str: TSTRRET;
begin
  if not Assigned(FItemIdList) then exit;
  if (NOERROR=FShellFolder.GetDisplayNameOf(FItemIdList, SHGDN_NORMAL, str)) then
  Result := GetStringFromStrRet(FItemIdList, str);
  if Result='' then Result := ObjectName;
  FreeStrRet(str);
end;

// Returns, if the current object is a folder or not
function TShellBrowser.IsFolder: Boolean;
var attr    : UINT;
begin
  if not Assigned(FItemIdList) then begin Result := False; exit end;
  attr := SFGAO_FOLDER or SFGAO_HASSUBFOLDER;
  ShellFolder.GetAttributesOf(1, FItemIdList, attr);
  Result := (attr AND SFGAO_FOLDER) <> 0;
end;//IsFolder

// Returns True, if the current object is a link to folder
function TShellBrowser.IsLinkToFolder: String;
var ishl : IShellLink;
    ipf  : IPersistFile;
    wsz  : array [0..MAX_PATH] of WideChar;
    tmp  : array [0..MAX_PATH] of Char;
    F    : TWin32FindData;
begin
  Result := '';
  if not IsLink then exit;
  if Failed(CoCreateInstance(CLSID_ShellLink, nil, CLSCTX_INPROC_SERVER, IID_IShellLinkA, ishl)) then exit;
  if Failed(ishl.QueryInterface(IID_IPersistFile, ipf )) then exit;
  if Failed(ipf.Load(StringToWideChar(Folder+ObjectName, @wsz[0], High(wsz)), STGM_READ)) then exit;
  if Failed(ishl.GetPath(@tmp[0], High(tmp), F, 0)) then exit;
  if (F.dwFileAttributes AND FILE_ATTRIBUTE_DIRECTORY) > 0 then
    Result := tmp;
end;//IsLinkToFolder

// Returns, if the current object is a folder or not
function TShellBrowser.HasSubFolders: Boolean;
var attr    : UINT;
begin
  attr := SFGAO_FOLDER or SFGAO_HASSUBFOLDER;
  ShellFolder.GetAttributesOf(1, FItemIdList, attr);
  Result := (attr AND SFGAO_HASSUBFOLDER) <> 0;
end;//IsFolder

// Returns, if the current object is a hidden object
function TShellBrowser.IsHidden: Boolean;
begin
  Result := GetAttributes(SFGAO_HIDDEN) AND SFGAO_HIDDEN <> 0;
end;//IsHidden

// Returns, if the current object is a hidden object
function TShellBrowser.IsLink: Boolean;
begin
  Result := GetAttributes(SFGAO_LINK) AND SFGAO_LINK <> 0;
end;//IsLink

// Returns domain name like '\\domain' if the current folder is a domain, empty string otheerwise
function TShellBrowser.GetDomain: String;
var pnr: PNetResource;
    nr_size: Cardinal;
    hr: HResult;
begin
  Result := '';
  nr_size := sizeof(TNetResource) + MAX_PATH;
  try GetMem(pnr, nr_size);
  except exit end;
  hr := SHGetDataFromIDList(ShellFolder, fItemIdList, SHGDFIL_NETRESOURCE, pnr, nr_size);
  if hr=NO_ERROR then begin
    if (pnr.dwDisplayType in [RESOURCEDISPLAYTYPE_DOMAIN,RESOURCEDISPLAYTYPE_SERVER]) then begin
      Result := pnr.lpRemoteName;
    end;//if
  end;//if
  FreeMem(pnr);
end;//IsDomain

// Makes the parent folder the active folder and the current folder the current object
function TShellBrowser.SelectParent: Boolean;
begin
  AbsoluteItemIdList := FolderIdList;
  Result := True;
end;//SelectParent

// Shows the Windows standard dialog to choose a folder
function  TShellBrowser.BrowseForFolder(Msg: String): Boolean;
var IdList: PItemIdList;
    BrowseInfo: TBrowseInfo;
    DisplayName: Array [0..MAX_PATH] of Char;
begin
  IdList := nil;
  SHGetSpecialFolderLocation(WinHandle, $FEFE{CSIDL_DESKTOPEXPANDED, undocumented by MS}, IdList);// <> NOERROR) then begin Result:=False; exit end;
  With BrowseInfo Do Begin
    hWndOwner := WinHandle;
    pidlRoot  := IdList;
    pszDisplayName := DisplayName;
    lpszTitle := PChar(Msg);
    ulFlags   := 0; if FileSystemOnly then ulFlags := ulFlags + BIF_RETURNONLYFSDIRS;
    lpfn      := Nil;
    lparam    := 0;
  End;
  IDList := SHBrowseForFolder(BrowseInfo);
  Result := True;
  If Assigned(IdList) then SetFolderIdList(IdList)
  else Result := False;
end;

// Convert Strings in the MultiObjects StringList to PItemIdLists
procedure TShellBrowser.GetPidlsFromMultiObjects(var pidls: Array of PItemIdList);
var TempIdList: PItemIdList;
    counter   : Integer;
begin
  TempIdList := ItemIdList;
  for counter:=0 to MultiObjects.Count-1 do begin
      pidls[counter] := GetIdListFromPath(ShellFolder, MultiObjects.Strings[counter]);
      if not Assigned(pidls[counter]) then begin // Use more difficult method
        ObjectName := MultiObjects[counter];
        pidls[counter] := CopyItemIdList(FItemIdList);
      end;
  end;
  SetItemIdList(TempIdList);
end;

// Shows the explorer context menu for the current object
function TShellBrowser.ShowContextMenu(lppt: TPoint; M: TPopUpMenu): String;

  function CopyMenuItem(M: TMenuItem): TMenuItem;
  begin
    Result := NewItem(M.Caption, M.ShortCut, False, True, M.OnClick, 0, M.Name+'2');
    Result.Break      := M.Break;
    Result.Checked    := M.Checked;
    Result.Default    := M.Default;
    Result.Enabled    := M.Enabled;
    Result.GroupIndex := M.GroupIndex;
    Result.HelpContext:= M.HelpContext;
    Result.RadioItem  := M.RadioItem;
    Result.Tag        := M.Tag;
    Result.Visible    := M.Visible;
{$ifdef _VCL_4_UP}
    Result.ImageIndex := M.ImageIndex;
{$endif}
  end;//CopyMenuItem

var hr      : HRESULT;
    lpcm    : IContextMenu;
    ContextMenuFlags: UINT;
    idcmd   : WORD;
    pidls   : Array [0..60000] of PItemIdList;
    counter : Integer; // counts the number of ItemIdList in pidls
    cmi     : TCMInvokeCommandInfo;
    cmd_verb: Array [0..MAX_PATH] of char;
    i,j     : Integer;
    Menu    : TPopUpMenu;
    OldShowHint: TNotifyEvent;  // to store Applicatio.OnHint in order to turn it off
    filename: String;
    ExecuteCommand: Boolean;
begin
  Result := '';
  ExecuteCommand := True;
  // Copy User Defined Popup Menu
  Menu := TPopUpMenu.Create(Self);
  if Assigned(M) then
    for i:=0 to M.Items.Count-1 do
      //if M.Items[i].Visible then
      begin
        Menu.Items.Add(CopyMenuItem(M.Items[i]));
        if M.Items[i].Count>0 then // Submenu?
          for j:=0 to M.Items[i].Count-1 do
            //if M.Items[i].Items[j].Visible then
              Menu.Items[i].Add(CopyMenuItem(M.Items[i].Items[j]));
      end;//if


  OldShowHint := Application.OnHint;
  Application.OnHint := nil;
  // Get ItemIdList(s)
  if MultiObjects.Count>0 then begin
    try // next line may fail
      GetPidlsFromMultiObjects(pidls);
      counter := MultiObjects.Count;
      filename := Folder+MultiObjects.Strings[0];   // Store the file name and path
    finally
      MultiObjects.Clear;
    end;//try
  end {if} else begin
    pidls[0] := CopyItemIdList(FItemIdList);
    filename := Folder+ObjectName;   // Store the file name and path
    counter := 1;
  end;
  // Get Shell Context Menu      IShellView
  try
    hr := ShellFolder.GetUIObjectOf(WinHandle, counter, pidls[0], IID_IContextMenu, nil, Pointer(lpcm));
    If SUCCEEDED(hr) then begin
      if not (lpcm.QueryInterface(IID_IContextMenu2, ActiveIContextMenu) = S_OK) then begin
        ActiveIContextMenu := nil;
      end;
      if Menu.Handle<>0 then begin
        ActiveDelphiContextMenu := Menu; // for handling the messages
        ContextMenuFlags := CMF_EXPLORE;
        if Assigned(OnRename) then ContextMenuFlags := ContextMenuFlags + CMF_CANRENAME;
        hr := lpcm.QueryContextMenu(Menu.Handle, 0, 1, $7fff, ContextMenuFlags);
        if Succeeded(hr) then begin
           // Call OnPopup event handler
           if Assigned(M) and Assigned(M.OnPopup) then M.OnPopup(M);
           // Show context menu
           idCmd := WORD(TrackPopupMenu(Menu.Handle, TPM_LEFTALIGN or TPM_RETURNCMD or TPM_RIGHTBUTTON, lppt.x, lppt.y, 0, TWinControl(Owner).Handle, nil));
           //if idCmd=0 then ShowMessage('Error: '+IntToStr(GetLastError));
           for i:=0 to Menu.Items.Count-1 do begin
             if (idcmd=Menu.Items[i].Command) and Assigned(Menu.Items[i].OnClick) then
               begin Menu.Items[i].OnClick(Menu.Items[i]); idcmd:=0 end;
             if M.Items[i].Count>0 then  // Submenu?
               for j:=0 to M.Items[i].Count-1 do
                 if (idcmd=Menu.Items[i].Items[j].Command) and Assigned(Menu.Items[i].Items[j].OnClick) then
                   begin Menu.Items[i].Items[j].OnClick(Menu.Items[i]); idcmd:=0 end;
           end;
           if idcmd>0 then with cmi do begin
             lpcm.GetCommandString(idcmd-1, GCS_VERB, nil, @cmd_verb, MAX_PATH);
             Result := PChar(@cmd_verb);// Get command string
             if (CompareText(Result, 'rename')=0) and Assigned(OnRename) then
               OnRename(Self)
             else begin
               if Assigned(OnContextMenuSelect) then
                 OnContextMenuSelect(Result, ExecuteCommand)
               else
                 ExecuteCommand := not (ReadOnly and ((CompareText(Result, 'delete')=0) or (CompareText(Result, 'cut')=0) or (CompareText(Result, 'paste')=0)));
               if ExecuteCommand then begin
                 cbSize    := sizeof(cmi);
                 fMask     := 0;
                 hwnd      := WinHandle;
                 lpVerb    := PChar(idCmd -1);
                 dwHotkey  := 0;
                 hicon     := 0;
                 nShow     := SW_SHOWNORMAL;
                 lpParameters:=nil;
                 lpDirectory:=nil;
                 hr := lpcm.InvokeCommand(cmi);
                 if not SUCCEEDED(hr) then Result := '';//no command string on failure
               end//if
               else Result := '';
             end;//else
           end;//if
        end;//if Succeeded(hr)
      end;//if Menu.Handle<>0
      Application.OnHint := OldShowHint;
    end;//if Succeeded(hr)
  finally
    Menu.Destroy;
    ActiveIContextMenu := nil;
    ActiveDelphiContextMenu := nil;
    for i:=0 to counter-1 do
      Allocator.Free(pidls[i]);
  end;
  // Check if it is really deleted
  if (UpperCase(Result)='DELETE') and FileOrFolderExists(filename) then
    Result := '';
end;

function TShellBrowser.GetAttributes(Attributes: UINT): UINT;
begin
  if ShellFolder.GetAttributesOf(1, FItemIdList, Attributes) = NO_ERROR then
    result := Attributes
  else
    result := 0;
end;//GetAttributes

function TShellBrowser.InvokeContextMenuCommand(verb: String): Boolean;
var hr       : HRESULT;
    lpcm     : IContextMenu;
    cmi      : TCMInvokeCommandInfo;
    Popup    : HMENU;
    MenuCmd  : Integer;
    pidls    : Array [0..60000] of PItemIdList; // Space for the PItemIdLists
    counter  : Integer; // counts the number of ItemIdList in pidls
    filename : String;  // space for name and full path of the object
    oldcursor: Integer;
    ExecuteCommand: Boolean;
begin
  // Get Shell Context Menu
  Result:=False;
  ExecuteCommand := True;
  if Assigned(OnContextMenuSelect) then OnContextMenuSelect(verb, ExecuteCommand);
  if not ExecuteCommand then exit;

  if not (Assigned(FItemIdList) or (MultiObjects.Count>0)) or not Assigned(ShellFolder) then exit;
  if verb='' then verb:='default';
  if (UpperCase(verb)='DELETE') and (MultiObjects.Count<=0) and (GetAttributes(SFGAO_CANDELETE) and SFGAO_CANDELETE = 0) then //this object cannot be deleted
      exit;
  oldcursor := Screen.Cursor;
  Screen.Cursor := crHourGlass;

  // Get ItemIdList(s)
  if MultiObjects.Count>0 then begin
    GetPidlsFromMultiObjects(pidls);
    counter := MultiObjects.Count;
    filename := Folder+MultiObjects.Strings[0];   // Store the file name and path
    MultiObjects.Clear;
  end else begin
    pidls[0] := FItemIdList;
    counter := 1;
    filename := Folder+ObjectName;
  end;
  // Get Context Menu
  hr := FShellfolder.GetUIObjectOf(WinHandle, counter, pidls[0], IID_IContextMenu, nil, Pointer(lpcm));
  If SUCCEEDED(hr) then begin
    if UpperCase(verb)='DEFAULT' then begin  // Perform Default Action
      Popup := CreatePopupMenu;
      try
        if Succeeded(lpcm.QueryContextMenu(Popup, 0, 1, $7FFF, CMF_DEFAULTONLY)) then begin
          MenuCmd := GetMenuDefaultItem(Popup, 0, 0);
          if (MenuCmd <> 0) then with cmi do begin
             cbSize    := sizeof(cmi);
             fMask     := 0;
             hwnd      := WinHandle;
             lpVerb    := MakeIntResource(MenuCmd-1);
             dwHotkey  := 0;
             hicon     := 0;
             nShow     := SW_SHOWNORMAL;
             lpParameters:=nil;
             lpDirectory:=nil;
             hr := lpcm.InvokeCommand(cmi);
          end;
        end;
      finally
        DestroyMenu(Popup);
      end;
    end else with cmi do begin // perform specified action via verb
      cbSize     := sizeof(cmi);
      fMask      := 0;
      hwnd       := WinHandle;
      lpVerb     := PChar(verb);
      dwHotkey   := 0;
      hicon      := 0;
      nShow      := SW_SHOWNORMAL;
      lpParameters:=nil;
      lpDirectory:=nil;
      hr := lpcm.InvokeCommand(cmi);
    end;
    Result := SUCCEEDED(hr);
  end;
  if (UpperCase(PChar(verb))='DELETE') and FileOrFolderExists(filename) then
    Result := False;
  Screen.Cursor := oldcursor;
end;//InvokeContextMenuCommand

function TShellBrowser.Next: Boolean;
var n     : ULONG;
    IdList: PItemIdList;
begin
  Result := False;
  if not Assigned(Objects) then begin
    if not Succeeded(FShellFolder.EnumObjects(WinHandle, SHCONTF_FOLDERS+SHCONTF_NONFOLDERS+SHCONTF_INCLUDEHIDDEN , Objects)) then exit;
  end;

  //Inc(_cc);OutputDebugString(PChar('TShellBrowser.Next: '+IntToStr(_cc)));
  while (Objects.Next(1, IdList, n)=NOERROR) do begin
    ItemIdList := IdList;
    if FileSystemOnly  and (GetAttributes(SFGAO_FILESYSTEM+SFGAO_FILESYSANCESTOR) = 0) and (UpperCase(Copy(ObjectName,1,7))<>'RECYCLE') then
      if not (IsSpecialObject in [SF_DRIVES,SF_NETWORK]) and not (IsSpecialFolder=SF_NETWORK) then
        continue; //Next item if no file system item
    if not FilterMatch then
      continue; // Next item if filter doesn't match
    Result := True;
    exit;
  end;
  Objects := nil;
end;//Next

// Fills a given ListView with data of the current folder
function  TShellBrowser.FillListView(ListView: TListView; Details: Boolean): Boolean;

  procedure StoreColumnWidths;
  var i: Integer;
  begin
    for i:=0 to ListView.Columns.Count-1 do ColumnWidth[i]:=ListView.Columns[i].Width;
  end;//StoreColumnsWidthS

  procedure InitShellColumns;
  var i,w : Integer;
      col : TListColumn;
      txt : String;
  begin
    ListView.Columns.BeginUpdate;
    if FileSystemFolder then StoreColumnWidths;
    FileSystemFolder := Length(Folder)>0;
    ListView.Columns.Clear;
    i := 0;
    txt := GetColumnText(i,True);
    while Length(txt)>0 do begin
      col := ListView.Columns.Add;
      col.Caption := txt;
      col.Alignment := GetColumnInfo(i, w);
      if FileSystemFolder and (ColumnWidth[col.Index]>0) then
        col.Width := ColumnWidth[col.Index]
      else
        col.Width := w;
      Inc(i);
      if not Details then break;//while
      txt := GetColumnText(i, True);
    end;
    ListView.Columns.EndUpdate;
  end;

var Item : TListItem;
    i    : Integer;
begin
  Screen.Cursor := crHourGlass;
  ListView.Items.BeginUpdate;
  ListView.Items.Clear; // Clear list
  if ListView.AllocBy<32 then ListView.AllocBy := 32;
//  if (ListView.SmallImages <> SmallImages) and Assigned(SmallImages) then    ListView.SmallImages := SmallImages;
  InitShellColumns;

  While Next do begin // Enumerate Files
    Item := ListView.Items.Add;
    Item.Caption    := GetShellObjectName;
    Item.ImageIndex := IconNumber;
    Item.OverlayIndex := GetOverlayIndex;

    if not Details then continue;
    for i:=1 to ListView.Columns.Count-1 do
      Item.SubItems.Add(GetColumnText(i,False));
  end;//while

  if FileSystemFolder then HandleColumnClick(ListView, ListView.Columns[0]);
  ListView.Items.EndUpdate;
  Screen.Cursor := crDefault;
  Result := True;
end;


const _FolderIcon: Integer=-1;
var _SortDirection: Integer;
function _SortProc(Item1, Item2: TListItem; ColIndex: integer): integer; stdcall;

  function GetFolderIcon: integer;
  var SHFileInfo: TSHFileInfo;
      path: Array [0..MAX_PATH] of Char;
  begin
    if _FolderIcon=-1 then begin
      GetWindowsDirectory(@path[0], MAX_PATH);
      SHGetFileInfo(@path[0], 0, SHFileInfo, sizeof(SHFileInfo), SHGFI_SMALLICON+SHGFI_SYSICONINDEX);
      _FolderIcon := SHFileInfo.iIcon;
    end;
    Result := _FolderIcon;
  end;//GetFolderIcon

  function IsValidNumber(const S: string; var V: extended): boolean;
  var
    NumCode: integer;
    firstspace: integer;
  begin
    firstspace := pos(' ', S);
    if firstspace>0 then
      Val(Copy(S,1,firstspace-1), V, NumCode)
    else
      Val(S, V, NumCode);
    if Pos(ThousandSeparator,S)>0 then V := V * 1000;
    Result := (NumCode = 0);
  end;//IsValidNumber

  function IsValidDateTime(const S: string; var D: TDateTime): boolean;
  var
    HasDate: boolean;
    HasTime: boolean;
  begin
    HasDate := (Pos(DateSeparator, S) > 0) and (ColIndex>0);
    HasTime := Pos(TimeSeparator, S) > 0;
    Result := HasDate or HasTime;
    if Result then
    begin
      try
        if HasDate and HasTime then
          D := StrToDateTime(S)
        else if HasDate then
          D := StrToDate(S)
        else if HasTime then
          D := StrToTime(S);
      except
        // Something failed to convert...
        D := 0;
        Result := FALSE;
      end;
    end;
  end; //IsValidDateTime

var
  Str1, Str2: string;
  Val1, Val2: extended;
  Date1, Date2: TDateTime;
  Diff: TDateTime;
begin
  if (Item1 = NIL) or (Item2 = NIL) then
  begin
    Result := 0;
    exit;
  end;

  try
    if ColIndex = -1 then begin
      if Item1.ImageIndex=Item2.ImageIndex then
        Result := AnsiCompareStr(Item1.Caption, Item2.Caption)
      else begin
        if Item1.ImageIndex=GetFolderIcon then
          Result := -1
        else if Item2.ImageIndex=GetFolderIcon then
          Result := 1
        else
          Result := AnsiCompareStr(Item1.Caption, Item2.Caption);
      end;
    end else begin
      if ColIndex < Item1.SubItems.Count then
        Str1 := Item1.SubItems[ColIndex]
      else
        Str1 := '';
      if ColIndex < Item2.SubItems.Count then
        Str2 := Item2.SubItems[ColIndex]
      else
        Str2 := '';

      if IsValidDateTime(Str1, Date1) and IsValidDateTime(Str2, Date2) then
      begin
        Diff := Date1 - Date2;
        if Diff < 0.0 then Result := -1
        else if Diff > 0.0 then Result := 1
        else Result := 0
      end else if IsValidNumber(Str1, Val1) and IsValidNumber(Str2, Val2) then
      begin
        if Val1 < Val2 then Result := -1
        else if Val1 > Val2 then Result := 1
        else Result := 0
      end else
      Result := AnsiCompareStr(Str1, Str2);
   end;
   Result := _SortDirection * Result; // Set direction flag.
  except
    Result := 0;  // Something went bad in the comparison.  Say they are equal.
  end;
end;// _SortProc

procedure TShellBrowser.HandleColumnClick(Sender: TObject; Column: TListColumn);
begin
  If Sender is TListView then begin
    if FLastColSorted = Column.Index then
      FSortDirection := -FSortDirection
    else begin
      FLastColSorted := Column.Index;
      FSortDirection := 1;
    end;
    _SortDirection := FSortDirection;
    (Sender as TListView).CustomSort(@_SortProc, Column.Index-1);
  end;
end;

// Set ItemIdList of object
procedure TShellBrowser.SetItemIdList(IdList: PItemIdList);
begin
  if Assigned(FItemIdList) and (FItemIdList<>IdList) then Allocator.Free(FItemIdList);
  if Assigned(FAbsoluteIdList) then begin
    Allocator.Free(FAbsoluteIdList);//AbsoluteIDList is not up to date any more
    FAbsoluteIdList := nil;
  end;
  FItemIdList := CopyItemIdList(IdList); // Copy ItemIdList
  FindData.cFileName[0] := #0;// FindData record is not up to date
end;

// Get a copy of the ItemIdList of the current object
function TShellBrowser.GetItemIdList: PItemIdList;
begin
  Result := CopyItemIdList(FItemIdList);
end;

function TShellBrowser.GetAbsoluteItemIdList: PItemIdList;
begin
  if not Assigned(FAbsoluteIdList) then begin
    FAbsoluteIdList := ConcatItemIdLists(FFolderIdList, FItemIdList);
  end;//if
  Result := FAbsoluteIdList;
end;//GetAbsoluteIdList

procedure TShellBrowser.SetAbsoluteItemIdList(IdList: PItemIdList);
var pidl1, pidl2, old, tmp: PItemIdList;
    S: UINT;
begin
  if not Assigned(IdList) then exit;
  S := GetPIDLSize(IdList);
  pidl1 := CreatePIDL(S);
  Move(IdList^, pidl1^, S);

  tmp := pidl1; old := pidl1;
  while tmp^.mkid.cb <> 0 do begin
    old := tmp;
    Inc(longint(tmp), tmp^.mkid.cb);
  end;
  S := GetPIDLSize(old);
  pidl2 := CreatePIDL(S);
  Move(old^, pidl2^, S);
  old.mkid.cb := 0;
  SetFolderIdList(pidl1);
  SetItemIdList(pidl2);
end;//SetAbsoluteItemIdList

// Set a new folder
procedure TShellBrowser.SetDirectory(Path: String);
var IdList: PItemIdList;
    oldPath: String;
begin
  // Same Folder?
  if (StrIComp(PChar(Path), PChar(Folder))=0) and (Length(Path)>0) then exit;
  oldPath := FDirectory;
  FDirectory := Path;
  if Length(FDirectory)=0 then
    SHGetSpecialFolderLocation(WinHandle, CSIDL_DRIVES, IdList)
  else
    IdList := GetIdListFromPath(nil, FDirectory);
  if not Assigned(IdList) then begin
    FDirectory := oldPath;
    raise EShellBrowserError.Create('Cannot Find Folder: ' + Path);
  end;//if
  if (Length(FDirectory)>0) and (FDirectory[Length(FDirectory)]<>'\') then FDirectory := FDirectory + '\';
  SetFolderIdList(IdList);
end;

// Sets the IdList of the folders and retrieves the correct IShellFolder interface
procedure TShellBrowser.SetFolderIdList(IdList: PItemIdList);
var tmp: Array[0..MAX_PATH] of Char;
    l  : Integer;
    hr : HRESULT;
    NewFolder: IShellFolder;
begin
  ishd := nil; // now invalid
  ishf2:= nil;
  if Assigned(FFolderIdList) and (FFolderIdList<>IdList) then Allocator.Free(FFolderIdList);
  FFolderIdList := nil;
  TriedIshd := False;
  if not Assigned(IdList) then exit;
  hr := Desktop.CompareIDs(0,IdList,DesktopIdList);
  if hr=0 then begin
    IdList    := DesktopIdList;
    NewFolder := Desktop;
  end else
    if Desktop.BindToObject(IdList, Nil, IID_IShellFolder, Pointer(NewFolder))<>NOERROR then
      raise EShellBrowserError.Create('ShellBrowser.SetFolderIDList: Desktop.BindToObject: Could not get Folder');
  SetShellFolder(NewFolder);
  FFolderIdList := CopyItemIdList(IdList);
  SetItemIdList(nil); //now invalid. IMPORTANT: Don't place this line above FFolderIdList := ...
  if SHGetPathFromIdList(FFolderIdList, @Tmp)=True then FDirectory := PChar(@Tmp)
  else begin
    fDirectory := '';
  end;
  l := Length(FDirectory);
  if (l>0) and (FDirectory[l]<>'\') then FDirectory := FDirectory + '\';
  if Assigned(fDirMon) then fDirMon.Directory := fDirectory;
end;//SetDirectory

// Get a copy of the ItemIdList of the current object
function TShellBrowser.GetFolderIdList: PItemIdList;
begin
  Result := CopyItemIdList(FFolderIdList);
end;

// Sets the ShellFolder property
procedure TShellBrowser.SetShellFolder(Folder: IShellfolder);
begin
  FShellFolder := Folder;
  Objects := nil;
  // To do here: Put correct path in FDirectory, but how to get a path from a IShellfolder interface?
end;//SetShellFolder

// Make given object active and get ItemIdList
procedure TShellBrowser.SetObjectName(ObjName: String);
begin
  if Length(ObjName)=0 then begin SetItemIdList(nil); exit end;
  // Eliminate backslash at the end, if it is not a drive
  if (ObjName[Length(ObjName)]='\') and (Length(ObjName)>3) then ObjName:=Copy(ObjName,1,Length(ObjName)-1);
  if (Pos('\', ObjName)>0) then  // Contains Path?
    if (Length(ObjName)>3) then begin  // then Divide path and name
      Folder     := ExtractFilePath(ObjName);
      ObjectName := ExtractFileName(ObjName);
    end else begin
      Folder := ObjName;
      SelectParent;
    end
  else begin
    SetItemIdList(GetIdListFromPath(ShellFolder, ObjName));
    if not Assigned(FItemIDList) then begin // Maybe a shell name, so search for it
      while Next do
        if (GetShellObjectName=ObjName) or (ObjectName=ObjName) then begin
          Objects := nil;
          exit;
        end;//if
      raise EShellBrowserError.Create('Error! Cannot find Object "'+ObjName+'" in Folder "'+Folder+'"');
    end
  end;
end;//SetFileName


// Handle ImageList for the small Images
{procedure TShellBrowser.SetSmallImageList(ImageList: TImageList);
var FileInfo: TSHFileInfo;
begin
  FSmallImageList := ImageList;
  if not Assigned(FSmallImageList) then exit;
  FSmallImageList.Handle := SHGetFileInfo('C:\', 0, FileInfo, sizeof(FileInfo), SHGFI_SMALLICON+SHGFI_SYSICONINDEX);
  FSmallImageList.ShareImages := True;
end;//SetImageList}

// Handle ImageList for the large Images
{procedure TShellBrowser.SetLargeImageList(ImageList: TImageList);
var FileInfo: TSHFileInfo;
begin
  FLargeImageList := ImageList;
  if not Assigned(FLargeImageList) then exit;
  FLargeImageList.Handle := SHGetFileInfo('C:\', 0, FileInfo, sizeof(FileInfo), SHGFI_LARGEICON+SHGFI_SYSICONINDEX);
  FLargeImageList.ShareImages := True;
end;//SetImageList}


function TShellBrowser.GetObjectName: string;
var Tmp: Array [0..MAX_PATH] of Char;
begin
  Result := '';
  if not Assigned(FFolderIdList) or not Assigned(FItemIdList) then exit;
  if SHGetPathFromIdList(GetAbsoluteItemIdList, @Tmp) then
    Result := Tmp; //PChar(@Tmp[0]);
  if (Length(Result)>0) and (ExtractFileDrive(Result) = Copy(Result, 1, Length(Result)-1)) then exit
  else Result := ExtractFileName(Result);
  if Length(Result)=0 then Result:=GetDomain; // See if it is a domain
end;//GetObjectName


function TShellBrowser.GetIconNumber: Integer;
var FileInfo: TSHFileInfo;
begin
  SHGetFileInfo(PChar(GetAbsoluteItemIdList), 0, FileInfo, sizeof(FileInfo),
                SHGFI_PIDL+SHGFI_SMALLICON+SHGFI_SYSICONINDEX);
  Result := FileInfo.iIcon;
end;//GetIconNumber

// Gets the number of the selected-icon of the current object
function TShellBrowser.GetSelectedIconNumber: Integer;
var FileInfo: TSHFileInfo;
begin
  SHGetFileInfo(PChar(GetAbsoluteItemIdList), 0, FileInfo, sizeof(FileInfo),
                SHGFI_PIDL+SHGFI_SMALLICON+SHGFI_SYSICONINDEX+SHGFI_OPENICON);
  Result := FileInfo.iIcon;
end;//GetIconNumber

//Browses into the current object
function TShellBrowser.BrowseObject: Boolean;
begin
  Result := False;
  if not IsFolder then exit;
  SetFolderIdList(GetAbsoluteItemIdList);
  Result := Assigned(ShellFolder);
end;//BrowseObject

// Gives the current object a new name
procedure TShellBrowser.RenameObject(var NewName: String);
var OleStr   : PWideChar;
    newIdList: PItemIdList;
    hr       : HResult;
    OldCursor: Integer;
begin
  OldCursor     := Screen.Cursor;
  Screen.Cursor := crHourGlass;
  OleStr := StringToOleStr(NewName);
  hr := ShellFolder.SetNameOf(WinHandle, FItemIdList, OleStr, SHCONTF_FOLDERS, newidlist);
  if (hr=NOERROR) and Assigned(newIdList) then
    SetItemIdList(NewIdList);
  SysFreeString(OleStr);
  NewName := GetShellObjectName;
  Screen.Cursor := OldCursor;
end;

function TShellBrowser.ShowNetConnectionDialog: Boolean;
var hr: HResult;
begin
  hr := WNetConnectionDialog(WinHandle, RESOURCETYPE_DISK);
  Result := hr = NOERROR;
end;

function TShellBrowser.BrowseSpecialFolder(folder: TJamShellFolder): Boolean;
var pidl: PItemIdList;
begin
  if SHGetSpecialFolderLocation(WinHandle, SpecialFolders[Ord(folder)], pidl)=NOERROR then begin
    SetFolderIdList(pidl);
    Result := True;
  end else
    Result:=False;
end;//BrowseSpecialFolder

procedure TShellBrowser.HandlePopupMessages(var Message: TMessage);
var n: Integer;
begin
  if ( (Message.Msg=WM_INITMENUPOPUP) or (Message.Msg=WM_MEASUREITEM) or (Message.Msg=WM_DRAWITEM) )
     and Assigned(ActiveIContextMenu) then begin
    // Check if it is a delphi menu
    n := GetMenuItemCount(ActiveDelphiContextMenu.Handle);
    n := n - ActiveDelphiContextMenu.Items.Count;
    if (Message.Msg=WM_INITMENUPOPUP) and (Message.LParamLo>=n) then exit;
    ActiveIContextMenu.HandleMenuMsg(Message.Msg, Message.wparam, Message.lparam);
    Message.Msg := 0;  // This message is already handled
  end;
end;

procedure TShellBrowser.SendToWindowProc(var Message: TMessage);
begin
  HandlePopupMessages(Message);
  if Assigned(OriginalWndProc) then
    OriginalWndProc(Message);
end;

// Returns the icon index of the Desktop itself
function  TShellBrowser.GetDesktopIconIndex: Integer;
var root: Word;
    SHF: TSHFileInfo;
begin
  root := 0;
  SHGetFileInfo(@root, 0, SHF, sizeof(SHF), SHGFI_PIDL+SHGFI_SYSICONINDEX+SHGFI_SMALLICON);
  Result := SHF.iIcon;
end;//GetDesktopIconIndex;

// Returns the index of the overlay image for the current object
function TShellBrowser.GetOverlayIndex: Integer;
var Attributes : Cardinal;
    psio       : IShellIconOverlay;
begin
  if IsNT and SUCCEEDED(ShellFolder.QueryInterface(IID_IShellIconOverlay, psio)) then begin
    if FAILED(psio.GetOverlayIconIndex(fItemIdList, Result)) then
      Result := -1;
  end else begin
    Attributes := GetAttributes(SFGAO_LINK or SFGAO_SHARE);
    if (Attributes and SFGAO_LINK) <> 0 then Result := LinkOverlay
    else if (Attributes and SFGAO_SHARE) <> 0 then Result := ShareOverlay
    else Result := -1;
  end//else
end;

// Returns the language dependant name of the Desktop
function  TShellBrowser.GetDesktopName: String;
var root: Word;
    SHF: TSHFileInfo;
begin
  root := 0;
  SHGetFileInfo(@root, 0, SHF, sizeof(SHF), SHGFI_PIDL+SHGFI_DISPLAYNAME);
  Result := SHF.szDisplayName;
end;//GetDesktopIconIndex;

function TShellBrowser.CanRename: Boolean;
var attr    : UINT;
    h       : HResult;
begin
  attr := SFGAO_CANRENAME;
  h := ShellFolder.GetAttributesOf(1, FItemIdList, attr);
  Result := Succeeded(h) and ((attr AND SFGAO_CANRENAME) <> 0);
end;//CanRename

procedure TShellBrowser.SetFilter(aFilter: String);
var p: Integer;
begin
  FFilter.Clear;
  if aFilter='' then aFilter:='*;';
  if aFilter[length(aFilter)] <> ';' then aFilter := aFilter + ';';

  p := Pos(';', aFilter);
  repeat
    FFilter.Add(Copy(aFilter, 1, p-1));
    Delete(aFilter, 1, p);
    p := Pos(';', aFilter);
  until p=0;
end;//SetFilter;

function TShellBrowser.GetFilter: String;
var i: Integer;
begin
  for i:=0 to FFilter.Count-1 do
    Result := Result + FFilter[i] + ';';
  Delete(Result, Length(Result), 1);
end;//GetFilter

function TShellBrowser.FilterMatch: Boolean;

  function MatchPattern(element, pattern: PChar): Boolean;
  begin
    if 0 = StrComp(pattern,'*') then
      Result := True
    else if (element^ = Chr(0)) and (pattern^ <> Chr(0)) then
      Result := False
    else if element^ = Chr(0) then
      Result := True
    else begin
      case pattern^ of
      '*': if MatchPattern(element,@pattern[1]) then
             Result := True
           else
             Result := MatchPattern(@element[1],pattern);
      '?': Result := MatchPattern(@element[1],@pattern[1]);
      else
        if UpperCase(element^) = Uppercase(pattern^) then
          Result := MatchPattern(@element[1],@pattern[1])
        else
          Result := False;
      end;
    end;
  end;//MatchPattern

var i: Integer;
begin
  Result := False;
  if IsFolder then
    Result := True
  else
   for i:=0 to FFilter.Count-1 do
     if MatchPattern(PChar(ObjectName), PChar(FFilter[i])) then begin
       Result := True;
       exit;
     end;//if
end;//FilterMatch

procedure TShellBrowser.SetOnFileChange(Event: TNotifyEvent);
begin
  if Assigned(fDirMon) then begin
    fDirMon.Stop;
    fDirMon.Free;
    fDirMon := nil;
  end;
  if Assigned(Event) then begin
    fOnFileChange := Event;
    fDirMon := TDirMon.Create(Self);
    fDirMon.NotifyFilter := [dmcFileName, dmcDirName];
    fDirMon.Directory := Folder;
    fDirMon.OnDirChange := FileChange;
    fDirMon.Start;
  end;//if
end;//SetOnFileChange

function TShellBrowser.IsSpecialFolder: TJamShellFolder;
begin
  Result := TestForSpecialFolder(fFolderIdList);
end;//IsSpecialfolder

function TShellBrowser.IsSpecialObject: TJamShellFolder;
begin
  Result := TestForSpecialFolder(GetAbsoluteItemIdList);
end;//IsSpecialfolder

procedure TShellBrowser.FileChange(Sender: TObject);
begin
  if Assigned(OnFilechange) then
    OnFileChange(Self);
end;//FileChange


function TShellBrowser.GetIShellDetails: Boolean;
begin
  if not Assigned(ishd) and not TriedIshd then  //Try to get IShellDetails interface
    if not Succeeded(ShellFolder.CreateViewObject(WinHandle, IID_IShellDetails, Pointer(ishd))) then
    begin // Failed, Try IShellFolder2
      ishd := nil;
      if not Succeeded(ShellFolder.QueryInterface({WinHandle,} IID_IShellFolder2, ishf2)) then
      begin
        ishf2:= nil;
        TriedIshd := True;
        //ShowErrorMessage(ShellFolder.CreateViewObject(WinHandle, IID_IShellFolder2, Pointer(ishf2)), '');
      end;//if
    end;//if
  Result := Assigned(ishd) or Assigned(ishf2);
end;//GetIShellDetails

function TShellBrowser.GetColumnText(col: Integer; Header: Boolean): String;

  function GetDate(Date: TFileTime): String;
  var LocalFileTime: TFILETIME;
      DosFileTime: Integer;
  begin
    if Date.dwHighDateTime>0 then begin
      FileTimeToLocalFileTime(Date, LocalFileTime);
      FileTimeToDosDateTime(LocalFileTime, LongRec(DosFileTime).Hi,LongRec(DosFileTime).Lo);
      //Result := DateTimeToStr(FileDateToDateTime(DosFileTime));
      Result := FormatDateTime(ShortDateFormat+' '+ShortTimeFormat, FileDateToDateTime(DosFileTime));
    end else
      Result := '';
  end;//GetDate

var info: TShellDetails;
    pidl: PItemIdList;
    SHF : TSHFileInfo;
begin
  Result := '';
  if (col=0) and not Header then begin
    Result := GetShellObjectName;
    exit;
  end;

  if GetIShellDetails then begin
    if Header then pidl := nil else pidl := FItemIdList;
    ZeroMemory(@info, Sizeof(info));
    if Assigned(ishd) and Succeeded(ishd.GetDetailsOf(pidl, col, info)) then begin
      Result := GetStringFromStrRet(FItemIdList, info.str);
      FreeStrRet(info.str);
    end;//if ishd
    if Assigned(ishf2) and Succeeded(ishf2.GetDetailsOf(pidl, col, info)) then begin
      Result := GetStringFromStrRet(FItemIdList, info.str);
      FreeStrRet(info.str);
    end;//if ishf2
  end else begin
    if Header then begin
      if col>High(colData) then Result := ''
      else Result := colData[col].Title;
      exit;
    end;//if
    if (FindData.cFileName[0]<>#0) or
       Succeeded(SHGetDataFromIDList(ShellFolder, FItemIdList, SHGDFIL_FINDDATA, @FindData, SizeOf(FindData))) then
      case col of
       1: begin
            if FindData.dwFileAttributes and FILE_ATTRIBUTE_DIRECTORY > 0 then
              Result := ''
            else begin
              if (FindData.nFileSizeLow<1024) and (FindData.nFileSizeLow>0) then
                FindData.nFileSizeLow:=1024; // Minimum 1 KB
              Result := Format('%1.0n %s', [FindData.nFileSizeLow/1024, strKB]);
            end;//else
          end;//1:
       2: begin
           SHGetFileInfo(PChar(GetAbsoluteItemIdList), 0, SHF, sizeof(TSHFileInfo), SHGFI_TYPENAME+SHGFI_PIDL);
           Result := SHF.szTypeName;
          end;
       3: Result := GetDate(FindData.ftLastWriteTime);
      end;//case
  end;//else
end;//GetColumnText

function TShellBrowser.GetColumnInfo(col: Integer; var Width: Integer): TAlignment;
var info: TShellDetails;
const _justify: array[0..2] of TAlignment = (taLeftJustify, taRightJustify, taCenter);
begin
  Result := taLeftJustify; Width := 120; // default values
  if not GetIShellDetails then begin
    Result := colData[col].Alignment;
    Width  := colData[col].Width;
    exit;
  end;//if
  if Assigned(ishd) and Succeeded(ishd.GetDetailsOf(nil, col, info)) then begin
    Result := _justify[info.fmt];
    Width  := info.cxChar*6;
    FreeStrRet(info.str);
    exit;
  end;
  if Assigned(ishf2) and Succeeded(ishf2.GetDetailsOf(nil, col, info)) then begin
    Result := _justify[info.fmt];
    Width  := info.cxChar*6;
    FreeStrRet(info.str);
    { // This code should hidden columns prevent from being displyed, but it seems that Microsoft didn't implement GetDefaultColumnState for its defualt filesystem folder object ...
      // Additionally this code produces access violations on some Windows 2000/XP machines and therewfore teporarily disabled
      if Succeeded(ishf2.GetDefaultColumnState(col,flags)) and ( ((flags AND SHCOLSTATE_ONBYDEFAULT)=0) OR ((flags AND SHCOLSTATE_HIDDEN) > 0) ) then
        Width := 0;}
    exit;
  end;
end;//GetColumnWidth

function TShellBrowser.GetVersion: String;
begin
  Result := ClassName + JAM_COMPONENT_VERSION;
end;//GetVersion

procedure TShellBrowser.SetVersion(s: String);
begin
  // empty
end;//SetVersion

procedure TShellBrowser.SetItemIdList2(IdList: DWORD);
begin
  SetItemIdList(PItemIdList(IdList));
end;

procedure TShellBrowser.SetFolderIdList2(IdList: DWORD);
begin
  SetFolderIdList(PItemIdList(IdList));
end;

function TShellBrowser.GetItemIdList2: DWORD;
begin
  Result := DWORD(GetItemIdList);
end;

function TShellBrowser.GetFolderIdList2: DWORD;
begin
  Result := DWORD(GetFolderIdList);
end;

/////////////////////////////////// TJamSystemImageList /////////////////////
constructor TJamSystemImageList.Create(AOwner: TComponent);
begin
  Inherited;
  ShareImages := True;
  Size := si_small;
end;//Create

procedure TJamSystemImageList.SetSize(aSize: TJamImageListSize);
begin
  fSize := aSize;
  SetImageListHandle;
end;//SetSize

function TJamSystemImageList.GetIndexFromExtension(Extension: String): Integer;
var FileInfo: TSHFileInfo;
    filename: String;
begin
  if Length(Extension)>0 then begin
    if Extension[1]='.' then
      filename := 'C:\test' + Extension
    else
      filename := 'C:\test.' + Extension;
  end else
    filename := 'c:\test';
  if Size=si_Large then
    SHGetFileInfo(PChar(filename), FILE_ATTRIBUTE_NORMAL , FileInfo, sizeof(FileInfo), SHGFI_LARGEICON+SHGFI_SYSICONINDEX+SHGFI_USEFILEATTRIBUTES)
  else
    SHGetFileInfo(PChar(filename), FILE_ATTRIBUTE_NORMAL , FileInfo, sizeof(FileInfo), SHGFI_SMALLICON+SHGFI_SYSICONINDEX+SHGFI_USEFILEATTRIBUTES);
  Result := FileInfo.iIcon;
end;//GetIndexFromExtension

function TJamSystemImageList.GetIndexFromFilename(filename: String): Integer;
var FileInfo: TSHFileInfo;
begin
  if Size=si_Large then
    SHGetFileInfo(PChar(filename), 0, FileInfo, sizeof(FileInfo), SHGFI_LARGEICON+SHGFI_SYSICONINDEX)
  else
    SHGetFileInfo(PChar(filename), 0, FileInfo, sizeof(FileInfo), SHGFI_SMALLICON+SHGFI_SYSICONINDEX);
  Result := FileInfo.iIcon;
end;//GetIndexFromExtension

function TJamSystemImageList.GetFolderIconNumber: Integer;
var folder: Array [0..MAX_PATH] of Char;
    FileInfo: TSHFileInfo;
begin
  GetTempPath(High(folder), @folder[0]);
  if Size=si_Large then
    SHGetFileInfo(@folder[0], 0, FileInfo, sizeof(FileInfo), SHGFI_LARGEICON+SHGFI_SYSICONINDEX)
  else
    SHGetFileInfo(@folder[0], 0, FileInfo, sizeof(FileInfo), SHGFI_SMALLICON+SHGFI_SYSICONINDEX);
  Result := FileInfo.iIcon;
end;//GetFolderIconNumber

function TJamSystemImageList.GetSpecialFolderIcon(folder: TJamShellFolder): Integer;
var pidl: PItemIdList;
    FileInfo: TSHFileInfo;
begin
  Result := -1;
  if SHGetSpecialFolderLocation(0, SpecialFolders[Ord(folder)], pidl)=NOERROR then begin
    if Size=si_Large then
      SHGetFileInfo(PChar(pidl), 0, FileInfo, sizeof(FileInfo), SHGFI_LARGEICON+SHGFI_SYSICONINDEX+SHGFI_PIDL)
    else
      SHGetFileInfo(PChar(pidl), 0, FileInfo, sizeof(FileInfo), SHGFI_SMALLICON+SHGFI_SYSICONINDEX+SHGFI_PIDL);
    Result := FileInfo.iIcon;
  end;
end;//GetSpecialFolderIcon

procedure TJamSystemImageList.WriteState(Writer: TWriter);
var Temp: HImageList;
begin
  // We don't want the system image list being streamed out to disk.
  // It could be quite large
  Temp := Handle;
  inherited Handle := 0;
  inherited WriteState(Writer);
  inherited Handle := Temp;
end;//WriteState

procedure TJamSystemImageList.ReadState(Reader: TReader);
begin
  inherited ReadState(Reader);
  SetImageListHandle;
end;//ReadState

procedure TJamSystemImageList.SetImageListHandle;
var FileInfo  : TSHFileInfo;
    TempHandle: HImageList;
    TempList  : TImageList;
begin
  // Delete old Handle
  if Size=si_small then
    TempHandle := SHGetFileInfo('C:\', 0, FileInfo, sizeof(FileInfo), SHGFI_SMALLICON+SHGFI_SYSICONINDEX)
  else
    TempHandle := SHGetFileInfo('C:\', 0, FileInfo, sizeof(FileInfo), SHGFI_LARGEICON+SHGFI_SYSICONINDEX);

  if ShareImages then begin
    if Handle<>TempHandle then
      Handle := TempHandle
  end else begin
    // Make a copy of the complete list.
    TempList := TImageList.Create(Self);
    try
      TempList.ShareImages := True;
      TempList.Handle := TempHandle;
      Assign(TempList);
    finally
      TempList.Free;
    end;
  end;
end;//SetImageListHandle

function TJamSystemImageList.GetShareImages: Boolean;
begin
  Result := inherited ShareImages;
end;

procedure TJamSystemImageList.SetShareImages(val: Boolean);
begin
  if HandleAllocated then SetImageListHandle;
  inherited ShareImages := val;
end;

// Registers the TShellBrowser component
procedure Register;
begin
  RegisterComponents('JAM Software', [TShellBrowser,TJamSystemImageList]);
end;//Register

const
  _w: Word=0;

var _item : Array [0..255] of TMenuItem;
    _itemindex : Integer;
    h_shlwapidll : THandle;
    OsVer: TOSVersionInfo;

Initialization
  OleInitialize(nil);
  // Get the shell memory allocator
  if Not(Succeeded(SHGetMalloc(Allocator)) and
         Succeeded(SHGetDesktopFolder(Desktop))) then
  begin
    ShowMessage('Cannot find Shell!');
    Application.Terminate;
  end;
  DesktopIdList := @_w;
  SHGetSpecialFolderLocation(0, CSIDL_NETHOOD, NetHoodIdList);
  CF_IDLIST := RegisterClipboardFormat( CFSTR_SHELLIDLIST );

  // Workaround for ShowContextMenu: Adjust unique command values to a number >255
  for _itemindex:=0 to High(_item) do
    _item[_itemindex] := TMenuItem.Create(nil);

// Shareware message
{$ifdef JAMSHAREWARE}         
  if (FindWindow('TApplication', nil)=0) or (FindWindow('TPropertyInspector', nil)=0) then
    Application.MessageBox('You are using an unregistered copy of the ShellBrowser components! For more information please visit http://www.jam-software.com/delphi/', 'TShellBrowser', MB_ICONEXCLAMATION);
{$endif}

  h_shlwapidll := LoadLibrary('shlwapi');
  if (h_shlwapidll>0) then begin
    fShAutoComplete := GetProcAddress(h_shlwapidll, 'SHAutoComplete');
  end;

  // Get information about the OS
  OSVer.dwOSVersionInfoSize := SizeOf(TOSVersionInfo);
  GetVersionEx(OSVer);
  IsNT := (OSVer.dwPlatformId = VER_PLATFORM_WIN32_NT);

Finalization
  OleUnInitialize;
  if (h_shlwapidll>0) then FreeLibrary(h_shlwapidll);
end.





