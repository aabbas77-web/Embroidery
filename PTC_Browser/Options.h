//---------------------------------------------------------------------------

#ifndef OptionsH
#define OptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TPanel *Panel1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox1;
    TScrollBar *ScrollBar1;
    TScrollBar *ScrollBar2;
    TPanel *Panel3;
    TPanel *Panel2;
    TGroupBox *GroupBox2;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TGroupBox *GroupBox4;
    TCheckBox *CheckBox6;
    TCheckBox *CheckBox7;
    TCheckBox *CheckBox8;
    TTabSheet *TabSheet3;
    TPanel *Panel4;
    TCheckBox *CheckBox9;
    TImage *Image1;
    TColorDialog *ColorDialog1;
    TOpenPictureDialog *OpenPictureDialog1;
    TSpeedButton *SpeedButton4;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TImageList *ImageList1;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TPanel *Panel5;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ScrollBar1Change(TObject *Sender);
    void __fastcall ScrollBar2Change(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall CheckBox9Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall CheckBox3Click(TObject *Sender);
    void __fastcall ToolButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormOptions(TComponent* Owner);
    void __fastcall LoadLanguage();
    void __fastcall SaveLanguage();
    void __fastcall LoadSettings(bool Update);
    void __fastcall SaveSettings();

    // Background
    bool ShowPreviewWindow;
    bool UseColor;
    TColor BackgroundColor;
    AnsiString BackgroundFileName;

    Graphics::TBitmap *pBitmap;
    bool BitmapChanged;

    // Language
    int LanguageID;
    AnsiString LanguageName;
    AnsiString LanguageFileName;
    AnsiString LoadStr;
    AnsiString ChangeStr;
    AnsiString CommentStr;
    AnsiString TotalStr;
    AnsiString NormalStr;
    AnsiString JumpStr;
    AnsiString ColorStr;
    AnsiString WidthStr;
    AnsiString HeightStr;
    AnsiString CaptionStr;
    AnsiString DisplayCaptionStr;

    // Application
    AnsiString AppPath;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
