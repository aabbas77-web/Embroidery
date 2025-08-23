{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrScanner;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils, VrThreads;

type
  TVrLedStyle = (lsRaised, lsLowered, lsNone, lsFlat);

  TVrLedGroup = class(TVrGraphicImageControl)
  private
    FSpacing: Integer;
    FStyle: TVrLedStyle;
    FPlainColors: Boolean;
    FOnChange: TNotifyEvent;
    Collection: TVrCollection;
    procedure SetSpacing(Value: Integer);
    procedure SetStyle(Value: TVrLedStyle);
    procedure SetPlainColors(Value: Boolean);
  protected
    procedure Change; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Spacing: Integer read FSpacing write SetSpacing default 2;
    property Style: TVrLedStyle read FStyle write SetStyle default lsRaised;
    property PlainColors: Boolean read FPlainColors write SetPlainColors default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  end;

  TVrScanDirection = (sdBoth, sdLeftRight, sdRightLeft);

  TVrScanner = class;

  TVrScannerLed = class(TVrCollectionItem)
  private
    FActive: Boolean;
    procedure SetActive(Value: Boolean);
  public
    constructor Create(Collection: TVrCollection); override;
    property Active: Boolean read FActive write SetActive;
  end;

  TVrScannerLeds = class(TVrCollection)
  private
    FOwner: TVrScanner;
    function GetItem(Index: Integer): TVrScannerLed;
  protected
    procedure Update(Item: TVrCollectionItem); override;
  public
    constructor Create(AOwner: TVrScanner);
    property Items[Index: Integer]: TVrScannerLed read GetItem;
  end;

  TVrScanner = class(TVrLedGroup)
  private
    FLeds: Integer;
    FPalette: TVrPalette;
    FActive: Boolean;
    FPosition: Integer;
    FDirection: TVrScanDirection;
    FThreaded: Boolean;
    ToLeft: Boolean;
    PrevPosition: Integer;
    FTimer: TVrTimer;
    function GetTimeInterval: Integer;
    procedure SetLeds(Value: Integer);
    procedure SetActive(Value: Boolean);
    procedure SetTimeInterval(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetPalette(Value: TVrPalette);
    procedure SetThreaded(Value: Boolean);
    procedure TimerEvent(Sender: TObject);
    procedure PaletteModified(Sender: TObject);
  protected
    procedure CreateItems;
    procedure UpdateLed(Index: Integer);
    procedure UpdateLeds;
    procedure UpdateLedState;
    procedure Paint; override;
    procedure GetItemRect(Index: Integer; var R: TRect);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Leds: Integer read FLeds write SetLeds default 7;
    property Palette: TVrPalette read FPalette write SetPalette;
    property Active: Boolean read FActive write SetActive default false;
    property Direction: TVrScanDirection read FDirection write FDirection default sdBoth;
    property TimeInterval: Integer read GetTimeInterval write SetTimeInterval default 100;
    property Position: Integer read FPosition write SetPosition default 0;
    property Spacing;
    property Style;
    property PlainColors;
    property Transparent default false;
    property OnChange;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
    property ParentColor;
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

  TVrIndicator = class;

  TVrIndicatorLed = class(TVrScannerLed)
  private
    FColorLow: TColor;
    FColorHigh: TColor;
  public
    constructor Create(Collection: TVrCollection); override;
    property ColorLow: TColor read FColorLow write FColorLow;
    property ColorHigh: TColor read FColorHigh write FColorHigh;
  end;

  TVrIndicatorLeds = class(TVrCollection)
  private
    FOwner: TVrIndicator;
    function GetItem(Index: Integer): TVrIndicatorLed;
  protected
    procedure Update(Item: TVrCollectionItem); override;
  public
    constructor Create(AOwner: TVrIndicator);
    property Items[Index: Integer]: TVrIndicatorLed read GetItem;
  end;

  TVrIndicator = class(TVrLedGroup)
  private
    FPosition: Integer;
    FMax: Integer;
    FMin: Integer;
    FLedsLow: Integer;
    FLedsMedium: Integer;
    FLedsHigh: Integer;
    FPalette1: TVrPalette;
    FPalette2: TVrPalette;
    FPalette3: TVrPalette;
    Leds: Integer;
    function GetPercentDone: Longint;
    procedure SetPosition(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetMin(Value: Integer);
    procedure SetLedsLow(Value: Integer);
    procedure SetLedsMedium(Value: Integer);
    procedure SetLedsHigh(Value: Integer);
    procedure SetPalette1(Value: TVrPalette);
    procedure SetPalette2(Value: TVrPalette);
    procedure SetPalette3(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
  protected
    procedure CreateItems;
    procedure UpdateLed(Index: Integer);
    procedure UpdateLeds;
    procedure UpdatePosition;
    procedure Paint; override;
    procedure GetItemRect(Index: Integer; var R: TRect);
  public
    constructor Create(AOwner: TComponent); override;
    property PercentDone: Longint read GetPercentDone;
  published
    property Palette1: TVrPalette read FPalette1 write SetPalette1;
    property Palette2: TVrPalette read FPalette2 write SetPalette2;
    property Palette3: TVrPalette read FPalette3 write SetPalette3;
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property Position: Integer read FPosition write SetPosition default 0;
    property LedsLow: Integer read FLedsLow write SetLedsLow default 3;
    property LedsMedium: Integer read FLedsMedium write SetLedsMedium default 2;
    property LedsHigh: Integer read FLedsHigh write SetLedsHigh default 2;
    property Spacing;
    property Style;
    property PlainColors;
    property Transparent default false;
    property OnChange;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
    property ParentColor;
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


{ TVrLedGroup }

constructor TVrLedGroup.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 250;
  Height := 9;
  FSpacing := 2;
  FStyle := lsRaised;
  FPlainColors := false;
end;

destructor TVrLedGroup.Destroy;
begin
  Collection.Free;
  inherited Destroy;
end;

procedure TVrLedGroup.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLedGroup.SetStyle(Value: TVrLedStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLedGroup.SetPlainColors(Value: Boolean);
begin
  if FPlainColors <> Value then
  begin
    FPlainColors := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLedGroup.Change;
begin
  if Assigned(FOnChange) then
    FOnChange(Self);
end;

{ TVrScannerLed }

constructor TVrScannerLed.Create(Collection: TVrCollection);
begin
  FActive := false;
  inherited Create(Collection);
end;

procedure TVrScannerLed.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    Changed(false);
  end;
end;

{ VrScannerLeds }

constructor TVrScannerLeds.Create(AOwner: TVrScanner);
begin
  inherited Create;
  FOwner := AOwner;
end;

function TVrScannerLeds.GetItem(Index: Integer): TVrScannerLed;
begin
  Result := TVrScannerLed(inherited Items[Index]);
end;

procedure TVrScannerLeds.Update(Item: TVrCollectionItem);
begin
  if Item <> nil then
    FOwner.UpdateLed(Item.Index) else
    FOwner.UpdateLeds;
end;

{ TVrScanner }

constructor TVrScanner.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FLeds := 7;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FActive := false;
  FPosition := -1;
  FDirection := sdBoth;
  FThreaded := True;
  FTimer := TVrTimer.Create(Self);
  FTimer.Enabled := false;
  FTimer.Interval := 100;
  FTimer.OnTimer := TimerEvent;
  Collection := TVrScannerLeds.Create(Self);
  CreateItems;
end;

destructor TVrScanner.Destroy;
begin
  FPalette.Free;
  FTimer.Free;
  inherited Destroy;
end;

procedure TVrScanner.CreateItems;
var
  I: Integer;
begin
  Collection.Clear;
  for I := 0 to Pred(FLeds) do
    TVrScannerLed.Create(Collection);
end;

procedure TVrScanner.PaletteModified(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrScanner.UpdateLed(Index: Integer);
var
  R: TRect;
  AColor: TColor;
  Item: TVrScannerLed;
begin
  Item := TVrScannerLeds(Collection).Items[Index];
  AColor := FPalette.Colors[ord(Item.Active)];

  GetItemRect(Index, R);

  if not FPlainColors then
    DrawGradient(DestCanvas, R, AColor, clBlack, voVertical, 1)
  else
  begin
    DestCanvas.Brush.Color := AColor;
    DestCanvas.FillRect(R);
  end;

  case FStyle of
    lsRaised:
      begin
        DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
        if not FPlainColors then
          DrawOutline3D(DestCanvas, R, AColor, clBlack, 1)
        else
        begin
          if not Item.Active then
            DrawOutline3D(DestCanvas, R, FPalette.High, FPalette.Low, 1)
          else DrawOutline3D(DestCanvas, R, clBtnHighlight, FPalette.High, 1);
        end;
      end;
    lsLowered:
      begin
        DrawOutline3D(DestCanvas, R, clBtnShadow, clBtnHighlight, 1);
        DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
      end;
    lsFlat:
      DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
    lsNone:;
  end;
end;

procedure TVrScanner.UpdateLeds;
var
  I: Integer;
begin
  for I := 0 to Collection.Count - 1 do UpdateLed(I);
end;

procedure TVrScanner.Paint;
begin
  ClearBitmapCanvas;
  DestCanvas := BitmapCanvas;
  try
    UpdateLeds;
    inherited Paint;
  finally
    DestCanvas := Self.Canvas;
  end;
end;

procedure TVrScanner.GetItemRect(Index: Integer; var R: TRect);
var
  X, W, Gap: Integer;
begin
  Gap := Pred(FLeds) * FSpacing;
  W := (Width - Gap) div FLeds;
  X := (FLeds * W) + Gap;
  X := (Width - X) div 2;
  Inc(X, (W * Index) + (FSpacing * Index));
  R := Bounds(X, 0, W, Height);
end;

procedure TVrScanner.SetLeds(Value: Integer);
begin
  if FLeds <> Value then
  begin
    FLeds := Value;
    CreateItems;
    FPosition := -1;
    PrevPosition := -1;
    UpdateControlCanvas;
  end;
end;

function TVrScanner.GetTimeInterval: Integer;
begin
  Result := FTimer.Interval;
end;

procedure TVrScanner.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    if Designing then Exit;
    FTimer.Enabled := FActive;
  end;
end;

procedure TVrScanner.SetTimeInterval(Value: Integer);
begin
  FTimer.Interval := Value;
end;

procedure TVrScanner.SetPosition(Value: Integer);
begin
  if FPosition <> Value then
  begin
    FPosition := Value;
    UpdateLedState;
    Change;
  end;
end;

procedure TVrScanner.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;

procedure TVrScanner.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrScanner.UpdateLedState;
begin
  AdjustRange(FPosition, -1, Pred(FLeds));
  if PrevPosition <> -1 then
    TVrscannerLeds(Collection).Items[PrevPosition].Active := False;
  if FPosition <> -1 then
    TVrscannerLeds(Collection).Items[Position].Active := True;
  PrevPosition := FPosition;
end;

procedure TVrScanner.TimerEvent(Sender: TObject);
begin
  case FDirection of
    sdBoth:
      begin
        if (ToLeft) then
        begin
          if (FPosition > 0) then Position := Position - 1
          else ToLeft := false;
        end
       else
        begin
          if (FPosition < FLeds - 1) then Position := Position + 1
          else ToLeft := true;
        end;
      end;
    sdLeftRight:
      begin
        if (FPosition < FLeds - 1) then
          Position := Position + 1 else Position := 0;
      end;
    sdRightLeft:
      begin
        if FPosition > 0 then Position := Position - 1
        else Position := FLeds - 1;
      end;
  end;
end;

{ TVrIndicatorLed }

constructor TVrIndicatorLed.Create(Collection: TVrCollection);
begin
  FColorLow := clGreen;
  FColorHigh := clLime;
  inherited Create(Collection);
end;

{ TVrIndicatorLeds }

constructor TVrIndicatorLeds.Create(AOwner: TVrIndicator);
begin
  inherited Create;
  FOwner := AOwner;
end;

function TVrIndicatorLeds.GetItem(Index: Integer): TVrIndicatorLed;
begin
  Result := TVrIndicatorLed(inherited Items[Index]);
end;

procedure TVrIndicatorLeds.Update(Item: TVrCollectionItem);
begin
  if Item <> nil then
    FOwner.UpdateLed(Item.Index) else
    FOwner.UpdateLeds;
end;

{ TVrIndicator }

constructor TVrIndicator.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FMax := 100;
  FMin := 0;
  FLedsLow := 3;
  FLedsMedium := 2;
  FLedsHigh := 2;
  FPosition := 0;

  FPalette1 := TVrPalette.Create;
  FPalette1.OnChange := PaletteModified;

  FPalette2 := TVrPalette.Create;
  with FPalette2 do
  begin
    Low := clOlive;
    High := clYellow;
    OnChange := PaletteModified;
  end;

  FPalette3 := TVrPalette.Create;
  with FPalette3 do
  begin
    Low := clMaroon;
    High := clRed;
    OnChange := PaletteModified;
  end;

  Collection := TVrIndicatorLeds.Create(Self);
  CreateItems;
end;

procedure TVrIndicator.CreateItems;
var
  I: Integer;
  Item: TVrIndicatorLed;
begin
  Collection.Clear;
  Leds := FLedsLow + FLedsMedium + FLedsHigh;
  for I := 0 to Leds - 1 do
  begin
    Item := TVrIndicatorLed.Create(Collection);
    if I < FLedsLow then
    begin
      Item.ColorLow := Palette1[0];
      Item.ColorHigh := Palette1[1];
    end
    else
    if I < FLedsLow + FLedsMedium then
    begin
      Item.ColorLow := Palette2[0];
      Item.ColorHigh := Palette2[1];
    end
    else
    begin
      Item.ColorLow := Palette3[0];
      Item.ColorHigh := Palette3[1];
    end;
  end;
end;

procedure TVrIndicator.PaletteModified(Sender: TObject);
begin
  CreateItems;
  UpdateControlCanvas;
end;

procedure TVrIndicator.SetPalette1(Value: TVrPalette);
begin
  FPalette1.Assign(Value);
end;

procedure TVrIndicator.SetPalette2(Value: TVrPalette);
begin
  FPalette2.Assign(Value);
end;

procedure TVrIndicator.SetPalette3(Value: TVrPalette);
begin
  FPalette3.Assign(Value);
end;

procedure TVrIndicator.UpdatePosition;
var
  I, Ticks: Integer;
begin
  AdjustRange(FPosition, FMin, FMax);
  Ticks := SolveForX(PercentDone, Leds);
  for I := 0 to Leds - 1 do
    TVrIndicatorLeds(Collection).Items[I].Active := Succ(I) <= Ticks;
end;

procedure TVrIndicator.SetPosition(Value: Integer);
begin
  if FPosition <> Value then
  begin
    FPosition := Value;
    UpdatePosition;
    Change;
  end;
end;

procedure TVrIndicator.SetMax(Value: Integer);
begin
  if (FMax <> Value) and (Value > FMin) then
  begin
    FMax := Value;
    UpdatePosition;
  end;
end;

procedure TVrIndicator.SetMin(Value: Integer);
begin
  if (FMin <> Value) and (Value < FMax) then
  begin
    FMin := Value;
    UpdatePosition;
  end;
end;

procedure TVrIndicator.SetLedsLow(Value: Integer);
begin
  if FLedsLow <> Value then
  begin
    FLedsLow := Value;
    CreateItems;
    UpdateControlCanvas;
  end;
end;

procedure TVrIndicator.SetLedsMedium(Value: Integer);
begin
  if FLedsMedium <> Value then
  begin
    FLedsMedium := Value;
    CreateItems;
    UpdateControlCanvas;
  end;
end;

procedure TVrIndicator.SetLedsHigh(Value: Integer);
begin
  if FLedsHigh <> Value then
  begin
    FLedsHigh := Value;
    CreateItems;
    UpdateControlCanvas;
  end;
end;

function TVrIndicator.GetPercentDone: Longint;
begin
  Result := SolveForY(FPosition - FMin, FMax - FMin);
end;

procedure TVrIndicator.UpdateLed(Index: Integer);
var
  R: TRect;
  AColor: TColor;
  Item: TVrIndicatorLed;
begin
  Item := TVrIndicatorLeds(Collection).Items[Index];
  if Item.Active then AColor := Item.ColorHigh
                 else AColor := Item.ColorLow;

  GetItemRect(Index, R);

  if not FPlainColors then
    DrawGradient(DestCanvas, R, AColor, clBlack, voVertical, 1)
  else
  begin
    DestCanvas.Brush.Color := AColor;
    DestCanvas.FillRect(R);
  end;

  case FStyle of
    lsRaised:
      begin
        DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
        if not FPlainColors then
          DrawOutline3D(DestCanvas, R, AColor, clBlack, 1)
        else
        begin
          if not Item.Active then
            DrawOutline3D(DestCanvas, R, Item.ColorHigh, Item.ColorLow, 1)
          else DrawOutline3D(DestCanvas, R, clBtnHighlight, Item.ColorHigh, 1);
        end;
      end;
    lsLowered:
      begin
        DrawOutline3D(DestCanvas, R, clBtnShadow, clBtnHighlight, 1);
        DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
      end;
    lsFlat:
      DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
    lsNone:;
  end;
end;

procedure TVrIndicator.UpdateLeds;
var
  I: Integer;
begin
  for I := 0 to Collection.Count - 1 do UpdateLed(I);
end;

procedure TVrIndicator.Paint;
begin
  ClearBitmapCanvas;
  DestCanvas := BitmapCanvas;
  try
    UpdateLeds;
    inherited Paint;
  finally
    DestCanvas := Self.Canvas;
  end;
  UpdatePosition;
end;

procedure TVrIndicator.GetItemRect(Index: Integer; var R: TRect);
var
  X, W, Gap: Integer;
begin
  Gap := Pred(Leds) * FSpacing;
  W := (ClientWidth - Gap) div Leds;
  X := (Leds * W) + Gap;
  X := (ClientWidth - X) div 2;
  Inc(X, (W * Index) + (FSpacing * Index));
  R := Bounds(X, 0, W, ClientHeight);
end;


end.
