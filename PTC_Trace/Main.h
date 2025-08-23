//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <ActnList.hpp>
#include <AppEvnts.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TListBox *ListBoxMessages;
	TPanel *Panel2;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TActionList *ActionList1;
	TAction *ARasterImage;
	TAction *AVectorImage;
	TStatusBar *StatusBar;
	TSplitter *Splitter1;
	TFormTranslation *FormTranslation1;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ARasterImageExecute(TObject *Sender);
	void __fastcall AVectorImageExecute(TObject *Sender);
	void __fastcall ApplicationEvents1Activate(TObject *Sender);
	void __fastcall ApplicationEvents1Deactivate(TObject *Sender);
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall ShowForm(TForm *pForm);
	void __fastcall AddMessage(AnsiString strMessage);

    TMainMenu *pPrevMenu;
    TForm *pPrevForm;
//    AnsiString strPrevCaption;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
