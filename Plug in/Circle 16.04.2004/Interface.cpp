//---------------------------------------------------------------------------

#include <vcl.h>
#include <Math.hpp>
#pragma hdrstop

#include "Interface.h"
#include "About.h"
#include "spl_Contour.h"
#include "spl_Embroidery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFormInterface *FormInterface;
//---------------------------------------------------------------------------
__fastcall TFormInterface::TFormInterface(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//-----------------------Exported functions----------------------------------
//---------------------------------------------------------------------------
void plug_CreateInterface()
{
	FormInterface = new TFormInterface(Application);
}
//---------------------------------------------------------------------------
void plug_DestroyInterface()
{
	if(FormInterface)
    {
    	delete FormInterface;
        FormInterface = NULL;
    }
}
//---------------------------------------------------------------------------
int plug_ShowModalInterface()
{
	if(FormInterface)
    {
    	return FormInterface->ShowModal();
    }
    else
    {
    	return mrNone;
    }
}
//---------------------------------------------------------------------------
void plug_ShowInterface()
{
	if(FormInterface)
    {
    	FormInterface->Show();
    }
}
//---------------------------------------------------------------------------
void plug_CloseInterface()
{
	if(FormInterface)
    {
    	FormInterface->Close();
    }
}
//---------------------------------------------------------------------------
void plug_GetIcon(Graphics::TBitmap *pIcon)
{
	if(FormInterface == NULL)	return;
	pIcon->Width = 32;
	pIcon->Height = 32;
    pIcon->Canvas->Brush->Style = bsSolid;
    pIcon->Canvas->Brush->Color = clWhite;
    pIcon->Canvas->FillRect(Rect(0,0,pIcon->Width,pIcon->Height));
    pIcon->Canvas->Draw(0,0,FormInterface->Icon);
}
//---------------------------------------------------------------------------
void plug_About()
{
	FormAbout = new TFormAbout(Application);
	FormAbout->ShowModal();
    if(FormAbout)
    {
     	delete FormAbout;
        FormAbout = NULL;
    }
}
//---------------------------------------------------------------------------
char *plug_GetName()
{
	return "Circles";
}
//---------------------------------------------------------------------------
char *plug_GetHint()
{
	return "Circles drawing tool";
}
//---------------------------------------------------------------------------
char *plug_GetVersion()
{
	return "1.0";
}
//---------------------------------------------------------------------------
char *plug_GetAuthorName()
{
	return "Ali Abbas";
}
//---------------------------------------------------------------------------
char *plug_GetDate()
{
	return "15/04/2004";
}
//---------------------------------------------------------------------------
char *plug_GetGroup()
{
	return "Standard";
}
//---------------------------------------------------------------------------
TShortCut plug_GetShortCut()
{
	return ShortCut(Word('C'), TShiftState() << ssCtrl);
}
//---------------------------------------------------------------------------
TFunc_Redraw func_Redraw;

TFunc_DrawLine func_DrawLine;
TFunc_DrawPolyline func_DrawPolyline;
TFunc_DrawPolygon func_DrawPolygon;
TFunc_DrawCircle func_DrawCircle;
TFunc_DrawArc func_DrawArc; 
TFunc_DrawEllipse func_DrawEllipse;
TFunc_DrawText func_DrawText;

TFunc_AddLine func_AddLine;
TFunc_AddCircle func_AddCircle;
TFunc_AddCircle3P func_AddCircle3P;
TFunc_AddArc func_AddArc;
TFunc_AddArc3P func_AddArc3P;
TFunc_AddEllipse func_AddEllipse;
TFunc_AddArcEx func_AddArcEx;
TFunc_SetTextParam func_SetTextParam;
TFunc_SetTextParams func_SetTextParams;
TFunc_AddText func_AddText;
TFunc_PolylineBegin func_PolylineBegin;
TFunc_Vertex func_Vertex;
TFunc_VertexR func_VertexR;
TFunc_VertexF func_VertexF;
TFunc_VertexB func_VertexB;
TFunc_AddPolyline func_AddPolyline;
TFunc_AddRect func_AddRect;
//---------------------------------------------------------------------------
void plug_Initialize(TFunc_Redraw f_Redraw,TFunc_DrawLine f_DrawLine,
				TFunc_DrawPolyline f_DrawPolyline,TFunc_DrawPolygon f_DrawPolygon,
                TFunc_DrawCircle f_DrawCircle,TFunc_DrawArc f_DrawArc,
                TFunc_DrawEllipse f_DrawEllipse,TFunc_DrawText f_DrawText,
                TFunc_AddLine f_AddLine,TFunc_AddCircle f_AddCircle,
                TFunc_AddCircle3P f_AddCircle3P,TFunc_AddArc f_AddArc,
                TFunc_AddArc3P f_AddArc3P,TFunc_AddEllipse f_AddEllipse,
                TFunc_AddArcEx f_AddArcEx,TFunc_SetTextParam f_SetTextParam,
                TFunc_SetTextParams f_SetTextParams,TFunc_AddText f_AddText,
                TFunc_PolylineBegin f_PolylineBegin,TFunc_Vertex f_Vertex,
                TFunc_VertexR f_VertexR,TFunc_VertexF f_VertexF,
                TFunc_VertexB f_VertexB,TFunc_AddPolyline f_AddPolyline,
                TFunc_AddRect f_AddRect)
{
	func_Redraw = f_Redraw;
	func_DrawLine = f_DrawLine;
	func_DrawPolyline = f_DrawPolyline;
	func_DrawPolygon = f_DrawPolygon;
	func_DrawCircle = f_DrawCircle;
	func_DrawArc = f_DrawArc;
	func_DrawEllipse = f_DrawEllipse;
	func_DrawText = f_DrawText;

	func_AddLine = f_AddLine;
	func_AddCircle = f_AddCircle;
	func_AddCircle3P = f_AddCircle3P;
	func_AddArc = f_AddArc;
	func_AddArc3P = f_AddArc3P;
	func_AddEllipse = f_AddEllipse;
	func_AddArcEx = f_AddArcEx;
	func_SetTextParam = f_SetTextParam;
	func_SetTextParams = f_SetTextParams;
	func_AddText = f_AddText;
	func_PolylineBegin = f_PolylineBegin;
	func_Vertex = f_Vertex;
	func_VertexR = f_VertexR;
	func_VertexF = f_VertexF;
	func_VertexB = f_VertexB;
	func_AddPolyline = f_AddPolyline;
	func_AddRect = f_AddRect;
}
//---------------------------------------------------------------------------
void AddPolyline(spl_Contour &Contour,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    func_PolylineBegin();
    for(spl_UInt i=0;i<=PointsCount;i++)
    {
        func_Vertex(Contour.Points[i % PointsCount].x,Contour.Points[i % PointsCount].y);
    }
    func_AddPolyline(VL_POLY_LINE,true);
}
//---------------------------------------------------------------------------
void DrawPolyline(spl_Contour &Contour,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    for(spl_UInt i=0;i<PointsCount;i++)
    {
        func_DrawLine(Contour.Points[(i) % PointsCount].x,Contour.Points[(i) % PointsCount].y,Contour.Points[(i+1) % PointsCount].x,Contour.Points[(i+1) % PointsCount].y);
    }
}
//---------------------------------------------------------------------------
int plug_Draw(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;
    static double dScaleDistance;

    static double Density=1.0;
    static bool Default = false;
    static bool bMin = true;

    static spl_Rect Frame;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            func_Redraw();
            Created = false;
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.clear();
            Extrude.Points.clear();
            Created = false;
            return 2;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == 2)
            {
				// Create new shape
	        	spl_Point P;
	            float fXRadius = 3.0;
	            float fYRadius = 3.0;
                float Degrees = 45.0;
                ExtrudeDistance = 10.0;
				if(FormInterface)
			    {
		            fXRadius = FormInterface->CSpinEditRadiusX->Value;
		            fYRadius = FormInterface->CSpinEditRadiusY->Value;
        	        Degrees = FormInterface->CSpinEditDegrees->Value;
                    ExtrudeDistance = FormInterface->CSpinEditExtrude->Value;
                }
                if(Degrees <= 2)	Degrees = 3;
                float fStep = 360.0/Degrees;
                float fSign = 1.0;

                Contour.Points.clear();
	        	for(float fAngle=0.0;fAngle<360.0;fAngle+=fStep)
	            {
					P.x = x + fSign*fXRadius * cos(DegToRad(fAngle));
					P.y = y + fSign*fYRadius * sin(DegToRad(fAngle));

	            	Contour.Points.push_back(P);
                    fSign = -fSign;
	            }

//	            spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
//	            spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Extrude,Result);
//                Result = Extrude;
//                Contour = Result;
				Result = Contour;
	        	Center = spl_Center(Result);
            	Created = true;
    	        return 1;
            }
            else
        	if(Step == 1)
            {
	            AddPolyline(Contour,Color);
    	        return 0;// End The Command
            }
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
			dx=spl_ABS(x-Center.x);
            dy=spl_ABS(y-Center.y);
            dScaleDistance=sqrt(dx*dx+dy*dy);

			Frame.left = Center.x - dScaleDistance;
			Frame.right = Center.x + dScaleDistance;
			Frame.top = Center.y - dScaleDistance;
			Frame.bottom = Center.y + dScaleDistance;

            spl_ScaleContour(Result,Frame,false,1.0,Contour);
            DrawPolyline(Contour,Color);
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            func_Redraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
//-------------------Interface methods---------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFormInterface::SpeedButton1Click(TObject *Sender)
{
	plug_About();
}
//---------------------------------------------------------------------------

