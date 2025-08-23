//---------------------------------------------------------------------------
#ifndef InterfaceH
#define InterfaceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "api_VecApi.h"
//---------------------------------------------------------------------------
typedef BOOL VC_API (*TFunc_Redraw)();

typedef BOOL VC_API (*TFunc_DrawLine)(double X1, double Y1, double X2, double Y2);
typedef BOOL VC_API (*TFunc_DrawPolyline)(const VLPOINT* Ver, int n_ver, BOOL bClosed);
typedef BOOL VC_API (*TFunc_DrawPolygon)(const VLPOINT* Ver, int n_ver, BOOL bFill, BOOL bBorder, COLORREF FillColor);
typedef BOOL VC_API (*TFunc_DrawCircle)(double X, double Y, double Rad);
typedef BOOL VC_API (*TFunc_DrawArc)(double X, double Y, double Rad, double Angle1, double Angle2);
typedef BOOL VC_API (*TFunc_DrawEllipse)(double X, double Y, double Rh, double Rv, double Angle);
typedef BOOL VC_API (*TFunc_DrawText)(double X, double Y, LPCTSTR szText);

typedef int  VC_API (*TFunc_AddLine)(double X1, double Y1, double X2, double Y2);
typedef int  VC_API (*TFunc_AddCircle)(double X, double Y, double Rad);
typedef int  VC_API (*TFunc_AddCircle3P)(double X1, double Y1, double X2, double Y2, double X3, double Y3);
typedef int  VC_API (*TFunc_AddArc)(double X, double Y, double Rad, double Ang1, double Ang2);
typedef int  VC_API (*TFunc_AddArc3P)(double X1, double Y1, double X2, double Y2, double X3, double Y3);
typedef int  VC_API (*TFunc_AddEllipse)(double X, double Y, double Rh, double Rv, double Angle);
typedef int  VC_API (*TFunc_AddArcEx)(double X, double Y, double Rh, double Rv, double Ang0, double AngArc, double AngRot);
typedef BOOL VC_API (*TFunc_SetTextParam)(int Mode, double Var);
typedef BOOL VC_API (*TFunc_SetTextParams)(int Align, double Height, double Angle, double ScaleW, double Oblique, double HInter, double VInter);
typedef int  VC_API (*TFunc_AddText)(double X, double Y, LPCTSTR szStr);
typedef BOOL VC_API (*TFunc_PolylineBegin)();
typedef BOOL VC_API (*TFunc_Vertex)(double X, double Y);
typedef BOOL VC_API (*TFunc_VertexR)(double X, double Y, double Radius);
typedef BOOL VC_API (*TFunc_VertexF)(double X, double Y, BOOL bOnCurve);
typedef BOOL VC_API (*TFunc_VertexB)(double X, double Y, double Bulge);
typedef int  VC_API (*TFunc_AddPolyline)(int SmoothType, BOOL bClosed);
typedef int  VC_API (*TFunc_AddRect)(double X, double Y, double W, double H, double Ang, double Rad);
//---------------------------------------------------------------------------
class TFormInterface : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TCheckBox *CheckBoxPolyline;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TSpeedButton *SpeedButton1;
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInterface(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInterface *FormInterface;
//---------------------------------------------------------------------------
void plug_CreateInterface();
void plug_DestroyInterface();
//---------------------------------------------------------------------------
//extern "C" __declspec(dllexport) void plug_CreateInterface();
//extern "C" __declspec(dllexport) void plug_DestroyInterface();
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) void plug_ShowInterface();
extern "C" __declspec(dllexport) void plug_CloseInterface();
extern "C" __declspec(dllexport) int plug_ShowModalInterface();
extern "C" __declspec(dllexport) void plug_GetIcon(Graphics::TBitmap *pIcon);
extern "C" __declspec(dllexport) char *plug_GetName();
extern "C" __declspec(dllexport) char *plug_GetHint();
extern "C" __declspec(dllexport) char *plug_GetVersion();
extern "C" __declspec(dllexport) char *plug_GetGroup();
extern "C" __declspec(dllexport) TShortCut plug_GetShortCut();
extern "C" __declspec(dllexport) char *plug_GetAuthorName();
extern "C" __declspec(dllexport) char *plug_GetDate();
extern "C" __declspec(dllexport) void plug_About();
extern "C" __declspec(dllexport) void plug_Initialize(TFunc_Redraw f_Redraw,TFunc_DrawLine func_DrawLine,
				TFunc_DrawPolyline func_DrawPolyline,TFunc_DrawPolygon func_DrawPolygon,
                TFunc_DrawCircle func_DrawCircle,TFunc_DrawArc func_DrawArc,
                TFunc_DrawEllipse func_DrawEllipse,TFunc_DrawText func_DrawText,
                TFunc_AddLine func_AddLine,TFunc_AddCircle func_AddCircle,
                TFunc_AddCircle3P func_AddCircle3P,TFunc_AddArc func_AddArc,
                TFunc_AddArc3P func_AddArc3P,TFunc_AddEllipse func_AddEllipse,
                TFunc_AddArcEx func_AddArcEx,TFunc_SetTextParam func_SetTextParam,
                TFunc_SetTextParams func_SetTextParams,TFunc_AddText func_AddText,
                TFunc_PolylineBegin func_PolylineBegin,TFunc_Vertex func_Vertex,
                TFunc_VertexR func_VertexR,TFunc_VertexF func_VertexF,
                TFunc_VertexB func_VertexB,TFunc_AddPolyline func_AddPolyline,
                TFunc_AddRect func_AddRect);
extern "C" __declspec(dllexport) int plug_Draw(int Msg,int Step,double x,double y);
//---------------------------------------------------------------------------
#endif
