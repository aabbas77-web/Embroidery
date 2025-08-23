{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrTrayGauge;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, VrSystem, VrSysUtils;


type
  TVrTrayGaugeStyle = (gsSingle, gsDual);
  TVrTrayGauge = class(TVrCustomTrayIcon)
  private
    FMin: Integer;
    FMax: Integer;
    FPosition: Integer;
    FOnChange: TNotifyEvent;
    FPalette: TVrPalette;
    FStyle: TVrTrayGaugeStyle;
    ResName: string;
    ImageList: TImageList;
    Bitmap: TBitMap;
    procedure SetMin(Value: Integer);
    procedure SetMax(Value: Integer);
    procedure SetPosition(Value: Integer);
    procedure SetStyle(Value: TVrTrayGaugeStyle);
    procedure SetPalette(Value: TVrPalette);
    procedure UpdateTrayIcon;
    procedure PaletteModified(Sender: TObject);
  protected
    procedure Loaded; override;
    procedure LoadBitmaps;
    function IconIndex: Integer;
    procedure Change;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Palette: TVrPalette read FPalette write SetPalette;
    property Max: Integer read FMax write SetMax default 100;
    property Min: Integer read FMin write SetMin default 0;
    property Position: Integer read FPosition write SetPosition default 0;
    property Style: TVrTrayGaugeStyle read FStyle write SetStyle default gsSingle;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property Visible;
    property Enabled;
    property Hint;
    property ShowHint;
    property PopupMenu;
    property HideTaskBtn;
    property LeftBtnPopup;
    property OnClick;
    property OnDblClick;
    property OnMouseDown;
    property OnMouseUp;
    property OnMouseMove;
  end;


implementation

{$R VRTRAYGAUGE.D32}

const
  ImageCount = 12;
  MaskColor = $00B8CCB5;


constructor TVrTrayGauge.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FMin := 0;
  FMax := 100;
  FPosition := 0;
  FStyle := gsSingle;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  ImageList := TImageList.Create(nil);
  ImageList.Width := 15;
  ResName := 'ICGAUGE';
  Bitmap := TBitMap.Create;
  LoadBitmaps;
end;

destructor TVrTrayGauge.Destroy;
begin
  Bitmap.Free;
  ImageList.Free;
  FPalette.Free;
  inherited Destroy;
end;

procedure TVrTrayGauge.Loaded;
begin
  inherited Loaded;
  LoadBitmaps;
  UpdateTrayIcon;
end;

function TVrTrayGauge.IconIndex: Integer;
begin
  Result := (ImageCount * (FPosition - FMin)) div (FMax - FMin);
end;

procedure TVrTrayGauge.Change;
begin
  if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrTrayGauge.UpdateTrayIcon;
begin
  ImageList.GetIcon(IconIndex, Icon);
end;

procedure TVrTrayGauge.SetMin(Value: Integer);
begin
  if FMin <> Value then
  begin
    FMin := MinIntVal(Value, FMax - 1);
    AdjustRange(FPosition, FMin, FMax);
    UpdateTrayIcon;
  end;
end;

procedure TVrTrayGauge.SetMax(Value: Integer);
begin
  if FMax <> Value then
  begin
    FMax := MaxIntVal(FMin + 1, Value);
    AdjustRange(FPosition, FMin, FMax);
    UpdateTrayIcon;
  end;
end;

procedure TVrTrayGauge.SetPosition(Value: Integer);
begin
  if FPosition <> Value then
  begin
    FPosition := Value;
    AdjustRange(FPosition, FMin, FMax);
    UpdateTrayIcon;
    Change;
  end;
end;

procedure TVrTrayGauge.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrTrayGauge.LoadBitmaps;
begin
  Bitmap.Handle := LoadBitmap(hInstance, PChar(ResName));
  FPalette.ToBMP(Bitmap, clGreen, clLime);
  ImageList.Clear;
  ImageList.AddMasked(Bitmap, MaskColor);
end;

procedure TVrTrayGauge.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateTrayIcon;
end;

procedure TVrTrayGauge.SetStyle(Value: TVrTrayGaugeStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    if FStyle = gsSingle then ResName := 'ICGAUGE'
      else ResName := 'ICLEVELS';
    LoadBitmaps;
    UpdateTrayIcon;
  end;
end;



end.
