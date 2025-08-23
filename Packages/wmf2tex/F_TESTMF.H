//---------------------------------------------------------------------------
#ifndef f_testmfH
#define f_testmfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include "wmfeps_utils_RealMeta.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TButton *bPaste;
        TPaintBox *PaintBox;
        TComboBox *FileName;
        TButton *bOpen;
        TStatusBar *StatusBar;
        TToolBar *ToolBar2;
        TComboBox *SaveFileName;
        TButton *bSaveEmf;
        TToolButton *ToolButton2;
        TButton *bCopy;
        TToolBar *ToolBar3;
        TButton *bEnum;
        TToolButton *ToolButton3;
        TButton *bStripLatex;
        TButton *bSaveWmf;
        TToolButton *ToolButton4;
        TButton *bClear;
        TToolButton *ToolButton5;
        TButton *bEnhanced;
        void __fastcall bOpenClick(TObject *Sender);
        
        void __fastcall PaintBoxPaint(TObject *Sender);
        void __fastcall FileNameClick(TObject *Sender);
        void __fastcall bPasteClick(TObject *Sender);
        void __fastcall bEnumClick(TObject *Sender);
        void __fastcall bSaveEmfClick(TObject *Sender);
        void __fastcall bSaveWmfClick(TObject *Sender);
        void __fastcall bCopyClick(TObject *Sender);
        void __fastcall bClearClick(TObject *Sender);
        void __fastcall bEnhancedClick(TObject *Sender);
        void __fastcall bStripLatexClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        __fastcall ~TForm1();
        TRealMetafile *rm;
        void __fastcall Update();
        void __fastcall EnumWmr(TRealMetafile *Sender,const METARECORD *rec,TEnumAction &Action);
        void __fastcall EnumEmr(TRealMetafile *Sender,const ENHMETARECORD *rec,TEnumAction &Action);
        void __fastcall ShowFormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall OnWmrTextOut(TRealMetafile *Sender,const METARECORD *rec,TEnumAction &Action);
        void __fastcall OnEmrExtTextOutW(TRealMetafile *Sender,const EMREXTTEXTOUTW *rec,TEnumAction &Action);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
