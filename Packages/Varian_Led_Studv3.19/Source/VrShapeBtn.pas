{*****************************************************}
{                                                     }
{     Varian Led Studio Component Library             }
{                                                     }
{     Varian Software Services NL (c) 1996-1999       }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrShapeBtn;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs, Buttons,
  Forms, VrControls;

type
  TVrShapeBtn = class(TVrGraphicControl)
  private
    FAutoSize: Boolean;
    FBitmap: TBitmap;
    FBitmapUp: TBitmap;
    FBitmapDown: TBitmap;
    TempBitmap: TBitmap;
    procedure AdjustBounds;
    function BevelColor(const AState: TButtonState; const TopLeft: Boolean): TColor;
    procedure BitmapChanged(Sender: TObject);
    procedure Create3DBitmap(Source: TBitmap; const AState: TButtonState; Target: TBitmap);
    procedure SetBitmap(Value: TBitmap);
    procedure SetBitmapDown(Value: TBitmap);
    procedure SetBitmapUp(Value: TBitmap);
    procedure CMDialogChar(var Message: TCMDialogChar); message CM_DIALOGCHAR;
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    procedure CMSysColorChange(var Message: TMessage); message CM_SYSCOLORCHANGE;
    function PtInMask(const X, Y: Integer): Boolean;
  protected
    FState: TButtonState;
    procedure Loaded; override;
    procedure Click; override;
    procedure Paint; override;
    function GetPalette: HPALETTE; override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState;  X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState;  X, Y: Integer); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
  published
    property Bitmap: TBitmap read FBitmap write SetBitmap;
    property Caption;
    property Enabled;
    property Font;
    property ShowHint;
    property Visible;
    property OnClick;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
  end;

procedure Register;

implementation

type
  Apair = array[0..1] of Integer;


function MakeMask(ColorBmp: TBitmap; TransparentColor: TColor): TBitmap;
var
  Temp: TRect;
  OldBkColor: TColorRef;
  TmpBitmap : Tbitmap;
begin
  Result := nil;
  TmpBitmap := TBitmap.Create;
  try
    TmpBitmap.Monochrome := True;
    TmpBitmap.Width := ColorBmp.Width;
    TmpBitmap.Height := ColorBmp.Height;
    OldBkColor := SetBkColor(ColorBmp.Canvas.Handle, ColorToRGB(TransparentColor));
    Temp := Rect(0, 0, ColorBmp.Width, ColorBmp.Height);
    TmpBitmap.Canvas.CopyMode := cmSrcCopy;
    TmpBitmap.Canvas.CopyRect(Temp, ColorBmp.Canvas, Temp);
    SetBkColor(ColorBmp.Canvas.Handle, OldBkColor);
    Result := TmpBitmap;
  except
    TmpBitmap.Free;
  end;
end;

function MakeBorder(Source, NewSource: TBitmap; const OffsetPts: Array of Apair;
  TransparentColor: TColor): TBitmap;
var
  I : Integer;
  R, NewR: TRect;
  SmallMask, BigMask, NewSourceMask: TBitmap;
begin
  Result := TBitmap.Create;
  try
    R := Rect(0, 0, Source.Width, Source.Height);
    Result.Monochrome := True;
    Result.Width := Source.Width;
    Result.Height := Source.Height;

    SmallMask := MakeMask(Source, TransparentColor);
    NewSourceMask := MakeMask(NewSource, TransparentColor);
    BigMask := MakeMask(NewSourceMask, TransparentColor);

    try

      BigMask.Canvas.CopyMode := cmSrcCopy;
      BigMask.Canvas.CopyRect(R, NewSourceMask.Canvas, R);

      for I := Low(OffsetPts) to High(OffsetPts) do
      begin
        if (OffsetPts[I, 0] = 0) and (OffsetPts[I, 1] = 0) then
          Break;
        NewR := R;
        OffsetRect(NewR, OffsetPts[I, 0], OffsetPts[I, 1]);
        BigMask.Canvas.CopyMode := cmSrcAnd;
        BigMask.Canvas.CopyRect(NewR, SmallMask.Canvas, R);
      end;
      BigMask.Canvas.CopyMode := cmSrcCopy;

      with Result do
      begin
        Canvas.CopyMode := cmSrcCopy;
        Canvas.CopyRect(R, NewSourceMask.Canvas, R);
        Canvas.CopyMode := $00DD0228;
        Canvas.CopyRect(R, BigMask.Canvas, R);
        Canvas.CopyMode := cmSrcCopy;
      end;

    finally
      SmallMask.Free;
      NewSourceMask.Free;
      BigMask.Free;
    end;

  except
    Result.Free;
    Raise;
  end;

end;

constructor TVrShapeBtn.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csCaptureMouse, csOpaque];
  Width := 50;
  Height := 50;
  Color := clBtnFace;
  ParentFont := True;
  FAutoSize := True;
  FBitmap := TBitmap.Create;
  FBitmap.OnChange := BitmapChanged;
  FBitmapUp := TBitmap.Create;
  FBitmapDown := TBitmap.Create;
  TempBitmap := nil;
  FState := bsUp;
end;

destructor TVrShapeBtn.Destroy;
begin
  FBitmap.Free;
  FBitmapUp.Free;
  FBitmapDown.Free;
  TempBitmap.Free;
  inherited Destroy;
end;

procedure TVrShapeBtn.Loaded;
var
  BigMask: TBitmap;
  R: TRect;
begin
  inherited Loaded;
  if (FBitmap <> nil) and (FBitmap.Width > 0) and (FBitmap.Height > 0) then
  begin
    TempBitmap.Free;
    TempBitmap := MakeMask(FBitmap, FBitmap.TransparentColor);
    BigMask := MakeMask(FBitmapUp, FBitmap.TransparentColor);
    try
      R := Rect(0, 0, FBitmap.Width, FBitmap.Height);
      TempBitmap.Canvas.CopyMode := cmSrcAnd;
      TempBitmap.Canvas.CopyRect(R, BigMask.Canvas, R);
    finally
      BigMask.Free;
    end;
  end;
end;

procedure TVrShapeBtn.Paint;
var
  W, H: Integer;
  Composite, Mask, Overlay, CurrentBmp: TBitmap;
  R, NewR: TRect;
begin
//  R := ClientRect;
//  NewR := R;
//  Canvas.CopyRect(R, FBitmapDown.Canvas, NewR);

  if (csDesigning in ComponentState) or
    (FState in [bsDisabled, bsExclusive]) then FState := bsUp;

  if (FState = bsUp) then CurrentBmp := FBitmapUp
  else CurrentBmp := FBitmapDown;

  if not CurrentBmp.Empty then
  begin
    W := Width;
    H := Height;
    R := ClientRect;
    NewR := R;

    Composite := TBitmap.Create;
    Overlay := TBitmap.Create;

    try
      with Composite do
      begin
        Width := W;
        Height := H;
        Canvas.CopyMode := cmSrcCopy;
        Canvas.CopyRect(R, Self.Canvas, R);
      end;

      with Overlay do
      begin
        Width := W;
        Height := H;
        Canvas.CopyMode := cmSrcCopy;
        Canvas.Brush.Color := FBitmap.TransparentColor;
        Canvas.FillRect(R);
        if FState = bsDown then
          OffsetRect(NewR, 1, 1);
        Canvas.CopyRect(NewR, CurrentBmp.Canvas, R);
      end;

      Mask := MakeMask(Overlay, FBitmap.TransparentColor);
      try

        Composite.Canvas.CopyMode := cmSrcAnd;
        Composite.Canvas.CopyRect(R, Mask.Canvas, R);


        Overlay.Canvas.CopyMode := $00220326;
        Overlay.Canvas.CopyRect(R, Mask.Canvas, R);


        Composite.Canvas.CopyMode := cmSrcPaint;
        Composite.Canvas.CopyRect(R, Overlay.Canvas, R);

        Canvas.CopyMode := cmSrcCopy;
        Canvas.CopyRect(R, Composite.Canvas, R);

      finally
        Mask.Free;
      end;

    finally
      Composite.Free;
      Overlay.Free;
    end;

  end;

  R := ClientRect;
  Canvas.Font := Self.Font;
  Canvas.Brush.Style := bsClear;
  if FState = bsDown then OffsetRect(R, 1, 1);
  DrawText(Canvas.Handle, PChar(Caption), -1, R,
      DT_CENTER or DT_VCENTER or DT_SINGLELINE);

  if csDesigning in ComponentState then
    with Canvas do
    begin
      Pen.Style := psDot;
      Brush.Style := bsClear;
      Rectangle(0, 0, Width, Height);
    end;
end;

function TVrShapeBtn.PtInMask(const X, Y: Integer): Boolean;
begin
  Result := True;
  if TempBitmap <> nil then
    Result := (TempBitmap.Canvas.Pixels[X, Y] = clBlack);
end;

procedure TVrShapeBtn.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
var Clicked: Boolean;
begin
  inherited MouseDown(Button, Shift, X, Y);
  if (Button = mbLeft) and Enabled then
  begin
      Clicked := PtInMask(X, Y);

    if Clicked then
    begin
      FState := bsDown;
      Repaint;
    end;
  end;
end;

procedure TVrShapeBtn.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited MouseMove(Shift, X, Y);
end;

procedure TVrShapeBtn.MouseUp(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
var
  DoClick: Boolean;
begin
  inherited MouseUp(Button, Shift, X, Y);
  DoClick := PtInMask(X, Y);
  if (FState = bsDown) then
    begin
      FState := bsUp;
      Repaint;
    end;
    if DoClick then Click;
end;

procedure TVrShapeBtn.Click;
begin
  inherited Click;
end;

function TVrShapeBtn.GetPalette: HPALETTE;
begin
  Result := FBitmap.Palette;
end;

procedure TVrShapeBtn.SetBitmap(Value: TBitmap);
begin
  FBitmap.Assign(Value);
end;

procedure TVrShapeBtn.SetBitmapUp(Value: TBitmap);
begin
  FBitmapUp.Assign(Value);
end;

procedure TVrShapeBtn.SetBitmapDown(Value: TBitmap);
begin
  FBitmapDown.Assign(Value);
end;

procedure TVrShapeBtn.BitmapChanged(Sender: TObject);
var
  OldCursor: TCursor;
  W, H: Integer;
begin
  AdjustBounds;

  if FBitmap.Empty then
  begin
    SetBitmapUp(nil);
    SetBitmapDown(nil);
  end
  else
  begin
    W := FBitmap.Width;
    H := FBitmap.Height;
    OldCursor := Screen.Cursor;
    Screen.Cursor := crHourGlass;
    try
      if (FBitmapUp.Width <> W) or (FBitmapUp.Height <> H) or
        (FBitmapDown.Width <> W) or (FBitmapDown.Height <> H) then
      begin
        FBitmapUp.Width := W;
        FBitmapUp.Height := H;
        FBitmapDown.Width := W;
        FBitmapDown.Height := H;
      end;
      Create3DBitmap(FBitmap, bsUp, FBitmapUp);
      Create3DBitmap(FBitmap, bsDown, FBitmapDown);
      TempBitmap.Free;
      TempBitmap := MakeMask(FBitmapUp, FBitmap.TransparentColor);
    finally
      Screen.Cursor := OldCursor;
    end;
  end;

  UpdateControlCanvas;
end;

procedure TVrShapeBtn.CMDialogChar(var Message: TCMDialogChar);
begin
  with Message do
    if IsAccel(CharCode, Caption) and Enabled then
    begin
      Click;
      Result := 1;
    end else
      inherited;
end;

procedure TVrShapeBtn.CMFontChanged(var Message: TMessage);
begin
  UpdateControlCanvas;
end;

procedure TVrShapeBtn.CMTextChanged(var Message: TMessage);
begin
  UpdateControlCanvas;
end;

procedure TVrShapeBtn.CMSysColorChange(var Message: TMessage);
begin
  BitmapChanged(Self);
end;

function TVrShapeBtn.BevelColor(const AState: TButtonState; const TopLeft: Boolean): TColor;
begin
  if (AState = bsUp) then
  begin
    if TopLeft then Result := clBtnHighlight
    else Result := clBtnShadow
  end
  else { bsDown }
  begin
    if TopLeft then Result := clBtnShadow
    else Result := clBtnHighlight;
  end;
end;


procedure TVrShapeBtn.Create3DBitmap(Source: TBitmap;
  const AState: TButtonState; Target: TBitmap);
type
  OutlineOffsetPts = array[1..3, 0..1, 0..12] of Apair;
const
  OutlinePts: OutlineOffsetPts =
    ( (((1,-1),(1,0),(1,1),(0,1),(-1,1),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0)),
       ((-1,0),(-1,-1),(0,-1),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0))),
      (((2,-2),(2,-1),(2, 0),(2, 1),(2, 2),(1, 2),(0, 2),(-1,2),(-2,2),(0,0),(0,0),(0,0),(0,0)),
       ((-2,1),(-2,0),(-2,-1),(-2,-2),(-1,-2),(0,-2),(1,-2),(0,0),(0,0),(0,0),(0,0),(0,0),(0,0))),
      (((3,-3),(3,-2),(3,-1),(3,0),(3,1),(3,2),(3,3),(2,3),(1,3),(0,3),(-1,3),(-2,3),(-3,3)),
       ((-3,2),(-3,1),(-3,0),(-3,-1),(-3,-2),(-3,-3),(-2,-3),(-1,-3),(0,-3),(1,-3),(2,-3),(0,0),(0,0)))
    );
var
  I, J, W, H, Outlines: Integer;
  R: TRect;
  OutlineMask, Overlay, NewSource: TBitmap;
begin
  if (Source = nil) or (Target = nil) then
    Exit;

  W := Source.Width;
  H := Source.Height;
  R := Rect(0, 0, W, H);

  Overlay := TBitmap.Create;
  NewSource := TBitmap.Create;

  try

    NewSource.Width := W;
    NewSource.Height := H;

    Target.Canvas.CopyMode := cmSrcCopy;
    Target.Canvas.CopyRect(R, Source.Canvas, R);

    Overlay.Width := W;
    Overlay.Height := H;

    Outlines := 1;
    Inc(Outlines);

    for I := 1 to Outlines do
    begin
      with NewSource.Canvas do
      begin
        CopyMode := cmSrcCopy;
        CopyRect(R, Target.Canvas, R);
      end;

      for J := 0 to 1 do
      begin
        if (AState = bsDown) and (I = Outlines) and (J = 0) then
          Continue;

        OutlineMask := MakeBorder(Source, NewSource, OutlinePts[I, J],
                        FBitmap.TransparentColor);
        try
          with Overlay.Canvas do
          begin
            if (I = Outlines) then
              Brush.Color := clBlack
            else
              Brush.Color := BevelColor(AState, (J = 1));
            CopyMode := cmWhiteness;//$0030032A; { PSna }
            CopyRect(R, OutlineMask.Canvas, R);
          end;

          with Target.Canvas do
          begin

            CopyMode := cmSrcAnd; { DSa }
            CopyRect(R, OutlineMask.Canvas, R);

            CopyMode := cmSrcPaint; { DSo }
            CopyRect(R, Overlay.Canvas, R);
            CopyMode := cmSrcCopy;
          end;

        finally
          OutlineMask.Free;
        end;

      end;
    end;

  finally
    Overlay.Free;
    NewSource.Free;
  end;
end;


procedure TVrShapeBtn.AdjustBounds;
begin
  SetBounds(Left, Top, Width, Height);
end;

procedure TVrShapeBtn.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
var W, H: Integer;
begin
  W := AWidth;
  H := AHeight;
  if not (csReading in ComponentState) and FAutoSize and not FBitmap.Empty then
  begin
    W := FBitmap.Width;
    H := FBitmap.Height;
  end;
  inherited SetBounds(ALeft, ATop, W, H);
end;

procedure Register;
begin
  RegisterComponents('Varian Page3', [TVrShapeBtn]);
end;

end.
