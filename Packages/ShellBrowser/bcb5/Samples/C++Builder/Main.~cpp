//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ShellControls"
#pragma link "ShellLink"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButton2Click(TObject *Sender)
{
  if (ShellListView->Focused())
    ShellListView->InvokeCommandOnSelected("properties");
  if (ShellTree->Focused())
    ShellTree->InvokeCommandOnSelected("properties");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SpeedButton4Click(TObject *Sender)
{
  ShellListView->ViewStyle = TViewStyle(vsIcon + ((TComponent*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FullExpand1Click(TObject *Sender)
{
  ShellTree->Selected->Expand(True);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FullCollapse1Click(TObject *Sender)
{
  ShellTree->Selected->Collapse(True);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::About1Click(TObject *Sender)
{
  ShellAbout(Application->Handle, "Explorer Sample for ShellBrowser components\n", "Explorer example for ShellBrowser components. More info at: http://www.jam-software.com", Application->Icon->Handle);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SpeedButton1Click(TObject *Sender)
{
  ShellTree->GoUp();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SpeedButton5Click(TObject *Sender)
{
  ShellTree->ShowNetConnectionDialog();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SpeedButton3Click(TObject *Sender)
{
  if (ShellListView->Focused())
    ShellListView->InvokeCommandOnSelected("delete");
  if (ShellTree->Focused())
    ShellTree->InvokeCommandOnSelected("delete");
}
//---------------------------------------------------------------------------

