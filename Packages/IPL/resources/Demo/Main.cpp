//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
/*
 InitializeLibrary();
 pEmbFile=new TEmbFile();
*/
 Left=0;
 Top=0;
 Width=Screen->Width;
 Height=Screen->Height;

 pBitmap=new Graphics::TBitmap();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Open1Click(TObject *Sender)
{
 if(OpenPictureDialog1->Execute())
 {
  FileName=OpenPictureDialog1->FileName;
  Caption="IPL Demo ["+FileName+"]";
  Image.Load(FileName.c_str());
  pImage=Image.GetTImagePtr();
  W=Image.GetWidth();
  H=Image.GetHeight();
  Bits=Image.GetBits();
  RowSize=W*Bits/8;
  ImageSize=RowSize*H;

  pBitmap->Width=W;
  pBitmap->Height=H;
  switch(Bits)
  {
   case 1:
   {
    pBitmap->PixelFormat=pf1bit;
    break;
   }
   case 8:
   {
    pBitmap->PixelFormat=pf8bit;
    break;
   }
   case 24:
   {
    pBitmap->PixelFormat=pf24bit;
    break;
   }
   default:
   {
    MessageDlg("Invalid Image Type...",mtError,TMsgDlgButtons()<<mbOK,0);
    return;
   }
  }

  Image1->Picture->Bitmap->Assign(pBitmap);
  for(int y=0;y<H;y++)
  {
   pData=(Byte *)pBitmap->ScanLine[y];
   CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
  }
  Image1->Canvas->Draw(0,0,pBitmap);
 }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Save1Click(TObject *Sender)
{
 if(SavePictureDialog1->Execute())
 {
  FileName=SavePictureDialog1->FileName;
  Caption="IPL Demo ["+FileName+"]";
  Image.Save(FileName.c_str());
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
 Application->Terminate();    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Negative1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Image.Invert();
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Delay=GetTickCount()-StartTime+1;
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Horizontal1Click(TObject *Sender)
{
 Image.FlipHorisontal();    
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Vertical1Click(TObject *Sender)
{
 Image.FlipVertical();
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Rotate1Click(TObject *Sender)
{
// int Angle=90;
// Image.Rotate90(Angle);
// CopyMemory(pData,Image.GetImageDataPtr(),ImageSize);
// Image1->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ScaleIntensity1Click(TObject *Sender)
{
 float Prefactor=1.0f;
 Image.ScaleIntensity(Prefactor);
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplyBias1Click(TObject *Sender)
{
 int Bias=100;
 Image.ApplyBias(Bias);
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Border1Click(TObject *Sender)
{
 Image.SetBorder(0,clBlue);
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Thining1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Morphology.Thinning(Image);
 Delay=GetTickCount()-StartTime+1;
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Erosion1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Morphology.ErodeFast(Image,1,1,1);
 Delay=GetTickCount()-StartTime+1;
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Dilation1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Morphology.DilateFast(Image,1,1,1);
 Delay=GetTickCount()-StartTime+1;
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Skeleton1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Morphology.Skeletonizing(Image);
 Delay=GetTickCount()-StartTime+1;
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SkeletonZhou1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Morphology.SkeletonZhou(Image,true);
 Delay=GetTickCount()-StartTime+1;
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SkeletonZhouwithoutEdges1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Morphology.SkeletonZhou(Image,false);
 Delay=GetTickCount()-StartTime+1;
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LowContours1Click(TObject *Sender)
{
/*
 StartTime=GetTickCount();

 CPoint2D<int> Start;
 ipl::DIRECTION SearchDirection=ipl::EAST;//SOUTH;
// ipl::CONNECTIVITY Connected=ipl::FOURCONNECTED;
 ipl::CONNECTIVITY Connected=ipl::EIGHTCONNECTED;
 ipl::ROTATION RotationDirection;
 ipl::COLORTYPE SurroundedColor;


 pPolygons=new TPolygons();
 for(int y=0;y<H;y++)
 {
  for(int x=0;x<W;x++)
  {
   if(!k_GetPixel1bp(x,y,*pImage))
   {
    Start.Set(x,y);
    PixelGroup.Empty();
    Segmentate.FindAndFollowLowContour(Image,Start,SearchDirection,Connected,
    					   PixelGroup,RotationDirection,SurroundedColor);

    pPolygon=new TPolygon();
    pPolygon->Type=ptContour;
    pPolygon->LineColor=clBlack;
    pPolygon->FillColor=clBlack;

    PixlesCount=PixelGroup.GetTotalPositions();
    CurrIndex=0;
    for(int i=0;i<PixlesCount;i++)
    {
     P=PixelGroup[i];
     k_SetPixel1bp(P.x,P.y,true,*pImage);

     pPoint=new TRPoint();
     pPoint->x=P.x;
     pPoint->y=P.y;
     pPolygon->Add(pPoint);
    }
    pPolygons->Add(pPolygon);
   }
  }
 }
 pPolyPolygons=new TPolyPolygons();
 pPolyPolygons->Add(pPolygons);

 pEmbFile->PolyStitchs->Clear();
 pEmbFile->PolyStitchs->AddPolyPolygons(pPolyPolygons);

 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Delay=GetTickCount()-StartTime+1;
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
*/ 
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
 CurrIndex++;
 if(CurrIndex<PixlesCount)
 {
  P=PixelGroup[CurrIndex];
  Image1->Canvas->Pixels[P.x][P.y]=clRed;
 }
 else
 {
  Timer1->Enabled=false;
  CurrIndex=0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Start1Click(TObject *Sender)
{
 Timer1->Enabled=true;
 CurrIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DeriveBlobs1Click(TObject *Sender)
{
/*
// ipl::COLORTYPE Color=ipl::HIGHCOLOR;
 ipl::COLORTYPE Color=ipl::LOWCOLOR;
 ipl::UINT8 Threshold=128;
 ipl::CONNECTIVITY Connected=ipl::EIGHTCONNECTED;

 StartTime=GetTickCount();
 Segmentate.DeriveBlobs(Image,PixelGroups,Color,Threshold,Connected);

 PixlesGroupCount=PixelGroups.GetTotalGroups();
 pPolygons=new TPolygons();
 for(int i=0;i<PixlesGroupCount;i++)
 {
  PixelGroup=(*PixelGroups.GetGroup(i));
  PixlesCount=PixelGroup.GetTotalPositions();
  pPolygon=new TPolygon();
  pPolygon->Type=ptContour;
  pPolygon->LineColor=clBlack;
  pPolygon->FillColor=clBlack;
  for(int j=0;j<PixlesCount;j++)
  {
   P=PixelGroup[j];
   Image1->Canvas->Pixels[P.x][P.y]=clBlue;

   pPoint=new TRPoint();
   pPoint->x=P.x;
   pPoint->y=H-1-P.y;
   pPolygon->Add(pPoint);
  }
  pPolygons->Add(pPolygon);
 }
 pEmbFile->PolyStitchs->Clear();
 pEmbFile->PolyStitchs->AddPolygons(false,pPolygons);

 Delay=GetTickCount()-StartTime+1;
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
*/ 
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Save2Click(TObject *Sender)
{
/*
 if(SaveDialog1->Execute())
 {
  pEmbFile->SaveToFile(SaveDialog1->FileName);
 }
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Pol1Click(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
 if(pBitmap)
  delete pBitmap;
/*
 if(pEmbFile)
  delete pEmbFile;
 FinalizeLibrary();
*/ 
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MyNegative1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 ipl::TImage *pImage=Image.GetTImagePtr();
 for(int y=0;y<pImage->Height;y++)
 {
  for(int x=0;x<pImage->ByteWidth;x++)
  {
   pImage->ppMatrix[y][x]=255-pImage->ppMatrix[y][x];
  }
 }
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);

 Delay=GetTickCount()-StartTime+1;
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Flush1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 Image.Flush(clWhite);
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);

 Delay=GetTickCount()-StartTime+1;
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Save3Click(TObject *Sender)
{
/*
 if(SaveDialog2->Execute())
 {
  pPolyPolygons->SaveToFile(SaveDialog2->FileName);
 }
*/     
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FillPattern1Click(TObject *Sender)
{
/*
 StartTime=GetTickCount();

 const int PointsCount=7;
 TPoint Path[PointsCount];
 int x1=4;
 int x2=8;
 int x3=12;
 int x4=16;
 int y1=10;
 int y2=16;
 Path[0]=Point(x1,0);
 Path[1]=Point(x2,y2);
 Path[2]=Point(x3,0);
 Path[3]=Point(0,y1);
 Path[4]=Point(x4,y1);
 Path[5]=Point(x1,0);
 Path[6]=Point(x2,y2);

 int PathW=16;
 int PathH=16;

 pPolygons=new TPolygons();
 for(int y=0;y<H-PathH;y+=PathH)
 {
  for(int x=0;x<W-PathW;x+=PathW)
  {
   pPolygon=new TPolygon();
   pPolygon->Type=ptContour;
   pPolygon->LineColor=clBlack;
   pPolygon->FillColor=clBlack;

   for(int i=0;i<PointsCount;i++)
   {
    if(!k_GetPixel1bp(x+Path[i].x,y+Path[i].y,*pImage))
    {
     pPoint=new TRPoint();
     pPoint->x=x+Path[i].x;
     pPoint->y=H-1-(y+Path[i].y);
     pPolygon->Add(pPoint);
    }
   }

   if(!pPolygon->Empty)
    pPolygons->Add(pPolygon);
   else
    delete pPolygon;
  }
 }
 pPolyPolygons=new TPolyPolygons();
 pPolyPolygons->Add(pPolygons);

 pEmbFile->PolyStitchs->Clear();
 pEmbFile->PolyStitchs->AddPolyPolygons(pPolyPolygons);

 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Delay=GetTickCount()-StartTime+1;
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";


 if(SaveDialog1->Execute())
  pEmbFile->SaveToFile(SaveDialog1->FileName);
*/  
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SmoothEdges1Click(TObject *Sender)
{
 StartTime=GetTickCount();
 double maxS=3.0;
 double minS=1.0/maxS;
 k_ScaleAuto(pImage,pImage,minS,minS,1);
 k_ScaleAuto(pImage,pImage,maxS,maxS,1);

 Delay=GetTickCount()-StartTime+1;
 for(int y=0;y<H;y++)
 {
  pData=(Byte *)pBitmap->ScanLine[y];
  CopyMemory(pData,pImage->ppAllScanLines[y],RowSize);
 }
 Image1->Canvas->Draw(0,0,pBitmap);
 Caption="IPL Demo ["+FileName+"] {"+FormatFloat("0 ms",Delay)+"}";
}
//---------------------------------------------------------------------------

