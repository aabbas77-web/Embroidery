//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "api_VecApi.h"
#include "About.h"
#include "cad_Messages.h"
#include "spl_EmbOpenDialog.h"
#include "spl_MultiLayer.h"
#include "cad_Display.h"
#include "ProtectionLib.h"
#include "spl_Embroidery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TB97"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FindFiles(TStringList *pFiles)
{
 	TSearchRec SR;
 	int iAttributes=0;
    AnsiString strPath = IncludeTrailingBackslash(ExtractFilePath(Application->ExeName))+"Plug in\\";
 	iAttributes |= faArchive | faAnyFile;
    pFiles->Clear();
 	if(FindFirst(strPath+"*.dll",iAttributes,SR)==0)
  	{
   		do
    	{
     		if((SR.Attr & iAttributes) == SR.Attr)
      			pFiles->AddObject(IncludeTrailingBackslash(strPath)+SR.Name,NULL);
    	}
        while(FindNext(SR) == 0);
   		FindClose(SR);
  	}
}    
//---------------------------------------------------------------------------
void __fastcall TFormMain::DoClickPlugin(TObject *Sender)
{
	if(Sender == NULL)	return;
    nCurrPluginIndex = (dynamic_cast<TMenuItem *>(Sender))->Tag;
    TEmbPlugin *pEmbPlugin;
    pEmbPlugin = (TEmbPlugin *)pPlugins->Objects[nCurrPluginIndex];
    if(pEmbPlugin == NULL)	return;
    if(pEmbPlugin->ShowModalInterface() != mrOk)	return;
    vlExecute(spl_CMD_PLUG_IN);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClearPlugins()
{
    TEmbPlugin *pEmbPlugin;
    for(int i=0;i<pPlugins->Count;i++)
    {
     	pEmbPlugin = (TEmbPlugin *)pPlugins->Objects[i];
        if(pEmbPlugin)
        {
         	delete pEmbPlugin;
            pEmbPlugin = NULL;
        }
    }
    pPlugins->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::UpdatePlugins()
{
	ClearPlugins();
    FindFiles(pPlugins);

    TEmbPlugin *pEmbPlugin;
    TMenuItem *pItem;
    TMenuItem *pGroupItem;
    AnsiString strGroupName;
    bool bGroupFound;
    Plugin1->Clear();
    for(int i=0;i<pPlugins->Count;i++)
    {
    	pItem = new TMenuItem(this);

        pEmbPlugin = new TEmbPlugin();
		pEmbPlugin->LoadFromFile(pPlugins->Strings[i]);
        pEmbPlugin->GetIcon(pItem->Bitmap);
		pEmbPlugin->Initialize(vlRedraw,vlDrawLine,vlDrawPolyline,vlDrawPolygon,
                vlDrawCircle,vlDrawArc,vlDrawEllipse,vlDrawText,
                vlAddLine,vlAddCircle,vlAddCircle3P,vlAddArc,
                vlAddArc3P,vlAddEllipse,vlAddArcEx,vlSetTextParam,
                vlSetTextParams,vlAddText,vlPolylineBegin,vlVertex,
                vlVertexR,vlVertexF,vlVertexB,vlAddPolyline,vlAddRect);

        pPlugins->Objects[i] = (TObject *)pEmbPlugin;

        pItem->Caption = pEmbPlugin->GetName()+AnsiString(" - V")+pEmbPlugin->GetVersion();
        pItem->Hint = pEmbPlugin->GetHint();
        pItem->ShortCut = pEmbPlugin->GetShortCut();
//        pEmbPlugin->GetAuthorName();
//        pEmbPlugin->GetDate();
        pItem->OnClick = DoClickPlugin;
        pItem->Tag = i;

        strGroupName = pEmbPlugin->GetGroup();
        bGroupFound = false;
        for(int j=0;j<Plugin1->Count;j++)
        {
			if(Plugin1->Items[j]->Caption == strGroupName)
            {
            	pGroupItem = Plugin1->Items[j];
            	bGroupFound = true;
             	break;
            }
        }
        if(bGroupFound)
        {
	    	pGroupItem->Add(pItem);
        }
        else
        {
	    	pGroupItem = new TMenuItem(this);
            pGroupItem->Caption = strGroupName;
	    	Plugin1->Add(pGroupItem);
	    	pGroupItem->Add(pItem);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClearLayers()
{
    ListView->Items->Clear();
    ImageList->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::UpdateLayers()
{
    // Update Layers Viewer
    ClearLayers();
    char Buffer[256];
    spl_SInt LayersCount;
    spl_SInt LayerColor;
    AnsiString LayerName;
    LayersCount=vlLayerCount();
    for(spl_SInt i=0;i<LayersCount;i++)
    {
        LayerColor=(TColor)vlPropGetInt(VD_LAYER_COLOR,i);
        vlPropGet(VD_LAYER_NAME,i,Buffer);
        LayerName=Buffer;
        AddLayer(LayerName,LayerColor);
    }

    // Update Caption
    vlPropGet(VD_DWG_PATHNAME,-1,Buffer);
    FormDisplay->m_strFileName=Buffer;
    if(FormDisplay->m_strFileName=="")
    {
        FormDisplay->m_strFileName="Untitled";
    }
    FormMain->Caption=spl_EmbEditorCaption+"["+FormDisplay->m_strFileName+"]";

    // Show All
//    vlZoom(VL_ZOOM_ALL);
//    vlUpdate();
//    vlExecute(VC_ZOOM_ALL);
//    vlUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AddLayer(AnsiString Name,spl_UInt Color)
{
    // Add Image Icon To ImageList
    pBMP->Canvas->Brush->Color=(TColor)Color;
    pBMP->Canvas->FillRect(Rect(0,0,ImageList->Width,ImageList->Height));
    ImageList->Add(pBMP,NULL);

    // Add Layer Item To the ListView
    TListItem *ListItem;
    ListItem=ListView->Items->Add();
    ListItem->Caption=Name;
    ListItem->ImageIndex=ListItem->Index;

    SetCurrLayer(ListItem->Index);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SetCurrLayer(spl_UInt LayerIndex)
{
    // Lock Previous Layer
    LockCurrLayer();
    vlLayerActive(LayerIndex);
    // UnLock Current Layer
    UnLockCurrLayer();

    PanelCurrLayer->Color=(TColor)vlPropGetInt(VD_LAYER_COLOR,-1);
    CheckBoxVisible->Checked=vlPropGetInt(VD_LAYER_VISIBLE,-1);
    vlExecute(VC_RESET);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LockCurrLayer()
{
    // Lock Previous Layer
//    vlPropPutInt(VD_LAYER_LOCK,-1,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::UnLockCurrLayer()
{
    // UnLock Current Layer
//    vlPropPutInt(VD_LAYER_LOCK,-1,false);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ANewExecute(TObject *Sender)
{
    FormDisplay->m_strFileName="Untitled";
    FormDisplay->FileNew();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AOpenExecute(TObject *Sender)
{
    if(FormEmbOpenDialog->ShowModal() == mrOk)
    {
        FormDisplay->m_strFileName=FormEmbOpenDialog->FileName;
        FormDisplay->FileOpen(FormEmbOpenDialog->CheckBoxShowJumps->Checked);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ASaveExecute(TObject *Sender)
{
    FormDisplay->FileSave();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ASaveAsExecute(TObject *Sender)
{
    if(SaveDialogEmb->Execute())
    {
        FormDisplay->m_strFileName=SaveDialogEmb->FileName;
        FormDisplay->FileSave();
    } 
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AExitExecute(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    AppPath=IncludeTrailingBackslash(ExtractFilePath(Application->ExeName));

//    Left=0;
//    Top=0;
//    Width=Screen->Width;
//    Height=Screen->Height;

    pBMP=new Graphics::TBitmap();
    pBMP->Width=ImageList->Width;
    pBMP->Height=ImageList->Height;
    pBMP->PixelFormat=pf24bit;
    pBMP->Canvas->Brush->Style=bsSolid;

    OpenDialogEmb->DefaultExt=spl_EmbDefaultExtension;
    OpenDialogEmb->Filter=spl_EmbFullFilter;

    SaveDialogEmb->DefaultExt=spl_EmbDefaultExtension;
    SaveDialogEmb->Filter=spl_EmbFullFilter;

    pPlugins = new TStringList();
	UpdatePlugins();
    nCurrPluginIndex = 0;

//    FormDisplay = NULL;
//    FormTranslation1 = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ACloseExecute(TObject *Sender)
{
    vlExecute(VC_FILE_CLOSE);    
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    if(pBMP)    delete pBMP;pBMP = NULL;
    ClearPlugins();
    if(pPlugins)	delete pPlugins;pPlugins = NULL;
//    if(FormDisplay)	delete FormDisplay;FormDisplay = NULL;
//    if(FormTranslation1)	delete FormTranslation1;FormTranslation1 = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AToolsExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ANavigatorExecute(TObject *Sender)
{
    vlExecute(VC_TOOL_NAVIGATOR);   
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton973Click(TObject *Sender)
{
    vlExecute(VC_ZOOM_ALL);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton974Click(TObject *Sender)
{
    vlExecute(VC_ZOOM_WIN);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton971Click(TObject *Sender)
{
    vlExecute(VC_ZOOM_IN);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton972Click(TObject *Sender)
{
    vlExecute(VC_ZOOM_OUT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9710Click(TObject *Sender)
{
    vlExecute(VC_ZOOM_PAN);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DockUpResize(TObject *Sender)
{
    if(FormDisplay)
    {
        FormDisplay->Left=DockLeft->Left+DockLeft->Width;
        FormDisplay->Top=DockUp->Top+DockUp->Height;
        FormDisplay->Width=ClientWidth-(DockLeft->Left+DockLeft->Width+PanelLayersViewer->Width);
        FormDisplay->Height=ClientHeight-(DockUp->Top+DockUp->Height);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton978Click(TObject *Sender)
{
    vlExecute(VC_EDIT_COPY);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton979Click(TObject *Sender)
{
    vlExecute(VC_EDIT_MOVE);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton977Click(TObject *Sender)
{
    vlExecute(VC_EDIT_ROTATE);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9712Click(TObject *Sender)
{
    vlExecute(VC_EDIT_SCALE);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9714Click(TObject *Sender)
{
    vlExecute(VC_EDIT_MIRROR);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9713Click(TObject *Sender)
{
    vlExecute(VC_EDIT_ERASE);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AViewExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ARefreshExecute(TObject *Sender)
{
    vlExecute(VC_RESET);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEmbTraceExecute(TObject *Sender)
{
    WinExec("EmbTrace.exe",SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEmbSimulatorExecute(TObject *Sender)
{
    WinExec("EmbSimulator.exe",SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEmbBrowserExecute(TObject *Sender)
{
    WinExec("EmbBrowser.exe",SW_SHOW);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    vlExecute(VC_FILE_CLOSEALL);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9711Click(TObject *Sender)
{
    vlExecute(VC_DRAW_POLYLINE);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9724Click(TObject *Sender)
{
    vlExecute(VC_EDIT_CBCOPY);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9725Click(TObject *Sender)
{
    vlExecute(VC_EDIT_CBCUT);    
    UpdateLayers();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9719Click(TObject *Sender)
{
    vlExecute(VC_EDIT_CBPASTE);
    UpdateLayers();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APrintExecute(TObject *Sender)
{
    vlExecute(VC_PRINT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9728Click(TObject *Sender)
{
    vlExecute(VC_EDIT_UNDO);
    UpdateLayers();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9726Click(TObject *Sender)
{
    vlExecute(VC_EDIT_REDO);
    UpdateLayers();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AContentsExecute(TObject *Sender)
{
    Application->HelpFile=AppPath+"EMBEDITOR.HLP";
    Application->HelpCommand(HELP_CONTENTS,0);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AAboutExecute(TObject *Sender)
{
    FormAbout->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
    if(Selected && Item)
    {
        SetCurrLayer(Item->Index);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PanelCurrLayerClick(TObject *Sender)
{
    if(ColorDialog1->Execute())
    {
        vlPropPutInt(VD_LAYER_COLOR,-1,ColorDialog1->Color);
        vlExecute(VC_RESET);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CheckBoxVisibleClick(TObject *Sender)
{
    int LayerIndex=vlLayerIndex(NULL,0);
    if((ListView->Items->Count>0)&&(LayerIndex>=0)&&(LayerIndex<ListView->Items->Count))
    {
        ListView->Items->Item[LayerIndex]->Cut=!CheckBoxVisible->Checked;
        vlPropPutInt(VD_LAYER_VISIBLE,-1,CheckBoxVisible->Checked);
        vlPropPutInt(VD_LAYER_NOPRINT,-1,!CheckBoxVisible->Checked);
        vlExecute(VC_RESET);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListViewEdited(TObject *Sender, TListItem *Item,
      AnsiString &S)
{
    vlPropPut(VD_LAYER_NAME,-1,S.c_str());
    vlExecute(VC_RESET);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AListExecute(TObject *Sender)
{
    vlFileList(Handle);    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton975Click(TObject *Sender)
{
//    vlExecute(spl_CMD_LINE);
//    vlExecute(spl_CMD_POLYLINE);
//    vlExecute(VC_DRAW_LINE);

	AnsiString strText = "3";
    if(InputQuery("Draw Extrude Polyline","Enter Nodes Count:",strText))
    {
    	g_nEdgeCounts = StrToInt(strText);
	    vlExecute(spl_CMD_POLYSATIN);
    }

//	    vlExecute(spl_CMD_POLYSATIN);
//	CommandType = ctPolySatin;
//    spl_Initialize_Commands();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton976Click(TObject *Sender)
{
//    vlExecute(VC_INS_TEXT);
//	vlSetTextParams (VL_TA_LEFBOT, 10.0, 45.0, 1.0, 0.0, 1.0, 1.0);
//	int nObjIndex = vlAddText(0,0,"Ali");
//	int nObjIndex = vlAddText(0,0,"[100]");
//    if(nObjIndex < 0)	return;
//	vlExplode(nObjIndex);
//	vlExecute( VC_INS_SYMBOL );

    vlExecute(spl_CMD_TEXT);
//	spl_DrawString(FormInsertText->RichEdit->Text.Trim());
//    vlRedraw();

    // Show All
//    vlZoom(VL_ZOOM_ALL);
//    vlUpdate();
//    vlExecute(VC_ZOOM_ALL);
//    vlUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ACopyColorExecute(TObject *Sender)
{
	ColorCopied = PanelCurrLayer->Color;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APasteColorExecute(TObject *Sender)
{
	vlPropPutInt(VD_LAYER_COLOR,-1,ColorCopied);
    vlExecute(VC_RESET);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AImportExecute(TObject *Sender)
{
	if(OpenDialogImport->Execute())
    {
    	if(UpperCase(OpenDialogImport->FileName).Pos(".ML") > 0)
        {
	        FormDisplay->FileImport(OpenDialogImport->FileName);
        }
        else
    	if((UpperCase(OpenDialogImport->FileName).Pos(".EMF") > 0) || (UpperCase(OpenDialogImport->FileName).Pos(".WMF") > 0))
        {
        	FormDisplay->ImportEMF(OpenDialogImport->FileName);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9715Click(TObject *Sender)
{
	vlExecute(spl_CMD_POLYSHAPE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9716Click(TObject *Sender)
{
	vlExecute(spl_CMD_EXTRUDE_POLYSHAPE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APluginExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AAddLayerExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormShow(TObject *Sender)
{
/*
	if(FormDisplay)	return;
    FormDisplay = new TFormDisplay(NULL);
	FormDisplay->Parent = FormMain;
    FormDisplay->BorderStyle = bsNone;
    FormDisplay->Align = alClient;
    FormDisplay->Show();
*/
//	if(FormTranslation1)	return;
//    FormTranslation1 = new TFormTranslation(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Activate(TObject *Sender)
{
	#ifdef _PROTECTED_
    pro_SoftIceCheck();
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_Check();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Deactivate(TObject *Sender)
{
	#ifdef _PROTECTED_
	pro_DebuggerCheck();
    pro_Scrambling();
    pro_SoftIceCheck();
    pro_Check();
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEvents1Idle(TObject *Sender,
      bool &Done)
{
	#ifdef _PROTECTED_
	pro_DebuggerCheck();
    pro_SoftIceCheck();
    pro_Scrambling();
    pro_Check();
    #endif

    Done = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolbarButton9717Click(TObject *Sender)
{
	bool First;
	int iEnt;
    int EntityType;
    spl_UInt PointsCount;
    spl_Region Region;
    spl_Contour Contour;
    double Param;
    spl_Point P;
	First = true;
	while(true)
    {
  		if(First==true)
        {
    		iEnt = vlGetEntity(VL_EI_FIRST,VL_SELECTION,0);
    		First = false;
  		}
        else
    		iEnt = vlGetEntity(VL_EI_NEXT,0,0);
  		if(iEnt < 0)	break;// exit from cycle
        EntityType=vlPropGetInt(VD_ENT_TYPE,iEnt);
        switch(EntityType)
        {
            case VL_ENT_POLYLINE:// Polyline
            {
                PointsCount=vlPropGetInt(VD_POLY_N_VER,iEnt);
                for(spl_UInt PointIndex=0;PointIndex<PointsCount;PointIndex++)
                {
                    vlPolyVerGet(iEnt,PointIndex,&P.x,&P.y,&Param);
                    Contour.Points.push_back(P);
                }
                Region.Contours.push_back(Contour);
                break;
            }
        }
	}
    spl_GlobalStitchPath GlobalStitchPath;
    spl_EmbroidRegion(Region,GlobalStitchPath);
	FormDisplay->DrawGlobalStitchPath(GlobalStitchPath,false);    

    // Show All
    vlZoom(VL_ZOOM_ALL);
    vlUpdate();
    vlExecute(VC_ZOOM_ALL);
    vlUpdate();
}
//---------------------------------------------------------------------------

