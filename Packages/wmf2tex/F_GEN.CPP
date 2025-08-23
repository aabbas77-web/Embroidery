#include "wmf2tex.h"
#pragma hdrstop

#include "f_gen.h"
#include "f_preview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "wmfeps_utils_EnumMeta"
#pragma link "wmfeps_utils_EpsGen"
#pragma resource "*.dfm"
TOldProc *OldProc;
//---------------------------------------------------------------------------
__fastcall TOldProc::TOldProc(TComponent* Owner)
        : TDataModule(Owner)
{ SLStrings=NULL;
}
__fastcall TOldProc::~TOldProc()
{ if (SLStrings!=NULL) delete SLStrings;
}
//---------------------------------------------------------------------------
#include <pshpack1.h>
typedef struct _PlaceableMetaHeader{
  DWORD Key;           /* Magic number (always 9AC6CDD7h) */
  WORD  Handle;        /* Metafile HANDLE number (always 0) */
  SHORT Left;          /* Left coordinate in metafile units */
  SHORT Top;           /* Top coordinate in metafile units */
  SHORT Right;         /* Right coordinate in metafile units */
  SHORT Bottom;        /* Bottom coordinate in metafile units */
  WORD  Inch;          /* Number of metafile units per inch */
  DWORD Reserved;      /* Reserved (always 0) */
  WORD  Checksum;      /* Checksum value for previous 10 WORDs */
} PLACEABLEMETAHEADER;
#include <poppack.h>
// Left, Top, Right, and Bottom contain the coordinates of the upper-left and lower-right
// corners of the image on the output device. These are measured in twips[1]. These four
// fields also correspond to the RECT structure used in Microsoft Windows and defined in
// the file WINDOWS.H.
// A twip (meaning "twentieth of a point") is the logical unit of measurement used in
// Windows Metafiles. A twip is equal to 1/1440 of an inch. Thus 720 twips equal 1/2
// inch, while 32,768 twips is 22.75 inches.

bool __fastcall TOldProc::CopyFromClipboard(TMetafile *mf)
{ mf->Assign(Clipboard());
  return true;
}
bool __fastcall TOldProc::SaveType(TWinControl *Parent,TMetafile *mf,AnsiString fn,int index)
{ if (index==0) return SaveToWmf(Parent,mf,fn);
  if (index==1) return SaveToEmf(Parent,mf,fn);
  if (index==2) return SaveToEps(Parent,mf,fn);
  if (index==3) return SaveToTexWmf(Parent,mf,fn,ChangeFileExt(fn,".wmf"));
  if (index==4) return SaveToTexEps(Parent,mf,fn,ChangeFileExt(fn,".eps"));
  if (index==5) return SaveToTexEpic(Parent,mf,fn);
  return false;
}

bool __fastcall TOldProc::SaveToWmf(TWinControl *Parent,TMetafile *mf,AnsiString fn)
{ PLACEABLEMETAHEADER aph; ZeroMemory(&aph,sizeof(aph));
  aph.Key=0x9AC6CDD7;
  aph.Handle=0;
  aph.Left=0;
  aph.Top=0;
  aph.Right=(SHORT)(mf->MMWidth*1440/2540);
  aph.Bottom=(SHORT)(mf->MMHeight*1440/2540);
  aph.Inch=1440;
  aph.Reserved=0;
  aph.Checksum=0; for (WORD *ptr=(WORD*)&aph; ptr<(WORD*)&aph.Checksum; ptr++) aph.Checksum ^= *ptr;
  //
  HDC hdc=GetDC(0);
  DWORD sz=GetWinMetaFileBits((HENHMETAFILE)mf->Handle,NULL,0,MM_ANISOTROPIC,hdc);
  BYTE *buf=new BYTE[sz];
  GetWinMetaFileBits((HENHMETAFILE)mf->Handle,sz,buf,MM_ANISOTROPIC,hdc);
  TFileStream *fs=new TFileStream(fn,fmCreate);
  fs->Write(&aph,sizeof(aph));
  fs->Write(buf,sz);
  delete fs;
  delete[] buf;
  ReleaseDC(0,hdc);
  return true;
}
bool __fastcall TOldProc::SaveToEmf(TWinControl *Parent,TMetafile *mf,AnsiString fn)
{ UINT sz=GetEnhMetaFileBits((HENHMETAFILE)mf->Handle,0,NULL);
  BYTE *buf=new BYTE[sz];
  GetEnhMetaFileBits((HENHMETAFILE)mf->Handle,sz,buf);
  TFileStream *fs=new TFileStream(fn,fmCreate);
  fs->Write(buf,sz);
  delete fs;
  delete[] buf;
  return true;
}
bool __fastcall TOldProc::SaveToTexWmf(TWinControl *Parent,TMetafile *mf,AnsiString tfn,AnsiString gfn)
{ Application->MessageBox(tfn.c_str(),"Saving to tex/wmf",MB_OK);
  return false;
}
bool __fastcall TOldProc::SaveToTexEps(TWinControl *Parent,TMetafile *mf,AnsiString tfn,AnsiString gfn)
{ Application->MessageBox(tfn.c_str(),"Saving to tex/eps",MB_OK);
  return false;
}
bool __fastcall TOldProc::SaveToTexEpic(TWinControl *Parent,TMetafile *mf,AnsiString fn)
{ Application->MessageBox(fn.c_str(),"Saving to tex/epic",MB_OK);
  return false;
}

bool __fastcall TOldProc::SaveToEps(TWinControl *Parent,TMetafile *mf,AnsiString fn)
{ /*EnumToEps->Metafile->Clear();
  PreviewForm->Visible=true;
  StripLatexText(mf,EnumToEps->Metafile);
  PreviewForm->Before->Picture->Metafile->Assign(mf);
  PreviewForm->After->Picture->Metafile->Assign(EnumToEps->Metafile);
  EpsGenerator->FileName=fn;
  EpsGenerator->BeginDoc();
  EnumToEps->EnumToCanvas(EpsGenerator->Canvas);
  EpsGenerator->EndDoc(EnumToEps->BoundsLog);
  PreviewForm->Memo->Lines->LoadFromFile(fn);
  */
  return true;
}


// Strip-Latex
// We are interested in fonts in the 'Latex Embed' truetype font.
// We'll treat it just as a long stream of characters: we won't make
// any distinction about which characters make up which word. That's because
// the information typically isn't present in a wmf file.
//         This is a string\#c in latex\#.
// The \#c means: 'center the string on the center of the #'
// The \#. at the end means: 'this is the end of a string. Render it now'
// We need the \#. at the end because, as mentioned, there is no other indication
// of where a piece of text actually ends.
//
// Figuring out text:
// Any text not in the latex font goes into epic.
// Any text that is in the latex font does not appear in the final wmf.
// Whenever we encounter a string in a latex font, it's like receiving the characters one by one
// If we're currently blank and we receive a character, we take note of its bottom-left
// as a provisional reference point and get ready for bottom-left.
// Normal characters just get added to the string.
// Whenever we encounter a \, it puts us into 'ready-command-mode' and we don't add the \slash
// Whenever we're in ready-command-mode and we encounter a non-# character, we
// add both \ and the character to the current string
// When we're in ready-command-mode and receive a #, we record the center coordinates
// of the # as our current coordinates and go into 'ready-use1-mode'
// When in ready-use-1 we encounter . we emit the string, zero it, go into normal-mode,
// and start again.
// When in ready-use-1 we encounter tmblcr we mark the mode as whatever and switch to
// ready-use-2. If any other character then we go back into normal-mode and
// interpret the character as one would.
// When in ready-use-2 we encounter tmblcr we mark the mode as whatever and switch back
// to normal-mode. Any other character, and we go back into normal-mode and then interpet
// the character as one would.

bool __fastcall TOldProc::StripLatexText(TMetafile *src,TMetafile *dst)
{ if (SLStrings!=NULL) delete SLStrings;
  SLStrings=new TStringList();
  SLLatexIsSelectedFont=false;
  SLMode=0;
  SLCurrentString=""; SLHaveStartedString=false;
  SLCurrentPoint.x=0; SLCurrentPoint.y=0; SLHashPoint=SLCurrentPoint;
  SLHoriz=0, SLVert=5;
  SLViewportOrg.x=0; SLViewportOrg.y=0;
  SLViewportExt.cx=0; SLViewportExt.cy=0;
  SLTexExt.cx=0; SLTexExt.cy=0;
  //
  //EnumStripLatex->Metafile->Handle=src->Handle; // for some reason it doesn't work when you assign it
  //EnumStripLatex->EnumToMetafile(dst);
  return true;
}
void __fastcall TOldProc::EnumStripLatexEmrHeader(TEnumMetafile *Sender,
      const ENHMETAHEADER *rec, TEmrAction &Action)
{ int l=min(rec->rclBounds.left,rec->rclBounds.right);
  int r=max(rec->rclBounds.left,rec->rclBounds.right);
  int t=min(rec->rclBounds.top,rec->rclBounds.bottom);
  int b=max(rec->rclBounds.top,rec->rclBounds.bottom);
  SLViewportOrg.x=l; SLViewportOrg.y=t;
  SLViewportExt.cx=r-t; SLViewportExt.cy=b-t;
  double w=((double)(rec->rclFrame.right-rec->rclFrame.left))/100.0;
  double h=((double)(rec->rclFrame.bottom-rec->rclFrame.top))/100.0;
  SLTexExt.cx=w; SLTexExt.cy=h;
}
TEXPOINT TOldProc::SLScaleViewportToTex(const POINT &src)
{ int dx=src.x-SLViewportOrg.x;
  int dy=src.y-SLViewportOrg.y;
  double fx=((double)dx)/((double)SLViewportExt.cx);
  double fy=((double)dy)/((double)SLViewportExt.cy);
  double x=fx*SLTexExt.cx, y=SLTexExt.cy*(1.0-fy);
  TEXPOINT dst; dst.x=x; dst.y=y;
  return dst;
}
void __fastcall TOldProc::EnumStripLatexEmrSelectObject(TEnumMetafile *Sender,
      const EMRSELECTOBJECT *rec, TEmrAction &Action)
{ HGDIOBJ h; int i=rec->ihObject;
  if (i&0x80000000) h=GetStockObject(i&0x7FFFFFFF);
  else h=(HGDIOBJ)EnumStripLatex->Handle[i];
  DWORD type=GetObjectType(h);
  if (type!=OBJ_FONT) return;
  LOGFONT lf;
  GetObject(h,sizeof(lf),&lf);
  AnsiString name=AnsiString(lf.lfFaceName);
  if (name.LowerCase().Pos("latex")!=0) SLLatexIsSelectedFont=true; else SLLatexIsSelectedFont=false;
}
void __fastcall TOldProc::EnumStripLatexEmrExtTextOutW(TEnumMetafile *Sender,
      const EMREXTTEXTOUTA *rec, TEmrAction &Action)
{ if (!SLLatexIsSelectedFont) return;
  EMRTEXT *emr=(EMRTEXT*)&rec->emrtext;
  POINT tl; tl.x=rec->rclBounds.left; tl.y=rec->rclBounds.top;
  POINT br; br.x=rec->rclBounds.right; br.y=rec->rclBounds.bottom;
  TEXPOINT xtl=SLScaleViewportToTex(tl);
  TEXPOINT xbr=SLScaleViewportToTex(br);
  TEXRECT xrc; xrc.left=min(xtl.x,xbr.x); xrc.top=max(xtl.y,xbr.y);
  xrc.right=max(xtl.x,xbr.x); xrc.bottom=min(xtl.y,xbr.y);
  AnsiString str=AnsiString((char *)rec+emr->offString);
  for (int i=1; i<=str.Length(); i++) SLCharacter(str[i],xrc);
  Action=emrDiscard;
}
void __fastcall TOldProc::SLCharacter(char ch,const TEXRECT &xrc)
{ // See instructions for figuring out text at top of page.
  AnsiString dirs="tmblcrTMBLCR";
  if (SLMode==1) { if (ch!='#') {SLCurrentString=SLCurrentString+"\\"; SLMode=0;}  }
  if (SLMode==2) { if (dirs.Pos(AnsiString(ch))==0 && ch!='.') SLMode=0; }
  if (SLMode==3) { if (dirs.Pos(AnsiString(ch))==0) SLMode=0;  }
  //
  if (SLMode==0)
  { if (!SLHaveStartedString)
    { SLCurrentPoint.x=xrc.left; SLCurrentPoint.y=xrc.bottom;
      SLHoriz=0; SLVert=5;
      SLHaveStartedString=true;
    }
    if (ch=='\\') SLMode=1;
    else SLCurrentString=SLCurrentString+AnsiString(ch);
    return;
  }
  if (SLMode==1)
  { // we assume that ch=='#', from above
    double x=(xrc.right+xrc.left)/2;
    double y=(xrc.bottom+xrc.top)/2;
    SLHashPoint.x=x; SLHashPoint.y=y;
    SLMode=2; return;
  }
  if (SLMode==2)
  { // we assume that ch is a direction or a .
    if (ch=='.')
    { SLEmitText();
      SLCurrentString=""; SLHaveStartedString=false;
      return;
    }
    else
    { SLSetPoint(ch,xrc);
      SLMode=3;
      return;
    }
  }
  if (SLMode==3)
  { // again, assume that ch is a direction
    SLSetPoint(ch,xrc);
    SLMode=0; return;
  }
}
void __fastcall TOldProc::SLSetPoint(char ch,const TEXRECT &xrc)
{ if (ch>'Z') ch=(BYTE)(ch-'a'+'A');
  switch (ch)
  { case 'L': SLCurrentPoint.x=SLHashPoint.x; SLHoriz=0; return;
    case 'C': SLCurrentPoint.x=SLHashPoint.x; SLHoriz=1; return;
    case 'R': SLCurrentPoint.x=SLHashPoint.x; SLHoriz=2; return;
    case 'T': SLCurrentPoint.y=SLHashPoint.y; SLVert=3; return;
    case 'M': SLCurrentPoint.y=SLHashPoint.y; SLVert=4; return;
    case 'B': SLCurrentPoint.y=SLHashPoint.y; SLVert=5; return;
  }
}
void __fastcall TOldProc::SLEmitText()
{ AnsiString txt=SLCurrentString;
  AnsiString s="\\put"+strTexPoint(SLCurrentPoint);
  s=s+"{";
  s=s+"\\makebox(0,0)";
  AnsiString dir="";
  switch (SLVert)
  { case 3: dir=dir+"t"; break;
    case 5: dir=dir+"b"; break;
  }
  switch (SLHoriz)
  { case 0: dir=dir+"l"; break;
    case 2: dir=dir+"r"; break;
  }
  if (dir!="") s=s+"["+dir+"]";
  s=s+"{";
  s=s+txt;
  s=s+"}";
  s=s+"}";
  SLStrings->Add(s);
}

//---------------------------------------------------------------------------



AnsiString __fastcall TOldProc::strFloat(const double d)
{ double e=d; if (e<0) e=-e;
  int i=d; if ((double)i==d) return AnsiString(i);
  if (e>=1000.0) return FormatFloat("0.0",d);
  else if (e>=100.0) return FormatFloat("0.00",d);
  else if (e>=10.0) return FormatFloat("0.000",d);
  else if (e>=1.0) return FormatFloat("0.000",d);
  else if (e>=0.0) return FormatFloat("0.0000",d);
  else if (e>=0.1) return FormatFloat("0.00000",d);
  else if (e>=0.01) return FormatFloat("0.000000",d);
  else if (e>=0.001) return FormatFloat("0.0000000",d);
  else return AnsiString(d);
}
AnsiString __fastcall TOldProc::strTexPoint(const TEXPOINT &pt) {return "("+strFloat(pt.x)+","+strFloat(pt.y)+")";}

