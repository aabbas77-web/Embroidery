{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrAnimate;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrControls, VrThreads;

type
  TVrAnimate = class(TVrGraphicImageControl)
  private
    FAutoSize: Boolean;
    FStretch: Boolean;
    FBitmap: TBitmap;
    FFrameCount: Integer;
    FTimer: TVrTimer;
    FLoop: Boolean;
    FActive: Boolean;
    FOrientation: TVrOrientation;
    FCurrentFrame: Integer;
    FThreaded: Boolean;
    FImageWidth: Integer;
    FImageHeight: Integer;
    FOnNotify: TNotifyEvent;
    function GetInterval: Integer;
    procedure SetInterval(Value: integer);
    procedure SetBitmap(Value: TBitmap);
    procedure SetActive(Value: Boolean);
    procedure SetAutoSize(Value: Boolean);
    procedure SetStretch(Value: Boolean);
    procedure SetFrameCount(Value: Integer);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetCurrentFrame(Value: Integer);
    procedure SetThreaded(Value: Boolean);
    procedure UpdateImage;
    procedure BitmapChanged(Sender: TObject);
    procedure TimerEvent(Sender: TObject);
  protected
    function GetPalette: HPALETTE; override;
    procedure Loaded; override;
    procedure AdjustBounds;
    procedure Paint; override;
    function DestRect: TRect;
    function GetImageRect(Index: Integer): TRect;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
    property CurrentFrame: Integer read FCurrentFrame write SetCurrentFrame;
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Interval: Integer read GetInterval write SetInterval default 150;
    property FrameCount: integer read FFrameCount write SetFrameCount default 1;
    property AutoSize: Boolean read FAutoSize write SetAutoSize default false;
    property Stretch: Boolean read FStretch write SetStretch default false;
    property Bitmap: TBitmap read FBitmap write SetBitmap;
    property Loop: Boolean read FLoop write FLoop default True;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property Active: Boolean read FActive write SetActive default false;
    property OnNotify: TNotifyEvent read FOnNotify write FOnNotify;
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
    property Hint;
    property ParentColor default false;
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


constructor TVrAnimate.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csDoubleClicks, csSetCaption];
  Width := 50;
  Height := 50;
  Color := clBtnFace;
  ParentColor := false;
  Transparent := false;
  FActive := false;
  FFrameCount := 1;
  FAutoSize := false;
  FStretch := false;
  FLoop := True;
  FOrientation := voHorizontal;
  FBitmap := TBitmap.Create;
  FBitmap.OnChange := BitmapChanged;
  FThreaded := True;
  FTimer := TVrTimer.Create(Self);
  FTimer.Enabled := false;
  FTimer.Interval := 150;
  FTimer.OnTimer := TimerEvent;
end;

destructor TVrAnimate.Destroy;
begin
  FTimer.Free;
  FBitmap.Free;
  inherited Destroy;
end;

procedure TVrAnimate.Loaded;
begin
  inherited Loaded;
  UpdateImage;
end;

procedure TVrAnimate.SetBitmap(Value: TBitMap);
begin
  FBitmap.Assign(Value);
end;

procedure TVrAnimate.BitmapChanged(Sender: TObject);
begin
  Active := false;
  UpdateImage;
  UpdateControlCanvas;
end;

function TVrAnimate.GetInterval: Integer;
begin
  Result := FTimer.Interval;
end;

procedure TVrAnimate.SetInterval(Value: Integer);
begin
  FTimer.Interval := Value;
end;

procedure TVrAnimate.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    if Value then FCurrentFrame := 0;
    if not Designing then
      FTimer.Enabled := Value;
  end;
end;

procedure TVrAnimate.SetAutoSize(Value: Boolean);
begin
  if FAutoSize <> Value then
  begin
    FAutoSize :=  Value;
    AdjustBounds;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnimate.SetStretch(Value: Boolean);
begin
  if FStretch <> Value then
  begin
    FStretch := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnimate.SetFrameCount(Value: Integer);
begin
  if (FFrameCount <> Value) and (Value > 0) then
  begin
    FFrameCount := Value;
    UpdateImage;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnimate.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    UpdateImage;
    UpdateControlCanvas;
  end;
end;

procedure TVrAnimate.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;

function TVrAnimate.GetPalette: HPALETTE;
begin
  Result := 0;
  if not Bitmap.Empty then Result := Bitmap.Palette;
end;

procedure TVrAnimate.AdjustBounds;
begin
  if (AutoSize) and (not Bitmap.Empty) then
    SetBounds(Left, Top, FImageWidth, FImageHeight);
end;

procedure TVrAnimate.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  if AutoSize then
    if not Bitmap.Empty then
    begin
      AWidth := FImageWidth;
      AHeight := FImageHeight;
    end;
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
end;

procedure TVrAnimate.UpdateImage;
begin
  FImageWidth := 1;
  FImageHeight := 1;
  FCurrentFrame := 0;
  if not Bitmap.Empty then
  begin
    if Orientation = voHorizontal then
    begin
      FImageWidth := Bitmap.Width div FrameCount;
      FImageHeight := Bitmap.Height;
    end
    else
    begin
      FImageWidth := Bitmap.Width;
      FImageHeight := Bitmap.Height div FrameCount;
    end;
  end;
  AdjustBounds;
end;

function TVrAnimate.GetImageRect(Index: Integer): TRect;
begin
  if Orientation = voHorizontal then
    Result := Bounds(Index * FImageWidth, 0, FImageWidth, FImageHeight)
  else Result := Bounds(0, Index * FImageHeight, FImageWidth, FImageHeight);
end;

function TVrAnimate.DestRect: TRect;
var
  MidX, MidY: Integer;
begin
  if Stretch then Result := ClientRect
  else
  begin
    MidX := (ClientWidth - FImageWidth) div 2;
    MidY := (ClientHeight - FImageHeight) div 2;
    Result := Bounds(MidX, MidY, FImageWidth, FImageHeight);
  end;
end;

procedure TVrAnimate.Paint;
begin
  ClearBitmapCanvas;

  if not Bitmap.Empty then
    with BitmapCanvas do
    begin
      if Transparent then Brush.Style := bsClear
      else Brush.Style := bsSolid;
      BrushCopy(DestRect, Bitmap, GetImageRect(FCurrentFrame), Self.Color);
    end;

  if Designing then
    with BitmapCanvas do
    begin
      Pen.Style := psDot;
      Brush.Style := bsClear;
      Rectangle(0, 0, Width, Height);
    end;

  inherited Paint;
end;

procedure TVrAnimate.SetCurrentFrame(Value: Integer);
begin
  if not Active then
    if (FCurrentFrame <> Value) and (Value < FrameCount - 1) then
    begin
      FCurrentFrame := Value;
      UpdateControlCanvas;
    end;
end;

procedure TVrAnimate.TimerEvent(Sender: TObject);
begin
  if not Loading then
  begin
    if FCurrentFrame < FrameCount - 1 then Inc(FCurrentFrame)
    else
    begin
      if not Loop then
      begin
        Active := false;
        if Assigned(FOnNotify) then FOnNotify(Self);
      end else FCurrentFrame := 0;
    end;
    UpdateControlCanvas;
  end;
end;


end.
