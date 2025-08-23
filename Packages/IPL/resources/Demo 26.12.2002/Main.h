//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include "ipl98_cplusplus.h"
#include "Image.h"
#include "morphology.h"
#include "segmentate.h"
#include "EmbFile.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *Save1;
    TMenuItem *N1;
    TMenuItem *Exit1;
    TOpenPictureDialog *OpenPictureDialog1;
    TSavePictureDialog *SavePictureDialog1;
    TScrollBox *ScrollBox1;
    TImage *Image1;
    TMenuItem *Imaging1;
    TMenuItem *Negative1;
    TMenuItem *Flip1;
    TMenuItem *Horizontal1;
    TMenuItem *Vertical1;
    TMenuItem *Rotate1;
    TMenuItem *ScaleIntensity1;
    TMenuItem *ApplyBias1;
    TMenuItem *Border1;
    TMenuItem *Morphology1;
    TMenuItem *Thining1;
    TMenuItem *Erosion1;
    TMenuItem *Dilation1;
    TMenuItem *Skeleton1;
    TMenuItem *SkeletonZhou1;
    TMenuItem *SkeletonZhouwithoutEdges1;
    TMenuItem *Segmentation1;
    TMenuItem *LowContours1;
    TMenuItem *HighContours1;
    TTimer *Timer1;
    TMenuItem *N2;
    TMenuItem *Start1;
    TMenuItem *DeriveBlobs1;
    TMenuItem *Pol1;
    TMenuItem *Emb1;
    TMenuItem *Save2;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TMenuItem *N4;
    TMenuItem *MyNegative1;
    TMenuItem *Flush1;
    TOpenDialog *OpenDialog2;
    TSaveDialog *SaveDialog2;
    TMenuItem *Save3;
    TMenuItem *N3;
    TMenuItem *FillPattern1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Open1Click(TObject *Sender);
    void __fastcall Save1Click(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall Negative1Click(TObject *Sender);
    void __fastcall Horizontal1Click(TObject *Sender);
    void __fastcall Vertical1Click(TObject *Sender);
    void __fastcall Rotate1Click(TObject *Sender);
    void __fastcall ScaleIntensity1Click(TObject *Sender);
    void __fastcall ApplyBias1Click(TObject *Sender);
    void __fastcall Border1Click(TObject *Sender);
    void __fastcall Thining1Click(TObject *Sender);
    void __fastcall Erosion1Click(TObject *Sender);
    void __fastcall Dilation1Click(TObject *Sender);
    void __fastcall Skeleton1Click(TObject *Sender);
    void __fastcall SkeletonZhou1Click(TObject *Sender);
    void __fastcall SkeletonZhouwithoutEdges1Click(TObject *Sender);
    void __fastcall LowContours1Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall Start1Click(TObject *Sender);
    void __fastcall DeriveBlobs1Click(TObject *Sender);
    void __fastcall Save2Click(TObject *Sender);
    void __fastcall Pol1Click(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall MyNegative1Click(TObject *Sender);
    void __fastcall Flush1Click(TObject *Sender);
    void __fastcall Save3Click(TObject *Sender);
    void __fastcall FillPattern1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);

    ipl::CImage Image;
    ipl::TImage *pImage;
    ipl::CMorphology Morphology;
    ipl::CSegmentate Segmentate;
    ipl::CPixelGroup PixelGroup,*pPixelGroup;
    ipl::T2DInt P;
    ipl::CPixelGroups PixelGroups;

    AnsiString FileName;
    int W,H;
    int ImageSize,RowSize;
    int Bits;
    Byte *pData;
    int PixlesCount;
    int CurrIndex;
    int PixlesGroupCount;

    DWORD StartTime,Delay;

    TRPoint *pPoint;
    TPolygon *pPolygon;
    TPolygons *pPolygons;
    TPolyPolygons *pPolyPolygons;
    TEmbFile *pEmbFile;

    Graphics::TBitmap *pBitmap;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
