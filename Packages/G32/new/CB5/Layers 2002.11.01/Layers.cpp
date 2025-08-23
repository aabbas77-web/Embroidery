//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Layers.res");
USEFORM("Main.cpp", FormMain);
USEFORM("New.cpp", FormNewImage);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TFormMain), &FormMain);
         Application->CreateForm(__classid(TFormNewImage), &FormNewImage);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
