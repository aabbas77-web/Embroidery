//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "New.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNewImage *FormNewImage;
//---------------------------------------------------------------------------
__fastcall TFormNewImage::TFormNewImage(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormNewImage::Button1Click(TObject *Sender)
{
 ColorDialog1->Color = Panel1->Color;
 if(ColorDialog1->Execute())
  Panel1->Color = ColorDialog1->Color;
}
//---------------------------------------------------------------------------
