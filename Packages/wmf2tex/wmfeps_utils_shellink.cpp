#include <vcl\vcl.h>
//AliSoft #include <shlobj.h>
#include "shlobj.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//

void __fastcall PACKAGE MessageLastErrorBox(AnsiString title)
{ LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),
    MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(LPTSTR)&lpMsgBuf,0,NULL);
  Application->MessageBox((LPTSTR)lpMsgBuf,title.c_str(),MB_OK);
  LocalFree(lpMsgBuf);
}


AnsiString __fastcall PACKAGE SHGetSpecialFolderLocationString(int nFolder)
{ LPITEMIDLIST pidl;
  SHGetSpecialFolderLocation(NULL,nFolder,&pidl);
  char FolderPath[MAX_PATH];
  SHGetPathFromIDList(pidl,FolderPath);
  return AnsiString(FolderPath);
}

AnsiString __fastcall PACKAGE ExtractFilePathWithoutSlash(AnsiString fn)
{ AnsiString dir=ExtractFilePath(fn);
  if (dir[dir.Length()]=='\\')
  { dir=dir.SubString(1,dir.Length()-1);
  }
  return dir;
}

AnsiString __fastcall PACKAGE ExtractFilePrefix(AnsiString fn)
{ AnsiString f=ChangeFileExt(ExtractFileName(fn),"");
  bool dig=true;
  while (dig)
  { char c=f[f.Length()];
    if (c>='0' && c<='9') dig=true; else dig=false;
    if (dig) f=f.SubString(1,f.Length()-1);
  }
  return f;
}

AnsiString __fastcall PACKAGE SuggestExt(AnsiString fn,AnsiString defext)
{ AnsiString ext=ExtractFileExt(fn);
  if (ext!="") return fn;
  return ChangeFileExt(fn,AnsiString(".")+defext);
}


AnsiString __fastcall PACKAGE GetFreeFileName(AnsiString path,AnsiString file,AnsiString ext)
{ int i=-1; AnsiString fn;
  bool FreeFile=false;
  while (!FreeFile)
  { i++;
    fn=path+"\\"+file;
    if (i>0) fn=fn+AnsiString(i);
    fn=fn+ext;
    FreeFile=!FileExists(fn);
  }
  return fn;
}

AnsiString __fastcall PACKAGE PrefixFileName(AnsiString fn,AnsiString pref)
{ AnsiString path=ExtractFilePath(fn);
  AnsiString name=ExtractFileName(fn);
  return path+pref+name;
}

AnsiString __fastcall PACKAGE ExtractFirstListedFile(AnsiString inp)
{ int len=inp.Length();
  char *cpy=new char[len+1];
  strcpy(cpy,inp.c_str());
  char *c=cpy;
  AnsiString fn="";
  if (*c=='\"')
  { fn=""; c++;
    while (*c!='\"' && *c!=0)
    { fn=fn+AnsiString(*c);
      c++;
    }
  }
  else fn=inp;
  delete[] cpy;
  return fn;
}


AnsiString __fastcall PACKAGE CheckShortcut(HWND hwnd,
                               AnsiString DestFileName, AnsiString Args,
                               AnsiString IconLocation, int IconIndex,
                               AnsiString ShortcutName,
                               int nFolder,
                               bool CreateIfNecessary,
                               IShellLink **isl)
{ CoInitialize(NULL);
  HRESULT hres;
  LPMALLOC g_pMalloc;
  SHGetMalloc(&g_pMalloc);
  LPITEMIDLIST pidl;
  SHGetSpecialFolderLocation(NULL,nFolder,&pidl);
  char FolderPath[MAX_PATH];
  SHGetPathFromIDList(pidl,FolderPath);
  WCHAR wFolderPath[MAX_PATH];
  MultiByteToWideChar(CP_ACP,0,FolderPath,-1,wFolderPath,MAX_PATH);
  //
  WCHAR wLinkPath[MAX_PATH];
  wcscpy(wLinkPath,L"");
  WCHAR wShortcutName[MAX_PATH];
  ShortcutName.WideChar(wShortcutName,MAX_PATH);
  BOOL FoundExisting=FALSE;
  // so now pidl points to the id for the special folder
  //
  // =======================================================================
  // First, we get the special folder and scan it for a file with the name ShortcutName
  LPSHELLFOLDER DesktopFolder;
  LPSHELLFOLDER DestFolder;
  hres=SHGetDesktopFolder(&DesktopFolder);
  if (SUCCEEDED(hres) && DesktopFolder!=NULL)
  { hres=DesktopFolder->BindToObject(pidl,NULL,IID_IShellFolder,(void**)&DestFolder);
    if (SUCCEEDED(hres) && DestFolder!=NULL)
    { // Here we have the destination folder. We're going to scan it.
      LPENUMIDLIST ppenumIDList;
      hres=DestFolder->EnumObjects(hwnd,SHCONTF_NONFOLDERS,&ppenumIDList);
      if (SUCCEEDED(hres) && ppenumIDList!=NULL)
      { LPITEMIDLIST pidlist[1];
        hres=ppenumIDList->Next(1,pidlist,NULL);
        while (hres==NOERROR)
        { STRRET str;
          hres=DestFolder->GetDisplayNameOf(pidlist[0],SHGDN_INFOLDER,&str);
          if (SUCCEEDED(hres))
          { WCHAR c[200]; wcscpy(c,L"");
            switch (str.uType)
            { case STRRET_CSTR: MultiByteToWideChar(CP_ACP,0,str.cStr, -1,c,200); break;
              case STRRET_OFFSET: {char *d=(char *)pidlist[0];MultiByteToWideChar(CP_ACP,0,d+str.uOffset,-1,c,200);} break;
              case STRRET_WSTR: wcscpy(c,str.pOleStr); break;
            }
            if (wcscmp(c,wShortcutName)==0)
            { hres=DestFolder->GetDisplayNameOf(pidlist[0],SHGDN_FORPARSING,&str);
              if (SUCCEEDED(hres))
              { switch (str.uType)
                { case STRRET_CSTR: MultiByteToWideChar(CP_ACP,0,str.cStr,-1,wLinkPath,MAX_PATH); break;
                  case STRRET_OFFSET: {char *d=(char *)pidlist[0];MultiByteToWideChar(CP_ACP,0,d+str.uOffset,-1,wLinkPath,MAX_PATH);} break;
                  case STRRET_WSTR: wcscpy(wLinkPath,str.pOleStr); break;
                }
                if (wcscmp(wLinkPath,L"")!=0) FoundExisting=TRUE;
              }
            }
            g_pMalloc->Free(pidlist[0]);
            hres=ppenumIDList->Next(1,pidlist,NULL);
          }
        }
        ppenumIDList->Release();
      }
      DestFolder->Release();
    }
    DesktopFolder->Release();
  }
  g_pMalloc->Free(pidl);
  g_pMalloc->Release();
  //
  // ==========================================================================
  // If the thing is already there, we can simply return it. In wLinkPath.
  if (FoundExisting)
  { IShellLink* psl;
    hres=CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,IID_IShellLink,(LPVOID*)&psl);
    if (SUCCEEDED(hres) && psl!=NULL)
    { IPersistFile* ppf;
      hres=psl->QueryInterface(IID_IPersistFile,(LPVOID*)&ppf);
      if (SUCCEEDED(hres) && ppf!=NULL)
      { hres=ppf->Load(wLinkPath,STGM_DIRECT|STGM_READ|STGM_SHARE_DENY_WRITE);
        if (SUCCEEDED(hres))
        { ppf->Release();
          if (isl==NULL) psl->Release(); else *isl=psl;
          CoUninitialize();
          return AnsiString(wLinkPath);
        }
        CoUninitialize();
        throw new Exception("Error loading the existing IShellLink");
      }
      psl->Release();
      CoUninitialize();
      throw new Exception("Couldn't get a persist-file interface to the IShellLink for existing file");
    }
    DWORD err=GetLastError();
    char c[300],d[500];
    wsprintf(c,"Couldn't get IShellLink to existing file. hres=%lx %lu. psl=%lx. ",hres,hres,psl);
    LPVOID lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL,err,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL);
    strcpy(d,(char*)lpMsgBuf);
    LocalFree( lpMsgBuf );
    CoUninitialize();
    throw new Exception(AnsiString(c)+": "+AnsiString(d));
  }
  //
  if (!CreateIfNecessary) {CoUninitialize(); return NULL;}
  // ==========================================================================
  // Otherwise, we're going to create it.
  wcscpy(wLinkPath,wFolderPath);
  WCHAR wc[MAX_PATH]; ShortcutName.WideChar(wc,MAX_PATH);
  wcscat(wLinkPath,L"\\");
  wcscat(wLinkPath,wc);
  wcscat(wLinkPath,L".lnk");
  AnsiString WorkingDirectory="";
  if (DestFileName!="")
  { int i=DestFileName.LastDelimiter("\\");
    if (i!=0 && i!=-1)
    { WorkingDirectory=DestFileName; WorkingDirectory.SetLength(i-1); }
  }
  //
  IShellLink* psl;
  hres=CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,IID_IShellLink,(LPVOID*)&psl);
  if (!SUCCEEDED(hres) || psl==NULL)
  { CoUninitialize();
    throw new Exception("Unable to create shortcut file");
  }
  if (DestFileName!="") psl->SetPath(DestFileName.c_str());
  psl->SetDescription("");
  if (Args!="") psl->SetArguments(Args.c_str());
  if (IconLocation!="") psl->SetIconLocation(IconLocation.c_str(),IconIndex);
  if (WorkingDirectory!="") psl->SetWorkingDirectory(WorkingDirectory.c_str());
  //
  IPersistFile* ppf;
  hres=psl->QueryInterface(IID_IPersistFile,(LPVOID*)&ppf);
  if (!SUCCEEDED(hres) || ppf==NULL)
  { psl->Release();
    CoUninitialize();
    throw new Exception("Unable to get IPersistFile interface on shortcut just created");
  }
  ppf->Save(wLinkPath, FALSE);
  ppf->Release();
  if (isl==NULL) psl->Release(); else *isl=psl;
  CoUninitialize();
  return AnsiString(wLinkPath);
}

