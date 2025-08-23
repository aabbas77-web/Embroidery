//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "bcb_editor_DwgProc.h"
#include "api_VecApi.h"
#include "bcb_editor_Funcs.h"
#include "bcb_editor_Strings.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


//-------------------------------------
int CALLBACK DwgProc (int iDwg, UINT Msg, int Prm1, int Prm2, double Prm3, double Prm4, void* Prm5)
{
  switch( Msg ){
    case VM_GETSTRING:
      return LoadString( Prm1 );

    case VM_ZOOM:
      break;

    case VM_MOUSEMOVE:
//      _stprintf( szStr, _T("%.3f : %.3f"), Prm3, Prm4 );
      break;

    case VM_ENDPAINT:
      break;

    case VM_OBJACTIVE:
      if (Prm1==VL_OBJ_PAGE){
        UpdateMainTitle();
      }
      break;

    case VM_DWGLOADED:
    case VM_DWGSAVED:
//      gMruList.Add( (LPCTSTR)Prm5 );
    case VM_DWGSELECT:
      UpdateMainTitle();
      break;

    case VM_DWGLOADING:
    case VM_DWGSAVING:
//      _stprintf( szStr, _T("Loading: %d%%"), Prm1 );
//      vlStatBarSetText( VL_SB_COORD, szStr );
      break;


    case VM_EXECUTE:
      if (Prm2!=0 &&
          (Prm1==VC_FILE_NEW || Prm1==VC_FILE_OPEN))
      {
        switch( Prm1 ){
          case VC_FILE_NEW:  FileNew();  break;
          case VC_FILE_OPEN: FileOpen(); break;
        }
      }
      break;

    case VM_LBDOWN:
//      return CmdPaint2();
      break;
  }
  return 0;
}

