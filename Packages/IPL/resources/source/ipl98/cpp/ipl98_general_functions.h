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

#ifndef _IPL98_GENERAL_FUNCTIONS_H
#define _IPL98_GENERAL_FUNCTIONS_H

#include <math.h>
#include <istream>
#include<limits>
#include <ctype.h>

namespace ipl{ // namespace ipl ~ General Functions

using std::istream;
using std::string;
using std::numeric_limits;

/** \defgroup cpp_globals IPL98 Global C++ only constants and template functions.
    @{ */
/** \defgroup constants IPL98 Constants (global)
    @{ */
/** Define PI with machine hardware precision (global constant) */
#ifndef PI
const double PI = acos(-1);
#endif
/** Define 2*PI with machine hardware precision (global constant) */
#ifndef PI2
const double PI2 = 2*PI;
#endif
/**@}*/ /* end group "constants" */

/** \defgroup templates IPL98 Template functions (global)
	\verbatim
	#include <ipl98/cpp/ipl98_general_functions.h>
	\endverbatim
	Basic small template functions which may be usefull everywhere.
	@version 0.1,  last updated 1/10/1999
	@author René Dencker Eriksen edr@mip.sdu.dk
    @{ */


/** Conversion from Radians to Degrees (global constant) */
template <class TYPE>
inline
double RadToDegree(TYPE &Rad)
{
	return (180.0/PI)*Rad;
}

/** Conversion from Degrees to Radians (global constant) */
template <class TYPE>
inline
double DegreeToRad(TYPE& Degree)
{
	return (PI/180.0)*Degree;
}

/** Calculate the square of given parameter value */
template <class TYPE>
inline
TYPE Sqr(const TYPE &x)
{
  return (x*x);
}

/** Swap the values - copy x value to y and copy y value to x */
template <class TYPE>
inline
void Swap(TYPE &x,TYPE &y)
{
  TYPE t = x;
  x = y;
  y = t;
}

/** Get the maximum value of x and y */
template <class TYPE>
inline
TYPE Max(const TYPE x, const TYPE y)
{
  return ((x>y) ? x : y);
}

/** Get the minimum value of x and y */
template <class TYPE>
inline
TYPE Min(const TYPE	&x,	const TYPE	&y)
{
  return ((x<y) ? x : y);
}

/** Round x to nearest integer value */
template <class TYPE>
inline
int Round(const TYPE &x)
{
  return ((x<0) ? (int)(x-0.5) : (int)(x+0.5));
}

/** Round x to nearest UINT8 value, or if x>255 then x=255, or
	if x<0 then x=0 */
template <class TYPE>
inline
unsigned char RoundUINT8(const TYPE	&x)
{
  return ((x<0) ? 0 : (x>255) ? 255 : (UINT8)(x+0.5));
}

/**@}*/ /* end group "templates" */

/** Streaming operator for a bool on an istream. The
	way IPL98 classes are built, we need this functionality
	for types used in the template based container classes such
	as CArray2D and CArrayOS2D. This may be changed later!
	@version 0.1
	@author Rene Dencker Eriksen (edr@mip.sdu.dk) */
istream& operator<<(bool b, istream& s);

/** Splits a file name including path given in "FilePathName" into
	a path (returned in "Path") and a filename including extension
	(returned in "FileNameExt") and an extension (returned in "Ext").
	@return False in these cases:
		FilePathName==NULL or it is an empty string (produce an error message)
		FilePathName ends with the character '/' or '\' (produce an error message) */
bool SplitFileName(const char* pFilePathName, string& Path, string& FileNameExt, string& Ext);

/** Converts all back slash characters '\' to slash '/'. Used to avoid problems
	with C++ reading a '\' path seperation as an escape character.
	@param Path Path to be converted, resultint string returned in this parameter.
	@version 0.8 */
bool ConvertBackslashToSlash(char* Path);

/** Adds a trailing '/' character to the path if not present.
	@return False, if Path is an empty string.
	@version 0.8 */
bool AddTrailingSlashToPath(string& Path);

/** used for in streams. Skips all whitespace, newline, tab characters and
	comment lines, i.e. rest of line from a '#' character.
	@version 0.8 */
inline 
void SkipSpaceAndComments(istream& s)
{
	while(isspace(s.peek()))
		s.get();
	while (s.peek()=='#')
	{
		s.ignore(std::numeric_limits<int>::max(),'\n');
		while (isspace(s.peek()))
			s.get();
	}
}

/** Converts all characters in str to upper case by calling std::toupper(char*)
	on each element in str. */
inline void ToUpperCase(string& str)
{
	string::iterator it=str.begin();
	while(it!=str.end())
	{
		*it=toupper(*it);
		++it;
	}
}

/** Compares two strings case insensitive. Return values are like the ANSI cmp function:
	-1 if s<s2, 0 if s==s2 or 1 if s>s2. */
int CompareNoCase(const string& s, const string& s2);

/**@}*/ /* end group "cpp_globals" */

} // end namespace ipl


#endif /* _IPL98_GENERAL_FUNCTIONS_H */
