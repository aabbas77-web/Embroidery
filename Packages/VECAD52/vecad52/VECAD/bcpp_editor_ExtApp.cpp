/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* External Applications
********************************************************************/
#include <windows.h>
#include <tchar.h>
#include "bcpp_editor_extapp.h"
#include "bcpp_editor_vecres.h"

extern HWND  ghwMain;    // Main App window

// defined in mru.cpp
bool ModifyMenuItem (HMENU hMenu, UINT Cmd, LPCTSTR Text);


//*******************************************************************
CExtApp::CExtApp ()
{
  ::ZeroMemory( szTitle, sizeof(szTitle) );
  ::ZeroMemory( szFileName, sizeof(szFileName) );
}

//-------------------------------------
void CExtApp::SetTitle (LPCTSTR szStr)
{
  _tcsncpy( szTitle, szStr, SZ_EXTAPPTITLE );
  szTitle[SZ_EXTAPPTITLE-1] = 0;
}

//-------------------------------------
void CExtApp::SetFileName (LPCTSTR szStr)
{
  _tcsncpy( szFileName, szStr, 255 );
  szFileName[255] = 0;
  _tcslwr( szFileName );
}



//*******************************************************************
CAppList::CAppList ()
{
  n_app = 0;
}

//-----------------------------------------------
LPCTSTR CAppList::GetFileName (int Index)
{
  static TCHAR szBuf[256];
  ::ZeroMemory( szBuf, sizeof(szBuf) );
  if (0<=Index && Index<n_app){
    _tcscpy( szBuf, App[Index].GetFileName() );
    return szBuf;
  }
  return NULL;
}


//-------------------------------------
bool CAppList::Load (CConfig& Cfg)
{
  TCHAR  szKey[64], szVal[300];
  TCHAR  szTitle[SZ_EXTAPPTITLE];  // title for menu
  TCHAR  szFileName[256];         // exe file name
  int i,j,k,len,mode;
    
  n_app = 0;
  for (i=0; i<MAX_EXTAPP; i++){
    _stprintf( szKey, _T("EXTAPP%02d"), i );
    if (Cfg.GetValue( szKey, szVal )){
      ::ZeroMemory( szTitle, sizeof(szTitle) );
      ::ZeroMemory( szFileName, sizeof(szFileName) );
      len = _tcslen( szVal );
      k = 0;
      mode = 0;
      for (j=0; j<len; j++){
        if (szVal[j]=='['){
          mode = 1;
          k = 0;
          continue;
        }
        if (szVal[j]==']'){
          mode = 2;
          j++;
          k = 0;
          continue;
        }
        switch( mode ){
          case 1: szTitle[k++]=szVal[j]; break;
          case 2: szFileName[k++]=szVal[j]; break;
        }
      }
      for (j=0; j<n_app; j++){
        if (_tcsicmp( szTitle, App[j].GetTitle())==0 &&
            _tcsicmp( szFileName, App[j].GetFileName())==0)
        {
          j = 1000;  // filename already exist
          break;
        }
      }
      if (j!=1000){
        if (n_app<MAX_EXTAPP){
          App[n_app].SetTitle( szTitle );
          App[n_app].SetFileName( szFileName );
          n_app++;
        }
      }
    }
  }
  UpdateMenu();
  return true;
}


//-------------------------------------
bool CAppList::UpdateMenu ()
{
  if (n_app>0){
    HMENU hMainMenu = ::GetMenu( ghwMain );
    HMENU hMnu = ::GetSubMenu( hMainMenu, 5 );  // 5 - index of "Tools" item in main menu
    if (hMnu){
      int i;
      ::InsertMenu( hMnu, -1, MF_BYPOSITION, 0, 0 );
      for (i=0; i<n_app; i++){
        ::InsertMenu( hMnu, -1, MF_BYPOSITION, CM_APP_01+i, _T("!") );
      }
      for (i=0; i<n_app; i++){
        ::ModifyMenuItem( hMainMenu, CM_APP_01+i, App[i].GetTitle() );
      }
    }
    // update changes of main menu
    ::DrawMenuBar( ghwMain );
  }
  return true;
}

/*
EXTAPP00=[Run program] notepad.exe
EXTAPP01=[Old VeCAD] d:\!oks\v5\v5.exe
*/
