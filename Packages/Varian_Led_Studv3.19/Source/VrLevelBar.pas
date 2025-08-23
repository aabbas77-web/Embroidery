{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrLevelBar;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrLevelBar = class(TVrGraphicImageControl)
  private
    FMinValue: Integer;
    FMaxValue: Integer;
    FPosition: Integer;
    FPercent1: TVrPercentInt;
    FPercent2: TVrPercentInt;
    FPalette1: TVrPalette;
    FPalette2: TVrPalette;
    FPalette3: TVrPalette;
    FBevel: TVrBevel;
    FOrientation: TVrOrientation;
    FSpacing: Integer;
    FTickHeight: Integer;
    FStyle: TVrProgressStyle;
    FOnChange: TNotifyEvent;
    FViewPort: TRect;
    FStep, FTicks: Integer;
    function GetPercentDone: Longint;
    procedure SetMinValue(Value: Integer);
    procedure SetMaxValue(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetPalette1(Value: TVrPalette);
    procedure SetPalette2(Value: TVrPalette);
    procedure SetPalette3(Value: TVrPalette);
    procedure SetBevel(Value: TVrBevel);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetSpacing(Value: Integer);
    procedure SetTickHeight(Value: Integer);
    procedure SetPercent1(Value: TVrPercentInt);
    procedure SetPercent2(Value: TVrPercentInt);
    procedure SetStyle(Value: TVrProgressStyle);
    procedure DrawHori;
    procedure DrawVert;
    procedure PaletteModified(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
  protected
    procedure CalcPaintParams;
    procedure Paint; override;
    procedure Changed; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property PercentDone: Longint read GetPercentDone;
  published
    property MaxValue: Integer read FMaxValue write SetMaxValue default 100;
    property MinValue: Integer read FMinValue write SetMinValue default 0;
    property Position: Integer read FPosition write SetPosition default 0;
    property Percent1: TVrPercentInt read FPercent1 write SetPercent1 default 60;
    property Percent2: TVrPercentInt read FPercent2 write SetPercent2 default 25;
    property Palette1: TVrPalette read FPalette1 write SetPalette1;
    property Palette2: TVrPalette read FPalette2 write SetPalette2;
    property Palette3: TVrPalette read FPalette3 write SetPalette3;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voVertical;
    property Spacing: Integer read FSpacing write SetSpacing default 1;
    property TickHeight: Integer read FTickHeight write SetTickHeight default 1;
    property Style: TVrProgressStyle read FStyle write SetStyle default psBottomLeft;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
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


constructor TVrLevelBar.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 20;
  Height := 170;
  ParentColor := false;
  Color := clBlack;
  FOrientation := voVertical;
  FSpacing := 1;
  FTickHeight := 1;
  FMinValue := 0;
  FMaxValue := 100;
  FPosition := 0;
  FPercent1 := 60;
  FPercent2 := 25;
  FStyle := psBottomLeft;
  FPalette1 := TVrPalette.Create;
  FPalette1.OnChange := PaletteModified;
  FPalette2 := TVrPalette.Create;
  with FPalette2 do
  begin
    Low := clOlive;
    High := clYellow;
    OnChange := PaletteModified;
  end;
  FPalette3 := TVrPalette.Create;
  with FPalette3 do
  begin
    Low := clMaroon;
    High := clRed;
    OnChange := PaletteModified;
  end;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
end;

destructor TVrLevelBar.Destroy;
begin
  FBevel.Free;
  FPalette1.Free;
  FPalette2.Free;
  FPalette3.Free;
  inherited Destroy;
end;

procedure TVrLevelBar.PaletteModified(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrLevelBar.BevelChanged(Sender: TObject);
var
  R: TRect;
begin
  if not Loading then
  begin
    R := ClientRect;
    FBevel.GetVisibleArea(R);
    InflateRect(FViewPort, R.Left, R.Top);
    BoundsRect := Bounds(Left, Top, WidthOf(FViewPort),
      HeightOf(FViewPort));
  end;
  UpdateControlCanvas;
end;

procedure TVrLevelBar.Changed;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

function TVrLevelBar.GetPercentDone: Longint;
begin
  Result := SolveForY(FPosition - FMinValue, FMaxValue - FMinValue);
end;

procedure TVrLevelBar.DrawHori;
var
  R: TRect;
  X, Y, I, Offset: Integer;
  TicksOn, TicksOff: Integer;
  Point, Point1, Point2: Integer;
begin
  TicksOn := SolveForX(PercentDone, FTicks);
  TicksOff := FTicks - TicksOn;

  Point1 := SolveForX(Percent1, FTicks);
  Point2 := Point1 + SolveForX(Percent2, FTicks);

  Y := FViewPort.Top;
  if FStyle = psBottomLeft then
  begin
    X := FViewPort.Left;
    Offset := FStep;
  end
  else
  begin
    X := FViewPort.Right - FTickHeight;
    Offset := -FStep;
  end;

  R := Bounds(X, Y, FTickHeight, HeightOf(FViewPort));

  Point := 0;
  for I := 1 to TicksOn do
  begin
    Inc(Point);
    if Point <= Point1 then BitmapCanvas.Brush.Color := FPalette1[1]
    else if Point <= Point2 then BitmapCanvas.Brush.Color := FPalette2[1]
    else BitmapCanvas.Brush.Color := FPalette3[1];
    BitmapCanvas.FillRect(R);
    OffsetRect(R, Offset, 0);
  end;

  for I := 1 to TicksOff do
  begin
    Inc(Point);
    if Point <= Point1 then BitmapCanvas.Brush.Color := FPalette1[0]
    else if Point <= Point2 then BitmapCanvas.Brush.Color := FPalette2[0]
    else BitmapCanvas.Brush.Color := FPalette3[0];
    BitmapCanvas.FillRect(R);
    OffsetRect(R, Offset, 0);
  end;
end;

procedure TVrLevelBar.DrawVert;
var
  R: TRect;
  X, Y, I, Offset: Integer;
  TicksOn, TicksOff: Integer;
  Point, Point1, Point2: Integer;
begin
  TicksOn := SolveForX(PercentDone, FTicks);
  TicksOff := FTicks - TicksOn;

  Point1 := SolveForX(Percent1, FTicks);
  Point2 := Point1 + SolveForX(Percent2, FTicks);

  X := FViewPort.Left;
  if FStyle = psBottomLeft then
  begin
    Y := FViewPort.Top;
    Offset := FStep;
  end
  else
  begin
    Y := FViewPort.Bottom - FTickHeight;
    Offset := -FStep;
  end;

  R := Bounds(X, Y, WidthOf(FViewPort), FTickHeight);

  Point := FTicks;
  for I := 1 to TicksOff do
  begin
    Dec(Point);
    if Point < Point1 then BitmapCanvas.Brush.Color := FPalette1[0]
    else if Point < Point2 then BitmapCanvas.Brush.Color := FPalette2[0]
    else BitmapCanvas.Brush.Color := FPalette3[0];
    BitmapCanvas.FillRect(R);
    OffsetRect(R, 0, Offset);
  end;

  for I := 1 to TicksOn do
  begin
    Dec(Point);
    if Point < Point1 then BitmapCanvas.Brush.Color := FPalette1[1]
    else if Point < Point2 then BitmapCanvas.Brush.Color := FPalette2[1]
    else BitmapCanvas.Brush.Color := FPalette3[1];
    BitmapCanvas.FillRect(R);
    OffsetRect(R, 0, Offset);
  end;
end;

procedure TVrLevelBar.Paint;
var
  R: TRect;
begin
  CalcPaintParams;
  ClearBitmapCanvas;

  R := ClientRect;
  FBevel.Paint(BitmapCanvas, R);

  case Orientation of
    voVertical: DrawVert;
    voHorizontal: DrawHori;
  end;

  inherited Paint;
end;

procedure TVrLevelBar.CalcPaintParams;
begin
  FStep := FTickHeight + FSpacing;
  FViewPort := ClientRect;
  FBevel.GetVisibleArea(FViewPort);
  case Orientation of
    voVertical:
      begin
        FTicks := (HeightOf(FViewPort) + FSpacing) div FStep;
        Height := (FViewPort.Top * 2) + (FTicks * FStep) - FSpacing;
      end;
    voHorizontal:
      begin
        FTicks := (WidthOf(FViewPort) + FSpacing) div FStep;
        Width := (FViewPort.Left * 2) + (FTicks * FStep) - FSpacing;
      end;
  end;
end;

procedure TVrLevelBar.SetPalette1(Value: TVrPalette);
begin
  FPalette1.Assign(Value);
end;

procedure TVrLevelBar.SetPalette2(Value: TVrPalette);
begin
  FPalette2.Assign(Value);
end;

procedure TVrLevelBar.SetPalette3(Value: TVrPalette);
begin
  FPalette3.Assign(Value);
end;

procedure TVrLevelBar.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if not Loading then
      BoundsRect := Bounds(Left, Top, Height, Width);
    UpdateControlCanvas;
  end;
end;

procedure TVrLevelBar.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrLevelBar.SetTickHeight(Value: Integer);
begin
  if (FTickHeight <> Value) and (Value > 0) then
  begin
    FTickHeight := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLevelBar.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLevelBar.SetMinValue(Value: Integer);
begin
  if (FMinValue <> Value) and (Value < FMaxValue) then
  begin
    FMinValue := Value;
    if FPosition < FMinValue then
      Position := FMinValue else UpdateControlCanvas;
  end;
end;

procedure TVrLevelBar.SetMaxValue(Value: Integer);
begin
  if (FMaxValue <> Value) and (Value > FMinValue) then
  begin
    FMaxValue := Value;
    if FPosition > FMaxValue then
      Position := FMaxValue else UpdateControlCanvas;
  end;
end;

procedure TVrLevelBar.SetPosition(Value: Integer);
begin
  if Value < FMinValue then Value := FMinValue;
  if Value > FMaxValue then Value := FMaxValue;
  if FPosition <> Value then
  begin
    FPosition := Value;
    UpdateControlCanvas;
    Changed;
  end;
end;

procedure TVrLevelBar.SetPercent1(Value: TVrPercentInt);
begin
  if (FPercent1 <> Value) then
  begin
    if not Loading then
      if Value + Percent2 > 100 then Value := 100 - Percent2;
    FPercent1 := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLevelBar.SetPercent2(Value: TVrPercentInt);
begin
  if (FPercent2 <> Value) and (Value + Percent1 <= 100) then
  begin
    if not Loading then
      if Value + Percent1 > 100 then Value := 100 - Percent1;
    FPercent2 := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLevelBar.SetStyle(Value: TVrProgressStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;



end.
