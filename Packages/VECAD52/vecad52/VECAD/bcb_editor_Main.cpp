//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "api_VecApi.h"
#include "bcb_editor_Main.h"
#include "bcb_editor_Funcs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  CreateVecWindow( Handle );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
  ResizeVecWindow( Handle );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  UnloadVecadDll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuItem1Click(TObject *Sender)
{
  FileNew();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{
  FileOpen();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
  vlExecute( VC_FILE_SAVE );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveAs1Click(TObject *Sender)
{
  vlExecute( VC_FILE_SAVEAS );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Properties1Click(TObject *Sender)
{
  vlExecute( VC_FILE_CLOSE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CloseAll1Click(TObject *Sender)
{
  vlExecute( VC_FILE_CLOSEALL );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::List1Click(TObject *Sender)
{
  vlFileList( Handle );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AutoCADDXF1Click(TObject *Sender)
{
  vlExecute( VC_IMPORT_DXF );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AutoCADDXF2Click(TObject *Sender)
{
  vlExecute( VC_EXPORT_DXF );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HPGL1Click(TObject *Sender)
{
  vlExecute( VC_EXPORT_HPGL );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RasterImage1Click(TObject *Sender)
{
  vlExecute( VC_EXPORT_BMP );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Print1Click(TObject *Sender)
{
  vlExecute( VC_PRINT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
  Close();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Undo2Click(TObject *Sender)
{
  vlExecute( VC_EDIT_UNDO );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Redo2Click(TObject *Sender)
{
  vlExecute( VC_EDIT_REDO );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Cut1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_CBCUT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy2Click(TObject *Sender)
{
  vlExecute( VC_EDIT_CBCOPY );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Paste1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_CBPASTE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ObjectsProperties1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_ENTPROP );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_COPY );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Move1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_MOVE );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Rotate1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_ROTATE );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Scale1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_SCALE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Mirror1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_MIRROR );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Explode1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_EXPLODE );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Group1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_CREBLOCK );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Erase1Click(TObject *Sender)
{
  vlExecute( VC_EDIT_ERASE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZoomAll1Click(TObject *Sender)
{
  vlExecute( VC_ZOOM_ALL );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZoomWindow1Click(TObject *Sender)
{
  vlExecute( VC_ZOOM_WIN );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZoomPage2Click(TObject *Sender)
{
  vlExecute( VC_ZOOM_PAGE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZoomIn1Click(TObject *Sender)
{
  vlExecute( VC_ZOOM_IN );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZoomOut1Click(TObject *Sender)
{
  vlExecute( VC_ZOOM_OUT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PageFirst1Click(TObject *Sender)
{
  vlExecute( VC_PAGE_FIRST );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PageLasttEnd1Click(TObject *Sender)
{
  vlExecute( VC_PAGE_LAST );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PageNext1Click(TObject *Sender)
{
  vlExecute( VC_PAGE_NEXT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PagePrevious1Click(TObject *Sender)
{
  vlExecute( VC_PAGE_PREV );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SelectPage1Click(TObject *Sender)
{
  vlExecute( VC_PAGE_DLG );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SavecurrentView1Click(TObject *Sender)
{
  vlExecute( VC_VIEW_SAVE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ViewsList1Click(TObject *Sender)
{
  vlExecute( VC_VIEW_LIST );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Page1Click(TObject *Sender)
{
  vlExecute( VC_FMT_PAGE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Layer1Click(TObject *Sender)
{
  vlExecute( VC_FMT_LAYER );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Linetype1Click(TObject *Sender)
{
  vlExecute( VC_FMT_STLINE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TextStyle1Click(TObject *Sender)
{
  vlExecute( VC_FMT_STTEXT );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PointStyle1Click(TObject *Sender)
{
  vlExecute( VC_FMT_STPOINT );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HatchStyle1Click(TObject *Sender)
{
  vlExecute( VC_FMT_STHATCH );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Blocks1Click(TObject *Sender)
{
  vlExecute( VC_FMT_BLOCK );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DimensionStyle1Click(TObject *Sender)
{
  vlExecute( VC_FMT_STDIM );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Grid1Click(TObject *Sender)
{
  vlExecute( VC_FMT_GRID );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ObjectSnap1Click(TObject *Sender)
{
  vlExecute( VC_FMT_OSNAP );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AngleSnap1Click(TObject *Sender)
{
  vlExecute( VC_FMT_PSNAP );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Units1Click(TObject *Sender)
{
  vlExecute( VC_FMT_UNITS );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Private1Click(TObject *Sender)
{
  vlExecute( VC_FMT_PRIVATE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Preferences1Click(TObject *Sender)
{
  vlExecute( VC_FMT_PREFERS );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Point1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_POINT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Line1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_LINE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Polyline1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_POLYLINE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Spline1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_SPLINE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::centerradius1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_CIRC_CR );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CenterDiameter1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_CIRC_CD );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Points1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_CIRC_2P );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3point1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_CIRC_3P );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ArcCSEClick(TObject *Sender)
{
  vlExecute( VC_DRAW_ARC_CSE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ArcSEMClick(TObject *Sender)
{
  vlExecute( VC_DRAW_ARC_SEM );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ArcSMEClick(TObject *Sender)
{
  vlExecute( VC_DRAW_ARC_SME );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Ellipse1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_ELLIPSE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Rectangle1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_RECT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Horizontal1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_DIM_HOR );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Vertical1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_DIM_VER );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Parallel1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_DIM_PAR );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Angular1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_DIM_ANG );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Radius1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_DIM_RAD );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Diameter1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_DIM_DIAM );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Ordinate1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_DIM_ORD );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Hatch1Click(TObject *Sender)
{
  vlExecute( VC_DRAW_HATCH );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Text1Click(TObject *Sender)
{
  vlExecute( VC_INS_TEXT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Symbol1Click(TObject *Sender)
{
  vlExecute( VC_INS_SYMBOL );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InsertBlock1Click(TObject *Sender)
{
  vlExecute( VC_INS_BLOCK );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InsertImage1Click(TObject *Sender)
{
  vlExecute( VC_INS_IMAGE );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DistanceArea1Click(TObject *Sender)
{
  vlExecute( VC_TOOL_DIST );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PrintRectangles1Click(TObject *Sender)
{
  vlExecute( VC_TOOL_PRNRECT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Statistics1Click(TObject *Sender)
{
  vlExecute( VC_TOOL_STAT );    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
  ::MessageBox( Handle, "Test program", "About", MB_OK );
}
//---------------------------------------------------------------------------

