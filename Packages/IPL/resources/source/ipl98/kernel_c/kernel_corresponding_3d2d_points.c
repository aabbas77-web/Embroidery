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

#include "kernel_corresponding_3d2d_points.h"
#include "kernel_string.h"
#include "kernel_error.h"
#include "kernel_io.h"
#include <stdlib.h>
#include <string.h>

#ifdef _IPL98_USING_CPP
namespace ipl{ /* use namespace if C++ */
extern "C" { /* prevent name mangling for C functions */
#endif

void k_Init3D2DPoints(T3D2DPoints* pInfo)
{
	pInfo->pSet=NULL;
	pInfo->NumberOfSets=0;
	pInfo->AllocatedSets=0;
}

void k_Empty3D2DPoints(T3D2DPoints* pInfo)
{
	if (pInfo->pSet!=NULL)
		free(pInfo->pSet);
	k_Init3D2DPoints(pInfo);
}

void k_Alloc3D2DPoints(T3D2DPoints* pInfo,unsigned int InitialSize)
{
	k_Empty3D2DPoints(pInfo);
	if (InitialSize==0)
		InitialSize=1; /* minimum one allocated set of points */
	pInfo->pSet=(TSinglePointSet*)malloc(InitialSize*sizeof(TSinglePointSet));
	pInfo->NumberOfSets=0; /* just in case! */
	pInfo->AllocatedSets=InitialSize; /* internal use */
}

void k_ReAlloc3D2DPoints(T3D2DPoints* pInfo,unsigned int NewSize)
{
	if ((pInfo->pSet=(TSinglePointSet*)realloc(pInfo->pSet,NewSize*sizeof(TSinglePointSet)))!=NULL)
	{
		if (NewSize<pInfo->NumberOfSets)
			pInfo->NumberOfSets=NewSize;

		pInfo->AllocatedSets=NewSize; /* internal use */
	}
	else
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_ReAlloc3D2DPoints() Realloc failed");
		k_EmptyString(&str);
	}
}

void k_AdjustSizeOf3D2DPoints(T3D2DPoints* pInfo)
{
	if ((pInfo->pSet=(TSinglePointSet*)realloc(pInfo->pSet,pInfo->NumberOfSets*sizeof(TSinglePointSet)))!=NULL)
	{
		pInfo->AllocatedSets=pInfo->NumberOfSets; /* internal use */
	}
	else
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_AdjustSizeOf3D2DPoints() Realloc failed");
		k_EmptyString(&str);
	}
}

bool k_SetAll3DPointsToNotUsed(T3D2DPoints* pInfo)
{
	unsigned int count;
	bool ReturnValue=true;
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_SetAll3DPointsToNotUsed() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if (pInfo->pSet[count].Pnt2DInUse==false)
		{
			ReturnValue=false;
		}
		pInfo->pSet[count].Pnt3DInUse=false;
	}
	return ReturnValue;
}

bool k_SetAll2DPointsToNotUsed(T3D2DPoints* pInfo)
{
	unsigned int count;
	bool ReturnValue=true;
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_SetAll2DPointsToNotUsed() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if (pInfo->pSet[count].Pnt3DInUse==false)
		{
			ReturnValue=false;
		}
		pInfo->pSet[count].Pnt2DInUse=false;
	}
	return ReturnValue;
}

bool k_SetAllIdsToNotUsed(T3D2DPoints* pInfo)
{
	unsigned int count;
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_SetAllIdsToNotUsed() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		pInfo->pSet[count].IdInUse=false;
	}
	return true;
}

bool k_AddPointSetAndIdTo3D2DPoints(const T3DFloat* pPnt3D, const T2DFloat* pPnt2D,
									int Id, T3D2DPoints* pInfo)
{
	unsigned int count;
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_AddPointSetAndIdTo3D2DPoints() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	/* check if Id is unique */
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if (pInfo->pSet[count].Id == Id)
		{
			TString str;
			k_InitString(&str);
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_ERROR,&str,"k_AddPointSetAndIdTo3D2DPoints() Id=%d not unique",Id);
			k_EmptyString(&str);
			return false;
		}
	}
	if (pInfo->NumberOfSets==pInfo->AllocatedSets)
	{
		/* allocate 2 times previous allocated memory or 2 if memory never allocated before */
		pInfo->AllocatedSets = 
			(pInfo->AllocatedSets==0) ? 2 : 2*pInfo->AllocatedSets;

		k_ReAlloc3D2DPoints(pInfo,pInfo->AllocatedSets);
	}
	/* insert point set and increment total number of point sets variable */
	pInfo->pSet[pInfo->NumberOfSets].Pnt3D = (*pPnt3D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt3DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].Pnt2D = (*pPnt2D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt2DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].Id = Id;
	pInfo->pSet[pInfo->NumberOfSets].IdInUse = true;
	pInfo->NumberOfSets++;
	return true;
}

bool k_AddPoint3DAndIdTo3D2DPoints(const T3DFloat* pPnt3D, int Id, T3D2DPoints* pInfo)
{
	unsigned int count;
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_AddPoint3DAndIdTo3D2DPoints() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	/* check if Id is unique */
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if (pInfo->pSet[count].Id == Id)
		{
			TString str;
			k_InitString(&str);
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_ERROR,&str,"k_AddPoint3DAndIdTo3D2DPoints() Id=%d not unique",Id);
			k_EmptyString(&str);
			return false;
		}
	}
	if (pInfo->NumberOfSets==pInfo->AllocatedSets)
	{
		/* allocate 2 times previous allocated memory or 2 if memory never allocated before */
		pInfo->AllocatedSets = 
			(pInfo->AllocatedSets==0) ? 2 : 2*pInfo->AllocatedSets;

		k_ReAlloc3D2DPoints(pInfo,pInfo->AllocatedSets);
	}
	/* insert point set and increment total number of point sets variable */
	pInfo->pSet[pInfo->NumberOfSets].Pnt3D = (*pPnt3D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt3DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].Pnt2DInUse = false;
	pInfo->pSet[pInfo->NumberOfSets].Id = Id;
	pInfo->pSet[pInfo->NumberOfSets].IdInUse = true;
	pInfo->NumberOfSets++;
	return true;
}

bool k_AddPoint2DAndIdTo3D2DPoints(const T2DFloat* pPnt2D, int Id, T3D2DPoints* pInfo)
{
	unsigned int count;
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_AddPoint2DAndIdTo3D2DPoints() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	/* check if Id is unique */
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if (pInfo->pSet[count].Id == Id)
		{
			TString str;
			k_InitString(&str);
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_ERROR,&str,"k_AddPoint2DAndIdTo3D2DPoints() Id=%d not unique",Id);
			k_EmptyString(&str);
			return false;
		}
	}
	if (pInfo->NumberOfSets==pInfo->AllocatedSets)
	{
		/* allocate 2 times previous allocated memory or 2 if memory never allocated before */
		pInfo->AllocatedSets = 
			(pInfo->AllocatedSets==0) ? 2 : 2*pInfo->AllocatedSets;

		k_ReAlloc3D2DPoints(pInfo,pInfo->AllocatedSets);
	}
	/* insert point set and increment total number of point sets variable */
	pInfo->pSet[pInfo->NumberOfSets].Pnt3DInUse = false;
	pInfo->pSet[pInfo->NumberOfSets].Pnt2D = (*pPnt2D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt2DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].Id = Id;
	pInfo->pSet[pInfo->NumberOfSets].IdInUse = true;
	pInfo->NumberOfSets++;
	return true;
}

bool k_AddPointSetTo3D2DPoints(const T3DFloat* pPnt3D, const T2DFloat* pPnt2D,
									T3D2DPoints* pInfo)
{
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_AddPointSetTo3D2DPoints() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	if (pInfo->NumberOfSets==pInfo->AllocatedSets)
	{
		/* allocate 2 times previous allocated memory or 2 if memory never allocated before */
		pInfo->AllocatedSets = 
			(pInfo->AllocatedSets==0) ? 2 : 2*pInfo->AllocatedSets;

		k_ReAlloc3D2DPoints(pInfo,pInfo->AllocatedSets);
	}
	/* insert point set and increment total number of point sets variable */
	pInfo->pSet[pInfo->NumberOfSets].Pnt3D = (*pPnt3D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt3DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].Pnt2D = (*pPnt2D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt2DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].IdInUse = false;
	pInfo->NumberOfSets++;
	return true;
}

bool k_AddPoint3DTo3D2DPoints(const T3DFloat* pPnt3D, T3D2DPoints* pInfo)
{
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_AddPoint3DTo3D2DPoints() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	if (pInfo->NumberOfSets==pInfo->AllocatedSets)
	{
		/* allocate 2 times previous allocated memory or 2 if memory never allocated before */
		pInfo->AllocatedSets = 
			(pInfo->AllocatedSets==0) ? 2 : 2*pInfo->AllocatedSets;

		k_ReAlloc3D2DPoints(pInfo,pInfo->AllocatedSets);
	}
	/* insert point set and increment total number of point sets variable */
	pInfo->pSet[pInfo->NumberOfSets].Pnt3D = (*pPnt3D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt3DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].Pnt2DInUse = false;
	pInfo->pSet[pInfo->NumberOfSets].IdInUse = false;
	pInfo->NumberOfSets++;
	return true;
}

bool k_AddPoint2DTo3D2DPoints(const T2DFloat* pPnt2D, T3D2DPoints* pInfo)
{
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_AddPoint2DTo3D2DPoints() pInfo is NULL");
		k_EmptyString(&str);
		return false;
	}
	if (pInfo->NumberOfSets==pInfo->AllocatedSets)
	{
		/* allocate 2 times previous allocated memory or 2 if memory never allocated before */
		pInfo->AllocatedSets = 
			(pInfo->AllocatedSets==0) ? 2 : 2*pInfo->AllocatedSets;

		k_ReAlloc3D2DPoints(pInfo,pInfo->AllocatedSets);
	}
	/* insert point set and increment total number of point sets variable */
	pInfo->pSet[pInfo->NumberOfSets].Pnt3DInUse = false;
	pInfo->pSet[pInfo->NumberOfSets].Pnt2D = (*pPnt2D);
	pInfo->pSet[pInfo->NumberOfSets].Pnt2DInUse = true;
	pInfo->pSet[pInfo->NumberOfSets].IdInUse = false;
	pInfo->NumberOfSets++;
	return true;
}

bool k_Copy3D2DPoints(T3D2DPoints* pDest,const T3D2DPoints* pSource)
{
	if (pDest==pSource)
	{
		/* cannot copy to itself! */
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_Copy3D2DPoints() Source and destination T3D2DPoints"
			" structure the same - doing nothing");
		k_EmptyString(&str);
		return false;
	}
	else if ((pSource!=NULL) && (pDest!=NULL))
	{
		unsigned int count;
		k_Empty3D2DPoints(pDest);
		pDest->pSet = (TSinglePointSet*) malloc(pSource->NumberOfSets*sizeof(TSinglePointSet));
		pDest->NumberOfSets=pSource->NumberOfSets;
		pDest->AllocatedSets=pSource->AllocatedSets;
		for(count=0;count<pSource->NumberOfSets;count++)
		{
			pDest->pSet[count] = pSource->pSet[count];
		}
		return true;
	}
	else
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_Copy3D2DPoints() pSource or pDest is NULL");
		k_EmptyString(&str);
		return false;
	}
}

unsigned int k_GetTotal3D2DPointSetsInUse(const T3D2DPoints* pInfo)
{
	unsigned int count, TotalSetsInUse=0;
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if ((pInfo->pSet[count].Pnt2DInUse==true) && 
			(pInfo->pSet[count].Pnt3DInUse==true))
		{
			TotalSetsInUse++;
		}
	}
	return TotalSetsInUse;
}

unsigned int k_GetTotal2DPointsOnlyInUse(const T3D2DPoints* pInfo)
{
	unsigned int count, TotalInUse=0;
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if ((pInfo->pSet[count].Pnt2DInUse==true) && 
			(pInfo->pSet[count].Pnt3DInUse==false))
		{
			TotalInUse++;
		}
	}
	return TotalInUse;
}

unsigned int k_GetTotal3DPointsOnlyInUse(const T3D2DPoints* pInfo)
{
	unsigned int count, TotalInUse=0;
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if ((pInfo->pSet[count].Pnt2DInUse==false) && 
			(pInfo->pSet[count].Pnt3DInUse==true))
		{
			TotalInUse++;
		}
	}
	return TotalInUse;
}

bool k_SetPoint2DIn3D2DPoints(const T2DFloat* pPnt2D, unsigned int Index, T3D2DPoints* pInfo)
{
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_SetPoint2DIn3D2DPoints() pSource or pDest is NULL");
		k_EmptyString(&str);
		return false;
	}
	else if (Index>=pInfo->NumberOfSets)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_SetPoint2DIn3D2DPoints() Index (%d) out of range",Index);
		k_EmptyString(&str);
		return false;
	}
	else
	{
		pInfo->pSet[Index].Pnt2D=(*pPnt2D);
		pInfo->pSet[Index].Pnt2DInUse=true;
		return true;
	}
}

bool k_SetPoint3DIn3D2DPoints(const T3DFloat* pPnt3D, unsigned int Index, T3D2DPoints* pInfo)
{
	if (pInfo==NULL)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_SetPoint3DIn3D2DPoints() pSource or pDest is NULL");
		k_EmptyString(&str);
		return false;
	}
	else if (Index>=pInfo->NumberOfSets)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_SetPoint3DIn3D2DPoints() Index (%d) out of range",Index);
		k_EmptyString(&str);
		return false;
	}
	else
	{
		pInfo->pSet[Index].Pnt3D=(*pPnt3D);
		pInfo->pSet[Index].Pnt3DInUse=true;
		return true;
	}
}

bool k_GetIndexIn3D2DPoints(unsigned int* pIndex, int Id, const T3D2DPoints* pInfo)
{
	unsigned int count;
	for(count=0; count<pInfo->NumberOfSets; count++)
	{
		if (pInfo->pSet[count].IdInUse==true)
		{
			if (Id==pInfo->pSet[count].Id)
			{
				*pIndex=count;
				return true;
			}
		}
	}
	/* if we end up here, no set was found with "Id" */
	return false;

}

bool k_Load3D2DPoints(const char* PathAndFileName, T3D2DPoints* pInfo)
{
	bool returnValue;
	FILE* fp;
	char* Path=NULL,*FileNameExt=NULL,*Ext=NULL;
	TString str;
	k_InitString(&str);
	if (!k_SplitFileName(PathAndFileName, &Path,&FileNameExt,&Ext))
	{
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Filename not valid");
		k_EmptyString(&str);
		return false;
	}
	else if (strcmp(Ext,"")==0)
	{
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() No extension found");
		k_EmptyString(&str);
		returnValue=false;
	}
	else
	{
		returnValue=true;
		fp=fopen(PathAndFileName,"rb"); /* open file */
		if (fp==NULL)
		{
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Could not open file");
			returnValue=false;
		}
		else
		{
			/* read from file */
			bool NumberOfSetsFound=false;
			char c;
			unsigned int i=0;
			k_Empty3D2DPoints(pInfo);
			k_SkipWhiteSpace(fp);
			while (((c=fgetc(fp))!=EOF) && (returnValue==true))
			{
				ungetc(c,fp);
				if (c=='#')
				{
					k_SkipLine(fp);
				}
				else /* it must be a token then! */
				{
					char* Token;
					if (k_ReadToken(fp,&Token)==false)
					{
						k_EmptyString(&str);
						k_AddFileAndLine(str);
						k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Failed reading token");
						returnValue=false;
					}
					else
					{
						k_StringToUpper(Token);
						if (strcmp(Token,"NUMBEROFSETS")==0)
						{
							NumberOfSetsFound=true;
							if (fscanf(fp,"%d",&pInfo->NumberOfSets)!=1)
							{
								k_EmptyString(&str);
								k_AddFileAndLine(str);
								k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Failed reading number of sets");
								returnValue=false;
							}
							k_Alloc3D2DPoints(pInfo,pInfo->NumberOfSets);
							/* started reading each set */
							for(i=0; i<pInfo->AllocatedSets; i++)
							{
								int Error;
								k_SkipWhiteSpace(fp);
								Error=fscanf(fp,"Id= %d 3D-pnt= (%g,%g,%g) 2D-pnt= (%g,%g)  ",&pInfo->pSet[i].Id,
									&pInfo->pSet[i].Pnt3D.x,&pInfo->pSet[i].Pnt3D.y,&pInfo->pSet[i].Pnt3D.z,
									&pInfo->pSet[i].Pnt2D.x,&pInfo->pSet[i].Pnt2D.y);
								if ((Error==EOF) || (Error!=6))
								{
									k_EmptyString(&str);
									k_AddFileAndLine(str);
									k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Missing values in one of the pointsets");
									returnValue=false;
								}
								free(Token);
								/* read IDInUse */
								if (k_ReadToken(fp,&Token)==false)
								{
									k_EmptyString(&str);
									k_AddFileAndLine(str);
									k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Failed reading token IdInUse");
									returnValue=false;
								}
								else
								{
									k_StringToUpper(Token);
									if (strcmp(Token,"IDINUSE=YES")==0)
										pInfo->pSet[i].IdInUse=true;
									else
										pInfo->pSet[i].IdInUse=false;
								}
								free(Token);
								/* read Pnt3DInUse */
								if (k_ReadToken(fp,&Token)==false)
								{
									k_EmptyString(&str);
									k_AddFileAndLine(str);
									k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Failed reading token Pnt3DInUse");
									returnValue=false;
								}
								else
								{
									k_StringToUpper(Token);
									if (strcmp(Token,"PNT3DINUSE=YES")==0)
										pInfo->pSet[i].Pnt3DInUse=true;
									else
										pInfo->pSet[i].Pnt3DInUse=false;
								}
								free(Token);
								/* read Pnt2DInUse */
								if (k_ReadToken(fp,&Token)==false)
								{
									k_EmptyString(&str);
									k_AddFileAndLine(str);
									k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Failed reading token Pnt2DInUse");
									returnValue=false;
								}
								else
								{
									k_StringToUpper(Token);
									if (strcmp(Token,"PNT2DINUSE=YES")==0)
										pInfo->pSet[i].Pnt2DInUse=true;
									else
										pInfo->pSet[i].Pnt2DInUse=false;
								}
							}
							pInfo->NumberOfSets=pInfo->AllocatedSets;
						}
						free(Token);
					}
				}
				k_SkipWhiteSpace(fp);
			}
			if (NumberOfSetsFound==false)
			{
				k_EmptyString(&str);
				k_AddFileAndLine(str);
				k_ShowMessage(IPL_ERROR,&str,"k_Load3D2DPoints() Tokens NumberOfSets not found");
				returnValue=false;
			}
		}
	}
	k_EmptyString(&str);
	free(Path);
	free(FileNameExt);
	free(Ext);
	return returnValue;
}

bool k_Save3D2DPoints(const char* PathAndFileName, T3D2DPoints* pInfo)
{
	bool returnValue;
	FILE* fp;
	char* Path=NULL,*FileNameExt=NULL,*Ext=NULL;
	if (!k_SplitFileName(PathAndFileName, &Path,&FileNameExt,&Ext))
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_Save3D2DPoints() Filename not valid");
		k_EmptyString(&str);
		return false;
	}
	else if (strcmp(Ext,"")==0)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_Save3D2DPoints() No extension found");
		k_EmptyString(&str);
		returnValue=false;
	}
	else
	{
		returnValue=true;
		k_StringToUpper(Ext);
		fp=fopen(PathAndFileName,"wb"); /* open file */
		if (fp==NULL)
		{
			TString str;
			k_InitString(&str);
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_ERROR,&str,"k_Save3D2DPoints() Could not save file");
			k_EmptyString(&str);
			returnValue=false;
		}
		else if (pInfo->NumberOfSets==0)
		{
			TString str;
			k_InitString(&str);
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_ERROR,&str,"k_Save3D2DPoints() No points in set - cannot save");
			k_EmptyString(&str);
			returnValue=false;
		}
		else
		{
			unsigned int i;
			/* Save point set */
			fprintf(fp,"# Point sets data file written by the kernel CCorresponding3D2DPoints class from IPL98\n\n");
			fprintf(fp,"NumberOfSets %d\n\n", pInfo->NumberOfSets);
			for(i=0; i<pInfo->NumberOfSets; i++)
			{
				fprintf(fp, "Id= %d 3D-pnt= (%g,%g,%g) 2D-pnt= (%g,%g)  ",pInfo->pSet[i].Id,pInfo->pSet[i].Pnt3D.x,
					pInfo->pSet[i].Pnt3D.y,pInfo->pSet[i].Pnt3D.z,pInfo->pSet[i].Pnt2D.x,pInfo->pSet[i].Pnt2D.y);
				if (pInfo->pSet[i].IdInUse==true)
				{
					fprintf(fp, "IdInUse=YES ",pInfo->pSet[i].Id);
				}
				else
				{
					fprintf(fp,"IdInUse=NO ");
				}
				if (pInfo->pSet[i].Pnt3DInUse==true)
				{
					fprintf(fp,"Pnt3DInUse=YES ");
				}
				else
				{
					fprintf(fp,"Pnt3DInUse=NO ");
				}
				if (pInfo->pSet[i].Pnt2DInUse==true)
				{
					fprintf(fp,"Pnt2DInUse=YES");
				}
				else
				{
					fprintf(fp,"Pnt2DInUse=NO");
				}
				fprintf(fp,"\n");
			}
		}
		if (fp!=NULL)
		{
			fclose(fp);
		}
	}
	free(Path);
	free(FileNameExt);
	free(Ext);
	return returnValue;
}

void k_Print3D2DPoints(const T3D2DPoints* pInfo)
{
	printf("*********** Corresponding 3D-2D points: ***********\n");
	if (pInfo->NumberOfSets==0)
	{
		printf(" no points - empty structure\n");
	}
	else
	{
		unsigned int count;
		printf(" Point sets inserted: %d  Point sets allocated: %d\n",pInfo->NumberOfSets,pInfo->AllocatedSets);
		for(count=0; count<pInfo->NumberOfSets; count++)
		{
			printf(" %d) ",count);
			if (pInfo->pSet[count].Pnt3DInUse==true)
			{
				printf(" 3D pnt = (%g,%g,%g)",pInfo->pSet[count].Pnt3D.x,
						pInfo->pSet[count].Pnt3D.y,pInfo->pSet[count].Pnt3D.z);
			}
			else
			{
				printf(" 3D pnt = not in use");
			}
			if (pInfo->pSet[count].Pnt2DInUse==true)
			{
				printf(" 2D pnt = (%g,%g)",pInfo->pSet[count].Pnt2D.x,
						pInfo->pSet[count].Pnt2D.y);
			}
			else
			{
				printf(" 2D pnt = not in use");
			}
			if (pInfo->pSet[count].IdInUse==true)
			{
				printf(" Id = %d",pInfo->pSet[count].Id);
			}
			else
			{
				printf(" Id = not in use");
			}
			printf("\n");
		}
	}
}


#ifdef _IPL98_USING_CPP
} /* end of extern "C" */
} /* end namespace ipl */
#endif
