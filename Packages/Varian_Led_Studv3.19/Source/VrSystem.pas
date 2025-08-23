{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrSystem;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ShellAPI, Menus, VrTypes, VrClasses, VrControls;


type
  TVrBitmapList = class(TVrComponent)
  private
    FBitmaps: TVrBitmaps;
    FOnChange: TNotifyEvent;
    procedure SetBitmaps(Value: TVrBitmaps);
    procedure BitmapsChanged(Sender: TObject);
  protected
    procedure Changed; virtual;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Bitmaps: TVrBitmaps read FBitmaps write SetBitmaps;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  end;

  TVrStringList = class(TVrComponent)
  private
    FItems: TStrings;
    FOnChange: TNotifyEvent;
    FOnChanging: TNotifyEvent;
    function GetCount: Integer;
    function GetSorted: Boolean;
    procedure SetItems(Value: TStrings);
    procedure SetSorted(Value: Boolean);
    procedure Change(Sender: TObject);
    procedure Changing(Sender: TObject);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Count: Integer read GetCount;
  published
    property Strings: TStrings read FItems write SetItems;
    property Sorted: Boolean read GetSorted write SetSorted default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property OnChanging: TNotifyEvent read FOnChanging write FOnChanging;
  end;

  TVrKeyStateType = (ksNUM, ksCAPS, ksSCROLL);
  TVrKeyStateTypes = set of TVrKeyStateType;

  TVrKeyStatus = class(TVrComponent)
  private
    FHandle: HWnd;
    FMonitorEvents: Boolean;
    FKeys: TVrKeyStateTypes;
    FOnChange: TNotifyEvent;
    procedure SetKeys(Value: TVrKeyStateTypes);
    procedure SetMonitorEvents(Value: Boolean);
    procedure ChangeState(Key: Word; Active: Boolean);
    procedure UpdateTimer;
    procedure WndProc(var Msg: TMessage);
  protected
    procedure Timer;
    procedure Changed; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Keys: TVrKeyStateTypes read FKeys write SetKeys default [];
    property MonitorEvents: Boolean read FMonitorEvents write SetMonitorEvents default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  end;

const  
  WM_TOOLTRAYNOTIFY = WM_USER + $44;

type
  TVrCustomTrayIcon = class(TVrComponent)
  private
    FIconData: TNOTIFYICONDATA;
    FIcon: TIcon;
    FEnabled: Boolean;
    FHint: string;
    FShowHint: Boolean;
    FVisible: Boolean;
    FPopupMenu: TPopupMenu;
    FExists: Boolean;
    FClicked: Boolean;
    FHideTaskBtn: Boolean;
    FLeftBtnPopup: Boolean;
    FOnClick: TNotifyEvent;
    FOnDblClick: TNotifyEvent;
    FOnMouseDown: TMouseEvent;
    FOnMouseUp: TMouseEvent;
    FOnMouseMove: TMouseMoveEvent;
    OldAppProc: Pointer;
    NewAppProc: Pointer;
    procedure SetIcon(Value: TIcon);
    procedure SetVisible(Value: Boolean);
    procedure SetHint(const Value: string);
    procedure SetShowHint(Value: Boolean);
    procedure SetPopupMenu(Value: TPopupMenu);
    procedure ShowMenu;
    procedure UpdateHint;
    procedure UpdateSystemTray;
    procedure IconChanged(Sender: TObject);
    procedure HookApp;
    procedure UnhookApp;
    procedure HookAppProc(var Message: TMessage);
  protected
    procedure WndProc(var Msg: TMessage); virtual;
    procedure Notification(AComponent: TComponent;
      Operation: TOperation); override;
    procedure DoHideTaskBtn;
    procedure Click; dynamic;
    procedure DblClick; dynamic;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer); dynamic;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer); dynamic;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); dynamic;
    property Icon: TIcon read FIcon write SetIcon;
    property Visible: Boolean read FVisible write SetVisible default false;
    property Enabled: Boolean read FEnabled write FEnabled default True;
    property Hint: string read FHint write SetHint;
    property ShowHint: Boolean read FShowHint write SetShowHint default false;
    property PopupMenu: TPopupMenu read FPopupMenu write SetPopupMenu;
    property HideTaskBtn: Boolean read FHideTaskBtn write FHideTaskBtn default false;
    property LeftBtnPopup: Boolean read FLeftBtnPopup write FLeftBtnPopup default false;
    property OnClick: TNotifyEvent read FOnClick write FOnClick;
    property OnDblClick: TNotifyEvent read FOnDblClick write FOnDblClick;
    property OnMouseDown: TMouseEvent read FOnMouseDown write FOnMouseDown;
    property OnMouseUp: TMouseEvent read FOnMouseUp write FOnMouseUp;
    property OnMouseMove: TMouseMoveEvent read FOnMouseMove write FOnMouseMove;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure HideMainForm;
    procedure ShowMainForm;
  end;

  TVrTrayIcon = class(TVrCustomTrayIcon)
  published
    property Icon;
    property Visible;
    property Enabled;
    property Hint;
    property ShowHint;
    property PopupMenu;
    property HideTaskBtn;
    property LeftBtnPopup;
    property OnClick;
    property OnDblClick;
    property OnMouseDown;
    property OnMouseUp;
    property OnMouseMove;
  end;


implementation

{ TVrBitmapList }

constructor TVrBitmapList.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FBitmaps := TVrBitmaps.Create;
  FBitmaps.OnChange := BitmapsChanged;
end;

destructor TVrBitmapList.Destroy;
begin
  FBitmaps.Free;
  inherited Destroy;
end;

procedure TVrBitmapList.SetBitmaps(Value: TVrBitmaps);
begin
  FBitmaps.Assign(Value);
end;

procedure TVrBitmapList.Changed;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrBitmapList.BitmapsChanged(Sender: TObject);
begin
  Changed;
end;

{ TVrStringList }

constructor TVrStringList.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FItems := TStringList.Create;
  TStringList(FItems).OnChange := Change;
  TStringList(FItems).OnChanging := Changing;
end;

destructor TVrStringList.Destroy;
begin
  FItems.Free;
  inherited Destroy;
end;

procedure TVrStringList.SetItems(Value: TStrings);
begin
  FItems.Assign(Value);
end;

function TVrStringList.GetSorted: Boolean;
begin
  Result := TStringList(FItems).Sorted;
end;

function TVrStringList.GetCount: Integer;
begin
  Result := FItems.Count;
end;

procedure TVrStringList.SetSorted(Value: Boolean);
begin
  TStringList(FItems).Sorted := Value;
end;

procedure TVrStringList.Change(Sender: TObject);
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrStringList.Changing(Sender: TObject);
begin
  if Assigned(FOnChanging) then FOnChanging(Self);
end;

{ TVrKeyStatus }

constructor TVrKeyStatus.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FKeys := [];
  FMonitorEvents := false;
  FHandle := AllocateHWnd(WndProc);
end;

destructor TVrKeyStatus.Destroy;
begin
  FMonitorEvents := false;
  UpdateTimer;
  DeallocateHWnd(FHandle);
  inherited Destroy;
end;

procedure TVrKeyStatus.WndProc(var Msg: TMessage);
begin
  with Msg do
    if Msg = WM_TIMER then
      try
        Timer;
      except
        Application.HandleException(Self);
      end
    else
      Result := DefWindowProc(FHandle, Msg, wParam, lParam);
end;

procedure TVrKeyStatus.UpdateTimer;
begin
  KillTimer(FHandle, 1);
  if MonitorEvents then
    if SetTimer(FHandle, 1, 100, nil) = 0 then
      raise EOutOfResources.Create('Out of resources.');
end;

procedure TVrKeyStatus.Changed;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrKeyStatus.Timer;
var
  Current: Integer;
  NewKeys: TVrKeyStateTypes;
begin
  NewKeys := [];
  Current := GetKeyState(VK_NUMLOCK);
  if Current <> 0 then NewKeys := NewKeys + [ksNUM];
  Current := GetKeyState(VK_CAPITAL);
  if Current <> 0 then NewKeys := NewKeys + [ksCAPS];
  Current := GetKeyState(VK_SCROLL);
  if Current <> 0 then NewKeys := NewKeys + [ksSCROLL];
  if not (csDesigning in ComponentState) then
    if Keys <> NewKeys then
    begin
      FKeys := NewKeys;
      Changed;
    end;
end;

procedure TVrKeyStatus.ChangeState(Key: Word; Active: Boolean);
var
  Current: Integer;
  KeyState: TKeyBoardState;
begin
  Current := GetKeyState(Key);
  GetKeyboardState(KeyState);
  if (Current = 0) and (Active) then
  begin
    KeyState[Key] := 1;
    SetKeyboardState(KeyState);
  end
  else
  if (not Active) then
  begin
    KeyState[Key] := 0;
    SetKeyboardState(KeyState);
  end;
end;

procedure TVrKeyStatus.SetMonitorEvents(Value: Boolean);
begin
  if FMonitorEvents <> Value then
  begin
    FMonitorEvents := Value;
    UpdateTimer;
  end;
end;

procedure TVrKeyStatus.SetKeys(Value: TVrKeyStateTypes);
const
  KeyValues: array[TVrKeyStateType] of Word =
    (VK_NUMLOCK, VK_CAPITAL, VK_SCROLL);
var
  I: TVrKeyStateType;
begin
  if FKeys <> Value then
  begin
    FKeys := Value;
    for I := Low(TVrKeyStateType) to High(TVrKeyStateType) do
      ChangeState(KeyValues[I], I in Value);
    Changed;
  end;
end;

{ TVrCustomTrayIcon }

constructor TVrCustomTrayIcon.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FIcon := TIcon.Create;
  FIcon.OnChange := IconChanged;
  FEnabled := True;
  FVisible := false;
  FExists := false;
  FShowHint := false;
  FLeftBtnPopup := false;
  FHideTaskBtn := false;
  with FIconData do
  begin
    cbSize := SizeOf(TNOTIFYICONDATA);
    Wnd := AllocateHWnd(WndProc);
    uID := 0;
    uFlags := NIF_MESSAGE + NIF_ICON + NIF_TIP;
    uCallbackMessage := WM_TOOLTRAYNOTIFY;
  end;
  HookApp;
end;

destructor TVrCustomTrayIcon.Destroy;
begin
  Visible := false;
  FIcon.Free;
  DeallocateHWnd(FIconData.Wnd);
  UnhookApp;
  inherited Destroy;
end;

procedure TVrCustomTrayIcon.HookApp;
begin
  if not (csDesigning in ComponentState) then
  begin
    OldAppProc := Pointer(GetWindowLong(Application.Handle, GWL_WNDPROC));
    NewAppProc := MakeObjectInstance(HookAppProc);
    SetWindowLong(Application.Handle, GWL_WNDPROC, LongInt(NewAppProc));
  end;
end;

procedure TVrCustomTrayIcon.UnhookApp;
begin
  if not (csDesigning in ComponentState) then
  begin
    if Assigned(OldAppProc) then
      SetWindowLong(Application.Handle, GWL_WNDPROC, LongInt(OldAppProc));
    if Assigned(NewAppProc) then
      FreeObjectInstance(NewAppProc);
    NewAppProc := nil;
    OldAppProc := nil;
  end;
end;

procedure TVrCustomTrayIcon.HookAppProc(var Message: TMessage);
begin
  with Message do
  begin
    case Msg of
      WM_SIZE:
        if wParam = SIZE_MINIMIZED then
        begin
          if FHideTaskBtn then
            DoHideTaskBtn;
        end;
    end;
    Result := CallWindowProc(OldAppProc, Application.Handle, Msg, wParam, lParam);
  end;
end;

procedure TVrCustomTrayIcon.DoHideTaskBtn;
begin
  HideMainForm;
  Visible := True;
end;

procedure TVrCustomTrayIcon.ShowMainForm;
begin
  ShowWindow(Application.Handle, SW_RESTORE);
  ShowWindow(Application.MainForm.Handle, SW_RESTORE);
end;

procedure TVrCustomTrayIcon.HideMainForm;
begin
  ShowWindow(Application.Handle, SW_HIDE);
  ShowWindow(Application.MainForm.Handle, SW_HIDE);
end;

procedure TVrCustomTrayIcon.SetPopupMenu(Value: TPopupMenu);
begin
  FPopupMenu := Value;
  Value.FreeNotification(Self);
end;

procedure TVrCustomTrayIcon.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) and (AComponent = FPopupMenu) then
    FPopupMenu := nil;
end;

procedure TVrCustomTrayIcon.IconChanged(Sender: TObject);
begin
  UpdateSystemTray;
end;

procedure TVrCustomTrayIcon.SetIcon(Value: TIcon);
begin
  FIcon.Assign(Value);
end;

procedure TVrCustomTrayIcon.SetVisible(Value: Boolean);
begin
  if FVisible <> Value then
  begin
    FVisible := Value;
    UpdateSystemTray;
  end;
end;

procedure TVrCustomTrayIcon.SetHint(const Value: string);
begin
  if FHint <> Value then
  begin
    FHint := Value;
    UpdateHint;
  end;
end;

procedure TVrCustomTrayIcon.SetShowHint(Value: Boolean);
begin
  if FShowHint <> Value then
  begin
    FShowHint := Value;
    UpdateHint;
  end;
end;

procedure TVrCustomTrayIcon.UpdateHint;
begin
  if (FHint <> '') and FShowHint then
    StrLCopy(FIconData.szTip, PChar(FHint), SizeOf(FIconData.szTip))
  else FIconData.szTip := '';
  UpdateSystemTray;
end;

procedure TVrCustomTrayIcon.UpdateSystemTray;
begin
  if (FIcon.Empty) or
    (csDesigning in ComponentState) then Exit;

  if (not Visible) and (FExists) then
  begin
    Shell_NotifyIcon(NIM_DELETE, @FIconData);
    FExists := false;
    Exit;
  end;

  if FVisible then
  begin
    FIconData.hIcon := FIcon.Handle;
    if (not FExists) then
    begin
      Shell_NotifyIcon(NIM_ADD, @FIconData);
      FExists := True;
    end else Shell_NotifyIcon(NIM_MODIFY, @FIconData);
  end;
end;

procedure TVrCustomTrayIcon.WndProc(var Msg: TMessage);

  function ShiftState: TShiftState;
  begin
    Result := [];
    if GetKeyState(Vk_Shift) < 0 then Include(Result, ssShift);
    if GetKeyState(Vk_Control) < 0 then Include(Result, ssCtrl);
    if GetKeyState(Vk_Menu) < 0 then Include(Result, ssAlt);
  end;

var
  P: TPoint;
  Shift: TShiftState;
begin
  with Msg do
    if Msg = WM_TOOLTRAYNOTIFY then
    begin
      case lParam of
        WM_MOUSEMOVE:
          if Enabled then
          begin
            Shift := ShiftState;
            GetCursorPos(P);
            MouseMove(Shift, P.X, P.Y);
          end;
        WM_LBUTTONDOWN:
          if Enabled then
          begin
            Shift := ShiftState + [ssLeft];
            GetCursorPos(P);
            MouseDown(mbLeft, Shift, P.X, P.Y);
            FClicked := True;
            if FLeftBtnPopup then
            begin
              FClicked := false;
              ShowMenu;
            end;
          end;
        WM_LBUTTONUP:
          if Enabled then
          begin
            Shift := ShiftState + [ssLeft];
            GetCursorPos(P);
            if FClicked then
            begin
              FClicked := False;
              Click;
            end;
            MouseUp(mbLeft, Shift, P.X, P.Y);
          end;
        WM_LBUTTONDBLCLK:
          if Enabled then DblClick;
        WM_RBUTTONDOWN:
          if Enabled then
          begin
            Shift := ShiftState + [ssRight];
            GetCursorPos(P);
            MouseDown(mbRight, Shift, P.X, P.Y);
            ShowMenu;
          end;
        WM_RBUTTONUP:
          if Enabled then
          begin
            Shift := ShiftState + [ssRight];
            GetCursorPos(P);
            MouseUp(mbRight, Shift, P.X, P.Y);
          end;
        WM_RBUTTONDBLCLK:
          if Enabled then DblClick;
        WM_MBUTTONDOWN:
          if Enabled then
          begin
            Shift := ShiftState + [ssMiddle];
            GetCursorPos(P);
            MouseDown(mbMiddle, Shift, P.X, P.Y);
          end;
        WM_MBUTTONUP:
          if Enabled then
          begin
            Shift := ShiftState + [ssMiddle];
            GetCursorPos(P);
            MouseUp(mbMiddle, Shift, P.X, P.Y);
          end;
        WM_MBUTTONDBLCLK:
          if Enabled then DblClick;
      end
    end else Result := DefWindowProc(FIconData.Wnd, Msg, wParam, lParam);
end;

procedure TVrCustomTrayIcon.ShowMenu;
var
  P: TPoint;
begin
  if (PopupMenu <> nil) then
  begin
    GetCursorPos(P);
    Application.ProcessMessages;
    SetForegroundWindow(Application.MainForm.Handle);
    PopupMenu.Popup(P.X, P.Y);
    PostMessage(Application.MainForm.Handle, WM_NULL, 0, 0);
  end;
end;

procedure TVrCustomTrayIcon.Click;
begin
  if Assigned(FOnClick) then FOnClick(Self);
end;

procedure TVrCustomTrayIcon.DblClick;
begin
  if Assigned(FOnDblClick) then FOnDblClick(Self);
end;

procedure TVrCustomTrayIcon.MouseDown(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseDown) then
    FOnMouseDown(Self, Button, Shift, X, Y);
end;

procedure TVrCustomTrayIcon.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseUp) then
    FOnMouseUp(Self, Button, Shift, X, Y);
end;

procedure TVrCustomTrayIcon.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseMove) then
    FOnMouseMove(Self, Shift, X, Y);
end;


end.
