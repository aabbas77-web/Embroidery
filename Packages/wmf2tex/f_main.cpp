#include "wmf2tex.h"
#pragma hdrstop
#include "wmfeps_utils_shellink.h"
#include "wmfeps_utils_RealMeta.h"

#include "f_main.h"
#include "f_clip.h"
#include "f_hen.h"
#include "f_custom.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "wmfeps_utils_shellink"
#pragma link "wmfeps_utils_EpsGen"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

const char *StandardExt[6] = {"wmf","emf","eps","tex","tex","tex"};
const char *StandardOutputType[6] = {"Wmf","Emf","Eps","TexWmf","TexEps","TexEpic"};

__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{ bInitialized=false;
}
__fastcall TMainForm::~TMainForm()
{ if (bHaveInstalledClipboardViewer)
  { ChangeClipboardChain(hThisClipboardViewer, hNextClipboardViewer);
    bHaveInstalledClipboardViewer=false;
  }
  if (hThisClipboardViewer!=NULL) DeallocateHWnd(hThisClipboardViewer); hThisClipboardViewer=NULL;
}
void __fastcall TMainForm::Initialize()
{ if (bInitialized) return;
  bInitialized=true;
  tePrinters->Items->Assign(EpsPrinterLister->Printers);
  PrinterIndex=-1; tePrinters->ItemIndex=-1;
  SetOutputFormat("TexWmf");
  tteWmf->Lines->Text=tteDefWmf->Lines->Text;
  tteEps->Lines->Text=tteDefEps->Lines->Text;
  // a principle is that setting these radio buttons on any other page
  // causes these buttons to be set.
  // On the clipboard page, we will set these buttons first and the wmf/emf
  // buttons next, to allow them to override.
  AnsiString DesktopPath=SHGetSpecialFolderLocationString(CSIDL_DESKTOP);
  tceDirectory->Text=DesktopPath;
  tfeInFile->Text=DesktopPath+"\\*.?mf";
  tfCurrentPreview="";
  //
  LoadRegistry();
  hThisClipboardViewer=AllocateHWnd(ClipboardViewerProc);
  bHaveInstalledClipboardViewer=false;
  bClipboardViewValid=false;
  if (!bHaveInstalledClipboardViewer)
  { hNextClipboardViewer=SetClipboardViewer(hThisClipboardViewer);
    bHaveInstalledClipboardViewer=true;
  }
}

void __fastcall TMainForm::LoadRegistry()
{ TRegistry *reg=new TRegistry();
  bool res=reg->OpenKey("\\Software\\Lu\\wmf2tex",false);
  if (!res) {delete reg; return;}
  //
  try
  { AnsiString s=reg->ReadString("PrinterDriver");
    for (int i=0; i<EpsPrinterLister->Printers->Count; i++)
    { if (s==EpsPrinterLister->Printers->Strings[i]) PrinterIndex=i;
    }
    tePrinters->ItemIndex=PrinterIndex;
  } catch (...) {}
  //
  try
  { AnsiString s=reg->ReadString("OutputFormat");
    SetOutputFormat(s);
  } catch (...) {}
  try
  { AnsiString s=reg->ReadString("OutputFormatClipboard");
    SetOutputFormat(s);
  } catch (...) {}
  //
  try
  { int i=reg->ReadInteger("SaveOnClipboardChange");
    tccSaveOnClipboardChange->Checked=(i==1);
    EnableSaveOnClipboardChange();
  } catch (...) {}
  //
  try
  { int i=reg->ReadInteger("SilentAutoSaves");
    if (i==1) tcrSilent->Checked=true; else tcrPrompt->Checked=true;
  } catch (...) {}
  //
  try
  { AnsiString s=reg->ReadString("SaveClipboardName");
    tceDirectory->Text=ExtractFilePathWithoutSlash(s);
    tceFileName->Text=ExtractFilePrefix(s);
  } catch (...) {}
  //
  try
  { AnsiString s=reg->ReadString("TexWmfCode");
    AnsiString t=reg->ReadString("TexEpsCode");
    //tteWmf->Lines->Text=s;
    //tteEps->Lines->Text=t;
  } catch (...) {}
  //
  try
  { AnsiString s=reg->ReadString("FileIn");
    AnsiString t=reg->ReadString("FileOut");
    int i=reg->ReadInteger("FileOutElsewhere");
    tfeInFile->Text=s;
    tfeOutFile->Text=t;
    tfcOutElsewhere->Checked=(i==1);
  } catch (...) {}
  tfEnableElsewhere();
  //
  delete reg;
}

void __fastcall TMainForm::SaveRegistry()
{ TRegistry *reg=new TRegistry(); AnsiString s; int i;
  bool res=reg->OpenKey("\\Software\\Lu\\wmf2tex",true);
  if (!res) {delete reg; return;}
  //
  if (PrinterIndex==-1) s=""; else s=EpsPrinterLister->Printers->Strings[PrinterIndex];
  reg->WriteString("PrinterDriver",s);
  //
  s="";
  if (torEps->Checked) s="Eps";
  else if (torTexWmf->Checked) s="TexWmf";
  else if (torTexEps->Checked) s="TexEps";
  else if (torTexEpic->Checked) s="TexEpic";
  reg->WriteString("OutputFormat",s);
  s="";
  if (tcrWmf->Checked) s="Wmf";
  else if (tcrEmf->Checked) s="Emf";
  reg->WriteString("OutputFormatClipboard",s);
  //
  if (tccSaveOnClipboardChange->Checked) i=1; else i=0;
  reg->WriteInteger("SaveOnClipboardChange",i);
  //
  if (tcrSilent->Checked) i=1; else i=0;
  reg->WriteInteger("SilentAutoSaves",i);
  //
  s=tceDirectory->Text+"\\"+tceFileName->Text;
  reg->WriteString("SaveClipboardName",s);
  //
  reg->WriteString("TexWmfCode",tteWmf->Lines->Text);
  reg->WriteString("TexEpsCode",tteEps->Lines->Text);
  //
  reg->WriteString("FileIn",tfeInFile->Text);
  reg->WriteString("FileOut",tfeOutFile->Text);
  if (tfcOutElsewhere->Checked) i=1; else i=0;
  reg->WriteInteger("FileOutElsewhere",i);
  //
  delete reg;
}
void __fastcall TMainForm::SetOutputFormat(AnsiString s)
{ if (s=="Eps") {torEps->Checked=true; tcrEps->Checked=true; tceSuffix->Text="EPS"; tfrEps->Checked=true;}
  else if (s=="Wmf") {tcrWmf->Checked=true; tceSuffix->Text="WMF";}
  else if (s=="Emf") {tcrEmf->Checked=true; tceSuffix->Text="EMF";}
  else if (s=="TexWmf") {torTexWmf->Checked=true; tcrTexWmf->Checked=true; tceSuffix->Text="TEX, WMF"; tfrTexWmf->Checked=true;}
  else if (s=="TexEps") {torTexEps->Checked=true; tcrTexEps->Checked=true; tceSuffix->Text="TEX, EPS"; tfrTexEps->Checked=true;}
  else if (s=="TexEpic") {torTexEpic->Checked=true; tcrTexEpic->Checked=true; tceSuffix->Text="TEX"; tfrTexEpic->Checked=true;}
}
int __fastcall TMainForm::GetClipboardOutputFormat()
{ if (tcrWmf->Checked) return 0;
  if (tcrEmf->Checked) return 1;
  if (tcrEps->Checked) return 2;
  if (tcrTexWmf->Checked) return 3;
  if (tcrTexEps->Checked) return 4;
  if (tcrTexEpic->Checked) return 5;
  return 0;
}
void __fastcall TMainForm::EnableSaveOnClipboardChange()
{ bool b=tccSaveOnClipboardChange->Checked;
  tcrPrompt->Enabled=b;
  tcrSilent->Enabled=b;
  tceDirectory->Enabled=b;
  tceFileName->Enabled=b;
  tcbBrowse->Enabled=b;
  tceNumber->Enabled=b;
  tceSuffix->Enabled=b;
  tclDirectory->Enabled=b;
  tclFiles->Enabled=b;
}
void __fastcall TMainForm::SaveType(TRealMetafile *mf,AnsiString fn,int i)
{ TProc *p=new TProc(this);
  p->EpsGenerator->PrinterIndex=PrinterIndex;
  p->TexWmfSource->Lines->Text=tteWmf->Lines->Text;
  p->TexEpsSource->Lines->Text=tteEps->Lines->Text;
  p->SaveType(this,mf,fn,i);
  delete p;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClipboardViewerProc(TMessage &Msg)
{ if (Msg.Msg==WM_CHANGECBCHAIN)
  { if ((HWND)Msg.WParam==hNextClipboardViewer) hNextClipboardViewer=(HWND)Msg.LParam;
    else if (hNextClipboardViewer!=NULL) ::SendMessage(hNextClipboardViewer,Msg.Msg,Msg.WParam,Msg.LParam);
  }
  if (Msg.Msg==WM_DRAWCLIPBOARD)
  { ClipboardChanged(true);
  }
}
void __fastcall TMainForm::GetClipboard()
{ ClipMetafile->LoadFromClipboard();
}
void __fastcall TMainForm::ClipboardChanged(bool really)
{ bClipboardViewValid=false;
  bool cok=Clipboard()->HasFormat(CF_ENHMETAFILE);
  // first we worry about the display of it
  if (PageControl->ActivePage==tClipboard && Visible && !IsIconic(Handle) && !IsIconic(Application->Handle))
  { EnsureClipboardViewValid();
  }
  // then about updating controls
  tcpSave->Enabled=true; //***cok;
  // now we worry about auto-prompt...
  if (cok && tccSaveOnClipboardChange->Checked && really)
  { AnsiString SaveFileName="";
    int index=GetClipboardOutputFormat(); AnsiString suffix=StandardExt[index];
    if (tcrPrompt->Checked)
    { if (ClipForm==NULL) Application->CreateForm(__classid(TClipForm),&ClipForm);
      if (ClipForm->Visible) return; // because one was already up
      ClipForm->Silent->Checked=false; // by assumption
      ClipForm->Format->ItemIndex=index;
      AnsiString fn=GetFreeFileName(tceDirectory->Text,tceFileName->Text,AnsiString(".")+suffix);
      ClipForm->File->Text=fn;
      ClipForm->Parent=NULL; ClipForm->ParentWindow=NULL;
      int res=ClipForm->ShowModal();
      if (res==mrNoToAll) {tccSaveOnClipboardChange->Checked=false;EnableSaveOnClipboardChange();return;}
      if (res==mrCancel) return;
      // update our main dialog according to what the user had changed
      if (ClipForm->Silent->Checked) tcrSilent->Checked=true;
      index=ClipForm->Format->ItemIndex;
      fn=SuggestExt(ClipForm->File->Text,StandardExt[index]);
      tceDirectory->Text=ExtractFilePathWithoutSlash(fn);
      tceFileName->Text=ExtractFilePrefix(fn);
      SetOutputFormat(StandardOutputType[index]);
      SaveFileName=fn;
    }
    else // otherwise we were expected to do it silently: so, find a name
    { SaveFileName=GetFreeFileName(tceDirectory->Text,tceFileName->Text,AnsiString(".")+suffix);
    }
    // now, whichever route we followed, idnex and suffix will be correct, and also SFN
    GetClipboard();
    AnsiString fn=SaveFileName;
    SaveType(ClipMetafile,fn,index);
  }
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{ Initialize();
  ClipboardChanged(false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EnsureClipboardViewValid()
{ if (bClipboardViewValid) return;
  GetClipboard();
  Update();
  bClipboardViewValid=true;
}


void __fastcall TMainForm::tcpPaintRectPaint(TObject *Sender)
{ EnsureClipboardViewValid();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{ SaveRegistry();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tePrintersClick(TObject *Sender)
{ PrinterIndex=tePrinters->ItemIndex;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::torEpsClick(TObject *Sender) {SetOutputFormat("Eps");}
void __fastcall TMainForm::torTexWmfClick(TObject *Sender) {SetOutputFormat("TexWmf");}
void __fastcall TMainForm::torTexEpsClick(TObject *Sender) {SetOutputFormat("TexEps");}
void __fastcall TMainForm::torTexEpicClick(TObject *Sender) {SetOutputFormat("TexEpic");}
void __fastcall TMainForm::tcrWmfClick(TObject *Sender) {SetOutputFormat("Wmf");}
void __fastcall TMainForm::tcrEmfClick(TObject *Sender) {SetOutputFormat("Emf");}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tccSaveOnClipboardChangeClick(TObject *Sender)
{ EnableSaveOnClipboardChange();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tcbBrowseClick(TObject *Sender)
{ ClipboardSaveDialog->FileName=tceDirectory->Text+"\\"+tceFileName->Text;
  ClipboardSaveDialog->InitialDir=tceDirectory->Text;
  bool res=ClipboardSaveDialog->Execute();
  if (!res) return;
  AnsiString fn=ClipboardSaveDialog->FileName;
  tceDirectory->Text=ExtractFilePathWithoutSlash(fn);
  tceFileName->Text=ExtractFilePrefix(fn);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tcpSaveClick(TObject *Sender)
{ int index=GetClipboardOutputFormat(); AnsiString suffix=StandardExt[index];
  SaveCurrentClipboard->FilterIndex=index+1;
  AnsiString fn=GetFreeFileName(tceDirectory->Text,tceFileName->Text,AnsiString(".")+suffix);
  SaveCurrentClipboard->FileName=fn;
  SaveCurrentClipboard->InitialDir=tceDirectory->Text;
  bool res=SaveCurrentClipboard->Execute();
  if (!res) return;
  index=SaveCurrentClipboard->FilterIndex-1;
  fn=SuggestExt(SaveCurrentClipboard->FileName,StandardExt[index]);
  SetOutputFormat(StandardOutputType[index]);
  SaveType(ClipMetafile,fn,index);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{ if ((Key=='V' && GetAsyncKeyState(VK_CONTROL)<0)
      && PageControl->ActivePage==tClipboard)
  { ClipboardChanged(true); // that will force a reload
  }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ttbWmfClick(TObject *Sender)
{ TCustomTexForm *ctf=new TCustomTexForm(this);
  ctf->Memo->Lines->Text=tteWmf->Lines->Text;
  ctf->Default->Lines->Text=tteDefWmf->Lines->Text;
  int res=ctf->ShowModal();
  if (res==mrOk) tteWmf->Lines->Text=ctf->Memo->Lines->Text;
  delete ctf;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ttbEpsClick(TObject *Sender)
{ TCustomTexForm *ctf=new TCustomTexForm(this);
  ctf->Memo->Lines->Text=tteEps->Lines->Text;
  ctf->Default->Lines->Text=tteDefEps->Lines->Text;
  int res=ctf->ShowModal();
  if (res==mrOk) tteEps->Lines->Text=ctf->Memo->Lines->Text;
  delete ctf;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tcpPaintBoxPaint(TObject *Sender)
{ ClipMetafile->StretchDraw(tcpPaintBox->Canvas,tcpPaintBox->ClientRect);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tfbInBrowseClick(TObject *Sender)
{ AnsiString fn=ExtractFirstListedFile(tfeInFile->Text);
  FileInDialog->FileName=fn;
  FileInDialog->InitialDir=ExtractFilePath(fn);
  bool res=FileInDialog->Execute();
  if (!res) return;
  AnsiString s="";
  if (FileInDialog->Files->Count==1) s=FileInDialog->FileName;
  else
  { for (int i=0; i<FileInDialog->Files->Count; i++) s=s+"\""+FileInDialog->Files->Strings[i]+"\" ";
  }
  tfeInFile->Text=s;
  tfUpdatePreview(tfeInFile->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tfcOutElsewhereClick(TObject *Sender)
{ tfEnableElsewhere();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tfEnableElsewhere()
{ bool b=tfcOutElsewhere->Checked;
  tfeOutFile->Enabled=b;
  tfbOutBrowse->Enabled=b;
}
void __fastcall TMainForm::tfUpdatePreview(AnsiString anewfn)
{ AnsiString newfn=anewfn.LowerCase();
  if (newfn==tfCurrentPreview) return;
  tfCurrentPreview=newfn;
  AnsiString fn=ExtractFirstListedFile(newfn);
  FileMetafile->LoadFromFile(fn);
  tfpSize->Caption=FileMetafile->Status;
  tfpPaintBox->Repaint();
}

void __fastcall TMainForm::tfpPaintBoxPaint(TObject *Sender)
{ if (FileMetafile->State==rmsNormal)
  { FileMetafile->StretchDraw(tfpPaintBox->Canvas,tfpPaintBox->ClientRect);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tfbConvertClick(TObject *Sender)
{ AnsiString src=tfeInFile->Text;
  // that might start with a quote and be a quote-delimited list of files
  // or without, and be either a single file or a wildcard match
  TStringList *files=new TStringList();
  int len=src.Length(); char *cpy=new char[len+1]; strcpy(cpy,src.c_str()); char *c=cpy;
  char fn[MAX_PATH];
  if (*c=='\"')
  { while (*c!=0)
    { char *dst=fn; c++;
      while (*c!='\"' && *c!=0) {*dst=*c;dst++;c++;}
      *dst=0;
      files->Add(AnsiString(fn));
      if (*c=='\"') c++;
      while (*c==' ') c++;
    }
  }
  else
  { // must do find-first-file and all that stuff
    WIN32_FIND_DATA fd;
    HANDLE hFind=FindFirstFile(cpy,&fd);
    if (hFind!=INVALID_HANDLE_VALUE)
    { bool res=true;
      while (res)
      { files->Add(fd.cFileName);
        res=FindNextFile(hFind,&fd);
      }
      FindClose(hFind);
    }
  }
  delete[] cpy;
  int index=GetClipboardOutputFormat(); // clipboard will have same output format as us
  AnsiString ext=AnsiString(".")+StandardExt[index];
  TCursor OldCursor=Screen->Cursor; Screen->Cursor=crHourGlass;
  for (int i=0; i<files->Count; i++)
  { AnsiString fn=files->Strings[i];
    tfUpdatePreview(fn);
    AnsiString sfn=ChangeFileExt(fn,ext);
    SaveType(FileMetafile,sfn,index);
    FileMetafile->Clear(); tfCurrentPreview="";
  }
  Screen->Cursor=OldCursor;
  delete files;
  tfUpdatePreview(tfeInFile->Text);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::bEngineClick(TObject *Sender)
{ TProc *p=new TProc(this);
  p->EpsGenerator->PrinterIndex=PrinterIndex;
  p->TexWmfSource->Lines->Text=tteWmf->Lines->Text;
  p->TexEpsSource->Lines->Text=tteEps->Lines->Text;
  p->ShowModal();
  delete p;
}
//---------------------------------------------------------------------------


