{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrScope;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, VrControls, VrSysUtils;

type
  TVrBaseOffsetInt = 0..100;
  TVrScopeStyle = (ssLines, ssBars);

  TVrScopePen = class(TPen)
  public
    constructor Create;
  published
    property Color default clYellow;
  end;

  TVrScope = class(TVrGraphicImageControl)
  private
    FMin: Integer;
    FMax: Integer;
    FBevel: TVrBevel;
    FPen: TVrScopePen;
    FGridSize: Integer;
    FBaseOffset: TVrBaseOffsetInt;
    FLineColor: TColor;
    FLineWidth: Integer;
    FBaseLineColor: TColor;
    FFrequency: Integer;
    FBufferSize: Integer;
    FStyle: TVrScopeStyle;
    BaseLineInt: Integer;
    hStep: Integer;
    ViewPort: TRect;
    LineImage: TBitmap;
    LineData: TVrIntList;
    procedure SetMin(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetGridSize(Value: Integer);
    procedure SetBaseOffset(Value: TVrBaseOffsetInt);
    procedure SetLineColor(Value: TColor);
    procedure SetBaseLineColor(Value: TColor);
    procedure SetLineWidth(Value: Integer);
    procedure SetFrequency(Value: Integer);
    procedure SetBufferSize(Value: Integer);
    procedure SetPen(Value: TVrScopePen);
    procedure SetBevel(Value: TVrBevel);
    procedure SetStyle(Value: TVrScopeStyle);
    procedure BevelChanged(Sender: TObject);
    procedure PenChanged(Sender: TObject);
  protected
    procedure StepIt;
    procedure PaintGrid;
    procedure PaintLineGraph;
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Clear;
    procedure AddValue(Value: Integer);
  published
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Pen: TVrScopePen read FPen write SetPen;
    property GridSize: Integer read FGridSize write SetGridSize default 16;
    property BaseOffset: TVrBaseOffsetInt read FBaseOffset write SetBaseOffset default 50;
    property LineColor: TColor read FLineColor write SetLineColor default clGreen;
    property BaseLineColor: TColor read FBaseLineColor write SetBaseLineColor default clLime;
    property LineWidth: Integer read FLineWidth write SetLineWidth default 1;
    property Frequency: Integer read FFrequency write SetFrequency default 1;
    property BufferSize: Integer read FBufferSize write SetBufferSize default 999;
    property Style: TVrScopeStyle read FStyle write SetStyle default ssLines;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property DragKind;
{$ENDIF}
    property DragCursor;
    property DragMode;
    property Color default clBlack;
{$IFDEF VER110}
    property Constraints;
{$ENDIF}
    property ParentColor default false;
    property ParentShowHint;
    property PopUpMenu;
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

{ TVrScopePen }
constructor TVrScopePen.Create;
begin
  inherited Create;
  Color := clYellow;
end;

{ TVrScope }

constructor TVrScope.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 249;
  Height := 137;
  Color := clBlack;
  ParentColor := false;
  FGridSize := 16;
  FBaseOffset := 50;
  FBaseLineColor := clLime;
  FLineColor := clGreen;
  FLineWidth := 1;
  FFrequency := 1;
  FStyle := ssLines;
  FMin := 0;
  FMax := 100;
  FBufferSize := 999;
  LineData := TVrIntList.Create;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  FPen := TVrScopePen.Create;
  FPen.OnChange := PenChanged;
  LineImage := TBitmap.Create;
end;

destructor TVrScope.Destroy;
begin
  FPen.Free;
  FBevel.Free;
  LineData.Free;
  LineImage.Free;
  inherited Destroy;
end;

procedure TVrScope.BevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrScope.PenChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrScope.SetGridSize(Value: Integer);
begin
  if (FGridSize <> Value) and (Value > 0) then
  begin
    FGridSize := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetBaseOffset(Value: TVrBaseOffsetInt);
begin
  if FBaseOffset <> Value then
  begin
    FBaseOffset := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetLineColor(Value: TColor);
begin
  if FLineColor <> Value then
  begin
    FLineColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetLineWidth(Value: Integer);
begin
  if FLineWidth <> Value then
  begin
    FLineWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetBaseLineColor(Value: TColor);
begin
  if FBaseLineColor <> Value then
  begin
    FBaseLineColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetFrequency(Value: Integer);
begin
  if (FFrequency <> Value) and (Value < FGridSize) then
  begin
    FFrequency := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetMin(Value: Integer);
begin
  if (FMin <> Value) and (Value < FMax) then
  begin
    FMin := Value;
    LineData.Clear;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetMax(Value: Integer);
begin
  if (FMax <> Value) and (Value > FMin) then
  begin
    FMax := Value;
    LineData.Clear;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetStyle(Value: TVrScopeStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetBufferSize(Value: Integer);
begin
  if (FBufferSize <> Value) and (Value > 0) then
  begin
    FBufferSize := Value;
    LineData.Clear;
    UpdateControlCanvas;
  end;
end;

procedure TVrScope.SetPen(Value: TVrScopePen);
begin
  FPen.Assign(Value);
end;

procedure TVrScope.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrScope.StepIt;
begin
  Inc(hStep, FFrequency);
  if hStep >= FGridSize then hStep := hStep - FGridSize;
end;

procedure TVrScope.Clear;
begin
  hStep := 0;
  LineData.Clear;
  UpdateControlCanvas;
end;

procedure TVrScope.AddValue(Value: Integer);
begin
  AdjustRange(Value, FMin, FMax);
  LineData.Add(Value);
  if LineData.Count - 1 > FBufferSize then LineData.Delete(0);
  UpdateControlCanvas;
  StepIt;
end;

procedure TVrScope.PaintLineGraph;
var
  X, I, BaseV, StepV: Integer;
begin
  with LineImage, LineImage.Canvas do
  begin
    Pen.Assign(FPen);
    X := ViewPort.Left + WidthOf(ViewPort) + FFrequency;
    I := LineData.Count - 1;
    while (X >= 0) and (I >= 0) do
    begin
      BaseV := LineData.Items[I] - LineData.Items[I] * (FBaseOffset div 100);
      StepV := (Height * (BaseV - FMin)) div (FMax - FMin);
      LineTo(X, StepV);
      Dec(I);
      Dec(X, FFrequency);
      if FStyle = ssBars then LineTo(X, StepV);
    end;
    LineTo(X, BaseLineInt);
  end;
end;

procedure TVrScope.PaintGrid;
var
  X, Y: Integer;
begin
  with LineImage, LineImage.Canvas do
  begin
    Width := WidthOf(ViewPort);
    Height := HeightOf(ViewPort);
    BaseLineInt := Height - Round(Height / 100 * FBaseOffset);

    Brush.Color := Self.Color;
    FillRect(Bounds(0, 0, Width, Height));

    Pen.Width := FLineWidth;
    Pen.Color := FLineColor;
    Pen.Mode := pmCopy;
    Pen.Style := psSolid;

    X := Width - hStep;
    while X >= 0 do
    begin
      MoveTo(X, 0);
      LineTo(X, Height);
      Dec(X, FGridSize);
    end;

    Y := BaseLineInt;
    while Y >= 0 do
    begin
      Dec(Y, FGridSize);
      MoveTo(0, Y);
      LineTo(Width, Y);
    end;

    Y := BaseLineInt;
    while Y <= Height do
    begin
      Inc(Y, FGridSize);
      MoveTo(0, Y);
      LineTo(Width, Y);
     end;

     Pen.Color := FBaseLineColor;
     MoveTo(0, BaseLineInt);
     LineTo(Width, BaseLineInt);

     PaintLineGraph;
  end;

  BitmapCanvas.Draw(ViewPort.Left, ViewPort.Top, LineImage);
end;

procedure TVrScope.Paint;
begin
  ClearBitmapCanvas;
  ViewPort := ClientRect;
  FBevel.Paint(BitmapCanvas, ViewPort);
  PaintGrid;
  inherited Paint;
end;


end.
