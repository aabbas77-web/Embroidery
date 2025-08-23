//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ShellControls"
#pragma link "ShellLink"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButton2Click(TObject *Sender)
{
  if (ShellListView->Focused())
    ShellListView->InvokeCommandOnSelected("properties");
  if (ShellTree->Focused())
    ShellTree->InvokeCommandOnSelected("properties");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton4Click(TObject *Sender)
{
  ShellListView->ViewStyle = TViewStyle(vsIcon + ((TComponent*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FullExpand1Click(TObject *Sender)
{
  ShellTree->Selected->Expand(True);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FullCollapse1Click(TObject *Sender)
{
  ShellTree->Selected->Collapse(True);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject *Sender)
{
  ShellAbout(Application->Handle, "Explorer Sample for ShellBrowser components\n", "Explorer example for ShellBrowser components. More info at: http://www.jam-software.com", Application->Icon->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton1Click(TObject *Sender)
{
  ShellTree->GoUp();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton5Click(TObject *Sender)
{
  ShellTree->ShowNetConnectionDialog();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton3Click(TObject *Sender)
{
  if (ShellListView->Focused())
    ShellListView->InvokeCommandOnSelected("delete");
  if (ShellTree->Focused())
    ShellTree->InvokeCommandOnSelected("delete");
}
//---------------------------------------------------------------------------

