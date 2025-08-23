{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrLights;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;


type
  TVrLightsState = (lsGreen, lsYellow, lsRed);
  TVrLightsStates = set of TVrLightsState;
  TVrLightsVisible = set of TVrLightsState;
  TVrLightsOrder = (loGreenToRed, loRedToGreen);
  TVrLightsType = (ltGlassRounded, ltGlassRect, ltGlassSquare, ltGlassDiamond);
  TVrLightsImages = array[0..1] of TBitmap;

  TVrLights = class(TVrGraphicImageControl)
  private
    FLedState: TVrLightsStates;
    FSpacing: Integer;
    FOrder: TVrLightsOrder;
    FOrientation: TVrOrientation;
    FLedType: TVrLightsType;
    FNumLeds: Integer;
    FLedsVisible: TVrLightsVisible;
    FImages: TVrLightsImages;
    FImageWidth: Integer;
    FImageHeight: Integer;
    FOnChange: TNotifyEvent;
    procedure SetLedState(Value: TVrLightsStates);
    procedure SetSpacing(Value: Integer);
    procedure SetOrder(Value: TVrLightsOrder);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetLedsVisible(Value: TVrLightsVisible);
    procedure SetLedType(Value: TVrLightsType);
  protected
    procedure LoadBitmaps; virtual;
    procedure DrawLed(X, Y, Index: Integer; Active: Boolean);
    procedure DrawHori;
    procedure DrawVert;
    procedure Paint; override;
    procedure Change; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property LedState: TVrLightsStates read FLedState write SetLedState default [];
    property Spacing: Integer read FSpacing write SetSpacing default 5;
    property Order: TVrLightsOrder read FOrder write SetOrder default loGreenToRed;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property LedsVisible: TVrLightsVisible read FLedsVisible write SetLedsVisible default [lsGreen, lsYellow, lsRed];
    property LedType: TVrLightsType read FLedType write SetLedType default ltGlassRect;
    property Transparent default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
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


implementation

{$R VRLIGHTS.D32}

const
  ResId: array[TVrLightsType] of PChar =
    ('RND', 'RECT', 'SQR', 'DMD');

{TVrLights}

constructor TVrLights.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 80;
  Height := 45;
  ParentColor := false;
  Color := clBlack;
  FSpacing := 5;
  FOrder := loGreenToRed;
  FOrientation := voHorizontal;
  FNumLeds := 3;
  FLedsVisible := [lsGreen, lsYellow, lsRed];
  FLedType := ltGlassRect;
  AllocateBitmaps(FImages);
  LoadBitmaps;
end;

destructor TVrLights.Destroy;
begin
  DeallocateBitmaps(FImages);
  inherited Destroy;
end;

procedure TVrLights.LoadBitmaps;
var
  ResName: array[0..40] of Char;
begin
  FImages[0].Handle := LoadBitmap(HInstance,
    StrFmt(ResName, 'LIGHTS_%s_%s', [ResId[FLedType], 'OFF']));
  FImages[1].Handle := LoadBitmap(hInstance,
    StrFmt(ResName, 'LIGHTS_%s_%s', [ResId[FLedType], 'ON']));
  FImageWidth := FImages[0].Width div 3;
  FImageHeight := FImages[0].Height;
end;

procedure TVrLights.SetLedState(Value: TVrLightsStates);
begin
  if FLedState <> Value then
  begin
    FLedState := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrLights.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLights.SetOrder(Value: TVrLightsOrder);
begin
  if FOrder <> Value then
  begin
    FOrder := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLights.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrLights.SetLedsVisible(Value: TVrLightsVisible);
var
  I: Integer;
begin
  if FLedsVisible <> Value then
  begin
    FLedsVisible := Value;
    FNumLeds := 0;
    for I := 0 to 2 do
      if TVrLightsState(I) in Value then Inc(FNumLeds);
    UpdateControlCanvas;
  end;
end;

procedure TVrLights.SetLedType(Value: TVrLightsType);
begin
  if FLedType <> Value then
  begin
    FLedType := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrLights.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrLights.DrawLed(X, Y, Index: Integer; Active: Boolean);
var
  D, R: TRect;
begin
  with BitmapCanvas do
  begin
    Brush.Style := bsClear;
    D := Bounds(X, Y, FImageWidth, FImageHeight);
    R := Bounds(Index * FImageWidth, 0, FImageWidth, FImageHeight);
    BrushCopy(D, FImages[ord(Active)], R, clBlack);
  end;
end;

procedure TVrLights.DrawHori;
var
  X, Y, I: Integer;
begin
  X := (FNumLeds * FImageWidth) + (Pred(FNumLeds) * FSpacing);
  X := (ClientWidth - X) div 2;
  Y := (ClientHeight - FImageHeight) div 2;
  case FOrder of
    loGreenToRed:
      for I := 0 to 2 do
      begin
        if not (TVrLightsState(I) in FLedsVisible) then
          Continue;
        DrawLed(X, Y, I, TVrLightsState(I) in FLedState);
        Inc(X, FImageWidth + FSpacing);
      end;
    loRedToGreen:
      for I := 2 downto 0 do
      begin
        if not (TVrLightsState(I) in FLedsVisible) then
          Continue;
        DrawLed(X, Y, I, TVrLightsState(I) in FLedState);
        Inc(X, FImageWidth + FSpacing);
      end;
  end;
end;

procedure TVrLights.DrawVert;
var
  X, Y, I: Integer;
begin
  X := (ClientWidth - FImageWidth) div 2;
  Y := (FNumLeds * FImageHeight) + (Pred(FNumLeds) * FSpacing);
  Y := (ClientHeight - Y) div 2;

  case FOrder of
    loGreenToRed:
      for I := 0 to 2 do
      begin
        if not (TVrLightsState(I) in FLedsVisible) then
          Continue;
        DrawLed(X, Y, I, TVrLightsState(I) in FLedState);
        Inc(Y, FImageHeight + FSpacing);
      end;
    loRedToGreen:
      for I := 2 downto 0 do
      begin
        if not (TVrLightsState(I) in FLedsVisible) then
          Continue;
        DrawLed(X, Y, I, TVrLightsState(I) in FLedState);
        Inc(Y, FImageHeight + FSpacing);
      end;
  end;
end;

procedure TVrLights.Paint;
begin
  ClearBitmapCanvas;
  if FOrientation = voHorizontal then
    DrawHori else DrawVert;
  inherited Paint;
end;


end.

