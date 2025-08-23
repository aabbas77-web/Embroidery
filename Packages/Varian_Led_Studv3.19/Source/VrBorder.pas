{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrBorder;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, VrControls, VrSysUtils;

type
  TVrBorderStyle = (bsLowered, bsRaised);
  TVrBorderShape = (bsBox, bsFrame, bsTopLine, bsBottomLine, bsLeftLine,
    bsRightLine, bsSpacer);

  TVrBorder = class(TVrGraphicControl)
  private
    FStyle: TVrBorderStyle;
    FShape: TVrBorderShape;
    FShadowColor: TColor;
    FHighlightColor: TColor;
    procedure SetStyle(Value: TVrBorderStyle);
    procedure SetShape(Value: TVrBorderShape);
    procedure SetShadowColor(Value: TColor);
    procedure SetHighlightColor(Value: TColor);
  protected
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Shape: TVrBorderShape read FShape write SetShape default bsFrame;
    property Style: TVrBorderStyle read FStyle write SetStyle default bsRaised;
    property ShadowColor: TColor read FShadowColor write SetShadowColor default clGreen;
    property HighlightColor: TColor read FHighlightColor write SetHighlightColor default clLime;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}    
    property ParentShowHint;
    property ShowHint;
    property Visible;
  end;



implementation


{ TVrBorder }

constructor TVrBorder.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csReplicatable];
  Width := 50;
  Height := 50;
  FStyle := bsRaised;
  FShape := bsFrame;
  FShadowColor := clGreen;
  FHighlightColor := clLime;
end;

procedure TVrBorder.SetStyle(Value: TVrBorderStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    Invalidate;
  end;
end;

procedure TVrBorder.SetShape(Value: TVrBorderShape);
begin
  if FShape <> Value  then
  begin
    FShape := Value;
    Invalidate;
  end;
end;

procedure TVrBorder.SetShadowColor(Value: TColor);
begin
  if FShadowColor <> Value then
  begin
    FShadowColor := Value;
    Invalidate;
  end;
end;

procedure TVrBorder.SetHighlightColor(Value: TColor);
begin
  if FHighlightColor <> Value then
  begin
    FHighlightColor := Value;
    Invalidate;
  end;
end;

procedure TVrBorder.Paint;
const
  XorColor = $00FFD8CE;
var
  Color1, Color2: TColor;
  Temp: TColor;

  procedure BevelRect(const R: TRect);
  begin
    with Canvas do
    begin
      Pen.Color := Color1;
      PolyLine([Point(R.Left, R.Bottom), Point(R.Left, R.Top),
        Point(R.Right, R.Top)]);
      Pen.Color := Color2;
      PolyLine([Point(R.Right, R.Top), Point(R.Right, R.Bottom),
        Point(R.Left, R.Bottom)]);
    end;
  end;

  procedure BevelLine(C: TColor; X1, Y1, X2, Y2: Integer);
  begin
    with Canvas do
    begin
      Pen.Color := C;
      MoveTo(X1, Y1);
      LineTo(X2, Y2);
    end;
  end;

begin
  with Canvas do
  begin
    if Designing then
    begin
      if (FShape = bsSpacer) then
      begin
        Pen.Style := psDot;
        Pen.Mode := pmXor;
        Pen.Color := XorColor;
        Brush.Style := bsClear;
        Rectangle(0, 0, ClientWidth, ClientHeight);
        Exit;
      end
      else
      begin
        Pen.Style := psSolid;
        Pen.Mode  := pmCopy;
        Pen.Color := clBlack;
        Brush.Style := bsSolid;
      end;
    end;

    Pen.Width := 1;

    if FStyle = bsLowered then
    begin
      Color1 := FShadowColor;
      Color2 := FHighlightColor;
    end
    else
    begin
      Color1 := FHighlightColor;
      Color2 := FShadowColor;
    end;

    case FShape of
      bsBox: BevelRect(Rect(0, 0, Width - 1, Height - 1));
      bsFrame:
        begin
          Temp := Color1;
          Color1 := Color2;
          BevelRect(Rect(1, 1, Width - 1, Height - 1));
          Color2 := Temp;
          Color1 := Temp;
          BevelRect(Rect(0, 0, Width - 2, Height - 2));
        end;
      bsTopLine:
        begin
          BevelLine(Color1, 0, 0, Width, 0);
          BevelLine(Color2, 0, 1, Width, 1);
        end;
      bsBottomLine:
        begin
          BevelLine(Color1, 0, Height - 2, Width, Height - 2);
          BevelLine(Color2, 0, Height - 1, Width, Height - 1);
        end;
      bsLeftLine:
        begin
          BevelLine(Color1, 0, 0, 0, Height);
          BevelLine(Color2, 1, 0, 1, Height);
        end;
      bsRightLine:
        begin
          BevelLine(Color1, Width - 2, 0, Width - 2, Height);
          BevelLine(Color2, Width - 1, 0, Width - 1, Height);
        end;
    end;
  end;
end;



end.
