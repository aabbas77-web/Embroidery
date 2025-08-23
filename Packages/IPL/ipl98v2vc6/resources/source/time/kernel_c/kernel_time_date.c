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

#ifndef _KERNELTIMEDATE_C
#define _KERNELTIMEDATE_C

#include "kernel_time_date.h"
#include "../../ipl98/kernel_c/kernel_string.h"
#include "../../ipl98/kernel_c/kernel_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _IPL98_USING_CPP
using ipl::TString;
using ipl::k_InitString;
using ipl::k_ShowMessage;
using ipl::k_EmptyString;
using ipl::k_AddCharToString;
using ipl::k_AddCharArrayToString;
using ipl::IPL_ERROR;
#endif

int k_GetTime(char** Time)
{
	struct tm tp;
	time_t t;
	time(&t);
	tp = *localtime(&t);

	if (mktime(&tp)==-1)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_GetTime() Failed reading the time");
	    k_EmptyString(&str);
		return -1;
	}
	if (*Time!=NULL)
	{
		free(*Time);
	}
	*Time = (char*)malloc(9);
	strftime(*Time,9,"%H:%M:%S",&tp);
	return 1;
}

int k_GetDate(char** Date)
{
	struct tm tp;
	time_t t;
	time(&t);
	tp = *localtime(&t);

	if (*Date!=NULL)
	{
		free(*Date);
	}
	*Date = (char*)malloc(12);
	if (mktime(&tp)==-1)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_GetDate() Failed reading the time");
	    k_EmptyString(&str);
		return -1;
	}
	strftime(*Date,12,"%a %b %d",&tp);
	return 1;
}

int k_GetDateTimeYear(char** DTY)
{
	char* pStr;
	struct tm* tp;
	time_t t;
	time(&t);
	tp = localtime(&t);

	if (*DTY!=NULL)
	{
		free(*DTY);
	}
	*DTY = (char*)malloc(30);
	if (mktime(tp)==-1)
	{
		TString str;
		k_InitString(&str);
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"k_GetDateTimeYear() Failed reading the time");
	    k_EmptyString(&str);
		return -1;
	}
	pStr=asctime(tp);
	strcpy(*DTY,pStr);
	return 1;
}

clock_t k_StartTimer()
{
	return clock();
}

double k_GetTimer(clock_t StartValue)
{
	return (double)(clock()-StartValue)/CLOCKS_PER_SEC;
}

void k_SecondsToHMS(unsigned long Seconds, char** Time)
{
	ldiv_t hours = ldiv(Seconds,3600);
	ldiv_t minutes = ldiv(hours.rem,60);
	int seconds = minutes.rem;
	if (*Time!=NULL)
	{
		free(*Time);
	}	
	*Time = (char*)malloc(12);
	if (minutes.quot<10)
	{
		if (seconds<10)
		{
			sprintf(*Time,"%d:0%d:0%d",hours.quot,minutes.quot,seconds);
		}
		else
		{
			sprintf(*Time,"%d:0%d:%d",hours.quot,minutes.quot,seconds);
		}
	}
	else
	{
		sprintf(*Time,"%d:%d:%d",hours.quot,minutes.quot,seconds);
	}
}

#endif/*_KERNELTIMEDATE_C*/
