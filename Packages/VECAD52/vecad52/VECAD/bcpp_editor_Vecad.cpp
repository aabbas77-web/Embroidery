/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* Main module
* Defines the entry point for the application.
********************************************************************/
#include <windows.h>
#include <tchar.h>
#include <process.h>
#include "bcpp_editor_vecres.h"
#include "bcpp_editor_config.h"
#include "bcpp_editor_mru.h"
#include "bcpp_editor_extapp.h"


// Global Variables:
HINSTANCE ghInst = 0;		     // app instance
HWND      ghwMain = NULL;    // Main App window
HWND      ghwVec = NULL;     // Drawing's window
CConfig   gConfig;
CMruList  gMruList;
CAppList  gAppList;

// Global Functions
int CALLBACK DwgProc (int iDwg, UINT Msg, int Prm1, int Prm2, double Prm3, double Prm4, void* Prm5);
void OnCmFileNew  ();
void OnCmFileOpen ();
int  DlgAbout     (HWND hw);  // defined in 'DgAbout.cpp'


// Variables, used in this code module:
static TCHAR* szVecWndClass = _T("VeCAD_MainWindow");   
static int  VecX0 = 0;
static int  VecY0 = 0;
static int  SBarH = 0;  // height of status bar



// Foward declarations of functions included in this code module:
static ATOM MyRegisterClass (HINSTANCE hInstance);
static BOOL InitInstance    (HINSTANCE, int);
static void CreateVecWindow ();
static bool OnCommand       (HWND hWnd, int Cmd);
static void UpdateMenu (HMENU hMenu);
static void CfgSave    ();
static void CfgLoad    ();

static LRESULT CALLBACK	WndProc (HWND, UINT, WPARAM, LPARAM);

#pragma argsused
//*******************************************************************
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
  MSG msg;
  HACCEL hAccelTable;

  // Load Vecad.dll
  vlStartup();
  // Perform application initialization:
  MyRegisterClass( hInstance );
  if (!InitInstance (hInstance, nCmdShow)) {
    // Free Vecad.dll
    vlCleanup();
    return FALSE;
  }

  // load config from ini file,
  // config will be saved in response to WM_DESTROY message of main window
  CfgLoad();

  hAccelTable = LoadAccelerators( hInstance, (LPCTSTR)ACC_TABLE );

  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0)) {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  // Free Vecad.dll
  vlCleanup();
  return msg.wParam;
}


//-----------------------------------------------
// Registers the main window class.
//-----------------------------------------------
static ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEX wc;
  ZeroMemory( &wc, sizeof(wc) );
  wc.cbSize        = sizeof(WNDCLASSEX); 
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon( hInstance, (LPCTSTR)ICON_VECAD );
  wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground = (HBRUSH)( COLOR_WINDOW+1 );
  wc.lpszMenuName  = (LPCSTR)MENU_MAIN;
  wc.lpszClassName = szVecWndClass;
  wc.hIconSm       = LoadIcon( hInstance, (LPCTSTR)ICON_VECADSM);

  return RegisterClassEx( &wc );
}


#pragma argsused
//-----------------------------------------------
// Saves instance handle and creates main window
// In this function, we save the instance handle in a global variable and
// create and display the main program window.
//-----------------------------------------------
static BOOL InitInstance (HINSTANCE hInstance, int nCmdShow)
{
  ghInst = hInstance; // Store instance handle in our global variable

  TCHAR szTitle[64];
  ZeroMemory( szTitle, sizeof(szTitle) );
  LoadString( hInstance, STR_APP_TITLE, szTitle, 62 );

  ghwMain = CreateWindow( szVecWndClass, szTitle, WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
                          NULL, NULL, hInstance, NULL );
  if (!ghwMain){
    return FALSE;
  }

  // Create window to view VeCAD drawings
  CreateVecWindow();
  // Show Windows
  ShowWindow( ghwMain, SW_MAXIMIZE ); //nCmdShow );
  UpdateWindow( ghwMain );
  return TRUE;
}


//-----------------------------------------------
static void CreateVecWindow ()
{
  // Register your copy of Vecad.dll
  vlRegistration( 0 );
  // set function that will receive VeCAD messages
  vlSetMsgHandler( DwgProc );
  // Create VeCAD toolbar
  int w=0, h=0, h2;
  int x = 0;
  int y = -1;
  vlToolBarCreate( ghwMain, VL_TB_MAIN, x, y, -1, 1, &w, &h );
  y+=h;
  h2=h;
  x=0;
  vlToolBarCreate( ghwMain, VL_CB_LAYER, x, y, 210, h2, &w, &h );
  x+=w;
  vlToolBarCreate( ghwMain, VL_CB_COLOR, x, y, 90, h2, &w, &h );
  x+=w;
  vlToolBarCreate( ghwMain, VL_CB_STLINE, x, y, 200, h2, &w, &h );
  x+=w;
  vlToolBarCreate( ghwMain, VL_TB_SNAP, x, y, -1, 1, &w, &h );
  y+=h;
  vlToolBarCreate( ghwMain, VL_TB_DRAW, 0, y, 60, 500, &w, &h );
  y+=h;
  vlToolBarCreate( ghwMain, VL_TB_EDIT, 0, y, 60, -1, &w, &h );
  x=w;
  y=h2+h2-1;
  VecX0 = x;
  VecY0 = y;
  // Create VeCAD StatusBar
  vlStatBarCreate( ghwMain, &SBarH );
  // Create VeCAD window, size will be set in OnSize()
  ghwVec = vlWndCreate( ghwMain, VL_WS_CHILD|VL_WS_SCROLL|VL_WS_BORDER, 0,0,400,300 );
  if (ghwVec){
    TCHAR szStr[128];
    ZeroMemory( szStr, sizeof(szStr) );
    LoadString( ghInst, STR_WNDTEXT, szStr, 126 );
    vlPropPut( VD_WND_EMPTYTEXT, (int)ghwVec, szStr );
//    vlPropPutInt( VD_WND_CURSOR_CROSS, (int)ghwVec, 0 );
  }
}


//-----------------------------------------------
// Processes messages for the main window.
//-----------------------------------------------
static LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int cx,cy;

  switch( message ){
    case WM_COMMAND:
      if (OnCommand( hWnd, LOWORD(wParam) )==false){
        return DefWindowProc( hWnd, message, wParam, lParam );
      } 
      break;

    case WM_CLOSE:
      CfgSave();   // save config
      if (vlExecute( VC_FILE_CLOSEALL )){
        // close main window
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
      // do not close main window
      return 0;

    case WM_DESTROY:
      ::DestroyWindow( ghwVec );	
      PostQuitMessage(0);
      break;

    case WM_ERASEBKGND:
      return 0;

    case WM_SIZE:
      // Resize VeCAD window
      cx = LOWORD(lParam);  // width of client area 
      cy = HIWORD(lParam); // height of client area       
      if (cx>0 && cy>0){
        vlWndResize( ghwVec, VecX0, VecY0, cx-VecX0, cy-VecY0-SBarH );
        vlStatBarResize();
      }
      break;

    case WM_INITMENU:
      UpdateMenu( (HMENU) wParam );
      break;

    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


//-----------------------------------------------
void UpdateMenu (HMENU hMenu)
{
  HMENU hMainMenu = ::GetMenu( ghwMain );
  if (hMenu==hMainMenu){
    BOOL bCheck;
    UINT b;
    bCheck = vlPropGetInt( VD_PRJ_WDWG_ON, 0 );
    b = (bCheck)? MF_BYCOMMAND | MF_CHECKED : MF_BYCOMMAND | MF_UNCHECKED;
    ::CheckMenuItem( hMainMenu, VC_FILE_LIST, b );
    bCheck = vlPropGetInt( VD_PRJ_WVIEW_ON, 0 );
    b = (bCheck)? MF_BYCOMMAND | MF_CHECKED : MF_BYCOMMAND | MF_UNCHECKED;
    ::CheckMenuItem( hMainMenu, VC_VIEW_LIST, b );
  }
}


//-----------------------------------------------
void CfgSave ()
{
  TCHAR szValue[64];
  int iv;
   
  //------- Most Recently Used files
  gMruList.Save( gConfig );

  //------- window "Drawings"
  iv = vlPropGetInt( VD_PRJ_WDWG_ON, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WDWG_ON"), szValue );

  iv = vlPropGetInt( VD_PRJ_WDWG_LEFT, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WDWG_LEFT"), szValue );

  iv = vlPropGetInt( VD_PRJ_WDWG_TOP, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WDWG_TOP"), szValue );

  iv = vlPropGetInt( VD_PRJ_WDWG_RIGHT, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WDWG_RIGHT"), szValue );

  iv = vlPropGetInt( VD_PRJ_WDWG_BOTTOM, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WDWG_BOTTOM"), szValue );

  //------- window "Views"
  iv = vlPropGetInt( VD_PRJ_WVIEW_ON, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WVIEW_ON"), szValue );

  iv = vlPropGetInt( VD_PRJ_WVIEW_LEFT, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WVIEW_LEFT"), szValue );

  iv = vlPropGetInt( VD_PRJ_WVIEW_TOP, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WVIEW_TOP"), szValue );

  iv = vlPropGetInt( VD_PRJ_WVIEW_RIGHT, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WVIEW_RIGHT"), szValue );

  iv = vlPropGetInt( VD_PRJ_WVIEW_BOTTOM, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WVIEW_BOTTOM"), szValue );

  //------- position of window "Distance/Area"
  iv = vlPropGetInt( VD_PRJ_WDIST_LEFT, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WDIST_LEFT"), szValue );

  iv = vlPropGetInt( VD_PRJ_WDIST_TOP, 0 );
  _itot( iv, szValue, 10 );
  gConfig.SetValue( _T("WDIST_TOP"), szValue );

  gConfig.Close();
}


//-----------------------------------------------
void CfgLoad ()
{
  TCHAR szCfgFile[256];
  TCHAR szValue[64];
  int iv;
  int ret = ::GetModuleFileName( NULL, szCfgFile, 255 );
  if (ret>1){
    TCHAR* p = _tcsrchr( szCfgFile, '\\' );
    if (p!=NULL){
      p[0]=0;
      _tcscat( szCfgFile, _T("\\vecad.ini") );

      gConfig.Open( szCfgFile );

      //------- Most Recently Used files
      gMruList.Load( gConfig );

      //------- window "Drawings"
      if (gConfig.GetValue( _T("WDWG_LEFT"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WDWG_LEFT, 0, iv );
      }
      if (gConfig.GetValue( _T("WDWG_TOP"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WDWG_TOP, 0, iv );
      }
      if (gConfig.GetValue( _T("WDWG_RIGHT"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WDWG_RIGHT, 0, iv );
      }
      if (gConfig.GetValue( _T("WDWG_BOTTOM"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WDWG_BOTTOM, 0, iv );
      }
      if (gConfig.GetValue( _T("WDWG_ON"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WDWG_ON, (int)ghwMain, (iv==0)?FALSE:TRUE );
      }

      //------- window "Views"
      if (gConfig.GetValue( _T("WVIEW_LEFT"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WVIEW_LEFT, 0, iv );
      }
      if (gConfig.GetValue( _T("WVIEW_TOP"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WVIEW_TOP, 0, iv );
      }
      if (gConfig.GetValue( _T("WVIEW_RIGHT"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WVIEW_RIGHT, 0, iv );
      }
      if (gConfig.GetValue( _T("WVIEW_BOTTOM"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WVIEW_BOTTOM, 0, iv );
      }
      if (gConfig.GetValue( _T("WVIEW_ON"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WVIEW_ON, (int)ghwMain, (iv==0)?FALSE:TRUE );
      }

      //------- position of window "Distance/Area"
      if (gConfig.GetValue( _T("WDIST_LEFT"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WDIST_LEFT, 0, iv );
      }
      if (gConfig.GetValue( _T("WDIST_TOP"), szValue )){
        iv = _ttoi( szValue );
        vlPropPutInt( VD_PRJ_WDIST_TOP, 0, iv );
      }

      //------- external applications
      gAppList.Load( gConfig );
    }
  }
}


//-----------------------------------------------
void OnCmFileNew () 
{
  vlFileNew( ghwVec, "" );
/*
  int iDwg = vlDocCreate( ghwVec, DwgProc );
  if (iDwg>=0){
    vlClear( TRUE );
    vlRedraw();
    vlSetFocus();
  }
*/
}

//-----------------------------------------------
void OnCmFileOpen () 
{
  vlFileOpen( ghwVec, "" );
/*
  int iDwg = vlDwgCreate( ghwVec, DwgProc );
  if (iDwg>=0){
    if (vlFileLoad( VL_FILE_VEC, NULL )==FALSE){
      vlDwgDelete( iDwg );
    }
  }
*/
}

//-----------------------------------------------
void OpenMruFile (int i)
{
  LPCTSTR pszFileName = gMruList.Get( i );
  if (pszFileName){
  	vlFileOpen( ghwVec, pszFileName );
/*
  	int iDwg = vlDwgCreate( ghwVec, DwgProc );
    if (iDwg>=0){
  	  if (vlFileLoad( VL_FILE_VEC, pszFileName )==FALSE){
        vlDwgDelete( iDwg );
      }else{
        vlSetFocus();
      }
    }
*/
  }    
}

//-----------------------------------------------
void OnMru01() 
{
  OpenMruFile( 0 );
}
//-----------------------------------------------
void OnMru02() 
{
  OpenMruFile( 1 );	
}
//-----------------------------------------------
void OnMru03() 
{
  OpenMruFile( 2 );
}
//-----------------------------------------------
void OnMru04() 
{
  OpenMruFile( 3 );
}
//-----------------------------------------------
void OnMru05() 
{
  OpenMruFile( 4 );
}
//-----------------------------------------------
void OnMru06() 
{
  OpenMruFile( 5 );
}
//-----------------------------------------------
void OnMru07() 
{
  OpenMruFile( 6 );
}
//-----------------------------------------------
void OnMru08() 
{
  OpenMruFile( 7 );
}
//-----------------------------------------------
void OnMru09() 
{
  OpenMruFile( 8 );
}
//-----------------------------------------------
void OnMru10() 
{
  OpenMruFile( 9 );
}
//-----------------------------------------------
void OnMru11() 
{
  OpenMruFile( 10 );
}


//-----------------------------------------------
void RunExtApp (int i)
{
  LPCTSTR pszFileName = gAppList.GetFileName( i );
  if (pszFileName){
    TCHAR szBuf[300]; szBuf[0]=0;
    TCHAR* arg[2];
    arg[0] = new TCHAR[256];
    arg[1] = NULL; //new TCHAR[256];
    _tcscpy( arg[0], pszFileName );
    if (_tspawnvp( P_NOWAIT, arg[0], arg )==-1){
      _stprintf( szBuf, _T("Can't to run '%s' (errno=%d)"), pszFileName, errno);
      ::MessageBox( ghwMain, szBuf, _T("VeCAD"), MB_OK|MB_ICONEXCLAMATION );
    }
    delete[] arg[0];
  }    
}

//-----------------------------------------------
void OnExtApp01() 
{
  RunExtApp( 0 );
}
//-----------------------------------------------
void OnExtApp02() 
{
  RunExtApp( 1 );
}
//-----------------------------------------------
void OnExtApp03() 
{
  RunExtApp( 2 );
}
//-----------------------------------------------
void OnExtApp04() 
{
  RunExtApp( 3 );
}
//-----------------------------------------------
void OnExtApp05() 
{
  RunExtApp( 4 );
}
//-----------------------------------------------
void OnExtApp06() 
{
  RunExtApp( 5 );
}
//-----------------------------------------------
void OnExtApp07() 
{
  RunExtApp( 6 );
}
//-----------------------------------------------
void OnExtApp08() 
{
  RunExtApp( 7 );
}
//-----------------------------------------------
void OnExtApp09() 
{
  RunExtApp( 8 );
}
//-----------------------------------------------
void OnExtApp10() 
{
  RunExtApp( 9 );
}



//-----------------------------------------------
void OnCmFileSave() 
{
  vlExecute( VC_FILE_SAVE );
}

//-----------------------------------------------
void OnCmFileSaveAs() 
{
  vlExecute( VC_FILE_SAVEAS );	
}


//-----------------------------------------------
void OnCmFileClose() 
{
  vlExecute( VC_FILE_CLOSE );
}

//-----------------------------------------------
void OnCmFileCloseAll() 
{
  vlExecute( VC_FILE_CLOSEALL );
}

//-----------------------------------------------
void OnCmFileList() 
{
  vlFileList( ghwMain );
  HMENU hMainMenu = ::GetMenu( ghwMain );
  BOOL bCheck = vlPropGetInt( VD_PRJ_WDWG_ON, 0 );
  UINT b = (bCheck)? MF_BYCOMMAND | MF_CHECKED : MF_BYCOMMAND | MF_UNCHECKED;
  ::CheckMenuItem( hMainMenu, VC_FILE_LIST, b );
}

//-----------------------------------------------
void OnCmImportDxf() 
{
  vlExecute( VC_IMPORT_DXF );
}
//-----------------------------------------------
void OnCmImportVdf() 
{
  vlExecute( VC_IMPORT_VDF );
}
//-----------------------------------------------
void OnCmExportDxf() 
{
  vlExecute( VC_EXPORT_DXF );
}
//-----------------------------------------------
void OnCmExportHpgl() 
{
  vlExecute( VC_EXPORT_HPGL );
}
//-----------------------------------------------
void OnCmExportBmp() 
{
  vlExecute( VC_EXPORT_BMP );
}



//***********************************************
void OnCmZoomAll() 
{
  vlExecute( VC_ZOOM_ALL );
}
//-----------------------------------------------
void OnCmZoomWin() 
{
  vlExecute( VC_ZOOM_WIN );
}
//-----------------------------------------------
void OnCmZoomIn() 
{
  vlExecute( VC_ZOOM_IN );
}
//-----------------------------------------------
void OnCmZoomOut() 
{
  vlExecute( VC_ZOOM_OUT );
}
//-----------------------------------------------
void OnCmZoomPan() 
{
  vlExecute( VC_ZOOM_PAN );
}
//-----------------------------------------------
void OnCmZoomPage() 
{
  vlExecute( VC_ZOOM_PAGE );
}

//-----------------------------------------------
void OnCmPageFirst() 
{
  vlExecute( VC_PAGE_FIRST );
}
//-----------------------------------------------
void OnCmPageLast() 
{
  vlExecute( VC_PAGE_LAST );
}
//-----------------------------------------------
void OnCmPagePrev() 
{
  vlExecute( VC_PAGE_PREV );
}
//-----------------------------------------------
void OnCmPageNext() 
{
  vlExecute( VC_PAGE_NEXT );
}
//-----------------------------------------------
void OnCmPageDlg() 
{
  vlExecute( VC_PAGE_DLG );
}

//-----------------------------------------------
void OnCmViewList() 
{
  vlExecute( VC_VIEW_LIST );
  HMENU hMainMenu = ::GetMenu( ghwMain );
  BOOL bCheck = vlPropGetInt( VD_PRJ_WVIEW_ON, 0 );
  UINT b = (bCheck)? MF_BYCOMMAND | MF_CHECKED : MF_BYCOMMAND | MF_UNCHECKED;
  ::CheckMenuItem( hMainMenu, VC_VIEW_LIST, b );
}

//-----------------------------------------------
void OnCmViewSave() 
{
  vlExecute( VC_VIEW_SAVE );
}




//***********************************************
void OnCmEditCbCut() 
{
  vlExecute( VC_EDIT_CBCUT );
}
//-----------------------------------------------
void OnCmEditCbCopy() 
{
  vlExecute( VC_EDIT_CBCOPY );
}
//-----------------------------------------------
void OnCmEditCbPaste() 
{
  vlExecute( VC_EDIT_CBPASTE );
}
//-----------------------------------------------
void OnCmEditEntprop() 
{
  vlExecute( VC_EDIT_ENTPROP );
}
//-----------------------------------------------
void OnCmEditRedo() 
{
  vlExecute( VC_EDIT_REDO );
}
//-----------------------------------------------
void OnCmEditUndo() 
{
  vlExecute( VC_EDIT_UNDO );
}
//-----------------------------------------------
void OnCmEditCopy() 
{
  vlExecute( VC_EDIT_COPY );
}
//-----------------------------------------------
void OnCmEditTrim() 
{
  vlExecute( VC_EDIT_TRIM );
}
//-----------------------------------------------
void OnCmEditScale() 
{
  vlExecute( VC_EDIT_SCALE );
}
//-----------------------------------------------
void OnCmEditCreblock() 
{
  vlExecute( VC_EDIT_CREBLOCK );
}
//-----------------------------------------------
void OnCmEditErase() 
{
  vlExecute( VC_EDIT_ERASE );
}
//-----------------------------------------------
void OnCmEditExplode() 
{
  vlExecute( VC_EDIT_EXPLODE );
}
//-----------------------------------------------
void OnCmEditExtend() 
{
  vlExecute( VC_EDIT_EXTEND );
}
//-----------------------------------------------
void OnCmEditFillet() 
{
  vlExecute( VC_EDIT_FILLET );
}
//-----------------------------------------------
void OnCmEditMirror() 
{
  vlExecute( VC_EDIT_MIRROR );
}
//-----------------------------------------------
void OnCmEditMove() 
{
  vlExecute( VC_EDIT_MOVE );
}
//-----------------------------------------------
void OnCmEditRotate() 
{
  vlExecute( VC_EDIT_ROTATE );
}


//***********************************************
void OnCmPrint() 
{
  vlExecute( VC_PRINT );
}
//-----------------------------------------------
void OnCmReset()
{
  vlExecute( VC_RESET );
}
//-----------------------------------------------
void OnCmLineWidth()
{
  vlExecute( VC_SHOWLINEW );
}


//***********************************************
void OnCmDrawLine() 
{
  vlExecute( VC_DRAW_LINE );	
}
//-----------------------------------------------
void OnCmDrawPolyline() 
{
  vlExecute( VC_DRAW_POLYLINE );	
}
//-----------------------------------------------
void OnCmDrawSpline() 
{
  vlExecute( VC_DRAW_SPLINE );	
}
//-----------------------------------------------
void OnCmDrawPoint() 
{
  vlExecute( VC_DRAW_POINT );
}
//-----------------------------------------------
void OnCmDrawCircCR() 
{
  vlExecute( VC_DRAW_CIRC_CR );
}
//-----------------------------------------------
void OnCmDrawCircCD() 
{
  vlExecute( VC_DRAW_CIRC_CD );
}
//-----------------------------------------------
void OnCmDrawCirc2P() 
{
  vlExecute( VC_DRAW_CIRC_2P );
}
//-----------------------------------------------
void OnCmDrawCirc3P() 
{
  vlExecute( VC_DRAW_CIRC_3P );
}
//-----------------------------------------------
void OnCmDrawArcCSE()
{
  vlExecute( VC_DRAW_ARC_CSE );
}
//-----------------------------------------------
void OnCmDrawArcSEM()
{
  vlExecute( VC_DRAW_ARC_SEM );
}
//-----------------------------------------------
void OnCmDrawArcSME()
{
  vlExecute( VC_DRAW_ARC_SME );
}
//-----------------------------------------------
void OnCmDrawEllipse() 
{
  vlExecute( VC_DRAW_ELLIPSE );
}
//-----------------------------------------------
void OnCmDrawRect() 
{
  vlExecute( VC_DRAW_RECT );
}
//-----------------------------------------------
void OnCmDrawHatch() 
{
  vlExecute( VC_DRAW_HATCH );
}
//-----------------------------------------------
void OnCmDrawDimHor()
{
  vlExecute( VC_DRAW_DIM_HOR );
}
//-----------------------------------------------
void OnCmDrawDimVer()
{
  vlExecute( VC_DRAW_DIM_VER );
}
//-----------------------------------------------
void OnCmDrawDimPar()
{
  vlExecute( VC_DRAW_DIM_PAR );
}
//-----------------------------------------------
void OnCmDrawDimAng()
{
  vlExecute( VC_DRAW_DIM_ANG );
}
//-----------------------------------------------
void OnCmDrawDimRad()
{
  vlExecute( VC_DRAW_DIM_RAD );
}
//-----------------------------------------------
void OnCmDrawDimDiam()
{
  vlExecute( VC_DRAW_DIM_DIAM );
}
//-----------------------------------------------
void OnCmDrawDimOrd()
{
  vlExecute( VC_DRAW_DIM_ORD );
}
//-----------------------------------------------
void OnCmInsText() 
{
  vlExecute( VC_INS_TEXT );	
}
//-----------------------------------------------
void OnCmInsSymbol() 
{
  vlExecute( VC_INS_SYMBOL );	
}
//-----------------------------------------------
void OnCmInsBlock() 
{
  vlExecute( VC_INS_BLOCK );
}
//-----------------------------------------------
void OnCmInsImage() 
{
  vlExecute( VC_INS_IMAGE );
}
//-----------------------------------------------
void OnCmInsRMap() 
{
  vlExecute( VC_INS_RMAP );
}


//***********************************************
void OnCmFmtBlock() 
{
  vlExecute( VC_FMT_BLOCK );
}
//-----------------------------------------------
void OnCmFmtLayer() 
{
  vlExecute( VC_FMT_LAYER );
}
//-----------------------------------------------
void OnCmFmtPage() 
{
  vlExecute( VC_FMT_PAGE );
}
//-----------------------------------------------
void OnCmFmtStdim() 
{
  vlExecute( VC_FMT_STDIM );
}
//-----------------------------------------------
void OnCmFmtSthatch() 
{
  vlExecute( VC_FMT_STHATCH );
}
//-----------------------------------------------
void OnCmFmtStline() 
{
  vlExecute( VC_FMT_STLINE );
}
//-----------------------------------------------
void OnCmFmtStpoint() 
{
  vlExecute( VC_FMT_STPOINT );
}
//-----------------------------------------------
void OnCmFmtSttext() 
{
  vlExecute( VC_FMT_STTEXT );
}
//-----------------------------------------------
void OnCmFmtLayout() 
{
  vlExecute( VC_FMT_LAYOUT );
}
//-----------------------------------------------
void OnCmFmtOsnap() 
{
  vlExecute( VC_FMT_OSNAP );
}
//-----------------------------------------------
void OnCmFmtGrid() 
{
  vlExecute( VC_FMT_GRID );
}
//-----------------------------------------------
void OnCmFmtPsnap() 
{
  vlExecute( VC_FMT_PSNAP );
}
//-----------------------------------------------
void OnCmFmtUnits() 
{
  vlExecute( VC_FMT_UNITS );
}
//-----------------------------------------------
void OnCmFmtPrivate() 
{
  vlExecute( VC_FMT_PRIVATE );
}
//-----------------------------------------------
void OnCmFmtPrefers() 
{
  vlExecute( VC_FMT_PREFERS );
}


//***********************************************
void OnCmToolDist() 
{
  vlExecute( VC_TOOL_DIST );
}
//-----------------------------------------------
void OnCmToolPrnRect() 
{
  vlExecute( VC_TOOL_PRNRECT );
}
//-----------------------------------------------
void OnCmToolStat() 
{
  vlExecute( VC_TOOL_STAT );
}



//*******************************************************************
static bool OnCommand (HWND hWnd, int Cmd)
{
  bool ret = true;
  switch( Cmd ){
    case CM_FILE_NEW:  OnCmFileNew();  break;
    case CM_FILE_OPEN: OnCmFileOpen(); break;
    case CM_MRU_01: OnMru01(); break;
    case CM_MRU_02: OnMru02(); break;
    case CM_MRU_03: OnMru03(); break;
    case CM_MRU_04: OnMru04(); break;
    case CM_MRU_05: OnMru05(); break;
    case CM_MRU_06: OnMru06(); break;
    case CM_MRU_07: OnMru07(); break;
    case CM_MRU_08: OnMru08(); break;
    case CM_MRU_09: OnMru09(); break;
    case CM_MRU_11: OnMru11(); break;
    case CM_MRU_10: OnMru10(); break;
    case CM_APP_01: OnExtApp01(); break;
    case CM_APP_02: OnExtApp02(); break;
    case CM_APP_03: OnExtApp03(); break;
    case CM_APP_04: OnExtApp04(); break;
    case CM_APP_05: OnExtApp05(); break;
    case CM_APP_06: OnExtApp06(); break;
    case CM_APP_07: OnExtApp07(); break;
    case CM_APP_08: OnExtApp08(); break;
    case CM_APP_EXIT:  PostMessage(hWnd,WM_CLOSE,0,0); break;
    case CM_APP_ABOUT: 
      DlgAbout(hWnd); 
      break;

    case VC_FILE_SAVE:      OnCmFileSave(); break;
    case VC_FILE_CLOSE:     OnCmFileClose(); break;
    case VC_FILE_CLOSEALL:  OnCmFileCloseAll(); break;
    case VC_FILE_LIST:      OnCmFileList(); break;

    case VC_FILE_SAVEAS: OnCmFileSaveAs(); break;
    case VC_IMPORT_DXF:  OnCmImportDxf(); break;
    case VC_IMPORT_VDF:  OnCmImportVdf(); break;
    case VC_EXPORT_DXF:  OnCmExportDxf(); break;
    case VC_EXPORT_HPGL: OnCmExportHpgl(); break;
    case VC_EXPORT_BMP:  OnCmExportBmp(); break;

    case VC_PRINT:      OnCmPrint(); break;
    case VC_RESET:      OnCmReset(); break;
    case VC_SHOWLINEW:  OnCmLineWidth(); break;

    case VC_ZOOM_ALL  : OnCmZoomAll(); break;
    case VC_ZOOM_WIN  : OnCmZoomWin(); break;
    case VC_ZOOM_IN   : OnCmZoomIn(); break;
    case VC_ZOOM_OUT  : OnCmZoomOut(); break;
    case VC_ZOOM_PAN  : OnCmZoomPan(); break;
    case VC_ZOOM_PAGE : OnCmZoomPage(); break;
    case VC_PAGE_FIRST: OnCmPageFirst(); break;
    case VC_PAGE_LAST : OnCmPageLast(); break;
    case VC_PAGE_PREV : OnCmPagePrev(); break;
    case VC_PAGE_NEXT : OnCmPageNext(); break;
    case VC_PAGE_DLG  : OnCmPageDlg(); break;
    case VC_VIEW_LIST : OnCmViewList(); break;
    case VC_VIEW_SAVE : OnCmViewSave(); break;

    case VC_EDIT_CBCUT   : OnCmEditCbCut(); break;
    case VC_EDIT_CBCOPY  : OnCmEditCbCopy(); break;
    case VC_EDIT_CBPASTE : OnCmEditCbPaste(); break;
    case VC_EDIT_ENTPROP : OnCmEditEntprop(); break;
    case VC_EDIT_REDO    : OnCmEditRedo(); break;
    case VC_EDIT_COPY    : OnCmEditCopy(); break;
    case VC_EDIT_UNDO    : OnCmEditUndo(); break;
    case VC_EDIT_TRIM    : OnCmEditTrim(); break;
    case VC_EDIT_SCALE   : OnCmEditScale(); break;
    case VC_EDIT_CREBLOCK: OnCmEditCreblock(); break;
    case VC_EDIT_ERASE   : OnCmEditErase(); break;
    case VC_EDIT_EXPLODE : OnCmEditExplode(); break;
    case VC_EDIT_EXTEND  : OnCmEditExtend(); break;
    case VC_EDIT_FILLET  : OnCmEditFillet(); break;
    case VC_EDIT_MIRROR  : OnCmEditMirror(); break;
    case VC_EDIT_MOVE    : OnCmEditMove(); break;
    case VC_EDIT_ROTATE  : OnCmEditRotate(); break;

    case VC_DRAW_LINE    : OnCmDrawLine(); break;
    case VC_DRAW_POLYLINE: OnCmDrawPolyline(); break;
    case VC_DRAW_SPLINE  : OnCmDrawSpline(); break;
    case VC_DRAW_POINT   : OnCmDrawPoint(); break;
    case VC_DRAW_CIRC_CR : OnCmDrawCircCR(); break;
    case VC_DRAW_CIRC_CD : OnCmDrawCircCD(); break;
    case VC_DRAW_CIRC_2P : OnCmDrawCirc2P(); break;
    case VC_DRAW_CIRC_3P : OnCmDrawCirc3P(); break;
    case VC_DRAW_ARC_CSE : OnCmDrawArcCSE(); break;
    case VC_DRAW_ARC_SEM : OnCmDrawArcSEM(); break;
    case VC_DRAW_ARC_SME : OnCmDrawArcSME(); break;
    case VC_DRAW_ELLIPSE : OnCmDrawEllipse(); break;
    case VC_DRAW_RECT    : OnCmDrawRect(); break;
    case VC_DRAW_HATCH   : OnCmDrawHatch(); break;
    case VC_DRAW_DIM_HOR : OnCmDrawDimHor(); break;
    case VC_DRAW_DIM_VER : OnCmDrawDimVer(); break;
    case VC_DRAW_DIM_PAR : OnCmDrawDimPar(); break;
    case VC_DRAW_DIM_ANG : OnCmDrawDimAng(); break;
    case VC_DRAW_DIM_RAD : OnCmDrawDimRad(); break;
    case VC_DRAW_DIM_DIAM: OnCmDrawDimDiam(); break;
    case VC_DRAW_DIM_ORD : OnCmDrawDimOrd(); break;
    case VC_INS_TEXT     : OnCmInsText(); break;
    case VC_INS_SYMBOL   : OnCmInsSymbol(); break;
    case VC_INS_BLOCK    : OnCmInsBlock(); break;
    case VC_INS_IMAGE    : OnCmInsImage(); break;
    case VC_INS_RMAP     : OnCmInsRMap(); break;

    case VC_FMT_BLOCK  : OnCmFmtBlock(); break;
    case VC_FMT_LAYER  : OnCmFmtLayer(); break;
    case VC_FMT_PAGE   : OnCmFmtPage(); break;
    case VC_FMT_STDIM  : OnCmFmtStdim(); break;
    case VC_FMT_STHATCH: OnCmFmtSthatch(); break;
    case VC_FMT_STLINE : OnCmFmtStline(); break;
    case VC_FMT_STPOINT: OnCmFmtStpoint(); break;
    case VC_FMT_STTEXT : OnCmFmtSttext(); break;
    case VC_FMT_LAYOUT : OnCmFmtLayout(); break;
    case VC_FMT_OSNAP  : OnCmFmtOsnap(); break;
    case VC_FMT_GRID   : OnCmFmtGrid(); break;
    case VC_FMT_PSNAP  : OnCmFmtPsnap(); break;
    case VC_FMT_UNITS  : OnCmFmtUnits(); break;
    case VC_FMT_PRIVATE: OnCmFmtPrivate(); break;
    case VC_FMT_PREFERS: OnCmFmtPrefers(); break;

    case VC_TOOL_DIST   : OnCmToolDist(); break;
    case VC_TOOL_PRNRECT: OnCmToolPrnRect(); break;
    case VC_TOOL_STAT   : OnCmToolStat(); break; 
    
    default:
      ret = false;
  }
  return ret;
}



/*
// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    case WM_INITDIALOG:
      return TRUE;

    case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
      {
        EndDialog(hDlg, LOWORD(wParam));
        return TRUE;
      }
      break;
  }
  return FALSE;
}
*/


