{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrMeter;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, VrControls, VrSysUtils;

type
  TVrMeter = class;

  TVrMeterScale = class(TVrPersistent)
  private
    FColor1: TColor;
    FColor2: TColor;
    FColor3: TColor;
    FEnlarge: Integer;
    FPercent1: Integer;
    FPercent2: Integer;
    FTicks: Integer;
    FHeightMax: Integer;
    FHeightMin: Integer;
    FVisible: Boolean;
    Owner: TVrMeter;
    procedure SetColor1(Value: TColor);
    procedure SetColor2(Value: TColor);
    procedure SetColor3(Value: TColor);
    procedure SetEnlarge(Value: Integer);
    procedure SetPercent1(Value: Integer);
    procedure SetPercent2(Value: Integer);
    procedure SetTicks(Value: Integer);
    procedure SetHeightMax(Value: Integer);
    procedure SetHeightMin(Value: Integer);
    procedure SetVisible(Value: Boolean);
  public
    constructor Create;
  published
    property Color1: TColor read FColor1 write SetColor1 default clGreen;
    property Color2: TColor read FColor2 write SetColor2 default clYellow;
    property Color3: TColor read FColor3 write SetColor3 default clRed;
    property Enlarge: Integer read FEnlarge write SetEnlarge default 5;
    property Percent1: Integer read FPercent1 write SetPercent1 default 61;
    property Percent2: Integer read FPercent2 write SetPercent2 default 25;
    property Ticks: Integer read FTicks write SetTicks default 60;
    property HeightMax: Integer read FHeightMax write SetHeightMax default 8;
    property HeightMin: Integer read FHeightMin write SetHeightMin default 5;
    property Visible: Boolean read FVisible write SetVisible default True;
  end;

  TVrMeter = class(TVrGraphicImageControl)
  private
    FAngle: Integer;
    FScale: TVrMeterScale;
    FMinValue: Integer;
    FMaxValue: Integer;
    FPosition: Integer;
    FNeedleColor: TColor;
    FNeedleWidth: Integer;
    FSpacing: Integer;
    FLabels: Integer;
    FLabelOffsetX: Integer;
    FLabelOffsetY: Integer;
    FBevel: TVrBevel;
    FBackImage: TBitmap;
    FCenter: TPoint;
    FRadius: Integer;
    procedure SetAngle(Value: Integer);
    procedure SetMinValue(Value: Integer);
    procedure SetMaxValue(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetNeedleColor(Value: TColor);
    procedure SetNeedleWidth(Value: Integer);
    procedure SetBevel(Value: TVrBevel);
    procedure SetSpacing(Value: Integer);
    procedure SetLabels(Value: Integer);
    procedure SetLabelOffsetX(Value: Integer);
    procedure SetLabelOffsetY(Value: Integer);
    procedure SetBackImage(Value: TBitmap);
    procedure BevelChanged(Sender: TObject);
    procedure ScaleChanged(Sender: TObject);
    procedure BackImageChanged(Sender: TObject);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
  protected
    procedure DrawScale;
    procedure DrawNeedle;
    procedure DrawLabels;
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
  published
    property MaxValue: Integer read FMaxValue write SetMaxValue default 100;
    property MinValue: Integer read FMinValue write SetMinValue default 0;
    property Position: Integer read FPosition write SetPosition default 0;
    property Angle: Integer read FAngle write SetAngle default 40;
    property Scale: TVrMeterScale read FScale write FScale;
    property NeedleColor: TColor read FNeedleColor write SetNeedleColor default clSilver;
    property NeedleWidth: Integer read FNeedleWidth write SetNeedleWidth default 1;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Spacing: Integer read FSpacing write SetSpacing default 20;
    property Labels: Integer read FLabels write SetLabels default 10;
    property LabelOffsetX: Integer read FLabelOffsetX write SetLabelOffsetX default 15;
    property LabelOffsetY: Integer read FLabelOffsetY write SetLabelOffsetY default 10;
    property BackImage: TBitmap read FBackImage write SetBackImage;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Caption;
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Font;
    property Hint;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property ParentFont;
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

function DegToRad(Degrees: Extended): Extended;
begin
  Result := Degrees * (PI / 180);
end;

{ TVrMeterScale }

constructor TVrMeterScale.Create;
begin
  inherited Create;
  FColor1 := clGreen;
  FColor2 := clYellow;
  FColor3 := clRed;
  FEnlarge := 5;
  FPercent1 := 60;
  FPercent2 := 25;
  FTicks := 61;
  FHeightMax := 8;
  FHeightMin := 5;
  FVisible := True
end;

procedure TVrMeterScale.SetColor1(Value: TColor);
begin
  if FColor1 <> Value then
  begin
    FColor1 := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetColor2(Value: TColor);
begin
  if FColor2 <> Value then
  begin
    FColor2 := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetColor3(Value: TColor);
begin
  if FColor3 <> Value then
  begin
    FColor3 := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetEnlarge(Value: Integer);
begin
  if FEnlarge <> Value then
  begin
    FEnlarge := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetPercent1(Value: Integer);
begin
  if (FPercent1 <> Value) then
  begin
    if not Owner.Loading then
      if Value + Percent2 > 100 then Value := 100 - Percent2;
    FPercent1 := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetPercent2(Value: Integer);
begin
  if (FPercent2 <> Value) and (Value + Percent1 <= 100) then
  begin
    if not Owner.Loading then
      if Value + Percent1 > 100 then Value := 100 - Percent1;
    FPercent2 := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetTicks(Value: Integer);
begin
  if FTicks <> Value then
  begin
    FTicks := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetHeightMax(Value: Integer);
begin
  if FHeightMax <> Value then
  begin
    FHeightMax := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetHeightMin(Value: Integer);
begin
  if FHeightMin <> Value then
  begin
    FHeightMin := Value;
    Changed;
  end;
end;

procedure TVrMeterScale.SetVisible(Value: Boolean);
begin
  if FVisible <> Value then
  begin
    FVisible := Value;
    Changed;
  end;
end;

{ TVrMeter }

constructor TVrMeter.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 240;
  Height := 115;
  Color := clBlack;
  ParentColor := false;
  with Font do
  begin
    Name := 'Arial';
    Size := 8;
    Color := clSilver;
  end;
  FAngle := 40;
  FMinValue := 0;
  FMaxValue := 100;
  FPosition := 0;
  FNeedleColor := clSilver;
  FNeedleWidth := 1;
  FSpacing := 20;
  FLabels := 10;
  FLabelOffsetX := 15;
  FLabelOffsetY := 10;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  FScale := TVrMeterScale.Create;
  FScale.Owner := Self;
  FScale.OnChange := ScaleChanged;
  FBackImage := TBitmap.Create;
  FBackImage.OnChange := BackImageChanged;
end;

destructor TVrMeter.Destroy;
begin
  FScale.Free;
  FBevel.Free;
  FBackImage.Free;
  inherited Destroy;
end;

procedure TVrMeter.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  FRadius := AHeight - 10;
  FCenter.X := AWidth div 2;
  FCenter.Y := AHeight + FSpacing;
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
end;

procedure TVrMeter.DrawScale;
var
  sX, sY, eX, eY: Integer;
  I, sAngle, eAngle: Integer;
  Ticks, TickHeight, Enlarge: Integer;
  Point, Point1, Point2: Integer;
  Offset, Step: Extended;
begin
  Ticks := Scale.Ticks;
  Enlarge := Scale.Enlarge;

  sAngle := 270 + FAngle;
  eAngle := sAngle + 180 - FAngle * 2;
  Step := (eAngle - sAngle)/Ticks;

  Point := 0;
  Point1 := SolveForX(Scale.Percent1, Scale.Ticks);
  Point2 := Point1 + SolveForX(Scale.Percent2, Scale.Ticks);

  with BitmapCanvas do
  begin
    Pen.Mode := pmCOPY;
    Pen.Width := 1;
    for I := 0 to Ticks - 1 do
    begin
      Inc(Point);
      if Point <= Point1 then Pen.Color := Scale.Color1
      else if Point <= Point2 then Pen.Color := Scale.Color2
      else Pen.Color := Scale.Color3;
      if Enlarge = Scale.Enlarge then TickHeight := Scale.HeightMax
      else TickHeight := Scale.HeightMin;
      Offset := DegToRad(sAngle + I * Step);
      sX := FCenter.X + Trunc(Sin(Offset) * (FRadius - Scale.HeightMin));
      sY := FCenter.Y + Trunc(Cos(Offset) * (FRadius - Scale.HeightMin));

      eX := FCenter.X + Trunc(Sin(Offset) *
            (FRadius + TickHeight - Scale.HeightMin));
      eY := FCenter.Y + Trunc(Cos(Offset) *
            (FRadius + TickHeight - Scale.HeightMin));
      MoveTo(sX, FCenter.Y * 2 - sY);
      LineTo(eX, FCenter.Y * 2 - eY);
      if Enlarge < Scale.Enlarge then Inc(Enlarge) else Enlarge := 1;
    end;
  end;
end;

procedure TVrMeter.DrawNeedle;
var
  X, Y, Ticks: Integer;
  P: Integer;
  Offset, Step: Extended;
  sAngle, eAngle: Integer;
begin
  Ticks := Scale.Ticks;
  sAngle := 270 + FAngle;
  eAngle := sAngle + 180 - FAngle * 2;
  Step := (eAngle - sAngle)/Ticks;
  P := Trunc((Position / (MaxValue - MinValue)) * Pred(Ticks));

  with BitmapCanvas do
  begin
    Pen.Mode := pmCOPY;
    Pen.Color := FNeedleColor;
    Pen.Width := FNeedleWidth;
    Offset := DegToRad(sAngle + P * Step);
    X := FCenter.X + Trunc(Sin(Offset) * FRadius);
    Y := FCenter.Y + Trunc(Cos(Offset) * FRadius);
    MoveTo(FCenter.X, FCenter.Y);
    LineTo(X, FCenter.Y * 2 - Y);
  end;
end;

procedure TVrMeter.DrawLabels;
var
  X, Y, Ticks, I, LabelCnt, LC, LV: Integer;
  str: string;
  Offset, Step, BaseValue: Extended;
  sAngle, eAngle, Adjust: Integer;
  TextSize: TSize;
begin
  Ticks := Scale.Ticks;
  sAngle := 270 + FAngle;
  eAngle := sAngle + 180 - FAngle * 2;
  Step := (eAngle - sAngle) / Scale.Ticks;
  BaseValue := (FMaxValue - FMinValue) / Labels;

  LabelCnt := (Scale.Ticks div Labels)-1;
  LC := 0;
  LV := -1;
  with BitmapCanvas do
  begin
    Font.Assign(Self.Font);
    Brush.Style := bsClear;
    for I := 0 to Ticks - 1 do
    begin
      if LC = 0 then
      begin
        Inc(LV);
        str := IntToStr(FMinValue + Round(BaseValue * LV));
        TextSize := TextExtent(str);
        Offset := DegToRad(sAngle + I * Step);
        X := FCenter.X + Trunc(Sin(Offset) *
             (FRadius + Scale.HeightMax - Scale.HeightMin + LabelOffsetX));
        Y := FCenter.Y + Trunc(Cos(Offset) *
             (FRadius + Scale.HeightMax - Scale.HeightMin + LabelOffsetY));

        Adjust := X - (TextSize.cX div 2);
        Y := Y + (TextSize.cY div 2);
        TextOut(Adjust, FCenter.Y * 2 - Y, str);
      end;
      if LC = 0 then LC := LabelCnt else Dec(LC);
    end;
  end;
end;

procedure TVrMeter.Paint;
var
  X: Integer;
  BevelRect: TRect;
begin
  ClearBitmapCanvas;

  if not FBackImage.Empty then
    BitmapCanvas.StretchDraw(ClientRect, FBackImage);

  if Scale.Visible then DrawScale;
  if Labels > 0 then DrawLabels;
  DrawNeedle;

  BevelRect := ClientRect;
  FBevel.GetVisibleArea(BevelRect);
  with BitmapCanvas do
  begin
    Font.Assign(Self.Font);
    X := FCenter.X - (TextWidth(Caption) div 2);
    TextOut(X, BevelRect.Bottom - 10 - TextHeight(Caption), Caption);
  end;

  BevelRect := ClientRect;
  FBevel.Paint(BitmapCanvas, BevelRect);
  inherited Paint;
end;

procedure TVrMeter.ScaleChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrMeter.SetAngle(Value: Integer);
begin
  if FAngle <> Value then
  begin
    FAngle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetMinValue(Value: Integer);
begin
  if (FMinValue <> Value) and (Value < FMaxValue) then
  begin
    FMinValue := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetMaxValue(Value: Integer);
begin
  if (FMaxValue <> Value) and (Value > FMinValue) then
  begin
    FMaxValue := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetPosition(Value: Integer);
begin
  AdjustRange(Value, FMinValue, FMaxValue);
  if (FPosition <> Value) then
  begin
    FPosition := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetNeedleColor(Value: TColor);
begin
  if FNeedleColor <> Value then
  begin
    FNeedleColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetNeedleWidth(Value: Integer);
begin
  if FNeedleWidth <> Value then
  begin
    FNeedleWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrMeter.BevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrMeter.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    FCenter.Y := Height + Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetLabels(Value: Integer);
begin
  if FLabels <> Value then
  begin
    FLabels := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetLabelOffsetX(Value: Integer);
begin
  if FLabelOffsetX <> Value then
  begin
    FLabelOffsetX := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.SetLabelOffsetY(Value: Integer);
begin
  if FLabelOffsetY <> Value then
  begin
    FLabelOffsetY := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMeter.CMTextChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrMeter.BackImageChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrMeter.SetBackImage(Value: TBitmap);
begin
  FBackImage.Assign(Value);
end;



end.
