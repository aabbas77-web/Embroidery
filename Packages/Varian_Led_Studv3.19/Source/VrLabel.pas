{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrLabel;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrLabelStyle = (lsNone, lsRaised, lsLowered, lsShadow);

  TVrLabel = class(TVrGraphicImageControl)
  private
    FAlignment: TAlignment;
    FAutoSize: Boolean;
    FLayout: TTextLayout;
    FColorHighlight: TColor;
    FColorShadow: TColor;
    FStyle: TVrLabelStyle;
    FShadowDepth: Integer;
    FBitmap: TBitmap;
    FAngle: TVrTextAngle;
    FRad: Double;
    FTextSize: TPoint;
    procedure SetAlignment(Value: TAlignment);
    procedure SetColorHighlight(Value: TColor);
    procedure SetColorShadow(Value: TColor);
    procedure SetStyle(Value: TVrLabelStyle);
    procedure SetLayout(Value: TTextLayout);
    procedure SetAutoSize(Value: Boolean);
    procedure SetShadowDepth(Value: Integer);
    procedure SetBitmap(Value: TBitmap);
    procedure SetAngle(Value: TVrTextAngle);
    procedure BitmapChanged(Sender: TObject);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
  protected
    procedure AdjustLabelSize;
    procedure GetLayoutCoords(var X, Y: Integer);
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Alignment: TAlignment read FAlignment write SetAlignment default taCenter;
    property ColorHighlight: TColor read FColorHighlight write SetColorHighlight default clWhite;
    property ColorShadow: TColor read FColorShadow write SetColorShadow default clGray;
    property Style: TVrLabelStyle read FStyle write SetStyle default lsRaised;
    property Layout: TTextLayout read FLayout write SetLayout default tlCenter;
    property AutoSize: Boolean read FAutoSize write SetAutoSize default false;
    property ShadowDepth: Integer read FShadowDepth write SetShadowDepth default 2;
    property Bitmap: TBitmap read FBitmap write SetBitmap;
    property Angle: TVrTextAngle read FAngle write SetAngle default 0;
    property Transparent default false;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property BiDiMode;
    property Constraints;
{$ENDIF}
    property Color;
    property Caption;
    property Font;
    property DragCursor;
    property DragMode;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property ParentColor;
    property ParentFont;
    property ParentShowHint;
{$IFDEF VER110}
    property ParentBiDiMode;
{$ENDIF}
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


{ TVrLabel }

constructor TVrLabel.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csSetCaption];
  Width := 100;
  Height := 25;
  Color := clBtnFace;
  Font.Name := 'Arial';
  Font.Size := 14;
  FAlignment := taCenter;
  FLayout := tlCenter;
  FColorHighlight := clWhite;
  FColorShadow := clGray;
  FStyle := lsRaised;
  FAutoSize := false;
  FShadowDepth := 2;
  FAngle := 0;
  FRad := 0;
  FBitmap := TBitmap.Create;
  FBitmap.OnChange := BitmapChanged;
end;

destructor TVrLabel.Destroy;
begin
  FBitmap.Free;
  inherited Destroy;
end;

procedure TVrLabel.AdjustLabelSize;
var
  NewWidth, NewHeight: Integer;
begin
  with BitmapCanvas do
  begin
    if FAutoSize then
    begin
      NewWidth := 4 + Trunc(FTextSize.X * Abs(cos(FRad)) +
        FTextSize.Y * Abs(sin(FRad)));
      NewHeight := 4 + Trunc(FTextSize.Y * Abs(cos(FRad)) +
        FTextSize.X * Abs(sin(FRad)));
      BoundsRect := Bounds(Left, Top, NewWidth, NewHeight);
    end;
  end;
end;

procedure TVrLabel.GetLayoutCoords(var X, Y: Integer);
var
  P: TPoint;
  LeftX: Integer;
begin
  X := 0;
  Y := (ClientHeight - FTextSize.Y) div 2;
  with BitmapCanvas do
  begin
    P := GetTextSize(BitmapCanvas, Caption);
    X := 2;
    if (FAngle > 90) and (FAngle < 270) then
      X := X + Trunc(FTextSize.X * Abs(cos(FRad)));
    if (FAngle > 180) then
      X := X + Trunc(FTextSize.Y * Abs(sin(FRad)));

    LeftX := X;

    case FAlignment of
      taCenter:
        begin
          X := Trunc(0.5 * ClientWidth -
            0.5 * FTextSize.X * cos(FRad) - 0.5 * FTextSize.Y * sin(FRad));
        end;
      taRightJustify :
        begin
          X := 2 + Trunc(FTextSize.X * Abs(cos(FRad)) +
            FTextSize.Y * Abs(sin(FRad)));
          X := ClientWidth - X;
          if (FAngle > 90) and (FAngle < 270) then
            X := X + Trunc(FTextSize.X * Abs(cos(FRad)));
          if (FAngle > 180) then
            X := X + Trunc(FTextSize.Y * Abs(sin(FRad)));
        end;
    end;

    X := MaxIntVal(LeftX, X);

    case FLayout of
      tlTop:
        begin
          Y := 2;
          if FAngle < 180 then
            Y := Y + Trunc(FTextSize.X * Abs(sin(FRad)));
          if (FAngle > 90) and (FAngle < 270) then
            Y := Y + Trunc(FTextSize.Y * Abs(cos(FRad)) );
         end;
      tlCenter:
        begin
          Y := Trunc(0.5 * ClientHeight -
            0.5 * FTextSize.Y * cos(FRad) + 0.5 * FTextSize.X * sin(FRad));
        end;
      tlBottom:
        begin
          Y := 2 + Trunc(FTextSize.Y * Abs(cos(FRad)) +
            FTextSize.X * Abs(sin(FRad)));
          Y := ClientHeight - Y;
          if FAngle < 180 then
            Y := Y + Trunc(FTextSize.X * Abs(sin(FRad)));
          if (FAngle > 90) and (FAngle < 270) then
            Y := Y + Trunc(FTextSize.Y * Abs(cos(FRad)) );
        end;
    end;
  end;
end;

procedure TVrLabel.Paint;
var
  X, Y: Integer;
begin
  with inherited BitmapCanvas do
  begin
    Font.Assign(Self.Font);
    FTextSize := GetTextSize(BitmapCanvas, Caption);
    SetCanvasTextAngle(BitmapCanvas, FAngle);
    AdjustLabelSize;

    ClearBitmapCanvas;

    GetLayoutCoords(X, Y);

    case FStyle of
      lsNone:
        begin
          if Transparent then Brush.Style := bsClear
          else Brush.Style := bsSolid;
          TextOut(X, Y, Caption);
        end;
      lsRaised:
        Draw3DText(BitmapCanvas, X, Y, Caption, FColorHighlight, FColorShadow);
      lsLowered:
        Draw3DText(BitmapCanvas, X, Y, Caption, FColorShadow, FColorHighlight);
      lsShadow:
        DrawShadowTextExt(BitmapCanvas, X, Y, Caption,
          FColorShadow, FShadowDepth, FShadowDepth);
    end;

    if not FBitmap.Empty then
      StretchPaintOnText(BitmapCanvas, ClientRect,
        X, Y, Caption, FBitmap, FAngle);
  end;

  inherited Paint;
end;

procedure TVrLabel.SetAlignment(Value: TAlignment);
begin
  if FAlignment <> Value then
  begin
    FAlignment := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.SetColorHighlight(Value: TColor);
begin
  if FColorHighlight <> Value then
  begin
    FColorHighlight := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.SetColorShadow(Value: TColor);
begin
  if FColorShadow <> Value then
  begin
    FColorShadow := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.SetStyle(Value: TVrLabelStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.SetLayout(Value: TTextLayout);
begin
  if FLayout <> Value then
  begin
    FLayout := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.SetAutoSize(Value: Boolean);
begin
  if FAutoSize <> Value then
  begin
    FAutoSize := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.SetShadowDepth(Value: Integer);
begin
  if FShadowDepth <> Value then
  begin
    FShadowDepth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.SetBitmap(Value: TBitmap);
begin
  FBitmap.Assign(Value);
end;

procedure TVrLabel.SetAngle(Value: TVrTextAngle);
begin
  if FAngle <> Value then
  begin
    FAngle := Value;
    FRad := Value * (PI / 180);
    UpdateControlCanvas;
  end;
end;

procedure TVrLabel.BitmapChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrLabel.CMTextChanged(var Message: TMessage);
begin
  UpdateControlCanvas;
  inherited;
end;


end.
