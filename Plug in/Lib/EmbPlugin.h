//---------------------------------------------------------------------------
#ifndef EmbPluginH
#define EmbPluginH
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
//typedef void (*TFunc_CreateInterface)();
//typedef void (*TFunc_DestroyInterface)();
typedef int (*TFunc_ShowModalInterface)();
typedef void (*TFunc_ShowInterface)();
typedef void (*TFunc_CloseInterface)();
typedef void (*TFunc_GetIcon)(Graphics::TBitmap *pIcon);
typedef char *(*TFunc_GetName)();
typedef char *(*TFunc_GetHint)();
typedef char *(*TFunc_GetVersion)();
typedef char *(*TFunc_GetAuthorName)();
typedef char *(*TFunc_GetDate)();
typedef char *(*TFunc_GetGroup)();
typedef TShortCut (*TFunc_GetShortCut)();
typedef void (*TFunc_About)();
typedef void (*TFunc_Initialize)(TFunc_Redraw f_Redraw,TFunc_DrawLine func_DrawLine,
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
typedef int (*TFunc_Draw)(int Msg,int Step,double x,double y);
//---------------------------------------------------------------------------
class TEmbPlugin
{
private:
//	TFunc_CreateInterface m_func_CreateInterface;
//	TFunc_DestroyInterface m_func_DestroyInterface;
    TFunc_ShowInterface	m_func_ShowInterface;
    TFunc_CloseInterface m_func_CloseInterface;
    TFunc_ShowModalInterface m_func_ShowModalInterface;
    TFunc_GetName m_func_GetName;
    TFunc_GetHint m_func_GetHint;
    TFunc_GetVersion m_func_GetVersion;
	TFunc_GetIcon m_func_GetIcon;
    TFunc_About m_func_About;
    TFunc_GetAuthorName m_func_GetAuthorName;
    TFunc_GetDate m_func_GetDate;
    TFunc_GetGroup m_func_GetGroup;
    TFunc_GetShortCut m_func_GetShortCut;
	TFunc_Initialize m_func_Initialize;
	TFunc_Draw m_func_Draw;
	void Free();
protected:
	HINSTANCE  hLib;
    bool       m_bLoaded;
public:
	TEmbPlugin();
    ~TEmbPlugin();
	TEmbPlugin(const TEmbPlugin &EmbPlugin);
	TEmbPlugin &operator=(const TEmbPlugin &EmbPlugin);
	void Error(AnsiString Function);
	void LoadFromFile(AnsiString FileName);
//	void CreateInterface();
//	void DestroyInterface();
	int ShowModalInterface();
	void ShowInterface();
	void CloseInterface();
	void GetIcon(Graphics::TBitmap *pIcon);
	char *GetName();
	char *GetHint();
	char *GetVersion();
	void About();
	char *GetAuthorName();
	char *GetDate();
	char *GetGroup();
	TShortCut GetShortCut();
	void Initialize(TFunc_Redraw f_Redraw,TFunc_DrawLine func_DrawLine,
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
	int Draw(int Msg,int Step,double x,double y);
};
//---------------------------------------------------------------------------
#endif
