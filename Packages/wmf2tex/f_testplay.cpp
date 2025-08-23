#include "wmf2tex.h"
#pragma hdrstop

#include "f_testplay.h"
#include "wmfeps_utils_RealMeta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

#include <pshpack2.h>
typedef struct
{ DWORD		dwKey;
  WORD		hmf;
  SMALL_RECT    bbox;
  WORD		wInch;
  DWORD		dwReserved;
  WORD		wCheckSum;
} TAldusHeader;
#include <poppack.h>


void __fastcall TForm2::Button1Click(TObject *Sender)
{ char *fn="d:/meta/ms/emfdco/bird.wmf";
  HANDLE hFile = CreateFile(fn,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
  if (hFile==INVALID_HANDLE_VALUE) return;
  DWORD size=GetFileSize(hFile,NULL);
  LPBYTE pbits=(LPBYTE)malloc(size);
  ReadFile(hFile,pbits,size,&size,NULL);
  CloseHandle(hFile);
  TAldusHeader *apmh=(TAldusHeader*)pbits;
  if(apmh->dwKey!=0x9ac6cdd7l) {free(pbits); return;}
  int spm=sizeof(TAldusHeader);
  HMETAFILE FWmf=SetMetaFileBitsEx(size-spm,pbits+spm);
  if (FWmf==NULL) {free(pbits);return;}
  free(pbits);
  // Ok, its a placeable metafile.
  HDC hdc=GetDC(NULL);
  SetMapMode(hdc,MM_ANISOTROPIC);
  SetWindowExtEx(hdc,800,800,NULL);
  SetViewportExtEx(hdc,800,800,NULL);
  RECT rc; rc.left=0; rc.top=0; rc.right=500; rc.bottom=500;
  MoveToEx(hdc,rc.left,rc.top,NULL);
  LineTo(hdc,rc.right,rc.bottom);
  PlayMetaFile(hdc,FWmf);
  ReleaseDC(NULL,hdc);
  DeleteMetaFile(FWmf);
}
//---------------------------------------------------------------------------
