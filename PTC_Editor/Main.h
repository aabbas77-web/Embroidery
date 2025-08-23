//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "TB97.hpp"
//---------------------------------------------------------------------------
#include "spl_EmbFile.h"
#include "EmbPlugin.h"
#include <Buttons.hpp>
#include "FormTranslation.h"
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TActionList *ActionList1;
    TMainMenu *MainMenu1;
	TImageList *ImageList;
    TAction *AFile;
    TAction *AOpen;
    TAction *ASave;
    TAction *ASaveAs;
    TAction *AExit;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *N1;
    TMenuItem *Save1;
    TMenuItem *Saveas1;
    TMenuItem *N2;
    TMenuItem *Exit1;
    TAction *ANew;
    TMenuItem *New1;
    TAction *AClose;
    TMenuItem *Close1;
    TMenuItem *N3;
    TOpenDialog *OpenDialogEmb;
    TAction *ATools;
    TAction *ANavigator;
    TMenuItem *Tools1;
    TMenuItem *Navigator1;
    TSaveDialog *SaveDialogEmb;
    TDock97 *DockUp;
    TToolbar97 *Toolbar1;
    TToolbarButton97 *ToolbarButton971;
    TToolbarButton97 *ToolbarButton972;
    TToolbarButton97 *ToolbarButton973;
    TToolbarButton97 *ToolbarButton974;
    TDock97 *DockLeft;
    TToolbar97 *Toolbar971;
    TToolbar97 *Toolbar973;
    TToolbarButton97 *ToolbarButton977;
    TToolbarButton97 *ToolbarButton978;
    TToolbarButton97 *ToolbarButton979;
    TToolbarButton97 *ToolbarButton9710;
    TToolbarButton97 *ToolbarButton9712;
    TToolbarButton97 *ToolbarButton9713;
    TToolbarButton97 *ToolbarButton9714;
    TAction *AView;
    TAction *ARefresh;
    TMenuItem *View1;
    TMenuItem *Refresh1;
    TAction *AEmbTrace;
    TAction *AEmbSimulator;
    TAction *AEmbBrowser;
    TMenuItem *N4;
    TMenuItem *EmbroideryTrace1;
    TMenuItem *EmbroiderySimulator1;
    TMenuItem *EmbroideryBrowser1;
    TToolbarButton97 *ToolbarButton9711;
    TToolbar97 *Toolbar972;
    TToolbarButton97 *ToolbarButton9719;
    TToolbarButton97 *ToolbarButton9724;
    TToolbarButton97 *ToolbarButton9725;
    TToolbar97 *Toolbar974;
    TToolbarButton97 *ToolbarButton9727;
    TToolbarButton97 *ToolbarButton9730;
    TToolbarButton97 *ToolbarButton9731;
    TToolbarButton97 *ToolbarButton9732;
    TAction *APrint;
    TMenuItem *Print1;
    TMenuItem *N5;
    TToolbar97 *Toolbar975;
    TToolbarButton97 *ToolbarButton9726;
    TToolbarButton97 *ToolbarButton9728;
    TAction *AHelp;
    TAction *AContents;
    TAction *AAbout;
    TMenuItem *Help1;
    TMenuItem *Contents1;
    TMenuItem *N6;
    TMenuItem *About1;
    TPanel *PanelLayersViewer;
    TPanel *Panel2;
    TPanel *PanelCurrLayer;
    TCheckBox *CheckBoxVisible;
    TListView *ListView;
    TColorDialog *ColorDialog1;
    TAction *AList;
    TMenuItem *List1;
    TMenuItem *N7;
    TToolbarButton97 *ToolbarButton975;
	TToolbarButton97 *ToolbarButton976;
	TPopupMenu *PopupMenuColors;
	TAction *ACopyColor;
	TAction *APasteColor;
	TMenuItem *CopyColor1;
	TMenuItem *PasteColor1;
	TAction *AImport;
	TMenuItem *Import1;
	TOpenDialog *OpenDialogImport;
	TToolbarButton97 *ToolbarButton9715;
	TToolbarButton97 *ToolbarButton9716;
	TOpenDialog *OpenDialogPlugin;
	TAction *APlugin;
	TMenuItem *Plugin1;
	TPopupMenu *PopupMenuLayers;
	TAction *AAddLayer;
	TMenuItem *AddLayer1;
	TApplicationEvents *ApplicationEvents1;
	TFormTranslation *FormTranslation1;
	TToolbarButton97 *ToolbarButton9717;
    void __fastcall AFileExecute(TObject *Sender);
    void __fastcall AOpenExecute(TObject *Sender);
    void __fastcall ASaveExecute(TObject *Sender);
    void __fastcall ASaveAsExecute(TObject *Sender);
    void __fastcall AExitExecute(TObject *Sender);
    void __fastcall ANewExecute(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ACloseExecute(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall AToolsExecute(TObject *Sender);
    void __fastcall ANavigatorExecute(TObject *Sender);
    void __fastcall ToolbarButton973Click(TObject *Sender);
    void __fastcall ToolbarButton974Click(TObject *Sender);
    void __fastcall ToolbarButton972Click(TObject *Sender);
    void __fastcall ToolbarButton971Click(TObject *Sender);
    void __fastcall DockUpResize(TObject *Sender);
    void __fastcall ToolbarButton9710Click(TObject *Sender);
    void __fastcall ToolbarButton978Click(TObject *Sender);
    void __fastcall ToolbarButton979Click(TObject *Sender);
    void __fastcall ToolbarButton977Click(TObject *Sender);
    void __fastcall ToolbarButton9712Click(TObject *Sender);
    void __fastcall ToolbarButton9714Click(TObject *Sender);
    void __fastcall ToolbarButton9713Click(TObject *Sender);
    void __fastcall AViewExecute(TObject *Sender);
    void __fastcall ARefreshExecute(TObject *Sender);
    void __fastcall AEmbTraceExecute(TObject *Sender);
    void __fastcall AEmbSimulatorExecute(TObject *Sender);
    void __fastcall AEmbBrowserExecute(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ToolbarButton9711Click(TObject *Sender);
    void __fastcall ToolbarButton9724Click(TObject *Sender);
    void __fastcall ToolbarButton9725Click(TObject *Sender);
    void __fastcall ToolbarButton9719Click(TObject *Sender);
    void __fastcall APrintExecute(TObject *Sender);
    void __fastcall ToolbarButton9728Click(TObject *Sender);
    void __fastcall ToolbarButton9726Click(TObject *Sender);
    void __fastcall AHelpExecute(TObject *Sender);
    void __fastcall AContentsExecute(TObject *Sender);
    void __fastcall AAboutExecute(TObject *Sender);
    void __fastcall ListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall PanelCurrLayerClick(TObject *Sender);
    void __fastcall CheckBoxVisibleClick(TObject *Sender);
    void __fastcall ListViewEdited(TObject *Sender, TListItem *Item,
          AnsiString &S);
    void __fastcall AListExecute(TObject *Sender);
    void __fastcall ToolbarButton975Click(TObject *Sender);
	void __fastcall ToolbarButton976Click(TObject *Sender);
	void __fastcall ACopyColorExecute(TObject *Sender);
	void __fastcall APasteColorExecute(TObject *Sender);
	void __fastcall AImportExecute(TObject *Sender);
	void __fastcall ToolbarButton9715Click(TObject *Sender);
	void __fastcall ToolbarButton9716Click(TObject *Sender);
	void __fastcall APluginExecute(TObject *Sender);
	void __fastcall AAddLayerExecute(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ApplicationEvents1Activate(TObject *Sender);
	void __fastcall ApplicationEvents1Deactivate(TObject *Sender);
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
	void __fastcall ToolbarButton9717Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
    void __fastcall ClearLayers();
    void __fastcall UpdateLayers();
    void __fastcall AddLayer(AnsiString Name,spl_UInt Color);
    void __fastcall SetCurrLayer(spl_UInt LayerIndex);
    void __fastcall LockCurrLayer();
    void __fastcall UnLockCurrLayer();
	void __fastcall FindFiles(TStringList *pFiles);
	void __fastcall UpdatePlugins();
	void __fastcall DoClickPlugin(TObject *Sender);
	void __fastcall ClearPlugins();

    Graphics::TBitmap *pBMP;
    AnsiString AppPath;
    TColor ColorCopied;
    TStringList *pPlugins;
    int nCurrPluginIndex;
    TMenuItem *pItem;
//    TFormTranslation *FormTranslation1;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
