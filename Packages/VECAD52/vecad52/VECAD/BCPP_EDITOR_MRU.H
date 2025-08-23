/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* Most Recent Files (MRU)
********************************************************************/
#ifndef MRU_H
#define MRU_H

#ifndef _WINDOWS_
  #include <windows.h>
#endif
#ifndef _INC_TIME
  #include <time.h>
#endif
#ifndef CONFIG_H
  #include "bcpp_editor_config.h"
#endif

#define SZ_MRUFILENAME 256
#define MAX_MRU  11

//-------------------------------------
class CMruFile {
  TCHAR  szName[SZ_MRUFILENAME];  // file name
  time_t OpenTime;     // time when file was last opened
public:
    CMruFile();

  void    SetName (LPCTSTR szName);
  LPCTSTR GetName () const {return szName;}
  void    SetTime (int t=-1) {if (t>=0) OpenTime=t; else time( &OpenTime );} 
  time_t  GetTime () const {return OpenTime;} 
};


//-------------------------------------
class CMruList {
  CMruFile File[MAX_MRU];
  int  n_file;       // number of files in the list
public:
    CMruList ();

  void    Add  (LPCTSTR szFileName);
  LPCTSTR Get  (int Index, bool bSetTime=true);
  bool    Load (CConfig& Cfg);
  bool    Save (CConfig& Cfg);
private:
  bool UpdateMenu ();
};


#endif  // MRU_H

