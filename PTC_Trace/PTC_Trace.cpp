//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("PTC_Trace.res");
USEFORM("About.cpp", FormAbout);
USEOBJ("..\Packages\GraphicEx\GraphicEx.obj");
USEFORM("Main.cpp", FormMain);
USEOBJ("..\Packages\GraphicEx\GraphicCompression.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENWMFGR.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENBMPGR.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENDCXGR.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENJPGGR.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENPCXGR.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENPNGGR.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENTGAGR.obj");
USEOBJ("..\Packages\Envision.Image.Lib\Envision\Sources\ENTIFGR.obj");
USEOBJ("E:\Ali\Library\Lib\Protection\skeydrv.obj");
USEFORM("..\SPL\spl_VectorImage.cpp", FormVectorImage);
USEUNIT("..\SPL\spl_CodingLib.cpp");
USEUNIT("..\SPL\spl_ColorQuantizer.cpp");
USEUNIT("..\SPL\spl_Contour.cpp");
USEFORM("..\SPL\spl_DigitizeDialog.cpp", FormDigitize);
USEUNIT("..\SPL\spl_Digitizer.cpp");
USEUNIT("..\SPL\spl_EmbFile.cpp");
USEUNIT("..\SPL\spl_EmbLib.cpp");
USEFORM("..\SPL\spl_EmbParams.cpp", FormEmbParams);
USEUNIT("..\SPL\spl_Embroidery.cpp");
USEUNIT("..\SPL\spl_FloodFill.cpp");
USEUNIT("..\SPL\spl_Image.cpp");
USEUNIT("..\SPL\spl_ImageProcessing.cpp");
USEFORM("..\SPL\spl_ImportImage.cpp", FormImportImage);
USEUNIT("..\SPL\spl_Layer.cpp");
USEFORM("..\SPL\spl_Monochrome.cpp", FormMonochrom);
USEUNIT("..\SPL\spl_MultiLayer.cpp");
USEFORM("..\SPL\spl_ObjectParams.cpp", FormObjectParams);
USEUNIT("..\SPL\spl_PathFinder.cpp");
USEUNIT("..\SPL\spl_Point.cpp");
USEFORM("..\SPL\spl_RasterImage.cpp", FormRasterImage);
USEUNIT("..\SPL\spl_Region.cpp");
USEFORM("..\SPL\spl_Resize.cpp", FormResize);
USEUNIT("..\SPL\spl_Types.cpp");
USEUNIT("..\SPL\Pyramids\pyramidfilters.cpp");
USEUNIT("..\SPL\Pyramids\pyramidtools.cpp");
USEUNIT("..\Protection\ProtectionLib.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "Embroidery Trace V1.0";
         Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->CreateForm(__classid(TFormVectorImage), &FormVectorImage);
		Application->CreateForm(__classid(TFormDigitize), &FormDigitize);
		Application->CreateForm(__classid(TFormEmbParams), &FormEmbParams);
		Application->CreateForm(__classid(TFormImportImage), &FormImportImage);
		Application->CreateForm(__classid(TFormMonochrom), &FormMonochrom);
		Application->CreateForm(__classid(TFormObjectParams), &FormObjectParams);
		Application->CreateForm(__classid(TFormRasterImage), &FormRasterImage);
		Application->CreateForm(__classid(TFormResize), &FormResize);
		Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
