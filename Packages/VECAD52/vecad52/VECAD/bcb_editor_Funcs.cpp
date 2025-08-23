//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "api_VecApi.h"
#include "bcb_editor_Funcs.h"
#include "bcb_editor_DwgProc.h"
#include "bcb_editor_Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

HWND ghwVec;   // VeCAD window to display draw
int  VecX0;    // coordinates of left top corner
int  VecY0;    //       of VeCAD window
int  SBarH;    // height of status bar
bool TheEnd=false;

//-----------------------------------------------
void UnloadVecadDll ()
{
  vlCleanup();
  TheEnd = true;
}

//-----------------------------------------------
// Create VeCAD window
//-----------------------------------------------
void CreateVecWindow (HWND Handle)
{
  TheEnd = false;
  // Register your copy of Vecad.dll
  vlRegistration( ALISOFT_REG_CODE_5_2 );
//  vlRegistration( 0 );
  // Set message handler function
  vlSetMsgHandler( DwgProc );
  // Create VeCAD toolbar
  int w=0, h=0, h2;
  int x = 0;
  int y = -1;
  vlToolBarCreate( Handle, VL_TB_MAIN, x, y, -1, 1, &w, &h );
  y+=h;
  h2=h;
  x=0;
  vlToolBarCreate( Handle, VL_CB_LAYER, x, y, 210, h2, &w, &h );
  x+=w;
  vlToolBarCreate( Handle, VL_CB_COLOR, x, y, 90, h2, &w, &h );
  x+=w;
  vlToolBarCreate( Handle, VL_CB_STLINE, x, y, 200, h2, &w, &h );
  x+=w;
  vlToolBarCreate( Handle, VL_TB_SNAP, x, y, -1, 1, &w, &h );
  y+=h;
  vlToolBarCreate( Handle, VL_TB_DRAW, 0, y, 60, 500, &w, &h );
  y+=h;
  vlToolBarCreate( Handle, VL_TB_EDIT, 0, y, 60, -1, &w, &h );
  x=w;
  y=h2+h2-1;
  VecX0 = x;
  VecY0 = y;
  // Create VeCAD StatusBar
  vlStatBarCreate( Handle, &SBarH );
  // Create VeCAD window, size will be set in OnSize()
  ghwVec = vlWndCreate( Handle, VL_WS_CHILD|VL_WS_SCROLL|VL_WS_BORDER, VecX0,VecY0,400,300 );
  if (ghwVec){
    ::PostMessage( Handle, WM_SIZE, 0, 0 );
    vlPropPut( VD_WND_EMPTYTEXT, (int)ghwVec, "Editor" );
  }
}

//-----------------------------------------------
// Resize VeCAD window
//-----------------------------------------------
void ResizeVecWindow (HWND Handle)
{
  if (!TheEnd){
    int w, h;
    vlGetWinSize( Handle, &w, &h );
    if (w>0 && h>0){
      // Resize drawing window
      vlWndResize( ghwVec, VecX0, VecY0, w - VecX0, h - VecY0 - SBarH );
      // Resize statusbar
      vlStatBarResize();
    }
  }
}

//-------------------------------------------------------------------
void UpdateMainTitle ()
{
  char szPgName[64], szTitle[256], szFName[256];

  int iPage = vlPageIndex( NULL, 0 );
  int nPage = vlPageCount();
  ZeroMemory( szPgName, sizeof(szPgName) );
  ZeroMemory( szFName, sizeof(szFName) );
  vlPropGet( VD_PAGE_NAME, iPage, szPgName );
  vlPropGet( VD_DWG_FILENAME, -1, szFName );
  if (strcmp(szFName,"")==0){
    strcpy( szFName, "noname" );
  }
  sprintf( szTitle, "Editor - [%s], page: %d/%d  %c%s%c", szFName, iPage+1, nPage, '"', szPgName, '"' );
  Form1->Caption = szTitle;
}

//-----------------------------------------------
void FileNew ()
{
  vlFileNew( ghwVec, "" );
}

//-----------------------------------------------
void FileOpen ()
{
  vlFileOpen( ghwVec, "" );
}


