{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrAnalog;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Forms, Graphics, Controls,
  VrTypes, VrClasses, VrControls, VrSysUtils, VrThreads;

type
  TVrAnalogClock = class(TVrGraphicImageControl)
  private
    FActive: Boolean;
    FSecondsIndicator: Boolean;
    FHourMarks: Boolean;
    FHours, FMinutes, FSeconds: Word;
    FGlyph: TBitmap;
    FHandsColor: TColor;
    FSecHandColor: TColor;
    FTickColor: TColor;
    FTickWidth: Integer;
    FTickOutline: TColor;
    FThreaded: Boolean;
    FOnHoursChanged: TVrHoursChangeEvent;
    FOnMinutesChanged: TVrMinutesChangeEvent;
    FOnSecondsChanged: TVrSecondsChangeEvent;
    FTimer: TVrTimer;
    procedure SetActive(Value: Boolean);
    procedure SetSecondsIndicator(Value: Boolean);
    procedure SetHourMarks(Value: Boolean);
    procedure SetGlyph(Value: TBitmap);
    procedure SetHandsColor(Value: TColor);
    procedure SetSecHandColor(Value: TColor);
    procedure SetTickColor(Value: TColor);
    procedure SetTickWidth(Value: Integer);
    procedure SetTickOutline(Value: TColor);
    procedure SetThreaded(Value: Boolean);
    procedure DrawHand(XCenter, YCenter, Radius, BackRadius: Integer; Angle: Double);
    procedure OnTimerEvent(Sender: TObject);
  protected
    procedure Paint; override;
    procedure HoursChanged; virtual;
    procedure MinutesChanged; virtual;
    procedure SecondsChanged; virtual;
  public
    constructor Create (AOwner: TComponent); override;
    destructor Destroy; override;
    property Hours: Word read FHours;
    property Minutes: Word read FMinutes;
    property Seconds: Word read FSeconds;
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Active: Boolean read FActive write SetActive default false;
    property SecondsIndicator: Boolean read FSecondsIndicator write SetSecondsIndicator default True;
    property HourMarks: Boolean read FHourMarks write SetHourMarks default True;
    property Glyph: TBitmap read FGlyph write SetGlyph;
    property HandsColor: TColor read FHandsColor write SetHandsColor default clLime;
    property SecHandColor: TColor read FSecHandColor write SetSecHandColor default clLime;
    property TickColor: TColor read FTickColor write SetTickColor default clLime;
    property TickWidth: Integer read FTickWidth write SetTickWidth default 2;
    property TickOutline: TColor read FTickOutline write SetTickOutline default clGreen;
    property OnHoursChanged: TVrHoursChangeEvent read FOnHoursChanged write FOnHoursChanged;
    property OnMinutesChanged: TVrMinutesChangeEvent read FOnMinutesChanged write FOnMinutesChanged;
    property OnSecondsChanged: TVrSecondsChangeEvent read FOnSecondsChanged write FOnSecondsChanged;
    property Transparent default false;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color default clBlack;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
    property ParentColor default false;
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

{TVrAnalogClock}

constructor TVrAnalogClock.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csSetCaption];
  Width := 90;
  Height := 90;
  ParentColor := false;
  Color := clBlack;
  Transparent := false;
  FSecondsIndicator := True;
  FHourMarks := True;
  FActive := false;
  FHandsColor := clLime;
  FSecHandColor := clLime;
  FTickColor := clLime;
  FTickWidth := 2;
  FTickOutline := clGreen;
  FGlyph := TBitmap.Create;
  FThreaded := True;
  FTimer := TVrTimer.Create(Self);
  FTimer.Enabled := false;
  FTimer.OnTimer := OnTimerEvent;
  OnTimerEvent(self);
end;

destructor TVrAnalogClock.Destroy;
begin
  FTimer.Free;
  FGlyph.Free;
  inherited Destroy;
end;

procedure TVrAnalogClock.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    if not Designing then
      FTimer.Enabled := Value;
  end;
end;

procedure TVrAnalogClock.SetSecondsIndicator(Value: Boolean);
begin
  if FSecondsIndicator <> Value then
  begin
    FSecondsIndicator := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnalogClock.SetHourMarks(Value: Boolean);
begin
  if FHourMarks <> Value then
  begin
    FHourMarks := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnalogClock.SetHandsColor(Value: TColor);
begin
  if FHandsColor <> Value then
  begin
    FHandsColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnalogClock.SetSecHandColor(Value: TColor);
begin
  if FSecHandColor <> Value then
  begin
    FSecHandColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnalogClock.SetTickColor(Value: TColor);
begin
  if FTickColor <> Value then
  begin
    FTickColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnalogClock.SetTickWidth(Value: Integer);
begin
  if (FTickWidth <> Value) and (Value > 0) then
  begin
    FTickWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnalogClock.SetTickOutline(Value: TColor);
begin
  if FTickOutline <> Value then
  begin
    FTickOutline := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnalogClock.SetGlyph(Value: TBitmap);
begin
  FGlyph.Assign(Value);
  UpdateControlCanvas;
end;

procedure TVrAnalogClock.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;

procedure TVrAnalogClock.HoursChanged;
begin
  if Assigned(FOnHoursChanged) then
    FOnHoursChanged(Self, FHours);
end;

procedure TVrAnalogClock.MinutesChanged;
begin
  if Assigned(FOnMinutesChanged) then
    FOnMinutesChanged(Self, FMinutes);
end;

procedure TVrAnalogClock.SecondsChanged;
begin
  if Assigned(FOnSecondsChanged) then
    FOnSecondsChanged(Self, FSeconds);
end;

procedure TVrAnalogClock.OnTimerEvent(Sender: TObject);
var
  S100: Word;
  Ho, Mo, So: Word;
  SecsChanged: Boolean;
begin
  //store old values
  Ho := FHours;
  Mo := FMinutes;
  So := FSeconds;

  DecodeTime(Time, FHours, FMinutes, FSeconds, S100);

  SecsChanged := (FSecondsIndicator) and (So <> FSeconds);
  if (SecsChanged) or (FMinutes <> Mo) then
    UpdateControlCanvas;

  if (FHours <> Ho) then HoursChanged;
  if (FMinutes <> Mo) then MinutesChanged;
  if (FSeconds <> So) then SecondsChanged;
end;

procedure TVrAnalogClock.Paint;
var
  Angle: Double;
  I, X, Y, Radius: Integer;
  XCenter, YCenter: Integer;
  R: TRect;
begin
  ClearBitmapCanvas;

  if not FGlyph.Empty then
  begin
    if Transparent then BitmapCanvas.Brush.Style := bsClear
    else BitmapCanvas.Brush.Style := bsSolid;
    BitmapCanvas.BrushCopy(ClientRect, FGlyph, BitmapRect(FGlyph), Self.Color);
  end;

  XCenter := Width div 2;
  YCenter := Height div 2;
  if XCenter > YCenter then
    Radius := YCenter - 10
  else Radius := XCenter - 10;

  with BitmapCanvas do
  begin
    Pen.Color := TickOutline;
    Pen.Style := psSolid;
    Brush.Color := TickColor;
    Brush.Style := bsSolid;
  end;

  if FHourMarks then
    for I := 0 to 11 do
    begin
      Angle := 2 * Pi * (I + 9) / 12;
      X := XCenter - Round (Radius * Cos(Angle));
      Y := YCenter - Round (Radius * Sin(Angle));

      with BitmapCanvas do
      begin
        R := Rect(X - TickWidth, Y - TickWidth, X + TickWidth, Y + TickWidth);
        Ellipse(R.Left, R.Top, R.Right, R.Bottom);
      end;
    end;

  BitmapCanvas.Pen.Color := FHandsColor;
  Angle := 2 * Pi * (FMinutes + 45) / 60;
  DrawHand (XCenter, YCenter,
    Radius * 90 div 100, 0, Angle);

  Angle := 2 * Pi * (FHours + 9 + FMinutes / 60) / 12;
  DrawHand (XCenter, YCenter,
    Radius * 70 div 100, 0, Angle);

  if FSecondsIndicator then
  begin
    BitmapCanvas.Pen.Color := FSecHandColor;
    Angle := 2 * Pi * (FSeconds + 45) / 60;
    DrawHand (XCenter, YCenter, Radius,
      Radius * 30 div 100, Angle);
  end;

  inherited Paint;
end;

procedure TVrAnalogClock.DrawHand (XCenter, YCenter,
  Radius, BackRadius: Integer; Angle: Double);
begin
  BitmapCanvas.MoveTo(
    XCenter - Round (BackRadius * Cos (Angle)),
    YCenter - Round (BackRadius * Sin (Angle)));
  BitmapCanvas.LineTo(
    XCenter + Round (Radius * Cos (Angle)),
    YCenter + Round (Radius * Sin (Angle)));
end;



end.
