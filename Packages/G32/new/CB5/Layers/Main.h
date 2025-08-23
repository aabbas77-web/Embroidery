//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "G32_Image.hpp"
#include "G32_RangeBars.hpp"
#include "G32_Transforms.hpp"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <Menus.hpp>
#include "G32_Filters.hpp"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TImgView32 *ImgView;
    TPanel *SidePanel;
    TPanel *pnlImage;
    TLabel *Label1;
    TComboBox *ScaleCombo;
    TPanel *Panel2;
    TCheckBox *ImageInterpolate;
    TPanel *pnlBitmapLayer;
    TLabel *Label2;
    TPanel *Panel3;
    TGaugeBar *LayerOpacity;
    TCheckBox *LayerInterpolate;
    TButton *LayerRescale;
    TButton *LayerResetScale;
    TCheckBox *Cropped;
    TPanel *PnlMagn;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TPanel *Panel4;
    TGaugeBar *MagnOpacity;
    TGaugeBar *MagnMagnification;
    TGaugeBar *MagnRotation;
    TCheckBox *MagnInterpolate;
    TMainMenu *MainMenu;
    TMenuItem *mnFile;
    TMenuItem *mnFileNew;
    TMenuItem *mnFileOpen;
    TMenuItem *mnLayers;
    TMenuItem *mnNewBitmapLayer;
    TMenuItem *mnNewBitmapRGBA;
    TMenuItem *mnNewCustomLayer;
    TMenuItem *mnSimpleDrawing;
    TMenuItem *mnMagnifier;
    TMenuItem *Text1;
    TMenuItem *N4;
    TMenuItem *mnFlatten;
    TMenuItem *mnArrange;
    TMenuItem *mnBringFront;
    TMenuItem *mnSendBack;
    TMenuItem *N1;
    TMenuItem *mnLevelUp;
    TMenuItem *mnLevelDown;
    TMenuItem *N2;
    TMenuItem *mnScaled;
    TMenuItem *mnDelete;
    TOpenPictureDialog *OpenPictureDialog1;
    TSaveDialog *SaveDialog1;
    TMenuItem *N3;
    TMenuItem *Exit1;
    TMenuItem *N5;
    TMenuItem *Quantize1;
    TPanel *Panel1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ImgViewMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, TCustomLayer *Layer);
    void __fastcall ImgViewPaintStage(TObject *Sender, TBitmap32 *Buffer,
          DWORD StageNum);
    void __fastcall mnFileNewClick(TObject *Sender);
    void __fastcall mnFileOpenClick(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall mnNewBitmapLayerClick(TObject *Sender);
    void __fastcall mnNewBitmapRGBAClick(TObject *Sender);
    void __fastcall mnSimpleDrawingClick(TObject *Sender);
    void __fastcall mnMagnifierClick(TObject *Sender);
    void __fastcall Text1Click(TObject *Sender);
    void __fastcall mnFlattenClick(TObject *Sender);
    void __fastcall mnBringFrontClick(TObject *Sender);
    void __fastcall mnLayersClick(TObject *Sender);
    void __fastcall mnArrangeClick(TObject *Sender);
    void __fastcall mnScaledClick(TObject *Sender);
    void __fastcall mnDeleteClick(TObject *Sender);
    void __fastcall CroppedClick(TObject *Sender);
    void __fastcall ScaleComboChange(TObject *Sender);
    void __fastcall ImageInterpolateClick(TObject *Sender);
    void __fastcall LayerOpacityChange(TObject *Sender);
    void __fastcall LayerRescaleClick(TObject *Sender);
    void __fastcall LayerResetScaleClick(TObject *Sender);
    void __fastcall MagnOpacityChange(TObject *Sender);
    void __fastcall Quantize1Click(TObject *Sender);
private:	// User declarations
    TPositionedLayer *FSelection;
    void __fastcall SetSelection(TPositionedLayer *Value);

    void __fastcall WMEraseBkgnd(TMessage &Message);
    BEGIN_MESSAGE_MAP
     MESSAGE_HANDLER(WM_ERASEBKGND,TMessage,WMEraseBkgnd)
    END_MESSAGE_MAP(TForm)
protected:
    TRubberbandLayer *RBLayer;
    void __fastcall CreatePositionedLayer(TPositionedLayer *Result);
    void __fastcall LayerMouseDown(TObject *Sender,TMouseButton Buttons,TShiftState Shift,int X,int Y);
    void __fastcall RBResizing(TObject *Sender, const TFloaTRect &OldLocation,TFloaTRect &NewLocation,TDragState32 DragState,TShiftState Shift);
    void __fastcall PaintMagnifierHandler(TObject *Sender,TBitmap32 *Buffer);
    void __fastcall PaintSimpleDrawingHandler(TObject *Sender,TBitmap32 *Buffer);
    void __fastcall PaintTextHandler(TObject *Sender,TBitmap32 *Buffer);
public:		// User declarations
    __fastcall TFormMain(TComponent* Owner);
    AnsiString Text;

    void __fastcall CreateNewImage(int AWidth,int AHeight,TColor32 FillColor);
    void __fastcall OpenImage(const AnsiString FileName);
    __property TPositionedLayer *Selection={read=FSelection,write=SetSelection};
    void __fastcall CreateBitmapLayer(TBitmap32 *pBMP);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
