{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrUpDown;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrControls, VrSysUtils, VrThreads;

type
  TVrUpDown = class(TVrGraphicImageControl)
  private
    FGlyphsUp: TBitmap;
    FGlyphsDown: TBitmap;
    FNumGlyphs: TVrNumGlyphs;
    FSizeUp: TPoint;
    FSizeDown: TPoint;
    FOrientation: TVrOrientation;
    FRepeatClick: Boolean;
    FRepeatPause: TVrMaxInt;
    FOnUpClick: TNotifyEvent;
    FOnDownClick: TNotifyEvent;
    FFocusIndex: Integer;
    FDown: Boolean;
    FDownIndex: Integer;
    FPressed: Boolean;
    FRepeatTimer: TVrTimer;
    procedure SetGlyphsUp(Value: TBitmap);
    procedure SetGlyphsDown(Value: TBitmap);
    procedure SetNumGlyphs(Value: TVrNumGlyphs);
    procedure SetOrientation(Value: TVrOrientation);
    procedure GlyphsChanged(Sender: TObject);
    procedure TimerExpired(Sender: TObject);
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
  protected
    procedure AdjustGlyphs;
    procedure Paint; override;
    procedure DrawGlyph(GlyphIndex: Integer; Glyphs: TBitmap; Size: TPoint);
    procedure LoadBitmaps; virtual;
    procedure Clicked;
    function GetGlyphRect(Index: Integer): TRect;
    function GetGlyphIndex(X, Y: Integer): Integer;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property GlyphsUp: TBitmap read FGlyphsUp write SetGlyphsUp;
    property GlyphsDown: TBitmap read FGlyphsDown write SetGlyphsDown;
    property NumGlyphs: TVrNumGlyphs read FNumGlyphs write SetNumGlyphs default 4;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voVertical;
    property RepeatClick: Boolean read FRepeatClick write FRepeatClick default True;
    property RepeatPause: TVrMaxInt read FRepeatPause write FRepeatPause default 100;
    property OnUpClick: TNotifyEvent read FOnUpClick write FOnUpClick;
    property OnDownClick: TNotifyEvent read FOnDownClick write FOnDownClick;
    property Transparent default false;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color default clBlack;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Enabled;
    property ParentColor default false;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Visible;
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

{$R VRUPDOWN.D32}

const
  InitRepeatPause = 400;
  ResId: array[0..1] of PChar = ('UPDOWN_UP', 'UPDOWN_DOWN');


constructor TVrUpDown.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 20;
  Height := 30;
  Color := clBlack;
  ParentColor := false;
  Transparent := false;
  FFocusIndex := -1;
  FOrientation := voVertical;
  FGlyphsUp := TBitmap.Create;
  FGlyphsUp.OnChange := GlyphsChanged;
  FGlyphsDown := TBitmap.Create;
  FGlyphsDown.OnChange := GlyphsChanged;
  FNumGlyphs := 4;
  LoadBitmaps;
  FRepeatClick := True;
  FRepeatPause := 100;
  FRepeatTimer := TVrTimer.Create(nil);
  with FRepeatTimer do
  begin
    Enabled := false;
    TimerType := ttSystem;
    Interval := InitRepeatPause;
    OnTimer := TimerExpired;
  end;
end;

destructor TVrUpDown.Destroy;
begin
  FGlyphsUp.Free;
  FGlyphsDown.Free;
  FRepeatTimer.Free;
  inherited Destroy;
end;

procedure TVrUpDown.LoadBitmaps;
begin
  FGlyphsUp.LoadFromResourceName(hInstance, ResId[0]);
  FGlyphsDown.LoadFromResourceName(hInstance, ResId[1]);
end;

procedure TVrUpDown.AdjustGlyphs;
var
  GlyphWidth: Integer;
begin
  if not FGlyphsUp.Empty then
  begin
    GlyphWidth := FGlyphsUp.Width div FNumGlyphs;
    FSizeUp := Point(GlyphWidth, FGlyphsUp.Height);
  end else FSizeUp := Point(0, 0);

  if not FGlyphsDown.Empty then
  begin
    GlyphWidth := FGlyphsDown.Width div FNumGlyphs;
    FSizeDown := Point(GlyphWidth, FGlyphsDown.Height);
  end else FSizeDown := Point(0, 0);
end;

procedure TVrUpDown.GlyphsChanged(Sender: TObject);
begin
  AdjustGlyphs;
  UpdateControlCanvas;
end;

function TVrUpDown.GetGlyphIndex(X, Y: Integer): Integer;
begin
  for Result := 0 to 1 do
    if PtInRect(GetGlyphRect(Result), Point(X, Y)) then Exit;
  Result := -1;
end;

function TVrUpDown.GetGlyphRect(Index: Integer): TRect;
var
  Size: TPoint;
begin
  if Orientation = voVertical then
  begin
    Size.X := Width;
    Size.Y := Height div 2;
    Result := Bounds(0, Size.Y * Index, Size.X, Size.Y);
  end
  else
  begin
    Size.X := Width div 2;
    Size.Y := Height;
    Result := Bounds(Index * Size.X, 0, Size.X, Size.Y);
  end;
end;

procedure TVrUpDown.DrawGlyph(GlyphIndex: Integer; Glyphs: TBitmap; Size: TPoint);
var
  Center: TPoint;
  Index: Integer;
  R, ImageRect, GlyphRect: TRect;
begin
  if Glyphs.Empty then
    Exit;

  Index := 0;
  if FFocusIndex = GlyphIndex then Index := 1;
  if (FDown) and (FFocusIndex = GlyphIndex) then Index := 2;
  if not Enabled then Index := 3;
  if Index > Pred(NumGlyphs) then Index := 0;

  R := GetGlyphRect(GlyphIndex);
  Center.X := R.Left + ((WidthOf(R) - Size.X) div 2);
  Center.Y := R.Top + ((HeightOf(R) - Size.Y) div 2);
  ImageRect := Bounds(Center.X, Center.Y, Size.X, Size.Y);
  GlyphRect := Bounds(Index * Size.X, 0, Size.X, Size.Y);
  BitmapCanvas.BrushCopy(ImageRect, Glyphs, GlyphRect, Glyphs.TransparentColor);
end;

procedure TVrUpDown.Paint;
begin
  ClearBitmapCanvas;
  DrawGlyph(0, GlyphsUp, FSizeUp);
  DrawGlyph(1, GlyphsDown, FSizeDown);
  inherited Paint;
end;

procedure TVrUpDown.SetGlyphsUp(Value: TBitmap);
begin
  if Value = nil then
    FGlyphsUp.LoadFromResourceName(hInstance, ResId[0])
  else FGlyphsUp.Assign(Value);
end;

procedure TVrUpDown.SetGlyphsDown(Value: TBitmap);
begin
  if Value = nil then
    FGlyphsDown.LoadFromResourceName(hInstance, ResId[1])
  else FGlyphsDown.Assign(Value);
end;

procedure TVrUpDown.SetNumGlyphs(Value: TVrNumGlyphs);
begin
  if FNumGlyphs <> Value then
  begin
    FNumGlyphs := Value;
    AdjustGlyphs;
    UpdateControlCanvas;
  end;
end;

procedure TVrUpDown.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if not Loading then
      BoundsRect := Bounds(Left, Top, Height, Width);
    UpdateControlCanvas;
  end;
end;

procedure TVrUpDown.Clicked;
begin
  case FDownIndex of
    0: if Assigned(FOnUpClick) then FOnUpClick(Self);
    1: if Assigned(FOnDownClick) then FOnDownClick(Self);
  end;
end;

procedure TVrUpDown.MouseMove(Shift: TShiftState; X, Y: Integer);
var
  NewIndex: Integer;
begin
  inherited;
  NewIndex := GetGlyphIndex(X, Y);
  if FPressed then
    FDown := NewIndex = FDownIndex;
  if FFocusIndex <> NewIndex then
  begin
    FFocusIndex := NewIndex;
    UpdateControlCanvas;
  end;
end;

procedure TVrUpDown.MouseDown(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if (Button = mbLeft) and Enabled then
  begin
    FPressed := True;
    FDown := True;
    FDownIndex := GetGlyphIndex(X, Y);
    FRepeatTimer.Interval := InitRepeatPause;
    FRepeatTimer.Enabled := RepeatClick;
    UpdateControlCanvas;
  end;
  inherited;
end;

procedure TVrUpDown.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  DoClick: Boolean;
begin
  FRepeatTimer.Enabled := false;

  if FPressed then
  begin
    FPressed := false;
    DoClick := FDown;
    FDown := false;
    UpdateControlCanvas;
    if DoClick then Clicked;
  end;
  inherited;
end;

procedure TVrUpDown.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  FFocusIndex := -1;
  UpdateControlCanvas;
end;

procedure TVrUpDown.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrUpDown.TimerExpired(Sender: TObject);
begin
  FRepeatTimer.Interval := RepeatPause;
  if (FPressed and FDown) then
  begin
    try
      Clicked;
    except
      FRepeatTimer.Enabled := False;
      raise;
    end;
  end;
end;



end.
