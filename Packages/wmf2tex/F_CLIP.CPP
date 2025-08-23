#include "wmf2tex.h"
#pragma hdrstop
#include "wmfeps_utils_shellink.h"

#include "f_clip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClipForm *ClipForm;
//---------------------------------------------------------------------------
extern const char *StandardExt[6];


__fastcall TClipForm::TClipForm(TComponent* Owner)
        : TForm(Owner)
{
}
void __fastcall TClipForm::CreateParams(TCreateParams &cp)
{ TForm::CreateParams(cp);
  cp.Style = (cp.Style & (!WS_CHILD));// | WS_POPUPWINDOW;
  cp.ExStyle |= WS_EX_TOPMOST;
  cp.WndParent=NULL;
}

//---------------------------------------------------------------------------
void __fastcall TClipForm::FormatChange(TObject *Sender)
{ AnsiString suffix=StandardExt[Format->ItemIndex];
  File->Text=ChangeFileExt(File->Text,AnsiString(".")+suffix);
}
//---------------------------------------------------------------------------

void __fastcall TClipForm::bFileClick(TObject *Sender)
{ SaveDialog->FileName=File->Text;
  SaveDialog->FilterIndex=Format->ItemIndex+1;
  SaveDialog->InitialDir=ExtractFilePathWithoutSlash(File->Text);
  Visible=false;
  bool res=SaveDialog->Execute();
  if (!res) {Visible=true;return;}
  File->Text=SaveDialog->FileName;
  Format->ItemIndex=SaveDialog->FilterIndex-1;
  ModalResult=mrOk;
}
//---------------------------------------------------------------------------

