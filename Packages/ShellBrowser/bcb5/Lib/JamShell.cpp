//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("JamShell.res");
USEUNIT("ShellStrings.pas");
USEUNIT("ShellLink.pas");
USEUNIT("DirMon.pas");
USEUNIT("ShellBrowser.pas");
USEUNIT("ShellControls.pas");
USEPACKAGE("vcl50.bpi");
USEPACKAGE("vclx50.bpi");
USEPACKAGE("bcbsmp50.bpi");
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
