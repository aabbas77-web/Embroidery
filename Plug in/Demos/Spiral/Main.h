//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TScrollBox *ScrollBox1;
	TImage *Image;
	TLabel *Label1;
	TCSpinEdit *CSpinEditA;
	TLabel *Label2;
	TCSpinEdit *CSpinEditB;
	TCSpinEdit *CSpinEditT;
	TLabel *Label3;
	TCSpinEdit *CSpinEditC;
	TLabel *Label4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CSpinEditAChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall DrawSpiral(double a,double b,double c,double T);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
