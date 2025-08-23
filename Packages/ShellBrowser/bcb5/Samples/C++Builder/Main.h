//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
// Please note: It may be necessary that you add your path to the lib folder
// of ShellBrowser to the include path and library path of this project.
// C++ Builder seems to be a bit buggy here sometimes.
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ShellControls.hpp>
#include <ShellLink.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TJamShellTree *ShellTree;
    TSplitter *Splitter1;
    TJamShellList *ShellListView;
    TPanel *Panel1;
    TJamShellLink *JamShellLink;
    TJamShellCombo *JamShellCombo1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TSpeedButton *SpeedButton8;
    TPopupMenu *PopupMenu1;
    TMenuItem *FullExpand1;
    TMenuItem *FullCollapse1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Exit1;
    TMenuItem *Help1;
    TMenuItem *About1;
    TStatusBar *StatusBar1;
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall FullExpand1Click(TObject *Sender);
    void __fastcall FullCollapse1Click(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
