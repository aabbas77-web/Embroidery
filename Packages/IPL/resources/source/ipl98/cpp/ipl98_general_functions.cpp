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

#include "ipl98_general_functions.h"
#include "../kernel_c/kernel_io.h"
#include "error.h"
#include <sstream>

namespace ipl{ // namespace ipl ~ General Functions

using std::ostringstream;

istream& operator<<(bool b, istream& s)
{
	s >> b;
	return s;
}

bool SplitFileName(const char* pFilePathName, string& Path, string& FileNameExt, string& Ext)
{
	bool ReturnValue=true;
	char *pPath=NULL, *pFileNameExt=NULL, *pExt=NULL;
	if (k_SplitFileName(pFilePathName,&pPath,&pFileNameExt,&pExt)==true)
	{
		Path.assign(pPath);
		FileNameExt.assign(pFileNameExt);
		Ext.assign(pExt);
	}
	else
	{
		ostringstream ost;
		ost << "SplitFileName() Failed splitting filename" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		ReturnValue=false;
	}
	if (pPath!=NULL)
		free(pPath);
	if (pFileNameExt!=NULL)
		free(pFileNameExt);
	if (pExt!=NULL)
		free(pExt);
	return ReturnValue;
}

bool ConvertBackslashToSlash(char* Path)
{
	char *c=Path;
	while(*c!='\0')
	{
		if (*c=='\\')
		{
			*c='/';
		}
		c++;
	}
	return true;
}

bool AddTrailingSlashToPath(string& Path)
{
	if (Path.size()==0)
		return false;
	if (Path.find_last_of('/')!=(Path.size()-1))
		Path += "/";
	return true;
}

int CompareNoCase(const string& s, const string& s2)
{
	string::const_iterator p=s.begin();
	string::const_iterator p2=s2.begin();
	while (p!=s.end() && p2!=s2.end())
	{
		if (toupper(*p)!=toupper(*p2)) return (toupper(*p)<toupper(*p2))? -1 : 1;
		++p;
		++p2;
	}
	return (s2.size()==s.size()) ? 0 : (s.size()<s2.size()) ? -1 : 1; // size is unsigned
}

} // end namespace ipl
