//---------------------------------------------------------------------------
#include <windows.h>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "Interface.h"
//---------------------------------------------------------------------------
#pragma argsused
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	switch(reason)
    {
     	case DLL_PROCESS_ATTACH:
        {
//        	ShowMessage("Create DLL");
			plug_CreateInterface();
         	break;
        }
     	case DLL_PROCESS_DETACH:
        {
//        	ShowMessage("Destroy DLL");
        	plug_DestroyInterface();
         	break;
        }
    }
    return 1;
}
//---------------------------------------------------------------------------
 