/********************************************************************
* Project: VeCAD ver.5.1
* Copyright (C) 1999-2000 by Oleg Kolbaskin.
* All rights reserved.
*
* Application Configuraion
********************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

#ifndef _WINDOWS_
  #include <windows.h>
#endif
#ifndef _INC_STDIO
  #include <stdio.h>
#endif

#define MAX_CFGITEM  1000


//-------------------------------------
class CConfigItem {
  TCHAR* szKey;
  TCHAR* szValue;
public:
    CConfigItem ();
    ~CConfigItem ();

  void Set      (LPCTSTR _szKey, LPCTSTR _szValue);
  void Get      (LPTSTR  _szKey, LPTSTR  _szValue) const;

  LPCTSTR GetKey   () const {return szKey;}
  LPCTSTR GetValue () const {return szValue;}

  bool GetValue (LPCTSTR _szKey, LPTSTR  _szValue) const;
  bool SetValue (LPCTSTR _szKey, LPCTSTR _szValue);

  bool Write (FILE* df);
};


//-------------------------------------
class CConfig {
  TCHAR       szFileName[256];
  CConfigItem Item[MAX_CFGITEM];
  int         ISort[MAX_CFGITEM];
  int         n_item;    
public:
    CConfig ();

  bool Open  (LPCTSTR szFileName);
  bool Close ();

  bool GetValue (LPCTSTR szKey, LPTSTR  szValue ) const;
  bool SetValue (LPCTSTR szKey, LPCTSTR szValue);

  int  CmpItems (int i1, int i2) const;
};


#endif  // CONFIG_H

