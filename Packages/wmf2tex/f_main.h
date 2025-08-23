//---------------------------------------------------------------------------
#ifndef f_mainH
#define f_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "wmfeps_utils_RealMeta.h"
#include "wmfeps_utils_EpsGen.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl;
        TTabSheet *tIntroduction;
        TTabSheet *tClipboard;
    TTabSheet *tFiles;
        TTabSheet *tAbout;
        TPanel *tcpCurrent;
        TButton *tcpSave;
        TTabSheet *tOutput;
        TRadioButton *torTexWmf;
        TRadioButton *torTexEps;
        TRadioButton *torTexEpic;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TGroupBox *GroupBox1;
        TRadioButton *tcrWmf;
        TRadioButton *tcrTexEpic;
        TRadioButton *tcrTexEps;
        TGroupBox *GroupBox2;
        TCheckBox *tccSaveOnClipboardChange;
        TRadioButton *tcrPrompt;
        TRadioButton *tcrSilent;
        TLabel *tclDirectory;
        TRadioButton *tcrTexWmf;
        TEdit *tceDirectory;
        TButton *tcbBrowse;
        TLabel *tclFiles;
        TEdit *tceFileName;
        TEdit *tceNumber;
        TEdit *tceSuffix;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *tfeInFile;
    TButton *tfbInBrowse;
        TEdit *tfeOutFile;
    TButton *tfbOutBrowse;
    TButton *tfbConvert;
        TPanel *Panel1;
        TCheckBox *tfcOutElsewhere;
        TGroupBox *GroupBox3;
    TRadioButton *tfrTexEpic;
    TRadioButton *tfrTexEps;
    TRadioButton *tfrTexWmf;
        TTabSheet *tEPS;
        TRadioButton *tcrEmf;
        TRadioButton *tcrEps;
        TRadioButton *torEps;
        TLabel *Label2;
    TRadioButton *tfrEps;
        TLabel *Label6;
        TEdit *Edit7;
        TEdit *Edit9;
        TLabel *Label11;
        TEdit *Edit10;
        TLabel *Label12;
        TLabel *Label13;
        TEdit *Edit11;
        TEdit *Edit12;
        TListBox *tePrinters;
        TButton *Button5;
    TPaintBox *tcpPaintRect;
        TLabel *tcpSize;
        TSaveDialog *ClipboardSaveDialog;
        TOpenDialog *FileOpenDialog;
        TSaveDialog *SaveCurrentClipboard;
        TTabSheet *tTEX;
        TLabel *Label7;
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button1;
        TLabel *Label15;
        TLabel *Label16;
        TButton *ttbWmf;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label8;
        TLabel *Label14;
        TLabel *Label19;
        TButton *ttbEps;
        TEdit *Edit3;
        TLabel *Label20;
        TLabel *Label21;
        TButton *Button6;
        TButton *Button7;
        TMemo *tteWmf;
        TMemo *tteEps;
        TMemo *tteDefWmf;
        TMemo *tteDefEps;
    TPaintBox *tcpPaintBox;
        TRealMetafile *ClipMetafile;
    TRealMetafile *FileMetafile;
    TEpsGenerator *EpsPrinterLister;
    TPaintBox *tfpPaintBox;
    TLabel *tfpSize;
    TOpenDialog *FileInDialog;
        TButton *bEngine;
        void __fastcall FormShow(TObject *Sender);
        
        void __fastcall tcpPaintRectPaint(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall tePrintersClick(TObject *Sender);
        void __fastcall torEpsClick(TObject *Sender);
        void __fastcall torTexWmfClick(TObject *Sender);
        void __fastcall torTexEpsClick(TObject *Sender);
        void __fastcall torTexEpicClick(TObject *Sender);
        void __fastcall tcrWmfClick(TObject *Sender);
        void __fastcall tcrEmfClick(TObject *Sender);
        void __fastcall tccSaveOnClipboardChangeClick(TObject *Sender);
        void __fastcall tcbBrowseClick(TObject *Sender);
        void __fastcall tcpSaveClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        
        void __fastcall ttbWmfClick(TObject *Sender);
        void __fastcall ttbEpsClick(TObject *Sender);
        void __fastcall tcpPaintBoxPaint(TObject *Sender);

    void __fastcall tfbInBrowseClick(TObject *Sender);
    void __fastcall tfcOutElsewhereClick(TObject *Sender);
    
    void __fastcall tfpPaintBoxPaint(TObject *Sender);
    void __fastcall tfbConvertClick(TObject *Sender);
        
        void __fastcall bEngineClick(TObject *Sender);
    
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        virtual __fastcall ~TMainForm();
        HWND hThisClipboardViewer;
        HWND hNextClipboardViewer; bool bHaveInstalledClipboardViewer;
        void __fastcall ClipboardViewerProc(TMessage &Msg);
        void __fastcall ClipboardChanged(bool really);
        void __fastcall EnsureClipboardViewValid(); bool bClipboardViewValid;
        void __fastcall LoadRegistry(); void __fastcall SaveRegistry();
        void __fastcall Initialize(); bool bInitialized;
        int PrinterIndex;
        void __fastcall SetOutputFormat(AnsiString s);
        int __fastcall GetClipboardOutputFormat();
        void __fastcall EnableSaveOnClipboardChange();
        void __fastcall GetClipboard();
        void __fastcall SaveType(TRealMetafile *mf,AnsiString fn,int index);
        //
        AnsiString tfCurrentPreview;
        void __fastcall tfEnableElsewhere();
        void __fastcall tfUpdatePreview(AnsiString newfn);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
