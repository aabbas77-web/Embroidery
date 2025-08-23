{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrHotImage;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrConst, VrClasses, VrControls, VrSysUtils;

type
  TVrHotRect = class(TVrPersistent)
  private
    FColor: TColor;
    FWidth: Integer;
    FVisible: Boolean;
    procedure SetColor(Value: TColor);
    procedure SetWidth(Value: Integer);
    procedure SetVisible(Value: Boolean);
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
  published
    property Color: TColor read FColor write SetColor default clYellow;
    property Width: Integer read FWidth write SetWidth default 1;
    property Visible: Boolean read FVisible write SetVisible default True;
  end;

  TVrHotImageDrawStyle = (dsCenter, dsStretch);
  TVrHotImage = class(TVrHyperLinkControl)
  private
    FImageLeave: TBitmap;
    FImageEnter: TBitmap;
    FColorEnter: TColor;
    FColorLeave: TColor;
    FDrawStyle: TVrHotImageDrawStyle;
    FTextAlignment: TVrTextAlignment;
    FHotRect: TVrHotRect;
    FHasMouse: Boolean;
    procedure SetImageLeave(Value: TBitmap);
    procedure SetImageEnter(Value: TBitmap);
    procedure SetColorEnter(Value: TColor);
    procedure SetColorLeave(Value: TColor);
    procedure SetDrawStyle(Value: TVrHotImageDrawStyle);
    procedure SetTextAlignment(Value: TVrTextAlignment);
    procedure SetHotRect(Value: TVrHotRect);
    procedure BitmapChanged(Sender: TObject);
    procedure HotRectChanged(Sender: TObject);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;
  protected
    procedure MouseEnter; override;
    procedure MouseLeave; override;
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property ImageLeave: TBitmap read FImageLeave write SetImageLeave;
    property ImageEnter: TBitmap read FImageEnter write SetImageEnter;
    property ColorEnter: TColor read FColorEnter write SetColorEnter default clBlue;
    property ColorLeave: TColor read FColorLeave write SetColorLeave default clBlack;
    property DrawStyle: TVrHotImageDrawStyle read FDrawStyle write SetDrawStyle default dsCenter;
    property TextAlignment: TVrTextAlignment read FTextAlignment write SetTextAlignment default vtaBottom;
    property HotRect: TVrHotRect read FHotRect write SetHotRect;
    property Transparent default false;
    property OnMouseEnter;
    property OnMouseLeave;
    property Align;
{$IFDEF VER110}
    property Anchors;
    property BiDiMode;
    property Constraints;
{$ENDIF}
    property Caption;
    property DragCursor;
    property DragMode;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property Enabled;
    property Font;
    property ParentShowHint;
{$IFDEF VER110}
    property ParentBiDiMode;
{$ENDIF}
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


{ TVrHotRect }

constructor TVrHotRect.Create;
begin
  inherited Create;
  FColor := clYellow;
  FWidth := 1;
  FVisible := True;
end;

procedure TVrHotRect.SetColor(Value: TColor);
begin
  if FColor <> Value then
  begin
    FColor :=  Value;
    Changed;
  end;
end;

procedure TVrHotRect.SetWidth(Value: Integer);
begin
  if FWidth <> Value then
  begin
    FWidth :=  Value;
    Changed;
  end;
end;

procedure TVrHotRect.SetVisible(Value: Boolean);
begin
  if FVisible <> Value then
  begin
    FVisible := Value;
    Changed;
  end;
end;

procedure TVrHotRect.Assign(Source: TPersistent);
begin
  if Source is TVrHotRect then
  begin
    BeginUpdate;
    try
      Color := TVrHotRect(Source).Color;
      Width := TVrHotRect(Source).Width;
      Visible := TVrHotRect(Source).Visible;
    finally
      EndUpdate;
    end;
    Exit;
  end;
  inherited Assign(Source);
end;

{ TVrHotImage }

constructor TVrHotImage.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csDoubleClicks];
  Width := 85;
  Height := 85;
  Color := clBlack;
  Font.Name := 'Arial';
  Font.Style := Font.Style + [fsBold];
  Font.Color := clWhite;
  Transparent := false;
  FColorEnter := clBlue;
  FColorLeave := clBlack;
  FDrawStyle := dsCenter;
  FTextAlignment := vtaBottom;
  FImageLeave := TBitmap.Create;
  FImageLeave.OnChange := BitmapChanged;
  FImageEnter := TBitmap.Create;
  FImageEnter.OnChange := BitmapChanged;
  FHotRect := TVrHotRect.Create;
  FHotRect.OnChange := HotRectChanged;
end;

destructor TVrHotImage.Destroy;
begin
  FHotRect.Free;
  FImageLeave.Free;
  FImageEnter.Free;
  inherited Destroy;
end;

procedure TVrHotImage.BitmapChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrHotImage.HotRectChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrHotImage.SetImageLeave(Value: TBitmap);
begin
  FImageLeave.Assign(Value);
end;

procedure TVrHotImage.SetImageEnter(Value: TBitmap);
begin
  FImageEnter.Assign(Value);
end;

procedure TVrHotImage.SetHotRect(Value: TVrHotRect);
begin
  FHotRect.Assign(Value);
end;

procedure TVrHotImage.SetDrawStyle(Value: TVrHotImageDrawStyle);
begin
  if FDrawStyle <> Value then
  begin
    FDrawStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHotImage.SetTextAlignment(Value: TVrTextAlignment);
begin
  if FTextAlignment <> Value then
  begin
    FTextAlignment := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHotImage.SetColorEnter(Value: TColor);
begin
  if FColorEnter <> Value then
  begin
    FColorEnter := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHotImage.SetColorLeave(Value: TColor);
begin
  if FColorLeave <> Value then
  begin
    FColorLeave := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHotImage.Paint;
var
  P: TPoint;
  MidX, MidY: Integer;
  Image: TBitmap;
  TxtRect, ImageRect: TRect;
  TransparentColor: TColor;
begin
  if Transparent then ClearBitmapCanvas;

  with BitmapCanvas do
  begin
    if FHasMouse and Enabled then
    begin
      Image := ImageEnter;
      Brush.Color := FColorEnter;
      TransparentColor := FColorEnter;
    end
    else
    begin
      Image := ImageLeave;
      Brush.Color := FColorLeave;
      TransparentColor := FColorLeave;
    end;
    if not Transparent then
    begin
      FillRect(ClientRect);
      Brush.Style := bsSolid;
    end else Brush.Style := bsClear;

    if not Image.Empty then
    begin
      P := Point(Image.Width, Image.Height);
      if DrawStyle = dsCenter then
      begin
        MidX := (ClientWidth - P.X) div 2;
        MidY := (ClientHeight - P.Y) div 2;
        ImageRect := Bounds(MidX, MidY, P.X, P.Y)
      end else ImageRect := ClientRect;

      if Transparent then
        BrushCopy(ImageRect, Image, Bounds(0, 0, P.X, P.Y), TransparentColor)
        else StretchDraw(ImageRect, Image);
    end;

    TxtRect := ClientRect;
    if (HotRect.Visible) then
    begin
      InflateRect(TxtRect, -HotRect.Width - 2, -HotRect.Width - 2);
      if FHasMouse then
      begin
        ImageRect := ClientRect;
        DrawFrame3D(Self.BitmapCanvas, ImageRect,
          HotRect.Color, HotRect.Color, HotRect.Width);
      end;
    end;

    Brush.Style := bsClear;
    Font.Assign(Self.Font);
    DrawText(BitmapCanvas.Handle, PChar(Caption), -1, TxtRect,
      DT_SINGLELINE + VrTextAlign[TextAlignment]);
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

procedure TVrHotImage.MouseEnter;
begin
  FHasMouse := True;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrHotImage.MouseLeave;
begin
  FHasMouse := false;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrHotImage.CMTextChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrHotImage.CMFontChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;


end.
