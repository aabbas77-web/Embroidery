//---------------------------------------------------------------------------
#include <vcl.h>
#include "api_VecApi.h"
#pragma hdrstop
USEUNIT("bcb_editor_DwgProc.cpp");
USEUNIT("bcb_editor_Funcs.cpp");
USEFORM("bcb_editor_Main.cpp", Form1);
USEUNIT("bcb_editor_Strings.cpp");
USEUNIT("api_VecApi.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
      // load vecad.dll
      if (vlStartup()==FALSE){
        MessageBox(0,"VECAD51.DLL is not found","Error",MB_OK);
      }else{
        // run application
        Application->Initialize();
        Application->CreateForm(__classid(TForm1), &Form1);
         Application->Run();
      }
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
