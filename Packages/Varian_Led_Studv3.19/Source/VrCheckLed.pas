{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrCheckLed;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrCheckInt = 10..40;

  TVrCheckLed = class(TVrCustomImageControl)
  private
    FChecked: Boolean;
    FPalette: TVrPalette;
    FSpacing: Integer;
    FMargin: Integer;
    FLayout: TVrImageTextLayout;
    FCheckWidth: TVrCheckInt;
    FCheckHeight: TVrCheckInt;
    FOnChange: TNotifyEvent;
    MouseButtonDown: Boolean;
    ImageRect: TRect;
    TextBounds: TRect;
    LastState: Boolean;
    HasMouse: Boolean;
    HasFocus: Boolean;
    procedure SetCheckWidth(Value: TVrCheckInt);
    procedure SetCheckHeight(Value: TVrCheckInt);
    procedure SetChecked(Value: Boolean);
    procedure SetLayout(Value: TVrImageTextLayout);
    procedure SetMargin(Value: Integer);
    procedure SetSpacing(Value: Integer);
    procedure SetPalette(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
    procedure WMSize(var Message: TMessage); message WM_SIZE;
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    procedure WMSetFocus(var Message: TWMSetFocus); message WM_SETFOCUS;
    procedure WMKillFocus(var Message: TWMKillFocus); message WM_KILLFOCUS;
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
  protected
    procedure CreateParams(var Params: TCreateParams); override;
    procedure CalcPaintParams(Repaint: Boolean);
    procedure DrawGlyph(Index: Integer; R: TRect; ACanvas: TCanvas);
    procedure Paint; override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure Keypress(var Key: Char); override;
    procedure Change; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property CheckWidth: TVrCheckInt read FCheckWidth write SetCheckWidth default 20;
    property CheckHeight: TVrCheckInt read FCheckHeight write SetCheckHeight default 13;
    property Checked: Boolean read FChecked write SetChecked default false;
    property Layout: TVrImageTextLayout read FLayout write SetLayout default ImageLeft;
    property Margin: Integer read FMargin write SetMargin default -1;
    property Spacing: Integer read FSpacing write SetSpacing default 5;
    property Palette: TVrPalette read FPalette write SetPalette;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
{$IFDEF VER110}
    property Anchors;
    property BiDiMode;
    property Constraints;
{$ENDIF}
    property Caption;
    property Color default clBtnFace;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Enabled;
    property Font;
    property ParentFont;
{$IFDEF VER110}
    property ParentBiDiMode;
{$ENDIF}
    property ParentColor default false;
    property ParentShowHint;
    property PopUpMenu;
    property ShowHint;
    property TabOrder;
    property TabStop default false;
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
    property OnEnter;
    property OnExit;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


implementation


{ TVrCheckLed }

constructor TVrCheckLed.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := [csCaptureMouse, csClickEvents,
    csOpaque, csSetCaption, csReplicatable];
  Width := 125;
  Height := 25;
  Color := clBtnFace;
  ParentColor := false;
  TabStop := false;
  FChecked := false;
  FCheckHeight := 13;
  FCheckWidth := 20;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  HasMouse := false;
  FSpacing := 5;
  FMargin := -1;
  FLayout := ImageLeft;
end;

destructor TVrCheckLed.Destroy;
begin
  FPalette.Free;
  inherited Destroy;
end;

procedure TVrCheckLed.CreateParams(var Params: TCreateParams);
begin
  inherited CreateParams(Params);
  with Params do
    WindowClass.style := WindowClass.style and not (CS_HREDRAW or CS_VREDRAW);
end;

procedure TVrCheckLed.DrawGlyph(Index: Integer; R: TRect; ACanvas: TCanvas);
begin
  if Index = 2 then
    DrawFrame3D(ACanvas, R, clBlack, clBtnHighlight, 1)
  else DrawFrame3D(ACanvas, R, clBtnHighlight, clBlack, 1);
  DrawFrame3D(ACanvas, R, clBtnHighlight, clBtnShadow, 1);
  DrawFrame3D(ACanvas, R, clBtnFace, clBtnFace, 1);
  DrawFrame3D(ACanvas, R, clBlack, clBtnHighlight, 1);
  case Index of
    0: ACanvas.Brush.Color := FPalette.Low;
    1: ACanvas.Brush.Bitmap :=
         CreateDitherPattern(FPalette.Low, FPalette.High);
    2: ACanvas.Brush.Color := FPalette.High;
  end;
  ACanvas.FillRect(R);
  FreeObject(ACanvas.Brush.Bitmap);
end;

procedure TVrCheckLed.Paint;
var
  R: TRect;
begin
  ClearBitmapCanvas;

  with BitmapCanvas do
  begin
    Brush.Color := Self.Color;
    FillRect(ClientRect);
  end;
  if (HasMouse) and not FChecked then
    DrawGlyph(1, ImageRect, BitmapCanvas)
  else
  if FChecked then DrawGlyph(2, ImageRect, BitmapCanvas)
  else DrawGlyph(0, ImageRect, BitmapCanvas);

  BitmapCanvas.Font := Self.Font;
  BitmapCanvas.Brush.Color := Self.Color;
  DrawButtonText(BitmapCanvas, Caption, TextBounds, Enabled);

  if HasFocus then
  begin
    R := TextBounds;
    InflateRect(R, 1, 1);
    DrawFrame3D(BitmapCanvas, R, clBlack, clBlack, 1);
  end;

  inherited Paint;
end;

procedure TVrCheckLed.CalcPaintParams(Repaint: Boolean);
var
  ImagePos: TPoint;
begin
  Canvas.Font := Self.Font;
  CalcImageTextLayout(Canvas, ClientRect, Point(1, 1), Caption, FLayout,
    FMargin, FSpacing, Point(FCheckWidth, FCheckHeight), ImagePos, TextBounds);
  ImageRect := Bounds(ImagePos.X, ImagePos.Y, FCheckWidth, FCheckHeight);
  if Repaint then UpdateControlCanvas;
end;

procedure TVrCheckLed.PaletteModified(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrCheckLed.WMSize(var Message: TMessage);
begin
  inherited;
  CalcPaintParams(True);
end;

procedure TVrCheckLed.CMFontChanged(var Message: TMessage);
begin
  inherited;
  CalcPaintParams(True);
end;

procedure TVrCheckLed.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  inherited MouseDown(Button, Shift, X, Y);
  if (Button = mbLeft) and Enabled then
    if ptInRect(ImageRect, Point(X, Y)) then
    begin
      MouseButtonDown := true;
      LastState := FChecked;
      FChecked := not FChecked;
      UpdateControlCanvas;
    end;
  if TabStop then SetFocus;
end;

procedure TVrCheckLed.MouseMove(Shift: TShiftState; X, Y: Integer);
var
  InRect: Boolean;
begin
  inherited MouseMove(Shift, X, Y);
  InRect := ptInRect(ImageRect, Point(X, Y));
  if HasMouse <> InRect then
  begin
    HasMouse := InRect;
    UpdateControlCanvas;
  end;
end;

procedure TVrCheckLed.MouseUp(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  inherited MouseUp(Button, Shift, X, Y);
  if MouseButtonDown then
    if not ptInRect(ImageRect, Point(X, Y)) then
    begin
      FChecked := LastState;
      UpdateControlCanvas;
    end else Change;
  MouseButtonDown := false;
end;

procedure TVrCheckLed.CMTextChanged(var Message: TMessage);
begin
  inherited;
  if HandleAllocated then
    CalcPaintParams(true);
end;

procedure TVrCheckLed.WMSetFocus(var Message: TWMSetFocus);
begin
  HasFocus := True;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrCheckLed.WMKillFocus(var Message: TWMKillFocus);
begin
  HasFocus := False;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrCheckLed.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrCheckLed.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  HasMouse := false;
  UpdateControlCanvas;
end;

procedure TVrCheckLed.Keypress(var Key: Char);
begin
  if Key = #32 then
  begin
    FChecked := not FChecked;
    UpdateControlCanvas;
  end;
  inherited;
end;

procedure TVrCheckLed.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrCheckLed.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrCheckLed.SetCheckWidth(Value: TVrCheckInt);
begin
  if FCheckWidth <> Value then
  begin
    FCheckWidth := Value;
    CalcPaintParams(True);
  end;
end;

procedure TVrCheckLed.SetCheckHeight(Value: TVrCheckInt);
begin
  if FCheckHeight <> Value then
  begin
    FCheckHeight := Value;
    CalcPaintParams(True);
  end;
end;

procedure TVrCheckLed.SetChecked(Value: Boolean);
begin
  if FChecked <> Value then
  begin
    FChecked := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrCheckLed.SetLayout(Value: TVrImageTextLayout);
begin
  if FLayout <> Value then
  begin
    FLayout := Value;
    CalcPaintParams(True);
  end;
end;

procedure TVrCheckLed.SetMargin(Value: Integer);
begin
  if FMargin <> Value then
  begin
    FMargin := Value;
    CalcPaintParams(True);
  end;
end;

procedure TVrCheckLed.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    CalcPaintParams(True);
  end;
end;


end.
