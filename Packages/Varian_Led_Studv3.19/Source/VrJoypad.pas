{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrJoypad;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrConst, VrClasses, VrControls, VrSysUtils;

type
  TVrJoypadDirection = (jdNone, jdUp, jdDown, jdLeft, jdRight);

  TVrVisibleArrow = (vaUp, vaDown, vaLeft, vaRight);
  TVrVisibleArrows = set of TVrVisibleArrow;

  TVrJoypad = class(TVrGraphicImageControl)
  private
    FSpacing: Integer;
    FDirection: TVrJoypadDirection;
    FVisibleArrows: TVrVisibleArrows;
    FPalette: TVrPalette;
    ImageWidth: Integer;
    ImageHeight: Integer;
    Bitmaps: array[0..1] of TBitmap;
    procedure SetSpacing(Value: Integer);
    procedure SetDirection(Value: TVrJoypadDirection);
    procedure SetVisibleArrows(Value: TVrVisibleArrows);
    procedure SetPalette(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
  protected
    procedure LoadBitmaps; virtual;
    procedure DestroyBitmaps;
    procedure UpdateLed(Index: TVrVisibleArrow; Active: Boolean);
    procedure UpdateLeds;
    procedure Paint; override;
    function GetPalette: HPalette; override;
    procedure GetImageRect(Index: TVrVisibleArrow; var R: TRect);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Spacing: Integer read FSpacing write SetSpacing default 4;
    property Direction: TVrJoypadDirection read FDirection write SetDirection default jdNone;
    property VisibleArrows: TVrVisibleArrows read FVisibleArrows write SetVisibleArrows default [vaUp, vaDown, vaLeft, vaRight];
    property Palette: TVrPalette read FPalette write SetPalette;
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

{$R VRJOYPAD.D32}

const
  ResName: array[0..1] of PChar = ('IMAGESOFF', 'IMAGESON');

{TVrJoypad}

constructor TVrJoypad.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 55;
  Height := 55;
  ParentColor := false;
  Color := clBlack;
  FSpacing := 4;
  FDirection := jdNone;
  FVisibleArrows := [vaLeft, vaRight, vaUp, vaDown];
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  LoadBitmaps;
end;

destructor TVrJoypad.Destroy;
begin
  FPalette.Free;
  DestroyBitmaps;
  inherited Destroy;
end;

procedure TVrJoypad.LoadBitmaps;
var
  I: Integer;
begin
  for I := 0 to 1 do
  begin
    if not Assigned(Bitmaps[I]) then
      Bitmaps[I] := TBitmap.Create;
    Bitmaps[I].Handle := LoadBitmap(hInstance, ResName[I]);
    FPalette.ToBMP(Bitmaps[I], ResColorLow, ResColorHigh);
  end;
  ImageWidth := Bitmaps[0].Width div 4;
  ImageHeight := Bitmaps[0].Height;
end;

procedure TVrJoypad.DestroyBitmaps;
var
  I: Integer;
begin
  for I := 0 to 1 do Bitmaps[I].Free;
end;

function TVrJoypad.GetPalette: HPalette;
begin
  Result := BitmapImage.Palette;
end;

procedure TVrJoypad.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrJoypad.SetSpacing(Value: Integer);
begin
  if (FSpacing <> Value) and (Value >= 0) then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrJoypad.SetDirection(Value: TVrJoypadDirection);
begin
  if FDirection <> Value then
  begin
    FDirection := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrJoypad.SetVisibleArrows(Value: TVrVisibleArrows);
begin
  if FVisibleArrows <> Value then
  begin
    FVisibleArrows := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrJoypad.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

procedure TVrJoypad.UpdateLed(Index: TVrVisibleArrow; Active: Boolean);
var
  R, Source: TRect;
begin
  with DestCanvas do
  begin
    GetImageRect(Index, R);
    Source := Bounds(ord(Index) * ImageWidth, 0, ImageWidth, ImageHeight);
    Brush.Style := bsClear;
    BrushCopy(R, Bitmaps[ord(Active)], Source, clBlack);
  end;
end;

procedure TVrJoyPad.UpdateLeds;
var
  I: TVrVisibleArrow;
  Dir: TVrJoypadDirection;
begin
  Dir := jdUp;
  for I := Low(TVrVisibleArrow) to High(TVrVisibleArrow) do
  begin
    if I in VisibleArrows then
      UpdateLed(I, FDirection = Dir);
    Inc(Dir);
  end;
end;

procedure TVrJoypad.Paint;
begin
  ClearBitmapCanvas;
  DestCanvas := BitmapCanvas;
  try
    UpdateLeds;
  finally
    DestCanvas := Self.Canvas;
  end;
  inherited Paint;
end;

procedure TVrJoypad.GetImageRect(Index: TVrVisibleArrow; var R: TRect);
var
  X, Y: Integer;
begin
  X := (Width - ImageWidth) div 2;
  Y := (Height - ImageHeight) div 2;
  case Index of
    vaUp: Y := Y - (ImageHeight div 2) - 3 - FSpacing;
    vaDown: Y := Y + (ImageHeight div 2) + 3 + FSpacing;
    vaLeft: X := X - (ImageWidth div 2) - 3 - FSpacing;
    vaRight: X := X + (ImageWidth div 2) + 3 + FSpacing;
  end;
  R := Bounds(X, Y, ImageWidth, ImageHeight);
end;

end.
