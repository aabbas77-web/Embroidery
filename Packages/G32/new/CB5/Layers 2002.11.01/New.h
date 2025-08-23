//---------------------------------------------------------------------------

#ifndef NewH
#define NewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormNewImage : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TEdit *ImageWidth;
    TUpDown *UpDown1;
    TEdit *ImageHeight;
    TUpDown *UpDown2;
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TColorDialog *ColorDialog1;
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormNewImage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNewImage *FormNewImage;
//---------------------------------------------------------------------------
#endif
