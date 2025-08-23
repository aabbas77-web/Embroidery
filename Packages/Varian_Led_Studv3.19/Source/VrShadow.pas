{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrShadow;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrShadowButtonStyle = (ssRectangle, ssRoundRect);
  TVrShadowDirection = (sdTopLeft, sdTopRight, sdBottomLeft, sdBottomRight);

  TVrShadowBrush = class(TBrush)
  public
    constructor Create;
  published
    property Color default clBlack;
  end;

  TVrShadowPen = class(TPen)
  public
    constructor Create;
  published
    property Color default clLime;
  end;

  TVrShadowButton = class(TVrGraphicImageControl)
  private
    FDepth: Integer;
    FShadowColor: TColor;
    FShadowOutline: TColor;
    FBrush: TVrShadowBrush;
    FPen: TVrShadowPen;
    FStyle: TVrShadowButtonStyle;
    FDirection: TVrShadowDirection;
    FTextAlign: TVrTextAlignment;
    Down: Boolean;
    Pressed: Boolean;
    CurrentRect: TRect;
    procedure SetBrush(Value: TVrShadowBrush);
    procedure SetPen(Value: TVrShadowPen);
    procedure SetDepth(Value: Integer);
    procedure SetShadowColor(Value: TColor);
    procedure SetShadowOutline(Value: TColor);
    procedure SetStyle(Value: TVrShadowButtonStyle);
    procedure SetDirection(Value: TVrShadowDirection);
    procedure SetTextAlign(Value: TVrTextAlignment);
    procedure StyleChanged(Sender: TObject);
    procedure AdjustBtnRect(var Rect: TRect; Offset: Integer);
    procedure DoMouseDown(XPos, YPos: Integer);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;
    procedure CMDialogChar(var Message: TCMDialogChar); message CM_DIALOGCHAR;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
    procedure WMLButtonDown(var Message: TWMLButtonDown); message WM_LButtonDown;
    procedure WMMouseMove(var Message: TWMMouseMove); message WM_MouseMove;
    procedure WMLButtonUp(var Message: TWMLButtonUp); message WM_LButtonUp;
    procedure WMLButtonDblClk(var Message: TWMLButtonDblClk); message WM_LButtonDblClk;
  protected
    procedure DrawButton;
    procedure Paint; override;
    procedure Click; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Brush: TVrShadowBrush read FBrush write SetBrush;
    property Pen: TVrShadowPen read FPen write SetPen;
    property Depth: Integer read FDepth write SetDepth default 4;
    property ShadowColor: TColor read FShadowColor write SetShadowColor default clBtnShadow;
    property ShadowOutline: TColor read FShadowOutline write SetShadowOutline default clBtnShadow;
    property Style: TVrShadowButtonStyle read FStyle write SetStyle default ssRoundRect;
    property Direction: TVrShadowDirection read FDirection write SetDirection default sdBottomRight;
    property TextAlign: TVrTextAlignment read FTextAlign write SetTextAlign default vtaCenter;
    property Transparent default false;
{$IFDEF VER110}
    property Anchors;
    property BiDiMode;
    property Constraints;
{$ENDIF}
    property Caption;
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Enabled;
    property Font;
{$IFDEF VER110}
    property ParentBiDiMode;
{$ENDIF}
    property ParentColor default true;
    property ParentFont default false;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Visible;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}    
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


{ TVrShadowBrush }
constructor TVrShadowBrush.Create;
begin
  inherited Create;
  Color := clBlack;
end;

{ TVrShadowPen }
constructor TVrShadowPen.Create;
begin
  inherited Create;
  Color := clLime;
end;

{TVrShadowButton}

constructor TVrShadowButton.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csDoubleClicks];
  Width := 110;
  Height := 30;
  Font.Color := clWhite;
  ParentColor := true;
  ParentFont := false;
  FDepth := 4;
  FShadowColor := clBtnShadow;
  FShadowOutline := clBtnShadow;
  FBrush := TVrShadowBrush.Create;
  FBrush.OnChange := StyleChanged;
  FPen := TVrShadowPen.Create;
  FPen.OnChange := StyleChanged;
  FStyle := ssRoundRect;
  FDirection := sdBottomRight;
  FTextAlign := vtaCenter;
end;

destructor TVrShadowButton.Destroy;
begin
  FBrush.Free;
  FPen.Free;
  inherited Destroy;
end;

procedure TVrshadowButton.Click;
begin
end;

procedure TVrShadowButton.SetBrush(Value: TVrShadowBrush);
begin
  FBrush.Assign(Value);
end;

procedure TVrShadowButton.SetPen(Value: TVrShadowPen);
begin
  FPen.Assign(Value);
end;

procedure TVrShadowButton.SetDepth(Value: Integer);
begin
  if (FDepth <> Value) and (Value > 2) then
  begin
    FDepth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrShadowButton.SetShadowColor(Value: TColor);
begin
  if FShadowColor <> Value then
  begin
    FShadowColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrShadowButton.SetShadowOutline(Value: TColor);
begin
  if FShadowOutline <> Value then
  begin
    FShadowOutline := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrShadowButton.SetStyle(Value: TVrShadowButtonStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrShadowButton.SetDirection(Value: TVrShadowDirection);
begin
  if FDirection <> Value then
  begin
    FDirection := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrShadowButton.SetTextAlign(Value: TVrTextAlignment);
begin
  if FTextAlign <> Value then
  begin
    FTextAlign := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrShadowButton.StyleChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrShadowButton.AdjustBtnRect(var Rect: TRect; Offset: Integer);
begin
  case FDirection of
    sdBottomRight: OffsetRect(Rect, Offset, Offset);
    sdBottomLeft: OffsetRect(Rect, -Offset, Offset);
    sdTopLeft: OffsetRect(Rect, -Offset, -Offset);
    sdTopRight: OffsetRect(Rect, Offset, -Offset);
  end;
end;

procedure TVrShadowButton.DrawButton;
const
  ShapeStyles: array[TVrShadowButtonStyle] of TVrShapeType =
    (stRectangle, stRoundRect);
var
  ImageRect, ShadowRect: TRect;
begin
  ClearBitmapCanvas;

  ImageRect := ClientRect;

  with BitmapImage do
  begin
    InflateRect(ImageRect, -FPen.Width, -FPen.Width);

    case FDirection of
      sdBottomRight:
        begin
          Dec(ImageRect.Right, FDepth);
          Dec(ImageRect.Bottom, FDepth);
        end;
      sdBottomLeft:
        begin
          Inc(ImageRect.Left, FDepth);
          Dec(ImageRect.Bottom, FDepth);
        end;
      sdTopLeft:
        begin
          Inc(ImageRect.Top, FDepth);
          Inc(ImageRect.Left, FDepth);
        end;
      sdTopRight:
        begin
          Inc(ImageRect.Top, FDepth);
          Dec(ImageRect.Right, FDepth);
        end;
    end;

    with Canvas do
    begin
      Pen.Width := 1;
      Pen.Color := FShadowOutline;
      Pen.Mode := pmCopy;
      Pen.Style := psSolid;
      Brush.Style := bsSolid;
      Brush.Color := FShadowColor;
    end;

    ShadowRect := ImageRect;
    AdjustBtnRect(ShadowRect, FDepth);
    if Down then
      AdjustBtnRect(ShadowRect, -1);

    DrawShape(Canvas, ShapeStyles[FStyle], ShadowRect.Left, ShadowRect.Top,
        ShadowRect.Right - ShadowRect.Left, ShadowRect.Bottom - ShadowRect.Top);

    if Down then AdjustBtnRect(ImageRect, 2);

    Canvas.Brush.Assign(FBrush);
    Canvas.Pen.Assign(FPen);
    Canvas.Font.Assign(Self.Font);
    if not Enabled then Canvas.Font.Color := clInActiveCaption;

    DrawShape(Canvas, ShapeStyles[FStyle], ImageRect.Left, ImageRect.Top,
      ImageRect.Right - ImageRect.Left, ImageRect.Bottom - ImageRect.Top);

    InflateRect(ImageRect, -Pen.Width, -Pen.Width);
    Canvas.Brush.Style := bsClear;
    DrawText(Canvas.Handle, PChar(Caption), -1, ImageRect,
      DT_SINGLELINE + VrTextAlign[TextAlign]);

    CurrentRect := ImageRect;
  end;

  inherited Paint;
end;

procedure TVrShadowButton.Paint;
begin
  DrawButton;
end;

procedure TVrShadowButton.CMTextChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrShadowButton.CMFontChanged(var Message: TMessage);
begin
  inherited;
  BitmapCanvas.Font.Assign(Self.Font);
  UpdateControlCanvas;
end;

procedure TVrShadowButton.DoMouseDown(XPos, YPos: Integer);
var
  P: TPoint;
begin
  P := Point(XPos, YPos);
  if PtInRect(CurrentRect, P) then
  begin
    Pressed := True;
    Down := True;
    MouseCapture := true;
    UpdateControlCanvas;
  end;
end;

procedure TVrShadowButton.WMLButtonDown(var Message: TWMLButtonDown);
begin
  inherited;
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrShadowButton.WMLButtonDblClk(var Message: TWMLButtonDblClk);
begin
  inherited;
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrShadowButton.WMMouseMove(var Message: TWMMouseMove);
var
  P: TPoint;
begin
  inherited;
  if Pressed then
  begin
    P := Point(Message.XPos, Message.YPos);
    if PtInRect(CurrentRect, P) <> Down then
    begin
      Down := not Down;
      UpdateControlCanvas;
    end;
  end;
end;

procedure TVrShadowButton.WMLButtonUp(var Message: TWMLButtonUp);
var
  DoClick: Boolean;
begin
  MouseCapture := false;
  DoClick := Pressed and Down;
  Down := false;
  Pressed := false;
  if DoClick then
  begin
    UpdateControlCanvas;
    inherited Click;
  end;
  inherited;
end;

procedure TVrShadowButton.CMDialogChar(var Message: TCMDialogChar);
begin
  if Enabled and IsAccel(Message.CharCode, Caption) then
    inherited Click;
end;

procedure TVrShadowButton.CMEnabledChanged(var Message: TMessage);
begin
  UpdateControlCanvas;
end;


end.
