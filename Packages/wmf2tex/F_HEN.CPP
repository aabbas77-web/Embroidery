#include "wmf2tex.h"
#pragma hdrstop

#include "f_hen.h"
#include "wmfeps_utils_shellink.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProc *Proc;

//---------------------------------------------------------------------------

__fastcall TProc::TProc(TComponent* Owner)
        : TForm(Owner)
{ SLStrings=NULL;
  SaveEpsPrinterName->Caption=EpsGenerator->Printers->Strings[EpsGenerator->PrinterIndex];
  bOpen->Click();
}
__fastcall TProc::~TProc()
{ if (SLStrings!=NULL) delete SLStrings;
}
void __fastcall TProc::Update()
{ double mmWidth=((double)RealMetafile->MMWidth)/100.0;
  double mmHeight=((double)RealMetafile->MMHeight)/100.0;
  AnsiString s="";
  if (RealMetafile->Enhanced) s=s+"EMF: "; else s=s+"WMF: ";
  s=s+FormatFloat("0.00mm",mmWidth)+" x "+FormatFloat("0.00mm",mmHeight);
  StatusBar->SimpleText=s;
  PaintBox->Repaint();
}
//---------------------------------------------------------------------------





bool __fastcall TProc::LoadFromWmf(TWinControl *Parent,TRealMetafile *mf,AnsiString fn)
{ return mf->LoadFromFile(fn);
}
bool __fastcall TProc::LoadFromClipboard(TWinControl *Parent,TRealMetafile *mf)
{ return mf->LoadFromClipboard();
}

bool __fastcall TProc::SaveType(TWinControl *Parent,TRealMetafile *mf,AnsiString fn,int index)
{ if (index==0) return SaveToWmf(Parent,mf,fn);
  if (index==1) return SaveToEmf(Parent,mf,fn);
  if (index==2) return SaveToEps(Parent,mf,fn);
  if (index==3) return SaveToTexWmf(Parent,mf,fn,ChangeFileExt(PrefixFileName(fn,"stripd_"),".wmf"));
  if (index==4) return SaveToTexEps(Parent,mf,fn,ChangeFileExt(fn,".eps"));
  if (index==5) return SaveToTexEpic(Parent,mf,fn);
  return false;
}

bool __fastcall TProc::SaveToClipboard(TWinControl *Parent,TRealMetafile *mf)
{ return mf->SaveToClipboard();
}
bool __fastcall TProc::SaveToWmf(TWinControl *Parent,TRealMetafile *mf,AnsiString fn)
{ mf->Enhanced=false;
  return mf->SaveToFile(fn);
}
bool __fastcall TProc::SaveToEmf(TWinControl *Parent,TRealMetafile *mf,AnsiString fn)
{ mf->Enhanced=true;
  return mf->SaveToFile(fn);
}
bool __fastcall TProc::SaveToEps(TWinControl *Parent,TRealMetafile *msrc,AnsiString fn)
{ TRealMetafile *mtemp=new TRealMetafile(this);
  StripLatexText(msrc,mtemp);
  EpsGenerator->FileName=fn;
  EpsGenerator->BeginDoc();
  mtemp->Enhanced=true; // because of bugs in EnumIntoCanvas for 16bit metafiles.
  mtemp->EnumIntoCanvas(EpsGenerator->Canvas,0,0);
  EpsGenerator->EndDoc(mtemp->BoundsLog);
  delete mtemp;
  return true;
}

// MACRO EXPANSION
// This is just a simply finite state automaton.
// The macros we expand according to the input data in TMacroData are:
// \#fn - filename without extension or path of graphics file. (But it may be passed to TMacroData as a full name)
// \#txt - any rendering instructions (eg. for boxes of text) for latex
// \#wf, \#hf - width and height in mm of the actual metafile
// \#xi, \#yi, \#wi, \#hi - position within that of the actual image after stripping, in metric measuring
// states: 0=normal, 1=got\, 2=got\#, 3=got\#f, 4=got\#t, 5=got\#tx, 6=got\#w, 7=got\#h, 8=got\#x, 9=got\#y
bool __fastcall TProc::SaveMacroToTex(TWinControl *Parent,AnsiString tfn, TStrings *src,TMacroData &md)
{ AnsiString fn=ChangeFileExt(ExtractFileName(md.fn),"");
  TStringList *dst=new TStringList();
  for (int y=0; y<src->Count; y++)
  { AnsiString s="";
    AnsiString in=src->Strings[y];
    int mode=0;
    for (int x=1; x<=in.Length(); x++)
    { char c=in[x];
      if (mode==0) {if (c=='\\') mode=1; else s=s+c;}
      else if (mode==1) {if (c=='#') mode=2; else {s=s+"\\"+c;mode=0;}}
      else if (mode==2)
      { if (c=='f') mode=3;
        else if (c=='t') mode=4;
        else if (c=='w') mode=6;
        else if (c=='h') mode=7;
        else if (c=='x') mode=8;
        else if (c=='y') mode=9;
        else {s=s+"\\#"+c; mode=0;}
      }
      else if (mode==3) {if (c=='n') {s=s+fn;mode=0;} else {s=s+"\\#f"+c;mode=0;}}
      else if (mode==4) {if (c=='x') mode=5; else {s=s+"\\#t"+c; mode=0;}}
      else if (mode==5)
      { if (c=='t') {dst->Add(s);s="";mode=0;for (int i=0;i<md.txt->Count;i++) dst->Add(md.txt->Strings[i]);}
        else {s=s+"\\#tx"+c;mode=0;}
      }
      else if (mode==6)
      { if (c=='f') {s=s+strFloat(md.wf);mode=0;}
        else if (c=='i') {s=s+strFloat(md.wi);mode=0;}
        else {s=s+"\\#w"+c;mode=0;}
      }
      else if (mode==7)
      { if (c=='f') {s=s+strFloat(md.hf);mode=0;}
        else if (c=='i') {s=s+strFloat(md.hi);mode=0;}
        else {s=s+"\\#h"+c;mode=0;}
      }
      else if (mode==8) {if (c=='i') {s=s+strFloat(md.xi);mode=0;} else {s=s+"\\#x"+c;mode=0;}}
      else if (mode==9) {if (c=='i') {s=s+strFloat(md.yi);mode=0;} else {s=s+"\\#y"+c;mode=0;}}
    }
    dst->Add(s);
  }
  dst->SaveToFile(tfn);
  delete dst;
  return true;
}

bool __fastcall TProc::SaveToTexWmf(TWinControl *Parent,TRealMetafile *msrc,AnsiString tfn,AnsiString gfn)
{ TRealMetafile *tmp=new TRealMetafile(this);
  StripLatexText(msrc,tmp);
  SaveToWmf(Parent,tmp,gfn);
  delete tmp;
  TMacroData md;
  md.fn=gfn; md.txt=SLStrings;
  if (SLFileDimensions.cx<0.1) SLFileDimensions.cx=0.1;
  if (SLFileDimensions.cy<0.1) SLFileDimensions.cy=0.1;
  // because dviwin crashes with an image of natwidth=0.08mm
  md.wf=SLFileDimensions.cx; md.hf=SLFileDimensions.cy;
  md.xi=SLImageOffset.x; md.yi=SLImageOffset.y;
  md.wi=SLImageSize.cx; md.hi=SLImageSize.cy;
  TStringList *src=new TStringList(); src->Text=TexWmfSource->Lines->Text; // because it wasn't registering 'Count' properly otherwise
  bool res=SaveMacroToTex(Parent,tfn,src,md);
  delete src;
  return res;
}
bool __fastcall TProc::SaveToTexEps(TWinControl *Parent,TRealMetafile *mf,AnsiString tfn,AnsiString gfn)
{ Application->MessageBox(tfn.c_str(),"Saving to tex/eps",MB_OK);
  return false;
}
bool __fastcall TProc::SaveToTexEpic(TWinControl *Parent,TRealMetafile *mf,AnsiString fn)
{ Application->MessageBox(fn.c_str(),"Saving to tex/epic",MB_OK);
  return false;
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

bool __fastcall TProc::MetafileToText(TRealMetafile *src,TStrings *dst)
{ EnumToText->Assign(src);
  MTTStrings=dst;
  dst->BeginUpdate();
  dst->Clear();
  EnumToText->Enum();
  dst->EndUpdate();
  EnumToText->Clear();
  return true;
}
void __fastcall TProc::EnumToTextEmr(TRealMetafile *Sender,const ENHMETARECORD *rec, TEnumAction &Action)
{ MTTStrings->Add(EnumToText->RecordString);
}
void __fastcall TProc::EnumToTextWmr(TRealMetafile *Sender,const METARECORD *rec, TEnumAction &Action)
{ MTTStrings->Add(EnumToText->RecordString);
}

bool __fastcall TProc::StripLatexText(TRealMetafile *src,TRealMetafile *dst)
{ if (SLStrings!=NULL) delete SLStrings;
  SLStrings=new TStringList();
  SLLatexIsSelectedFont=false;
  SLMode=0;
  SLCurrentString=""; SLHaveStartedString=false;
  SLCurrentPoint.x=0; SLCurrentPoint.y=0; SLHashPoint=SLCurrentPoint;
  SLHoriz=0, SLVert=5;
  SLViewportOrg.x=0; SLViewportOrg.y=0;
  SLViewportExt.cx=0; SLViewportExt.cy=0;
  //
  // First we enum it in enhanced mode. This will give use the latex text
  // and the smaller bounding box.
  RECTL rcBefore, rcAfter;
  EnumGetLatex->Assign(src);
  EnumGetLatex->Enhanced=true;
  if (EnumGetLatex->EnhMetafile==NULL)
  { rcBefore.left=0; rcBefore.top=0; rcBefore.right=src->MMWidth; rcBefore.bottom=src->MMHeight;
    rcAfter=rcBefore;
  }
  else
  {
  SLTexExt.cx=((double)src->MMWidth)/100.0; SLTexExt.cy=((double)src->MMHeight)/100.0;
  ENHMETAHEADER emh; ZeroMemory(&emh,sizeof(emh)); GetEnhMetaFileHeader(EnumGetLatex->EnhMetafile,sizeof(emh),&emh);
  SLViewportOrg.x=emh.rclBounds.left; SLViewportOrg.y=emh.rclBounds.top;
  SLViewportExt.cx=emh.rclBounds.right-emh.rclBounds.left;
  SLViewportExt.cy=emh.rclBounds.bottom-emh.rclBounds.top;
  rcBefore=emh.rclFrame;
  EnumGetLatex->EnumToMetafile(EnumRemoveLatex,true);
  GetEnhMetaFileHeader(EnumRemoveLatex->EnhMetafile,sizeof(emh),&emh);
  rcAfter=emh.rclFrame;
  }
  int wf=rcBefore.right-rcBefore.left, wh=rcBefore.bottom-rcBefore.top;
  int xi=rcAfter.left-rcBefore.left, yi=rcBefore.bottom-rcAfter.bottom;
  int wi=rcAfter.right-rcAfter.left, hi=rcAfter.bottom-rcAfter.top;
  SLFileDimensions.cx=((double)wf)/100; SLFileDimensions.cy=((double)wh)/100;
  SLImageOffset.x=((double)xi)/100; SLImageOffset.y=((double)yi)/100;
  SLImageSize.cx=((double)wi)/100; SLImageSize.cy=((double)hi)/100;
  //
  // Then we enum it in its native mode, because that's better.
  // (Although if it was originally enhanced, then this step isn't really needed)
  EnumRemoveLatex->Assign(src);
  EnumRemoveLatex->EnumToMetafile(dst,false);
  //
  EnumGetLatex->Clear();
  EnumRemoveLatex->Clear();
  return true;
}
TEXPOINT TProc::SLScaleViewportToTex(const POINT &src)
{ int dx=src.x-SLViewportOrg.x;
  int dy=src.y-SLViewportOrg.y;
  double fx=((double)dx)/((double)SLViewportExt.cx);
  double fy=((double)dy)/((double)SLViewportExt.cy);
  double x=fx*SLTexExt.cx, y=SLTexExt.cy*(1.0-fy);
  TEXPOINT dst; dst.x=x; dst.y=y;
  return dst;
}
void __fastcall TProc::EnumGetLatexEmrExtTextOutW(TRealMetafile *Sender,
      const EMREXTTEXTOUTA *rec, TEnumAction &Action)
{ if (AnsiString(Sender->CurrentFont.lfFaceName).LowerCase().Pos("latex")==0) return;
  EMRTEXT *emr=(EMRTEXT*)&rec->emrtext;
  wchar_t *wstr=new wchar_t[emr->nChars+1];
  CopyMemory(wstr,(BYTE*)rec+emr->offString,emr->nChars*sizeof(wchar_t));
  wstr[emr->nChars]=0;
  AnsiString str=WideCharToString(wstr);
  delete[] wstr;
  POINT tl; tl.x=rec->rclBounds.left; tl.y=rec->rclBounds.top;
  POINT br; br.x=rec->rclBounds.right; br.y=rec->rclBounds.bottom;
  TEXPOINT xtl=SLScaleViewportToTex(tl);
  TEXPOINT xbr=SLScaleViewportToTex(br);
  TEXRECT xrc; xrc.left=min(xtl.x,xbr.x); xrc.top=max(xtl.y,xbr.y);
  xrc.right=max(xtl.x,xbr.x); xrc.bottom=min(xtl.y,xbr.y);
  for (int i=1; i<=str.Length(); i++) SLCharacter(str[i],xrc);
  Action=enumDiscard;
}
void __fastcall TProc::EnumRemoveLatexEmrExtTextOutA(TRealMetafile *Sender,const EMREXTTEXTOUTA *rec, TEnumAction &Action)
{ if (AnsiString(Sender->CurrentFont.lfFaceName).LowerCase().Pos("latex")!=0) Action=enumDiscard;
}
void __fastcall TProc::EnumRemoveLatexEmrExtTextOutW(TRealMetafile *Sender,const EMREXTTEXTOUTA *rec, TEnumAction &Action)
{ if (AnsiString(Sender->CurrentFont.lfFaceName).LowerCase().Pos("latex")!=0) Action=enumDiscard;
}
void __fastcall TProc::EnumRemoveLatexWmrTextOut(TRealMetafile *Sender,const METARECORD *rec, TEnumAction &Action)
{ if (AnsiString(Sender->CurrentFont.lfFaceName).LowerCase().Pos("latex")!=0) Action=enumDiscard;
}

void __fastcall TProc::SLCharacter(char ch,const TEXRECT &xrc)
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
      SLMode=0;
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
void __fastcall TProc::SLSetPoint(char ch,const TEXRECT &xrc)
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
void __fastcall TProc::SLEmitText()
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



AnsiString __fastcall TProc::strFloat(const double d)
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
AnsiString __fastcall TProc::strTexPoint(const TEXPOINT &pt) {return "("+strFloat(pt.x)+","+strFloat(pt.y)+")";}






//---------------------------------------------------------------------------

void __fastcall TProc::bOpenClick(TObject *Sender)
{ RealMetafile->LoadFromFile(OpenFileName->Text); Update();
}
//---------------------------------------------------------------------------

void __fastcall TProc::bPasteClick(TObject *Sender)
{ RealMetafile->LoadFromClipboard();
  Update();
}
//---------------------------------------------------------------------------
TStrings* __fastcall TProc::ShowText(TStrings *s)
{ TForm *f=new TForm(Application);
  f->OnClose=TextFormClose;
  TMemo *m=new TMemo(f); m->Parent=f; m->Align=alClient; m->ScrollBars=ssBoth;
  if (s!=NULL) m->Lines->Assign(s);
  f->Show();
  return m->Lines;
}
void __fastcall TProc::TextFormClose(TObject *Sender, TCloseAction &Action)
{ Action=caFree;
}

void __fastcall TProc::bStripLatexClick(TObject *Sender)
{ StripLatexText(RealMetafile,RealMetafile); Update();
  if (SLStrings->Count>0) ShowText(SLStrings);
}

//---------------------------------------------------------------------------

void __fastcall TProc::bToTextClick(TObject *Sender)
{ TStrings *s=ShowText(NULL);
  TCursor OldCursor=Screen->Cursor;
  Screen->Cursor=crHourGlass;
  MetafileToText(RealMetafile,s);
  Screen->Cursor=OldCursor;
}
//---------------------------------------------------------------------------


void __fastcall TProc::bCopyClick(TObject *Sender)
{ RealMetafile->SaveToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TProc::bSaveClick(TObject *Sender)
{ RealMetafile->Enhanced=false;
  RealMetafile->SaveToFile(SaveFileName->Text); Update();
}
void __fastcall TProc::bSaveEmfClick(TObject *Sender)
{ RealMetafile->Enhanced=true;
  RealMetafile->SaveToFile(SaveFileName->Text); Update();
}

//---------------------------------------------------------------------------

void __fastcall TProc::PaintBoxPaint(TObject *Sender)
{ if (RealMetafile->State==rmsNormal)
  { RealMetafile->StretchDraw(PaintBox->Canvas,PaintBox->ClientRect);
  }
}
//---------------------------------------------------------------------------

void __fastcall TProc::bClearClick(TObject *Sender)
{ RealMetafile->Clear(); Update();
}
//---------------------------------------------------------------------------


void __fastcall TProc::bTexWmfClick(TObject *Sender)
{ AnsiString fn=SaveAllName->Text;
  SaveToTexWmf(this,RealMetafile,fn,ChangeFileExt(fn,"_stripd.wmf"));
}
//---------------------------------------------------------------------------


void __fastcall TProc::OpenFileNameClick(TObject *Sender)
{ bOpen->Click();

}
//---------------------------------------------------------------------------
void __fastcall TProc::bSaveEpsClick(TObject *Sender)
{ SaveToEps(this,RealMetafile,SaveEpsName->Text);
}
//---------------------------------------------------------------------------

