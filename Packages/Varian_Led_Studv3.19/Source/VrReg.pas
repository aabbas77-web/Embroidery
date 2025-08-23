{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrReg;

{$I VRLIB.INC}

interface

uses {$IFDEF VRSHARE}VrShareWin,{$ENDIF}
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  DsgnIntf,{ DsgnWnds,} VrConst, VrTypes, VrClasses, VrControls, VrSysUtils,
  VrAnalog, VrArrow, VrBlotter, VrBorder, VrCalendar, VrCheckLed, VrDigit,
  VrGauge, VrGradient, VrImageLed, VrJoyPad, VrLabel, VrLCD, VrLeds, VrLights,
  VrMatrix, VrMeter, VrNavigator, VrRaster, VrScale, VrScanner, VrScope,
  VrShadow, VrSpectrum, VrSpinner, VrSwitch, VrTrackBar, VrSlider,
  VrTrayGauge, VrProgressBar, VrPaletteDlg, VrHyperLink, VrBanner, VrDeskTop,
  VrDesign, VrBitmapsDlg, VrPropEdit, VrHotImage, VrLevelBar, VrSystem,
  VrAnimate, VrThreads, VrDemoButton, VrUpDown, VrSlideShow, VrFormShape,
  VrCompass;


procedure Register;


implementation

{$R VRLIB.RES}


procedure Register;
begin
  RegisterComponents('Varian Led Studio', [TVrAnalogClock,
    TVrArrow, TVrBlotter, TVrCalendar, TVrCheckLed, TVrGauge,
    TVrGradient, TVrJoypad, TVrNum, TVrClock, TVrLed, TVrLights,
    TVrMatrix, TVrRaster, TVrScanner, TVrIndicator, TVrSpectrum,
    TVrSlider, TVrLevelBar]);

  RegisterComponents('Varian Page 2', [TVrBorder,
    TVrDigit, TVrImageLed, TVrLabel, TVrMeter, TVrMediaButton,
    TVrNavigator, TVrScale, TVrScope, TVrShadowButton, TVrSpinner,
    TVrSwitch, TVrTrackBar, TVrTrayGauge, TVrUserLed, TVrProgressBar,
    TVrBanner, TVrHyperLink, TVrHotImage]);

  RegisterComponents('Varian Page 3', [TVrDemoButton, TVrUpDown,
    TVrSlideShow, TVrCompass, TVrCounter, TVrBitmapImage,
    TVrDeskTop, TVrAnimate, TVrBitmapButton, TVrFormShape,
    TVrBitmapList, TVrStringList, TVrTimer, TVrThread, TVrKeyStatus,
    TVrTrayIcon]);

  RegisterPropertyEditor(TypeInfo(TVrPalette), nil, '', TVrPaletteProperty);
  RegisterPropertyEditor(TypeInfo(TVrVersion), nil, '', TVrVersionProperty);
  RegisterPropertyEditor(TypeInfo(TVrBitmaps), nil, '', TVrBitmapsProperty);
  RegisterComponentEditor(TVrBitmapList, TVrBitmapListEditor);
  RegisterComponentEditor(TVrStringList, TVrStringListEditor);
end;


end.
