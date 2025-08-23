#include "wmf2tex.h"
#pragma hdrstop
USERES("wmf2tex.res");
USEFORM("f_main.cpp", MainForm);
USEFORM("f_clip.cpp", ClipForm);
USEUNIT("wmfeps_utils_EpsGen.cpp");
USEFORM("f_hen.cpp", Proc);
USEUNIT("wmfeps_utils_shellink.cpp");
USEFORM("f_custom.cpp", CustomTexForm);
USEUNIT("wmfeps_utils_RealMeta.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
