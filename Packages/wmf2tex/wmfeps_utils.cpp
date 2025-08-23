//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("wmfeps_utils.res");
USERES("wmfeps_utils.dcr");
USEUNIT("wmfeps_utils_EpsGen.cpp");
USEUNIT("wmfeps_utils_shellink.cpp");
USEUNIT("wmfeps_utils_RealMeta.cpp");
USEPACKAGE("VCL50.bpi");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Package source.
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
        return 1;
}
//---------------------------------------------------------------------------
