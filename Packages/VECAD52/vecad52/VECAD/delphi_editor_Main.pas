unit delphi_editor_Main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  OleCtnrs, StdCtrls, ExtCtrls, ComCtrls, Menus, Printers;

type
  TForm1 = class(TForm)
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    View1: TMenuItem;
    Draw1: TMenuItem;
    Edit1: TMenuItem;
    New1: TMenuItem;
    Open1: TMenuItem;
    Save1: TMenuItem;
    SaveAs1: TMenuItem;
    Properties1: TMenuItem;
    Print1: TMenuItem;
    N2: TMenuItem;
    Exit1: TMenuItem;
    ZoomAll1: TMenuItem;
    ZoomWindow1: TMenuItem;
    ZoomIn1: TMenuItem;
    ZoomOut1: TMenuItem;
    ZoomPage2: TMenuItem;
    Line1: TMenuItem;
    Polyline1: TMenuItem;
    Ellipse1: TMenuItem;
    Text1: TMenuItem;
    InsertBlock1: TMenuItem;
    InsertImage1: TMenuItem;
    Copy1: TMenuItem;
    Move1: TMenuItem;
    Rotate1: TMenuItem;
    Scale1: TMenuItem;
    Mirror1: TMenuItem;
    Erase1: TMenuItem;
    Group1: TMenuItem;
    ObjectsProperties1: TMenuItem;
    N3: TMenuItem;
    Bevel1: TBevel;
    N4: TMenuItem;
    N5: TMenuItem;
    SelectPage1: TMenuItem;
    Dimension1: TMenuItem;
    Horizontal1: TMenuItem;
    Vertical1: TMenuItem;
    Parallel1: TMenuItem;
    Angular1: TMenuItem;
    Radius1: TMenuItem;
    Diameter1: TMenuItem;
    Ordinate1: TMenuItem;
    Circle1: TMenuItem;
    centerradius1: TMenuItem;
    N3point1: TMenuItem;
    Arc1: TMenuItem;
    ArcCSE: TMenuItem;
    ArcSEM: TMenuItem;
    N7: TMenuItem;
    Importfrom1: TMenuItem;
    AutoCADDXF1: TMenuItem;
    Exportto1: TMenuItem;
    AutoCADDXF2: TMenuItem;
    HPGL1: TMenuItem;
    RasterImage1: TMenuItem;
    Symbol1: TMenuItem;
    Rectangle1: TMenuItem;
    Tools1: TMenuItem;
    PrintRectangles1: TMenuItem;
    N8: TMenuItem;
    CloseAll1: TMenuItem;
    List1: TMenuItem;
    Undo2: TMenuItem;
    Redo2: TMenuItem;
    N9: TMenuItem;
    N10: TMenuItem;
    Cut1: TMenuItem;
    Copy2: TMenuItem;
    Paste1: TMenuItem;
    Explode1: TMenuItem;
    N6: TMenuItem;
    N11: TMenuItem;
    N12: TMenuItem;
    PageFirst1: TMenuItem;
    PageLasttEnd1: TMenuItem;
    PageNext1: TMenuItem;
    PagePrevious1: TMenuItem;
    N13: TMenuItem;
    SavecurrentView1: TMenuItem;
    ViewsList1: TMenuItem;
    Format1: TMenuItem;
    Page1: TMenuItem;
    Layer1: TMenuItem;
    Linetype1: TMenuItem;
    TextStyle1: TMenuItem;
    PointStyle1: TMenuItem;
    HatchStyle1: TMenuItem;
    Blocks1: TMenuItem;
    N14: TMenuItem;
    DimensionStyle1: TMenuItem;
    N15: TMenuItem;
    Grid1: TMenuItem;
    ObjectSnap1: TMenuItem;
    AngleSnap1: TMenuItem;
    N16: TMenuItem;
    Units1: TMenuItem;
    Private1: TMenuItem;
    Preferences1: TMenuItem;
    Point1: TMenuItem;
    Spline1: TMenuItem;
    CenterDiameter1: TMenuItem;
    N2Points1: TMenuItem;
    ArcSME: TMenuItem;
    Hatch1: TMenuItem;
    N17: TMenuItem;
    DistanceArea1: TMenuItem;
    Statistics1: TMenuItem;
    Help1: TMenuItem;
    About1: TMenuItem;
    Test1: TMenuItem;
    Sinus1: TMenuItem;
    procedure FormCreate(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure New1Click(Sender: TObject);
    procedure Open1Click(Sender: TObject);
    procedure Save1Click(Sender: TObject);
    procedure SaveAs1Click(Sender: TObject);
    procedure Properties1Click(Sender: TObject);
    procedure CloseAll1Click(Sender: TObject);
    procedure List1Click(Sender: TObject);
    procedure AutoCADDXF1Click(Sender: TObject);
    procedure AutoCADDXF2Click(Sender: TObject);
    procedure HPGL1Click(Sender: TObject);
    procedure RasterImage1Click(Sender: TObject);
    procedure Print1Click(Sender: TObject);
    procedure Exit1Click(Sender: TObject);
    procedure Undo2Click(Sender: TObject);
    procedure Cut1Click(Sender: TObject);
    procedure Copy2Click(Sender: TObject);
    procedure Paste1Click(Sender: TObject);
    procedure Redo2Click(Sender: TObject);
    procedure ObjectsProperties1Click(Sender: TObject);
    procedure Copy1Click(Sender: TObject);
    procedure Move1Click(Sender: TObject);
    procedure Rotate1Click(Sender: TObject);
    procedure Scale1Click(Sender: TObject);
    procedure Mirror1Click(Sender: TObject);
    procedure Explode1Click(Sender: TObject);
    procedure Group1Click(Sender: TObject);
    procedure Erase1Click(Sender: TObject);
    procedure ZoomAll1Click(Sender: TObject);
    procedure ZoomWindow1Click(Sender: TObject);
    procedure ZoomPage2Click(Sender: TObject);
    procedure ZoomIn1Click(Sender: TObject);
    procedure ZoomOut1Click(Sender: TObject);
    procedure ViewsList1Click(Sender: TObject);
    procedure PageFirst1Click(Sender: TObject);
    procedure PageLasttEnd1Click(Sender: TObject);
    procedure PageNext1Click(Sender: TObject);
    procedure PagePrevious1Click(Sender: TObject);
    procedure SelectPage1Click(Sender: TObject);
    procedure SavecurrentView1Click(Sender: TObject);
    procedure Page1Click(Sender: TObject);
    procedure Layer1Click(Sender: TObject);
    procedure Linetype1Click(Sender: TObject);
    procedure TextStyle1Click(Sender: TObject);
    procedure PointStyle1Click(Sender: TObject);
    procedure HatchStyle1Click(Sender: TObject);
    procedure Blocks1Click(Sender: TObject);
    procedure DimensionStyle1Click(Sender: TObject);
    procedure Grid1Click(Sender: TObject);
    procedure ObjectSnap1Click(Sender: TObject);
    procedure AngleSnap1Click(Sender: TObject);
    procedure Units1Click(Sender: TObject);
    procedure Private1Click(Sender: TObject);
    procedure Preferences1Click(Sender: TObject);
    procedure Point1Click(Sender: TObject);
    procedure Line1Click(Sender: TObject);
    procedure Polyline1Click(Sender: TObject);
    procedure Spline1Click(Sender: TObject);
    procedure centerradius1Click(Sender: TObject);
    procedure CenterDiameter1Click(Sender: TObject);
    procedure N2Points1Click(Sender: TObject);
    procedure N3point1Click(Sender: TObject);
    procedure ArcCSEClick(Sender: TObject);
    procedure ArcSEMClick(Sender: TObject);
    procedure ArcSMEClick(Sender: TObject);
    procedure Ellipse1Click(Sender: TObject);
    procedure Rectangle1Click(Sender: TObject);
    procedure Hatch1Click(Sender: TObject);
    procedure Horizontal1Click(Sender: TObject);
    procedure Vertical1Click(Sender: TObject);
    procedure Parallel1Click(Sender: TObject);
    procedure Angular1Click(Sender: TObject);
    procedure Radius1Click(Sender: TObject);
    procedure Diameter1Click(Sender: TObject);
    procedure Ordinate1Click(Sender: TObject);
    procedure Text1Click(Sender: TObject);
    procedure Symbol1Click(Sender: TObject);
    procedure InsertBlock1Click(Sender: TObject);
    procedure InsertImage1Click(Sender: TObject);
    procedure DistanceArea1Click(Sender: TObject);
    procedure PrintRectangles1Click(Sender: TObject);
    procedure Statistics1Click(Sender: TObject);
    procedure Test1Click(Sender: TObject);
    procedure Sinus1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses api_VecApi, delphi_editor_DwgProc, delphi_editor_Funcs;

{$R *.DFM}


procedure TForm1.FormCreate(Sender: TObject);
begin
  CreateVecWindow( Handle )
end;

procedure TForm1.FormResize(Sender: TObject);
begin
  ResizeVecWindow( Handle )
end;


procedure TForm1.New1Click(Sender: TObject);
begin
  FileNew();
end;

procedure TForm1.Open1Click(Sender: TObject);
begin
  FileOpen();
end;

procedure TForm1.Save1Click(Sender: TObject);
begin
  vlExecute( VC_FILE_SAVE );
end;

procedure TForm1.SaveAs1Click(Sender: TObject);
begin
  vlExecute( VC_FILE_SAVEAS );
end;

procedure TForm1.Properties1Click(Sender: TObject);
begin
  vlExecute( VC_FILE_CLOSE );
end;

procedure TForm1.CloseAll1Click(Sender: TObject);
begin
  vlExecute( VC_FILE_CLOSEALL );
end;

procedure TForm1.List1Click(Sender: TObject);
begin
  vlFileList( Handle );
end;

procedure TForm1.AutoCADDXF1Click(Sender: TObject);
begin
  vlExecute( VC_IMPORT_DXF );
end;

procedure TForm1.AutoCADDXF2Click(Sender: TObject);
begin
  vlExecute( VC_EXPORT_DXF );
end;

procedure TForm1.HPGL1Click(Sender: TObject);
begin
  vlExecute( VC_EXPORT_HPGL );
end;

procedure TForm1.RasterImage1Click(Sender: TObject);
begin
  vlExecute( VC_EXPORT_BMP );
end;

procedure TForm1.Print1Click(Sender: TObject);
begin
  vlExecute( VC_PRINT );
end;

procedure TForm1.Exit1Click(Sender: TObject);
begin
  Close
end;

procedure TForm1.Undo2Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_UNDO );
end;

procedure TForm1.Redo2Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_REDO );
end;

procedure TForm1.Cut1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_CBCUT );
end;

procedure TForm1.Copy2Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_CBCOPY );
end;

procedure TForm1.Paste1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_CBPASTE );
end;

procedure TForm1.ObjectsProperties1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_ENTPROP );
end;

procedure TForm1.Copy1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_COPY );
end;

procedure TForm1.Move1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_MOVE );
end;

procedure TForm1.Rotate1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_ROTATE );
end;

procedure TForm1.Scale1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_SCALE );
end;

procedure TForm1.Mirror1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_MIRROR );
end;

procedure TForm1.Explode1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_EXPLODE );
end;

procedure TForm1.Group1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_CREBLOCK );
end;

procedure TForm1.Erase1Click(Sender: TObject);
begin
  vlExecute( VC_EDIT_ERASE );
end;

procedure TForm1.ZoomAll1Click(Sender: TObject);
begin
  vlExecute( VC_ZOOM_ALL );
end;

procedure TForm1.ZoomWindow1Click(Sender: TObject);
begin
  vlExecute( VC_ZOOM_WIN );
end;

procedure TForm1.ZoomPage2Click(Sender: TObject);
begin
  vlExecute( VC_ZOOM_PAGE );
end;

procedure TForm1.ZoomIn1Click(Sender: TObject);
begin
  vlExecute( VC_ZOOM_IN );
end;

procedure TForm1.ZoomOut1Click(Sender: TObject);
begin
  vlExecute( VC_ZOOM_OUT );
end;

procedure TForm1.PageFirst1Click(Sender: TObject);
begin
  vlExecute( VC_PAGE_FIRST );
end;

procedure TForm1.PageLasttEnd1Click(Sender: TObject);
begin
  vlExecute( VC_PAGE_LAST );
end;

procedure TForm1.PageNext1Click(Sender: TObject);
begin
  vlExecute( VC_PAGE_NEXT );
end;

procedure TForm1.PagePrevious1Click(Sender: TObject);
begin
  vlExecute( VC_PAGE_PREV );
end;

procedure TForm1.SelectPage1Click(Sender: TObject);
begin
  vlExecute( VC_PAGE_DLG );
end;

procedure TForm1.SavecurrentView1Click(Sender: TObject);
begin
  vlExecute( VC_VIEW_SAVE );
end;

procedure TForm1.ViewsList1Click(Sender: TObject);
begin
  vlExecute( VC_VIEW_LIST );
end;


procedure TForm1.Page1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_PAGE );
end;

procedure TForm1.Layer1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_LAYER );
end;

procedure TForm1.Linetype1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_STLINE );
end;

procedure TForm1.TextStyle1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_STTEXT );
end;

procedure TForm1.PointStyle1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_STPOINT );
end;

procedure TForm1.HatchStyle1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_STHATCH );
end;

procedure TForm1.Blocks1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_BLOCK );
end;

procedure TForm1.DimensionStyle1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_STDIM );
end;

procedure TForm1.Grid1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_GRID );
end;

procedure TForm1.ObjectSnap1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_OSNAP );
end;

procedure TForm1.AngleSnap1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_PSNAP );
end;

procedure TForm1.Units1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_UNITS );
end;

procedure TForm1.Private1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_PRIVATE );
end;

procedure TForm1.Preferences1Click(Sender: TObject);
begin
  vlExecute( VC_FMT_PREFERS );
end;

procedure TForm1.Point1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_POINT );
end;

procedure TForm1.Line1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_LINE );
end;

procedure TForm1.Polyline1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_POLYLINE );
end;

procedure TForm1.Spline1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_SPLINE );
end;

procedure TForm1.centerradius1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_CIRC_CR );
end;

procedure TForm1.CenterDiameter1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_CIRC_CD );
end;

procedure TForm1.N2Points1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_CIRC_2P );
end;

procedure TForm1.N3point1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_CIRC_3P );
end;

procedure TForm1.ArcCSEClick(Sender: TObject);
begin
  vlExecute( VC_DRAW_ARC_CSE );
end;

procedure TForm1.ArcSEMClick(Sender: TObject);
begin
  vlExecute( VC_DRAW_ARC_SEM );
end;

procedure TForm1.ArcSMEClick(Sender: TObject);
begin
  vlExecute( VC_DRAW_ARC_SME );
end;

procedure TForm1.Ellipse1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_ELLIPSE );
end;

procedure TForm1.Rectangle1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_RECT );
end;

procedure TForm1.Hatch1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_HATCH );
end;

procedure TForm1.Horizontal1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_DIM_HOR );
end;

procedure TForm1.Vertical1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_DIM_VER );
end;

procedure TForm1.Parallel1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_DIM_PAR );
end;

procedure TForm1.Angular1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_DIM_ANG );
end;

procedure TForm1.Radius1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_DIM_RAD );
end;

procedure TForm1.Diameter1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_DIM_DIAM );
end;

procedure TForm1.Ordinate1Click(Sender: TObject);
begin
  vlExecute( VC_DRAW_DIM_ORD );
end;

procedure TForm1.Text1Click(Sender: TObject);
begin
  vlExecute( VC_INS_TEXT );
end;

procedure TForm1.Symbol1Click(Sender: TObject);
begin
  vlExecute( VC_INS_SYMBOL );
end;

procedure TForm1.InsertBlock1Click(Sender: TObject);
begin
  vlExecute( VC_INS_BLOCK );
end;

procedure TForm1.InsertImage1Click(Sender: TObject);
begin
  vlExecute( VC_INS_IMAGE );
end;

procedure TForm1.DistanceArea1Click(Sender: TObject);
begin
  vlExecute( VC_TOOL_DIST );
end;

procedure TForm1.PrintRectangles1Click(Sender: TObject);
begin
  vlExecute( VC_TOOL_PRNRECT );
end;

procedure TForm1.Statistics1Click(Sender: TObject);
begin
  vlExecute( VC_TOOL_STAT );
end;

procedure TForm1.Test1Click(Sender: TObject);
begin
  TestLineStyles();
end;

procedure TForm1.Sinus1Click(Sender: TObject);
var
  x, y, step : Double;
begin
  vlFileNew( ghwVec, '' );
  step := 0.314;
  vlPolylineBegin();
  x :=0;
  repeat
    y := sin( x );
    vlVertex( x, y );
    x := x + step;
  until x>6.3;
  vlAddPolyline( VL_POLY_LINE, false );
  vlUpdate();
  vlZoom( VL_ZOOM_ALL );
end;

end.
