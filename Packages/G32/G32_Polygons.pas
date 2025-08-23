unit G32_Polygons;

{*********************************************}
{  This unit is a part of Graphics32 library  }
{  Copyright � 2000 Alex Denissov             }
{  See License.txt for licence information    }
{*********************************************}

interface

{$I G32.INC}

uses
  Windows, SysUtils, G32, G32_LowLevel, G32_Blend;

{ Polylines }

procedure PolylineTS(Bitmap: TBitmap32; const Points: TArrayOfFixedPoint;
  Color: TColor32; Closed: Boolean = False);
procedure PolylineAS(Bitmap: TBitmap32; const Points: TArrayOfFixedPoint;
  Color: TColor32; Closed: Boolean = False);
procedure PolylineXS(Bitmap: TBitmap32; const Points: TArrayOfFixedPoint;
  Color: TColor32; Closed: Boolean = False);

procedure PolyPolylineTS(Bitmap: TBitmap32; const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32; Closed: Boolean = False);
procedure PolyPolylineAS(Bitmap: TBitmap32; const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32; Closed: Boolean = False);
procedure PolyPolylineXS(Bitmap: TBitmap32; const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32; Closed: Boolean = False);

{ Polygons }

type
  TPolyFillMode = (pfAlternate, pfWinding);

procedure PolygonTS(Bitmap: TBitmap32; const Points: TArrayOfFixedPoint;
  Color: TColor32; Mode: TPolyFillMode = pfAlternate);
procedure PolygonXS(Bitmap: TBitmap32; const Points: TArrayOfFixedPoint;
  Color: TColor32; Mode: TPolyFillMode = pfAlternate);

procedure PolyPolygonTS(Bitmap: TBitmap32; const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32; Mode: TPolyFillMode = pfAlternate);
procedure PolyPolygonXS(Bitmap: TBitmap32; const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32; Mode: TPolyFillMode = pfAlternate);


{ TPoygon32 }
{ TODO : Bezier Curves, and QSpline curves for TrueType font rendering }
{ TODO : Check if QSpline is compatible with Type1 fonts }
type
  TPolygon32 = class
  private
    FAntialiased: Boolean;
    FClosed: Boolean;
    FFillMode: TPolyFillMode;
    FNormals: TArrayOfArrayOfFixedPoint;
    FPoints: TArrayOfArrayOfFixedPoint;
  protected
    procedure BuildNormals;
    procedure ClearNormals;
  public
    constructor Create; virtual;
    destructor Destroy; override;
    procedure Add(const P: TFixedPoint);
    procedure Clear;
    function  Grow(const Delta: TFixed; EdgeSharpness: Single = 0): TPolygon32;
    procedure Draw(Bitmap: TBitmap32; OutlineColor, FillColor: TColor32);
    procedure DrawEdge(Bitmap: TBitmap32; Color: TColor32);
    procedure DrawFill(Bitmap: TBitmap32; Color: TColor32);
    procedure NewLine;
    procedure Offset(const Dx, Dy: TFixed);
    function  Outline: TPolygon32;
    property Antialiased: Boolean read FAntialiased write FAntialiased;
    property Closed: Boolean read FClosed write FClosed;
    property FillMode: TPolyFillMode read FFillMode write FFillMode;
    property Normals: TArrayOfArrayOfFixedPoint read FNormals write FNormals;
    property Points: TArrayOfArrayOfFixedPoint read FPoints write FPoints;
  end;

implementation

uses Math;

type
// These are for edge scan info. Note, that the most significant bit of the
// edge in a scan line is used for winding (edge direction) info.
  TScanLine = TArrayOfInteger;
  TScanLines = TArrayOfArrayOfInteger;

procedure PolylineTS(
  Bitmap: TBitmap32;
  const Points: TArrayOfFixedPoint;
  Color: TColor32;
  Closed: Boolean);
var
  I, Count: Integer;
  DoAlpha: Boolean;
begin
  Count := Length(Points);
  if (Count = 1) and Closed then
    with Points[0] do Bitmap.SetPixelTS(FixedRound(X), FixedRound(Y), Color);
  if Count < 2 then Exit;
  DoAlpha := Color and $FF000000 <> $FF000000;
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  Bitmap.PenColor := Color;
  with Points[0] do Bitmap.MoveTo(FixedRound(X), FixedRound(Y));
  if DoAlpha then
    for I := 1 to Count - 1 do
      with Points[I] do
        Bitmap.LineToTS(FixedRound(X), FixedRound(Y))
  else
    for I := 1 to Count - 1 do
      with Points[I] do
        Bitmap.LineToS(FixedRound(X), FixedRound(Y));
  if Closed then with Points[0] do Bitmap.LineToTS(FixedRound(X), FixedRound(Y));
  Bitmap.EndUpdate;
  Bitmap.Changed;
end;

procedure PolylineAS(
  Bitmap: TBitmap32;
  const Points: TArrayOfFixedPoint;
  Color: TColor32;
  Closed: Boolean);
var
  I, Count: Integer;
begin
  Count := Length(Points);
  if (Count = 1) and Closed then
    with Points[0] do Bitmap.SetPixelTS(FixedRound(X), FixedRound(Y), Color);
  if Count < 2 then Exit;
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  Bitmap.PenColor := Color;
  with Points[0] do Bitmap.MoveTo(FixedRound(X), FixedRound(Y));
  for I := 1 to Count - 1 do
    with Points[I] do
      Bitmap.LineToAS(FixedRound(X), FixedRound(Y));
  if Closed then with Points[0] do Bitmap.LineToAS(FixedRound(X), FixedRound(Y));
  Bitmap.EndUpdate;
  Bitmap.Changed;
end;

procedure PolylineXS(
  Bitmap: TBitmap32;
  const Points: TArrayOfFixedPoint;
  Color: TColor32;
  Closed: Boolean);
var
  I, Count: Integer;
begin
  Count := Length(Points);
  if (Count = 1) and Closed then with Points[0] do Bitmap.SetPixelXS(X, Y, Color);
  if Count < 2 then Exit;
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  Bitmap.PenColor := Color;
  with Points[0] do Bitmap.MoveToX(X, Y);
  for I := 1 to Count - 1 do with Points[I] do Bitmap.LineToXS(X, Y);
  if Closed then with Points[0] do Bitmap.LineToXS(X, Y);
  Bitmap.EndUpdate;
  Bitmap.Changed;
end;

procedure PolyPolylineTS(
  Bitmap: TBitmap32;
  const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32;
  Closed: Boolean = False);
var
  I: Integer;
begin
  for I := 0 to High(Points) do PolylineTS(Bitmap, Points[I], Color, Closed);
end;

procedure PolyPolylineAS(
  Bitmap: TBitmap32;
  const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32;
  Closed: Boolean = False);
var
  I: Integer;
begin
  for I := 0 to High(Points) do PolylineAS(Bitmap, Points[I], Color, Closed);
end;

procedure PolyPolylineXS(
  Bitmap: TBitmap32;
  const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32;
  Closed: Boolean = False);
var
  I: Integer;
begin
  for I := 0 to High(Points) do PolylineXS(Bitmap, Points[I], Color, Closed);
end;

procedure QSortLine(const ALine: TScanLine; L, R: Integer);
var
  I, J, P: Integer;
begin
  repeat
    I := L;
    J := R;
    P := ALine[(L + R) shr 1] and $7FFFFFFF;
    repeat
      while (ALine[I] and $7FFFFFFF) < P do Inc(I);
      while (ALine[J] and $7FFFFFFF) > P do Dec(J);
      if I <= J then
      begin
        Swap(ALine[I], ALine[J]);
        Inc(I);
        Dec(J);
      end;
    until I > J;
    if L < J then QSortLine(ALine, L, J);
    L := I;
  until I >= R;
end;

procedure SortLine(const ALine: TScanLine);
var
  L: Integer;
begin
  L := Length(ALine);
  Assert(not Odd(L));
  if L = 2 then
  begin
    if (ALine[0] and $7FFFFFFF) > (ALine[1] and $7FFFFFFF) then
      Swap(ALine[0], ALine[1])
  end
  else
    if L > 2 then QSortLine(ALine, 0, L - 1);
end;

procedure SortLines(const ScanLines: TScanLines);
var
  I: Integer;
begin
  for I := 0 to High(ScanLines) do SortLine(ScanLines[I]);
end;

procedure AddPolygon(const Points: TArrayOfPoint; BaseY: Integer;
  MaxX, MaxY: Integer; var ScanLines: TScanLines; SubSampleX: Boolean);
var
  I, X1, Y1, X2, Y2: Integer;
  Direction, PrevDirection: Integer; // up = 1 or down = -1

  function Sign(I: Integer): Integer;
  begin
    if I > 0 then Result := 1
    else if I < 0 then Result := -1
    else Result := 0;
  end;

  procedure AddEdgePoint(X, Y: Integer; Direction: Integer);
  var
    L: Integer;
  begin
    // positive direction (+1) is down
    if (Y < 0) or (Y > MaxY) then Exit;
    X := Constrain(X, 0, MaxX);
    L := Length(ScanLines[Y - BaseY]);
    SetLength(ScanLines[Y - BaseY], L + 1);
    Assert(Direction <> 0);
    if Direction < 0 then X := Longword(X) or $80000000; // set the highest bit if the winding is up
    ScanLines[Y - BaseY][L] := X;
  end;

  function DrawEdge(X1, Y1, X2, Y2: Integer): Integer;
  var
    X, Y, I: Integer;
    Dx, Dy, Sx, Sy: Integer;
    Delta: Integer;
  begin
    // this function 'renders' a line into the edge (ScanLines) buffer
    // and returns the line direction (1 - down, -1 - up, 0 - horizontal)
    Result := 0;
    if Y2 = Y1 then Exit;
    Dx := X2 - X1;
    Dy := Y2 - Y1;
    if Dy > 0 then Sy := 1 
    else
    begin
      Sy := -1;
      Dy := -Dy;
    end;
    Result := Sy;
    if Dx > 0 then Sx := 1
    else
    begin
      Sx := -1;
      Dx := -Dx;
    end;
    Delta := (Dx mod Dy) shr 1;
    X := X1; Y := Y1;
    for I := 0 to Dy - 1 do
    begin
      AddEdgePoint(X, Y, Result);
      Inc(Y, Sy);
      Inc(Delta, Dx);
      while Delta > Dy do
      begin
        Inc(X, Sx);
        Dec(Delta, Dy);
      end;
    end;
  end;
begin
  if Length(Points) < 3 then Exit;

  X1 := Points[0].X; if SubSampleX then X1 := X1 shl 8;
  Y1 := Points[0].Y;

  // find the last Y different from Y1 and assign it to Y0
  PrevDirection := 0;
  I := High(Points);
  while I > 0 do
  begin
    PrevDirection := Sign(Y1 - Points[I].Y);
    if PrevDirection <> 0 then Break;
    Dec(I);
  end;
  Assert(PrevDirection <> 0);

  for I := 1 to High(Points) do
  begin
    X2 := Points[I].X; if SubSampleX then X2 := X2 shl 8;
    Y2 := Points[I].Y;
    if Y1 <> Y2 then
    begin
      Direction := DrawEdge(X1, Y1, X2, Y2);
      if Direction <> PrevDirection then
      begin
        AddEdgePoint(X1, Y1, -Direction);
        PrevDirection := Direction;
      end;
    end;
    X1 := X2; Y1 := Y2;
  end;
  X2 := Points[0].X; if SubSampleX then X2 := X2 shl 8;
  Y2 := Points[0].Y;
  if Y1 <> Y2 then
  begin
    Direction := DrawEdge(X1, Y1, X2, Y2);
    if Direction <> PrevDirection then AddEdgePoint(X1, Y1, -Direction);
  end;
end;

procedure FillLines(Bitmap: TBitmap32; BaseY: Integer;
  const ScanLines: TScanLines; Color: TColor32; Mode: TPolyFillMode);
var
  I, J, L: Integer;
  Left, Right, OldRight, LP, RP: Integer;
  DoAlpha: Boolean;
  Winding, NextWinding: Integer;
begin
  DoAlpha := Color and $FF000000 <> $FF000000;
  for J := 0 to High(ScanLines) do
  begin
    L := Length(ScanLines[J]); // assuming length is even
    if L = 0 then Continue;
    I := 0;
    OldRight := -1;
    if Mode = pfAlternate then
      while I < L do
      begin
        Left := ScanLines[J][I] and $7FFFFFFF;
        Inc(I);
        Right := ScanLines[J][I] and $7FFFFFFF - 1;
        if (Right > Left) then
        begin
          if Mode = pfAlternate then
          begin
            if (Left and $FF) < $80 then Left := Left shr 8
            else Left := Left shr 8 + 1;
            if (Right and $FF) < $80 then Right := Right shr 8
            else Right := Right shr 8 + 1;

            if Right >= Bitmap.Width - 1 then Right := Bitmap.Width - 1;

            if Left <= OldRight then Left := OldRight + 1;
            OldRight := Right;
            if Right >= Left then
              if DoAlpha then Bitmap.HorzLineT(Left, BaseY + J, Right, Color)
              else Bitmap.HorzLine(Left, BaseY + J, Right, Color);
          end;
        end;
        Inc(I);
      end
    else // Mode = pfWinding
    begin
      Winding := 0;
      Left := ScanLines[J][0];
      if (Left and $80000000) <> 0 then Inc(Winding) else Dec(Winding);
      Left := Left and $7FFFFFFF;
      Inc(I);
      while I < L do
      begin
        Right := ScanLines[J][I];
        if (Right and $80000000) <> 0 then NextWinding := 1 else NextWinding := -1;
        Right := Right and $7FFFFFFF;
        Inc(I);

        if Winding <> 0 then
        begin
          if (Left and $FF) < $80 then LP := Left shr 8
          else LP := Left shr 8 + 1;
          if (Right and $FF) < $80 then RP := Right shr 8
          else RP := Right shr 8 + 1;

          if RP >= Bitmap.Width - 1 then RP := Bitmap.Width - 1;

          if RP >= LP then
            if DoAlpha then Bitmap.HorzLineT(LP, BaseY + J, RP, Color)
            else Bitmap.HorzLine(LP, BaseY + J, RP, Color);
        end;

        Inc(Winding, NextWinding);
        Left := Right;
      end;
    end;
  end;
end;

procedure FillLines2(Bitmap: TBitmap32; BaseY: Integer;
  const ScanLines: TScanLines; Color: TColor32; Mode: TPolyFillMode);
var
  I, J, L, N: Integer;
  MinY, MaxY, Y, Top, Bottom: Integer;
  MinX, MaxX, X, Dx: Integer;
  Left, Right: Integer;
  Buffer: array of Integer;
  P: PColor32;
  DoAlpha: Boolean;
  Winding, NextWinding: Integer;
begin
  DoAlpha := Color and $FF000000 <> $FF000000;
  // find the range of Y screen coordinates
  MinY := BaseY shr 4;
  MaxY := (BaseY + Length(ScanLines) + 15) shr 4;

  Y := MinY;
  while Y < MaxY do
  begin
    Top := Y shl 4 - BaseY;
    Bottom := Top + 15;
    if Top < 0 then Top := 0;
    if Bottom > High(ScanLines) then Bottom := High(ScanLines);

    // find left and right edges of the screen scanline
    MinX := 1000000; MaxX := -1000000;
    for J := Top to Bottom do
    begin
      L := High(ScanLines[J]);
      Left := (ScanLines[J][0] and $7FFFFFFF) shr 4;
      Right := (ScanLines[J][L] and $7FFFFFFF + 15) shr 4;
      if Left < MinX then MinX := Left;
      if Right > MaxX then MaxX := Right;
    end;

    // allocate the buffer for a screen scanline
    SetLength(Buffer, MaxX - MinX + 2);
    FillLongword(Buffer[0], Length(Buffer), 0);

    // and fill it
    for J := Top to Bottom do
    begin
      I := 0;
      L := Length(ScanLines[J]);
      if Mode = pfAlternate then
        while I < L do
        begin
          // Left edge
          X := ScanLines[J][I] and $7FFFFFFF;
          Dx := X and $0F;
          X := X shr 4 - MinX;
          Inc(Buffer[X], Dx xor $0F);
          Inc(Buffer[X + 1], Dx);
          Inc(I);

          // Right edge
          X := ScanLines[J][I] and $7FFFFFFF;
          Dx := X and $0F;
          X := X shr 4 - MinX;
          Dec(Buffer[X], Dx xor $0F);
          Dec(Buffer[X + 1], Dx);
          Inc(I);
        end
      else // mode = pfWinding
      begin
        Winding := 0;
        while I < L do
        begin
          X := ScanLines[J][I];
          Inc(I);
          if (X and $80000000) <> 0 then NextWinding := 1 else NextWinding := -1;
          X := X and $7FFFFFFF;
          if Winding = 0 then
          begin
            Dx := X and $0F;
            X := X shr 4 - MinX;
            Inc(Buffer[X], Dx xor $0F);
            Inc(Buffer[X + 1], Dx);
          end;
          Inc(Winding, NextWinding);
          if Winding = 0 then
          begin
            Dx := X and $0F;
            X := X shr 4 - MinX;
            Dec(Buffer[X], Dx xor $0F);
            Dec(Buffer[X + 1], Dx);
          end;
        end;
      end;
    end;

    // integrate the buffer
    N := 0;
    for I := 0 to High(Buffer) do
    begin
      Inc(N, Buffer[I]);
      Buffer[I] := N;
      Buffer[I] := N * 273 shr 8; // some bias
    end;

    // draw it to the screen
    P := Bitmap.PixelPtr[MinX, Y];
    try
      if DoAlpha then
        for I := 0 to High(Buffer) do
        begin
          BlendMemEx(Color, P^, Buffer[I]);
          Inc(P);
        end
      else
        for I := 0 to High(Buffer) do
        begin
          N := Buffer[I];
          if N = 255 then P^ := Color
          else BlendMemEx(Color, P^, Buffer[I]);
          Inc(P);
        end;
    finally
      EMMS;
    end;

    Inc(Y);
  end;
end;

procedure GetMinMax(const Points: TArrayOfPoint; out MinY, MaxY: Integer); overload;
var
  I, Y: Integer;
begin
  MinY := 100000; MaxY := -100000;
  for I := 0 to High(Points) do
  begin
    Y := Points[I].Y;
    if Y < MinY then MinY := Y;
    if Y > MaxY then MaxY := Y;
  end;
end;

procedure PolygonTS(Bitmap: TBitmap32; const Points: TArrayOfFixedPoint; Color: TColor32; Mode: TPolyFillMode);
var
  L, I, MinY, MaxY: Integer;
  ScanLines: TScanLines;
  PP: TArrayOfPoint;
begin
  L := Length(Points);
  if L < 3 then Exit;
  SetLength(PP, L);

  for I := 0 to L - 1 do
    with Points[I] do
    begin
      PP[I].X := SAR_16(X + $00007FFF);
      PP[I].Y := SAR_16(Y + $00007FFF);
    end;

  GetMinMax(PP, MinY, MaxY);
  MinY := Constrain(MinY, 0, Bitmap.Height);
  MaxY := Constrain(MaxY, 0, Bitmap.Height);
  if MinY >= MaxY then Exit;

  SetLength(ScanLines, MaxY - MinY + 1);
  AddPolygon(PP, MinY, Bitmap.Width shl 8 - 1, Bitmap.Height - 1, ScanLines, True);
  SortLines(ScanLines);
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  try
    FillLines(Bitmap, MinY, ScanLines, Color, Mode);
  finally
    Bitmap.EndUpdate;
    Bitmap.Changed;
  end;
end;

procedure PolygonXS(Bitmap: TBitmap32; const Points: TArrayOfFixedPoint; Color: TColor32; Mode: TPolyFillMode);
var
  L, I, MinY, MaxY: Integer;
  ScanLines: TScanLines;
  PP: TArrayOfPoint;
begin
  L := Length(Points);
  if L < 3 then Exit;
  SetLength(PP, L);

  for I := 0 to L - 1 do
    with Points[I] do
    begin
      // use 16X oversampling (shl 4)
      PP[I].X := SAR_12(X + $00007FF); // since 16X = shl 4
      PP[I].Y := SAR_12(Y + $00007FF);
    end;

  GetMinMax(PP, MinY, MaxY);
  MinY := Constrain(MinY, 0, Bitmap.Height shl 4 - 1);
  MaxY := Constrain(MaxY, 0, Bitmap.Height shl 4 - 1);
  if MinY >= MaxY then Exit;

  SetLength(ScanLines, MaxY - MinY + 1);
  AddPolygon(PP, MinY, Bitmap.Width shl 4 - 1, Bitmap.Height shl 4 - 1,
    ScanLines, False);
  SortLines(ScanLines);
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  try
    FillLines2(Bitmap, MinY, ScanLines, Color, Mode);
  finally
    Bitmap.EndUpdate;
    Bitmap.Changed;
  end;
end;

procedure PolyPolygonTS(Bitmap: TBitmap32; const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32; Mode: TPolyFillMode = pfAlternate);
var
  L, I, J, min, max, MinY, MaxY: Integer;
  ScanLines: TScanLines;
  PP: TArrayOfArrayOfPoint;
begin
  SetLength(PP, Length(Points));

  for J := 0 to High(Points) do
  begin
    L := Length(Points[J]);
    SetLength(PP[J], L);
    for I := 0 to L - 1 do
      with Points[J][I] do
      begin
        PP[J][I].X := SAR_16(X + $00007FFF);
        PP[J][I].Y := SAR_16(Y + $00007FFF);
      end;
  end;

  MaxY := -100000;
  MinY := 100000;
  for J := 0 to High(PP) do
  begin
    GetMinMax(PP[J], min, max);
    if min < MinY then MinY := min;
    if max > MaxY then MaxY := max;
  end;

  MinY := Constrain(MinY, 0, Bitmap.Height);
  MaxY := Constrain(MaxY, 0, Bitmap.Height);
  if MinY >= MaxY then Exit;

  SetLength(ScanLines, MaxY - MinY + 1);
  for J := 0 to High(Points) do
    AddPolygon(PP[J], MinY, Bitmap.Width shl 8 - 1, Bitmap.Height - 1, ScanLines, True);
    
  SortLines(ScanLines);
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  try
    FillLines(Bitmap, MinY, ScanLines, Color, Mode);
  finally
    Bitmap.EndUpdate;
    Bitmap.Changed;
  end;
end;

procedure PolyPolygonXS(Bitmap: TBitmap32; const Points: TArrayOfArrayOfFixedPoint;
  Color: TColor32; Mode: TPolyFillMode = pfAlternate);
var
  L, I, J, min, max, MinY, MaxY: Integer;
  ScanLines: TScanLines;
  PP: TArrayOfArrayOfPoint;
begin
  SetLength(PP, Length(Points));

  for J := 0 to High(Points) do
  begin
    L := Length(Points[J]);
    if L > 2 then
    begin
      SetLength(PP[J], L);
      for I := 0 to L - 1 do
        with Points[J][I] do
        begin
          PP[J][I].X := SAR_12(X + $000007FF);
          PP[J][I].Y := SAR_12(Y + $000007FF);
        end;
    end
    else SetLength(PP[J], 0);
  end;

  MaxY := -100000;
  MinY := 100000;
  for J := 0 to High(PP) do
  begin
    GetMinMax(PP[J], min, max);
    if min < MinY then MinY := min;
    if max > MaxY then MaxY := max;
  end;

  MinY := Constrain(MinY, 0, Bitmap.Height shl 4 - 1);
  MaxY := Constrain(MaxY, 0, Bitmap.Height shl 4 - 1);
  if MinY >= MaxY then Exit;

  SetLength(ScanLines, MaxY - MinY + 1);
  for J := 0 to High(Points) do
    AddPolygon(PP[J], MinY, Bitmap.Width shl 4 - 1, Bitmap.Height shl 4 - 1, ScanLines, False);

  SortLines(ScanLines);
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  try
    FillLines2(Bitmap, MinY, ScanLines, Color, Mode);
  finally
    Bitmap.EndUpdate;
    Bitmap.Changed;
  end;
end;

{ TPolygon32 }

procedure TPolygon32.Add(const P: TFixedPoint);
var
  H, L: Integer;
begin
  H := High(Points);
  L := Length(Points[H]);
  SetLength(Points[H], L + 1);
  Points[H][L] := P;
  ClearNormals;
end;

procedure TPolygon32.BuildNormals;
var
  I, J, Count, NextI: Integer;
  dx, dy, r: Single;
begin
  if Length(Normals) <> 0 then Exit;

  SetLength(FNormals, Length(Points));

  for J := 0 to High(Points) do
  begin
    Count := Length(Points[J]);
    SetLength(Normals[J], Count);

    if Count = 0 then Exit;
    if Count = 1 then
    begin
      FillChar(Normals[J][0], SizeOf(TFixedPoint), 0);
      Exit;
    end;

    I := 0;
    NextI := 1;
    dx := 0;
    dy := 0;

    while I < Count do
    begin
      if Closed and (NextI >= Count) then NextI := 0;
      if NextI < Count then
      begin
        dx := (Points[J][NextI].X - Points[J][I].X) / $10000;
        dy := (Points[J][NextI].Y - Points[J][I].Y) / $10000;
      end;
      if (dx <> 0) or (dy <> 0) then
      begin
        r := Hypot(dx, dy);
        dx := dx / r;
        dy := dy / r;
      end;
      with Normals[J][I] do
      begin
        X := Fixed(dy);
        Y := Fixed(-dx);
      end;
      Inc(I);
      Inc(NextI);
    end;
  end;
end;

procedure TPolygon32.Clear;
var
  I: Integer;
begin
  for I := 0 to High(Points) do Points[I] := nil;
  Points := nil;
  ClearNormals;
  NewLine;
end;

procedure TPolygon32.ClearNormals;
var
  I: Integer;
begin
  for I := 0 to High(Normals) do Normals[I] := nil;
end;

constructor TPolygon32.Create;
begin
  FClosed := True;
  NewLine; // initiate a new contour
end;

destructor TPolygon32.Destroy;
begin
  Clear;
  inherited;
end;

procedure TPolygon32.Draw(Bitmap: TBitmap32; OutlineColor,
  FillColor: TColor32);
begin
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  if Antialiased then
  begin
    if (FillColor and $FF000000) <> 0 then
      PolyPolygonXS(Bitmap, Points, FillColor, FillMode);
    if (OutlineColor and $FF000000) <> 0 then
      PolyPolylineXS(Bitmap, Points, OutlineColor, Closed);
  end
  else
  begin
    if (FillColor and $FF000000) <> 0 then
      PolyPolygonTS(Bitmap, Points, FillColor, FillMode);
    if (OutlineColor and $FF000000) <> 0 then
      PolyPolylineTS(Bitmap, Points, OutlineColor, Closed);
  end;
  Bitmap.EndUpdate;
  Bitmap.Changed;
end;

procedure TPolygon32.DrawEdge(Bitmap: TBitmap32; Color: TColor32);
begin
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  if Antialiased then PolyPolylineXS(Bitmap, Points, Color, Closed)
  else PolyPolylineTS(Bitmap, Points, Color, Closed);
  Bitmap.EndUpdate;
  Bitmap.Changed;
end;

procedure TPolygon32.DrawFill(Bitmap: TBitmap32; Color: TColor32);
begin
  Bitmap.Changing;
  Bitmap.BeginUpdate;
  if Antialiased then PolyPolygonXS(Bitmap, Points, Color, FillMode)
  else PolyPolygonTS(Bitmap, Points, Color, FillMode);
  Bitmap.EndUpdate;
  Bitmap.Changed;
end;

function TPolygon32.Grow(const Delta: TFixed; EdgeSharpness: Single = 0): TPolygon32;
var
  J, I, PrevI: Integer;
  PX, PY, AX, AY, BX, BY, CX, CY, R, D, E: Integer;

  procedure AddPoint(LongDeltaX, LongDeltaY: Integer);
  var
    N, L: Integer;
  begin
    with Result do
    begin
      N := High(Points);
      L := Length(Points[N]);
      SetLength(Points[N], L + 1);
    end;
    with Result.Points[N][L] do
    begin
      X := PX + LongDeltaX;
      Y := PY + LongDeltaY;
    end;
  end;
begin
  BuildNormals;

  if EdgeSharpness > 0.99 then EdgeSharpness := 0.99
  else if EdgeSharpness < 0 then EdgeSharpness := 0;

  D := Delta;
  E := Round(D * (1 - EdgeSharpness));

  Result := TPolygon32.Create;
  Result.Antialiased := Antialiased;
  Result.Closed := Closed;
  Result.FillMode := FillMode;

  if Delta = 0 then
  begin
    // simply copy the data
    for J := 0 to High(Points) do
      Result.Points[J] := Copy(Points[J], 0, Length(Points[J]));
    Exit;
  end;

  Result.Points := nil;

  for J := 0 to High(Points) do
  begin
    if Length(Points[J]) < 2 then Continue;

    Result.NewLine;

    for I := 0 to High(Points[J]) do
    begin
      with Points[J][I] do
      begin
        PX := X;
        PY := Y;
      end;

      with Normals[J][I] do
      begin
        BX := MulDiv(X, D, $10000);
        BY := MulDiv(Y, D, $10000);
      end;

      if (I > 0) or Closed then
      begin
        PrevI := I - 1;
        if PrevI < 0 then PrevI := High(Points[J]);
        with Normals[J][PrevI] do
        begin
          AX := MulDiv(X, D, $10000);
          AY := MulDiv(Y, D, $10000);
        end;

        if (I = High(Points[J])) and (not Closed) then AddPoint(AX, AY)
        else
        begin
          CX := AX + BX;
          CY := AY + BY;
          R := MulDiv(AX, CX, D) + MulDiv(AY, CY, D);
          if R > E then AddPoint(MulDiv(CX, D, R), MulDiv(CY, D, R))
          else
          begin
            AddPoint(AX, AY);
            AddPoint(BX, BY);
          end;
        end;
      end
      else AddPoint(BX, BY);
    end;
  end;
end;

procedure TPolygon32.NewLine;
begin
  SetLength(FPoints, Length(Points) + 1);
  Normals := nil;
end;

procedure TPolygon32.Offset(const Dx, Dy: TFixed);
var
  J, I: Integer;
begin
  for J := 0 to High(Points) do
    for I := 0 to High(Points[J]) do
      with Points[J][I] do
      begin
        Inc(X, Dx);
        Inc(Y, Dy);
      end;
end;

function TPolygon32.Outline: TPolygon32;
var
  J, I: Integer;
begin
  BuildNormals;

  Result := TPolygon32.Create;
  Result.Antialiased := Antialiased;
  Result.Closed := Closed;
  Result.FillMode := FillMode;

  Result.Points := nil;

  for J := 0 to High(Points) do
  begin
    if Length(Points[J]) < 2 then Continue;

    if Closed then
    begin
      Result.NewLine;
      for I := 0 to High(Points[J]) do Result.Add(Points[J][I]);
      Result.NewLine;
      for I := High(Points[J]) downto 0 do Result.Add(Points[J][I]);
    end
    else // not closed
    begin
      Result.NewLine;
      for I := 0 to High(Points[J]) do Result.Add(Points[J][I]);
      for I := High(Points[J]) downto 0 do Result.Add(Points[J][I]);
    end;
  end;
end;

end.
