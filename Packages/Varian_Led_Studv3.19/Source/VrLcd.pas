{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrLcd;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrConst, VrTypes, VrClasses, VrControls, VrSysUtils, VrThreads;

type
  TVrNumStyle = (ns13x24, ns11x20, ns7x13, ns12x17, ns5x7);
  TVrNumAlignment = (naLeftJustify, naCenter, naRightJustify);

  TVrCustomNum = class(TVrGraphicImageControl)
  private
    FValue: Integer;
    FDigits: Integer;
    FMax: Integer;
    FMin: Integer;
    FSpacing: Integer;
    FStyle: TVrNumStyle;
    FLeadingZero: Boolean;
    FPalette: TVrPalette;
    FAlignment: TVrNumAlignment;
    FZeroBlank: Boolean;
    FAutoSize: Boolean;
    FOnChange: TNotifyEvent;
    Bitmap: TBitmap;
    ImageWidth: Integer;
    ImageHeight: Integer;
    BelowZero: Boolean;
    procedure SetDigits(Value: Integer);
    procedure SetValue(Value: Integer);
    procedure SetSpacing(Value: Integer);
    procedure SetStyle(Value: TVrNumStyle);
    procedure SetLeadingZero(Value: Boolean);
    procedure SetAlignment(Value: TVrNumAlignment);
    procedure SetAutoSize(Value: Boolean);
    procedure SetMin(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetZeroBlank(Value: Boolean);
    procedure SetPalette(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
  protected
    procedure LoadBitmaps; virtual;
    procedure DrawNum(Num: integer; X,Y: integer);
    procedure ChangeSize(NewWidth, NewHeight: Integer);
    procedure Paint; override;
    procedure Change; dynamic;
{$IFDEF VER110}
    procedure RequestAlign; override;
{$ELSE}
    procedure RequestAlign;
{$ENDIF}
    property Digits: Integer read FDigits write SetDigits default 4;
    property Value: Integer read FValue write SetValue default 0;
    property Spacing: Integer read FSpacing write SetSpacing default 2;
    property Style: TVrNumStyle read FStyle write SetStyle default ns13x24;
    property LeadingZero: Boolean read FLeadingZero write SetLeadingZero default false;
    property Palette: TVrPalette read FPalette write SetPalette;
    property Alignment: TVrNumAlignment read FAlignment write SetAlignment default naCenter;
    property AutoSize: Boolean read FAutoSize write SetAutoSize default false;
    property Max: Integer read FMax write SetMax default 9999;
    property Min: Integer read FMin write SetMin default 0;
    property ZeroBlank: Boolean read FZeroBlank write SetZeroBlank default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

  TVrNum = class(TVrCustomNum)
    property Digits;
    property Value;
    property Spacing;
    property Style;
    property LeadingZero;
    property Palette;
    property Alignment;
    property AutoSize;
    property Max;
    property Min;
    property ZeroBlank;
    property Transparent default false;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Visible;
    property OnChange;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}    
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;

  TVrClockType = (ctRealTime, ctElapsed, ctCustom);

  TVrClock = class(TVrCustomNum)
  private
    FHours: TVrHoursInt;
    FMinutes: TVrMinutesInt;
    FSeconds: TVrSecondsInt;
    FClockType: TVrClockType;
    FActive: Boolean;
    FShowSeconds: Boolean;
    FBlink: Boolean;
    FBlinkVisible: Boolean;
    FThreaded: Boolean;
    FOnHoursChanged: TVrHoursChangeEvent;
    FOnMinutesChanged: TVrMinutesChangeEvent;
    FOnSecondsChanged: TVrSecondsChangeEvent;
    FTimer: TVrTimer;
    ElapsedTime: TDateTime;
    Seperator: TBitmap;
    procedure SetHours(Value: TVrHoursInt);
    procedure SetMinutes(Value: TVrMinutesInt);
    procedure SetSeconds(Value: TVrSecondsInt);
    procedure SetActive(Value: Boolean);
    procedure SetClockType(Value: TVrClockType);
    procedure SetShowSeconds(Value: Boolean);
    procedure SetBlink(Value: Boolean);
    procedure SetThreaded(Value: Boolean);
    procedure OnTimerEvent(Sender: TObject);
  protected
    procedure LoadBitmaps; override;
    procedure Paint; override;
    procedure Loaded; override;
    procedure HoursChanged; virtual;
    procedure MinutesChanged; virtual;
    procedure SecondsChanged; virtual;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Hours: TVrHoursInt read FHours write SetHours default 0;
    property Minutes: TVrMinutesInt read FMinutes write SetMinutes default 0;
    property Seconds: TVrSecondsInt read FSeconds write SetSeconds default 0;
    property ClockType: TVrClockType read FClockType write SetClockType default ctRealTime;
    property Active: Boolean read FActive write SetActive default false;
    property ShowSeconds: Boolean read FShowSeconds write SetShowSeconds default false;
    property Blink: Boolean read FBlink write SetBlink default false;
    property Transparent default false;
    property OnHoursChanged: TVrHoursChangeEvent read FOnHoursChanged write FOnHoursChanged;
    property OnMinutesChanged: TVrMinutesChangeEvent read FOnMinutesChanged write FOnMinutesChanged;
    property OnSecondsChanged: TVrSecondsChangeEvent read FOnSecondsChanged write FOnSecondsChanged;
    property Palette;
    property Spacing;
    property Style;
    property AutoSize;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Visible;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}    
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


implementation

{$R VRLCD.D32}

const
  ResNumId: array[TVrNumStyle] of PChar =
    ('NUM13x24', 'NUM11x20', 'NUM7x13', 'NUM12x17', 'NUM5x7');
  ResClockId: array[TVrNumStyle] of PChar =
    ('CLOCKSEP1', 'CLOCKSEP2', 'CLOCKSEP3', 'CLOCKSEP4', 'CLOCKSEP5');

{TVrCustomNum}

constructor TVrCustomNum.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 100;
  Height := 26;
  ParentColor := false;
  Color := clBlack;
  FDigits := 4;
  FValue := 0;
  FSpacing := 2;
  FLeadingZero := false;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FStyle := ns13x24;
  FAlignment := naCenter;
  FAutoSize := false;
  FMin := 0;
  FMax := 9999;
  FZeroBlank := false;
  BelowZero := false;
  Bitmap := TBitmap.Create;
  LoadBitmaps;
end;

destructor TVrCustomNum.Destroy;
begin
  FPalette.Free;
  Bitmap.Free;
  inherited Destroy;
end;

procedure TVrCustomNum.LoadBitmaps;
begin
  Bitmap.Handle := LoadBitmap(hInstance, ResNumId[Style]);
  FPalette.ToBMP(Bitmap, ResColorLow, ResColorHigh);
  ImageWidth := Bitmap.Width div 13;
  ImageHeight := Bitmap.Height;
end;

procedure TVrCustomNum.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

procedure TVrCustomNum.SetDigits(Value: Integer);
begin
  if (FDigits <> Value) and (Value > 0) and (Value < 16) then
  begin
    FDigits := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetValue(Value: Integer);
begin
  AdjustRange(Value, FMin, FMax);
  if FValue <> Value then
  begin
    FValue := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrCustomNum.SetMin(Value: Integer);
begin
  if (FMin <> Value) and (Value < FMax) then
  begin
    FMin := Value;
    BelowZero := FMin < 0;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetMax(Value: Integer);
begin
  if (FMax <> Value) and (Value > FMin) then
  begin
    FMax := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetStyle(Value: TVrNumStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetLeadingZero(Value: Boolean);
begin
  if FLeadingZero <> Value then
  begin
    FLeadingZero := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetAlignment(Value: TVrNumAlignment);
begin
  if FAlignment <> Value then
  begin
    FAlignment := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetAutoSize(Value: Boolean);
begin
  if (FAutoSize <> Value) then
  begin
    FAutoSize := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetZeroBlank(Value: Boolean);
begin
  if FZeroBlank <> Value then
  begin
    FZeroBlank := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomNum.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrCustomNum.Change;
begin
  if Assigned(FOnChange) then FOnChange(self);
end;

procedure TVrCustomNum.RequestAlign;
begin
  inherited;
  if Align = alNone then UpdateControlCanvas;
end;

procedure TVrCustomNum.ChangeSize(NewWidth, NewHeight: Integer);
begin
  if (Align = alNone) then
    if (NewWidth <> Width) or (NewHeight <> Height) then
    begin
      Self.Width := NewWidth;
      Self.Height := NewHeight;
    end;
end;

procedure TVrCustomNum.DrawNum(Num: integer; X, Y: integer);
var
  R, D: TRect;
begin
  with BitmapCanvas do
  begin
    D := Bounds(X, Y, ImageWidth, ImageHeight);
    R := Bounds(Num * ImageWidth, 0, ImageWidth, ImageHeight);
    Brush.Style := bsClear;
    BrushCopy(D, Bitmap, R, clBlack);
  end;
end;

procedure TVrCustomNum.Paint;
var
  I, X, Y, W: Integer;
  S: string;
  Num, Chars: Integer;

  function PadLeft(str: string; Ch: Char; MaxWidth: Integer): string;
  begin
    while Length(str) < MaxWidth do
      str := Ch + str;
    Result := str;
  end;

begin
  ClearBitmapCanvas;

  Num := FValue;
  if Num < 0 then Num := -Num;

  Chars := FDigits;
  S := Format('%d', [Num]);
  if (FValue = 0) and (FZeroBlank) then S := '';
  if FLeadingZero then S := PadLeft(S, '0', Chars)
  else S := PadLeft(S, #32, Chars);

  if (BelowZero) then Inc(Chars);
  W := (Chars * ImageWidth) + (Pred(Chars) * FSpacing);

  if FAutoSize then
    ChangeSize(W, ImageHeight);

  case FAlignment of
    naLeftJustify: X := 0;
    naRightJustify: X := ClientWidth - W;
    else X := (ClientWidth - W) div 2;
  end;
  Y := (Self.Height - ImageHeight) div 2;

  if BelowZero then
  begin
    if (FValue >= 0) then
      DrawNum(11, X, Y) else DrawNum(12, X, Y);
    Inc(X, ImageWidth + FSpacing);
  end;

  for I := 1 to Length(S) do
  begin
    if (S[I] = #32) then DrawNum(10, X, Y)
    else DrawNum(StrToInt(S[I]), X, Y);
    Inc(X, ImageWidth + FSpacing);
  end;

  inherited Paint;
end;


{TVrClock}

constructor TVrClock.Create(AOwner: TCOmponent);
begin
  inherited Create(AOwner);
  Width := 140;
  FHours := 0;
  FMinutes := 0;
  FSeconds := 0;
  FShowSeconds := false;
  FBlink := false;
  FThreaded := True;
  FTimer := TVrTimer.Create(Self);
  FTimer.Enabled := false;
  FTimer.OnTimer := OnTimerEvent;
end;

destructor TVrClock.Destroy;
begin
  FTimer.Free;
  Seperator.Free;
  inherited Destroy;
end;

procedure TVrClock.Loaded;
begin
  inherited Loaded;
  if (FClockType <> ctCustom) and (not Designing) then
    OnTimerEvent(Self);
end;

procedure TVrClock.LoadBitmaps;
begin
  inherited LoadBitmaps;
  if not Assigned(Seperator) then
  begin
    Seperator := TBitmap.Create;
    Seperator.Transparent := true;
  end;
  Seperator.Handle := LoadBitmap(hInstance, ResClockId[Style]);
  FPalette.ToBMP(Seperator, ResColorLow, ResColorHigh);
end;

procedure TVrClock.HoursChanged;
begin
  if Assigned(FOnHoursChanged) then
    FOnHoursChanged(Self, FHours);
end;

procedure TVrClock.MinutesChanged;
begin
  if Assigned(FOnMinutesChanged) then
    FOnMinutesChanged(Self, FMinutes);
end;

procedure TVrClock.SecondsChanged;
begin
  if Assigned(FOnSecondsChanged) then
    FOnSecondsChanged(Self, FSeconds);
end;

procedure TVrClock.SetHours(Value: TVrHoursInt);
begin
  if FHours <> Value then
  begin
    FHours := Value;
    UpdateControlCanvas;
    HoursChanged;
  end;
end;

procedure TVrClock.SetMinutes(Value: TVrMinutesInt);
begin
  if FMinutes <> Value then
  begin
    FMinutes := Value;
    UpdateControlCanvas;
    MinutesChanged;
  end;
end;

procedure TVrClock.SetSeconds(Value: TVrSecondsInt);
begin
  if FSeconds <> Value then
  begin
    FSeconds := Value;
    UpdateControlCanvas;
    SecondsChanged;
  end;
end;

procedure TVrClock.SetActive(Value: Boolean);
begin
  if (Value) and (FClockType = ctCustom) then
    Value := false;
  if (FActive <> Value) then
  begin
    FActive := Value;
    FBlinkVisible := True;
    UpdateControlCanvas;
    if Designing then Exit;
    if FActive then ElapsedTime := Now;
    FTimer.Enabled := FActive;
  end;
end;

procedure TVrClock.SetClockType(Value: TVrClockType);
begin
  if (FClockType <> Value) then
  begin
    FClockType := Value;
    if FClockType <> ctCustom then
    begin
      FHours := 0;
      FMinutes := 0;
      FSeconds := 0;
    end
   else
    if Active then Active := false;
    UpdateControlCanvas;
  end;
end;

procedure TVrClock.SetShowSeconds(Value: Boolean);
begin
  if FShowSeconds <> Value then
  begin
    FShowSeconds := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrClock.SetBlink(Value: Boolean);
begin
  if FBlink <> Value then
  begin
    FBlink := Value;
    FBlinkVisible := True;
    UpdateControlCanvas;
  end;
end;

procedure TVrClock.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;

procedure TVrClock.OnTimerEvent(Sender: TObject);
var
  H, M, S, S100: Word;
  Ho, Mo, So: Word;
  T: TDateTime;
  SecsChanged: Boolean;
begin
  //store old values
  Ho := FHours;
  Mo := FMinutes;
  So := FSeconds;

  case FClockType of
    ctRealTime: T := Now;
    ctElapsed: T := Now - ElapsedTime;
    else
      T := 0; //This should never occure
  end;

  DecodeTime(T, H, M, S, S100);
  FHours := H;
  FMinutes := M;
  FSeconds := S;
  FBlinkVisible := not FBlinkVisible;

  SecsChanged := (FShowSeconds) and (So <> FSeconds);
  if (SecsChanged) or (FBlink) or (FMinutes <> Mo) then
    UpdateControlCanvas;

  if (FHours <> Ho) then HoursChanged;
  if (FMinutes <> Mo) then MinutesChanged;
  if (FSeconds <> So) then SecondsChanged;
end;

procedure TVrClock.Paint;
var
  I, X, Y, W: Integer;
  NumDigits: Integer;
  NumSpacing: Integer;
  S: string;
begin
  ClearBitmapCanvas;

  NumDigits := 4;
  NumSpacing := 4;
  if FShowSeconds then
  begin
    Inc(NumDigits, 2);
    Inc(NumSpacing, 3);
  end;

  W := (NumDigits * ImageWidth);
  W := W + (Seperator.Width * (ord(FShowSeconds) + 1));
  W := W + (NumSpacing * FSpacing);

  if FAutoSize then
    ChangeSize(W, ImageHeight);

  X := (Width - W) div 2;
  Y := (Self.Height - ImageHeight) div 2;

  S := Format('%.2d:%.2d', [FHours, FMinutes]);
  if FShowSeconds then
    S := S + Format(':%.2d', [FSeconds]);

  for I := 1 to Length(S) do
  begin
    if (S[I] = ':') then
    begin
      if (FClockType = ctCustom) or
         (not FBlink) or (FBlink and FBlinkVisible) then
        BitmapCanvas.Draw(X, Y, Seperator);
      Inc(X, Seperator.Width + FSpacing);
    end
   else
    begin
      DrawNum(StrToInt(S[I]), X, Y);
      Inc(X, ImageWidth + FSpacing);
    end;
  end;

  with inherited Canvas do
    Draw(0, 0, BitmapImage);
end;


end.
