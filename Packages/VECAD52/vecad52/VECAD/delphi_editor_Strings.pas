unit Strings;

interface
uses
  Windows;

function  LoadString (Id:Integer): Integer;

implementation

uses
  VecApi;


//-------------------------------------------------------------------
//  Overwrite VeCAD strings
//  Used to localize VeCAD to other languages
//-------------------------------------------------------------------
function LoadString (Id:Integer): Integer;
var
  str: Pchar;
  res: Integer;
begin
  str := '';
  res := 1;
  // assign new string according to string's identifier
  case Id of
    VS_PRINT_TITLE:   str:='Print2';
    VS_ENTPROP_TITLE: str:='Objects properties 2';
    VS_LINE_TITLE:    str:='Line2';
    else
      res := 0;  // string was not overwritten
  end;
  // pass new string to VeCAD
  if res=1 then vlPropPut( VD_MSG_STRING, 0, str );
  LoadString := res;
end;

end.
