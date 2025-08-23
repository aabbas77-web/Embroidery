//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("VarianPk.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("VrAnalog.pas");
USEUNIT("VrAnimate.pas");
USEUNIT("VrArrow.pas");
USEUNIT("VrBanner.pas");
USEUNIT("VrBitmapsDlg.pas");
USEUNIT("VrBlotter.pas");
USEUNIT("VrBorder.pas");
USEUNIT("VrCalendar.pas");
USEUNIT("VrCheckLed.pas");
USEUNIT("VrClasses.pas");
USEUNIT("VrCompass.pas");
USEUNIT("VrConst.pas");
USEUNIT("VrControls.pas");
USEUNIT("VrDemoButton.pas");
USEUNIT("VrDesign.pas");
USEUNIT("VrDeskTop.pas");
USEUNIT("VrDigit.pas");
USEUNIT("VrFormShape.pas");
USEUNIT("VrGauge.pas");
USEUNIT("VrGradient.pas");
USEUNIT("VrHotImage.pas");
USEUNIT("VrHyperLink.pas");
USEUNIT("VrImageLed.pas");
USEUNIT("VrJoypad.pas");
USEUNIT("VrLabel.pas");
USEUNIT("VrLcd.pas");
USEUNIT("VrLeds.pas");
USEUNIT("VrLevelBar.pas");
USEUNIT("VrLights.pas");
USEUNIT("VrMatrix.pas");
USEUNIT("VrMeter.pas");
USEUNIT("VrNavigator.pas");
USEFORMNS("VrPaletteDlg.pas", Vrpalettedlg, VrPaletteDlg);
USEUNIT("VrProgressBar.pas");
USEUNIT("VrPropEdit.pas");
USEUNIT("VrRaster.pas");
USEUNIT("VrReg.pas");
USEUNIT("VrScale.pas");
USEUNIT("VrScanner.pas");
USEUNIT("VrScope.pas");
USEUNIT("VrShadow.pas");
USEUNIT("VrShapeBtn.pas");
USEFORMNS("VrShareWin.pas", Vrsharewin, Form_VrShare);
USEUNIT("VrSlider.pas");
USEUNIT("VrSlideShow.pas");
USEUNIT("VrSpectrum.pas");
USEUNIT("VrSpinner.pas");
USEUNIT("VrSwitch.pas");
USEUNIT("VrSystem.pas");
USEUNIT("VrSysUtils.pas");
USEUNIT("VrThreads.pas");
USEUNIT("VrTrackBar.pas");
USEUNIT("VrTrayGauge.pas");
USEUNIT("VrTypes.pas");
USEUNIT("VrUpDown.pas");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
//---------------------------------------------------------------------------
