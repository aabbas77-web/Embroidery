#include "wmf2tex.h"
#pragma hdrstop

#include "f_testmf.h"
#include "wmfeps_utils_RealMeta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{ rm=new TRealMetafile(this);
  bOpenClick(this);
}
__fastcall TForm1::~TForm1()
{ if (rm!=NULL) delete rm; rm=NULL;
}
void __fastcall TForm1::Update()
{ AnsiString s="";
  if (rm->State==rmsNormal)
  { if (rm->Enhanced) s=s+"EMF: "; else s=s+"WMF: ";
    double mmWidth=((double)rm->MMWidth)/100.0;
    double mmHeight=((double)rm->MMHeight)/100.0;
    s=s+FormatFloat("0.00",mmWidth);
    s=s+"mm x ";
    s=s+FormatFloat("0.00",mmHeight);
    s=s+"mm";
  }
  StatusBar->SimpleText=s;
  PaintBox->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bOpenClick(TObject *Sender)
{ rm->LoadFromFile(FileName->Text);
  Update();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBoxPaint(TObject *Sender)
{ if (rm->State==rmsNormal)
  { rm->PlayIntoCanvas(PaintBox->Canvas,0,0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FileNameClick(TObject *Sender)
{ bOpenClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bPasteClick(TObject *Sender)
{ rm->LoadFromClipboard();
  Update();
}
//---------------------------------------------------------------------------

TMemo *m;
void __fastcall TForm1::EnumWmr(TRealMetafile *Sender,const METARECORD *rec,TEnumAction &Action)
{ m->Lines->Add(rm->RecordString);
}
void __fastcall TForm1::EnumEmr(TRealMetafile *Sender,const ENHMETARECORD *rec,TEnumAction &Action)
{ m->Lines->Add(rm->RecordString);
}
void __fastcall TForm1::ShowFormClose(TObject *Sender, TCloseAction &Action) {Action=caFree;}
void __fastcall TForm1::bEnumClick(TObject *Sender)
{ TForm *f=new TForm(this);
  f->Caption="Enum";
  m=new TMemo(f);
  m->Parent=f;
  m->Align=alClient;
  m->ScrollBars=ssBoth;
  f->Show();
  m->Lines->BeginUpdate();
  rm->OnWmr=EnumWmr;
  rm->OnEmr=EnumEmr;
  rm->OnWmrTextOut=NULL;
  rm->OnEmrExtTextOutW=NULL;
  rm->Enum();
  m->Lines->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bSaveEmfClick(TObject *Sender)
{ rm->Enhanced=true;
  rm->SaveToFile(SaveFileName->Text);
  Update();
}
void __fastcall TForm1::bSaveWmfClick(TObject *Sender)
{ rm->Enhanced=false;
  rm->SaveToFile(SaveFileName->Text);
  Update();
}
void __fastcall TForm1::bCopyClick(TObject *Sender)
{ rm->SaveToClipboard();
}
void __fastcall TForm1::bClearClick(TObject *Sender)
{ rm->Clear(); Update();
}
void __fastcall TForm1::bEnhancedClick(TObject *Sender)
{ rm->Enhanced=!rm->Enhanced; Update();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bStripLatexClick(TObject *Sender)
{ rm->OnWmr=NULL;
  rm->OnEmr=NULL;
  rm->OnWmrTextOut=OnWmrTextOut;
  rm->OnEmrExtTextOutW=OnEmrExtTextOutW;
  TRealMetafile *nm=new TRealMetafile(this);
  rm->EnumToMetafile(nm,true);
  delete rm;
  rm=nm;
  Update();
}
void __fastcall TForm1::OnWmrTextOut(TRealMetafile *Sender,const METARECORD *rec,TEnumAction &Action)
{ if (AnsiString(Sender->CurrentFont.lfFaceName).LowerCase().Pos("latex")!=0) Action=enumDiscard;
}
void __fastcall TForm1::OnEmrExtTextOutW(TRealMetafile *Sender,const EMREXTTEXTOUTW *rec,TEnumAction &Action)
{ if (AnsiString(Sender->CurrentFont.lfFaceName).LowerCase().Pos("latex")!=0) Action=enumDiscard;
}

//---------------------------------------------------------------------------

