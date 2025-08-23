//---------------------------------------------------------------------------
#ifndef f_clipH
#define f_clipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TClipForm : public TForm
{
__published:	// IDE-managed Components
        TEdit *File;
        TButton *bFile;
        TComboBox *Format;
        TButton *bSave;
        TButton *bCancel;
        TButton *bStop;
        TCheckBox *Silent;
        TBevel *Bevel1;
        TSaveDialog *SaveDialog;
        void __fastcall FormatChange(TObject *Sender);
        void __fastcall bFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TClipForm(TComponent* Owner);
        void __fastcall CreateParams(TCreateParams &cp);
};
//---------------------------------------------------------------------------
extern PACKAGE TClipForm *ClipForm;
//---------------------------------------------------------------------------
#endif
