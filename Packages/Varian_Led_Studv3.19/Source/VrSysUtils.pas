{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrSysUtils;

{$I VRLIB.INC}

interface

uses
  Windows, Classes, SysUtils, Graphics, Controls, Messages,
  VrTypes, Forms;


function SolveForX(Y, Z: Longint): Longint;

function SolveForY(X, Z: Longint): Longint;

procedure FreeObject(AObject: TObject);

function MinIntVal(X, Y: Integer): Integer;

function MaxIntVal(X, Y: Integer): Integer;

function InRange(Value, X, Y: Integer): boolean;

procedure AdjustRange(var Value: Integer; X, Y: Integer);

function Percent(a, b: Integer): Integer;

function WidthOf(const R: TRect): Integer;

function HeightOf(const R: TRect): Integer;

procedure AllocateBitmaps(var Items: array of TBitmap);

procedure DeallocateBitmaps(var Items: array of TBitmap);

function Color2RGB(Color: TColor): Longint;

procedure ClearBitmapCanvas(R: TRect; Bitmap: TBitmap; Color: TColor);

procedure DrawShape(Canvas: TCanvas; Shape: TVrShapeType; X, Y, W, H: Integer);

procedure CalcTextBounds(Canvas: TCanvas; const Client: TRect;
  var TextBounds: TRect; const Caption: string);

procedure DrawButtonText(Canvas: TCanvas; const Caption: string;
  TextBounds: TRect; Enabled: Boolean);

function CreateDitherPattern(Light, Face: TColor): TBitmap;

procedure CalcImageTextLayout(Canvas: TCanvas; const Client: TRect;
  const Offset: TPoint; const Caption: string; Layout: TVrImageTextLayout;
  Margin, Spacing: Integer; ImageSize: TPoint; var ImagePos: TPoint;
  var TextBounds: TRect);

procedure DrawOutline3D(Canvas: TCanvas; var Rect: TRect;
  TopColor, BottomColor: TColor; Width: Integer);

procedure DrawFrame3D(Canvas: TCanvas; var Rect: TRect;
  TopColor, BottomColor: TColor; Width: Integer);

procedure DrawGradient(Canvas: TCanvas; const Rect: TRect; StartColor,
  TargetColor: TColor; Orientation: TVrOrientation; LineWidth: Integer);

procedure CopyParentImage(Control: TControl; Dest: TCanvas);

function GetOwnerControl(Component: TComponent): TComponent;

procedure SetCanvasTextAngle(Canvas: TCanvas; Angle: Word);

procedure CanvasTextOutAngle(Canvas: TCanvas; X, Y: Integer;
  Angle: Word; const Text: string);

function GetTextSize(Canvas: TCanvas; const Text: string): TPoint;

procedure Draw3DText(Canvas: TCanvas; X, Y: Integer; const Text: String;
  HighEdge, LowEdge: TColor);

procedure DrawShadowTextExt(Canvas: TCanvas; X, Y : Integer;
  const Text: string; ShadowColor: TColor; SX, SY: Integer);

procedure StretchPaintOnText(Dest: TCanvas; DestRect: TRect; X, Y: Integer;
  const Text: string; Bitmap: TBitmap; Angle: Word);

procedure DrawOutlinedText(Canvas: TCanvas; X, Y : Integer;
  const Text: string; Color: TColor; Depth: Integer);

procedure DrawRasterPattern(Canvas: TCanvas; Rect: TRect;
  ForeColor, BackColor: TColor; PixelSize, Spacing: Integer);

procedure StretchPaintOnRasterPattern(Dest: TCanvas; Rect: TRect; Image: TBitmap;
  ForeColor, BackColor: TColor; PixelSize, Spacing: Integer);

procedure BitmapToLCD(Dest: TBitmap; Source: TBitmap;
  ForeColor, BackColor: TColor; PixelSize, Spacing: Integer);

procedure DrawTiledBitmap(Canvas: TCanvas; const Rect: TRect; Glyph: TBitmap);

function BitmapRect(Bitmap: TBitmap): TRect;

procedure ChangeBitmapColor(Bitmap: TBitmap; FromColor, ToColor: TColor);

procedure DrawBitmap(Canvas: TCanvas; DestRect: TRect;
  Bitmap: TBitmap; SourceRect: TRect; Transparent: Boolean; TransColor: TColor);


implementation

{ This function solves for x in the equation "x is y% of z". }
function SolveForX(Y, Z: Longint): Longint;
begin
  Result := Trunc( Z * (Y * 0.01) );
end;

{ This function solves for y in the equation "x is y% of z". }
function SolveForY(X, Z: Longint): Longint;
begin
  if Z = 0 then Result := 0
  else Result := Trunc( (X * 100.0) / Z );
end;

{$HINTS OFF}
procedure FreeObject(AObject: TObject);
begin
  if AObject <> nil then
  begin
    AObject.Free;
    AObject := nil;
  end;
end;
{$HINTS ON}

function MinIntVal(X, Y: Integer): Integer;
begin
  Result := X;
  if X > Y then Result := Y;
end;

function MaxIntVal(X, Y: Integer): Integer;
begin
  Result := Y;
  if X > Y then Result := X;
end;

function InRange(Value, X, Y: Integer): boolean;
begin
  Result := (Value >= X) and (Value <= Y);
end;

procedure AdjustRange(var Value: Integer; X, Y: Integer);
begin
  if Value < X then Value := X
  else if Value > Y then Value := Y;
end;

function Percent(a, b: Integer): Integer;
begin
  Result := Trunc((a / b)*100);
end;

function WidthOf(const R: TRect): Integer;
begin
  Result := R.Right - R.Left;
end;

function HeightOf(const R: TRect): Integer;
begin
  Result := R.Bottom - R.Top;
end;

procedure AllocateBitmaps(var Items: array of TBitmap);
var
  I: Integer;
begin
  for I := Low(Items) to High(Items) do
    Items[I] := TBitmap.Create;
end;

procedure DeallocateBitmaps(var Items: array of TBitmap);
var
  I: Integer;
begin
  for I := Low(Items) to High(Items) do
    if Items[I] <> nil then
    begin
      Items[I].Free;
      Items[I] := nil;
    end;
end;

type
  TRGBMap = packed record
    case boolean of
      TRUE:  (RGBVal: DWORD);
      FALSE: (Red, Green, Blue, Unused: byte);
  end;

  TParentControl = class(TWinControl);


{ CorrectColor }
function CorrectColor(C: Real) : Integer;
begin
  Result := Round(C);
  if Result > 255 then Result := 255
  else if Result < 0 then Result := 0;
end;

{ ERGB }
function ERGB(R, G, B: Real): TColor;
begin
  Result := RGB(CorrectColor(R), CorrectColor(G), CorrectColor(B));
end;

{ Color2RGB }
function Color2RGB(Color: TColor): Longint;
begin
  if Color < 0 then
    Result := GetSysColor(Color and $000000FF)
  else Result := Color;
end;

{ DrawGradientHorizontal }
procedure DrawGradientHorizontal(Canvas: TCanvas; const Rect: TRect;
  R1, G1, B1, R2, G2, B2: Integer; LineWidth: Integer);
var
  R, G, B: Real;
  Width, Height, I: Integer;
  ColorRect: TRect;
begin
  Width := WidthOf(Rect);
  Height := HeightOf(Rect);
  ColorRect := Bounds(Rect.Left, Rect.Top, LineWidth, Height);
  R := R1; G := G1; B := B1;
  I := 0;
  while I <= Width do
  begin
    Canvas.Brush.Color := ERGB(R, G, B);
    Canvas.FillRect(ColorRect);
    OffsetRect(ColorRect, LineWidth, 0);
    Inc(I, LineWidth);
    R := R + R2 / Width * LineWidth;
    G := G + G2 / Width * LineWidth;
    B := B + B2 / Width * LineWidth;
  end;
end;

{ DrawGradientVertical }
procedure DrawGradientVertical(Canvas: TCanvas; const Rect: TRect;
  R1, G1, B1, R2, G2, B2: Integer; LineWidth: Integer);
var
  R, G, B: Real;
  Width, Height, I: Integer;
  ColorRect: TRect;
begin
  Width := WidthOf(Rect);
  Height := HeightOf(Rect);
  ColorRect := Bounds(Rect.Left, Rect.Top, Width, LineWidth);
  R := R1; G := G1; B := B1;
  I := 0;
  while I <= Height do
  begin
    Canvas.Brush.Color := ERGB(R, G, B);
    Canvas.FillRect(ColorRect);
    OffsetRect(ColorRect, 0, LineWidth);
    Inc(I, LineWidth);
    R := R + R2 / Height * LineWidth;
    G := G + G2 / Height * LineWidth;
    B := B + B2 / Height * LineWidth;
  end;
end;

{ DrawGradient }
procedure DrawGradient(Canvas: TCanvas; const Rect: TRect; StartColor,
  TargetColor: TColor; Orientation: TVrOrientation; LineWidth: Integer);
var
  R1,G1,B1: Integer;
  R2,G2,B2: Integer;
begin
  //Implement Top Color
  StartColor := Color2RGB(StartColor);
  R1 := GetRValue(StartColor);
  G1 := GetGValue(StartColor);
  B1 := GetBValue(StartColor);

  //Implement Bottom Color
  TargetColor := Color2RGB(TargetColor);
  R2 := GetRValue(TargetColor) - R1;
  G2 := GetGValue(TargetColor) - G1;
  B2 := GetBValue(TargetColor) - B1;

  case Orientation of
    voVertical:
     DrawGradientVertical(Canvas, Rect, R1, G1, B1, R2, G2, B2, LineWidth);
    voHorizontal:
     DrawGradientHorizontal(Canvas, Rect, R1, G1, B1, R2, G2, B2, LineWidth);
  end;
end;

{ DrawShape }
procedure DrawShape(Canvas: TCanvas; Shape: TVrShapeType; X, Y, W, H: Integer);
var
  S: Integer;
begin
  with Canvas do
  begin
    if Pen.Width = 0 then
    begin
      Dec(W);
      Dec(H);
    end;
    if W < H then S := W else S := H;
    if Shape in [stSquare, stRoundSquare, stCircle] then
    begin
      Inc(X, (W - S) div 2);
      Inc(Y, (H - S) div 2);
      W := S;
      H := S;
    end;
    case Shape of
      stRectangle, stSquare:
        Rectangle(X, Y, X + W, Y + H);
      stRoundRect, stRoundSquare:
        RoundRect(X, Y, X + W, Y + H, S div 4, S div 4);
      stCircle, stEllipse:
        Ellipse(X, Y, X + W, Y + H);
    end;
  end;
end;

{ CalcTextBounds }
procedure CalcTextBounds(Canvas: TCanvas; const Client: TRect;
  var TextBounds: TRect; const Caption: string);
var
  X, Y: Integer;
  TextSize: TPoint;
begin
  TextBounds := Rect(0, 0, Client.Right - Client.Left, 0);
  DrawText(Canvas.Handle, PChar(Caption), Length(Caption), TextBounds, DT_CALCRECT);
  TextSize := Point(TextBounds.Right - TextBounds.Left,
    TextBounds.Bottom - TextBounds.Top);

  X := (WidthOf(Client) - TextSize.X + 1) div 2;
  Y := (HeightOf(Client) - TextSize.Y + 1) div 2;
  OffsetRect(TextBounds, Client.Left + X, Client.Top + Y);
end;

{ DrawButtonText }
procedure DrawButtonText(Canvas: TCanvas; const Caption: string;
  TextBounds: TRect; Enabled: Boolean);
begin
  with Canvas do
  begin
    Brush.Style := bsClear;
    if not Enabled then
    begin
      OffsetRect(TextBounds, 1, 1);
      Font.Color := clBtnHighlight;
      DrawText(Handle, PChar(Caption), Length(Caption), TextBounds, 0);
      OffsetRect(TextBounds, -1, -1);
      Font.Color := clBtnShadow;
      DrawText(Handle, PChar(Caption), Length(Caption), TextBounds, 0);
    end else
      DrawText(Handle, PChar(Caption), Length(Caption), TextBounds,
        DT_CENTER or DT_VCENTER or DT_SINGLELINE);
  end;
end;

{ ClearBitmapCanvas }
procedure ClearBitmapCanvas(R: TRect; Bitmap: TBitmap; Color: TColor);
begin
  Bitmap.Width := WidthOf(R);
  Bitmap.Height := HeightOf(R);
  with Bitmap.Canvas do
  begin
    Brush.Color := Color;
    Brush.Style := bsSolid;
    FillRect(R);
  end;
end;

{ CreateDitherPattern }
function CreateDitherPattern(Light, Face: TColor): TBitmap;
var
  X, Y: Integer;
begin
  Result := TBitmap.Create;
  Result.Width := 8;
  Result.Height := 8;
  with Result.Canvas do
  begin
    Brush.Color := Face;
    Brush.Style := bsSolid;
    FillRect(Rect(0, 0, Result.Width, Result.Height));
    for Y := 0 to 7 do
      for X := 0 to 7 do
        if (Y mod 2) = (X mod 2) then Pixels[X, Y] := Light;
  end;
end;

{ CalcImageTextLayout }
procedure CalcImageTextLayout(Canvas: TCanvas; const Client: TRect;
  const Offset: TPoint; const Caption: string; Layout: TVrImageTextLayout;
  Margin, Spacing: Integer; ImageSize: TPoint; var ImagePos: TPoint;
  var TextBounds: TRect);
var
  TextPos: TPoint;
  ClientSize, TextSize: TPoint;
  TotalSize: TPoint;
begin
  ClientSize := Point(Client.Right - Client.Left, Client.Bottom -
    Client.Top);

  if Length(Caption) > 0 then
  begin
    TextBounds := Rect(0, 0, Client.Right - Client.Left, 0);
    DrawText(Canvas.Handle, PChar(Caption), Length(Caption), TextBounds, DT_CALCRECT);
    TextSize := Point(TextBounds.Right - TextBounds.Left, TextBounds.Bottom -
      TextBounds.Top);
  end
  else
  begin
    TextBounds := Rect(0, 0, 0, 0);
    TextSize := Point(0,0);
  end;

  if Layout in [ImageLeft, ImageRight] then
  begin
    ImagePos.Y := (ClientSize.Y - ImageSize.Y + 1) div 2;
    TextPos.Y := (ClientSize.Y - TextSize.Y + 1) div 2;
  end
  else
  begin
    ImagePos.X := (ClientSize.X - ImageSize.X + 1) div 2;
    TextPos.X := (ClientSize.X - TextSize.X + 1) div 2;
  end;

  if (TextSize.X = 0) or (ImageSize.X = 0) then
    Spacing := 0;

  if Margin = -1 then
  begin
    if Spacing = -1 then
    begin
      TotalSize := Point(ImageSize.X + TextSize.X, ImageSize.Y + TextSize.Y);
      if Layout in [ImageLeft, ImageRight] then
        Margin := (ClientSize.X - TotalSize.X) div 3
      else
        Margin := (ClientSize.Y - TotalSize.Y) div 3;
      Spacing := Margin;
    end
    else
    begin
      TotalSize := Point(ImageSize.X + Spacing + TextSize.X, ImageSize.Y +
        Spacing + TextSize.Y);
      if Layout in [ImageLeft, ImageRight] then
        Margin := (ClientSize.X - TotalSize.X + 1) div 2
      else
        Margin := (ClientSize.Y - TotalSize.Y + 1) div 2;
    end;
  end
  else
  begin
    if Spacing = -1 then
    begin
      TotalSize := Point(ClientSize.X - (Margin + ImageSize.X), ClientSize.Y -
        (Margin + ImageSize.Y));
      if Layout in [ImageLeft, ImageRight] then
        Spacing := (TotalSize.X - TextSize.X) div 2
      else
        Spacing := (TotalSize.Y - TextSize.Y) div 2;
    end;
  end;

  case Layout of
    ImageLeft:
      begin
        ImagePos.X := Margin;
        TextPos.X := ImagePos.X + ImageSize.X + Spacing;
      end;
    ImageRight:
      begin
        ImagePos.X := ClientSize.X - Margin - ImageSize.X;
        TextPos.X := ImagePos.X - Spacing - TextSize.X;
      end;
    ImageTop:
      begin
        ImagePos.Y := Margin;
        TextPos.Y := ImagePos.Y + ImageSize.Y + Spacing;
      end;
    ImageBottom:
      begin
        ImagePos.Y := ClientSize.Y - Margin - ImageSize.Y;
        TextPos.Y := ImagePos.Y - Spacing - TextSize.Y;
      end;
  end;

  with ImagePos do
  begin
    Inc(X, Client.Left + Offset.X);
    Inc(Y, Client.Top + Offset.Y);
  end;
  OffsetRect(TextBounds, TextPos.X + Client.Left + Offset.X,
    TextPos.Y + Client.Top + Offset.X);
end;

{ Draw3DOutline - BottomLeft.X correction disabled }
procedure DrawOutline3D(Canvas: TCanvas; var Rect: TRect;
  TopColor, BottomColor: TColor; Width: Integer);

  procedure DoRect;
  var
    TopRight, BottomLeft: TPoint;
  begin
    with Canvas, Rect do
    begin
      TopRight.X := Right;
      TopRight.Y := Top;
      BottomLeft.X := Left;
      BottomLeft.Y := Bottom;
      Pen.Color := TopColor;
      PolyLine([BottomLeft, TopLeft, TopRight]);
      Pen.Color := BottomColor;
      PolyLine([TopRight, BottomRight, BottomLeft]);
    end;
  end;

begin
  Canvas.Pen.Width := 1;
  Dec(Rect.Bottom); Dec(Rect.Right);
  while Width > 0 do
  begin
    Dec(Width);
    DoRect;
    InflateRect(Rect, -1, -1);
  end;
  Inc(Rect.Bottom); Inc(Rect.Right);
end;

{ DrawFrame3D }
procedure DrawFrame3D(Canvas: TCanvas; var Rect: TRect;
  TopColor, BottomColor: TColor; Width: Integer);

  procedure DoRect;
  var
    TopRight, BottomLeft: TPoint;
  begin
    with Canvas, Rect do
    begin
      TopRight.X := Right;
      TopRight.Y := Top;
      BottomLeft.X := Left;
      BottomLeft.Y := Bottom;
      Pen.Color := TopColor;
      PolyLine([BottomLeft, TopLeft, TopRight]);
      Pen.Color := BottomColor;
      Dec(BottomLeft.X);
      PolyLine([TopRight, BottomRight, BottomLeft]);
    end;
  end;

begin
  Canvas.Pen.Width := 1;
  Dec(Rect.Bottom); Dec(Rect.Right);
  while Width > 0 do
  begin
    Dec(Width);
    DoRect;
    InflateRect(Rect, -1, -1);
  end;
  Inc(Rect.Bottom); Inc(Rect.Right);
end;

procedure CopyParentImage(Control: TControl; Dest: TCanvas);
var
  I, Count, X, Y, SaveIndex: Integer;
  DC: HDC;
  R, SelfR, CtlR: TRect;
begin
  if (Control = nil) or (Control.Parent = nil) then Exit;
  Count := Control.Parent.ControlCount;
  DC := Dest.Handle;
  with Control.Parent do ControlState := ControlState + [csPaintCopy];
  try
    with Control do
    begin
      SelfR := Bounds(Left, Top, Width, Height);
      X := -Left; Y := -Top;
    end;
    { Copy parent control image }
    SaveIndex := SaveDC(DC);
    try
      SetViewportOrgEx(DC, X, Y, nil);
      IntersectClipRect(DC, 0, 0, Control.Parent.ClientWidth,
        Control.Parent.ClientHeight);
      with TParentControl(Control.Parent) do
      begin
        Perform(WM_ERASEBKGND, DC, 0);
        PaintWindow(DC);
      end;
    finally
      RestoreDC(DC, SaveIndex);
    end;
    { Copy images of graphic controls }
    for I := 0 to Count - 1 do begin
      if Control.Parent.Controls[I] = Control then Break
      else if (Control.Parent.Controls[I] <> nil) and
        (Control.Parent.Controls[I] is TGraphicControl) then
      begin
        with TGraphicControl(Control.Parent.Controls[I]) do
        begin
          CtlR := Bounds(Left, Top, Width, Height);
          if Bool(IntersectRect(R, SelfR, CtlR)) and Visible then
          begin
            ControlState := ControlState + [csPaintCopy];
            SaveIndex := SaveDC(DC);
            try
              SetViewportOrgEx(DC, Left + X, Top + Y, nil);
              IntersectClipRect(DC, 0, 0, Width, Height);
              Perform(WM_PAINT, DC, 0);
            finally
              RestoreDC(DC, SaveIndex);
              ControlState := ControlState - [csPaintCopy];
            end;
          end;
        end;
      end;
    end;
  finally
    with Control.Parent do ControlState := ControlState - [csPaintCopy];
  end;
end;

{ GetOwnerControl }
function GetOwnerControl(Component: TComponent): TComponent;
var
  AOwner: TComponent;
begin
  Result := nil;
  AOwner := Component.Owner;
  while (AOwner <> nil) and (AOwner is TWinControl) do
  begin
    Result := AOwner;
    AOwner := Result.Owner;
  end;
end;

{ SetCanvasTextAngle }
procedure SetCanvasTextAngle(Canvas: TCanvas; Angle: Word);
var
  LogRec: TLOGFONT;
begin
  GetObject(Canvas.Font.Handle, SizeOf(LogRec), Addr(LogRec));
  LogRec.lfEscapement := Angle * 10;
  Canvas.Font.Handle := CreateFontIndirect(LogRec);
end;

{ CanvasTextOutAngle }
procedure CanvasTextOutAngle(Canvas: TCanvas; X, Y: Integer;
  Angle: Word; const Text: string);
var
  LogRec: TLOGFONT;
  OldFontHandle,
  NewFontHandle: HFONT;
begin
  GetObject(Canvas.Font.Handle, SizeOf(LogRec), Addr(LogRec));
  LogRec.lfEscapement := Angle * 10;
  NewFontHandle := CreateFontIndirect(LogRec);
  OldFontHandle := SelectObject(Canvas.Handle, NewFontHandle);
  Canvas.TextOut(X, Y, Text);
  NewFontHandle := SelectObject(Canvas.Handle, OldFontHandle);
  DeleteObject(NewFontHandle);
end;

{ GetTextSize }
function GetTextSize(Canvas: TCanvas; const Text: string): TPoint;
var
  TextBounds: TRect;
begin
  TextBounds := Rect(0, 0, 0, 0);
  DrawText(Canvas.Handle, PChar(Text), Length(Text), TextBounds, DT_CALCRECT);
  Result := Point(TextBounds.Right - TextBounds.Left,
    TextBounds.Bottom - TextBounds.Top);
end;

{ Draw3DText }
procedure Draw3DText(Canvas: TCanvas; X, Y: Integer; const Text: String;
  HighEdge, LowEdge: TColor);
var
  OrgColor: TColor;
begin
  with Canvas do
  begin
    OrgColor := Font.Color;
    Brush.Style := bsClear;
    Font.Color := LowEdge;
    TextOut(X + 1, Y + 1, Text);
    Font.Color := HighEdge;
    TextOut(X - 1, Y - 1, Text);
    Font.Color := OrgColor;
    TextOut(X, Y, Text);
  end;
end;

{ DrawShadowTextExt }
procedure DrawShadowTextExt(Canvas: TCanvas; X, Y : Integer; const Text: string;
  ShadowColor: TColor; SX, SY: Integer);
var
  OrgColor: TColor;
begin
  with Canvas do
  begin
    OrgColor := Font.Color;
    Brush.Style := bsClear;
    Font.Color := ShadowColor;
    TextOut(X + SX, Y + SY, Text);
    Font.Color := OrgColor;
    TextOut(X, Y, Text);
  end;
end;

{ StretchPaintOnText }
procedure StretchPaintOnText(Dest: TCanvas; DestRect: TRect; X, Y : Integer;
  const Text: String; Bitmap: TBitmap; Angle: Word);
var
  R: TRect;
  FMask, FStore: TBitmap;
begin
  FMask := TBitmap.Create;
  try
    with FMask, FMask.Canvas do
    begin
      Monochrome := True;
      Font.Assign(Dest.Font);
      Font.Color := clBlack;
      Width := WidthOf(DestRect);
      Height := HeightOf(DestRect);
      SetCanvasTextAngle(FMask.Canvas, Angle);
      TextOut(X, Y, Text);
    end;

    FStore := TBitmap.Create;
    try
      with FStore do
      begin
        Width := FMask.Width;
        Height := FMask.Height;
        R := Rect(0, 0, Width, Height);
        with Canvas do
        begin
          CopyRect(R, Dest, Bounds(0, 0, Width, Height));
          CopyMode := cmSrcInvert;
          StretchDraw(R, Bitmap);
          CopyMode := cmSrcAnd;
          Draw(0, 0, FMask);
          CopyMode := cmSrcInvert;
          StretchDraw(R, Bitmap);
        end;
      end;
      Dest.Draw(0, 0, FStore);
    finally
      FStore.Free;
    end;

  finally
    FMask.Free;
  end;
end;

{ DrawOutlinedText }
procedure DrawOutlinedText(Canvas: TCanvas; X, Y : Integer; const Text: String;
  Color: TColor; Depth: Integer);
var
  I: Integer;
  Tmp: TColor;
begin
  with Canvas do
  begin
    Tmp := Font.Color;
    Font.Color := Color;
    Brush.Style := bsClear;
    for I := 1 to Depth do
    begin
      TextOut(X + I, Y + I, Text);
      TextOut(X - I, Y + I, Text);
      TextOut(X - I, Y - I, Text);
      TextOut(X + I, Y - I, Text);
    end;
    Font.Color := Tmp;
    TextOut(X, Y, Text);
  end;
end;

{ DrawRasterPattern }
procedure DrawRasterPattern(Canvas: TCanvas; Rect: TRect;
  ForeColor, BackColor: TColor; PixelSize, Spacing: Integer);
var
  R: TRect;
  X, Y: Integer;
  Bitmap: TBitmap;
begin
  Bitmap := TBitmap.Create;
  try
    Bitmap.Width := (PixelSize + Spacing) * 20;
    Bitmap.Height := Bitmap.Width;

    with Bitmap do
    begin
      Canvas.Brush.Color := BackColor;
      Canvas.FillRect(Rect);
      Canvas.Brush.Color := ForeColor;
      X := 0;
      while X <= Width do
      begin
        Y := 0;
        while Y <= Height do
        begin
          R := Bounds(X, Y, PixelSize, PixelSize);
          Canvas.FillRect(R);
          Inc(Y, PixelSize + Spacing);
        end;
        Inc(X, PixelSize + Spacing);
      end;
    end;

    with Canvas do
    begin
      X := Rect.Left;
      while X < Rect.Right do
      begin
        Y := Rect.Top;
        while Y < Rect.Bottom do
        begin
          Draw(X, Y, Bitmap);
          Inc(Y, Bitmap.Height);
        end;
        Inc(X, Bitmap.Width);
      end;
    end;

  finally
    Bitmap.Free;
  end;
end;

{ StretchPaintOnText }
procedure StretchPaintOnRasterPattern(Dest: TCanvas; Rect: TRect;
  Image: TBitmap; ForeColor, BackColor: TColor; PixelSize, Spacing: Integer);
var
  R: TRect;
  FMask, FStore: TBitmap;
begin
  FMask := TBitmap.Create;
  try
    with FMask, FMask.Canvas do
    begin
      Width := WidthOf(Rect);
      Height := HeightOf(Rect);
      DrawRasterPattern(FMask.Canvas, Bounds(0, 0, Width, Height),
        clBlack, clWhite, PixelSize, Spacing);
    end;

    FStore := TBitmap.Create;
    try
      with FStore do
      begin
        Width := FMask.Width;
        Height := FMask.Height;
        R := Classes.Rect(0, 0, Width, Height);
        DrawRasterPattern(Canvas, R, ForeColor, BackColor,
          PixelSize, Spacing);
        with Canvas do
        begin
          CopyMode := cmSrcInvert;
          StretchDraw(R, Image);
          CopyMode := cmSrcAnd;
          Draw(0, 0, FMask);
          CopyMode := cmSrcInvert;
          StretchDraw(R, Image);
        end;
      end;

      Dest.Draw(0, 0, FStore);
    finally
      FStore.Free;
    end;
  finally
    FMask.Free;
  end;
end;

{ BitmapToLCD }
procedure BitmapToLCD(Dest: TBitmap; Source: TBitmap;
  ForeColor, BackColor: TColor; PixelSize, Spacing: Integer);
var
  R: TRect;
  FMask, FStore: TBitmap;
begin
  Dest.Width := Source.Width * (PixelSize + Spacing);
  Dest.Height := Source.Height * (PixelSize + Spacing);

  FMask := TBitmap.Create;
  try
    with FMask, FMask.Canvas do
    begin
      Width := Dest.Width;
      Height := Dest.Height;
      DrawRasterPattern(FMask.Canvas, Bounds(0, 0, Width, Height),
        clBlack, clWhite, PixelSize, Spacing);
    end;

    FStore := TBitmap.Create;
    try
      with FStore do
      begin
        Width := FMask.Width;
        Height := FMask.Height;
        R := Classes.Rect(0, 0, Width, Height);
        DrawRasterPattern(Canvas, R, ForeColor, BackColor,
          PixelSize, Spacing);
        with Canvas do
        begin
          CopyMode := cmSrcInvert;
          StretchDraw(R, Source);
          CopyMode := cmSrcAnd;
          Draw(0, 0, FMask);
          CopyMode := cmSrcInvert;
          StretchDraw(R, Source);
        end;
      end;

      Dest.Canvas.Draw(0, 0, FStore);
    finally
      FStore.Free;
    end;
  finally
    FMask.Free;
  end;
end;

{ DrawTiledBitmap - no clipping}
procedure DrawTiledBitmap(Canvas: TCanvas; const Rect: TRect; Glyph: TBitmap);
var
  X, Y: Integer;
begin
  X := Rect.Left;
  while X < Rect.Right do
  begin
    Y := Rect.Top;
    while Y < Rect.Bottom do
    begin
      Canvas.Draw(X, Y, Glyph);
      Inc(Y, Glyph.Height);
    end;
    Inc(X, Glyph.Width);
  end;
end;

{ BitmapRect }
function BitmapRect(Bitmap: TBitmap): TRect;
begin
  Result := Bounds(0, 0, Bitmap.Width, Bitmap.Height);
end;

{ ChangeBitmapColor }
procedure ChangeBitmapColor(Bitmap: TBitmap; FromColor, ToColor: TColor);
const
  ROP_DSPDxax = $00E20746;
var
  DestDC: HDC;
  DDB, MonoBmp: TBitmap;
  IWidth, IHeight: Integer;
  IRect: TRect;
begin
  IWidth := Bitmap.Width;
  IHeight := Bitmap.Height;
  IRect := Rect(0, 0, IWidth, IHeight);

  MonoBmp := TBitmap.Create;
  DDB := TBitmap.Create;
  try
    DDB.Assign(Bitmap);
    DDB.HandleType := bmDDB;

    with Bitmap.Canvas do
    begin
      MonoBmp.Width := IWidth;
      MonoBmp.Height := IHeight;
      MonoBmp.Monochrome := True;

      { Convert white to clBtnHighlight }
      DDB.Canvas.Brush.Color := FromColor;
      MonoBmp.Canvas.CopyRect(IRect, DDB.Canvas, IRect);

      Brush.Color := ToColor;
      DestDC := Bitmap.Canvas.Handle;

      SetTextColor(DestDC, clBlack);
      SetBkColor(DestDC, clWhite);
      BitBlt(DestDC, 0, 0, IWidth, IHeight,
      MonoBmp.Canvas.Handle, 0, 0, ROP_DSPDxax);
    end;
  finally
    DDB.Free;
    MonoBmp.Free;
  end;
end;

procedure DrawBitmap(Canvas: TCanvas; DestRect: TRect;
  Bitmap: TBitmap; SourceRect: TRect; Transparent: Boolean; TransColor: TColor);
begin
  with Canvas do
  begin
    if Transparent then
    begin
      Brush.Style := bsClear;
      BrushCopy(DestRect, Bitmap, SourceRect, TransColor);
    end
    else
    begin
      Brush.Style := bsSolid;
      StretchDraw(DestRect, Bitmap);
    end;
  end;
end;



end.
