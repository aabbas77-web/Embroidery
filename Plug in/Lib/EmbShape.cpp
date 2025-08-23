//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "EmbShape.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TEmbShape::TEmbShape()
{
	m_bLoaded = false;
    hLib = NULL;
}
//---------------------------------------------------------------------------
TEmbShape::~TEmbShape()
{
	Free();
}
//---------------------------------------------------------------------------
void TEmbShape::Error(AnsiString Function)
{
 DWORD dw = GetLastError();
 AnsiString Text="["+Function+"] failed... ,\n and returned the Code Error: "+IntToStr(dw);
// MessageDlg(Text.c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void TEmbShape::LoadFromFile(AnsiString FileName)
{
 	try
  	{
		Free();
   		hLib=LoadLibrary(FileName.c_str());
   		if(hLib==NULL)
    	{
     		Error(FileName.c_str());
     		m_bLoaded=false;
     		return;
    	}
   		m_bLoaded=true;
  	}
 	catch(...)
  	{
//   		MessageDlg("Error In Loading Device Data ...",
//              	mtError,TMsgDlgButtons()<<mbOK,0);
//   		if(!FreeLibrary(hLib))
//    		Error("FreeLibrary");
//   		m_bLoaded=false;
//   		return;
  	}
}
//---------------------------------------------------------------------------
void TEmbShape::Free()
{
 	try
  	{
	 	if(m_bLoaded)
  		{
        	DestroyInterface();
   			if(!FreeLibrary(hLib))
	    		Error("FreeLibrary");
	    	hLib = NULL;
     		m_bLoaded=false;
  		}
  	}
 	catch(...)
  	{
//   		MessageDlg("Error In Loading Device Data ...",
//              	mtError,TMsgDlgButtons()<<mbOK,0);
//   		return;
  	}
}
//---------------------------------------------------------------------------
void TEmbShape::DestroyInterface()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_DestroyInterface=(TFunc_DestroyInterface)GetProcAddress(hLib,"_DestroyInterface");
	   		if(m_func_DestroyInterface == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(m_func_DestroyInterface)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return;
  		}
	}
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------
void TEmbShape::GetIcon(Graphics::TBitmap *pIcon)
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetIcon=(TFunc_GetIcon)GetProcAddress(hLib,"_GetIcon");
	   		if(m_func_GetIcon == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(m_func_GetIcon)(pIcon);
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return;
  		}
	}
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------
void TEmbShape::Initialize(TFunc_Redraw f_Redraw,TFunc_DrawLine func_DrawLine,
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
                TFunc_AddRect func_AddRect)
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_Initialize=(TFunc_Initialize)GetProcAddress(hLib,"_Initialize");
	   		if(m_func_Initialize == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
     			return;
	    	}

	   		return (m_func_Initialize)(f_Redraw,func_DrawLine,
					func_DrawPolyline,func_DrawPolygon,
	                func_DrawCircle,func_DrawArc,
	                func_DrawEllipse,func_DrawText,
	                func_AddLine,func_AddCircle,
	                func_AddCircle3P,func_AddArc,
	                func_AddArc3P,func_AddEllipse,
	                func_AddArcEx,func_SetTextParam,
	                func_SetTextParams,func_AddText,
	                func_PolylineBegin,func_Vertex,
	                func_VertexR,func_VertexF,
	                func_VertexB,func_AddPolyline,
                    func_AddRect);
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
// 	       mtError,TMsgDlgButtons()<<mbOK,0);
    	    return;
		}
	}
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------
int TEmbShape::Draw(int Msg,int Step,double x,double y,bool OnlyOne)
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_Draw=(TFunc_Draw)GetProcAddress(hLib,"_Draw");
	   		if(m_func_Draw == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
     			return 0;
	    	}

            return (m_func_Draw)(Msg,Step,x,y,OnlyOne);
  		}
	 	else
  		{
//   			MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
        	return 0;
	  	}
	}
    catch(...)
    {
    	return 0;
    }
}
//---------------------------------------------------------------------------

