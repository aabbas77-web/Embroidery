{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrFormShape;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrSysUtils;

type
  TVrRgnData = class(TPersistent)
  private
    FSize: Integer;
    FBuffer: PRgnData;
    procedure SetSize(Value: Integer);
  public
    destructor Destroy; override;
    property Size: Integer read FSize write SetSize;
    property Buffer: PRgnData read FBuffer write FBuffer;
  end;

  TVrFormShape = class(TVrGraphicImageControl)
  private
    FMask: TBitmap;
    FRgnData: TVrRgnData;
    FRgn: HRgn;
    function GetMaskColor: TColor;
    procedure SetMask(Value: TBitmap);
    procedure SetMaskColor(Value: TColor);
    procedure UpdateMask;
    procedure UpdateRegion;
    procedure ReadMask(Reader: TStream);
    procedure WriteMask(Writer: TStream);
    procedure WMEraseBkgnd(var Message: TWMEraseBkgnd); message WM_ERASEBKGND;
  protected
    procedure Paint; override;
    procedure Loaded; override;
    procedure SetParent(Value: TWinControl); override;
    procedure DefineProperties(Filer: TFiler); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer);override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Mask: TBitmap read FMask write SetMask;
    property MaskColor: TColor read GetMaskColor write SetMaskColor;
    property DragCursor;
{$IFDEF VER110}
    property DragKind;
{$ENDIF}
    property DragMode;
    property Hint;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
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


procedure ExtGenerateMask(Bitmap: TBitmap; TransparentColor: TColor;
  RgnData: TVrRgnData);
var
  X, Y: integer;
  Rgn1: HRgn;
  Rgn2: HRgn;
  StartX, EndX: Integer;
  OldCursor: TCursor;
begin
  Rgn1 := 0;
  OldCursor := Screen.Cursor;
  Screen.Cursor := crHourGlass;
  try
    for Y := 0 to Bitmap.Height - 1 do
    begin
      X := 0;
      repeat
        while (Bitmap.Canvas.Pixels[X, Y] = TransparentColor) and
          (X < Bitmap.Width - 1) do Inc(X);
        StartX := X;

        Inc(X);
        while (Bitmap.Canvas.Pixels[X, Y] <> TransparentColor) and
         (X < Bitmap.Width - 1) do Inc(X);
        EndX := X;

        if StartX < Bitmap.Width - 1 then
        begin
          if Rgn1 = 0 then
            Rgn1 := CreateRectRgn(StartX + 1, Y, EndX, Y + 1)
          else
          begin
            Rgn2 := CreateRectRgn(StartX + 1, Y, EndX, Y + 1);
            if Rgn2 <> 0 then CombineRgn(Rgn1, Rgn1, Rgn2, RGN_OR);
            DeleteObject(Rgn2);
          end;
        end;
      until X >= Bitmap.Width - 1;
    end;

    if (Rgn1 <> 0) then
    begin
      RgnData.Size := GetRegionData(Rgn1, 0, nil);
      GetRegionData(Rgn1, RgnData.Size, RgnData.Buffer);
      DeleteObject(Rgn1);
    end;

  finally
    Screen.Cursor := OldCursor;
  end;
end;

{ TVrRgnData }

destructor TVrRgnData.Destroy;
begin
  SetSize(0);
  inherited Destroy;
end;

procedure TVrRgnData.SetSize(Value: Integer);
begin
  if FSize <> Value then
  begin
    FSize := Value;
    ReallocMem(FBuffer, Value);
  end;
end;

{ TVrFormShape }

constructor TVrFormShape.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  Align := alClient;
  Color := clOlive;
  ParentColor := false;
  Transparent := True;
  FMask := TBitmap.Create;
  FRgnData := TVrRgnData.Create;
end;

destructor TVrFormShape.Destroy;
begin
  FMask.Free;
  FRgnData.Free;
  if FRgn <> 0 then DeleteObject(FRgn);
  inherited Destroy;
end;

procedure TVrFormShape.SetParent(Value: TWinControl);
begin
  if Value <> nil then
  begin
    if not (Value is TForm) then
      raise Exception.Create('VrFormShape requires a FORM as parent!');
    with TForm(Value) do Borderstyle := bsNone;
  end;
  inherited;
end;

procedure TVrFormShape.Loaded;
begin
  inherited Loaded;
  if not (csDesigning in ComponentState) then
    UpdateRegion;
end;

procedure TVrFormShape.UpdateMask;
begin
  ExtGenerateMask(FMask, Self.Color, FRgnData);
  if not Designing then UpdateRegion;
end;

procedure TVrFormShape.UpdateRegion;
begin
  if FRgn <> 0 then
  begin
    DeleteObject(FRgn);
    FRgn := 0;
  end;
  FRgn := ExtCreateRegion (nil, FRgnData.Size, FRgnData.Buffer^);
  SetWindowRgn(Parent.Handle, FRgn, True);
end;

procedure TVrFormShape.SetMask(Value: TBitmap);
begin
  FMask.Assign(Value);
  if not Loading then UpdateMask;
  UpdateControlCanvas;
end;

function TVrFormShape.GetMaskColor: TColor;
begin
  Result := Self.Color;
end;

procedure TVrFormShape.SetMaskColor(Value: TColor);
begin
  if Self.Color <> Value then
  begin
    Self.Color := Value;
    if not Loading then
    begin
      UpdateMask;
      UpdateControlCanvas;
    end;
  end;
end;

procedure TVrFormShape.Paint;
begin
  if (FMask.Empty) or (Designing) then
    ClearBitmapCanvas;

  BitmapCanvas.Draw(0, 0, FMask);

  if Designing then
    with BitmapCanvas do
    begin
      Pen.Style := psDot;
      Brush.Style := bsClear;
      Rectangle(0, 0, Width, Height);
    end;

  inherited Paint;
end;

procedure TVrFormShape.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
begin
  if Button = mbleft then
  begin
    ReleaseCapture;
    TWinControl(Parent).Perform(WM_SYSCOMMAND, $F012, 0);
  end;
end;

procedure TVrFormShape.WMEraseBkgnd(var Message: TWMEraseBkgnd);
begin
  Message.Result := 1;
end;

procedure TVrFormShape.ReadMask(Reader: TStream);
var
  Size: Integer;
begin
  Reader.Read(Size, Sizeof(Integer));
  if Size <> 0 then
  begin
    FRgnData.Size := Size;
    Reader.Read(FRgnData.Buffer^, Size);
  end;
end;

procedure TVrFormShape.WriteMask(Writer: TStream);
begin
  Writer.Write(FRgnData.Size, Sizeof(Integer));
  if FRgnData.Size <> 0 then
    Writer.Write(FRgnData.Buffer^, FRgnData.Size);
end;

procedure TVrFormShape.DefineProperties(Filer: TFiler);
begin
  inherited DefineProperties(Filer);
  Filer.DefineBinaryProperty('RgnData', ReadMask, WriteMask, True);
end;



end.
