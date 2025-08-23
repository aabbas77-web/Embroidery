{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrTypes;

{$I VRLIB.INC}

interface

uses
  Windows, SysUtils;

type
  EVrException = class(Exception);

  TVrVersion = string[4];

  TVrHoursChangeEvent = procedure(Sender: TObject; Hours: Word) of object;
  TVrMinutesChangeEvent = procedure(Sender: TObject; Minutes: Word) of object;
  TVrSecondsChangeEvent = procedure(Sender: TObject; Seconds: Word) of object;

  TVrDrawStyle = (dsOwnerDraw, dsNormal);

  TVrColInt = 1..MaxInt;
  TVrRowInt = 1..MaxInt;
  TVrHoursInt = 0..23;
  TVrMinutesInt = 0..59;
  TVrSecondsInt = 0..59;
  TVrPercentInt = 0..100;
  TVrMaxInt = 1..MaxInt;
  TVrByteInt = 0..255;
  TVrNumGlyphs = 1..4;
  TVrTransparentMode = (tmPixel, tmColor);

  TVrTextAngle = 0..359;

  TVrTextAlignment = (vtaLeft, vtaCenter, vtaRight,
    vtaTopLeft, vtaTop, vtaTopRight,
    vtaBottomLeft, vtaBottom, vtaBottomRight);

const
  VrTextAlign: array[TVrTextAlignment] of Integer =
    (DT_LEFT + DT_VCENTER, DT_CENTER + DT_VCENTER, DT_RIGHT + DT_VCENTER,
     DT_TOP + DT_LEFT, DT_TOP + DT_CENTER, DT_TOP + DT_RIGHT,
     DT_BOTTOM + DT_LEFT, DT_BOTTOM + DT_CENTER, DT_BOTTOM + DT_RIGHT);


type
  TVrShapeType = (stRectangle, stSquare, stRoundRect, stRoundSquare,
    stEllipse, stCircle);

  TVrImageTextLayout = (ImageLeft, ImageRight, ImageTop, ImageBottom);

  TVrOrientation = (voVertical, voHorizontal);

  TVrTickMarks = (tmNone, tmBoth, tmBottomRight, tmTopLeft);

  TVrProgressStyle = (psBottomLeft, psTopRight);


implementation

end.
