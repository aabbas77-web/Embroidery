//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GraphicExPk.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("GraphicEx.pas");
USEPACKAGE("VCLJPG50.bpi");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
//---------------------------------------------------------------------------
