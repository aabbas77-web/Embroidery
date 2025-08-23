//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <AppEvnts.hpp>
#include "spl_EmbLib.h"
#include <ActnList.hpp>
#include "ShellControls.hpp"
#include "ShellLink.hpp"
#include "ShellBrowser.hpp"
//---------------------------------------------------------------------------
const double Margin=10;
//---------------------------------------------------------------------------
#define  _Round(x) ((x-int(x)>=0.5)?int(x)+1:int(x))
//---------------------------------------------------------------------------
class TThumbThread : public TThread
{
private:
protected:
    void __fastcall Execute();
    void __fastcall OpenFile();
    int Index;
    int IconIndex;
    int x,y;
public:
    __fastcall TThumbThread(bool CreateSuspended);
    __fastcall ~TThumbThread();
    Graphics::TBitmap *pBMP;
    TRect Frame;
    spl_EmbHeader EmbHeader;
    AnsiString FileName;
    spl_StitchPath StitchPath;
    int TotalCount;
    int Step;
    int ACol,ARow;
};
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TToolBar *ToolBar1;
    TImageList *ImageList2;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TApplicationEvents *ApplicationEvents1;
    TToolBar *ToolBar2;
    TToolButton *ToolButton6;
    TToolButton *ToolButton7;
    TPanel *Panel5;
    TStatusBar *StatusBar1;
    TPanel *Panel6;
    TPanel *Panel3;
    TNotebook *Notebook1;
    TPanel *Panel2;
    TPanel *Panel4;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *View1;
    TMenuItem *LargeIcons1;
    TMenuItem *SmallIcons1;
    TMenuItem *List1;
    TMenuItem *Details1;
    TMenuItem *Thumbnails1;
    TMenuItem *N1;
    TMenuItem *Arrange1;
    TMenuItem *byName1;
    TMenuItem *byType1;
    TMenuItem *by1;
    TMenuItem *byDate1;
    TPopupMenu *PopupMenu1;
    TActionList *ActionList1;
    TAction *AFile;
    TAction *AExit;
    TMenuItem *AExit1;
    TAction *AView;
    TAction *ALargeIcons;
    TAction *ASmallIcons;
    TAction *AList;
    TAction *ADetails;
    TAction *AThumbnails;
    TAction *AArrangeIcons;
    TAction *AbyName;
    TAction *AbyType;
    TAction *AbySize;
    TAction *AbyDate;
    TMenuItem *LargeIcons2;
    TMenuItem *LargeIcons3;
    TMenuItem *SmallIcons2;
    TMenuItem *List2;
    TMenuItem *Details2;
    TMenuItem *Thumbnails2;
    TMenuItem *ArrangeIcons1;
    TMenuItem *byName2;
    TMenuItem *byType2;
    TMenuItem *bySize1;
    TMenuItem *byDate2;
    TAction *AOptions;
    TMenuItem *N2;
    TMenuItem *Options1;
    TAction *AHelp;
    TAction *AAbout;
    TMenuItem *Help1;
    TMenuItem *About1;
    TToolButton *ToolButton8;
    TJamShellList *JamShellList1;
    TJamShellTree *JamShellTree1;
    TJamShellLink *JamShellLink1;
    TSplitter *Splitter1;
    TSplitter *Splitter2;
    TSplitter *Splitter3;
    TProgressBar *ProgressBar1;
    TShellBrowser *ShellBrowser1;
    TJamSystemImageList *JamSystemImageList1;
    TAction *ARefresh;
    TMenuItem *N3;
    TMenuItem *Refresh1;
    TMenuItem *N4;
    TMenuItem *Refresh2;
    TMenuItem *N5;
    TPanel *Panel7;
    TImage *Image1;
    TToolBar *ToolBar3;
    TPanel *Panel8;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TToolBar *ToolBar4;
    TPanel *Panel9;
    TCheckBox *CheckBoxPreview;
    TCheckBox *CheckBoxReal;
    TDrawGrid *DrawGrid1;
    TAction *AContents;
    TMenuItem *Contents1;
    TMenuItem *N6;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ImageLibThumbnails1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ApplicationEvents1Hint(TObject *Sender);
    void __fastcall AFileExecute(TObject *Sender);
    void __fastcall AExitExecute(TObject *Sender);
    void __fastcall AViewExecute(TObject *Sender);
    void __fastcall ALargeIconsExecute(TObject *Sender);
    void __fastcall ASmallIconsExecute(TObject *Sender);
    void __fastcall AListExecute(TObject *Sender);
    void __fastcall ADetailsExecute(TObject *Sender);
    void __fastcall AThumbnailsExecute(TObject *Sender);
    void __fastcall AArrangeIconsExecute(TObject *Sender);
    void __fastcall AbyNameExecute(TObject *Sender);
    void __fastcall AbyTypeExecute(TObject *Sender);
    void __fastcall AbySizeExecute(TObject *Sender);
    void __fastcall AbyDateExecute(TObject *Sender);
    void __fastcall AOptionsExecute(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall AHelpExecute(TObject *Sender);
    void __fastcall AAboutExecute(TObject *Sender);
    void __fastcall JamShellList1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ListView1DblClick(TObject *Sender);
    void __fastcall ListView1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ARefreshExecute(TObject *Sender);
    void __fastcall Panel7Resize(TObject *Sender);
    void __fastcall CheckBoxPreviewClick(TObject *Sender);
    void __fastcall CheckBoxRealClick(TObject *Sender);
    void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall DrawGrid1SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
    void __fastcall DrawGrid1DrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall Splitter2Moved(TObject *Sender);
    void __fastcall ApplicationEvents1ShortCut(TWMKey &Msg, bool &Handled);
    void __fastcall AContentsExecute(TObject *Sender);
	void __fastcall ApplicationEvents1Activate(TObject *Sender);
	void __fastcall ApplicationEvents1Deactivate(TObject *Sender);
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
private:	// User declarations
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
    void __fastcall OnTerminate(TObject *Sender);
    void __fastcall UpdateControls();
    Graphics::TBitmap *pBMP;
    Graphics::TBitmap *pBitmap;
    TThumbThread *pThread;
    spl_EmbHeader EmbHeader;
    spl_StitchPath StitchPath;
    TStringList *pList;

    AnsiString LinkCommand;
    AnsiString OldDirectory;
    TPoint P;
    int Step;
    int CurrCol,CurrRow;
    int Index;
    int Ident,Ident2;
    bool CanSelected;
    bool Selected;
    AnsiString FileName;
    AnsiString FName,Name;

    int ThumbWidth,ThumbHeight;
    int TextHeight,TextWidth,MaxTextWidth;
    int dx;

    bool Start;
    bool ShowNoneEmbroideryFiles;
    bool ItemSelected;
    bool ApplyChanges;
    int IconIndex;
    int x,y;
    bool CanSelect;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
