//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "spl_EmbOpenDialog.h"
#include "ProtectionLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "G32_Image"
#pragma link "CSPIN"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner)
{
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

    AppPath=IncludeTrailingBackslash(ExtractFilePath(Application->ExeName));

    pEmbSimulator=NULL;
    pEmbSimulator=new spl_EmbSimulator(20);
    pEmbSimulator->m_BackgroundColor=Image->Color;
    pEmbSimulator->m_Alpha=0xFF;
    pEmbSimulator->m_bShowJumps=false;

    ABackground->Checked=false;
    if(FileExists(AppPath+"Background.bmp"))
    {
        pEmbSimulator->m_pBk->LoadFromFile(AppPath+"Background.bmp");
        ABackground->Checked=true;
    }

    for(double d=8.0;d>1.0;d-=0.5)  Scales.push_back(1.0/d);
    for(double d=1.0;d<=8.0;d+=0.5)  Scales.push_back(d);

    OpenDialogEmb->DefaultExt=spl_EmbDefaultExtension;
    OpenDialogEmb->Filter=spl_EmbFullFilter;

    SaveDialogEmb->DefaultExt=spl_EmbDefaultExtension;
    SaveDialogEmb->Filter=spl_EmbFullFilter;
    Caption=spl_EmbSimulatorCaption;

    Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height - 30;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    pEmbSimulator->FlushAndFree();
    if(pEmbSimulator)   delete pEmbSimulator;pEmbSimulator=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileExecute(TObject *Sender)
{
    pEmbSimulator->Pause();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AOpenExecute(TObject *Sender)
{
    pEmbSimulator->Stop();
	if(FormEmbOpenDialog->ShowModal() == mrOk)
//    if(OpenDialogEmb->Execute())
    {

//        FileName=OpenDialogEmb->FileName;
        FileName=FormEmbOpenDialog->FileName;
        pEmbSimulator->LoadFromFile(FileName);
        Caption=spl_EmbSimulatorCaption+"["+FileName+"]";

        wd=pEmbSimulator->m_EmbHeader.right-pEmbSimulator->m_EmbHeader.left;
        hd=pEmbSimulator->m_EmbHeader.bottom-pEmbSimulator->m_EmbHeader.top;

        w=pEmbSimulator->m_nWidth;
        h=pEmbSimulator->m_nHeight;

        // Static Info
        PanelComment->Caption=pEmbSimulator->m_EmbHeader.Comments;
        PanelTotalStitchs->Caption=IntToStr(pEmbSimulator->m_EmbHeader.StitchsCount);
        PanelNormalStitchs->Caption=IntToStr(pEmbSimulator->m_EmbHeader.NormalStitchs);
        PanelJumpStitchs->Caption=IntToStr(pEmbSimulator->m_EmbHeader.JumpStitchs);
        PanelColorStitchs->Caption=IntToStr(pEmbSimulator->m_EmbHeader.ColorStitchs);
        PanelWidth->Caption=FormatFloat("0.0",wd/10.0);
        PanelHeight->Caption=FormatFloat("0.0",hd/10.0);

        AFitExecute(this);

        pEmbSimulator->m_nBlockSize=CSpinEditBlockSize->Value;
        pEmbSimulator->m_ndX=(Image->Width-w*Scale)/2-ShapeMachine->Width;
        pEmbSimulator->m_ndY=(Image->Height-h*Scale)/2-ShapeMachine->Height;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASaveExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Pause();
    if(SaveDialogEmb->Execute())
    {
        FileName=SaveDialogEmb->FileName;
        pEmbSimulator->SaveToFile(FileName);
        Caption=spl_EmbSimulatorCaption+"["+FileName+"]";
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AExitExecute(TObject *Sender)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASimulatorExecute(TObject *Sender)
{
    pEmbSimulator->Pause();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APlayExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    if(pEmbSimulator->Bof() || pEmbSimulator->Eof())
    {
        pEmbSimulator->Clear();
        pEmbSimulator->Show(false,clLightGray32);
        pEmbSimulator->Start();
    }
    else
        pEmbSimulator->Play();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APauseExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Pause();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AStopExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Stop();
    pEmbSimulator->Clear();
    pEmbSimulator->Show(false,clLightGray32);
    pEmbSimulator->Stop();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APlayToExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Pause();
    AnsiString Value="0";
    if(InputQuery("Play To","Enter Stitch Index:",Value))
    {
        pEmbSimulator->Clear();
        pEmbSimulator->Show(false,clLightGray32);
        pEmbSimulator->PlayTo(StrToInt(Value));
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AViewExecute(TObject *Sender)
{
    pEmbSimulator->Pause();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoom11Execute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Stop();

    ScaleIndex=Scales.size()/2;
    Scale=Scales[ScaleIndex];
    PanelScale->Caption=FormatFloat("0.00",Scale);
    pEmbSimulator->m_ndX=(Image->Width-w*Scale)/2-ShapeMachine->Width;
    pEmbSimulator->m_ndY=(Image->Height-h*Scale)/2-ShapeMachine->Height;

    pEmbSimulator->m_Frame=spl_Rect(0,0,w*Scale,h*Scale);
    pEmbSimulator->Show(true,clLightGray32);
    pEmbSimulator->Update();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomMaxExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Stop();

    if(ScaleIndex<Scales.size()-1)
    {
        ScaleIndex++;
        Scale=Scales[ScaleIndex];
        PanelScale->Caption=FormatFloat("0.00",Scale);
        pEmbSimulator->m_ndX=(Image->Width-w*Scale)/2-ShapeMachine->Width;
        pEmbSimulator->m_ndY=(Image->Height-h*Scale)/2-ShapeMachine->Height;

        pEmbSimulator->m_Frame=spl_Rect(0,0,w*Scale,h*Scale);
        pEmbSimulator->Show(true,clLightGray32);
        pEmbSimulator->Update();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomMinExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Stop();

    if(ScaleIndex>0)
    {
        ScaleIndex--;
        Scale=Scales[ScaleIndex];
        PanelScale->Caption=FormatFloat("0.00",Scale);
        pEmbSimulator->m_ndX=(Image->Width-w*Scale)/2-ShapeMachine->Width;
        pEmbSimulator->m_ndY=(Image->Height-h*Scale)/2-ShapeMachine->Height;

        pEmbSimulator->m_Frame=spl_Rect(0,0,w*Scale,h*Scale);
        pEmbSimulator->Show(true,clLightGray32);
        pEmbSimulator->Update();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFitExecute(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Stop();

    for(spl_UInt i=0;i<Scales.size();i++)
    {
        Scale=Scales[i];
        if((w*Scale>=Image->Width)||(h*Scale>=Image->Height))
        {
            if(i>0) ScaleIndex=i-1;
            break;
        }
    }
    Scale=Scales[ScaleIndex];
    PanelScale->Caption=FormatFloat("0.00",Scale);
    pEmbSimulator->m_ndX=(Image->Width-w*Scale)/2-ShapeMachine->Width;
    pEmbSimulator->m_ndY=(Image->Height-h*Scale)/2-ShapeMachine->Height;

    pEmbSimulator->m_Frame=spl_Rect(0,0,w*Scale,h*Scale);
    pEmbSimulator->Show(true,clLightGray32);
    pEmbSimulator->Update();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CSpinEditBlockSizeChange(TObject *Sender)
{
    pEmbSimulator->m_nBlockSize=CSpinEditBlockSize->Value;
    pEmbSimulator->Interval=pEmbSimulator->m_nBlockSize+20-1;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ATraceExecute(TObject *Sender)
{
    pEmbSimulator->Pause();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AStopOnNormalExecute(TObject *Sender)
{
    AStopOnNormal->Checked=!AStopOnNormal->Checked;    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AStopOnJumpExecute(TObject *Sender)
{
    AStopOnJump->Checked=!AStopOnJump->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AStopOnColorExecute(TObject *Sender)
{
    AStopOnColor->Checked=!AStopOnColor->Checked;    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AShowJumpsExecute(TObject *Sender)
{
    AShowJumps->Checked=!AShowJumps->Checked;
    pEmbSimulator->m_bShowJumps=AShowJumps->Checked;

    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Stop();

    Scale=Scales[ScaleIndex];
    PanelScale->Caption=FormatFloat("0.00",Scale);

    pEmbSimulator->m_Frame=spl_Rect(0,0,w*Scale,h*Scale);
    pEmbSimulator->Show(true,clLightGray32);
    pEmbSimulator->Update();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AMachineExecute(TObject *Sender)
{
    AMachine->Checked=!AMachine->Checked;
    ShapeMachine->Visible=AMachine->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpExecute(TObject *Sender)
{
    pEmbSimulator->Pause();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AContentsExecute(TObject *Sender)
{
    pEmbSimulator->Pause();
    Application->HelpFile=AppPath+"EMBSIMULATOR.HLP";
    Application->HelpCommand(HELP_CONTENTS,0);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AAboutExecute(TObject *Sender)
{
    pEmbSimulator->Pause();
    FormAbout->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ABackgroundExecute(TObject *Sender)
{
    pEmbSimulator->Stop();

    ABackground->Checked=!ABackground->Checked;
    if(ABackground->Checked)
    {
        if(OpenPictureDialog1->Execute())
        {
            pEmbSimulator->m_pBk->LoadFromFile(OpenPictureDialog1->FileName);
            pEmbSimulator->m_pBk->SaveToFile(AppPath+"Background.bmp");
        }
        if(FileExists(AppPath+"Background.bmp"))
        {
            pEmbSimulator->m_pBk->LoadFromFile(AppPath+"Background.bmp");
        }
    }
    else
    {
        if(ColorDialog1->Execute())
        {
            pEmbSimulator->m_BackgroundColor=Color32(ColorDialog1->Color);
            Image->Color=ColorDialog1->Color;
        }
        pEmbSimulator->m_pBk->SetSize(0,0);
    }

    if(!pEmbSimulator->m_bLoaded)   return;
    pEmbSimulator->Show(true,clLightGray32);
    pEmbSimulator->Update();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch(Key)
    {
     	case VK_RIGHT:
        {
        	NextStitchClick(NULL);
         	break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::NextStitchClick(TObject *Sender)
{
    if(!pEmbSimulator->m_bLoaded)   return;
    if(pEmbSimulator->Bof())
    {
        pEmbSimulator->Stop();
        pEmbSimulator->Clear();
        pEmbSimulator->Show(false,clLightGray32);
        pEmbSimulator->Stop();

	    NextStitch();
    }
    else
    if(pEmbSimulator->Eof())
    {

    }
    else
    {
	    NextStitch();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Activate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Deactivate(TObject *Sender)
{
	#ifdef _PROTECTED_
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_SoftIceCheck();
    pro_Check();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Idle(TObject *Sender,
      bool &Done)
{
	#ifdef _PROTECTED_
	pro_DebuggerCheck();
    pro_Check();
    pro_Scrambling();
    pro_SoftIceCheck();
    #endif

    Done = true;
}
//---------------------------------------------------------------------------

