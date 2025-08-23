#include "wmf2tex.h"
#pragma hdrstop
USERES("testmf.res");
USEFORM("f_testmf.cpp", Form1);
USEUNIT("wmfeps_utils_RealMeta.cpp");
USEFORM("f_testplay.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
