//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "G32_Image.hpp"
#include "spl_EmbSimulator.h"
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <vector.h>
#include "CSPIN.h"
#include <ExtDlgs.hpp>
#include "FormTranslation.h"
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TOpenDialog *OpenDialogEmb;
    TSaveDialog *SaveDialogEmb;
    TStatusBar *StatusBar1;
    TPanel *Panel1;
    TProgressBar *ProgressBar1;
    TImgView32 *Image;
    TShape *ShapeMachine;
    TActionList *ActionList1;
    TAction *AFile;
    TAction *AOpen;
    TAction *ASave;
    TAction *AExit;
    TMenuItem *AFile1;
    TMenuItem *ALoad1;
    TMenuItem *ASave1;
    TMenuItem *N1;
    TMenuItem *AExit1;
    TAction *ASimulator;
    TAction *APlay;
    TAction *APause;
    TAction *AStop;
    TAction *APlayTo;
    TMenuItem *ASimulator1;
    TMenuItem *APlay1;
    TMenuItem *APause1;
    TMenuItem *AStop1;
    TMenuItem *APlayTo1;
    TMenuItem *N2;
    TImageList *ImageList1;
    TPanel *Panel3;
    TToolBar *ToolBar1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TToolBar *ToolBar2;
    TToolButton *ToolButton6;
    TToolButton *ToolButton7;
    TAction *AView;
    TAction *AZoom11;
    TAction *AZoomMax;
    TAction *AZoomMin;
    TMenuItem *View1;
    TMenuItem *Zoom111;
    TMenuItem *ZoomMin1;
    TMenuItem *Exit1;
    TToolBar *ToolBar3;
    TToolButton *ToolButton8;
    TToolButton *ToolButton9;
    TToolButton *ToolButton10;
    TToolButton *ToolButton11;
    TAction *AFit;
    TMenuItem *AFit1;
    TPanel *PanelScale;
    TCSpinEdit *CSpinEditBlockSize;
    TToolButton *ToolButton1;
    TToolButton *ToolButton13;
    TToolButton *ToolButton14;
    TToolBar *ToolBar4;
    TToolButton *ToolButton15;
    TToolButton *ToolButton16;
    TToolButton *ToolButton17;
    TAction *ATrace;
    TAction *AStopOnNormal;
    TAction *AStopOnJump;
    TAction *AStopOnColor;
    TMenuItem *ATrace1;
    TMenuItem *AStopOnNormal1;
    TMenuItem *AStopOnJump1;
    TMenuItem *AStopOnColor1;
    TAction *AShowJumps;
    TAction *AMachine;
    TMenuItem *N3;
    TMenuItem *ShowJumps1;
    TMenuItem *Machine1;
    TToolButton *ToolButtonShowJumps;
    TToolButton *ToolButtonMachine;
    TAction *AHelp;
    TAction *AContents;
    TAction *AAbout;
    TMenuItem *Help1;
    TMenuItem *Contents1;
    TMenuItem *N4;
    TMenuItem *About1;
    TToolBar *ToolBar5;
    TToolButton *ToolButton12;
    TToolButton *ToolButton18;
    TAction *ABackground;
    TMenuItem *N5;
    TMenuItem *Background1;
    TToolButton *ToolButton19;
    TOpenPictureDialog *OpenPictureDialog1;
    TColorDialog *ColorDialog1;
	TScrollBox *ScrollBox1;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label1;
	TPanel *PanelStitchIndex;
	TPanel *PanelSt;
	TPanel *PanelRel;
	TPanel *PanelAbs;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TPanel *PanelJumpStitchs;
	TPanel *PanelNormalStitchs;
	TPanel *PanelTotalStitchs;
	TPanel *PanelComment;
	TPanel *PanelColorStitchs;
	TPanel *PanelWidth;
	TPanel *PanelHeight;
	TFormTranslation *FormTranslation1;
	TApplicationEvents *ApplicationEvents1;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall AFileExecute(TObject *Sender);
    void __fastcall AOpenExecute(TObject *Sender);
    void __fastcall ASaveExecute(TObject *Sender);
    void __fastcall AExitExecute(TObject *Sender);
    void __fastcall ASimulatorExecute(TObject *Sender);
    void __fastcall APlayExecute(TObject *Sender);
    void __fastcall APauseExecute(TObject *Sender);
    void __fastcall AStopExecute(TObject *Sender);
    void __fastcall APlayToExecute(TObject *Sender);
    void __fastcall AViewExecute(TObject *Sender);
    void __fastcall AZoom11Execute(TObject *Sender);
    void __fastcall AZoomMaxExecute(TObject *Sender);
    void __fastcall AZoomMinExecute(TObject *Sender);
    void __fastcall AFitExecute(TObject *Sender);
    void __fastcall CSpinEditBlockSizeChange(TObject *Sender);
    void __fastcall ATraceExecute(TObject *Sender);
    void __fastcall AStopOnNormalExecute(TObject *Sender);
    void __fastcall AStopOnJumpExecute(TObject *Sender);
    void __fastcall AStopOnColorExecute(TObject *Sender);
    void __fastcall AShowJumpsExecute(TObject *Sender);
    void __fastcall AMachineExecute(TObject *Sender);
    void __fastcall AHelpExecute(TObject *Sender);
    void __fastcall AContentsExecute(TObject *Sender);
    void __fastcall AAboutExecute(TObject *Sender);
    void __fastcall ABackgroundExecute(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall NextStitchClick(TObject *Sender);
	void __fastcall ApplicationEvents1Activate(TObject *Sender);
	void __fastcall ApplicationEvents1Deactivate(TObject *Sender);
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
private:	// User declarations
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
    AnsiString FileName;
    AnsiString AppPath;
    double Scale;
    spl_UInt ScaleIndex;
    vector<double> Scales;
    double wd,hd;
    double w,h;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
