#ifndef __EpsGenH
#define __EpsGenH
#include <vcl\graphics.hpp>

class TEpsPrinterDevice : public TObject
{
public:
  __fastcall TEpsPrinterDevice(char *ADevice);
  virtual __fastcall ~TEpsPrinterDevice();
  bool __fastcall IsEqual(char *ADevice);
  AnsiString Device;
};


class TEpsGenerator : public TComponent
{
public:
  __fastcall TEpsGenerator(TComponent *Owner);
  __fastcall ~TEpsGenerator();
  void __fastcall BeginDoc();
  void __fastcall EndDoc(const TRect &rc); // bbox in logical units
  void __fastcall AbortDoc();
  __property TCanvas* Canvas = {read=FCanvas,write=FCanvas};
  __property int PrinterIndex = {read=FPrinterIndex,write=SetPrinterIndex};
  __property TStrings *Printers = {read=FPrinters};
__published:
  __property AnsiString FileName = {read=FFileName,write=FFileName};
protected:
  bool __fastcall CloseDoc();
  AnsiString FFileName;
  TCanvas *FCanvas;
  bool StartedDoc, StartedPage;
  int FPrinterIndex;
  HDC Fdc;
  TStrings *FPrinters;
  void __fastcall SetPrinterIndex(int i);
  TEpsPrinterDevice* __fastcall GetSelectedPrinter();
  void __fastcall SetupPrinterList();
  int idPrintJob;
  HANDLE __fastcall OpenPrinterHandle();
};



#endif