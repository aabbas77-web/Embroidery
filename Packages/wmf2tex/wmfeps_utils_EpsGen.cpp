//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <winspool.h>
#include <vcl\printers.hpp>
#include <math.h>
#include "wmfeps_utils_EpsGen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------


__fastcall TEpsPrinterDevice::TEpsPrinterDevice(char *ADevice) : TObject()
{ Device=AnsiString(ADevice);
}
__fastcall TEpsPrinterDevice::~TEpsPrinterDevice()
{
}
bool __fastcall TEpsPrinterDevice::IsEqual(char *ADevice)
{ if (AnsiString(ADevice)!=Device) return false;
  return true;
}


__fastcall TEpsGenerator::TEpsGenerator(TComponent *Owner) : TComponent(Owner)
{ FFileName="";
  FCanvas=NULL;
  StartedDoc=false; StartedPage=false;
  idPrintJob=0;
  FPrinters=new TStringList(); SetupPrinterList();
}
__fastcall TEpsGenerator::~TEpsGenerator()
{ AbortDoc();
  if (FPrinters!=NULL)
  { for (int i=0; i<FPrinters->Count; i++)
    { TEpsPrinterDevice *pd=(TEpsPrinterDevice*)FPrinters->Objects[i];
      if (pd!=NULL) delete pd; FPrinters->Objects[i]=NULL;
    }
    delete FPrinters; FPrinters=NULL;
  }
}
void __fastcall TEpsGenerator::SetupPrinterList()
{ DWORD needed=0, returned=0;
  EnumPrinters(PRINTER_ENUM_LOCAL,NULL,5,NULL,0,&needed,&returned);
  if (needed==0) throw new EPrinter("Unable to begin to enum printers");
  char *c=new char[needed];
  BOOL res=EnumPrinters(PRINTER_ENUM_LOCAL,NULL,5,(BYTE*)c,needed,&needed,&returned);
  if (!res) {delete[] c; throw new EPrinter("Unable to enum printers");}
  PRINTER_INFO_5 *pi=(PRINTER_INFO_5 *)c;
  for (int i=0; i<(int)returned; i++)
  { char *pname=pi[i].pPrinterName; // we're only interested in the device.
    TEpsPrinterDevice *pd=new TEpsPrinterDevice(pname);
    FPrinters->AddObject(pname,pd);
  }
}
void __fastcall TEpsGenerator::SetPrinterIndex(int i)
{ AbortDoc();
  FPrinterIndex=i;
}
TEpsPrinterDevice* __fastcall TEpsGenerator::GetSelectedPrinter()
{ if (FPrinterIndex!=-1) return (TEpsPrinterDevice*)FPrinters->Objects[PrinterIndex];
  // otherwise search through the windows ini file for it
  char DefaultPrinter[80];
  GetProfileString("windows","device","", DefaultPrinter,sizeof(DefaultPrinter)-1);
  // the ini string looks like this: device=HP LaserJet III,HPPCL5MS,LPT1:
  // We're only interested in the first bit, having removed leading spaces
  char *c=DefaultPrinter; while (*c==' ') c++;
  char *cDevice=c; while (*c!=0 && *c!=',') c++; if (*c==',') *c=0;
  AnsiString Device=AnsiString(cDevice);
  // There it is. Device will be something like 'HP Laserject III'
  for (int i=0; i<Printer()->Printers->Count; i++)
  { TEpsPrinterDevice *pd=(TEpsPrinterDevice*)Printers->Objects[i];
    if (pd->Device==Device) return pd;
  }
  return NULL;
}
HANDLE __fastcall TEpsGenerator::OpenPrinterHandle()
{ TEpsPrinterDevice *pd=(TEpsPrinterDevice*)Printers->Objects[PrinterIndex];
  if (pd==NULL) throw new EPrinter("No default printer");
  HANDLE hPrinter=NULL; BOOL bres=OpenPrinter(pd->Device.c_str(),&hPrinter,NULL);
  if (!bres) throw new EPrinter("Cannot open selected printer");
  return hPrinter;
}
void __fastcall TEpsGenerator::BeginDoc()
{ AbortDoc();
  // first figure open the printer
  TEpsPrinterDevice *pd=GetSelectedPrinter();
  HANDLE hPrinter=OpenPrinterHandle();
  LONG dms=DocumentProperties(NULL,hPrinter,pd->Device.c_str(),NULL,NULL,0);
  char *devmode=new char[dms];
  LONG lres=DocumentProperties(NULL,hPrinter,pd->Device.c_str(),(DEVMODE*)devmode,NULL,DM_OUT_BUFFER);
  ClosePrinter(hPrinter);
  if (lres<0) {delete[] devmode; throw new EPrinter("Cannot get printer properties");}
  Fdc=CreateDC(NULL,pd->Device.c_str(),NULL,(DEVMODE*)devmode);
  delete[] devmode;
  if (Fdc==NULL) {AbortDoc(); throw new EPrinter("Invalid printer");}
  DOCINFO docinfo; ZeroMemory(&docinfo,sizeof(docinfo)); docinfo.cbSize=sizeof(docinfo);
  docinfo.lpszDocName=FileName.c_str();
  docinfo.lpszOutput=FileName.c_str();
  docinfo.lpszDatatype="Metafile";
  docinfo.fwType=0;
  //SetAbortProc(DC, AbortProc);
  int ires=::StartDoc(Fdc,&docinfo);
  if (ires<=0) {AbortDoc(); throw new EPrinter("Cannot start document");}
  StartedDoc=true;
  idPrintJob=ires;
  ires=::StartPage(Fdc);
  if (ires<=0) {AbortDoc(); throw new EPrinter("Cannot start page");}
  StartedPage=true;
  FCanvas=new TCanvas();
  FCanvas->Handle=Fdc;
}
void __fastcall TEpsGenerator::AbortDoc()
{ bool res=CloseDoc();
  if (res) DeleteFile(FileName.c_str());
}
bool __fastcall TEpsGenerator::CloseDoc()
{ if (FCanvas!=NULL)
  { delete FCanvas;
    FCanvas=NULL;
  }
  if (StartedPage)
  { ::EndPage(Fdc);
    StartedPage=false;
  }
  if (StartedDoc)
  { ::EndDoc(Fdc);
    StartedDoc=false;
  }
  if (Fdc!=NULL)
  { DeleteDC(Fdc);
    Fdc=NULL;
  }
  if (idPrintJob==0) return false;
  HANDLE hPrinter=OpenPrinterHandle();
  JOB_INFO_1 ji; ZeroMemory(&ji,sizeof(ji));
  DWORD needed=0;
  BOOL res=true;
  while (res)
  { res=GetJob(hPrinter,idPrintJob,1,(LPBYTE)&ji,sizeof(ji),&needed);
  }
  idPrintJob=0;
  return true;
}
void __fastcall TEpsGenerator::EndDoc(const TRect &wrc)
{ if (Fdc==NULL) {CloseDoc(); throw new EPrinter("Failed to generate a document");}
  // Will have to convert bbox to postscript units
  // now vrc is in terms of the viewport coordinates
  RECT rc; rc.left=wrc.Left; rc.top=wrc.Top; rc.right=wrc.Right; rc.bottom=wrc.Bottom;
  LPtoDP(Fdc,(POINT*)&rc,2); // to convert logical points to device points
  int pageLeft=GetDeviceCaps(Fdc,PHYSICALOFFSETX); // again, all these
  int pageTop=GetDeviceCaps(Fdc,PHYSICALOFFSETY);  // are in device
  int pageHeight=GetDeviceCaps(Fdc,PHYSICALHEIGHT);  // units
  RECT erc;
  erc.left=pageLeft+rc.left;
  erc.top=-pageHeight+pageTop+rc.top;
  erc.right=pageLeft+rc.right;
  erc.bottom=-pageHeight+pageTop+rc.bottom;
  SetMapMode(Fdc,MM_TWIPS);
  DPtoLP(Fdc,(POINT*)&erc,2); // erc now has the bounding box in twips
  erc.left=erc.left/20; erc.top=erc.top/20; // so divide by twenty to get it in points
  erc.right=erc.right/20; erc.bottom=erc.bottom/20;
  //
  bool res=CloseDoc();
  if (!res) throw new EPrinter("Failed to generate a document");TStringList *lines=new TStringList();
  //
  lines->LoadFromFile(FileName);
  if (lines->Strings[0].SubString(1,10)!="%!PS-Adobe"
    ||lines->Strings[5].SubString(1,13)!="%%BoundingBox")
  { delete lines; throw new EPrinter("Not a postscript file!");
  }
  //
  // Now tidy up the eps.
  // 1. we change the heading so it says 'EPSF' instead of 'PS'
  // 2. Add the bounding box which we calculated above.
  // 3. Remove reserved words. I don't have a clue here.
  // By experimentation I noticed that if you remove the %%BeginSetup .. %%EndSetup block
  // (which occurs before the first %%Page) then, at least with my Apple LaserwriterII NT
  // printer driver, it removes the offending statusdict and the rest works.
  lines->Strings[0]="%!PS-Adobe-3.0 EPSF-3.0";
  lines->Strings[5]=AnsiString("%%BoundingBox: ")+erc.left+" "+erc.bottom+" "+erc.right+" "+erc.top;
  int i=22; bool foundpage=false; int DeleteFirst=-1, DeleteLast=-1;
  while (i<lines->Count && !foundpage && DeleteLast==-1)
  { AnsiString s=lines->Strings[i];
    if (s.SubString(1,12)=="%%BeginSetup")
    { DeleteFirst=i;
    }
    if (s.SubString(1,10)=="%%EndSetup")
    { DeleteLast=i;
    }
    if (s.SubString(1,6)=="%%Page")
    { foundpage=true;
    }
    i++;
  }
  if (DeleteFirst!=-1 && DeleteLast!=-1)
  { for (int i=DeleteLast; i>=DeleteFirst; i--) lines->Delete(i);
  }
  //
  lines->SaveToFile(FileName);
  delete lines;

}



//---------------------------------------------------------------------------
namespace Wmfeps_utils_epsgen
{ void __fastcall PACKAGE Register()
  { TComponentClass classes[1] = {__classid(TEpsGenerator)};
    RegisterComponents("Additional", classes, 0);
  }
}
//---------------------------------------------------------------------------





