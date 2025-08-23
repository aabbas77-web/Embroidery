unit JAMControls;

interface

uses
  Windows, Messages, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ShellBrowser, ComCtrls, ShellApi, ShlObj;

{$I VER.INC}
{$IFDEF _CPPB_3_UP}
  {$ObjExportAll On}
{$ENDIF}

type
  TOwnerDrawState = StdCtrls.TOwnerDrawState;

  TJamComboItem = class (TObject)
    Caption    : String;
    DisplayName: String;
    Indent     : Integer;
    IconNumber : Integer;
    IsDrive    : Boolean;
  end;

  TJamFolderCombo = class(TCustomComboBox)
  private
    FShellBrowser : TShellBrowser;
    FImageList    : TJamSystemImageList;
    mIndentPixels : Integer;
    FIncludeDrives: Boolean;
    procedure CNDrawItem(var Message: TWMDrawItem); message CN_DRAWITEM;
    procedure WMRButtonDown(var Message: TWMRButtonDown); message WM_RBUTTONDOWN;
    procedure WMDeleteItem( var amsg: TWMDeleteItem ); message WM_DELETEITEM;
  protected
    procedure DrawItem(aIndex: Integer; aRect: TRect; aState: TOwnerDrawState); override;
    procedure Loaded; override;
    procedure DestroyWnd; override;
    function  GetIncludeDrives: Boolean;
    procedure SetIncludeDrives(aIncludeDrives: Boolean);
    function  GetVersion: String;
    procedure SetVersion(s: String);

  public
    // Constructor of the JamShellCombo
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function  InsertItem(aIndex: Integer; aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer): Integer;
    function  AddComboItem(aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer): Integer;
    function  AddFolder(Path: String; Indent: Integer): Integer;
    function  SelectFolder(aFolder: String): Boolean;

  published
    property IncludeDrives: Boolean read GetIncludeDrives write SetIncludeDrives ;
    property Version: String read GetVersion write SetVersion stored false;
    property Text;
    property Align;
    property Color;
    property Ctl3D;
    property DragMode;
    property DragCursor;
    property DropDownCount;
    property Enabled;
    property Font;
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
    property Sorted;
    property TabOrder;
    property TabStop;
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
  end;

procedure Register;


implementation

uses SysUtils
{$ifdef _VCL_4_UP}
,ImgList
{$endif}
;

function GetOwnerDrawState(itemState: UINT): TOwnerDrawState;
begin
{$ifdef _DELPHI_5_UP}
  Result := TOwnerDrawState(LongRec(itemState).Lo);
{$else}
  Result := TOwnerDrawState(WordRec(LongRec(itemState).Lo).Lo);
{$endif}
end;

constructor TJamFolderCombo.Create(AOwner: TComponent);
begin
  Inherited Create(AOwner);
  FShellBrowser := TShellBrowser.Create(Self);
  FImageList    := TJamSystemImageList.Create(Self);
  mIndentPixels := 5;
  //ControlStyle := ControlStyle + [csAcceptsControls];
  Style := csOwnerDrawFixed;
end;//Create

destructor TJamFolderCombo.Destroy;
begin
  FShellBrowser.Free;
  FImageList.Free;
  Inherited Destroy;
end;//Destroy

procedure TJamFolderCombo.DestroyWnd;
begin
  Inherited;
end;//DestroyWnd

procedure TJamFolderCombo.Loaded;
begin
  Inherited;
  ItemIndex := Items.IndexOf('C:\');
  if ItemIndex<0 then ItemIndex := 1;
  If Assigned(OnChange) then OnChange(Self);
end;//CreateWnd

function TJamFolderCombo.InsertItem(aIndex: Integer; aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer): Integer;
var item: TJamComboItem;
begin
  //if Length(aCaption)<=0 then exit;
  item            := TJamComboItem.Create;
  item.Caption    := aCaption;
  item.DisplayName:= aDisplayName;
  item.IconNumber := aIconNumber;
  item.Indent     := AIndent;
  item.IsDrive    := (Length(aCaption)>0) and (Length(aCaption)<=3) and (aCaption[2]=':');
  if aIndex>Items.Count then aIndex:=Items.Count; // Workaround for Delphi 3 problem under Windows 98
  Result := aIndex;
  if (aIndex>0) then
    Items.InsertObject(aIndex, aCaption, item)
  else
    Result := Items.AddObject(aCaption, item);
End;//InsertItem

function TJamFolderCombo.AddComboItem(aCaption: String; aDisplayName: String; aIconNumber: Integer; aIndent: Integer): Integer;
begin
  Result := InsertItem(-1, aCaption, aDisplayName, aIconNumber, aIndent);
End;//AddItem

function TJamFolderCombo.AddFolder(Path: String; Indent: Integer): Integer;
var SHFileInfo: TSHFileInfo;
begin
  Result := -1;
  if Items.IndexOf(Path)>=0 then exit;
  SHGetFileInfo(PChar(Path), 0, SHFileInfo, sizeof(SHFileInfo), SHGFI_DISPLAYNAME or SHGFI_SMALLICON or SHGFI_SYSICONINDEX);
  Result := AddComboItem(Path, SHFileInfo.szDisplayName, SHFileInfo.iIcon, Indent);
end;//AddFolder;

procedure TJamFolderCombo.CNDrawItem(var Message: TWMDrawItem);
var
   odsState: TOwnerDrawState;
begin
   with Message.DrawItemStruct^ do
    begin
       odsState := GetOwnerDrawState(itemState);
       Canvas.Handle := hDC;
       Canvas.Font := Font;
       Canvas.Brush := Brush;
       if (Integer(itemID) >= 0) and (odSelected in odsState) then
        begin
      	    Canvas.Brush.Color := clHighlight;
      	    Canvas.Font.Color := clHighlightText
        end;
       if Integer(itemID) >= 0 then
      	    DrawItem(itemID, rcItem, odsState)
       else
    	    Canvas.FillRect(TRect(rcItem));
       Canvas.Handle := 0;
    end;
end;//CNDrawItem

procedure TJamFolderCombo.DrawItem(aIndex: Integer; aRect: TRect; aState: TOwnerDrawState);
var x, y   : Integer;
    item   : TJamComboItem;
    SHFileInfo: TSHFileInfo;
    caption: String;
begin
  {if WindowFromDC(Canvas.Handle) = Handle then indent := 0 else indent := i.Indent;
   Should check odComboBoxEdit (aka. ODS_COMBOBOXEDIT) in aState, but StdCtrls doesn't declare it :(
    This WindowFromDC trick works Ok though. :) }
  item := Items.Objects[aIndex] as TJamComboItem;
  if not Assigned(item) then begin
    caption := Items[aIndex];
    Items.Delete(aIndex);
    SHGetFileInfo(PChar(caption), 0, SHFileInfo, sizeof(SHFileInfo), SHGFI_DISPLAYNAME or SHGFI_SMALLICON or SHGFI_SYSICONINDEX);
    InsertItem(aIndex, caption, SHFileInfo.szDisplayName, SHFileInfo.iIcon, 0);
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
      FImageList.DrawingStyle := dsNormal;

    y := (aRect.Top + aRect.Bottom - FImageList.Height) div 2;
    FImageList.Draw( Canvas, aRect.Left + item.Indent*mIndentPixels + 2, y, item.IconNumber )
  end;//if

  if (odSelected in aState) then
    Canvas.Brush.Color := clHighlight;

  if (item.Caption <> '') then
  begin
    If Assigned(FImageList) then x := FImageList.Width+6 else x := 6;
    y := ((aRect.Bottom - aRect.Top) - Canvas.TextHeight(Item.Caption)) div 2;
    if item.IsDrive then
      Canvas.Textout(aRect.Left+x, aRect.Top+y, item.DisplayName)
    else
      Canvas.Textout(aRect.Left+x, aRect.Top+y, item.Caption);
  end;//if
end;//DrawItem

function TJamFolderCombo.GetIncludeDrives: Boolean;
begin
  Result := FIncludeDrives;
end;//GezIncludeDrives

procedure TJamFolderCombo.SetIncludeDrives(aIncludeDrives: Boolean);
var i, Index: Integer;
begin
  FIncludeDrives := aIncludeDrives;
  if (csDesigning in ComponentState) then exit;

  FShellBrowser.FileSystemOnly := True;
  FShellBrowser.BrowseSpecialFolder(SF_DRIVES);
  if csLoading in ComponentState then i := 0 else i := Items.Count;
  while FShellBrowser.Next do begin
    Index := Items.IndexOf(FShellBrowser.ObjectName);
    if (Index<0) and (Length(FShellBrowser.ObjectName)>0) then begin
      InsertItem(i, FShellBrowser.ObjectName, FShellBrowser.GetShellObjectName, FShellBrowser.IconNumber, 0);
      Inc(i);
    end else
      if not FIncludeDrives then begin
        (Items.Objects[Index] as TJAmComboItem).Free;
        Items.Delete(Items.IndexOf(FShellBrowser.ObjectName));
      end;//if
  end;//while
{  ItemIndex := Items.IndexOf('C:\');
  if ItemIndex<0 then ItemIndex := 1;}
end;//SetInludeDrives

procedure TJamFolderCombo.WMRButtonDown(var Message: TWMRButtonDown);
begin
  Inherited;
  if Assigned(PopupMenu) then exit;
  try
    FShellBrowser.Folder := Text;
    FShellBrowser.SelectParent;
    FShellBrowser.ShowContextMenu(ClientToScreen(Point(Message.XPos,Message.YPos)), nil);
  finally
    Screen.Cursor := crDefault;
  end;
end;//WMRButtonDown

procedure TJamFolderCombo.WMDeleteItem( var aMsg: TWMDeleteItem );
begin
  if aMsg.deleteItemStruct.itemData<>0 then begin
    //TJamComboItem(aMsg.deleteItemStruct.itemData).Free;  //Sometimes crashes with items not generated by itself. Where do they come from?
    aMsg.deleteItemStruct.itemData := 0;
  end;
  Inherited;
end;//WMDeleteItem

function TJamFolderCombo.SelectFolder(aFolder:String): Boolean;
var idx: Integer;
begin
  idx := Items.IndexOf(aFolder);
  if idx=-1 then idx := AddFolder(aFolder, 0);
  ItemIndex := idx;
  Result := True;
end;//SelectFolder

function TJamFolderCombo.GetVersion: String;
begin
  Result := ClassName + JAM_COMPONENT_VERSION;
end;//GetVersion

procedure TJamFolderCombo.SetVersion(s: String);
begin
  // empty
end;//SetVersion



procedure Register;
begin
  RegisterComponents('JAM Software', [TJamFolderCombo]);
end;

end.
