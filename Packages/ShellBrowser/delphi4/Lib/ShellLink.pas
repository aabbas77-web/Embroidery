unit ShellLink;

interface

{$BOOLEVAL OFF}
{$I VER.INC}
{$IFDEF _CPPB_3_UP}
  {$ObjExportAll On}
{$ENDIF}

uses
  Windows, ShlObj, Messages, Classes, Controls, ShellBrowser;

const
  JAM_PATHCHANGED  = WM_USER + $280;
  JAM_SELECTALL    = WM_USER + $281;
  JAM_REFRESH      = WM_USER + $282;
  JAM_SMARTREFRESH = WM_USER + $283;
  JAM_GOUP         = WM_USER + $284;

type
  TJAMPathChanged = record
    Msg: Cardinal;
    PIDL: PItemIDList;
    Unused: longint;
    Result: Longint;
  end;

type
  TShellList = class(TList)
  protected
    function GetItem(aIndex: Integer): HWND;
    procedure SetItem(aIndex: Integer; newValue: HWND);
  public
    procedure Add(Handle: HWND);
    procedure Remove(Handle: HWND);
    property Items[aIndex: Integer]: HWND read GetItem write SetItem; default;
  end;

  TJamShellLink = class(TComponent)
  private
    FList    : TShellList;
    FEnabled : Boolean;
    FOnChange: TNotifyEvent;
  protected
    function  GetVersion: String;
    procedure SetVersion(s: String);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure RegisterShellControl(Handle: HWND);
    procedure UnregisterShellControl(Handle: HWND);
    procedure PathChanged(Sender: TWinControl; PIDL: PItemIdList);
    procedure SelectAll(Sender: TWinControl);
    procedure Refresh(Sender: TWinControl);
    procedure SmartRefresh(Sender: TWinControl);
    procedure GoUp(Sender: TWinControl);
  published
    property Enabled: Boolean read FEnabled write FEnabled default True;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property Version: String read GetVersion write SetVersion stored false;
  end;

procedure Register;


implementation

procedure TJamShellLink.PathChanged(Sender: TWinControl; PIDL: PItemIdList);
var i: integer;
begin
  if not Enabled then exit;
  Enabled := False;
  for i := 0 to FList.Count - 1 do begin    // Iterate
    if Sender.Handle <> FList[i] then
      SendMessage(FList[i], JAM_PATHCHANGED, Integer(PIDL) , 0);
  end;    // for
  Enabled := True;
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TJamShellLink.SelectAll(Sender: TWinControl);
var i: Integer;
begin
  if not Enabled then exit;
  for i := 0 to FList.Count - 1 do begin    // Iterate
    if Sender.Handle <> FList[i] then
      SendMessage(FList[i], JAM_SELECTALL, 0 , 0);
  end;    // for
end;//SelectAll

procedure TJamShellLink.Refresh(Sender: TWinControl);
var i: Integer;
begin
  if not Enabled then exit;
  for i := 0 to FList.Count - 1 do begin    // Iterate
    if Sender.Handle <> FList[i] then
      SendMessage(FList[i], JAM_REFRESH, 0 , 0);
  end;// for
end;//Refresh

procedure TJamShellLink.SmartRefresh(Sender: TWinControl);
var i: Integer;
begin
  if not Enabled then exit;
  for i := 0 to FList.Count - 1 do begin    // Iterate
    if Sender.Handle <> FList[i] then
      SendMessage(FList[i], JAM_SMARTREFRESH, 0 , 0);
  end;// for
end;//SmartRefresh

procedure TJamShellLink.GoUp(Sender: TWinControl);
var i: Integer;
begin
  if not Enabled then exit;
  for i := 0 to FList.Count - 1 do begin    // Iterate
    if Sender.Handle <> FList[i] then begin
      if SendMessage(FList[i], JAM_GOUP, 0 , 0)=1 then exit;
    end;//if
  end;// for
  // If no other control performed the GoUp, let the sender do it
  SendMessage(Sender.Handle, JAM_GOUP, 0 , 0); // If no other control
end;//GoUp

procedure TJamShellLink.UnregisterShellControl(Handle: HWND);
begin
  {$ifdef DebugShellLink}
  CodeSite.EnterMethod('UnregisterShellControl');
  {$endif}
  FList.Remove(Handle);
  {$ifdef DebugShellLink}
  CodeSite.ExitMethod('UnregisterShellControl');
  {$endif}
end;

procedure TJamShellLink.RegisterShellControl(Handle: HWND);
begin
  {$ifdef DebugShellLink}
  CodeSite.EnterMethod('RegisterShellControl');
  {$endif}
  FList.Add(Handle);
  {$ifdef DebugShellLink}
  CodeSite.ExitMethod('RegisterShellControl');
  {$endif}
end;

destructor TJamShellLink.Destroy;
begin
  FList.Free;
  inherited Destroy;
end;

constructor TJamShellLink.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FList := TShellList.Create;
  FEnabled := True;
end;

function TJamShellLink.GetVersion: String;
begin
  Result := ClassName + JAM_COMPONENT_VERSION;
end;//GetVersion

procedure TJamShellLink.SetVersion(s: String);
begin
  // empty
end;//SetVersion


//////////////////////////////////////////////////////////////////////////////

procedure TShellList.SetItem(aIndex: Integer; newValue: HWND);
begin
  inherited Items[aIndex] := Pointer(newValue);
end;

function TShellList.GetItem(aIndex: Integer): HWND;
begin
  result := HWND(inherited Items[aIndex]);
end;

procedure TShellList.Remove(Handle: HWND);
begin
  inherited Remove(Pointer(Handle));
end;

procedure TShellList.Add(Handle: HWND);
begin
  inherited Add(Pointer(Handle));
end;


procedure Register;
begin
  RegisterComponents('JAM Software', [TJamShellLink]);
end;

end.
