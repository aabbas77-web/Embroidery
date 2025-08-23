/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* Most Recent Files (MRU)
********************************************************************/
#include <windows.h>
#include <tchar.h>
#include "bcpp_editor_mru.h"
#include "bcpp_editor_vecres.h"

extern HWND  ghwMain;    // Main App window

bool ModifyMenuItem (HMENU hMenu, UINT Cmd, LPCTSTR Text);
static int  _cdecl CmpMruFile (const void* e1, const void* e2);


//-------------------------------------
CMruFile::CMruFile ()
{
  ::ZeroMemory( szName, sizeof(szName) );
  OpenTime = 0;
}


//-------------------------------------
void CMruFile::SetName (LPCTSTR szStr)
{
  _tcsncpy( szName, szStr, SZ_MRUFILENAME );
  szName[SZ_MRUFILENAME-1] = 0;
  _tcslwr( szName );
}



//*******************************************************************
CMruList::CMruList ()
{
  n_file = 0;
}


//-------------------------------------
void CMruList::Add (LPCTSTR szFileName)
{
  int  i;
  bool bExist = false;

  for (i=0; i<n_file; i++){
    if (_tcsicmp( szFileName, File[i].GetName())==0){
      File[i].SetTime();
      bExist = true;
      break;  // file already exist in the list
    }
  }
  if (bExist==false){
    if (n_file<MAX_MRU){
      i = n_file++;
    }else{
      i = n_file - 1;
    }
    File[i].SetName( szFileName );
  }
  // sort list and update main menu
  qsort( File, n_file, sizeof(CMruFile), CmpMruFile );
  UpdateMenu();
}


//-------------------------------------
LPCTSTR CMruList::Get (int Index, bool bSetTime)
{
  static TCHAR szBuf[256];
  ::ZeroMemory( szBuf, sizeof(szBuf) );
  if (0<=Index && Index<n_file){
    _tcscpy( szBuf, File[Index].GetName() );
    if (bSetTime){
      File[Index].SetTime();
      // sort list and update main menu
      qsort( File, n_file, sizeof(CMruFile), CmpMruFile );
      UpdateMenu();
    }
    return szBuf;
  }
  return NULL;
}


//-------------------------------------
bool CMruList::Load (CConfig& Cfg)
{
  TCHAR  szKey[64], szVal[256];
  HANDLE hFile;
  WIN32_FIND_DATA FindFileData;
  int i,j;
    
  n_file = 0;
  for (i=0; i<MAX_MRU; i++){
    _stprintf( szKey, _T("MRU%02d"), i );
    if (Cfg.GetValue( szKey, szVal )){
      for (j=0; j<n_file; j++){
        if (_tcsicmp( szVal, File[j].GetName())==0){
          j = 1000;  // filename already exist
          break;
        }
      }
      if (j!=1000){
        hFile = ::FindFirstFile( szVal, &FindFileData );
        if (hFile!=INVALID_HANDLE_VALUE){
          FindClose( hFile );
          if (n_file<MAX_MRU){
            File[n_file].SetName( szVal );
            File[n_file].SetTime( MAX_MRU-n_file );
            n_file++;
          }
        }
      }
    }
  }

  UpdateMenu();
  return true;
}


//-------------------------------------
bool CMruList::Save (CConfig& Cfg)
{
  TCHAR szKey[64];
  ::ZeroMemory( szKey, sizeof(szKey) );

  qsort( File, n_file, sizeof(CMruFile), CmpMruFile );
  for (int i=0; i<n_file; i++){
    _stprintf( szKey, _T("MRU%02d"), i );
    Cfg.SetValue( szKey, File[i].GetName() );
  }
  return true;
}


//-------------------------------------
bool CMruList::UpdateMenu ()
{
  int ItemPos = 4; // position of item "Recent" in the "File" popup menu
  HMENU hMainMenu = ::GetMenu( ghwMain );
  int i;
  for (i=0; i<MAX_MRU; i++){
    ::DeleteMenu( hMainMenu, CM_MRU_01+i, MF_BYCOMMAND );
  }
  HMENU hMnu = ::GetSubMenu( hMainMenu, 0 );  // 0 - index of "File" item in main menu
  HMENU hMnu2 = ::GetSubMenu( hMnu, ItemPos ); 
  if (n_file==0){
    ::EnableMenuItem( hMnu, 2, MF_BYPOSITION | MF_GRAYED | MF_DISABLED );
  }else{
    ::EnableMenuItem( hMnu, 2, MF_BYPOSITION | MF_ENABLED );
    if (hMnu2){
      for (i=0; i<n_file; i++){
        ::InsertMenu( hMnu2, i, MF_BYPOSITION, CM_MRU_01+i, _T("!") );
      }
      for (i=0; i<n_file; i++){
        ::ModifyMenuItem( hMainMenu, CM_MRU_01+i, File[i].GetName() );
      }
    }
  }

  // update changes of main menu
  ::DrawMenuBar( ghwMain );

  return true;
}



//***********************************************
static int _cdecl CmpMruFile (const void* e1, const void* e2)
{
  time_t t1 = ((CMruFile*)e1)->GetTime();
  time_t t2 = ((CMruFile*)e2)->GetTime();
  if (t1<t2) return 1;
  if (t1>t2) return -1;
  return 0;
}


//***********************************************
bool ModifyMenuItem (HMENU hMenu, UINT Cmd, LPCTSTR Text)
{
  HMENU hSub;
  UINT Id;
  int  i,n;

  n=::GetMenuItemCount(hMenu);
  if (n>0){
    for (i=0; i<n; i++){
      hSub=::GetSubMenu(hMenu,i);
      if (hSub){
        if (ModifyMenuItem( hSub, Cmd, Text )){
          return true;
        }
      }else{
        Id=::GetMenuItemID(hMenu,i);
        if (Id==Cmd){
          ::ModifyMenu( hMenu, i, MF_BYPOSITION, Cmd, Text );
          return true;
        }
      }
    }
  }
  return false;
}

