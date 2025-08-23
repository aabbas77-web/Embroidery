{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrSwitch;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrConst, VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrSwitchThumb = class(TVrCustomThumb)
  protected
    function GetImageIndex: Integer; override;
  public
    constructor Create(AOwner: TComponent); override;
  end;

  TVrSwitchOption = (soActiveClick, soMouseClip, soHandPoint);
  TVrSwitchOptions = set of TVrSwitchOption;
  TVrSwitchImageRange = 0..2;
  TVrSwitchImages = array[TVrSwitchImageRange] of TBitmap;

  TVrSwitch = class(TVrCustomControl)
  private
    FOffset: Integer;
    FPositions: Integer;
    FOrientation: TVrOrientation;
    FBevel: TVrBevel;
    FStyle: TVrProgressStyle;
    FOptions: TVrSwitchOptions;
    FBorderColor: TColor;
    FFocusColor: TColor;
    FOnChange: TNotifyEvent;
    FHit: Integer;
    FFocused: Boolean;
    FClipOn: Boolean;
    FDest: TBitmap;
    FThumb: TVrSwitchThumb;
    FImages: TVrSwitchImages;
    function GetImage(Index: Integer): TBitmap;
    function GetThumbStates: Integer;
    procedure SetImage(Index: Integer; Value: TBitmap);
    procedure SetThumbStates(Value: Integer);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetOffset(Value: Integer);
    procedure SetPositions(Value: Integer);
    procedure SetStyle(Value: TVrProgressStyle);
    procedure SetOptions(Value: TVrSwitchOptions);
    procedure SetBorderColor(Value: TColor);
    procedure SetFocusColor(Value: TColor);
    procedure SetBevel(Value: TVrBevel);
    procedure BevelChanged(Sender: TObject);
    procedure ImageChanged(Sender: TObject);
    procedure UpdateThumbGlyph;
    procedure AdjustControlSize;
    procedure WMSize(var Message: TWMSize); message WM_SIZE;
    procedure WMGetDlgCode(var Msg: TWMGetDlgCode); message WM_GETDLGCODE;
    procedure CMFocusChanged(var Message: TCMFocusChanged); message CM_FOCUSCHANGED;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
  protected
    procedure LoadBitmaps;
    procedure Loaded; override;
    procedure Paint; override;
    procedure CalcPaintParams;
    procedure Change; dynamic;
    function GetViewPortLength: Integer;
    function GetValueByOffset(Offset: Integer): Integer;
    function GetOffsetByValue(Value: Integer): Integer;
    procedure SetThumbOffset(Value: Integer; Update: Boolean);
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure ThumbMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure ThumbDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ThumbUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Positions: Integer read FPositions write SetPositions default 4;
    property Offset: Integer read FOffset write SetOffset default 0;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voVertical;
    property VThumb: TBitmap index 0 read GetImage write SetImage;
    property HThumb: TBitmap index 1 read GetImage write SetImage;
    property Glyph: TBitmap index 2 read GetImage write SetImage;
    property ThumbStates: Integer read GetThumbStates write SetThumbStates default 1;
    property Style: TVrProgressStyle read FStyle write SetStyle default psBottomLeft;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Options: TVrSwitchOptions read FOptions write SetOptions
      default [soActiveClick, soMouseClip, soHandPoint];
    property BorderColor: TColor read FBorderColor write SetBorderColor default clBtnFace;
    property FocusColor: TColor read FFocusColor write SetFocusColor default clBlue;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color default clBlack;
    property ParentColor default false;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Enabled;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Taborder;
    property TabStop default False;
    property Visible;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnDragDrop;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


implementation

{$R VRSWITCH.D32}

const
  Indent = 3;
  GlyphIndex = 2;
  ThumbNames: array[0..1] of PChar =
    ('VRSWITCHTHUMB_VERT', 'VRSWITCHTHUMB_HORI');

{ TVrSwitchThumb }

constructor TVrSwitchThumb.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  LoadFromResourceName(ThumbNames[0]);
  ThumbStates := 1;
  Cursor := VrCursorHandPoint;
end;

function TVrSwitchThumb.GetImageIndex: Integer;
begin
  Result := 0;
  if HasMouse then Result := 1;
  if Down then Result := 2;
  if not Enabled then Result := 3;
end;

{ TVrSwitch }

constructor TVrSwitch.Create(AOwner: TComponent);
var
  I: TVrSwitchImageRange;
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csSetCaption];
  Width := 24;
  Height := 60;
  Tabstop := False;
  Color := clBlack;
  ParentColor := false;
  FPositions := 4;
  FOffset := 0;
  FOrientation := voVertical;
  FOptions := [soActiveClick, soMouseClip, soHandPoint];
  FStyle := psBottomLeft;
  FBorderColor := clBtnFace;
  FFocusColor := clBlue;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerSpace := 0;
    OuterOutline := osNone;
    OnChange := BevelChanged;
  end;
  FThumb := TVrSwitchThumb.Create(Self);
  with FThumb do
  begin
    Parent := Self;
    OnMouseUp := ThumbUp;
    OnMouseDown := ThumbDown;
    OnMouseMove := ThumbMove;
  end;
  AllocateBitmaps(FImages);
  for I := Low(TVrSwitchImageRange) to High(TVrSwitchImageRange) do
    FImages[I].OnChange := ImageChanged;
  LoadBitmaps;
  FDest := TBitmap.Create;
end;

destructor TVrSwitch.Destroy;
begin
  FDest.Free;
  FThumb.Free;
  FBevel.Free;
  DeallocateBitmaps(FImages);
  inherited Destroy;
end;

procedure TVrSwitch.Loaded;
begin
  inherited Loaded;
  UpdateThumbGlyph;
end;

procedure TVrSwitch.LoadBitmaps;
begin
  FImages[0].LoadFromResourceName(hInstance, ThumbNames[0]);
  FImages[1].LoadFromResourceName(hInstance, ThumbNames[1]);
end;

procedure TVrSwitch.UpdateThumbGlyph;
begin
  if FOrientation = voHorizontal then
    FThumb.Glyph := FImages[1] else FThumb.Glyph := FImages[0];
  AdjustControlSize;  
end;

procedure TVrSwitch.BevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrSwitch.Paint;
var
  R: TRect;
  aGlyph: TBitmap;
begin
  with FDest, Canvas do
  begin
    Width := ClientWidth;
    Height := ClientHeight;
    R := ClientRect;
    Brush.Color := Self.Color;
    if FFocused then Pen.Color := FocusColor
    else Pen.Color := BorderColor;
    Rectangle(R.Left, R.Top, R.Right, R.Bottom);
    InflateRect(R, -1, -1);
    FBevel.Paint(Canvas, R);

    aGlyph := GetImage(GlyphIndex);
    if not aGlyph.Empty then Canvas.StretchDraw(R, aGlyph);
  end;

  with inherited Canvas do Draw(0, 0, FDest);

  case Orientation of
    voVertical: FThumb.Left := (ClientWidth - FThumb.Width) div 2;
    voHorizontal: FThumb.Top := (ClientHeight - FThumb.Height) div 2;
  end;
  SetThumbOffset(GetOffsetByValue(Offset), false);
end;

procedure TVrSwitch.CalcPaintParams;
begin
end;

function TVrSwitch.GetViewPortLength: Integer;
begin
  if Orientation = voVertical then
  begin
    Result := ClientHeight - (Indent * 2);
    Dec(Result, FThumb.Height);
  end
  else
  begin
    Result := ClientWidth - (Indent * 2);
    Dec(Result, FThumb.Width);
  end;
end;

function TVrSwitch.GetValueByOffset(Offset: Integer): Integer;
var
  Range: Double;
begin
  if Orientation = voVertical then
    Offset := ClientHeight - Offset - FThumb.Height;
  Range := Positions - 1;
  Result := Round((Offset - Indent) * Range / GetViewPortLength);
  Result := MinIntVal(MaxIntVal(Result, 0), Positions - 1);
end;

function TVrSwitch.GetOffsetByValue(Value: Integer): Integer;
var
  Range: Double;
begin
  Range := Positions - 1;
  Result := Round(Value / Range * GetViewPortLength) + Indent;
  if (Orientation = voVertical) and (Style = psBottomLeft) then
    Result := ClientHeight - Result - FThumb.Height
  else if (Orientation = voHorizontal) and (Style = psTopRight) then
    Result := ClientWidth - Result - FThumb.Width;
  Result := MaxIntVal(Result, Indent);
end;

procedure TVrSwitch.SetThumbOffset(Value: Integer; Update: Boolean);
var
  OldValue: Integer;
begin
  Value := MinIntVal(MaxIntVal(Value, Indent), Indent + GetViewPortLength);
  if FStyle = psBottomLeft then Value := GetValueByOffset(Value)
  else Value := Pred(Positions) - GetValueByOffset(Value);
  Value := MinIntVal(GetOffsetByValue(Value), Indent + GetViewPortLength);

  if Orientation = voHorizontal then FThumb.Left := Value
  else FThumb.Top := Value;

  if Update then
  begin
    OldValue := Offset;
    if FStyle = psBottomLeft then FOffset := GetValueByOffset(Value)
    else FOffset := Pred(Positions) - GetValueByOffset(Value);
    if FOffset <> OldValue then
    begin
      UpdateControlCanvas;
      Change;
    end;
  end;
end;

procedure TVrSwitch.AdjustControlSize;
var
  NewWidth, NewHeight: Integer;
begin
  if Orientation = voHorizontal then
  begin
    NewWidth := (FThumb.Width * FPositions) + (Indent * 2);
    NewHeight := FThumb.Height + (Indent * 2);
  end
  else
  begin
    NewWidth := FThumb.Width + (Indent * 2);
    NewHeight := (FThumb.Height * FPositions) + (Indent * 2);
  end;
  BoundsRect := Bounds(Left, Top, NewWidth, NewHeight);
end;

procedure TVrSwitch.WMSize(var Message: TWMSize);
begin
  inherited;
  AdjustControlSize;
end;

procedure TVrSwitch.WMGetDlgCode(var Msg: TWMGetDlgCode);
begin
  Msg.Result := DLGC_WANTARROWS;
end;

procedure TVrSwitch.CMFocusChanged(var Message: TCMFocusChanged);
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

procedure TVrSwitch.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  FTHumb.Enabled := Enabled;
end;

procedure TVrSwitch.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

function TVrSwitch.GetThumbStates: Integer;
begin
  Result := FThumb.ThumbStates;
end;

procedure TVrSwitch.SetThumbStates(Value: Integer);
begin
  if Value > 0 then FThumb.ThumbStates := Value;
  UpdateThumbGlyph;
end;

procedure TVrSwitch.ImageChanged(Sender: TObject);
begin
  UpdateThumbGlyph;
  UpdateControlCanvas;
end;

function TVrSwitch.GetImage(Index: Integer): TBitmap;
begin
  Result := FImages[Index];
end;

procedure TVrSwitch.SetImage(Index: Integer; Value: TBitmap);
begin
  if (Value = nil) and (Index <> GlyphIndex) then
    FImages[Index].LoadFromResourceName(hInstance, ThumbNames[Index])
  else FImages[Index].Assign(Value);
end;

procedure TVrSwitch.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    UpdateThumbGlyph;
    if not Loading then
    begin
      BoundsRect := Bounds(Left, Top, Height, Width);
      AdjustControlSize;
    end;
    UpdateControlCanvas;
  end;
end;

procedure TVrSwitch.SetStyle(Value: TVrProgressStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSwitch.SetOffset(Value: Integer);
begin
  if Value < 0 then Value := 0;
  if Value > Positions - 1 then Value := Positions - 1;
  if FOffset <> Value then
  begin
    FOffset := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrSwitch.SetPositions(Value: Integer);
begin
  if FPositions <> Value then
  begin
    FPositions := Value;
    AdjustControlSize;
  end;
end;

procedure TVrSwitch.SetOptions(Value: TVrSwitchOptions);
begin
  if FOptions <> Value then
  begin
    FOptions := Value;
    if soHandPoint in Value then FThumb.Cursor := VrCursorHandPoint
    else FThumb.Cursor := crDefault;
  end;
end;

procedure TVrSwitch.SetBorderColor(Value: TColor);
begin
  if FBorderColor <> Value then
  begin
    FBorderColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSwitch.SetFocusColor(Value: TColor);
begin
  if FFocusColor <> Value then
  begin
    FFocusColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSwitch.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrSwitch.ThumbDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  R: TRect;
begin
  if TabStop then SetFocus;
  if Button = mbLeft then
  begin
    if Orientation = voVertical then FHit := Y
    else FHit := X;
    FThumb.Down := True;
    if (soMouseClip in Options) then
    begin
      R := Bounds(ClientOrigin.X, ClientOrigin.Y, ClientWidth, ClientHeight);
      ClipCursor(@R);
      FClipOn := True;
    end;
  end;
end;

procedure TVrSwitch.ThumbMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
var
  P: TPoint;
  Value: Integer;
begin
  if FThumb.Down then
  begin
    P := ScreenToClient(FThumb.ClientToScreen(Point(X, Y)));
    if Orientation = voVertical then Value := P.Y
    else Value := P.X;
    Dec(Value, FHit);
    SetThumbOffset(Value, True);
  end;
end;

procedure TVrSwitch.ThumbUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  FThumb.Down := False;
  if FClipOn then
  begin
    ClipCursor(nil);
    FClipOn := false;
  end;
end;

procedure TVrSwitch.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  if (soActiveClick in FOptions) and (Button = mbLeft) then
  begin
    if TabStop then SetFocus;
    if Orientation = voVertical then FHit := Y - FThumb.Height div 2
    else FHit := X - FThumb.Width div 2;
    SetThumbOffset(FHit, True);
  end;
  inherited;
end;

procedure TVrSwitch.KeyDown(var Key: Word; Shift: TShiftState);

  function Adjust(Value: Integer): Integer;
  begin
    Result := Value;
    if Style = psTopRight then Result := -Result;
  end;

begin
  if Shift = [] then
  begin
    if Key = VK_HOME then Offset := 0
    else if Key = VK_END then Offset := Positions - 1;
    if Orientation = voHorizontal then
    begin
      if Key = VK_LEFT then Offset := Offset + Adjust(-1)
      else if Key = VK_RIGHT then Offset := Offset + Adjust(1);
    end
    else
    begin
      if Key = VK_UP then Offset := Offset + Adjust(1)
      else if Key = VK_DOWN then Offset := Offset + Adjust(-1);
    end;
  end;
  inherited KeyDown(Key, Shift);
end;


end.
