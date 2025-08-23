{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrGradient;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrConst, VrTypes, VrClasses, VrControls, VrSysUtils;

type
  TVrCustomGradient = class(TVrGraphicImageControl)
  private
    FStartColor: TColor;
    FEndColor: TColor;
    FColorWidth: Integer;
    FOrientation: TVrOrientation;
    FFormDrag: Boolean;
    procedure SetColorWidth(Value: Integer);
    procedure SetOrientation(Value: TVrOrientation);
    procedure SetStartColor(Value: TColor);
    procedure SetEndColor(Value: TColor);
    procedure WMLButtonDown(var Msg: TWMLBUTTONDOWN); message WM_LBUTTONDOWN;
  protected
    procedure Paint; override;
    function GetPalette: HPalette; override;
    property ColorWidth: Integer read FColorWidth write SetColorWidth default 1;
    property Orientation: TVrOrientation read FOrientation write SetOrientation default voVertical;
    property StartColor: TColor read FStartColor write SetStartColor default clLime;
    property EndColor: TColor read FEndColor write SetEndColor default clBlack;
    property FormDrag: Boolean read FFormDrag write FFormDrag default false;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

  TVrGradient = class(TVrCustomGradient)
    property StartColor;
    property EndColor;
    property ColorWidth;
    property Orientation;
    property FormDrag;
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

{TVrGradient}

constructor TVrCustomGradient.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque, csReplicatable];
  Width := 150;
  Height := 150;
  FColorWidth := 1;
  FOrientation := voVertical;
  FStartColor := clLime;
  FEndColor := clBlack;
  FFormDrag := false;
end;

destructor TVrCustomGradient.Destroy;
begin
  inherited Destroy;
end;

function TVrCustomGradient.GetPalette: HPalette;
begin
  Result := BitmapImage.Palette;
end;

procedure TVrCustomGradient.Paint;
begin
  DrawGradient(BitmapCanvas, ClientRect,
    FStartColor, FEndColor, FOrientation, FColorWidth);
  inherited Paint;
end;

procedure TVrCustomGradient.SetColorWidth(Value: Integer);
begin
  if (FColorWidth <> Value) and (Value > 0) then
  begin
    FColorWidth := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomGradient.SetOrientation(Value: TVrOrientation);
begin
  if FOrientation <> Value then
  begin
    FOrientation := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomGradient.SetStartColor(Value: TColor);
begin
  if FStartColor <> Value then
  begin
    FStartColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomGradient.SetEndColor(Value: TColor);
begin
  if FEndColor <> Value then
  begin
    FEndColor := Value;
    UpdateControlCanvas;
  end;
end;

procedure TVrCustomGradient.WMLButtonDown(var Msg: TWMLBUTTONDOWN);
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
