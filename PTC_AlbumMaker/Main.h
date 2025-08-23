//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <JPEG.hpp>
//---------------------------------------------------------------------------
#include "spl_EmbLib.h"
#include "spl_CodingLib.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
const Byte Key = 0xF4;
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TStatusBar *StatusBar1;
	TPanel *Panel6;
	TPanel *Panel1;
	TGroupBox *GroupBox2;
	TDirectoryListBox *DirectoryListBox1;
	TDriveComboBox *DriveComboBox1;
	TPanel *Panel2;
	TLabel *Label1;
	TPanel *Panel3;
	TGroupBox *GroupBox3;
	TDirectoryListBox *DirectoryListBox2;
	TDriveComboBox *DriveComboBox2;
	TPanel *Panel4;
	TLabel *Label5;
	TPanel *Panel5;
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TGroupBox *GroupBox4;
	TLabel *Label6;
	TSpeedButton *SpeedButton1;
	TBitBtn *BitBtn1;
	TEdit *Edit1;
	TBitBtn *BitBtn2;
	TFormTranslation *FormTranslation1;
	TCheckBox *CB_Encrypt;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
    void __fastcall OpenFile(AnsiString FileName,AnsiString ImageFileName);
    Graphics::TBitmap *pBMP;
    Graphics::TBitmap *pBk;
    TJPEGImage *pJPG;
    TRect Frame;
    spl_EmbHeader EmbHeader;
    AnsiString FileName;
    int ThumbWidth,ThumbHeight;
    AnsiString AppPath;
    int Margin;
    bool ShowJumps;
    bool Stretch;
    bool Real;
    spl_StitchPath StitchPath;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
