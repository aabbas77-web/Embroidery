unit LUTControl;

{**************************************************}
{  LUTControl is a VCL control similar to the      }
{  tone curve control in some graphic programs.    }
{  It may be used for generation of various        }
{  lookup tables (LUTs)                            }
{                                                  }
{  Copyright (c) 2000 Alex Denissov                }
{  Version: 1.21                                   }
{  Date: 03-July-2000                              }
{  See Licence.txt for license information         }
{**************************************************}

interface

uses
  Windows, SysUtils, Classes, Controls, G32, Math;

const
  NODE_SPOT = 6;

type
  TArrayOfPoints = array of TPoint;
  TLUT256 = array [0..255] of Integer;
  TNodeString = type string;
  TLUTControl = class;
  TLUTMode = (lmNodes, lmCustom);

  TCustomPaintEvent = procedure(
    Sender: TObject;
    Bitmap: TBitmap32;
    var DrawDefault: Boolean
  ) of object;

  TLUTControl = class(TCustomControl)
  private
    FBackgndImage: TBitmap32;
    FDefaultLeftEdge: Byte;
    FDefaultRightEdge: Byte;
    FEdge: Integer;
    FGridColor: TColor32;
    FLineColor: TColor32;
    FMode: TLUTMode;
    FNodeColor: TColor32;
    FNodeSize: Integer;
    FNodePoints: TArrayOfPoints;
    FOnCustomPaint: TCustomPaintEvent;
    FOnChange: TNotifyEvent;
    FGridCols: Integer;
    FGridRows: Integer;
    procedure BackgndImageChanged(Sender: TObject);
    function  GetNodeCount: Integer;
    function  GetNodes: TNodeString;
    procedure SetBackgndImage(Value: TBitmap32);
    procedure SetDefaultLeftEdge(Value: Byte);
    procedure SetDefaultRightEdge(Value: Byte);
    procedure SetEdge(Value: Integer);
    procedure SetGridColor(Value: TColor32);
    procedure SetLineColor(Value: TColor32);
    procedure SetMode(Value: TLUTMode);
    procedure SetNodeColor(Value: TColor32);
    procedure SetNodeCount(Value: Integer);
    procedure SetNodes(const NodeString: TNodeString);
    procedure SetNodeSize(Value: Integer);
    procedure SetGridCols(Value: Integer);
    procedure SetGridRows(Value: Integer);
  protected
    LUT: TLUT256;
    MousePressed: Boolean;
    PaintBuffer: TBitmap32;
    SelNode: Integer;
    UpdateCount: Integer;
    procedure Changed; virtual;
    function ClientToLUT(APoint: TPoint): TPoint;
    procedure SmoothInsert(P: TPoint);
    procedure UpdateFromNodes;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure BeginUpdate;
    procedure Clear;
    procedure CopyTo(out Destination: TLUT256);
    procedure EndUpdate;
    procedure GetFrom(const Source: TLUT256);
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure Paint; override;
    property NodeCount: Integer read GetNodeCount write SetNodeCount;
    property NodePoints: TArrayOfPoints read FNodePoints write FNodePoints;
  published
    property Align;
    property Anchors;
    property BackgndImage: TBitmap32 read FBackgndImage write SetBackgndImage;
    property Color;
    property Constraints;
    property Cursor;
    property DefaultLeftEdge: Byte read FDefaultLeftEdge write SetDefaultLeftEdge default 0;
    property DefaultRightEdge: Byte read FDefaultRightEdge write SetDefaultRightEdge default 255;
    property DragCursor;
    property DragKind;
    property DragMode;
    property DoubleBuffered;
    property Edge: Integer read FEdge write SetEdge default 1;
    property Enabled;
    property GridColor: TColor32 read FGridColor write SetGridColor;
    property GridCols: Integer read FGridCols write SetGridCols;
    property GridRows: Integer read FGridRows write SetGridRows;
    property Hint;
    property LineColor: TColor32 read FLineColor write SetLineColor;
    property Mode: TLUTMode read FMode write SetMode default lmNodes;
    property NodeColor: TColor32 read FNodeColor write SetNodeColor;
    property Nodes: TNodeString read GetNodes write SetNodes;
    property NodeSize: Integer read FNodeSize write SetNodeSize default 2;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Tag;
    property Visible;
    property OnCustomPaint: TCustomPaintEvent read FOnCustomPaint write FOnCustomPaint;
    property OnClick;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property OnDblClick;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
  end;

procedure Register;

implementation

uses TypInfo;

function StringToPoints(const s: string): TArrayOfPoints;
var
  i: Integer;
  Len: Integer;
  P: TPoint;

  procedure PassSpaces;
  begin
    while (i <= Len) and (s[i] = ' ') do Inc(i);
  end;

  procedure CheckLBracket;
  begin
    if i > Len then raise EConvertError.Create('Unexpected string end');
    if s[i] <> '(' then
      raise EConvertError.CreateFmt('''('' expected but found ''%s''', [s[i]]);
    Inc(i);
    PassSpaces;
  end;

  procedure CheckRBracket;
  begin
    if i > Len then raise EConvertError.Create('Unexpected string end');
    if s[i] <> ')' then
      raise EConvertError.CreateFmt(''')'' expected but ''%s'' found', [s[i]]);
    Inc(i);
    PassSpaces;
  end;

  procedure CheckComma;
  begin
    if i > Len then raise EConvertError.Create('Unexpected string end');
    if s[i] <> ',' then
      raise EConvertError.CreateFmt(''','' expected but ''%s'' found', [s[i]]);
    Inc(i);
    PassSpaces;
  end;

  procedure CheckCommaOrEnd;
  begin
    if i > Len then Exit;
    if s[i] <> ',' then
      raise EConvertError.CreateFmt(''','' expected but ''%s'' found', [s[i]]);
    Inc(i);
    PassSpaces;
  end;

  function GetNumber: Integer;
  var
    ns: string;
  begin
    while (i <= Len) and (s[i] in ['0'..'9']) do
    begin
      ns := ns + s[i];
      Inc(i);
    end;
    if ns = '' then
      raise EConvertError.Create('Number expected');
    try
      Result := StrToInt(ns);
      if Result < 0 then Result := 0;
      if Result > 255 then Result := 255;
    except
      raise EConvertError.Create('Number is invalid');
    end;
    PassSpaces;
  end;

  function GetPoint: TPoint;
  begin
    CheckLBracket;
    Result.X := GetNumber;
    CheckComma;
    Result.Y := GetNumber;
    CheckRBracket;
    CheckCommaOrEnd;
  end;
begin
  Result := nil;
  Len := Length(s);
  if Len > 0 then
  begin
    i := 1; // start from the first symbol
    PassSpaces;
    while i <= Len do
    begin
      P := GetPoint;
      SetLength(Result, Length(Result) + 1);
      Result[High(Result)] := P;
    end;
    PassSpaces;
  end;
end;

function PointsToString(const Points: TArrayOfPoints): string;
var
  i: Integer;
begin
  for i := 0 to High(Points) do
  begin
    Result := Result + Format('(%d, %d)', [Points[i].X, Points[i].Y]);
    if i <> High(Points) then Result := Result + ', ';
  end;
end;

function FindNode(const Nodes: TArrayOfPoints; ANode: TPoint; ASpot: Integer = NODE_SPOT): Integer;
var
  i: Integer;
  MinDist, Dist: Single;
begin
  Result := -1;
  if Nodes = nil then Exit;
  MinDist := 1000000;
  for i := 0 to High(Nodes) do
  begin
    Dist := Hypot(Nodes[i].X - ANode.X, Nodes[i].Y - ANode.Y);
    if Dist < MinDist then
    begin
      MinDist := Dist;
      Result := i;
    end;
  end;
  if MinDist > ASpot then Result := -1;
end;

function FindNodeX(const Nodes: TArrayOfPoints; ANode: TPoint; ASpot: Integer = NODE_SPOT): Integer;
var
  i: Integer;
  MinDist, Dist: Single;
begin
  Result := -1;
  if Nodes = nil then Exit;
  MinDist := 1000000;
  for i := 0 to High(Nodes) do
  begin
    Dist := Abs(Nodes[i].X - ANode.X);
    if Dist < MinDist then
    begin
      MinDist := Dist;
      Result := i;
    end;
  end;
  if MinDist > ASpot then Result := -1;
end;

function AddLUTNode(var Nodes: TArrayOfPoints; NewNode: TPoint; ASpot: Integer = NODE_SPOT): Integer;
var
  i, sel: Integer;
begin
  if Nodes = nil then
  begin
    SetLength(Nodes, 1);
    Nodes[0] := NewNode;
    Result := 0;
    Exit;
  end;

  sel := FindNode(Nodes, NewNode, ASpot);
  if sel = -1 then sel := FindNodeX(Nodes, NewNode, ASpot);
  if sel <> -1 then
  begin
    Nodes[sel] := NewNode;
    if (sel > 0) and (Nodes[sel].X <= Nodes[sel - 1].X) then
      Nodes[sel].X := Nodes[sel - 1].X + 1;
    if (sel < High(Nodes)) and (Nodes[sel].X >= Nodes[sel + 1].X) then
      Nodes[sel].X := Nodes[sel + 1].X - 1;
    Result := sel;
    Exit;
  end;
  sel := High(Nodes) + 1;
  for i := 0 to High(Nodes) do
    if NewNode.X < Nodes[i].X then
    begin
      sel := i;
      Break;
    end;
  SetLength(Nodes, Length(Nodes) + 1);
  for i := High(Nodes) downto sel + 1 do Nodes[i] := Nodes[i - 1];
  Nodes[sel] := NewNode;
  Result := sel;
end;

procedure MoveLUTNode(var Nodes: TArrayOfPoints; Node: Integer; NewPos: TPoint);
begin
  if not Node in [0..High(Nodes)] then Exit;
  if NewPos.X < 0 then NewPos.X := 0;
  if NewPos.X > 255 then NewPos.X := 255;
  if NewPos.Y < 0 then NewPos.Y := 0;
  if NewPos.Y > 255 then NewPos.Y := 255;
  Nodes[Node] := NewPos;
  if (Node > 0) and (NewPos.X <= Nodes[Node - 1].X) then
    Nodes[Node].X := Nodes[Node - 1].X + 1;
  if (Node < High(Nodes)) and (NewPos.X >= Nodes[Node + 1].X) then
    Nodes[Node].X := Nodes[Node + 1].X - 1;
end;

procedure RemoveLUTNode(var Nodes: TArrayOfPoints; Point: TPoint);
var
  i, sel: Integer;
begin
  sel := FindNode(Nodes, Point);
  if sel <> -1 then
  begin
    for i := Sel to High(Nodes) - 1 do Nodes[i] := Nodes[i + 1];
    SetLength(Nodes, Length(Nodes) - 1);
  end
end;



{ TLUTControl }

constructor TLUTControl.Create(AOwner: TComponent);
begin
  inherited;
  ControlStyle := [csClickEvents, csDoubleClicks, csOpaque, csCaptureMouse,
    csReplicatable];
  DoubleBuffered := True;
  Height := 131;
  Width := 131;
  PaintBuffer := TBitmap32.Create;
  FBackgndImage := TBitmap32.Create;
  FBackgndImage.OnChange := BackgndImageChanged;
  FDefaultRightEdge := 255;
  FEdge := 1;
  FGridColor := clGray32;
  FGridCols := 8;
  FGridRows := 8;
  FLineColor := clBlack32;
  FNodeColor := clBlue32;
  FNodeSize := 2;
  SetNodes('');
end;

destructor TLUTControl.Destroy;
begin
  PaintBuffer.Free;
  FBackgndImage.Free;
  FNodePoints := nil;
  inherited;
end;

procedure TLUTControl.BackgndImageChanged(Sender: TObject);
begin
  Invalidate;
end;

procedure TLUTControl.BeginUpdate;
begin
  Inc(UpdateCount);
end;

procedure TLUTControl.Changed;
begin
  if Assigned(FOnChange) and (UpdateCount = 0) then FOnChange(Self);
end;

procedure TLUTControl.Clear;
var
  i: Integer;
begin
  FNodePoints := nil;
  for i := 0 to 255 do
    LUT[i] := DefaultLeftEdge + i * (DefaultRightEdge - DefaultLeftEdge) div 255;
  Invalidate;
  Changed;
end;

function TLUTControl.ClientToLUT(APoint: TPoint): TPoint;
begin
  if (Width - Edge * 2 < 2) or (Height - Edge * 2 < 2) then
    Result := Point(0, 0)
  else
  begin
    Result.X := Round((APoint.X - Edge) * 255 / (Width - Edge * 2 - 1));
    Result.Y := 255 - Round((APoint.Y - Edge) * 255 / (Height - Edge * 2 - 1));
    if Result.X < 0 then Result.X := 0
    else if Result.X > 255 then Result.X := 255;
    if Result.Y < 0 then Result.Y := 0
    else if Result.Y > 255 then Result.Y := 255;
  end;
end;

procedure TLUTControl.CopyTo(out Destination: TLUT256);
begin
  Move(LUT[0], Destination[0], 256 * SizeOf(Integer));
end;

procedure TLUTControl.EndUpdate;
begin
  Dec(UpdateCount);
end;

procedure TLUTControl.GetFrom(const Source: TLUT256);
begin
  FMode := lmCustom;
  Move(Source[0], LUT[0], 256 * SizeOf(Integer));
end;

function TLUTControl.GetNodeCount: Integer;
begin
  Result := Length(NodePoints);
end;

function TLUTControl.GetNodes: TNodeString;
begin
  Result := PointsToString(FNodePoints);
end;

procedure TLUTControl.MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  P: TPoint;
begin
  inherited;
  P := ClientToLUT(Point(X, Y));
  SelNode := -1;
  if Mode = lmNodes then
  begin
    if Button = mbLeft then SelNode := AddLUTNode(FNodePoints, P)
    else if Button = mbRight then RemoveLUTNode(FNodePoints, P);

    if Button = mbLeft then
    begin
      MousePressed := True;
      SetCaptureControl(Self);
    end
    else
    begin
      MousePressed := False;
      ReleaseCapture;
    end;
    UpdateFromNodes;
    Changed;
  end
  else // lmCustom
  begin
    if Button = mbLeft then
    begin
      MousePressed := True;
      SetCaptureControl(Self);
      SmoothInsert(P);
    end;
  end;
end;

procedure TLUTControl.MouseMove(Shift: TShiftState; X, Y: Integer);
var
  P: TPoint;
begin
  inherited;
  if MousePressed then
  begin
    P := ClientToLUT(Point(X, Y));
    if SelNode in [0..High(FNodePoints)] then
    begin
      MoveLUTNode(FNodePoints, SelNode, P);
      UpdateFromNodes;
    end
    else if Mode = lmCustom then
    begin
      SmoothInsert(P);
    end;
    Changed;
  end;
end;

procedure TLUTControl.MouseUp(Button: TMouseButton; Shift: TShiftState; X,
  Y: Integer);
begin
  inherited;
  MousePressed := False;
  ReleaseCapture;
  SelNode := -1;
end;

procedure TLUTControl.Paint;
var
  R: TRect;
  i, x, y, ww, hh: Integer;
  x0, y0, x1, y1: Single;
  DrawDefault: Boolean;

  procedure iMoveTo(const a: TPoint);
  begin
    x0 := Edge + a.X * ww / 255;
    y0 := Edge + hh - a.Y * hh / 255;
  end;

  procedure iLineTo(const a: TPoint);
  begin
    x1 := Edge + a.X * ww / 255;
    y1 := Edge + hh - a.Y * hh / 255;
    PaintBuffer.LineFS(x0, y0, x1, y1, LineColor);
    x0 := x1;
    y0 := y1;
  end;
begin
  PaintBuffer.SetSize(Width, Height);
  PaintBuffer.Clear(Color32(Color));
  ww := Width - 1 - Edge * 2;
  hh := Height - 1 - Edge * 2;

  if BackgndImage.Empty then PaintBuffer.Clear(Color32(Color))
  else
    BackgndImage.DrawTo(PaintBuffer,
      Rect(Edge, Edge, Width - Edge, Height - Edge));

  DrawDefault := True;
  if Assigned(FOnCustomPaint) then
    FOnCustomPaint(Self, PaintBuffer, DrawDefault);

  if DrawDefault then
  begin
    { draw grid }
    if GridCols > 0 then
      for i := 0 to GridCols do
        PaintBuffer.VertLineTS(Edge + i * ww div GridCols, Edge,
          hh + Edge, GridColor);

    if GridRows > 0 then
      for i := 0 to GridRows do
        PaintBuffer.HorzLineTS(Edge, Edge + i * hh div GridRows,
          ww + Edge, GridColor);

    { draw the curve }
    if Mode = lmNodes then
    begin
      if NodePoints <> nil then
      begin
        if NodePoints[0].X > 0 then
        begin
          iMoveTo(Point(0, DefaultLeftEdge));
          iLineTo(NodePoints[0]);
        end
        else iMoveTo(FNodePoints[0]);
        for i := 1 to High(NodePoints) do iLineTo(NodePoints[i]);
        if NodePoints[High(NodePoints)].X < 255 then
          iLineTo(Point(255, DefaultRightEdge));
      end
      else
      begin
        iMoveTo(Point(0, DefaultLeftEdge));
        iLineTo(Point(255, DefaultRightEdge));
      end;
    end
    else // mode = lmCustom
    begin
      iMoveTo(Point(0, LUT[0]));
      for i := 1 to 255 do iLineTo(Point(i, LUT[i]));
    end;

    if Mode = lmNodes then
    begin
      { draw nodes }
      if NodePoints <> nil then
        for i := 0 to High(NodePoints) do
        begin
          x := Edge + Round(NodePoints[i].X * ww / 255);
          y := Edge + hh - Round(NodePoints[i].Y * hh / 255);
          R := Rect(x - NodeSize, y - NodeSize, x + NodeSize, y + NodeSize);
          IntersectRect(R, R, Rect(0, 0, Width - 1, Height - 1));
          PaintBuffer.FillRectT(R.Left, R.Top, R.Right, R.Bottom, NodeColor);
        end;
    end;
  end;

  PaintBuffer.DrawTo(Canvas.Handle, 0, 0);
end;

procedure TLUTControl.SetBackgndImage(Value: TBitmap32);
begin
  FBackgndImage.Assign(Value);
  Invalidate;
end;

procedure TLUTControl.SetDefaultLeftEdge(Value: Byte);
begin
  FDefaultLeftEdge := Value;
  if Mode = lmNodes then
  begin
    UpdateFromNodes;
    Changed;
  end;
end;

procedure TLUTControl.SetDefaultRightEdge(Value: Byte);
begin
  FDefaultRightEdge := Value;
  if Mode = lmNodes then
  begin
    UpdateFromNodes;
    Changed;
  end;
end;

procedure TLUTControl.SetEdge(Value: Integer);
begin
  if FEdge <> Value then
  begin
    FEdge := Value;
    if Mode = lmNodes then Invalidate;
  end;
end;

procedure TLUTControl.SetGridColor(Value: TColor32);
begin
  if FGridColor <> Value then
  begin
    FGridColor := Value;
    Invalidate;
  end;
end;

procedure TLUTControl.SetGridCols(Value: Integer);
begin
  if Value < 0 then
    raise EPropertyError.Create('Number of columns should be positive');
  if FGridCols <> Value then
  begin
    FGridCols := Value;
    Invalidate;
  end;
end;

procedure TLUTControl.SetGridRows(Value: Integer);
begin
  if Value < 0 then
    raise EPropertyError.Create('Number of rows should be positive');
  if FGridRows <> Value then
  begin
    FGridRows := Value;
    Invalidate;
  end;
end;

procedure TLUTControl.SetLineColor(Value: TColor32);
begin
  if FLineColor <> Value then
  begin
    FLineColor := Value;
    Invalidate;
  end;
end;

procedure TLUTControl.SetMode(Value: TLUTMode);
begin
  if FMode <> Value then
  begin
    FMode := Value;
    if Value = lmNodes then UpdateFromNodes;
    Invalidate;
    Changed;
  end;
end;

procedure TLUTControl.SetNodeSize(Value: Integer);
begin
  if not Value in [0..16] then
    raise EPropertyError.Create('Handle size should be in [0..16] range');
  FNodeSize := Value;
  if Mode = lmNodes then Invalidate;
end;

procedure TLUTControl.SetNodeColor(Value: TColor32);
begin
  if FNodeColor <> Value then
  begin
    FNodeColor := Value;
    if Mode = lmNodes then Invalidate;
  end;
end;

procedure TLUTControl.SetNodeCount(Value: Integer);
begin
  if UpdateCount > 0 then
    raise Exception.Create('LUTControl.NodePoints is called from the outside'#13#10 +
      'of BeginUpdate..EndUpdate block');
  SetLength(FNodePoints, Value);
end;

procedure TLUTControl.SetNodes(const NodeString: TNodeString);
var
  a: TArrayOfPoints;
  i: Integer;
begin
  a := StringToPoints(NodeString);
  FNodePoints := nil;
  for i := 0 to High(a) do AddLUTNode(FNodePoints, a[i], 0);
  if Mode = lmNodes then
  begin
    UpdateFromNodes;
    Changed;
  end;
end;

procedure TLUTControl.SmoothInsert(P: TPoint);
var
  X, Y: Integer;
begin
  X := P.X;
  Y := P.Y;
  if not X in [0..255] then Exit;
  LUT[X] := Y;
  if X > 0 then LUT[X - 1] := Y;
  if X < 255 then LUT[X + 1] := Y;
  if X > 1 then LUT[X - 2] := (LUT[X - 2] + Y) div 2;
  if X < 254 then LUT[X + 2] := (LUT[X + 2] + Y) div 2;
  if X > 2 then LUT[X - 3] := (3 * LUT[X - 3] + Y) div 4;
  if X < 253 then LUT[X + 3] := (3 * LUT[X + 3] + Y) div 4;
  Invalidate;
  Changed;
end;

procedure TLUTControl.UpdateFromNodes;
var
  n: Integer;

  procedure Interpolate(a, b: TPoint);
  var
    i, v: Integer;
  begin
    for i := a.x to b.x do
    begin
      v := a.y + (b.y - a.y) * (i - a.x) div (b.x - a.x);
      if v < 0 then v := 0;
      if v > 255 then v := 255;
      LUT[i] := v;
    end;
  end;
begin
  if NodePoints = nil then Clear
  else
  begin
    if NodePoints[0].X > 0 then
      Interpolate(Point(0, DefaultLeftEdge), NodePoints[0]);

    for n := 0 to High(NodePoints) - 1 do
      Interpolate(NodePoints[n], NodePoints[n + 1]);

    n := High(NodePoints);

    if NodePoints[n].X < 255 then
      Interpolate(NodePoints[n], Point(255, DefaultRightEdge));
  end;
  Invalidate;
end;

procedure Register;
begin
  RegisterComponents('Samples', [TLUTControl]);
end;

end.
