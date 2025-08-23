{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrArrow;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrClasses, VrControls, VrSysUtils;

type
  TVrArrowDirection = (pdLeft, pdRight, pdUp, pdDown);

  TVrArrow = class(TVrGraphicImageControl)
  private
    FDirection: TVrArrowDirection;
    FPalette: TVrPalette;
    FActive: Boolean;
    FTrackMouse: Boolean;
    Glyphs: TBitmap;
    GlyphMask: TBitmap;
    HasMouse: Boolean;
    function ImageRect: TRect;
    function InControl(X, Y: Integer): Boolean;
    procedure SetActive(Value: Boolean);
    procedure SetDirection(Value: TVrArrowDirection);
    procedure SetPalette(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
  protected
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure LoadBitmaps; virtual;
    procedure Paint; override;
    function GetPalette: HPalette; override;
  public
    constructor Create(Aowner: TComponent); override;
    destructor Destroy; override;
  published
    property Active: Boolean read FActive write SetActive default false;
    property Direction: TVrArrowDirection read FDirection write SetDirection default pdUp;
    property Palette: TVrPalette read FPalette write SetPalette;
    property TrackMouse: Boolean read FTrackMouse write FTrackMouse default false;
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

{$R VRARROW.D32}

const
  ResId: array[TVrArrowDirection] of PChar =
    ('LEFTARROW', 'RIGHTARROW', 'UPARROW', 'DOWNARROW');

{TVrArrow}

constructor TVrArrow.Create(Aowner: TComponent);
begin
  inherited Create(Aowner);
  ControlStyle := ControlStyle + [csOpaque] - [csDoubleClicks];
  Width := 50;
  Height := 45;
  ParentColor := false;
  Color := clBlack;
  FActive := false;
  FDirection := pdUp;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  Glyphs := TBitmap.Create;
  GlyphMask := TBitmap.Create;
  HasMouse := false;
  LoadBitmaps;
end;

destructor TVrArrow.Destroy;
begin
  FPalette.Free;
  Glyphs.Free;
  GlyphMask.Free;
  inherited Destroy;
end;

procedure TVrArrow.LoadBitmaps;
begin
  Glyphs.Handle := LoadBitmap(hInstance, ResId[FDirection]);
  GlyphMask.Assign(Glyphs);
  GlyphMask.Mask(clWhite);
  FPalette.ToBMP(Glyphs, clGreen, clLime);
end;

function TVrArrow.GetPalette: HPalette;
begin
  Result := Glyphs.Palette;
end;

procedure TVrArrow.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrArrow.SetDirection(Value: TVrArrowDirection);
begin
  if FDirection <> Value then
  begin
    FDirection := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrArrow.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

procedure TVrArrow.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrArrow.Paint;
var
  GlyphRect: TRect;
  Index, W, H: Integer;
begin
  ClearBitmapCanvas;

  if FTrackMouse then Active := HasMouse;

  Index := Ord(FActive);
  with BitmapCanvas do
  begin
    Brush.Style := bsClear;
    W := Glyphs.Width div 2;
    H := Glyphs.Height;
    GlyphRect := Bounds(Index * W, 0, W, H);
    BrushCopy(ImageRect, Glyphs, GlyphRect, clWhite);
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

function TVrArrow.ImageRect: TRect;
var
  X, Y, W, H: Integer;
begin
  W := Glyphs.Width div 2;
  H := Glyphs.Height;
  X := (Width - W) div 2;
  Y := (Height - W) div 2;
  Result := Bounds(X, Y, W, H);
end;

function TVrArrow.InControl(X, Y: Integer): Boolean;
var
  R: TRect;
  Px, Py: Integer;
begin
  R := ImageRect;
  Px := R.Right - X - 1;
  Py := R.Bottom - Y - 1;
  Result := (PtInRect(R, Point(X, Y))) and
            (GlyphMask.Canvas.Pixels[Px, Py] = clBlack);
end;

procedure TVrArrow.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited;
  if FTrackMouse then
  begin
    HasMouse := InControl(X, Y);
    UpdateControlCanvas;
  end;
end;

procedure TVrArrow.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  if TrackMouse then
  begin
    HasMouse := false;
    UpdateControlCanvas;
  end;
end;


end.
