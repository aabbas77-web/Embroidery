/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* VeCAD drawing procedure
********************************************************************/
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "bcpp_editor_vecres.h"
#include "bcpp_editor_mru.h"

extern HINSTANCE ghInst;     // app instance
extern HWND      ghwMain;    // Main App window
extern CMruList  gMruList;

void OnCmFileNew   ();
void OnCmFileOpen  ();
int  LoadAppString (int Id);
void OnEndPaint (VLPAINTSTRUCT* ps);
void OnMouseMove (int xw, int yw, double x, double y);

static void UpdateMainTitle ();

bool bInTimerProc = false;

//-------------------------------------
int CALLBACK DwgProc (int iDwg, UINT Msg, int Prm1, int Prm2, double Prm3, double Prm4, void* Prm5)
{
  TCHAR szStr[256];
  double x, y, w, h, scx, scy;
  int BmpW, BmpH;
  HBITMAP hImage;

  switch( Msg ){
    case VM_ERROR:
      break;

    case VM_GETSTRING:
      break;

    case VM_ZOOM:
      break;

    case VM_MOUSEMOVE:
      break;

    case VM_ENDPAINT:
      // this message are sent just after VeCAD finish redraw entities from VEC file
      // here we can use vlDraw... functions

      // load some image
      BmpW = 500;   // I take this value, but you must know real size of your bitmap
      BmpH = 500;
      hImage = (HBITMAP)LoadImage( NULL, "c:\\abc123.bmp", IMAGE_BITMAP, BmpW, BmpH, LR_LOADFROMFILE );
      if (hImage){
        // get left cottom corner of the current drawing (-1)
        x = vlPropGetDbl( VD_DWG_LEFT, -1 );
        y = vlPropGetDbl( VD_DWG_BOTTOM, -1 );
        // get size of drawing
        w = vlPropGetDbl( VD_DWG_WIDTH, -1 );
        h = vlPropGetDbl( VD_DWG_HEIGHT, -1 );
        // calculate scale value, in order bitmap takes 1/4 of drawing size
        // pixels per drawing's unit
        scx = BmpW / w * 4;
        scy = BmpH / h * 4;
        // draw bitmap here
        vlDrawBitmap( hImage, BmpW, BmpH, x,y, scx, scy );
        DeleteObject( hImage ); 
      }
      break;

    case VM_OBJACTIVE:
      if (Prm1==VL_OBJ_PAGE){
        UpdateMainTitle();
      }
      break;

    case VM_DWGLOADED:
    case VM_DWGSAVED:
      gMruList.Add( (LPCTSTR)Prm5 );
    case VM_DWGSELECT:
      UpdateMainTitle();
      break;

    case VM_DWGLOADING:
    case VM_DWGSAVING:
      _stprintf( szStr, _T("Loading: %d%%"), Prm1 );
      vlStatBarSetText( VL_SB_COORD, szStr );
      break;


    case VM_EXECUTE:
      if (Prm2!=0 && 
          (Prm1==VC_FILE_NEW || Prm1==VC_FILE_OPEN))
      {
        switch( Prm1 ){
          case VC_FILE_NEW:  OnCmFileNew();  break;
          case VC_FILE_OPEN: OnCmFileOpen(); break;
        }
      }
      break;

    case VM_GRIPMOVE:
//      vlDataSetInt( VD_POLY_C_VER, Prm1, Prm2-1 );
//      id = (int)vlDataGetDouble( VD_POLY_VER_R, Prm1 );
      break;

    case VM_TOOLOPEN:
      if (Prm1==VC_CUSTOM+1){
        return 1;
      }
      break;

    case VM_TOOLCLICK:
      if (Prm1==VC_CUSTOM+1){
        MessageBox( 0, "aaa", "qqq", MB_OK );
      }
      break;

    case VM_LBDOWN:
      break;

  }
  return 0;
}


//-------------------------------------
//  Update title of the main window
//-------------------------------------
static void UpdateMainTitle ()
{
  TCHAR szPgName[64], szTitle[256], szFmt[64], szFName[256];

  int iPage = vlPageIndex( NULL, 0 );
  int nPage = vlPageCount();
  ZeroMemory( szPgName, sizeof(szPgName) );
  ZeroMemory( szFName, sizeof(szFName) );
  vlPropGet( VD_PAGE_NAME, iPage, szPgName );
  vlPropGet( VD_DWG_FILENAME, -1, szFName );
  if (_tcscmp(szFName,_T(""))==0){
    LoadString( ghInst, STR_NONAME, szFName,32 );
  }
  LoadString( ghInst, STR_APP_TITLE2, szFmt, 60 );
  _stprintf( szTitle, szFmt, szFName, iPage+1, nPage, szPgName );
  SetWindowText( ghwMain, szTitle );
}

