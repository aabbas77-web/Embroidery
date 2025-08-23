{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrDeskTop;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrConst, VrControls, VrSysUtils;

type
  TVrDeskTop = class(TVrGraphicImageControl)
  private
    FGlyph: TBitmap;
    FFormDrag: Boolean;
    procedure SetGlyph(Value: TBitmap);
    procedure WMLButtonDown(var Msg: TWMLBUTTONDOWN); message WM_LBUTTONDOWN;
  protected
    procedure Paint; override;
    function GetPalette: HPalette; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Glyph: TBitmap read FGlyph write SetGlyph;
    property FormDrag: Boolean read FFormDrag write FFormDrag default false;
    property Color default clBlack;
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


{ TVrDeskTop }

constructor TVrDeskTop.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csReplicatable];
  Width := 150;
  Height := 150;
  Color := clBtnFace;
  ParentColor := false;
  FFormDrag := false;
  FGlyph := TBitmap.Create;
end;

destructor TVrDeskTop.Destroy;
begin
  FGlyph.Free;
  inherited Destroy;
end;

function TVrDeskTop.GetPalette: HPalette;
begin
  Result := FGlyph.Palette;
end;

procedure TVrDeskTop.Paint;
begin
  if FGlyph.Empty then
    ClearBitmapCanvas
  else DrawTiledBitmap(BitmapCanvas, ClientRect, FGlyph);

  if Designing then
    with inherited BitmapCanvas do
    begin
      Pen.Style := psDot;
      Brush.Style := bsClear;
      Rectangle(0, 0, Width, Height);
    end;

  inherited Paint;
end;

procedure TVrDeskTop.SetGlyph(Value: TBitmap);
begin
  FGlyph.Assign(Value);
  UpdateControlCanvas;
end;

procedure TVrDeskTop.WMLButtonDown(var Msg: TWMLBUTTONDOWN);
var
  AOwner: TComponent;
begin
  inherited;
  if FFormDrag then
  begin
    ReleaseCapture;
    AOwner := GetOwnerControl(Self);
    if AOwner <> nil then
      TWinControl(AOwner).Perform(WM_SYSCOMMAND, SC_DRAGMOVE, 0);
  end;
end;



end.
