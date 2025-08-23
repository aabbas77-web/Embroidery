//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Interface.h"
#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInterface *FormInterface;
//---------------------------------------------------------------------------
__fastcall TFormInterface::TFormInterface(TComponent* Owner)
        : TForm(Owner)
{      
}
//---------------------------------------------------------------------------
//-----------------------None Exported functions-----------------------------
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
    	FormInterface->Close();
    	delete FormInterface;
        FormInterface = NULL;
    }
}
//---------------------------------------------------------------------------
//-----------------------Exported functions----------------------------------
//---------------------------------------------------------------------------
int plug_ShowModalInterface()
{
	if(FormInterface)
    {
    	return FormInterface->ShowModal();
    }
    else
    {
    	return mrOk;
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
	pIcon->Width = 16;
	pIcon->Height = 16;
    pIcon->Canvas->Brush->Style = bsSolid;
    pIcon->Canvas->Brush->Color = clWhite;
    pIcon->Canvas->FillRect(Rect(0,0,pIcon->Width,pIcon->Height));
    pIcon->TransparentColor = clWhite;
    pIcon->Transparent = true;
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
	return "Polyline";
}
//---------------------------------------------------------------------------
char *plug_GetHint()
{
	return "Polyline drawing tool";
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
	return "13/04/2004";
}
//---------------------------------------------------------------------------
char *plug_GetGroup()
{
	return "Standard";
}
//---------------------------------------------------------------------------
TShortCut plug_GetShortCut()
{
	return ShortCut(Word('L'), TShiftState() << ssCtrl);
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
int plug_Draw(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double x0;
    static double y0;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            func_Redraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need 2 Steps
            return 2;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 2:// Entered First Point
                {
                    x0=x;
                    y0=y;
                    return 1;
                }
                case 1:// Entered Second Point
                {
                    func_AddLine(x0,y0,x,y);
					if(FormInterface)
				    {
	                    if(FormInterface->CheckBoxPolyline->Checked)
	                    {
	                        x0=x;
    	                    y0=y;
	                        return 1;// Don`t End The Command
	                    }
	                    else
    	                {
	                        return 0;// End The Command
	                    }
                    }
                    else
                    {
                    	x0=x;
                        y0=y;
                        return 1;// Don`t End The Command
                    }
                }
            }
            return 0;
        }
        case VM_CMD_DRAG:
        {
            if(Step==1)
            {
                // Drag Line By Mouse While Not Click The Second Point
                func_DrawLine(x0,y0,x,y);
            }
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

