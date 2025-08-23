/********************************************************************
   The Image Processing Library 98 - IPL98
   Copyright (C) by René Dencker Eriksen - edr@mip.sdu.dk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation. Only
   addition is, that if the library is used in proprietary software
   it must be stated that IPL98 was used.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   More details can be found in the file licence.txt distributed
   with this library.
*********************************************************************/

#include "b_kernel_functions.h"
#include "../kernel_string.h"
#include "../kernel_error.h"
#include "../kernel_history.h"
#include <memory.h>

#ifdef _IPL98_USING_CPP
namespace ipl{ /* use namespace if C++ */
extern "C" { /* prevent name mangling for C functions */
#endif

/************************************************/
/********        Private functions       ********/
/************************************************/

bool kB_CreatePal(TPalette* pPal);

/* returns the size of a scanline incl. zero padding in bytes */
UINT32 kB_GetSizeScanLine(UINT32 Width);


/************************************************/
/********        Public functions        ********/
/************************************************/

void kB_EmptyImage(TImage* pInfo)
{
	k_EmptyFileInfo(&(pInfo->FileInfo));
	k_EmptyText(&(pInfo->History));
	k_EmptyPalette(&(pInfo->Pal));
	if (pInfo->pPixelStream!=NULL)
	{
		free(pInfo->pPixelStream);
		pInfo->pPixelStream=NULL;
	}
	if (pInfo->ppAllScanLines!=NULL)
	{
		free(pInfo->ppAllScanLines);
		pInfo->ppAllScanLines=NULL;
	}
	pInfo->Width=0;
	pInfo->Height=0;
	pInfo->BorderSize=0;
	pInfo->ByteWidth=0;
	pInfo->TotalSize=0;
	pInfo->Origin=EMPTY;
	pInfo->Pal.PalEntries=0;
	pInfo->Origo.x=0;
	pInfo->Origo.y=0;
}

void kB_InitImage(TImage* pInfo)
{
	k_InitFileInfo(&(pInfo->FileInfo));
	k_InitText(&(pInfo->History));
	k_InitPalette(&(pInfo->Pal));
	pInfo->pPixelStream=NULL;
	pInfo->ppMatrix=NULL;
	pInfo->ppAllScanLines=NULL;
	pInfo->Origin=EMPTY;
	pInfo->Bits=8; /* always 8 */
	pInfo->Origo.x=0;
	pInfo->Origo.y=0;
}

bool kB_AllocImage(UINT32 Width, UINT32 Height, TImage* pInfo)
{
	/* set values in the image info structure */
	pInfo->Origin=RAM;
	pInfo->Width=Width;
	pInfo->Height=Height;
	pInfo->Bits=8; /* always 8 */
	pInfo->BorderSize=0; /* always 0 for a new image */
	pInfo->Origo.x=0;
	pInfo->Origo.y=0;
	/* calculate size and width (incl zero-padding) of image */
	pInfo->ByteWidth=(UINT16) kB_GetSizeScanLine(Width);
	pInfo->TotalSize = pInfo->ByteWidth * Height; /* no compression */
	/* Allocate memory for image */
	pInfo->pPixelStream=(UINT8*) calloc(sizeof(UINT8),pInfo->TotalSize);
	kB_SetImageMatrix(pInfo);
	/* Create gray palette */
	if (kB_CreatePal(&pInfo->Pal)==false)
	{
		kB_EmptyImage(pInfo);
		return false;
	}
	return true;
}

bool kB_AllocImageFast(UINT32 Width, UINT32 Height, TImage* pInfo)
{
	/* set values in the image info structure */
	pInfo->Origin=RAM;
	pInfo->Width=Width;
	pInfo->Height=Height;
	pInfo->Bits=8; /* always 8 */
	pInfo->BorderSize=0; /* always 0 for a new image */
	pInfo->Origo.x=0;
	pInfo->Origo.y=0;
	/* calculate size and width (incl zero-padding) of image */
	pInfo->ByteWidth=(UINT16) kB_GetSizeScanLine(Width);
	pInfo->TotalSize = pInfo->ByteWidth * Height; /* no compression */
	/* Allocate memory for image */
	pInfo->pPixelStream=(UINT8*) malloc(sizeof(UINT8)*pInfo->TotalSize);
	kB_SetImageMatrix(pInfo);
	/* Create gray palette */
	if (kB_CreatePal(&pInfo->Pal)==false)
	{
		kB_EmptyImage(pInfo);
		return false;
	}
	return true;
}

bool kB_Load(const char* FileName, TImage* pInfo)
{
	/* Load the image into the general TImage structure */
	bool returnValue=k_Load(FileName,pInfo);
	if (pInfo->Bits!=8)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_Load() Image is %d b/p, should be 8 b/p",pInfo->Bits);
		k_EmptyString(&str);
		return false;
	}
	if (!returnValue)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_Load() Failed loading");
		k_EmptyString(&str);
	}
	return returnValue;
}

bool kB_Save(const char* FileName, TImage* pInfo)
{
	bool returnValue=k_Save(FileName,pInfo);
	if (!returnValue)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_Save() Failed saving");
		k_EmptyString(&str);
	}
	return returnValue;
}

bool kB_CopyImage(TImage* pDest, const TImage* pSource)
{
	if (pDest==pSource)
	{
		/* cannot copy to itself! */
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_CopyImage() Source and destination image"
			"the same - doing nothing");
		k_EmptyString(&str);
		return false;
	}
	else if (pSource->Bits!=8)
	{
		/* Bits != 8, a conversion is nescesarry */
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_CopyImage() Conversion of %d b/p to 8 b/p not "
			"possible with this function",pSource->Bits);
		k_EmptyString(&str);
		return false;
	}
	/* Allocate memory if necessary */
	if ((pDest->TotalSize!=pSource->TotalSize) || (pDest->Bits!=pSource->Bits) || 
		(pDest->BorderSize!=pSource->BorderSize))
	{
		kB_EmptyImage(pDest);
		pDest->TotalSize = pSource->TotalSize;
		pDest->Bits=pSource->Bits;
		pDest->BorderSize=pSource->BorderSize;
		pDest->pPixelStream=(UINT8*) malloc(pDest->TotalSize*sizeof(UINT8));
		pDest->Width=pSource->Width; /* need to set width and height for k_SetImageMatrix! */
		pDest->Height=pSource->Height;
		kB_SetImageMatrix(pDest);
	}
	/* set values in the image info structure */
	pDest->Origin=RAM;
	pDest->Width=pSource->Width;
	pDest->Height=pSource->Height;
	pDest->Origo.x=0;
	pDest->Origo.y=0;
	pDest->ByteWidth=pSource->ByteWidth;
	if (pSource->Origin!=EMPTY)
	{
#ifdef IPL_ADD_HISTORY
		/* copy history before adding comment */
		k_CopyText(&(pDest->History),&(pSource->History));
		/* add comment to history */
		{
			TString History;
			k_InitString(&History);
			k_SprintfString(&History,"%skB_CopyImage() Source image file info: %s"
				,ipl_HistoryIndent,pSource->FileInfo.PathAndFileName);
			k_AppendTextIPL(&(pDest->History),History.pChars);
			k_EmptyString(&History);
			k_IplStartHistoryMacro();
		}
#endif
		/* copy palette */
		k_CopyPalette(&(pDest->Pal),&(pSource->Pal));
		/* copy file information */
		k_CopyFileInfo(&(pDest->FileInfo),&(pSource->FileInfo));
		/* Alloc memory and copy bitmap data */
		memcpy(pDest->pPixelStream,pSource->pPixelStream,pDest->TotalSize);
#ifdef IPL_ADD_HISTORY
		/* end history appending (remove a leading '\t' character) */
		k_IplStopHistoryMacro();
#endif
	}
	return true;
}

bool kB_SetBorder(UINT16 Size, UINT32 Color, TImage* pInfo)
{
	UINT32 realX,realY,offset;
	UINT32 UINT32Value; /* temporary variable */
	UINT8* pNewImage; /* variable pointing to new allocated image area */
	UINT32 i;
	UINT32 SmallestByteWidth;
	realX=pInfo->Width+2*Size; /* width of image + border */
	realY=pInfo->Height+2*Size; /* height of image + border */
	/* calculate size and width (incl zero-padding) of image + border */
	UINT32Value=kB_GetSizeScanLine(realX);
	/* Only copy memory area for the shortest width of the destination and source image */
	SmallestByteWidth=UINT32Value<(UINT32)pInfo->ByteWidth ? UINT32Value : pInfo->ByteWidth;
	pInfo->BorderSize=Size;
	/* Allocate memory for image */
	pNewImage=(UINT8*) malloc(sizeof(UINT8)*UINT32Value*realY);
	offset=pInfo->Height-1+Size;
	for(i=Size;i<Size+pInfo->Height;i++)
	{
		memcpy(pNewImage+Size+i*UINT32Value,(pInfo->ppMatrix)[offset-i],SmallestByteWidth);
	}
	free(pInfo->pPixelStream); /* release old image area */
	pInfo->pPixelStream=pNewImage;
	kB_SetImageMatrix(pInfo);
	pInfo->ByteWidth=(UINT16) UINT32Value;
	pInfo->TotalSize=(UINT16) UINT32Value*(realY);
	kB_SetBorderColor(Color,pInfo);
	return true;
}

bool kB_SetBorderColor(UINT32 Color, TImage* pInfo)
{
	UINT16 borderSize=pInfo->BorderSize;
	UINT16 byteWidth=pInfo->ByteWidth;
	int i,offset;
	/* Set upper border */
	memset(pInfo->pPixelStream,Color,byteWidth*borderSize);
	for(i=borderSize;i<(int)pInfo->Height+borderSize;i++){
		/* Set left border */
		memset(pInfo->ppAllScanLines[i]-borderSize,Color,borderSize);
		/* Set right border */
		memset(pInfo->ppAllScanLines[i]+pInfo->Width,Color,borderSize);
	}
	/* Set lower border */
	offset=byteWidth*(borderSize+pInfo->Height);
	memset(pInfo->pPixelStream+offset,Color,byteWidth*borderSize);
	return true;
}

bool kB_CopySubImage(int xmin,int ymin,int xmax,int ymax,
				  TImage* pDest,const TImage* pSource)
{
	TImage* pTarget=pDest;
	bool CopyToSource=false;
	if (pSource->Origin==EMPTY)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_WARNING,&str,"kB_CopySubImage() Source image is empty - doing nothing");
		k_EmptyString(&str);
		return false;
	}
	else if (pSource->Bits!=8)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_CopySubImage() %d b/p not supported - doing nothing",pSource->Bits);
		k_EmptyString(&str);
		return false;
	}
	/* Check if the source and destination is the same image */
	if (pDest==pSource)
	{
		pTarget=(TImage*) malloc(sizeof(TImage));
		kB_InitImage(pTarget);
		CopyToSource=true;
	}
	/* Not optimised regarding speed! */
	if ((xmin<xmax) && (ymin<ymax) && 
		(xmin>=kB_GetMinX(pSource)) && (ymin>=kB_GetMinY(pSource)) &&
		(xmax<=kB_GetMaxX(pSource)) && (ymax<=kB_GetMaxY(pSource)))
	{
		UINT16 xdim,ydim;
		int i,j;
		xdim=(UINT16)(xmax-xmin);
		ydim=(UINT16)(ymax-ymin);
		kB_EmptyImage(pTarget);
		/* prepare destination image, following lines faster than calling kB_CopyImage() */
		kB_AllocImage(xdim,ydim,pTarget);
		k_CopyPalette(&(pTarget->Pal),&(pSource->Pal));
		k_CopyFileInfo(&(pTarget->FileInfo),&(pSource->FileInfo));
#ifdef IPL_ADD_HISTORY
		/* copy history before adding comment */
		k_CopyText(&(pTarget->History),&(pSource->History));
		/* add comment to history */
		{
			TString History;
			k_InitString(&History);
			k_SprintfString(&History,"%skB_CopySubImage(xmin=%d,ymin=%d,xmax=%d,ymax=%d) Source image file info: %s"
				,ipl_HistoryIndent,xmin,ymin,xmax,ymax,pSource->FileInfo.PathAndFileName);
			k_AppendTextIPL(&(pTarget->History),History.pChars);
			k_EmptyString(&History);
			k_IplStartHistoryMacro();
		}
#endif
		/* copy palette */
		k_CopyPalette(&pTarget->Pal,&pSource->Pal);
		/* copy image pixels */
		for(i=ymin; i<ymax; i++)
			for(j=xmin; j<xmax; j++)
				k_SetPixel8bp((j-xmin),(i-ymin),k_GetPixel8bp(j,i,*pSource),*pTarget);
		pTarget->Origin=RAM;
        if (CopyToSource==true)
        {
	        kB_CopyImage(pDest,pTarget);
			kB_EmptyImage(pTarget);
		    free(pTarget);
        }
#ifdef IPL_ADD_HISTORY
		/* end history appending (remove a leading '\t' character) */
		k_IplStopHistoryMacro();
#endif
		return true;
	}
	else
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_CopySubImage() Illegal clipping rectangel");
		k_EmptyString(&str);
		return false;
	}
}

int kB_GetMinX(const TImage* Img)
{
	return 0;
}

int kB_GetMinY(const TImage* Img)
{
	return 0;
}

int kB_GetMaxX(const TImage* Img)
{
	return Img->Width;
}

int kB_GetMaxY(const TImage* Img)
{
	return Img->Height;
}

void kB_PrintImageInfo(const TImage* pInfo)
{
	char* Name;
	k_GetOriginString(pInfo->Origin,&Name);
	printf("**************** ByteImage info ********************\n");
	printf(" Width=%d Height=%d ByteWidth=%d SizeImage=%d Bits=8 (always!)\n",
		pInfo->Width,pInfo->Height,pInfo->ByteWidth,pInfo->TotalSize);
	printf(" PalEntries=%d BorderSize=%d Origo=(0,0) (always!) Origin=%s\n",
		pInfo->Pal.PalEntries,pInfo->BorderSize,Name);
	k_PrintFileInfo(&pInfo->FileInfo);
	free(Name);
}

/****************************************/
/*           C only functions           */
/****************************************/

UINT32 kB_GetPixel(int x, int y,const TImage* pInfo)
{
	UINT16 border=pInfo->BorderSize;

	if ((x>=-border) && (x<(int) pInfo->Width+border) &&
		(y>=-border) && (y<(int) pInfo->Height+border))
	{
		/*return (pInfo->ppMatrix[y][x])&0xff;*/
		return k_GetPixel8bp(x,y,(*pInfo));
	}
	else
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_GetPixel(%d,%d) Outside image and border",x,y);
		k_EmptyString(&str);
		return 0;
	}
}

bool kB_SetPixel(int x, int y, UINT32 Color,TImage* pInfo)
{
	UINT16 border=pInfo->BorderSize;

	if((x>=-border) && (x<(int) pInfo->Width+border) &&
		(y>=-border) && (y<(int) pInfo->Height+border))
	{
		/*pInfo->ppMatrix[y][x]=(UINT8)Color;*/
		k_SetPixel8bp(x,y,Color,(*pInfo));
		return true;
	}
	else
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_SetPixel(%d,%d) Outside image and border",x,y);
		k_EmptyString(&str);
		return false;
	}
}

UINT32 kB_GetPixelFast(int x, int y,const TImage* pInfo)
{
	return k_GetPixel8bp(x,y,(*pInfo));
}

bool kB_SetPixelFast(int x, int y, UINT32 Color,TImage* pInfo)
{
	k_SetPixel8bp(x,y,Color,(*pInfo));
	return true;
}

float kB_GetPixelInterpolated(float x, float y, const TImage* pInfo)
{
	/* for graytone images only
	   for 1,4 and 8 b/p: uses bilinar interpolation */
	/* no need to add origo, since it is always (0,0) */
	INT16 border=(INT16)(pInfo->BorderSize-1); /* interpolation need to access pixels around actual value */

	if ((pInfo->Bits!=1) && (pInfo->Bits!=4) && (pInfo->Bits!=8))
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_GetPixelInterpolated() Image must be 1,8 or 24 b/p");
	    k_EmptyString(&str);
		return 0;
	}

	if((x>=-border) && (x<(int) pInfo->Width+border) &&
		(y>=-border) && (y<(int) pInfo->Height+border))
	{
		/* upper left pixel (l ~ low) */
		int xl = (int)x;
		int yl = (int)y;
		/* lower right pixel (h ~ high) */
		int xh = xl + 1;
		int yh = yl + 1;
		/* do bilinear interpolation */
		return ((k_GetPixel8bp(xl,yl,(*pInfo))*((float)xh-x) + k_GetPixel8bp(xh,yl,(*pInfo))*(x-(float)xl))*((float)yh-y) +
		 (k_GetPixel8bp(xl,yh,(*pInfo))*((float)xh-x) + k_GetPixel8bp(xh,yh,(*pInfo))*(x-(float)xl))*(y-(float)yl));
	}
	else
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"kB_GetPixelInterpolated(%f,%f) Needs "
			"to access pixels outside image and border",x,y);
		k_EmptyString(&str);
		return -1;
	}
}

float kB_GetPixelInterpolatedFast(float x, float y, const TImage* pInfo)
{
	/* for graytone images only
	   for 1,4 and 8 b/p: uses bilinar interpolation
	   upper left pixel (l ~ low) */
	int xl = (int)x;
	int yl = (int)y;
	/* lower right pixel (h ~ high) */
	int xh = xl + 1;
	int yh = yl + 1;
	/* do bilinear interpolation */
	return ((k_GetPixel8bp(xl,yl,(*pInfo))*((float)xh-x) + k_GetPixel8bp(xh,yl,(*pInfo))*(x-(float)xl))*((float)yh-y) +
	 (k_GetPixel8bp(xl,yh,(*pInfo))*((float)xh-x) + k_GetPixel8bp(xh,yh,(*pInfo))*(x-(float)xl))*(y-(float)yl));
}

void kB_SetImageMatrix(TImage* pInfo)
{
	/* Sets "pInfo->ppMatrix[y]" to point to start of every scan line
	   inside image and set the pInfo->ppMatrix[y][x]
	   call this function after pInfo->BorderSize is set */
	UINT32 y;
	UINT16 border=pInfo->BorderSize;
	UINT32 totalHeight=pInfo->Height+2*border;
	UINT32 realX=pInfo->Width+2*border; /* width of image + border */
	UINT32 UINT32Value; /* temporary variable */
	/* calculate size and width (incl zero-padding) of image + border */
	UINT32Value=kB_GetSizeScanLine(realX);
	/*printf("totalHeight=%d\n",totalHeight);*/
	if (pInfo->ppAllScanLines!=NULL){
		free(pInfo->ppAllScanLines);
	}

	(pInfo->ppAllScanLines) = (UINT8**) malloc(sizeof(UINT8*)*(totalHeight));
	pInfo->ppMatrix = &((pInfo->ppAllScanLines)[border]);

	for(y=0;y<totalHeight;y++)
	{
		(pInfo->ppAllScanLines)[totalHeight-1-y]=(pInfo->pPixelStream+y*UINT32Value+border);
	}
}

UINT32 kB_GetSizeScanLine(UINT32 Width)
{
	/* returns the size of a scanline incl. zero padding in bytes */
	UINT32 UINT32Value = (Width*8) / 32;
	if((Width*8) % 32)
	{
		UINT32Value++;
	}
	UINT32Value *= 4;
	return UINT32Value;
}

/****************************************/
/*           Palette functions          */
/****************************************/

bool kB_CreatePal(TPalette* pPal)
{
	/* allocates memory for palette and initialises to gray tones */
	UINT16 count;
	pPal->PalEntries=256;
	pPal->pPalette=(UINT32*) malloc(sizeof(UINT32)*256);
	/* Create gray tone palette */
	for(count=0; count<256; count++)
	{
		k_SetPalValue(count,k_PalCreateRGB(count,count,count),pPal);
	}
	return true;
}


#ifdef _IPL98_USING_CPP
} /* end of extern "C" */
} /* end namespace ipl */
#endif
