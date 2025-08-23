/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* Dialog "About"
********************************************************************/
#include <windows.h>
#include "bcpp_editor_vecres.h"
  #pragma  hdrstop

extern HINSTANCE ghInst;     // app instance

static BOOL CALLBACK DlgProcAbout (HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);


//-----------------------------------------------
int DlgAbout (HWND hw)
{
  int ret = DialogBox( ghInst, MAKEINTRESOURCE(DG_ABOUT), hw, (DLGPROC)DlgProcAbout );
  return ret;
}

#pragma argsused
//-----------------------------------------------
BOOL CALLBACK DlgProcAbout (HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  RECT  rect;
  POINT p;
  switch (uMsg) {
    case WM_INITDIALOG:
      GetWindowRect( hDlg, &rect );
      p.x = (GetSystemMetrics(SM_CXSCREEN)-(rect.right-rect.left))>>1;
      p.y = (GetSystemMetrics(SM_CYSCREEN)-(rect.bottom-rect.top))>>1;
      SetWindowPos( hDlg, HWND_TOP, p.x, p.y, 0,0, SWP_NOSIZE );
      return TRUE;

    case WM_CLOSE:
      EndDialog( hDlg, 0 );
      break;

    case WM_COMMAND:
      switch (LOWORD(wParam)) {
        case IDOK:
          EndDialog( hDlg, 1 );
          break;
      }
      break;
  }
  return FALSE;
}


