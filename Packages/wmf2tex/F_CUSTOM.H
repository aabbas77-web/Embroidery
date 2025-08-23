//---------------------------------------------------------------------------
#ifndef f_customH
#define f_customH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TCustomTexForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label7;
        TLabel *Label1;
        TLabel *Label2;
        TMemo *Memo;
        TButton *Revert;
        TButton *Cancel;
        TButton *OK;
        TMemo *Default;
        void __fastcall RevertClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TCustomTexForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCustomTexForm *CustomTexForm;
//---------------------------------------------------------------------------
#endif
