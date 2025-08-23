{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrThreads;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls;


{$I VRLIB.INC}

type
  TVrTimerType = (ttThread, ttSystem);

  TVrTimer = class(TVrComponent)
  private
    FEnabled: Boolean;
    FInterval: Cardinal;
    FOnTimer: TNotifyEvent;
    FWindowHandle: HWND;
    FSyncEvent: Boolean;
    FTimerType: TVrTimerType;
    FTimerThread: TThread;
    FPriority: TThreadPriority;
    FAllocated: Boolean;
    procedure SetTimerType(Value: TVrTimerType);
    procedure SetPriority(Value: TThreadPriority);
    procedure SetEnabled(Value: Boolean);
    procedure SetInterval(Value: Cardinal);
    procedure CreateTimer;
    procedure DestroyTimer;
    procedure UpdateTimer;
    procedure WndProc(var Msg: TMessage);
  protected
    procedure Loaded; override;
    procedure Timer; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Enabled: Boolean read FEnabled write SetEnabled default True;
    property Interval: Cardinal read FInterval write SetInterval default 1000;
    property SyncEvent: Boolean read FSyncEvent write FSyncEvent default True;
    property TimerType: TVrTimerType read FTimerType write SetTimerType default ttThread;
    property Priority: TThreadPriority read FPriority write SetPriority default tpNormal;
    property OnTimer: TNotifyEvent read FOnTimer write FOnTimer;
  end;

  TVrThread = class;

  TVrSystemThread = class(TThread)
  private
    FOwner: TVrThread;
    FOnExecute: TNotifyEvent;
  protected
    procedure CallExecute;
    procedure Execute; override;
  public
    constructor Create(AOwner: TVrThread; Enabled: Boolean);
    property OnExecute: TNotifyEvent read FOnExecute write FOnExecute;
  end;

  TVrThread = class(TVrComponent)
  private
    FEnabled: Boolean;
    FSyncEvent: Boolean;
    FPriority: TThreadPriority;
    FOnExecute: TNotifyEvent;
    FSystemThread: TVrSystemThread;
    procedure SetEnabled(Value: Boolean);
    procedure SetPriority(Value: TThreadPriority);
    procedure ExecuteEvent(Sender: TObject);
  protected
    procedure UpdateThreadParams;
    procedure Loaded; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Enabled: Boolean read FEnabled write SetEnabled default True;
    property Priority: TThreadPriority read FPriority write SetPriority default tpNormal;
    property SyncEvent: Boolean read FSyncEvent write FSyncEvent default True;
    property OnExecute: TNotifyEvent read FOnExecute write FOnExecute;
  end;


implementation

{ TVrTimerThread }

type
  TVrTimerThread = class(TThread)
  private
    FOwner: TVrTimer;
    FEvent: THandle;
    FInterval: Cardinal;
  protected
    procedure Execute; override;
  public
    constructor Create(Timer: TVrTimer; Enabled: Boolean);
    destructor Destroy; override;
    procedure Reset;
  end;

constructor TVrTimerThread.Create(Timer: TVrTimer; Enabled: Boolean);
begin
  FOwner := Timer;
  FInterval := 1000;
  FEvent := CreateEvent(nil, False, False, nil);
  inherited Create(not Enabled);
end;

destructor TVrTimerThread.Destroy;
begin
  CloseHandle(FEvent);
  inherited;
end;

procedure TVrTimerThread.Reset;
begin
  while Suspended do Resume;
  Terminate;
  SetEvent(FEvent);
end;

procedure TVrTimerThread.Execute;
begin
  while not Terminated do
    case WaitForSingleObject(FEvent, FInterval) of
      WAIT_OBJECT_0:;
      WAIT_TIMEOUT:
        if (not Terminated) and (not Application.Terminated) then
          with FOwner do
          begin
            if (FSyncEvent) then
              Synchronize(Timer) else Timer;
          end;
    end;
end;

{ TVrTimer }

constructor TVrTimer.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FEnabled := True;
  FInterval := 1000;
  FSyncEvent := True;
  FTimerType := ttThread;
  FPriority := tpNormal;
  FAllocated := false;
end;

destructor TVrTimer.Destroy;
begin
  FEnabled := False;
  FOnTimer := nil;
  DestroyTimer;
  inherited Destroy;
end;

procedure TVrTimer.Loaded;
begin
  inherited Loaded;
  UpdateTimer;
end;

procedure TVrTimer.WndProc(var Msg: TMessage);
begin
  with Msg do
    if Msg = WM_TIMER then Timer
    else Result := DefWindowProc(FWindowHandle, Msg, wParam, lParam);
end;

procedure TVrTimer.CreateTimer;
begin
  if TimerType = ttThread then
    FTimerThread := TVrTimerThread.Create(Self, False)
  else FWindowHandle := AllocateHWnd(WndProc);
  FAllocated := True;
end;

procedure TVrTimer.DestroyTimer;
begin
  if FAllocated then
  begin
    if TimerType = ttThread then
    begin
      TVrTimerThread(FTimerThread).Reset;
      FTimerThread.Free;
    end
    else
     begin
       KillTimer(FWindowHandle, 1);
       DeallocateHWnd(FWindowHandle);
     end;
     FAllocated := false;
  end;
end;

procedure TVrTimer.UpdateTimer;
begin
  if (csDesigning in ComponentState) then Exit;

  if (not FAllocated) then CreateTimer;

  if TimerType = ttThread then
  begin
    if not FTimerThread.Suspended then FTimerThread.Suspend;
    TVrTimerThread(FTimerThread).FInterval := FInterval;
    if (FInterval <> 0) and FEnabled and Assigned(FOnTimer) then
    begin
      FTimerThread.Priority := FPriority;
      while FTimerThread.Suspended do FTimerThread.Resume;
    end;
  end
  else
  begin
    KillTimer(FWindowHandle, 1);
    if (FInterval <> 0) and FEnabled and Assigned(FOnTimer) then
      if SetTimer(FWindowHandle, 1, FInterval, nil) = 0 then
        raise EOutOfResources.Create('No timer resources left.');
  end;
end;

procedure TVrTimer.SetEnabled(Value: Boolean);
begin
  if FEnabled <> Value then
  begin
    FEnabled := Value;
    if Value then UpdateTimer;
  end;
end;

procedure TVrTimer.SetInterval(Value: Cardinal);
begin
  if FInterval <> Value then
  begin
    FInterval := Value;
    if Enabled then UpdateTimer;
  end;
end;

procedure TVrTimer.SetTimerType(Value: TVrTimerType);
begin
  if FTimerType <> Value then
  begin
    DestroyTimer;
    FTimerType := Value;
    if Enabled then UpdateTimer;
  end;
end;

procedure TVrTimer.SetPriority(Value: TThreadPriority);
begin
  if FPriority <> Value then
  begin
    FPriority := Value;
    if (TimerType = ttThread) and (Enabled) then UpdateTimer;
  end;
end;

procedure TVrTimer.Timer;
begin
  if (FEnabled) and Assigned(FOnTimer) then
  begin
    try
      FOnTimer(Self);
    except
      Application.HandleException(Self);
    end;
  end;

end;

{ TVrSystemThread }

constructor TVrSystemThread.Create(AOwner: TVrThread; Enabled: Boolean);
begin
  FOwner := AOwner;
  inherited Create(not Enabled);
end;

procedure TVrSystemThread.Execute;

  function ThreadClosed: Boolean;
  begin
    Result := Terminated or (FOwner = nil);
  end;

begin
  while not Terminated do
  begin
    if (FOwner.FEnabled) and (not Application.Terminated) then
      with FOwner do
        if SyncEvent then Synchronize(CallExecute)
        else CallExecute;
  end;
end;

procedure TVrSystemThread.CallExecute;
begin
  if Assigned(FOnExecute) then FOnExecute(Self);
end;

{ TVrThread }

constructor TVrThread.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FEnabled := True;
  FPriority := tpNormal;
  FSyncEvent := True;
  FSystemThread := TVrSystemThread.Create(Self, false);
  FSystemThread.OnExecute := ExecuteEvent;
end;

destructor TVrThread.Destroy;
begin
  FSystemThread.OnExecute := nil;
  while FSystemThread.Suspended do
    FSystemThread.Resume;
  FSystemThread.Terminate;
  FSystemThread.Free;
  inherited Destroy;
end;

procedure TVrThread.Loaded;
begin
  inherited Loaded;
  UpdateThreadParams;
end;

procedure TVrThread.UpdateThreadParams;
begin
  if (csDesigning in ComponentState) then Exit;
  if not FSystemThread.Suspended then FSystemThread.Suspend;
  if Enabled then
  begin
    FSystemThread.Priority := FPriority;
    while FSystemThread.Suspended do FSystemThread.Resume;
  end;
end;

procedure TVrThread.SetEnabled(Value: Boolean);
begin
  if FEnabled <> Value then
  begin
    FEnabled := Value;
    UpdateThreadParams;
  end;
end;

procedure TVrThread.SetPriority(Value: TThreadPriority);
begin
  if FPriority <> Value then
  begin
    FPriority := Value;
    UpdateThreadParams;
  end;
end;

procedure TVrThread.ExecuteEvent(Sender: TObject);
begin
  if Enabled and Assigned(FOnExecute) then
  begin
    try
      FOnExecute(Self);
    except
      Application.HandleException(Self);
    end;
  end;
end;


end.
