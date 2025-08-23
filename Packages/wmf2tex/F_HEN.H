//---------------------------------------------------------------------------
#ifndef f_henH
#define f_henH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "wmfeps_utils_RealMeta.h"
#include "wmfeps_utils_EpsGen.h"
//---------------------------------------------------------------------------
#include "tex.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>

typedef struct tagMacroData
{ AnsiString fn;
  TStrings *txt;
  double wf,hf;
  double xi,yi,wi,hi;
} TMacroData;


class TProc : public TForm
{
__published:	// IDE-managed Components
        TEpsGenerator *EpsGenerator;
        TPanel *Panel1;
        TPaintBox *PaintBox;
        TRealMetafile *RealMetafile;
        TToolBar *ToolBar1;
        TToolBar *ToolBar2;
        TToolBar *ToolBar3;
        TComboBox *OpenFileName;
        TButton *bOpen;
        TButton *bPaste;
        TToolButton *ToolButton1;
        TComboBox *SaveFileName;
        TButton *bSave;
        TToolButton *ToolButton2;
        TButton *bCopy;
        TButton *bToText;
        TToolButton *ToolButton3;
        TButton *bStripLatex;
        TToolButton *ToolButton5;
        TStatusBar *StatusBar;
        TButton *bClear;
        TToolButton *ToolButton7;
        TToolButton *ToolButton4;
        TMemo *TexEpsSource;
        TMemo *TexWmfSource;
        TRealMetafile *EnumToText;
        TRealMetafile *EnumGetLatex;
        TRealMetafile *EnumRemoveLatex;
        TButton *bSaveEmf;
        TToolButton *ToolButton6;
        TToolBar *ToolBar4;
        TComboBox *SaveAllName;
        TButton *bTexWmf;
        TToolBar *ToolBar5;
        TComboBox *SaveEpsName;
        TButton *bSaveEps;
        TLabel *SaveEpsPrinterName;
        void __fastcall bOpenClick(TObject *Sender);
        void __fastcall bPasteClick(TObject *Sender);
        void __fastcall bStripLatexClick(TObject *Sender);
        void __fastcall bToTextClick(TObject *Sender);
        void __fastcall bCopyClick(TObject *Sender);
        void __fastcall bSaveClick(TObject *Sender);
        void __fastcall PaintBoxPaint(TObject *Sender);
        void __fastcall bClearClick(TObject *Sender);
        void __fastcall EnumToTextEmr(TRealMetafile *Sender,
          const ENHMETARECORD *rec, TEnumAction &Action);
        void __fastcall EnumToTextWmr(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
        void __fastcall EnumGetLatexEmrExtTextOutW(TRealMetafile *Sender,
          const EMREXTTEXTOUTA *rec, TEnumAction &Action);
        
        void __fastcall EnumRemoveLatexEmrExtTextOutA(
          TRealMetafile *Sender, const EMREXTTEXTOUTA *rec,
          TEnumAction &Action);
        void __fastcall EnumRemoveLatexEmrExtTextOutW(
          TRealMetafile *Sender, const EMREXTTEXTOUTA *rec,
          TEnumAction &Action);
        void __fastcall EnumRemoveLatexWmrTextOut(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
        void __fastcall bSaveEmfClick(TObject *Sender);
        void __fastcall bTexWmfClick(TObject *Sender);
        void __fastcall OpenFileNameClick(TObject *Sender);
        void __fastcall bSaveEpsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TProc(TComponent* Owner);
        __fastcall ~TProc();
        void __fastcall Update();
        //
        bool __fastcall LoadFromWmf(TWinControl *Parent,TRealMetafile *mf,AnsiString fn);
        bool __fastcall LoadFromClipboard(TWinControl *Parent,TRealMetafile *mf);
        bool __fastcall SaveToClipboard(TWinControl *Parent,TRealMetafile *mf);
        bool __fastcall SaveToWmf(TWinControl *Parent,TRealMetafile *mf,AnsiString fn);
        bool __fastcall SaveToEmf(TWinControl *Parent,TRealMetafile *mf,AnsiString fn);
        bool __fastcall SaveToEps(TWinControl *Parent,TRealMetafile *mf,AnsiString fn);
        bool __fastcall SaveToTexWmf(TWinControl *Parent,TRealMetafile *mf,AnsiString tfn,AnsiString gfn);
        bool __fastcall SaveToTexEps(TWinControl *Parent,TRealMetafile *mf,AnsiString tfn,AnsiString gfn);
        bool __fastcall SaveToTexEpic(TWinControl *Parent,TRealMetafile *mf,AnsiString fn);
        bool __fastcall SaveType(TWinControl *Parent,TRealMetafile *mf,AnsiString fn,int index);
        bool __fastcall SaveMacroToTex(TWinControl *Parent,AnsiString tfn,TStrings *macro,TMacroData &md);
        //
        AnsiString __fastcall strTexPoint(const TEXPOINT &pt);
        AnsiString __fastcall strFloat(const double d);
        //
        bool __fastcall StripLatexText(TRealMetafile *src,TRealMetafile *dst);
        TStringList *SLStrings;
        bool SLLatexIsSelectedFont;
        int SLMode; // 0=nromal, 1=ready-command, 2=read-firstparam, 3=ready-secondparam
        AnsiString SLCurrentString; bool SLHaveStartedString;
        TEXPOINT SLCurrentPoint, SLHashPoint;
        int SLHoriz, SLVert; // 0=l, 1=c, 2=r,  3=t, 4=m, 5=b;
        TEXPOINT SLScaleViewportToTex(const POINT &src);
        SIZE SLViewportExt; POINT SLViewportOrg; TEXSIZE SLTexExt;
        TEXSIZE SLFileDimensions; TEXPOINT SLImageOffset; TEXSIZE SLImageSize; // these are hf+wf and xi+yi+hi+wi respectively: see the macro stuff for an explanation
        void __fastcall SLSetPoint(char ch,const TEXRECT &xrc);
        void __fastcall SLCharacter(char c,const TEXRECT &xrc);
        void __fastcall SLEmitText();
        //
        bool __fastcall MetafileToText(TRealMetafile *src,TStrings *dst);
        TStrings *MTTStrings;
        //
        TStrings* __fastcall ShowText(TStrings *s);
        void __fastcall TextFormClose(TObject *Sender, TCloseAction &Action);
};
//---------------------------------------------------------------------------
extern PACKAGE TProc *Proc;
//---------------------------------------------------------------------------
#endif
 