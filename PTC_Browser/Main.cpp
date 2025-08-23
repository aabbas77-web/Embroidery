//---------------------------------------------------------------------------
#include <vcl.h>
#include <FileCtrl.hpp>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "Options.h"
#include "ProtectionLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ShellControls"
#pragma link "ShellLink"
#pragma link "ShellBrowser"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
AnsiString AppDataPath;
AnsiString AppPath;
//---------------------------------------------------------------------------
AnsiString GetAppDataFolder()
{
    PItemIDList AppDataFolder;
    int Index;
    char strAppDataFolder[MAX_PATH];

    SHGetSpecialFolderLocation(0, CSIDL_APPDATA, &AppDataFolder);
    SHGetPathFromIDList(AppDataFolder,strAppDataFolder);
    return AnsiString(strAppDataFolder);
}
//---------------------------------------------------------------------------
//------------------------Thread---------------------------------------------
//---------------------------------------------------------------------------
__fastcall TThumbThread::TThumbThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
    pBMP=new Graphics::TBitmap();
    pBMP->Assign(FormOptions->pBitmap);
    pBMP->Canvas->Brush->Color=clWhite;
    pBMP->Canvas->Brush->Style=bsSolid;

    TotalCount=0;
    Step=10;
}
//---------------------------------------------------------------------------
__fastcall TThumbThread::~TThumbThread()
{
    if(pBMP)    delete pBMP;
}
//---------------------------------------------------------------------------
void __fastcall TThumbThread::OpenFile()
{
    try
    {
        pBMP->Canvas->Lock();

        FileName=FormMain->pList->Strings[Index];
        pBMP->Canvas->FillRect(Frame);

        if((UpperCase(FileName).Pos(".DST")>0)||
           (UpperCase(FileName).Pos(".EXP")>0)||
           (UpperCase(FileName).Pos(".DSZ")>0)||
           (UpperCase(FileName).Pos(".DSB")>0)||
           (UpperCase(FileName).Pos(".KSM")>0)||
           (UpperCase(FileName).Pos(".ALI")>0))
        {
            spl_LoadEmbFromFile(FileName,StitchPath,&EmbHeader,NULL);
            spl_StitchStretchDraw(StitchPath,&EmbHeader,pBMP,Frame,Margin,false,false,false);
        }
        else
        {
            x=(pBMP->Width-FormMain->JamSystemImageList1->Width)/2.0;
            y=(pBMP->Height-FormMain->JamSystemImageList1->Height)/2.0;
            IconIndex=FormMain->JamSystemImageList1->GetIndexFromFileName(FileName);
            FormMain->JamSystemImageList1->Draw(pBMP->Canvas,x,y,IconIndex,true);
        }
        pBMP->SaveToFile(AppDataPath+FormatFloat("Th000000",Index)+".bmp");
        if((Index>=Step)&&(Index % Step ==0))
        {
            FormMain->ProgressBar1->Position++;
            FormMain->DrawGrid1->Invalidate();
        }
    }
    __finally
    {
        pBMP->Canvas->Unlock();
    }
}
//---------------------------------------------------------------------------
void __fastcall TThumbThread::Execute()
{
    for(int i=0;i<TotalCount;i++)
    {
        if(Terminated)  break;

        Index=i;
        Synchronize(OpenFile);
    }
    FormMain->DrawGrid1->Invalidate();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
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

    AppDataPath=GetAppDataFolder()+"\\AliSoft\\EmbBrowserV1.0\\Temp\\";
    ForceDirectories(AppDataPath);

    AppPath=ExtractFilePath(Application->ExeName);

    pList=new TStringList();

    pThread=NULL;
    Start=false;
    pBMP=new Graphics::TBitmap();
    pBitmap=new Graphics::TBitmap();

    ShowNoneEmbroideryFiles=false;
    ApplyChanges=true;

    Left=0;
    Top=0;
    Width=Screen->Width;
    Height=Screen->Height;

    Ident=2;
    Ident2=Ident/2.0;
    TextHeight=15;
    Selected=false;

    Label6->Caption="";
    Label2->Caption="";
    Label3->Caption="";
    Label4->Caption="";
    Label5->Caption="";
    Label7->Caption="";
    Label8->Caption="";

    JamShellList1->Filter=spl_EmbFilter;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ImageLibThumbnails1KeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
    switch(Key)
    {
        case VK_RETURN:
        {
            ListView1DblClick(this);
            break;
        }
        case VK_ESCAPE:
        {
            if(pThread)
            {
                Start=false;
                pThread->Terminate();
            }
            break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    pList->Clear();
    if(pList)   delete pList;

    if(pBMP)    delete pBMP;
    if(pBitmap) delete pBitmap;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OnTerminate(TObject *Sender)
{
    ProgressBar1->Position=0;
    pThread=NULL;
    if(Start)   AThumbnailsExecute(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Hint(TObject *Sender)
{
    StatusBar1->Panels->Items[0]->Text=Application->Hint;    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AExitExecute(TObject *Sender)
{
    Application->Terminate();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AViewExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ALargeIconsExecute(TObject *Sender)
{
    if(pThread)
    {
        Start=false;
        pThread->Terminate();
    }
    Notebook1->ActivePage="Browser";
    JamShellList1->ViewStyle = TViewStyle(vsIcon + ((TComponent*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASmallIconsExecute(TObject *Sender)
{
    if(pThread)
    {
        Start=false;
        pThread->Terminate();
    }
    Notebook1->ActivePage="Browser";
    JamShellList1->ViewStyle = TViewStyle(vsIcon + ((TComponent*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AListExecute(TObject *Sender)
{
    if(pThread)
    {
        Start=false;
        pThread->Terminate();
    }
    Notebook1->ActivePage="Browser";
    JamShellList1->ViewStyle = TViewStyle(vsIcon + ((TComponent*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADetailsExecute(TObject *Sender)
{
    if(pThread)
    {
        Start=false;
        pThread->Terminate();
    }
    Notebook1->ActivePage="Browser";
    JamShellList1->ViewStyle = TViewStyle(vsIcon + ((TComponent*)Sender)->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AThumbnailsExecute(TObject *Sender)
{
    Notebook1->ActivePage="Thumbnail";
    if(!FormOptions)    return;
    OldDirectory=JamShellTree1->SelectedFolder;

    if(pThread)
    {
        Start=true;
        pThread->Terminate();
    }
    else
    {
        if(pBMP)
        {
            // Clear Old Elements
            pList->Clear();

            DrawGrid1->DefaultColWidth=ThumbWidth+2*Ident;
            DrawGrid1->DefaultRowHeight=ThumbHeight+2*Ident+TextHeight;
            DrawGrid1->ColCount=_Round(double(DrawGrid1->ClientWidth)/double(DrawGrid1->DefaultColWidth));
            DrawGrid1->RowCount=double(JamShellList1->Items->Count)/double(DrawGrid1->ColCount);
            for(int i=0;i<JamShellList1->Items->Count;i++)
            {
                pList->Add(JamShellList1->GetFullPath(JamShellList1->Items->Item[i]));
            }
            pBMP->Width=ThumbWidth;
            pBMP->Height=ThumbHeight;

            Step=pList->Count/20+1;
            ProgressBar1->Min=0;
            ProgressBar1->Max=20;
            ProgressBar1->Position=0;
            ProgressBar1->Step=Step;

            SCROLLINFO ScrollInfo;
            ScrollInfo.cbSize=sizeof(SCROLLINFO);
            ScrollInfo.fMask=SIF_POS;
            ScrollInfo.nPos=0;
            SetScrollInfo(DrawGrid1->Handle,SB_VERT,&ScrollInfo,true);
            DrawGrid1SelectCell(this,0,0,CanSelect);

            Start=false;
            pThread=new TThumbThread(true);

            pThread->Frame=Rect(0,0,ThumbWidth,ThumbHeight);
            pThread->TotalCount=pList->Count;
            pThread->Step=Step;
            pThread->pBMP->Width=ThumbWidth;
            pThread->pBMP->Height=ThumbHeight;
            pThread->FreeOnTerminate=true;
            pThread->OnTerminate=OnTerminate;
            pThread->Resume();
            Selected=false;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AArrangeIconsExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AbyNameExecute(TObject *Sender)
{
    JamShellList1->SortColumn=0;
    ARefreshExecute(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AbyTypeExecute(TObject *Sender)
{
    JamShellList1->SortColumn=2;
    ARefreshExecute(this);  
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AbySizeExecute(TObject *Sender)
{
    JamShellList1->SortColumn=1;
    ARefreshExecute(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AbyDateExecute(TObject *Sender)
{
    JamShellList1->SortColumn=3;
    ARefreshExecute(this);  
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UpdateControls()
{
    Panel1->Visible=FormOptions->CheckBox1->Checked;
    Panel5->Visible=FormOptions->CheckBox2->Checked;
    Panel7->Visible=FormOptions->ShowPreviewWindow;
    CheckBoxPreview->Checked=Panel7->Visible;
 
    if(FormOptions->BitmapChanged)
    {
        if((JamShellList1->ShowHidden!=FormOptions->CheckBox6->Checked)||
           (JamShellList1->ShowFolders!=FormOptions->CheckBox8->Checked)||
           (ShowNoneEmbroideryFiles!=FormOptions->CheckBox7->Checked))
        {
            JamShellList1->ShowHidden=FormOptions->CheckBox6->Checked;
            JamShellList1->ShowFolders=FormOptions->CheckBox8->Checked;

            ShowNoneEmbroideryFiles=FormOptions->CheckBox7->Checked;
            if(FormOptions->CheckBox7->Checked)
            {
                JamShellList1->Filter="*.*";
            }
            else
            {
                JamShellList1->Filter=spl_EmbFilter;
            }
        }

        if((ThumbWidth!=FormOptions->ScrollBar1->Position)||
           (ThumbHeight!=FormOptions->ScrollBar2->Position))
        {
            ThumbWidth=FormOptions->ScrollBar1->Position;
            ThumbHeight=FormOptions->ScrollBar2->Position;
        }

        if(Notebook1->ActivePage=="Thumbnail")
        {
            AThumbnailsExecute(this);
        }
        else
            JamShellList1->Refresh();
    }
    DrawGrid1->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AOptionsExecute(TObject *Sender)
{
    if(FormOptions->ShowModal()!=mrOk)  return;
    Selected=false;
    UpdateControls();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormShow(TObject *Sender)
{
    UpdateControls();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AAboutExecute(TObject *Sender)
{
    FormAbout->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::JamShellList1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbRight)
    {
        P=JamShellList1->ClientToScreen(Point(X,Y));
        if(ItemSelected)
            JamShellList1->ShowContextMenu(P);
        else
            PopupMenu1->Popup(P.x,P.y);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListView1DblClick(TObject *Sender)
{
    if(!Selected)   return;

    ShellBrowser1->ObjectName=LinkCommand;
    ShellBrowser1->InvokeContextMenuCommand("default");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListView1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbRight)
    {
        DrawGrid1->MouseToCell(X,Y,CurrCol,CurrRow);
        Index=CurrCol+CurrRow*DrawGrid1->ColCount;
        Selected=false;
        if((Index<0)||(Index>=pList->Count))    return;
        Selected=true;
        P=DrawGrid1->ClientToScreen(Point(X,Y));
        if(Selected)
        {
            ShellBrowser1->ObjectName=pList->Strings[Index];
            ShellBrowser1->ShowContextMenu(P,NULL);
        }
        else
            PopupMenu1->Popup(P.x,P.y);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ARefreshExecute(TObject *Sender)
{
    if(!ApplyChanges)   return;
    Selected=false;
    if(Notebook1->ActivePage=="Thumbnail")
    {
        AThumbnailsExecute(this);
    }
    else
        JamShellList1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Panel7Resize(TObject *Sender)
{
    if(!Selected)   return;
    DrawGrid1SelectCell(this,CurrCol,CurrRow,CanSelected);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CheckBoxPreviewClick(TObject *Sender)
{
    if(CheckBoxPreview->Checked)
    {
        Panel7->Visible=CheckBoxPreview->Checked;
        Splitter1->Visible=CheckBoxPreview->Checked;
    }
    else
    {
        Splitter1->Visible=CheckBoxPreview->Checked;
        Panel7->Visible=CheckBoxPreview->Checked;
    }

    FormOptions->ShowPreviewWindow=CheckBoxPreview->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CheckBoxRealClick(TObject *Sender)
{
    if(!Selected)   return;
    DrawGrid1SelectCell(this,CurrCol,CurrRow,CanSelected);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbRight)
    {
        P=Image1->ClientToScreen(Point(X,Y));
        if(Selected)
        {
            ShellBrowser1->ObjectName=LinkCommand;
            ShellBrowser1->ShowContextMenu(P,NULL);
        }
        else
            PopupMenu1->Popup(P.x,P.y);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DrawGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
    CurrCol=ACol;
    CurrRow=ARow;
    Index=ACol+ARow*DrawGrid1->ColCount;
    Selected=false;
    CanSelect=false;
    if((Index<0)||(Index>=pList->Count))    return;
    Selected=true;
    CanSelect=true;
    if(!CheckBoxPreview->Checked)   return;

    FileName=JamShellList1->GetFullPath(JamShellList1->Items->Item[Index]);
    if(!FileExists(FileName)) return;
    LinkCommand=FileName;
    Caption=FormOptions->DisplayCaptionStr+" ["+LinkCommand+"]";

    double W=min(Image1->Width,Image1->Height)-2.0*Margin;
    pBMP->Width=W;
    pBMP->Height=W;
    TRect Frame=Rect(0,0,W,W);

    // Draw Background
    for(int y=0;y<pBMP->Height;y+=FormOptions->pBitmap->Height)
    {
        for(int x=0;x<pBMP->Width;x+=FormOptions->pBitmap->Width)
        {
            pBMP->Canvas->Draw(x,y,FormOptions->pBitmap);
        }
    }

    if( (UpperCase(LinkCommand).Pos(".DST")>0)||
        (UpperCase(LinkCommand).Pos(".EXP")>0)||
        (UpperCase(LinkCommand).Pos(".DSZ")>0)||
        (UpperCase(LinkCommand).Pos(".DSB")>0)||
        (UpperCase(LinkCommand).Pos(".KSM")>0)||
        (UpperCase(LinkCommand).Pos(".ALI")>0))
    {
        spl_LoadEmbFromFile(LinkCommand,StitchPath,&EmbHeader,NULL);
        spl_StitchStretchDraw(StitchPath,&EmbHeader,pBMP,Frame,Margin,FormOptions->CheckBox3->Checked,FormOptions->CheckBox4->Checked,FormMain->CheckBoxReal->Checked);

        pBMP->Canvas->Brush->Color=clBlack;
        pBMP->Canvas->FrameRect(Frame);
    }
    else
    {
        x=(pBMP->Width-JamSystemImageList1->Width)/2.0;
        y=(pBMP->Height-JamSystemImageList1->Height)/2.0;
        IconIndex=JamSystemImageList1->GetIndexFromFileName(LinkCommand);
        JamSystemImageList1->Draw(pBMP->Canvas,x,y,IconIndex,true);
    }
    pBMP->Canvas->Pen->Color=clBlack;
    pBMP->Canvas->Brush->Style=bsClear;
    pBMP->Canvas->Rectangle(Frame);

    Image1->Picture->Bitmap->Assign(pBMP);

    Label6->Caption=FormOptions->CommentStr+EmbHeader.Comments;
    Label2->Caption=FormatFloat(FormOptions->TotalStr,EmbHeader.StitchsCount);
    Label3->Caption=FormatFloat(FormOptions->NormalStr,EmbHeader.NormalStitchs);
    Label4->Caption=FormatFloat(FormOptions->JumpStr,EmbHeader.JumpStitchs);
    Label5->Caption=FormatFloat(FormOptions->ColorStr,EmbHeader.ColorStitchs);
    Label7->Caption=FormatFloat(FormOptions->WidthStr,(EmbHeader.right-EmbHeader.left)/10.0);
    Label8->Caption=FormatFloat(FormOptions->HeightStr,(EmbHeader.bottom-EmbHeader.top)/10.0);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DrawGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    Index=ACol+ARow*DrawGrid1->ColCount;
    if((Index<0)||(Index>=pList->Count))    return;
    FName=JamShellList1->GetFullPath(JamShellList1->Items->Item[Index]);
    FileName=AppDataPath+FormatFloat("Th000000",Index)+".bmp";
    if(!FileExists(FileName))   return;
    pBitmap->LoadFromFile(FileName);

    // Clear Old Thumbnail
    DrawGrid1->Canvas->Brush->Color=DrawGrid1->Color;
    DrawGrid1->Canvas->Brush->Style=bsSolid;
    DrawGrid1->Canvas->FillRect(Rect);

    if((pBitmap->Width==ThumbWidth)&&(pBitmap->Height==ThumbHeight))
    {
        // Draw New Thumbnail
        DrawGrid1->Canvas->Draw(Rect.left+Ident,Rect.top+Ident,pBitmap);
    }
    
    // Frame New Thumbnail
    DrawGrid1->Canvas->Brush->Style=bsClear;
    DrawGrid1->Canvas->Pen->Color=clBlack;
    DrawGrid1->Canvas->Pen->Width=1;
    DrawGrid1->Canvas->Rectangle(Rect.left+Ident,Rect.top+Ident,Rect.right-Ident,Rect.bottom-Ident-TextHeight);

    // Clear Old Text
    DrawGrid1->Canvas->Brush->Color=TColor(0x00FFC993);
    DrawGrid1->Canvas->Pen->Color=clBlack;
    DrawGrid1->Canvas->Pen->Width=1;
    DrawGrid1->Canvas->Rectangle(Rect.left+Ident,Rect.top-1+Ident+ThumbHeight,Rect.right-Ident,Rect.bottom-Ident);

    // Draw New Text
    MaxTextWidth=ThumbWidth-3*Ident;
    Name=MinimizeName(FName,DrawGrid1->Canvas,MaxTextWidth);
    TextWidth=DrawGrid1->Canvas->TextWidth(Name);
    if(TextWidth>MaxTextWidth)
    {
        Name=ExtractShortPathName(FName);
        Name=MinimizeName(Name,DrawGrid1->Canvas,MaxTextWidth);
        TextWidth=DrawGrid1->Canvas->TextWidth(Name);
    }
    dx=(ThumbWidth-TextWidth)/2.0;
    DrawGrid1->Canvas->TextOut(Rect.left+Ident+dx,Rect.top+Ident+ThumbHeight,Name);

    // Draw Selection Rectangle
    if(State.Contains(gdSelected))
    {
        DrawGrid1->Canvas->Brush->Style=bsClear;
        DrawGrid1->Canvas->Pen->Color=clRed;
        DrawGrid1->Canvas->Pen->Width=Ident;
        DrawGrid1->Canvas->Rectangle(Rect.left+Ident+1,Rect.top+Ident+1,Rect.right-Ident,Rect.bottom-Ident-TextHeight);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Splitter2Moved(TObject *Sender)
{
    DrawGrid1->ColCount=_Round(double(DrawGrid1->ClientWidth)/double(DrawGrid1->DefaultColWidth));
    DrawGrid1->RowCount=double(JamShellList1->Items->Count)/double(DrawGrid1->ColCount);
    DrawGrid1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1ShortCut(TWMKey &Msg,
      bool &Handled)
{
    unsigned short Key=Msg.KeyData;
    ImageLibThumbnails1KeyDown(this,Key,TShiftState());
    Handled=false;    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AContentsExecute(TObject *Sender)
{
    Application->HelpFile=AppPath+"EMBBROWSER.HLP";
    Application->HelpCommand(HELP_CONTENTS,0);    
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
    pro_SoftIceCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    Done = true;
}
//---------------------------------------------------------------------------

