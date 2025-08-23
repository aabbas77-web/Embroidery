/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* External Applications
********************************************************************/
#ifndef EXTAPP_H
#define EXTAPP_H

#ifndef _WINDOWS_
  #include <windows.h>
#endif
#ifndef CONFIG_H
  #include "bcpp_editor_config.h"
#endif


#define SZ_EXTAPPTITLE  256
#define MAX_EXTAPP      10

//-------------------------------------
class CExtApp {
  TCHAR  szTitle[SZ_EXTAPPTITLE];  // title for menu
  TCHAR  szFileName[256];         // exe file name
public:
    CExtApp();

  void    SetTitle    (LPCTSTR szTitle);
  LPCTSTR GetTitle    () const {return szTitle;}
  void    SetFileName (LPCTSTR szFileName);
  LPCTSTR GetFileName () const {return szFileName;}
};


//-------------------------------------
class CAppList {
  CExtApp App[MAX_EXTAPP];
  int     n_app;       // number of app in the list
public:
    CAppList ();

  bool    Load        (CConfig& Cfg);
  LPCTSTR GetFileName (int Index);
private:
  bool UpdateMenu ();
};

#endif  // EXTAPP_H

