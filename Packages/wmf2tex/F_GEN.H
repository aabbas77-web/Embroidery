//---------------------------------------------------------------------------
#ifndef f_genH
#define f_genH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "wmfeps_utils_RealMeta.h"
#include "wmfeps_utils_EpsGen.h"
#include "tex.h"
//---------------------------------------------------------------------------


class TOldProc : public TDataModule
{
__published:	// IDE-managed Components
        TEpsGenerator *EpsGenerator;
        void __fastcall EnumStripLatexEmrSelectObject(
          TEnumMetafile *Sender, const EMRSELECTOBJECT *rec,
          TEmrAction &Action);
        void __fastcall EnumStripLatexEmrExtTextOutW(TEnumMetafile *Sender,
          const EMREXTTEXTOUTA *rec, TEmrAction &Action);
        void __fastcall EnumStripLatexEmrHeader(TEnumMetafile *Sender,
          const ENHMETAHEADER *rec, TEmrAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TOldProc(TComponent* Owner);
        __fastcall ~TOldProc();
        bool __fastcall SaveToWmf(TWinControl *Parent,TMetafile *mf,AnsiString fn);
        bool __fastcall SaveToEmf(TWinControl *Parent,TMetafile *mf,AnsiString fn);
        bool __fastcall SaveToEps(TWinControl *Parent,TMetafile *mf,AnsiString fn);
        bool __fastcall SaveToTexWmf(TWinControl *Parent,TMetafile *mf,AnsiString tfn,AnsiString gfn);
        bool __fastcall SaveToTexEps(TWinControl *Parent,TMetafile *mf,AnsiString tfn,AnsiString gfn);
        bool __fastcall SaveToTexEpic(TWinControl *Parent,TMetafile *mf,AnsiString fn);
        bool __fastcall CopyFromClipboard(TMetafile *mf);
        bool __fastcall SaveType(TWinControl *Parent,TMetafile *mf,AnsiString fn,int index);
        //
        AnsiString __fastcall strTexPoint(const TEXPOINT &pt);
        AnsiString __fastcall strFloat(const double d);
        //
        bool __fastcall StripLatexText(TMetafile *src,TMetafile *dst);
        TStringList *SLStrings;
        bool SLLatexIsSelectedFont;
        int SLMode; // 0=nromal, 1=ready-command, 2=read-firstparam, 3=ready-secondparam
        AnsiString SLCurrentString; bool SLHaveStartedString;
        TEXPOINT SLCurrentPoint, SLHashPoint;
        int SLHoriz, SLVert; // 0=l, 1=c, 2=r,  3=t, 4=m, 5=b;
        TEXPOINT SLScaleViewportToTex(const POINT &src);
        SIZE SLViewportExt; POINT SLViewportOrg; TEXSIZE SLTexExt;
        void __fastcall SLSetPoint(char ch,const TEXRECT &xrc);
        void __fastcall SLCharacter(char c,const TEXRECT &xrc);
        void __fastcall SLEmitText();
        //

};
//---------------------------------------------------------------------------
extern PACKAGE TOldProc *OldProc;
//---------------------------------------------------------------------------
#endif
