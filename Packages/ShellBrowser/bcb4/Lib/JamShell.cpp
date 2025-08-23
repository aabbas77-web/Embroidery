//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("JamShell.res");
USEUNIT("ShellStrings.pas");
USEUNIT("JamAbout.pas");
USEUNIT("ShellLink.pas");
USEUNIT("DirMon.pas");
USEPACKAGE("VCL40.bpi");
USEPACKAGE("VCLX40.bpi");
USEUNIT("ShellBrowser.pas");
USEUNIT("ShellControls.pas");
USEPACKAGE("bcbsmp40.bpi");
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
