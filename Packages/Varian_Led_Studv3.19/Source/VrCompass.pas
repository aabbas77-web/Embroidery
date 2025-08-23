{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrCompass;

{$I VRLIB.INC}

interface

uses
  Classes, Controls, Windows, Graphics, SysUtils, Messages,
  VrControls, VrSysUtils;

type
  TVrCompass = class(TVrGraphicImageControl)
  private
    FBackImage: TBitmap;
    FAutoSize: Boolean;
    FHeading: Integer;
    FNeedleLength: Integer;
    FNeedleWidth: Integer;
    FNeedleColor: TColor;
    FNeedleTransparent: Boolean;
    FCircleColor: TColor;
    FCircleWidth: Integer;
    FCircleOutlineColor: TColor;
    FCircleOutlineWidth: Integer;
    FOnChange: TNotifyEvent;
    procedure SetHeading(Value: Integer);
    procedure SetNeedleColor(Value: TColor);
    procedure SetCircleWidth(Value: Integer);
    procedure SetCircleOutlineColor(Value: TColor);
    procedure SetNeedleLength(Value: Integer);
    procedure SetNeedleWidth(Value: Integer);
    procedure SetCircleOutlineWidth (Value: Integer);
    procedure SetCircleColor(Value: TColor);
    procedure SetBackImage(Value: TBitmap);
    procedure SetAutoSize(Value: Boolean);
    procedure SetNeedleTransparent(Value: Boolean);
    procedure BackImageChanged(Sender: TObject);
  protected
    procedure Paint; override;
    procedure AdjustClientRect;
    function GetPalette: HPALETTE; override;
    procedure Changed; virtual;
 public
    constructor Create(AOwner : Tcomponent);override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
  published
    property Heading: Integer read fHeading write SetHeading;
    property NeedleLength: Integer read fNeedleLength write SetNeedleLength default 40;
    property NeedleWidth: Integer read FNeedleWidth write SetNeedleWidth;
    property CircleOutlineWidth: Integer read FCircleOutlineWidth write SetCircleOutlineWidth;
    property CircleWidth: Integer read FCircleWidth write SetCircleWidth default 8;
    property CircleOutlineColor: TColor read FCircleOutlineColor write SetCircleOutlineColor default clBlue;
    property NeedleColor: TColor read FNeedleColor write SetNeedleColor default clRed;
    property CircleColor: TColor read FCircleColor write SetCircleColor default clNavy;
    property BackImage: TBitmap read FBackImage write SetBackImage;
    property AutoSize: Boolean read FAutoSize write SetAutoSize default True;
    property NeedleTransparent: Boolean read FNeedleTransparent write SetNeedleTransparent default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
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



implementation


function DegToRad(Degrees: Extended): Extended;
begin
  Result := Degrees * (PI / 180);
end;

{ TVrCompass }

constructor TVrCompass.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable, csSetCaption];
  Width := 100;
  Height := 100;
  Color := clBlack;
  ParentColor := false;
  Transparent := false;
  FAutoSize := True;
  FHeading := 90;
  FNeedleLength := 40;
  FNeedleWidth := 2;
  FNeedleColor := clRed;
  FNeedleTransparent := false;
  FCircleWidth := 8;
  FCircleOutlineWidth := 1;
  FCircleOutlineColor := clBlue;
  FCircleColor := clNavy;
  FBackImage := TBitmap.Create;
  FBackImage.OnChange := BackImageChanged;
end;

destructor TVrCompass.Destroy;
begin
  FBackImage.Free;
  inherited Destroy;
end;

procedure TVrCompass.Changed;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrCompass.Paint;
const
  PenMode: array[Boolean] of TPenMode = (pmCOPY, pmXOR);
var
  Center: TPoint;
  R: TRect;
  X, Y, Radius: Integer;
begin
  ClearBitmapCanvas;

  Center.X := ClientWidth div 2;
  Center.Y := ClientHeight div 2;

  Radius := FCircleWidth;

  DrawBitmap(BitmapCanvas, ClientRect, BackImage,
    BitmapRect(BackImage),  Transparent, Self.Color);

  with BitmapCanvas do
  begin
    R := Rect(Center.X - Radius, Center.Y - Radius,
      Center.X + Radius, Center.Y + Radius);

    Pen.Mode := pmCOPY;
    Pen.Width := FCircleOutlineWidth;
    Pen.Color := FCircleOutlineColor;
    Brush.Color := FCircleColor;
    Brush.Style := bsSolid;
    Ellipse(R.Left, R.Top, R.Right, R.Bottom);

    Pen.Mode := PenMode[NeedleTransparent];
    Pen.Width:= FNeedleWidth;
    Pen.Color := FNeedleColor;

    X := Center.X + Trunc(Sin(DegToRad(FHeading)) * FNeedleLength);
    Y := Center.Y + Trunc(Cos(DegToRad(FHeading)) * FNeedleLength);
    MoveTo(Center.X, Center.Y);
    LineTo(X, (Center.Y * 2) - Y);
  end;

  inherited Paint;
end;

procedure TVrCompass.AdjustClientRect;
begin
  if not FBackImage.Empty then
  begin
    Width := FBackImage.Width;
    Height := FBackImage.Height;
  end;
end;

procedure TVrCompass.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  if AutoSize then
    if not FBackImage.Empty then
    begin
      AWidth := FBackImage.Width;
      AHeight := FBackImage.Height;
    end;
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
end;

function TVrCompass.GetPalette: HPALETTE;
begin
  Result := BackImage.Palette;
end;

procedure TVrCompass.SetHeading (Value: Integer);
begin
   if FHeading <> value then
   begin
     FHeading := Value;
     UpdateControlCanvas;
     Changed;
   end;
end;

procedure TVrCompass.SetAutoSize(Value: Boolean);
begin
  if FAutoSize <> Value then
  begin
    FAutoSize := Value;
    AdjustClientRect;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetNeedleLength (Value: Integer);
begin
  if FNeedleLength <> value then
  begin
    FNeedleLength := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetNeedleWidth(Value: Integer);
begin
  if NeedleWidth <> Value then
  begin
    FNeedleWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetCircleOutlineWidth(Value: Integer);
begin
   if FCircleOutlineWidth <> value then
   begin
     FCircleOutlineWidth := Value;
     UpdateControlCanvas;
   end;
end;

procedure TVrCompass.SetCircleWidth(Value: Integer);
begin
  if FCircleWidth <> Value then
  begin
    FCircleWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetNeedleColor(Value: TColor);
begin
  if FNeedleColor <> Value then
  begin
    FNeedleColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetCircleOutlineColor(Value: TColor);
begin
  if FCircleOutlineColor <> Value then
  begin
    FCircleOutlineColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetCircleColor(Value: TColor);
begin
  if FCircleColor <> Value then
  begin
    FCircleColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetNeedleTransparent(Value: Boolean);
begin
  if FNeedleTransparent <> Value then
  begin
    FNeedleTransparent := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCompass.SetBackImage(Value: TBitmap);
begin
  FBackImage.Assign(Value);
end;

procedure TVrCompass.BackImageChanged(Sender: TObject);
begin
  if AutoSize then AdjustClientRect;
  UpdateControlCanvas;
end;



end.
