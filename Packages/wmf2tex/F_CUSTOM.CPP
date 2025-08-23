#include "wmf2tex.h"
#pragma hdrstop


#include "f_custom.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCustomTexForm *CustomTexForm;
//---------------------------------------------------------------------------
__fastcall TCustomTexForm::TCustomTexForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCustomTexForm::RevertClick(TObject *Sender)
{ Memo->Lines->Text=Default->Lines->Text;

}
//---------------------------------------------------------------------------
