unit G32_Layers;

interface

uses
  SysUtils, Classes, Controls, Forms, Graphics, G32, Dialogs;

const
  { Layer Options Bits }
  LOB_VISIBLE           = $80000000; // 31-st bit
  LOB_GDI_OVERLAY       = $40000000; // 30-th bit
  LOB_MOUSE_EVENTS      = $20000000; // 29-th bit
  LOB_RESERVED_28       = $10000000; // 28-th bit
  LOB_RESERVED_27       = $08000000; // 27-th bit
  LOB_RESERVED_26       = $04000000; // 26-th bit
  LOB_RESERVED_25       = $02000000; // 25-th bit
  LOB_RESERVED_24       = $01000000; // 24-th bit
  LOB_RESERVED_MASK     = $FF000000;

type
  TCustomLayer = class;
  TPositionedLayer = class;
  TLayerClass = class of TCustomLayer;
  TLocateLayerEvent = procedure(Sender: TObject; var Location: TFloatRect) of object;

  TLayerCollection = class(TPersistent)
  private
    FItems: TList;
    FMouseEvents: Boolean;
    FMouseListener: TCustomLayer;
    FUpdateCount: Integer;
    FOwner: TComponent;
    FOnChanging: TNotifyEvent;
    FOnChange: TNotifyEvent;
    FOnGDIUpdate: TNotifyEvent;
    FOnLocateLayer: TLocateLayerEvent;
    function GetCount: Integer;
    procedure InsertItem(Item: TCustomLayer);
    procedure RemoveItem(Item: TCustomLayer);
    procedure SetMouseEvents(Value: Boolean);
  protected
    procedure BeginUpdate;
    procedure Changed;
    procedure Changing;
    procedure DoLocateLayer(var Location: TFloatRect); virtual;
    procedure EndUpdate;
    function  FindLayerAtPos(X, Y: Integer; OptionsMask: Cardinal): TCustomLayer;
    function  GetItem(Index: Integer): TCustomLayer;
    function  GetOwner: TPersistent; override;
    procedure GDIUpdate;
    procedure SetItem(Index: Integer; Value: TCustomLayer);
    function MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer): Boolean;
    function MouseMove(Shift: TShiftState; X, Y: Integer): Boolean;
    function MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer): Boolean;
    property OnChanging: TNotifyEvent read FOnChanging write FOnChanging;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property OnGDIUpdate: TNotifyEvent read FOnGDIUpdate write FOnGDIUpdate;
    property OnLocateLayer: TLocateLayerEvent read FOnLocateLayer write FOnLocateLayer;
  public
    constructor Create(AOwner: TComponent);
    destructor Destroy; override;
    function  Add(ItemClass: TLayerClass): TCustomLayer;
    procedure Assign(Source: TPersistent); override;
    procedure Clear;
    procedure Delete(Index: Integer);
    function  Insert(Index: Integer; ItemClass: TLayerClass): TCustomLayer;
    property Count: Integer read GetCount;
    property Items[Index: Integer]: TCustomLayer read GetItem write SetItem; default;
    property MouseListener: TCustomLayer read FMouseListener write FMouseListener;
    property MouseEvents: Boolean read FMouseEvents write SetMouseEvents;
  end;

  TLayerState = (lsMouseLeft, lsMouseRight, lsMouseMiddle);
  TLayerStates = set of TLayerState;

  TPaintLayerEvent = procedure(Sender: TObject; Buffer: TBitmap32) of object;
  THitTestEvent = procedure(Sender: TObject; X, Y: Integer; var Passed: Boolean) of object;

  TCustomLayer = class(TPersistent)
  private
    FCursor: TCursor;
    FFreeNotifies: TList;
    FLayerCollection: TLayerCollection;
    FLayerStates: TLayerStates;
    FLayerOptions: Cardinal;
    FOnHitTest: THitTestEvent;
    FOnMouseDown: TMouseEvent;
    FOnMouseMove: TMouseMoveEvent;
    FOnMouseUp: TMouseEvent;
    FOnPaint: TPaintLayerEvent;
    FTag: Integer;
    function  GetIndex: Integer;
    function  GetMouseEvents: Boolean;
    function  GetVisible: Boolean;
    procedure SetCursor(Value: TCursor);
    procedure SetLayerCollection(Value: TLayerCollection);
    procedure SetLayerOptions(Value: Cardinal);
    procedure SetMouseEvents(Value: Boolean);
    procedure SetVisible(Value: Boolean);
  protected
    procedure AddNotification(ALayer: TCustomLayer);
    procedure Changed;
    procedure Changing;
    function  DoHitTest(X, Y: Integer): Boolean; virtual;
    procedure DoPaint(Buffer: TBitmap32);
    function  GetOwner: TPersistent; override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); virtual;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); virtual;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); virtual;
    procedure Notification(ALayer: TCustomLayer); virtual;
    procedure Paint(Buffer: TBitmap32); virtual;
    procedure PaintGDI(Canvas: TCanvas); virtual;
    procedure RemoveNotification(ALayer: TCustomLayer);
    procedure SetIndex(Value: Integer); virtual;
  public
    constructor Create(ALayerCollection: TLayerCollection); virtual;
    destructor Destroy; override;
    procedure BringToFront;
    function  HitTest(X, Y: Integer): Boolean;
    procedure SendToBack;
    property Cursor: TCursor read FCursor write SetCursor;
    property Index: Integer read GetIndex write SetIndex;
    property LayerCollection: TLayerCollection read FLayerCollection write SetLayerCollection;
    property LayerOptions: Cardinal read FLayerOptions write SetLayerOptions;
    property LayerStates: TLayerStates read FLayerStates;
    property MouseEvents: Boolean read GetMouseEvents write SetMouseEvents;
    property Tag: Integer read FTag write FTag;
    property Visible: Boolean read GetVisible write SetVisible;
    property OnHitTest: THitTestEvent read FOnHitTest write FOnHitTest;
    property OnPaint: TPaintLayerEvent read FOnPaint write FOnPaint;
    property OnMouseDown: TMouseEvent read FOnMouseDown write FOnMouseDown;
    property OnMouseMove: TMouseMoveEvent read FOnMouseMove write FOnMouseMove;
    property OnMouseUp: TMouseEvent read FOnMouseUp write FOnMouseUp;
  end;

  TPositionedLayer = class(TCustomLayer)
  private
    FLocation: TFloatRect;
    FScaled: Boolean;
    procedure SetLocation(const Value: TFloatRect);
    procedure SetScaled(Value: Boolean);
  protected
    function DoHitTest(X, Y: Integer): Boolean; override;
    procedure DoSetLocation(const NewLocation: TFloatRect); virtual;
  public
    constructor Create(ALayerCollection: TLayerCollection); override;
    function GetAdjustedLocation: TFloatRect;
    property Location: TFloatRect read FLocation write SetLocation;
    property Scaled: Boolean read FScaled write SetScaled;
  end;

  TBitmapLayer = class(TPositionedLayer)
  private
    FBitmap: TBitmap32;
    FAlphaHit: Boolean;
    FCropped: Boolean;
    procedure BitmapChanging(Sender: TObject);
    procedure BitmapChanged(Sender: TObject);
    procedure SetBitmap(Value: TBitmap32);
    procedure SetCropped(Value: Boolean);
  protected
    function DoHitTest(X, Y: Integer): Boolean; override;
    procedure Paint(Buffer: TBitmap32); override;
  public
    constructor Create(ALayerCollection: TLayerCollection); override;
    destructor Destroy; override;
    property AlphaHit: Boolean read FAlphaHit write FAlphaHit;
    property Bitmap: TBitmap32 read FBitmap write SetBitmap;
    property Cropped: Boolean read FCropped write SetCropped;
  end;

  TDragState = (dsNone, dsMove, dsSizeL, dsSizeT, dsSizeR, dsSizeB,
    dsSizeTL, dsSizeTR, dsSizeBL, dsSizeBR);
  TRBHandles = set of (rhCenter, rhSides, rhCorners);
  TRBResizeOptions = set of (rroProportional, rroSymmetrical);

  TRubberbandLayer = class(TPositionedLayer)
  private
    FChildLayer: TPositionedLayer;
    FHandleFrame: TColor;
    FHandleFill: TColor;
    FHandles: TRBHandles;
    FHandleSize: Integer;
    FMinWidth: Single;
    FMaxHeight: Single;
    FMinHeight: Single;
    FMaxWidth: Single;
    FResizeOptions: TRBResizeOptions;
    procedure SetChildLayer(Value: TPositionedLayer);
    procedure SetHandleFill(Value: TColor);
    procedure SetHandleFrame(Value: TColor);
    procedure SetHandles(Value: TRBHandles);
    procedure SetHandleSize(Value: Integer);
  protected
    IsDragging: Boolean;
    DragState: TDragState;
    OldLocation: TFloatRect;
    MouseShift: TFloatPoint;
    FrameBitmap: TBitmap;
    procedure BuildFrameBitmap;
    function  DoHitTest(X, Y: Integer): Boolean; override;
    procedure DoSetLocation(const NewLocation: TFloatRect); override;
    function  GetDragState(X, Y: Integer): TDragState;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure Notification(ALayer: TCustomLayer); override;
    procedure PaintGDI(Canvas: TCanvas); override;
    procedure UpdateChildLayer;
  public
    constructor Create(ALayerCollection: TLayerCollection); override;
    destructor Destroy; override;
    property ChildLayer: TPositionedLayer read FChildLayer write SetChildLayer;
    property Handles: TRBHandles read FHandles write SetHandles;
    property HandleSize: Integer read FHandleSize write SetHandleSize;
    property HandleFill: TColor read FHandleFill write SetHandleFill;
    property HandleFrame: TColor read FHandleFrame write SetHandleFrame;
    property MaxHeight: Single read FMaxHeight write FMaxHeight;
    property MaxWidth: Single read FMaxWidth write FMaxWidth;
    property MinHeight: Single read FMinHeight write FMinHeight;
    property MinWidth: Single read FMinWidth write FMinWidth;
    property ResizeOptions: TRBResizeOptions read FResizeOptions write FResizeOptions;
  end;

implementation

uses TypInfo, G32_Image;

const
  // mouse state mapping
  CStateMap: array [TMouseButton] of TLayerState = (lsMouseLeft, lsMouseRight, lsMouseMiddle);

{ TLayerCollection }

function TLayerCollection.Add(ItemClass: TLayerClass): TCustomLayer;
begin
  Result := ItemClass.Create(Self);
end;

procedure TLayerCollection.Assign(Source: TPersistent);
var
  I: Integer;
  Item: TCustomLayer;
begin
  if Source is TLayerCollection then
  begin
    BeginUpdate;
    try
      while FItems.Count > 0 do TCustomLayer(FItems.Last).Free;
      for I := 0 to TLayerCollection(Source).Count - 1 do
      begin
        Item := TLayerCollection(Source).Items[I];
        Add(TLayerClass(Item.ClassType)).Assign(Item);
      end;
    finally
      EndUpdate;
    end;
    Exit;
  end;
  inherited Assign(Source);
end;

procedure TLayerCollection.BeginUpdate;
begin
  if FUpdateCount = 0 then Changing;
  Inc(FUpdateCount);
end;

procedure TLayerCollection.Changed;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TLayerCollection.Changing;
begin
  if Assigned(FOnChanging) then FOnChanging(Self);
end;

procedure TLayerCollection.Clear;
begin
  BeginUpdate;
  try
    while FItems.Count > 0 do TCustomLayer(FItems.Last).Free;
  finally
    EndUpdate;
  end;
end;

constructor TLayerCollection.Create(AOwner: TComponent);
begin
  FOwner := AOwner;
  FItems := TList.Create;
  FMouseEvents := True;
end;

procedure TLayerCollection.Delete(Index: Integer);
begin
  TCollectionItem(FItems[Index]).Free;
end;

destructor TLayerCollection.Destroy;
begin
  FUpdateCount := 1; // disable update notification
  if FItems <> nil then Clear;
  FItems.Free;
  inherited;
end;

procedure TLayerCollection.DoLocateLayer(var Location: TFloatRect);
begin
  if Assigned(FOnLocateLayer) then FOnLocateLayer(Self, Location);
end;

procedure TLayerCollection.EndUpdate;
begin
  Dec(FUpdateCount);
  if FUpdateCount = 0 then Changed;
  Assert(FUpdateCount >= 0, 'Unpaired EndUpdate');
end;

function TLayerCollection.FindLayerAtPos(X, Y: Integer; OptionsMask: Cardinal): TCustomLayer;
var
  I: Integer;
begin
  for I := Count - 1 downto 0 do
  begin
    Result := Items[I];
    if (Result.LayerOptions and OptionsMask) = 0 then Continue; // skip to the next one
    if Result.DoHitTest(X, Y) then Exit;
  end;
  Result := nil;
end;

procedure TLayerCollection.GDIUpdate;
begin
  if (FUpdateCount = 0) and Assigned(FOnGDIUpdate) then FOnGDIUpdate(Self);
end;

function TLayerCollection.GetCount: Integer;
begin
  Result := FItems.Count;
end;

function TLayerCollection.GetItem(Index: Integer): TCustomLayer;
begin
  Result := FItems[Index];
end;

function TLayerCollection.GetOwner: TPersistent;
begin
  Result := FOwner;
end;

function TLayerCollection.Insert(Index: Integer; ItemClass: TLayerClass): TCustomLayer;
begin
  BeginUpdate;
  try
    Result := Add(ItemClass);
    Result.Index := Index;
  finally
    EndUpdate;
  end;
end;

procedure TLayerCollection.InsertItem(Item: TCustomLayer);
begin
  BeginUpdate;
  try
    FItems.Add(Item);
    Item.FLayerCollection := Self;
  finally
    EndUpdate;
  end;
end;

function TLayerCollection.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer): Boolean;
begin
  if MouseListener = nil then MouseListener := FindLayerAtPos(X, Y, LOB_MOUSE_EVENTS);
  if Assigned(MouseListener) then
  begin
    Include(MouseListener.FLayerStates, CStateMap[Button]);
    MouseListener.MouseDown(Button, Shift, X, Y);
  end;
  Result := Assigned(MouseListener);
end;

function TLayerCollection.MouseMove(Shift: TShiftState; X, Y: Integer): Boolean;
var
  ALayer: TCustomLayer;
begin
  ALayer := MouseListener;
  if ALayer = nil then ALayer := FindLayerAtPos(X, Y, LOB_MOUSE_EVENTS);
  if Assigned(ALayer) then ALayer.MouseMove(Shift, X, Y)
  else if FOwner is TControl then Screen.Cursor := TControl(FOwner).Cursor;
  Result := Assigned(ALayer);
end;

function TLayerCollection.MouseUp(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer): Boolean;
var
  ALayer: TCustomLayer;
begin
  ALayer := MouseListener;
  if ALayer = nil then ALayer := FindLayerAtPos(X, Y, LOB_MOUSE_EVENTS);
  if Assigned(ALayer) then
  begin
    Exclude(ALayer.FLayerStates, CStateMap[Button]);
    ALayer.MouseUp(Button, Shift, X, Y);
  end;

  Result := Assigned(ALayer);
  if Assigned(MouseListener) and
    (MouseListener.FLayerStates *
      [lsMouseLeft, lsMouseRight, lsMouseMiddle] = []) then
    MouseListener := nil; // reset mouse capture
end;

procedure TLayerCollection.RemoveItem(Item: TCustomLayer);
begin
  BeginUpdate;
  try
    FItems.Remove(Item);
    Item.FLayerCollection := nil;
  finally
    EndUpdate;
  end;
end;

procedure TLayerCollection.SetItem(Index: Integer; Value: TCustomLayer);
begin
  TCollectionItem(FItems[Index]).Assign(Value);
end;

procedure TLayerCollection.SetMouseEvents(Value: Boolean);
begin
  FMouseEvents := Value;
  MouseListener := nil;
end;

{ TCustomLayer }

procedure TCustomLayer.AddNotification(ALayer: TCustomLayer);
begin
  if not Assigned(FFreeNotifies) then FFreeNotifies := TList.Create;
  if FFreeNotifies.IndexOf(ALayer) < 0 then FFreeNotifies.Add(ALayer);
end;

procedure TCustomLayer.BringToFront;
begin
  Index := LayerCollection.Count;
end;

procedure TCustomLayer.Changed;
begin
  if FLayerCollection <> nil then
  begin
    if Visible then FLayerCollection.Changed
    else if (FLayerOptions and $40000000) <> 0 then FLayerCollection.GDIUpdate;
  end;
end;

procedure TCustomLayer.Changing;
begin
  if Visible and (FLayerCollection <> nil) then FLayerCollection.Changing;
end;

constructor TCustomLayer.Create(ALayerCollection: TLayerCollection);
begin
  LayerCollection := ALayerCollection;
  FLayerOptions := LOB_VISIBLE;
end;

destructor TCustomLayer.Destroy;
var
  I: Integer;
begin
  if FFreeNotifies <> nil then
  begin
    for I := FFreeNotifies.Count - 1 downto 0 do
    begin
      TCustomLayer(FFreeNotifies[I]).Notification(Self);
      if FFreeNotifies = nil then Break;
    end;
    FFreeNotifies.Free;
    FFreeNotifies := nil;
  end;
  SetLayerCollection(nil);
  inherited;
end;

function TCustomLayer.DoHitTest(X, Y: Integer): Boolean;
begin
  Result := True;
end;

procedure TCustomLayer.DoPaint(Buffer: TBitmap32);
begin
  Paint(Buffer);
  if Assigned(FOnPaint) then FOnPaint(Self, Buffer);
end;

function TCustomLayer.GetIndex: Integer;
begin
  if FLayerCollection <> nil then Result := FLayerCollection.FItems.IndexOf(Self)
  else Result := -1;
end;

function TCustomLayer.GetMouseEvents: Boolean;
begin
  Result := FLayerOptions and LOB_MOUSE_EVENTS <> 0;
end;

function TCustomLayer.GetOwner: TPersistent;
begin
  Result := FLayerCollection;
end;

function TCustomLayer.GetVisible: Boolean;
begin
  Result := FLayerOptions and LOB_VISIBLE <> 0;
end;

function TCustomLayer.HitTest(X, Y: Integer): Boolean;
begin
  Result := DoHitTest(X, Y);
  if Assigned(FOnHitTest) then FOnHitTest(Self, X, Y, Result);
end;

procedure TCustomLayer.MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseDown) then FOnMouseDown(Self, Button, Shift, X, Y);
end;

procedure TCustomLayer.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  Screen.Cursor := Cursor;
  if Assigned(FOnMouseMove) then FOnMouseMove(Self, Shift, X, Y);
end;

procedure TCustomLayer.MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseUp) then FOnMouseUp(Self, Button, Shift, X, Y);
end;

procedure TCustomLayer.Notification(ALayer: TCustomLayer);
begin
  // do nothing by default
end;

procedure TCustomLayer.Paint(Buffer: TBitmap32);
begin
  // descendants override this method
end;

procedure TCustomLayer.PaintGDI(Canvas: TCanvas);
begin
  // descendants override this method
end;

procedure TCustomLayer.RemoveNotification(ALayer: TCustomLayer);
begin
  if FFreeNotifies <> nil then
  begin
    FFreeNotifies.Remove(ALayer);
    if FFreeNotifies.Count = 0 then
    begin
      FFreeNotifies.Free;
      FFreeNotifies := nil;
    end;
  end;
end;

procedure TCustomLayer.SendToBack;
begin
  Index := 0;
end;

procedure TCustomLayer.SetCursor(Value: TCursor);
begin
  if Value <> FCursor then
  begin
    FCursor := Value;
    if FLayerCollection.MouseListener = Self then Screen.Cursor := Value;
  end;
end;

procedure TCustomLayer.SetIndex(Value: Integer);
var
  CurIndex: Integer;
begin
  CurIndex := GetIndex;
  if (CurIndex >= 0) and (CurIndex <> Value) then
    with FLayerCollection do
    begin
      if Value < 0 then Value := 0;
      if Value >= Count then Value := Count - 1;
      if Value <> CurIndex then
      begin
        if Visible then BeginUpdate;
        try
          FLayerCollection.FItems.Move(CurIndex, Value);
        finally
          if Visible then EndUpdate;
        end;
      end;
    end;
end;

procedure TCustomLayer.SetLayerCollection(Value: TLayerCollection);
begin
  if FLayerCollection <> Value then
  begin
    if FLayerCollection <> nil then
    begin
      if FLayerCollection.MouseListener = Self then
        FLayerCollection.MouseListener := nil;
      FLayerCollection.RemoveItem(Self);
    end;
    if Value <> nil then Value.InsertItem(Self);
  end;
end;

procedure TCustomLayer.SetLayerOptions(Value: Cardinal);
begin
  Changing;
  FLayerOptions := Value;
  Changed;
end;

procedure TCustomLayer.SetMouseEvents(Value: Boolean);
begin
  if Value then LayerOptions := LayerOptions or LOB_MOUSE_EVENTS
  else LayerOptions := LayerOptions and not LOB_MOUSE_EVENTS;
end;

procedure TCustomLayer.SetVisible(Value: Boolean);
begin
  if Value then LayerOptions := LayerOptions or LOB_VISIBLE
  else LayerOptions := LayerOptions and not LOB_VISIBLE;
end;

{ TPositionedLayer }

constructor TPositionedLayer.Create(ALayerCollection: TLayerCollection);
begin
  inherited;
  with FLocation do
  begin
    Left := 0;
    Top := 0;
    Right := 64;
    Bottom := 64;
  end;
  FLayerOptions := LOB_VISIBLE or LOB_MOUSE_EVENTS;
end;

function TPositionedLayer.DoHitTest(X, Y: Integer): Boolean;
begin
  with GetAdjustedLocation do
    Result := (X >= Left) and (X < Right) and (Y >= Top) and (Y < Bottom);
end;

procedure TPositionedLayer.DoSetLocation(const NewLocation: TFloatRect);
begin
  FLocation := NewLocation;
end;

function TPositionedLayer.GetAdjustedLocation: TFloatRect;
begin
  Result := FLocation;
  if Scaled then FLayerCollection.DoLocateLayer(Result);
end;

procedure TPositionedLayer.SetLocation(const Value: TFloatRect);
begin
  Changing;
  DoSetLocation(Value);
  Changed;
end;

procedure TPositionedLayer.SetScaled(Value: Boolean);
begin
  if Value <> FScaled then
  begin
    Changing;
    FScaled := Value;
    Changed;
  end;
end;

{ TBitmapLayer }

procedure TBitmapLayer.BitmapChanged(Sender: TObject);
begin
  Changed;
end;

procedure TBitmapLayer.BitmapChanging(Sender: TObject);
begin
  Changing;
end;

constructor TBitmapLayer.Create(ALayerCollection: TLayerCollection);
begin
  inherited;
  FBitmap := TBitmap32.Create;
  FBitmap.OnChanging := BitmapChanging;
  FBitmap.OnChange := BitmapChanged;
end;

function TBitmapLayer.DoHitTest(X, Y: Integer): Boolean;
var
  BitmapX, BitmapY: Integer;
  LayerWidth, LayerHeight: Integer;
begin
  Result := inherited DoHitTest(X, Y);
  if Result and AlphaHit then
  begin
    with GetAdjustedLocation do
    begin
      LayerWidth := Round(Right - Left);
      LayerHeight := Round(Bottom - Top);
      if (LayerWidth < 0.5) or (LayerHeight < 0.5) then Result := False
      else
      begin
        // check the pixel alpha at (X, Y) position
        BitmapX := Round((X - Left) * Bitmap.Width / LayerWidth);
        BitmapY := Round((Y - Top) * Bitmap.Height / LayerHeight);
        if Bitmap.PixelS[BitmapX, BitmapY] and $FF000000 = 0 then Result := False;
      end;
    end;
  end;
end;

destructor TBitmapLayer.Destroy;
begin
  FBitmap.Free;
  inherited;
end;

procedure TBitmapLayer.Paint(Buffer: TBitmap32);
var
  SrcRect, DstRect, CroppedDst: TRect;
  ImageRect: TRect;
  LayerWidth, LayerHeight: Single;
begin
  DstRect := Rect(GetAdjustedLocation);
  SrcRect := Rect(0, 0, Bitmap.Width, Bitmap.Height);
  if Cropped and (LayerCollection.FOwner is TCustomImage32) then
  begin
    with DstRect do
    begin
      LayerWidth := Right - Left;
      LayerHeight := Bottom - Top;
    end;
    if (LayerWidth < 0.5) or (LayerHeight < 0.5) then Exit;
    ImageRect := TCustomImage32(LayerCollection.FOwner).GetBitmapRect;
    IntersectRect(CroppedDst, DstRect, ImageRect);
    SrcRect.Left := Round((CroppedDst.Left - DstRect.Left) * Bitmap.Width / LayerWidth);
    SrcRect.Right := Round((CroppedDst.Right - DstRect.Left) * Bitmap.Width / LayerWidth);
    SrcRect.Top := Round((CroppedDst.Top - DstRect.Top) * Bitmap.Height / LayerHeight);
    SrcRect.Bottom := Round((CroppedDst.Bottom - DstRect.Top) * Bitmap.Height / LayerHeight);
    DstRect := CroppedDst;
  end;
  FBitmap.DrawTo(Buffer, DstRect, SrcRect);
end;

procedure TBitmapLayer.SetBitmap(Value: TBitmap32);
begin
  FBitmap.Assign(Value);
end;

procedure TBitmapLayer.SetCropped(Value: Boolean);
begin
  if Value <> FCropped then
  begin
    Changing;
    FCropped := Value;
    Changed;
  end;
end;

{ TRubberbandLayer }

procedure TRubberbandLayer.BuildFrameBitmap;
var
  I, J: Integer;
  C1, C2: TColor;
begin
  C1 := clBlack;
  C2 := clWhite;
  with FrameBitmap.Canvas do
    for J := 0 to 7 do
      for I := 0 to 7 do
        if (I + J) mod 4 < 2 then Pixels[I, J] := C1
        else Pixels[I, J] := C2;
end;

constructor TRubberbandLayer.Create(ALayerCollection: TLayerCollection);
begin
  inherited;
  FHandleFrame := clBlack;
  FHandleFill := clWhite;
  FHandles := [rhCenter, rhSides, rhCorners];
  FHandleSize := 3;
  FMinWidth := 10;
  FMinHeight := 10;
  FrameBitmap := TBitmap.Create;
  FrameBitmap.Width := 8;
  FrameBitmap.Height := 8;
  FLayerOptions := LOB_GDI_OVERLAY or LOB_MOUSE_EVENTS;
  BuildFrameBitmap;
end;

destructor TRubberbandLayer.Destroy;
begin
  FrameBitmap.Free;
  inherited;
end;

function TRubberbandLayer.DoHitTest(X, Y: Integer): Boolean;
begin
  Result := GetDragState(X, Y) <> dsNone;
end;

procedure TRubberbandLayer.DoSetLocation(const NewLocation: TFloatRect);
begin
  inherited;
  UpdateChildLayer;
end;

function TRubberbandLayer.GetDragState(X, Y: Integer): TDragState;
var
  R: TRect;
  dh_center, dh_sides, dh_corners: Boolean;
  dl, dt, dr, db, dx, dy: Boolean;
  Sz: Integer;
begin
  Result := dsNone;
  Sz := FHandleSize + 1;
  dh_center := rhCenter in FHandles;
  dh_sides := rhSides in FHandles;
  dh_corners := rhCorners in FHandles;
  R := Rect(GetAdjustedLocation);
  with R do
  begin
    Dec(Right);
    Dec(Bottom);
    dl := Abs(Left - X) <= Sz;
    dr := Abs(Right - X) <= Sz;
    dx := Abs((Left + Right) div 2 - X) <= Sz;
    dt := Abs(Top - Y) <= Sz;
    db := Abs(Bottom - Y) <= Sz;
    dy := Abs((Top + Bottom) div 2 - Y) <= Sz;
  end;

  if dr and db and dh_corners then Result := dsSizeBR
  else if dl and db and dh_corners then Result := dsSizeBL
  else if dr and dt and dh_corners then Result := dsSizeTR
  else if dl and dt and dh_corners then Result := dsSizeTL
  else if dr and dy and dh_sides   then Result := dsSizeR
  else if db and dx and dh_sides   then Result := dsSizeB
  else if dl and dy and dh_sides   then Result := dsSizeL
  else if dt and dx and dh_sides   then Result := dsSizeT
  else if dh_center and PtInRect(R, Point(X, Y)) then Result := dsMove;
end;

procedure TRubberbandLayer.MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  ALoc: TFloatRect;
begin
  if IsDragging then Exit;
  DragState := GetDragState(X, Y);
  IsDragging := DragState <> dsNone;
  if IsDragging then
  begin
    OldLocation := Location;
    ALoc := GetAdjustedLocation;
    case DragState of
      dsMove: MouseShift := FloatPoint(X - ALoc.Left, Y - ALoc.Top);
    else
      MouseShift := FloatPoint(0, 0);
    end;
  end;
  inherited;
end;

procedure TRubberbandLayer.MouseMove(Shift: TShiftState; X, Y: Integer);
const
  CURSOR_ID: array [TDragState] of TCursor = (crDefault, crDefault, crSizeWE,
    crSizeNS, crSizeWE, crSizeNS, crSizeNWSE, crSizeNESW, crSizeNESW, crSizeNWSE);
var
  Mx, My: Single;
  L, T, R, B, W, H: Single;
  ALoc: TFloatRect;

  procedure IncLT(var LT, RB: Single; Delta, MinSize, MaxSize: Single);
  var
    C: Single;
  begin
    if rroSymmetrical in ResizeOptions then
    begin
      LT := LT + Delta;
      RB := RB - Delta;
      C := (LT + RB) / 2;
      if RB - LT < MinSize then
      begin
        LT := C - MinSize / 2;
        RB := C + MinSize / 2;
      end;
      if (MaxSize > MinSize) and (RB - LT > MaxSize) then
      begin
        LT := C - MaxSize / 2;
        RB := C + MaxSize / 2;
      end;
    end
    else
    begin
      LT := LT + Delta;
      if RB - LT < MinSize then LT := RB - MinSize;
      if MaxSize > MinSize then
        if RB - LT > MaxSize then LT := RB - MaxSize;
    end;
  end;

  procedure IncRB(var LT, RB: Single; Delta, MinSize, MaxSize: Single);
  var
    C: Single;
  begin
    if rroSymmetrical in ResizeOptions then
    begin
      RB := RB + Delta;
      LT := LT - Delta;
      C := (LT + RB) / 2;
      if RB - LT < MinSize then
      begin
        LT := C - MinSize / 2;
        RB := C + MinSize / 2;
      end;
      if (MaxSize > MinSize) and (RB - LT > MaxSize) then
      begin
        LT := C - MaxSize / 2;
        RB := C + MaxSize / 2;
      end;
    end
    else
    begin
      RB := RB + Delta;
      if RB - LT < MinSize then RB := LT + MinSize;
      if MaxSize > MinSize then
        if RB - LT > MaxSize then RB := LT + MaxSize;
    end;
  end;

begin
  if not IsDragging then
  begin
    DragState := GetDragState(X, Y);
    if DragState = dsMove then Screen.Cursor := Cursor
    else Screen.Cursor := CURSOR_ID[DragState];
  end
  else
  begin
    Mx := X - MouseShift.X;
    My := Y - MouseShift.Y;
    if Scaled then with Location do
    begin
      ALoc := GetAdjustedLocation;
      if IsRectEmpty(ALoc) then Exit;
      Mx := (Mx - ALoc.Left) / (ALoc.Right - ALoc.Left) * (Right - Left) + Left;
      My := (My - ALoc.Top) / (ALoc.Bottom - ALoc.Top) * (Bottom - Top) + Top;
    end;

    with OldLocation do
    begin
      L := Left; T := Top; R := Right; B := Bottom; W := R - L; H := B - T;
    end;
    if DragState = dsMove then
    begin
      L := Mx; T := My; R := L + W; B := T + H;
    end
    else
    begin
      if DragState in [dsSizeL, dsSizeTL, dsSizeBL] then
        IncLT(L, R, Mx - L, MinWidth, MaxWidth);
      if DragState in [dsSizeR, dsSizeTR, dsSizeBR] then
        IncRB(L, R, Mx - R, MinWidth, MaxWidth);
      if DragState in [dsSizeT, dsSizeTL, dsSizeTR] then
        IncLT(T, B, My - T, MinHeight, MaxHeight);
      if DragState in [dsSizeB, dsSizeBL, dsSizeBR] then
        IncRB(T, B, My - B, MinHeight, MaxHeight);
    end;

    if (L <> Location.Left) or (R <> Location.Right) or (T <> Location.Top) or
      (B <> Location.Bottom) then
    begin
      LayerCollection.BeginUpdate;
      Location := FloatRect(L, T, R, B);
      LayerCollection.EndUpdate;
      UpdateChildLayer;
    end;
  end;
end;

procedure TRubberbandLayer.MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  IsDragging := False;
  inherited;
end;

procedure TRubberbandLayer.Notification(ALayer: TCustomLayer);
begin
  if ALayer = FChildLayer then FChildLayer := nil;
end;

procedure TRubberbandLayer.PaintGDI(Canvas: TCanvas);
var
  Cx, Cy: Integer;
  R: TRect;

  procedure DrawHandle(X, Y: Integer);
  begin
    Canvas.Rectangle(X - FHandleSize, Y - FHandleSize, X + FHandleSize, Y + FHandleSize);
  end;

begin
  Canvas.Pen.Color := HandleFrame;
  Canvas.Pen.Style := psSolid;
  R := Rect(GetAdjustedLocation);
  with R do
  begin
    Canvas.Brush.Bitmap := FrameBitmap;
    Canvas.FrameRect(R);
    Canvas.Brush.Color := HandleFill;
    Canvas.Brush.Style := bsSolid;
    Cx := (Left + Right) div 2;
    Cy := (Top + Bottom) div 2;
    DrawHandle(Left, Top);
    DrawHandle(Cx, Top);
    DrawHandle(Right, Top);
    DrawHandle(Left, Cy);
    DrawHandle(Right, Cy);
    DrawHandle(Left, Bottom);
    DrawHandle(Cx, Bottom);
    DrawHandle(Right, Bottom);
  end;
end;

procedure TRubberbandLayer.SetChildLayer(Value: TPositionedLayer);
begin
  if FChildLayer <> nil then RemoveNotification(FChildLayer);
  FChildLayer := Value;
  if Value <> nil then
  begin
    FLayerCollection.BeginUpdate;
    Location := Value.Location;
    Scaled := Value.Scaled;
    AddNotification(FChildLayer);
    FLayerCollection.EndUpdate;
  end;
end;

procedure TRubberbandLayer.SetHandleFill(Value: TColor);
begin
  if Value <> FHandleFill then
  begin
    FHandleFill := Value;
    FLayerCollection.GDIUpdate;
  end;
end;

procedure TRubberbandLayer.SetHandleFrame(Value: TColor);
begin
  if Value <> FHandleFrame then
  begin
    FHandleFrame := Value;
    FLayerCollection.GDIUpdate;
  end;
end;

procedure TRubberbandLayer.SetHandles(Value: TRBHandles);
begin
  if Value <> FHandles then
  begin
    FHandles := Value;
    FLayerCollection.GDIUpdate;
  end;
end;

procedure TRubberbandLayer.SetHandleSize(Value: Integer);
begin
  if Value < 1 then Value := 1;
  if Value <> FHandleSize then
  begin
    FHandleSize := Value;
    FLayerCollection.GDIUpdate;
  end;
end;

procedure TRubberbandLayer.UpdateChildLayer;
begin
  if Assigned(FChildLayer) then FChildLayer.Location := Location;
end;

end.
