//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "EmbPlugin.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TEmbPlugin::TEmbPlugin()
{
	m_bLoaded = false;
    hLib = NULL;
}
//---------------------------------------------------------------------------
TEmbPlugin::~TEmbPlugin()
{
	Free();
}
//---------------------------------------------------------------------------
TEmbPlugin::TEmbPlugin(const TEmbPlugin &EmbPlugin)
{
	hLib = EmbPlugin.hLib;
    m_bLoaded = EmbPlugin.m_bLoaded;
}
//---------------------------------------------------------------------------
TEmbPlugin &TEmbPlugin::operator=(const TEmbPlugin &EmbPlugin)
{
	hLib = EmbPlugin.hLib;
    m_bLoaded = EmbPlugin.m_bLoaded;
    return *this;
}
//---------------------------------------------------------------------------
void TEmbPlugin::Error(AnsiString Function)
{
 DWORD dw = GetLastError();
 AnsiString Text="["+Function+"] failed... ,\n and returned the Code Error: "+IntToStr(dw);
// MessageDlg(Text.c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void TEmbPlugin::LoadFromFile(AnsiString FileName)
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
//    	CreateInterface();
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
void TEmbPlugin::Free()
{
 	try
  	{
	 	if(m_bLoaded)
  		{
//        	DestroyInterface();
//   			if(!FreeLibrary(hLib))
//	    		Error("FreeLibrary");
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
/*
void TEmbPlugin::CreateInterface()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_CreateInterface=(TFunc_CreateInterface)GetProcAddress(hLib,"_plug_CreateInterface");
	   		if(m_func_CreateInterface == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(*m_func_CreateInterface)();
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
void TEmbPlugin::DestroyInterface()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_DestroyInterface=(TFunc_DestroyInterface)GetProcAddress(hLib,"_plug_DestroyInterface");
	   		if(m_func_DestroyInterface == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(*m_func_DestroyInterface)();
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
*/
//---------------------------------------------------------------------------
int TEmbPlugin::ShowModalInterface()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_ShowModalInterface=(TFunc_ShowModalInterface)GetProcAddress(hLib,"_plug_ShowModalInterface");
	   		if(m_func_ShowModalInterface == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return mrOk;
	    	}

	   		return (*m_func_ShowModalInterface)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return mrOk;
  		}
	}
    catch(...)
    {
    	return mrOk;
    }
}
//---------------------------------------------------------------------------
void TEmbPlugin::ShowInterface()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_ShowInterface=(TFunc_ShowInterface)GetProcAddress(hLib,"_plug_ShowInterface");
	   		if(m_func_ShowInterface == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(*m_func_ShowInterface)();
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
    	return;
    }
}
//---------------------------------------------------------------------------
void TEmbPlugin::CloseInterface()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_CloseInterface=(TFunc_CloseInterface)GetProcAddress(hLib,"_plug_CloseInterface");
	   		if(m_func_CloseInterface == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(*m_func_CloseInterface)();
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
    	return;
    }
}
//---------------------------------------------------------------------------
void TEmbPlugin::About()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_About=(TFunc_About)GetProcAddress(hLib,"_plug_About");
	   		if(m_func_About == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(*m_func_About)();
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
    	return;
    }
}
//---------------------------------------------------------------------------
void TEmbPlugin::GetIcon(Graphics::TBitmap *pIcon)
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetIcon=(TFunc_GetIcon)GetProcAddress(hLib,"_plug_GetIcon");
	   		if(m_func_GetIcon == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return;
	    	}

	   		(*m_func_GetIcon)(pIcon);
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
char *TEmbPlugin::GetName()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetName=(TFunc_GetName)GetProcAddress(hLib,"_plug_GetName");
	   		if(m_func_GetName == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return "";
	    	}

	   		return (*m_func_GetName)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return "";
  		}
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TEmbPlugin::GetHint()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetHint=(TFunc_GetHint)GetProcAddress(hLib,"_plug_GetHint");
	   		if(m_func_GetHint == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return "";
	    	}

	   		return (*m_func_GetHint)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return "";
  		}
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TEmbPlugin::GetVersion()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetVersion=(TFunc_GetVersion)GetProcAddress(hLib,"_plug_GetVersion");
	   		if(m_func_GetVersion == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return "";
	    	}

	   		return (*m_func_GetVersion)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return "";
  		}
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TEmbPlugin::GetAuthorName()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetAuthorName=(TFunc_GetAuthorName)GetProcAddress(hLib,"_plug_GetAuthorName");
	   		if(m_func_GetAuthorName == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return "";
	    	}

	   		return (*m_func_GetAuthorName)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return "";
  		}
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TEmbPlugin::GetDate()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetDate=(TFunc_GetDate)GetProcAddress(hLib,"_plug_GetDate");
	   		if(m_func_GetDate == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return "";
	    	}

	   		return (*m_func_GetDate)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return "";
  		}
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TEmbPlugin::GetGroup()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetGroup=(TFunc_GetGroup)GetProcAddress(hLib,"_plug_GetGroup");
	   		if(m_func_GetGroup == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
	     		return "";
	    	}

	   		return (*m_func_GetGroup)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
	        return "";
  		}
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
TShortCut TEmbPlugin::GetShortCut()
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_GetShortCut=(TFunc_GetShortCut)GetProcAddress(hLib,"_plug_GetShortCut");
	   		if(m_func_GetShortCut == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
				return ShortCut(Word(' '), TShiftState() << ssCtrl);
	    	}

	   		return (*m_func_GetShortCut)();
	  	}
	 	else
	  	{
//  	 		MessageDlg("Device library not loaded...",
//      	  mtError,TMsgDlgButtons()<<mbOK,0);
			return ShortCut(Word(' '), TShiftState() << ssCtrl);
  		}
	}
    catch(...)
    {
    	return ShortCut(Word(' '), TShiftState() << ssCtrl);
    }
}
//---------------------------------------------------------------------------
void TEmbPlugin::Initialize(TFunc_Redraw f_Redraw,TFunc_DrawLine func_DrawLine,
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
	   		m_func_Initialize=(TFunc_Initialize)GetProcAddress(hLib,"_plug_Initialize");
	   		if(m_func_Initialize == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
     			return;
	    	}

	   		return (*m_func_Initialize)(f_Redraw,func_DrawLine,
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
int TEmbPlugin::Draw(int Msg,int Step,double x,double y)
{
	try
    {
	 	if(m_bLoaded)
	  	{
	   		// DeviceInit
	   		m_func_Draw=(TFunc_Draw)GetProcAddress(hLib,"_plug_Draw");
	   		if(m_func_Draw == NULL)
	    	{
//  	   		MessageDlg("Error In Loading [DeviceInit] Function ...",
//      	      mtError,TMsgDlgButtons()<<mbOK,0);
     			return 0;
	    	}

            return (*m_func_Draw)(Msg,Step,x,y);
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

