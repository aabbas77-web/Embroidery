//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("PTC_AlbumMaker.res");
USEFORM("Main.cpp", FormMain);
USEFORM("About.cpp", FormAbout);
USEUNIT("..\SPL\spl_Types.cpp");
USEUNIT("..\SPL\spl_CodingLib.cpp");
USEUNIT("..\SPL\spl_EmbLib.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
