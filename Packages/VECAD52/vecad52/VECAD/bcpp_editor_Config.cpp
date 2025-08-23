/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* Application Configuraion
********************************************************************/
#include <windows.h>
#include <tchar.h>
#include "bcpp_editor_config.h"

const CConfig* __pCfg = NULL;

int _cdecl CmpCfgItem (const void* e1, const void* e2);

//-------------------------------------
CConfigItem::CConfigItem ()
{
  szKey = NULL;
  szValue = NULL;
}


//-------------------------------------
CConfigItem::~CConfigItem ()
{
  delete[] szKey;
  delete[] szValue;
  szKey = NULL;
  szValue = NULL;
}


//-------------------------------------
void CConfigItem::Set (LPCTSTR _szKey, LPCTSTR _szValue)
{
  int len;

  len = _tcslen( _szKey );
  delete[] szKey;
  szKey = new TCHAR[len+1];
  ::ZeroMemory( szKey, len+1 );
  _tcscpy( szKey, _szKey );

  len = _tcslen( _szValue );
  delete[] szValue;
  szValue = new TCHAR[len+1];
  ::ZeroMemory( szValue, len+1 );
  _tcscpy( szValue, _szValue );
}


//-------------------------------------
void CConfigItem::Get (LPTSTR _szKey, LPTSTR _szValue) const
{
  _tcscpy( _szKey, szKey );
  _tcscpy( _szValue, szValue );
}


//-------------------------------------
bool CConfigItem::GetValue (LPCTSTR _szKey, LPTSTR _szValue) const
{
  if (szKey && szValue){
    if (_tcsicmp( szKey, _szKey )==0){
      _tcscpy( _szValue, szValue );
      return true;
    }
  }
  _szValue[0] = 0;
  return false;
}


//-------------------------------------
bool CConfigItem::SetValue (LPCTSTR _szKey, LPCTSTR _szValue)
{
  if (szKey && szValue){
    if (_tcsicmp( szKey, _szKey )==0){
      int len = _tcslen( _szValue );
      delete[] szValue;
      szValue = new TCHAR[len+1];
      ::ZeroMemory( szValue, len+1 );
      _tcscpy( szValue, _szValue );
      return true;
    }
  }
  return false;
}


//-------------------------------------
bool CConfigItem::Write (FILE* df)
{
  if (szKey && szValue){
    _ftprintf( df, _T("%s=%s\n"), szKey, szValue ); 
    return true;
  }
  return false;
}







//*******************************************************************
CConfig::CConfig ()
{
  ::ZeroMemory( szFileName, sizeof(szFileName) );
  n_item = 0;
  for (int i=0; i<MAX_CFGITEM; i++){
    ISort[i] = i;
  }
}


//-------------------------------------
bool CConfig::Open  (LPCTSTR szFName)
{
  TCHAR  szBuf[320];
  TCHAR* pd;
  _TINT divider = '=';
  _TINT endstr = '\n';
  _tcscpy( szFileName, szFName);
  n_item = 0;
  FILE* df = _tfopen( szFileName, _T("rt") );
  if (df){
    while (1){
      szBuf[0] = 0;
      if (_fgetts( szBuf, 310, df )==NULL){
        break;
      }
      pd = _tcschr( szBuf, endstr );
      pd[0] = 0;
      pd = _tcschr( szBuf, divider );
      if (pd){
        pd[0] = 0;
        Item[n_item].Set( szBuf, pd+1 );
        n_item++;
        if (n_item>=MAX_CFGITEM){
          break;
        }
      }
    }
    fclose( df );
    return true;
  }   
  return false;
}


//-------------------------------------
bool CConfig::Close ()
{
  FILE* df = _tfopen( szFileName, _T("wt") );
  if (df){
    __pCfg = this;
    qsort( ISort, n_item, sizeof(int), CmpCfgItem );
    __pCfg = NULL;
    int i,j;
    for (i=0; i<n_item; i++){
      j = ISort[i];
      Item[j].Write( df );
    }
    fclose( df );
    return true;
  }
  return false;
}


//-------------------------------------
bool CConfig::GetValue (LPCTSTR szKey, LPTSTR szValue) const
{
  for (int i=0; i<n_item; i++){
    if (Item[i].GetValue( szKey, szValue )){
      return true;
    }
  }
  return false;  // key not found
}


//-------------------------------------
bool CConfig::SetValue (LPCTSTR szKey, LPCTSTR szValue)
{
  int i;
  for (i=0; i<n_item; i++){
    if (Item[i].SetValue( szKey, szValue )){
      return true;
    }
  }
  // key not found, create it
  if (n_item<MAX_CFGITEM){
    i = n_item++;
    Item[i].Set( szKey, szValue );
    return true;  // added new key
  }
  return false; 
}


//-------------------------------------
int CConfig::CmpItems (int i1, int i2) const
{
  return _tcsicmp( Item[i1].GetKey(), Item[i2].GetKey() );
}



//***********************************************
int _cdecl CmpCfgItem (const void* e1, const void* e2)
{
  int i1 = *(int*)e1;
  int i2 = *(int*)e2;
  return __pCfg->CmpItems( i1, i2 );
}
   
