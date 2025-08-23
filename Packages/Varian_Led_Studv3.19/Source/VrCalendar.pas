{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrCalendar;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrGridStyle = (gsRaised, gsLowered, gsSingle);
  TVrCalendarGrid = class(TVrPersistent)
  private
    FStyle: TVrGridStyle;
    FColor: TColor;
    FShadow3D: TColor;
    FHighlight3D: TColor;
    FWidth: Integer;
    procedure SetStyle(Value: TVrGridStyle);
    procedure SetColor(Value: TColor);
    procedure SetShadow3D(Value: TColor);
    procedure SetHighlight3D(Value: TColor);
    procedure SetWidth(Value: Integer);
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
  published
    property Style: TVrGridStyle read FStyle write SetStyle;
    property Color: TColor read FColor write SetColor;
    property Highlight3D: TColor read FHighlight3D write SetHighlight3D;
    property Shadow3D: TColor read FShadow3D write SetShadow3D;
    property Width: Integer read FWidth write SetWidth;
  end;

  TVrCalendar = class;
  TVrCalendarItem = class(TVrCollectionItem)
  private
    FCaption: string;
    FActive: Boolean;
    FVisible: Boolean;
    procedure SetActive(Value: Boolean);
    procedure SetCaption(const Value: string);
    procedure SetVisible(Value: Boolean);
  public
    constructor Create(Collection: TVrCollection); override;
    property Caption: string read FCaption write SetCaption;
    property Active: Boolean read FActive write SetActive;
    property Visible: Boolean read FVisible write SetVisible;
  end;

  TVrCalendarItems = class(TVrCollection)
  private
    FOwner: TVrCalendar;
    function GetItem(Index: Integer): TVrCalendarItem;
  protected
    procedure Update(Item: TVrCollectionItem); override;
    property Owner: TVrCalendar read FOwner;
  public
    constructor Create(AOwner: TVrCalendar);
    property Items[Index: Integer]: TVrCalendarItem read GetItem;
  end;

  TVrCalendarDrawEvent = procedure(Sender: TObject; Canvas: TCanvas; Rect: TRect;
    Index: Integer; State: Boolean) of object;

  TVrGridAlignment =
    (gaUpperLeft, gaUpperRight, gaBottomLeft, gaBottomRight, gaCenter);

  TVrCalendarOption = (coActiveClick, coMouseClip, coTrackMouse);
  TVrCalendarOptions = set of TVrCalendarOption;

  TVrCalendar = class(TVrGraphicImageControl)
  private
    FRows: TVrRowInt;
    FColumns: TVrColInt;
    FGrid: TVrCalendarGrid;
    FDrawStyle: TVrDrawStyle;
    FAlignment: TVrGridAlignment;
    FPalette: TVrPalette;
    FFirstIndex: Integer;
    FOnDraw: TVrCalendarDrawEvent;
    FItemIndex: Integer;
    FDigits: Integer;
    FOptions: TVrCalendarOptions;
    FOrientation: TVrOrientation;
    FNextStep: Integer;
    FBevel: TVrBevel;
    ViewPort: TRect;
    SizeX, SizeY: Integer;
    IsPressed: Boolean;
    TrackLast: Integer;
    CurrIndex: Integer;
    Collection: TVrCalendarItems;
    procedure SetRows(Value: TVrRowInt);
    procedure SetColumns(Value: TVrColInt);
    procedure SetDrawStyle(Value: TVrDrawStyle);
    procedure SetAlignment(Value: TVrGridAlignment);
    procedure SetFirstIndex(Value: Integer);
    procedure SetDigits(Value: Integer);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetNextStep(Value: Integer);
    procedure SetOptions(Value: TVrCalendarOptions);
    procedure SetPalette(Value: TVrPalette);
    procedure SetBevel(Value: TVrBevel);
    procedure SetGrid(Value: TVrCalendarGrid);
    function GetCount: Integer;
    function GetItem(Index: Integer): TVrCalendarItem;
    procedure StyleChanged(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
  protected
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure CreateObjects;
    procedure CalcPaintParams;
    procedure UpdateItem(Index: Integer);
    procedure UpdateItems;
    procedure Paint; override;
    procedure GetItemRect(Index: Integer; var R: TRect);
    function GetItemIndex(X, Y: Integer): Integer;
    procedure Loaded; override;
    procedure Click; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Reset;
    property Count: Integer read GetCount;
    property Items[Index: Integer]: TVrCalendarItem read GetItem;
    property ItemIndex: Integer read FItemIndex;
  published
    property Palette: TVrPalette read FPalette write SetPalette;
    property Rows: TVrRowInt read FRows write SetRows default 5;
    property Columns: TVrColInt read FColumns write SetColumns default 5;
    property Grid: TVrCalendarGrid read FGrid write SetGrid;
    property DrawStyle: TVrDrawStyle read FDrawStyle write SetDrawStyle default dsNormal;
    property Alignment: TVrGridAlignment read FAlignment write SetAlignment default gaCenter;
    property FirstIndex: Integer read FFirstIndex write SetFirstIndex default 1;
    property Digits: Integer read FDigits write SetDigits default 2;
    property Options: TVrCalendarOptions read FOptions write SetOptions default [];
    property NextStep: Integer read FNextStep write SetNextStep default 1;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voHorizontal;
    property Bevel: TVrBevel read FBevel write SetBevel;
    property OnDraw: TVrCalendarDrawEvent read FOnDraw write FOnDraw;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color default clBlack;
    property Enabled;
    property Font;
    property Cursor;
    property DragMode;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragCursor;
    property ParentColor default false;
    property ParentFont;
    property ParentShowHint;
    property ShowHint;
    property Visible;
    property OnClick;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}    
    property OnDblClick;
    property OnMouseMove;
    property OnMouseDown;
    property OnMouseUp;
    property OnDragOver;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnDragDrop;
    property OnEndDrag;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


implementation

const
  TextAlignments: array[TVrGridAlignment] of Integer = (
    DT_LEFT or DT_TOP,
    DT_RIGHT or DT_TOP,
    DT_LEFT or DT_BOTTOM,
    DT_RIGHT or DT_BOTTOM,
    DT_VCENTER or DT_CENTER);


{ TVrCalendarGrid }

constructor TVrCalendarGrid.Create;
begin
  inherited Create;
  FStyle := gsLowered;
  FColor := clLime;
  FShadow3D := clBtnShadow;
  FHighlight3D := clBtnHighlight;
  FWidth := 1;
end;

procedure TVrCalendarGrid.Assign(Source: TPersistent);
begin
  if (Source <> nil) and (Source is TVrCalendarGrid) then
  begin
    BeginUpdate;
    try
      Style := TVrCalendarGrid(Source).Style;
      Color := TVrCalendarGrid(Source).Color;
      Shadow3D := TVrCalendarGrid(Source).Shadow3D;
      Highlight3D := TVrCalendarGrid(Source).Highlight3D;
      Width := TVrCalendarGrid(Source).Width;
    finally
      EndUpdate;
    end;
  end else inherited Assign(Source);
end;

procedure TVrCalendarGrid.SetStyle(Value: TVrGridStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    Changed;
  end;
end;

procedure TVrCalendarGrid.SetColor(Value: TColor);
begin
  if FColor <> Value then
  begin
    FColor := Value;
    Changed;
  end;
end;

procedure TVrCalendarGrid.SetShadow3D(Value: TColor);
begin
  if FShadow3D <> Value then
  begin
    FShadow3D := Value;
    Changed;
  end;
end;

procedure TVrCalendarGrid.SetHighlight3D(Value: TColor);
begin
  if FHighlight3D <> Value then
  begin
    FHighlight3D := Value;
    Changed;
  end;
end;

procedure TVrCalendarGrid.SetWidth(Value: Integer);
begin
  if FWidth <> Value then
  begin
    FWidth := Value;
    Changed;
  end;
end;

{ TVrCalendarItem }

constructor TVrCalendarItem.Create(Collection: TVrCollection);
begin
  inherited Create(Collection);
  FActive := false;
  FVisible := True;
  with (Collection as TVrCalendarItems).Owner do
    FCaption := Format('%.' + IntToStr(Digits) + 'd',
      [FirstIndex + (Index * NextStep)]);
end;

procedure TVrCalendarItem.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    Changed(false);
  end;
end;

procedure TVrCalendarItem.SetCaption(const Value: string);
begin
  if FCaption <> Value then
  begin
    FCaption := Value;
    Changed(false);
  end;
end;

procedure TVrCalendarItem.SetVisible(Value: Boolean);
begin
  if FVisible <> Value then
  begin
    FVisible := Value;
    Changed(false);
  end;
end;

{ TVrCalendarItems }

constructor TVrCalendarItems.Create(AOwner: TVrCalendar);
begin
  inherited Create;
  FOwner := AOwner;
end;

function TVrCalendarItems.GetItem(Index: Integer): TVrCalendarItem;
begin
  Result := TVrCalendarItem(inherited Items[Index]);
end;

procedure TVrCalendarItems.Update(Item: TVrCollectionItem);
begin
  if Item <> nil then
    FOwner.UpdateItem(Item.Index) else
    FOwner.UpdateItems;
end;

{ TVrCalendar }

constructor TVrCalendar.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque] - [csDoubleClicks];
  Height := 145;
  Width := 225;
  Color := clBlack;
  Font.Name := 'Arial';
  Font.Size := 7;
  FRows := 5;
  FColumns := 5;
  FDrawStyle := dsNormal;
  FAlignment := gaCenter;
  FDigits := 2;
  FOrientation := voHorizontal;
  FFirstIndex := 1;
  FNextStep := 1;
  FOptions := [];
  FPalette := TVrPalette.Create;
  FPalette.OnChange := StyleChanged;
  FGrid := TVrCalendarGrid.Create;
  FGrid.OnChange := StyleChanged;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsLowered;
    InnerWidth := 2;
    InnerSpace := 0;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  TrackLast := -1;
  Collection := TVrCalendarItems.Create(Self);
  CreateObjects;
end;

destructor TVrCalendar.Destroy;
begin
  FPalette.Free;
  FGrid.Free;
  FBevel.Free;
  Collection.Free;
  inherited Destroy;
end;

procedure TVrCalendar.Loaded;
begin
  inherited Loaded;
  SizeX := Width div FColumns;
  SizeY := Height div FRows;
end;

procedure TVrCalendar.Click;
begin
end;

procedure TVrCalendar.CreateObjects;
var
  I, Count: Integer;
begin
  Collection.Clear;
  Count := FColumns * FRows;
  for I := 0 to Pred(Count) do
    TVrCalendarItem.Create(Collection);
  FItemIndex := -1;
  TrackLast := -1;
end;

function TVrCalendar.GetCount: Integer;
begin
  Result := Collection.Count;
end;

function TVrCalendar.GetItem(Index: Integer): TVrCalendarItem;
begin
  Result := Collection.Items[Index];
end;

procedure TVrCalendar.StyleChanged(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrCalendar.BevelChanged(Sender: TObject);
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


procedure TVrCalendar.SetOptions(Value: TVrCalendarOptions);
begin
  FOptions := Value;
end;

procedure TVrCalendar.UpdateItem(Index: Integer);
var
  Rect: TRect;
  Item: TVrCalendarItem;
  State: Boolean;
begin
  Item := Collection.Items[Index];

  GetItemRect(Index, Rect);

  with DestCanvas do
    case FGrid.Style of
      gsLowered:
          DrawFrame3D(DestCanvas, Rect, FGrid.Shadow3D, FGrid.Highlight3D, FGrid.Width);
        gsRaised:
          DrawFrame3D(DestCanvas, Rect, FGrid.Highlight3D, FGrid.Shadow3D, FGrid.Width);
        gsSingle:
          begin
            if FOrientation = voHorizontal then
            begin
              if (Index mod FColumns <> FColumns - 1) then Inc(Rect.Right);
              if Index < Count - FColumns then Inc(Rect.Bottom);
            end
            else
            begin
              if (Index mod FRows <> FRows - 1) then Inc(Rect.Bottom);
              if Index < Count - FRows then Inc(Rect.Right);
            end;
            DrawFrame3D(DestCanvas, Rect, FGrid.Color, FGrid.Color, FGrid.Width);
          end;
    end; //case

  State := (TrackLast = Index) or Item.Active;

  if FDrawStyle = dsOwnerDraw then
  begin
    if Assigned(FOnDraw) then
      FOnDraw(Self, DestCanvas, Rect, Index, State);
    Exit;
  end;

  if Item.Visible then
    with DestCanvas do
    begin
      Font := Self.Font;

      Font.Color := FPalette.Colors[ord(State)];
      Brush.Color := Self.Color;
      DrawText(handle, PChar(Item.Caption), -1, Rect,
        DT_SINGLELINE or DT_EXPANDTABS or TextAlignments[FAlignment]);
    end;
end;

procedure TVrCalendar.UpdateItems;
var
  I: Integer;
begin
  for I := 0 to Collection.Count - 1 do
    UpdateItem(I);
end;

procedure TVrCalendar.Reset;
var
  I: Integer;
begin
  for I := 0 to Collection.Count - 1 do
    Items[I].Active := false;
end;

procedure TVrCalendar.Paint;
var
  R: TRect;
begin
  CalcPaintParams;
  ClearBitmapCanvas;

  DestCanvas := BitmapCanvas;
  try
    R := ClientRect;
    FBevel.Paint(DestCanvas, R);
    UpdateItems;
    inherited Paint;
  finally
    DestCanvas := Self.Canvas;
  end;
end;

procedure TVrCalendar.CalcPaintParams;
var
  NewWidth, NewHeight, X, Y: Integer;
begin
  ViewPort := ClientRect;
  FBevel.GetVisibleArea(ViewPort);

  X := WidthOf(ViewPort) div FColumns;
  NewWidth := (ViewPort.Left * 2) + (FColumns * X);

  Y := HeightOf(ViewPort) div FRows;
  NewHeight := (ViewPort.Top * 2) + (FRows * Y);

  if (NewWidth <> Width) or (NewHeight <> Height) then
    BoundsRect := Bounds(Left, Top, NewWidth, NewHeight);

  SizeX := WidthOf(ViewPort) div FColumns;
  SizeY := HeightOf(ViewPort) div FRows;
end;

procedure TVrCalendar.GetItemRect(Index: Integer; var R: TRect);
var
  X, Y: Integer;
begin
  if FOrientation = voHorizontal then
  begin
    X := (Index mod FColumns) * SizeX;
    Y := (Index div FColumns) * SizeY;
  end
  else
  begin
    X := (Index div FRows) * SizeX;
    Y := (Index mod FRows) * SizeY;
  end;

  R := Bounds(ViewPort.Left + X, ViewPort.Top + Y, SizeX, SizeY);
end;

function TVrCalendar.GetItemIndex(X, Y: Integer): Integer;
begin
  if X > ViewPort.Right then X := ViewPort.Right
  else if X < ViewPort.Left then X := ViewPort.Left;
  if Y > ViewPort.Bottom then Y := ViewPort.Bottom
  else if Y < ViewPort.Top then Y := ViewPort.Top;

  if Orientation = voHorizontal then
  begin
    X := ((Y - ViewPort.Top) div SizeY) * FColumns +
         ((X - ViewPort.Left) div SizeX);
    Result := X;
  end
  else
  begin
    Y := ((X - ViewPort.Left) div SizeX) * FRows +
         ((Y - ViewPort.Top) div SizeY);
    Result := Y;
  end;
end;

procedure TVrCalendar.SetRows(Value: TVrRowInt);
begin
  if FRows <> Value then
  begin
    FRows := Value;
    CreateObjects;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetColumns(Value: TVrColInt);
begin
  if FColumns <> Value then
  begin
    FColumns := Value;
    CreateObjects;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetDrawStyle(Value: TVrDrawStyle);
begin
  if FDrawStyle <> Value then
  begin
    FDrawStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetFirstIndex(Value: Integer);
begin
  if FFirstIndex <> Value then
  begin
    FFirstIndex := Value;
    CreateObjects;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetDigits(Value: Integer);
begin
  if FDigits <> Value then
  begin
    FDigits := Value;
    CreateObjects;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetAlignment(Value: TVrGridAlignment);
begin
  if FAlignment <> Value then
  begin
    FAlignment := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetNextStep(Value: Integer);
begin
  if FNextStep <> Value then
  begin
    FNextStep := Value;
    CreateObjects;
    UpdateControlCanvas;
  end;
end;

procedure TVrCalendar.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrCalendar.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrCalendar.SetGrid(Value: TVrCalendarGrid);
begin
  FGrid.Assign(Value);
end;

procedure TVrCalendar.MouseMove(Shift: TShiftState; X, Y: Integer);
var
  Index, P: Integer;
begin
  inherited;
  if not PtInRect(ViewPort, Point(X, Y)) then
    if (coTrackMouse in Options) and Enabled then
    begin
      if TrackLast <> -1 then
      begin
        P := TrackLast;
        TrackLast := -1;
        UpdateItem(P);
      end;
      Exit;
    end;

  if (coTrackMouse in Options) and Enabled then
  begin
    Index := GetItemIndex(X, Y);
    if (TrackLast <> Index) then
    begin
      if TrackLast <> -1 then
      begin
        P := TrackLast;
        TrackLast := -1;
        UpdateItem(P);
      end;
      TrackLast := Index;
      UpdateItem(TrackLast);
    end;
  end;
end;

procedure TVrCalendar.MouseDown(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  R: TRect;
begin
  if PtInRect(ViewPort, Point(X, Y)) then
    if (Button = mbLeft) and Enabled then
    begin
      IsPressed := True;
      CurrIndex := GetItemIndex(X, Y);
      FItemIndex := -1;
      if (coMouseClip in Options) then
      begin
        R := Bounds(ClientOrigin.X, ClientOrigin.Y,
          ClientWidth, ClientHeight);
        ClipCursor(@R);
      end;
    end;
  inherited;
end;

procedure TVrCalendar.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if IsPressed then
  begin
    IsPressed := false;
    if (coMouseClip in Options) then ClipCursor(nil);

    FItemIndex := GetItemIndex(X, Y);
    if CurrIndex <> FItemIndex then FItemIndex := -1
    else
    begin
      if (coActiveClick in Options) then
        Items[FItemIndex].Active := True;
      inherited Click;
    end;
  end;
  inherited;
end;

procedure TVrCalendar.CMMouseLeave(var Message: TMessage);
var
  P: Integer;
begin
  inherited;
  if (coTrackMouse in Options) and Enabled then
  begin
    if TrackLast <> -1 then
    begin
      P := TrackLast;
      TrackLast := -1;
      UpdateItem(P);
    end;
  end;
end;


end.
