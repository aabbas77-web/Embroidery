unit G32_Reg;

{*********************************************}
{  This unit is a part of Graphics32 library  }
{  Copyright © 2000-2001 Alex Denissov        }
{  See License.txt for licence information    }
{*********************************************}

interface

{$I G32.INC}

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Consts, Registry, ExtCtrls, StdCtrls, DsgnIntf, TypInfo, ExtDlgs, Clipbrd,
  ImgList, ComCtrls, Menus;

procedure Register;

implementation

uses
  G32,
  G32_Dsgn_Color,
  G32_Dsgn_Bitmap,
  G32_Image,
  G32_Layers,
  G32_RangeBars;

{ Registration }
procedure Register;
begin
  RegisterComponents('Graphics32', [TPaintBox32, TImage32, TBitmap32List,
    TRangeBar, TGaugeBar, TImgView32]);
  RegisterPropertyEditor(TypeInfo(TColor32), nil, '', TColor32Property);
  RegisterPropertyEditor(TypeInfo(TBitmap32), nil, '', TBitmap32Property);
  RegisterComponentEditor(TCustomImage32, TImage32Editor);
end;

end.
