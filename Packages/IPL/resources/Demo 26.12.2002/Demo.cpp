//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Demo.res");
USEFORM("Main.cpp", FormMain);
USELIB("..\lib\ipl98d.lib");
USELIB("..\lib\ipl98.lib");
USEUNIT("..\..\..\..\Types\EXPFormat.cpp");
USEUNIT("..\..\..\..\Types\APolygon.cpp");
USEUNIT("..\..\..\..\Types\APolygons.cpp");
USEUNIT("..\..\..\..\Types\APolyPolygons.cpp");
USEUNIT("..\..\..\..\Types\DSTFormat.cpp");
USEUNIT("..\..\..\..\Types\EmbFile.cpp");
USEUNIT("..\..\..\..\Types\EmbTypes.cpp");
USEUNIT("..\..\..\..\Types\APoint.cpp");
USEUNIT("..\..\..\..\Types\PolyStitch.cpp");
USELIB("..\..\..\..\CVOPEN\Lib\CV.lib");
USEFORM("..\..\..\..\Types\ProgressOne.cpp", FormProgressOne);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TFormMain), &FormMain);
         Application->CreateForm(__classid(TFormProgressOne), &FormProgressOne);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
