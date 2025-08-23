{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrTrackBar;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrConst, VrTypes, VrClasses, VrControls, VrSysUtils;


type
  TVrTrackBarOption = (toActiveClick, toMouseClip, toHandPoint, toFixedPoints);
  TVrTrackBarOptions = set of TVrTrackBarOption;
  TVrTrackBarImageRange = 0..2;
  TVrTrackBarImages = array[TVrTrackBarImageRange] of TBitmap;

  TVrTrackBarThumb = class(TVrCustomThumb)
  protected
    function GetImageIndex: Integer; override;
  public
    constructor Create(AOwner: TComponent); override;
  end;

  TVrTrackBar = class(TVrCustomImageControl)
  private
    FMin: Integer;
    FMax: Integer;
    FPosition: Integer;
    FStyle: TVrProgressStyle;
    FOrientation: TVrOrientation;
    FOptions: TVrTrackBarOptions;
    FFrequency: Integer;
    FBorderWidth: Integer;
    FGutterBevel: TVrBevel;
    FGutterWidth: Integer;
    FGutterColor: TColor;
    FTickMarks: TVrTickMarks;
    FTickColor: TColor;
    FScaleOffset: Integer;
    FOnChange: TNotifyEvent;
    FHit: Integer;
    FClipOn: Boolean;
    FFocused: Boolean;
    FThumb: TVrTrackBarThumb;
    FImages: TVrTrackBarImages;
    function GetThumbStates: Integer;
    function GetImage(Index: Integer): TBitmap;
    procedure SetMin(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetStyle(Value: TVrProgressStyle);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetOptions(Value: TVrTrackBarOptions);
    procedure SetFrequency(Value: Integer);
    procedure SetBorderWidth(Value: Integer);
    procedure SetGutterWidth(Value: Integer);
    procedure SetGutterColor(Value: TColor);
    procedure SetGutterBevel(Value: TVrBevel);
    procedure SetTickMarks(Value: TVrTickMarks);
    procedure SetTickColor(Value: TColor);
    procedure SetScaleOffset(Value: Integer);
    procedure SetThumbStates(Value: Integer);
    procedure SetImage(Index: Integer; Value: TBitmap);
    procedure DrawScale(Canvas: TCanvas; Offset, ThumbOffset,
      RulerLength, PointsStep, PointsHeight, ExtremePointsHeight: Integer);
    procedure UpdateThumbGlyph;
    procedure GutterBevelChanged(Sender: TObject);
    procedure ImageChanged(Sender: TObject);
    procedure WMGetDlgCode(var Msg: TWMGetDlgCode); message WM_GETDLGCODE;
    procedure CMFocusChanged(var Message: TCMFocusChanged); message CM_FOCUSCHANGED;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
  protected
    procedure Loaded; override;
    procedure LoadBitmaps; virtual;
    procedure Paint; override;
    procedure Change; dynamic;
    function GetRulerLength: Integer;
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
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property Position: Integer read FPosition write SetPosition default 0;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property Style: TVrProgressStyle read FStyle write SetStyle default psBottomLeft;
    property Options: TVrTrackBarOptions read FOptions write SetOptions
      default [toActiveClick, toMouseClip, toHandPoint];
    property Frequency: Integer read FFrequency write SetFrequency default 10;
    property BorderWidth: Integer read FBorderWidth write SetBorderWidth default 10;
    property GutterBevel: TVrBevel read FGutterBevel write SetGutterBevel;
    property GutterWidth: Integer read FGutterWidth write SetGutterWidth default 9;
    property GutterColor: TColor read FGutterColor write SetGutterColor default clBlack;
    property TickMarks: TVrTickMarks read FTickMarks write SetTickMarks default tmBoth;
    property TickColor: TColor read FTickColor write SetTickColor default clBlack;
    property ThumbStates: Integer read GetThumbStates write SetThumbStates default 1;
    property VThumb: TBitmap index 0 read GetImage write SetImage;
    property HThumb: TBitmap index 1 read GetImage write SetImage;
    property Bitmap: TBitmap index 2 read GetImage write SetImage;
    property ScaleOffset: Integer read FScaleOffset write SetScaleOffset default 5;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Enabled;
    property Color;
    property Cursor;
    property DragMode;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragCursor;
    property ParentColor;
    property ParentShowHint;
    property ShowHint;
    property TabOrder;
    property TabStop default false;
    property Visible;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}
    property OnEnter;
    property OnExit;
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

{$R VRTRACKBAR.D32}

const
  ThumbNames: array[0..1] of PChar =
    ('VRTB_VERT', 'VRTB_HORI');

  BkImage = 2;


{ TVrTrackBarThumb }

constructor TVrTrackBarThumb.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  LoadFromResourceName(ThumbNames[1]);
  ThumbStates := 1;
  Cursor := VrCursorHandPoint;
end;

function TVrTrackBarThumb.GetImageIndex: Integer;
begin
  Result := 0;
  if HasMouse then Result := 1;
  if Down then Result := 2;
  if not Enabled then Result := 3;
end;

{ TVrTrackBar }

constructor TVrTrackBar.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 175;
  Height := 45;
  TabStop := false;
  FMin := 0;
  FMax := 100;
  FPosition := 0;
  FStyle := psBottomLeft;
  FOrientation := voHorizontal;
  FOptions := [toActiveClick, toMouseClip, toHandPoint];
  FFrequency := 10;
  FBorderWidth := 10;
  FTickMarks := tmBoth;
  FTickColor := clBlack;
  FScaleOffset := 5;
  FGutterWidth := 9;
  FGutterColor := clBlack;
  FGutterBevel := TVrBevel.Create;
  with FGutterBevel do
  begin
    InnerStyle := bsNone;
    InnerSpace := 0;
    InnerOutline := osNone;
    OuterStyle := bsLowered;
    OuterSpace := 0;
    OuterOutline := osNone;
    OnChange := GutterBevelChanged;
  end;
  FThumb := TVrTrackBarThumb.Create(Self);
  with FThumb do
  begin
    Parent := Self;
    OnMouseUp := ThumbUp;
    OnMouseDown := ThumbDown;
    OnMouseMove := ThumbMove;
  end;
  AllocateBitmaps(FImages);
  FImages[0].OnChange := ImageChanged;
  FImages[1].OnChange := ImageChanged;
  FImages[2].OnChange := ImageChanged;
  LoadBitmaps;
end;

destructor TVrTrackBar.Destroy;
begin
  FThumb.Free;
  FGutterBevel.Free;
  DeallocateBitmaps(FImages);
  inherited Destroy;
end;

procedure TVrTrackBar.Loaded;
begin
  inherited Loaded;
  UpdateThumbGlyph;
end;

procedure TVrTrackBar.LoadBitmaps;
begin
  FImages[0].LoadFromResourceName(hInstance, ThumbNames[0]);
  FImages[1].LoadFromResourceName(hInstance, ThumbNames[1]);
end;

procedure TVrTrackBar.UpdateThumbGlyph;
begin
  if FOrientation = voHorizontal then
    FThumb.Glyph := FImages[1] else FThumb.Glyph := FImages[0];
end;

procedure TVrTrackBar.Paint;
var
  R: TRect;
  Offset: Integer;
begin
  with BitmapImage, BitmapCanvas do
  begin
    if FImages[bkImage].Empty then
    begin
      Brush.Color := Self.Color;
      FillRect(ClientRect);
    end else StretchDraw(ClientRect, FImages[bkImage]);

    Pen.Color := TickColor;
    case Orientation of
      voVertical:
        begin
          Offset := (ClientWidth - FGutterWidth) div 2;
          R := Bounds(Offset, BorderWidth, GutterWidth,
            ClientHeight - FBorderWidth * 2);
          FThumb.Left := (ClientWidth - FThumb.Width) div 2;
          if (FTickMarks in [tmBoth, tmTopLeft]) then
            DrawScale(BitmapCanvas, R.Left - FScaleOffset, FThumb.Height div 2,
                      GetRulerLength, Frequency, -3, -4);
          if (FTickMarks in [tmBoth, tmBottomRight]) then
            DrawScale(BitmapCanvas, R.Right + FScaleOffset, FThumb.Height div 2,
                      GetRulerLength, Frequency, 3, 4);
        end;
      voHorizontal:
        begin
          Offset := (ClientHeight - FGutterWidth) div 2;
          R := Bounds(BorderWidth, Offset,
            ClientWidth - FBorderWidth * 2, GutterWidth);
          FThumb.Top := (ClientHeight - FThumb.Height) div 2;
          if (FTickMarks in [tmBoth, tmTopLeft]) then
            DrawScale(BitmapCanvas, R.Top - FScaleOffset, FThumb.Width div 2,
                      GetRulerLength, Frequency, -3, -4);
          if (FTickMarks in [tmBoth, tmBottomRight]) then
            DrawScale(BitmapCanvas, R.Bottom + FScaleOffset, FThumb.Width div 2,
                      GetRulerLength, Frequency, 3, 4);
        end;
    end;
    GutterBevel.Paint(BitmapCanvas, R);
    Brush.Color := GutterColor;
    FillRect(R);

    if (Focused) then
    begin
      R := ClientRect;
      InflateRect(R, -2, -2);
      FrameRect(R);
    end;

  end; { Bitmap, BitmapCanvas }

  inherited Paint;

  SetThumbOffset(GetOffsetByValue(Position), false);
end;

procedure TVrTrackBar.DrawScale(Canvas: TCanvas; Offset, ThumbOffset,
  RulerLength, PointsStep, PointsHeight, ExtremePointsHeight: Integer);
const
  MinInterval = 3;
var
  Interval, Scale, Cnt, I, Value: Integer;
  X, H, X1, X2, Y1, Y2, Tmp: Integer;
  Range: Double;
begin
  Scale := 0;
  Range := FMax - FMin;
  repeat
    Inc(Scale);
    Cnt := Round(Range / (Scale * PointsStep)) + 1;
    if Cnt > 1 then
      Interval := RulerLength div (Cnt - 1)
    else Interval := RulerLength;
  until (Interval >= MinInterval + 1) or (Interval >= RulerLength);
  Value := FMin;
  for I := 1 to Cnt do
  begin
    H := PointsHeight;
    if I = Cnt then Value := FMax;
    if (Value = FMax) or (Value = FMin) then H := ExtremePointsHeight;
    X := GetOffsetByValue(Value);
    if Orientation = voHorizontal then
    begin
      X1 := X + ThumbOffset;
      Y1 := Offset;
      X2 := X1 + 1;
      Y2 := Y1 + H;
      if Y1 > Y2 then
      begin
        Tmp := Y1;
        Y1 := Y2;
        Y2 := Tmp;
      end;
    end
    else
    begin
      X1 := Offset;
      Y1 := X + ThumbOffset;
      X2 := X1 + H;
      Y2 := Y1 + 1;
      if X1 > X2 then
      begin
        Tmp := X1;
        X1 := X2;
        X2 := Tmp;
      end;
    end;
    Canvas.Rectangle(X1, Y1, X2, Y2);
    Inc(Value, Scale * PointsStep);
  end;
end;

procedure TVrTrackBar.WMGetDlgCode(var Msg: TWMGetDlgCode);
begin
  Msg.Result := DLGC_WANTARROWS;
end;

procedure TVrTrackBar.CMFocusChanged(var Message: TCMFocusChanged);
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

procedure TVrTrackBar.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  FThumb.Enabled := Enabled;
end;

procedure TVrTrackBar.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrTrackBar.GutterBevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

function TVrTrackBar.GetRulerLength: Integer;
begin
  if Orientation = voVertical then
  begin
    Result := ClientHeight - (FBorderWidth * 2);
    Dec(Result, FThumb.Height);
  end
  else
  begin
    Result := ClientWidth - (FBorderWidth * 2);
    Dec(Result, FThumb.Width);
  end;
end;

function TVrTrackBar.GetValueByOffset(Offset: Integer): Integer;
var
  Range: Double;
begin
  if Orientation = voVertical then
    Offset := ClientHeight - Offset - FThumb.Height;
  Range := FMax - FMin;
  Result := Round((Offset - BorderWidth) * Range / GetRulerLength);
  if (toFixedPoints in Options) then
    Result := (Result div Frequency) * Frequency;
  Result := MinIntVal(FMin + MaxIntVal(Result, 0), FMax);
end;

function TVrTrackBar.GetOffsetByValue(Value: Integer): Integer;
var
  Range: Double;
begin
  Range := FMax - FMin;
  Result := Round((Value - FMin) / Range * GetRulerLength) + BorderWidth;
  if (Orientation = voVertical) and (Style = psBottomLeft) then
    Result := ClientHeight - Result - FThumb.Height
  else if (Orientation = voHorizontal) and (Style = psTopRight) then
    Result := ClientWidth - Result - FThumb.Width;
  Result := MaxIntVal(Result, BorderWidth);
end;

procedure TVrTrackBar.SetThumbOffset(Value: Integer; Update: Boolean);
var
  OldValue: Integer;
begin
  Value := MinIntVal(MaxIntVal(Value, BorderWidth), BorderWidth + GetRulerLength);
  if (toFixedPoints in Options) then
  begin
    if FStyle = psBottomLeft then Value := GetValueByOffset(Value)
    else Value := FMax - GetValueByOffset(Value) + FMin;
    Value := MinIntVal(GetOffsetByValue(Value),
      BorderWidth + GetRulerLength);
  end;
  if Orientation = voHorizontal then FThumb.Left := Value
  else FThumb.Top := Value;
  if Update then
  begin
    OldValue := Position;
    if FStyle = psBottomLeft then FPosition := GetValueByOffset(Value)
    else FPosition := FMax - GetValueByOffset(Value) + FMin;
    if FPosition <> OldValue then
    begin
      UpdateControlCanvas;
      Change;
    end;
  end;
end;

procedure TVrTrackBar.SetMax(Value: Integer);
begin
  if FMax <> Value then
  begin
    FMax := Value;
    if FPosition > FMax then Position := FMax
    else UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetMin(Value: Integer);
begin
  if FMin <> Value then
  begin
    FMin := Value;
    if FPosition < FMin then Position := FMin
    else UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetPosition(Value: Integer);
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

procedure TVrTrackBar.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if not Loading then
      BoundsRect := Bounds(Left, Top, Height, Width);
    UpdateThumbGlyph;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetStyle(Value: TVrProgressStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetOptions(Value: TVrTrackBarOptions);
begin
  if FOptions <> Value then
  begin
    FOptions := Value;
    if toHandPoint in Value then FThumb.Cursor := VrCursorHandPoint
    else FThumb.Cursor := crDefault;
  end;
end;

procedure TVrTrackBar.SetFrequency(Value: Integer);
begin
  if FFrequency <> Value then
  begin
    FFrequency := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetBorderWidth(Value: Integer);
begin
  if FBorderWidth <> Value then
  begin
    FBorderWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetGutterWidth(Value: Integer);
begin
  if FGutterWidth <> Value then
  begin
    FGutterWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetGutterColor(Value: TColor);
begin
  if FGutterColor <> Value then
  begin
    FGutterColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetGutterBevel(Value: TVrBevel);
begin
  FGutterBevel.Assign(Value);
end;

procedure TVrTrackBar.SetTickMarks(Value: TVrTickMarks);
begin
  if FTickMarks <> Value then
  begin
    FTickMarks := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetTickColor(Value: TColor);
begin
  if FTickColor <> Value then
  begin
    FTickColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrTrackBar.SetScaleOffset(Value: Integer);
begin
  if FScaleOffset <> Value then
  begin
    FScaleOffset := Value;
    UpdateControlCanvas;
  end;
end;

function TVrTrackBar.GetThumbStates: Integer;
begin
  Result := FThumb.ThumbStates;
end;

procedure TVrTrackBar.SetThumbStates(Value: Integer);
begin
  if Value > 0 then FThumb.ThumbStates := Value;
end;

procedure TVrTrackBar.ImageChanged(Sender: TObject);
begin
  UpdateThumbGlyph;
  UpdateControlCanvas;
end;

function TVrTrackBar.GetImage(Index: Integer): TBitmap;
begin
  Result := FImages[Index];
end;

procedure TVrTrackBar.SetImage(Index: Integer; Value: TBitmap);
begin
  if (Value = nil) and (Index <> BkImage) then
    FImages[Index].LoadFromResourceName(hInstance, ThumbNames[Index])
  else FImages[Index].Assign(Value);
end;

procedure TVrTrackBar.ThumbDown(Sender: TObject; Button: TMouseButton;
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
    if (toMouseClip in Options) then
    begin
      R := Bounds(ClientOrigin.X, ClientOrigin.Y, ClientWidth, ClientHeight);
      ClipCursor(@R);
      FClipOn := True;
    end;
  end;
end;

procedure TVrTrackBar.ThumbMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
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

procedure TVrTrackBar.ThumbUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  FThumb.Down := False;
  if FClipOn then
  begin
    ClipCursor(nil);
    FClipOn := false;
  end;
end;

procedure TVrTrackBar.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  if (toActiveClick in FOptions) and (Button = mbLeft) then
  begin
    if TabStop then SetFocus;
    if FOrientation = voVertical then FHit := Y - FThumb.Height div 2
    else FHit := X - FThumb.Width div 2;
    SetThumbOffset(FHit, True);
  end;
  inherited;
end;

procedure TVrTrackBar.KeyDown(var Key: Word; Shift: TShiftState);

  function Adjust(Value: Integer): Integer;
  begin
    Result := Value;
    if Style = psTopRight then Result := -Result;
  end;

begin
  if Shift = [] then
  begin
    if Key = VK_HOME then Position := FMax
    else if Key = VK_END then Position := FMin;
    if Orientation = voHorizontal then
    begin
      if Key = VK_LEFT then Position := Position + Adjust(-Frequency)
      else if Key = VK_RIGHT then Position := Position + Adjust(Frequency);
    end
    else
    begin
      if Key = VK_UP then Position := Position + Adjust(Frequency)
      else if Key = VK_DOWN then Position := Position + Adjust(-Frequency);
    end;
  end;
  inherited KeyDown(Key, Shift);
end;



end.
