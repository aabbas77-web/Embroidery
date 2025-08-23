{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrControls;

{$I VRLIB.INC}

interface

uses
{$IFDEF VRSHARE}VrShareWin,{$ENDIF}
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrConst, VrTypes, VrSysUtils;


type
  TGraphicControlCanvas = class(TGraphicControl)
  public
    property Canvas;
  end;

  TCustomControlCanvas = class(TCustomControl)
  public
    property Canvas;
  end;

  TVrComponent = class(TComponent)
  private
    FVersion: TVrVersion;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Version: TVrVersion read FVersion write FVersion stored false;
  end;

  TVrCustomControl = class(TCustomControl)
  private
    FVersion: TVrVersion;
    FUpdateCount: Integer;
  protected
    function Designing: Boolean;
    function Loading: Boolean;
    procedure ClearClientCanvas;
    procedure UpdateControlCanvas; virtual;
  public
    constructor Create(AOwner: TComponent); override;
    procedure BeginUpdate;
    procedure EndUpdate;
  published
    property Version: TVrVersion read FVersion write FVersion stored false;
  end;

  TVrCustomImageControl = class(TVrCustomControl)
  private
    FBitmapImage: TBitmap;
    function GetBitmapCanvas: TCanvas;
  protected
    DestCanvas: TCanvas;
    procedure ClearBitmapCanvas; virtual;
    procedure Paint; override;
    property BitmapImage: TBitmap read FBitmapImage;
    property BitmapCanvas: TCanvas read GetBitmapCanvas;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
  end;

  TVrGraphicControl = class(TGraphicControl)
  private
    FVersion: TVrVersion;
    FUpdateCount: Integer;
  protected
    function Designing: Boolean;
    function Loading: Boolean;
    procedure ClearClientCanvas;
    procedure UpdateControlCanvas; virtual;
  public
    constructor Create(AOwner: TComponent); override;
    procedure BeginUpdate;
    procedure EndUpdate;
  published
    property Version: TVrVersion read FVersion write FVersion stored false;
  end;

  TVrGraphicImageControl = class(TVrGraphicControl)
  private
    FBitmapImage: TBitmap;
    FTransparent: Boolean;
    function GetBitmapCanvas: TCanvas;
    procedure SetTransparent(Value: Boolean);
  protected
    DestCanvas: TCanvas;
    procedure ClearBitmapCanvas; virtual;
    procedure Paint; override;
    property BitmapImage: TBitmap read FBitmapImage;
    property BitmapCanvas: TCanvas read GetBitmapCanvas;
    property Transparent: Boolean read FTransparent write SetTransparent;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
  end;

  TVrHyperLinkControl = class(TVrGraphicImageControl)
  private
    FOnMouseEnter: TNotifyEvent;
    FOnMouseLeave: TNotifyEvent;
    procedure CMMouseEnter(var Message: TMessage); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
  protected
    procedure MouseEnter; virtual;
    procedure MouseLeave; virtual;
    property OnMouseEnter: TNotifyEvent read FOnMouseEnter write FOnMouseEnter;
    property OnMouseLeave: TNotifyEvent read FOnMouseLeave write FOnMouseLeave;
  end;

  TVrThumbStates = 1..4;
  TVrCustomThumb = class(TVrGraphicImageControl)
  private
    FGlyph: TBitmap;
    FThumbStates: TVrThumbStates;
    FDown: Boolean;
    FHasMouse: Boolean;
    procedure SetGlyph(Value: TBitmap);
    procedure SetThumbStates(Value: TVrThumbStates);
    procedure SetDown(Value: Boolean);
    procedure AdjustBoundsRect; virtual;
    procedure CMMouseEnter(var Message: TMessage); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
  protected
    procedure Paint; override;
    procedure LoadFromResourceName(const ResName: string);
    function GetImageIndex: Integer; virtual;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Glyph: TBitmap read FGlyph write SetGlyph stored false;
    property ThumbStates: TVrThumbStates read FThumbStates write SetThumbStates;
    property Down: Boolean read FDown write SetDown;
    property HasMouse: Boolean read FHasMouse;
  end;


implementation


{ TVrComponent }

constructor TVrComponent.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FVersion := VrLibVersion;
{$IFDEF VRSHARE}
  if not (csDesigning in ComponentState) then
    ShowRegWin;
{$ENDIF}
end;

{ TVrCustomControl }

constructor TVrCustomControl.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FVersion := VrLibVersion;
{$IFDEF VRSHARE}
  if not Designing then
    ShowRegWin;
{$ENDIF}
end;

function TVrCustomControl.Designing: Boolean;
begin
  Result := (csDesigning in ComponentState);
end;

function TVrCustomControl.Loading: Boolean;
begin
  Result := (csLoading in ComponentState);
end;

procedure TVrCustomControl.ClearClientCanvas;
begin
  with inherited Canvas do
  begin
    Brush.Style := bsSolid;
    Brush.Color := Self.Color;
    FillRect(ClientRect);
  end;
end;

procedure TVrCustomControl.UpdateControlCanvas;
begin
  if not Loading then
    if FUpdateCount = 0 then Repaint;
end;

procedure TVrCustomControl.BeginUpdate;
begin
  Inc(FUpdateCount);
end;

procedure TVrCustomControl.EndUpdate;
begin
  Dec(FUpdateCount);
  UpdateControlCanvas;
end;

{ TVrCustomImageControl }

constructor TVrCustomImageControl.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FBitmapImage := TBitmap.Create;
  DestCanvas := Self.Canvas;
end;

destructor TVrCustomImageControl.Destroy;
begin
  FBitmapImage.Free;
  inherited Destroy;
end;

procedure TVrCustomImageControl.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  with FBitmapImage do
  begin
    Width := AWidth;
    Height := AHeight;
  end;
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
end;

procedure TVrCustomImageControl.ClearBitmapCanvas;
begin
  with FBitmapImage do
  begin
    Canvas.Brush.Style := bsSolid;
    Canvas.Brush.Color := Self.Color;
    Canvas.FillRect(Bounds(0, 0, Width, Height));
  end;
end;

procedure TVrCustomImageControl.Paint;
begin
  BitBlt(Canvas.Handle, 0, 0, Width, Height,
    FBitmapImage.Canvas.Handle, 0, 0, SRCCOPY);
end;

function TVrCustomImageControl.GetBitmapCanvas: TCanvas;
begin
  Result := FBitmapImage.Canvas;
end;

{ TVrGraphicControl }

constructor TVrGraphicControl.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FVersion := VrLibVersion;
{$IFDEF VRSHARE}
  if not Designing then
    ShowRegWin;
{$ENDIF}
end;

function TVrGraphicControl.Designing: Boolean;
begin
  Result := (csDesigning in ComponentState);
end;

function TVrGraphicControl.Loading: Boolean;
begin
  Result := (csLoading in ComponentState);
end;

procedure TVrGraphicControl.ClearClientCanvas;
begin
  with inherited Canvas do
  begin
    Brush.Style := bsSolid;
    Brush.Color := Self.Color;
    FillRect(ClientRect);
  end;
end;

procedure TVrGraphicControl.UpdateControlCanvas;
begin
  if not Loading then
    if FUpdateCount = 0 then Repaint;
end;

procedure TVrGraphicControl.BeginUpdate;
begin
  Inc(FUpdateCount);
end;

procedure TVrGraphicControl.EndUpdate;
begin
  Dec(FUpdateCount);
  UpdateControlCanvas;
end;

{ TVrGraphicImageControl }

constructor TVrGraphicImageControl.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FBitmapImage := TBitmap.Create;
  FTransparent := false;
  DestCanvas := Self.Canvas;
end;

destructor TVrGraphicImageControl.Destroy;
begin
  FBitmapImage.Free;
  inherited Destroy;
end;

procedure TVrGraphicImageControl.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  with FBitmapImage do
  begin
    Width := AWidth;
    Height := AHeight;
  end;
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
end;

procedure TVrGraphicImageControl.SetTransparent(Value: Boolean);
begin
  if FTransparent <> Value then
  begin
    FTransparent := Value;
    UpdateControlCanvas;
  end;
end;

type
  ParentControl = class(TWinControl);

procedure TVrGraphicImageControl.ClearBitmapCanvas;
begin
  with FBitmapImage do
  begin
//    if (FTransparent) and (Self.Parent <> nil) then
//    Canvas.Brush.Color := ParentControl(Self.Parent).Color

    Canvas.Brush.Style := bsSolid;
    if FTransparent then CopyParentImage(Self, Canvas)
    else
    begin
      Canvas.Brush.Color := Self.Color;
      Canvas.FillRect(Bounds(0, 0, Width, Height));
    end;
  end;
end;

procedure TVrGraphicImageControl.Paint;
begin
  BitBlt(Canvas.Handle, 0, 0, Width, Height,
    FBitmapImage.Canvas.Handle, 0, 0, SRCCOPY);
end;

function TVrGraphicImageControl.GetBitmapCanvas: TCanvas;
begin
  Result := FBitmapImage.Canvas;
end;

{ TVrHyperLinkControl }

procedure TVrHyperLinkControl.MouseEnter;
begin
  if Assigned(FOnMouseEnter) then
    FOnMouseEnter(Self);
end;

procedure TVrHyperLinkControl.MouseLeave;
begin
  if Assigned(FOnMouseLeave) then
    FOnMouseLeave(Self);
end;

procedure TVrHyperLinkControl.CMMouseEnter(var Message: TMessage);
begin
  inherited;
  MouseEnter;
end;

procedure TVrHyperLinkControl.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  MouseLeave;
end;

{ TVrCustomThumb }

constructor TVrCustomThumb.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  FGlyph := TBitmap.Create;
  FTransparent := True;
  FThumbStates := 1;
end;

destructor TVrCustomThumb.Destroy;
begin
  FGlyph.Free;
  inherited Destroy;
end;

procedure TVrCustomThumb.SetGlyph(Value: TBitmap);
begin
  FGlyph.Assign(Value);
  AdjustBoundsRect;
end;

procedure TVrCustomThumb.SetThumbStates(Value: TVrThumbStates);
begin
  if FThumbStates <> Value then
  begin
    FThumbStates := Value;
    AdjustBoundsRect;
  end;
end;

procedure TVrCustomThumb.AdjustBoundsRect;
begin
  if not FGlyph.Empty then
    BoundsRect := Bounds(Left, Top, FGlyph.Width div ThumbStates, FGlyph.Height);
end;

procedure TVrCustomThumb.LoadFromResourceName(const ResName: string);
begin
  FGlyph.LoadFromResourceName(hInstance, ResName);
  AdjustBoundsRect;
end;

procedure TVrCustomThumb.Paint;
var
  Index, Offset: Integer;
begin
  ClearBitmapCanvas;
  Index := GetImageIndex;
  if Succ(Index) > ThumbStates then Index := 0;
  if (not FGlyph.Empty) then
  begin
    Offset := Index * Width;
    with BitmapCanvas do
    begin
      Brush.Style := bsClear;
      BrushCopy(ClientRect, FGlyph,
        Bounds(Offset, 0, FGlyph.Width div ThumbStates, FGlyph.Height), clOlive);
    end;
  end;
  inherited Paint;
end;

function TVrCustomThumb.GetImageIndex: Integer;
begin
  Result := 0;
end;

procedure TVrCustomThumb.SetDown(Value: Boolean);
begin
  if FDown <> Value then
  begin
    FDown := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomThumb.CMMouseEnter(var Message: TMessage);
begin
  inherited;
  FHasMouse := True;
  UpdateControlCanvas;
end;

procedure TVrCustomThumb.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  FHasMouse := false;
  UpdateControlCanvas;
end;




end.
