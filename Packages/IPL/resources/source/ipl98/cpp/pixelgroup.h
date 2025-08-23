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

#ifndef _IPL98_PIXELGROUP_H
#define _IPL98_PIXELGROUP_H

#include "../ipl98_setup.h" /* always include the setup file */
#include "image.h"
#include "std_image.h"
#include "../kernel_c/kernel_pixelgroup.h"
#include "pixelgroup_it.h"
#include "pixelgroup_const_it.h"
#include <sstream>

namespace ipl{ // use namespace ipl

using std::ostringstream;

/** CPixelGroup, contains a group of pixels, it can optionally contain color
	information for each position, last updated 1/25/2002. One example of use
	is segmentation algorithms. The simple blob-algorithm
	found in the CSegmentate class uses several CPixelGroup objects to store
	the found segments in. The class CPixelGroups is used to keep track of many
	CPixelGroup objects. A template based group holding positions is also available,
	see CPositionGroup2D for more information.

	This class has two iterators: ConstIterator and Iterator. They work like the iterators
	in the C++ std-library, so if you are familiar with them, these are very easy to use.
	Here is an example:
	\verbatim
	CPixelGroup Grp;
	// Fill some pixels in the Grp object...

	// Search whole group for given positions
	// this could be done by calling PosInGroup(), but to demonstrate
	// the iterator class, we will do it this way
	CPoint2D<INT16> P(1500,388); // just a random position
	CPixelGroup::ConstIterator It;
	// iterating whole group with the ConstIterator class
	for(It=Grp.Begin();It<Grp.End();It++)
	{
		// The internal representation of positions in a CPixelGroup is
		// stored in a C struct T2DInt, but functions are available for
		// comparing CPoint2D<INT16> with these T2DInt, so no time consuming
		// conversion is needed. It means that the comparison 
		// '((P.GetX()==It->x) && (P.GetY()==It->y))' is not faster than 
		// 'P==*t', even though the last comparison is two different types.
		if (P==*It)
		{
			cout << "Found P" << endl;
			// If you explicitly need to convert the iterator
			// value to a CPoint2D<INT16>, the method ToCPoint2D() can do it
			cout << It.ToCPoint2D() << endl;
		}

	}
	// Doing the same without the iterator is considerably slower.
	// On a PENTIUM III with Visual C++ 6.0 it is about a factor 4 slower.
	for(int i=0; i<Grp.GetTotalPositions(); i++)
	{
		if (P==Grp.GetPosition(i))
			cout << "Found P" << endl;
	}

	\endverbatim

	For more details, see CPixelGroupIterator and CPixelGroupConstIterator
	classes.

	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CPixelGroup ipl98/cpp/pixelgroup.h
	@see CPixelGroups
	@see CPositionGroup2D
	@see CPositionGroupIterator
	@see CPositionGroupConstIterator
	@version 1.60,  by edr@mip.sdu.dk
	@author René Dencker Eriksen */

class CPixelGroup {
	public: // attributes
	private: // attributes
		TPixelGroup* m_pGroup;
		bool m_OwnGroup; // if true, the class contains its own TPixelGroup and must
						// remember to deallocate the memory when destructing
	public: // methods
		/// default constructor
		CPixelGroup();
		/** Constructor allocating memory for pixel positions to be contained in this class.
			To make insertions fast, call this funcion with a value in InitialSize
			greater than the expected pixels in the group.
			@param InitialSize Number of positions to allocate memory for.
			@param AllocateColors If true, a color array is also allocated, defaults to false.
			Must be 1 or greater. */
		CPixelGroup(unsigned int InitialSize, bool AllocateColors=false);
		// constructor which takes an external TGroup as reference to data,
		// in this case, the class does not deallocate memory for the TPixelGroup pointet
		// to by m_pGroup.
		CPixelGroup(TPixelGroup& TGroup);
		/** copy constructor 
			@param SourceGroup Group to copy into this group */
		CPixelGroup(const CPixelGroup& SourceGroup);
		/** overloading of assignment operator, deletes old pixel positions in destination.
			Also deletes the color values if available. Calls the kernel function k_CopyGroup(). */
		CPixelGroup& operator=(const CPixelGroup& SourceGroup);
		/** overloading of []-operator. Returns the position at Index, no range
			check, fast access. Note, this operator returns a T2DInt kernel C structure to avoid
			allocation of a CPoint2D<INT16> as in GetPosition() and hence make the access faster.
			The T2DInt structure contains attributes x and y of type INT16.
			@see GetPosition */
		T2DInt operator[](unsigned int Index);
		/// default destructor
		~CPixelGroup();
		/** Sets all members to 0 and deallocates memory */
		void Empty();
		/** Iterator for the CPixelGroup class. This typedef is included to make
			the class work like the std library. Instantiate an iterator object
			like this:
			\verbatim
			CPixelGroup::Iterator it;
			\endverbatim */
		typedef CPixelGroupIterator Iterator;
		/** ConstIterator for the CPixelGroup class. This typedef is included to make
			the class work like the std library. Instantiate an iterator object
			like this:
			\verbatim
			CPixelGroup::ConstIterator it;
			\endverbatim */
		typedef CPixelGroupConstIterator ConstIterator;
		/** Returns an iterator to the last element plus one.
		@return Last element plus one. */
		inline Iterator End(){return Iterator(m_pGroup->pPos+m_pGroup->NumberOfPixels);}
		/** Returns an iterator to the first element.
		@return First element. */
		inline Iterator Begin(){return Iterator(m_pGroup->pPos);}
		/** Get position with lowest y-value in group.
			@return Top position in group. */
		CPoint2D<int> GetTop() const;
		/** Get position with highest y-value in group.
			@return Bottom position in group. */
		CPoint2D<int> GetBottom() const;
		/** Get position with lowest x-value in group.
			@return Leftmost position in group. */
		CPoint2D<int> GetLeft() const;
		/** Get position with highest x-value in group.
			@return Rightmost position in group. */
		CPoint2D<int> GetRight() const;
		/** Get number of positions stored in the group. To iterate through
			all positions in the group use indexes from 0 to GetTotalPostitions()-1.
			@return Total number of positions. */
		inline unsigned int GetTotalPositions() const;
		/** Returns the width of this group. Note: Uses the boundary information,
			be sure they are updated. They are only invalid if you have used the
			fast methods, such as AddPositionFast().
			@return Width of group. */
		inline unsigned int GetWidth() const;
		/** Returns the height of this group. Note: Uses the boundary information,
			be sure they are updated. They are only invalid if you have used the
			fast methods, such as AddPositionFast().
			@return Height of group. */
		inline unsigned int GetHeight() const;
		/** Returns the color type, HIGHCOLOR if the group is derived from high color pixels
			otherwise the value is LOWCOLOR. This value may not be used by all segmentation
			algorithms.
			@return The color type from which the positions were derived. */
		COLORTYPE GetColorType() const;
		/** Returns the position stored at "Index" in the group. Maximum index is
			GetTotalPostitions()-1.
			@return Position at given index, returns (0,0) if Index is out of range. */
		inline CPoint2D<INT16> GetPosition(unsigned int Index) const;
		/** Returns the color corresponding to the position stored at "Index" in the group.
			Maximum index is GetTotalPostitions()-1. There may not be any colors stored
			in the group, use ColorsAvailable() to check this. For faster access consider
			using the operator[].
			@return Position at given index, returns 0 if index is out of range
				or if colors are unavailable.
			@see operator[] */
		inline UINT32 GetColor(unsigned int Index) const;
		/** Sets the color ColorValue corresponding to the position stored at "Index" in
			the group. Maximum index is GetTotalPostitions()-1. There may not be any
			colors stored in the group, use ColorsAvailable() to check this.
			@return False, if index is out of range or if colors are unavailable. */
		inline bool SetColor(UINT32 ColorValue, unsigned int Index);
		/** Use this method to check if colors are stored in the pixel group.
			@return True, if there are colors stored in the group. */
		bool ColorsAvailable() const;
		/** Reallocates memory for the positions contained in this class. If colors 
			are available the color array will also be adjusted. The new allocated
			memory is not initialised.
			@param NewSize The new number of positions to allocate memory for.
				Note: The NewSize may be less than the actual allocated memory! In that case
				the corresponding positions stored in the end of the actual memory are deleted. */
		void ReAllocPositions(unsigned int NewSize);
		/** Removes unused memory allocated for pixel positions in this class.
			If colors are available the color array will also be adjusted.
			Because memory allocation is a time consuming operation it is a good idea by each
			ReAllocPositions (or the CPixelGroup(unsigned int InitialSize) constructor) call to
			allocate a big number of pixels and then at the end of the construction of a
			CPixelGroup calling this AdjustSizeOfPositions() method to deallocate unused memory. */
		void AdjustSizeOfPositions();
		/** To use the kernel C functions it is sometimes necessary
			to pass the TPixelGroup structure.
			In other cases do not use this function to manipulate the 
			pixel group but use the methods in this class!
			@return pointer to pixel group data */
		const TPixelGroup* GetConstTPixelGroupPtr() const;
		/** To use the kernel C functions it is sometimes necessary
			to pass the TPixelGroup structure which contents will be changed.
			In other cases do not use this function to manipulate the 
			pixel group but use the methods in this class!
			@return pointer to pixel group data */
		TPixelGroup* GetTPixelGroupPtr();
		/* only used by the class CPixelGroups */
		void MoveTPixelGroupPtr(TPixelGroup* p);
		/** The position (x,y) is added to the group of pixels. If pixel colors are 
			present this function cannot be used. A call to RemoveColors() is then
			needed. The method AddColorsToGroup() can be called later to insert the 
			colors again if a source image is available. The boundary is updated if
			the new position is outside the old boundary.
			@param x Position in horisontal direction.
			@param y Position in vertical direction. 
			@return False, if colors are available, in that case the method does nothing.
			@see AddPositionFast */
		inline bool AddPosition(INT16 x, INT16 y);
		/**	Same as AddPosition(x,y), except the position is given in a CPoint2D object.
			@param Pos Position to add to PixelGroup.
			@see AddPositionFast */
		inline bool AddPosition(const CPoint2D<INT16>& Pos);
		/** Inserts the position (x,y) at given Index, which must be less than the
			inserted pixels (returned by GetTotalPositions()). The ordering of
			the positions is preserved. If pixel colors are present this function cannot
			be used. A call to RemoveColors() is then needed. The method AddColorsToGroup()
			can be called later to insert the colors again if a source image is available.
			The boundary is updated if the new position is outside the old boundary.
			@param x Position in horisontal direction.
			@param y Position in vertical direction.
			@param Index Index in the array of positions to be removed.
			@return False, if pixel colors are present or if Index is out of range.
			@see InsertPositionFast */
		bool InsertPosition(INT16 x, INT16 y, unsigned int Index);
		/** Same as InsertPosition(x,y,Index), except the position is given in a
			CPoint2D<INT16> type.
			@param Pos Position to add to the PixelGroup.
			@return False, if pixel colors are present or if Index is out of range.
			@see InsertPositionFast */
		bool InsertPosition(CPoint2D<INT16> Pos, unsigned int Index);
		/** Same as AddPosition(x,y), except a color value is also inserted.
			@param x Position in horisontal direction.
			@param y Position in vertical direction. 
			@return False, if colors are not available, in that case the method does nothing.
			@see AddPositionColorFast */
		inline bool AddPositionColor(INT16 x, INT16 y, UINT32 Color);
		/**	Same as AddPositionColor(x,y), except the position is given in a CPoint2D object.
			@param Pos Position to add to PixelGroup.
			@see AddPositionColorFast */
		inline bool AddPositionColor(const CPoint2D<INT16>& Pos, UINT32 Color);
		/** Same as InsertPosition(x,y), except a color value is also inserted.
			@param x Position in horisontal direction.
			@param y Position in vertical direction. 
			@return False, if colors are not available, in that case the method does nothing.
			@see InsertPositionColorFast */
		bool InsertPositionColor(INT16 x, INT16 y, UINT32 Color, unsigned int Index);
		/**	Same as InsertPositionColor(x,y), except the position is given in a CPoint2D object.
			@param Pos Position to add to PixelGroup.
			@return False, if colors are not available, in that case the method does nothing.
			@see AddPositionColorFast */
		bool InsertPositionColor(const CPoint2D<INT16>& Pos, UINT32 Color, unsigned int Index);
		/** Removes a position stored in the group at given index. Done by moving the
			last position in the pPos array contained in the m_pGroup (type TPixelGroup)
			to the index which is to be removed. If pixel colors are available, the color
			array is updated. The boundary is also updated if the removed position causes
			changes in the boundary.
			@param Index Index in the array of position to be removed.
			@return False, if Index is out of range.
			@see RemovePositionSlow */
		bool RemovePosition(unsigned int Index);
		/** Same as RemovePosition, but the ordering of the pixels is preserved.
			This method is slower than RemovePosition.
			@param Index Index in the array of position to be removed.
			@return False, if Index is out of range.
			@see RemovePosition */
		bool RemovePositionSlow(unsigned int Index);
		/** Removes duplicates of same position in this pixelgroup. The algorithm could
			probably be more efficient but it is still nice to have this functionality.
			To make it a bit efficient though, the order of the positions is not preserved, i.e.
			the same code as RemovePosition is used to remove positions, but no update of
			boundary is neccesary.
			@return Total number of duplicate positions removed. */
		unsigned int RemoveDuplicates();
		/** Allocates cells for color values but does not initialize the values.
			Faster than using AllocAndInitColors(). Note: If you later on call AddPosition()
			or InsertPosition() without adding a color, memory for previous allocated colors
			are deleted since the number of allocated colors does not equal number of positions.
			The class takes care of it.
			@return False, if colors are allready available.
			@see AllocAndInitColors */
		bool AllocColors();
		/** Same as AllocColors but here the initial value of the allocated
			cells can be specified. Note: If you later on call AddPosition()
			or InsertPosition() without adding a color, memory for previous allocated colors
			are deleted since the number of allocated colors does not equal number of positions.
			The class takes care of it.
			@param InitialValue Initial value of allocated colors.
			@return False, if colors are allready available.
			@see AllocColors */
		bool AllocAndInitColors(UINT32 InitialValue);
		/**	Get the original pixel colors from the inserted pixels and given source image and
			insert them into the PixelGroup. Note: If you later on call AddPosition()
			or InsertPosition() without adding a color, memory for previous allocated colors
			are deleted since the number of allocated colors does not equal number of positions.
			The class takes care of it.
			@param pSource Image to get the original pixel values from. The PixelGroups positions
				must be derived from this image.
			@return False if the PixelGroup has no pixels in it, colors have already been added
				or one of the parameters is a NULL pointer. */
		bool AddColors(const CStdImage& Img);
		/** Removes colors stored in the m_pGroup member attribute. If no colors are present,
			the method just returns without doing anything. */
		void RemoveColors();
		/** Copies a pixel group to a new image. Origo of the new image is set to (-Left.x,-Top.y)
			which is the pixelgroups top left boundary. There are three cases which decides the
			bit depth of the output image: 1) No colors available (i.e. the method
			AddColors() has not been called), then a black and white image with
			1 b/p is produced and the positions are plotted in the image according to the
			"Color" member of the TPixelGroup-structure. If the Color-type is undefined
			the default is a white background with black pixels set at the given
			positions. 2) Colors available but no palette is given (i.e. Palette is a NULL
			pointer), then an image with a graytone palette is produced if the Bits pixel
			depth member of CPixelGroup is 1 or 8. If the pixel depts is 24 b/p
			an image with 24 b/p without a palette is produced. 3) Colors available and
			a palette is provided. An image with pixel depth given in CPixelGroup and the given
			palette is produced. The pallette must correspond with the pixel depth in the
			TPixelGroup, otherwise an error message will be produced.
			@param pPalette The pallette to be used in the new image. If no colors are available
				or the pixel depth is 24 b/p this parameter is ignored. If the parameter is NULL
				a default palette is used (see case 2 above).
			@param BackGround The background color of new image, the user must be sure that
				the value in case of 1 or 8 b/p is in the range of the palette index and in
				case of 24 b/p the value must be the RGB color.
			@param Dest Image to copy the group to. All previous information in Dest is
				destroyed.
			@return False, if the pixel group is empty. */
		bool CopyToImage(const CPalette* pPalette, UINT32 BackGround, CStdImage& Dest);
		/** Adds the points in PixelGroup to the already allocated image, only the positions contained
			in the pixelgroup will affect the image. Positions outside image are ignored. If the
			pixelgroup contains color values they can be used as plotting values by calling
			the method AddColorsToImage(CStdImage& Dest) instead. The method automaically does the
			copying as fast as possible by doing some range checks before entering the inner loops.
			@param Dest Image to plot points in, only pixels at positions contained in pixelgroup
				will affect the image.
			@param Color A UINT32 value containing the color, in case of a palette it is the index
				in the palette. If the group contains colors, you can use them by calling
				AddToImage(CStdImage& Dest) instead of this function.
			@return True, always when using this C++ version of the algorithm. */
		bool AddToImage(CStdImage& Dest, UINT32 Color);
		/** Adds the points in PixelGroup to the already allocated image, only the positions
			contained in the pixelgroup will affect the image. Positions outside image are ignored.
			The color values in the pixelgroup are used when inserting postitions, if you want
			the positions plotted with a constant color call the method 
			AddToImage(CStdImage& Dest, UINT32 Color). Ensure that the bit depth (and palette if
			present) complies with the color values in the pixelgroup. The method will not do any
			tests for that. The function automaically does the copying as fast as possible by
			doing some range checks before entering the inner loops.
			@param Dest Image to plot points in, only pixels at positions contained in pixelgroup
				will affect the image.
			@return False, if pPixelgroup is NULL.
			@see True, always when using this C++ version of the algorithm. */
		bool AddToImage(CStdImage& Dest);
		/**	Tests if given position is included in the PixelGroup
			@param Pos Position to test for.
			@param Index If the position "Pos" is found, the Index of the position is returned
				in this parameter. If not found, the parameter is unchanged.
			@return true if the position was found, false if not found. */
		bool PosInGroup(const CPoint2D<INT16>& Pos,unsigned int& Index);
		/** Same as PosInGroup, except the position is given as two INT16
			values (x,y).
			@return true if the position was found, false if not found. */
		bool PosInGroup(INT16 x, INT16 y,unsigned int& Index);
		/**	Tests if given position is included in the PixelGroup. If you want
			the index with the position returned, see 
			PosInGroup(const CPoint2D<INT16>& Pos,unsigned int& Index).
			@param Pos Position to test for.
			@return true if the position was found, false if not found. */
		bool PosInGroup(const CPoint2D<INT16>& Pos);
		/** Same as PosInGroup(Pos), except the position is given as two INT16
			values (x,y).
			@return true if the position was found, false if not found. */
		bool PosInGroup(INT16 x, INT16 y);
		/**	Prints the information contained in the PixelGroup to stdout.
			@param PrintPositions If true, all pixel positions stored in the PixelGroup are written
				to stdout.
			@param PosPrLine Number of positions to be written on each line
				(defaults to 5). Only used if PrintPositions is true.*/
		void PrintInfo(bool PrintPositions,unsigned int PosPrLine=5);
		/** writes all the pixel group information to stream */
		friend ostream& operator<<(ostream& s,const CPixelGroup& Group);
		
		/** Runs through all positions in the group and update the left/right/top/bottom
			boundaries, this is usefull if you have used the fast methods which do not
			update boundary values. */
		void UpdateBoundaries();

		/** @name Fast functions, no updating of boundaries! */
		//@{
		/** Same as RemovePosition, except that there is no range check for
			given index and the boundary is not	updated and hence the function is a
			lot faster.
			@return True, always.
			@see RemovePosition */
		inline bool RemovePositionFast(unsigned int Index);
		
		/**	Same as AddPosition, except the boundary is not updated. It is not checked 
			if the colors are available, i.e. it is not legal later on to access the colors
			eventhough they seem to be available! You can manually later on call RemoveColors()
			and AllocColors() to update the array, but earlier values will be lost.
			@param x Position in horisontal direction.
			@param y Position in vertical direction.
			@see AddPosition */
		inline void AddPositionFast(INT16 x, INT16 y);

		/**	Same as AddPositionFast, except the position is given in a
			CPoint2D<INT16> type.
			@param Pos Position to add to PixelGroup
			@see AddPositionFast */
		inline void AddPositionFast(const CPoint2D<INT16>& Pos);

		/** Same as InsertPosition, except that there is no range check for
			given index and if colors are available it is ignored, the function
			simply inserts the position without referencing the color.
			@param x Position in horisontal direction.
			@param y Position in vertical direction.
			@param Index Index in the array of positions to be removed.
			@return True, always.
			@see InsertPosition */
		inline bool InsertPositionFast(INT16 x, INT16 y, unsigned int Index);

		/** Same as InsertPositionFast, except the position is given in a CPoint2D<INT16> type.
			@param Pos Position to add to PixelGroup.
			@return True, always.
			@see InsertPositionFast */
		inline bool InsertPositionFast(CPoint2D<INT16> Pos, unsigned int Index);

		/** Same as AddPositionFast, except a color value is also inserted.
			@param x Position in horisontal direction.
			@param y Position in vertical direction. 
			@see AddPositionFast */
		inline void AddPositionColorFast(INT16 x, INT16 y, UINT32 Color);
		/**	Same as AddPositionColorFast(x,y), except the position is given in a CPoint2D object.
			@param Pos Position to add to PixelGroup.
			@see AddPositionFast */
		inline void AddPositionColorFast(const CPoint2D<INT16>& Pos, UINT32 Color);
		/** Same as InsertPosition(x,y), except a color value is also inserted.
			@param x Position in horisontal direction.
			@param y Position in vertical direction. 
			@return True, always.
			@see InsertPositionColorFast */
		inline bool InsertPositionColorFast(INT16 x, INT16 y, UINT32 Color, unsigned int Index);
		/**	Same as InsertPositionColor(x,y), except the position is given in a CPoint2D object.
			@param Pos Position to add to PixelGroup.
			@return True, always.
			@see AddPositionColorFast */
		inline bool InsertPositionColorFast(const CPoint2D<INT16>& Pos, UINT32 Color, unsigned int Index);
		/** Adds an offset to all points in group. Boundaries are updated.
			@param Offset The offset value to be added to all positions.
			@return False, if the group is empty. */
		bool AddOffset(const CPoint2D<INT16>& Offset);
		//@}

};

/////////////////////////////////////////////////
//// Inline methods
/////////////////////////////////////////////////

inline T2DInt CPixelGroup::operator[](unsigned int Index)
{
	return m_pGroup->pPos[Index];
}

inline unsigned int CPixelGroup::GetTotalPositions() const
{
	return m_pGroup->NumberOfPixels;
}

inline unsigned int CPixelGroup::GetWidth() const
{
	return m_pGroup->Right.x-m_pGroup->Left.x+1;
}

inline unsigned int CPixelGroup::GetHeight() const
{
	return m_pGroup->Bottom.y-m_pGroup->Top.y+1;
}

inline CPoint2D<INT16> CPixelGroup::GetPosition(unsigned int Index) const
{
	if (Index<m_pGroup->NumberOfPixels)
		return CPoint2D<INT16>(m_pGroup->pPos[Index].x,m_pGroup->pPos[Index].y);
	else
	{
		ostringstream ost;
		ost << "CPixelGroup::GetPosition() Index(" << Index << ") out of range" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<INT16>(0,0);
	}
}

inline UINT32 CPixelGroup::GetColor(unsigned int Index) const
{
	if ((m_pGroup->pColor!=NULL) && (Index<m_pGroup->NumberOfPixels))
		return m_pGroup->pColor[Index];
	else
	{
		ostringstream ost;
		ost << "CPixelGroup::GetColor() Index(" << Index << ") out of range or colors not available" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return 0;
	}
}

inline bool CPixelGroup::SetColor(UINT32 ColorValue, unsigned int Index)
{
	if ((m_pGroup->pColor!=NULL) && (Index<m_pGroup->NumberOfPixels))
	{
		m_pGroup->pColor[Index]=ColorValue;
		return true;
	}
	else
	{
		ostringstream ost;
		ost << "CPixelGroup::SetColor() Index(" << Index << ") out of range or colors not available" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
}

inline bool CPixelGroup::AddPosition(INT16 x, INT16 y)
{
	if (k_AddPosToGroup(x,y,m_pGroup)!=true)
	{
		ostringstream ost;
		ost << "CPixelGroup::AddPosition() Colors available, cannot insert position only" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
		return true;
}

inline bool CPixelGroup::AddPosition(const CPoint2D<INT16>& Pos)
{
	if (k_AddPosToGroup(Pos.GetX(),Pos.GetY(),m_pGroup)!=true)
	{
		ostringstream ost;
		ost << "CPixelGroup::AddPosition() Colors available, cannot insert position only" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
		return true;	
}

inline bool CPixelGroup::AddPositionColor(INT16 x, INT16 y, UINT32 Color)
{
	if (k_AddPosColorToGroup(x,y,Color,m_pGroup)!=true)
	{
		ostringstream ost;
		ost << "CPixelGroup::AddPositionColor() Colors not available" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
		return true;
}

inline bool CPixelGroup::AddPositionColor(const CPoint2D<INT16>& Pos,UINT32 Color)
{
	if (k_AddPosColorToGroup(Pos.GetX(),Pos.GetY(),Color,m_pGroup)!=true)
	{
		ostringstream ost;
		ost << "CPixelGroup::AddPositionColor() Colors not available" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
		return true;
}

inline bool CPixelGroup::RemovePositionFast(unsigned int Index)
{
	return k_RemovePosFromGroupFast(Index,m_pGroup);
}

inline void CPixelGroup::AddPositionFast(INT16 x, INT16 y)
{
	k_AddPosToGroupFast(x,y,m_pGroup);
}

inline void CPixelGroup::AddPositionFast(const CPoint2D<INT16>& Pos)
{
	k_AddPosToGroupFast(Pos.GetX(),Pos.GetY(),m_pGroup);
}

inline void CPixelGroup::AddPositionColorFast(INT16 x, INT16 y, UINT32 Color)
{
	k_AddPosColorToGroupFast(x,y,Color,m_pGroup);
}

inline void CPixelGroup::AddPositionColorFast(const CPoint2D<INT16>& Pos, UINT32 Color)
{
	k_AddPosColorToGroupFast(Pos.GetX(),Pos.GetY(),Color,m_pGroup);
}

inline bool CPixelGroup::InsertPositionFast(INT16 x, INT16 y, unsigned int Index)
{
	return k_InsertPosInGroupFast(x,y,Index,m_pGroup);
}

inline bool CPixelGroup::InsertPositionFast(CPoint2D<INT16> Pos, unsigned int Index)
{
	return k_InsertPosInGroupFast(Pos.GetX(),Pos.GetY(),Index,m_pGroup);
}

bool CPixelGroup::InsertPositionColorFast(INT16 x, INT16 y, UINT32 Color, unsigned int Index)
{
	return k_InsertPosColorInGroupFast(x,y,Color,Index,m_pGroup);
}

bool CPixelGroup::InsertPositionColorFast(const CPoint2D<INT16>& Pos, UINT32 Color, unsigned int Index)
{
	return k_InsertPosColorInGroupFast(Pos.GetX(),Pos.GetY(),Color,Index,m_pGroup);
}

} // end namespace ipl

#endif //_IPL98_PIXELGROUP_H
