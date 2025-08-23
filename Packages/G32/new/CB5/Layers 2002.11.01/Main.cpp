//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Main.h"
#include "New.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "G32_Image"
#pragma link "G32_RangeBars"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
 Left=0;
 Top=0;
 Width=Screen->Width;
 Height=Screen->Height;

 // by default, PST_CLEAR_BACKGND is executed at this stage,
 // which, in turn, calls ExecClearBackgnd method of ImgView.
 // Here I substitute PST_CLEAR_BACKGND with PST_CUSTOM, so force ImgView
 // to call the OnPaintStage event instead of performing default action.
 if(ImgView->PaintStages->Items[0]->Stage == PST_CLEAR_BACKGND)
  ImgView->PaintStages->Items[0]->Stage = PST_CUSTOM;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
 FSelection=NULL;
 RBLayer=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::WMEraseBkgnd(TMessage &Msg)
{
 // disable form background cleaning
 Msg.Result = 1;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CreatePositionedLayer(TPositionedLayer *Result)
{
 TPoint P;
 TRect R=ImgView->GetViewporTRect();
 // get coordinates of the center of viewport
 P = ImgView->ControlToBitmap(Point((R.Right + R.Left) / 2, (R.Top + R.Bottom) / 2));

 Result->Location = FloaTRect(P.x - 32, P.y - 32, P.x + 32, P.y + 32);
 Result->Scaled = true;
 Result->MouseEvents = true;
 Result->OnMouseDown = LayerMouseDown;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LayerMouseDown(TObject *Sender,TMouseButton Buttons,TShiftState Shift,int X,int Y)
{
 if(Sender)
  Selection = ((TPositionedLayer *)Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RBResizing(TObject *Sender, const TFloaTRect &OldLocation,TFloaTRect &NewLocation,TDragState32 DragState,TShiftState Shift)
{
 Single w, h, cx, cy;
 Single nw, nh, r;

 if(DragState == dsMove)
  return; // we are interested only in scale operations
 if((!Shift.Contains(ssShift))&&
    (!Shift.Contains(ssAlt))&&
    (!Shift.Contains(ssCtrl))&&
    (!Shift.Contains(ssLeft))&&
    (!Shift.Contains(ssRight))&&
    (!Shift.Contains(ssMiddle))&&
    (!Shift.Contains(ssDouble))
   )
  return; // special processing is not required

 if(Shift.Contains(ssCtrl))
 {
  // make changes symmetrical

  cx = (OldLocation.Left + OldLocation.Right) / 2.0f;
  cy = (OldLocation.Top + OldLocation.Bottom) / 2.0f;
  w = OldLocation.Right - OldLocation.Left;
  h = OldLocation.Bottom - OldLocation.Top;

  nw = w / 2.0f;
  nh = h / 2.0f;
  switch(DragState)
  {
   case dsSizeL:
   {
    nw = cx - NewLocation.Left;
    break;
   } 
   case dsSizeT:
   {
    nh = cy - NewLocation.Top;
    break;
   } 
   case dsSizeR:
   {
    nw = NewLocation.Right - cx;
    break;
   }
   case dsSizeB:
   {
    nh = NewLocation.Bottom - cy;
    break;
   }
   case dsSizeTL:
   {
    nw = cx - NewLocation.Left;
    nh = cy - NewLocation.Top;
    break;
   }
   case dsSizeTR:
   {
    nw = NewLocation.Right - cx;
    nh = cy - NewLocation.Top;
    break;
   }
   case dsSizeBL:
   {
    nw = cx - NewLocation.Left;
    nh = NewLocation.Bottom - cy;
    break;
   }
   case dsSizeBR:
   {
    nw = NewLocation.Right - cx;
    nh = NewLocation.Bottom - cy;
    break;
   }
  }
  if(nw < 2.0f)
   nw = 2.0f;
  if(nh < 2.0f)
   nh = 2.0f;

  NewLocation.Left = cx - nw;
  NewLocation.Right = cx + nw;
  NewLocation.Top = cy - nh;
  NewLocation.Bottom = cy + nh;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CreateNewImage(int AWidth,int AHeight,TColor32 FillColor)
{
 Selection = NULL;
 RBLayer = NULL;
 ImgView->Layers->Clear();
 ImgView->Scale = 1.0f;
 ImgView->Bitmap->SetSize(AWidth, AHeight);
 ImgView->Bitmap->Clear(FillColor);
 pnlImage->Visible = !ImgView->Bitmap->Empty();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenImage(const AnsiString FileName)
{
 try
 {
  Selection = NULL;
  RBLayer = NULL;
  ImgView->Layers->Clear();
  ImgView->Scale = 1.0f;
  ImgView->Bitmap->LoadFromFile(FileName);
 }
 __finally
 {
  pnlImage->Visible = !ImgView->Bitmap->Empty();
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PaintMagnifierHandler(TObject *Sender,TBitmap32 *Buffer)
{
 Single Magnification, Rotation;
 TFloaTRect SrcRect, DsTRect;
 TRect R;
 TAffineTransformation *T;
 TBitmap32 *B;
 Single W2, H2;
 TPositionedLayer *pLayer=((TPositionedLayer *)Sender);

 if(pLayer)
 {
     Magnification = pow(10, (MagnMagnification->Position / 50.0f));
     Rotation = -MagnRotation->Position;

     DsTRect = pLayer->GetAdjustedLocation();
     R = Rect32(DsTRect.Left,DsTRect.Top,DsTRect.Right,DsTRect.Bottom);
     B = new TBitmap32();
     try
     {
      B->SetSize(R.Right - R.Left, R.Bottom - R.Top);
      W2 = (R.Right - R.Left) / 2.0f;
      H2 = (R.Bottom - R.Top) / 2.0f;

      SrcRect = DsTRect;

      SrcRect.Left = SrcRect.Left - H2;
      SrcRect.Right = SrcRect.Right + H2;
      SrcRect.Top = SrcRect.Top - W2;
      SrcRect.Bottom = SrcRect.Bottom + W2;

       T = new TAffineTransformation();
       try
       {
        T->SrcRect = SrcRect;
        T->Translate(-R.Left, -R.Top);

        T->Translate(-W2, -H2);
        T->Scale(Magnification, Magnification);
        T->Rotate(0, 0, Rotation);
        T->Translate(W2, H2);

        if(MagnInterpolate->Checked)
        {
          Buffer->BeginUpdate();
          Buffer->StretchFilter = sfLinear;
          Transform(B, Buffer, T);
          Buffer->StretchFilter = sfNearest;
          Buffer->EndUpdate();
        }
        else
         Transform(B, Buffer, T);

        B->ResetAlpha();
        B->DrawMode = dmBlend;
        B->MasterAlpha = MagnOpacity->Position;
        B->DrawTo(Buffer, R);

        // draw frame
        for(int i=0;i<=4;i++)
        {
         Buffer->RaiseRectTS(R.Left, R.Top, R.Right, R.Bottom, 35 - i * 8);
         InflateRect(R, -1, -1);
        }
       } 
       __finally
       {
        if(T)
         delete T;
       }
     }
     __finally
     {
      if(B)
       delete B;
     }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PaintSimpleDrawingHandler(TObject *Sender,TBitmap32 *Buffer)
{
 Single Cx, Cy;
 Single W2, H2;
 TPositionedLayer *pLayer=((TPositionedLayer *)Sender);
 if(pLayer)
 {
  TFloaTRect R=pLayer->GetAdjustedLocation();

  W2 = (R.Right - R.Left) / 2;
  H2 = (R.Bottom - R.Top) / 2;
  Cx = R.Left + W2;
  Cy = R.Top + H2;
  Buffer->PenColor = clRed32;
  Buffer->MoveToF(Cx,Cy);
  for(int i=0;i<=240;i++)
   Buffer->LineToFS(Cx + W2 * i / 200.0f * cos(i / 8.0f), Cy + H2 * i / 200.0f * sin(i / 8.0f));
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PaintTextHandler(TObject *Sender,TBitmap32 *Buffer)
{
 Single Cx, Cy;
 Single W2, H2;
 Single W, H;
 TSize Size;
 TPositionedLayer *pLayer=((TPositionedLayer *)Sender);
 if(pLayer)
 {
  TFloaTRect R=pLayer->GetAdjustedLocation();

  W=R.Right-R.Left;
  H=R.Bottom-R.Top;
  W2=W/2.0f;
  H2=H/2.0f;
  Cx = R.Left + W2;
  Cy = R.Top + H2;
  Buffer->Font->Name="Traditional Arabic";
  Buffer->Font->Size=int(W);
  Size=Buffer->TextExtent(Text);
//  Buffer->TextOutA(int(Cx-Size.cx/2.0f),int(Cy-Size.cy/2.0f),Text);
  Buffer->RenderText(int(Cx-Size.cx/2.0f),int(Cy-Size.cy/2.0f),Text,0,clBlue32);
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ImgViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y,
      TCustomLayer *Layer)
{
 if(Layer == NULL)
 {
  Selection = NULL;
  ReleaseCapture;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ImgViewPaintStage(TObject *Sender,
      TBitmap32 *Buffer, DWORD StageNum)
{
 TColor32 Colors[2]={0xFFFFFFFF,0xFFB0B0B0};

 int W;
 PColor32 P;
 int OddY;

 ImgView->Buffer->Clear();
 P = ImgView->Buffer->PixelPtr[0][0];
 for(int j=0;j<ImgView->Buffer->Height;j++)
 {
  OddY = (j >> 3) & 0x1;
  for(int i=0;i<ImgView->Buffer->Width;i++)
  {
   (*P) = Colors[((i >> 3) & 0x1 == OddY)];
   P++;
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SetSelection(TPositionedLayer *Value)
{
 if(Value != FSelection)
 {
  if(RBLayer !=NULL)
  {
   RBLayer->ChildLayer = NULL;
   RBLayer->LayerOptions = LOB_NO_UPDATE;
   pnlBitmapLayer->Visible = false;
   PnlMagn->Visible = false;
   ImgView->Invalidate();
  }

  FSelection = Value;

  if(Value != NULL)
  {
   if(RBLayer == NULL)
   {
    RBLayer = new TRubberbandLayer(ImgView->Layers);
    RBLayer->MinHeight = 1;
    RBLayer->MinWidth = 1;
   }
   else
    RBLayer->BringToFront();
   RBLayer->ChildLayer = Value;
   RBLayer->LayerOptions = LOB_VISIBLE | LOB_MOUSE_EVENTS | LOB_NO_UPDATE;
   RBLayer->OnResizing = RBResizing;

   TBitmapLayer *pBitmapLayer=(TBitmapLayer *)Value;
   if(pBitmapLayer)
   {
    pnlBitmapLayer->Visible = true;
    LayerOpacity->Position = pBitmapLayer->Bitmap->MasterAlpha;
    LayerInterpolate->Checked = (pBitmapLayer->Bitmap->StretchFilter == sfLinear);
   }
   else
   if(Value->Tag == 2)
   {
    // tag = 2 for magnifiers
    PnlMagn->Visible = true;
   }
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::mnFileNewClick(TObject *Sender)
{
 FormNewImage->ShowModal();
 if(FormNewImage->ModalResult == mrOk)
  CreateNewImage(FormNewImage->UpDown1->Position, FormNewImage->UpDown2->Position, Color32(FormNewImage->Panel1->Color));
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::mnFileOpenClick(TObject *Sender)
{
 if(OpenPictureDialog1->Execute())
  OpenImage(OpenPictureDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
 Close();    
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::mnNewBitmapLayerClick(TObject *Sender)
{
 TBitmapLayer *B;
 TPoint P;
 Single W, H;

 if(OpenPictureDialog1->Execute())
 {
  B = new TBitmapLayer(ImgView->Layers);
  try
  {
   B->Bitmap->LoadFromFile(OpenPictureDialog1->FileName);
   B->Bitmap->DrawMode = dmBlend;

   TRect R=ImgView->GetViewporTRect();
   P = ImgView->ControlToBitmap(Point((R.Right + R.Left) / 2, (R.Top + R.Bottom) / 2));

   W = B->Bitmap->Width / 2.0f;
   H = B->Bitmap->Height / 2.0f;

   B->Location = FloaTRect(P.x - W, P.y - H, P.x + W, P.y + H);

   Scaled = true;
   OnMouseDown = LayerMouseDown;
  }
  catch(...)
  {
   if(B)
    delete B;
   throw;
  }
  Selection = B;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::mnNewBitmapRGBAClick(TObject *Sender)
{
/*
var
  B: TBitmapLayer;
  P: TPoint;
  Tmp: TBitmap32;
  W, H: Single;
begin
  with RGBALoaderForm do
  begin
    ImgRGB.Bitmap.Delete;
    ImgRGB.Scale := 1;
    ImgAlpha.Bitmap.Delete;
    ImgAlpha.Scale := 1;
    ShowModal;
    if (ModalResult = mrOK) and not ImgRGB.Bitmap.Empty then
    begin
      B := TBitmapLayer.Create(ImgView.Layers);
      B.Bitmap := ImgRGB.Bitmap;
      B.Bitmap.DrawMode := dmBlend; 

      if not ImgAlpha.Bitmap.Empty then
      begin
        Tmp := TBitmap32.Create;
        try
          Tmp.SetSize(B.Bitmap.Width, B.Bitmap.Height);
          ImgAlpha.Bitmap.DrawTo(Tmp, Rect32(0, 0, Tmp.Width, Tmp.Height));

          // combine Alpha into already loaded RGB colors
          IntensityToAlpha(B.Bitmap, Tmp);
        finally
          Tmp.Free;
        end;
      end;

      with ImgView.GetViewporTRect do
        P := ImgView.ControlToBitmap(Point((Right + Left) div 2, (Top + Bottom) div 2));

      with B do
      begin
        W := Bitmap.Width / 2;
        H := Bitmap.Height / 2;

        with ImgView.Bitmap do
          Location := FloaTRect(P.X - W, P.Y - H, P.X + W, P.Y + H);

        Scaled := True;
        OnMouseDown := LayerMouseDown;
      end;
      Selection := B;
    end;
  end;
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::mnSimpleDrawingClick(TObject *Sender)
{
 TPositionedLayer *L=new TPositionedLayer(ImgView->Layers);
 CreatePositionedLayer(L);
 L->OnPaint = PaintSimpleDrawingHandler;
 L->Tag = 1;
 Selection = L;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::mnMagnifierClick(TObject *Sender)
{
 TPositionedLayer *L=new TPositionedLayer(ImgView->Layers);
 CreatePositionedLayer(L);
 L->OnPaint = PaintMagnifierHandler;
 L->Tag = 2;
 Selection = L;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Text1Click(TObject *Sender)
{
 Text=InputBox("Text","Enter Text:","AliSoft");

 TPositionedLayer *L=new TPositionedLayer(ImgView->Layers);
 CreatePositionedLayer(L);
 L->OnPaint = PaintTextHandler;
 L->Tag = 3;
 Selection = L;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::mnFlattenClick(TObject *Sender)
{
 TBitmap32 *B;
 int W, H;
 // deselect everything
 Selection = NULL;
 W = ImgView->Bitmap->Width;
 H = ImgView->Bitmap->Height;

 // Create a new bitmap to store a flattened image
 B = new TBitmap32();
 try
 {
  B->SetSize(W, H);
  ImgView->PaintTo(B, Rect32(0, 0, W, H));

  // destroy all the layers of the original image...
  ImgView->Layers->Clear();
  RBLayer = NULL; // note that RBLayer reference is destroyed here as well.
                  // The rubber band will be recreated during the next
                  // SetSelection call. Alternatively, you can delete
                  // all the layers except the rubber band.
  // ...and overwrite it with the flattened one
  ImgView->Bitmap = B;
 }
 __finally
 {
  if(B)
   delete B;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::mnBringFrontClick(TObject *Sender)
{
 // note that the top-most layer is occupied with the rubber-banding layer
 if(Selection != NULL)
 {
  switch(((TMenuItem *)Sender)->Tag)
  {
   case 1: // Bring to front, do not use BringToFront here, see note above
   {
    Selection->Index = ImgView->Layers->Count - 2;
    break;
   }
   case 2:
   {
    Selection->SendToBack();
    break;
   }
   case 3:
   {
    Selection->Index = Selection->Index + 1; // up one level
    break;
   }
   case 4:
   {
    Selection->Index = Selection->Index - 1; // down one level
    break;
   }
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::mnLayersClick(TObject *Sender)
{
 bool B;
 B = ! ImgView->Bitmap->Empty();
 mnNewBitmapLayer->Enabled = B;
 mnNewBitmapRGBA->Enabled = B;
 mnNewCustomLayer->Enabled = B;
 mnFlatten->Enabled = B && (ImgView->Layers->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::mnArrangeClick(TObject *Sender)
{
 bool B;
 B = Selection != NULL;
 mnBringFront->Enabled = B && (Selection->Index < ImgView->Layers->Count - 2);
 mnSendBack->Enabled = B && (Selection->Index > 0);
 mnLevelUp->Enabled = B && (Selection->Index < ImgView->Layers->Count - 2);
 mnLevelDown->Enabled = B && (Selection->Index > 0);
 mnScaled->Enabled = B;
 mnScaled->Checked = B && Selection->Scaled;
 mnDelete->Enabled = B;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::mnScaledClick(TObject *Sender)
{
 if(Selection != NULL)
  Selection->Scaled = ! Selection->Scaled;
 RBLayer->Scaled = Selection->Scaled;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::mnDeleteClick(TObject *Sender)
{
 TPositionedLayer *ALayer;
 if(Selection != NULL)
 {
  ALayer = Selection;
  Selection = NULL;
  ALayer->Free();
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CroppedClick(TObject *Sender)
{
 if((TBitmapLayer *)Selection)
  ((TBitmapLayer *)Selection)->Cropped = Cropped->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ScaleComboChange(TObject *Sender)
{
 AnsiString S;
 int I;
 S = ScaleCombo->Text;
 S = StringReplace(S, "%", "", TReplaceFlags()<<rfReplaceAll);
 S = StringReplace(S, " ", "", TReplaceFlags()<<rfReplaceAll);
 if(S == "")
  return;
 I = StrToIntDef(S, -1);
 if((I < 1) || (I > 2000))
  I = int(ImgView->Scale * 100);
 else
  ImgView->Scale = I / 100;
 ScaleCombo->Text = IntToStr(I) + '%';
 ScaleCombo->SelStart = ScaleCombo->Text.Length() - 1;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ImageInterpolateClick(TObject *Sender)
{
 const TStretchFilter STRETCH_FILTER[2]={sfNearest,sfLinear};
 ImgView->Bitmap->StretchFilter = STRETCH_FILTER[ImageInterpolate->Checked];
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LayerOpacityChange(TObject *Sender)
{
 if(((TBitmapLayer *)Selection)!=NULL)
  ((TBitmapLayer *)Selection)->Bitmap->MasterAlpha = LayerOpacity->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LayerRescaleClick(TObject *Sender)
{
 TBitmap32 *T;
 TBitmapLayer *L=((TBitmapLayer *)Selection);
 // resize the layer's bitmap to the size of the layer
 if(L)
 {
  T = new TBitmap32();
  T->Assign(L->Bitmap);
  TRect R=Rect32(L->Location.Left,L->Location.Top,L->Location.Right,L->Location.Bottom);
  L->Bitmap->SetSize(R.Right - R.Left, R.Bottom - R.Top);
  T->StretchFilter = sfLinear;
  T->DrawMode = dmOpaque;
  T->DrawTo(L->Bitmap, Rect32(0, 0, L->Bitmap->Width, L->Bitmap->Height));
  if(T)
   delete T;
  LayerResetScaleClick(this);
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LayerResetScaleClick(TObject *Sender)
{
 TFloaTRect L;
 TBitmapLayer *T=(TBitmapLayer *)Selection;
 // resize the layer to the size of its bitmap
 if(T)
 {
//  with RBLayer, TBitmapLayer(Selection).Bitmap do
  L = RBLayer->Location;
  L.Right = L.Left + T->Bitmap->Width;
  L.Bottom = L.Top + T->Bitmap->Height;
  RBLayer->Location = L;
  T->Bitmap->Changed();
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MagnOpacityChange(TObject *Sender)
{
 ImgView->Invalidate();
}
//---------------------------------------------------------------------------

