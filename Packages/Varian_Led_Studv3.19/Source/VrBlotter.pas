{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrBlotter;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  VrClasses, VrControls, VrSysUtils;

type
{$IFDEF VER110}
  TCustomVrBlotter = class(TVrCustomControl)
  private
    FAutoSizeDocking: Boolean;
    FBevel: TVrBevel;
    FFullRepaint: Boolean;
    FLocked: Boolean;
    FGlyph: TBitmap;
    procedure SetGlyph(Value: TBitmap);
    procedure BevelChanged(Sender: TObject);
    procedure GlyphChanged(Sender: TObject);
    procedure CMIsToolControl(var Message: TMessage); message CM_ISTOOLCONTROL;
    procedure WMWindowPosChanged(var Message: TWMWindowPosChanged); message WM_WINDOWPOSCHANGED;
    procedure CMDockClient(var Message: TCMDockClient); message CM_DOCKCLIENT;
  protected
    procedure CreateParams(var Params: TCreateParams); override;
    function CanAutoSize(var NewWidth, NewHeight: Integer): Boolean; override;
    procedure AdjustClientRect(var Rect: TRect); override;
    procedure Paint; override;
    property Bevel: TVrBevel read FBevel write FBevel;
    property Color default clBlack;
    property FullRepaint: Boolean read FFullRepaint write FFullRepaint default True;
    property Locked: Boolean read FLocked write FLocked default False;
    property ParentColor default False;
    property Glyph: TBitmap read FGlyph write SetGlyph;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

  TVrBlotter = class(TCustomVrBlotter)
  public
    property DockManager;
  published
    property Align;
    property Anchors;
    property AutoSize;
    property Bevel;
    property Glyph;
    property Color;
    property Constraints;
    property Ctl3D;
    property UseDockManager default True;
    property DockSite;
    property DragCursor;
    property DragKind;
    property DragMode;
    property Enabled;
    property FullRepaint;
    property Locked;
    property ParentColor;
    property ParentCtl3D;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnCanResize;
    property OnClick;
    property OnConstrainedResize;
{$IFDEF VER130}
    property OnContextPopup;
{$ENDIF}
    property OnDockDrop;
    property OnDockOver;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnEndDock;
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnGetSiteInfo;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnResize;
    property OnStartDock;
    property OnStartDrag;
    property OnUnDock;
  end;

{$ELSE}

  TCustomVrBlotter = class(TVrCustomControl)
  private
    FBevel: TVrBevel;
    FFullRepaint: Boolean;
    FLocked: Boolean;
    FGlyph: TBitmap;
    FOnResize: TNotifyEvent;
    procedure SetGlyph(Value: TBitmap);
    procedure GlyphChanged(Sender: TObject);
    procedure BevelChanged(Sender: TObject);
    procedure CMIsToolControl(var Message: TMessage); message CM_ISTOOLCONTROL;
    procedure WMWindowPosChanged(var Message: TWMWindowPosChanged); message WM_WINDOWPOSCHANGED;
  protected
    procedure CreateParams(var Params: TCreateParams); override;
    procedure AlignControls(AControl: TControl; var Rect: TRect); override;
    procedure Paint; override;
    procedure Resize; dynamic;
    property Color default clBlack;
    property FullRepaint: Boolean read FFullRepaint write FFullRepaint default True;
    property Locked: Boolean read FLocked write FLocked default False;
    property Bevel: TVrBevel read FBevel write FBevel;
    property ParentColor default False;
    property Glyph: TBitmap read FGlyph write SetGlyph;
    property OnResize: TNotifyEvent read FOnResize write FOnResize;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

  TVrBlotter = class(TCustomVrBlotter)
  published
    property Align;
    property Bevel;
    property Glyph;
    property DragCursor;
    property DragMode;
    property Enabled;
    property FullRepaint;
    property Color;
    property Font;
    property Locked;
    property ParentColor;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnClick;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnResize;
    property OnStartDrag;
  end;

{$ENDIF}

implementation


{ TCustomVrBlotter }

{$IFDEF VER110}
constructor TCustomVrBlotter.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := [csAcceptsControls, csCaptureMouse, csClickEvents,
    csOpaque, csDoubleClicks, csReplicatable] - [csSetCaption];
  Width := 185;
  Height := 75;
  Color := clBlack;
  UseDockManager := True;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerShadow := clGreen;
    InnerHighlight := clLime;
    InnerColor := clBlack;
    OuterShadow := clGreen;
    OuterHighlight := clLime;
    OnChange := BevelChanged;
  end;
  FGlyph := TBitmap.Create;
  FGlyph.OnChange := GlyphChanged;
  FFullRepaint := True;
end;

destructor TCustomVrBlotter.Destroy;
begin
  FBevel.Free;
  FGlyph.Free;
  inherited Destroy;
end;

procedure TCustomVrBlotter.CreateParams(var Params: TCreateParams);
begin
  inherited CreateParams(Params);
  with Params do
    WindowClass.style := WindowClass.style and not (CS_HREDRAW or CS_VREDRAW);
end;

procedure TCustomVrBlotter.CMIsToolControl(var Message: TMessage);
begin
  if not FLocked then Message.Result := 1;
end;

procedure TCustomVrBlotter.SetGlyph(Value: TBitmap);
begin
  FGlyph.Assign(Value);
end;

procedure TCustomVrBlotter.GlyphChanged(Sender: TObject);
begin
  Invalidate;
end;

procedure TCustomVrBlotter.BevelChanged(Sender: TObject);
begin
  Realign;
  Invalidate;
end;

procedure TCustomVrBlotter.WMWindowPosChanged(var Message: TWMWindowPosChanged);
var
  BevelPixels: Integer;
  Rect: TRect;
begin
  if FullRepaint then
    Invalidate
  else
  begin
    BevelPixels := 0;
    if Bevel.InnerOutline <> osNone then Inc(BevelPixels);
    if Bevel.OuterOutline <> osNone then Inc(BevelPixels);

    Inc(BevelPixels, Bevel.InnerSpace);
    Inc(BevelPixels, Bevel.OuterSpace);

    if Bevel.InnerStyle <> bsNone then Inc(BevelPixels, Bevel.InnerWidth);
    if Bevel.OuterStyle <> bsNone then Inc(BevelPixels, Bevel.OuterWidth);

    if BevelPixels > 0 then
    begin
      Rect.Right := Width;
      Rect.Bottom := Height;
      if Message.WindowPos^.cx <> Rect.Right then
      begin
        Rect.Top := 0;
        Rect.Left := Rect.Right - BevelPixels - 1;
        InvalidateRect(Handle, @Rect, True);
      end;
      if Message.WindowPos^.cy <> Rect.Bottom then
      begin
        Rect.Left := 0;
        Rect.Top := Rect.Bottom - BevelPixels - 1;
        InvalidateRect(Handle, @Rect, True);
      end;
    end;
  end;
  inherited;
  if not Loading then Resize;
end;

procedure TCustomVrBlotter.AdjustClientRect(var Rect: TRect);
begin
  inherited AdjustClientRect(Rect);
  Bevel.GetVisibleArea(Rect);
end;

procedure TCustomVrBlotter.Paint;
var
  Rect: TRect;
begin
  Rect := GetClientRect;
  if FGlyph.Empty then
  begin
    with Canvas do
    begin
      Brush.Color := Color;
      FillRect(Rect);
    end;
  end else DrawTiledBitmap(Canvas, Rect, FGlyph);
  FBevel.Paint(Canvas, Rect);
end;

procedure TCustomVrBlotter.CMDockClient(var Message: TCMDockClient);
var
  R: TRect;
  Dim: Integer;
begin
  if AutoSize then
  begin
    FAutoSizeDocking := True;
    try
      R := Message.DockSource.DockRect;
      case Align of
        alLeft: if Width = 0 then Width := R.Right - R.Left;
        alRight: if Width = 0 then
          begin
            Dim := R.Right - R.Left;
            SetBounds(Left - Dim, Top, Dim, Height);
          end;
        alTop: if Height = 0 then Height := R.Bottom - R.Top;
        alBottom: if Height = 0 then
          begin
            Dim := R.Bottom - R.Top;
            SetBounds(Left, Top - Dim, Width, Dim);
          end;
      end;
      inherited;
      Exit;
    finally
      FAutoSizeDocking := False;
    end;
  end;
  inherited;
end;

function TCustomVrBlotter.CanAutoSize(var NewWidth, NewHeight: Integer): Boolean;
begin
  Result := (not FAutoSizeDocking) and inherited CanAutoSize(NewWidth, NewHeight);
end;

{$ELSE}

constructor TCustomVrBlotter.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := [csAcceptsControls, csCaptureMouse, csClickEvents,
    csOpaque, csDoubleClicks, csReplicatable] - [csSetCaption];
  Width := 185;
  Height := 75;
  Color := clBlack;
  FBevel := TVrBevel.Create;
  with FBevel do
  begin
    InnerShadow := clGreen;
    InnerHighlight := clLime;
    InnerColor := clBlack;
    OuterShadow := clGreen;
    OuterHighlight := clLime;
    OnChange := BevelChanged;
  end;
  FGlyph := TBitmap.Create;
  FGlyph.OnChange := GlyphChanged;
  FFullRepaint := True;
end;

destructor TCustomVrBlotter.Destroy;
begin
  FBevel.Free;
  FGlyph.Free;
  inherited Destroy;
end;

procedure TCustomVrBlotter.CreateParams(var Params: TCreateParams);
begin
  inherited CreateParams(Params);
  with Params do
    WindowClass.style := WindowClass.style and not (CS_HREDRAW or CS_VREDRAW);
end;

procedure TCustomVrBlotter.CMIsToolControl(var Message: TMessage);
begin
  if not FLocked then Message.Result := 1;
end;

procedure TCustomVrBlotter.SetGlyph(Value: TBitmap);
begin
  FGlyph.Assign(Value);
end;

procedure TCustomVrBlotter.GlyphChanged(Sender: TObject);
begin
  Invalidate;
end;

procedure TCustomVrBlotter.BevelChanged(Sender: TObject);
begin
  Realign;
  Invalidate;
end;

procedure TCustomVrBlotter.Resize;
begin
  if Assigned(FOnResize) then FOnResize(Self);
end;

procedure TCustomVrBlotter.WMWindowPosChanged(var Message: TWMWindowPosChanged);
var
  BevelPixels: Integer;
  Rect: TRect;
begin
  if FullRepaint then
    Invalidate
  else
  begin
    BevelPixels := 0;
    if Bevel.InnerOutline <> osNone then Inc(BevelPixels);
    if Bevel.OuterOutline <> osNone then Inc(BevelPixels);

    Inc(BevelPixels, Bevel.InnerSpace);
    Inc(BevelPixels, Bevel.OuterSpace);

    if Bevel.InnerStyle <> bsNone then Inc(BevelPixels, Bevel.InnerWidth);
    if Bevel.OuterStyle <> bsNone then Inc(BevelPixels, Bevel.OuterWidth);

    if BevelPixels > 0 then
    begin
      Rect.Right := Width;
      Rect.Bottom := Height;
      if Message.WindowPos^.cx <> Rect.Right then
      begin
        Rect.Top := 0;
        Rect.Left := Rect.Right - BevelPixels - 1;
        InvalidateRect(Handle, @Rect, True);
      end;
      if Message.WindowPos^.cy <> Rect.Bottom then
      begin
        Rect.Left := 0;
        Rect.Top := Rect.Bottom - BevelPixels - 1;
        InvalidateRect(Handle, @Rect, True);
      end;
    end;
  end;
  inherited;
  if not Loading then Resize;
end;

procedure TCustomVrBlotter.AlignControls(AControl: TControl; var Rect: TRect);
begin
  FBevel.GetVisibleArea(Rect);
  inherited AlignControls(AControl, Rect);
end;

procedure TCustomVrBlotter.Paint;
var
  Rect: TRect;
begin
  Rect := GetClientRect;
  if FGlyph.Empty then
  begin
    with Canvas do
    begin
      Brush.Color := Color;
      FillRect(Rect);
    end;
  end else DrawTiledBitmap(Canvas, Rect, FGlyph);
  FBevel.Paint(Canvas, Rect);
end;

{$ENDIF}



end.
