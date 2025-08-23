{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrScale;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrScale = class(TVrGraphicImageControl)
  private
    FMin: Integer;
    FMax: Integer;
    FTicks: Integer;
    FOrientation: TVrOrientation;
    FDigits: Integer;
    FLeadingZero: Boolean;
    FAlignment: TAlignment;
    FLayOut: TTextLayout;
    FScaleColor: TColor;
    FPeakLevel: Integer;
    FPeakColor: TColor;
    FShowSign: Boolean;
    FTickMarks: TVrTickMarks;
    FScaleOffset: Integer;
    FItemSize: Integer;
    FIncrement: Integer;
    procedure SetMin(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetTicks(Value: Integer);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetLeadingZero(Value: Boolean);
    procedure SetDigits(Value: Integer);
    procedure SetAlignment(Value: TAlignment);
    procedure SetScaleColor(Value: TColor);
    procedure SetScaleOffset(Value: Integer);
    procedure SetPeakLevel(Value: Integer);
    procedure SetPeakColor(Value: TColor);
    procedure SetLayout(Value: TTextLayout);
    procedure SetShowSign(Value: Boolean);
    procedure SetTickMarks(Value: TVrTickMarks);
    procedure ShowText(const S: string; R: TRect);
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;
  protected
    procedure DrawHori;
    procedure DrawVert;
    procedure Paint; override;
    procedure CalcPaintParams;
    function FormatValue(Value: Integer): string;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin Default 0;
    property Ticks: Integer read FTicks write SetTicks default 5;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property LeadingZero: Boolean read FLeadingZero write SetLeadingZero default false;
    property Digits: Integer read FDigits write SetDigits default 3;
    property Alignment: TAlignment read FAlignment write SetAlignment default taCenter;
    property Layout: TTextLayout read FLayout write SetLayout default tlCenter;
    property ScaleColor: TColor read FScaleColor write SetScaleColor default clGreen;
    property PeakLevel: Integer read FPeakLevel write SetPeakLevel default 80;
    property PeakColor: TColor read FPeakColor write SetPeakColor default clLime;
    property ShowSign: Boolean read FShowSign write SetShowSign default True;
    property TickMarks: TVrTickMarks read FTickMarks write SetTickMarks default tmNone;
    property ScaleOffset: Integer read FScaleOffset write SetScaleOffset default 4;
    property Transparent default false;
    property Color default clBlack;
    property ParentColor default false;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Font;
    property ParentFont;
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


const
  AlignValue: array[TAlignment] of Integer =
    (DT_LEFT, DT_RIGHT, DT_CENTER);
  LayoutValue: array[TTextLayout] of Integer =
    (DT_TOP, DT_VCENTER, DT_BOTTOM);



constructor TVrScale.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 215;
  Height := 11;
  Color := clBlack;
  ParentColor := false;
  Font.Name := 'Arial';
  Font.Size := 7;
  Font.Color := clGreen;
  FMin := 0;
  FMax := 100;
  FDigits := 3;
  FTicks := 5;
  FTickMarks := tmNone;
  FOrientation := voHorizontal;
  FLeadingZero := false;
  FAlignment := taCenter;
  FLayout := tlCenter;
  FScaleColor := clGreen;
  FScaleOffset := 4;
  FPeakLevel := 80;
  FPeakColor := clLime;
  FShowSign := True;
end;

procedure TVrScale.SetMin(Value: Integer);
begin
  if FMin <> Value then
  begin
    FMin := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetMax(Value: Integer);
begin
  if FMax <> Value then
  begin
    FMax := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetTicks(Value: Integer);
begin
  if FTicks <> Value then
  begin
    FTicks := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if not Loading then
      BoundsRect := Bounds(Top, Left, Height, Width);
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetLeadingZero(Value: Boolean);
begin
  if FLeadingZero <> Value then
  begin
    FLeadingZero := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetDigits(Value: Integer);
begin
  if FDigits <> Value then
  begin
    FDigits := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetAlignment(Value: TAlignment);
begin
  if FAlignment <> Value then
  begin
    FAlignment := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetLayout(Value: TTextLayout);
begin
  if FLayout <> Value then
  begin
    FLayout := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetScaleColor(Value: TColor);
begin
  if FScaleColor <> Value then
  begin
    FScaleColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetScaleOffset(Value: Integer);
begin
  if FScaleOffset <> Value then
  begin
    FScaleOffset := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetPeakLevel(Value: Integer);
begin
  if FPeakLevel <> Value then
  begin
    FPeakLevel := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetPeakColor(Value: TColor);
begin
  if FPeakColor <> Value then
  begin
    FPeakColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetShowSign(Value: Boolean);
begin
  if FShowSign <> Value then
  begin
    FShowSign := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrScale.SetTickMarks(Value: TVrTickMarks);
begin
  if FTickMarks <> Value then
  begin
    FTickMarks := Value;
    UpdateControlCanvas;
  end;
end;

function TVrScale.FormatValue(Value: Integer): string;
begin
  if FLeadingZero then
    Result := Format('%0.' + IntToStr(FDigits) + 'd', [Value])
  else Result := Format('%d', [Value]);
  if FShowSign then if Value > 0 then Result := '+' + Result;
end;

procedure TVrScale.ShowText(const S: string; R: TRect);
begin
  DrawText(BitmapCanvas.Handle, PChar(S), -1, R,
    DT_NOCLIP or DT_SINGLELINE or
    LayoutValue[FLayout] or AlignValue[FAlignment]);
end;

procedure TVrScale.DrawHori;
var
  I, X, Level: Integer;
  R: TRect;
  S: string;
begin
  with BitmapCanvas do
  begin
    if Transparent then Brush.Style := bsClear
    else Brush.Style := bsSolid;
    Level := FMin;
    R := Bounds(0, 0, FItemSize, ClientHeight);

    for I := 0 to FTicks do
    begin
      if Level >= FPeakLevel then
        Font.Color := FPeakColor else
        Font.Color := Self.Font.Color;

      S := FormatValue(Level);
      ShowText(S, R);
      Inc(Level, FIncrement);
      OffsetRect(R, FItemSize, 0);
    end;

    if FTickMarks <> tmNone then
    begin
      Pen.Width := 1;
      Pen.Color := FScaleColor;

      R := Bounds(0, 0, FItemSize, ClientHeight);
      X := (R.Right - R.Left) div 2;
      for I := 0 to FTicks do
      begin
        if FTickMarks in [tmBoth, tmTopLeft] then
        begin
          MoveTo(R.Left + X, ScaleOffset);
          LineTo(R.Left + X, ScaleOffset + 4);
        end;
        if FTickMarks in [tmBoth, tmBottomRight] then
        begin
          MoveTo(R.Left + X, ClientHeight - ScaleOffset - 4);
          LineTo(R.Left + X, ClientHeight - ScaleOffset);
        end;
        OffsetRect(R, FItemSize, 0);
      end;
    end;
  end;
end;

procedure TVrScale.DrawVert;
var
  I, Y, Level: Integer;
  R: TRect;
  S: string;
begin
  with BitmapCanvas do
  begin
    if Transparent then Brush.Style := bsClear
    else Brush.Style := bsSolid;
    Level := FMin;
    R := Bounds(0, ClientHeight - FItemSize, ClientWidth, FItemSize);

    for I := 0 to FTicks do
    begin
      if Level >= FPeakLevel then
        Font.Color := FPeakColor else
        Font.Color := Self.Font.Color;

      S := FormatValue(Level);
      ShowText(S, R);
      Inc(Level, FIncrement);
      OffsetRect(R, 0, -FItemSize);
    end;

    if FTickMarks <> tmNone then
    begin
      Pen.Width := 1;
      Pen.Color := FScaleColor;

      R := Bounds(0, ClientHeight - FItemSize, ClientWidth, FItemSize);
      Y := (R.Bottom - R.Top) div 2;
      for I := 0 to FTicks do
      begin
        if FTickMarks in [tmBoth, tmTopLeft] then
        begin
          MoveTo(ScaleOffset, R.Top + Y);
          LineTo(ScaleOffset + 4, R.Top + Y);
        end;
        if FTickMarks in [tmBoth, tmBottomRight] then
        begin
          MoveTo(ClientWidth - ScaleOffset - 4, R.Top + Y);
          LineTo(ClientWidth - ScaleOffset, R.Top + Y);
        end;
        OffsetRect(R, 0, -FItemSize);
      end;
    end;
  end;
end;

procedure TVrScale.Paint;
begin
  CalcPaintParams;
  ClearBitmapCanvas;
  if FOrientation = voHorizontal then
    DrawHori else DrawVert;
  inherited Paint;
end;

procedure TVrScale.CalcPaintParams;
begin
  FIncrement := (FMax - FMin) div FTicks;
  case Orientation of
    voVertical: FItemSize := ClientHeight div Succ(FTicks);
    voHorizontal: FItemSize := ClientWidth div Succ(FTicks);
  end;
end;

procedure TVrScale.CMFontChanged(var Message: TMessage);
begin
  BitmapCanvas.Font.Assign(Self.Font);
  inherited;
end;


end.
