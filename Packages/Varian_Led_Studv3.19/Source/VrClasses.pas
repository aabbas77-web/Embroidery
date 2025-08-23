{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrClasses;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrSysUtils;


type
  TVrPersistent = class(TPersistent)
  private
    FUpdateCount: Integer;
    FOnChange: TNotifyEvent;
  protected
    procedure Changed;
  public
    procedure BeginUpdate;
    procedure EndUpdate;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  end;

  TVrBevelStyle = (bsNone, bsLowered, bsRaised);
  TVrBevelOutlineStyle = (osOuter, osInner, osNone);
  TVrBevelWidth = 1..MaxInt;
  TVrBorderWidth = 0..MaxInt;
  TVrBevelSpace = 0..MaxInt;

  TVrBevel = class(TVrPersistent)
  private
    FInnerShadow: TColor;
    FInnerHighlight: TColor;
    FInnerWidth: TVrBevelWidth;
    FInnerStyle: TVrBevelStyle;
    FInnerOutline: TVrBevelOutlineStyle;
    FInnerSpace: TVrBevelSpace;
    FInnerColor: TColor;
    FOuterShadow: TColor;
    FOuterHighlight: TColor;
    FOuterWidth: TVrBevelWidth;
    FOuterStyle: TVrBevelStyle;
    FOuterOutline: TVrBevelOutlineStyle;
    FOuterSpace: TVrBevelSpace;
    FOuterColor: TColor;
    procedure SetInnerShadow(Value: TColor);
    procedure SetInnerHighlight(Value: TColor);
    procedure SetInnerWidth(Value: TVrBevelWidth);
    procedure SetInnerStyle(Value: TVrBevelStyle);
    procedure SetInnerOutline(Value: TVrBevelOutlineStyle);
    procedure SetInnerSpace(Value: TVrBevelSpace);
    procedure SetInnerColor(Value: TColor);
    procedure SetOuterShadow(Value: TColor);
    procedure SetOuterHighlight(Value: TColor);
    procedure SetOuterWidth(Value: TVrBevelWidth);
    procedure SetOuterStyle(Value: TVrBevelStyle);
    procedure SetOuterOutline(Value: TVrBevelOutlineStyle);
    procedure SetOuterSpace(Value: TVrBevelSpace);
    procedure SetOuterColor(Value: TColor);
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
    procedure GetVisibleArea(var Rect: TRect);
    procedure Paint(Canvas: TCanvas; var Rect: TRect);
  published
    property InnerShadow: TColor read FInnerShadow write SetInnerShadow;
    property InnerHighlight: TColor read FInnerHighlight write SetInnerHighlight;
    property InnerWidth: TVrBevelWidth read FInnerWidth write SetInnerWidth;
    property InnerStyle: TVrBevelStyle read FInnerStyle write SetInnerStyle;
    property InnerOutline: TVrBevelOutlineStyle read FInnerOutline write SetInnerOutline;
    property InnerSpace: TVrBevelSpace read FInnerSpace write SetInnerSpace;
    property InnerColor: TColor read FInnerColor write SetInnerColor;
    property OuterShadow: TColor read FOuterShadow write SetOuterShadow;
    property OuterHighlight: TColor read FOuterHighlight write SetOuterHighlight;
    property OuterWidth: TVrBevelWidth read FOuterWidth write SetOuterWidth;
    property OuterStyle: TVrBevelStyle read FOuterStyle write SetOuterStyle;
    property OuterOutline: TVrBevelOutlineStyle read FOuterOutline write SetOuterOutline;
    property OuterSpace: TVrBevelSpace read FOuterSpace write SetOuterSpace;
    property OuterColor: TColor read FOuterColor write SetOuterColor;
  end;

  TVrPalette = class(TVrPersistent)
  private
    FLow: TColor;
    FHigh: TColor;
    procedure SetLow(Value: TColor);
    procedure SetHigh(Value: TColor);
    function GetColors(Index: Integer): TColor; virtual;
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
    procedure ToBMP(Bitmap: TBitmap; DarkColor, LightColor: TColor);
    property Colors[Index: Integer]: TColor read GetColors; default;
  published
    property Low: TColor read FLow write SetLow;
    property High: TColor read FHigh write SetHigh;
  end;

  TVrMinMax = class(TVrPersistent)
  private
    FMinValue: Integer;
    FMaxValue: Integer;
    FPosition: Integer;
    procedure SetMinValue(Value: Integer);
    procedure SetMaxValue(Value: Integer);
    procedure SetPosition(Value: Integer);
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
  published
    property MinValue: Integer read FMinValue write SetMinValue;
    property MaxValue: Integer read FMaxValue write SetMaxValue;
    property Position: Integer read FPosition write SetPosition;
  end;

  TVrTextOutline = class(TVrPersistent)
  private
    FColor: TColor;
    FVisible: Boolean;
    procedure SetColor(Value: TColor);
    procedure SetVisible(Value: Boolean);
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
  published
    property Color: TColor read FColor write SetColor default clNavy;
    property Visible: Boolean read FVisible write SetVisible default True;
  end;

  TVrBitmaps = class(TVrPersistent)
  private
    FItems: TList;
    function GetCount: Integer;
    function GetBitmap(Index: Integer): TBitmap;
    procedure SetBitmap(Index: Integer; Value: TBitmap);
    procedure ReadData(Stream: TStream);
    procedure WriteData(Stream: TStream);
  protected
    procedure DefineProperties(Filer: TFiler); override;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Clear;
    procedure Assign(Source: TPersistent); override;
    function Add(Value: TBitmap): Integer;
    procedure Delete(Index: Integer);
    procedure Insert(Index: Integer; Value: TBitmap);
    procedure Exchange(Index1, Index2: Integer);
    procedure Move(CurIndex, NewIndex: Integer);
    function IndexOf(Bitmap: TBitmap): Integer;
    procedure LoadFromStream(Stream: TStream); virtual;
    procedure SaveToStream(Stream: TStream); virtual;
    procedure LoadFromFile(const FileName: string); virtual;
    procedure SaveToFile(const FileName: string); virtual;
    property Bitmaps[Index: Integer]: TBitmap read GetBitmap write SetBitmap; default;
    property Count: Integer read GetCount;
  end;

  TVrRect = class(TVrPersistent)
  private
    FLeft: Integer;
    FTop: Integer;
    FWidth: Integer;
    FHeight: Integer;
    function GetBoundsRect: TRect;
    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
    procedure SetBoundsRect(const Rect: TRect);
    procedure SetLeft(Value: Integer);
    procedure SetTop(Value: Integer);
    procedure SetWidth(Value: Integer);
    procedure SetHeight(Value: Integer);
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
    property BoundsRect: TRect read GetBoundsRect write SetBoundsRect;
  published
    property Left: Integer read FLeft write SetLeft default 0;
    property Top: Integer read FTop write SetTop default 0;
    property Width: Integer read FWidth write SetWidth default 0;
    property Height: Integer read FHeight write SetHeight default 0;
  end;

  TVrFont3DStyle = (f3dNone, f3dRaised, f3dSunken, f3dShadow);
  TVrFont3D = class(TVrPersistent)
  private
    FStyle: TVrFont3DStyle;
    FHighlightColor: TColor;
    FShadowColor: TColor;
    FHighlightDepth: Integer;
    FShadowDepth: Integer;
    procedure SetStyle(Value: TVrFont3DStyle);
    procedure SetHighlightColor(Value: TColor);
    procedure SetShadowColor(Value: TColor);
    procedure SetHighlightDepth(Value: Integer);
    procedure SetShadowDepth(Value: Integer);
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
    procedure Paint(Canvas: TCanvas; R: TRect;
      const Text: string; Flags: Integer);
  published
    property Style: TVrFont3DStyle read FStyle write SetStyle default f3dNone;
    property HighlightColor: TColor read FHighlightColor write SetHighlightColor default clBtnHighlight;
    property ShadowColor: TColor read FShadowColor write SetShadowColor default clBtnShadow;
    property HighlightDepth: Integer read FHighlightDepth write SetHighlightDepth default 1;
    property ShadowDepth: Integer read FShadowDepth write SetShadowDepth default 1;
  end;

const
  MaxIntListSize = MaxInt div 16;

type
  PVrIntArray = ^TVrIntArray;
  TVrIntArray = array[0..MaxIntListSize - 1] of Integer;

  TVrIntList = class(TObject)
  private
    FCount: Integer;
    FCapacity: Integer;
    FItems: PVrIntArray;
    procedure SetCapacity(NewCapacity: Integer);
    procedure SetCount(NewCount: Integer);
    procedure Grow;
    function GetCount: Integer;
    function GetItem(Index: Integer): Integer;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Clear;
    function Add(Value: Integer): Integer;
    procedure Delete(Index: Integer);
    property Count: Integer read GetCount;
    property Items[Index: Integer]: Integer read GetItem;
  end;

  TVrCollection = class;

  TVrCollectionItem = class(TObject)
  private
    FCollection: TVrCollection;
    FIndex: Integer;
    procedure SetCollection(Value: TVrCollection);
  protected
    procedure Changed(AllItems: Boolean);
  public
    constructor Create(Collection: TVrCollection); virtual;
    destructor Destroy; override;
    property Collection: TVrCollection read FCollection write SetCollection;
    property Index: Integer read FIndex write FIndex;
  end;

  TVrCollection = class(TObject)
  private
    FItems: TList;
    FUpdateCount: Integer;
    function GetCount: Integer;
    procedure InsertItem(Item: TVrCollectionItem);
    procedure RemoveItem(Item: TVrCollectionItem);
  protected
    procedure Changed;
    function GetItem(Index: Integer): TVrCollectionItem;
    procedure Update(Item: TVrCollectionItem); virtual;
    property UpdateCount: Integer read FUpdateCount;
  public
    constructor Create;
    destructor Destroy; override;
    procedure BeginUpdate; virtual;
    procedure Clear;
    procedure EndUpdate; virtual;
    property Count: Integer read GetCount;
    property Items[Index: Integer]: TVrCollectionItem read GetItem;
  end;


implementation

const
  BitmapsFileId: Integer = $355462;  //Define a unique stream format


{ TVrPersistent }

procedure TVrPersistent.Changed;
begin
  if FUpdateCount = 0 then
    if Assigned(FOnChange) then FOnChange(Self);
end;

procedure TVrPersistent.BeginUpdate;
begin
  Inc(FUpdateCount);
end;

procedure TVrPersistent.EndUpdate;
begin
  if FUpdateCount > 0 then Dec(FUpdateCount);
  Changed;
end;

{ TVrBevel }

constructor TVrBevel.Create;
begin
  inherited Create;
  FInnerShadow := clBtnShadow;
  FInnerHighlight := clBtnHighlight;
  FInnerWidth := 1;
  FInnerStyle := bsLowered;
  FInnerOutline := osNone;
  FInnerSpace := 1;
  FInnerColor := clBtnFace;
  FOuterShadow := clBtnShadow;
  FOuterHighlight := clBtnHighlight;
  FOuterWidth := 1;
  FOuterStyle := bsRaised;
  FOuterOutline := osOuter;
  FOuterSpace := 0;
  FOuterColor := clBtnFace;
end;

procedure TVrBevel.Assign(Source: TPersistent);
begin
  if (Source <> nil) and (Source is TVrBevel) then
  begin
    BeginUpdate;
    try
      InnerShadow := TVrBevel(Source).InnerShadow;
      InnerHighlight := TVrBevel(Source).InnerHighlight;
      InnerWidth := TVrBevel(Source).InnerWidth;
      InnerStyle := TVrBevel(Source).InnerStyle;
      InnerOutline := TVrBevel(Source).InnerOutline;
      InnerSpace := TVrBevel(Source).InnerSpace;
      InnerColor := TVrBevel(Source).InnerColor;
      OuterShadow := TVrBevel(Source).OuterShadow;
      OuterHighlight := TVrBevel(Source).OuterHighlight;
      OuterWidth := TVrBevel(Source).OuterWidth;
      OuterStyle := TVrBevel(Source).OuterStyle;
      OuterOutline := TVrBevel(Source).OuterOutline;
      OuterSpace := TVrBevel(Source).OuterSpace;
      OuterColor := TVrBevel(Source).OuterColor;
    finally
      EndUpdate;
    end;
  end else inherited Assign(Source);
end;

procedure TVrBevel.SetInnerShadow(Value: TColor);
begin
  if FInnerShadow <> Value then
  begin
    FInnerShadow := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetInnerHighlight(Value: TColor);
begin
  if FInnerHighlight <> Value then
  begin
    FInnerHighlight := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetInnerWidth(Value: TVrBevelWidth);
begin
  if FInnerWidth <> Value then
  begin
    FInnerWidth := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetInnerStyle(Value: TVrBevelStyle);
begin
  if FInnerStyle <> Value then
  begin
    FInnerStyle := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetInnerOutline(Value: TVrBevelOutlineStyle);
begin
  if FInnerOutline <> Value then
  begin
    FInnerOutline := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetInnerSpace(Value: TVrBevelSpace);
begin
  if FInnerSpace <> Value then
  begin
    FInnerSpace := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetInnerColor(Value: TColor);
begin
  if FInnerColor <> Value then
  begin
    FInnerColor := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetOuterShadow(Value: TColor);
begin
  if FOuterShadow <> Value then
  begin
    FOuterShadow := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetOuterHighlight(Value: TColor);
begin
  if FOuterHighlight <> Value then
  begin
    FOuterHighlight := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetOuterWidth(Value: TVrBevelWidth);
begin
  if FOuterWidth <> Value then
  begin
    FOuterWidth := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetOuterStyle(Value: TVrBevelStyle);
begin
  if FOuterStyle <> Value then
  begin
    FOuterStyle := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetOuterOutline(Value: TVrBevelOutlineStyle);
begin
  if FOuterOutline <> Value then
  begin
    FOuterOutline := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetOuterSpace(Value: TVrBevelSpace);
begin
  if FOuterSpace <> Value then
  begin
    FOuterSpace := Value;
    Changed;
  end;
end;

procedure TVrBevel.SetOuterColor(Value: TColor);
begin
  if FOuterColor <> Value then
  begin
    FOuterColor := Value;
    Changed;
  end;
end;

procedure TVrBevel.GetVisibleArea(var Rect: TRect);
var
  BevelPixels: Integer;
begin
  BevelPixels := 0;
  if FInnerOutline <> osNone then Inc(BevelPixels);
  if FOuterOutline <> osNone then Inc(BevelPixels);

  Inc(BevelPixels, FInnerSpace);
  Inc(BevelPixels, FOuterSpace);

  if FInnerStyle <> bsNone then Inc(BevelPixels, FInnerWidth);
  if FOuterStyle <> bsNone then Inc(BevelPixels, FOuterWidth);

  InflateRect(Rect, -BevelPixels, -BevelPixels);
end;

procedure TVrBevel.Paint(Canvas: TCanvas; var Rect: TRect);
var
  TopColor, BottomColor: TColor;

  procedure AdjustColors(BevelStyle: TVrBevelStyle;
    ShadowColor, HighlightColor: TColor);
  begin
    TopColor := HighlightColor;
    if (BevelStyle = bsLowered) then TopColor := ShadowColor;
    BottomColor := ShadowColor;
    if (BevelStyle = bsLowered) then BottomColor := HighlightColor;
  end;

begin
  if OuterOutline = osOuter then
    DrawFrame3D(Canvas, Rect, clBlack, clBlack, 1);

  if OuterStyle <> bsNone then
  begin
    AdjustColors(OuterStyle, OuterShadow, OuterHighlight);
    DrawFrame3D(Canvas, Rect, TopColor, BottomColor, OuterWidth);
  end;

  if OuterOutline = osInner then
    DrawFrame3D(Canvas, Rect, clBlack, clBlack, 1);

  DrawFrame3D(Canvas, Rect, OuterColor, OuterColor, OuterSpace);

  if InnerOutline = osOuter then
    DrawFrame3D(Canvas, Rect, clBlack, clBlack, 1);

  if InnerStyle <> bsNone then
  begin
    AdjustColors(InnerStyle, InnerShadow, InnerHighlight);
    DrawFrame3D(Canvas, Rect, TopColor, BottomColor, InnerWidth);
  end;

  if InnerOutline = osInner then
    DrawFrame3D(Canvas, Rect, clBlack, clBlack, 1);

  DrawFrame3D(Canvas, Rect, InnerColor, InnerColor, InnerSpace);
end;


{ TVrPalette }

constructor TVrPalette.Create;
begin
  inherited Create;
  FLow := clGreen;
  FHigh := clLime;
end;

procedure TVrPalette.SetLow(Value: TColor);
begin
  if FLow <> Value then
  begin
    FLow := Value;
    Changed;
  end;
end;

procedure TVrPalette.SetHigh(Value: TColor);
begin
  if FHigh <> Value then
  begin
    FHigh := Value;
    Changed;
  end;
end;

procedure TVrPalette.Assign(Source: TPersistent);
begin
  if (Source <> nil) and (Source is TVrPalette) then
  begin
    BeginUpdate;
    try
      Low := TVrPalette(Source).Low;
      High := TVrPalette(Source).High;
    finally
      EndUpdate;
    end;
  end else inherited Assign(Source);
end;

function TVrPalette.GetColors(Index: Integer): TColor;
begin
  Result := FLow;
  if Index > 0 then Result := FHigh;
end;

procedure TVrPalette.ToBMP(Bitmap: TBitmap; DarkColor, LightColor: TColor);
const
  ROP_DSPDxax = $00E20746;
var
  DestDC: HDC;
  DDB, MonoBmp: TBitmap;
  IWidth, IHeight: Integer;
  IRect: TRect;
begin
  IWidth := Bitmap.Width;
  IHeight := Bitmap.Height;
  IRect := Rect(0, 0, IWidth, IHeight);

  MonoBmp := TBitmap.Create;
  DDB := TBitmap.Create;
  try
    DDB.Assign(Bitmap);
    DDB.HandleType := bmDDB;

    with Bitmap.Canvas do
    begin
      MonoBmp.Width := IWidth;
      MonoBmp.Height := IHeight;
      MonoBmp.Monochrome := True;

      { Convert DarkColor to FLow }
      DDB.Canvas.Brush.Color := DarkColor;
      MonoBmp.Canvas.CopyRect(IRect, DDB.Canvas, IRect);

      Brush.Color := FLow;
      DestDC := Bitmap.Canvas.Handle;

      SetTextColor(DestDC, clBlack);
      SetBkColor(DestDC, clWhite);
      BitBlt(DestDC, 0, 0, IWidth, IHeight,
        MonoBmp.Canvas.Handle, 0, 0, ROP_DSPDxax);

      { Convert LightColor to FHigh }
      DDB.Canvas.Brush.Color := LightColor;
      MonoBmp.Canvas.CopyRect(IRect, DDB.Canvas, IRect);
      Brush.Color := FHigh;
      DestDC := Handle;
      SetTextColor(DestDC, clBlack);
      SetBkColor(DestDC, clWhite);
      BitBlt(DestDC, 0, 0, IWidth, IHeight,
        MonoBmp.Canvas.Handle, 0, 0, ROP_DSPDxax);
    end;
  finally
    DDB.Free;
    MonoBmp.Free;
  end;
end;


{ TVrMinMax }

constructor TVrMinMax.Create;
begin
  inherited Create;
  FMinValue := 0;
  FMaxValue := 100;
  FPosition := 0;
end;

procedure TVrMinMax.SetMinValue(Value: Integer);
begin
  if (FMinValue <> Value) and (Value < FMaxValue) then
  begin
    FMinValue :=  Value;
    if Position < Value then Position := Value
    else Changed;
  end;
end;

procedure TVrMinMax.SetMaxValue(Value: Integer);
begin
  if (FMaxValue <> Value) and (Value > FMinValue) then
  begin
    FMaxValue := Value;
    if Position > Value then Position := Value
    else Changed;
  end;
end;

procedure TVrMinMax.SetPosition(Value: Integer);
begin
  if Value < FMinValue then Value := FMinValue;
  if Value > FMaxValue then Value := FMaxValue;
  if FPosition <> Value then
  begin
    FPosition := Value;
    Changed;
  end;
end;

procedure TVrMinMax.Assign(Source: TPersistent);
begin
  if Source is TVrMinMax then
  begin
    BeginUpdate;
    try
      MinValue := TVrMinMax(Source).MinValue;
      MaxValue := TVrMinMax(Source).MaxValue;
      Position := TVrMinMax(Source).Position;
    finally
      EndUpdate;
    end;
  end
  else inherited Assign(Source);
end;

{ TVrTextOutline }

constructor TVrTextOutline.Create;
begin
  inherited Create;
  FColor := clNavy;
  FVisible := True;
end;

procedure TVrTextOutline.SetColor(Value: TColor);
begin
  if FColor <> Value then
  begin
    FColor :=  Value;
    Changed;
  end;
end;

procedure TVrTextOutline.SetVisible(Value: Boolean);
begin
  if FVisible <> Value then
  begin
    FVisible := Value;
    Changed;
  end;
end;

procedure TVrTextOutline.Assign(Source: TPersistent);
begin
  if Source is TVrTextOutline then
  begin
    BeginUpdate;
    try
      Color := TVrTextOutline(Source).Color;
      Visible := TVrTextOutline(Source).Visible;
    finally
      EndUpdate;
    end;
    Exit;
  end;
  inherited Assign(Source);
end;

{ TVrFont3D }

constructor TVrFont3D.Create;
begin
  inherited Create;
  FStyle := f3dNone;
  FHighlightColor := clBtnHighlight;
  FShadowColor := clBtnShadow;
  FHighlightDepth := 1;
  FShadowDepth := 1;
end;

procedure TVrFont3D.Assign(Source: TPersistent);
begin
  if Source is TVrFont3D then
  begin
    BeginUpdate;
    try
      Style := TVrFont3D(Source).Style;
      HighlightColor := TVrFont3D(Source).HighlightColor;
      ShadowColor := TVrFont3D(Source).ShadowColor;
      HighlightDepth := TVrFont3D(Source).HighlightDepth;
      ShadowDepth := TVrFont3D(Source).ShadowDepth;
    finally
      EndUpdate;
    end;
    Exit;
  end;
  inherited Assign(Source);
end;

procedure TVrFont3D.SetStyle(Value: TVrFont3DStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    Changed;
  end;
end;

procedure TVrFont3D.SetHighlightColor(Value: TColor);
begin
  if FHighlightColor <> Value then
  begin
    FHighlightColor := Value;
    Changed;
  end;
end;

procedure TVrFont3D.SetShadowColor(Value: TColor);
begin
  if FShadowColor <> Value then
  begin
    FShadowColor := Value;
    Changed;
  end;
end;

procedure TVrFont3D.SetHighlightDepth(Value: Integer);
begin
  if FHighlightDepth <> Value then
  begin
    FHighlightDepth := Value;
    Changed;
  end;
end;

procedure TVrFont3D.SetShadowDepth(Value: Integer);
begin
  if FShadowDepth <> Value then
  begin
    FShadowDepth := Value;
    Changed;
  end;
end;

procedure TVrFont3D.Paint(Canvas: TCanvas; R: TRect; const Text: string; Flags: Integer);
var
  DestRect: TRect;
  OrgColor: TColor;
begin
  with Canvas do
  begin
    OrgColor := Font.Color;
    Brush.Style := bsClear;
    case Style of
      f3dNone: DrawText(Handle, PChar(Text), -1, R, Flags);
      f3dRaised:
        begin
          Font.Color := ShadowColor;
          DestRect := R;
          OffsetRect(DestRect, ShadowDepth, ShadowDepth);
          DrawText(Handle, PChar(Text), -1, DestRect, Flags);

          Font.Color := HighlightColor;
          DestRect := R;
          OffsetRect(DestRect, - HighlightDepth, - HighlightDepth);
          DrawText(Handle, PChar(Text), -1, DestRect, Flags);

          Font.Color := OrgColor;
          DrawText(Handle, PChar(Text), -1, R, Flags);
        end;
      f3dSunken:
        begin
          Font.Color := HighlightColor;
          DestRect := R;
          OffsetRect(DestRect, HighlightDepth, HighlightDepth);
          DrawText(Handle, PChar(Text), -1, DestRect, Flags);

          Font.Color := ShadowColor;
          DestRect := R;
          OffsetRect(DestRect, -ShadowDepth, -ShadowDepth);
          DrawText(Handle, PChar(Text), -1, DestRect, Flags);

          Font.Color := OrgColor;
          DrawText(Handle, PChar(Text), -1, R, Flags);
        end;
      f3dShadow:
        begin
          Font.Color := ShadowColor;
          DestRect := R;
          OffsetRect(DestRect, ShadowDepth, ShadowDepth);
          DrawText(Handle, PChar(Text), -1, DestRect, Flags);

          Font.Color := OrgColor;
          DrawText(Handle, PChar(Text), -1, R, Flags);
        end;
    end; //case
  end;
end;

{ TVrBitmaps }

constructor TVrBitmaps.Create;
begin
  inherited;
  FItems := TList.Create;
end;

destructor TVrBitmaps.Destroy;
begin
  OnChange := nil;
  if FItems <> nil then Clear;
  FItems.Free;
  inherited Destroy;
end;

procedure TVrBitmaps.Clear;
var
  I: Integer;
begin
  BeginUpdate;
  try
    for I := 0 to Count - 1 do
      TBitmap(FItems[I]).Free;
    FItems.Clear;
  finally
    EndUpdate;
  end;
  Changed;
end;

function TVrBitmaps.Add(Value: TBitmap): Integer;
begin
  Result := FItems.Add(nil);
  FItems[Result] := TBitmap.Create;
  Bitmaps[Result].Assign(Value);
  Changed;
end;

procedure TVrBitmaps.Insert(Index: Integer; Value: TBitmap);
begin
  FItems.Insert(Index, nil);
  FItems[Index] := TBitmap.Create;
  Bitmaps[Index].Assign(Value);
  Changed;
end;

procedure TVrBitmaps.Delete(Index: Integer);
begin
  TBitmap(FItems[Index]).Free;
  FItems.Delete(Index);
  Changed;
end;

procedure TVrBitmaps.Exchange(Index1, Index2: Integer);
begin
  FItems.Exchange(Index1, Index2);
  Changed;
end;

function TVrBitmaps.IndexOf(Bitmap: TBitmap): Integer;
begin
  Result := FItems.IndexOf(Bitmap);
end;

procedure TVrBitmaps.Move(CurIndex, NewIndex: Integer);
begin
  FItems.Move(CurIndex, NewIndex);
  Changed;
end;

function TVrBitmaps.GetCount: Integer;
begin
  Result := FItems.Count;
end;

function TVrBitmaps.GetBitmap(Index: Integer): TBitmap;
begin
  Result := FItems[Index];
end;

procedure TVrBitmaps.SetBitmap(Index: Integer; Value: TBitmap);
begin
  Bitmaps[Index].Assign(Value);
end;

procedure TVrBitmaps.Assign(Source: TPersistent);
var
  I: Integer;
begin
  if Source = nil then Clear
  else if Source is TVrBitmaps then
  begin
    BeginUpdate;
    try
      Clear;
      for I := 0 to TVrBitmaps(Source).Count - 1 do
        Add(TVrBitmaps(Source).Bitmaps[I]);
    finally
      EndUpdate;
    end;
  end;
end;

procedure TVrBitmaps.ReadData(Stream: TStream);
begin
  BeginUpdate;
  try
    Clear;
    LoadFromStream(Stream);
  finally
    EndUpdate;
  end;
end;

procedure TVrBitmaps.WriteData(Stream: TStream);
begin
  BeginUpdate;
  try
    SaveToStream(Stream);
  finally
    EndUpdate;
  end;
end;

procedure TVrBitmaps.DefineProperties(Filer: TFiler);

  function DoWrite: Boolean;
  begin
    Result := Count > 0;
  end;

begin
  Filer.DefineBinaryProperty('Bitmaps', ReadData, WriteData, DoWrite);
end;

procedure TVrBitmaps.LoadFromStream(Stream: TStream);
var
  Bitmap: TBitmap;
  I, Id, Cnt: Integer;
begin
  Bitmap := TBitmap.Create;
  try
    Stream.Read(Id, Sizeof(Integer));
    if BitmapsFileId <> Id then raise Exception.Create('Invalid file format');
    Stream.Read(Cnt, Sizeof(Integer));
    for I := 0 to Cnt - 1 do
    begin
      Bitmap.LoadFromStream(Stream);
      Add(Bitmap);
    end;
  finally
    Bitmap.Free;
  end;
end;

procedure TVrBitmaps.SaveToStream(Stream: TStream);
var
  I, Cnt: Integer;
begin
  Stream.Write(BitmapsFileId, Sizeof(Integer));
  Cnt := Count;
  Stream.Write(Cnt, Sizeof(Integer));
  for I := 0 to Count - 1 do
    TBitmap(Bitmaps[I]).SaveToStream(Stream);
end;

procedure TVrBitmaps.LoadFromFile(const FileName: string);
var
  Stream: TFileStream;
begin
  Stream := TFileStream.Create(FileName, fmOpenRead);
  try
    LoadFromStream(Stream);
  finally
    Stream.Free;
  end;
end;

procedure TVrBitmaps.SaveToFile(const FileName: string);
var
  Stream: TFileStream;
begin
  Stream := TFileStream.Create(FileName, fmCreate);
  try
    SaveToStream(Stream);
  finally
    Stream.Free;
  end;
end;

{ TVrIntList }

constructor TVrIntList.Create;
begin
  inherited Create;
  FCount := 0;
  FCapacity := 0;
end;

destructor TVrIntList.Destroy;
begin
  Clear;
  inherited Destroy;
end;

procedure TVrIntList.Clear;
begin
  SetCount(0);
  SetCapacity(0);
end;

function TVrIntList.GetCount: Integer;
begin
  Result := FCount;
end;

function TVrIntList.GetItem(Index: Integer): Integer;
begin
  Result := FItems[Index];
end;

function TVrIntList.Add(Value: Integer): Integer;
begin
  Result := FCount;
  if Result = FCapacity then Grow;
  FItems^[Result] := Value;
  Inc(FCount);
end;

procedure TVrIntList.Delete(Index: Integer);
begin
  if (Index < 0) or (Index >= FCount) then
    Exception.Create('TVrIntList index out of bounds');
  Dec(FCount);
  if Index < FCount then
    System.Move(FItems^[Index + 1], FItems^[Index],
    (FCount - Index) * SizeOf(Integer));
end;

procedure TVrIntList.Grow;
var
  Delta: Integer;
begin
  if FCapacity > 64 then Delta := FCapacity div 4 else
    if FCapacity > 8 then Delta := 16 else
      Delta := 4;
  SetCapacity(FCapacity + Delta);
end;

procedure TVrIntList.SetCapacity(NewCapacity: Integer);
begin
  if (NewCapacity < FCount) or (NewCapacity > MaxIntListSize) then
    Exception.Create('TVrIntList Capacity overrun');
  if NewCapacity <> FCapacity then
  begin
    ReallocMem(FItems, NewCapacity * SizeOf(Integer));
    FCapacity := NewCapacity;
  end;
end;

procedure TVrIntList.SetCount(NewCount: Integer);
begin
  if (NewCount < 0) or (NewCount > MaxListSize) then
    Exception.Create('TVrIntList Count overrun');
  if NewCount > FCapacity then SetCapacity(NewCount);
  if NewCount > FCount then
    FillChar(FItems^[FCount], (NewCount - FCount) * SizeOf(Integer), 0);
  FCount := NewCount;
end;

{ TVrRect }

constructor TVrRect.Create;
begin
  FLeft := 0;
  FTop := 0;
  FWidth := 0;
  FHeight := 0;
end;

procedure TVrRect.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  if (FLeft <> ALeft) or (FTop <> ATop) or
     (FWidth <> AWidth) or (FHeight <> AHeight) then
  begin
    FLeft := ALeft;
    FTop := ATop;
    FWidth := AWidth;
    FHeight := AHeight;
    Changed;
  end;
end;

procedure TVrRect.Assign(Source: TPersistent);
begin
  if (Source <> nil) and (Source is TVrRect) then
  begin
    BeginUpdate;
    try
      Left := (Source as TVrRect).Left;
      Top := (Source as TVrRect).Top;
      Width := (Source as TVrRect).Width;
      Height := (Source as TVrRect).Height;
    finally
      EndUpdate;
    end;
  end;
  inherited Assign(Source);
end;

procedure TVrRect.SetLeft(Value: Integer);
begin
  SetBounds(Value, FTop, FWidth, FHeight);
end;

procedure TVrRect.SetTop(Value: Integer);
begin
  SetBounds(FLeft, Value, FWidth, FHeight);
end;

procedure TVrRect.SetWidth(Value: Integer);
begin
  SetBounds(FLeft, FTop, Value, FHeight);
end;

procedure TVrRect.SetHeight(Value: Integer);
begin
  SetBounds(FLeft, FTop, FWidth, Value);
end;

function TVrRect.GetBoundsRect: TRect;
begin
  Result.Left := Left;
  Result.Top := Top;
  Result.Right := Left + Width;
  Result.Bottom := Top + Height;
end;

procedure TVrRect.SetBoundsRect(const Rect: TRect);
begin
  with Rect do SetBounds(Left, Top, Right - Left, Bottom - Top);
end;

{ TVrCollectionItem }

constructor TVrCollectionItem.Create(Collection: TVrCollection);
begin
  SetCollection(Collection);
end;

destructor TVrCollectionItem.Destroy;
begin
  SetCollection(nil);
  inherited Destroy;
end;

procedure TVrCollectionItem.Changed(AllItems: Boolean);
var
  Item: TVrCollectionItem;
begin
  if (FCollection <> nil) and (FCollection.FUpdateCount = 0) then
  begin
    if AllItems then Item := nil
    else Item := Self;
    FCollection.Update(Item);
  end;
end;

procedure TVrCollectionItem.SetCollection(Value: TVrCollection);
begin
  if FCollection <> Value then
  begin
    if FCollection <> nil then FCollection.RemoveItem(Self);
    if Value <> nil then Value.InsertItem(Self);
  end;
end;

{ TVrCollection }

constructor TVrCollection.Create;
begin
  FItems := TList.Create;
end;

destructor TVrCollection.Destroy;
begin
  FUpdateCount := 1;
  if FItems <> nil then Clear;
  FItems.Free;
  inherited Destroy;
end;

procedure TVrCollection.BeginUpdate;
begin
  Inc(FUpdateCount);
end;

procedure TVrCollection.Changed;
begin
  if FUpdateCount = 0 then Update(nil);
end;

procedure TVrCollection.Clear;
begin
  if FItems.Count > 0 then
  begin
    BeginUpdate;
    try
      while FItems.Count > 0 do TCollectionItem(FItems.Last).Free;
    finally
      EndUpdate;
    end;
  end;
end;

procedure TVrCollection.EndUpdate;
begin
  Dec(FUpdateCount);
  Changed;
end;

procedure TVrCollection.RemoveItem(Item: TVrCollectionItem);
begin
  FItems.Remove(Item);
  Item.FCollection := nil;
end;

procedure TVrCollection.InsertItem(Item: TVrCollectionItem);
begin
  Item.Index := FItems.Add(Item);
  Item.FCollection := Self;
end;

function TVrCollection.GetCount: Integer;
begin
  Result := FItems.Count;
end;

function TVrCollection.GetItem(Index: Integer): TVrCollectionItem;
begin
  Result := FItems[Index];
end;

procedure TVrCollection.Update(Item: TVrCollectionItem);
begin
end;



end.
