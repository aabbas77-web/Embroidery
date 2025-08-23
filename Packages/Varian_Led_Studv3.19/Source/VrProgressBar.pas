{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrProgressBar;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrProgressBar = class(TVrGraphicImageControl)
  private
    FBevel: TVrBevel;
    FMin: Integer;
    FMax: Integer;
    FPosition: Integer;
    FPlainColors: Boolean;
    FStartColor: TColor;
    FEndColor: TColor;
    FSmooth: Boolean;
    FOrientation: TVrOrientation;
    FStep: Integer;
    ViewPort: TRect;
    Bitmap: TBitmap;
    ColorUpdate: Boolean;
    function GetPercentDone: Longint;
    procedure SetMin(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetStartColor(Value: TColor);
    procedure SetEndColor(Value: TColor);
    procedure SetPlainColors(Value: Boolean);
    procedure SetSmooth(Value: Boolean);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetBevel(Value: TVrBevel);
    procedure BevelChanged(Sender: TObject);
  protected
    procedure CreateBitmap(const Rect: TRect);
    procedure Paint; override;
    procedure DrawHori;
    procedure DrawVert;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure StepIt;
    procedure StepBy(Delta: Integer);
    property PercentDone: Longint read GetPercentDone;
  published
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property Position: Integer read FPosition write SetPosition default 100;
    property StartColor: TColor read FStartColor write SetStartColor default clNavy;
    property EndColor: TColor read FEndColor write SetEndColor default clAqua;
    property PlainColors: Boolean read FPlainColors write SetPlainColors default false;
    property Smooth: Boolean read FSmooth write SetSmooth default false;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property Step: Integer read FStep write FStep default 10;
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


{ TVrProgressBar }
constructor TVrProgressBar.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csSetCaption];
  Width := 200;
  Height := 16;
  Color := clBlack;
  ParentColor := false;
  FMin := 0;
  FMax := 100;
  FPosition := 100;
  FStartColor := clNavy;
  FEndColor := clAqua;
  FPlainColors := false;
  FSmooth := false;
  FOrientation := voHorizontal;
  FStep := 10;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsNone;
    InnerSpace := 0;
    OuterStyle := bsLowered;
    OuterOutline := osNone;
    OnChange := BevelChanged;
  end;
  Bitmap := TBitmap.Create;
end;

destructor TVrProgressBar.Destroy;
begin
  Bitmap.Free;
  FBevel.Free;
  inherited Destroy;
end;

procedure TVrProgressBar.BevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrProgressBar.CreateBitmap(const Rect: TRect);
var
  R: TRect;
  NewWidth, NewHeight: Integer;
begin
  NewWidth := Rect.Right - Rect.Left;
  NewHeight := Rect.Bottom - Rect.Top;
  if (ColorUpdate) or
     (Bitmap.Width <> NewWidth) or
     (Bitmap.Height <> NewHeight) then
  begin
    Bitmap.Width := NewWidth;
    Bitmap.Height := NewHeight;
    R := Bounds(0, 0, NewWidth, NewHeight);
    if FPlainColors then
    begin
      Bitmap.Canvas.Brush.Color := clHighlight;
      Bitmap.Canvas.FillRect(R);
    end
    else
      case FOrientation of
        voHorizontal:
          DrawGradient(Bitmap.Canvas, R, FStartColor,
            FEndColor, FOrientation, 1);
        voVertical:
          DrawGradient(Bitmap.Canvas, R, FEndColor,
            FStartColor, FOrientation, 1);
      end;
    ColorUpdate := false;
  end;
end;

function TVrProgressBar.GetPercentDone: Longint;
begin
  Result := SolveForY(FPosition - FMin, FMax - FMin);
end;

procedure TVrProgressBar.StepIt;
begin
  Position := Position + FStep;
end;

procedure TVrProgressBar.StepBy(Delta: Integer);
begin
  Position := Position + Delta;
end;

procedure TVrProgressBar.Paint;
begin
  ClearBitmapCanvas;
  ViewPort := ClientRect;
  FBevel.Paint(BitmapCanvas, ViewPort);

  CreateBitmap(ViewPort);
  case Orientation of
    voVertical: DrawVert;
    voHorizontal: DrawHori;
  end;
  inherited Paint;
end;

procedure TVrProgressBar.DrawHori;
var
  R: TRect;
  BarWidth: Integer;
  XLimit: Integer;
begin
  BarWidth := ((ViewPort.Bottom - ViewPort.Top) div 3) * 2;
  R := Bounds(ViewPort.Left + ord(FSmooth), ViewPort.Top,
    BarWidth, ViewPort.Bottom - ViewPort.Top);
  InflateRect(R, -ord(not FSmooth), -1);

  XLimit := SolveForX(PercentDone, WidthOf(ViewPort));

  if FSmooth then
    R.Right := ViewPort.Left + XLimit;

  while R.Left < ViewPort.Left + XLimit do
  begin
    if R.Right >= ViewPort.Right then
      R.Right := ViewPort.Right - 1;
    BitmapCanvas.CopyRect(R, Bitmap.Canvas,
       Bounds(R.Left - ViewPort.Left, 0, R.Right - R.Left, R.Bottom - R.Top));
    OffsetRect(R, R.Right - R.Left + 2, 0);
  end;
end;

procedure TVrProgressBar.DrawVert;
var
  R: TRect;
  BarHeight: Integer;
  XLimit: Integer;
begin
  BarHeight := ((ViewPort.Right - ViewPort.Left) div 3) * 2;

  R := Bounds(ViewPort.Left, ViewPort.Bottom - BarHeight,
    ViewPort.Right - ViewPort.Left, BarHeight);

  InflateRect(R, -1, -ord(not FSmooth));

  XLimit := SolveForX(PercentDone, HeightOf(ViewPort));

  if FSmooth then
    R.Top := ViewPort.Bottom - XLimit;

  while R.Bottom > ViewPort.Bottom - XLimit do
  begin
    if R.Top <= ViewPort.Top then
      R.Top := ViewPort.Top - 1;
    BitmapCanvas.CopyRect(R, Bitmap.Canvas,
       Bounds(0, R.Top - ViewPort.Top - 1, Bitmap.Width, R.Bottom - R.Top));
    OffsetRect(R, 0, -(R.Bottom - R.Top + 2));
  end;
end;

procedure TVrProgressBar.SetMin(Value: Integer);
begin
  if (FMin <> Value) and (Value < FMax) then
  begin
    FMin := Value;
    if FPosition < FMin then Position := FMin
    else UpdateControlCanvas;
  end;
end;

procedure TVrProgressBar.SetMax(Value: Integer);
begin
  if (FMax <> Value) and (Value > FMin) then
  begin
    FMax := Value;
    if FPosition > FMax then Position := FMax
    else UpdateControlCanvas;
  end;
end;

procedure TVrProgressBar.SetPosition(Value: Integer);
begin
  if Value < FMin then Value := FMin;
  if Value > FMax then Value := FMax;
  if FPosition <> Value then
  begin
    FPosition := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrProgressBar.SetStartColor(Value: TColor);
begin
  if FStartColor <> Value then
  begin
    FStartColor := Value;
    ColorUpdate := True;
    UpdateControlCanvas;
  end;
end;

procedure TVrProgressBar.SetEndColor(Value: TColor);
begin
  if FEndColor <> Value then
  begin
    FEndColor := Value;
    ColorUpdate := True;
    UpdateControlCanvas;
  end;
end;

procedure TVrProgressBar.SetPlainColors(Value: Boolean);
begin
  if FPlainColors <> Value then
  begin
    FPlainColors := Value;
    ColorUpdate := True;
    UpdateControlCanvas;
  end;
end;

procedure TVrProgressBar.SetSmooth(Value: Boolean);
begin
  if FSmooth <> Value then
  begin
    FSmooth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrProgressBar.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrProgressBar.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    ColorUpdate := True;
    if not Loading then
      BoundsRect := Bounds(Left, Top, Height, Width);
    UpdateControlCanvas;
  end;
end;


end.
