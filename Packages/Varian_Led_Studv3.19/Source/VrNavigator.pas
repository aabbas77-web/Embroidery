{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrNavigator;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrButtonType = (btPower, btPlay, btPause, btStop, btPrev, btBack, btStep,
    btNext, btRecord, btEject);
  TVrButtonSet = set of TVrButtonType;

  TVrButtonState = (mgEnabled, mgDisabled);

  TVrNavButton = record
    Visible: Boolean;
    Enabled: Boolean;
    Bitmaps: array[TVrButtonState] of TBitmap;
  end;

  TVrMediaButton = class(TVrCustomImageControl)
  private
    FButtonType: TVrButtonType;
    FFocusColor: TColor;
    FBorderColor: TColor;
    Bitmaps: array[TVrButtonState] of TBitmap;
    Down: Boolean;
    Pressed: Boolean;
    MaskColor: TColor;
    HasFocus: Boolean;
    procedure SetButtonType(Value: TVrButtonType);
    procedure SetFocusColor(Value: TColor);
    procedure SetBorderColor(Value: TColor);
    procedure DoMouseDown(XPos, YPos: Integer);
    procedure WMLButtonDown(var Message: TWMLButtonDown); message WM_LBUTTONDOWN;
    procedure WMMouseMove(var Message: TWMMouseMove); message WM_MOUSEMOVE;
    procedure WMLButtonUp(var Message: TWMLButtonUp); message WM_LBUTTONUP;
    procedure WMLButtonDblClk(var Message: TWMLButtonDblClk); message WM_LBUTTONDBLCLK;
    procedure CMEnabledChanged(var Message: TMessage); message CM_ENABLEDCHANGED;
    procedure WMSetFocus(var Message: TWMSetFocus); message WM_SETFOCUS;
    procedure WMKillFocus(var Message: TWMKillFocus); message WM_KILLFOCUS;
  protected
    procedure LoadBitmaps;
    procedure DestroyBitmaps;
    procedure Paint; override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure KeyUp(var Key: Word; Shift: TShiftState); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property ButtonType: TVrButtonType read FButtonType write SetButtonType default btPause;
    property FocusColor: TColor read FFocusColor write SetFocusColor default clBlue;
    property BorderColor: TColor read FBorderColor write SetBorderColor default clBlack;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Enabled;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop default false;
    property Visible;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnDragDrop;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;

const
  DefEnabledButtons = [btPower, btPlay, btPause, btStop, btPrev, btBack, btStep,
    btNext, btRecord, btEject];
  DefVisibleButtons = [btPower, btPlay, btPause, btStop, btPrev, btBack, btStep,
    btNext, btRecord, btEject];

type
  TVrClickEvent = procedure (Sender: TObject; Button: TVrButtonType) of object;

  TVrNavigator = class(TVrCustomImageControl)
  private
    FVisibleButtons: TVrButtonSet;
    FEnabledButtons: TVrButtonSet;
    FBevel: TVrBevel;
    FFocusColor: TColor;
    FBorderColor: TColor;
    FSpacing: Integer;
    FOrientation: TVrOrientation;
    FOnButtonClick: TVrClickEvent;
    Bitmap: TBitmap;
    Pressed: Boolean;
    Down: Boolean;
    CurrentButton: TVrButtonType;
    ViewPort: TRect;
//  DestCanvas: TCanvas;
    ButtonWidth: Integer;
    ButtonHeight: Integer;
    FocusedButton: TVrButtonType;
    Buttons: array[TVrButtonType] of TVrNavButton;
    function VisibleButtonCount: Integer;
    procedure SetVisibleButtons(Value: TVrButtonSet);
    procedure SetEnabledButtons(Value: TVrButtonSet);
    procedure SetSpacing(Value: Integer);
    procedure SetFocusColor(Value: TColor);
    procedure SetBorderColor(Value: TColor);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetBevel(Value: TVrBevel);
    procedure DoMouseDown(XPos, YPos: Integer);
    procedure BevelChanged(Sender: TObject);
    procedure WMLButtonDown(var Message: TWMLButtonDown); message WM_LButtonDown;
    procedure WMLButtonDblClk(var Message: TWMLButtonDblClk); message WM_LButtonDblClk;
    procedure WMMouseMove(var Message: TWMMouseMove); message WM_MouseMove;
    procedure WMLButtonUp(var Message: TWMLButtonUp); message WM_LButtonUp;
    procedure WMSetFocus(var Message: TWMSetFocus); message WM_SETFOCUS;
    procedure WMKillFocus(var Message: TWMKillFocus); message WM_KILLFOCUS;
    procedure WMGetDlgCode(var Message: TWMGetDlgCode); message WM_GETDLGCODE;
  protected
    procedure DoClick(Button: TVrButtonType);
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure KeyUp(var Key: Word; Shift: TShiftState); override;
    procedure LoadBitmaps;
    procedure DestroyBitmaps;
    procedure CalcPaintParams;
    procedure GetButtonRect(Btn: TVrButtonType; var R: TRect);
    procedure DrawButton(Btn: TVrButtonType);
    procedure SetFocusedButton(Btn: TVrButtonType);
    procedure Paint; override;
    procedure Loaded; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure ButtonClick(Button: TVrButtonType); dynamic;
  published
    property Bevel: TVrBevel read FBevel write SetBevel;
    property Spacing: Integer read FSpacing write SetSpacing default 1;
    property FocusColor: TColor read FFocusColor write SetFocusColor default clBlue;
    property BorderColor: TColor read FBorderColor write SetBorderColor default clBlack;
    property VisibleButtons: TVrButtonSet read FVisibleButtons write SetVisibleButtons default DefVisibleButtons;
    property EnabledButtons: TVrButtonSet read FEnabledButtons write SetEnabledButtons default DefEnabledButtons;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property OnButtonClick: TVrClickEvent read FOnButtonClick write FOnButtonClick;
    property Color;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop default True;
    property Visible;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnDragDrop;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


implementation

{$R VRNAVIGATOR.D32}

const
  BtnStateName: array[TVrButtonState] of PChar = ('EN', 'DI');
  BtnTypeName: array[TVrButtonType] of PChar = ('BTPOWER', 'BTPLAY', 'BTPAUSE',
    'BTSTOP', 'BTPREV', 'BTBACK', 'BTSTEP', 'BTNEXT', 'BTRECORD', 'BTEJECT');


{ TVrNavigator }

constructor TVrNavigator.Create(AOwner: TComponent);
var
  I: TVrButtonType;
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csSetCaption];
  Width := 340;
  Height := 25;
  TabStop := True;
  for I := Low(Buttons) to High(Buttons) do
  begin
    Buttons[I].Visible := True;
    Buttons[I].Enabled := True;
  end;
  LoadBitmaps;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerSpace := 0;
    OnChange := BevelChanged;
  end;
  FFocusColor := clBlue;
  FBorderColor := clBlack;
  FSpacing := 1;
  FVisibleButtons := DefVisibleButtons;
  FEnabledButtons := DefEnabledButtons;
  FOrientation := voHorizontal;
  Bitmap := TBitmap.Create;
//DestCanvas := Self.Canvas;
end;

destructor TVrNavigator.Destroy;
begin
  Bitmap.Free;
  DestroyBitmaps;
  inherited Destroy;
end;

procedure TVrNavigator.Loaded;
var
  I: TVrButtonType;
begin
  inherited Loaded;
  for I := Low(Buttons) to High(Buttons) do
    if Buttons[I].Visible then
    begin
      FocusedButton := I;
      CurrentButton := I;
      Exit;
    end;
end;

procedure TVrNavigator.BevelChanged(Sender: TObject);
var
  R: TRect;
begin
  if not Loading then
  begin
    R := ClientRect;
    FBevel.GetVisibleArea(R);
    InflateRect(ViewPort, R.Left, R.Top);
    BoundsRect := Bounds(Left, Top, WidthOf(ViewPort),
      HeightOf(ViewPort));
  end;
  UpdateControlCanvas;
end;

procedure TVrNavigator.LoadBitmaps;
var
  I: TVrButtonType;
  J: TVrButtonState;
  ResName: array[0..40] of Char;
begin
  DestroyBitmaps;
  for I := Low(Buttons) to High(Buttons) do
    for J := Low(TVrButtonState) to High(TVrButtonState) do
    begin
      Buttons[I].Bitmaps[J] := TBitmap.Create;
      Buttons[I].Bitmaps[J].Handle := LoadBitmap(hInstance,
        StrFmt(ResName, '%s_%s', [BtnStateName[J], BtnTypeName[I]]));
  end;
end;

procedure TVrNavigator.DestroyBitmaps;
var
  I: TVrButtonType;
  J: TVrButtonState;
begin
  for I := Low(Buttons) to High(Buttons) do
    for J := Low(TVrButtonState) to High(TVrButtonState) do
      Buttons[I].Bitmaps[J].Free;
end;

procedure TVrNavigator.SetEnabledButtons(Value: TVrButtonSet);
var
  I: TVrButtonType;
begin
  FEnabledButtons := Value;
  for I := Low(Buttons) to High(Buttons) do
    Buttons[I].Enabled := I in FEnabledButtons;
  UpdateControlCanvas;
end;

procedure TVrNavigator.SetVisibleButtons(Value: TVrButtonSet);
var
  I: TVrButtonType;
begin
  FVisibleButtons := Value;
  for I := Low(Buttons) to High(Buttons) do
    Buttons[I].Visible := I in FVisibleButtons;
  UpdateControlCanvas;
end;

function TVrNavigator.VisibleButtonCount: Integer;
var
  I: TVrButtonType;
begin
  Result := 0;
  for I := Low(Buttons) to High(Buttons) do
    if Buttons[I].Visible then Inc(Result);
  if Result = 0 then Inc(Result);
end;

procedure TVrNavigator.SetSpacing(Value: Integer);
begin
  if FSpacing <> Value then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrNavigator.SetFocusColor(Value: TColor);
begin
  if FFocusColor <> Value then
  begin
    FFocusColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrNavigator.SetBorderColor(Value: TColor);
begin
  if FBorderColor <> Value then
  begin
    FBorderColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrNavigator.SetOrientation(Value: TVrOrientation);
var
  R: TRect;
  NewWidth: Integer;
  NewHeight: Integer;
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    if not Loading then
    begin
      NewWidth := 0;
      NewHeight := 0;
      case Value of
        voHorizontal:
          begin
            NewWidth := (VisibleButtonCount * (ButtonWidth + FSpacing));
            NewHeight := ButtonHeight;
          end;
        voVertical:
          begin
            NewWidth := ButtonWidth;
            NewHeight := (VisibleButtonCount * (ButtonHeight + FSpacing));
          end;
      end;
      R := Bounds(0, 0, NewWidth, NewHeight);
      InflateRect(R, ViewPort.Left, ViewPort.Top);
      BoundsRect := Bounds(Left, Top, WidthOf(R), HeightOf(R));
    end;
    UpdateControlCanvas;
  end;
end;

procedure TVrNavigator.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrNavigator.DrawButton(Btn: TVrButtonType);
var
  IsDown: Boolean;
  BX, BY, hRes: Integer;
  TheGlyph: TVrButtonState;
  Glyph: TBitmap;
  R: TRect;
  BtnRect: TRect;
  Colors: array[0..1] of TColor;
begin
  GetButtonRect(Btn, BtnRect);
  IsDown := Down and (Btn = CurrentButton);

  Bitmap.Width := ButtonWidth;
  Bitmap.Height := ButtonHeight;

  with Bitmap.Canvas do
  begin
    if Down then
    begin
      Colors[0] := clBtnFace;
      Colors[1] := clBtnHighlight;
    end
    else
    begin
      Colors[0] := clBtnHighlight;
      Colors[1] := clBtnShadow;
    end;

    hRes := ButtonHeight div 10;
    if hRes < 2 then HRes := 2;
    R := Bounds(0, 0, ButtonWidth, ButtonHeight);
    InflateRect(R, -2, -2);
    DrawGradient(Bitmap.Canvas, R, Colors[0], Colors[1], voVertical, hRes);

    if Buttons[Btn].Enabled then
      TheGlyph := mgEnabled else TheGlyph := mgDisabled;

    Glyph := Buttons[Btn].Bitmaps[TheGlyph];
    BX := (ButtonWidth div 2) - (Glyph.Width div 2);
    BY := (ButtonHeight div 2) - (Glyph.Height div 2);
    if IsDown then
    begin
      Inc(BX);
      Inc(BY);
    end;
    Brush.Style := bsClear;
    BrushCopy(Bounds(BX, BY, Glyph.Width, Glyph.Height),
      Glyph, BitmapRect(Glyph), clOlive);

    R := Bounds(0, 0, ButtonWidth, ButtonHeight);
    if (Focused) and (Btn = FocusedButton) then
      DrawFrame3D(Bitmap.Canvas, R, FFocusColor, FFocusColor, 1)
    else DrawFrame3D(Bitmap.Canvas, R, FBorderColor, FBorderColor, 1);

    if Down then
      DrawFrame3D(Bitmap.Canvas, R, clBtnShadow, clBtnFace, 1)
    else DrawOutline3D(Bitmap.Canvas, R, Colors[0], Colors[1], 1);
  end;

  DestCanvas.Draw(BtnRect.Left, BtnRect.Top, Bitmap);
end;

procedure TVrNavigator.Paint;
var
  I: TVrButtonType;
  R: TRect;
begin
  CalcPaintParams;
  ClearBitmapCanvas;

  DestCanvas := BitmapCanvas;
  try
    with DestCanvas do
    begin
      R := ClientRect;
      FBevel.Paint(DestCanvas, R);
      for I := Low(Buttons) to High(Buttons) do
        if Buttons[I].Visible then DrawButton(I);
    end;
  finally
    DestCanvas := Self.Canvas;
  end;

  inherited Paint;
end;

procedure TVrNavigator.CalcPaintParams;
var
  Gap: Integer;
  Count: Integer;
begin
  ViewPort := ClientRect;
  FBevel.GetVisibleArea(ViewPort);
  Count := VisibleButtonCount;
  if Count > 0 then
  begin
    Gap := (Count - 1) * FSpacing;
    case FOrientation of
      voHorizontal:
        begin
          ButtonWidth := (WidthOf(ViewPort) - Gap) div Count;
          ButtonHeight := HeightOf(ViewPort);
          if Count > 1 then
            Width := (ViewPort.Left * 2) + (Count * ButtonWidth) + Gap;
        end;
      voVertical:
        begin
          ButtonWidth := WidthOf(ViewPort);
          ButtonHeight := (HeightOf(ViewPort) - Gap) div Count;
          if Count > 1 then
            Height := (ViewPort.Top * 2) + (Count * ButtonHeight) + Gap;
        end;
    end;
  end;
end;

procedure TVrNavigator.GetButtonRect(Btn: TVrButtonType; var R: TRect);
var
  X, Y: Integer;
  I: TVrButtonType;
begin
  X := ViewPort.Left;
  Y := ViewPort.Top;
  for I := Low(Buttons) to High(Buttons) do
  begin
    if Buttons[I].Visible then
    begin
      if I = Btn then Break;
      case FOrientation of
        voHorizontal: Inc(X, ButtonWidth + FSpacing);
        voVertical: Inc(Y, ButtonHeight + FSpacing);
      end;
    end;
  end;
  R := Bounds(X, Y, ButtonWidth, ButtonHeight);
end;

procedure TVrNavigator.SetFocusedButton(Btn: TVrButtonType);
var
  OrgBtn: TVrButtonType;
begin
  if FocusedButton <> Btn then
  begin
    OrgBtn := FocusedButton;
    FocusedButton := Btn;
    DrawButton(OrgBtn);
    DrawButton(FocusedButton);
  end;
end;

procedure TVrNavigator.DoMouseDown(XPos, YPos: Integer);
var
  I: TVrButtonType;
  BtnRect: TRect;
  Clicked: Boolean;
begin
  Clicked := false;
  for I := Low(Buttons) to High(Buttons) do
    if Buttons[I].Visible then
    begin
      GetButtonRect(I, BtnRect);
      if PtInRect(BtnRect, Point(XPos, YPos)) then
      begin
        if Buttons[I].Enabled then
        begin
          Clicked := True;
          Break;
        end else Exit;
      end;
    end;

  if not Clicked then Exit;

  CurrentButton := I;

  if TabStop then SetFocus;

  if CurrentButton <> FocusedButton then
    SetFocusedButton(CurrentButton);

  Pressed := True;
  Down := True;
  DrawButton(I);
  MouseCapture := True;
end;

procedure TVrNavigator.WMLButtonDown(var Message: TWMLButtonDown);
begin
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrNavigator.WMLButtonDblClk(var Message: TWMLButtonDblClk);
begin
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrNavigator.WMMouseMove(var Message: TWMMouseMove);
var
  P: TPoint;
  R: TRect;
begin
  if Pressed then
  begin
    P := Point(Message.XPos, Message.YPos);
    GetButtonRect(CurrentButton, R);
    if PtInRect(R, P) <> Down then
    begin
      Down := not Down;
      DrawButton(CurrentButton);
    end;
  end;
end;

procedure TVrNavigator.DoClick(Button: TVrButtonType);
begin
  ButtonClick(CurrentButton);
end;

procedure TVrNavigator.WMLButtonUp(var Message: TWMLButtonUp);
begin
  MouseCapture := False;
  if Pressed then
  begin
    Pressed := False;
    if Down then
    begin
      Down := False;
      DrawButton(CurrentButton);  {raise button before calling code}
      DoClick(CurrentButton);
    end;
  end;
end;

procedure TVrNavigator.WMSetFocus(var Message: TWMSetFocus);
begin
  inherited;
  DrawButton(FocusedButton);
end;

procedure TVrNavigator.WMKillFocus(var Message: TWMKillFocus);
begin
  DrawButton(FocusedButton);
  inherited;
end;

procedure TVrNavigator.WMGetDlgCode(var Message: TWMGetDlgCode);
begin
  Message.Result := DLGC_WANTARROWS;
end;

procedure TVrNavigator.KeyUp(var Key: Word; Shift: TShiftState);
begin
  case Key of
    VK_SPACE:
      if Down then
        if Buttons[FocusedButton].Enabled then
        begin
          Down := false;
          DrawButton(CurrentButton);
          DoClick(CurrentButton);
        end;
  end;
end;

procedure TVrNavigator.KeyDown(var Key: Word; Shift: TShiftState);
var
  NewFocus: TVrButtonType;
begin
  case Key of
    VK_RIGHT:
      if not Down then
      begin
        NewFocus := FocusedButton;
        repeat
          if NewFocus < High(Buttons) then
            NewFocus := Succ(NewFocus);
        until (NewFocus = High(Buttons)) or (Buttons[NewFocus].Visible);
        if Buttons[NewFocus].Visible then
          SetFocusedButton(NewFocus);
      end;
    VK_LEFT:
      if not Down then
      begin
        NewFocus := FocusedButton;
        repeat
          if NewFocus > Low(Buttons) then
            NewFocus := Pred(NewFocus);
        until (NewFocus = Low(Buttons)) or (Buttons[NewFocus].Visible);
        if Buttons[NewFocus].Visible then
          SetFocusedButton(NewFocus);
      end;
    VK_SPACE:
      begin
        if Buttons[FocusedButton].Enabled then
        begin
          CurrentButton := FocusedButton;
          Down := True;
          DrawButton(CurrentButton);
        end;
      end;
  end;
end;

procedure TVrNavigator.ButtonClick(Button: TVrButtonType);
begin
  if Assigned(FOnButtonClick) then FOnButtonClick(Self, Button);
end;

{ TVrMediaButton }

constructor TVrMediaButton.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csSetCaption];
  Height := 15;
  Width := 40;
  TabStop := false;
  FFocusColor := clBlue;
  FBorderColor := clBlack;
  FButtonType := btPause;
  LoadBitmaps;
end;

destructor TVrMediaButton.Destroy;
begin
  DestroyBitmaps;
  inherited Destroy;
end;

procedure TVrMediaButton.LoadBitmaps;
var
  J: TVrButtonState;
  ResName: array[0..40] of Char;
begin
  DestroyBitmaps;
  for J := Low(TVrButtonState) to High(TVrButtonState) do
  begin
    Bitmaps[J] := TBitmap.Create;
    Bitmaps[J].Handle := LoadBitmap(HInstance,
        StrFmt(ResName, '%s_%s', [BtnStateName[J], BtnTypeName[FButtonType]]));
  end;
  MaskColor := clOlive;
end;

procedure TVrMediaButton.DestroyBitmaps;
var
  J: TVrButtonState;
begin
  for J := Low(TVrButtonState) to High(TVrButtonState) do
    FreeObject(Bitmaps[J]);
end;

procedure TVrMediaButton.SetButtonType(Value: TVrButtonType);
begin
  if FButtonType <> Value then
  begin
    FButtonType := Value;
    LoadBitmaps;
    UpdateControlCanvas;
  end;
end;

procedure TVrMediaButton.SetFocusColor(Value: TColor);
begin
  if FFocusColor <> Value then
  begin
    FFocusColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMediaButton.SetBorderColor(Value: TColor);
begin
  if FBorderColor <> Value then
  begin
    FBorderColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrMediaButton.Paint;
var
  R: TRect;
  HRes: Integer;
  Colors: array[0..1] of TColor;
  BX, BY: Integer;
  TheGlyph: TVrButtonState;
  ImageRect: TRect;
  Bitmap: TBitmap;
begin
  if Down then
  begin
    Colors[0] := clBtnFace;
    Colors[1] := clBtnHighlight;
  end
  else
  begin
    Colors[0] := clBtnHighlight;
    Colors[1] := clBtnShadow;
  end;

  HRes := ClientHeight div 10;
  if HRes < 2 then HRes := 2;
  R := ClientRect;
  InflateRect(R, -2, -2);
  DrawGradient(BitmapCanvas, R, Colors[0], Colors[1], voVertical, HRes);

  if Enabled then
    TheGlyph := mgEnabled else TheGlyph := mgDisabled;
  Bitmap := Bitmaps[TheGlyph];
  BX := (ClientWidth div 2) - (Bitmap.Width div 2);
  BY := (ClientHeight div 2) - (Bitmap.Height div 2);

  if Down then Inc(BY);
  ImageRect := Bounds(BX, BY, MinIntVal(R.Right, Bitmap.Width),
    MinIntVal(R.Bottom - 1, Bitmap.Height));
  BitmapCanvas.Brush.Style := bsClear;
  BitmapCanvas.BrushCopy(ImageRect, Bitmap,
    BitmapRect(Bitmap), MaskColor);

  R := ClientRect;
  if HasFocus then
    DrawFrame3D(BitmapCanvas, R, FFocusColor, FFocusColor, 1)
  else DrawFrame3D(BitmapCanvas, R, FBorderColor, FBorderColor, 1);

  if Down then
    DrawFrame3D(BitmapCanvas, R, clBtnShadow, clBtnFace, 1)
  else DrawOutline3D(BitmapCanvas, R, Colors[0], Colors[1], 1);

  inherited Paint;
end;

procedure TVrMediaButton.DoMouseDown(XPos, YPos: Integer);
var
  P: TPoint;
begin
  P := Point(XPos, YPos);
  if PtInRect(ClientRect, P) then
  begin
    Pressed := True;
    Down := True;
    MouseCapture := true;
    UpdateControlCanvas;
  end;
end;

procedure TVrMediaButton.WMLButtonDown(var Message: TWMLButtonDown);
begin
  inherited;
  DoMouseDown(Message.XPos, Message.YPos);
  if TabStop then SetFocus;
end;

procedure TVrMediaButton.WMLButtonDblClk(var Message: TWMLButtonDblClk);
begin
  inherited;
  DoMouseDown(Message.XPos, Message.YPos);
end;

procedure TVrMediaButton.WMMouseMove(var Message: TWMMouseMove);
var
  P: TPoint;
begin
  inherited;
  if Pressed then
  begin
    P := Point(Message.XPos, Message.YPos);
    if PtInRect(ClientRect, P) <> Down then
    begin
      Down := not Down;
      UpdateControlCanvas;
    end;
  end;
end;

procedure TVrMediaButton.WMLButtonUp(var Message: TWMLButtonUp);
var
  DoClick: Boolean;
begin
  MouseCapture := false;
  DoClick := Pressed and Down;
  Down := False;
  Pressed := false;
  if DoClick then UpdateControlCanvas;
  inherited;
end;

procedure TVrMediaButton.CMEnabledChanged(var Message: TMessage);
begin
  inherited;
  UpdateControlCanvas;
end;

procedure TVrMediaButton.WMSetFocus(var Message: TWMSetFocus);
begin
  HasFocus := true;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrMediaButton.WMKillFocus(var Message: TWMKillFocus);
begin
  HasFocus := false;
  UpdateControlCanvas;
  inherited;
end;

procedure TVrMediaButton.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited KeyDown(Key, Shift);
  if (not Down) and (Key = VK_SPACE) then DoMouseDown(0, 0);
end;

procedure TVrMediaButton.KeyUp(var Key: Word; Shift: TShiftState);
begin
  inherited KeyUp(Key, Shift);
  if Key = VK_SPACE then
  begin
    MouseCapture := false;
    if Pressed and Down then
    begin
      Down := False;
      UpdateControlCanvas;
      inherited Click;
    end;
    Pressed := False;
  end;
end;


end.
