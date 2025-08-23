unit DwgProc;

interface
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  OleCtnrs, StdCtrls, ExtCtrls, ComCtrls, Menus, Printers;

function MyDwgProc (hDwg,Msg,Prm1,Prm2:Integer; Prm3,Prm4:Double; Prm5:Pointer):Integer; stdcall;

implementation

uses
  api_VecApi, delphi_editor_Funcs, delphi_editor_Strings;

//-------------------------------------------------------------------
// Drawing's procedure
//-------------------------------------------------------------------
function MyDwgProc (hDwg,Msg,Prm1,Prm2:Integer; Prm3,Prm4:Double; Prm5:Pointer):Integer;
var
  bmp: tbitmap;
begin
  Result := 0;
  case Msg of
    VM_GETSTRING:
    begin
      Result := LoadString( Prm1 );
    end;

    VM_OBJACTIVE:
    begin
      if (Prm1=VL_OBJ_PAGE) then
      begin
        UpdateMainTitle();
      end
    end;

    VM_DWGLOADED:
    begin
      UpdateMainTitle();
    end;

    VM_DWGSAVED:
    begin
      UpdateMainTitle();
    end;

    VM_DWGSELECT:
    begin
      UpdateMainTitle();
    end;
{
    case VM_DWGLOADING:
    case VM_DWGSAVING:
      _stprintf( szStr, _T("Loading: %d%%"), Prm1 );
      vlStatBarSetText( VL_SB_COORD, szStr );
      break;
}

    VM_EXECUTE:
    begin
      if ((Prm2<>0) and ((Prm1=VC_FILE_NEW) or (Prm1=VC_FILE_OPEN))) then
      begin
        case Prm1 of
          VC_FILE_NEW:
          begin
            FileNew();
          end;
          VC_FILE_OPEN:
          begin
            FileOpen();
          end;
        end;
      end
    end;

    VM_RASTER:
    begin
     bmp:=tbitmap.Create;
     bmp.Width:=prm1;
     bmp.Height:=prm2;
     bmp.PixelFormat:=pf24bit;
     SetBItmapBits(bmp.Handle,Prm2*Prm1*3+Prm2*4,prm5);
     bmp.SaveToFile('c:\a1.bmp');
     bmp.Free;
     Result := 1;
    end;

  end;
end;



end.
