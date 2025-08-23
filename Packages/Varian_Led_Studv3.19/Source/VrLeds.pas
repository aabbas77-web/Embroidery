{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrLeds;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrLedType = (ltRounded, ltRectangle, ltLargeRect);
  TVrLedDrawStyle = (dsDesign, dsCustom);
  TVrCustomLed = class(TVrGraphicImageControl)
  private
    FLedType: TVrLedType;
    FPalette: TVrPalette;
    FActive: Boolean;
    FSpacing: Integer;
    FMargin: Integer;
    FLayout: TVrImageTextLayout;
    FGlyphs: TBitmap;
    FDrawStyle: TVrLedDrawStyle;
    FOnChange: TNotifyEvent;
    FImageRect: TRect;
    FTextBounds: TRect;
    FBitmap: TBitmap;
    procedure SetActive(Value: Boolean);
    procedure SetLedType(Value: TVrLedType);
    procedure SetLayout(Value: TVrImageTextLayout);
    procedure SetMargin(Value: Integer);
    procedure SetSpacing(Value: Integer);
    procedure SetPalette(Value: TVrPalette);
    procedure SetGlyphs(Value: TBitmap);
    procedure SetDrawStyle(Value: TVrLedDrawStyle);
    procedure PaletteModified(Sender: TObject);
    procedure GlyphsChanged(Sender: TObject);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
  protected
    procedure LoadBitmaps; virtual;
    procedure Paint; override;
    procedure CalcPaintParams;
    procedure Changed; dynamic;
    function GetPalette: HPalette; override;
    property Active: Boolean read FActive write SetActive default false;
    property Palette: TVrPalette read FPalette write SetPalette;
    property LedType: TVrLedType read FLedType write SetLedType default ltRounded;
    property Layout: TVrImageTextLayout read FLayout write SetLayout default ImageLeft;
    property Margin: Integer read FMargin write SetMargin default -1;
    property Spacing: Integer read FSpacing write SetSpacing default 5;
    property Glyphs: TBitmap read FGlyphs write SetGlyphs;
    property DrawStyle: TVrLedDrawStyle read FDrawStyle write SetDrawStyle default dsDesign;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

  TVrLed = class(TVrCustomLed)
  published
    property Active;
    property Palette;
    property LedType;
    property Layout;
    property Margin;
    property Spacing;
    property Transparent default false;
    property DrawStyle;
    property Glyphs;
    property OnChange;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property BiDiMode;
    property Constraints;
{$ENDIF}
    property Caption;
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Font;
    property Hint;
{$IFDEF VER110}
    property ParentBiDiMode;
{$ENDIF}
    property ParentColor;
    property ParentFont;
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

  TVrUserLedDrawEvent = procedure(Sender: TObject; Canvas: TCanvas;
    Rect: TRect) of object;

  TVrUserLed = class(TVrGraphicControl)
  private
    FBevel: TVrBevel;
    FPalette: TVrPalette;
    FActive: Boolean;
    FOutlineColor: TColor;
    FOutlineWidth: Integer;
    FDrawStyle: TVrDrawStyle;
    FOnChange: TNotifyEvent;
    FOnDraw: TVrUserLedDrawEvent;
    procedure SetActive(Value: Boolean);
    procedure SetOutlineColor(Value: TColor);
    procedure SetOutlineWidth(Value: Integer);
    procedure SetDrawStyle(Value: TVrDrawStyle);
    procedure SetPalette(Value: TVrPalette);
    procedure SetBevel(Value: TVrBevel);
    procedure PaletteModified(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
  protected
    procedure Change; dynamic;
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Palette: TVrPalette read FPalette write SetPalette;
    property Active: Boolean read FActive write SetActive default false;
    property OutlineColor: TColor read FOutlineColor write SetOutlineColor default clBlack;
    property OutlineWidth: Integer read FOutlineWidth write SetOutlineWidth default 0;
    property DrawStyle: TVrDrawStyle read FDrawStyle write SetDrawStyle default dsNormal;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property OnDraw: TVrUserLedDrawEvent read FOnDraw write FOnDraw;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
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

{$R VRLEDS.D32}

const
  LedTypeName: array[TVrLedType] of PChar = ('RND', 'RECT', 'BIG');

{TVrCustomLed}

constructor TVrCustomLed.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable,
    csClickEvents] - [csDoubleClicks, csSetCaption];
  Width := 25;
  Height := 25;
  ParentColor := false;
  Color := clBlack;
  Font.Color := clWhite;
  FActive := false;
  FLedType := ltRounded;
  FSpacing := 5;
  FMargin := -1;
  FLayout := ImageLeft;
  FPalette := TVrPalette.Create;
  with FPalette do
  begin
    Low := clMaroon;
    High := clRed;
    OnChange := PaletteModified;
  end;

  FDrawStyle := dsDesign;

  FGlyphs := TBitmap.Create;
  FGlyphs.OnChange := GlyphsChanged;

  FBitmap := TBitmap.Create;

  LoadBitmaps;
end;

destructor TVrCustomLed.Destroy;
begin
  FPalette.Free;
  FGlyphs.Free;
  FBitmap.Free;
  inherited Destroy;
end;

procedure TVrCustomLed.LoadBitmaps;
var
  ResName: array[0..40] of Char;
begin
  if DrawStyle = dsDesign then
  begin
    FBitmap.Handle := LoadBitmap(hInstance,
      StrFmt(ResName, 'LI_%s', [LedTypeName[FLedType]]));
    FPalette.ToBMP(FBitmap, clMaroon, clRed);
  end else FBitmap.Assign(FGlyphs);
end;

function TVrCustomLed.GetPalette: HPalette;
begin
  Result := FBitmap.Palette;
end;

procedure TVrCustomLed.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

procedure TVrCustomLed.GlyphsChanged(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

procedure TVrCustomLed.Changed;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrCustomLed.CMTextChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrCustomLed.Paint;
var
  Offset: Integer;
  ImageWidth: Integer;
  TransparentColor: TColor;
begin
  ClearBitmapCanvas;
  CalcPaintParams;
  ImageWidth := FBitmap.Width div 2;
  Offset := ImageWidth * ord(FActive);

  with BitmapCanvas do
  begin
    Brush.Style := bsClear;
    if DrawStyle = dsDesign then TransparentColor := clBlack
    else TransparentColor := Self.Color;
    BrushCopy(FImageRect, FBitmap,
      Bounds(Offset, 0, ImageWidth, FBitmap.Height), TransparentColor);

    Font := Self.Font;
    DrawText(Handle, PChar(Caption), Length(Caption), FTextBounds,
      DT_LEFT or DT_VCENTER or DT_SINGLELINE);
  end;

  inherited Paint;
end;

procedure TVrCustomLed.CalcPaintParams;
var
  Offset, ImagePos: TPoint;
begin
  Canvas.Font.Assign(Self.Font);
  Offset := Point(0,0);
  CalcImageTextLayout(Canvas, ClientRect, Offset, Caption, FLayout,
    FMargin, FSpacing, Point(FBitmap.Width div 2, FBitmap.Height),
    ImagePos, FTextBounds);
  FImageRect := Bounds(ImagePos.X, ImagePos.Y,
    FBitmap.Width div 2, FBitmap.Height);
end;

procedure TVrCustomLed.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    UpdateControlCanvas;
    Changed;
  end;
end;

procedure TVrCustomLed.SetLedType(Value: TVrLedType);
begin
  if FLedType <> Value then
  begin
    FLedType := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomLed.SetLayout(Value: TVrImageTextLayout);
begin
  if FLayout <> Value then
  begin
    FLayout := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomLed.SetMargin(Value: Integer);
begin
  if FMargin <> Value then
  begin
    FMargin := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomLed.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomLed.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrCustomLed.SetGlyphs(Value: TBitmap);
begin
  FGlyphs.Assign(Value);
end;

procedure TVrCustomLed.SetDrawStyle(Value: TVrLedDrawStyle);
begin
  if FDrawStyle <> Value then
  begin
    FDrawStyle := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

{ TVrUserLed }

constructor TVrUserLed.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable] -
    [csSetCaption, csDoubleClicks];
  Width := 20;
  Height := 10;
  FActive := false;
  FOutlineColor := clBlack;
  FOutlineWidth := 0;
  FDrawStyle := dsNormal;
  FPalette := TVrPalette.Create;
  with FPalette do
  begin
    Low := clMaroon;
    High := clRed;
    OnChange := PaletteModified;
  end;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsNone;
    InnerHighlight := clLime;
    InnerShadow := clGreen;
    OnChange := BevelChanged;
  end;
end;

destructor TVrUserLed.Destroy;
begin
  FPalette.Free;
  FBevel.Free;
  inherited Destroy;
end;

procedure TVrUserLed.PaletteModified(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrUserLed.BevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrUserLed.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrUserLed.Paint;
var
  R: TRect;
begin
  if FDrawStyle = dsOwnerDraw then
  begin
    ClearClientCanvas;
    if Assigned(FOnDraw) then
      FOnDraw(Self, Canvas, ClientRect);
    Exit;
  end;

  R := ClientRect;
  if FOutlineWidth > 0 then
    DrawFrame3D(Canvas, R, FOutlineColor, FOutlineColor, FOutlineWidth);

  FBevel.Paint(Canvas, R);

  with inherited Canvas do
  begin
    Brush.Color := FPalette.Colors[ord(FActive)];
    FillRect(R);
  end;
end;

procedure TVrUserLed.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrUserLed.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrUserLed.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrUserLed.SetOutlineColor(Value: TColor);
begin
  if FOutlineColor <> Value then
  begin
    FOutlineColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrUserLed.SetDrawStyle(Value: TVrDrawStyle);
begin
  if FDrawStyle <> Value then
  begin
    FDrawStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrUserLed.SetOutlineWidth(Value: Integer);
begin
  if FOutlineWidth <> Value then
  begin
    FOutlineWidth := Value;
    UpdateControlCanvas;
  end;
end;


end.
