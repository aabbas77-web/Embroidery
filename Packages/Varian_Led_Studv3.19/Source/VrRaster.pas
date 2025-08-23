{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrRaster;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrCustomRaster = class;

  TVrRasterLed = class(TVrCollectionItem)
  private
    FActive: Boolean;
    procedure SetActive(Value: Boolean);
  public
    constructor Create(Collection: TVrCollection); override;
    property Active: Boolean read FActive write SetActive;
  end;

  TVrRasterLeds = class(TVrCollection)
  private
    FOwner: TVrCustomRaster;
    function GetItem(Index: Integer): TVrRasterLed;
  protected
    procedure Update(Item: TVrCollectionItem); override;
  public
    constructor Create(AOwner: TVrCustomRaster);
    property Items[Index: Integer]: TVrRasterLed read GetItem;
  end;

  TVrRasterStyle = (rsRaised, rsLowered, rsNone, rsFlat);

  TVrCustomRaster = class(TVrGraphicImageControl)
  private
    FColumns: TVrColInt;
    FRows: TVrRowInt;
    FPalette: TVrPalette;
    FStyle: TVrRasterStyle;
    FPlainColors: Boolean;
    FMultiSelect: Boolean;
    FSpacing: Integer;
    FBevel: TVrBevel;
    ViewPort: TRect;
    CellXSize: Integer;
    CellYSize: Integer;
    Collection: TVrRasterLeds;
    function GetCount: Integer;
    function GetItem(Index: Integer): TVrRasterLed;
    procedure SetColumns(Value: TVrColInt);
    procedure SetRows(Value: TVrRowInt);
    procedure SetStyle(Value: TVrRasterStyle);
    procedure SetPlainColors(Value: Boolean);
    procedure SetMultiSelect(Value: Boolean);
    procedure SetSpacing(Value: Integer);
    procedure SetPalette(Value: TVrPalette);
    procedure SetBevel(Value: TVrBevel);
    procedure PaletteModified(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
    procedure SetActiveState(Origin: Integer; State: Boolean);
  protected
    procedure CreateObjects;
    procedure GetItemRect(Index: Integer; var R: TRect);
    procedure CalcPaintParams;
    procedure UpdateLed(Index: Integer);
    procedure UpdateLeds;
    procedure Paint; override;
    property Columns: TVrColInt read FColumns write SetColumns default 5;
    property Rows: TVrRowInt read FRows write SetRows default 5;
    property Style: TVrRasterStyle read FStyle write SetStyle default rsLowered;
    property Palette: TVrPalette read FPalette write SetPalette;
    property PlainColors: boolean read FPlainColors write SetPlainColors default true;
    property MultiSelect: Boolean read FMultiSelect write SetMultiSelect default True;
    property Spacing: Integer read FSpacing write SetSpacing default 2;
    property Bevel: TVrBevel read FBevel write SetBevel;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Count: Integer read GetCount;
    property Items[Index: Integer]: TVrRasterLed read GetItem;
  end;

  TVrRaster = class(TVrCustomRaster)
    property Columns;
    property Rows;
    property Style;
    property Palette;
    property PlainColors;
    property MultiSelect;
    property Spacing;
    property Bevel;
{$IFDEF VER110}
    property Anchors;
    property Constraints;
{$ENDIF}
    property Color;
    property Cursor;
    property DragMode;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragCursor;
    property ParentColor default True;
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
    property OnDragDrop;
{$IFDEF VER110}
    property OnEndDock;
{$ENDIF}
    property OnEndDrag;
{$IFDEF VER110}
    property OnStartDock;
{$ENDIF}
    property OnStartDrag;
  end;


implementation


{ TVrRasterLed }

constructor TVrRasterLed.Create(Collection: TVrCollection);
begin
  FActive := false;
  inherited Create(Collection);
end;

procedure TVrRasterLed.SetActive(Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;
    Changed(false);
  end;
end;

{ TVrRasterLeds }

constructor TVrRasterLeds.Create(AOwner: TVrCustomRaster);
begin
  inherited Create;
  FOwner := AOwner;
end;

function TVrRasterLeds.GetItem(Index: Integer): TVrRasterLed;
begin
  Result := TVrRasterLed(inherited Items[Index]);
end;

procedure TVrRasterLeds.Update(Item: TVrCollectionItem);
begin
  if Item <> nil then
    FOwner.UpdateLed(Item.Index) else
    FOwner.UpdateLeds;
end;

{TVrCustomRaster}

constructor TVrCustomRaster.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 145;
  Height := 70;
  ParentColor := true;
  FStyle := rsLowered;
  FMultiSelect := true;
  FSpacing := 2;
  FPalette := TVrPalette.Create;
  FPalette.OnChange := PaletteModified;
  FPlainColors := true;
  FColumns := 5;
  FRows := 5;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerStyle := bsNone;
    InnerWidth := 1;
    InnerSpace := 0;
    InnerColor := clBlack;
    OnChange := BevelChanged;
  end;
  Collection := TVrRasterLeds.Create(Self);
  CreateObjects;
end;

destructor TVrCustomRaster.Destroy;
begin
  FPalette.Free;
  FBevel.Free;
  Collection.Free;
  inherited Destroy;
end;

procedure TVrCustomRaster.CreateObjects;
var
  I, N: Integer;
begin
  Collection.Clear;
  N := FColumns * FRows;
  for I := 0 to Pred(N) do
    TVrRasterLed.Create(Collection);
end;

function TVrCustomRaster.GetCount: Integer;
begin
  Result := Collection.Count;
end;

function TVrCustomRaster.GetItem(Index: Integer): TVrRasterLed;
begin
  Result := Collection.Items[Index];
end;

procedure TVrCustomRaster.PaletteModified(Sender: TObject);
begin
  UpdateControlCanvas;
end;

procedure TVrCustomRaster.BevelChanged(Sender: TObject);
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

procedure TVrCustomRaster.SetActiveState(Origin: Integer; State: Boolean);
var
  I: Integer;
begin
  for I := 0 to Pred(Count) do
    if I <> Origin then Collection.Items[I].Active := State;
end;

procedure TVrCustomRaster.UpdateLed(Index: Integer);
var
  R: TRect;
  Item: TVrRasterLed;

  function GetCurrentColor(Value: Boolean): TColor;
  begin
    Result := FPalette.Low;
    if Value then Result := FPalette.High;
  end;

begin
  Item := Collection.Items[Index];

  if (Item.Active) and (not FMultiSelect) then
    SetActiveState(Index, false);

  GetItemRect(Index, R);
  InflateRect(R, -FSpacing, -FSpacing);
  case FStyle of
    rsRaised:
      begin
        DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
        if not FPlainColors then
          DrawOutline3D(DestCanvas, R, GetCurrentColor(Item.Active), clBlack, 1)
        else
        begin
          if not Item.Active then
            DrawOutline3D(DestCanvas, R, FPalette.High, FPalette.Low, 1)
          else DrawOutline3D(DestCanvas, R, clBtnHighlight, FPalette.High, 1);
        end;
      end;
    rsLowered:
      begin
        DrawOutline3D(DestCanvas, R, clBtnShadow, clBtnHighlight, 1);
        DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
      end;
    rsFlat:
      DrawOutline3D(DestCanvas, R, clBlack, clBlack, 1);
    rsNone:;
  end;

  with DestCanvas do
  begin
    if FPlainColors then
    begin
      Brush.Style := bsSolid;
      Brush.Color := GetCurrentColor(Item.Active);
      FillRect(R);
    end
    else DrawGradient(DestCanvas, R,
      GetCurrentColor(Item.Active), clBlack, voVertical, 1);
  end;
end;

procedure TVrCustomRaster.UpdateLeds;
var
  I: Integer;
begin
  for I := 0 to Count - 1 do
    UpdateLed(I);
end;

procedure TVrCustomRaster.Paint;
var
  R: TRect;
begin
  CalcPaintParams;
  ClearBitmapCanvas;
  DestCanvas := BitmapCanvas;
  try
    R := ClientRect;
    FBevel.Paint(DestCanvas, R);
    UpdateLeds;
    inherited Paint;
  finally
    DestCanvas := Self.Canvas;
  end;
end;

procedure TVrCustomRaster.CalcPaintParams;
var
  NewWidth, NewHeight: Integer;
begin
  ViewPort := ClientRect;
  FBevel.GetVisibleArea(ViewPort);

  CellXSize := WidthOf(ViewPort) div FColumns;
  CellYSize := HeightOf(ViewPort) div FRows;
  NewWidth := (ViewPort.Left * 2) + (CellXSize * FColumns);
  NewHeight := (ViewPort.Top * 2) + (CellYSize * FRows);

  if (NewWidth <> Width) or (NewHeight <> Height) then
    BoundsRect := Bounds(Left, Top, NewWidth, NewHeight);
end;

procedure TVrCustomRaster.GetItemRect(Index: Integer; var R: TRect);
var
  X, Y: Integer;
begin
  X := (Index mod FColumns) * CellXSize;
  Y := (Index div FColumns) * CellYSize;
  R := Bounds(ViewPort.Left + X, ViewPort.Top + Y, CellXSize, CellYSize);
end;

procedure TVrCustomRaster.SetPalette(Value: TVrPalette);
begin
  FPalette.Assign(Value);
end;

procedure TVrCustomRaster.SetBevel(Value: TVrBevel);
begin
  FBevel.Assign(Value);
end;

procedure TVrCustomRaster.SetColumns(Value: TVrColInt);
begin
  if (FColumns <> Value) then
  begin
    FColumns := Value;
    CreateObjects;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomRaster.SetRows(Value: TVrRowInt);
begin
  if (FRows <> Value) then
  begin
    FRows := Value;
    CreateObjects;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomRaster.SetStyle(Value: TVrRasterStyle);
begin
  if FStyle <> Value then
  begin
    FStyle := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomRaster.SetMultiSelect(Value: Boolean);
begin
  if FMultiSelect <> Value then
  begin
    FMultiSelect := Value;
    if not Value then SetActiveState(-1, false)
      else UpdateLeds;
  end;
end;

procedure TVrCustomRaster.SetPlainColors(Value: Boolean);
begin
  if FPlainColors <> Value then
  begin
    FPlainColors := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomRaster.SetSpacing(Value: Integer);
begin
  if (FSpacing <> Value) and (Value >= 0) then
  begin
    FSpacing := Value;
    UpdateControlCanvas;
  end;
end;


end.
