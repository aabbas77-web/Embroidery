#ifndef __shelllink_h
#define __shelllink_h

/*
AnsiString __fastcall CheckShortcut(HWND hwndOwner,
                               AnsiString DestFileName, AnsiString Args,
                               AnsiString IconLocation, int IconIndex,
                               AnsiString ShortcutName,
                               int nFolder,
                               bool CreateIfNecessary,
                               IShellLink **ppsl);
*/

AnsiString __fastcall PACKAGE SHGetSpecialFolderLocationString(int nFolder);
AnsiString __fastcall PACKAGE ExtractFilePathWithoutSlash(AnsiString fn);
AnsiString __fastcall PACKAGE ExtractFirstListedFile(AnsiString inp);
AnsiString __fastcall PACKAGE GetFreeFileName(AnsiString path,AnsiString file,AnsiString ext);
AnsiString __fastcall PACKAGE ExtractFilePrefix(AnsiString fn);
AnsiString __fastcall PACKAGE SuggestExt(AnsiString fn,AnsiString defext);
AnsiString __fastcall PACKAGE PrefixFileName(AnsiString fn,AnsiString pref);
void __fastcall PACKAGE MessageLastErrorBox(AnsiString title);
// See the file shellink.cpp for discussion

#endif
