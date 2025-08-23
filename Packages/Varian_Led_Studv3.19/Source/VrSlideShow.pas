{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrSlideShow;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils, VrThreads;

type
  TVrTransitionEffect =
   (StretchFromLeft, StretchFromRight, StretchFromTop,
    StretchFromBottom, StretchFromTopLeft, StretchFromBottomRight,
    StretchFromXcenter, StretchFromYcenter, PushFromBottom, PushFromLeft,
    PushFromRight, PushFromTop, SlideFromLeft, SlideFromRight, SlideFromTop,
    SlideFromBottom, SlideFromTopLeft, SlideFromBottomRight,Zoom);

  TVrSlideShow = class(TVrGraphicImageControl)
  private
    FActive: Boolean;
    FImageOrg: TBitmap;
    FImageNew: TBitmap;
    FCurrentStep: Integer;
    FSteps: Integer;
    FLoop: Boolean;
    FTransition: TVrTransitionEffect;
    FAnimateInit: Boolean;
    FTimer: TVrTimer;
    FThreaded: Boolean;
    FOnNotify: TNotifyEvent;
    sglGrowX, sglGrowY: Double;
    function GetInterval: Integer;
    procedure SetActive(Value: Boolean);
    procedure SetInterval(Value: Integer);
    procedure SetImageOrg(Value: TBitmap);
    procedure SetImageNew(Value: TBitmap);
    procedure SetSteps(Value: Integer);
    procedure SetTransition(Value: TVrTransitionEffect);
    procedure SetThreaded(Value: Boolean);
    procedure TimerEvent(Sender: TObject);
    procedure ImageChanged(Sender: TObject);
  protected
    procedure CalcViewParams;
    procedure Paint; override;
    procedure Step;
  public
    destructor Destroy; override;
    constructor Create(AOwner: TComponent);override;
    procedure ExchangeImages(DoPaint: Boolean);
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Interval: integer read GetInterval write SetInterval;
    property ImageOrg: TBitmap read FImageOrg write SetImageOrg;
    property ImageNew: TBitmap read FImageNew write SetImageNew;
    property Steps: integer read FSteps write SetSteps default 10;
    property Transition: TVrTransitionEffect read FTransition write SetTransition;
    property Loop: Boolean read FLoop write FLoop default True;
    property Active: Boolean read FActive write SetActive default false;
    property OnNotify: TNotifyEvent read FOnNotify Write FOnNotify;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Align;
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


constructor TVrSlideShow.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Width := 110;
  Height := 110;
  FActive := false;
  FSteps := 10;
  FLoop := True;
  FImageOrg := TBitmap.Create;
  FImageOrg.OnChange := ImageChanged;
  FImageNew := TBitmap.Create;
  FImageNew.OnChange := ImageChanged;
  FThreaded := True;
  FTimer := TVrTimer.Create(self);
  FTimer.Enabled := False;
  FTimer.OnTimer := TimerEvent;
  FTimer.Interval := 100;
end;

destructor TVrSlideShow.Destroy;
begin
  FTimer.Free;
  FImageOrg.Free;
  FImageNew.Free;
  inherited Destroy;
end;

procedure TVrSlideShow.CalcViewParams;
begin
  sglGrowX := Width / FSteps;
  sglGrowY := Height / FSteps;
  FCurrentStep := 0;
end;

procedure TVrSlideShow.Paint;
begin
  ClearBitmapCanvas;

  if not ImageOrg.Empty then
  begin
    BitmapCanvas.Brush.Style := bsSolid;
    BitmapCanvas.CopyRect(ClientRect, ImageOrg.Canvas,
      Rect(0, 0, ImageOrg.Width, ImageOrg.Height));
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

procedure TVrSlideShow.Step;
var
  IntLeft, IntRight, IntTop, IntBottom: Integer;
begin
  if (ImageNew.Empty) or (ImageOrg.Empty) then
  begin
    Active := false;
    raise EVrException.Create('Transition bitmap(s) not assigned.');
  end;

  IntRight := Width;
  IntTop := 0;
  IntBottom := Height;

  case FTransition of
   SlideFromLeft,
   SlideFromTopLeft,
   PushFromLeft: IntLeft := Trunc((sglGrowX * FCurrentStep) - Width);
   StretchFromBottomRight,
   StretchFromRight,
   SlideFromRight,
   SlideFromBottomRight,
   PushFromRight: IntLeft := Trunc(Width - (sglGrowX * FCurrentStep));
   Zoom,
   StretchFromXcenter: IntLeft := Trunc((Width - (sglGrowX * FCurrentStep)) / 2);
   else
     IntLeft:=0;
  end;

  case FTransition of
    SlideFromRight,
    SlideFromBottomRight,
    PushFromRight: IntRight := Trunc((Width * 2) - (sglGrowX * FCurrentStep));
    StretchFromLeft,
    StretchFromTopLeft,
    SlideFromLeft,
    SlideFromTopLeft,
    PushFromLeft: IntRight := Trunc(sglGrowX * FCurrentStep);
    Zoom,
    StretchFromXcenter: IntRight := IntLeft + Trunc(sglGrowX * FCurrentStep);
  end;

  case FTransition of
    SlideFromTop,
    SlideFromTopLeft,
    PushFromTop: IntTop := Trunc((sglGrowY * FCurrentStep) - Height);
    StretchFromBottom,
    StretchFromBottomRight,
    SlideFromBottom,
    SlideFromBottomRight,
    PushFromBottom: IntTop := Trunc(Height - (sglGrowY * FCurrentStep));
    Zoom,
    StretchFromYcenter: IntTop := Trunc((Height - (sglGrowY * FCurrentStep)) / 2);
  end;

  case FTransition of
    SlideFromBottom,
    SlideFromBottomRight,
    PushFromBottom: IntBottom := Trunc((Height * 2) - (sglGrowY * FCurrentStep));
    StretchFromTop,
    StretchFromTopLeft,
    SlideFromTop,
    SlideFromTopLeft,
    PushFromTop: IntBottom := Trunc(sglGrowY * FCurrentStep);
    Zoom,
    StretchFromYcenter: IntBottom := IntTop + Trunc(sglGrowY * FCurrentStep);
  end;

  BitmapCanvas.CopyRect(Rect(IntLeft, IntTop, IntRight, IntBottom),
    FImageNew.Canvas, Rect(0, 0, FImageNew.Width, FImageNew.Height));

  case FTransition of
    PushFromBottom:
      BitmapCanvas.CopyRect(Rect(0, IntTop - Height, Width, IntTop),
        FImageOrg.Canvas, Rect(0, 0, ImageOrg.Width, ImageOrg.Height));
    PushFromLeft:
      BitmapCanvas.CopyRect(Rect(IntRight, 0, IntRight + Width, Height),
        ImageOrg.Canvas, Rect(0, 0, ImageOrg.Width, ImageOrg.Height));
    PushFromRight:
      BitmapCanvas.CopyRect(Rect(IntLeft - Width, 0, IntLeft, Height),
        ImageOrg.Canvas, Rect(0, 0, ImageOrg.Width, ImageOrg.Height));
    PushFromTop:
      BitmapCanvas.CopyRect(Rect(0, IntBottom, Width, IntBottom + Height),
        ImageOrg.Canvas, Rect(0, 0, ImageOrg.Width, ImageOrg.Height));
  end;

  Inc(FCurrentStep);
  if FCurrentStep > FSteps then
  begin
    if Loop then
    begin
      FCurrentStep := 0;
      ExchangeImages(false);
      UpdateControlCanvas;
    end
    else
    begin
      Active := false;
      ExchangeImages(True);
      if Assigned(OnNotify) then OnNotify(Self);
    end;
  end;
  inherited Paint;
end;

procedure TVrSlideShow.TimerEvent(Sender: TObject);
begin
  if FAnimateInit then
  begin
    CalcViewParams;
    FAnimateInit := false;
  end else Step;
end;

procedure TVrSlideShow.ExchangeImages(DoPaint: Boolean);
var
  Tmp: TBitmap;
begin
  Tmp := FImageNew;
  FImageNew := FImageOrg;
  FImageOrg := Tmp;
  if (not Active) and (DoPaint) then
    UpdateControlCanvas;
end;

procedure TVrSlideShow.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    if Designing then Exit;
    FTimer.Enabled := Value;
    if Value then FAnimateInit := True
    else UpdateControlCanvas;
  end;
end;

procedure TVrSlideShow.SetTransition(Value: TVrTransitionEffect);
var
  IsActive: Boolean;
begin
  if FTransition <> Value then
  begin
    FTransition := Value;
    IsActive := Active;
    Active := false;
    UpdateControlCanvas;
    Active := IsActive;
  end;
end;

procedure TVrSlideShow.ImageChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrSlideShow.SetImageNew(Value: TBitmap);
begin
  FImageNew.Assign(Value);
end;

procedure TVrSlideShow.SetImageOrg(Value: TBitmap);
begin
  ImageOrg.Assign(Value);
end;

procedure TVrSlideShow.SetSteps(Value: Integer);
begin
  if (Value > 0) and (Value < Height) and (Value < Width) then
    FSteps := Value
end;

function TVrSlideShow.GetInterval: Integer;
begin
  Result := FTimer.Interval;
end;

procedure TVrSlideShow.SetInterval(Value: Integer);
begin
  FTimer.Interval := Value;
end;

procedure TVrSlideShow.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;



end.
