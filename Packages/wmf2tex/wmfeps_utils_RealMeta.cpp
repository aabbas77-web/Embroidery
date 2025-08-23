#include "wmf2tex.h"
#pragma hdrstop
#include "wmfeps_utils_RealMeta.h"
#include "wmfeps_utils_shellink.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TRealMetafile::TRealMetafile(TComponent *Owner) : TComponent(Owner)
{ FEmf=NULL; FWmf=NULL; FMMWidth=0; FMMHeight=0; FEnhanced=false; FState=rmsEmpty;
  FEmrHeader=NULL;
  FEmrPolyBezier=NULL;
  FEmrPolygon=NULL;
  FEmrPolyLine=NULL;
  FEmrPolyBezierTo=NULL;
  FEmrPolyLineTo=NULL;
  FEmrPolyPolyLine=NULL;
  FEmrPolyPolygon=NULL;
  FEmrSetWindowExtEx=NULL;
  FEmrSetWindowOrgEx=NULL;
  FEmrSetViewportExtEx=NULL;
  FEmrSetViewportOrgEx=NULL;
  FEmrSetBrushorgEx=NULL;
  FEmrEof=NULL;
  FEmrSetPixelv=NULL;
  FEmrSetMapperFlags=NULL;
  FEmrSetMapMode=NULL;
  FEmrSetBkMode=NULL;
  FEmrSetPolyFillMode=NULL;
  FEmrSetRop2=NULL;
  FEmrSetStretchBltMode=NULL;
  FEmrSetTextAlign=NULL;
  FEmrSetColorAdjustment=NULL;
  FEmrSetTextColor=NULL;
  FEmrSetBkColor=NULL;
  FEmrOffsetClipRgn=NULL;
  FEmrMoveToEx=NULL;
  FEmrSetMetaRgn=NULL;
  FEmrExcludeClipRect=NULL;
  FEmrIntersectClipRect=NULL;
  FEmrScaleViewportExtEx=NULL;
  FEmrScaleWindowExtEx=NULL;
  FEmrSaveDC=NULL;
  FEmrRestoreDC=NULL;
  FEmrSetWorldTransform=NULL;
  FEmrModifyWorldTransform=NULL;
  FEmrSelectObject=NULL;
  FEmrCreatePen=NULL;
  FEmrCreateBrushIndirect=NULL;
  FEmrDeleteObject=NULL;
  FEmrAngleArc=NULL;
  FEmrEllipse=NULL;
  FEmrRectangle=NULL;
  FEmrRoundRect=NULL;
  FEmrArc=NULL;
  FEmrChord=NULL;
  FEmrPie=NULL;
  FEmrSelectPalette=NULL;
  FEmrCreatePalette=NULL;
  FEmrSetPaletteEntries=NULL;
  FEmrResizePalette=NULL;
  FEmrRealizePalette=NULL;
  FEmrExtFloodFill=NULL;
  FEmrLineTo=NULL;
  FEmrArcTo=NULL;
  FEmrPolyDraw=NULL;
  FEmrSetArcDirection=NULL;
  FEmrSetMiterLimit=NULL;
  FEmrBeginPath=NULL;
  FEmrEndPath=NULL;
  FEmrCloseFigure=NULL;
  FEmrFillPath=NULL;
  FEmrStrokeAndFillpath=NULL;
  FEmrStrokePath=NULL;
  FEmrFlattenPath=NULL;
  FEmrWidenPath=NULL;
  FEmrSelectClipPath=NULL;
  FEmrAbortPath=NULL;
  FEmrGdiComment=NULL;
  FEmrFillRgn=NULL;
  FEmrFrameRgn=NULL;
  FEmrInvertRgn=NULL;
  FEmrPaintRgn=NULL;
  FEmrExtSelectClipRgn=NULL;
  FEmrBitBlt=NULL;
  FEmrStretchBlt=NULL;
  FEmrMaskBlt=NULL;
  FEmrPlgBlt=NULL;
  FEmrSetDIBitsToDevice=NULL;
  FEmrStretchDIBits=NULL;
  FEmrExtCreateFontIndirectW=NULL;
  FEmrExtTextOutA=NULL;
  FEmrExtTextOutW=NULL;
  FEmrPolyBezier16=NULL;
  FEmrPolygon16=NULL;
  FEmrPolyLine16=NULL;
  FEmrPolyBezierTo16=NULL;
  FEmrPolyLineTo16=NULL;
  FEmrPolyPolyLine16=NULL;
  FEmrPolyPolygon16=NULL;
  FEmrPolyDraw16=NULL;
  FEmrCreateMonoBrush=NULL;
  FEmrCreateDIBPatternBrushPt=NULL;
  FEmrExtCreatePen=NULL;
  FEmrPolyTextOutA=NULL;
  FEmrPolyTextOutW=NULL;
  FEmrSetICMMode=NULL;
  FEmrCreateColorSpace=NULL;
  FEmrSetColorSpace=NULL;
  FEmrDeleteColorSpace=NULL;
  FEmrGLSRecord=NULL;
  FEmrGLSBoundedRecord=NULL;
  FEmrPixelFormat=NULL;
  //
  FWmrSetBkColor=NULL;
  FWmrSetBkMode=NULL;
  FWmrSetMapMode=NULL;
  FWmrSetRop2=NULL;
  FWmrSetRelabs=NULL;
  FWmrSetPolyFillMode=NULL;
  FWmrSetStretchBltMode=NULL;
  FWmrSetTextCharExtra=NULL;
  FWmrSetTextColor=NULL;
  FWmrSetTextJustification=NULL;
  FWmrSetWindowOrg=NULL;
  FWmrSetWindowExt=NULL;
  FWmrSetViewportOrg=NULL;
  FWmrSetViewportExt=NULL;
  FWmrOffSetWindowOrg=NULL;
  FWmrScaleWindowExt=NULL;
  FWmrOffSetViewportOrg=NULL;
  FWmrScaleViewportExt=NULL;
  FWmrLineTo=NULL;
  FWmrMoveTo=NULL;
  FWmrExcludeClipRect=NULL;
  FWmrIntersectClipRect=NULL;
  FWmrArc=NULL;
  FWmrEllipse=NULL;
  FWmrFloodFill=NULL;
  FWmrPie=NULL;
  FWmrRectangle=NULL;
  FWmrRoundRect=NULL;
  FWmrPatBlt=NULL;
  FWmrSaveDC=NULL;
  FWmrSetPixel=NULL;
  FWmrOffSetClipRgn=NULL;
  FWmrTextOut=NULL;
  FWmrBitBlt=NULL;
  FWmrStretchBlt=NULL;
  FWmrPolygon=NULL;
  FWmrPolyLine=NULL;
  FWmrEscape=NULL;
  FWmrResToReDC=NULL;
  FWmrFillRegion=NULL;
  FWmrFrameRegion=NULL;
  FWmrInvertRegion=NULL;
  FWmrPaintRegion=NULL;
  FWmrSelectClipRegion=NULL;
  FWmrSelectObject=NULL;
  FWmrSetTextAlign=NULL;
  FWmrChord=NULL;
  FWmrSetMapperFlags=NULL;
  FWmrExtTextOut=NULL;
  FWmrSetDIBToDev=NULL;
  FWmrSelectPalette=NULL;
  FWmrRealizePalette=NULL;
  FWmrAnimatePalette=NULL;
  FWmrSetPalEntries=NULL;
  FWmrPolyPolygon=NULL;
  FWmrResizePalette=NULL;
  FWmrDIBBitBlt=NULL;
  FWmrDIBStretchBlt=NULL;
  FWmrDIBCreatePatternBrush=NULL;
  FWmrStretchDIB=NULL;
  FWmrExtFloodFill=NULL;
  FWmrDeleteObject=NULL;
  FWmrCreatePalette=NULL;
  FWmrCreatePatternBrush=NULL;
  FWmrCreatePenIndirect=NULL;
  FWmrCreateFontIndirect=NULL;
  FWmrCreateBrushIndirect=NULL;
  FWmrCreateRegion=NULL;
  //
  FWmr=NULL;
}
__fastcall TRealMetafile::~TRealMetafile()
{ Clear();
}
void __fastcall TRealMetafile::Assign(TPersistent *Source)
{ Clear();
  TRealMetafile *rm=dynamic_cast<TRealMetafile*>(Source);
  if (rm!=NULL)
  { if (rm->Enhanced) FEmf=CopyEnhMetaFile(rm->FEmf,NULL);
    else FWmf=CopyMetaFile(rm->FWmf,NULL);
    FEnhanced=rm->FEnhanced;
    FState=rmsNormal;
    FMMWidth=rm->FMMWidth;
    FMMHeight=rm->FMMHeight;
    return;
  }
  TMetafile *m=dynamic_cast<TMetafile*>(Source);
  if (m!=NULL)
  { FEmf=CopyEnhMetaFile((HENHMETAFILE)m->Handle,NULL);
    FEnhanced=true;
    FState=rmsNormal;
    ENHMETAHEADER emh; GetEnhMetaFileHeader(FEmf,sizeof(emh),&emh);
    FMMWidth=emh.rclFrame.right-emh.rclFrame.left;
    FMMHeight=emh.rclFrame.bottom-emh.rclFrame.top;
    return;
  }
}
void __fastcall TRealMetafile::Clear()
{ if (FEmf!=NULL) DeleteEnhMetaFile(FEmf); FEmf=NULL;
  if (FWmf!=NULL) DeleteMetaFile(FWmf); FWmf=NULL;
  FState=rmsEmpty;
}

HENHMETAFILE __fastcall TRealMetafile::GetEnhMetafile()
{ if (!Enhanced) return NULL; // in case it couldn't convert
  return FEmf;
}
HMETAFILE __fastcall TRealMetafile::GetWinMetafile()
{ if (FEnhanced) return NULL;
  return FWmf;
}
int __fastcall TRealMetafile::GetMMWidth()
{ return FMMWidth;
}
int __fastcall TRealMetafile::GetMMHeight()
{ return FMMHeight;
}
void __fastcall TRealMetafile::SetMMWidth(int w)
{ if (State!=rmsNormal) return;
  if (Enhanced) return;
  if (FMMWidth==w) return;
  FMMWidth=w;
}
void __fastcall TRealMetafile::SetMMHeight(int h)
{ if (State!=rmsNormal) return;
  if (Enhanced) return;
  if (FMMHeight==h) return;
  FMMHeight=h;
}
bool __fastcall TRealMetafile::GetEnhanced()
{ return FEnhanced;
}
void __fastcall TRealMetafile::SetEnhanced(bool b)
{ if (State!=rmsNormal) return;
  if (FEnhanced==b) return;
  if (FEnhanced)
  { // convert to wmf
    HDC hdcScreen=GetDC(NULL);
    int size=GetWinMetaFileBits(FEmf,0,NULL,MM_ANISOTROPIC,hdcScreen);
    LPBYTE pbits=(LPBYTE)malloc(size);
    GetWinMetaFileBits(FEmf,size,pbits,MM_ANISOTROPIC,hdcScreen);
    ReleaseDC(NULL,hdcScreen);
    DeleteEnhMetaFile(FEmf); FEmf=NULL;
    FWmf=SetMetaFileBitsEx(size,pbits);
    free(pbits);
    FEnhanced=false;
  }
  else
  { // convert to emf
    int size=GetMetaFileBitsEx(FWmf,0,NULL);
    LPBYTE pbits=(LPBYTE)malloc(size);
    GetMetaFileBitsEx(FWmf,size,pbits);
    DeleteMetaFile(FWmf); FWmf=NULL;
    HDC hdcScreen=GetDC(NULL);
    METAFILEPICT mfp; mfp.mm=MM_ANISOTROPIC; mfp.xExt=FMMWidth; mfp.yExt=FMMHeight; mfp.hMF=NULL;
    FEmf=SetWinMetaFileBits(size,pbits,hdcScreen,&mfp);
    //if (FEmf==NULL) MessageLastErrorBox("Wmf->Emf error");
    ReleaseDC(NULL,hdcScreen);
    FEnhanced=true;
  }
}
AnsiString __fastcall TRealMetafile::GetStatus()
{ AnsiString s="";
  if (State==rmsNormal)
  { if (Enhanced) s=s+"EMF: "; else s=s+"WMF: ";
    double mmWidth=((double)FMMWidth)/100.0;
    double mmHeight=((double)FMMHeight)/100.0;
    s=s+FormatFloat("0.00",mmWidth);
    s=s+"mm x ";
    s=s+FormatFloat("0.00",mmHeight);
    s=s+"mm";
  }
  return s;
}


bool __fastcall TRealMetafile::LoadFromFile(AnsiString fn)
{ bool res=false;
  TStream *stream=new TFileStream(fn,fmOpenRead);
  try
  { res=LoadFromStream(stream);
  }
  catch (...)
  {
  }
  delete stream;
  return res;
}
bool __fastcall TRealMetafile::LoadFromStream(TStream *s)
{ Clear();
  //
  bool IsEnhMetafile=false;
  bool IsWinMetafile=false; int WmfLength=s->Size-s->Position;
  int StreamSize=s->Size-s->Position;
  if (StreamSize>sizeof(ENHMETAHEADER))
  { ENHMETAHEADER emh;
    s->Read(&emh,sizeof(emh));
    s->Seek(sizeof(emh)*-1,soFromCurrent);
    if (emh.iType==EMR_HEADER && emh.dSignature==ENHMETA_SIGNATURE) IsEnhMetafile=true;
  }
  if (StreamSize>sizeof(APMHEADER))
  { APMHEADER apmh;
    s->Read(&apmh,sizeof(apmh));
    s->Seek(sizeof(apmh)*-1,soFromCurrent);
    if (apmh.dwKey==0x9ac6cdd7l) IsWinMetafile=true;
  }
  //
  if (IsEnhMetafile)
  { ENHMETAHEADER emh;
    s->ReadBuffer(&emh,sizeof(emh));
    LPBYTE pbits=(LPBYTE)malloc(emh.nBytes);
    MoveMemory(pbits,&emh,sizeof(emh));
    s->ReadBuffer(pbits+sizeof(emh),emh.nBytes-sizeof(emh));
    FEmf=SetEnhMetaFileBits(emh.nBytes,pbits);
//AliSoft 14/09/2002
    free(pbits);

    if (FEmf==NULL) return false;
    FMMWidth=emh.rclFrame.right-emh.rclFrame.left;
    FMMHeight=emh.rclFrame.bottom-emh.rclFrame.top; if (FMMHeight<0) FMMHeight=-FMMHeight;
    FEnhanced=true;FState=rmsNormal;return true;
  }
  //
  if (IsWinMetafile)
  { APMHEADER apmh; s->Read(&apmh,sizeof(apmh));
    DWORD size=WmfLength-sizeof(apmh);
    LPBYTE pbits=(LPBYTE)LocalAlloc(LMEM_FIXED,size);
    s->Read(pbits,size);
    FWmf=SetMetaFileBitsEx(size,pbits);
    if (FWmf==NULL) {LocalFree(pbits);return false;}
    // Ok, its a placeable metafile.
    FMMWidth=apmh.bbox.Right-apmh.bbox.Left;
    FMMWidth=(FMMWidth * 2540l ) / (DWORD)(apmh.wInch);
    FMMHeight=apmh.bbox.Bottom - apmh.bbox.Top;
    FMMHeight=(FMMHeight * 2540l ) / (DWORD)(apmh.wInch);
    LocalFree(pbits);
    FEnhanced=false;FState=rmsNormal;return true;
  }
  //
  return false;
}
bool __fastcall TRealMetafile::LoadFromClipboard()
{ Clear();
  bool res=OpenClipboard(NULL);
  if (!res) return false;
  int format=EnumClipboardFormats(0);
  while (format!=0 && format!=CF_METAFILEPICT && format!=CF_ENHMETAFILE) format=EnumClipboardFormats(format);
  if (format==0) {CloseClipboard();return false;}
  if (format==CF_METAFILEPICT)
  { METAFILEPICT *mfp=(METAFILEPICT*)GetClipboardData(CF_METAFILEPICT);
    FWmf=CopyMetaFile(mfp->hMF,NULL);
    CloseClipboard();
    if (FWmf==NULL) return false;
    double x=(double)mfp->xExt;
    double y=(double)mfp->yExt;
    switch (mfp->mm)
    { case MM_HIENGLISH: FMMWidth=(int)floor(x*2.54+0.5); FMMHeight=(int)floor(y*2.54+0.5); break;
      case MM_HIMETRIC:  FMMWidth=(int)floor(x+0.5); FMMHeight=(int)floor(y+0.5); break;
      case MM_LOENGLISH: FMMWidth=(int)floor(x*25.4+0.5); FMMHeight=(int)floor(y*25.4+0.5); break;
      case MM_LOMETRIC:  FMMWidth=(int)floor(x+10+0.5); FMMHeight=(int)floor(y*10+0.5); break;
      case MM_TWIPS:     FMMWidth=(int)floor(x*2540/1440+0.5); FMMHeight=(int)floor(y*2540/1440+0.5); break;
      case MM_TEXT: // we assume these are display-sized pixels
      { HDC hdcScreen=GetDC(NULL);
        double mmDeviceWidth=(double)GetDeviceCaps(hdcScreen,HORZSIZE);
        double mmDeviceHeight=(double)GetDeviceCaps(hdcScreen,VERTSIZE);
        double pixDeviceWidth=(double)GetDeviceCaps(hdcScreen,HORZRES);
        double pixDeviceHeight=(double)GetDeviceCaps(hdcScreen,VERTRES);
        FMMWidth=(int)floor(x*mmDeviceWidth/pixDeviceWidth*100+0.5);
        FMMHeight=(int)floor(y*mmDeviceHeight/pixDeviceHeight*100+0.5);
        ReleaseDC(NULL,hdcScreen);
      } break;
      // The docs say that these two are in HIMETRIC. But CorelXara has them in HIENGLISH.
      // We'll use HIMETRIC.
      case MM_ANISOTROPIC:
      { if (mfp->xExt==0 && mfp->yExt==0) {FMMWidth=1000; FMMHeight=1000;}
        else {FMMWidth=mfp->xExt; FMMHeight=mfp->yExt;}
      } break;
      case MM_ISOTROPIC:
      { if (mfp->xExt>0 || mfp->yExt>0) {FMMWidth=(int)floor(x*2.54+0.5); FMMHeight=(int)floor(y*2.54+0.5);}
        else
        { int rx=mfp->xExt, ry=mfp->yExt; if (rx<0) rx=-rx; if (ry<0) ry=-ry;
          int max=rx; if (ry>max) max=ry;
          double fx=((double)rx)/((double)max);
          double fy=((double)ry)/((double)max);
          FMMWidth=(int)floor(fx*1000+0.5);
          FMMHeight=(int)floor(fy*1000+0.5);
        }
      } break;
      default: FMMWidth=1000; FMMHeight=1000;
    }
    FEnhanced=false;FState=rmsNormal;
    return true;
  }
  else
  { HENHMETAFILE hClipEmf=(HENHMETAFILE)GetClipboardData(CF_ENHMETAFILE); if (hClipEmf==NULL) {CloseClipboard();return false;}
    FEmf=CopyEnhMetaFile(hClipEmf,NULL); if (FEmf==NULL) {CloseClipboard();return false;}
    ENHMETAHEADER emh; GetEnhMetaFileHeader(FEmf,sizeof(emh),&emh);
    FMMWidth=emh.rclFrame.right-emh.rclFrame.left;
    FMMHeight=emh.rclFrame.bottom-emh.rclFrame.top; if (FMMHeight<0) FMMHeight=-FMMHeight;
    FEnhanced=true;FState=rmsNormal;
    CloseClipboard();
    return true;
  }
}
bool __fastcall TRealMetafile::SaveToFile(AnsiString fn)
{ bool res=false;
  TStream *stream=new TFileStream(fn,fmCreate);
  try
  { res=SaveToStream(stream);
  }
  catch (...)
  {
  }
  delete stream;
  return res;
}
WORD CalculateAPMCheckSum(APMHEADER apmfh)
{ LPWORD ptr=(LPWORD)&apmfh;
  WORD w=0; for (int i=0; i<10; i++) w &= ptr[i];
  return w;
}
bool __fastcall TRealMetafile::SaveToStream(TStream *s)
{ if (FState!=rmsNormal) return false;
  if (Enhanced)
  { int size=GetEnhMetaFileBits(FEmf,0,NULL);
    LPBYTE pbits=(LPBYTE)malloc(size);
    GetEnhMetaFileBits(FEmf,size,pbits);
    s->WriteBuffer(pbits,size);
    free(pbits);
    return true;
  }
  else
  { APMHEADER apmh; ZeroMemory(&apmh,sizeof(apmh));
    apmh.dwKey = 0x9ac6cdd7l;
    apmh.hmf = 0;
    apmh.wInch = 1440;
    apmh.bbox.Top = 0;
    apmh.bbox.Left = 0;
    apmh.bbox.Right = (SHORT)(1440*FMMWidth/2540);
    apmh.bbox.Bottom = (SHORT)(1440*FMMHeight/2540);
    apmh.dwReserved = 0;
    apmh.wCheckSum = CalculateAPMCheckSum(apmh);
    //
    int size=GetMetaFileBitsEx(FWmf,0,NULL);
    LPBYTE pbits=(LPBYTE)malloc(size);
    GetMetaFileBitsEx(FWmf,size,pbits);
    s->WriteBuffer(&apmh,sizeof(apmh));
    s->WriteBuffer(pbits,size);
    free(pbits);
    return true;
  }
}
bool __fastcall TRealMetafile::SaveToClipboard()
{ if (State!=rmsNormal) return false;
  OpenClipboard(NULL);
  EmptyClipboard();
  if (Enhanced) SetClipboardData(CF_ENHMETAFILE,CopyEnhMetaFile(FEmf,NULL));
  else
  { METAFILEPICT mfp; mfp.mm=MM_ANISOTROPIC;
    // We'll use MM_HIMETRIC, like the docs say
    mfp.xExt=FMMWidth; mfp.yExt=FMMHeight;
    mfp.hMF=CopyMetaFile(FWmf,NULL);
    HGLOBAL hGlob=GlobalAlloc(GMEM_DDESHARE,sizeof(mfp)); if (hGlob==NULL) {CloseClipboard();return false;}
    LPBYTE ptr=(LPBYTE)GlobalLock(hGlob);
    CopyMemory(ptr,&mfp,sizeof(mfp));
    GlobalUnlock(hGlob);
    SetClipboardData(CF_METAFILEPICT,hGlob);
  }
  CloseClipboard();
  return true;
}


int CALLBACK EnumMetaFileCallback(HDC hdc,HANDLETABLE *HTable, METARECORD *rec,int nObj,LPARAM data)
{ void *vdata=(void*)data;
  TMetafileCallback *mc=(TMetafileCallback*)vdata;
  return (*mc)(hdc,HTable,rec,nObj);
}
int CALLBACK EnumEnhMetaFileCallback(HDC hdc,HANDLETABLE *HTable,const ENHMETARECORD *rec,int nObj,LPARAM data)
{ void *vdata=(void*)data;
  TEnhMetafileCallback *mc=(TEnhMetafileCallback*)vdata;
  return (*mc)(hdc,HTable,rec,nObj);
}

void __fastcall TRealMetafile::Draw(TCanvas *cdest,int x,int y)
{ if (State!=rmsNormal) return;
  if (!Enhanced)
  { // We worry about the viewport
    HDC hdc=cdest->Handle;
    POINT tl; tl.x=x; tl.y=y; LPtoDP(hdc,&tl,1); // tl now has device coordinates for top left
    double mmImageWidth=((double)MMWidth)/100.0, mmImageHeight=((double)MMHeight)/100.0;
    double pixDeviceWidth=(double)GetDeviceCaps(hdc,HORZRES), pixDeviceHeight=(double)GetDeviceCaps(hdc,VERTRES);
    double mmDeviceWidth=(double)GetDeviceCaps(hdc,HORZSIZE), mmDeviceHeight=(double)GetDeviceCaps(hdc,VERTSIZE);
    int pixWidth=(int)floor(pixDeviceWidth*mmImageWidth/mmDeviceWidth+0.5), pixHeight=(int)floor(pixDeviceHeight*mmImageHeight/mmDeviceHeight+0.5);
    pixWidth=500; pixHeight=100;
    //
    int mapPrev=SetMapMode(hdc,MM_ANISOTROPIC);
    POINT OldViewportOrg;  SetViewportOrgEx(hdc,tl.x,tl.y,&OldViewportOrg);
    SIZE OldViewportExt; SetViewportExtEx(hdc,pixWidth,pixHeight,&OldViewportExt);
    //
    PlayMetaFile(hdc,FWmf);
    SetViewportExtEx(hdc,OldViewportExt.cx,OldViewportExt.cy,NULL);
    SetViewportOrgEx(hdc,OldViewportOrg.x,OldViewportOrg.y,NULL);
    SetMapMode(hdc,mapPrev);
  }
  else
  { HDC hdc=cdest->Handle;
    POINT tl; tl.x=x; tl.y=y;
    LPtoDP(hdc,&tl,1); // tl now has device-coordinates for top left
    int mmWidth=MMWidth, mmHeight=MMHeight; // in 100th mm
    int mapPrev=SetMapMode(hdc,MM_HIMETRIC); // each logical unit maps to 100th mm
    DPtoLP(hdc,&tl,1); // pt now has logical coordinatates of tl in MM_HIMETRIC
    RECT rc; rc.left=tl.x; rc.top=tl.y; rc.right=rc.left+mmWidth; rc.bottom=rc.top-mmHeight;
    PlayEnhMetaFile(hdc,FEmf,&rc);
    SetMapMode(hdc,mapPrev);
  }
}
void __fastcall TRealMetafile::StretchDraw(TCanvas *cdest,TRect &rdst)
{ if (State!=rmsNormal) return;
  if (!Enhanced)
  { // We worry about the viewport
    HDC hdc=cdest->Handle;
    POINT tl,br; tl.x=rdst.Left; tl.y=rdst.Top; br.x=rdst.Right; br.y=rdst.Bottom;
    LPtoDP(hdc,&tl,1); LPtoDP(hdc,&br,1);
    int l=min(tl.x,br.x); int r=max(tl.x,br.x); int w=r-l;
    int t=min(tl.y,br.y); int b=max(tl.y,br.y); int h=b-t;
    int mapPrev=SetMapMode(hdc,MM_ANISOTROPIC);
    POINT OldViewportOrg; SetViewportOrgEx(hdc,l,t,&OldViewportOrg);
    SIZE OldViewportExt; SetViewportExtEx(hdc,w,h,&OldViewportExt);
    PlayMetaFile(hdc,FWmf);
    SetViewportExtEx(hdc,OldViewportExt.cx,OldViewportExt.cy,NULL);
    SetViewportOrgEx(hdc,OldViewportOrg.x,OldViewportOrg.y,NULL);
    SetMapMode(hdc,mapPrev);
  }
  else
  { HDC hdc=cdest->Handle;
    RECT rc; rc.left=rdst.Left; rc.top=rdst.Top; rc.right=rdst.Right; rc.bottom=rdst.Bottom;
    PlayEnhMetaFile(hdc,FEmf,&rc);
  }
}
void __fastcall TRealMetafile::Enum()
{ // We have to enum into a metafile anyway, just because we need to get a valid hdc for it
  // to enum into. So we're not loosing any efficiency in enumming to a metafile.
  TRealMetafile *rmt=new TRealMetafile(this);
  EnumToMetafile(rmt,false);
  delete rmt;
}
void __fastcall TRealMetafile::EnumToMetafile(TRealMetafile *mdest,bool trim)
{ if (State!=rmsNormal) return;
  if (!Enhanced && trim) return;
  mdest->Clear();
  InitializeEnum();
  FState=rmsEnum;
  if (!Enhanced)
  { HDC hdc=CreateMetaFile(NULL); FhDC=hdc;
    // There's no point in trying to set the viewport ext for enumming this thing. That's because
    // you can't query a metafile device's attributes, and it is not done with any device in mind.
    // All we need do is set mdest's MMWidth and MMHeight correctly
    TMetafileCallback mc=&EnumMetafileProc;
    EnumMetaFile(hdc,FWmf,EnumMetaFileCallback,(LPARAM)&mc);
    mdest->FWmf=CloseMetaFile(hdc); FhDC=NULL;
    mdest->FEnhanced=false; mdest->FMMWidth=FMMWidth; mdest->FMMHeight=FMMHeight; mdest->FState=rmsNormal;
  }
  else
  { RECT rcDest; rcDest.left=0; rcDest.top=0; rcDest.right=FMMWidth; rcDest.bottom=FMMHeight;
    RECT *prcDest; if (trim) prcDest=NULL; else prcDest=&rcDest;
    HDC hdc=CreateEnhMetaFile(NULL,NULL,prcDest,NULL); FhDC=hdc;
    RECT rc; rc.top=0; rc.right=FMMWidth; rc.left=0; rc.bottom=-FMMHeight;
    SetMapMode(hdc,MM_HIMETRIC);
    TEnhMetafileCallback mc=&EnumEnhMetafileProc;
    EnumEnhMetaFile(hdc,FEmf,EnumEnhMetaFileCallback,&mc,&rc);
    mdest->FEmf=CloseEnhMetaFile(hdc); FhDC=NULL;
    ENHMETAHEADER emh; GetEnhMetaFileHeader(mdest->FEmf,sizeof(emh),&emh);
    mdest->FMMWidth=emh.rclFrame.right-emh.rclFrame.left;
    mdest->FMMHeight=emh.rclFrame.bottom-emh.rclFrame.top;
    mdest->FEnhanced=true; mdest->FState=rmsNormal;
  }
  EndEnum();
  FState=rmsNormal;
}
void __fastcall TRealMetafile::EnumIntoCanvas(TCanvas *cdest,int x,int y)
{ if (State!=rmsNormal) return;
  InitializeEnum(); FState=rmsEnum;
  HDC hdc=cdest->Handle; FCanvas=cdest; OwnCanvas=false; FhDC=hdc;
  if (!Enhanced)
  { // We worry about the viewport
    POINT tl; tl.x=x; tl.y=y; LPtoDP(hdc,&tl,1); // tl now has device coordinates for top left
    int mapPrev=SetMapMode(hdc,MM_ANISOTROPIC);
    POINT OldViewportOrg; SetViewportOrgEx(hdc,tl.x,tl.y,&OldViewportOrg);
    double mmImageWidth=((double)MMWidth)/100.0, mmImageHeight=((double)MMHeight)/100.0;
    double pixDeviceWidth=(double)GetDeviceCaps(hdc,HORZRES), pixDeviceHeight=(double)GetDeviceCaps(hdc,VERTRES);
    double mmDeviceWidth=(double)GetDeviceCaps(hdc,HORZSIZE), mmDeviceHeight=(double)GetDeviceCaps(hdc,VERTSIZE);
    int pixWidth=(int)floor(pixDeviceWidth*mmImageWidth/mmDeviceWidth+0.5), pixHeight=(int)floor(pixDeviceHeight*mmImageHeight/mmDeviceHeight+0.5);
    SIZE OldViewportExt; SetViewportExtEx(hdc,pixWidth,pixHeight,&OldViewportExt);
    PlayMetaFile(hdc,FWmf);
    //
    FBoundsDev.Left=tl.x; FBoundsDev.Top=tl.y; FBoundsDev.Right=FBoundsDev.Left+pixWidth; FBoundsDev.Bottom=FBoundsDev.Top+pixHeight;
    SetMapMode(hdc,mapPrev);
    SetViewportOrgEx(hdc,OldViewportOrg.x,OldViewportOrg.y,NULL);
    SetViewportExtEx(hdc,OldViewportExt.cx,OldViewportExt.cy,NULL);
    POINT br; br.x=FBoundsDev.Right; br.y=FBoundsDev.Bottom; DPtoLP(hdc,&br,1);
    FBoundsLog.Left=x; FBoundsLog.Top=y; FBoundsLog.Right=br.x; FBoundsLog.Bottom=br.y;
    // There's something wrong going on here. Somehow, in restoring the map mode and
    // viewport and then doing a DPtoLP, the logical-stuff that we're getting back
    // is in fact DIFFERENT and INCOMPATIBLE with the logical stuff that we hadd
    // at the entry of this call. Therefore the FBoundsLog we're getting out is nonsense.
  }
  else
  { POINT tl; tl.x=x; tl.y=y;
    LPtoDP(hdc,&tl,1); // tl now has device-coordinates for top left
    int mmWidth=MMWidth, mmHeight=MMHeight; // in 100th mm
    int mmPrev=SetMapMode(hdc,MM_HIMETRIC); // each logical unit maps to 100th mm
    DPtoLP(hdc,&tl,1); // pt now has logical coordinatates of tl in MM_HIMETRIC
    RECT rc; rc.left=tl.x; rc.top=tl.y; rc.right=rc.left+mmWidth; rc.bottom=rc.top-mmHeight;
    TEnhMetafileCallback mc=&EnumEnhMetafileProc;
    EnumEnhMetaFile(hdc,FEmf,EnumEnhMetaFileCallback,&mc,&rc);
    POINT br; br.x=rc.right; br.y=rc.bottom; // tl, br are in HIMETRIC
    LPtoDP(hdc,&tl,1); LPtoDP(hdc,&br,1);    // tl,br are now in DEVICE
    FBoundsDev.Left=tl.x; FBoundsDev.Top=tl.y; FBoundsDev.Right=br.x; FBoundsDev.Bottom=br.y;
    SetMapMode(hdc,mmPrev);
    DPtoLP(hdc,&tl,1); DPtoLP(hdc,&br,1);    // tl,br are now in OLD-LOGICAL
    FBoundsLog.Left=tl.x; FBoundsLog.Top=tl.y; FBoundsLog.Right=br.x; FBoundsLog.Bottom=br.y;
  }
  EndEnum();
  FState=rmsNormal;
}
void __fastcall TRealMetafile::InitializeEnum()
{ InternalSelectObject(0x80000000 | NULL_PEN);
  InternalSelectObject(0x80000000 | NULL_BRUSH);
  InternalSelectObject(0x80000000 | SYSTEM_FONT);
  FhDC=NULL; FCanvas=NULL;
  OwnCanvas=true;
}
void __fastcall TRealMetafile::EndEnum()
{ if (FCanvas!=NULL && OwnCanvas) delete FCanvas; FCanvas=NULL;
}
TCanvas* __fastcall TRealMetafile::GetCanvas()
{ if (FCanvas!=NULL) return FCanvas;
  if (FhDC==NULL) return NULL;
  FCanvas=new TCanvas(); FCanvas->Handle=FhDC;
  return FCanvas;
}
void __fastcall TRealMetafile::PlayCurrentRecord()
{ if (FState!=rmsEnum) return;
  if (Enhanced)
  { PlayEnhMetaFileRecord(FhDC,FHandleTable,FEnhRec,FNumHandles);
    if (FEnhRec->iType==EMR_SELECTOBJECT) {EMRSELECTOBJECT *eso=(EMRSELECTOBJECT*)FEnhRec;InternalSelectObject(eso->ihObject);}
  }
  else
  { PlayMetaFileRecord(FhDC,FHandleTable,FWinRec,FNumHandles);
    if (FWinRec->rdFunction==META_SELECTOBJECT) {InternalSelectObject(FWinRec->rdParm[0]);}
  }
}
ENHMETARECORD* __fastcall TRealMetafile::GetEnhRec()
{ if (State!=rmsEnum) return NULL;
  if (!Enhanced) return NULL;
  return FEnhRec;
}
METARECORD* __fastcall TRealMetafile::GetWinRec()
{ if (State!=rmsEnum) return NULL;
  if (Enhanced) return NULL;
  return FWinRec;
}
THandle __fastcall TRealMetafile::GetObjectHandle(int i)
{ if (State!=rmsEnum) return 0;
  if (i>=FNumHandles) return 0;
  return (THandle)(HandleTable->objectHandle[i]);
}
void __fastcall TRealMetafile::InternalSelectObject(int ihObject)
{ HGDIOBJ h; int i=ihObject;
  if (i&0x80000000) h=GetStockObject(i&0x7FFFFFFF);
  else h=(HGDIOBJ)ObjectHandle[i];
  DWORD type=GetObjectType(h);
  switch (type)
  { case OBJ_FONT: GetObject(h,sizeof(FEnumCurrentFont),&FEnumCurrentFont); break;
    case OBJ_PEN: GetObject(h,sizeof(FEnumCurrentPen),&FEnumCurrentPen); break;
    case OBJ_BRUSH: GetObject(h,sizeof(FEnumCurrentBrush),&FEnumCurrentBrush); break;
  }
}
LOGFONT __fastcall TRealMetafile::GetCurrentFont() {return FEnumCurrentFont;}
LOGPEN __fastcall TRealMetafile::GetCurrentPen() {return FEnumCurrentPen;}
LOGBRUSH __fastcall TRealMetafile::GetCurrentBrush() {return FEnumCurrentBrush;}
int __fastcall TRealMetafile::EnumMetafileProc(HDC hdc,HANDLETABLE *hTable,METARECORD *rec,int nObj)
{ TEnumAction action=enumKeep;
  FHandleTable=hTable; FNumHandles=nObj; FWinRec=(METARECORD*)rec;
  if (FWmr!=NULL) FWmr(this,FWinRec,action);
  bool handled=false;
  if (action==enumKeep)
  { switch (FWinRec->rdFunction)
    { case META_SETBKCOLOR: if (FWmrSetBkColor!=NULL) {handled=true;FWmrSetBkColor(this,rec,action);} break;
      case META_SETBKMODE: if (FWmrSetBkMode!=NULL) {handled=true;FWmrSetBkMode(this,rec,action);} break;
      case META_SETMAPMODE: if (FWmrSetMapMode!=NULL) {handled=true;FWmrSetMapMode(this,rec,action);} break;
      case META_SETROP2: if (FWmrSetRop2!=NULL) {handled=true;FWmrSetRop2(this,rec,action);} break;
      case META_SETRELABS: if (FWmrSetRelabs!=NULL) {handled=true;FWmrSetRelabs(this,rec,action);} break;
      case META_SETPOLYFILLMODE: if (FWmrSetPolyFillMode!=NULL) {handled=true;FWmrSetPolyFillMode(this,rec,action);} break;
      case META_SETSTRETCHBLTMODE: if (FWmrSetStretchBltMode!=NULL) {handled=true;FWmrSetStretchBltMode(this,rec,action);} break;
      case META_SETTEXTCHAREXTRA: if (FWmrSetTextCharExtra!=NULL) {handled=true;FWmrSetTextCharExtra(this,rec,action);} break;
      case META_SETTEXTCOLOR: if (FWmrSetTextColor!=NULL) {handled=true;FWmrSetTextColor(this,rec,action);} break;
      case META_SETTEXTJUSTIFICATION: if (FWmrSetTextJustification!=NULL) {handled=true;FWmrSetTextJustification(this,rec,action);} break;
      case META_SETWINDOWORG: if (FWmrSetWindowOrg!=NULL) {handled=true;FWmrSetWindowOrg(this,rec,action);} break;
      case META_SETWINDOWEXT: if (FWmrSetWindowExt!=NULL) {handled=true;FWmrSetWindowExt(this,rec,action);} break;
      case META_SETVIEWPORTORG: if (FWmrSetViewportOrg!=NULL) {handled=true;FWmrSetViewportOrg(this,rec,action);} break;
      case META_SETVIEWPORTEXT: if (FWmrSetViewportExt!=NULL) {handled=true;FWmrSetViewportExt(this,rec,action);} break;
      case META_OFFSETWINDOWORG: if (FWmrOffSetWindowOrg!=NULL) {handled=true;FWmrOffSetWindowOrg(this,rec,action);} break;
      case META_SCALEWINDOWEXT: if (FWmrScaleWindowExt!=NULL) {handled=true;FWmrScaleWindowExt(this,rec,action);} break;
      case META_OFFSETVIEWPORTORG: if (FWmrOffSetViewportOrg!=NULL) {handled=true;FWmrOffSetViewportOrg(this,rec,action);} break;
      case META_SCALEVIEWPORTEXT: if (FWmrScaleViewportExt!=NULL) {handled=true;FWmrScaleViewportExt(this,rec,action);} break;
      case META_LINETO: if (FWmrLineTo!=NULL) {handled=true;FWmrLineTo(this,rec,action);} break;
      case META_MOVETO: if (FWmrMoveTo!=NULL) {handled=true;FWmrMoveTo(this,rec,action);} break;
      case META_EXCLUDECLIPRECT: if (FWmrExcludeClipRect!=NULL) {handled=true;FWmrExcludeClipRect(this,rec,action);} break;
      case META_INTERSECTCLIPRECT: if (FWmrIntersectClipRect!=NULL) {handled=true;FWmrIntersectClipRect(this,rec,action);} break;
      case META_ARC: if (FWmrArc!=NULL) {handled=true;FWmrArc(this,rec,action);} break;
      case META_ELLIPSE: if (FWmrEllipse!=NULL) {handled=true;FWmrEllipse(this,rec,action);} break;
      case META_FLOODFILL: if (FWmrFloodFill!=NULL) {handled=true;FWmrFloodFill(this,rec,action);} break;
      case META_PIE: if (FWmrPie!=NULL) {handled=true;FWmrPie(this,rec,action);} break;
      case META_RECTANGLE: if (FWmrRectangle!=NULL) {handled=true;FWmrRectangle(this,rec,action);} break;
      case META_ROUNDRECT: if (FWmrRoundRect!=NULL) {handled=true;FWmrRoundRect(this,rec,action);} break;
      case META_PATBLT: if (FWmrPatBlt!=NULL) {handled=true;FWmrPatBlt(this,rec,action);} break;
      case META_SAVEDC: if (FWmrSaveDC!=NULL) {handled=true;FWmrSaveDC(this,rec,action);} break;
      case META_SETPIXEL: if (FWmrSetPixel!=NULL) {handled=true;FWmrSetPixel(this,rec,action);} break;
      case META_OFFSETCLIPRGN: if (FWmrOffSetClipRgn!=NULL) {handled=true;FWmrOffSetClipRgn(this,rec,action);} break;
      case META_TEXTOUT: if (FWmrTextOut!=NULL) {handled=true;FWmrTextOut(this,rec,action);} break;
      case META_BITBLT: if (FWmrBitBlt!=NULL) {handled=true;FWmrBitBlt(this,rec,action);} break;
      case META_STRETCHBLT: if (FWmrStretchBlt!=NULL) {handled=true;FWmrStretchBlt(this,rec,action);} break;
      case META_POLYGON: if (FWmrPolygon!=NULL) {handled=true;FWmrPolygon(this,rec,action);} break;
      case META_POLYLINE: if (FWmrPolyLine!=NULL) {handled=true;FWmrPolyLine(this,rec,action);} break;
      case META_ESCAPE: if (FWmrEscape!=NULL) {handled=true;FWmrEscape(this,rec,action);} break;
      case META_RESTOREDC: if (FWmrResToReDC!=NULL) {handled=true;FWmrResToReDC(this,rec,action);} break;
      case META_FILLREGION: if (FWmrFillRegion!=NULL) {handled=true;FWmrFillRegion(this,rec,action);} break;
      case META_FRAMEREGION: if (FWmrFrameRegion!=NULL) {handled=true;FWmrFrameRegion(this,rec,action);} break;
      case META_INVERTREGION: if (FWmrInvertRegion!=NULL) {handled=true;FWmrInvertRegion(this,rec,action);} break;
      case META_PAINTREGION: if (FWmrPaintRegion!=NULL) {handled=true;FWmrPaintRegion(this,rec,action);} break;
      case META_SELECTCLIPREGION: if (FWmrSelectClipRegion!=NULL) {handled=true;FWmrSelectClipRegion(this,rec,action);} break;
      case META_SELECTOBJECT: if (FWmrSelectObject!=NULL) {handled=true;FWmrSelectObject(this,rec,action);} break;
      case META_SETTEXTALIGN: if (FWmrSetTextAlign!=NULL) {handled=true;FWmrSetTextAlign(this,rec,action);} break;
      case META_CHORD: if (FWmrChord!=NULL) {handled=true;FWmrChord(this,rec,action);} break;
      case META_SETMAPPERFLAGS: if (FWmrSetMapperFlags!=NULL) {handled=true;FWmrSetMapperFlags(this,rec,action);} break;
      case META_EXTTEXTOUT: if (FWmrExtTextOut!=NULL) {handled=true;FWmrExtTextOut(this,rec,action);} break;
      case META_SETDIBTODEV: if (FWmrSetDIBToDev!=NULL) {handled=true;FWmrSetDIBToDev(this,rec,action);} break;
      case META_SELECTPALETTE: if (FWmrSelectPalette!=NULL) {handled=true;FWmrSelectPalette(this,rec,action);} break;
      case META_REALIZEPALETTE: if (FWmrRealizePalette!=NULL) {handled=true;FWmrRealizePalette(this,rec,action);} break;
      case META_ANIMATEPALETTE: if (FWmrAnimatePalette!=NULL) {handled=true;FWmrAnimatePalette(this,rec,action);} break;
      case META_SETPALENTRIES: if (FWmrSetPalEntries!=NULL) {handled=true;FWmrSetPalEntries(this,rec,action);} break;
      case META_POLYPOLYGON: if (FWmrPolyPolygon!=NULL) {handled=true;FWmrPolyPolygon(this,rec,action);} break;
      case META_RESIZEPALETTE: if (FWmrResizePalette!=NULL) {handled=true;FWmrResizePalette(this,rec,action);} break;
      case META_DIBBITBLT: if (FWmrDIBBitBlt!=NULL) {handled=true;FWmrDIBBitBlt(this,rec,action);} break;
      case META_DIBSTRETCHBLT: if (FWmrDIBStretchBlt!=NULL) {handled=true;FWmrDIBStretchBlt(this,rec,action);} break;
      case META_DIBCREATEPATTERNBRUSH: if (FWmrDIBCreatePatternBrush!=NULL) {handled=true;FWmrDIBCreatePatternBrush(this,rec,action);} break;
      case META_STRETCHDIB: if (FWmrStretchDIB!=NULL) {handled=true;FWmrStretchDIB(this,rec,action);} break;
      case META_EXTFLOODFILL: if (FWmrExtFloodFill!=NULL) {handled=true;FWmrExtFloodFill(this,rec,action);} break;
      case META_DELETEOBJECT: if (FWmrDeleteObject!=NULL) {handled=true;FWmrDeleteObject(this,rec,action);} break;
      case META_CREATEPALETTE: if (FWmrCreatePalette!=NULL) {handled=true;FWmrCreatePalette(this,rec,action);} break;
      case META_CREATEPATTERNBRUSH: if (FWmrCreatePatternBrush!=NULL) {handled=true;FWmrCreatePatternBrush(this,rec,action);} break;
      case META_CREATEPENINDIRECT: if (FWmrCreatePenIndirect!=NULL) {handled=true;FWmrCreatePenIndirect(this,rec,action);} break;
      case META_CREATEFONTINDIRECT: if (FWmrCreateFontIndirect!=NULL) {handled=true;FWmrCreateFontIndirect(this,rec,action);} break;
      case META_CREATEBRUSHINDIRECT: if (FWmrCreateBrushIndirect!=NULL) {handled=true;FWmrCreateBrushIndirect(this,rec,action);} break;
      case META_CREATEREGION: if (FWmrCreateRegion!=NULL) {handled=true;FWmrCreateRegion(this,rec,action);} break;
    }
  }
  AnsiString s=AnsiString((int)handled); // so compiler doesn't complain that handled is unused
  if (action==enumKeep) PlayCurrentRecord();
  FHandleTable=NULL; FNumHandles=0; FWinRec=NULL;
  if (action==enumAbort) return 0;
  return 1;
}
int __fastcall TRealMetafile::EnumEnhMetafileProc(HDC hdc,HANDLETABLE *hTable,const ENHMETARECORD *rec,int nObj)
{ TEnumAction action=enumKeep;
  FHandleTable=hTable; FNumHandles=nObj; FEnhRec=(ENHMETARECORD*)rec;
  if (FEmr!=NULL) FEmr(this,FEnhRec,action);
  bool handled=false;
  if (action==enumKeep)
  { switch (FEnhRec->iType)
    { case EMR_HEADER: if (FEmrHeader!=NULL) {handled=true;FEmrHeader(this,(ENHMETAHEADER*)rec,action);} break;
      case EMR_POLYBEZIER: if (FEmrPolyBezier!=NULL) {handled=true;FEmrPolyBezier(this,(EMRPOLYBEZIER*)rec,action);} break;
      case EMR_POLYGON: if (FEmrPolygon!=NULL) {handled=true;FEmrPolygon(this,(EMRPOLYGON*)rec,action);} break;
      case EMR_POLYLINE: if (FEmrPolyLine!=NULL) {handled=true;FEmrPolyLine(this,(EMRPOLYLINE*)rec,action);} break;
      case EMR_POLYBEZIERTO: if (FEmrPolyBezierTo!=NULL) {handled=true;FEmrPolyBezierTo(this,(EMRPOLYBEZIERTO*)rec,action);} break;
      case EMR_POLYLINETO: if (FEmrPolyLineTo!=NULL) {handled=true;FEmrPolyLineTo(this,(EMRPOLYLINETO*)rec,action);} break;
      case EMR_POLYPOLYLINE: if (FEmrPolyPolyLine!=NULL) {handled=true;FEmrPolyPolyLine(this,(EMRPOLYPOLYLINE*)rec,action);} break;
      case EMR_POLYPOLYGON: if (FEmrPolyPolygon!=NULL) {handled=true;FEmrPolyPolygon(this,(EMRPOLYPOLYGON*)rec,action);} break;
      case EMR_SETWINDOWEXTEX: if (FEmrSetWindowExtEx!=NULL) {handled=true;FEmrSetWindowExtEx(this,(EMRSETWINDOWEXTEX*)rec,action);} break;
      case EMR_SETWINDOWORGEX: if (FEmrSetWindowOrgEx!=NULL) {handled=true;FEmrSetWindowOrgEx(this,(EMRSETWINDOWORGEX*)rec,action);} break;
      case EMR_SETVIEWPORTEXTEX: if (FEmrSetViewportExtEx!=NULL) {handled=true;FEmrSetViewportExtEx(this,(EMRSETVIEWPORTEXTEX*)rec,action);} break;
      case EMR_SETVIEWPORTORGEX: if (FEmrSetViewportOrgEx!=NULL) {handled=true;FEmrSetViewportOrgEx(this,(EMRSETVIEWPORTORGEX*)rec,action);} break;
      case EMR_SETBRUSHORGEX: if (FEmrSetBrushorgEx!=NULL) {handled=true;FEmrSetBrushorgEx(this,(EMRSETBRUSHORGEX*)rec,action);} break;
      case EMR_EOF: if (FEmrEof!=NULL) {handled=true;FEmrEof(this,(EMREOF*)rec,action);} break;
      case EMR_SETPIXELV: if (FEmrSetPixelv!=NULL) {handled=true;FEmrSetPixelv(this,(EMRSETPIXELV*)rec,action);} break;
      case EMR_SETMAPPERFLAGS: if (FEmrSetMapperFlags!=NULL) {handled=true;FEmrSetMapperFlags(this,(EMRSETMAPPERFLAGS*)rec,action);} break;
      case EMR_SETMAPMODE: if (FEmrSetMapMode!=NULL) {handled=true;FEmrSetMapMode(this,(EMRSETMAPMODE*)rec,action);} break;
      case EMR_SETBKMODE: if (FEmrSetBkMode!=NULL) {handled=true;FEmrSetBkMode(this,(EMRSETBKMODE*)rec,action);} break;
      case EMR_SETPOLYFILLMODE: if (FEmrSetPolyFillMode!=NULL) {handled=true;FEmrSetPolyFillMode(this,(EMRSETPOLYFILLMODE*)rec,action);} break;
      case EMR_SETROP2: if (FEmrSetRop2!=NULL) {handled=true;FEmrSetRop2(this,(EMRSETROP2*)rec,action);} break;
      case EMR_SETSTRETCHBLTMODE: if (FEmrSetStretchBltMode!=NULL) {handled=true;FEmrSetStretchBltMode(this,(EMRSETSTRETCHBLTMODE*)rec,action);} break;
      case EMR_SETTEXTALIGN: if (FEmrSetTextAlign!=NULL) {handled=true;FEmrSetTextAlign(this,(EMRSETTEXTALIGN*)rec,action);} break;
      case EMR_SETCOLORADJUSTMENT: if (FEmrSetColorAdjustment!=NULL) {handled=true;FEmrSetColorAdjustment(this,(EMRSETCOLORADJUSTMENT*)rec,action);} break;
      case EMR_SETTEXTCOLOR: if (FEmrSetTextColor!=NULL) {handled=true;FEmrSetTextColor(this,(EMRSETTEXTCOLOR*)rec,action);} break;
      case EMR_SETBKCOLOR: if (FEmrSetBkColor!=NULL) {handled=true;FEmrSetBkColor(this,(EMRSETBKCOLOR*)rec,action);} break;
      case EMR_OFFSETCLIPRGN: if (FEmrOffsetClipRgn!=NULL) {handled=true;FEmrOffsetClipRgn(this,(EMROFFSETCLIPRGN*)rec,action);} break;
      case EMR_MOVETOEX: if (FEmrMoveToEx!=NULL) {handled=true;FEmrMoveToEx(this,(EMRMOVETOEX*)rec,action);} break;
      case EMR_SETMETARGN: if (FEmrSetMetaRgn!=NULL) {handled=true;FEmrSetMetaRgn(this,(EMRSETMETARGN*)rec,action);} break;
      case EMR_EXCLUDECLIPRECT: if (FEmrExcludeClipRect!=NULL) {handled=true;FEmrExcludeClipRect(this,(EMREXCLUDECLIPRECT*)rec,action);} break;
      case EMR_INTERSECTCLIPRECT: if (FEmrIntersectClipRect!=NULL) {handled=true;FEmrIntersectClipRect(this,(EMRINTERSECTCLIPRECT*)rec,action);} break;
      case EMR_SCALEVIEWPORTEXTEX: if (FEmrScaleViewportExtEx!=NULL) {handled=true;FEmrScaleViewportExtEx(this,(EMRSCALEVIEWPORTEXTEX*)rec,action);} break;
      case EMR_SCALEWINDOWEXTEX: if (FEmrScaleWindowExtEx!=NULL) {handled=true;FEmrScaleWindowExtEx(this,(EMRSCALEWINDOWEXTEX*)rec,action);} break;
      case EMR_SAVEDC: if (FEmrSaveDC!=NULL) {handled=true;FEmrSaveDC(this,(EMRSAVEDC*)rec,action);} break;
      case EMR_RESTOREDC: if (FEmrRestoreDC!=NULL) {handled=true;FEmrRestoreDC(this,(EMRRESTOREDC*)rec,action);} break;
      case EMR_SETWORLDTRANSFORM: if (FEmrSetWorldTransform!=NULL) {handled=true;FEmrSetWorldTransform(this,(EMRSETWORLDTRANSFORM*)rec,action);} break;
      case EMR_MODIFYWORLDTRANSFORM: if (FEmrModifyWorldTransform!=NULL) {handled=true;FEmrModifyWorldTransform(this,(EMRMODIFYWORLDTRANSFORM*)rec,action);} break;
      case EMR_SELECTOBJECT: if (FEmrSelectObject!=NULL) {handled=true;FEmrSelectObject(this,(EMRSELECTOBJECT*)rec,action);} break;
      case EMR_CREATEPEN: if (FEmrCreatePen!=NULL) {handled=true;FEmrCreatePen(this,(EMRCREATEPEN*)rec,action);} break;
      case EMR_CREATEBRUSHINDIRECT: if (FEmrCreateBrushIndirect!=NULL) {handled=true;FEmrCreateBrushIndirect(this,(EMRCREATEBRUSHINDIRECT*)rec,action);} break;
      case EMR_DELETEOBJECT: if (FEmrDeleteObject!=NULL) {handled=true;FEmrDeleteObject(this,(EMRDELETEOBJECT*)rec,action);} break;
      case EMR_ANGLEARC: if (FEmrAngleArc!=NULL) {handled=true;FEmrAngleArc(this,(EMRANGLEARC*)rec,action);} break;
      case EMR_ELLIPSE: if (FEmrEllipse!=NULL) {handled=true;FEmrEllipse(this,(EMRELLIPSE*)rec,action);} break;
      case EMR_RECTANGLE: if (FEmrRectangle!=NULL) {handled=true;FEmrRectangle(this,(EMRRECTANGLE*)rec,action);} break;
      case EMR_ROUNDRECT: if (FEmrRoundRect!=NULL) {handled=true;FEmrRoundRect(this,(EMRROUNDRECT*)rec,action);} break;
      case EMR_ARC: if (FEmrArc!=NULL) {handled=true;FEmrArc(this,(EMRARC*)rec,action);} break;
      case EMR_CHORD: if (FEmrChord!=NULL) {handled=true;FEmrChord(this,(EMRCHORD*)rec,action);} break;
      case EMR_PIE: if (FEmrPie!=NULL) {handled=true;FEmrPie(this,(EMRPIE*)rec,action);} break;
      case EMR_SELECTPALETTE: if (FEmrSelectPalette!=NULL) {handled=true;FEmrSelectPalette(this,(EMRSELECTPALETTE*)rec,action);} break;
      case EMR_CREATEPALETTE: if (FEmrCreatePalette!=NULL) {handled=true;FEmrCreatePalette(this,(EMRCREATEPALETTE*)rec,action);} break;
      case EMR_SETPALETTEENTRIES: if (FEmrSetPaletteEntries!=NULL) {handled=true;FEmrSetPaletteEntries(this,(EMRSETPALETTEENTRIES*)rec,action);} break;
      case EMR_RESIZEPALETTE: if (FEmrResizePalette!=NULL) {handled=true;FEmrResizePalette(this,(EMRRESIZEPALETTE*)rec,action);} break;
      case EMR_REALIZEPALETTE: if (FEmrRealizePalette!=NULL) {handled=true;FEmrRealizePalette(this,(EMRREALIZEPALETTE*)rec,action);} break;
      case EMR_EXTFLOODFILL: if (FEmrExtFloodFill!=NULL) {handled=true;FEmrExtFloodFill(this,(EMREXTFLOODFILL*)rec,action);} break;
      case EMR_LINETO: if (FEmrLineTo!=NULL) {handled=true;FEmrLineTo(this,(EMRLINETO*)rec,action);} break;
      case EMR_ARCTO: if (FEmrArcTo!=NULL) {handled=true;FEmrArcTo(this,(EMRARCTO*)rec,action);} break;
      case EMR_POLYDRAW: if (FEmrPolyDraw!=NULL) {handled=true;FEmrPolyDraw(this,(EMRPOLYDRAW*)rec,action);} break;
      case EMR_SETARCDIRECTION: if (FEmrSetArcDirection!=NULL) {handled=true;FEmrSetArcDirection(this,(EMRSETARCDIRECTION*)rec,action);} break;
      case EMR_SETMITERLIMIT: if (FEmrSetMiterLimit!=NULL) {handled=true;FEmrSetMiterLimit(this,(EMRSETMITERLIMIT*)rec,action);} break;
      case EMR_BEGINPATH: if (FEmrBeginPath!=NULL) {handled=true;FEmrBeginPath(this,(EMRBEGINPATH*)rec,action);} break;
      case EMR_ENDPATH: if (FEmrEndPath!=NULL) {handled=true;FEmrEndPath(this,(EMRENDPATH*)rec,action);} break;
      case EMR_CLOSEFIGURE: if (FEmrCloseFigure!=NULL) {handled=true;FEmrCloseFigure(this,(EMRCLOSEFIGURE*)rec,action);} break;
      case EMR_FILLPATH: if (FEmrFillPath!=NULL) {handled=true;FEmrFillPath(this,(EMRFILLPATH*)rec,action);} break;
      case EMR_STROKEANDFILLPATH: if (FEmrStrokeAndFillpath!=NULL) {handled=true;FEmrStrokeAndFillpath(this,(EMRSTROKEANDFILLPATH*)rec,action);} break;
      case EMR_STROKEPATH: if (FEmrStrokePath!=NULL) {handled=true;FEmrStrokePath(this,(EMRSTROKEPATH*)rec,action);} break;
      case EMR_FLATTENPATH: if (FEmrFlattenPath!=NULL) {handled=true;FEmrFlattenPath(this,(EMRFLATTENPATH*)rec,action);} break;
      case EMR_WIDENPATH: if (FEmrWidenPath!=NULL) {handled=true;FEmrWidenPath(this,(EMRWIDENPATH*)rec,action);} break;
      case EMR_SELECTCLIPPATH: if (FEmrSelectClipPath!=NULL) {handled=true;FEmrSelectClipPath(this,(EMRSELECTCLIPPATH*)rec,action);} break;
      case EMR_ABORTPATH: if (FEmrAbortPath!=NULL) {handled=true;FEmrAbortPath(this,(EMRABORTPATH*)rec,action);} break;
      case EMR_GDICOMMENT: if (FEmrGdiComment!=NULL) {handled=true;FEmrGdiComment(this,(EMRGDICOMMENT*)rec,action);} break;
      case EMR_FILLRGN: if (FEmrFillRgn!=NULL) {handled=true;FEmrFillRgn(this,(EMRFILLRGN*)rec,action);} break;
      case EMR_FRAMERGN: if (FEmrFrameRgn!=NULL) {handled=true;FEmrFrameRgn(this,(EMRFRAMERGN*)rec,action);} break;
      case EMR_INVERTRGN: if (FEmrInvertRgn!=NULL) {handled=true;FEmrInvertRgn(this,(EMRINVERTRGN*)rec,action);} break;
      case EMR_PAINTRGN: if (FEmrPaintRgn!=NULL) {handled=true;FEmrPaintRgn(this,(EMRPAINTRGN*)rec,action);} break;
      case EMR_EXTSELECTCLIPRGN: if (FEmrExtSelectClipRgn!=NULL) {handled=true;FEmrExtSelectClipRgn(this,(EMREXTSELECTCLIPRGN*)rec,action);} break;
      case EMR_BITBLT: if (FEmrBitBlt!=NULL) {handled=true;FEmrBitBlt(this,(EMRBITBLT*)rec,action);} break;
      case EMR_STRETCHBLT: if (FEmrStretchBlt!=NULL) {handled=true;FEmrStretchBlt(this,(EMRSTRETCHBLT*)rec,action);} break;
      case EMR_MASKBLT: if (FEmrMaskBlt!=NULL) {handled=true;FEmrMaskBlt(this,(EMRMASKBLT*)rec,action);} break;
      case EMR_PLGBLT: if (FEmrPlgBlt!=NULL) {handled=true;FEmrPlgBlt(this,(EMRPLGBLT*)rec,action);} break;
      case EMR_SETDIBITSTODEVICE: if (FEmrSetDIBitsToDevice!=NULL) {handled=true;FEmrSetDIBitsToDevice(this,(EMRSETDIBITSTODEVICE*)rec,action);} break;
      case EMR_STRETCHDIBITS: if (FEmrStretchDIBits!=NULL) {handled=true;FEmrStretchDIBits(this,(EMRSTRETCHDIBITS*)rec,action);} break;
      case EMR_EXTCREATEFONTINDIRECTW: if (FEmrExtCreateFontIndirectW!=NULL) {handled=true;FEmrExtCreateFontIndirectW(this,(EMREXTCREATEFONTINDIRECTW*)rec,action);} break;
      case EMR_EXTTEXTOUTA: if (FEmrExtTextOutA!=NULL) {handled=true;FEmrExtTextOutA(this,(EMREXTTEXTOUTA*)rec,action);} break;
      case EMR_EXTTEXTOUTW: if (FEmrExtTextOutW!=NULL) {handled=true;FEmrExtTextOutW(this,(EMREXTTEXTOUTW*)rec,action);} break;
      case EMR_POLYBEZIER16: if (FEmrPolyBezier16!=NULL) {handled=true;FEmrPolyBezier16(this,(EMRPOLYBEZIER16*)rec,action);} break;
      case EMR_POLYGON16: if (FEmrPolygon16!=NULL) {handled=true;FEmrPolygon16(this,(EMRPOLYGON16*)rec,action);} break;
      case EMR_POLYLINE16: if (FEmrPolyLine16!=NULL) {handled=true;FEmrPolyLine16(this,(EMRPOLYLINE16*)rec,action);} break;
      case EMR_POLYBEZIERTO16: if (FEmrPolyBezierTo16!=NULL) {handled=true;FEmrPolyBezierTo16(this,(EMRPOLYBEZIERTO16*)rec,action);} break;
      case EMR_POLYLINETO16: if (FEmrPolyLineTo16!=NULL) {handled=true;FEmrPolyLineTo16(this,(EMRPOLYLINETO16*)rec,action);} break;
      case EMR_POLYPOLYLINE16: if (FEmrPolyPolyLine16!=NULL) {handled=true;FEmrPolyPolyLine16(this,(EMRPOLYPOLYLINE16*)rec,action);} break;
      case EMR_POLYPOLYGON16: if (FEmrPolyPolygon16!=NULL) {handled=true;FEmrPolyPolygon16(this,(EMRPOLYPOLYGON16*)rec,action);} break;
      case EMR_POLYDRAW16: if (FEmrPolyDraw16!=NULL) {handled=true;FEmrPolyDraw16(this,(EMRPOLYDRAW16*)rec,action);} break;
      case EMR_CREATEMONOBRUSH: if (FEmrCreateMonoBrush!=NULL) {handled=true;FEmrCreateMonoBrush(this,(EMRCREATEMONOBRUSH*)rec,action);} break;
      case EMR_CREATEDIBPATTERNBRUSHPT: if (FEmrCreateDIBPatternBrushPt!=NULL) {handled=true;FEmrCreateDIBPatternBrushPt(this,(EMRCREATEDIBPATTERNBRUSHPT*)rec,action);} break;
      case EMR_EXTCREATEPEN: if (FEmrExtCreatePen!=NULL) {handled=true;FEmrExtCreatePen(this,(EMREXTCREATEPEN*)rec,action);} break;
      case EMR_POLYTEXTOUTA: if (FEmrPolyTextOutA!=NULL) {handled=true;FEmrPolyTextOutA(this,(EMRPOLYTEXTOUTA*)rec,action);} break;
      case EMR_POLYTEXTOUTW: if (FEmrPolyTextOutW!=NULL) {handled=true;FEmrPolyTextOutW(this,(EMRPOLYTEXTOUTW*)rec,action);} break;
      case EMR_SETICMMODE: if (FEmrSetICMMode!=NULL) {handled=true;FEmrSetICMMode(this,(EMRSETICMMODE*)rec,action);} break;
      case EMR_CREATECOLORSPACE: if (FEmrCreateColorSpace!=NULL) {handled=true;FEmrCreateColorSpace(this,(EMRCREATECOLORSPACE*)rec,action);} break;
      case EMR_SETCOLORSPACE: if (FEmrSetColorSpace!=NULL) {handled=true;FEmrSetColorSpace(this,(EMRSETCOLORSPACE*)rec,action);} break;
      case EMR_DELETECOLORSPACE: if (FEmrDeleteColorSpace!=NULL) {handled=true;FEmrDeleteColorSpace(this,(EMRDELETECOLORSPACE*)rec,action);} break;
      case EMR_GLSRECORD: if (FEmrGLSRecord!=NULL) {handled=true;FEmrGLSRecord(this,(EMRGLSRECORD*)rec,action);} break;
      case EMR_GLSBOUNDEDRECORD: if (FEmrGLSBoundedRecord!=NULL) {handled=true;FEmrGLSBoundedRecord(this,(EMRGLSBOUNDEDRECORD*)rec,action);} break;
      case EMR_PIXELFORMAT: if (FEmrPixelFormat!=NULL) {handled=true;FEmrPixelFormat(this,(EMRPIXELFORMAT*)rec,action);} break;
    }
  }
  AnsiString s=AnsiString((int)handled); // so compiler doesn't complain that handled is unused
  if (action==enumKeep) PlayCurrentRecord();
  FHandleTable=NULL; FNumHandles=0; FWinRec=NULL;
  if (action==enumAbort) return 0;
  return 1;
}



AnsiString __fastcall TRealMetafile::GetRecordString()
{ if (FState!=rmsEnum) return "";
  if (Enhanced)
  { switch (FEnhRec->iType)
    { case EMR_HEADER: return strEmrHeader((ENHMETAHEADER*)FEnhRec);
      case EMR_SETWINDOWEXTEX: return strEmrSetWindowExtEx((EMRSETWINDOWEXTEX*)FEnhRec);
      case EMR_SETWINDOWORGEX: return strEmrSetWindowOrgEx((EMRSETWINDOWORGEX*)FEnhRec);
      case EMR_SETVIEWPORTEXTEX: return strEmrSetViewportExtEx((EMRSETWINDOWEXTEX*)FEnhRec);
      case EMR_SETVIEWPORTORGEX: return strEmrSetViewportOrgEx((EMRSETWINDOWORGEX*)FEnhRec);
      case EMR_EOF: return strEmrEof((EMREOF*)FEnhRec);
      case EMR_SETMAPMODE: return strEmrSetMapMode((EMRSETMAPMODE*)FEnhRec);
      case EMR_SETBKMODE: return strEmrSetBkMode((EMRSETMAPMODE*)FEnhRec);
      case EMR_SETPOLYFILLMODE: return strEmrSetPolyFillMode((EMRSETMAPMODE*)FEnhRec);
      case EMR_SETROP2: return strEmrSetRop2((EMRSETMAPMODE*)FEnhRec);
      case EMR_SETTEXTALIGN: return strEmrSetTextAlign((EMRSETMAPMODE*)FEnhRec);
      case EMR_SETTEXTCOLOR: return strEmrSetTextColor((EMRSETTEXTCOLOR*)FEnhRec);
      case EMR_SELECTOBJECT: return strEmrSelectObject((EMRSELECTOBJECT*)FEnhRec);
      case EMR_CREATEPEN: return strEmrCreatePen((EMRCREATEPEN*)FEnhRec);;
      case EMR_CREATEBRUSHINDIRECT: return strEmrCreateBrushIndirect((EMRCREATEBRUSHINDIRECT*)FEnhRec);
      case EMR_DELETEOBJECT: return strEmrDeleteObject((EMRSELECTOBJECT*)FEnhRec);
      case EMR_SELECTPALETTE: return strEmrSelectPalette((EMRSELECTPALETTE*)FEnhRec);
      case EMR_GDICOMMENT: return strEmrGdiComment((EMRGDICOMMENT*)FEnhRec);
      case EMR_EXTSELECTCLIPRGN: return strEmrExtSelectClipRgn((EMREXTSELECTCLIPRGN*)FEnhRec);
      case EMR_EXTCREATEFONTINDIRECTW: return strEmrExtCreateFontIndirectW((EMREXTCREATEFONTINDIRECTW*)FEnhRec);
      case EMR_EXTTEXTOUTW: return strEmrExtTextOutW((EMREXTTEXTOUTA*)FEnhRec);
      case EMR_POLYGON16: return strEmrPolygon16((EMRPOLYBEZIER16*)FEnhRec);
      case EMR_POLYLINE16: return strEmrPolyLine16((EMRPOLYBEZIER16*)FEnhRec);
      case EMR_POLYPOLYGON16: return strEmrPolyPolygon16((EMRPOLYPOLYLINE16*)FEnhRec);
      // These following ones only return basic information
      case EMR_POLYBEZIER: return "PolyBezier";
      case EMR_POLYGON: return "Polygon";
      case EMR_POLYLINE: return "PolyLine";
      case EMR_POLYBEZIERTO: return "PolyBezierTo";
      case EMR_POLYLINETO: return "PolyLineTo";
      case EMR_POLYPOLYLINE: return "PolyPolyLine";
      case EMR_POLYPOLYGON: return "PolyPolygon";
      case EMR_SETBRUSHORGEX: return "SetBrushorgEx";
      case EMR_SETPIXELV: return "SetPixelv";
      case EMR_SETMAPPERFLAGS: return "SetMapperFlags";
      case EMR_SETSTRETCHBLTMODE: return "SetStretchBltMode";
      case EMR_SETCOLORADJUSTMENT: return "SetColorAdjustment";
      case EMR_SETBKCOLOR: return "SetBkColor";
      case EMR_OFFSETCLIPRGN: return "OffsetClipRgn";
      case EMR_MOVETOEX: return "MoveToEx";
      case EMR_SETMETARGN: return "SetMetaRgn";
      case EMR_EXCLUDECLIPRECT: return "ExcludeClipRect";
      case EMR_INTERSECTCLIPRECT: return "IntersectClipRect";
      case EMR_SCALEVIEWPORTEXTEX: return "ScaleViewportExtEx";
      case EMR_SCALEWINDOWEXTEX: return "ScaleWindowExtEx";
      case EMR_SAVEDC: return "SaveDC";
      case EMR_RESTOREDC: return "RestoreDC";
      case EMR_SETWORLDTRANSFORM: return "SetWorldTransform";
      case EMR_MODIFYWORLDTRANSFORM: return "ModifyWorldTransform";
      case EMR_ANGLEARC: return "AngleArc";
      case EMR_ELLIPSE: return "Ellipse";
      case EMR_RECTANGLE: return "Rectangle";
      case EMR_ROUNDRECT: return "RoundRect";
      case EMR_ARC: return "Arc";
      case EMR_CHORD: return "Chord";
      case EMR_PIE: return "Pie";
      case EMR_CREATEPALETTE: return "CreatePalette";
      case EMR_SETPALETTEENTRIES: return "SetPaletteEntries";
      case EMR_RESIZEPALETTE: return "ResizePalette";
      case EMR_REALIZEPALETTE: return "RealizePalette";
      case EMR_EXTFLOODFILL: return "ExtFloodFill";
      case EMR_LINETO: return "LineTo";
      case EMR_ARCTO: return "ArcTo";
      case EMR_POLYDRAW: return "PolyDraw";
      case EMR_SETARCDIRECTION: return "SetArcDirection";
      case EMR_SETMITERLIMIT: return "SetMiterLimit";
      case EMR_BEGINPATH: return "BeginPath";
      case EMR_ENDPATH: return "EndPath";
      case EMR_CLOSEFIGURE: return "CloseFigure";
      case EMR_FILLPATH: return "FillPath";
      case EMR_STROKEANDFILLPATH: return "StrokeAndFillpath";
      case EMR_STROKEPATH: return "StrokePath";
      case EMR_FLATTENPATH: return "FlattenPath";
      case EMR_WIDENPATH: return "WidenPath";
      case EMR_SELECTCLIPPATH: return "SelectClipPath";
      case EMR_ABORTPATH: return "AbortPath";
      case EMR_FILLRGN: return "FillRgn";
      case EMR_FRAMERGN: return "FrameRgn";
      case EMR_INVERTRGN: return "InvertRgn";
      case EMR_PAINTRGN: return "PaintRgn";
      case EMR_BITBLT: return "BitBlt";
      case EMR_STRETCHBLT: return "StretchBlt";
      case EMR_MASKBLT: return "MaskBlt";
      case EMR_PLGBLT: return "PlgBlt";
      case EMR_SETDIBITSTODEVICE: return "SetDIBitsToDevice";
      case EMR_STRETCHDIBITS: return "StretchDIBits";
      case EMR_EXTTEXTOUTA: return "ExtTextOutA";
      case EMR_POLYBEZIER16: return "PolyBezier16";
      case EMR_POLYBEZIERTO16: return "PolyBezierTo16";
      case EMR_POLYLINETO16: return "PolyLineTo16";
      case EMR_POLYPOLYLINE16: return "PolyPolyLine16";
      case EMR_POLYDRAW16: return "PolyDraw16";
      case EMR_CREATEMONOBRUSH: return "CreateMonoBrush";
      case EMR_CREATEDIBPATTERNBRUSHPT: return "CreateDIBPatternBrushPt";
      case EMR_EXTCREATEPEN: return "ExtCreatePen";
      case EMR_POLYTEXTOUTA: return "PolyTextOutA";
      case EMR_POLYTEXTOUTW: return "PolyTextOutW";
      case EMR_SETICMMODE: return "SetICMMode";
      case EMR_CREATECOLORSPACE: return "CreateColorSpace";
      case EMR_SETCOLORSPACE: return "SetColorSpace";
      case EMR_DELETECOLORSPACE: return "DeleteColorSpace";
      case EMR_GLSRECORD: return "GLSRecord";
      case EMR_GLSBOUNDEDRECORD: return "GLSBoundedRecord";
      case EMR_PIXELFORMAT: return "PixelFormat";
      default: AnsiString s="<Unknown enhanced metafile record ";s=s+AnsiString(FEnhRec->iType)+">"; return s;
    }
  }
  else
  { switch (FWinRec->rdFunction)
    { case META_SETBKCOLOR: return "SetBkColor";
      case META_SETBKMODE: return "SetBkMode";
      case META_SETMAPMODE: return "SetMapMode";
      case META_SETROP2: return "SetRop2";
      case META_SETRELABS: return "SetRelabs";
      case META_SETPOLYFILLMODE: return "SetPolyFillMode";
      case META_SETSTRETCHBLTMODE: return "SetStretchBltMode";
      case META_SETTEXTCHAREXTRA: return "SetTextCharExtra";
      case META_SETTEXTCOLOR: return "SetTextColor";
      case META_SETTEXTJUSTIFICATION: return "SetTextJustification";
      case META_SETWINDOWORG: return "SetWindowOrg";
      case META_SETWINDOWEXT: return "SetWindowExt";
      case META_SETVIEWPORTORG: return "SetViewportOrg";
      case META_SETVIEWPORTEXT: return "SetViewportExt";
      case META_OFFSETWINDOWORG: return "OffSetWindowOrg";
      case META_SCALEWINDOWEXT: return "ScaleWindowExt";
      case META_OFFSETVIEWPORTORG: return "OffSetViewportOrg";
      case META_SCALEVIEWPORTEXT: return "ScaleViewportExt";
      case META_LINETO: return "LineTo";
      case META_MOVETO: return "MoveTo";
      case META_EXCLUDECLIPRECT: return "ExcludeClipRect";
      case META_INTERSECTCLIPRECT: return "IntersectClipRect";
      case META_ARC: return "Arc";
      case META_ELLIPSE: return "Ellipse";
      case META_FLOODFILL: return "FloodFill";
      case META_PIE: return "Pie";
      case META_RECTANGLE: return "Rectangle";
      case META_ROUNDRECT: return "RoundRect";
      case META_PATBLT: return "PatBlt";
      case META_SAVEDC: return "SaveDC";
      case META_SETPIXEL: return "SetPixel";
      case META_OFFSETCLIPRGN: return "OffSetClipRgn";
      case META_TEXTOUT: return "TextOut";
      case META_BITBLT: return "BitBlt";
      case META_STRETCHBLT: return "StretchBlt";
      case META_POLYGON: return "Polygon";
      case META_POLYLINE: return "PolyLine";
      case META_ESCAPE: return "Escape";
      case META_RESTOREDC: return "ResToReDC";
      case META_FILLREGION: return "FillRegion";
      case META_FRAMEREGION: return "FrameRegion";
      case META_INVERTREGION: return "InvertRegion";
      case META_PAINTREGION: return "PaintRegion";
      case META_SELECTCLIPREGION: return "SelectClipRegion";
      case META_SELECTOBJECT: return strWmrSelectObject(FWinRec);
      case META_SETTEXTALIGN: return "SetTextAlign";
      case META_CHORD: return "Chord";
      case META_SETMAPPERFLAGS: return "SetMapperFlags";
      case META_EXTTEXTOUT: return "ExtTextOut";
      case META_SETDIBTODEV: return "SetDIBToDev";
      case META_SELECTPALETTE: return "SelectPalette";
      case META_REALIZEPALETTE: return "RealizePalette";
      case META_ANIMATEPALETTE: return "AnimatePalette";
      case META_SETPALENTRIES: return "SetPalEntries";
      case META_POLYPOLYGON: return "PolyPolygon";
      case META_RESIZEPALETTE: return "ResizePalette";
      case META_DIBBITBLT: return "DIBBitBlt";
      case META_DIBSTRETCHBLT: return "DIBStretchBlt";
      case META_DIBCREATEPATTERNBRUSH: return "DIBCreatePatternBrush";
      case META_STRETCHDIB: return "StretchDIB";
      case META_EXTFLOODFILL: return "ExtFloodFill";
      case META_DELETEOBJECT: return "DeleteObject";
      case META_CREATEPALETTE: return "CreatePalette";
      case META_CREATEPATTERNBRUSH: return "CreatePatternBrush";
      case META_CREATEPENINDIRECT: return "CreatePenIndirect";
      case META_CREATEFONTINDIRECT: return "CreateFontIndirect";
      case META_CREATEBRUSHINDIRECT: return "CreateBrushIndirect";
      case META_CREATEREGION: return "CreateRegion";
      default: AnsiString s="<Unknown metafile record ";s=s+AnsiString(FWinRec->rdFunction)+">"; return s;
    }
  }
}
AnsiString __fastcall TRealMetafile::strRect(const RECTL &rc) {return AnsiString("(")+rc.left+","+rc.top+")-("+rc.right+","+rc.bottom+")";}
AnsiString __fastcall TRealMetafile::strHex(const int d) {return "0x"+IntToHex(d,4);}
AnsiString __fastcall TRealMetafile::strInt(const int d) {return AnsiString(d);}
AnsiString __fastcall TRealMetafile::strSize(const SIZE &sz) {return AnsiString(sz.cx)+" x "+AnsiString(sz.cy);}
AnsiString __fastcall TRealMetafile::strPointL(const POINTL &pt) {return "("+AnsiString(pt.x)+", "+AnsiString(pt.y)+")";}
AnsiString __fastcall TRealMetafile::strPoint(const POINT &pt) {return "("+AnsiString(pt.x)+", "+AnsiString(pt.y)+")";}
AnsiString __fastcall TRealMetafile::strInt16(const int i) {if (i&0xF000) return AnsiString(-65536+i); else return i;}
AnsiString __fastcall TRealMetafile::strPoint16(const POINT16 &pt) {return "("+AnsiString(pt.x)+", "+AnsiString(pt.y)+")";}
AnsiString __fastcall TRealMetafile::strBool(const BOOL b) {return b?"true":"false";}
AnsiString __fastcall TRealMetafile::strWChar(const WCHAR *t) {return AnsiString(t);}
AnsiString __fastcall TRealMetafile::strByteChar(const BYTE*t) {return AnsiString((char*)t);}
AnsiString __fastcall TRealMetafile::strFloat(const double d)
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
AnsiString __fastcall TRealMetafile::strMapMode(int m)
{ switch (m)
  { case MM_ANISOTROPIC: return "MM_ANISOTROPIC (arbitrary units, arbitrary scale)";
    case MM_HIENGLISH: return "MM_HIENGLISH (1 unit = 0.001 inch, +x right, +y up)";
    case MM_HIMETRIC: return "MM_HIMETRIC (1 unit = 0.01mm, +x right, +y up)";
    case MM_ISOTROPIC: return "MM_ISOTROPIC (arbitrary units, both axes same scale)";
    case MM_LOENGLISH: return "MM_LOENGLISH (1 unit = 0.01 inch, +x right, +y up)";
    case MM_LOMETRIC: return "MM_LOMETRIC (1 unit = 0.1mm, +x right, +y up)";
    case MM_TEXT: return "MM_TEXT (1 unit = 1 pixel, +x right, +y down)";
    case MM_TWIPS: return "MM_TWIPS (1 unit = 1/20th of a printer's point)";
    default: return "UNKNOWN MapMode";
  }
}
AnsiString __fastcall TRealMetafile::strRop2(int m)
{ switch (m)
  { case R2_BLACK: return "R2_BLACK: always 0";
    case R2_COPYPEN: return "R2_COPYPEN: Pixel is the pen color.";
    case R2_MASKNOTPEN: return "R2_MASKNOTPEN: Pixel is a combination of the colors common to both the screen and the inverse of the pen.";
    case R2_MASKPEN: return "R2_MASKPEN: Pixel is a combination of the colors common to both the pen and the screen.";
    case R2_MASKPENNOT: return "R2_MASKPENNOT: Pixel is a combination of the colors common to both the pen and the inverse of the screen.";
    case R2_MERGENOTPEN: return "R2_MERGENOTPEN: Pixel is a combination of the screen color and the inverse of the pen color.";
    case R2_MERGEPEN: return "R2_MERGEPEN: Pixel is a combination of the pen color and the screen color.";
    case R2_MERGEPENNOT: return "R2_MERGEPENNOT: Pixel is a combination of the pen color and the inverse of the screen color.";
    case R2_NOP: return "R2_NOP: Pixel remains unchanged.";
    case R2_NOT: return "R2_NOT: Pixel is the inverse of the screen color.";
    case R2_NOTCOPYPEN: return "R2_NOTCOPYPEN: Pixel is the inverse of the pen color.";
    case R2_NOTMASKPEN: return "R2_NOTMASKPEN: Pixel is the inverse of the R2_MASKPEN color.";
    case R2_NOTMERGEPEN: return "R2_NOTMERGEPEN: Pixel is the inverse of the R2_MERGEPEN color.";
    case R2_NOTXORPEN: return "R2_NOTXORPEN: Pixel is the inverse of the R2_XORPEN color.";
    case R2_WHITE: return "R2_WHITE: Pixel is always 1.";
    case R2_XORPEN: return "R2_XORPEN: Pixel is a combination of the colors in the pen and in the screen, but not in both.";
    default: return "UNKNOWN Rop2";
  }
}
AnsiString __fastcall TRealMetafile::strCharset(BYTE c)
{ switch (c)
  { case ANSI_CHARSET: return "ANSI_CHARSET";
    case DEFAULT_CHARSET: return "DEFAULT_CHARSET";
    case SYMBOL_CHARSET: return "SYMBOL_CHARSET";
    case SHIFTJIS_CHARSET: return "SHIFTJIS_CHARSET";
    case GB2312_CHARSET: return "GB2312_CHARSET";
    case HANGEUL_CHARSET: return "HANGEUL_CHARSET";
    case CHINESEBIG5_CHARSET: return "CHINESEBIG5_CHARSET";
    case OEM_CHARSET: return "OEM_CHARSET";
    case JOHAB_CHARSET: return "JOHAB_CHARSET";
    case HEBREW_CHARSET: return "HEBREW_CHARSET";
    case ARABIC_CHARSET: return "ARABIC_CHARSET";
    case GREEK_CHARSET: return "GREEK_CHARSET";
    case TURKISH_CHARSET: return "TURKISH_CHARSET";
    case THAI_CHARSET: return "THAI_CHARSET";
    case EASTEUROPE_CHARSET: return "EASTEUROPE_CHARSET";
    case RUSSIAN_CHARSET: return "RUSSIAN_CHARSET";
    case MAC_CHARSET: return "MAC_CHARSET";
    case BALTIC_CHARSET: return "BALTIC_CHARSET";
    default: return "***unknown charset***";
  }
}
AnsiString __fastcall TRealMetafile::strOutPrecision(BYTE c)
{ switch (c)
  { case OUT_CHARACTER_PRECIS: return "OUT_CHARACTER_PRECIS";
    case OUT_DEFAULT_PRECIS: return "OUT_DEFAULT_PRECIS";
    case OUT_DEVICE_PRECIS: return "OUT_DEVICE_PRECIS";
    case OUT_OUTLINE_PRECIS: return "OUT_OUTLINE_PRECIS";
    case OUT_RASTER_PRECIS: return "OUT_RASTER_PRECIS";
    case OUT_STRING_PRECIS: return "OUT_STRING_PRECIS";
    case OUT_STROKE_PRECIS: return "OUT_STROKE_PRECIS";
    case OUT_TT_ONLY_PRECIS: return "OUT_TT_ONLY_PRECIS";
    case OUT_TT_PRECIS: return "OUT_TT_PRECIS";
    default: return "***unknown out-precision***";
  }
}
AnsiString __fastcall TRealMetafile::strClipPrecision(BYTE c)
{ switch (c)
  { case CLIP_DEFAULT_PRECIS: return "CLIP_DEFAULT_PRECIS";
    case CLIP_CHARACTER_PRECIS: return "CLIP_CHARACTER_PRECIS";
    case CLIP_STROKE_PRECIS: return "CLIP_STROKE_PRECIS";
    case CLIP_MASK: return "CLIP_MASK";
    case CLIP_EMBEDDED: return "CLIP_EMBEDDED";
    case CLIP_LH_ANGLES: return "CLIP_LH_ANGLES";
    case CLIP_TT_ALWAYS: return "CLIP_TT_ALWAYS";
    default: return "***unknown clip-precision***";
  }
}
AnsiString __fastcall TRealMetafile::strQuality(BYTE c)
{ switch (c)
  { case DEFAULT_QUALITY: return "DEFAULT_QUALITY";
    case DRAFT_QUALITY: return "DRAFT_QUALITY";
    case PROOF_QUALITY: return "PROOF_QUALITY";
    default: return "***unknown quality***";
  }
}
AnsiString __fastcall TRealMetafile::strPitchAndFamily(BYTE c)
{ BYTE a=(BYTE)(c & 0x03);
  BYTE b=(BYTE)(c & 0xF0);
  AnsiString s="";
  switch (a)
  { case DEFAULT_PITCH: s=s+"DEFAULT_PITCH"; break;
    case FIXED_PITCH: s=s+"FIXED_PITCH"; break;
    case VARIABLE_PITCH: s=s+"VARIABLE_PITCH"; break;
    default: s=s+"UnknownPitch";
  }
  switch (b)
  { case FF_DECORATIVE: s=s+",FF_Decorative";break;
    case FF_DONTCARE: s=s+",FF_Don'tCare";break;
    case FF_MODERN: s=s+",FF_Modern";break;
    case FF_ROMAN: s=s+",FF_Roman"; break;
    case FF_SCRIPT: s=s+",FF_Script"; break;
    case FF_SWISS: s=s+",FF_Swiss"; break;
    default: s=s+",FF_UnknownFamily";
  }
  return s;
}
AnsiString __fastcall TRealMetafile::strLogFont(const LOGFONTW &lf)
{ AnsiString s="";
  s=s+"face="+AnsiString(lf.lfFaceName)+" ";
  s=s+"h="+strInt(lf.lfHeight)+" "; if (lf.lfHeight<0) s=s+"(character-height)"; else if (lf.lfHeight==0) s=s+"(default-height)"; else s=s+"(cell-height)"; s=s+" ";
  s=s+"w="+strInt(lf.lfWidth)+" ";
  s=s+"escap="+strInt(lf.lfEscapement)+" ";
  s=s+"orient="+strInt(lf.lfOrientation)+" ";
  s=s+"weight="+strInt(lf.lfWeight)+" "; if (lf.lfWeight==0) s=s+"(default) ";
  s=s+"italic="+strBool(lf.lfItalic)+" ";
  s=s+"underline="+strBool(lf.lfUnderline)+" ";
  s=s+"strikeout="+strBool(lf.lfStrikeOut)+" ";
  s=s+"charset="+strCharset(lf.lfCharSet)+" ";
  s=s+"outprecision="+strOutPrecision(lf.lfOutPrecision)+" ";
  s=s+"clipprecision="+strClipPrecision(lf.lfClipPrecision)+" ";
  s=s+"quality="+strQuality(lf.lfQuality)+" ";
  s=s+"pitchfamily="+strPitchAndFamily(lf.lfPitchAndFamily)+" ";
  return s;
}
AnsiString __fastcall TRealMetafile::strExtFont(const EXTLOGFONTW &elf)
{ AnsiString s="";
  s=s+strLogFont(elf.elfLogFont);
  s=s+"fullname="+strWChar(elf.elfFullName)+" ";
  s=s+"style="+strWChar(elf.elfStyle)+" ";
  s=s+"ver="+strHex(elf.elfVersion)+" ";
  s=s+"stylesyze="+strInt(elf.elfStyleSize)+" ";
  s=s+"match="+strInt(elf.elfMatch)+" ";
  s=s+"vendor="+strByteChar(elf.elfVendorId)+" ";
  s=s+"culture="+strInt(elf.elfCulture)+" ";
  return s;
}
AnsiString __fastcall TRealMetafile::strTextAlign(const int a)
{ AnsiString s="";
  int update=(a&1);
  int horiz=(a&6);
  int vert=(a&24);
  int dir=(a&256);
  if (update==TA_NOUPDATECP) s=s+"NoUpdateCP "; else s=s+"UpdateCP ";
  if (horiz==TA_LEFT) s=s+"Left "; else if (horiz==TA_RIGHT) s=s+"Right "; else s=s+"Center ";
  if (vert==TA_TOP) s=s+"Top "; else if (vert==TA_BOTTOM) s=s+"Bottom "; else s=s+"Baseline ";
  if (dir==TA_RTLREADING) s=s+"RightToLeft "; else s=s+"LeftToRight";
  return s;
}
AnsiString __fastcall TRealMetafile::strBkMode(const int m)
{ if (m==OPAQUE) return "OPAQUE"; else if (m==TRANSPARENT) return "TRANSPARENT"; else return "***DunnoBk***";
}
AnsiString __fastcall TRealMetafile::strColorRef(const COLORREF &cr)
{ return AnsiString("r=")+GetRValue(cr)+" g="+GetGValue(cr)+" b="+GetBValue(cr);
}
AnsiString __fastcall TRealMetafile::strLogPenStyle(int s)
{ switch (s)
  { case PS_SOLID: return "Solid";
    case PS_DASH: return "Dashed";
    case PS_DOT: return "Dotted";
    case PS_DASHDOT: return "DashDot";
    case PS_DASHDOTDOT: return "DashDashDot";
    case PS_NULL: return "Invisible";
    case PS_INSIDEFRAME: return "SolidGeometricPensShrinkInsideFrame";
    default: return "***unknown-pen-style***";
  }
}
AnsiString __fastcall TRealMetafile::strLogPen(const LOGPEN &lp)
{ AnsiString s="";
  s=s+"style="+strLogPenStyle(lp.lopnStyle)+" ";
  s=s+"width="+strPoint(lp.lopnWidth)+" ";
  s=s+"col="+strColorRef(lp.lopnColor)+" ";
  return s;
}
AnsiString __fastcall TRealMetafile::strLogBrushStyle(int s)
{ switch (s)
  { case BS_DIBPATTERN: return "DIBPatternBrush";
    case BS_DIBPATTERN8X8: return "DIBPattern8x8";
    case BS_DIBPATTERNPT: return "DIBPatternPt";
    case BS_HATCHED: return "Hatched";
    case BS_HOLLOW: return "Hollow";
    case BS_PATTERN: return "Patterned";
    case BS_PATTERN8X8: return "Patterned8X8";
    case BS_SOLID: return "Solid";
    default: return "***unknown-brush-style***";
  }
}
AnsiString __fastcall TRealMetafile::strBrushHatch(LONG h)
{ switch (h)
  { case HS_BDIAGONAL: return "45-degree upward, left-to-right hatch";
    case HS_CROSS: return "Horizontal and vertical cross-hatch";
    case HS_DIAGCROSS: return "45-degree crosshatch";
    case HS_FDIAGONAL: return "A 45-degree downward, left-to-right hatch";
    case HS_HORIZONTAL: return "Horizontal hatch";
    case HS_VERTICAL: return "Vertical hatch";
    default: return "***unknown-hatch***";
  }
}
AnsiString __fastcall TRealMetafile::strLogBrush(const LOGBRUSH &lb)
{ AnsiString s="";
  s=s+"style="+strLogBrushStyle(lb.lbStyle)+" ";
  s=s+"col="+strColorRef(lb.lbColor)+" ";
  if (lb.lbStyle==BS_DIBPATTERN || lb.lbStyle==BS_DIBPATTERN8X8) s=s+"(+DIB-handle-data) ";
  if (lb.lbStyle==BS_DIBPATTERNPT) s=s+"(+pointer-to-DIB) ";
  if (lb.lbStyle==BS_PATTERN || lb.lbStyle==BS_PATTERN8X8) s=s+"(+BITMAP-data) ";
  if (lb.lbStyle==BS_HATCHED) s=s+"hatch="+strBrushHatch(lb.lbHatch)+" ";
  return s;
}
AnsiString __fastcall TRealMetafile::strPolyFillMode(const int m)
{ if (m==ALTERNATE) return "ALTERNATE"; else if (m==WINDING) return "WINDING"; else return "***unknown***";
}
AnsiString __fastcall TRealMetafile::strObject(const int i)
{ if  ((i&0x80000000)==0) return AnsiString("(")+i+")";
  int s=i&0x7FFFFFFF;
  switch (s)
  { case WHITE_BRUSH: return "WHITE_BRUSH";
    case LTGRAY_BRUSH: return "LTGRAY_BRUSH";
    case DKGRAY_BRUSH: return "DKGRAY_BRUSH";
    case BLACK_BRUSH: return "BLACK_BRUSH";
    case NULL_BRUSH: return "NULL_BRUSH";
    case WHITE_PEN: return "WHITE_PEN";
    case BLACK_PEN: return "BLACK_PEN";
    case NULL_PEN: return "NULL_PEN";
    case OEM_FIXED_FONT: return "OEM_FIXED_FONT";
    case ANSI_FIXED_FONT: return "ANSI_FIXED_FONT";
    case ANSI_VAR_FONT: return "ANSI_VAR_FONT";
    case SYSTEM_FONT: return "SYSTEM_FONT";
    case DEVICE_DEFAULT_FONT: return "DEVICE_DEFAULT_FONT";
    case DEFAULT_PALETTE: return "DEFAULT_PALETTE";
    case SYSTEM_FIXED_FONT: return "SYSTEM_FIXED_FONT";
    case DEFAULT_GUI_FONT: return "DEFAULT_GUI_FONT";
    default: return "***UnknownStockObject***";
  }
}
AnsiString __fastcall TRealMetafile::strPolyLine16(int npt,POINT16 *pt)
{ AnsiString s="";
  int max=8; if (max<npt) max=npt;
  for (int i=0; i<max; i++) s=s+strPoint16(pt[i])+".";
  if (npt>max) s=s+"...";
  return s;
}

//---------------------------------------------------------------------------

AnsiString __fastcall TRealMetafile::strEmrHeader(const ENHMETAHEADER *rec)
{ AnsiString s="WMF-HEADER. ";
  s=s+"Bounds="+strRect(rec->rclBounds)+" du. ";
  s=s+"Frame="+strRect(rec->rclFrame)+" 0.01mm. ";
  s=s+"DeviceRes="+strSize(rec->szlDevice)+"pix. ";
  s=s+strSize(rec->szlMillimeters)+"mm. ";
  return s;
}
AnsiString __fastcall TRealMetafile::strEmrGdiComment(const EMRGDICOMMENT *rec)
{ return "GDI-COMMENT: (ignored)";
}
AnsiString __fastcall TRealMetafile::strEmrSetMapMode(const EMRSETMAPMODE *rec)
{ AnsiString s="SETMAPMODE: "+strMapMode(rec->iMode); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSetViewportExtEx(const EMRSETWINDOWEXTEX *rec)
{ AnsiString s="SET-VIEWPORT-EXT-EX: ViewportExtent = ";
  s=s+strSize(rec->szlExtent); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSetWindowExtEx(const EMRSETWINDOWEXTEX *rec)
{ AnsiString s="SET-WINDOW-EXT-EX: WindowExtent = ";
  s=s+strSize(rec->szlExtent); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSetRop2(const EMRSETMAPMODE *rec)
{ AnsiString s="SETROP2: ";
  s=s+strRop2(rec->iMode); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSetViewportOrgEx(const EMRSETWINDOWORGEX *rec)
{ AnsiString s="SET-VIEWPORT-ORG-EX: viewport-origin = "+strPointL(rec->ptlOrigin); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSetWindowOrgEx(const EMRSETWINDOWORGEX *rec)
{ AnsiString s="SET-WINDOW-ORG-EX: window-origin = "+strPointL(rec->ptlOrigin); return s;
}
AnsiString __fastcall TRealMetafile::strEmrExtCreateFontIndirectW(const EMREXTCREATEFONTINDIRECTW *rec)
{ AnsiString s="CREATEFONT "+strInt(rec->ihFont);
  s=s+": "+strExtFont(rec->elfw); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSelectObject(const EMRSELECTOBJECT *rec)
{ AnsiString s="SELECTOBJECT "+strObject(rec->ihObject); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSetTextAlign(const EMRSETMAPMODE *rec)
{ AnsiString s="SETTEXTALIGN: ";
  s=s+strTextAlign(rec->iMode); return s;
}
AnsiString __fastcall TRealMetafile::strEmrSetBkMode(const EMRSETMAPMODE *rec)
{ return "SETBKMODE: "+strBkMode(rec->iMode);
}
AnsiString __fastcall TRealMetafile::strEmrSetTextColor(const EMRSETTEXTCOLOR *rec)
{ return "SETTEXTCOLOR: "+strColorRef(rec->crColor);
}
AnsiString __fastcall TRealMetafile::strEmrExtTextOutW(const EMREXTTEXTOUTA *rec)
{ AnsiString s="TEXTOUT: ";
  EMRTEXT *emr=(EMRTEXT*)&rec->emrtext;
  wchar_t *wstr=(wchar_t*)((BYTE*)rec+emr->offString);
  AnsiString str=WideCharToString(wstr);
  s=s+"\""+str+"\""+" ";
  s=s+" bounds="+strRect(rec->rclBounds)+". ";
  if (rec->iGraphicsMode==GM_ADVANCED) s=s+"(advanced). ";
  else s=s+"(compatible, xscale="+strFloat(rec->exScale)+" yscale="+strFloat(rec->eyScale)+"). ";
  s=s+"refpoint="+strPointL(emr->ptlReference)+" numchars="+strInt(emr->nChars)+". ";
  if (emr->fOptions!=0)
  { if (emr->fOptions & ETO_CLIPPED) s=s+"Clipped. ";
    if (emr->fOptions & ETO_OPAQUE) s=s+"Opaque. ";
    s=s+" to "+strRect(emr->rcl)+". ";
  }
  return s;
}
AnsiString __fastcall TRealMetafile::strEmrCreatePen(const EMRCREATEPEN *rec)
{ return "CREATEPEN "+strInt(rec->ihPen)+": "+strLogPen(rec->lopn);
}
AnsiString __fastcall TRealMetafile::strEmrSetPolyFillMode(const EMRSETMAPMODE *rec)
{ return "SETPOLYFILLMODE: "+strPolyFillMode(rec->iMode);
}
AnsiString __fastcall TRealMetafile::strEmrPolyPolygon16(const EMRPOLYPOLYLINE16 *rec)
{ AnsiString s="POLYPOLYGON16: bounds="+strRect(rec->rclBounds)+"du npolys=";
  s=s+strInt(rec->nPolys);
  POINT16 *pt=(POINT16*)rec->apts;
  int pti=0;
  DWORD *count=(DWORD*)rec->aPolyCounts;
  for (int poly=0; poly<(int)rec->nPolys; poly++)
  { int npt=count[poly];
    s=s+strPolyLine16(npt,&(pt[pti]));
    pti=pti+npt;
  }
  return s;
}
AnsiString __fastcall TRealMetafile::strEmrCreateBrushIndirect(const EMRCREATEBRUSHINDIRECT *rec)
{
//AliSoft return "CREATEBRUSH "+strInt(rec->ihBrush)+": "+strLogBrush(rec->lb);
 LOGBRUSH lb;
 lb.lbStyle=rec->lb.lbStyle;
 lb.lbColor=rec->lb.lbColor;
 lb.lbHatch=rec->lb.lbHatch;
 return "CREATEBRUSH "+strInt(rec->ihBrush)+": "+strLogBrush(lb);
}
AnsiString __fastcall TRealMetafile::strEmrPolygon16(const EMRPOLYBEZIER16 *rec)
{ AnsiString s="POLYGON16: bounds="+strRect(rec->rclBounds)+"du. ";
  s=s+strPolyLine16(rec->cpts,(POINT16*)rec->apts);
  return s;
}
AnsiString __fastcall TRealMetafile::strEmrDeleteObject(const EMRSELECTOBJECT *rec)
{ return "DELETEOBJECT "+strInt(rec->ihObject);
}
AnsiString __fastcall TRealMetafile::strEmrPolyLine16(const EMRPOLYBEZIER16 *rec)
{ AnsiString s="POLYLINE16: bounds="+strRect(rec->rclBounds)+"du. ";
  s=s+strPolyLine16(rec->cpts,(POINT16*)rec->apts);
  return s;
}
AnsiString __fastcall TRealMetafile::strEmrSelectPalette(const EMRSELECTPALETTE *rec)
{ return "SELECTPALETTE "+strInt(rec->ihPal);
}
AnsiString __fastcall TRealMetafile::strEmrExtSelectClipRgn(const EMREXTSELECTCLIPRGN *rec)
{ return "EXTSELECTCLIPRGN: (+region-data)";
}
AnsiString __fastcall TRealMetafile::strEmrEof(const EMREOF *rec)
{ return "END-OF-EMF";
}




AnsiString __fastcall TRealMetafile::strWmrSelectObject(const METARECORD *rec)
{ AnsiString s="SELECTOBJECT "+strObject(rec->rdParm[0]); return s;
}


//---------------------------------------------------------------------------
namespace Wmfeps_utils_realmeta
{ void __fastcall PACKAGE Register()
  { TComponentClass classes[1] = {__classid(TRealMetafile)};
    RegisterComponents("System", classes, 0);
  }
}
//---------------------------------------------------------------------------



