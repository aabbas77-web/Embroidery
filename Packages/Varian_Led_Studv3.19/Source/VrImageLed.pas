{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrImageLed;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrConst, VrClasses, VrControls, VrSysUtils, VrThreads;

type
  TVrImageType = (itSound, itCD, itPlug, itMike, itPlayMedia, itSpeaker,
    itNote, itPlayBack, itFrequency, itRecord, itRewind, itReplay);

  TVrImageLed = class(TVrGraphicImageControl)
  private
    FActive: Boolean;
    FImageType: TVrImageType;
    FPalette: TVrPalette;
    FBlink: Boolean;
    FInverted: Boolean;
    FThreaded: Boolean;
    Bitmap: TBitmap;
    FTimer: TVrTimer;
    FOnChange: TNotifyEvent;
    function GetTimeInterval: Integer;
    procedure SetImageType(Value: TVrImageType);
    procedure SetActive(Value: Boolean);
    procedure SetTimeInterval(Value: Integer);
    procedure SetBlink(Value: Boolean);
    procedure SetInverted(Value: Boolean);
    procedure SetPalette(Value: TVrPalette);
    procedure SetThreaded(Value: Boolean);
    procedure PaletteModified(Sender: TObject);
    procedure OnTimerEvent(Sender: TObject);
  protected
    procedure LoadBitmaps;
    procedure DestroyBitmaps;
    procedure Paint; override;
    procedure Change; dynamic;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Blink: Boolean read FBlink write SetBlink default false;
    property Active: Boolean read FActive write SetActive default false;
    property ImageType: TVrImageType read FImageType write SetImageType default itSound;
    property Palette: TVrPalette read FPalette write SetPalette;
    property TimeInterval: Integer read GetTimeInterval write SetTimeInterval default 1000;
    property Inverted: Boolean read FInverted write SetInverted default false;
    property Transparent default false;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
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

{$R VRIMAGELED.D32}

const
  ImageTypeName: array[TVrImageType] of PChar = ('SOUND', 'CD', 'PLUG',
    'MIKE', 'PLAYMEDIA', 'SPEAKER', 'NOTE', 'PLAYBACK', 'FREQUENCY',
    'RECORD', 'REWIND', 'REPLAY');


{ TVrImageLed }

constructor TVrImageLed.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csReplicatable, csOpaque] -
    [csSetCaption, csDoubleClicks];
  Width := 40;
  Height := 40;
  Color := clBlack;
  ParentColor := false;
  FActive := false;
  FBlink := false;
  FImageType := itSound;
  FInverted := false;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  Bitmap := TBitmap.Create;
  LoadBitmaps;
  FThreaded := True;
  FTimer := TVrTimer.Create(Self);
  FTimer.Enabled := false;
  FTimer.Interval := 1000;
  FTimer.OnTimer := OnTimerEvent;
end;

destructor TVrImageLed.Destroy;
begin
  FTimer.Free;
  FPalette.Free;
  DestroyBitmaps;
  inherited Destroy;
end;

procedure TVrImageLed.LoadBitmaps;
var
  ResName: array[0..40] of Char;
begin
  Bitmap.Handle := LoadBitmap(HInstance,
    StrFmt(ResName, 'IT_%s', [ImageTypeName[FImageType]]));
  FPalette.ToBMP(Bitmap, ResColorLow, ResColorHigh);
end;

procedure TVrImageLed.DestroyBitmaps;
begin
  Bitmap.Free;
end;

procedure TVrImageLed.SetImageType(Value: TVrImageType);
begin
  if FImageType <> Value then
  begin
    FImageType := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrImageLed.Change;
begin
  if Assigned(FOnChange) then
    FOnChange(Self);
end;

procedure TVrImageLed.SetActive(Value: Boolean);
begin
  if (FBlink and Designing) then
    Value := false;
  if FActive <> Value then
  begin
    FActive := Value;
    UpdateControlCanvas;
    Change;
  end;
end;

procedure TVrImageLed.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

procedure TVrImageLed.SetTimeInterval(Value: Integer);
begin
  FTimer.Interval := Value;
end;

procedure TVrImageLed.SetBlink(Value: Boolean);
begin
  if FBlink <> Value then
  begin
    FBlink := Value;
    if FBlink then Active := false;
    if not (csDesigning in ComponentState) then
      FTimer.Enabled := Value;
  end;
end;

procedure TVrImageLed.SetInverted(Value: Boolean);
begin
  if FInverted <> Value then
  begin
    FInverted := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrImageLed.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;

function TVrImageLed.GetTimeInterval: Integer;
begin
  Result := FTimer.Interval;
end;

procedure TVrImageLed.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrImageLed.Paint;
var
  ImageWidth, Offset: Integer;
  X, Y: Integer;
  R: TRect;
begin
  ClearBitmapCanvas;
  ImageWidth := Bitmap.Width div 2;
  Offset := ImageWidth * ord(FActive);

  X := (ClientWidth - ImageWidth) div 2;
  Y := (ClientHeight - Bitmap.Height) div 2;

  if FInverted then
  begin
    R := ClientRect;
    BitmapCanvas.Brush.Color := FPalette.Colors[ord(FActive)];
    BitmapCanvas.FillRect(R);
    BitBlt(BitmapCanvas.Handle, X, Y, ImageWidth, Bitmap.Height,
      Bitmap.Canvas.Handle, Offset, 0, SRCINVERT);
  end
 else
  with BitmapCanvas do
  begin
    Brush.Style := bsClear;
    BrushCopy(Bounds(X, Y, ImageWidth, Bitmap.Height), Bitmap,
       Bounds(Offset, 0, ImageWidth, Bitmap.Height), clBlack);
  end;

  inherited Paint;
end;

procedure TVrImageLed.OnTimerEvent(Sender: TObject);
begin
  Active := not Active;
end;


end.
