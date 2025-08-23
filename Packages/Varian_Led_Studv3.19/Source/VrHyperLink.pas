{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrHyperLink;

interface

{$I VRLIB.INC}

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, VrControls, VrSysUtils;

type
  TVrHyperLink = class(TVrHyperLinkControl)
  private
    FAutoSize: Boolean;
    FFontEnter: TFont;
    FFontLeave: TFont;
    FColorEnter: TColor;
    FColorLeave: TColor;
    FTextOutline: TVrTextOutline;
    FAlignment: TAlignment;
    FOrgSize: TPoint;
    FHasMouse: Boolean;
    FUpdateSize: Boolean;
    procedure SetAutoSize(Value: Boolean);
    procedure SetFontEnter(Value: TFont);
    procedure SetFontLeave(Value: TFont);
    procedure SetColorEnter(Value: TColor);
    procedure SetColorLeave(Value: TColor);
    procedure SetTextOutline(Value: TVrTextOutline);
    procedure SetAlignment(Value: TAlignment);
    procedure FontChanged(Sender: TObject);
    procedure TextOutlineChanged(Sender: TObject);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
  protected
    procedure AdjustClientSize;
    procedure MouseEnter; override;
    procedure MouseLeave; override;
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property AutoSize: Boolean read FAutoSize write SetAutoSize default false;
    property FontEnter: TFont read FFontEnter write SetFontEnter;
    property FontLeave: TFont read FFontLeave write SetFontLeave;
    property ColorEnter: TColor read FColorEnter write SetColorEnter default clBlue;
    property ColorLeave: TColor read FColorLeave write SetColorLeave default clBlack;
    property TextOutline: TVrTextOutline read FTextOutline write SetTextOutline;
    property Alignment: TAlignment read FAlignment write SetAlignment default taCenter;
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


{ TVrHyperLink }

constructor TVrHyperLink.Create(AOwner : TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csDoubleClicks];
  Width := 135;
  Height := 32;
  FFontEnter := TFont.Create;
  with FFontEnter do
  begin
    Name := 'Arial';
    Size := 12;
    Color := clLime;
    Style := Style + [fsBold, fsUnderline];
    OnChange := FontChanged;
  end;
  FFontLeave := TFont.Create;
  with FFontLeave do
  begin
    Name := 'Arial';
    Size := 12;
    Color := clGreen;
    Style := Style + [fsBold, fsUnderline];
    OnChange := FontChanged;
  end;
  FColorEnter := clBlue;
  FColorLeave := clBlack;
  FAutoSize := false;
  FAlignment := taCenter;
  FTextOutline := TVrTextOutline.Create;
  FTextOutline.OnChange := TextOutlineChanged;
  Transparent := false;
end;

destructor TVrHyperLink.Destroy;
begin
  FTextOutline.Free;
  FFontEnter.Free;
  FFontLeave.Free;
  inherited Destroy;
end;

procedure TVrHyperLink.AdjustClientSize;
var
  P1, P2: TPoint;
  NewWidth, NewHeight: Integer;
begin
  if Align <> alNone then
    Align := alNone;
  with BitmapCanvas do
  begin
    Font.Assign(FFontEnter);
    P1 := Point(TextWidth(Caption), TextHeight(Caption));
    Font.Assign(FFontLeave);
    P2 := Point(TextWidth(Caption), TextHeight(Caption));
  end;
  NewWidth := MaxIntVal(P1.X, P2.X) + 4;
  NewHeight := MaxIntVal(P1.Y, P2.Y) + 4;
  BoundsRect := Bounds(Left, Top, NewWidth, NewHeight);
end;

procedure TVrHyperLink.Paint;
var
  P: TPoint;
  MidX, MidY: Integer;
begin
  if FAutoSize then
    if FUpdateSize or
      (FOrgSize.X <> Width) or (FOrgSize.Y <> Height) then
    begin
      AdjustClientSize;
      FOrgSize := Point(Width, Height);
      FUpdateSize := false;
      Update;
    end;

  if Transparent then ClearBitmapCanvas;
  with BitmapCanvas do
  begin
    if FHasMouse and Enabled then
    begin
      Font.Assign(FFontEnter);
      Brush.Color := FColorEnter;
    end
    else
    begin
      Font.Assign(FFontLeave);
      Brush.Color := FColorLeave;
    end;
    if not Transparent then FillRect(ClientRect);

    P := Point(TextWidth(Caption), TextHeight(Caption));

    MidX := (ClientWidth - P.X) div 2;
    MidY := (ClientHeight - P.Y) div 2;
    case Alignment of
      taLeftJustify: MidX := 2;
      taRightJustify: MidX := ClientWidth - P.X - 2;
    end;

    if Transparent then Brush.Style := bsClear
    else Brush.Style := bsSolid;

    if FTextOutline.Visible then
      DrawOutlinedText(BitmapCanvas, MidX, MidY, Caption, FTextOutline.Color, 1)
    else TextOut(MidX, MidY, Caption);
  end;

  inherited Paint;
end;

procedure TVrHyperLink.SetAutoSize(Value: Boolean);
begin
  if FAutoSize <> Value then
  begin
    FAutoSize := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHyperLink.SetFontEnter(Value: TFont);
begin
  FFontEnter.Assign(Value);
end;

procedure TVrHyperLink.SetFontLeave(Value: TFont);
begin
  FFontLeave.Assign(Value);
end;

procedure TVrHyperLink.SetColorEnter(Value: TColor);
begin
  if FColorEnter <> Value then
  begin
    FColorEnter := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHyperLink.SetColorLeave(Value: TColor);
begin
  if FColorLeave <> Value then
  begin
    FColorLeave := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHyperLink.SetAlignment(Value: TAlignment);
begin
  if FAlignment <> Value then
  begin
    FAlignment := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrHyperLink.SetTextOutline(Value: TVrTextOutline);
begin
  FTextOutline.Assign(Value);
end;

procedure TVrHyperLink.FontChanged(Sender: TObject);
begin
  FUpdateSize := True;
  UpdateControlCanvas;
end;

procedure TVrHyperLink.TextOutlineChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrHyperLink.MouseEnter;
begin
  FHasMouse := True;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrHyperLink.MouseLeave;
begin
  FHasMouse := false;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrHyperLink.CMTextChanged(var Message: TMessage);
begin
  inherited;
  FUpdateSize := True;
  UpdateControlCanvas;
end;


end.
