//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("RealMetaFilePk.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("wmfeps_utils_RealMeta.cpp");
USEUNIT("wmfeps_utils.cpp");
USERES("wmfeps_utils.dcr");
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
