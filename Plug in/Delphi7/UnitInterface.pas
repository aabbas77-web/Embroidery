unit UnitInterface;

interface

uses
  Classes, Controls, Windows, Messages, SysUtils,
  Variants, Graphics, Forms, Dialogs, StdCtrls, Menus;

type
  VLPOINT = record
    x: Double;
    y: Double;
  end;

  TFunc_Redraw = function : Boolean;
  TFunc_DrawLine = function (X1, Y1, X2, Y2: Double): Boolean;
  TFunc_DrawPolyline = function (Ver: VLPOINT; n_ver: Integer; bClosed: Boolean): Boolean;
  TFunc_DrawPolygon = function (Ver: VLPOINT; n_ver: Integer; bFill, bBorder: Boolean; FillColor: COLORREF): Boolean;
  TFunc_DrawCircle = function (X, Y, Rad: Double): Boolean;
  TFunc_DrawArc = function (X, Y, Rad, Angle1, Angle2: Double): Boolean;
  TFunc_DrawEllipse = function (X, Y, Rh, Rv, Angle: Double): Boolean;
  TFunc_DrawText = function (X, Y: Double; szText: LPCTSTR): Boolean;
  TFunc_AddLine = function (X1, Y1, X2, Y2: Double): Integer;
  TFunc_AddCircle = function (X, Y, Rad: Double): Integer;
  TFunc_AddCircle3P = function (X1, Y1, X2, Y2, X3, Y3: Double): Integer;
  TFunc_AddArc = function (X, Y, Rad, Ang1, Ang2: Double): Integer;
  TFunc_AddArc3P = function (X1, Y1, X2, Y2, X3, Y3: Double): Integer;
  TFunc_AddEllipse = function (X, Y, Rh, Rv, Angle: Double): Integer;
  TFunc_AddArcEx = function (X, Y, Rh, Rv, Ang0, AngArc, AngRot: Double): Integer;
  TFunc_SetTextParam = function (Mode: Integer; Var_: Double): Boolean;
  TFunc_SetTextParams = function (Align: Integer; Height, Angle, ScaleW, Oblique, HInter, VInter: Double): Boolean;
  TFunc_AddText = function (X, Y: Double; szStr: LPCTSTR): Integer;
  TFunc_PolylineBegin = function (): Boolean;
  TFunc_Vertex = function (X, Y: Double): Boolean;
  TFunc_VertexR = function (X, Y, Radius: Double): Boolean;
  TFunc_VertexF = function (X, Y: Double; bOnCurve: Boolean): Boolean;
  TFunc_VertexB = function (X, Y, Bulge: Double): Boolean;
  TFunc_AddPolyline = function (SmoothType: Integer; bClosed: Boolean): Integer;
  TFunc_AddRect = function (X, Y, W, H, Ang, Rad: Double): Integer;

const
  VM_CMD_CREATE = 51;
  VM_CMD_OPEN   = 52;
  VM_CMD_CLOSE  = 53;
  VM_CMD_CLICK  = 54;
  VM_CMD_DRAG   = 55;
  VM_CMD_REDRAW = 56;

type
  TFormInterface = class(TForm)
    ButtonAbout: TButton;
    Button1: TButton;
    Button2: TButton;
    procedure ButtonAboutClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FormInterface: TFormInterface;

  FirstX,
  FirstY,
  SecondX,
  SecondY: Double; 

//__Procedures_In_From_Another_DLL_
  func_Redraw:        TFunc_Redraw;
  func_DrawLine:      TFunc_DrawLine;
  func_DrawPolyline:  TFunc_DrawPolyline;
  func_DrawPolygon:   TFunc_DrawPolygon;
  func_DrawCircle:    TFunc_DrawCircle;
  func_DrawArc:       TFunc_DrawArc;
  func_DrawEllipse:   TFunc_DrawEllipse;
  func_DrawText:      TFunc_DrawText;
  func_AddLine:       TFunc_AddLine;
  func_AddCircle:     TFunc_AddCircle;
  func_AddCircle3P:   TFunc_AddCircle3P;
  func_AddArc:        TFunc_AddArc;
  func_AddArc3P:      TFunc_AddArc3P;
  func_AddEllipse:    TFunc_AddEllipse;
  func_AddArcEx:      TFunc_AddArcEx;
  func_SetTextParam:  TFunc_SetTextParam;
  func_SetTextParams: TFunc_SetTextParams;
  func_AddText:       TFunc_AddText;
  func_PolylineBegin: TFunc_PolylineBegin;
  func_Vertex:        TFunc_Vertex;
  func_VertexR:       TFunc_VertexR;
  func_VertexF:       TFunc_VertexF;
  func_VertexB:       TFunc_VertexB;
  func_AddPolyline:   TFunc_AddPolyline;
  func_AddRect:       TFunc_AddRect;
//__Regular_Procedures_
  procedure _plug_CreateInterface();
  procedure _plug_DestroyInterface();
//__Procedures_Out_From_This_DLL_
  function _plug_ShowModalInterface(): Integer;
  procedure _plug_ShowInterface();
  procedure _plug_CloseInterface();
  procedure _plug_GetIcon(pIcon: TBitmap);
  procedure _plug_About();
  function _plug_GetName(): PChar;
  function _plug_GetHint(): PChar;
  function _plug_GetVersion(): PChar;
  function _plug_GetAuthorName(): PChar;
  function _plug_GetDate(): PChar;
  function _plug_GetGroup(): PChar;
  function _plug_GetShortCut(): TShortCut;
  procedure _plug_Initialize(f_Redraw:        TFunc_Redraw;
                             f_DrawLine:      TFunc_DrawLine;
                             f_DrawPolyline:  TFunc_DrawPolyline;
                             f_DrawPolygon:   TFunc_DrawPolygon;
                             f_DrawCircle:    TFunc_DrawCircle;
                             f_DrawArc:       TFunc_DrawArc;
                             f_DrawEllipse:   TFunc_DrawEllipse;
                             f_DrawText:      TFunc_DrawText;
                             f_AddLine:       TFunc_AddLine;
                             f_AddCircle:     TFunc_AddCircle;
                             f_AddCircle3P:   TFunc_AddCircle3P;
                             f_AddArc:        TFunc_AddArc;
                             f_AddArc3P:      TFunc_AddArc3P;
                             f_AddEllipse:    TFunc_AddEllipse;
                             f_AddArcEx:      TFunc_AddArcEx;
                             f_SetTextParam:  TFunc_SetTextParam;
                             f_SetTextParams: TFunc_SetTextParams;
                             f_AddText:       TFunc_AddText;
                             f_PolylineBegin: TFunc_PolylineBegin;
                             f_Vertex:        TFunc_Vertex;
                             f_VertexR:       TFunc_VertexR;
                             f_VertexF:       TFunc_VertexF;
                             f_VertexB:       TFunc_VertexB;
                             f_AddPolyline:   TFunc_AddPolyline;
                             f_AddRect:       TFunc_AddRect);
  function _plug_Draw(Msg, Step: Integer; X, Y: Double): Integer;

implementation

uses About;

{$R *.dfm}

//---------------------------------------------------------------------------
//-----------------------None Exported functions-----------------------------
//---------------------------------------------------------------------------
procedure _plug_CreateInterface();
begin
	FormInterface:= TFormInterface.Create(Application);
end;
//---------------------------------------------------------------------------
procedure _plug_DestroyInterface();
begin
	if FormInterface <> nil then
  begin
  	FormInterface.Close();
   	FormInterface.Free;
    FormInterface:= nil;
  end;
end;
//---------------------------------------------------------------------------
//-----------------------Exported functions----------------------------------
//---------------------------------------------------------------------------
function _plug_ShowModalInterface(): Integer;
begin
	if FormInterface <> nil then
    Result:= FormInterface.ShowModal()
  else
    Result:= mrOk;
end;
//---------------------------------------------------------------------------
procedure _plug_ShowInterface();
begin
	if FormInterface <> nil then
  	FormInterface.Show();
end;
//---------------------------------------------------------------------------
procedure _plug_CloseInterface();
begin
	if FormInterface <> nil then
  	FormInterface.Close();
end;
//---------------------------------------------------------------------------
procedure _plug_GetIcon(pIcon: TBitmap);
begin
	if FormInterface <> nil then
	begin
	  pIcon.Width:= 16;
  	pIcon.Height:= 16;
    pIcon.Canvas.Brush.Style:= bsSolid;
    pIcon.Canvas.Brush.Color:= clWhite;
    pIcon.Canvas.FillRect(Rect(0, 0, pIcon.Width, pIcon.Height));
    pIcon.TransparentColor:= clWhite;
    pIcon.Transparent:= true;
    pIcon.Canvas.Draw(0, 0, FormInterface.Icon);
  end;
end;
//---------------------------------------------------------------------------
procedure _plug_About();
begin
	FormAbout:= TFormAbout.Create(Application);
	FormAbout.ShowModal();
  if FormAbout <> nil then
  begin
    FormAbout.Free;
    FormAbout:= nil;
  end;
end;
//---------------------------------------------------------------------------
function _plug_GetName(): PChar;
begin
	Result:= 'PolyArc';
end;
//---------------------------------------------------------------------------
function _plug_GetHint(): PChar;
begin
	Result:= 'PolyArc Drawing Tool';
end;
//---------------------------------------------------------------------------
function _plug_GetVersion(): PChar;
begin
	Result:= '1.0';
end;
//---------------------------------------------------------------------------
function _plug_GetAuthorName(): PChar;
begin
	Result:= 'Feras Al-Hayek';
end;
//---------------------------------------------------------------------------
function _plug_GetDate(): PChar;
begin
	Result:= '01/06/2004';
end;
//---------------------------------------------------------------------------
function _plug_GetGroup(): PChar;
begin
	Result:= 'Standard';
end;
//---------------------------------------------------------------------------
function _plug_GetShortCut(): TShortCut;
begin
	Result:= ShortCut(Ord('A'), [ssCtrl] + [ssShift]);
end;
//---------------------------------------------------------------------------
procedure _plug_Initialize(f_Redraw:        TFunc_Redraw;
                           f_DrawLine:      TFunc_DrawLine;
                           f_DrawPolyline:  TFunc_DrawPolyline;
                           f_DrawPolygon:   TFunc_DrawPolygon;
                           f_DrawCircle:    TFunc_DrawCircle;
                           f_DrawArc:       TFunc_DrawArc;
                           f_DrawEllipse:   TFunc_DrawEllipse;
                           f_DrawText:      TFunc_DrawText;
                           f_AddLine:       TFunc_AddLine;
                           f_AddCircle:     TFunc_AddCircle;
                           f_AddCircle3P:   TFunc_AddCircle3P;
                           f_AddArc:        TFunc_AddArc;
                           f_AddArc3P:      TFunc_AddArc3P;
                           f_AddEllipse:    TFunc_AddEllipse;
                           f_AddArcEx:      TFunc_AddArcEx;
                           f_SetTextParam:  TFunc_SetTextParam;
                           f_SetTextParams: TFunc_SetTextParams;
                           f_AddText:       TFunc_AddText;
                           f_PolylineBegin: TFunc_PolylineBegin;
                           f_Vertex:        TFunc_Vertex;
                           f_VertexR:       TFunc_VertexR;
                           f_VertexF:       TFunc_VertexF;
                           f_VertexB:       TFunc_VertexB;
                           f_AddPolyline:   TFunc_AddPolyline;
                           f_AddRect:       TFunc_AddRect);
begin
  func_Redraw:=        f_Redraw;
  func_DrawLine:=      f_DrawLine;
  func_DrawPolyline:=  f_DrawPolyline;
  func_DrawPolygon:=   f_DrawPolygon;
  func_DrawCircle:=    f_DrawCircle;
  func_DrawArc:=       f_DrawArc;
  func_DrawEllipse:=   f_DrawEllipse;
  func_DrawText:=      f_DrawText;
  func_AddLine:=       f_AddLine;
  func_AddCircle:=     f_AddCircle;
  func_AddCircle3P:=   f_AddCircle3P;
  func_AddArc:=        f_AddArc;
  func_AddArc3P:=      f_AddArc3P;
  func_AddEllipse:=    f_AddEllipse;
  func_AddArcEx:=      f_AddArcEx;
  func_SetTextParam:=  f_SetTextParam;
  func_SetTextParams:= f_SetTextParams;
  func_AddText:=       f_AddText;
  func_PolylineBegin:= f_PolylineBegin;
  func_Vertex:=        f_Vertex;
  func_VertexR:=       f_VertexR;
  func_VertexF:=       f_VertexF;
  func_VertexB:=       f_VertexB;
  func_AddPolyline:=   f_AddPolyline;
  func_AddRect:=       f_AddRect;
end;
//---------------------------------------------------------------------------
function _plug_Draw(Msg, Step: Integer; X, Y: Double): Integer;
begin
  case Msg of
    VM_CMD_CREATE :
      begin
        func_Redraw();
        Result:= 0;
        Exit;
      end;
    VM_CMD_OPEN :
      begin
        Result:= 3;
        Exit;
      end;
    VM_CMD_CLICK :
      begin
        case Step of
          3 :
            begin
              FirstX:= x;
              FirstY:= y;
              Result:= 2;
              Exit;
            end;
          2 :
            begin
              SecondX:= x;
              SecondY:= y;
              //func_DrawArc3P(FirstX, FirstY, ?, ?, SecondX, SecondY);
              //func_DrawLine(FirstX, FirstY, ?, ?);
              //func_DrawLine(?, ?, SecondX, SecondY);
              Result:= 1;
              Exit;
            end;
          1 :
            begin
              func_AddArc3P(FirstX, FirstY, x, y, SecondX, SecondY);
              FirstX:= SecondX;
              FirstY:= SecondY;
              Result:= 2;
              Exit;
            end;
        end;
        Result:= 0;
        Exit;
      end;
    VM_CMD_DRAG :
      begin
        if Step = 1 then
        begin
          //func_DrawArc3P(FirstX, FirstY, x, y, SecondX, SecondY);
          func_DrawLine(FirstX, FirstY, x, y);
          func_DrawLine(x, y, SecondX, SecondY);
        end;
        Result:= 0;
        Exit;
      end;
    VM_CMD_CLOSE :
      begin
        func_Redraw();
        Result:= 0;
        Exit;
      end;
    VM_CMD_REDRAW :
      begin
        Result:= 0;
        Exit;
      end;
  end;
  Result:= 0;
end;
//---------------------------------------------------------------------------
//-------------------Interface methods---------------------------------------
//---------------------------------------------------------------------------
procedure TFormInterface.ButtonAboutClick(Sender: TObject);
begin
  _plug_About();
end;
//---------------------------------------------------------------------------

end.
