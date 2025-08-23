//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <math.hpp>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DrawSpiral(double a,double b,double c,double T)
{
	// Clear Image
	Image->Canvas->Brush->Color = clWhite;
	Image->Canvas->Brush->Style = bsSolid;
	Image->Canvas->FillRect(Rect(0,0,Image->Width,Image->Height));

    // Draw
    double dt = 1.0;
    double r;
    TPoint P0 = Point(Image->Width/2.0,Image->Height/2.0);
    TPoint P = Point(P0.x+c,P0.y);
	Image->Canvas->Pen->Color = clBlue;
	Image->Canvas->Pen->Width = 10;
    Image->Canvas->MoveTo(P.x,P.y);
    for(double t=0.0;t<=T;t+=dt)
    {
    	r = a*t*t+b*t+c;
		P.x = P0.x + r*cos(DegToRad(t));
		P.y = P0.y + r*sin(DegToRad(t));

        Image->Canvas->LineTo(P.x,P.y);
        Image->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	Image->Picture->Bitmap->Width = 1024;
	Image->Picture->Bitmap->Height = 867;
    CSpinEditAChange(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CSpinEditAChange(TObject *Sender)
{
	DrawSpiral(CSpinEditA->Value/100000.0,CSpinEditB->Value/1000.0,CSpinEditC->Value,CSpinEditT->Value);	
}
//---------------------------------------------------------------------------

