//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include <jpeg.hpp>
#pragma hdrstop

#include "Options.h"
#include "Main.h"
#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::LoadLanguage()
{
    TIniFile *pIniFile=new TIniFile(AppPath+LanguageFileName);

    // Language Parameters
    LanguageName=pIniFile->ReadString("Language","LanguageName","English");
    BiDiMode=(TBiDiMode)pIniFile->ReadInteger("Language","BiDiMode",bdLeftToRight);
    FormAbout->BiDiMode=BiDiMode;
    FormMain->MainMenu1->AutoHotkeys = maManual;
    FormMain->MainMenu1->AutoLineReduction = maManual;
    FormMain->MainMenu1->ParentBiDiMode = false;
    FormMain->MainMenu1->BiDiMode=BiDiMode;
    FormMain->BiDiMode=BiDiMode;

    // Options
    Caption=pIniFile->ReadString("Options","Options","Options");
    TabSheet1->Caption=pIniFile->ReadString("Options","View","View");
    TabSheet2->Caption=pIniFile->ReadString("Options","Thumbnails","Thumbnails");
    TabSheet3->Caption=pIniFile->ReadString("Options","Background","Background");
    SpeedButton1->Caption=pIniFile->ReadString("Options","Ok","&Ok");
    SpeedButton2->Caption=pIniFile->ReadString("Options","Cancel","&Cancel");

    // View
    GroupBox2->Caption=pIniFile->ReadString("OptionsView","Interface","Interface");
    GroupBox4->Caption=pIniFile->ReadString("OptionsView","Files","Files");
    CheckBox1->Caption=pIniFile->ReadString("OptionsView","ShowToolBar","Show ToolBar");
    CheckBox2->Caption=pIniFile->ReadString("OptionsView","ShowStatusBar","Show StatusBar");
    CheckBox3->Caption=pIniFile->ReadString("OptionsView","ShowJumps","Show Jumps");
    CheckBox4->Caption=pIniFile->ReadString("OptionsView","Stretch","Stretch");
    CheckBox6->Caption=pIniFile->ReadString("OptionsView","ShowHiddenFiles","Show Hidden Files");
    CheckBox7->Caption=pIniFile->ReadString("OptionsView","ShowNoneEmbroideryFiles","Show None Embroidery Files");
    CheckBox8->Caption=pIniFile->ReadString("OptionsView","ShowFoldersInBrowser","Show Folders In Browser");

    // Thumbnails
    GroupBox1->Caption=pIniFile->ReadString("OptionsThumbnails","ThumbnailSize","Thumbnail Size");

    // Background
    CheckBox9->Caption=pIniFile->ReadString("OptionsBackground","Color","Color");
    LoadStr=pIniFile->ReadString("OptionsBackground","Load","Load");
    ChangeStr=pIniFile->ReadString("OptionsBackground","Change","Change");

    // Main
    CaptionStr=pIniFile->ReadString("Main","Embroidery_Browser_V10","Embroidery Browser V1.0");
#ifdef spl_Demo_Version
    if(UpperCase(LanguageFileName).Pos(UpperCase("Arabic"))>0)
        DisplayCaptionStr="(Ïíãæ) "+CaptionStr;
    else
    if(UpperCase(LanguageFileName).Pos(UpperCase("Français"))>0)
        DisplayCaptionStr="(Demo) "+CaptionStr;
    else
        DisplayCaptionStr="(Demo) "+CaptionStr;
#else
    DisplayCaptionStr=CaptionStr;
#endif

    FormMain->Caption=DisplayCaptionStr+" ["+FormMain->LinkCommand+"]";
    FormMain->AArrangeIcons->Caption=pIniFile->ReadString("Main","ArrangeIcons","&Arrange Icons");
    FormMain->AArrangeIcons->Hint=pIniFile->ReadString("Main","ArrangeIconsHint","Arrange Icons");
    FormMain->AbyName->Caption=pIniFile->ReadString("Main","byName","by &Name");
    FormMain->AbyName->Hint=pIniFile->ReadString("Main","byNameHint","Arrange Icons By Name");
    FormMain->AbyType->Caption=pIniFile->ReadString("Main","byType","by &Type");
    FormMain->AbyType->Hint=pIniFile->ReadString("Main","byTypeHint","Arrange Icons By Type");
    FormMain->AbySize->Caption=pIniFile->ReadString("Main","bySize","by &Size");
    FormMain->AbySize->Hint=pIniFile->ReadString("Main","bySizeHint","Arrange Icons By Size");
    FormMain->AbyDate->Caption=pIniFile->ReadString("Main","byDate","by &Date");
    FormMain->AbyDate->Hint=pIniFile->ReadString("Main","byDateHint","Arrange Icons By Date");

    FormMain->AFile->Caption=pIniFile->ReadString("Main","File","&File");
    FormMain->AFile->Hint=pIniFile->ReadString("Main","FileHint","File");
    FormMain->AExit->Caption=pIniFile->ReadString("Main","Exit","&Exit");
    FormMain->AExit->Hint=pIniFile->ReadString("Main","ExitHint","Exit");
    FormMain->AOptions->Caption=pIniFile->ReadString("Main","Options","&Options");
    FormMain->AOptions->Hint=pIniFile->ReadString("Main","OptionsHint","Change Browser Options");

    FormMain->AHelp->Caption=pIniFile->ReadString("Main","Help","&Help");
    FormMain->AHelp->Hint=pIniFile->ReadString("Main","HelpHint","Help");
    FormMain->AContents->Caption=pIniFile->ReadString("Main","Contents","&Contents");
    FormMain->AContents->Hint=pIniFile->ReadString("Main","ContentsHint","Contents");
    FormMain->AAbout->Caption=pIniFile->ReadString("Main","About","&About");
    FormMain->AAbout->Hint=pIniFile->ReadString("Main","AboutHint","Show About Dialog");

    FormMain->AView->Caption=pIniFile->ReadString("Main","View","&View");
    FormMain->AView->Hint=pIniFile->ReadString("Main","ViewHint","View");
    FormMain->ALargeIcons->Caption=pIniFile->ReadString("Main","LargeIcons","&Large Icons");
    FormMain->ALargeIcons->Hint=pIniFile->ReadString("Main","LargeIconsHint","Show Large Icons");
    FormMain->ASmallIcons->Caption=pIniFile->ReadString("Main","SmallIcons","&Small Icons");
    FormMain->ASmallIcons->Hint=pIniFile->ReadString("Main","SmallIconsHint","Show Small Icons");
    FormMain->AList->Caption=pIniFile->ReadString("Main","List","&List");
    FormMain->AList->Hint=pIniFile->ReadString("Main","ListHint","Show List");
    FormMain->ADetails->Caption=pIniFile->ReadString("Main","Details","&Details");
    FormMain->ADetails->Hint=pIniFile->ReadString("Main","DetailsHint","Show Details");
    FormMain->AThumbnails->Caption=pIniFile->ReadString("Main","Thumbnails","&Thumbnails");
    FormMain->AThumbnails->Hint=pIniFile->ReadString("Main","ThumbnailsHint","Show Thumbnails");
    FormMain->ARefresh->Caption=pIniFile->ReadString("Main","Refresh","&Refresh");
    FormMain->ARefresh->Hint=pIniFile->ReadString("Main","RefreshHint","Refresh");

    FormMain->CheckBoxPreview->Caption=pIniFile->ReadString("Main","Preview","Preview");
    FormMain->CheckBoxPreview->Hint=pIniFile->ReadString("Main","PreviewHint","Show/Hide Preview Window");
    FormMain->CheckBoxReal->Caption=pIniFile->ReadString("Main","Real","Real");
    FormMain->CheckBoxReal->Hint=pIniFile->ReadString("Main","RealHint","Activate Real View");
    FormMain->Label6->Hint=pIniFile->ReadString("Main","CommentHint","Design Comment");
    FormMain->Label2->Hint=pIniFile->ReadString("Main","TotalHint","Total Stitchs");
    FormMain->Label3->Hint=pIniFile->ReadString("Main","NormalHint","Normal(Run) Stitchs");
    FormMain->Label4->Hint=pIniFile->ReadString("Main","JumpHint","Jump(Stop) Stitchs");
    FormMain->Label5->Hint=pIniFile->ReadString("Main","ColorHint","Color(Color Changed) Stitchs");
    FormMain->Label7->Hint=pIniFile->ReadString("Main","WidthHint","Design Width in mm");
    FormMain->Label8->Hint=pIniFile->ReadString("Main","HeightHint","Design Height in mm");

    CommentStr=pIniFile->ReadString("Main","Comment","Comment: ");
    TotalStr=pIniFile->ReadString("Main","Total","Total      : 0");
    NormalStr=pIniFile->ReadString("Main","Normal","Normal: 0");
    JumpStr=pIniFile->ReadString("Main","Jump","Jump: 0");
    ColorStr=pIniFile->ReadString("Main","Color","Color   : 0");
    WidthStr=pIniFile->ReadString("Main","Width","Width : 0.0 mm");
    HeightStr=pIniFile->ReadString("Main","Height","Height: 0.0 mm");

    if(pIniFile)
        delete pIniFile;
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::SaveLanguage()
{
    TIniFile *pIniFile=new TIniFile(AppPath+LanguageFileName);

    // Language Parameters
    pIniFile->WriteString("Language","LanguageName",LanguageName);
    pIniFile->WriteInteger("Language","BiDiMode",BiDiMode);

    // Options
    pIniFile->WriteString("Options","Options",Caption);
    pIniFile->WriteString("Options","View",TabSheet1->Caption);
    pIniFile->WriteString("Options","Thumbnails",TabSheet2->Caption);
    pIniFile->WriteString("Options","Background",TabSheet3->Caption);
    pIniFile->WriteString("Options","Ok",SpeedButton1->Caption);
    pIniFile->WriteString("Options","Cancel",SpeedButton2->Caption);

    // View
    pIniFile->WriteString("OptionsView","Interface",GroupBox2->Caption);
    pIniFile->WriteString("OptionsView","Files",GroupBox4->Caption);
    pIniFile->WriteString("OptionsView","ShowToolBar",CheckBox1->Caption);
    pIniFile->WriteString("OptionsView","ShowStatusBar",CheckBox2->Caption);
    pIniFile->WriteString("OptionsView","ShowJumps",CheckBox3->Caption);
    pIniFile->WriteString("OptionsView","Stretch",CheckBox4->Caption);
    pIniFile->WriteString("OptionsView","ShowHiddenFiles",CheckBox6->Caption);
    pIniFile->WriteString("OptionsView","ShowNoneEmbroideryFiles",CheckBox7->Caption);
    pIniFile->WriteString("OptionsView","ShowFoldersInBrowser",CheckBox8->Caption);
 
    // Thumbnails
    pIniFile->WriteString("OptionsThumbnails","ThumbnailSize",GroupBox1->Caption);

    // Background
    pIniFile->WriteString("OptionsBackground","Color",CheckBox9->Caption);
    pIniFile->WriteString("OptionsBackground","Load",LoadStr);
    pIniFile->WriteString("OptionsBackground","Change",ChangeStr);

    // Main
    pIniFile->WriteString("Main","Embroidery_Browser_V10",CaptionStr);
    pIniFile->WriteString("Main","ArrangeIcons",FormMain->AArrangeIcons->Caption);
    pIniFile->WriteString("Main","ArrangeIconsHint",FormMain->AArrangeIcons->Hint);

    pIniFile->WriteString("Main","byName",FormMain->AbyName->Caption);
    pIniFile->WriteString("Main","byNameHint",FormMain->AbyName->Hint);
    pIniFile->WriteString("Main","byType",FormMain->AbyType->Caption);
    pIniFile->WriteString("Main","byTypeHint",FormMain->AbyType->Hint);
    pIniFile->WriteString("Main","bySize",FormMain->AbySize->Caption);
    pIniFile->WriteString("Main","bySizeHint",FormMain->AbySize->Hint);
    pIniFile->WriteString("Main","byDate",FormMain->AbyDate->Caption);
    pIniFile->WriteString("Main","byDateHint",FormMain->AbyDate->Hint);

    pIniFile->WriteString("Main","File",FormMain->AFile->Caption);
    pIniFile->WriteString("Main","FileHint",FormMain->AFile->Hint);
    pIniFile->WriteString("Main","Exit",FormMain->AExit->Caption);
    pIniFile->WriteString("Main","ExitHint",FormMain->AExit->Hint);
    pIniFile->WriteString("Main","Options",FormMain->AOptions->Caption);
    pIniFile->WriteString("Main","OptionsHint",FormMain->AOptions->Hint);

    pIniFile->WriteString("Main","Help",FormMain->AHelp->Caption);
    pIniFile->WriteString("Main","HelpHint",FormMain->AHelp->Hint);
    pIniFile->WriteString("Main","Contents",FormMain->AContents->Caption);
    pIniFile->WriteString("Main","ContentsHint",FormMain->AContents->Hint);
    pIniFile->WriteString("Main","About",FormMain->AAbout->Caption);
    pIniFile->WriteString("Main","AboutHint",FormMain->AAbout->Hint);

    pIniFile->WriteString("Main","View",FormMain->AView->Caption);
    pIniFile->WriteString("Main","ViewHint",FormMain->AView->Hint);
    pIniFile->WriteString("Main","LargeIcons",FormMain->ALargeIcons->Caption);
    pIniFile->WriteString("Main","LargeIconsHint",FormMain->ALargeIcons->Hint);
    pIniFile->WriteString("Main","SmallIcons",FormMain->ASmallIcons->Caption);
    pIniFile->WriteString("Main","SmallIconsHint",FormMain->ASmallIcons->Hint);
    pIniFile->WriteString("Main","List",FormMain->AList->Caption);
    pIniFile->WriteString("Main","ListHint",FormMain->AList->Hint);
    pIniFile->WriteString("Main","Details",FormMain->ADetails->Caption);
    pIniFile->WriteString("Main","DetailsHint",FormMain->ADetails->Hint);
    pIniFile->WriteString("Main","Thumbnails",FormMain->AThumbnails->Caption);
    pIniFile->WriteString("Main","ThumbnailsHint",FormMain->AThumbnails->Hint);
    pIniFile->WriteString("Main","Refresh",FormMain->ARefresh->Caption);
    pIniFile->WriteString("Main","RefreshHint",FormMain->ARefresh->Hint);

    pIniFile->WriteString("Main","Preview",FormMain->CheckBoxPreview->Caption);
    pIniFile->WriteString("Main","PreviewHint",FormMain->CheckBoxPreview->Hint);
    pIniFile->WriteString("Main","Real",FormMain->CheckBoxReal->Caption);
    pIniFile->WriteString("Main","RealHint",FormMain->CheckBoxReal->Hint);
    pIniFile->WriteString("Main","CommentHint",FormMain->Label6->Hint);
    pIniFile->WriteString("Main","TotalHint",FormMain->Label2->Hint);
    pIniFile->WriteString("Main","NormalHint",FormMain->Label3->Hint);
    pIniFile->WriteString("Main","JumpHint",FormMain->Label4->Hint);
    pIniFile->WriteString("Main","ColorHint",FormMain->Label5->Hint);
    pIniFile->WriteString("Main","WidthHint",FormMain->Label7->Hint);
    pIniFile->WriteString("Main","HeightHint",FormMain->Label8->Hint);

    pIniFile->WriteString("Main","Comment",CommentStr);
    pIniFile->WriteString("Main","Total",TotalStr);
    pIniFile->WriteString("Main","Normal",NormalStr);
    pIniFile->WriteString("Main","Jump",JumpStr);
    pIniFile->WriteString("Main","Color",ColorStr);
    pIniFile->WriteString("Main","Width",WidthStr);
    pIniFile->WriteString("Main","Height",HeightStr);

    if(pIniFile)
        delete pIniFile;
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::LoadSettings(bool Update)
{
    TIniFile *pIniFile=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));

    // Language
    LanguageID=pIniFile->ReadInteger("Language","LanguageID",0);
    switch(LanguageID)
    {
        case 0:
        {
            ToolButton1Click(ToolButton1);
            break;
        }
        case 1:
        {
            ToolButton1Click(ToolButton2);
            break;
        }
        case 2:
        {
            ToolButton1Click(ToolButton3);
            break;
        }
    }

    // View
    CheckBox1->Checked=pIniFile->ReadBool("Interface","ShowToolBar",true);
    CheckBox2->Checked=pIniFile->ReadBool("Interface","ShowStatusBar",true);
    ShowPreviewWindow=pIniFile->ReadBool("Interface","ShowPreviewWindow",true);
    CheckBox3->Checked=pIniFile->ReadBool("Interface","ShowJumps",true);
    CheckBox4->Checked=pIniFile->ReadBool("Interface","Stretch",false);
    CheckBox6->Checked=pIniFile->ReadBool("Interface","ShowHiddenFiles",false);
    CheckBox7->Checked=pIniFile->ReadBool("Interface","ShowNoneEmbroideryFiles",false);
    CheckBox8->Checked=pIniFile->ReadBool("Interface","ShowFoldersInBrowser",false);

    // Thumbnails
    ScrollBar1->Position=pIniFile->ReadInteger("Thumbnails","ThumbWidth",100);
    ScrollBar2->Position=pIniFile->ReadInteger("Thumbnails","ThumbHeight",100);

    // Background
    UseColor=pIniFile->ReadBool("Background","UseColor",true);
    BackgroundColor=(TColor)pIniFile->ReadInteger("Background","BackgroundColor",clWhite);

    // Interface
    if(Update)
    {
        FormMain->ApplyChanges=false;
        FormMain->Panel2->Width=pIniFile->ReadInteger("Interface","Panel2Width",226);
        FormMain->Panel7->Height=pIniFile->ReadInteger("Interface","Panel2Height",236);
        FormMain->JamShellTree1->SelectedFolder=pIniFile->ReadString("Interface","Folder","");
        FormMain->StatusBar1->Width=pIniFile->ReadInteger("Interface","StatusBar1Width",200);
        FormMain->ApplyChanges=true;
    }

    if(pIniFile)
        delete pIniFile;

    CheckBox9->Checked=UseColor;
    CheckBox9Click(this);
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::SaveSettings()
{
    TIniFile *pIniFile=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));

    // Language
    pIniFile->WriteInteger("Language","LanguageID",LanguageID);
    SaveLanguage();

    // View
    pIniFile->WriteBool("Interface","ShowToolBar",CheckBox1->Checked);
    pIniFile->WriteBool("Interface","ShowStatusBar",CheckBox2->Checked);
    pIniFile->WriteBool("Interface","ShowPreviewWindow",ShowPreviewWindow);
    pIniFile->WriteBool("Interface","ShowJumps",CheckBox3->Checked);
    pIniFile->WriteBool("Interface","Stretch",CheckBox4->Checked);
    pIniFile->WriteBool("Interface","ShowHiddenFiles",CheckBox6->Checked);
    pIniFile->WriteBool("Interface","ShowNoneEmbroideryFiles",CheckBox7->Checked);
    pIniFile->WriteBool("Interface","ShowFoldersInBrowser",CheckBox8->Checked);

    // Thumbnails
    pIniFile->WriteInteger("Thumbnails","ThumbWidth",ScrollBar1->Position);
    pIniFile->WriteInteger("Thumbnails","ThumbHeight",ScrollBar2->Position);

    // Background
    pIniFile->WriteBool("Background","UseColor",UseColor);
    pIniFile->WriteInteger("Background","BackgroundColor",BackgroundColor);

    // Interface
    pIniFile->WriteInteger("Interface","Panel2Width",FormMain->Panel2->Width);
    pIniFile->WriteInteger("Interface","Panel2Height",FormMain->Panel7->Height);
    pIniFile->WriteString("Interface","Folder",FormMain->JamShellTree1->SelectedFolder);
    pIniFile->WriteInteger("Interface","StatusBar1Width",FormMain->StatusBar1->Width);

    if(pIniFile)
        delete pIniFile;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormCreate(TObject *Sender)
{
    AppPath=ExtractFilePath(Application->ExeName)+"\\";
    BackgroundFileName=AppPath+"Background.bmp";

    pBitmap=new Graphics::TBitmap();
    LoadSettings(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormDestroy(TObject *Sender)
{
    SaveSettings();
    if(pBitmap)
        delete pBitmap;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ScrollBar1Change(TObject *Sender)
{
    BitmapChanged=true;
    ScrollBar1->Position=ScrollBar1->Position;
    Panel2->Width=ScrollBar1->Position;
    Panel2->Left=(Panel3->Width-Panel2->Width)/2.0;
    Panel2->Caption=FormatFloat("0",ScrollBar1->Position)+" x "+FormatFloat("0",ScrollBar2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ScrollBar2Change(TObject *Sender)
{
    BitmapChanged=true;
    ScrollBar2->Position=ScrollBar2->Position;
    Panel2->Height=ScrollBar2->Position;
    Panel2->Top=(Panel3->Height-Panel2->Height)/2.0;
    Panel2->Caption=FormatFloat("0",ScrollBar1->Position)+" x "+FormatFloat("0",ScrollBar2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::SpeedButton1Click(TObject *Sender)
{
    SaveSettings();
    ModalResult=mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::SpeedButton2Click(TObject *Sender)
{
    LoadSettings(false);
    ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::CheckBox9Click(TObject *Sender)
{
    UseColor=CheckBox9->Checked;
//    BitmapChanged=true;
    Image1->Visible=!UseColor;
    FormMain->DrawGrid1->Color=BackgroundColor;
    pBitmap->Canvas->Brush->Style=bsSolid;
    pBitmap->Canvas->Brush->Color=BackgroundColor;
    pBitmap->Width=10;
    pBitmap->Height=10;
    pBitmap->Canvas->FillRect(Rect(0,0,pBitmap->Width,pBitmap->Height));
    if(CheckBox9->Checked)
    {
        Panel4->Color=BackgroundColor;
        SpeedButton4->Caption=ChangeStr;
    }
    else
    {
        Panel4->Color=clBtnFace;
        SpeedButton4->Caption=LoadStr;
        if(FileExists(BackgroundFileName))
        {
            pBitmap->LoadFromFile(BackgroundFileName);
            Image1->Picture->Assign(pBitmap);
            FormMain->pBMP->Assign(pBitmap);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::SpeedButton4Click(TObject *Sender)
{
    if(CheckBox9->Checked)
    {
        if(ColorDialog1->Execute())
        {
            BackgroundColor=ColorDialog1->Color;
//            BitmapChanged=true;
        }
    }
    else
    {
        if(OpenPictureDialog1->Execute())
        {
//            BitmapChanged=true;

            if(FileExists(OpenPictureDialog1->FileName))
            {
                try
                {
                    Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
                    pBitmap->Assign(Image1->Picture->Graphic);
                    pBitmap->PixelFormat=pf24bit;
                    pBitmap->SaveToFile(BackgroundFileName);
                    Image1->Picture->Assign(pBitmap);
                }
                catch(...)
                {
                    MessageDlg("Invalid Image File",mtError,TMsgDlgButtons()<<mbOK,0);
                }
            }
        }
    }
    CheckBox9Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormActivate(TObject *Sender)
{
    BitmapChanged=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::CheckBox3Click(TObject *Sender)
{
    BitmapChanged=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ToolButton1Click(TObject *Sender)
{
    LanguageFileName=((TToolButton *)Sender)->Hint;
    LanguageID=((TToolButton *)Sender)->Tag;
    ToolButton1->Down=false;
    ToolButton2->Down=false;
    ToolButton3->Down=false;
    ((TToolButton *)Sender)->Down=true;
    LoadLanguage();
    Panel5->Caption=LanguageFileName;
    if(!FormMain->Selected)
        return;
    FormMain->DrawGrid1SelectCell(this,FormMain->CurrCol,FormMain->CurrRow,FormMain->CanSelected);
}
//---------------------------------------------------------------------------

