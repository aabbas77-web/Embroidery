{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrSpectrum;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrSpectrum = class;

  TVrSpectrumBar = class(TVrCollectionItem)
  private
    FPosition: Integer;
    procedure SetPosition(Value: Integer);
  public
    constructor Create(Collection: TVrCollection); override;
    property Position: Integer read FPosition write SetPosition;
  end;

  TVrSpectrumBars = class(TVrCollection)
  private
    FOwner: TVrSpectrum;
    function GetItem(Index: Integer): TVrSpectrumBar;
  protected
    procedure Update(Item: TVrCollectionItem); override;
  public
    constructor Create(AOwner: TVrSpectrum);
    property Items[Index: Integer]: TVrSpectrumBar read GetItem;
  end;

  TVrSpectrum = class(TVrGraphicImageControl)
  private
    FColumns: Integer;
    FMax: Integer;
    FMin: Integer;
    FBevel: TVrBevel;
    FPalette1: TVrPalette;
    FPalette2: TVrPalette;
    FPalette3: TVrPalette;
    FPercent1: TVrPercentInt;
    FPercent2: TVrPercentInt;
    FMarkerColor: TColor;
    FMarkerVisible: Boolean;
    FBarsVisible: Boolean;
    FTickHeight: Integer;
    FSpacing: Integer;
    FViewPort: TRect;
    BarWidth: Integer;
    Ticks: Integer;
    Collection: TVrSpectrumBars;
    function GetCount: Integer;
    function GetItem(Index: Integer): TVrSpectrumBar;
    function GetPercentDone(Position: Longint): Longint;
    procedure SetColumns(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetMin(Value: Integer);
    procedure SetMarkerColor(Value: TColor);
    procedure SetMarkerVisible(Value: Boolean);
    procedure SetTickHeight(Value: Integer);
    procedure SetSpacing(Value: Integer);
    procedure SetPalette1(Value: TVrPalette);
    procedure SetPalette2(Value: TVrPalette);
    procedure SetPalette3(Value: TVrPalette);
    procedure SetPercent1(Value: TVrPercentInt);
    procedure SetPercent2(Value: TVrPercentInt);
    procedure SetBevel(Value: TVrBevel);
    procedure SetBarsVisible(Value: Boolean);
    procedure PaletteModified(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
  protected
    procedure CreateObjects;
    procedure GetItemRect(Index: Integer; var R: TRect);
    procedure UpdateBar(Index: Integer);
    procedure UpdateBars;
    procedure Paint; override;
    procedure CalcPaintParams;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Reset(Value: Integer);
    property Count: Integer read GetCount;
    property Items[Index: Integer]: TVrSpectrumBar read GetItem;
  published
    property Palette1: TVrPalette read FPalette1 write SetPalette1;
    property Palette2: TVrPalette read FPalette2 write SetPalette2;
    property Palette3: TVrPalette read FPalette3 write SetPalette3;
    property Percent1: TVrPercentInt read FPercent1 write SetPercent1 default 60;
    property Percent2: TVrPercentInt read FPercent2 write SetPercent2 default 25;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Columns: Integer read FColumns write SetColumns default 24;
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property MarkerColor: TColor read FMarkerColor write SetMarkerColor default clWhite;
    property MarkerVisible: Boolean read FMarkerVisible write SetMarkerVisible default True;
    property TickHeight: Integer read FTickHeight write SetTickHeight default 1;
    property Spacing: Integer read FSpacing write SetSpacing default 1;
    property BarsVisible: Boolean read FBarsVisible write SetBarsVisible default True;
    property Color default clBlack;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Cursor;
    property DragMode;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragCursor;
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
    property OnDragOver;
    property OnDragDrop;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
    property OnMouseMove;
    property OnMouseDown;
    property OnMouseUp;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


implementation


{ TVrSpectrumBar }

constructor TVrSpectrumBar.Create(Collection: TVrCollection);
begin
  FPosition := 0;
  inherited Create(Collection);
end;

procedure TVrSpectrumBar.SetPosition(Value: Integer);
begin
  if FPosition <> Value then
  begin
    FPosition := Value;
    Changed(false);
  end;
end;

{ TVrSpectrumBars }

constructor TVrSpectrumBars.Create(AOwner: TVrSpectrum);
begin
  inherited Create;
  FOwner := AOwner;
end;

function TVrSpectrumBars.GetItem(Index: Integer): TVrSpectrumBar;
begin
  Result := TVrSpectrumBar(inherited Items[Index]);
end;

procedure TVrSpectrumBars.Update(Item: TVrCollectionItem);
begin
  if Item <> nil then
    FOwner.UpdateBar(Item.Index) else
    FOwner.UpdateBars;
end;

{TVrSpectrum}

constructor TVrSpectrum.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 217;
  Height := 117;
  ParentColor := false;
  Color := clBlack;
  FColumns := 24;
  FMin := 0;
  FMax := 100;
  FMarkerColor := clWhite;
  FMarkerVisible := True;
  FTickHeight := 1;
  FSpacing := 1;
  FPercent1 := 60;
  FPercent2 := 25;
  FBarsVisible := True;

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
    InnerSpace := 1;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  Collection := TVrSpectrumBars.Create(Self);
  CreateObjects;
end;

destructor TVrSpectrum.Destroy;
begin
  Collection.Free;
  FBevel.Free;
  FPalette1.Free;
  FPalette2.Free;
  FPalette3.Free;
  inherited Destroy;
end;

procedure TVrSpectrum.CreateObjects;
var
  I: Integer;
begin
  Collection.Clear;
  for I := 0 to Pred(FColumns) do
    TVrSpectrumBar.Create(Collection);
end;

procedure TVrSpectrum.PaletteModified(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrSpectrum.BevelChanged(Sender: TObject);
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

function TVrSpectrum.GetCount: Integer;
begin
  Result := Collection.Count;
end;

function TVrSpectrum.GetItem(Index: Integer): TVrSpectrumBar;
begin
  Result := Collection.Items[Index];
end;

procedure TVrSpectrum.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpectrum.SetColumns(Value: Integer);
var
  Gap: Integer;
begin
  if (FColumns <> Value) and (Value > 0) then
  begin
    FColumns := Value;
    CreateObjects;
    if not Loading then
    begin
      Gap := (FColumns - 1) * FSpacing;
      Width := (FColumns * BarWidth) + (FViewPort.Left * 2) + Gap;
    end;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpectrum.SetMax(Value: Integer);
var
  I: Integer;
begin
  if (FMax <> Value) and (Value > FMin) then
  begin
    FMax := Value;
    for I := 0 to Pred(Count) do
      with Items[I] do
        if (Position > FMax) then Position := FMax;
  end;
end;

procedure TVrSpectrum.SetMin(Value: Integer);
var
  I: Integer;
begin
  if (FMin <> Value) and (Value < FMax) then
  begin
    FMin := Value;
    for I := 0 to Pred(Count) do
      with Items[I] do
        if (Position < FMin) then Position := FMin;
  end;
end;

procedure TVrSpectrum.SetMarkerColor(Value: TColor);
begin
  if FMarkerColor <> Value then
  begin
    FMarkerColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpectrum.SetMarkerVisible(Value: Boolean);
begin
  if FMarkerVisible <> Value then
  begin
    FMarkerVisible := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpectrum.SetTickHeight(Value: Integer);
begin
  if (FTickHeight <> Value) and (Value > 0) then
  begin
    FTickHeight := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpectrum.SetPalette1(Value: TVrPalette);
begin
  FPalette1.Assign(Value);
end;

procedure TVrSpectrum.SetPalette2(Value: TVrPalette);
begin
  FPalette2.Assign(Value);
end;

procedure TVrSpectrum.SetPalette3(Value: TVrPalette);
begin
  FPalette3.Assign(Value);
end;

procedure TVrSpectrum.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrSpectrum.SetPercent1(Value: TVrPercentInt);
begin
  if (FPercent1 <> Value) then
  begin
    if not Loading then
      if Value + Percent2 > 100 then Value := 100 - Percent2;
    FPercent1 := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpectrum.SetPercent2(Value: TVrPercentInt);
begin
  if (FPercent2 <> Value) then
  begin
    if not Loading then
      if Value + Percent1 > 100 then Value := 100 - Percent1;
    FPercent2 := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSpectrum.SetBarsVisible(Value: Boolean);
begin
  if FBarsVisible <> Value then
  begin
    FBarsVisible := Value;
    UpdateControlCanvas;
  end;
end;

function TVrSpectrum.GetPercentDone(Position: Longint): Longint;
begin
  Result := SolveForY(Position - FMin, FMax - FMin);
end;

procedure TVrSpectrum.UpdateBar(Index: Integer);
var
  R, V: TRect;
  I: Integer;
  TicksOn, TicksOff: Integer;
  Item: TVrSpectrumBar;
  Point, Point1, Point2: Integer;
begin
  Item := Collection.Items[Index];

  GetItemRect(Index, R);

  TicksOn := SolveForX(GetPercentDone(Item.Position), Ticks);
  TicksOff := Ticks - TicksOn;
  Point1 := SolveForX(Percent1, Ticks);
  Point2 := Point1 + SolveForX(Percent2, Ticks);

  Point := Ticks;
  V := Bounds(R.Left, R.Top, R.Right - R.Left, FTickHeight);

  with DestCanvas do
  begin
    Brush.Style := bsSolid;
    for I := 1 to TicksOff do
    begin
      Dec(Point);
      if not FBarsVisible then Brush.Color := Self.Color
      else
      begin
        if Point <= Point1 then Brush.Color := FPalette1[0]
        else if Point <= Point2 then Brush.Color := FPalette2[0]
        else Brush.Color := FPalette3[0];
      end;
      FillRect(V);
      OffsetRect(V, 0, FTickHeight + FSpacing);
    end;

    for I := 1 to TicksOn do
    begin
      Dec(Point);
      if (MarkerVisible) and (I = 1) then Brush.Color := FMarkerColor
      else
      begin
        if Point <= Point1 then Brush.Color := FPalette1[1]
        else if Point <= Point2 then Brush.Color := FPalette2[1]
        else Brush.Color := FPalette3[1];
      end;
      FillRect(V);
      OffsetRect(V, 0, FTickHeight + FSpacing);
    end;
  end;
end;

procedure TVrSpectrum.UpdateBars;
var
  I: Integer;
begin
  for I := 0 to Collection.Count - 1 do
    UpdateBar(I);
end;

procedure TVrSpectrum.Paint;
var
  R: TRect;
begin
  CalcPaintParams;
  ClearBitmapCanvas;
  DestCanvas := BitmapCanvas;
  try
    R := ClientRect;
    FBevel.Paint(BitmapCanvas, R);
    UpdateBars;
    inherited Paint;
  finally
    DestCanvas := Self.Canvas;
  end;
end;

procedure TVrSpectrum.CalcPaintParams;
var
  R: TRect;
  Gap, Step: Integer;
  NewWidth, NewHeight: Integer;
begin
  R := ClientRect;
  FBevel.GetVisibleArea(R);
  FViewPort := R;

  Gap := (FColumns - 1) * FSpacing;
  BarWidth := (WidthOf(R) - Gap) div FColumns;
  NewWidth := (R.Left * 2) + Gap + (FColumns * BarWidth);

  Step := FTickHeight + FSpacing;
  Ticks := (HeightOf(R) + FSpacing) div Step;
  NewHeight := (R.Top * 2) + (Ticks * Step) - FSpacing;

  if (Width <> NewWidth) or (Height <> NewHeight) then
    BoundsRect := Bounds(Left, Top, NewWidth, NewHeight);
end;

procedure TVrSpectrum.GetItemRect(Index: Integer; var R: TRect);
var
  X: Integer;
begin
  R := ClientRect;
  FBevel.GetVisibleArea(R);
  X := (BarWidth * Index) + (FSpacing * Index);
  R := Bounds(R.Left + X, R.Top, BarWidth, HeightOf(R));
end;

procedure TVrSpectrum.Reset(Value: Integer);
var
  I: Integer;
begin
  if Value > FMax then Value := FMax
  else if Value < FMin then Value := FMin;
  for I := 0 to Pred(Count) do
    Collection.Items[I].Position := Value;
end;


end.
