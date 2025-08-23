unit G32_Image;

{*********************************************}
{  This unit is a part of Graphics32 library  }
{  Copyright © 2000 Alex Denissov             }
{  See License.txt for licence information    }
{*********************************************}

interface

{$I G32.INC}

uses
  Windows, Classes, Messages, Controls, SysUtils, StdCtrls, Forms, ExtCtrls,
  Graphics, G32, G32_Layers, G32_RangeBars;

const
  { Paint Stage Constants }
  PST_CUSTOM            = 1;   // Calls OnPaint with # of current stage in parameter
  PST_CLEAR_BUFFER      = 2;   // Clears the buffer
  PST_CLEAR_BACKGND     = 3;   // Clears a visible buffer area
  PST_DRAW_BITMAP       = 4;   // Draws a bitmap
  PST_DRAW_LAYERS       = 5;   // Draw layers (Parameter = Layer Mask)
  PST_CONTROL_FRAME     = 6;   // Draws a dotted frame around the control
  PST_BITMAP_FRAME      = 7;   // Draws a dotted frame around the scaled bitmap

type
  TPaintStageEvent = procedure(Sender: TObject; StageNum: Cardinal) of object;

  { TPaintStage }
  PPaintStage = ^TPaintStage;
  TPaintStage = record
    DsgnTime: Boolean;
    RunTime: Boolean;
    Stage: Cardinal;             // a PST_* constant
    Parameter: Cardinal;         // an optional parameter
  end;

  { TPaintStages }

  TPaintStages = class
  private
    FItems: array of TPaintStage;
    function GetItem(Index: Integer): PPaintStage;
  public
    destructor Destroy; override;
    function  Add: PPaintStage;
    procedure Clear;
    function  Count: Integer;
    procedure Delete(Index: Integer);
    function  Insert(Index: Integer): PPaintStage;
    property Items[Index: Integer]: PPaintStage read GetItem; default;
  end;

  { Alignment of the bitmap in TCustomImage32 }
  TBitmapAlign = (baTopLeft, baCenter, baTile, baCustom);
  TScaleMode = (smNormal, smStretch, smScale, smResize);

  { TCustomPaintBox32 }
  TCustomPaintBox32 = class(TCustomControl)
  private
    FBuffer: TBitmap32;
    FBufferOversize: Integer;
    FBufferValid: Boolean;
    procedure SetBufferOversize(Value: Integer);
    procedure WMEraseBkgnd(var Msg: TWmEraseBkgnd); message WM_ERASEBKGND;
  protected
    procedure DoPaintBuffer; virtual;
    procedure Paint; override;
    procedure ResizeBuffer;
    property  BufferOversize: Integer read FBufferOversize write SetBufferOversize;
    property  BufferValid: Boolean read FBufferValid write FBufferValid;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function  GetViewportRect: TRect; virtual;
    procedure Invalidate; override;
    procedure Loaded; override;
    procedure Resize; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
    property Buffer: TBitmap32 read FBuffer;
  end;

  { TPaintBox32 }
  TPaintBox32 = class(TCustomPaintBox32)
  private
    FOnPaintBuffer: TNotifyEvent;
  protected
    procedure DoPaintBuffer; override;
  published
    property Align;
    property Anchors;
    property AutoSize;
    property Constraints;
    property Cursor;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Visible;
    property OnClick;
{$IFDEF DELPHI5}
    property OnContextPopup;
{$ENDIF}
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnResize;
  end;

  { TCustomImage32 }
  TCustomImage32 = class(TCustomPaintBox32)
  private
    FBitmap: TBitmap32;
    FBitmapAlign: TBitmapAlign;
    FLayers: TLayerCollection;
    FOffsetHorz: Single;
    FOffsetVert: Single;
    FPaintStages: TPaintStages;
    FScale: Single;
    FScaleMode: TScaleMode;
    FUpdateCount: Integer;
    FOnBitmapResize: TNotifyEvent;
    FOnChanging: TNotifyEvent;
    FOnChange: TNotifyEvent;
    FOnGDIOverlay: TNotifyEvent;
    FOnInitStages: TNotifyEvent;
    FOnPaintStage: TPaintStageEvent;
    procedure ResizedHandler(Sender: TObject);
    procedure ChangingHandler(Sender: TObject);
    procedure ChangedHandler(Sender: TObject);
    function  GetOnPixelCombine: TPixelCombineEvent;
    procedure GDIUpdateHandler(Sender: TObject);
    procedure SetBitmap(Value: TBitmap32);
    procedure SetBitmapAlign(Value: TBitmapAlign);
    procedure SetLayers(Value: TLayerCollection);
    procedure SetOffsetHorz(Value: Single);
    procedure SetOffsetVert(Value: Single);
    procedure SetScale(Value: Single);
    procedure SetScaleMode(Value: TScaleMode);
    procedure SetOnPixelCombine(Value: TPixelCombineEvent);
  protected
    CachedBitmapRect: TRect;
    CacheValid: Boolean;
    OldSzX, OldSzY: Integer;
    procedure AdjustLayerLocation(Sender: TObject; var Location: TFloatRect);
    procedure BitmapResized; virtual;
    function  CanAutoSize(var NewWidth, NewHeight: Integer): Boolean; override;
    procedure DoInitStages; virtual;
    procedure DoPaintBuffer; override;
    procedure DoPaintGDIOverlay; virtual;
    procedure DoScaleChange; virtual;
    procedure InvalidateCache;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure Paint; override;
    procedure UpdateCache;
    property  UpdateCount: Integer read FUpdateCount;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure AfterConstruction; override;
    procedure BeginUpdate; virtual;
    function  BitmapToControl(const APoint: TPoint): TPoint;
    procedure Changing; virtual;
    procedure Changed; virtual;
    function  ControlToBitmap(const APoint: TPoint): TPoint;
    procedure EndUpdate; virtual;
    procedure ExecBitmapFrame(StageNum: Integer); virtual;   // PST_BITMAP_FRAME
    procedure ExecClearBuffer(StageNum: Integer); virtual;   // PST_CLEAR_BUFFER
    procedure ExecClearBackgnd(StageNum: Integer); virtual;  // PST_CLEAR_BACKGND
    procedure ExecControlFrame(StageNum: Integer); virtual;  // PST_CONTROL_FRAME
    procedure ExecCustom(StageNum: Integer); virtual;        // PST_CUSTOM
    procedure ExecDrawBitmap(StageNum: Integer); virtual;    // PST_DRAW_BITMAP
    procedure ExecDrawLayers(StageNum: Integer); virtual;    // PST_DRAW_LAYERS
    function  GetBitmapRect: TRect; virtual;
    function  GetBitmapSize: TSize; virtual;
    procedure Invalidate; override;
    procedure Resize; override;
    procedure SetupBitmap(DoClear: Boolean = False; ClearColor: TColor32 = $FF000000);
    property Bitmap: TBitmap32 read FBitmap write SetBitmap;
    property BitmapAlign: TBitmapAlign read FBitmapAlign write SetBitmapAlign;
    property Layers: TLayerCollection read FLayers write SetLayers;
    property OffsetHorz: Single read FOffsetHorz write SetOffsetHorz;
    property OffsetVert: Single read FOffsetVert write SetOffsetVert;
    property PaintStages: TPaintStages read FPaintStages;
    property Scale: Single read FScale write SetScale;
    property ScaleMode: TScaleMode read FScaleMode write SetScaleMode;
    property OnBitmapResize: TNotifyEvent read FOnBitmapResize write FOnBitmapResize;
    property OnBitmapPixelCombine: TPixelCombineEvent read GetOnPixelCombine write SetOnPixelCombine;
    property OnInitStages: TNotifyEvent read FOnInitStages write FOnInitStages;
    property OnGDIOverlay: TNotifyEvent read FOnGDIOverlay write FOnGDIOverlay;
    property OnChanging: TNotifyEvent read FOnChanging write FOnChanging;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property OnPaintStage: TPaintStageEvent read FOnPaintStage write FOnPaintStage;
  end;

  TImage32 = class(TCustomImage32)
  published
    property Align;
    property Anchors;
    property AutoSize;
    property Bitmap;
    property BitmapAlign;
    property Color;
    property Constraints;
    property Cursor;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property Scale;
    property ScaleMode;
    property ShowHint;
    property Visible;
    property OnBitmapResize;
    property OnClick;
    property OnChange;
    property OnChanging;
{$IFDEF DELPHI5}
    property OnContextPopup;
{$ENDIF}
    property OnDblClick;
    property OnGDIOverlay;
    property OnDragDrop;
    property OnDragOver;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnPaintStage;
    property OnResize;
  end;

  TCustomImgView32 = class;

  { TIVScrollProperties }
  TIVScrollProperties = class(TPersistent)
  private
    function GetBackgnd: TRBBackgnd;
    function GetBorderStyle: TBorderStyle;
    function GetButtonSize: Integer;
    function GetColor: TColor;
    function GetFramed: Boolean;
    function GetHandleColor: TColor;
    function GetIncrement: Integer;
    function GetShowArrows: Boolean;
    function GetShowHandleGrip: Boolean;
    function GetSize: Integer;
    procedure SetBackgnd(Value: TRBBackgnd);
    procedure SetBorderStyle(Value: TBorderStyle);
    procedure SetButtonSize(Value: Integer);
    procedure SetColor(Value: TColor);
    procedure SetFramed(Value: Boolean);
    procedure SetHandleColor(Value: TColor);
    procedure SetIncrement(Value: Integer);
    procedure SetShowArrows(Value: Boolean);
    procedure SetShowHandleGrip(Value: Boolean);
    procedure SetSize(Value: Integer);
  protected
    ImgView: TCustomImgView32;
  published
    property Backgnd: TRBBackgnd read GetBackgnd write SetBackgnd default bgPattern;
    property BorderStyle: TBorderStyle read GetBorderStyle write SetBorderStyle default bsNone;
    property ButtonSize: Integer read GetButtonSize write SetButtonSize default 0;
    property Framed: Boolean read GetFramed write SetFramed default True;
    property HandleColor: TColor read GetHandleColor write SetHandleColor default clBtnShadow;
    property Increment: Integer read GetIncrement write SetIncrement default 8;
    property Color: TColor read GetColor write SetColor default clBtnShadow;
    property Size: Integer read GetSize write SetSize default 0;
    property ShowArrows: Boolean read GetShowArrows write SetShowArrows default True;
    property ShowHandleGrip: Boolean read GetShowHandleGrip write SetShowHandleGrip;
  end;

  { TCustomImgView32 }
  TCustomImgView32 = class(TCustomImage32)
  private
    FCentered: Boolean;
    FScrollBarSize: Integer;
    FOnScroll: TNotifyEvent;
    FScrollBars: TIVScrollProperties;
    procedure SetCentered(Value: Boolean);
    procedure SetScrollBars(Value: TIVScrollProperties);
  protected
    DisableScrollUpdate: Boolean;
    HScroll: TCustomRangeBar;
    VScroll: TCustomRangeBar;
    procedure AlignAll;
    procedure BitmapResized; override;
    procedure DoScaleChange; override;
    function  GetScrollBarSize: Integer;
    procedure RangeSizeHandler(Sender: TObject; var Size: Integer);
    procedure ScrollHandler(Sender: TObject); virtual;
    procedure ScrollToCenter(X, Y: Integer);
    procedure UpdateImage;
    procedure UpdateScrollBars;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function  GetViewportRect: TRect; override;
    procedure Loaded; override;
    procedure Paint; override;
    procedure Resize; override;
    property Centered: Boolean read FCentered write SetCentered default True;
    property ScrollBars: TIVScrollProperties read FScrollBars write SetScrollBars;
    property OnScroll: TNotifyEvent read FOnScroll write FOnScroll;
  end;

  TImgView32 = class(TCustomImgView32)
    property Align;
    property Anchors;
    property AutoSize;
    property Bitmap;
    property Centered;
    property Color;
    property Constraints;
    property Cursor;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property Scale;
    property ScrollBars;
    property ShowHint;
    property Visible;
    property OnBitmapResize;
    property OnClick;
    property OnChange;
    property OnChanging;
{$IFDEF DELPHI5}
    property OnContextPopup;
{$ENDIF}
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnGDIOverlay;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnPaintStage;
    property OnResize;
  end;

  { TBitmap32Item }
  { A bitmap container designed to be inserted into TBitmap32Collection }
  TBitmap32Item = class(TCollectionItem)
  private
    FBitmap: TBitmap32;
    procedure SetBitmap(ABitmap: TBitmap32);
  public
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
  published
    property Bitmap: TBitmap32 read FBitmap write SetBitmap;
  end;

  TBitmap32ItemClass = class of TBitmap32Item;

  { TBitmap32Collection }
  { A collection of TBitmap32Item objects }
  TBitmap32Collection = class(TCollection)
  private
    FOwner: TPersistent;
    function  GetItem(Index: Integer): TBitmap32Item;
    procedure SetItem(Index: Integer; Value: TBitmap32Item);
  protected
    function  GetOwner: TPersistent; override;
  public
    constructor Create(AOwner: TPersistent; ItemClass: TBitmap32ItemClass);
    function Add: TBitmap32Item;
    property Items[Index: Integer]: TBitmap32Item read GetItem write SetItem; default;
  end;

  { TBitmap32List }
  { A component that stores TBitmap32Collection }
  TBitmap32List = class(TComponent)
  private
    FBitmap32Collection: TBitmap32Collection;
    procedure SetBitmap(Index: Integer; Value: TBitmap32);
    function GetBitmap(Index: Integer): TBitmap32;
    procedure SetBitmap32Collection(Value: TBitmap32Collection);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Bitmap[Index: Integer]: TBitmap32 read GetBitmap write SetBitmap; default;
  published
    property Bitmaps: TBitmap32Collection read FBitmap32Collection write SetBitmap32Collection;
  end;

implementation

uses Math, TypInfo;

type
  TLayerAccess = class(TCustomLayer);
  TLayerCollectionAccess = class(TLayerCollection);





{ TPaintStages }

function TPaintStages.Add: PPaintStage;
var
  L: Integer;
begin
  L := Length(FItems);
  SetLength(FItems, L + 1);
  Result := @FItems[L];
  with Result^ do
  begin
    DsgnTime := False;
    RunTime := True;
    Stage := 0;
    Parameter := 0;
  end;
end;

procedure TPaintStages.Clear;
begin
  FItems := nil;
end;

function TPaintStages.Count: Integer;
begin
  Result := Length(FItems);
end;

procedure TPaintStages.Delete(Index: Integer);
var
  Count: Integer;
begin
  if (Index < 0) or (Index > High(FItems)) then
    raise EListError.Create('Invalid stage index');
  Count := Length(FItems) - Index - 1;
  if Count > 0 then
    Move(FItems[Index + 1], FItems[Index], Count * SizeOf(TPaintStage));
  SetLength(FItems, High(FItems));
end;

destructor TPaintStages.Destroy;
begin
  Clear;
  inherited;
end;

function TPaintStages.GetItem(Index: Integer): PPaintStage;
begin
  Result := @FItems[Index];
end;

function TPaintStages.Insert(Index: Integer): PPaintStage;
var
  Count: Integer;
begin
  if Index < 0 then Index := 0
  else if Index > Length(FItems) then Index := Length(FItems);
  Count := Length(FItems) - Index;
  SetLength(FItems, Length(FItems) + 1);
  if Count > 0 then
    Move(FItems[Index], FItems[Index + 1], Count * SizeOf(TPaintStage));
  Result := @FItems[Index];
  with Result^ do
  begin
    DsgnTime := False;
    RunTime := True;
    Stage := 0;
    Parameter := 0;
  end;
end;





{ TCustomPaintBox32 }

constructor TCustomPaintBox32.Create(AOwner: TComponent);
begin
  inherited;
  FBuffer := TBitmap32.Create;
  FBuffer.BeginUpdate; // just to speed the things up a little
  FBufferOversize := 40;
  Height := 192;
  Width := 192;
end;

destructor TCustomPaintBox32.Destroy;
begin
  FBuffer.Free;
  inherited;
end;

procedure TCustomPaintBox32.DoPaintBuffer;
begin
  // do nothing by default, descendants should override this method
  // for painting operations, not the Paint method!!!
  FBufferValid := True;
end;

function TCustomPaintBox32.GetViewportRect: TRect;
begin
  // returns position of the buffered area within the control bounds
  with Result do
  begin
    // by default, the whole control is buffered
    Left := 0;
    Top := 0;
    Right := Width;
    Bottom := Height;
  end;
end;

procedure TCustomPaintBox32.Invalidate;
begin
  FBufferValid := False;
  inherited;
end;

procedure TCustomPaintBox32.Loaded;
begin
  FBufferValid := False;
  inherited;
end;

procedure TCustomPaintBox32.Paint;
begin
  ResizeBuffer;
  if not FBufferValid then DoPaintBuffer;
  FBuffer.Lock;
  try
    with GetViewportRect do
      BitBlt(Canvas.Handle, Left, Top, Right, Bottom, FBuffer.Handle, 0, 0, SRCCOPY);
  finally
    FBuffer.Unlock;
  end;
end;

procedure TCustomPaintBox32.Resize;
begin
  ResizeBuffer;
  BufferValid := False;
  inherited;
end;

procedure TCustomPaintBox32.ResizeBuffer;
var
  VPWidth, VPHeight: Integer;
  NewWidth, NewHeight: Integer;
begin
  // get the viewport parameters
  with GetViewportRect do
  begin
    VPWidth := Right - Left;
    VPHeight := Bottom - Top;
  end;
  if VPWidth < 0 then VPWidth := 0;
  if VPHeight < 0 then VPHeight := 0;
  if (FBuffer.Width = VPWidth) and (FBuffer.Height = VPHeight) then Exit
  else if not FBufferOversize = 0 then
  begin
    FBuffer.SetSize(VPWidth, VPHeight);
    FBufferValid := False;
  end
  else // 'smart' resize mode
  begin
    // calculate new buffer dimensions
    NewWidth := FBuffer.Width;
    NewHeight := FBuffer.Height;
    if VPWidth > FBuffer.Width then NewWidth := VPWidth + FBufferOversize;
    if VPHeight > FBuffer.Height then NewHeight := VPHeight + FBufferOversize;
    if VPWidth < FBuffer.Width - FBufferOversize then NewWidth := VPWidth;
    if VPHeight < FBuffer.Height - FBufferOversize then NewHeight := VPHeight;
    if (NewWidth <> FBuffer.Width) or (NewHeight <> FBuffer.Height) then
    begin
      FBuffer.SetSize(NewWidth, NewHeight);
      FBufferValid := False;
    end;
  end;
end;

procedure TCustomPaintBox32.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  FBufferValid := False;
  inherited;
end;

procedure TCustomPaintBox32.SetBufferOversize(Value: Integer);
begin
  if Value < 0 then Value := 0;
  FBufferOversize := Value;
  ResizeBuffer;
end;

procedure TCustomPaintBox32.WMEraseBkgnd(var Msg: TWmEraseBkgnd);
begin
  Msg.Result := 1;
end;




{ TPaintBox32 }

procedure TPaintBox32.DoPaintBuffer;
begin
  if Assigned(FOnPaintBuffer) then FOnPaintBuffer(Self);
end;    





{ TCustomImage32 }

procedure TCustomImage32.AdjustLayerLocation(Sender: TObject; var Location: TFloatRect);

  procedure AdjustPoint(var APoint: TFloatPoint);
  begin
    with CachedBitmapRect do
    begin
      APoint.X := APoint.X * (Right - Left) / Bitmap.Width + Left;
      APoint.Y := APoint.Y * (Bottom - Top) / Bitmap.Height + Top;
    end
  end;

begin
  // this function is called by the layer collection to scale and reposition
  // positioned layers, which have the Scaled property set to True
  UpdateCache;
  if not IsRectEmpty(CachedBitmapRect) then
  begin
    AdjustPoint(Location.TopLeft);
    AdjustPoint(Location.BottomRight);
  end
  else
    with Location do
    begin
      Left := 0;
      Top := 0;
      Right := 0;
      Bottom := 0;
    end;
end;

procedure TCustomImage32.AfterConstruction;
begin
  inherited;
  DoInitStages;
end;

procedure TCustomImage32.BeginUpdate;
begin
  // disable OnChange & OnChanging generation
  Inc(FUpdateCount);
end;

procedure TCustomImage32.BitmapResized;
var
  W, H: Integer;
begin
  if AutoSize then
  begin
    W := Bitmap.Width;
    H := Bitmap.Height;
    if ScaleMode = smScale then
    begin
      W := Round(W * Scale);
      H := Round(H * Scale);
    end;
    if AutoSize and (W > 0) and (H > 0) then SetBounds(Left, Top, W, H);
  end;
  if (FUpdateCount <> 0) and Assigned(FOnBitmapResize) then FOnBitmapResize(Self);
  InvalidateCache;
  Invalidate;
end;

function TCustomImage32.BitmapToControl(const APoint: TPoint): TPoint;
begin
  // convert coordinates from bitmap's ref. frame to control's ref. frame
  UpdateCache;
  if (Bitmap.Width > 0) and (Bitmap.Height > 0) then
    with CachedBitmapRect do
    begin
      Result.X := APoint.X * (Right - Left) div Bitmap.Width + Left;
      Result.Y := APoint.Y * (Bottom - Top) div Bitmap.Height + Top;
    end
  else Result := Point(0, 0);
end;

function TCustomImage32.CanAutoSize(var NewWidth, NewHeight: Integer): Boolean;
var
  W, H: Integer;
begin
  InvalidateCache;
  Result := True;
  W := Bitmap.Width;
  H := Bitmap.Height;
  if ScaleMode = smScale then
  begin
    W := Round(W * Scale);
    H := Round(H * Scale);
  end;
  if not (csDesigning in ComponentState) or (W > 0) and (H > 0) then
  begin
    if Align in [alNone, alLeft, alRight] then NewWidth := W;
    if Align in [alNone, alTop, alBottom] then NewHeight := H;
  end;
end;

procedure TCustomImage32.Changed;
begin
  if FUpdateCount = 0 then
  begin
    Invalidate;
    if Assigned(FOnChange) then FOnChange(Self);
  end;
end;

procedure TCustomImage32.ChangedHandler(Sender: TObject);
begin
  Changed;
end;

procedure TCustomImage32.Changing;
begin
  if (FUpdateCount = 0) and Assigned(FOnChanging) then FOnChanging(Self);
end;

procedure TCustomImage32.ChangingHandler(Sender: TObject);
begin
  Changing;
end;

function TCustomImage32.ControlToBitmap(const APoint: TPoint): TPoint;
begin
  // convert point coords from control's ref. frame to bitmap's ref. frame
  // the coordinates are not clipped to bitmap image boundary
  Result := Point(-1, -1);
  if (Bitmap = nil) or (Bitmap.Empty) then Exit;
  UpdateCache;
  with CachedBitmapRect do
    if (Right > Left + 1) and (Bottom > Top + 1) then
    begin
      Result.X := ((APoint.X - Left) * (Bitmap.Width) div (Right - Left));
      Result.Y := ((APoint.Y - Top) * (Bitmap.Height) div (Bottom - Top));
    end;
end;

constructor TCustomImage32.Create(AOwner: TComponent);
begin
  inherited;
  { TODO : Check if csOpaque is required here }
  ControlStyle := [csAcceptsControls, csCaptureMouse, csClickEvents,
    csDoubleClicks, csReplicatable, csOpaque];
  FBitmap := TBitmap32.Create;
  FBitmap.OnChanging := ChangingHandler;
  FBitmap.OnChange := ChangedHandler;
  FBitmap.OnResize := ResizedHandler;
  FLayers := TLayerCollection.Create(Self);
  with TLayerCollectionAccess(FLayers) do
  begin
    OnChanging := ChangingHandler;
    OnChange := ChangedHandler;
    OnGDIUpdate := GDIUpdateHandler;
    OnLocateLayer := AdjustLayerLocation;
  end;
  FPaintStages := TPaintStages.Create;
  FScale := 1.0;
end;

destructor TCustomImage32.Destroy;
begin
  BeginUpdate;
  FPaintStages.Free;
  FLayers.Free;
  FBitmap.Free;
  inherited;
end;

procedure TCustomImage32.DoInitStages;
begin
  // background
  with PaintStages.Add^ do
  begin
    DsgnTime := True;
    RunTime := True;
    Stage := PST_CLEAR_BACKGND;
  end;

  // control frame
  with PaintStages.Add^ do
  begin
    DsgnTime := True;
    RunTime := False;
    Stage := PST_CONTROL_FRAME;
  end;


  // bitmap
  with PaintStages.Add^ do
  begin
    DsgnTime := True;
    RunTime := True;
    Stage := PST_DRAW_BITMAP;
  end;

  // bitmap frame
  with PaintStages.Add^ do
  begin
    DsgnTime := True;
    RunTime := False;
    Stage := PST_BITMAP_FRAME;
  end;

  // layers
  with PaintStages.Add^ do
  begin
    DsgnTime := True;
    RunTime := True;
    Stage := PST_DRAW_LAYERS;
    Parameter := $80000000;
  end;

  if Assigned(FOnInitStages) then FOnInitStages(Self);
end;

procedure TCustomImage32.DoPaintBuffer;
var
  I: Integer;
  DT, RT: Boolean;
begin
  UpdateCache;
  DT := csDesigning in ComponentState;
  RT := not DT;

  for I := 0 to FPaintStages.Count - 1 do
    with FPaintStages[I]^ do
      if (DsgnTime and DT) or (RunTime and RT) then
        case Stage of
          PST_CUSTOM: ExecCustom(I);
          PST_CLEAR_BUFFER: ExecClearBuffer(I);
          PST_CLEAR_BACKGND: ExecClearBackgnd(I);
          PST_DRAW_BITMAP: ExecDrawBitmap(I);
          PST_DRAW_LAYERS: ExecDrawLayers(I);
          PST_CONTROL_FRAME: ExecControlFrame(I);
          PST_BITMAP_FRAME: ExecBitmapFrame(I);
        end;
  inherited;
end;

procedure TCustomImage32.DoPaintGDIOverlay;
var
  I: Integer;
begin
  for I := 0 to Layers.Count - 1 do
    if (Layers[I].LayerOptions and $40000000) <> 0 then
      TLayerAccess(Layers[I]).PaintGDI(Canvas);
  if Assigned(FOnGDIOverlay) then FOnGDIOverlay(Self);
end;

procedure TCustomImage32.DoScaleChange;
begin
  // do nothing here
end;

procedure TCustomImage32.EndUpdate;
begin
  // re-enable OnChange & OnChanging generation
  Dec(FUpdateCount);
  Assert(FUpdateCount >= 0, 'Unpaired EndUpdate call');
end;

procedure TCustomImage32.ExecBitmapFrame(StageNum: Integer);
begin
  DrawFocusRect(FBuffer.Handle, CachedBitmapRect);
end;

procedure TCustomImage32.ExecClearBackgnd(StageNum: Integer);
var
  C: TColor32;
begin
  C := Color32(Color);
  if (Bitmap.Empty) or (Bitmap.DrawMode <> dmOpaque) then FBuffer.Clear(C)
  else
    with CachedBitmapRect do
    begin
      if (Left > 0) or (Right < Width) or (Top > 0) or (Bottom < Height) and
        not (BitmapAlign = baTile) then
      begin
        // clean only the part of the buffer lying around image edges
        Buffer.FillRectS(0, 0, Width - 1, Top - 1, C);          // top
        Buffer.FillRectS(0, Bottom, Width - 1, Height - 1, C);  // bottom
        Buffer.FillRectS(0, Top, Left - 1, Bottom - 1, C);      // left
        Buffer.FillRectS(Right, Top, Width - 1, Bottom - 1, C); // right
      end;
    end;
end;

procedure TCustomImage32.ExecClearBuffer(StageNum: Integer);
begin
  FBuffer.Clear(Color32(Color));
end;

procedure TCustomImage32.ExecControlFrame(StageNum: Integer);
begin
  DrawFocusRect(FBuffer.Handle, Rect(0, 0, Width, Height));
end;

procedure TCustomImage32.ExecCustom(StageNum: Integer);
begin
  if Assigned(FOnPaintStage) then FOnPaintStage(Self, StageNum);
end;

procedure TCustomImage32.ExecDrawBitmap(StageNum: Integer);
var
  I, J, Tx, Ty: Integer;
  R: TRect;
begin
  if Bitmap.Empty or IsRectEmpty(CachedBitmapRect) then Exit;
  Bitmap.Lock;
  try
    if BitmapAlign <> baTile then Bitmap.DrawTo(Buffer, CachedBitmapRect)
    else with CachedBitmapRect do
    begin
      Tx := Width div Right;
      Ty := Height div Bottom;
      for J := 0 to Ty do
        for I := 0 to Tx do
        begin
          R := CachedBitmapRect;
          OffsetRect(R, Right * I, Bottom * J);
          Bitmap.DrawTo(Buffer, R);
        end;
    end;
  finally
    Bitmap.Unlock;
  end;
end;

procedure TCustomImage32.ExecDrawLayers(StageNum: Integer);
var
  I: Integer;
  Mask: Cardinal;
begin
  Mask := PaintStages[StageNum]^.Parameter;
  for I := 0 to Layers.Count - 1 do
    if (Layers.Items[I].LayerOptions and Mask) <> 0 then
      TLayerAccess(Layers.Items[I]).DoPaint(Buffer);
end;

procedure TCustomImage32.GDIUpdateHandler(Sender: TObject);
begin
  Paint;
end;

function TCustomImage32.GetBitmapRect: TRect;
var
  Size: TSize;
begin
  if Bitmap.Empty then
    with Result do
    begin
      Left := 0;
      Right := 0;
      Top := 0;
      Bottom := 0;
    end
  else
  begin
    Size := GetBitmapSize;
    with Size do
    begin
      Result := Rect(0, 0, Cx, Cy);
      if BitmapAlign = baCenter then
        OffsetRect(Result, (Width - Cx) div 2, (Height - Cy) div 2)
      else if BitmapAlign = baCustom then
        OffsetRect(Result, Round(OffsetHorz), Round(OffsetVert));
    end;
  end;
end;

function TCustomImage32.GetBitmapSize: TSize;
var
  ScaleX, ScaleY: Single;
begin
  with Result do
  begin
    if Bitmap.Empty or (Width = 0) or (Height = 0) then
    begin
      Cx := 0;
      Cy := 0;
      Exit;
    end;

    case ScaleMode of
      smNormal:
        begin
          Cx := Bitmap.Width;
          Cy := Bitmap.Height;
        end;

      smStretch:
        begin
          Cx := Width;
          Cy := Height;
        end;

      smResize:
        begin
          Cx := Bitmap.Width;
          Cy := Bitmap.Height;
          ScaleX := Width / Cx;
          ScaleY := Height / Cy;
          if ScaleX >= ScaleY then
          begin
            Cx := Round(Cx * ScaleY);
            Cy := Height;
          end
          else
          begin
            Cx := Width;
            Cy := Round(Cy * ScaleX);
          end;
        end;
    else // smScale
      begin
        Cx := Round(Bitmap.Width * Scale);
        Cy := Round(Bitmap.Height * Scale);
      end;
    end;
  end;
end;

function TCustomImage32.GetOnPixelCombine: TPixelCombineEvent;
begin
  Result := FBitmap.OnPixelCombine;
end;

procedure TCustomImage32.Invalidate;
begin
  BufferValid := False;
  CacheValid := False;
  inherited;
end;

procedure TCustomImage32.InvalidateCache;
begin
  CacheValid := False;
end;

procedure TCustomImage32.MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  MouseCapture := True;
  if Layers.MouseEvents then
  begin
    if not TLayerCollectionAccess(Layers).MouseDown(Button, Shift, X, Y) then inherited;
  end
  else
    inherited;
end;

procedure TCustomImage32.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited;
  if Layers.MouseEvents then
  begin
    if not TLayerCollectionAccess(Layers).MouseMove(Shift, X, Y) then inherited;
  end
  else
    inherited;
end;

procedure TCustomImage32.MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if Layers.MouseEvents then
  begin
    if not TLayerCollectionAccess(Layers).MouseUp(Button, Shift, X, Y) then inherited;
  end
  else
    inherited;
  ReleaseCapture;
end;

procedure TCustomImage32.Paint;
begin
  inherited;
  DoPaintGDIOverlay;
end;

procedure TCustomImage32.Resize;
begin
  InvalidateCache;
  inherited;
end;

procedure TCustomImage32.ResizedHandler(Sender: TObject);
begin
  BitmapResized;
end;

procedure TCustomImage32.SetBitmap(Value: TBitmap32);
begin
  InvalidateCache;
  FBitmap.Assign(Value);
end;

procedure TCustomImage32.SetBitmapAlign(Value: TBitmapAlign);
begin
  Changing;
  InvalidateCache;
  FBitmapAlign := Value;
  Changed;
end;

procedure TCustomImage32.SetLayers(Value: TLayerCollection);
begin
  FLayers.Assign(Value);
end;

procedure TCustomImage32.SetOffsetHorz(Value: Single);
begin
  Changing;
  InvalidateCache;
  FOffsetHorz := Value;
  Changed;
end;

procedure TCustomImage32.SetOffsetVert(Value: Single);
begin
  Changing;
  FOffsetVert := Value;
  InvalidateCache;
  Changed;
end;

procedure TCustomImage32.SetOnPixelCombine(Value: TPixelCombineEvent);
begin
  Changing;
  FBitmap.OnPixelCombine := Value;
  Changed;
end;

procedure TCustomImage32.SetScale(Value: Single);
begin
  if Value < 0.001 then Value := 0.001;
  if Value <> FScale then
  begin
    Changing;
    InvalidateCache;
    FScale := Value;
    DoScaleChange;
    Changed;
  end;
end;

procedure TCustomImage32.SetScaleMode(Value: TScaleMode);
begin
  if Value <> FScaleMode then
  begin
    Changing;
    InvalidateCache;
    FScaleMode := Value;
    Changed;
  end;
end;

procedure TCustomImage32.SetupBitmap(DoClear: Boolean = False; ClearColor: TColor32 = $FF000000);
begin
  Changing;
  FBitmap.BeginUpdate;
  FBitmap.SetSize(Width, Height);
  if DoClear then FBitmap.Clear(ClearColor);
  FBitmap.EndUpdate;
  InvalidateCache;
  Changed;
end;

procedure TCustomImage32.UpdateCache;
begin
  if CacheValid then Exit;
  CachedBitmapRect := GetBitmapRect;
  CacheValid := True;
end;




{ TIVScrollProperties }

function TIVScrollProperties.GetBackgnd: TRBBackgnd;
begin
  Result := ImgView.HScroll.Backgnd;
end;

function TIVScrollProperties.GetBorderStyle: TBorderStyle;
begin
  Result := ImgView.HScroll.BorderStyle;
end;

function TIVScrollProperties.GetButtonSize: Integer;
begin
  Result := ImgView.HScroll.ButtonSize;
end;

function TIVScrollProperties.GetColor: TColor;
begin
  Result := ImgView.HScroll.Color;
end;

function TIVScrollProperties.GetFramed: Boolean;
begin
  Result := ImgView.HScroll.Framed;
end;

function TIVScrollProperties.GetHandleColor: TColor;
begin
  Result := ImgView.HScroll.HandleColor;
end;

function TIVScrollProperties.GetIncrement: Integer;
begin
  Result := ImgView.HScroll.Increment;
end;

function TIVScrollProperties.GetShowArrows: Boolean;
begin
  Result := ImgView.HScroll.ShowArrows;
end;

function TIVScrollProperties.GetShowHandleGrip: Boolean;
begin
  Result := ImgView.HScroll.ShowHandleGrip;
end;

function TIVScrollProperties.GetSize: Integer;
begin
  Result := ImgView.FScrollBarSize;
end;

procedure TIVScrollProperties.SetBackgnd(Value: TRBBackgnd);
begin
  ImgView.HScroll.Backgnd := Value;
  ImgView.VScroll.Backgnd := Value;
end;

procedure TIVScrollProperties.SetBorderStyle(Value: TBorderStyle);
begin
  ImgView.HScroll.BorderStyle := Value;
  ImgView.VScroll.BorderStyle := Value;
end;

procedure TIVScrollProperties.SetButtonSize(Value: Integer);
begin
  ImgView.HScroll.ButtonSize := Value;
  ImgView.VScroll.ButtonSize := Value;
end;

procedure TIVScrollProperties.SetColor(Value: TColor);
begin
  ImgView.HScroll.Color := Value;
  ImgView.VScroll.Color := Value;
end;

procedure TIVScrollProperties.SetFramed(Value: Boolean);
begin
  ImgView.HScroll.Framed := Value;
  ImgView.VScroll.Framed := Value;
end;

procedure TIVScrollProperties.SetHandleColor(Value: TColor);
begin
  ImgView.HScroll.HandleColor := Value;
  ImgView.VScroll.HandleColor := Value;
end;

procedure TIVScrollProperties.SetIncrement(Value: Integer);
begin
  ImgView.HScroll.Increment := Value;
  ImgView.VScroll.Increment := Value;
end;

procedure TIVScrollProperties.SetShowArrows(Value: Boolean);
begin
  ImgView.HScroll.ShowArrows := Value;
  ImgView.VScroll.ShowArrows := Value;
end;

procedure TIVScrollProperties.SetShowHandleGrip(Value: Boolean);
begin
  ImgView.HScroll.ShowHandleGrip := Value;
  ImgView.VScroll.ShowHandleGrip := Value;
end;

procedure TIVScrollProperties.SetSize(Value: Integer);
begin
  ImgView.FScrollBarSize := Value;
  ImgView.AlignAll;
end;




{ TCustomImgView32 }

procedure TCustomImgView32.AlignAll;
begin
  with GetViewportRect do
  begin
    HScroll.BoundsRect := Rect(Left, Bottom, Right, Height);
    VScroll.BoundsRect := Rect(Right, Top, Width, Bottom);
  end;
end;

procedure TCustomImgView32.BitmapResized;
begin
  inherited;
  UpdateScrollBars;
  if Centered then ScrollToCenter(Bitmap.Width div 2, Bitmap.Height div 2)
  else
  begin
    HScroll.Position := 0;
    VScroll.Position := 0;
    UpdateImage;
  end;
end;

constructor TCustomImgView32.Create(AOwner: TComponent);
begin
  inherited;

  HScroll := TCustomRangeBar.Create(Self);
  with HScroll do
  begin
    Parent := Self;
    Framed := True;
    Color := clBtnShadow;
    HandleColor := clBtnShadow;
    Centered := True;
    OnUserChange := ScrollHandler;
    OnGetWindowSize := RangeSizeHandler;
  end;

  VScroll := TCustomRangeBar.Create(Self);
  with VScroll do
  begin
    Parent := Self;
    Framed := True;
    Color := clBtnShadow;
    HandleColor := clBtnShadow;
    Centered := True;
    Kind := sbVertical;
    OnUserChange := ScrollHandler;
    OnGetWindowSize := RangeSizeHandler;
  end;

  FCentered := True;
  ScaleMode := smScale;
  BitmapAlign := baCustom;
  with GetViewportRect do
  begin
    OldSzX := Right - Left;
    OldSzY := Bottom - Top;
  end;

  FScrollBars := TIVScrollProperties.Create;
  FScrollBars.ImgView := Self;

  AlignAll;
end;

destructor TCustomImgView32.Destroy;
begin
  FScrollBars.Free;
  inherited;
end;

procedure TCustomImgView32.DoScaleChange;
begin
  InvalidateCache;
  UpdateScrollBars;
  UpdateImage;
  Invalidate;
end;

function TCustomImgView32.GetScrollBarSize: Integer;
begin
  Result := FScrollBarSize;
  if Result = 0 then Result := GetSystemMetrics(SM_CYHSCROLL);
end;

function TCustomImgView32.GetViewportRect: TRect;
var
  Sz: Integer;
begin
  Result := Rect(0, 0, Width, Height);
  Sz := GetScrollBarSize;
  Dec(Result.Right, Sz);
  Dec(Result.Bottom, Sz);
end;

procedure TCustomImgView32.Loaded;
begin
  AlignAll;
  Invalidate;
  UpdateScrollBars;
  if Centered then with Bitmap do ScrollToCenter(Width div 2, Height div 2);
  inherited;
end;

procedure TCustomImgView32.Paint;
var
  Sz: Integer;
begin
  inherited;
  Sz := GetScrollBarSize;
  Canvas.Brush.Color := clBtnFace;
  Canvas.FillRect(Rect(Width - Sz, Height - Sz, Width, Height));
end;

procedure TCustomImgView32.RangeSizeHandler(Sender: TObject; var Size: Integer);
var
  Sz: Integer;
begin
  Sz := GetScrollBarSize;
  if Sender = HScroll then Size := Width - Sz
  else if Sender = VScroll then Size := Height - Sz;
  if Size < 0 then Size := 0;
end;

procedure TCustomImgView32.Resize;
begin
  AlignAll;
  InvalidateCache;
  UpdateScrollBars;
  UpdateImage;
  Invalidate;
  inherited;
end;

procedure TCustomImgView32.ScrollHandler(Sender: TObject);
begin
  if DisableScrollUpdate then Exit;
  if Sender = HScroll then HScroll.Repaint;
  if Sender = VScroll then VScroll.Repaint;
  UpdateImage;
  Repaint;
end;

procedure TCustomImgView32.ScrollToCenter(X, Y: Integer);
begin
  DisableScrollUpdate := True;
  AlignAll;
  with GetViewportRect do
  begin
    HScroll.Position := X * Scale - (Right - Left) / 2;
    VScroll.Position := Y * Scale - (Bottom - Top) / 2;
  end;
  DisableScrollUpdate := False;
  UpdateImage;
end;

procedure TCustomImgView32.SetCentered(Value: Boolean);
begin
  InvalidateCache;
  FCentered := Value;
  HScroll.Centered := Value;
  VScroll.Centered := Value;
  UpdateScrollBars;
  UpdateImage;
  if Value then with Bitmap do ScrollToCenter(Width div 2, Height div 2)
  else ScrollToCenter(0, 0);
end;

procedure TCustomImgView32.SetScrollBars(Value: TIVScrollProperties);
begin
  FScrollBars.Assign(Value);
end;

procedure TCustomImgView32.UpdateImage;
var
  Sz: TSize;
  W, H: Integer;
begin
  Sz := GetBitmapSize;
  with GetViewportRect do
  begin
    W := Right - Left;
    H := Bottom - Top;
  end;
  Changing;
  BeginUpdate;
  if not Centered then
  begin
    OffsetHorz := -HScroll.Position;
    OffsetVert := -VScroll.Position;
  end
  else
  begin
    if W > Sz.Cx then OffsetHorz := (W - Sz.Cx) / 2
    else OffsetHorz := -HScroll.Position;
    if H > Sz.Cy then OffsetVert := (H - Sz.Cy) / 2
    else OffsetVert := -VScroll.Position;
  end;
  InvalidateCache;
  EndUpdate;    
  Changed;     
end;

procedure TCustomImgView32.UpdateScrollBars;
var
  Sz: TSize;
begin
  Sz := GetBitmapSize;
  HScroll.Range := Sz.Cx;
  VScroll.Range := Sz.Cy;
end;




{ TBitmap32Item }

constructor TBitmap32Item.Create(Collection: TCollection);
begin
  inherited;
  FBitmap := TBitmap32.Create;
end;

destructor TBitmap32Item.Destroy;
begin
  FBitmap.Free;
  inherited;
end;

procedure TBitmap32Item.SetBitmap(ABitmap: TBitmap32);
begin
  FBitmap.Assign(ABitmap)
end;




{ TBitmap32Collection }

function TBitmap32Collection.Add: TBitmap32Item;
begin
  Result := TBitmap32Item(inherited Add);
end;

constructor TBitmap32Collection.Create(AOwner: TPersistent; ItemClass: TBitmap32ItemClass);
begin
  inherited Create(ItemClass);
  FOwner := AOwner;
end;

function TBitmap32Collection.GetItem(Index: Integer): TBitmap32Item;
begin
  Result := TBitmap32Item(inherited GetItem(Index));
end;

function TBitmap32Collection.GetOwner: TPersistent;
begin
  Result := FOwner;
end;

procedure TBitmap32Collection.SetItem(Index: Integer; Value: TBitmap32Item);
begin
  inherited SetItem(Index, Value);
end;




{ TBitmap32List }

constructor TBitmap32List.Create(AOwner: TComponent);
begin
  inherited;
  FBitmap32Collection := TBitmap32Collection.Create(Self, TBitmap32Item);
end;

destructor TBitmap32List.Destroy;
begin
  FBitmap32Collection.Free;
  inherited;
end;

function TBitmap32List.GetBitmap(Index: Integer): TBitmap32;
begin
  Result := FBitmap32Collection.Items[Index].Bitmap;
end;

procedure TBitmap32List.SetBitmap(Index: Integer; Value: TBitmap32);
begin
  FBitmap32Collection.Items[Index].Bitmap := Value;
end;

procedure TBitmap32List.SetBitmap32Collection(Value: TBitmap32Collection);
begin
  FBitmap32Collection := Value;
end;

end.
