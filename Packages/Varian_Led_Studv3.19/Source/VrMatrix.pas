{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrMatrix;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrConst, VrTypes, VrClasses, VrControls, VrSysUtils, VrThreads;

type
  TVrMatrixTextStyle = (tsUpperCase, tsLowerCase, tsAsIs, tsProperCase);
  TVrMatrixScrollDirection = (sdRightToLeft, sdLeftToRight);
  TVrMatrixLedStyle = (ls9x13, ls14x20, ls19x27);

  TVrMatrix = class(TVrGraphicImageControl)
  private
    FLeds: Integer;
    FSpacing: Integer;
    FOutString: string;
    FAlignment: TAlignment;
    FPalette: TVrPalette;
    FTextStyle: TVrMatrixTextStyle;
    FAutoScroll: Boolean;
    FBevel: TVrBevel;
    FScrollDirection: TVrMatrixScrollDirection;
    FLedStyle: TVrMatrixLedStyle;
    FLedsVisible: Boolean;
    FThreaded: Boolean;
    FOrientation: TVrOrientation;
    FCurrColor: TColor;
    FCharIndex: Integer;
    FCharCount: Integer;
    FOnScrollDone: TNotifyEvent;
    Bitmap: TBitMap;
    FTimer: TVrTimer;
    ScrollInit: Boolean;
    Initialized: Boolean;
    FStartLed: Integer;
    FImageRect: TRect;
    function GetTimeInterval: Integer;
    procedure SetLeds(Value: Integer);
    procedure SetSpacing(Value: Integer);
    procedure SetOutString(Value: string);
    procedure SetAlignment(Value: TAlignment);
    procedure SetTextStyle(Value: TVrMatrixTextStyle);
    procedure SetAutoScroll(Value: Boolean);
    procedure SetTimeInterval(Value: Integer);
    procedure SetLedStyle(Value: TVrMatrixLedStyle);
    procedure SetLedsVisible(Value: Boolean);
    procedure SetPalette(Value: TVrPalette);
    procedure SetBevel(Value: TVrBevel);
    procedure SetThreaded(Value: Boolean);
    procedure SetOrientation(Value: TVrOrientation);
    procedure PaletteModified(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
    procedure TimerEvent(Sender: TObject);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
  protected
    procedure LoadBitmaps; virtual;
    procedure DestroyBitmaps;
    procedure UpdateLed(Index: Integer; Ch: Char);
    procedure UpdateLeds(Redraw: Boolean);
    procedure Paint; override;
    procedure Loaded; override;
    procedure GetItemRect(Index: Integer; var R: TRect);
    procedure CalcPaintParams;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Threaded: Boolean read FThreaded write SetThreaded default True;
    property Leds: Integer read FLeds write SetLeds default 15;
    property Spacing: Integer read FSpacing write SetSpacing default 2;
    property Alignment: TAlignment read FAlignment write SetAlignment default taLeftJustify;
    property Palette: TVrPalette read FPalette write SetPalette;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property TextStyle: TVrMatrixTextStyle read FTextStyle write SetTextStyle default tsUpperCase;
    property AutoScroll: Boolean read FAutoScroll write SetAutoScroll default false;
    property TimeInterval: Integer read GetTimeInterval write SetTimeInterval default 500;
    property ScrollDirection: TVrMatrixScrollDirection read FScrollDirection write FScrollDirection default sdRightToLeft;
    property LedStyle: TVrMatrixLedStyle read FLedStyle write SetLedStyle default ls14x20;
    property LedsVisible: Boolean read FLedsVisible write SetLedsVisible default True;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property OnScrollDone: TNotifyEvent read FOnScrollDone write FOnScrollDone;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Text;
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

{$R VRMATRIX.D32}

const
  CharState: array[0..895] of byte = { all ASCII according to Hewlett Packard HDSP 2470 }
              ($02, $06, $0e, $1e, $0e, $06, $02,     { NUL }
               $04, $00, $04, $08, $11, $11, $0e,     { SOH }
               $1f, $00, $11, $0a, $04, $0a, $11,     { STX }
               $1f, $00, $11, $19, $15, $13, $11,     { ETX }
               $1f, $00, $16, $19, $11, $11, $11,     { EOT }
               $00, $00, $0d, $12, $12, $12, $0d,     { ENQ }
               $1c, $12, $12, $16, $11, $16, $10,     { ACK }
               $06, $08, $04, $0e, $11, $11, $0e,     { BEL }
               $00, $00, $00, $04, $0a, $11, $1f,     { BS }
               $00, $10, $1c, $12, $12, $02, $01,     { HT }
               $0e, $11, $11, $1f, $11, $11, $0e,     { LF }
               $00, $10, $08, $04, $0a, $11, $11,     { VT }
               $00, $00, $09, $09, $09, $0e, $10,     { FF }
               $00, $01, $0e, $1a, $0a, $0a, $0a,     { CR }
               $00, $00, $0f, $12, $12, $12, $0c,     { SO }
               $1f, $08, $04, $02, $04, $08, $1f,     { SI }
               $00, $00, $01, $0e, $14, $04, $04,     { DLE }
               $00, $04, $0e, $15, $15, $0e, $04,     { DC1 }
               $0e, $11, $11, $11, $11, $0a, $1b,     { DC2 }
               $04, $00, $0e, $11, $1f, $11, $11,     { DC3 }
               $04, $00, $0e, $12, $12, $12, $0d,     { DC4 }
               $0a, $00, $0e, $11, $1f, $11, $11,     { NAK }
               $0a, $00, $0e, $12, $12, $12, $0d,     { SYN }
               $0a, $0e, $11, $11, $11, $11, $0e,     { ETB }
               $0a, $00, $0e, $11, $11, $11, $0e,     { CAN }
               $0a, $00, $11, $11, $11, $11, $0e,     { EM }
               $00, $0a, $00, $11, $11, $11, $0e,     { SUB }
               $00, $04, $02, $1f, $02, $04, $00,     { ESC }
               $00, $0f, $08, $08, $08, $18, $08,     { FS }
               $0c, $12, $04, $08, $1e, $00, $00,     { GS }
               $06, $09, $08, $1c, $08, $08, $1f,     { RS }
               $11, $0a, $04, $04, $0e, $04, $04,     { US }
               $00, $00, $00, $00, $00, $00, $00,     { Space }
               $08, $08, $08, $08, $08, $00, $08,     { ! }
               $0a, $0a, $00, $00, $00, $00, $00,     { " }
               $0a, $0a, $1f, $0a, $1f, $0a, $0a,     { # }
               $04, $0f, $14, $0e, $05, $1e, $04,     { $ }
               $18, $19, $02, $04, $08, $13, $03,     { % }
               $08, $14, $14, $08, $15, $12, $0d,     { & }
               $0c, $0c, $04, $08, $00, $00, $00,     { ' }
               $02, $04, $04, $04, $04, $04, $02,     { ( }
               $08, $04, $04, $04, $04, $04, $08,     { ) }
               $00, $0a, $04, $1f, $04, $0a, $00,     { * }
               $00, $04, $04, $1f, $04, $04, $00,     { + }
               $00, $00, $00, $0c, $0c, $04, $08,     { , }
               $00, $00, $00, $1f, $00, $00, $00,     { - }
               $00, $00, $00, $00, $0c, $0c, $00,     { . }
               $00, $01, $02, $04, $08, $10, $00,     { / }
               $0e, $11, $13, $15, $19, $11, $0e,     { 0 }
               $04, $0c, $04, $04, $04, $04, $0e,     { 1 }
               $0e, $11, $01, $06, $08, $10, $1f,     { 2 }
               $0e, $11, $01, $06, $01, $11, $0e,     { 3 }
               $02, $06, $0a, $12, $1f, $02, $02,     { 4 }
               $1f, $10, $1e, $01, $01, $11, $0e,     { 5 }
               $06, $08, $10, $1e, $11, $11, $0e,     { 6 }
               $1f, $01, $02, $04, $08, $08, $08,     { 7 }
               $0e, $11, $11, $0e, $11, $11, $0e,     { 8 }
               $0e, $11, $11, $0f, $01, $02, $0c,     { 9 }
               $00, $0c, $0c, $00, $0c, $0c, $00,     { : }
               $0c, $0c, $00, $0c, $0c, $04, $08,     { ; }
               $01, $02, $04, $08, $04, $02, $01,     { < }
               $00, $00, $1f, $00, $1f, $00, $00,     { = }
               $10, $08, $04, $02, $04, $08, $10,     { > }
               $0e, $11, $01, $02, $04, $00, $04,     { ? }
               $0e, $11, $17, $15, $17, $10, $0e,     { @ }
               $0e, $11, $11, $1f, $11, $11, $11,     { A }
               $1e, $11, $11, $1e, $11, $11, $1e,     { B }
               $0e, $11, $10, $10, $10, $11, $0e,     { C }
               $1e, $11, $11, $11, $11, $11, $1e,     { D }
               $1f, $10, $10, $1e, $10, $10, $1f,     { E }
               $1f, $10, $10, $1e, $10, $10, $10,     { F }
               $0e, $11, $10, $10, $13, $11, $0f,     { G }
               $11, $11, $11, $1f, $11, $11, $11,     { H }
               $0e, $04, $04, $04, $04, $04, $0e,     { I }
               $01, $01, $01, $01, $01, $11, $0e,     { J }
               $11, $12, $14, $18, $14, $12, $11,     { K }
               $10, $10, $10, $10, $10, $10, $1f,     { L }
               $11, $1b, $15, $15, $11, $11, $11,     { M }
               $11, $11, $19, $15, $13, $11, $11,     { N }
               $0e, $11, $11, $11, $11, $11, $0e,     { O }
               $1e, $11, $11, $1e, $10, $10, $10,     { P }
               $0e, $11, $11, $11, $15, $12, $0d,     { Q }
               $1e, $11, $11, $1e, $14, $12, $11,     { R }
               $0e, $11, $10, $0e, $01, $11, $0e,     { S }
               $1f, $04, $04, $04, $04, $04, $04,     { T }
               $11, $11, $11, $11, $11, $11, $0e,     { U }
               $11, $11, $11, $11, $11, $0a, $04,     { V }
               $11, $11, $11, $15, $15, $1b, $11,     { W }
               $11, $11, $0a, $04, $0a, $11, $11,     { X }
               $11, $11, $0a, $04, $04, $04, $04,     { Y }
               $1f, $01, $02, $04, $08, $10, $1f,     { Z }
               $07, $04, $04, $04, $04, $04, $07,     { [ }
               $00, $10, $08, $04, $02, $01, $00,     { \ }
               $1c, $04, $04, $04, $04, $04, $1c,     { ] }
               $04, $0e, $15, $04, $04, $04, $04,     { ^ }
               $00, $00, $00, $00, $00, $00, $1f,     { _ }
               $0c, $0c, $08, $04, $00, $00, $00,     { ` }
               $00, $00, $0e, $12, $12, $12, $0d,     { a }
               $10, $10, $16, $19, $11, $11, $1e,     { b }
               $00, $00, $0e, $10, $10, $11, $0e,     { c }
               $01, $01, $0d, $13, $11, $11, $0f,     { d }
               $00, $00, $0e, $11, $1e, $10, $0e,     { e }
               $04, $0a, $08, $1c, $08, $08, $08,     { f }
               $00, $00, $0f, $11, $0f, $01, $06,     { g }
               $10, $10, $16, $19, $11, $11, $11,     { h }
               $04, $00, $0c, $04, $04, $04, $0e,     { i }
               $02, $00, $06, $02, $02, $12, $0c,     { j }
               $08, $08, $09, $0a, $0c, $0a, $09,     { k }
               $0c, $04, $04, $04, $04, $04, $0e,     { l }
               $00, $00, $0a, $15, $15, $11, $11,     { m }
               $00, $00, $16, $19, $11, $11, $11,     { n }
               $00, $00, $0e, $11, $11, $11, $0e,     { o }
               $00, $00, $1e, $11, $19, $16, $10,     { p }
               $00, $00, $0e, $12, $16, $0a, $03,     { q }
               $00, $00, $0b, $0c, $08, $08, $08,     { r }
               $00, $00, $0e, $10, $0e, $01, $1e,     { s }
               $00, $08, $1c, $08, $08, $0a, $04,     { t }
               $00, $00, $11, $11, $11, $13, $0d,     { u }
               $00, $00, $11, $11, $11, $0a, $04,     { v }
               $00, $00, $11, $11, $15, $15, $0a,     { w }
               $00, $00, $11, $0a, $04, $0a, $11,     { x }
               $00, $00, $11, $0a, $04, $04, $08,     { y }
               $00, $00, $1f, $02, $04, $08, $1f,     { z }
               $02, $04, $04, $08, $04, $04, $02,     (* { *)
               $04, $04, $04, $00, $04, $04, $04,     { | }
               $08, $04, $04, $02, $04, $04, $08,     (* } *)
               $00, $00, $08, $15, $02, $00, $00,     { ~ }
               $0a, $15, $0a, $15, $0a, $15, $0a);    { DEL }

  SegSize: array[TVrMatrixLedStyle] of Integer = (1, 2, 3);

  ColorCmd = '%';

  ColorArray: array[1..16] of TColor = (
    clBlack, clMaroon, clGreen, clOlive, clNavy, clPurple,
    clTeal, clGray, clSilver, clRed, clLime, clYellow,
    clBlue, clFuchsia, clAqua, clWhite);

  //Each color code is made out of a percentage charater and a combination
  //of digits: for example "%12Hello" will display all characters in clYellow.
  //Combinations are also possible: %12H%0ello. This will only display the
  //"H" in a different color.

  //Note: in order to reset to the default palette color use "%0", or
  //to display a % character use %%.


function IsNumChar(Ch: Char): Boolean;
begin
  Result := Ch in ['0'..'9'];
end;

function CountChars(const S: string): Integer;
var
  I: Integer;
begin
  I := 1;
  Result := 0;
  while I <= Length(S) do
  begin
    if S[I] = ColorCmd then
    begin
      Inc(I);
      if (I <= Length(S)) and (S[I] = ColorCmd) then
      begin
        Inc(Result);
        Inc(I);
      end
      else while (I <= Length(S)) and IsNumChar(S[I]) do Inc(I);
    end
    else
    begin
      Inc(Result);
      Inc(I);
    end;
  end;
end;

function FirstCharIndex(const S: string): Integer;
var
  I: Integer;
begin
  I := 1;
  while I <= Length(S) do
  begin
    if S[I] = ColorCmd then
    begin
      Inc(I);
      if (I <= Length(S)) and (S[I] = ColorCmd) then
      begin
        Result := I;
        Exit;
      end
      else while (I <= Length(S)) and IsNumChar(S[I]) do Inc(I);
    end
    else
    begin
      Result := I;
      Exit;
    end;
  end;
  Result := -1;
end;



{TVrMatrix}

constructor TVrMatrix.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csSetCaption];
  Width := 245;
  Height := 30;
  ParentColor := false;
  Color := clBlack;
  FLeds := 15;
  FSpacing := 2;
  FAlignment := taLeftjustify;
  FTextStyle := tsUpperCase;
  FAutoScroll := false;
  FCharIndex := 1;
  FScrollDirection := sdRightToLeft;
  FLedStyle := ls14x20;
  FLedsVisible := True;
  FOrientation := voHorizontal;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  Bitmap := TBitMap.Create;
  LoadBitmaps;
  FThreaded := True;
  FTimer := TVrTimer.Create(Self);
  FTimer.Enabled := false;
  FTimer.Interval := 500;
  FTimer.OnTimer := TimerEvent;
end;

destructor TVrMatrix.Destroy;
begin
  DestroyBitmaps;
  FBevel.Free;
  FPalette.Free;
  FTimer.Free;
  inherited Destroy;
end;

procedure TVrMatrix.Loaded;
begin
  inherited Loaded;
  CalcPaintParams;
end;

procedure TVrMatrix.LoadBitmaps;
const
  ResNames: array[TVrMatrixLedStyle] of PChar =
    ('9x13', '14x20', '19x27');
begin
  Bitmap.Handle := LoadBitmap(hInstance, PChar('VRMATRIXLED' + ResNames[FLedStyle]));
  FPalette.ToBMP(Bitmap, ResColorLow, ResColorHigh);
  FImageRect := Bounds(0, 0, Bitmap.Width, Bitmap.Height);
end;

procedure TVrMatrix.DestroyBitmaps;
begin
  Bitmap.Free;
end;

procedure TVrMatrix.PaletteModified(Sender: TObject);
begin
  LoadBitmaps;
  UpdateControlCanvas;
end;

procedure TVrMatrix.BevelChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrMatrix.SetLeds(Value: Integer);
begin
  if FLeds <> Value then
  begin
    FLeds := Value;
    SetOutString(Text);
    UpdateControlCanvas;
  end;
end;

procedure TVrMatrix.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMatrix.SetOutString(Value: string);
var
  Idx: Integer;
begin
  FOutString := Value;
  case FTextStyle of
    tsUpperCase: FOutString := AnsiUpperCase(FOutString);
    tsLowerCase: FOutString := AnsiLowerCase(FOutString);
    tsProperCase:
      begin
        FOutString := AnsiLowerCase(FOutString);
        Idx := FirstCharIndex(FOutString);
        if Idx <> -1 then
          FOutString[Idx] := Upcase(FOutString[Idx]);
      end;
    tsAsIs:; //do nothing
  end;
  FCharCount := CountChars(FOutString);
end;

procedure TVrMatrix.SetTextStyle(Value: TVrMatrixTextStyle);
begin
  if FTextStyle <> Value then
  begin
    FTextStyle := Value;
    SetOutString(Text);
    UpdateLeds(True);
  end;
end;

procedure TVrMatrix.SetAlignment(Value: TAlignment);
begin
  if FAlignment <> Value then
  begin
    FAlignment := Value;
    if (Designing) or (not FAutoScroll) then
      UpdateControlCanvas;
  end;
end;

procedure TVrMatrix.SetAutoScroll(Value: Boolean);
begin
  if FAutoScroll <> Value then
  begin
    FAutoScroll := Value;
    FCharIndex := 1;
    UpdateControlCanvas;
    if not (Designing or Loading) then
    begin
      ScrollInit := True;
      FTimer.Enabled := Value;
    end;
  end;
end;

procedure TVrMatrix.SetLedStyle(Value: TVrMatrixLedStyle);
begin
  if FLedStyle <> Value then
  begin
    FLedStyle := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrMatrix.SetLedsVisible(Value: Boolean);
begin
  if FLedsVisible <> Value then
  begin
    FLedsVisible := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMatrix.SetThreaded(Value: Boolean);
begin
  if FThreaded <> Value then
  begin
    FThreaded := Value;
    if Value then FTimer.TimerType := ttThread
    else FTimer.TimerType := ttSystem;
  end;
end;

procedure TVrMatrix.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMatrix.SetTimeInterval(Value: Integer);
begin
  FTimer.Interval := Value;
end;

function TVrMatrix.GetTimeInterval: Integer;
begin
  Result := FTimer.Interval;
end;

procedure TVrMatrix.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrMatrix.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrMatrix.CMTextChanged(var Message: TMessage);
begin
  inherited;
  SetOutString(Text);
  UpdateControlCanvas;
end;

procedure TVrMatrix.UpdateLed(Index: Integer; Ch: Char);
var
  R, ItemRect: TRect;
  I, J, Idx, W: Integer;
begin
  with BitmapCanvas do
  begin
    GetItemRect(Index, ItemRect);
    Brush.Style := bsSolid;
    Brush.Color := Self.Color;
    FillRect(ItemRect);
    if FLedsVisible then
    begin
      Brush.Style := bsClear;
      BrushCopy(ItemRect, Bitmap, FImageRect, clBlack);
    end;

    if Ch = #32 then Exit;

    Brush.Color := FCurrColor;
    Idx := ord(Ch) * 7;
    for I := 0 to 6 do
      for J := 0 to 4 do
      begin
        if CharState[Idx + I] and (1 shl J) > 0 then
        begin
          W := SegSize[FLedStyle];
          R := Bounds(ItemRect.Left + Bitmap.Width - W - (J * Succ(W)),
                      ItemRect.Top + (I * Succ(W)), W, W);
          FillRect(R);
        end;
      end;
  end;
end;

procedure TVrMatrix.UpdateLeds(Redraw: Boolean);
var
  I: Integer;
  S: string;
  Idx, CharCount: Integer;

  procedure DecodeColorCode(var S: string);
  var
    ColorCode: string;
    ColorIndex, ErrCode: Integer;
  begin
    ColorCode := '';
    while (S <> '') and (IsNumChar(S[1])) do
    begin
      ColorCode := ColorCode + S[1];
      Delete(S, 1, 1);
    end;
    Val(ColorCode, ColorIndex, ErrCode);
    if (ErrCode <> 0) or (ColorIndex < 1) or (ColorIndex > 16) then
       FCurrColor := FPalette.High
    else FCurrColor := ColorArray[ColorIndex];
  end;

  procedure ShowNextChar(var S: string);
  begin
    Inc(CharCount);
    if CharCount >= FCharIndex then
    begin
      UpdateLed(Idx, S[1]);
      Inc(Idx);
    end;
    Delete(S, 1, 1);
  end;

begin
  FCurrColor := FPalette.High;
  for I := 0 to FLeds - 1 do
    UpdateLed(I, #32);

  Idx := FStartLed;
  CharCount := 0;
  S := FOutString;
  while Length(S) > 0 do
  begin
    if S[1] = ColorCmd then
    begin
      Delete(S, 1, 1);
      if (S <> '') and (S[1] = ColorCmd) then
        ShowNextChar(S)
      else DecodeColorCode(S);
    end else ShowNextChar(S);
    if Idx >= FLeds then Break;
  end;

  if not Loading then
    if Redraw then inherited Paint;
end;

procedure TVrMatrix.Paint;
var
  R: TRect;
begin
  CalcPaintParams;
  ClearBitmapCanvas;
  R := ClientRect;
  FBevel.Paint(BitmapCanvas, R);
  FCharIndex := 1;
  case FAlignment of
    taCenter: FStartLed := MaxIntVal(0, ((FLeds - FCharCount) div 2));
    taRightJustify: FStartLed := MaxIntVal(0, (FLeds - FCharCount));
    else FStartLed := 0;
  end;

  UpdateLeds(True);

  //Make sure we first display the control
  if (not Initialized) and (AutoScroll) then
  begin
    Initialized := True;
    ScrollInit := True;
    FTimer.Enabled := True;
  end;
end;

procedure TVrMatrix.CalcPaintParams;
var
  R: TRect;
  Gap, NewWidth, NewHeight: Integer;
begin
  R := ClientRect;
  FBevel.GetVisibleArea(R);
  Gap := (FLeds - 1) * FSpacing;

  if Orientation = voHorizontal then
  begin
    NewWidth := (R.Left * 2) + Gap + (FLeds * Bitmap.Width);
    NewHeight := (R.Top * 2) + Bitmap.Height;
  end
  else
  begin
    NewWidth := (R.Left * 2) + Bitmap.Width;
    NewHeight := (R.Top * 2) + Gap + (FLeds * Bitmap.Height);
  end;
  BoundsRect := Bounds(Left, Top, NewWidth, NewHeight);
end;

procedure TVrMatrix.GetItemRect(Index: Integer; var R: TRect);
var
  X, Y: Integer;
begin
  R := ClientRect;
  FBevel.GetVisibleArea(R);
  X := R.Left;
  Y := R.Top;
  if Orientation = voHorizontal then
    X := X + (Index * Bitmap.Width) + (Index * FSpacing)
  else Y := Y + (Index * Bitmap.Height) + (Index * FSpacing);
  R := Bounds(X, Y, Bitmap.Width, Bitmap.Height);
end;

procedure TVrMatrix.TimerEvent(Sender: TObject);
begin
  if (ScrollInit) then
  begin
    FCharIndex := 1;
    ScrollInit := false;
  end;

  if FScrollDirection = sdRightToLeft then
  begin
    if FStartLed > 0 then Dec(FStartLed)
    else if FCharIndex <= FCharCount then Inc(FCharIndex)
    else
    begin
      if Assigned(FOnScrollDone) then
        FOnScrollDone(Self);
      FCharIndex := 1;
      FStartLed := FLeds - 1;
    end;
  end
  else
  begin
    if (FCharIndex = 1) and (FStartLed < FLeds-1) then Inc(FStartLed)
    else
    if FCharIndex > 1 then
    begin
      Dec(FCharIndex);
      FStartLed := 0;
    end
    else
    begin
      if Assigned(FOnScrollDone) then
        FOnScrollDone(Self);
      FCharIndex := FCharCount;
      FStartLed := 0;
    end;
  end;

  UpdateLeds(True);
end;



end.
