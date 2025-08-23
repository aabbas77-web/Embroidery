{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrDemoButton;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrControls, VrClasses, VrSysUtils;

type
  TVrDemoButton = class(TVrCustomImageControl)
  private
    FBitmap: TBitmap;
    FFontEnter: TFont;
    FFontLeave: TFont;
    FBevelWidth: TVrByteInt;
    FOutlineWidth: Integer;
    FOutlineColor: TColor;
    FShadowColor: TColor;
    FHighlightColor: TColor;
    FFocusColor: TColor;
    FTextAlignment: TVrTextAlignment;
    FDisabledTextColor: TColor;
    FFont3D: TVrFont3D;
    FHasMouse: Boolean;
    FFocused: Boolean;
    Down: Boolean;
    Pressed: Boolean;
    procedure SetBitmap(Value: TBitmap);
    procedure SetFontEnter(Value: TFont);
    procedure SetFontLeave(Value: TFont);
    procedure SetOutlineColor(Value: TColor);
    procedure SetShadowColor(Value: TColor);
    procedure SetHighlightColor(Value: TColor);
    procedure SetBevelWidth(Value: TVrByteInt);
    procedure SetOutlineWidth(Value: Integer);
    procedure SetTextAlignment(Value: TVrTextAlignment);
    procedure SetDisabledTextColor(Value: TColor);
    procedure SetFocusColor(Value: TColor);
    procedure SetFont3D(Value: TVrFont3D);
    procedure FontChanged(Sender: TObject);
    procedure BitmapChanged(Sender: TObject);
    procedure DoMouseDown(XPos, YPos: Integer);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    procedure CMDialogChar(var Message: TCMDialogChar); message CM_DIALOGCHAR;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
    procedure WMLButtonDown(var Message: TWMLButtonDown); message WM_LButtonDown;
    procedure WMMouseMove(var Message: TWMMouseMove); message WM_MouseMove;
    procedure WMLButtonUp(var Message: TWMLButtonUp); message WM_LButtonUp;
    procedure WMLButtonDblClk(var Message: TWMLButtonDblClk); message WM_LButtonDblClk;
    procedure CMMouseEnter(var Message: TMessage); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
    procedure CMFocusChanged(var Message: TCMFocusChanged); message CM_FOCUSCHANGED;
  protected
    procedure Paint; override;
    function GetPalette: HPalette; override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure KeyUp(var Key: Word; Shift: TShiftState); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property FontEnter: TFont read FFontEnter write SetFontEnter;
    property FontLeave: TFont read FFontLeave write SetFontLeave;
    property Bitmap: TBitmap read FBitmap write SetBitmap;
    property OutlineColor: TColor read FOutlineColor write SetOutlineColor default clBlack;
    property ShadowColor: TColor read FShadowColor write SetShadowColor default clBtnShadow;
    property HighlightColor: TColor read FHighlightColor write SetHighlightColor default clBtnHighlight;
    property BevelWidth: TVrByteInt read FBevelWidth write SetBevelWidth default 2;
    property OutlineWidth: Integer read FOutlineWidth write SetOutlineWidth default 1;
    property TextAlignment: TVrTextAlignment read FTextAlignment write SetTextAlignment default vtaCenter;
    property DisabledTextColor: TColor read FDisabledTextColor write SetDisabledTextColor default clInActiveCaption;
    property FocusColor: TColor read FFocusColor write SetFocusColor default clBlue;
    property Font3D: TVrFont3D read FFont3D write SetFont3D;
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

{ TVrDemoButton }

constructor TVrDemoButton.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csDoubleClicks];
  Width := 150;
  Height := 25;
  Color := clBtnFace;
  ParentColor := false;

  FBitmap := TBitmap.Create;
  FBitmap.OnChange := BitmapChanged;

  FFont3D := TVrFont3D.Create;
  FFont3D.OnChange := FontChanged;

  FFontEnter := TFont.Create;
  with FFontEnter do
  begin
    Name := 'Arial';
    Size := 12;
    Color := clRed;
    Style := Style + [fsBold];
    OnChange := FontChanged;
  end;
  FFontLeave := TFont.Create;
  with FFontLeave do
  begin
    Name := 'Arial';
    Size := 12;
    Color := clBlack;
    Style := Style + [fsBold];
    OnChange := FontChanged;
  end;

  FBevelWidth := 2;
  FOutlineWidth := 1;
  FShadowColor := clBtnShadow;
  FHighlightColor := clBtnHighlight;
  FOutlineColor := clBlack;
  FTextAlignment := vtaCenter;
  FDisabledTextColor := clInActiveCaption;
  FFocusColor := clBlue;
end;

destructor TVrDemoButton.Destroy;
begin
  FBitmap.Free;
  FFont3D.Free;
  FFontEnter.Free;
  FFontLeave.Free;
  inherited Destroy;
end;

procedure TVrDemoButton.FontChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrDemoButton.BitmapChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

function TVrDemoButton.GetPalette: HPalette;
begin
  if FBitmap.Empty then Result := inherited GetPalette
  else Result := FBitmap.Palette;
end;

procedure TVrDemoButton.Paint;
var
  R: TRect;
begin
  if FBitmap.Empty then ClearBitmapCanvas
  else
    begin
      R := ClientRect;
      if Down then OffsetRect(R, 1, 1);
      DrawTiledBitmap(BitmapCanvas, R, Bitmap);
    end;

  R := ClientRect;
  if FFocused then
    DrawFrame3D(BitmapCanvas, R, FocusColor, FocusColor, OutlineWidth)
  else DrawFrame3D(BitmapCanvas, R, OutlineColor, OutlineColor, OutlineWidth);

  if Down then
    DrawFrame3D(BitmapCanvas, R, ShadowColor, HighlightColor, BevelWidth)
  else DrawFrame3D(BitmapCanvas, R, HighlightColor, ShadowColor, BevelWidth);

  with BitmapCanvas do
  begin
    if FHasMouse and Enabled then
      Font.Assign(FontEnter)
    else Font.Assign(FontLeave);
    if not Enabled then
      Font.Color := DisabledTextColor;

    Brush.Style := bsClear;
    if Down then OffsetRect(R, 1, 1);

    FFont3D.Paint(BitmapCanvas, R, Caption,
      DT_SINGLELINE + VrTextAlign[TextAlignment]);
  end;

  inherited Paint;
end;

procedure TVrDemoButton.SetBitmap(Value: TBitmap);
begin
  FBitmap.Assign(Value);
end;

procedure TVrDemoButton.SetFontEnter(Value: TFont);
begin
  FFontEnter.Assign(Value);
end;

procedure TVrDemoButton.SetFontLeave(Value: TFont);
begin
  FFontLeave.Assign(Value);
end;

procedure TVrDemoButton.SetOutlineColor(Value: TColor);
begin
  if FOutlineColor <> Value then
  begin
    FOutlineColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetShadowColor(Value: TColor);
begin
  if FShadowColor <> Value then
  begin
    FShadowColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetHighlightColor(Value: TColor);
begin
  if FHighlightColor <> Value then
  begin
    FHighlightColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetBevelWidth(Value: TVrByteInt);
begin
  if FBevelWidth <> Value then
  begin
    FBevelWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetOutlineWidth(Value: Integer);
begin
  if FOutlineWidth <> Value then
  begin
    FOutlineWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetTextAlignment(Value: TVrTextAlignment);
begin
  if FTextAlignment <> Value then
  begin
    FTextAlignment := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetDisabledTextColor(Value: TColor);
begin
  if FDisabledTextColor <> Value then
  begin
    FDisabledTextColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetFocusColor(Value: TColor);
begin
  if FFocusColor <> Value then
  begin
    FFocusColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.SetFont3D(Value: TVrFont3D);
begin
  FFont3D.Assign(Value);
end;

procedure TVrDemoButton.CMTextChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrDemoButton.DoMouseDown(XPos, YPos: Integer);
var
  P: TPoint;
begin
  P := Point(XPos, YPos);
  if PtInRect(ClientRect, P) then
  begin
    Pressed := True;
    Down := True;
    MouseCapture := true;
    if TabStop then SetFocus;
    UpdateControlCanvas;
  end;
end;

procedure TVrDemoButton.WMLButtonDown(var Message: TWMLButtonDown);
begin
  inherited;
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrDemoButton.WMLButtonDblClk(var Message: TWMLButtonDblClk);
begin
  inherited;
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrDemoButton.WMMouseMove(var Message: TWMMouseMove);
var
  P: TPoint;
begin
  inherited;
  if Pressed then
  begin
    P := Point(Message.XPos, Message.YPos);
    if PtInRect(ClientRect, P) <> Down then
    begin
      Down := not Down;
      UpdateControlCanvas;
    end;
  end;
end;

procedure TVrDemoButton.WMLButtonUp(var Message: TWMLButtonUp);
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

procedure TVrDemoButton.CMDialogChar(var Message: TCMDialogChar);
begin
  if Enabled and IsAccel(Message.CharCode, Caption) then
    inherited Click;
end;

procedure TVrDemoButton.CMEnabledChanged(var Message: TMessage);
begin
  UpdateControlCanvas;
end;

procedure TVrDemoButton.CMMouseEnter(var Message: TMessage);
begin
  inherited;
  FHasMouse := True;
  UpdateControlCanvas;
end;

procedure TVrDemoButton.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  FHasMouse := false;
  UpdateControlCanvas;
end;

procedure TVrDemoButton.CMFocusChanged(var Message: TCMFocusChanged);
var
  Active: Boolean;
begin
  with Message do Active := (Sender = Self);
  if Active <> FFocused then
  begin
    FFocused := Active;
    UpdateControlCanvas;
  end;
  inherited;
end;

procedure TVrDemoButton.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited KeyDown(Key, Shift);
  if (not Down) and (Key = VK_SPACE) then DoMouseDown(0, 0);
end;

procedure TVrDemoButton.KeyUp(var Key: Word; Shift: TShiftState);
begin
  inherited KeyUp(Key, Shift);
  if Key = VK_SPACE then
  begin
    MouseCapture := false;
    if Pressed and Down then
    begin
      Down := False;
      UpdateControlCanvas;
      inherited Click;
    end;
    Pressed := False;
  end;
end;


end.
