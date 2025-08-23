{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrDigit;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, Classes, Graphics, Controls, Forms,
  VrClasses, VrControls;


type
  TVrDigit = class(TVrGraphicImageControl)
  private
    FValue: Integer;
    FValueBinary: Byte;
    FPalette: TVrPalette;
    FActiveOnly: Boolean;
    FOutlineColor: TColor;
    FOnChange: TNotifyEvent;
    procedure SetValue(Value: Integer);
    procedure SetValueBinary(Value: Byte);
    procedure SetActiveOnly(Value: Boolean);
    procedure SetOutlineColor(Value: TColor);
    procedure SetPalette(Value: TVrPalette);
    procedure PaletteModified(Sender: TObject);
  protected
    procedure Change; dynamic;
    procedure Paint; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Value: Integer read FValue write SetValue default 0;
    property ValueBinary: Byte read FValueBinary write SetValueBinary default 125;
    property Palette: TVrPalette read FPalette write SetPalette;
    property ActiveOnly: Boolean read FActiveOnly write SetActiveOnly default false;
    property Transparent default false;
    property OutlineColor: TColor read FOutlineColor write SetOutlineColor default clBlack;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property Align;
    property DragCursor;
{$IFDEF VER110}
    property Anchors;
    property DragKind;
{$ENDIF}
    property DragMode;
    property Color default clBlack;
{$IFDEF VER110}
    property Constraints;
{$ENDIF}
    property ParentColor default false;
    property ParentShowHint;
    property PopUpMenu;
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

const
  BitMask: array[0..10] of byte =
    (125, 80, 55, 87, 90, 79, 111, 81, 127, 95, 47);


{ TVrDigit }
constructor TVrDigit.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csSetCaption];
  Width := 50;
  Height := 60;
  Color := clBlack;
  ParentColor := false;
  FValue := 0;
  FValueBinary := 125;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FActiveOnly := false;
  FOutlineColor := clBlack;
end;

procedure TVrDigit.PaletteModified(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrDigit.Paint;
var
 Iy, Ix, W, H, G, Dp, X, Y: Integer;
 Bit: Byte;
 Active: Boolean;
begin
  ClearBitmapCanvas;
  BitmapCanvas.Pen.Color := FOutlineColor;

  W := ClientWidth - (ClientWidth div 6);
  H := ClientHeight-1;

  G := W div 12;
  if (G > (H div 12)) then G := H div 12;

  Bit := 1;
  Dp := 2;
  for Iy:= 0 to 2 do
  begin
    case Iy of
      0 : y := 0;
      1 : y := H div 2 - G;
      2 : y := H - 2 * G;
      else Y := 0;
    end;

    Active := (FValueBinary and Bit) = Bit;
    if (not FActiveOnly) or (FActiveOnly and Active)  then
    begin
      BitmapCanvas.Brush.Color := FPalette.Colors[ord(Active)];
      BitmapCanvas.Polygon([Point(0 + g + dp,     g + y),
                            Point(2 * g + dp,     0 + y),
                            Point(W - 2 * g - dp, 0 + y),
                            Point(W - g - dp,     g + y),
                            Point(W - 2 * g - dp, 2 * g + y),
                            Point(2 * g + dp,     2 * g + y)]);
    end;
    Bit := Bit * 2;
  end;

  for Iy := 0 to 1 do
    for Ix := 0 to 1 do
    begin

      if Ix = 0 then X := 0 else X := W - 2 * G;
      if Iy = 0 then Y := 0 else Y := H div 2 - G;

      Active := (FValueBinary and Bit) = Bit;
      if (not FActiveOnly) or (FActiveOnly and Active)  then
      begin
        BitmapCanvas.Brush.Color := FPalette.Colors[ord(Active)];
        BitmapCanvas.Polygon([Point(0 + x,     2 * g + Y + dp),
                              Point(g + x,     g + Y + dp),
                              Point(2 * g + x, 2 * g + Y + dp),
                              Point(2 * g + x, H div 2 - g + y - dp),
                              Point(g + x,     H div 2 + y - dp),
                              Point(0 + x,     H div 2 - g + y - dp)]);
      end;
      Bit := Bit * 2;
    end;

  Active := (FValueBinary and Bit) = Bit;
  if (not FActiveOnly) or (FActiveOnly and Active)  then
  begin
    BitmapCanvas.Brush.Color := FPalette.Colors[ord(Active)];
    BitmapCanvas.Rectangle(W + G * 2, H - G * 2, W, H);
  end;

  inherited Paint;
end;

procedure TVrDigit.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrDigit.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrDigit.SetActiveOnly(Value: Boolean);
begin
  if FActiveOnly <> Value then
  begin
    FActiveOnly := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrDigit.SetValue(Value: Integer);
begin
  if (FValue <> Value) and (Value in [0..9]) then
  begin
    FValue := Value;
    FValueBinary := BitMask[FValue];
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrDigit.SetValueBinary(Value: Byte);
var
  I: Integer;
begin
  if FValueBinary <> Value then
  begin
    FValueBinary := Value;
    for I := 0 to 9 do
      if FValueBinary = BitMask[I] then SetValue(I)
    else
    begin
      UpdateControlCanvas;
      Change;
    end;
  end;
end;

procedure TVrDigit.SetOutlineColor(Value: TColor);
begin
  if FOutlineColor <> Value then
  begin
    FOutlineColor := Value;
    UpdateControlCanvas;
  end;
end;


end.
