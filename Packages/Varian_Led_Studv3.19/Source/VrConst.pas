{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrConst;

{$I VRLIB.INC}

interface

uses
  Forms, Windows, Graphics, VrTypes;

const
  VrLibVersion = '3.19';

  ResColorLow = clGray;
  ResColorHigh = clSilver;

  VrCursorHandPoint = 99;

  SC_DRAGMOVE = $F012;


implementation

{$R VRCURSORS.D32}



initialization
  Screen.Cursors[VrCursorHandPoint] := LoadCursor(hInstance, 'VRCURSORHANDPOINT');

end.
 