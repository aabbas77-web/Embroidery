unit ShellControls;

interface

uses
  Windows, Messages, Classes, Graphics, Controls, Forms, ExtCtrls,
  StdCtrls, ShellBrowser, ComCtrls, ShellApi, ShlObj, CommCtrl,
  ShellLink, ActiveX, Menus;

{$BOOLEVAL OFF}
{$I VER.INC}
{$IFDEF _CPPB_3_UP}
  {$ObjExportAll On}
  // To work around a C++ Builder bug:
  {$HPPEMIT 'typedef IDropTarget *_di_IDropTarget;' }
{$ELSE}
  type TOwnerDrawState = StdCtrls.TOwnerDrawState;
{$ENDIF}

type
  // For use in the shell controls and TJamShellLink
  TJamShellOperation = (sopCopy, sopMove, sopDrag, sopDrop, sopCut, sopPaste, sopDelete, sopRemove, sopAdd, sopRename);
  TJamShellOperations = set of TJamShellOperation;
  TOnOperation = procedure(Sender: TObject; Operation: TJamShellOperations; Files: TStrings; Destination: String) of object;

type
  TJamComboItem = class (TObject)
    Caption    : String;
    DisplayName: String;
    Indent     : Integer;
    IconNumber : Integer;
    IsDrive    : Boolean;
    Persistent : Boolean;
    PIDL       : PItemIdList;
  end;

  TJamShellCombo = class(TCustomComboBox)
  private
    FInitialized  : Boolean;
    FNotDrawingInComboboxEdit: boolean;
    FShellLink    : TJamShellLink;
    FShellBrowser : TShellBrowser;
    FImageList    : TJamSystemImageList;
    fIndentPixels : Integer;
    procedure CNDrawItem(var Message: TWMDrawItem); message CN_DRAWITEM;
    procedure WMRButtonDown(var Message: TWMRButtonDown); message WM_CONTEXTMENU;//WM_RBUTTONDOWN;

  protected
    procedure Loaded; override;
    procedure Notification(AComponent: TComponent; operation: TOperation); override;
    procedure DeleteNonPersistentFolders(fromIndex: Integer);
    procedure Delete(Index: Integer);
    procedure AddPathToCombo(path: string);
    procedure AddIdListToCombo(absIdList: PItemIdList);
    procedure JamSetItemIndex(newValue: Integer);
    function  JamGetItemIndex: Integer;
    procedure Change; override;
    procedure CNCommand(var Message: TWMCommand); message CN_COMMAND;
    procedure AddToComboList(aIndex, aIndent: Integer);
    procedure JAMPathChanged(var Message: TJAMPathChanged); message JAM_PATHCHANGED;
    procedure DrawItem(aIndex: Integer; aRect: TRect; aState: TOwnerDrawState); override;
    procedure CreateWnd; override;
    procedure SetShellLink(newValue: TJamShellLink);
    procedure SetFileSystemOnly(aValue: Boolean);
    function  GetFileSystemOnly: Boolean;
    function  GetVersion: String;
    procedure SetVersion(s: String);

  public
    // Constructor of the JamShellCombo
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure InsertItem(aIndex: Integer; aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer; PIDL: Pointer; Persistent: boolean);
    procedure AddShellItem(aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer; PIDL: Pointer; Persistent: boolean);
    procedure AddFolder(Path: String; Indent: Integer; Persistent: boolean);
    property  Font;

  published
    property  ItemIndex read JamGetItemIndex write JamSetItemIndex;
    property ShellLink: TJamShellLink read FShellLink write SetShellLink;
    property FileSystemOnly: Boolean read GetFileSystemOnly write SetFileSystemOnly default False;
    // Version information for this component
    property Version: String read GetVersion write SetVersion stored false;
    property Align;
    property Color;
    property Ctl3D;
    property DragMode;
    property DragCursor;
    property DropDownCount;
    property Enabled;
    property ImeMode;
    property ImeName;
    property ItemHeight;
    property MaxLength;
    property ParentColor;
    property ParentCtl3D;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Text;
    property Visible;
    property OnChange;
    property OnClick;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnDrawItem;
    property OnDropDown;
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnStartDrag;
{$ifdef _VCL_4_UP}
    property DragKind;
    property Anchors;
{$endif}
  end;//TJamShellCombo

  TOnAddItem = procedure(Item: TListItem; var CanAdd: Boolean) of object;

  TJamShellListItem = class (TObject)
    RelativePIDL       : PItemIdList;
    Data               : Pointer;
    Tag                : Integer;
  end;

  TJamShellList = class(TCustomListView, {$ifndef _VCL_4_UP} IUnknown, {$endif} IDropTarget, IDropSource)
  private
    FInitialized    : Boolean;
    fShellBrowser   : TShellBrowser;
    fOnCreateColumns: TNotifyEvent;
    fOnAddItem      : TOnAddItem;
    fOnPopulated    : TNotifyEvent;
    fOnOperation    : TOnOperation;
    FShellLink      : TJamShellLink;
    fColCount       : Integer;
    fDetails        : Boolean;
    fShowFolders    : Boolean;
    fShowHidden     : Boolean;
    fSortColumn     : Integer;
    fReverseOrder   : Boolean;
    ColumnWidth     : Array [0..255] of Integer;
    FileSystemFolder: Boolean;
    fContextMenu    : Boolean;
    fOleDragDrop    : Boolean;
    fIgnoreChanges  : Boolean;
    fSelectedList   : TStringList;
    fDataObj        : IDataObject;
    fDropTarget     : IDropTarget;
    fDropTarget2    : IDropTarget;
    fDropItem       : TListItem;
    fDragButton     : Integer;
    fDropButton     : Integer;
    fLastAutoScroll : DWord;
    fUpdateTimer    : TTimer;
    fBackgroundPopupMenu: TPopupMenu;
    fNumShellColumns: Integer;
{$ifndef _VCL_4_UP}
    FRefCount       : Integer;
{$endif}
    procedure WMRButtonUp(var Message: TWMRButtonUp); message {$ifdef _VCL_5_UP} WM_CONTEXTMENU {$else} WM_RBUTTONUP {$endif};
    procedure WMInitMenuPopup(var Message: TMessage); message WM_INITMENUPOPUP;
    procedure WMMeasureItem(var Message: TMessage); message WM_MEASUREITEM;
    procedure WMDrawItem(var Message: TMessage); message WM_DRAWITEM;
    procedure JAMPathChanged(var Message: TJAMPathChanged); message JAM_PATHCHANGED;
    procedure JAMSelectAll(var Message: TJAMPathChanged); message JAM_SELECTALL;
    procedure JAMRefresh(var Message: TJAMPathChanged); message JAM_REFRESH;
    procedure JAMSmartRefresh(var Message: TJAMPathChanged); message JAM_SMARTREFRESH;
    procedure JAMGoUp(var Message: TMessage); message JAM_GOUP;
    function  IndexOfPIDL(pidl: PItemIDList): Integer;
    procedure HandleRenameEvent(Sender: TObject);
    procedure CNNotify(var Message: TWMNotify); message CN_NOTIFY;

  protected
    procedure Notification(AComponent: TComponent; operation: TOperation); override;
    procedure CreateWnd; override;
    procedure DestroyWnd; override;
    procedure Loaded; override;
    procedure MouseDown( aButton: TMouseButton;  aShift: TShiftState;  x, y: Integer ); override;
    procedure Change(Item: TListItem; Change: Integer); override;
    procedure PrepareMultiObjects;
    procedure SetPath(aPath: String);
    function  GetPath: String;
    procedure AddShellItem(Details: Boolean);
    procedure Delete(Item: TListItem); override;
    procedure SetFileSystemOnly(aValue: Boolean);
    function  GetFileSystemOnly: Boolean;
    procedure SetFolderIdList(IdList: PItemIdList);
    function  GetFolderIdList: PItemIdList;
    procedure TimerChange(Sender: TObject);
    function  CanEdit(Item: TListItem): Boolean; override;
    procedure Edit(const Item: TLVItem); override;
    procedure Operation(op: TJamShellOperations; files: TStrings; Destination: String);
    procedure KeyDown( var key: Word;  aShiftState: TShiftState ); override;
    procedure KeyPress( var key: Char ); override;
    procedure ColClick(Column: TListColumn); override;
    procedure SetShellLink(newValue: TJamShellLink);
    procedure SetDetails(aDetails: Boolean);
    procedure SetShowHidden(val: Boolean);
    procedure SetSortColumn(col: Integer);
    procedure SetReverseSortOrder(reverse: Boolean);
    procedure SetShowFolders(val: Boolean);
    procedure SetFilter(Pattern: String);
    function  GetFilter: String;
    procedure FileChange(Sender: TObject);
    procedure SetSpecialFolder(folder: TJamShellFolder);
    function  GetSpecialFolder: TJamShellfolder;
    procedure SetOleDragDrop(val: Boolean);
    procedure BeginOleDrag(aButton: TMouseButton);
    function  GetSelectedFiles: TStringList;
    function  ShowBackgroundMenu(p: TPoint): Boolean;
    function  GetOnContextMenuSelect: TOnContextMenuSelectEvent;
    procedure SetOnContextMenuSelect(anEvent: TOnContextMenuSelectEvent);
    procedure SelectedListChange(Sender: TObject);
    function  GetVersion: String;
    procedure SetVersion(s: String);
    // IDropTarget methods
    function DragEnter(const DataObj: IDataObject; grfKeyState: Longint;
      pt: TPoint; var dwEffect: Longint): HRESULT; StdCall;
    function DragOver(grfKeyState: Longint; pt: TPoint; var dwEffect: Longint): HRESULT; {$ifdef _VCL_4_UP} reintroduce; {$endif} stdcall;
    function DragLeave: HRESULT; StdCall;
    function Drop(const dataObj: IDataObject; grfKeyState: Longint; pt: TPoint;
      var dwEffect: Longint): HRESULT; StdCall;
    // IDropSource methods
    function QueryContinueDrag(fEscapePressed: Bool;  grfKeyState: Longint): HResult; virtual; stdcall;
    function GiveFeedback(dwEffect: Longint): HResult; virtual; stdcall;
{$ifndef _VCL_4_UP}
    // IUknown methods
    function QueryInterface(const IID: TGUID; out Obj): HResult; stdcall;
    function _AddRef: Integer; stdcall;
    function _Release: Integer; stdcall;
{$endif}

  public
    // Constructor of the JamShellList
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function  Refresh: Boolean;
    procedure GoUp;
    function  CreateDir(Name: String; EditMode: Boolean): Boolean;
    function  InvokeCommandOnSelected(Command: String): Boolean;
    function  InvokeCommandOnFolder(Command: String): Boolean;
    function  ShowContextMenu(p: TPoint): String;
    function  GetFullPath(item: TListItem): String;
    // ItemIdList of the current Folder
    property  FolderIdList: PItemIdList read GetFolderIdList write SetFolderIdList;
    property  SortColumn: Integer read fSortColumn write SetSortColumn;
    property  ReverseSortOrder: Boolean read fReverseOrder write SetReverseSortOrder;
    property  SelectedFiles: TStringList read GetSelectedFiles;
    property  Items;
    procedure SmartRefresh;
    property  Font;
    property  Columns;
    property  SmallImages;
    property  LargeImages;
{$ifndef _VCL_6_UP}
    procedure SelectAll;
{$endif}

  published
    property Details: Boolean read fDetails write SetDetails default True;
    property ShowHidden: Boolean read fShowHidden write setShowHidden default True;
    property FileSystemOnly: Boolean read GetFileSystemOnly write SetFileSystemOnly default False;
    property Filter: String read GetFilter write SetFilter;
    property Path: String read GetPath write SetPath;
    property SpecialFolder: TJamShellFolder read GetSpecialFolder write SetSpecialFolder;
    property ShellLink: TJamShellLink read FShellLink write SetShellLink;
    property OleDragDrop: Boolean read fOLEDragDrop write SetOleDragDrop;
    property ShellContextMenu: Boolean read fContextMenu write fContextMenu;
    property BackgroundPopupMenu: TPopupMenu read fBackgroundPopupMenu write fBackgroundPopupMenu;
    property ShowFolders: Boolean read fShowFolders write SetShowFolders default True;
    property OnAddItem: TOnAddItem read fOnAddItem write fOnAddItem;
    property OnPopulated: TNotifyEvent read fOnPopulated write fOnPopulated;
    property OnCreateColumns: TNotifyEvent read fOnCreateColumns write fOnCreateColumns;
    property OnOperation: TOnOperation read fOnOperation write fOnOperation;
    property OnContextMenuSelect: TOnContextMenuSelectEvent read GetOnContextMenuSelect write SetOnContextMenuSelect;
    property Version: String read GetVersion write SetVersion stored false;
    property Align;
    property BorderStyle;
    property Checkboxes;
    property HideSelection;
    property Color;
    property Ctl3D;
    property DragMode;
    property DragCursor;
    property Enabled;
    property Hint;
    property ImeMode;
    property ImeName;
    property IconOptions;
    property MultiSelect;
    property ParentColor;
    property ParentFont;
    property ParentCtl3D;
    property ParentShowHint;
    property PopupMenu;
    property ReadOnly;
    property RowSelect;
    property ShowHint;
    property ShowColumnHeaders;
    property StateImages;
    property TabOrder;
    property TabStop;
    property ViewStyle default vsReport;
    property Visible;
    property OnChange;
    property OnClick;
    property OnColumnClick;
    property OnDblClick;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnEnter;
    property OnExit;
    property OnMouseDown;
    property OnMouseUp;
    property OnMouseMove;
    property OnDragDrop;
    property OnDragOver;
    property OnStartDrag;
    property OnEndDrag;
    property OnDeletion;
    property OnEdited;
{$ifdef _VCL_4_UP}
    property Anchors;
    property DragKind;
    property HotTrack;
    property OnCustomDraw;
    property OnCustomDrawItem;
    property OnSelectItem;
    property OnResize;
    property OnStartDock;
    property OnEndDock;
    property OnChanging;
{$endif}
  end;//TJamShellList

  TJamShellTreeItem = class (TObject)
    RelativePIDL       : Pointer;
    AbsolutePIDL       : Pointer;
    Tag                : Integer;
    Data               : Pointer;
    ParentShellFolder  : IShellFolder;
  end;

  TOnAddNode = procedure(Node: TTreeNode; Path: String; var CanAdd: Boolean) of object;

  TJamShellTree = class(TCustomTreeView, {$ifndef _VCL_4_UP} IUnknown, {$endif} IDropTarget, IDropSource)
  private
    fInitialized  : Boolean;
    fAllowExpand  : Boolean;
    fShellBrowser : TShellBrowser;
    fShellLink    : TJamShellLink;
    fRootedAt     : TJamShellFolder;
    fOnAddFolder  : TOnAddNode;
    fOnOperation  : TOnOperation;
    fChangeTimer  : TTimer;
    fQuickSelect  : Boolean;
    fIsExpanding  : Boolean;
    fRootedAtFileSystemFolder: String;
    fOleDragDrop    : Boolean;
    fDataObj        : IDataObject;
    fContextMenu    : Boolean;
    fShowHidden     : Boolean;
    fShowFiles      : Boolean;
    fShowNetHood    : Boolean;
    fDropTarget2    : IDropTarget;
    fDropItem       : TTreeNode;
    fDragNode       : TTreeNode;
    fDragButton     : Integer;
    fDropButton     : Integer;
    fOldDragEffect  : LongInt;
    fLastAutoScroll : Dword;
    fAutoExpand     : Dword;
{$ifndef _VCL_4_UP}
    FRefCount       : Integer;
{$endif}
    procedure WMRButtonUp(var Message: TWMRButtonUp); message {$ifdef _VCL_5_UP} WM_CONTEXTMENU {$else} WM_RBUTTONUP {$endif};
    procedure WMLButtonDown(var Message: TWMRButtonUp); message WM_LBUTTONDOWN;
    procedure WMInitMenuPopup(var Message: TMessage); message WM_INITMENUPOPUP;
    procedure WMMeasureItem(var Message: TMessage); message WM_MEASUREITEM;
    procedure WMDrawItem(var Message: TMessage); message WM_DRAWITEM;
    procedure CNNotify(var Message: TWMNotify); message CN_NOTIFY;
    procedure JAMRefresh(var Message: TJAMPathChanged); message JAM_REFRESH;
    procedure JAMSmartRefresh(var Message: TJAMPathChanged); message JAM_SMARTREFRESH;
    procedure JAMGoUp(var Message: TMessage); message JAM_GOUP;
    procedure AddItem(Parent: TTreeNode);
    procedure HandleRenameEvent(Sender: TObject);

  protected
    procedure Notification(AComponent: TComponent; operation: TOperation); override;
    procedure CreateWnd; override;
    procedure Loaded; override;
    procedure DestroyWnd; override;
    procedure TimerChange(Sender: TObject);
    function  CanExpand(aNode: TTreeNode): Boolean; override;
    procedure Expand(aNode: TTreeNode); override;
    procedure Delete(aNode: TTreeNode); {$ifndef _DELPHI_3} override; {$endif}
    procedure SetJAMShellLink(newValue: TJamShellLink);
    procedure SetRootedAt(Root: TJamShellFolder);
    procedure Change(Node: TTreeNode); override;
    procedure JAMPathChanged(var Message: TJAMPathChanged); message JAM_PATHCHANGED;
    function  GotoFolderIdList(const ItemIdList: PItemIdList): Boolean;
    function  GetSelectedFolder: String;
    procedure SetSelectedFolder(aPath: String);
    function  CanEdit(Node: TTreeNode): Boolean; override;
    procedure Edit(const Item: TTVItem); override;
    procedure Operation(op: TJamShellOperations; Folders: TStrings; Destination: String);
    procedure KeyDown( var key: Word;  aShiftState: TShiftState ); override;
    procedure KeyPress( var key: Char ); override;
    procedure SetSpecialFolder(folder: TJamShellFolder);
    function  GetSpecialFolder: TJamShellfolder;
    procedure SetRootedAtFileSystemFolder(aPath: String);
    procedure SetShowHidden(aValue: Boolean);
    procedure SetShowNetHood(aValue: Boolean);
    procedure SetShowFiles(aValue: Boolean);
    procedure SetFileSystemOnly(aValue: Boolean);
    function  GetFileSystemOnly: Boolean;
    function  GetOnContextMenuSelect: TOnContextMenuSelectEvent;
    procedure SetOnContextMenuSelect(anEvent: TOnContextMenuSelectEvent);
    procedure SetFilter(Pattern: String);
    function  GetFilter: String;
    function  GetVersion: String;
    procedure SetVersion(s: String);
    procedure SetOleDragDrop(val: Boolean);
    procedure BeginOleDrag(aButton: TMouseButton);
    // IDropTarget methods
    function DragEnter(const DataObj: IDataObject; grfKeyState: Longint;
      pt: TPoint; var dwEffect: Longint): HRESULT; StdCall;
    function DragOver(grfKeyState: Longint; pt: TPoint; var dwEffect: Longint): HRESULT; {$ifdef _VCL_4_UP} reintroduce; {$endif} StdCall;
    function DragLeave: HRESULT; StdCall;
    function Drop(const dataObj: IDataObject; grfKeyState: Longint; pt: TPoint;
      var dwEffect: Longint): HRESULT; StdCall;
    // IDropSource methods
    function QueryContinueDrag(fEscapePressed: Bool;  grfKeyState: Longint): HResult; virtual; stdcall;
    function GiveFeedback(dwEffect: Longint): HResult; virtual; stdcall;
{$ifndef _VCL_4_UP}
    // IUknown methods
    function QueryInterface(const IID: TGUID; out Obj): HResult; stdcall;
    function _AddRef: Integer; stdcall;
    function _Release: Integer; stdcall;
{$endif}

  public
    // Constructor of the JamShellTree
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    function  InvokeCommandOnSelected(Command: String): Boolean;
    procedure GoUp;
    procedure Refresh;
    procedure SmartRefresh;
    function  GetFullPath(node: TTreeNode): String;
    procedure CreateDir(path: String; foldername: String; editmode: Boolean);
    procedure RefreshNode(Node: TTreeNode; Recursive: Boolean);
    function  ShowContextMenu(p: TPoint): String;
    function  ShowNetConnectionDialog: Boolean;
    property  Items;
    property  Images;
    property  Font;

  published
    // Published properties and events
    property ShellLink: TJamShellLink read FShellLink write SeTJAMShellLink;
    property RootedAt: TJamShellFolder read fRootedAt write SetRootedAt;
    property RootedAtFileSystemFolder: String read fRootedAtFileSystemFolder write SetRootedAtFileSystemFolder;
    property SelectedFolder: String read GetSelectedFolder write SetSelectedFolder;
    property SpecialFolder: TJamShellFolder read GetSpecialFolder write SetSpecialFolder;
    property OleDragDrop: Boolean read fOLEDragDrop write SetOleDragDrop;
    property ShellContextMenu: Boolean read fContextMenu write fContextMenu;
    property ShowHidden: Boolean read fShowHidden write SetShowHidden default True;
    property ShowNetHood: Boolean read fShowNetHood write SetShowNetHood default True;
    property FileSystemOnly: Boolean read GetFileSystemOnly write SetFileSystemOnly default False;
    property ShowFiles: Boolean read fShowFiles write SetShowFiles;
    property Filter: String read GetFilter write SetFilter;
    property Version: String read GetVersion write SetVersion stored false;
    property OnAddFolder: TOnAddNode read fOnAddFolder write fOnAddFolder;
    property OnOperation: TOnOperation read fOnOperation write fOnOperation;
    property OnContextMenuSelect: TOnContextMenuSelectEvent read GetOnContextMenuSelect write SetOnContextMenuSelect;
    property ShowButtons;
    property BorderStyle;
    property DragCursor;
    property ShowLines;
    property ShowRoot;
    property ReadOnly;
    property DragMode;
    property HideSelection;
    property Indent;
    property OnEditing;
    property OnEdited;
    property OnExpanding;
    property OnExpanded;
    property OnCollapsing;
    property OnCompare;
    property OnCollapsed;
    property OnChanging;
    property OnChange;
    property OnDeletion;
    property OnGetImageIndex;
    property OnGetSelectedIndex;
    property Align;
    property Enabled;
    property Color;
    property ParentColor default False;
    property ParentCtl3D;
    property Ctl3D;
    property TabOrder;
    property TabStop default True;
    property Visible;
    property OnClick;
    property OnEnter;
    property OnExit;
    property OnDragDrop;
    property OnDragOver;
    property OnStartDrag;
    property OnEndDrag;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnDblClick;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property PopupMenu;
    property ParentFont;
    property ParentShowHint;
    property ShowHint;
    property StateImages;
{$ifdef _VCL_4_UP}
    property DragKind;
    property Anchors;
    property HotTrack;
    property OnStartDock;
    property OnEndDock;
    property OnCustomDraw;
    property OnCustomDrawItem;
{$endif}
  end;//TJamShellTree

procedure Register;

var AUTOSCROLL_DELAY_MS    : DWord   = 100;
    AUTOSCROLL_THRESHOLD_X : Integer = 25;
    AUTOSCROLL_THRESHOLD_Y : Integer = 20;
    AUTOEXPAND_DELAY_MS    : DWord   = 2000;

implementation

uses SysUtils, ShellStrings, Dialogs, ClipBrd
{$ifndef _VCL_6_UP} ,FileCtrl {$endif}
{$ifdef _VCL_4_UP} ,ImgList {$endif};

const DRAGFLAGS = SFGAO_CANCOPY or SFGAO_CANMOVE or SFGAO_CANLINK;

function GetOwnerDrawState(itemState: UINT): TOwnerDrawState;
begin
{$ifdef _VCL_5_UP}
  Result := TOwnerDrawState(LongRec(itemState).Lo);
{$else}
  Result := TOwnerDrawState(WordRec(LongRec(itemState).Lo).Lo);
{$endif}
end;

procedure CheckAutoScroll(control: TWinControl; pt: TPoint);

  procedure PerformScroll(code, direction: Integer );
  const _scrollbars: array[SB_HORZ .. SB_VERT] of Integer = (WM_HSCROLL, WM_VSCROLL);
  var info: TScrollInfo;
  begin
    ZeroMemory(@info, Sizeof(info));
    info.cbSize := Sizeof(TScrollInfo);
    info.fMask := SIF_ALL;
    Windows.GetScrollInfo(control.Handle, code, info);
    if (info.nMax - info.nMin - Integer(info.nPage)) > 0 then
      control.Perform(_scrollbars[code], direction, 0 );
  end;//PerformScroll

begin
  if (pt.x < AUTOSCROLL_THRESHOLD_X) then
    PerformScroll(SB_HORZ, SB_LINEUP)
  else if (pt.x > control.ClientRect.right - AUTOSCROLL_THRESHOLD_X) then
    PerformScroll(SB_HORZ, SB_LINEDOWN);
  if (pt.y < AUTOSCROLL_THRESHOLD_Y) then
    PerformScroll(SB_VERT, SB_LINEUP )
  else if (pt.y > control.ClientRect.bottom - AUTOSCROLL_THRESHOLD_Y) then
    PerformScroll(SB_VERT, SB_LINEDOWN);
end;//CheckAutoScroll


function GetFilenamesFromHandle(h: HGlobal): TStrings;
var num, i   : Integer;
    FFileName: array [0..MAX_PATH] of Char;
begin
  Result := nil;
  if h=0 then exit;
  num := DragQueryFile(h, $FFFFFFFF, nil, 0);
  if num<=0 then exit;
  Result := TStringList.Create;
  for i:=0 to num-1 do begin
    if Failed(DragQueryFile(h, i, FFileName, SizeOf(FFileName))) then
      break;
    Result.Add(FFileName);
  end;//for
end;//GetFilenamesFromHandle

function GetFilenamesFromDataObject(lpdobj: IDataObject): TStrings;
var
  StgMedium: TStgMedium;
  FormatEtc: TFormatEtc;
  hr       : HResult;
begin
  Result := nil;
  // Fail the call if lpdobj is Nil.
  if not Assigned(lpdobj) then exit;

  with FormatEtc do begin
    cfFormat := CF_HDROP;
    ptd      := nil;
    dwAspect := DVASPECT_CONTENT;
    lindex   := -1;
    tymed    := TYMED_HGLOBAL;
  end;

  // Render the data referenced by the IDataObject pointer to an HGLOBAL
  // storage medium in CF_HDROP format.
  hr := lpdobj.GetData(FormatEtc, StgMedium);
  if Failed(hr) then exit;
  Result := GetFilenamesFromHandle(StgMedium.hGlobal);
  ReleaseStgMedium(StgMedium);
end;//GetFilenamesFromDataObject


///////////////////////////////////// TJamShellCombo /////////////////////////

procedure TJamShellCombo.JAMPathChanged(var Message: TJAMPathChanged);
var
  hr: HResult;
  i: integer;
  pszPath: array[0..MAX_PATH] of char;
begin
  if assigned(Message.PIDL) then begin
    SHGetPathFromIDList(Message.PIDL, pszPath);
    hr := Desktop.CompareIDs(0, DesktopIdList, Message.PIDL);
    if (StrLen(pszPath) > 0) and (hr <> 0) and (pszPath[1]<>'\'){exclude network folders} then begin
      AddPathToCombo(pszPath);
    end else begin
      DeleteNonPersistentFolders(-1);
      { If it's not a path then run through items to find the right one. }
      for i := 0 to Items.Count - 1 do begin    // Iterate
        hr := Desktop.CompareIDs(0, (Items.Objects[i] as TJamComboItem).PIDL, Message.PIDL);
        if hr=0 then begin
          ItemIndex := i;
          exit;
        end;
      end;    // for
      // Not included, so add it.
      AddIdListToCombo(Message.PIDL);
    end;
  end;
end;

procedure TJamShellCombo.SetShellLink(newValue: TJamShellLink);
begin
  if FShellLink <> newValue then begin
    if assigned(FShellLink) then
      FShellLink.UnregisterShellControl(Handle);
    FShellLink := newValue;
    if assigned(FShellLink) then begin
      FShellLink.RegisterShellControl(Handle);
    end;
  end;
end;

procedure TJamShellCombo.SetFileSystemOnly(aValue: Boolean);
begin
  fShellBrowser.FileSystemOnly := aValue;
  Refresh;
end;//SetFileSystemOnly

function TJamShellCombo.GetFileSystemOnly: Boolean;
begin
  Result := fShellBrowser.FileSystemOnly;
end;//GetFileSystemOnly

constructor TJamShellCombo.Create(AOwner: TComponent);
begin
  Inherited Create(AOwner);
  fInitialized := False;
  FShellBrowser := TShellBrowser.Create(Self);
  fShellBrowser.FileSystemOnly := False;
  FImageList    := TJamSystemImageList.Create(Self);
  fIndentPixels := 10;
  //ControlStyle := ControlStyle + [csAcceptsControls];
  Style := csOwnerDrawFixed;
end;//Create

destructor TJamShellCombo.Destroy;
begin
  FShellBrowser.Free;
  FImageList.Free;
  Inherited Destroy;
end;//Destroy

procedure TJamShellCombo.InsertItem(aIndex: Integer; aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer; PIDL: Pointer; Persistent: boolean);
var item: TJamComboItem;
begin
  if Length(aCaption)<= 0 then begin
    aCaption := aDisplayName;
    if Length(aCaption)<= 0 then
      exit;
  end;
  item            := TJamComboItem.Create;
  item.Caption    := aCaption;
  item.DisplayName:= aDisplayName;
  item.IconNumber := aIconNumber;
  item.Indent     := AIndent;
  item.IsDrive    := (Length(aCaption) in [2..3]) and (aCaption[2]=':');
  item.PIDL       := PIDL;
  item.Persistent := Persistent;
  if aIndex>Items.Count then aIndex:=Items.Count; // Workaround for Delphi 3 problem under Windows 98
  if (aIndex>=0) then
    Items.InsertObject(aIndex, aCaption, item)
  else
    Items.AddObject(aCaption, item);
End;//InsertItem

procedure TJamShellCombo.AddShellItem(aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer; PIDL: Pointer; Persistent: boolean);
begin
  InsertItem(-1, aCaption, aDisplayName, aIconNumber, aIndent, PIDL, Persistent);
End;//AddItem

procedure TJamShellCombo.AddFolder(Path: String; Indent: Integer; Persistent: boolean);
var SHFileInfo: TSHFileInfo;
begin
  if Items.IndexOf(Path)>=0 then exit;
  SHGetFileInfo(PChar(Path), 0, SHFileInfo, sizeof(SHFileInfo), SHGFI_DISPLAYNAME or SHGFI_SMALLICON or SHGFI_SYSICONINDEX);
  AddShellItem(Path, SHFileInfo.szDisplayName, SHFileInfo.iIcon, Indent, nil, Persistent);
end;//AddFolder;

procedure TJamShellCombo.CNDrawItem(var Message: TWMDrawItem);
var
   odsState: TOwnerDrawState;
begin
   with Message.DrawItemStruct^ do
    begin
       FNotDrawingInComboboxEdit := ItemState and ODS_COMBOBOXEDIT = 0;
       odsState := GetOwnerDrawState(itemState);
       Canvas.Handle := hDC;
       Canvas.Font := Font;
       Canvas.Brush := Brush;
       if (Integer(itemID) >= 0) and (odSelected in odsState) then
        begin
      	    Canvas.Brush.Color := clHighlight;
      	    Canvas.Font.Color := clHighlightText
        end;
       if Integer(itemID) >= 0 then     //TOwnerDrawState
      	 DrawItem(itemID, rcItem, odsState)
       else
         Canvas.FillRect(TRect(rcItem));
       Canvas.Handle := 0;
    end;
end;//CNDrawItem

procedure TJamShellCombo.DrawItem(aIndex: Integer; aRect: TRect; aState: TOwnerDrawState);
var x, y   : Integer;
    item   : TJamComboItem;
    SHFileInfo: TSHFileInfo;
    caption: String;
begin
  {if WindowFromDC(Canvas.Handle) = Handle then indent := 0 else indent := i.Indent;
   Should check odComboBoxEdit (aka. ODS_COMBOBOXEDIT) in aState, but StdCtrls doesn't declare it :(
    This WindowFromDC trick works Ok though. :) }

  { Here's what I've done, in CNDrawItem we check if the ODS_COMBOBOXEDIT is checked, if so, we set a boolean field variable
    To True, otherwise to false. We shouldn't use Field variables for this purpose, but at least we're sure that we're doing
    the right thing.
  }

  item := Items.Objects[aIndex] as TJamComboItem;
  if not Assigned(item) then begin
    caption := Items[aIndex];
    Items.Delete(aIndex);
    SHGetFileInfo(PChar(caption), 0, SHFileInfo, sizeof(SHFileInfo), SHGFI_DISPLAYNAME or SHGFI_SMALLICON or SHGFI_SYSICONINDEX);
    InsertItem(aIndex, caption, SHFileInfo.szDisplayName, SHFileInfo.iIcon, 0, nil, True);
    exit;
  end;//if
  Canvas.Brush.Color := Self.Color;
  Canvas.FillRect(aRect);

  if Assigned(FImageList) then
  begin
    if (odSelected in aState) then
    begin
      Canvas.Brush.Color := clHighlight;
      FImageList.BlendColor := clHighlight;
      FImageList.DrawingStyle := dsSelected;
    end
    else
      FImageList.DrawingStyle := dsTransparent;

    y := (aRect.Top + aRect.Bottom - FImageList.Height) div 2;
    FImageList.Draw( Canvas, aRect.Left + Ord(FNotDrawingInComboboxEdit) * item.Indent * fIndentPixels + 2, y, item.IconNumber )
  end;//if

  if (odSelected in aState) then
    Canvas.Brush.Color := clHighlight;

  if (item.Caption <> '') then
  begin
    If Assigned(FImageList) then
      x := FImageList.Width + 6 + item.Indent*fIndentPixels * Ord(FNotDrawingInComboboxEdit)
    else
      x := 6 + item.Indent * fIndentPixels * Ord(FNotDrawingInComboboxEdit);
    y := ((aRect.Bottom - aRect.Top) - Canvas.TextHeight(Item.Caption)) div 2;
    if item.IsDrive then
      Canvas.Textout(aRect.Left+x, aRect.Top+y, item.DisplayName)
    else
      Canvas.Textout(aRect.Left+x, aRect.Top+y, item.Caption);
  end;//if
end;//DrawItem

procedure TJamShellCombo.AddToComboList(aIndex, aIndent: Integer);
var
  Top: Integer;
begin
  Top := aIndex;
  while FShellBrowser.Next do
    if FShellBrowser.GetAttributes(SFGAO_FOLDER or SFGAO_HASSUBFOLDER or SFGAO_FILESYSANCESTOR) and (SFGAO_FOLDER or SFGAO_HASSUBFOLDER or SFGAO_FILESYSANCESTOR) <> 0 then begin // Is it a folder?
      if True{Items.IndexOf(FShellBrowser.ObjectName)<0} then begin // Already inserted?
        if (Length(FShellBrowser.ObjectName)=3) and (FShellBrowser.ObjectName[2]=':') { If it's a drive } then begin
          InsertItem(Top, FShellBrowser.ObjectName, FShellBrowser.GetShellObjectName, FShellBrowser.IconNumber, aIndent, ConcatItemIdLists(FShellBrowser.FolderIdList, FShellBrowser.ItemIdList), True);
          inc(Top);
        end else
          //if not FileSystemOnly or not (fShellBrowser.IsSpecialObject in [SF_NETHOOD, SF_NETWORK]) then begin // Keep out nethood
            InsertItem(aIndex, FShellBrowser.ObjectName, FShellBrowser.GetShellObjectName, FShellBrowser.IconNumber, aIndent, ConcatItemIdLists(FShellBrowser.FolderIdList, FShellBrowser.ItemIdList), True);
            Inc(aIndex);
          //end;//if
      end;//if Items
    end; // FShell...
end;

procedure TJamShellCombo.WMRButtonDown(var Message: TWMRButtonDown);
begin
  Inherited;
  if Assigned(PopupMenu) then exit;
  try
    FShellBrowser.FolderIdList := (Items.Objects[ItemIndex] as TJamComboItem).Pidl;
    FShellBrowser.ShowContextMenu(Point(Message.XPos,Message.YPos), nil);
  finally
    Screen.Cursor := crDefault;
  end;
end;//WMRButtonDown

procedure TJamShellCombo.CreateWnd;
var  LogFont : TLOGFONT;
     h       : THandle;
begin
  Inherited;
  if fInitialized then begin
    if Assigned(FShellLink) then FShellLink.RegisterShellControl(Handle);
    exit;
  end;

  // Get Icon Font
  if SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LogFont), @LogFont, 0) then
  begin
    h := CreateFontIndirect(LogFont);
    Font.Handle := h;
  end;//if
  //EnableAutoComplete(Self.EditHandle, True, False);
  fInitialized := True;
end;

procedure TJamShellCombo.Loaded;
var  Desktopname: String;
begin
  Items.Clear;
  if csDesigning in ComponentState then
    exit;

  fShellBrowser.Loaded;
  FShellBrowser.FolderIdList := DeskTopIdList;

  DesktopName := fShellBrowser.GetDesktopName;
  InsertItem(0, DesktopName, DesktopName, FShellBrowser.GetDesktopIconIndex, 0, DesktopIDList, True);
  FShellBrowser.BrowseSpecialFolder(SF_DESKTOP);
  AddToComboList(1,1);
  if Items.Count > 0 then
  	with Items.Objects[1] as TJamComboItem do begin
                FShellBrowser.BrowseSpecialFolder(SF_DRIVES);
  		AddToComboList(2,2);
  	end;    // with
  if ItemIndex < 0 then
    ItemIndex := 1;
  If Assigned(OnChange) then
    OnChange(Self);
  Inherited;
end;//Loaded

procedure TJamShellCombo.CNCommand(var Message: TWMCommand);
begin
  inherited;
end;

procedure TJamShellCombo.Change;
begin
  Inherited;
  if ItemIndex < 0 then
    exit;
  DeleteNonPersistentFolders(ItemIndex);
  if Assigned(FShellLink) then
    FShellLink.PathChanged(Self, (Items.Objects[ItemIndex] as TJamComboItem).PIDL);
end;

procedure TJamShellCombo.JamSetItemIndex(newValue: Integer);
begin
  if newValue <> inherited ItemIndex then begin
    inherited ItemIndex := newValue;
    if Assigned(FShellLink) and not (csLoading in ComponentState) then
      if inherited ItemIndex <> -1 then
        FShellLink.PathChanged(Self, (Items.Objects[newValue]as TJamComboItem).PIDL)
      else
        FShellLink.PathChanged(Self, nil);
  end;
end;

function TJamShellCombo.JamGetItemIndex: Integer;
begin
  result := inherited ItemIndex;
end;

procedure TJamShellCombo.AddPathToCombo(path: string);

  function FindRoot(DriveName: string; var aIndent: Integer): Integer;
  var
    i: Integer;
  begin
    result := -1;
    for i := 0 to Items.Count - 1 do begin    // Iterate
      with TJamComboItem(items.Objects[i]) do begin
        if TJamComboItem(items.Objects[i]).Caption = DriveName then begin
          aIndent := Indent;
          result := i;
          break;
        end;
      end;
    end;    // for
  end;

  function AddDirectoriesToCombo(path: string; aIndex, aIndent: Integer): Integer;
  var
    localIconNumber, P: Integer;
    localDir: string;
  begin
    result := aIndex;
    if Length(path) = 0 then
      exit;
    p := Pos('\', path);
    if p = 0 then begin
      path := path + '\';
      p := Length(path);
    end;
    localDir := Copy(path, 1, p - 1);
    //if Length(localDir) > 1 then localDir := UpperCase(copy(localDir, 1, 1)) + Lowercase(Copy(localDir, 2, MAX_PATH)); ;
    FShellBrowser.ObjectName := localDir;
    localIconNumber := FShellBrowser.IconNumber;
    FShellBrowser.BrowseObject;
    InsertItem(aIndex, localDir, localDir, localIconNumber, aIndent + 1, CopyItemIdList(FShellBrowser.FolderIdList), false);
    result := AddDirectoriesToCombo(Copy(path, p + 1, MAX_PATH), aIndex +1, aIndent + 1);
  end;

var
  localIndex: Integer;
  localIndent: Integer;
begin
  DeleteNonPersistentFolders(-1);
  localIndex := FindRoot(copy(path, 1, 3), localIndent);
  if localIndex <> -1 then begin
    FShellBrowser.FolderIdList := TJAMComboItem(Items.Objects[localIndex]).PIDL;
    localIndex := AddDirectoriesToCombo(copy(path, 4, MAX_PATH), localIndex + 1, localIndent + 1);
    inherited ItemIndex := localIndex - 1;
    fShellBrowser.SelectParent;
    (Items.Objects[ItemIndex] as TJamComboItem).IconNumber := fShellBrowser.SelectedIconNumber;
  end;
end;

procedure TJamShellCombo.AddIdListToCombo(absIdList: PItemIdList);
var rel_pidl   : PItemIdList;
    in_pidl    : PItemIDList;
    ParentIndex: Integer;
    j          : Integer;
    old_cb     : Integer;
    new_indent : Integer;
begin
  DeleteNonPersistentFolders(-1);
  ParentIndex := 0;
  If not Assigned(absIdList) or (Items.Count=0) then exit;
  in_pidl := absIdList;
  rel_pidl := in_pidl;

  while in_pidl^.mkid.cb <> 0 do begin // Find parent
    Inc(longint(in_pidl), in_pidl^.mkid.cb);
    old_cb := in_pidl.mkid.cb;
    in_pidl.mkid.cb := 0;
    for j:=0 to Items.Count-1 do
      if Desktop.CompareIds(0, absIdList, TJamComboItem(items.Objects[j]).PIDL)=0 then begin
        ParentIndex := j;
        rel_pidl := in_pidl;
        break;
      end;//if
    in_pidl.mkid.cb := old_cb;
  end;//while
  FShellBrowser.FolderIdList := TJAMComboItem(Items.Objects[ParentIndex]).PIDL;

  while rel_pidl^.mkid.cb <> 0 do begin
    in_pidl := rel_pidl;
    Inc(longint(in_pidl), in_pidl^.mkid.cb);
    old_cb := in_pidl.mkid.cb;
    in_pidl.mkid.cb := 0;
    FShellBrowser.ItemIdList := rel_pidl;
    in_pidl.mkid.cb := old_cb;
    new_indent := TJAMComboItem(Items.Objects[ParentIndex]).Indent + 1;
    With FShellBrowser do
      InsertItem(ParentIndex+1, GetShellObjectName, GetShellObjectName, IconNumber, new_indent, CopyItemIdList(FShellBrowser.AbsoluteItemIdList), false);
    Inc(ParentIndex);
    rel_pidl := in_pidl;
    FShellBrowser.BrowseObject;
  end;//while

  inherited ItemIndex := ParentIndex;
end;//AddIdListToCombo

procedure TJamShellCombo.DeleteNonPersistentFolders(fromIndex: Integer);
var
  i: integer;
begin
  for i := Items.Count - 1 downto FromIndex + 1 do begin    // Iterate
    with TJamComboItem(items.Objects[i]) do begin
      if not persistent then
        Self.Delete(i);
    end;    // with
  end;    // for
end;

procedure TJamShellCombo.Delete(Index: Integer);
var Data: TJamComboItem;
begin
  Data := Items.Objects[Index] as TJamComboItem;
  if Assigned(Data) then begin
    With Data do begin
      Allocator.Free(PIDL);
    end;//with
  end;//if
  items.Delete(Index);
  Data.Free;
end;//Delete


procedure TJamShellCombo.Notification(AComponent: TComponent; operation: TOperation);
begin
  inherited Notification(AComponent, operation);
  if operation = opRemove then
  begin
    if AComponent = FShellLink then
      FShellLink := nil;
  end;
end;

function TJamShellCombo.GetVersion: String;
begin
  Result := ClassName + JAM_COMPONENT_VERSION;
end;//GetVersion

procedure TJamShellCombo.SetVersion(s: String);
begin
  // empty
end;//SetVersion


{***************************** T J A M S H E L L L I S T **********************}

var _Reverse: Integer;  // One parameter for the compare function is not enough

function ShellListCompareFunc(aItem1, aItem2: TListItem; ishf: IShellFolder): Integer; stdcall;
var h   : HResult;
begin
  h := ishf.CompareIds(TJamShellList(aItem1.ListView).SortColumn, TJamShellListItem(aItem1.Data).RelativePIDL, TJamShellListItem(aItem2.Data).RelativePIDL);
  if Succeeded(h) then
    result := SmallInt(HResultCode(h)) * _Reverse
  else
    result := 0;
end;//ShellListCompareFunc


constructor TJamShellList.Create(AOwner: TComponent);
begin
  Inherited Create(AOwner);
  fInitialized := False;
  fShellBrowser := TShellBrowser.Create(Self);
  SmallImages := TJamSystemImageList.Create(Self);
  LargeImages := TJamSystemImageList.Create(Self);
  (LargeImages as TJamSystemImageList).Size := si_large;
  fShellBrowser.FileSystemOnly := False;
  fShellBrowser.OnFileChange := FileChange;
  fUpdateTimer := TTimer.Create(Self);
  fUpdateTimer.Enabled := False;
  fUpdateTimer.OnTimer := TimerChange;
  fUpdateTimer.Interval := 500;
  fDetails := True;
  fShowHidden := True;
  fShowFolders := True;
  fSortColumn := 0;
  ViewStyle := vsReport;
  MultiSelect := True;
  AllocBy := 32;
  fDropTarget := nil;
  fOleDragDrop := True;
  fIgnoreChanges := False;
  fContextMenu := True;
  fSelectedList := nil;
  {$ifndef _VCL_4_UP} _AddRef; {$endif}
end;//Create

destructor TJamShellList.Destroy;
begin
  fShellBrowser.Free;
  SmallImages.Free;
  LargeImages.Free;
  fSelectedList.Free;
  inherited Destroy;
end;//Destroy

procedure TJamShellList.CreateWnd;
var  LogFont : TLOGFONT;
     h       : THandle;
begin
  Inherited;
  if fInitialized then begin
    if assigned(FShellLink) then FShellLink.RegisterShellControl(Handle);
    Refresh;
    exit;
  end;

  // Get icon font
  if SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LogFont), @LogFont, 0) then
  begin
    h := CreateFontIndirect(LogFont);
    Font.Handle := h;
  end;//if

  fShellBrowser.Loaded;
  if Path='' then Path := ''; // Initilize correctly if no path set
  fInitialized := True;
end;//CreateWnd

procedure TJamShellList.Loaded;
begin
  Inherited;
  if not Assigned(ShellLink) or (Items.Count<=0) then Refresh;
end;//Loaded

procedure TJamShellList.DestroyWnd;
begin
  if assigned(FShellLink) then
    FShellLink.UnregisterShellControl(Handle);
  Inherited;
end;//DestroyWnd

procedure TJamShellList.SetPath(aPath: String);
begin
  if csLoading in ComponentState then
    try // We don't want that during loading an exception prevents the application from being started
      fShellBrowser.Folder := aPath;
    except
      MessageDlg('Cannot find path: ' + aPath, mtError, [mbOK], 0);
    end
  else
    fShellBrowser.Folder := aPath;
  if assigned(FShellLink) then
    FShellLink.PathChanged(Self, fShellBrowser.FolderIdList);
  Refresh;
end;//SetPath

function TJamShellList.GetPath: String;
begin
  Result := fShellBrowser.Folder;
end;//GetPath

procedure TJamShellList.SetSortColumn(col: Integer);
begin
  fReverseOrder := (fSortColumn = col) and not fReverseOrder;
  fSortColumn := col;
  if fReverseOrder then _Reverse := -1 else _Reverse := 1;
  CustomSort(@ShellListCompareFunc, Integer(fShellBrowser.ShellFolder));
end;//SetSortColumn

procedure TJamShellList.SetReverseSortOrder(reverse: Boolean);
begin
  fReverseOrder := reverse;
  if fReverseOrder then _Reverse := -1 else _Reverse := 1;
  CustomSort(@ShellListCompareFunc, Integer(fShellBrowser.ShellFolder));
end;//SetSortColumn

procedure TJamShellList.SetFileSystemOnly(aValue: Boolean);
begin
  fShellBrowser.FileSystemOnly := aValue;
  Refresh;
end;

function  TJamShellList.GetFileSystemOnly: Boolean;
begin
  Result := fShellBrowser.FileSystemOnly
end;//GetFileSystemOnly

procedure TJamShellList.WMRButtonUp(var Message: TWMRButtonUp);
var Item   : TListItem;
    Pos,
    AbsPos : TPoint;
    hti: TLVHitTestInfo;
    index: Integer;
begin
  if Message.XPos>=0 then begin
    Inherited MouseUp(mbRight, KeysToShiftState(Message.Keys), Message.XPos, Message.YPos);
    {$ifdef _DELPHI_5_UP}
    Pos    := ScreenToClient(Point(Message.XPos,Message.YPos));
    AbsPos := Point(Message.XPos,Message.YPos);
    {$else}
    Pos    := Point(Message.XPos,Message.YPos);
    AbsPos := ClientToScreen(Point(Message.XPos,Message.YPos));
    {$endif}
    // Perform hit test, TCustomListView.GetItemAt doesn't work as expected, se we use the API functions here
    hti.pt := Pos;
    hti.flags := LVHT_ONITEM;
    index := ListView_HitTest(Handle, hti);
    if hti.flags=LVHT_NOWHERE then
      Item := nil
    else
      Item := Items[index];
  end else begin
    // The context menu key was used, No X or Y postion
    Item := Selected;
    if Assigned(Selected) then
      AbsPos := ClientToScreen(Item.DisplayRect(drSelectBounds).BottomRight)
    else
      AbsPos := Point(1,1);
  end;//else
  if Assigned(Item) and ShellContextMenu then
    ShowContextMenu(AbsPos)
  else // No Item hit
    ShowBackgroundMenu(AbsPos);
  Message.Msg := 0;
end;//WMRButtonUp


procedure TJamShellList.Change(Item: TListItem; Change: Integer);
begin
  if not fIgnoreChanges and ((Change AND LVIF_STATE) >0) and Assigned(fSelectedList) then
    fSelectedList.Clear;
  Inherited;
end;

function TJamShellList.GetSelectedFiles: TStringList;
var i: Integer;
    s: String;
begin
  if not Assigned(fSelectedList) then
    fSelectedList := TStringList.Create;
  Result := fSelectedList;
  fSelectedList.OnChange := nil; // We don't want the OnChange event fired while _we_ change the list
  if fSelectedList.Count=0 then begin
    for i:=0 to Items.Count-1 do
      if Items[i].Selected then begin
        fShellBrowser.ItemIdList := TJamShellListItem(Items[i].Data).RelativePidl;
        s := fShellBrowser.ObjectName;
        if Length(s)=0 then s := fShellBrowser.GetShellObjectName;
        fSelectedList.Add(s);
      end;//if
  end;//if
  fSelectedList.OnChange := SelectedListChange;
end;//GetSelectecFiles

procedure TJamShellList.SelectedListChange(Sender: TObject);
var i,n: Integer;
begin
  if fSelectedList.Count<=0 then exit;
  fIgnoreChanges := True;
  Selected := nil;
  try
    for i:=0 to fSelectedList.Count-1 do begin
      fShellBrowser.Objectname := fSelectedList.Strings[i];
      n := IndexOfPIDL(fShellBrowser.ItemIdList);
      if n>=0 then with Items[n] do begin
        Selected := True;
        Focused := True;
        MakeVisible(False);
        SetFocus;
      end;//with/if
    end;//for i
  finally
    fIgnoreChanges := False;
  end;//try
end;//SelectedListChange

function TJamShellList.GetFullPath(item: TListItem): String;
begin
  fShellBrowser.ItemIdList := TJamShellListItem(Item.Data).RelativePidl;
  Result := fShellBrowser.Folder + fShellBrowser.ObjectName;
end;

function TJamShellList.ShowContextMenu(p: TPoint): String;
var i: Integer;
    Files_clip: TStrings;
    Files_del: TStrings;
    op: TJamShellOperations;
begin
  PrepareMultiObjects;
  if ReadOnly then
    fShellBrowser.OnRename := nil
  else
    fShellBrowser.OnRename := HandleRenameEvent;
  // Save file names for OnOperation event
  Files_clip := GetFilenamesFromHandle(Clipboard.GetAsHandle(CF_HDROP));
  Files_del := TStringList.Create;
  for i:=0 to SelectedFiles.Count-1 do
    Files_del.Add(Path+SelectedFiles[i]);

  fShellBrowser.ReadOnly := Self.ReadOnly;
  if Assigned(PopupMenu) then PopupMenu.Autopopup := False;
  Result := fShellBrowser.ShowContextMenu(p, PopupMenu);
  if (CompareText(Result, 'delete')=0) then
    Operation([sopDelete,sopRemove], Files_del, '')
  else begin
    Files_del.Free;
  end;
  if (CompareText(Result, 'paste')=0) then begin
    op := [sopPaste,sopAdd];
    if Assigned(Files_clip) and ((Files_clip.Count>0) and not FileExists(Files_clip[0])) then
      op := op + [sopMove]
    else
      op := op + [sopCopy];
    Operation(op, Files_clip, Path+Selected.Caption);
  end else
    Files_clip.Free;
  if CompareText(Result, 'cut')=0 then begin
    for i:=0 to Items.Count-1 do
      if Items[i].Selected then
        Items[i].Cut := True;
  end;//if 'cut'
end;//ShowContextMenu

function  TJamShellList.GetOnContextMenuSelect: TOnContextMenuSelectEvent;
begin
  Result := fShellBrowser.OnContextMenuSelect;
end;//GetOnContextMenuSelect

procedure TJamShellList.SetOnContextMenuSelect(anEvent: TOnContextMenuSelectEvent);
begin
  fShellBrowser.OnContextMenuSelect := anEvent;
end;//SetOnContextMenuSelect

function TJamShellList.ShowBackgroundMenu(p: TPoint): Boolean;
{var shellview: IShellView;
    lpcm     : IContextMenu;
    Menu     : TPopupMenu;
    idcmd    : WORD;
    hr       : HResult;}
begin
  Result := False;
  { does not work yet
  hr := fShellBrowser.ShellFolder.CreateViewObject(Handle, IID_IShellView, Pointer(shellview));
  if SUCCEEDED(hr) then begin
    hr := shellview.GetItemObject(SVGIO_BACKGROUND, IID_IContextMenu, Pointer(lpcm));
    if SUCCEEDED(hr) then begin
      Menu := TPopUpMenu.Create(Self);
      if Assigned(Menu) then begin
        hr := lpcm.QueryContextMenu(Menu.Handle, 0, 1, $7fff, CMF_EXPLORE);
        if Succeeded(hr) then begin
           idCmd := WORD(TrackPopupMenu(Menu.Handle, TPM_LEFTALIGN or TPM_RETURNCMD or TPM_RIGHTBUTTON, 200, 200, 0, TWinControl(Owner).Handle, nil));
        end;
      end;
    end;
  end;//if}
  if Assigned(BackgroundPopupMenu) then begin
    BackgroundPopupMenu.Popup(p.X, p.Y);
    Result := True;
  end;
end;

procedure TJamShellList.MouseDown( aButton: TMouseButton;  aShift: TShiftState;  x, y: Integer );
var tmp: Integer;
begin
  Inherited;
  if (aButton = mbLeft) and (ssDouble in aShift) and (not Assigned(OnDblClick) or not Assigned(Owner)) then begin
    if csLoading in ComponentState then begin
      tmp := Selected.Index;
      Loaded; //Works around a strange Delphi bug when BorderStyle = bsNone
      if (tmp>=0) and (tmp<Items.Count) then Items[tmp].Selected := True;
    end;
    InvokeCommandOnSelected('default');
  end;
end;//MouseDown

procedure TJamShellList.SetDetails(aDetails: Boolean);
begin
  if FDetails = ADetails then exit;
  fDetails := ADetails;
  Refresh;
end;//SetDetails

// Set method for the ShowHidden property
procedure TJamShellList.SetShowHidden(val: Boolean);
begin
  if val=fShowHidden then exit;
  fShowHidden := val;
  Refresh;
end;//SetShowHidden

// Set method for the ShowFolders property
procedure TJamShellList.SetShowFolders(val: Boolean);
begin
  if val=fShowFolders then exit;
  fShowFolders := val;
  Refresh;
end;//SetShowFolders

procedure TJamShellList.AddShellItem(Details: Boolean);
var i          : Integer;
    Item       : TListItem;
    CanAdd     : Boolean;
begin
  if not fShowHidden and fShellBrowser.IsHidden then exit;
  if not ShowFolders and fShellBrowser.IsFolder then exit;
  Item := Items.Add;
  Item.Caption := fShellBrowser.GetShellObjectName;

  //OnAddItem event
  If Assigned(OnAddItem) then begin
    CanAdd := True;
    if Details then
      for i:=1 to fColCount-1 do
        Item.SubItems.Add(FShellBrowser.GetColumnText(i, False));
    OnAddItem(Item, CanAdd);
    if not CanAdd then begin
      Item.Delete;
      exit;
    end;
  end;//if

  Item.Data       := TJamShellListItem.Create;
  TJamShellListItem(Item.Data).RelativePIDL := fShellBrowser.ItemIdList;
  TJamShellTreeItem(Item.Data).Tag := 1;  // for SmartRefresh
end;//AddItem

// Fills a given ListView with data of the current folder
function  TJamShellList.Refresh: Boolean;

  procedure StoreColumnWidths;
  var i: Integer;
  begin
    for i:=0 to Columns.Count-1 do begin
      ColumnWidth[i]:=Columns[i].Width;
      if i>=High(ColumnWidth) then exit;
    end;//for
  end;//StoreColumnsWidthS

  procedure InitShellColumns;
  var col : TListColumn;
      Title: String;
      w   : Integer;
      alg   : TAlignment;
  begin
    Columns.BeginUpdate;
    if FileSystemFolder then StoreColumnWidths;
    FileSystemFolder := Length(fShellBrowser.Folder)>0;
    Columns.Clear;
    fColCount := 0;
    Title := fShellBrowser.GetColumnText(fColCount, True);
    while Length(Title)>0 do begin
      alg := FShellBrowser.GetColumnInfo(fColCount, w);
      if w<=0 then continue;// Column isn't visible by default
      col := Columns.Add;
      col.Caption := Title;
      col.Alignment := alg;
      if FileSystemFolder and (col.Index<High(ColumnWidth)) and (ColumnWidth[col.Index]>0) then
        col.Width := ColumnWidth[col.Index]
      else
        col.Width := w;
      Inc(fColCount);
      if not Details then break;//while
      Title := FShellBrowser.GetColumnText(fColCount, True);
    end;
    Columns.EndUpdate;
    fNumShellColumns := Columns.Count;
  end;

begin
  Result := False;
  if (csLoading in ComponentState) or not Enabled then exit;
  Screen.Cursor := crHourGlass;
  Items.BeginUpdate;
  Items.Clear; // Clear list
  InitShellColumns;
  if Assigned(OnCreateColumns) then OnCreateColumns(Self);

  While fShellBrowser.Next do begin // Enumerate Files
    AddShellItem(Details);
  end;//while

  if fReverseOrder then _Reverse := -1 else _Reverse := 1;
  CustomSort(@ShellListCompareFunc, Integer(fShellBrowser.ShellFolder));
  if Assigned(OnPopulated) then OnPopulated(Self);
  Items.EndUpdate;
  Screen.Cursor := crDefault;
  Result := True;
end;//Refresh

procedure TJamShellList.CNNotify(var Message: TWMNotify);
var Item: TListItem;
    Attributes : Cardinal;
    col_text: String;
begin
  case Message.NMHdr.code of
  LVN_GETDISPINFO: begin
    with PLVDispInfo(Pointer(Message.NMHdr))^.item do begin
      if (mask and LVIF_PARAM) <> 0 then
        Item := TListItem(lParam)
      else
        Item := Items[IItem];
      if (mask and LVIF_TEXT) <> 0 then begin
        if ((iSubItem=0) or Details) and Assigned(Item.Data) then begin
          FShellBrowser.ItemIdList := TJamShellListItem(Item.Data).RelativePidl;
          if (iSubItem<=fColCount) and (iSubItem<fNumShellColumns) then begin
            col_text := FShellBrowser.GetColumnText(iSubItem, False);
            StrPLCopy(pszText, col_text, cchTextMax);
          end else
            Inherited;
          mask := mask or LVIF_DI_SETITEM;//invariant, do not ask again
        end//if
        else
          Inherited;
      end;//if LVIF_TEXT
      if (mask and LVIF_IMAGE) <> 0 then begin // Icon number
        if (iSubItem=0) and Assigned(Item.Data) then begin
          FShellBrowser.ItemIdList := TJamShellListItem(Item.Data).RelativePidl;
          iImage := FShellBrowser.IconNumber;
          // Get Overlay Icon
          Attributes := fShellBrowser.GetAttributes({SFGAO_LINK or SFGAO_SHARE or }SFGAO_HIDDEN or SFGAO_GHOSTED);
          //if (Attributes and SFGAO_LINK) <> 0 then Item.OverlayIndex := LinkOverlay;
          //if (Attributes and SFGAO_SHARE) <> 0 then Item.OverlayIndex := ShareOverlay;
          Item.OverlayIndex := fShellBrowser.GetOverlayIndex;
          if (Attributes and (SFGAO_HIDDEN or SFGAO_GHOSTED)) <> 0 then begin
            mask := mask or LVIF_STATE; stateMask := LVIS_CUT; state := LVIS_CUT;
          end;
          mask := mask or LVIF_DI_SETITEM;//invariant icon, do not ask again
        end;//if
      end;//if
    end;//with
  end;//LVN_GETDISPINFO

  LVN_BEGINDRAG: begin
    if OleDragDrop and Assigned(Selected) then
      BeginOleDrag(mbLeft);
  end;//LVN_BEGINDRAG

  LVN_BEGINRDRAG: begin
    if OleDragDrop and Assigned(Selected) then
      BeginOleDrag(mbRight);
  end;//LVN_BEGINRDRAG

  else//case
    Inherited;
  end;//case
end;//CNNotify

// Returns index of object based on its ItemIDList or -1 if object is not present
// The passed ItemIDList is freed afterwards
function TJamShellList.IndexOfPIDL(pidl: PItemIDList): Integer;
var i: Integer;
begin
  Result := -1;
  for i:=0 to Items.Count-1 do
    if fShellBrowser.ShellFolder.CompareIDs(0, pidl, TJamShellListItem(Items[i].Data).RelativePIDL) = 0 then
    begin
      Result := i;
      break;
    end;//if
  Allocator.Free(pidl);
end;//IndexOf

procedure TJamShellList.SmartRefresh;

{  // Returns index of object based on its name -1 if object is not present
  function IndexOf(Caption: String): Integer;
  var i: Integer;
  begin
    Result := -1;
    for i:=0 to Items.Count-1 do
      if Caption=Items[i].Caption then begin
        Result := i;
        exit;
      end;//if
  end;//IndexOf}

var i      : Integer;
    index  : Integer;
    cutfiles: TStrings;
begin
  cutfiles := TStringList.Create;
  for i:=0 to Items.Count-1 do // Set all Tags to "not present"
    TJamShellListItem(Items[i].Data).Tag := 0;

  While fShellBrowser.Next do begin // Enumerate folder again
    //index := IndexOf(fShellBrowser.GetShellObjectName);
    index := IndexOfPIDL(fShellBrowser.ItemIDList);
    if index>=0 then // Set tag to "is present"
      TJamShellListItem(Items[index].Data).Tag := 1
    else begin
      AddShellItem(Details);
    end;
  end;//while

  i:=0;
  while i<Items.Count do begin
    if TJamShellListItem(Items[i].Data).Tag = 0 then begin
      if Items[i].Cut then cutfiles.Add(Path+Items[i].Caption);
      Items[i].Delete;
    end else
      Inc(i);
  end;//while
  Operation([sopCut,sopRemove], cutfiles, '');
end;//SmartRefresh

procedure TJamShellList.TimerChange(Sender: TObject);
begin
  fUpdateTimer.Enabled := False;
  SmartRefresh;
  //if Assigned(fShellLink) then fShellLink.SmartRefresh(self);
end;//TimerChange

procedure TJamShellList.Delete(Item: TListItem);
var Data: TJamShellListItem;
begin
  // Free memory that is associated with each item
  Data := TJamShellListItem(Item.Data);
  if Assigned(Data) then begin
    With Data do begin
      Allocator.Free(RelativePIDL);
    end;//with
    Item.Data := nil;
  end;//if
  Inherited;
  Data.Free;
end;//Delete

procedure TJamShellList.ColClick(Column: TListColumn);
begin
  SortColumn := Column.Index;
  Inherited;
end;//ColClick

procedure TJamShellList.GoUp;
begin
  if assigned(fShellLink) then
    fShellLink.GoUp(Self)
  else begin
    fShellBrowser.SelectParent;
    Refresh;
  end;
end;//Refresh

function TJamShellList.CreateDir(Name: String; EditMode: Boolean): Boolean;
var item: TListItem;
begin
  if Length(Name)<=0 then name := strNewFolder;
  Result := SysUtils.CreateDir(Path+Name);
  if EditMode then begin
    SmartRefresh;
    item := FindCaption(0, Name, False, True, False);
    if Assigned(item) then begin
      item.Selected := True;
      item.EditCaption;
    end;
  end;
end;//CreateDir

function TJamShellList.InvokeCommandOnSelected(Command: String): Boolean;
var i     : Integer;
    Files : TStrings;
    LinkTarget: String;
    op: TJamShellOperations;
begin
  if SelCount=0 then begin
    Result := False;
    exit;
  end;
  // Save file names for OnOperation event
  Files := nil;
  if (CompareText(command, 'paste')=0) then begin
    Files := GetFilenamesFromHandle(Clipboard.GetAsHandle(CF_HDROP))
  end else
    if (CompareText(command, 'delete')=0) then begin
      Files := TStringList.Create;
      for i:=0 to SelectedFiles.Count-1 do
        Files.Add(Path+SelectedFiles[i]);
    end;//if

  // different code for one and multiple selected objects
  if SelCount=1 then begin
    fShellBrowser.ItemIdList := TJamShellListItem(Selected.Data).RelativePIDL;
    if (CompareText(Command, 'default')=0) or (CompareText(Command, 'open')=0) then
    begin // Browse into folder
      LinkTarget := fShellBrowser.IsLinkToFolder;
      if fShellBrowser.IsFolder then begin
        fShellBrowser.BrowseObject;
        if assigned(FShellLink) then
          FShellLink.PathChanged(Self, fShellBrowser.FolderIdList);
        Refresh;
        Result := True;
      end else if Length(LinkTarget)>0 then begin
        fShellBrowser.Folder := LinkTarget;
        Refresh;
        if assigned(FShellLink) then
          FShellLink.PathChanged(Self, fShellBrowser.FolderIdList);
        Result := True;
      end else
        Result := fShellBrowser.InvokeContextMenuCommand(Command);
    end//if default/open
    else
      Result := fShellBrowser.InvokeContextMenuCommand(Command);
  end//if SelCount=1
  else begin
    PrepareMultiObjects;
    Result := fShellBrowser.InvokeContextMenuCommand(Command);
  end;//else
  if Result and (CompareText(command, 'delete')=0) then begin
    Operation([sopDelete,sopRemove], Files, '');
    SmartRefresh;
  end;//if 'delete'
  if Result and (CompareText(command, 'paste')=0) then begin
    op := [sopPaste,sopAdd];
    if Assigned(files) and ((files.Count>0) and not FileExists(files[0])) then
      op := op + [sopMove]
    else
      op := op + [sopCopy];
    Operation(op, Files, Path);
  end;//if 'paste'
  if Result and (CompareText(command, 'cut')=0) then begin
    for i:=0 to Items.Count-1 do
      if Items[i].Selected then
        Items[i].Cut := True;
  end;//if 'cut'
end;//InvokeCommandOnSelected


function TJamShellList.InvokeCommandOnFolder(Command: String): Boolean;
var Files: TStrings;
    op: TJamShellOperations;
begin
  Files := nil;
  fShellBrowser.OnFileChange := nil;
  fShellBrowser.SelectParent;
  if (CompareText(command, 'paste')=0) then begin
    Files := GetFilenamesFromHandle(Clipboard.GetAsHandle(CF_HDROP));
  end;//if
  Result := fShellBrowser.InvokeContextMenuCommand(command);
  fShellBrowser.BrowseObject;
  fShellBrowser.OnFileChange := FileChange;
  if Result and (CompareText(command, 'paste')=0) then begin
    op := [sopPaste,sopAdd];
    if ((files.Count>0) and not FileExists(files[0])) then op := op + [sopMove]
    else op := op + [sopCopy];
    Operation(op, Files, Path);
  end;//if
  FileChange(Self);
end;//InvokeCommandOnFolder


procedure TJamShellList.PrepareMultiObjects;
var i: Integer;
begin
  if not Assigned(Selected) then exit;
  for i:=0 to SelectedFiles.Count-1 do
    fShellBrowser.MultiObjects.Add(SelectedFiles[i]);
end;//PrepareMultiObjects

procedure TJamShellList.KeyDown( var key: Word;  aShiftState: TShiftState );
//var Files: TStrings;
begin
  if not IsEditing then
    case key of
      vk_F2:     if Assigned(Selected) then Selected.EditCaption;
      vk_F5:     begin Refresh;   if Assigned(fShellLink) then fShellLink.Refresh(Self) end;
      vk_F10:    if (ssShift in aShiftState) and ShellContextMenu and Assigned(Selected) then
                   ShowContextMenu(ClientToScreen(Selected.DisplayRect(drSelectBounds).BottomRight));
      vk_Delete: if not ReadOnly then InvokeCommandOnSelected('delete');
      Word('C'): if (ssCtrl in aShiftState) then begin
                   InvokeCommandOnSelected('copy');
                   key := 0;
                 end;
      Word('X'): if not ReadOnly and (ssCtrl in aShiftState) then begin
                   InvokeCommandOnSelected('cut');
                   key := 0;
                 end;
      Word('V'): if not ReadOnly and (ssCtrl in aShiftState) then begin
                   InvokeCommandOnFolder('paste');
                   key := 0;
                 end;
      Word('A'): if (ssCtrl in aShiftState) then begin
                   SelectAll;
                   key := 0;
                 end;
    end;//case
end;//KeyDown

procedure TJamShellList.KeyPress( var key: Char );
begin
  if not IsEditing then
    case key of
      #13: begin
             InvokeCommandOnSelected('default');
             key := #0;
           end;
      #8:  begin
             GoUp;
             key := #0;
           end;
    end;
  inherited;
end;//KeyPress

procedure TJamShellList.SetFolderIdList(IdList: PItemIdList);
begin
  fShellBrowser.FolderIdList := IdList;
  if assigned(fShellLink) then
    fShellLink.PathChanged(Self, CopyItemIdList(fShellBrowser.FolderIdList));
  Refresh;
end;//SetFolderIdList

function  TJamShellList.GetFolderIdList: PItemIdList;
begin
  Result := fShellBrowser.FolderIdList;
end;//GetFolderIdList

function TJamShellList.CanEdit(Item: TListItem): Boolean;
begin
  Result := Inherited CanEdit(Item);
  fShellBrowser.ObjectName := Item.Caption;
  Result := Result and fShellBrowser.CanRename;
end;

procedure TJamShellList.Edit(const Item: TLVItem);
  function GetItem(Value: TLVItem): TListItem;
  begin
    with Value do
      if (mask and LVIF_PARAM) <> 0 then Result := TListItem(lParam)
      else Result := Items[IItem];
  end;
var
  S: string;
  EditItem: TListItem;
  Files: TStringList;
begin
  Inherited;
  with Item do
  begin
    if not Assigned(Item.pszText) then exit;
    S := pszText;
    EditItem := GetItem(Item);
    if EditItem <> nil then begin
      Files := TStringList.Create;
      fShellBrowser.ItemIdList := TJamShellListItem(EditItem.Data).RelativePIDL;
      Files.Add(Path+fShellBrowser.ObjectName);
      fShellBrowser.RenameObject(S);
      EditItem.Caption := S; //fShellBrowser.GetShellObjectName;
      Allocator.Free(TJamShellListItem(EditItem.Data).RelativePIDL);
      TJamShellListItem(EditItem.Data).RelativePIDL := fShellBrowser.ItemIdList;
      if ViewStyle=vsIcon then Refresh;
      Operation([sopRename], Files, S);
    end;
  end;
end;//Edit

procedure TJamShellList.Operation(op: TJamShellOperations; Files: TStrings; Destination: String);
begin
  if sopDelete in op then begin
    Items.BeginUpdate;
    while Assigned(Selected) do
      Selected.Delete;
    Items.EndUpdate;
  end;//if
  if Assigned(Files) and (Files.Count>0) and Assigned(OnOperation) then begin
    OnOperation(Self, op, Files, Destination);
    Files.Free;
  end;
  if (([sopMove, sopDelete, sopRemove, sopRename] * op) <> []) and Assigned(ShellLink) then
    ShellLink.SmartRefresh(Self);
end;//Operation

procedure TJamShellList.SetShellLink(newValue: TJamShellLink);
begin
  if FShellLink <> newValue then begin
    if assigned(FShellLink) then
      FShellLink.UnregisterShellControl(Handle);
    FShellLink := newValue;
    if assigned(FShellLink) then
      FShellLink.RegisterShellControl(Handle);
  end;
end;

procedure TJamShellList.SetOleDragDrop(val: Boolean);
var DropTarget: IDropTarget;
begin
  fOleDragDrop := val;
  DropTarget := Self;
  if csDesigning in ComponentState then exit;
  if fOleDragDrop then begin
    if not (RegisterDragDrop(Self.Handle, DropTarget) = S_OK) then
      fOleDragDrop := False;
  end else begin
    RevokeDragDrop(Self.Handle);
  end;//else
end;//SetOleDragDrop

procedure TJamShellList.JAMPathChanged(var Message: TJAMPathChanged);
begin
  if assigned(Message.PIDL) then begin
    try
      fShellBrowser.FolderIdList := Message.PIDL;
      Refresh;
    except
      Items.Clear;
    end;
  end;
end;//JAMPathChanged

procedure TJamShellList.JAMRefresh(var Message: TJAMPathChanged);
begin
  Refresh;
end;//JAMRefresh;

procedure TJamShellList.JAMSmartRefresh(var Message: TJAMPathChanged);
begin
  SmartRefresh;
end;//JAMSmartRefresh;

procedure TJamShellList.JAMSelectAll(var Message: TJAMPathChanged);
begin
  SelectAll;
  SetFocus;
end;//JAmSelectAll

procedure TJamShellList.JAMGoUp(var Message: TMessage);
begin
  fShellBrowser.SelectParent;
  Refresh;
  if assigned(fShellLink) then
    fShellLink.PathChanged(Self, CopyItemIdList(fShellBrowser.FolderIdList));
  Message.ResultLo := 1;
end;

procedure TJamShellList.FileChange(Sender: TObject);
begin
  fUpdateTimer.Enabled := False;
  fUpdateTimer.Enabled := True;
end;//FileChange

procedure TJamShellList.Notification(AComponent: TComponent; operation: TOperation);
begin
  inherited Notification(AComponent, operation);
  if operation = opRemove then
  begin
    if AComponent = FShellLink then
      FShellLink := nil;
  end;
end;//Notification

procedure TJamShellList.WMInitMenuPopup(var Message: TMessage);
begin
  Inherited;
  fShellBrowser.HandlePopupMessages(Message);
end;

procedure TJamShellList.WMMeasureItem(var Message: TMessage);
begin
  Inherited;
  fShellBrowser.HandlePopupMessages(Message);
end;

procedure TJamShellList.WMDrawItem(var Message: TMessage);
begin
  Inherited;
  fShellBrowser.HandlePopupMessages(Message);
end;

procedure TJamShellList.SetFilter(Pattern: String);
begin
  fShellBrowser.Filter := Pattern;
  Refresh;
end;//SetFilter

function  TJamShellList.GetFilter: String;
begin
  Result := fShellBrowser.Filter;
end;//GetFilter

procedure TJamShellList.HandleRenameEvent;
begin
  if Assigned(Selected) then Selected.EditCaption;
end;

function TJamShellList.GetSpecialFolder: TJamShellfolder;
begin
  Result := fShellBrowser.IsSpecialFolder;
  if (Result=SF_DRIVES) and (Length(Path)>0) then Result := SF_FILESYSTEMFOLDER;
end;//GetSpecialFolder

procedure TJamShellList.SetSpecialFolder(folder: TJamShellFolder);
begin
  if folder=SF_FILESYSTEMFOLDER then
//    Path := Path;
  else
    fShellBrowser.BrowseSpecialFolder(folder);
  Refresh;
  if assigned(FShellLink) then
    FShellLink.PathChanged(Self, fShellBrowser.FolderIdList);
end;//SetSpecialFolder

function TJamShellList.GetVersion: String;
begin
  Result := ClassName + JAM_COMPONENT_VERSION;
end;//GetVersion

procedure TJamShellList.SetVersion(s: String);
begin
  // empty
end;//SetVersion

procedure TJamShellList.BeginOleDrag(aButton: TMouseButton);
var pidls   : Array [0..60000] of PItemIdList;
    attr    : Array [0..60000] of UINT;
    fDropSource: IDropSource;
    fDataObject: IDataObject;
    effect, effect2: LongInt;
    i, counter: Integer;
    hr: HResult;
    op: TJamShellOperations;
begin
  counter := 0;
  // Collect all PItemIdLists of the selected ITems
  for i:=0 to Items.Count-1 do
    if Items[i].Selected and Assigned(Items[i].Data) then begin
      pidls[counter] := TJamShellListItem(Items[i].Data).RelativePIDL;
      attr[counter]  := DRAGFLAGS;
      Inc(counter);
    end;//if
  // Get Drag Drop Attributes of these items
  fShellBrowser.ShellFolder.GetAttributesOf(counter, pidls[0], attr[0]);
  effect := DRAGFLAGS;
  for i:=0 to counter-1 do
    effect := effect and attr[i];
  // Store initially pressed mouse button
  case aButton of
    mbLeft  : fDragButton := MK_LBUTTON;
    mbRight : fDragButton := MK_RBUTTON;
    mbMiddle: fDragButton := MK_MBUTTON;
  end;

  try // Get IDataObject
    hr := fShellBrowser.ShellFolder.GetUIObjectOf(Self.Handle, counter, pidls[0], IID_IDataObject, nil, Pointer(fDataObject));
    if (hr<>NOERROR) then exit;//ShowMessage('Could not get IDataObject');
    DoDragDrop(fDataObject, Self, effect, effect2);
  finally
    if effect2<>DROPEFFECT_NONE then begin
      op := [sopDrag];
      if effect2=DROPEFFECT_COPY then op := op + [sopCopy];
      if effect2=DROPEFFECT_MOVE then op := op + [sopMove,sopRemove];
      Operation(op, GetFilenamesFromDataObject(fDataObject), '');
    end;
    fDropSource := nil;
    fDragButton := 0;
  end;
end;

// IDropTarget methods
function TJamShellList.DragEnter(const DataObj: IDataObject; grfKeyState: Longint;
    pt: TPoint; var dwEffect: Longint): HRESULT; StdCall;
var pidl : PItemIdList;
begin
  //Result := DataObj.QueryGetData(HDropFormatEtc); // Files dropped?
  //if not (Result=S_OK) then exit;
  // Save DataObject
  fDataObj := DataObj;
  // Get IDropTarget
  fShellBrowser.SelectParent;
  pidl := fShellBrowser.ItemIdList;
  fShellBrowser.ShellFolder.GetUIObjectOf(Self.Handle, 1, pidl, IID_IDropTarget, nil, Pointer(fDropTarget));
  Allocator.Free(pidl);
  fShellBrowser.BrowseObject;
  if Assigned(fDropTarget) then
    Result := fDropTarget.DragEnter(fDataObj, grfKeyState, pt, dwEffect)
  else begin
    Result := S_OK;
    dwEffect := DROPEFFECT_NONE;
  end;//else
  fLastAutoScroll := GetTickCount;
end;//DragEnter

function TJamShellList.DragOver(grfKeyState: Longint; pt: TPoint; var dwEffect: Longint): HRESULT;
var NewDropItem : TListItem;
    hr : HResult;
begin
  if ReadOnly then begin
    dwEffect :=  DROPEFFECT_NONE;
    Result := S_OK;
    exit;
  end;//if
  pt := ScreenToClient(pt);
  NewDropItem := GetItemAt(pt.X, pt.Y);
  fDropButton := grfKeyState and (MK_LBUTTON or MK_RBUTTON or MK_MBUTTON);
  if NewDropItem<>fDropItem then begin
    if Assigned(fDropItem) then fDropItem.DropTarget := False;
    fDropTarget2 := nil;
    fDropItem := NewDropItem;
    if Assigned(fDropItem) then begin
      hr := fShellBrowser.ShellFolder.GetUIObjectOf(Self.Handle, 1, TJamShellListItem(fDropItem.Data).RelativePIDL, IID_IDropTarget, nil, Pointer(fDropTarget2));
      if (hr<>NOERROR) or (fDropTarget2.DragEnter(fDataObj, grfKeyState, pt, dwEffect) <> S_OK) then
        fDropItem := nil
      else
        fDropItem.DropTarget := True;
      //OutputDebugString(PChar(IntToStr(dwEffect)));
    end;
    Update;
  end;

  //Auto scroll
  if Windows.GetTickCount > (fLastAutoScroll + AUTOSCROLL_DELAY_MS) then begin
    CheckAutoScroll(Self, pt);
    fLastAutoScroll := GetTickCount;
  end;//if

  if Assigned(fDropTarget2) then
    Result := fDropTarget2.DragOver(grfKeyState, pt, dwEffect)
  else if Assigned(fDropTarget) then begin
    if (fDragButton>0) and (grfKeyState and MK_RBUTTON=0) then begin // Currently Dragging?
      Result := S_OK;
      dwEffect :=  DROPEFFECT_NONE;
    end else
      Result := fDropTarget.DragOver(grfKeyState, pt, dwEffect)
  end else begin
    Result := S_OK;
    dwEffect :=  DROPEFFECT_NONE;
  end;//else

end;//DragOver

function TJamShellList.DragLeave: HRESULT;
begin
  if Assigned(fDropItem) then fDropItem.DropTarget := False;
  fDataObj     := nil;
  fDropTarget  := nil;
  fDropTarget2 := nil;
  fDropItem    := nil;
  fDropButton  := 0;
  Result       := S_OK;
end;//DragLeave

function TJamShellList.Drop(const dataObj: IDataObject; grfKeyState: Longint; pt: TPoint; var dwEffect: Longint): HRESULT;
var op: TJamShellOperations;
    files: TStrings;
begin
  op := [sopDrop];
  if Assigned(fDropTarget2) then // Drop on a certain item
    Result := fDropTarget2.Drop(dataObj, grfKeyState, pt, dwEffect)
  else if Assigned(fDropTarget) then // Drop on background
    Result := fDropTarget.Drop(dataObj, grfKeyState, pt, dwEffect)
  else
    Result := E_UNEXPECTED;

  if Succeeded(Result) then begin
    if (dwEffect<>DROPEFFECT_NONE) then begin
      // Generate OnOperation event
      op := [sopDrop];
      if dwEffect=DROPEFFECT_MOVE then op := op + [sopMove];
      if dwEffect=DROPEFFECT_COPY then op := op + [sopCopy];
      if Assigned(fDropTarget2) then // Drop on a certain item
        Operation(op, GetFilenamesFromDataObject(dataobj), Path+fDropItem.Caption)
      else // Drop on background
        Operation(op, GetFilenamesFromDataObject(dataobj), Path);
    end else if IsNT then begin
      // dwEffect might be DROPEFFECT_NONE undert NT+ although the file(s) have been moved. See: http://support.microsoft.com/support/kb/articles/Q182/2/19.ASP?LN=EN-US&SD=g
      // Workaround for this problem
      files := GetFilenamesFromDataObject(dataobj);
      if Assigned(files) and ((files.Count>0) and not FileExists(files[0])) then begin
        // OK, the file has really benn moved
        dwEffect:=DROPEFFECT_MOVE;
        op := op + [sopMove];
        if Assigned(fDropTarget2) then // Drop on a certain item
          Operation(op, files, Path+fDropItem.Caption)
        else // Drop on background
          Operation(op, files, Path);
      end;//if files.Count>0
    end;//Workarounf
  end;//if Succeeded
  // Clean up
  DragLeave;
end;

// IDropSource methods
function TJamShellList.QueryContinueDrag(fEscapePressed: Bool;  grfKeyState: Longint): HResult;
const BUTTONS = (MK_LBUTTON or MK_MBUTTON or MK_RBUTTON);
begin
  if fEscapePressed or (( (fDragButton xor BUTTONS) and grfKeyState) <> 0) then
    result := DRAGDROP_S_CANCEL
  else if (grfKeyState and fDragButton) = 0 then
    result := DRAGDROP_S_DROP
  else
    result := S_OK;
end;

function TJamShellList.GiveFeedback(dwEffect: Longint): HResult;
begin
  //OutputDebugString(PChar('TJamShellList.GiveFeedBack: '+IntToStr(dwEffect)));
  result := DRAGDROP_S_USEDEFAULTCURSORS;
end;

{$ifndef _VCL_6_UP}
procedure TJamShellList.SelectAll;
var i: Integer;
begin
  Items.BeginUpdate;
  for i:=0 to Items.Count-1 do
    Items[i].Selected := True;
  SetFocus;
  Items.EndUpdate;
end;//SelectAll
{$endif}

{$ifndef _VCL_4_UP}
// IUnknown methods
function TJamShellList.QueryInterface(const IID: TGUID; out Obj): HResult;
const E_NOINTERFACE = $80004002;
begin
  if GetInterface(IID, Obj) then Result := 0 else Result := E_NOINTERFACE;
end;

function TJamShellList._AddRef: Integer;
begin
  Inc(FRefCount);
  Result := FRefCount;
end;

function TJamShellList._Release: Integer;
begin
  Dec(FRefCount);
  if FRefCount = 0 then
  begin
    Destroy;
    Result := 0;
    Exit;
  end;
  Result := FRefCount;
end;
{$endif}

{***************************** T J A M S H E L L T R E E **********************}

function ShellTreeCompareFunc(aNode1, aNode2: TTreeNode; ishf: IShellFolder): Integer; stdcall;
var h: HResult;
begin
  h := ishf.CompareIds( 0, TJamShellTreeItem(aNode1.Data).RelativePIDL, TJamShellTreeItem(aNode2.Data).RelativePIDL);
  if Succeeded(h) then
    result := SmallInt(HResultCode(h))
  else
    result := 0;
end;//ShellTreeCompareFunc

constructor TJamShellTree.Create(AOwner: TComponent);
begin
  Inherited Create(AOwner);
  fInitialized := False;
  fQuickSelect := True; // First Change notification should not be processed delayed
  fAllowExpand := not (csDesigning in ComponentState);
  fShellBrowser := TShellBrowser.Create(Self);
  Images := TJamSystemImageList.Create(Self);
  fShellBrowser.FileSystemOnly := False;
  fChangeTimer := TTimer.Create(Self);
  fChangeTimer.Enabled := False;
  fChangeTimer.OnTimer := TimerChange;
  fChangeTimer.Interval := 100;
  Width := 150;
  Height := 200;
  HideSelection := False;
  fRootedAt := SF_DESKTOP;
  fOleDragDrop := True;
  fContextMenu := True;
  fShowHidden := True;
  fShowNetHood := True;
end;//Create

destructor TJamShellTree.Destroy;
begin
  fShellBrowser.Free;
  Images.Free;
  fChangeTimer.Free;
  inherited Destroy;
end;//Destroy

procedure TJamShellTree.CreateWnd;
var  LogFont : TLOGFONT;
     h       : THandle;
begin
  Inherited;

  if fInitialized then begin
    // Delphi recreates the control after drag & dock operations or after
    // a change of the BorderStyle property. The recreated control will have a
    // different handle and the folowing code needs to be executed.
    if Assigned(FShellLink) then FShellLink.RegisterShellControl(Handle);
    if Items.Count>0 then RefreshNode(Items[0], True);
    OleDragDrop := OleDragDrop;
    exit;
  end;

  // Get icon font
  if SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LogFont), @LogFont, 0) then
  begin
    h := CreateFontIndirect(LogFont);
    Font.Handle := h;
  end;//if

  fShellBrowser.Loaded;
  ShowRoot := False;
  RightClickSelect := True;
  fInitialized := True;

  if csDesigning in ComponentState then begin
    if Items.Count=0 then
      RootedAt := RootedAt; //Populate Tree
  end;//if
end;

procedure TJamShellTree.Loaded;
begin
  Inherited;
  //if OleDragDrop=True then OleDragDrop := True; // Workaround: if BorderStye=bsNone Delphi recreates the control and the new handle isn't registered for Drag&Drop any more
  // distribute selected folders among connected shell controls
  if assigned(fShellLink) and Assigned(Selected) and Assigned(Selected.Data) then
    fShellLink.PathChanged(Self, TJamShellTreeItem(Selected.Data).AbsolutePIDL);
end;//Loaded

procedure TJamShellTree.DestroyWnd;
begin
  if assigned(FShellLink) then
    FShellLink.UnregisterShellControl(Handle);
  Inherited;
end;//DestroyWnd

function TJamShellTree.CanExpand(aNode: TTreeNode): Boolean;
begin
  Result := (Inherited CanExpand(aNode)) and (fAllowExpand or (aNode.Level=0));
  fIsExpanding := True;
  if Result then Expand(aNode);
end;//CanExpand


procedure TJamShellTree.Expand(aNode: TTreeNode);
var old_cursor: TCursor;
begin
  // For some reasons that we do not yet have figured out yet, the VCL sometimes
  // calls Expand 2 times for each expand. fIsExpanding should prevent that
  if aNode.Count>0 then begin //Alredy filled?
    if not fIsExpanding then
      //RefreshNode(aNode, False) // slows down a second expand
    else
      fIsExpanding := False;
  end else begin
    old_cursor := Screen.Cursor;
    Screen.Cursor := crHourglass;
    Items.BeginUpdate;
    fShellBrowser.FolderIdList := TJamShellTreeItem(aNode.Data).AbsolutePIDL;
    // fill branch
    While fShellBrowser.Next do begin
      if not ShowFiles and not fShellBrowser.IsFolder then continue;
      AddItem(aNode);
    end;//while
    aNode.CustomSort(@ShellTreeCompareFunc, Integer(fShellBrowser.ShellFolder));
    aNode.HasChildren := aNode.Count>0;
    Items.EndUpdate;
    Screen.Cursor := old_cursor;
  end;//else
  Inherited;
end;//ExpandNode

procedure TJamShellTree.AddItem(Parent: TTreeNode);
var NewNode: TTreeNode;
    Attributes : Cardinal;
    CanAdd : Boolean;
begin
  if not ShowHidden and fShellBrowser.IsHidden then exit;
  if not ShowNetHood and (fShellBrowser.IsSpecialObject in [SF_NETWORK,SF_NETHOOD]) then exit;

  NewNode := Items.AddChild(Parent, fShellBrowser.GetShellObjectName);
  NewNode.ImageIndex := fShellBrowser.IconNumber;
  NewNode.SelectedIndex := fShellBrowser.SelectedIconNumber;
  if ShowFiles then
    NewNode.HasChildren := fShellBrowser.IsFolder
  else
    NewNode.HasChildren := fShellBrowser.HasSubFolders;
  NewNode.Data := TJamShellTreeItem.Create;
  With TJamShellTreeItem(NewNode.Data) do begin
    RelativePIDL := fShellBrowser.ItemIDList;
    AbsolutePIDL := ConcatItemIdLists(fShellBrowser.FolderIdList, RelativePIDL);
    Tag := 1; // Necessary for RefreshNode
    ParentShellFolder := fShellBrowser.ShellFolder;
  end;

  Attributes := fShellBrowser.GetAttributes(SFGAO_HIDDEN);
  if (Attributes and SFGAO_HIDDEN) <> 0 then NewNode.Cut := True;
  if (Attributes and SFGAO_GHOSTED) <> 0 then NewNode.Cut := True;
  NewNode.OverlayIndex := fShellBrowser.GetOverlayIndex;
  if Assigned(OnAddFolder) then begin // Call the OnAddItem event and see if this node should be added or not
    CanAdd := True;
    OnAddFolder(NewNode, GetFullPath(NewNode), CanAdd);
    if not CanAdd then NewNode.Delete;
  end;//if
end;

procedure TJamShellTree.Delete(ANode: TTreeNode);
var TheData: TJamShellTreeItem;
begin
  TheData := TJamShellTreeItem(aNode.Data);
  {$ifndef _VCL_4_UP} if csDesigning in ComponentState then exit; {$endif}
  // There is a bug in the VCL of Delphi 3: When the BorderStyle property is
  // changed or the window is reparented or docked, the VCL
  // recreates the control and the Delete method is called for each node,
  // although they don't get deleted. Then the shell information in the Data
  // property is lost. If you intend to change the BorderStyle property in
  // Delphi 3 at runtime, you should comment out the following lines
  // BTW, Delphi 6 has a protected property CreateWndRestoreswhich which is True
  // when the control is recreated
  if {$ifdef _VCL_6_UP} not CreateWndRestores and {$endif} Assigned(TheData) then With TheData do begin
    if RelativePIDL<>DesktopIdList then
      Allocator.Free(RelativePIDL);
    if AbsolutePIDL<>DesktopIdList then
      Allocator.Free(AbsolutePIDL);
    ParentShellfolder := nil; // free memory
    TheData.Free;
  end;//with, if
  Inherited;
end;

procedure TJamShellTree.SetJAMShellLink(newValue: TJamShellLink);
begin
  if FShellLink <> newValue then
  begin
    if assigned(FShellLink) then
      FShellLink.UnregisterShellControl(Handle);
    FShellLink := newValue;
    if assigned(FShellLink) then begin
      FShellLink.RegisterShellControl(Handle);
    end;
  end;
end;//SeJAMShellLink

procedure TJamShellTree.Notification(AComponent: TComponent; operation: TOperation);
begin
  inherited Notification(AComponent, operation);
  if operation = opRemove then
  begin
    if AComponent = FShellLink then
      FShellLink := nil;
  end;
end;//Notification

function TJamShellTree.GetFullPath(node: TTreeNode): String;
var tmp: array[0..MAX_PATH] of Char;
begin
  if not Assigned(node) or not Assigned(node.Data) then begin
    Result := '';
    exit;
  end;
  SHGetPathFromIdList(TJamShellTreeItem(node.data).AbsolutePIDL, @tmp[0]);
  Result := tmp;
end;

procedure TJamShellTree.Change(Node: TTreeNode);
begin
  if not fQuickSelect then begin
    fChangeTimer.Enabled := False;
    fChangeTimer.Enabled := True;
  end else begin
    fQuickSelect := False;
    if assigned(fShellLink) and Assigned(Node) and Assigned(Node.Data) and not (csLoading in ComponentState)
    then
      fShellLink.PathChanged(Self, TJamShellTreeItem(Node.Data).AbsolutePIDL);
  end;
  Inherited;
end;//Change

procedure TJamShellTree.TimerChange(Sender: TObject);
begin
  fChangeTimer.Enabled := False;
  if assigned(fShellLink) and Assigned(Selected) and Assigned(Selected.Data) then
    fShellLink.PathChanged(Self, TJamShellTreeItem(Selected.Data).AbsolutePIDL);
end;//TimerChange

function TJamShellTree.InvokeCommandOnSelected(Command: String): Boolean;
var Files: TStrings;
    op: TJamShellOperations;
begin
  Result := False;
  if not Assigned(Selected) then exit;
  // Save file names for OnOperation event
  if (CompareText(command, 'paste')=0) then
    Files := GetFilenamesFromHandle(Clipboard.GetAsHandle(CF_HDROP))
  else begin
    Files := TStringList.Create;
    Files.Add(SelectedFolder);
  end;//else

  if Assigned(Selected.Data) then begin
    fShellBrowser.AbsoluteItemIdList := TJamShellTreeItem(Selected.Data).AbsolutePIDL;
    Result := fShellBrowser.InvokeContextMenuCommand(Command);
  end//if
  else Result := True;
  
  if Result and (CompareText(command, 'delete')=0) then begin
    fQuickSelect := True;
    Selected.Delete;
    Operation([sopDelete,sopRemove], Files, '');
    Files := nil;
  end;//if 'delete'
  if Result and (CompareText(command, 'paste')=0) then begin
    Application.ProcessMessages;
    SmartRefresh;
    op := [sopPaste,sopAdd];
    if ((files.Count>0) and not FileExists(files[0])) then op := op + [sopMove]
    else op := op + [sopCopy];
    Operation(op, Files, SelectedFolder);
    Files := nil;
  end;//if 'paste'
  if Result and (CompareText(command, 'cut')=0) then
    Selected.Cut := True;
  Files.Free;
end;

procedure TJamShellTree.WMRButtonUp(var Message: TWMRButtonUp);
var p: TPoint;
begin
  if not Assigned(Selected) or not ShellContextMenu then exit;
  {$ifdef _DELPHI_4_UP}
  p := Point(Message.XPos,Message.YPos);
  {else}
  p := ClientToScreen(Point(Message.XPos,Message.YPos));
  {$endif}
  ShowContextMenu(p);
end;//WMRButtonUp

procedure TJamShellTree.CreateDir(path: String; foldername: String; editmode: Boolean);
var i: Integer;
    n: TTreeNode;
begin
  if path[Length(path)]<>'\' then path := path + '\';
  if Length(foldername)=0 then foldername := strNewFolder;
  ForceDirectories(path+foldername);
  SelectedFolder := path;
  Selected.Expand(False);
  RefreshNode(Selected, False);
  for i:=0 to Selected.Count-1 do begin
    n := Selected.Item[i];
    if CompareText(n.Text, foldername) = 0 then begin
      n.Selected := True;
      if EditMode then
        n.EditText;
      break;
    end;//if
  end;//for
end;//CreateDir


function TJamShellTree.ShowContextMenu(p: TPoint): String;
var Files: TStrings;
    op: TJamShellOperations;
begin
  if not Assigned(Selected) or not Assigned(Selected.Data) then exit;
  if Assigned(Selected.Parent) and Assigned(Selected.Parent.Data) then begin
    fShellBrowser.FolderIdList := TJamShellTreeItem(Selected.Parent.Data).AbsolutePIDL;
    fShellBrowser.ItemIdList   := TJamShellTreeItem(Selected.Data).RelativePIDL;
  end else begin
    // For topmost object, e.g. desktop
    fShellBrowser.FolderIdList := TJamShellTreeItem(Selected.Data).AbsolutePIDL;
    fShellBrowser.SelectParent;
  end;//else
  if ReadOnly then
    fShellBrowser.OnRename := nil
  else
    fShellBrowser.OnRename := HandleRenameEvent;
  // Save file names for OnOperation event
  Files := GetFilenamesFromHandle(Clipboard.GetAsHandle(CF_HDROP));
  fShellBrowser.ReadOnly := Self.ReadOnly;

  if Assigned(PopupMenu) then PopupMenu.Autopopup := False;
  Result := fShellBrowser.ShowContextMenu(p, PopupMenu);
  if CompareText(Result, 'delete')=0 then begin
    fQuickSelect := True;
    if Assigned(Files) then
      Files.Clear
    else
      Files := TStringList.Create;
    Files.Add(SelectedFolder); // Save for OnOperation Event
    Selected.Delete;
    Operation([sopDelete,sopRemove], Files, '');
    Files := nil;
  end;
  if CompareText(Result, 'cut')=0 then
    Selected.Cut := True
  else if CompareText(Result, 'paste')=0 then begin
    Application.ProcessMessages;
    SmartRefresh;
    op := [sopPaste,sopAdd];
    if Assigned(files) and ((files.Count>0) and not FileExists(files[0])) then
      op := op + [sopMove]
    else
      op := op + [sopCopy];
    Operation(op, Files, SelectedFolder);
    Files := nil;
  end;
  Files.Free;
end;//ShowContextMenu

function  TJamShellTree.GetOnContextMenuSelect: TOnContextMenuSelectEvent;
begin
  Result := fShellBrowser.OnContextMenuSelect;
end;//GetOnContextMenuSelect

procedure TJamShellTree.SetOnContextMenuSelect(anEvent: TOnContextMenuSelectEvent);
begin
  fShellBrowser.OnContextMenuSelect := anEvent;
end;//SetOnContextMenuSelect

procedure TJamShellTree.WMLButtonDown(var Message: TWMRButtonUp);
begin
  fChangeTimer.Interval := 100;
  Inherited;
end;//WMLButtonDown

procedure TJamShellTree.WMInitMenuPopup(var Message: TMessage);
begin
  Inherited;
  fShellBrowser.HandlePopupMessages(Message);
end;

procedure TJamShellTree.WMMeasureItem(var Message: TMessage);
begin
  Inherited;
  fShellBrowser.HandlePopupMessages(Message);
end;

procedure TJamShellTree.WMDrawItem(var Message: TMessage);
begin
  Inherited;
  fShellBrowser.HandlePopupMessages(Message);
end;

procedure TJamShellTree.JAMRefresh(var Message: TJAMPathChanged);
begin
  Refresh;
end;//JAMRefresh;

procedure TJamShellTree.JAMSmartRefresh(var Message: TJAMPathChanged);
begin
  SmartRefresh;
end;//JAMSmartRefresh;

procedure TJamShellTree.JAMGoUp(var Message: TMessage);
begin
  GoUp;
  Message.ResultLo := 1;
end;

procedure TJamShellTree.GoUp;
begin
  fChangeTimer.Interval := 100;
  if Assigned(Selected) then
    if Assigned(Selected.Parent) then
      Selected.Parent.Selected := True;
end;//GoUp

procedure TJamShellTree.SetRootedAt(Root: TJamShellFolder);
var rootnode: TTreeNode;
    old_cursor: TCursor;
begin
  fRootedAt := Root;

  old_cursor := Screen.Cursor;
  try
    Screen.Cursor := crHourGlass;
    Items.BeginUpdate;
    Selected := nil;
    Items.Clear;
    rootnode := Items.Add(nil, '');
    rootnode.Data := TJamShellTreeItem.Create;
    if Root=SF_DESKTOP then begin
      With TJamShellTreeItem(rootnode.Data) do begin
        RelativePIDL := DesktopIdList;
        AbsolutePIDL := DesktopIdList;
      end;//with
      rootnode.ImageIndex := fShellBrowser.GetDesktopIconIndex;
      rootnode.SelectedIndex := fShellBrowser.GetDesktopIconIndex;
      rootnode.Text := fShellBrowser.GetDesktopName;
      rootnode.HasChildren := True;
    end else begin
      if Root=SF_FILESYSTEMFOLDER then
        fShellBrowser.Folder := fRootedAtFileSystemFolder
      else
        fShellBrowser.BrowseSpecialFolder(Root);
      With TJamShellTreeItem(rootnode.Data) do begin
        RelativePIDL := fShellBrowser.FolderIdList;
        AbsolutePIDL := fShellBrowser.FolderIdList;
      end;//with
      fShellBrowser.SelectParent;
      rootnode.ImageIndex := fShellBrowser.IconNumber;
      rootnode.SelectedIndex := fShellBrowser.SelectedIconNumber;
      rootnode.Text := fShellBrowser.GetShellObjectName;
      rootnode.HasChildren := fShellBrowser.HasSubFolders;
    end;//else
    rootnode.Expand(False);

    If Root=SF_DRIVES then begin
      If Assigned(rootnode.Item[1]) then // select second node if possible
        rootnode.Item[1].Selected := True;
    end else
      If (rootnode.Count>0) then // select first node if possible
        rootnode.Item[0].Selected := True;

    if Root<>SF_FILESYSTEMFOLDER then RootedAtFileSystemFolder := '';

  finally
    Items.EndUpdate;
    Screen.Cursor := old_cursor;
  end;//try
end;

procedure TJamShellTree.JAMPathChanged(var Message: TJAMPathChanged);
begin
  if assigned(Message.PIDL) then begin
    if RootedAt = SF_FileSystemFolder then begin
      fShellBrowser.FolderIdList := Message.PIDL;
      try
        SelectedFolder := fShellBrowser.Folder;
      except
      end;
    end else
      GotoFolderIdList(Message.Pidl);
  end;
end;

function TJamShellTree.GotoFolderIdList(const ItemIdList: PItemIdList): Boolean;

  function PidlsEqual2(abs_pidl, rel_pidl : PItemIdList): Boolean;
  var old_cb: Integer;
  begin // This sometimes fails if the tree isn't rooted at the Desktop
    Inc(longint(rel_pidl), rel_pidl^.mkid.cb);
    old_cb := rel_pidl.mkid.cb;
    rel_pidl.mkid.cb := 0;
    Result := Desktop.CompareIds(0, abs_pidl, ItemIdList) = 0;
    rel_pidl.mkid.cb := old_cb;
  end;

  function PidlsEqual3(abs_pidl, rel_pidl, rel_pidl2 : PItemIdList): Boolean;
  var ShellFolder: IShellFolder;
      old_cb: Integer;
      next_pidl: PItemIdList;
  begin
    // Get the correct parent IShellFolder
    if Desktop.CompareIds(0, abs_pidl, DesktopIdList)=0 then
      ShellFolder := Desktop
    else
      if Desktop.BindToObject(abs_pidl, nil, IID_IShellFolder, Pointer(ShellFolder)) <> NOERROR then begin
        Result := False;
        exit;
      end;//if
    // Cut off rel_pidl at next segment
    next_pidl := rel_pidl;
    Inc(longint(next_pidl), next_pidl^.mkid.cb);
    old_cb := next_pidl.mkid.cb;
    next_pidl.mkid.cb := 0;
    // See if the first part of rel_pidl2 matches rel_pidl
    Result := ShellFolder.CompareIds(0, rel_pidl, rel_pidl2) = 0; //Compare
    next_pidl.mkid.cb := old_cb; //Restore old value
    ShellFolder := nil; // Free Memory
  end;

  function PidlsEqual4(Shf: IShellFolder; rel_pidl1, rel_pidl2 : PItemIdList): Boolean;
  var old_cb: Integer;
      next_pidl: PItemIdList;
  begin
    // Cut off rel_pidl at next segment
    next_pidl := rel_pidl1;
    Inc(longint(next_pidl), next_pidl^.mkid.cb);
    old_cb := next_pidl.mkid.cb;
    next_pidl.mkid.cb := 0;
    Result := Shf.CompareIds(0, rel_pidl1, rel_pidl2) = 0;
    next_pidl.mkid.cb := old_cb; //Restore old value
  end;//PidlsEqual4


var node      : TTreeNode;
    //in_pidl   : PItemIdList;
    i         : Integer;
    oldvalue  : Boolean;
    old_cursor: TCursor;
    Match     : Boolean;
    part_pidl : PItemIdList;
    pidl_size : Integer;
begin
  Result := False;
  if not Assigned(ItemIdList) then exit;
  old_cursor := Screen.Cursor;
  Screen.Cursor := crHourGlass;
  Items.BeginUpdate;
  oldvalue := fAllowExpand; // Save old value
  fAllowExpand := True;     // Allow Expanding also in designing mode
  node := Items[0];         // Select root folder
  Match := True;
  part_pidl := GetItemIdListPart(ItemIdList, node.Level);
  pidl_size := GetItemIdListCount(ItemIdList);
  //in_pidl := ItemIdList;

  while node.Level<pidl_size{in_pidl^.mkid.cb <> 0} do begin
    node.HasChildren := True;
    node.Expand(False);
    Match := False;
    for i:=0 to node.Count-1 do begin
      // Sometimes PidlsEqual fails, sometimes PidlsEqual4 fails, so we use a
      // combination of both. This seems to work fine in most cases
      //if PidlsEqual(TJamShellTreeItem(node[i].data).RelativePIDL, in_pidl)
      //or PidlsEqual4(TJamShellTreeItem(node[i].data).ShellFolder, in_pidl, TJamShellTreeItem(node[i].data).RelativePIDL) then begin
      if TJamShellTreeItem(node[i].data).ParentShellFolder.CompareIds(0, part_pidl, TJamShellTreeItem(node[i].data).RelativePIDL)=0 then begin
        Allocator.Free(part_pidl);
        node := node[i];
        part_pidl := GetItemIdListPart(ItemIdList, node.Level);
        //Inc(longint(in_pidl), in_pidl^.mkid.cb);
        Match := True;
        break;
      end;
    end;//for
    if not Match then break;
  end;//while
  Allocator.Free(part_pidl);
  fAllowExpand := oldvalue;  // restore old value
  fQuickSelect := True;
  node.Selected := True;
  node.MakeVisible;
  Items.EndUpdate;
  Screen.Cursor := old_cursor;
  Result := Match;
end;//GotoFolderIdList

function TJamShellTree.GetSelectedFolder: String;
begin
  Result := '';
  if not Assigned(Selected) or not Assigned(Selected.Data) then exit;
  FShellBrowser.FolderIdList := TJamShellTreeItem(Selected.data).AbsolutePIDL;
  Result := fShellBrowser.Folder;
end;//GetSelectedFolder

procedure TJamShellTree.SetSelectedFolder(aPath: String);
var tmp        : array[0..MAX_PATH] of WideChar;
    ulEaten,
    ulAttribs  : ULONG;
    hr         : HResult;
    pidl       : PItemIdList;
begin
  // Select the correct root folder
  if RootedAt=SF_FILESYSTEMFOLDER then begin
    FShellBrowser.Folder := RootedAtFileSystemFolder;
    if CompareText(FShellBrowser.Folder, Copy(aPath, 1, Length(FShellBrowser.Folder))) = 0 then
      aPath := Copy(aPath, Length(FShellBrowser.Folder)+1, MAX_PATH);
  end else
    FShellBrowser.BrowseSpecialFolder(RootedAt);
  if Length(aPath)=0 then begin
    if RootedAt=SF_DESKTOP then begin
      SpecialFolder := SF_DRIVES;
    end else
      Items[0].Selected := True;
    exit;
  end else begin
    StringToWideChar(apath, tmp, High(tmp));
    hr := FShellBrowser.ShellFolder.ParseDisplayName(Handle, nil, @tmp, ulEaten, pidl, ulAttribs);
  end;//else

  if (not Succeeded(hr) or not GotoFolderIdList(pidl)) and not (csLoading in ComponentState) then
    //raise EShellBrowserError.Create('Cannot Find Folder: ' + aPath) // throwing exceptions here resuls in an Access Violation, we were not yet able to find out why
    MessageDlg('Unable to find path: '+ aPath, mtError, [mbOK], 0)
  else
    if assigned(fShellLink) and Assigned(Selected) then
      fShellLink.PathChanged(Self, TJamShellTreeItem(Selected.Data).AbsolutePIDL);
  if Assigned(pidl) then Allocator.Free(pidl);
end;//SetSelectedFolder

procedure TJamShellTree.Edit(const Item: TTVItem);
  function GetItem(Value: TTVItem): TTreeNode;
  begin
    with Value do
      if (mask and TVIF_PARAM) <> 0 then Result := TTreeNode(lParam)
      else Result := Items.GetNode(hItem);
  end;
var
  S: string;
  EditItem: TTreeNode;
  Files: TStrings;
  WasExpanded : Boolean;
begin
  Inherited;
  with Item do
  begin
    if not Assigned(Item.pszText) then exit;
    S := pszText;
    EditItem := GetItem(Item);
    if Assigned(EditItem) and Assigned(EditItem.Data) then begin
      Files := TStringList.Create;
      Files.Add(GetFullPath(EditItem));
      fShellBrowser.FolderIdList := TJamShellTreeItem(EditItem.data).AbsolutePIDL;
      fShellBrowser.SelectParent;
      fShellBrowser.RenameObject(S);
      EditItem.Text := fShellBrowser.GetShellObjectName;
      Operation([sopRename], Files, S);
      With TJamShellTreeItem(EditItem.Data) do begin
        // Update ItemIdList of the renamed folder
        Allocator.Free(RelativePIDL);
        Allocator.Free(AbsolutePIDL);
        RelativePIDL := fShellBrowser.ItemIDList;
        AbsolutePIDL := ConcatItemIdLists(fShellBrowser.FolderIdList, RelativePIDL);
        // The itemIdLists of the subfolders are invalid too, we need to refresh them
        WasExpanded := EditItem.Expanded;
        EditItem.DeleteChildren;
        RefreshNode(EditItem, True);
        EditItem.Expanded := WasExpanded;
        // update linkeded components if present
        if assigned(fShellLink) and Assigned(AbsolutePIDL) then
          fShellLink.PathChanged(Self, AbsolutePIDL);
      end;//with
    end//if
  end;//with
end;//Edit

function TJamShellTree.CanEdit(Node: TTreeNode): Boolean;
begin
  Result := Inherited CanEdit(Node);
  if not Result or not Assigned(Node.Data) then exit;
  fShellBrowser.FolderIdList := TJamShellTreeItem(Node.data).AbsolutePIDL;
  fShellBrowser.SelectParent;
  Result := fShellBrowser.CanRename;
end;

procedure TJamShellTree.Operation(op: TJamShellOperations; Folders: TStrings; Destination: String);
begin
  if Assigned(OnOperation) and Assigned(Folders) and (Folders.Count>0) then
    OnOperation(Self, op, Folders, Destination);
  Folders.Free;
end;//Operation

procedure TJamShellTree.KeyDown( var key: Word;  aShiftState: TShiftState );
var Files: TStrings;
begin
  if not IsEditing then
    case key of
      vk_F2:     if Assigned(Selected) then Selected.EditText;
      vk_F5:     begin Refresh; if Assigned(fShellLink) then fShellLink.Refresh(Self) end;
      vk_F10:    if (ssShift in aShiftState) and ShellContextMenu and Assigned(Selected) then
                   ShowContextMenu(ClientToScreen(Selected.DisplayRect(True).BottomRight));
      vk_Delete: if not ReadOnly then InvokeCommandOnSelected('delete');
      Word('C'): if (ssCtrl in aShiftState) then begin
                   InvokeCommandOnSelected('copy');
                   key := 0;
                 end;
      Word('X'): if not ReadOnly and (ssCtrl in aShiftState) then begin
                   InvokeCommandOnSelected('cut');
                   //key := 0;
                 end;
      Word('V'): if not ReadOnly and (ssCtrl in aShiftState) then begin
                   Files := GetFilenamesFromHandle(Clipboard.GetAsHandle(CF_HDROP));
                   InvokeCommandOnSelected('paste');
                   Operation([sopPaste,sopAdd], Files, GetFullPath(Selected));
                   key := 0;
                 end;
      Word('A'): if (ssCtrl in aShiftState) then begin
                   if Assigned(fShellLink) then fShellLink.SelectAll(Self);
                   key := 0;
                 end;
    end;// case

  fChangeTimer.Interval := 800;
  Inherited;
end;//KeyDown

procedure TJamShellTree.KeyPress( var key: Char );
begin
  fChangeTimer.Interval := 800;
  inherited;
end;//KeyPress

procedure TJamShellTree.Refresh;
var OldCursor: TCursor;
begin
  OldCursor := Screen.Cursor;
  Screen.Cursor := crHourGlass;
  Application.ProcessMessages; // First finish all operations
  Items.BeginUpdate;
  RefreshNode(Items[0], True);
  Items.EndUpdate;
  Screen.Cursor := OldCursor;
end;//Refresh

procedure TJamShellTree.SmartRefresh;
var node: TTreeNode;
    i   : Integer;
begin
  if not Assigned(Selected) or (not Selected.Expanded and (Selected.Count=0)) then exit;
  Application.ProcessMessages; // First finish all operations
  Items.BeginUpdate;
  node := Selected;
  if Assigned(node) and (Length(node.Text)<=0) and Assigned(node.Parent) then
    node := node.Parent;
  RefreshNode(node, True);

  i:=0; // Search for Nodes marked as 'Cut' and check if they are still there
  while i<Items.Count do begin
    if Items[i].Cut then
      RefreshNode(Items[i].Parent, True);
    Inc(i);
  end;
  Items.EndUpdate;
end;//SmartRefresh

procedure TJamShellTree.RefreshNode(Node: TTreeNode; Recursive: Boolean);

  function IndexOf(Text: String): Integer; // very slow!!
  var n: TTreeNode;
  begin
    Result := -1;
    n := Node.GetFirstChild;
    while Assigned(n) do begin
      if Text=n.Text then begin
        Result := n.Index;
        exit;
      end;//if
      n := n.GetNextChild(n);
    end;//while
  end;//IndexOf

var i      : Integer;
    index  : Integer;
    changes: Boolean;
begin
  Changes := False;
  if not Assigned(Node) then exit;
  for i:=0 to Node.Count-1 do // Set all Tags to "not present"
    TJamShellTreeItem(Node.Item[i].Data).Tag := 0;

  fShellBrowser.FolderIdList :=  TJamShellTreeItem(Node.Data).AbsolutePIDL;
  While fShellBrowser.Next do begin // Enumerate folder again
    if not ShowFiles and not fShellBrowser.IsFolder then continue;
    index := IndexOf(fShellBrowser.GetShellObjectName);
    if index>=0 then begin// Set tag to "is present"
      TJamShellTreeItem(Node.Item[index].Data).Tag := 1;
      Node.Item[Index].HasChildren := fShellBrowser.HasSubFolders;
    end else begin
      AddItem(Node);
      Changes := True;
    end;
  end;//while

  i:=0;
  while i<Node.Count do begin
    if TJamShellTreeItem(Node.Item[i].Data).Tag = 0 then begin
      Node.Item[i].Delete;
    end else begin
      if Recursive and Node.Item[i].Expanded then
        RefreshNode(Node.Item[i], Recursive)
      else
        {Node.Item[i].DeleteChildren};
      Inc(i);
    end;//else
  end;//while

  if Changes then begin
    Node.CustomSort(@ShellTreeCompareFunc, Integer(fShellBrowser.ShellFolder));
  end;
end;

procedure TJamShellTree.HandleRenameEvent;
begin
  if Assigned(Selected) then Selected.EditText;
end;//HandleRenameEvent

function TJamShellTree.ShowNetConnectionDialog: Boolean;
begin
  Result := fShellBrowser.ShowNetConnectionDialog;
end;//ShowNetConnectionDialog

function TJamShellTree.GetSpecialFolder: TJamShellfolder;
begin
  Result := SF_UNKNOWN;
  if not Assigned(Selected) then exit;
  fShellBrowser.FolderIdList := TJamShellTreeItem(Selected.Data).AbsolutePIDL;
  Result := fShellBrowser.IsSpecialFolder;
  if (Result=SF_DRIVES) and (Length(SelectedFolder)>0) then Result := SF_FILESYSTEMFOLDER;
end;//GetSpecialFolder

procedure TJamShellTree.SetSpecialFolder(folder: TJamShellFolder);
var pidl: PItemIdList;
begin
  if folder=SF_FILESYSTEMFOLDER then begin
    //SelectedFolder := 'C:\';
    exit;
  end;
  fShellBrowser.BrowseSpecialFolder(folder);
  pidl := fShellBrowser.FolderIdList;
  GotoFolderIdList(pidl);
  Allocator.Free(pidl);
end;//SetSpecialFolder

procedure TJamShellTree.SetRootedAtFileSystemFolder(aPath: String);
begin
  fRootedAtFileSystemFolder := aPath;
  if not DirectoryExists(aPath) then exit;
  RootedAt := SF_FILESYSTEMFOLDER;
end;//SetRootedAtFileSystemFolder

procedure TJamShellTree.CNNotify(var Message: TWMNotify);

  function GetNodeFromItem(const Item: TTVItem): TTreeNode;
  begin
    with Item do
      if (state and TVIF_PARAM) <> 0 then Result := Pointer(lParam)
      else Result := Items.GetNode(hItem);
  end;

begin
  case Message.NMHdr.code of
  TVN_BEGINDRAG, TVN_BEGINRDRAG:
    if OleDragDrop then begin
      with PNMTreeView(Pointer(Message.NMHdr))^ do
         fDragNode := GetNodeFromItem(ItemNew);
      if Assigned(fDragNode) and Assigned(fDragNode.Parent) then
        if Message.NMHdr.code = TVN_BEGINDRAG then
          BeginOleDrag(mbLeft)
        else
          BeginOleDrag(mbRight);
        fDragNode := nil;
    end else
      inherited;
{$ifdef _DELPHI_3}
  TVN_DELETEITEM:
    begin
      with PNMTreeView(Pointer(Message.NMHdr))^ do
        Delete(GetNodeFromItem(itemOld));
      Inherited;
    end;
{$endif}
  else
    inherited;
  end;//case
end;//CNNotify

function TJamShellTree.GetVersion: String;
begin
  Result := ClassName + JAM_COMPONENT_VERSION;
end;//GetVersion

procedure TJamShellTree.SetVersion(s: String);
begin
  // empty
end;//SetVersion

procedure TJamShellTree.SetShowHidden(aValue: Boolean);
var old_path: String;
begin
  if aValue=fShowHidden then exit;
  fShowHidden := aValue;
  old_path := SelectedFolder;
  RootedAt := RootedAt;
  SelectedFolder := old_path;
end;//SetShowHidden

procedure TJamShellTree.SetShowNetHood(aValue: Boolean);
var old_path: String;
begin
  if aValue=fShowNetHood then exit;
  fShowNetHood := aValue;
  old_path := SelectedFolder;
  RootedAt := RootedAt;
  SelectedFolder := old_path;
end;//SetShowNetHood

procedure TJamShellTree.SetFileSystemOnly(aValue: Boolean);
begin
  fShellBrowser.FileSystemOnly := aValue;
  Refresh;
end;//SetFileSystemOnly

function TJamShellTree.GetFileSystemOnly: Boolean;
begin
  Result := fShellBrowser.FileSystemOnly;
end;//GetFileSystemOnly

procedure TJamShellTree.SetShowFiles(aValue: Boolean);
begin
  if fShowFiles=aValue then exit;
  fShowFiles := aValue;
  Refresh;
end;//SetShowFiles

procedure TJamShellTree.SetFilter(Pattern: String);
begin
  fShellBrowser.Filter := Pattern;
  Refresh;
end;//SetFilter

function  TJamShellTree.GetFilter: String;
begin
  Result := fShellBrowser.Filter;
end;//GetFilter

procedure TJamShellTree.SetOleDragDrop(val: Boolean);
begin
  fOleDragDrop := val;
  if csDesigning in ComponentState then exit;
  if fOleDragDrop then begin
    if not (RegisterDragDrop(Self.Handle, Self) = S_OK) then
      fOleDragDrop := False;
  end else begin
    RevokeDragDrop(Self.Handle);
  end;//else
  if fOleDragDrop then DragMode := dmAutomatic
  else DragMode := dmManual;
end;//SetOleDragDrop

procedure TJamShellTree.BeginOleDrag(aButton: TMouseButton);
var pidl    : PItemIdList;
    attr    : Cardinal;
    fDropSource: IDropSource;
    fDataObject: IDataObject;
    hr: HResult;
    effect: Integer;
    ToRefreshNode: TTreeNode;
    op: TJamShellOperations;
begin
  fShellBrowser.AbsoluteItemIdList := TJamShellTreeItem(fDragNode.Data).AbsolutePIDL;
  attr := fShellBrowser.GetAttributes(DRAGFLAGS) and DRAGFLAGS;
  effect := attr ;
  // Store initially pressed mouse button
  case aButton of
    mbLeft  : fDragButton := MK_LBUTTON;
    mbRight : fDragButton := MK_RBUTTON;
    mbMiddle: fDragButton := MK_MBUTTON;
  end;
  pidl := TJamShellTreeItem(fDragNode.Data).RelativePIDL;

  if Assigned(fDragNode.Parent) then
    ToRefreshNode := fDragNode.Parent
  else
    ToRefreshNode := fDragNode;

  try // Get IDataObject
    hr := fShellBrowser.ShellFolder.GetUIObjectOf(Self.Handle, 1, pidl, IID_IDataObject, nil, Pointer(fDataObject));
    if (hr<>NOERROR) then exit;//ShowMessage('Could not get IDataObject');
    DoDragDrop(fDataObject, Self, effect, effect);
  finally
    fDropSource := nil;
    fDragButton := 0;
    Application.ProcessMessages;
    RefreshNode(ToRefreshNode, True); //Refresh;
    if effect<>DROPEFFECT_NONE then begin
      op := [sopDrag];
      if effect=DROPEFFECT_COPY then op := op + [sopCopy];
      if effect=DROPEFFECT_MOVE then op := op + [sopMove,sopRemove];
      Operation(op, GetFilenamesFromDataObject(fDataObject), '');
    end;
  end;
end;

// IDropTarget methods
function TJamShellTree.DragEnter(const DataObj: IDataObject; grfKeyState: Longint;
    pt: TPoint; var dwEffect: Longint): HRESULT; StdCall;
begin
  Result := S_OK;
  //Result := DataObj.QueryGetData(HDropFormatEtc); // Files dropped?
  //if not (Result=S_OK) then exit;
  dwEffect := DROPEFFECT_NONE;//DRAGFLAGS;//GetDefaultDropEffect(grfKeyState);
  // Save DataObject
  fDataObj := DataObj;
  fOldDragEffect := dwEffect;
  fLastAutoScroll := GetTickCount;
end;//DragEnter

function TJamShellTree.DragOver(grfKeyState: Longint; pt: TPoint; var dwEffect: Longint): HRESULT;
var NewDropItem : TTreeNode;
    hr: HResult;
    pidl: PItemIdList;
begin
  if ReadOnly then begin
    dwEffect :=  DROPEFFECT_NONE;
    Result := S_OK;
    exit;
  end;//if
  pt := ScreenToClient(pt);
  NewDropItem := GetNodeAt(pt.X, pt.Y);
  fDropButton := grfKeyState and (MK_LBUTTON or MK_RBUTTON or MK_MBUTTON);
  if NewDropItem<>fDropItem then begin
    Items.BeginUpdate;
    if Assigned(fDropItem) then fDropItem.DropTarget := False;
    if Assigned(fDropTarget2) then fDropTarget2.DragLeave;
    fDropTarget2 := nil;
    fDropItem := NewDropItem;
    if Assigned(fDropItem) then begin
      fShellBrowser.AbsoluteItemIdList := TJamShellTreeItem(fDropItem.Data).AbsolutePIDL;
      pidl := fShellBrowser.ItemIdList;
      hr := fShellBrowser.ShellFolder.GetUIObjectOf(Self.Handle, 1, pidl, IID_IDropTarget, nil, Pointer(fDropTarget2));
      //dwEffect := DRAGFLAGS;//GetDefaultDropEffect(grfKeyState);
      if not Succeeded(hr) or (fDropTarget2.DragEnter(fDataObj, grfKeyState, pt, dwEffect) <> S_OK)
      then
        dwEffect := DROPEFFECT_NONE;
      fDropItem.DropTarget := True;
      Allocator.Free(pidl);
      fAutoExpand := GetTickCount;// for AutoExpand
    end;
    Items.EndUpdate;
  end;

  //Auto Scroll
  if Windows.GetTickCount > (fLastAutoScroll + AUTOSCROLL_DELAY_MS) then begin
    CheckAutoScroll(Self, pt);
    fLastAutoScroll := GetTickCount;
  end;//if
  // AutoExpand
  if GetTickCount > (fAutoExpand + AUTOEXPAND_DELAY_MS) then
    if Assigned(fDropItem) then
      fDropItem.Expand(False);

  if Assigned(fDropTarget2) then
    Result := fDropTarget2.DragOver(grfKeyState, pt, dwEffect)
  else
    Result := E_FAIL;

  // The following lines cover a bug: The cursor doesn't change although the
  // returned dwEffect does. Returning E_FAIL one time will cause an update
  // of the cursor;
  if fOldDragEffect<>dwEffect then begin
    fOldDragEffect := dwEffect;
    Result := E_FAIL;
  end;
end;//DragOver

function TJamShellTree.DragLeave: HRESULT;
begin
  if Assigned(fDropItem) then fDropItem.DropTarget := False;
  fDataObj := nil;
  if Assigned(fDropTarget2) then fDropTarget2.DragLeave;
  fDropTarget2 := nil;
  fDropItem := nil;
  fDropButton := 0;
  Result := S_OK;
end;//DragLeave

function TJamShellTree.Drop(const dataObj: IDataObject; grfKeyState: Longint;
  pt: TPoint; var dwEffect: Longint): HRESULT;
var op: TJamshellOperations;
    files: TStrings;
begin
  op := [sopDrop];
  if Assigned(fDropTarget2) then
    Result := fDropTarget2.Drop(dataObj, grfKeyState, pt, dwEffect)
  else
    Result := E_UNEXPECTED;
  Application.ProcessMessages;
  if Succeeded(Result) then begin
    if (dwEffect<>DROPEFFECT_NONE) then begin
      // Generate OnOperation event
      op := [sopDrop];
      if dwEffect=DROPEFFECT_MOVE then op := op + [sopMove];
      if dwEffect=DROPEFFECT_COPY then op := op + [sopCopy];
      Operation(op, GetFilenamesFromDataObject(dataObj), GetFullPath(fDropItem));
    end else if IsNT then begin
      // dwEffect might be DROPEFFECT_NONE undert NT+ although the file(s) have been moved. See: http://support.microsoft.com/support/kb/articles/Q182/2/19.ASP?LN=EN-US&SD=g
      // Workaround for this problem
      files := GetFilenamesFromDataObject(dataobj);
      if Assigned(files) and ((files.Count>0) and not FileExists(files[0])) then begin
        // OK, the file has really benn moved
        dwEffect:=DROPEFFECT_MOVE;
        op := op + [sopMove];
        Operation(op, GetFilenamesFromDataObject(dataObj), GetFullPath(fDropItem));
      end;//if files.Count>0
    end;//Workarounf
  end;//if Succeeded
  if Assigned(fDropItem) and (fDropItem.Count>0) then RefreshNode(fDropItem, True); //Refresh;
  DragLeave;
end;

// IDropSource methods
function TJamShellTree.QueryContinueDrag(fEscapePressed: Bool;  grfKeyState: Longint): HResult;
const BUTTONS = (MK_LBUTTON or MK_MBUTTON or MK_RBUTTON);
begin
  if fEscapePressed or (( (fDragButton xor BUTTONS) and grfKeyState) <> 0) then
    result := DRAGDROP_S_CANCEL
  else if (grfKeyState and fDragButton) = 0 then
    result := DRAGDROP_S_DROP
  else
    result := S_OK;
end;

function TJamShellTree.GiveFeedback(dwEffect: Longint): HResult;
begin
  //OutputDebugString(PChar('TJamShellTree.GiveFeedBack: '+IntToStr(dwEffect)));
  result := DRAGDROP_S_USEDEFAULTCURSORS;
end;

{$ifndef _VCL_4_UP}
// IUnknown methods
function TJamShellTree.QueryInterface(const IID: TGUID; out Obj): HResult;
const
  E_NOINTERFACE = $80004002;
begin
  if GetInterface(IID, Obj) then Result := 0 else Result := E_NOINTERFACE;
end;

function TJamShellTree._AddRef: Integer;
begin
  Inc(FRefCount);
  Result := FRefCount;
end;

function TJamShellTree._Release: Integer;
begin
  Dec(FRefCount);
  if FRefCount = 0 then
  begin
    Destroy;
    Result := 0;
    Exit;
  end;
  Result := FRefCount;
end;
{$endif}

procedure Register;
begin
  RegisterComponents('JAM Software', [TJamShellCombo,TJamShellList,TJamShellTree]);
end;

initialization

_Reverse := 1;

end.
