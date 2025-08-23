//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Main.h"
#include "About.h"
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
static int FilesCount;
static int DirsCount;
static __int64 FilesSize;
static int         Err;
static AnsiString  DirName;
static AnsiString  BaseDirName;
static AnsiString  NewDirName;
static AnsiString  NewBaseDirName;
static AnsiString  FileName;
static AnsiString  NewFileName;
static AnsiString  NewEmbFileName;
static bool Continue;
//---------------------------------------------------------------------------
void SearchTree()
{
    TSearchRec  Sr;
    Err=FindFirst("*.*",faAnyFile,Sr) ;
    while(Continue &&(!Err))
    {
        Application->ProcessMessages();
        if(Sr.Name[1]!='.')
        {
            if(!(Sr.Attr & faDirectory))
            {
                FileName=ExpandFileName(Sr.Name);
                FormMain->StatusBar1->SimpleText=MinimizeName(FileName,FormMain->StatusBar1->Canvas,400);
                if(
					#ifndef spl_Demo_Version
                   (UpperCase(FileName).Pos(".DST")>0)||
                   (UpperCase(FileName).Pos(".EXP")>0)||
                   (UpperCase(FileName).Pos(".DSZ")>0)||
                   (UpperCase(FileName).Pos(".DSB")>0)||
                   (UpperCase(FileName).Pos(".KSM")>0)||
					#endif
                   (UpperCase(FileName).Pos(".ALI")>0))
                {
                    FilesSize=FilesSize+Sr.Size;
                    FilesCount++;
                    FormMain->Label3->Caption=FormatFloat("Files Count: 0",FilesCount);
                    FormMain->Label4->Caption=FormatFloat("Total Size: 0.0 KB",FilesSize/1024.0);
                    NewEmbFileName=NewDirName+Sr.Name;
//                    NewFileName=NewEmbFileName+".bmp";
                    NewFileName=NewEmbFileName+".jpg";
                    FormMain->OpenFile(FileName,NewFileName);
                    spl_EncodeFile(Key,FileName,NewEmbFileName);
                }
            }
        }

        // Begin Recursion
        if((Sr.Attr & faDirectory)&&(Sr.Name[1] != '.'))
        {
            DirName=ExpandFileName(Sr.Name);
            NewDirName=IncludeTrailingBackslash(NewBaseDirName+ExtractRelativePath(BaseDirName,DirName));
            ForceDirectories(NewDirName);

            DirsCount++;
            FormMain->Label2->Caption=FormatFloat("Folders Count: 0",DirsCount);
            SetCurrentDir(Sr.Name);
            SearchTree();
            SetCurrentDir("..") ;
        }
        // End Recursion
        Err=FindNext(Sr) ;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtn1Click(TObject *Sender)
{
    StatusBar1->SimpleText="";
    BaseDirName=IncludeTrailingBackslash(DirectoryListBox1->Directory);
    DirName=BaseDirName;
    NewBaseDirName=IncludeTrailingBackslash(IncludeTrailingBackslash(DirectoryListBox2->Directory)+Edit1->Text);
    NewDirName=NewBaseDirName;
    if(DirectoryExists(NewDirName))
    {
        if(MessageDlg("This Root Exists, Replace it?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)!=mrYes)
        {
            return;
        }
    }
    ForceDirectories(NewDirName);

    FilesCount=0;
    DirsCount=0;
    FilesSize=0;
    SetCurrentDir(DirName);
    Continue=true;
    SearchTree();
    StatusBar1->SimpleText="";
    MessageDlg("Success...",mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    switch(Key)
    {
        case VK_ESCAPE:
        {
            Continue=false;
            break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    AppPath=ExtractFilePath(Application->ExeName)+"\\";
    ThumbWidth=200;
    ThumbHeight=200;
    pBMP=new Graphics::TBitmap();
    pBk=new Graphics::TBitmap();
    if(FileExists(AppPath+"Background.bmp"))
    {
        pBMP->LoadFromFile(AppPath+"Background.bmp");
        pBk->Assign(pBMP);
        pBk->Width=ThumbWidth;
        pBk->Height=ThumbHeight;
        pBk->Canvas->StretchDraw(Rect(0,0,pBk->Width,pBk->Height),pBMP);
        pBMP->Assign(pBk);
    }
    else
    {
//        pBk->PixelFormat=pf4bit;
        pBk->PixelFormat=pf24bit;
        pBk->Width=ThumbWidth;
        pBk->Height=ThumbHeight;
        pBMP->Assign(pBk);
    }

    Margin=5;
    ShowJumps=false;
    Stretch=false;
    Real=false;
    Frame=Rect(0,0,ThumbWidth,ThumbHeight);

    pJPG = new TJPEGImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    if(pBMP)
        delete pBMP;
    pBMP=NULL;
    if(pBk)
        delete pBk;
    pBk=NULL;
    if(pJPG)
    {
     	delete pJPG;
        pJPG = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenFile(AnsiString FileName,AnsiString ImageFileName)
{
    try
    {
        pBMP->Canvas->Draw(0,0,pBk);
        ZeroMemory(&EmbHeader,sizeof(EmbHeader));
        spl_LoadEmbFromFile(FileName,StitchPath,&EmbHeader,NULL);
        if(EmbHeader.StitchsCount > 0)
        {
	        spl_StitchStretchDraw(StitchPath,&EmbHeader,pBMP,Frame,Margin,ShowJumps,Stretch,Real);
            if(UpperCase(ImageFileName).Pos(".BMP") > 0)
            {
	    	    pBMP->SaveToFile(ImageFileName);
            }
            else
            if(UpperCase(ImageFileName).Pos(".JPG") > 0)
            {
            	pJPG->Assign(pBMP);
                pJPG->SaveToFile(ImageFileName);
            }
        }
    }
    __finally
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn2Click(TObject *Sender)
{
    Continue=false;
    Application->Terminate();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SpeedButton1Click(TObject *Sender)
{
    FormAbout->ShowModal();    
}
//---------------------------------------------------------------------------

