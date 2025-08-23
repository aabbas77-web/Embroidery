{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrSlider;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrConst, VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrSliderThumb = class(TVrCustomThumb)
  protected
    function GetImageIndex: Integer; override;
  public
    constructor Create(AOwner: TComponent); override;
  end;

  TVrSliderStyle = (ssBottomLeft, ssTopRight);
  TVrSliderOption = (soActiveClick, soMouseClip, soHandPoint);
  TVrSliderOptions = set of TVrSliderOption;
  TVrSliderImageRange = 0..3;
  TVrSliderImages = array[TVrSliderImageRange] of TBitmap;

  TVrSlider = class(TVrCustomImageControl)
  private
    FMin: Integer;
    FMax: Integer;
    FPosition: Integer;
    FFocusColor: TColor;
    FBorderColor: TColor;
    FOrientation: TVrOrientation;
    FStyle: TVrSliderStyle;
    FPalette: TVrPalette;
    FBevel: TVrBevel;
    FTickHeight: Integer;
    FSpacing: Integer;
    FSolidFill: Boolean;
    FOptions: TVrSliderOptions;
    FOnChange: TNotifyEvent;
    FViewPort: TRect;
    FThumb: TVrSliderThumb;
    FFocused: Boolean;
    FKeyIncrement: Integer;
    FClipOn: Boolean;
    FHit: Integer;
    FIndent: Integer;
    FStep, FTicks: Integer;
    FImages: TVrSliderImages;
    function Progress: Longint;
    function GetThumbImage(Index: Integer): TBitmap;
    function GetThumbStates: Integer;
    procedure SetMin(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetBorderColor(Value: TColor);
    procedure SetFocusColor(Value: TColor);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetStyle(const Value: TVrSliderStyle);
    procedure SetThumbImage(Index: Integer; Value: TBitmap);
    procedure SetTickHeight(Value: Integer);
    procedure SetSpacing(Value: Integer);
    procedure SetSolidFill(Value: Boolean);
    procedure SetOptions(Value: TVrSliderOptions);
    procedure SetThumbStates(Value: Integer);
    procedure SetPalette(Value: TVrPalette);
    procedure SetBevel(Value: TVrBevel);
    procedure UpdateThumbGlyph;
    procedure BevelChanged(Sender: TObject);
    procedure ImageChanged(Sender: TObject);
    procedure PaletteModified(Sender: TObject);
    procedure WMSize(var Message: TWMSize); message WM_SIZE;
    procedure CMFocusChanged(var Message: TCMFocusChanged); message CM_FOCUSCHANGED;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
    procedure WMGetDlgCode(var Msg: TWMGetDlgCode); message WM_GETDLGCODE;
  protected
    procedure DrawHori;
    procedure DrawVert;
    procedure Paint; override;
    procedure CalcPaintParams;
    procedure Change; dynamic;
    procedure Loaded; override;
    procedure LoadBitmaps; virtual;
    procedure CreateViewPortImages;
    function GetViewPortLength: Integer;
    procedure SetThumbOffset(Value: Integer; Update: Boolean);
    function GetValueByOffset(Offset: Integer): Integer;
    function GetOffsetByValue(Value: Longint): Integer;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure ThumbMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure ThumbDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure ThumbUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property Position: Integer read FPosition write SetPosition default 0;
    property FocusColor: TColor read FFocusColor write SetFocusColor default clBlue;
    property BorderColor: TColor read FBorderColor write SetBorderColor default clBtnFace;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voVertical;
    property Style: TVrSliderStyle read FStyle write SetStyle default ssBottomLeft;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property VThumb: TBitmap index 2 read GetThumbImage write SetThumbImage;
    property HThumb: TBitmap index 3 read GetThumbImage write SetThumbImage;
    property Palette: TVrPalette read FPalette write SetPalette;
    property SolidFill: Boolean read FSolidFill write SetSolidFill default false;
    property Spacing: Integer read FSpacing write SetSpacing default 1;
    property TickHeight: Integer read FTickHeight write SetTickHeight default 1;
    property Options: TVrSliderOptions read FOptions write SetOptions
      default [soActiveClick, soMouseClip, soHandPoint];
    property ThumbStates: Integer read GetThumbStates write SetThumbStates default 1;
    property KeyIncrement: Integer read FKeyIncrement write FKeyIncrement default 5;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Enabled;
    property Color default clBlack;
    property Cursor;
    property DragMode;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragCursor;
    property ParentColor default false;
    property ParentShowHint;
    property ShowHint;
    property TabOrder;
    property TabStop default false;
    property Visible;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}
    property OnDblClick;
    property OnMouseMove;
    property OnMouseDown;
    property OnMouseUp;
    property OnKeyDown;
    property OnKeyUp;
    property OnKeyPress;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnDragDrop;
    property OnEndDrag;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


  
implementation

{$R VRSLIDER.D32}

const
  BevelIndent = 2;
  ThumbNames: array[2..3] of PChar =
    ('VRSLIDERTHUMB_VERT', 'VRSLIDERTHUMB_HORI');


{ TVrSliderThumb }

constructor TVrSliderThumb.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  LoadFromResourceName(ThumbNames[3]);
  ThumbStates := 1;
  Cursor := VrCursorHandPoint;
  Left := -1000;
end;

function TVrSliderThumb.GetImageIndex: Integer;
begin
  Result := 0;
  if HasMouse then Result := 1;
  if Down then Result := 2;
  if not Enabled then Result := 3;
end;

{ TVrSlider }

constructor TVrSlider.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 37;
  Height := 170;
  TabStop := false;
  Color := clBlack;
  ParentColor := false;
  FMin := 0;
  FMax := 100;
  FPosition := 0;
  FFocusColor := clBlue;
  FBorderColor := clBtnFace;
  FOrientation := voVertical;
  FStyle := ssBottomLeft;
  FTickHeight := 1;
  FSpacing := 1;
  FSolidFill := false;
  FOptions := [soActiveClick, soMouseClip, soHandPoint];
  FKeyIncrement := 5;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  FThumb := TVrSliderThumb.Create(Self);
  with FThumb do
  begin
    Parent := Self;
    OnMouseUp := ThumbUp;
    OnMouseDown := ThumbDown;
    OnMouseMove := ThumbMove;
  end;
  AllocateBitmaps(FImages);
  FImages[2].OnChange := ImageChanged;
  FImages[3].OnChange := ImageChanged;
  LoadBitmaps;
end;

destructor TVrSlider.Destroy;
begin
  FThumb.Free;
  FBevel.Free;
  FPalette.Free;
  DeallocateBitmaps(FImages);
  inherited Destroy;
end;

procedure TVrSlider.Loaded;
begin
  inherited Loaded;
  UpdateThumbGlyph;
end;

procedure TVrSlider.LoadBitmaps;
begin
  FImages[2].LoadFromResourceName(hInstance, ThumbNames[2]);
  FImages[3].LoadFromResourceName(hInstance, ThumbNames[3]);
end;

procedure TVrSlider.UpdateThumbGlyph;
begin
  if FOrientation = voHorizontal then
    FThumb.Glyph := FImages[2] else FThumb.Glyph := FImages[3];
end;

procedure TVrSlider.CreateViewPortImages;
var
  R: TRect;
begin
  R := ClientRect;
  InflateRect(R, -1, -1);
  FBevel.GetVisibleArea(R);

  with FImages[0] do
  begin
    case FOrientation of
      voVertical:
        begin
          Height := FTickHeight;
          Width := WidthOf(R);
        end;
      voHorizontal:
        begin
          Height := HeightOf(R);
          Width := FTickHeight;
        end;
    end;

    if (FTickHeight > 1) and (not FSolidFill) then
      Canvas.Brush.Bitmap := CreateDitherPattern(FPalette.Low, clBlack)
    else
      Canvas.Brush.Color := FPalette.Low;
    try
      R := Bounds(0, 0, Width, Height);
      Canvas.FillRect(R);
    finally
      if Canvas.Brush.Bitmap <> nil then
      begin
        Canvas.Brush.Bitmap.Free;
        Canvas.Brush.Bitmap := nil;
      end;
    end;
  end;

  with FImages[1] do
  begin
    Width := FImages[0].Width;
    Height := FImages[0].Height;
    Canvas.Brush.Color := FPalette.High;
    Canvas.FillRect(R);
  end;
end;

function TVrSlider.Progress: Longint;
begin
  Result := SolveForY(FPosition - FMin, FMax - FMin);
end;

procedure TVrSlider.DrawHori;
var
  X, Y, I, Offset: Integer;
  TicksOn, TicksOff: Integer;
begin
  TicksOn := SolveForX(Progress, FTicks);
  TicksOff := FTicks - TicksOn;

  Y := FViewPort.Top;
  if FStyle = ssBottomLeft then
  begin
    X := FViewPort.Left;
    Offset := FStep;
  end
  else
  begin
    X := FViewPort.Right - FTickHeight;
    Offset := -FStep;
  end;

  for I := 1 to TicksOn do
  begin
    BitmapCanvas.Draw(X, Y, FImages[1]);
    Inc(X, Offset);
  end;
  for I := 1 to TicksOff do
  begin
    BitmapCanvas.Draw(X, Y, FImages[0]);
    Inc(X, Offset);
  end;
end;

procedure TVrSlider.DrawVert;
var
  X, Y, I, Offset: Integer;
  TicksOn, TicksOff: Integer;
begin
  TicksOn := SolveForX(Progress, FTicks);
  TicksOff := FTicks - TicksOn;

  X := FViewPort.Left;
  if FStyle = ssBottomLeft then
  begin
    Y := FViewPort.Top;
    Offset := FStep;
  end
  else
  begin
    Y := FViewPort.Bottom - FTickHeight;
    Offset := -FStep;
  end;

  for I := 1 to TicksOff do
  begin
    BitmapCanvas.Draw(X, Y, FImages[0]);
    Inc(Y, Offset);
  end;
  for I := 1 to TicksOn do
  begin
    BitmapCanvas.Draw(X, Y, FImages[1]);
    Inc(Y, Offset);
  end;
end;

procedure TVrSlider.Paint;
var
  R: TRect;
begin
  CalcPaintParams;

  with BitmapImage, BitmapCanvas do
  begin
    if FFocused then Pen.Color := FFocusColor
      else Pen.Color := FBorderColor;
    Brush.Color := Self.Color;
    R := ClientRect;
    Rectangle(R.Left, R.Top, R.Right, R.Bottom);
    InflateRect(R, -1, -1);
    FBevel.Paint(BitmapCanvas, R);

    case FOrientation of
      voVertical:
        begin
          DrawVert;
          FThumb.Left := (ClientWidth - FThumb.Width) div 2;
        end;
      voHorizontal:
        begin
          DrawHori;
          FThumb.Top := (ClientHeight - FThumb.Height) div 2;
        end;
    end;
  end;

  inherited Paint;

  SetThumbOffset(GetOffsetByValue(Position), false);
end;

procedure TVrSlider.CalcPaintParams;
begin
  FViewPort := ClientRect;
  InflateRect(FViewPort, -1, -1);
  FBevel.GetVisibleArea(FViewPort);
  FIndent := FViewPort.Left - BevelIndent;

  FStep := FTickHeight + FSpacing;
  case Orientation of
    voVertical:
      begin
        FTicks := (HeightOf(FViewPort) + FSpacing) div FStep;
        Height := (FViewPort.Top * 2) + (FTicks * FStep) - FSpacing;
      end;
    voHorizontal:
      begin
        FTicks := (WidthOf(FViewPort) + FSpacing) div FStep;
        Width := (FViewPort.Left * 2) + (FTicks * FStep) - FSpacing;
      end;
  end;
end;

procedure TVrSlider.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrSlider.BevelChanged(Sender: TObject);
var
  R: TRect;
begin
  if not Loading then
  begin
    R := ClientRect;
    FBevel.GetVisibleArea(R);
    InflateRect(FViewPort, R.Left + 1, R.Top + 1);
    BoundsRect := Bounds(Left, Top, WidthOf(FViewPort),
      HeightOf(FViewPort));
  end;
  CreateViewPortImages;
  UpdateControlCanvas;
end;

procedure TVrSlider.PaletteModified(Sender: TObject);
begin
  CreateViewPortImages;
  UpdateControlCanvas;
end;

function TVrSlider.GetViewPortLength: Integer;
begin
  if FOrientation = voVertical then
  begin
    Result := HeightOf(FViewPort) + (BevelIndent * 2);
    Dec(Result, FThumb.Height);
  end
  else
  begin
    Result := WidthOf(FViewPort) + (BevelIndent * 2);
    Dec(Result, FThumb.Width);
  end;
end;

function TVrSlider.GetOffsetByValue(Value: Longint): Integer;
var
  Range: Double;
begin
  Range := FMax - FMin;
  Result := Round((Value - FMin) / Range * GetViewPortLength) + FIndent;
  if (FOrientation = voVertical) and (FStyle = ssBottomLeft) then
    Result := ClientHeight - Result - FThumb.Height
  else if (FOrientation = voHorizontal) and (FStyle = ssTopRight) then
    Result := ClientWidth - Result - FThumb.Width;
end;

function TVrSlider.GetValueByOffset(Offset: Integer): Integer;
var
  Range: Double;
begin
  if Orientation = voVertical then
    Offset := ClientHeight - Offset - FThumb.Height;
  Range := FMax - FMin;
  Result := Round((Offset - FIndent) * Range / GetViewPortLength);
  Result := MinIntVal(FMin + MaxIntVal(Result, 0), FMax);
end;

procedure TVrSlider.SetThumbOffset(Value: Integer; Update: Boolean);
var
  OldValue: Integer;
begin
  Value := MinIntVal(MaxIntVal(Value, FIndent), FIndent + GetViewPortLength);
  if FOrientation = voVertical then
    FThumb.Top := Value else FThumb.Left := Value;
  if Update then
  begin
    OldValue := Position;
    if FStyle = ssBottomLeft then FPosition := GetValueByOffset(Value)
    else FPosition := FMax - GetValueByOffset(Value) + FMin;
    if FPosition <> OldValue then
    begin
      UpdateControlCanvas;
      Change;
    end;
  end;
end;

procedure TVrSlider.CMFocusChanged(var Message: TCMFocusChanged);
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

procedure TVrSlider.WMSize(var Message: TWMSize);
begin
  inherited;
  CreateViewPortImages;
  UpdateControlCanvas;
end;

procedure TVrSlider.WMGetDlgCode(var Msg: TWMGetDlgCode);
begin
  Msg.Result := DLGC_WANTARROWS;
end;

procedure TVrSlider.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  FThumb.Enabled := Enabled;
end;

procedure TVrSlider.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrSlider.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrSlider.SetMax(Value: Integer);
begin
  if FMax <> Value then
  begin
    FMax := Value;
    if FPosition > FMax then Position := FMax
    else UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetMin(Value: Integer);
begin
  if FMin <> Value then
  begin
    FMin := Value;
    if FPosition < FMin then Position := FMin
    else UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetPosition(Value: Integer);
begin
  if Value < FMin then Value := FMin;
  if Value > FMax then Value := FMax;
  if FPosition <> Value then
  begin
    FPosition := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrSlider.SetBorderColor(Value: TColor);
begin
  if FBorderColor <> Value then
  begin
    FBorderColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetFocusColor(Value: TColor);
begin
  if FFocusColor <> Value then
  begin
    FFocusColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if not Loading then
    begin
      BoundsRect := Bounds(Left, Top, Height, Width);
      CreateViewPortImages;
    end;
    UpdateThumbGlyph;
    UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetStyle(const Value: TVrSliderStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSlider.ImageChanged(Sender: TObject);
begin
  UpdateThumbGlyph;
  UpdateControlCanvas;
end;

function TVrSlider.GetThumbImage(Index: Integer): TBitmap;
begin
  Result := FImages[Index];
end;

procedure TVrSlider.SetThumbImage(Index: Integer; Value: TBitmap);
begin
  if Value = nil then
    FImages[Index].LoadFromResourceName(hInstance, ThumbNames[Index])
  else FImages[Index].Assign(Value);
end;

procedure TVrSlider.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetSolidFill(Value: Boolean);
begin
  if FSolidFill <> Value then
  begin
    FSolidFill := Value;
    CreateViewPortImages;
    UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetTickHeight(Value: Integer);
begin
  if (FTickHeight <> Value) and (Value > 0) then
  begin
    FTickHeight := Value;
    CreateViewPortImages;
    UpdateControlCanvas;
  end;
end;

procedure TVrSlider.SetOptions(Value: TVrSliderOptions);
begin
  if FOptions <> Value then
  begin
    FOptions := Value;
    if soHandPoint in Value then FThumb.Cursor := VrCursorHandPoint
    else FThumb.Cursor := crDefault;
  end;
end;

function TVrSlider.GetThumbStates: Integer;
begin
  Result := FThumb.ThumbStates;
end;

procedure TVrSlider.SetThumbStates(Value: Integer);
begin
  if Value > 0 then FThumb.ThumbStates := Value;
end;

procedure TVrSlider.ThumbDown(Sender: TObject;Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  R: TRect;
begin
  if TabStop then SetFocus;
  if Button = mbLeft then
  begin
    if FOrientation = voVertical then FHit := Y
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

procedure TVrSlider.ThumbMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
var
  P: TPoint;
  Value: Integer;
begin
  if FThumb.Down then
  begin
    P := ScreenToClient(FThumb.ClientToScreen(Point(X, Y)));
    if FOrientation = voVertical then Value := P.Y
    else Value := P.X;
    Dec(Value, FHit);
    SetThumbOffset(Value, True);
  end;
end;

procedure TVrSlider.ThumbUp(Sender: TObject;Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  FThumb.Down := False;
  if FClipOn then
  begin
    ClipCursor(nil);
    FClipOn := false;
  end;
end;

procedure TVrSlider.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  if (soActiveClick in FOptions) and (Button = mbLeft) then
    if PtInRect(FViewPort, Point(X, Y)) then
    begin
      if TabStop then SetFocus;
      if FOrientation = voVertical then FHit := Y - FThumb.Height div 2
      else FHit := X - FThumb.Width div 2;
      SetThumbOffset(FHit, True);
    end;
  inherited;
end;

procedure TVrSlider.KeyDown(var Key: Word; Shift: TShiftState);

  function Adjust(Value: Integer): Integer;
  begin
    Result := Value;
    if Style = ssTopRight then Result := -Result;
  end;

begin
  if Shift = [] then
  begin
    if Key = VK_HOME then Position := FMax
    else if Key = VK_END then Position := FMin;
    if Orientation = voHorizontal then
    begin
      if Key = VK_LEFT then Position := Position + Adjust(-FKeyIncrement)
      else if Key = VK_RIGHT then Position := Position + Adjust(FKeyIncrement);
    end
    else
    begin
      if Key = VK_UP then Position := Position + Adjust(FKeyIncrement)
      else if Key = VK_DOWN then Position := Position + Adjust(-FKeyIncrement);
    end;
  end;
  inherited KeyDown(Key, Shift);
end;


end.
