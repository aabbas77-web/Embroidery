{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrDesign;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrControls, VrSystem, VrSysUtils;


type
  TVrBitmapButton = class(TVrGraphicImageControl)
  private
    FAutoSize: Boolean;
    FGlyph: TBitmap;
    FMask: TBitmap;
    FNumGlyphs: TVrNumGlyphs;
    FImageWidth: Integer;
    FImageHeight: Integer;
    FVIndent: Integer;
    FHIndent: Integer;
    FHasMouse: Boolean;
    FTransparentMode: TVrTransparentMode;
    Down: Boolean;
    Pressed: Boolean;
    function InControl(X, Y: Integer): Boolean;
    procedure SetGlyph(Value: TBitmap);
    procedure SetNumGlyphs(Value: TVrNumGlyphs);
    procedure SetVIndent(Value: Integer);
    procedure SetHIndent(Value: Integer);
    procedure SetAutoSize(Value: Boolean);
    procedure SetTransparentMode(Value: TVrTransparentMode);
    procedure GlyphChanged(Sender: TObject);
    procedure DoMouseDown(XPos, YPos: Integer);
    procedure WMLButtonDown(var Message: TWMLButtonDown); message WM_LButtonDown;
    procedure WMMouseMove(var Message: TWMMouseMove); message WM_MouseMove;
    procedure WMLButtonUp(var Message: TWMLButtonUp); message WM_LButtonUp;
    procedure CMMouseEnter(var Message: TMessage); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
  protected
    function GetPalette: HPalette; override;
    procedure Loaded; override;
    procedure Paint; override;
    procedure AdjustBounds;
    procedure AdjustImageSize;
    function DestRect: TRect;
    function GetImageRect(Index: Integer): TRect;
    function GetTransparentColor: TColor;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Glyph: TBitmap read FGlyph write SetGlyph;
    property NumGlyphs: TVrNumGlyphs read FNumGlyphs write SetNumGlyphs default 1;
    property VIndent: Integer read FVIndent write SetVIndent default 2;
    property HIndent: Integer read FHIndent write SetHIndent default 2;
    property AutoSize: Boolean read FAutoSize write SetAutoSize default false;
    property TransparentMode: TVrTransparentMode read FTransparentMode write SetTransparentMode default tmColor;
    property Transparent default false;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color default clBtnFace;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Enabled;
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

  TVrBitmapImage = class(TVrGraphicImageControl)
  private
    FAutoSize: Boolean;
    FCenter: Boolean;
    FStretch: Boolean;
    FImageIndex: Integer;
    FBitmap: TBitmap;
    FBitmapList: TVrBitmapList;
    FChangeEvent: TNotifyEvent;
    function GetBitmap: TBitmap;
    procedure SetAutoSize(Value: Boolean);
    procedure SetCenter(Value: Boolean);
    procedure SetStretch(Value: Boolean);
    procedure SetImageIndex(Value: Integer);
    procedure SetBitmapList(Value: TVrBitmapList);
    procedure BitmapsChanged(Sender: TObject);
  protected
    function GetPalette: HPALETTE; override;
    function DestRect: TRect;
    procedure AdjustBounds;
    procedure Paint; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property AutoSize: Boolean read FAutoSize write SetAutoSize default false;
    property Center: Boolean read FCenter write SetCenter default True;
    property Stretch: Boolean read FStretch write SetStretch default false;
    property ImageIndex: Integer read FImageIndex write SetImageIndex default -1;
    property BitmapList: TVrBitmapList read FBitmapList write SetBitmapList;
    property Transparent default false;
    property Align;
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

  TVrCounterDigits = 1..10;
  TVrCounterValue = 0..MaxInt;
  TVrCounter = class(TVrGraphicImageControl)
  private
    FValue: TVrCounterValue;
    FDigits: TVrCounterDigits;
    FAutoSize: Boolean;
    FBitmap: TBitmap;
    FSpacing: Integer;
    FDigitSize: TPoint;
    FStretch: Boolean;
    FOnChange: TNotifyEvent;
    FImage: TBitmap;
    procedure SetValue(Value: TVrCounterValue);
    procedure SetDigits(Value: TVrCounterDigits);
    procedure SetAutoSize(Value: Boolean);
    procedure SetBitmap(Value: TBitmap);
    procedure SetSpacing(Value: Integer);
    procedure SetStretch(Value: Boolean);
    procedure BitmapChanged(Sender: TObject);
  protected
    function GetPalette: HPalette; override;
    procedure CalcPaintParams;
    procedure Paint; override;
    procedure Changed; virtual;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Value: TVrCounterValue read FValue write SetValue default 0;
    property Digits: TVrCounterDigits read FDigits write SetDigits default 8;
    property AutoSize: Boolean read FAutoSize write SetAutoSize default True;
    property Bitmap: TBitmap read FBitmap write SetBitmap;
    property Spacing: Integer read FSpacing write SetSpacing default 0;
    property Stretch: Boolean read FStretch write SetStretch default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
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

{ TVrBitmapButton }

constructor TVrBitmapButton.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable] -
    [csDoubleClicks, csSetCaption];
  Width := 50;
  Height := 50;
  Color := clBtnFace;
  ParentColor := false;
  FGlyph := TBitmap.Create;
  FGlyph.OnChange := GlyphChanged;
  FMask := TBitmap.Create;
  FNumGlyphs := 1;
  FAutoSize := false;
  FVIndent := 2;
  FHIndent := 2;
  FTransparentMode := tmColor;
end;

destructor TVrBitmapButton.Destroy;
begin
  FMask.Free;
  FGlyph.Free;
  inherited Destroy;
end;

procedure TVrBitmapButton.Loaded;
begin
  inherited Loaded;
  AdjustImageSize;
  FMask.Assign(Glyph);
  FMask.Mask(Self.Color);
end;

procedure TVrBitmapButton.Paint;
var
  Index: Integer;
begin
  AdjustBounds;

  ClearBitmapCanvas;

  Index := 0;
  if FHasMouse then Index := 1;
  if Down then Index := 2;
  if not Enabled then Index := 3;
  if Succ(Index) > NumGlyphs then Index := 0;

  if not Glyph.Empty then
    with BitmapCanvas do
    begin
      if Transparent then Brush.Style := bsClear
      else Brush.Style := bsSolid;
      BrushCopy(DestRect, FGlyph, GetImageRect(Index), GetTransparentColor);
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

function TVrBitmapButton.GetTransparentColor: TColor;
begin
  Result := Self.Color;
  if (not Glyph.Empty) and (TransparentMode = tmPixel) then
    Result := Glyph.Canvas.Pixels[0,0];
end;

function TVrBitmapButton.GetPalette: HPALETTE;
begin
  Result := 0;
  if not Glyph.Empty then
    Result := Glyph.Palette;
end;

procedure TVrBitmapButton.AdjustImageSize;
begin
  FImageWidth := 0;
  FImageHeight := 0;
  if not Glyph.Empty then
  begin
    FImageWidth := Glyph.Width div NumGlyphs;
    FImageHeight := Glyph.Height;
  end;
end;

function TVrBitmapButton.GetImageRect(Index: Integer): TRect;
begin
  Result := Bounds(Index * FImageWidth, 0, FImageWidth, FImageHeight)
end;

procedure TVrBitmapButton.AdjustBounds;
begin
  if (AutoSize) and (Align = alNone) then
    if (FImageWidth > 0) and (FImageHeight > 0) then
      SetBounds(Left, Top, FImageWidth + HIndent + 1, FImageHeight + VIndent + 1);
end;

function TVrBitmapButton.DestRect: TRect;
var
  MidX, MidY: Integer;
begin
  MidX := (ClientWidth - FImageWidth) div 2;
  MidY := (ClientHeight - FImageHeight) div 2;
  Result := Bounds(MidX, MidY, FImageWidth, FImageHeight);
  if Down then OffsetRect(Result, HIndent, VIndent);
end;

procedure TVrBitmapButton.GlyphChanged(Sender: TObject);
begin
  AdjustImageSize;
  UpdateControlCanvas;
end;

procedure TVrBitmapButton.SetGlyph(Value: TBitmap);
begin
  FGlyph.Assign(Value);
  FMask.Assign(Value);
  FMask.Mask(Self.Color);
end;

procedure TVrBitmapButton.SetNumGlyphs(Value: TVrNumGlyphs);
begin
  if (FNumGlyphs <> Value) then
  begin
    FNumGlyphs := Value;
    AdjustImageSize;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapButton.SetVIndent(Value: Integer);
begin
  if (FVIndent <> Value) and (Value >= 0) then
  begin
    FVIndent := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapButton.SetHIndent(Value: Integer);
begin
  if (FHIndent <> Value) and (Value >= 0) then
  begin
    FHIndent := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapButton.SetAutoSize(Value: Boolean);
begin
  if FAutoSize <> Value then
  begin
    FAutoSize := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapButton.SetTransparentMode(Value: TVrTransparentMode);
begin
  if FTransparentMode <> Value then
  begin
    FTransparentMode := Value;
    UpdateControlCanvas;
  end;
end;

function TVrBitmapButton.InControl(X, Y: Integer): Boolean;
var
  R: TRect;
begin
  R := ClientRect;
  Result := (PtInRect(R, Point(X, Y))) and
            (FMask.Canvas.Pixels[X, Y] = clBlack);
end;

procedure TVrBitmapButton.DoMouseDown(XPos, YPos: Integer);
begin
  if InControl(XPos, YPos) then
  begin
    Pressed := True;
    Down := True;
    MouseCapture := true;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapButton.WMLButtonDown(var Message: TWMLButtonDown);
begin
  inherited;
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrBitmapButton.WMMouseMove(var Message: TWMMouseMove);
var
  P: TPoint;
begin
  inherited;
  if Pressed then
  begin
    P := Point(Message.XPos, Message.YPos);
    if InControl(P.X, P.Y) <> Down then
    begin
      Down := not Down;
      UpdateControlCanvas;
    end;
  end;
end;

procedure TVrBitmapButton.WMLButtonUp(var Message: TWMLButtonUp);
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
    inherited; // Click;
  end;
end;

procedure TVrBitmapButton.CMMouseEnter(var Message: TMessage);
begin
  inherited;
  FHasMouse := True;
  UpdateControlCanvas;
end;

procedure TVrBitmapButton.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  FHasMouse := false;
  UpdateControlCanvas;
end;

procedure TVrBitmapButton.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;


{ TVrBitmapImage }

constructor TVrBitmapImage.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 105;
  Height := 105;
  Color := clBtnFace;
  ParentColor := false;
  FAutoSize := false;
  FCenter := True;
  FStretch := false;
  FImageIndex := -1;
end;

destructor TVrBitmapImage.Destroy;
begin
  if FBitmapList <> nil then
    with FBitmapList do Bitmaps.OnChange := FChangeEvent;
  inherited Destroy;
end;

function TVrBitmapImage.GetBitmap: TBitmap;
begin
  Result := nil;
  if Assigned(FBitmapList) and
    (ImageIndex <> -1) and
    (ImageIndex < FBitmapList.Bitmaps.Count) then
       Result := FBitmapList.Bitmaps[ImageIndex];
end;

procedure TVrBitmapImage.SetBitmapList(Value: TVrBitmapList);
begin
  FBitmapList := Value;
  if Value <> nil then
    with FBitmapList do
    begin
      FChangeEvent := Bitmaps.OnChange;
      Bitmaps.OnChange := BitmapsChanged;
    end;
  Value.FreeNotification(Value);
  UpdateControlCanvas;
end;

procedure TVrBitmapImage.BitmapsChanged(Sender: TObject);
begin
  UpdateControlCanvas;
  if Assigned(FChangeEvent) then FChangeEvent(FBitmapList.Bitmaps);
end;

function TVrBitmapImage.GetPalette: HPALETTE;
begin
  Result := 0;
  if GetBitmap <> nil then
    Result := GetBitmap.Palette;
end;

procedure TVrBitmapImage.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) and (AComponent = FBitmapList) then
  begin
    FBitmapList.Bitmaps.OnChange := FChangeEvent;
    FBitmapList := nil;
    FImageIndex := -1;
    UpdateControlCanvas;
  end;
end;

function TVrBitmapImage.DestRect: TRect;
begin
  if Stretch then
    Result := ClientRect
  else if Center then
    Result := Bounds((Width - FBitmap.Width) div 2, (Height - FBitmap.Height) div 2,
      FBitmap.Width, FBitmap.Height)
  else
    Result := Rect(0, 0, FBitmap.Width, FBitmap.Height);
end;

procedure TVrBitmapImage.AdjustBounds;
begin
  if (AutoSize) and (Align = alNone) then
    if (FBitmap.Width > 0) and (FBitmap.Height > 0) then
      SetBounds(Left, Top, FBitmap.Width, FBitmap.Height);
end;

procedure TVrBitmapImage.Paint;
begin
  FBitmap := GetBitmap;
  if FBitmap <> nil then AdjustBounds;
  ClearBitmapCanvas;
  if FBitmap <> nil then
    with BitmapCanvas do
    begin
      if Transparent then Brush.Style := bsClear
        else Brush.Style := bsSolid;
      BrushCopy(DestRect, FBitmap,
        BitmapRect(FBitmap), Self.Color);
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

procedure TVrBitmapImage.SetAutoSize(Value: Boolean);
begin
  if FAutoSize <> Value then
  begin
    FAutoSize := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapImage.SetCenter(Value: Boolean);
begin
  if FCenter <> Value then
  begin
    FCenter := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapImage.SetStretch(Value: Boolean);
begin
  if FStretch <> Value then
  begin
    FStretch := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBitmapImage.SetImageIndex(Value: Integer);
begin
  if FImageIndex <> Value then
  begin
    FImageIndex := Value;
    UpdateControlCanvas;
  end;
end;

{ TVrCounter }

constructor TVrCounter.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 150;
  Height := 25;
  Color := clBtnFace;
  ParentColor := false;
  Transparent := false;
  FValue := 0;
  FDigits := 8;
  FAutoSize := True;
  FSpacing := 0;
  FStretch := false;
  FBitmap := TBitmap.Create;
  FBitmap.OnChange := BitmapChanged;
  FImage := TBitmap.Create;
end;

destructor TVrCounter.Destroy;
begin
  FImage.Free;
  FBitmap.Free;
  inherited Destroy;
end;

procedure TVrCounter.Changed;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrCounter.BitmapChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrCounter.Paint;
var
  str: string;
  I, V, MidX, MidY: Integer;
begin
  CalcPaintParams;
  ClearBitmapCanvas;

  with FImage, FImage.Canvas do
  begin
    Brush.Color := Self.Color;
    Brush.Style := bsSolid;
    FillRect(Bounds(0, 0, Width, Height));
  end;

  MidX := 0;
  MidY := 0;
  if not Bitmap.Empty then
  begin
    str := Format('%.' + IntToStr(Digits) + 'd', [Value]);
    for I := 1 to Length(str) do
    begin
      V := StrToInt(str[I]);
      FImage.Canvas.BrushCopy(Bounds(MidX, MidY, FDigitSize.X, FDigitSize.Y),
        Bitmap, Bounds(V * FDigitSize.X, 0, FDigitSize.X, FDigitSize.Y),
        Self.Color);
      Inc(MidX, FSpacing + FDigitSize.X);
    end;
  end;

  if Transparent then BitmapCanvas.Brush.Style := bsClear
    else BitmapCanvas.Brush.Style := bsSolid;

  if (Stretch) and (not AutoSize) then
    BitmapCanvas.BrushCopy(ClientRect, FImage,
      BitmapRect(FImage), Self.Color)
  else
  begin
    MidX := (ClientWidth - FImage.Width) div 2;
    MidY := (ClientHeight - FImage.Height) div 2;
    BitmapCanvas.BrushCopy(Bounds(MidX, MidY, FImage.Width, FImage.Height),
      FImage, BitmapRect(FImage), Self.Color);
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

procedure TVrCounter.CalcPaintParams;
begin
  if not Bitmap.Empty then
  begin
    FDigitSize.X := Bitmap.Width div 10;
    FDigitSize.Y := Bitmap.Height;
    FImage.Width := (Spacing * Pred(Digits)) + (FDigitSize.X * Digits);
    FImage.Height := Bitmap.Height;
    if AutoSize then
      BoundsRect := Bounds(Left, Top, FImage.Width, FImage.Height);
  end;
end;

function TVrCounter.GetPalette: HPalette;
begin
  if FBitmap.Empty then Result := inherited GetPalette
  else Result := FBitmap.Palette;
end;

procedure TVrCounter.SetValue(Value: TVrCounterValue);
begin
  if FValue <> Value then
  begin
    FValue := Value;
    UpdateControlCanvas;
    Changed;
  end;
end;

procedure TVrCounter.SetDigits(Value: TVrCounterDigits);
begin
  if FDigits <> Value then
  begin
    FDigits := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCounter.SetAutoSize(Value: Boolean);
begin
  if FAutoSize <> Value then
  begin
    FAutoSize := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCounter.SetBitmap(Value: TBitmap);
begin
  FBitmap.Assign(Value);
end;

procedure TVrCounter.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCounter.SetStretch(Value: Boolean);
begin
  if FStretch <> Value then
  begin
    FStretch := Value;
    UpdateControlCanvas;
  end;
end;



end.
