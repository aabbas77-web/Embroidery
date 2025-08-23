{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrSpinner;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  CommCtrl, {$IFDEF VER110} ImgList,{$ENDIF} VrClasses, VrControls,
  VrTypes, VrSysUtils, VrThreads;


const
  InitRepeatPause = 400;
  RepeatPause     = 100;

type
  TVrSpinButton = class;
  TVrTimerSpinButton = class;

  TVrSpinButtonType = (stUp, stDown, stLeft, stRight);

  TVrSpinner = class (TWinControl)
  private
    FUpButton: TVrTimerSpinButton;
    FDownButton: TVrTimerSpinButton;
    FFocusedButton: TVrTimerSpinButton;
    FFocusControl: TWinControl;
    FOrientation: TVrOrientation;
    FPalette: TVrPalette;
    FOnUpClick: TNotifyEvent;
    FOnDownClick: TNotifyEvent;
    function CreateButton(BtnType: TVrSpinButtonType): TVrTimerSpinButton;
    procedure BtnClick(Sender: TObject);
    procedure BtnMouseDown (Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure SetFocusBtn (Btn: TVrTimerSpinButton);
    procedure ChangeSize (var W: Integer; var H: Integer);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetPalette(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
    procedure WMSize(var Message: TWMSize);  message WM_SIZE;
    procedure WMSetFocus(var Message: TWMSetFocus); message WM_SETFOCUS;
    procedure WMKillFocus(var Message: TWMKillFocus); message WM_KILLFOCUS;
    procedure WMGetDlgCode(var Message: TWMGetDlgCode); message WM_GETDLGCODE;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
  protected
    procedure Loaded; override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure Notification(AComponent: TComponent;
      Operation: TOperation); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
  published
    property FocusControl: TWinControl read FFocusControl write FFocusControl;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voVertical;
    property Palette: TVrPalette read FPalette write SetPalette;
    property OnDownClick: TNotifyEvent read FOnDownClick write FOnDownClick;
    property OnUpClick: TNotifyEvent read FOnUpClick write FOnUpClick;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color default clBtnFace;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Enabled;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnDragDrop;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
    property OnEnter;
    property OnExit;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;

  TVrSpinButton = class(TVrGraphicControl)
  private
    FBtnType: TVrSpinButtonType;
    FPalette: TVrPalette;
    ImageList: TImageList;
    Bitmap: TBitmap; //Mask
    MouseBtnDown: Boolean;
    procedure SetBtnType(Value: TVrSpinButtonType);
    procedure SetPalette(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
    function InControl(X, Y: Integer): Boolean;
  protected
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure LoadBitmaps; virtual;
    function ImageRect: TRect;
    procedure Paint; override;
    procedure Click; override;
    procedure DoClick;
    property BtnType: TVrSpinButtonType read FBtnType write SetBtnType default stUp;
    property Palette: TVrPalette read FPalette write SetPalette;
    property Color default clBtnFace;
    property ParentColor default true;
    property Enabled;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

  { TTimerSpeedButton }

  TTimeBtnState = set of (tbFocusRect, tbAllowTimer);

  TVrTimerSpinButton = class(TVrSpinButton)
  private
    FRepeatTimer: TVrTimer;
    FTimeBtnState: TTimeBtnState;
    procedure TimerExpired(Sender: TObject);
  protected
    procedure Paint; override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer); override;
  public
    destructor Destroy; override;
    property TimeBtnState: TTimeBtnState read FTimeBtnState write FTimeBtnState;
  end;


implementation

{$R VRSPINNER.D32}

const
  ResId: array[TVrSpinButtonType] of PChar =
    ('ARROWS_UP', 'ARROWS_DOWN', 'ARROWS_LEFT', 'ARROWS_RIGHT');



{ TVrSpinner }
constructor TVrSpinner.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle -
    [csAcceptsControls, csSetCaption, csFramed] + [csOpaque];
  Width := 35;
  Height := 40;
  Color := clBtnFace;
  ParentColor := true;
  FOrientation := voVertical;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FUpButton := CreateButton(stUp);
  FDownButton := CreateButton(stDown);
  FFocusedButton := FUpButton;
end;

destructor TVrSpinner.Destroy;
begin
  FPalette.Free;
  inherited Destroy;
end;

function TVrSpinner.CreateButton(BtnType: TVrSpinButtonType): TVrTimerSpinButton;
begin
  Result := TVrTimerSpinButton.Create (Self);
  Result.OnClick := BtnClick;
  Result.OnMouseDown := BtnMouseDown;
  Result.Visible := True;
  Result.Enabled := True;
  Result.TimeBtnState := [tbAllowTimer];
  Result.BtnType := BtnType;
  Result.Palette.Assign(Palette);
  Result.Parent := Self;
end;

procedure TVrSpinner.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) and (AComponent = FFocusControl) then
    FFocusControl := nil;
end;

procedure TVrSpinner.ChangeSize(var W: Integer; var H: Integer);
begin
  if (FUpButton = nil) or (csLoading in ComponentState) then Exit;
  if W < 15 then W := 15;
  if FOrientation = voVertical then
  begin
    FUpButton.SetBounds (0, 0, W, H div 2);
    FDownButton.SetBounds (0, FUpButton.Height - 1, W, H - FUpButton.Height + 1);
  end
  else
  begin
    FUpButton.SetBounds (0, 0, W div 2, H);
    FDownButton.SetBounds(W div 2, 0, W div 2, H);
  end;
end;

procedure TVrSpinner.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
var
  W, H: Integer;
begin
  W := AWidth;
  H := AHeight;
  ChangeSize (W, H);
  inherited SetBounds (ALeft, ATop, W, H);
end;

procedure TVrSpinner.WMSize(var Message: TWMSize);
var
  W, H: Integer;
begin
  inherited;
  { check for minimum size }
  W := Width;
  H := Height;
  ChangeSize (W, H);
  if (W <> Width) or (H <> Height) then
    inherited SetBounds(Left, Top, W, H);
  Message.Result := 0;
end;

procedure TVrSpinner.WMSetFocus(var Message: TWMSetFocus);
begin
  FFocusedButton.TimeBtnState := FFocusedButton.TimeBtnState + [tbFocusRect];
  FFocusedButton.UpdateControlCanvas;
end;

procedure TVrSpinner.WMKillFocus(var Message: TWMKillFocus);
begin
  FFocusedButton.TimeBtnState := FFocusedButton.TimeBtnState - [tbFocusRect];
  FFocusedButton.UpdateControlCanvas;
end;

procedure TVrSpinner.KeyDown(var Key: Word; Shift: TShiftState);
begin
  case Key of
    VK_UP:
      if FOrientation = voVertical then
      begin
        SetFocusBtn (FUpButton);
        FUpButton.DoClick;
      end;
    VK_DOWN:
      if FOrientation = voVertical then
      begin
        SetFocusBtn (FDownButton);
        FDownButton.DoClick;
      end;
    VK_LEFT:
      if FOrientation = voHorizontal then
      begin
        SetFocusBtn (FUpButton);
        FUpButton.DoClick;
      end;
    VK_RIGHT:
      if FOrientation = voHorizontal then
      begin
        SetFocusBtn (FDownButton);
        FDownButton.DoClick;
      end;

    VK_SPACE:
      FFocusedButton.DoClick;
  end;
end;

procedure TVrSpinner.BtnMouseDown (Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if Button = mbLeft then
  begin
    SetFocusBtn (TVrTimerSpinButton(Sender));
    if (FFocusControl <> nil) and FFocusControl.TabStop and
        FFocusControl.CanFocus and (GetFocus <> FFocusControl.Handle) then
      FFocusControl.SetFocus
    else if TabStop and (GetFocus <> Handle) and CanFocus then
      SetFocus;
  end;
end;

procedure TVrSpinner.BtnClick(Sender: TObject);
begin
  if Sender = FUpButton then
  begin
    if Assigned(FOnUpClick) then FOnUpClick(Self);
  end
  else
    if Assigned(FOnDownClick) then FOnDownClick(Self);
end;

procedure TVrSpinner.SetFocusBtn (Btn: TVrTimerSpinButton);
begin
  if TabStop and CanFocus and  (Btn <> FFocusedButton) then
  begin
    FFocusedButton.TimeBtnState := FFocusedButton.TimeBtnState - [tbFocusRect];
    FFocusedButton := Btn;
    if (GetFocus = Handle) then
    begin
       FFocusedButton.TimeBtnState := FFocusedButton.TimeBtnState + [tbFocusRect];
       Repaint;
    end;
  end;
end;

procedure TVrSpinner.WMGetDlgCode(var Message: TWMGetDlgCode);
begin
  Message.Result := DLGC_WANTARROWS;
end;

procedure TVrSpinner.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  FUpButton.Enabled := Enabled;
  FDownButton.Enabled := Enabled;
end;

procedure TVrSpinner.Loaded;
var
  W, H: Integer;
begin
  inherited Loaded;
  W := Width;
  H := Height;
  ChangeSize(W, H);
  if (W <> Width) or (H <> Height) then
    inherited SetBounds (Left, Top, W, H);
end;

procedure TVrSpinner.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if FUpButton <> nil then FUpButton.Free;
    if FDownButton <> nil then FDownButton.Free;
    if Value = voVertical then
    begin
      FUpButton := CreateButton(stUp);
      FDownButton := CreateButton(stDown);
    end
    else
    begin
      FUpButton := CreateButton(stLeft);
      FDownButton := CreateButton(stRight);
    end;
    if csDesigning in ComponentState then
    begin
      if Align = alNone then
        BoundsRect := Bounds(Left, Top, Height, Width)
      else RecreateWnd;
    end;
  end;
end;

procedure TVrSpinner.PaletteModified(Sender: TObject);
begin
  FUpButton.Palette.Assign(FPalette);
  FDownButton.Palette.Assign(FPalette);
end;

procedure TVrSpinner.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

{ VrSpinButton }
constructor TVrSpinButton.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csClickEvents] - [csDoubleClicks];
  Height := 25;
  Width := 25;
  Color := clBtnFace;
  ParentColor := true;
  FBtnType := stUp;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;

  ImageList := TImageList.Create(nil);
  ImageList.DrawingStyle := dsTransparent;
  Bitmap := TBitmap.Create;
  LoadBitmaps;
end;

destructor TVrSpinButton.Destroy;
begin
  FPalette.Free;
  Bitmap.Free;
  ImageList.Free;
  inherited Destroy;
end;

procedure TVrSpinButton.LoadBitmaps;
begin
  ImageList.Width := 21;
  ImageList.Height := 16;
  if FBtnType in [stLeft, stRight] then
  begin
    ImageList.Width := 17;
    ImageList.Height := 21;
  end;
  Bitmap.Handle := LoadBitmap(hInstance, ResId[FBtnType]);
  FPalette.ToBMP(Bitmap, clGreen, clLime);
  ImageList.Clear;
  ImageList.AddMasked(Bitmap, Bitmap.TransparentColor);
  ImageList.GetBitmap(0, Bitmap);
  Bitmap.Mask(Bitmap.TransparentColor);
end;

procedure TVrSpinButton.SetBtnType(Value: TVrSpinButtonType);
begin
  if FBtnType <> Value then
  begin
    FBtnType := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpinButton.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrSpinButton.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

function TVrSpinButton.ImageRect: TRect;
var
  X, Y: Integer;
begin
  X := (Width - ImageList.Width) div 2;
  Y := (Height - ImageList.Height) div 2;
  Result := Bounds(X, Y, ImageList.Width, ImageList.Height);
end;

procedure TVrSpinButton.Paint;
var
  Index: Integer;
begin
  ClearClientCanvas;

  Index := 1;
  if Enabled then
  begin
    if (MouseBtnDown) then Index := 2;
  end else Index := 0;

  {$IFDEF VER110}
    ImageList.Draw(Canvas,
      ImageRect.Left, ImageRect.Top, Index, True);
  {$ELSE}
    ImageList.Draw(Canvas,
      ImageRect.Left, ImageRect.Top, Index);
  {$ENDIF}
end;

function TVrSpinButton.InControl(X, Y: Integer): Boolean;
var
  Px, Py: Integer;
begin
  Px := ImageRect.Right - X - 1;
  Py := ImageRect.Bottom - Y - 1;
  Result := (Bitmap.Canvas.Pixels[Px, Py] = clBlack) and
            (Canvas.Pixels[X, Y] <> clBlack);
end;

procedure TVrSpinButton.Click;
begin
end;

procedure TVrSpinButton.DoClick;
begin
  inherited Click;
end;

procedure TVrSpinButton.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  inherited;
  if (Button = mbLeft) and Enabled then
    if InControl(X, Y) then
    begin
      MouseBtnDown := true;
      MouseCapture := true;
      UpdateControlCanvas;
    end;
end;

procedure TVrSpinButton.MouseUp(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  inherited;
  MouseBtnDown := false;
  MouseCapture := false;
  UpdateControlCanvas;
  if InControl(X, Y) then DoClick;
end;

{TVrTimerSpinButton}
destructor TVrTimerSpinButton.Destroy;
begin
  if FRepeatTimer <> nil then
    FRepeatTimer.Free;
  inherited Destroy;
end;

procedure TVrTimerSpinButton.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  inherited MouseDown (Button, Shift, X, Y);
  if tbAllowTimer in FTimeBtnState then
  begin
    if FRepeatTimer = nil then
      FRepeatTimer := TVrTimer.Create(Self);
    FRepeatTimer.Enabled := false;
    FRepeatTimer.OnTimer := TimerExpired;
    FRepeatTimer.Interval := InitRepeatPause;
    FRepeatTimer.TimerType := ttSystem;
    FRepeatTimer.Enabled := True;
  end;
end;

procedure TVrTimerSpinButton.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  inherited MouseUp(Button, Shift, X, Y);
  if FRepeatTimer <> nil then
    FRepeatTimer.Enabled  := False;
end;

procedure TVrTimerSpinButton.TimerExpired(Sender: TObject);
begin
  FRepeatTimer.Interval := RepeatPause;
  if (MouseBtnDown) and MouseCapture then
  begin
    try
      DoClick;
    except
      FRepeatTimer.Enabled := False;
      raise;
    end;
  end;
end;

procedure TVrTimerSpinButton.Paint;
var
  R: TRect;
begin
  inherited Paint;
  if tbFocusRect in FTimeBtnState then
  begin
    R := Bounds(0, 0, Width, Height);
    InflateRect(R, -3, -3);
    Canvas.Brush.Style := bsSolid;
    Canvas.Brush.Color := clBlack;
    Canvas.FrameRect(R);
  end;
end;


end.
