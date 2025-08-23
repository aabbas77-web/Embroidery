{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrBanner;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, VrControls, VrSysUtils, VrThreads;

type
  TVrBannerPixelMode = (pmAuto, pmCustom);
  TVrBannerDirection = (bdRightToLeft, bdLeftToRight,
    bdTopToBottom, bdBottomToTop);

  TVrBanner = class(TVrGraphicImageControl)
  private
    FBitmap: TBitmap;
    FRaster: TBitmap;
    FPixelSize: Integer;
    FPixelColor: TColor;
    FPixelMode: TVrBannerPixelMode;
    FSpacing: Integer;
    FIncrement: Integer;
    FAutoScroll: Boolean;
    FBevel: TVrBevel;
    FDirection: TVrBannerDirection;
    FThreaded: Boolean;
    FOnScrollDone: TNotifyEvent;
    FDstX, FDstY: Integer;
    FScrollInit: Boolean;
    Initialized: Boolean;
    FTimer: TVrTimer;
    function GetTimeInterval: Integer;
    function GetPixelColor: TColor;
    procedure SetBitmap(Value: TBitmap);
    procedure SetPixelSize(Value: Integer);
    procedure SetPixelColor(Value: TColor);
    procedure SetSpacing(Value: Integer);
    procedure SetTimeInterval(Value: Integer);
    procedure SetAutoScroll(Value: Boolean);
    procedure SetPixelMode(Value: TVrBannerPixelMode);
    procedure SetBevel(Value: TVrBevel);
    procedure SetThreaded(Value: Boolean);
    procedure CreateRasterImage;
    procedure TimerEvent(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
    procedure CMColorChanged(var Message: TMessage); message CM_COLORCHANGED;
  protected
    procedure Reset;
    procedure Paint; override;
    procedure Loaded; override;
    procedure Notify;
    procedure BitmapChanged(Sender: TObject);
    function StepSize: Integer;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Bitmap: TBitmap read FBitmap write SetBitmap;
    property PixelSize: Integer read FPixelSize write SetPixelSize default 2;
    property PixelColor: TColor read FPixelColor write SetPixelColor default clGray;
    property PixelMode: TVrBannerPixelMode read FPixelMode write SetPixelMode default pmAuto;
    property Spacing: Integer read FSpacing write SetSpacing default 1;
    property TimeInterval: Integer read GetTimeInterval write SetTimeInterval default 50;
    property AutoScroll: Boolean read FAutoScroll write SetAutoScroll default false;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Direction: TVrBannerDirection read FDirection write FDirection default bdRightToLeft;
    property OnScrollDone: TNotifyEvent read FOnScrollDone write FOnScrollDone;
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


{ TVrBanner }

constructor TVrBanner.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 320;
  Height := 40;
  Color := clBlack;
  ParentColor := false;
  FPixelSize := 2;
  FPixelColor := clGray;
  FSpacing := 1;
  FIncrement := 0;
  FAutoScroll := false;
  FPixelMode := pmAuto;
  FDirection := bdRightToLeft;
  FScrollInit := True;
  FDstX := 0;
  FDstY := 0;
  FBitmap := TBitmap.Create;
  FBitmap.OnChange := BitmapChanged;
  FRaster := TBitmap.Create;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerSpace := 0;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  FThreaded := True;
  FTimer := TVrTimer.Create(Self);
  FTimer.Enabled := false;
  FTimer.Interval := 50;
  FTimer.OnTimer := TimerEvent;
end;

destructor TVrBanner.Destroy;
begin
  FBitmap.Free;
  FRaster.Free;
  FTimer.Free;
  FBevel.Free;
  inherited Destroy;
end;

procedure TVrBanner.Loaded;
begin
  inherited Loaded;
  CreateRasterImage;
  BoundsRect := Bounds(Left, Top, Width, Height);
end;

procedure TVrBanner.Reset;
var
  W, H, I: Integer;
begin
  I := StepSize;
  W := (Width - FRaster.Width) div 2;
  FDstX := MaxIntVal(0, (W div I) * I);
  H := (Height - FRaster.Height) div 2;
  FDstY := MaxIntVal(0, (H div I) * I);
end;

procedure TVrBanner.BevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrBanner.CreateRasterImage;
begin
  if not FBitmap.Empty then
    BitmapToLCD(FRaster, FBitmap, FPixelColor, Self.Color, FPixelSize, FSpacing)
  else FRaster.Assign(nil);
end;

procedure TVrBanner.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
var
  Ticks: Integer;
begin
  if not Loading then
  begin
    Ticks := (AWidth + FSpacing) div StepSize;
    AWidth := (Ticks * StepSize) - FSpacing;
    Ticks := (AHeight + FSpacing) div StepSize;
    AHeight := (Ticks * StepSize) - FSpacing;
  end;
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  if FRaster <> nil then Reset;
end;

procedure TVrBanner.Paint;
var
  R: TRect;
begin
  DrawRasterPattern(BitmapCanvas, ClientRect, GetPixelColor,
    Self.Color, FPixelSize, FSpacing);

  if not FRaster.Empty then
    BitmapCanvas.Draw(FDstX, FDstY, FRaster);

  R := ClientRect;
  FBevel.Paint(BitmapCanvas, R);

  inherited Paint;

  //Make sure we first display the control
  if (not Initialized) and (AutoScroll) then
  begin
    Initialized := True;
    FScrollInit := True;
    FTimer.Enabled := True;
  end;
end;

procedure TVrBanner.SetBitmap(Value: TBitmap);
begin
  FBitmap.Assign(Value);
end;

procedure TVrBanner.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrBanner.SetPixelSize(Value: Integer);
begin
  if (FPixelSize <> Value) and (Value > 0) then
  begin
    FPixelSize := Value;
    BitmapChanged(Self);
  end;
end;

procedure TVrBanner.SetPixelColor(Value: TColor);
begin
  if FPixelColor <> Value then
  begin
    FPixelColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBanner.SetSpacing(Value: Integer);
begin
  if (FSpacing <> Value) and (Value > 0) then
  begin
    FSpacing := Value;
    BitmapChanged(Self);
  end;
end;

procedure TVrBanner.SetAutoScroll(Value: Boolean);
begin
  if FAutoScroll <> Value then
  begin
    FAutoScroll := Value;
    Reset;
    UpdateControlCanvas;
    if not (Designing or Loading) then
    begin
      FScrollInit := True;
      FTimer.Enabled := Value;
    end;
  end;
end;

function TVrBanner.GetTimeInterval: Integer;
begin
  Result := FTimer.Interval;
end;

procedure TVrBanner.SetTimeInterval(Value: Integer);
begin
  FTimer.Interval := Value;
end;

procedure TVrBanner.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;

function TVrBanner.GetPixelColor: TColor;
begin
  Result := FPixelColor;
  if FPixelMode = pmAuto then
    if not FBitmap.Empty then Result := FRaster.Canvas.Pixels[0, 0];
end;

procedure TVrBanner.SetPixelMode(Value: TVrBannerPixelMode);
begin
  if FPixelMode <> Value then
  begin
    FPixelMode := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrBanner.CMColorChanged(var Message: TMessage);
begin
  inherited;
  if not (csLoading in ComponentState) then
    if FBitmap <> nil then CreateRasterImage;
end;

procedure TVrBanner.BitmapChanged(Sender: TObject);
begin
  if not (csLoading in ComponentState) then
  begin
    CreateRasterImage;
    BoundsRect := Bounds(Left, Top, Width, Height);
    if not AutoScroll then UpdateControlCanvas;
  end;
end;

function TVrBanner.StepSize: Integer;
begin
  Result := FPixelSize + FSpacing;
  if Result = 0 then Result := 1;
end;

procedure TVrBanner.Notify;
begin
  if Assigned(FOnScrollDone) then
    FOnScrollDone(Self);
end;

procedure TVrBanner.TimerEvent(Sender: TObject);
begin
  if FScrollInit then
  begin
    Reset;
    FScrollInit := false;
  end;

  case Direction of
    bdRightToLeft:
      begin
        if FDstX + FRaster.Width > 0 then
          Dec(FDstX, StepSize)
        else
        begin
          Notify;
          FDstX := ClientWidth - FPixelSize;
        end;
      end;

    bdLeftToRight:
      begin
        if (FDstX < Width) then
          Inc(FDstX, StepSize)
        else
        begin
          Notify;
          FDstX := -FRaster.Width;
        end;
      end;

    bdTopToBottom:
      begin
        if (FDstY < Height) then
          Inc(FDstY, StepSize)
        else
        begin
          Notify;
          FDstY := -FRaster.Height;
        end;
      end;

    bdBottomToTop:
      begin
        if FDstY + FRaster.Height > 0 then
          Dec(FDstY, StepSize)
        else
        begin
          Notify;
          FDstY := ClientHeight - FPixelSize;
        end;
      end;
  end; //case

  UpdateControlCanvas;
end;



end.
