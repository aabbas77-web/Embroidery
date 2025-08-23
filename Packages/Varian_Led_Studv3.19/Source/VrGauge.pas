{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrGauge;

{$I VRLIB.INC}

interface

uses
  Windows, Forms, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrGaugeImages = array[0..1] of TBitmap;
  TVrGauge = class(TVrGraphicImageControl)
  private
    FMax: Integer;
    FMin: Integer;
    FPosition: Integer;
    FOrientation: TVrOrientation;
    FPalette: TVrPalette;
    FTickHeight: Integer;
    FSpacing: Integer;
    FSolidFill: Boolean;
    FBevel: TVrBevel;
    FStyle: TVrProgressStyle;
    FActiveClick: Boolean;
    FOnChange: TNotifyEvent;
    FViewPort: TRect;
    Step, Ticks: Integer;
    FImages: TVrGaugeImages;
    OrgSize: TPoint;
    function GetPercentDone: Longint;
    procedure SetMax(Value: Integer);
    procedure SetMin(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetTickHeight(Value: Integer);
    procedure SetSpacing(Value: Integer);
    procedure SetSolidFill(Value: Boolean);
    procedure SetStyle(Value: TVrProgressStyle);
    procedure SetPalette(Value: TVrPalette);
    procedure SetBevel(Value: TVrBevel);
    procedure DrawHori;
    procedure DrawVert;
    procedure PaletteModified(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
  protected
    procedure CreateBitmaps;
    procedure DestroyBitmaps;
    procedure CalcPaintParams;
    procedure Paint; override;
    procedure Change; dynamic;
    procedure MoveTo(X, Y: Integer);
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property PercentDone: Longint read GetPercentDone;
  published
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property Position: Integer read FPosition write SetPosition default 0;
    property Palette: TVrPalette read FPalette write SetPalette;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voVertical;
    property TickHeight: Integer read FTickHeight write SetTickHeight default 1;
    property Spacing: Integer read FSpacing write SetSpacing default 1;
    property SolidFill: Boolean read FSolidFill write SetSolidFill default false;
    property Style: TVrProgressStyle read FStyle write SetStyle default psBottomLeft;
    property ActiveClick: Boolean read FActiveClick write FActiveClick default false;
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


{ TVrGauge }

constructor TVrGauge.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 30;
  Height := 170;
  ParentColor := false;
  Color := clBlack;
  FMax := 100;
  FMin := 0;
  FPosition := 0;
  FOrientation := voVertical;
  FTickHeight := 1;
  FSpacing := 1;
  FSolidFill := false;
  FStyle := psBottomLeft;
  FActiveClick := false;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  AllocateBitmaps(FImages);
end;

destructor TVrGauge.Destroy;
begin
  FBevel.Free;
  DestroyBitmaps;
  inherited Destroy;
end;

procedure TVrGauge.CreateBitmaps;
var
  R: TRect;
begin
  R := ClientRect;
  FBevel.GetVisibleArea(R);

  with FImages[0] do
  begin
    case FOrientation of
      voVertical:
        begin
          Height := FTickHeight;
          Width := WidthOf(R);
        end;
      voHorizontal:
        begin
          Height := HeightOf(R);
          Width := FTickHeight;
        end;
    end; //case

    if (FTickHeight > 1) and (not FSolidFill) then
      Canvas.Brush.BitMap := CreateDitherPattern(FPalette.Low, clBlack)
    else
      Canvas.Brush.Color := FPalette.Low;
    try
      R := Bounds(0, 0, Width, Height);
      Canvas.FillRect(R);
    finally
      if Canvas.Brush.BitMap <> nil then
      begin
        Canvas.Brush.BitMap.Free;
        Canvas.Brush.BitMap := nil;
      end;
    end;
  end;

  with FImages[1] do
  begin
    Width := FImages[0].Width;
    Height := FImages[0].Height;
    Canvas.Brush.Color := FPalette.High;
    Canvas.FillRect(R);
  end;

  OrgSize.X := ClientWidth;
  OrgSize.Y := ClientHeight;
end;

procedure TVrGauge.DestroyBitmaps;
begin
  DeAllocateBitmaps(FImages);
end;

procedure TVrGauge.PaletteModified(Sender: TObject);
begin
  CreateBitmaps;
  UpdateControlCanvas;
end;

procedure TVrGauge.BevelChanged(Sender: TObject);
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
  CreateBitmaps;
  UpdateControlCanvas;
end;

procedure TVrGauge.SetMax(Value: Integer);
begin
  if (FMax <> Value) and (Value > FMin) then
  begin
    FMax := Value;
    if FPosition > FMax then
      Position := FMax else UpdateControlCanvas;
  end;
end;

procedure TVrGauge.SetMin(Value: Integer);
begin
  if (FMin <> Value) and (Value < FMax) then
  begin
    FMin := Value;
    if FPosition < FMin then
      Position := FMin else UpdateControlCanvas;
  end;
end;

procedure TVrGauge.SetPosition(Value: Integer);
begin
  if Value < FMin then Value := FMin;
  if Value > FMax then Value := FMax;
  if FPosition <> Value then
  begin
    FPosition := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrGauge.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if not Loading then
      BoundsRect := Bounds(Left, Top, Height, Width);
    UpdateControlCanvas;
  end;
end;

procedure TVrGauge.SetTickHeight(Value: Integer);
begin
  if (FTickHeight <> Value) and (Value > 0) then
  begin
    FTickHeight := Value;
    CreateBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrGauge.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrGauge.SetSolidFill(Value: Boolean);
begin
  if FSolidFill <> Value then
  begin
    FSolidFill := Value;
    CreateBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrGauge.SetStyle(Value: TVrProgressStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrGauge.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrGauge.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrGauge.Change;
begin
  if Assigned(FOnChange) then FOnChange(self);
end;

function TVrGauge.GetPercentDone: Longint;
begin
  Result := SolveForY(FPosition - FMin, FMax - FMin);
end;

procedure TVrGauge.DrawHori;
var
  X, Y, I, Offset: Integer;
  TicksOn, TicksOff: Integer;
begin
  TicksOn := SolveForX(PercentDone, Ticks);
  TicksOff := Ticks - TicksOn;

  Y := FViewPort.Top;
  if FStyle = psBottomLeft then
  begin
    X := FViewPort.Left;
    Offset := Step;
  end
  else
  begin
    X := FViewPort.Right - FTickHeight;
    Offset := -Step;
  end;

  for I := 1 to TicksOn do
  begin
    BitmapCanvas.Draw(X, Y, FImages[1]);
    Inc(X, Offset);
  end;
  for I := 1 to TicksOff do
  begin
    BitmapCanvas.Draw(X, Y, FImages[0]);
    Inc(X, Offset);
  end;
end;

procedure TVrGauge.DrawVert;
var
  X, Y, I, Offset: Integer;
  TicksOn, TicksOff: Integer;
begin
  TicksOn := SolveForX(PercentDone, Ticks);
  TicksOff := Ticks - TicksOn;

  X := FViewPort.Left;
  if FStyle = psBottomLeft then
  begin
    Y := FViewPort.Top;
    Offset := Step;
  end
  else
  begin
    Y := FViewPort.Bottom - FTickHeight;
    Offset := -Step;
  end;

  for I := 1 to TicksOff do
  begin
    BitmapCanvas.Draw(X, Y, FImages[0]);
    Inc(Y, Offset);
  end;

  for I := 1 to TicksOn do
  begin
    BitmapCanvas.Draw(X, Y, FImages[1]);
    Inc(Y, Offset);
  end;
end;

procedure TVrGauge.Paint;
var
  R: TRect;
begin
  CalcPaintParams;

  if (OrgSize.X <> ClientWidth) or
   (OrgSize.Y <> ClientHeight) then CreateBitmaps;

  ClearBitmapCanvas;

  R := ClientRect;
  FBevel.Paint(BitmapCanvas, R);

  case FOrientation of
    voVertical: DrawVert;
    voHorizontal: DrawHori;
  end;

  inherited Paint;
end;

procedure TVrGauge.CalcPaintParams;
begin
  Step := FTickHeight + FSpacing;
  FViewPort := ClientRect;
  FBevel.GetVisibleArea(FViewPort);
  case Orientation of
    voVertical:
      begin
        Ticks := (HeightOf(FViewPort) + FSpacing) div Step;
        Height := (FViewPort.Top * 2) + (Ticks * Step) - FSpacing;
      end;
    voHorizontal:
      begin
        Ticks := (WidthOf(FViewPort) + FSpacing) div Step;
        Width := (FViewPort.Left * 2) + (Ticks * Step) - FSpacing;
      end;
  end;
end;

procedure TVrGauge.MoveTo(X, Y: Integer);
var
  Range: Double;
begin
  Range := FMax - FMin;
  case FOrientation of
    voVertical:
      begin
        if FStyle = psBottomLeft then
          Y := ClientHeight - Y - FTickHeight
        else Y := Y - FTickHeight;
        Position := Round(Y * Range / HeightOf(FViewPort))-1;
      end;
    voHorizontal:
      begin
        if FStyle = psBottomLeft then
          X := X - FTickHeight
        else X := ClientWidth - X - FTickHeight;
        Position := Round(X * Range / WidthOf(FViewPort))-1;
      end;
  end;
end;

procedure TVrGauge.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  inherited;
  if (Button = mbLeft) and (FActiveClick) then
    if PtInRect(FViewPort, Point(X, Y)) then MoveTo(X, Y);
end;


end.
