//---------------------------------------------------------------------------

#include <vcl.h>
#include <assert.h>
#pragma hdrstop

#include "Main.h"
#include "spl_RasterImage.h"
#include "spl_VectorImage.h"
#include "ProtectionLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AddMessage(AnsiString strMessage)
{
	ListBoxMessages->Items->Add(strMessage);
    ListBoxMessages->ItemIndex = ListBoxMessages->Items->Count - 1;
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowForm(TForm *pForm)
{
	assert(pForm != NULL);
	if(pPrevForm)
    {
    	FormMain->Menu = NULL;
		pPrevForm->Menu = pPrevMenu;
//		pPrevForm->Caption = strPrevCaption;
        pPrevForm->Close();
    }

	pPrevForm = pForm;
	pPrevMenu = pForm->Menu;
//    strPrevCaption = pForm->Caption;

    pForm->Menu = NULL;
	FormMain->Menu = pPrevMenu;
//    FormMain->Caption = strPrevCaption;
	pForm->Parent = FormMain->Panel1;
    pForm->BorderStyle = bsNone;
    pForm->Align = alClient;
    pForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject *Sender)
{
	ARasterImageExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif

	pPrevForm = NULL;
    pPrevMenu = NULL;

    Left = 0;
    Top = 0;
    Width = Screen->Width;	
    Height = Screen->Height - 30;

    Caption = spl_EmbTraceCaption;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ARasterImageExecute(TObject *Sender)
{
	FormRasterImage->pImage->Assign(FormRasterImage->pRestore);
    FormRasterImage->Image->Picture->Assign(FormRasterImage->pImage->pBitmap);
	ShowForm(FormRasterImage);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AVectorImageExecute(TObject *Sender)
{
	if(FormVectorImage->pImage->ImageSize <= 0)
    {
    	FormRasterImage->ADigitizeExecute(NULL);
    }
    else
    if(MessageDlg("Would you like to update the vector image?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0) == IDYES)
    {
    	FormRasterImage->ADigitizeExecute(NULL);
    }
    FormVectorImage->PrevContourIndex=spl_MaxWord;
	ShowForm(FormVectorImage);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Activate(TObject *Sender)
{
	#ifdef _PROTECTED_
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_SoftIceCheck();
    pro_Check();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Deactivate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_Scrambling();
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Check();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Idle(TObject *Sender,
      bool &Done)
{
	#ifdef _PROTECTED_
    pro_Scrambling();
    pro_Check();
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    #endif

    Done = true;
}
//---------------------------------------------------------------------------

