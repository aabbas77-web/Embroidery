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

using std::ios_base;
using std::setprecision;
using std::setiosflags;

template<class T> 
CPositionGroup2D<T>::CPositionGroup2D(const T& InitBoundaryVal)
{
	// constructor
	m_Right=InitBoundaryVal;
	m_Left=InitBoundaryVal;
	m_Bottom=InitBoundaryVal;
	m_Top=InitBoundaryVal;
}

template<class T> 
CPositionGroup2D<T>::CPositionGroup2D(unsigned int InitialSize)
{
	m_Positions.reserve(InitialSize);
}

template<class T> 
CPositionGroup2D<T>::CPositionGroup2D(const CPositionGroup2D& SourceGroup)
{ 
	// copy constructor
	*this=SourceGroup; // use assignment operator
}

template<class T> 
CPositionGroup2D<T>& CPositionGroup2D<T>::operator=(const CPositionGroup2D& SourceGroup)
{
	// overloading of assignment operator
	if (this != &SourceGroup)
	{
		// ok to do assignment
		m_Positions=SourceGroup.m_Positions;
		UpdateBoundaries();
	}
	else
	{
		ostringstream ost;
		ost << "CPositionGroup2D::operator=() Cannot assign CPositionGroup2D to itself" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return *this;
}

template<class T> 
CPositionGroup2D<T>::~CPositionGroup2D()
{
	//destructor
}

template<class T> 
void CPositionGroup2D<T>::Empty()
{
	m_Positions.clear();
	// trick to clear capacity
	vector< T > v=m_Positions;
	m_Positions.swap(v);
}

template<class T> 
void CPositionGroup2D<T>::EmptyNoDeallocation()
{
	m_Positions.clear();
}

//template<class T> 
//bool CPositionGroup2D<T>::InsertPosition(T x, T y, unsigned int Index)
//{
//	return InsertPosition(T(x,y),Index);
//}

template<class T> 
bool CPositionGroup2D<T>::InsertPosition(T Pos, unsigned int Index)
{
	if (Index>=GetTotalPositions())
	{
		ostringstream ost;
		ost << "CPositionGroup2D::InsertPosition() Index(" << Index << ") out of range" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		vector< T > v;
		v.assign(m_Positions.begin()+Index,m_Positions.end());
		m_Positions[Index]=Pos;
		m_Positions.resize(Index+1);
		std::vector< T >::const_iterator it;
		for(it=v.begin(); it!=v.end(); ++it)
		{
			m_Positions.push_back(*it);
		}
		UpdateBoundaries(Pos);
		return true;
	}
}

template<class T> 
bool CPositionGroup2D<T>::RemovePosition(unsigned int Index)
{
	if (Index>=GetTotalPositions())
	{
		ostringstream ost;
		ost << "CPositionGroup2D::RemovePosition() Index(" << Index << ") out of range" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		if (Index!=(GetTotalPositions()-1))
		{
			m_Positions[Index]=m_Positions[GetTotalPositions()-1];
		}
		m_Positions.resize(GetTotalPositions()-1);
		UpdateBoundaries();
		return true;
	}
}

template<class T> 
bool CPositionGroup2D<T>::RemovePositionSlow(unsigned int Index)
{
	if (Index>=GetTotalPositions())
	{
		ostringstream ost;
		ost << "CPositionGroup2D::RemovePositionSlow() Index(" << Index << ") out of range" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		m_Positions.erase(m_Positions.begin()+Index);
		UpdateBoundaries();
		return true;
	}
}

template<class T> 
unsigned int CPositionGroup2D<T>::RemoveDuplicates()
{
	unsigned int count1=0,count2;
	unsigned int TotalPositions=GetTotalPositions();
	unsigned PosRemoved=0;
	while(count1<TotalPositions)
	{
		count2=count1+1;
		while(count2<TotalPositions)
		{
			if (m_Positions[count2]==m_Positions[count1])
			{
				/* Move last position to Index */
				m_Positions[count2]=m_Positions[GetTotalPositions()-1];
				m_Positions.resize(GetTotalPositions()-1);
				PosRemoved++;
			}
			else
			{
				count2++;
			}
			TotalPositions=GetTotalPositions();
		}
		count1++;
	}
	return PosRemoved;
}

template<class T> 
void CPositionGroup2D<T>::ReAllocPositions(unsigned int NewSize)
{
	if (NewSize>GetAllocatedPositions())
		m_Positions.reserve(NewSize);
	else
	{
		if (m_Positions.size()>NewSize)
			m_Positions.erase(m_Positions.begin()+NewSize,m_Positions.end());
		vector< T > v=m_Positions;
		m_Positions.swap(v);
		if (m_Positions.size()<NewSize)
			m_Positions.reserve(NewSize);
	}
//	k_ReAllocGroup(m_pGroup,NewSize);
}

template<class T> 
void CPositionGroup2D<T>::AdjustSizeOfPositions()
{
	// trick to clear capacity
	vector< T > v=m_Positions;
	m_Positions.swap(v);
}

template<class T> 
bool CPositionGroup2D<T>::PosInGroup(const T& Pos,unsigned int& Index)
{	
	std::vector< T >::const_iterator it1=m_Positions.begin(),it2;
	it2=it1;
	for(; it1!=m_Positions.end(); ++it1)
	{
		if ((it1->GetX()==Pos.GetX()) && (it1->GetY()==Pos.GetY()))
		{
			Index=it1-it2;
			return true;
		}
	}
	return false;
}

template<class T> 
void CPositionGroup2D<T>::PrintInfo(bool PrintPositions,unsigned int PosPrLine, unsigned int Precision)
{
	unsigned int x,y;
	if (PosPrLine==0)
		PosPrLine=1; /* minimum one position on each line! */
	cout << "**************** Token group info ********************" << endl;
	cout <<	" Positions: Top=(" << m_Top.GetX() << "," << m_Top.GetY() << ") Bottom=(" 
		<< m_Bottom.GetX() << "," << m_Bottom.GetY() << ") Left=("
		<< m_Left.GetX() << "," << m_Left.GetY() << ") Right=(" << m_Right.GetX()
		<< "," << m_Right.GetY() << ")" << endl;
	cout << " Width=" << GetWidth() << " Height=" << GetHeight() << endl;
	cout << " Total positions=" << m_Positions.size() << " Allocated positions=" <<
		m_Positions.capacity() << endl;
	if (PrintPositions==true)
	{
		ios_base::fmtflags Flags=cout.flags();
		cout << setprecision(Precision) << setiosflags(ios_base::right);
		cout << endl;
		if (m_Positions.size()>0)
		{
			for(x=0; x<(m_Positions.size()/PosPrLine); x++)
			{
				for(y=0; y<PosPrLine; y++)
				{
					cout << " pos " << x*PosPrLine+y << "=" << m_Positions[x*PosPrLine+y];
				}
				cout << endl;
			}
			for(y=m_Positions.size()-(m_Positions.size() %  PosPrLine);
			y<m_Positions.size(); y++)
			{
				cout << " pos " << y << "=" << m_Positions[y];
			}
			cout << endl;			
		}
		else
		{
			cout << "No positions in PositionGroup2D" << endl;
		}
		cout.flags(Flags);
	}
}

template<class T> 
ostream& operator<<(ostream& s,const CPositionGroup2D<T>& Group)
{
	s << "**************** PositionGroup2D info *****************\n";
	s <<	" Positions: Top=(" << Group.GetTop().GetX() << "," << Group.GetTop().GetY() << ") Bottom=(" 
		<< Group.GetBottom().GetX() << "," << Group.GetBottom().GetY() << ") Left=("
		<< Group.GetLeft().GetX() << "," << Group.GetLeft().GetY() << ") Right=(" << Group.GetRight().GetX()
		<< "," << Group.GetRight().GetY() << ")" << endl;
	s << " Width=" << Group.GetWidth() << " Height=" << Group.GetHeight() << endl;
	s << " Total positions=" << Group.GetTotalPositions() << " Allocated positions=" <<
		Group.GetAllocatedPositions() << endl;
	return s;
}

template<class T> 
void CPositionGroup2D<T>::UpdateBoundaries()
{
	if (GetTotalPositions()>0)
	{
		// update with first available position
		std::vector< T >::const_iterator it=m_Positions.begin();
		m_Right=*it;
		m_Left=*it;
		m_Bottom=*it;
		m_Top=*it;
		for(; it!=m_Positions.end(); ++it)
			UpdateBoundaries(*it);
	}
}

template<class T> 
bool CPositionGroup2D<T>::Load(const char* pPathAndFileName)
{
	ifstream s(pPathAndFileName);
	if (s.is_open()==true)
	{
		unsigned int TotalPositions;
		Empty(); // delete all contents
		string str;
		SkipSpaceAndComments(s);
		s >> str;
		if (str!=string("CPositionGroup2D"))
		{
			ostringstream ost;
			ost << "CPositionGroup2D<T>::Load() Did not find the token CPositionGroup2D in beginning of file" << IPLAddFileAndLine;
			CError::ShowMessage(IPL_ERROR,ost.str().c_str());
			s.close();
			return false;
		}
		SkipSpaceAndComments(s);
		s >> str;
		if (str!=string("TotalPositions"))
		{
			ostringstream ost;
			ost << "CPositionGroup2D<T>::Load() Did not find the token 'TotalPositions'" << IPLAddFileAndLine;
			CError::ShowMessage(IPL_ERROR,ost.str().c_str());
			s.close();
			return false;
		}
		SkipSpaceAndComments(s);
		s >> TotalPositions;
		SkipSpaceAndComments(s);
		int x;
		T P;
		for(x=0; x<TotalPositions; x++)
		{
			SkipSpaceAndComments(s);
			//P << s;
			s >> P;
			AddPositionFast(P);
			SkipSpaceAndComments(s);
		}
		UpdateBoundaries();
		return true;
	}
	else
	{
		ostringstream ost;
		ost << "CPositionGroup2D<T>::Load() Failed opening file: " << pPathAndFileName << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
}

template<class T> 
bool CPositionGroup2D<T>::Save(const char* pPathAndFileName)
{
	ofstream s(pPathAndFileName);
	if (s.is_open()==true)
	{
		s << "# Data from a CPositionGroup2D object in IPL98" << endl;
		s << "CPositionGroup2D" << endl;
		int Total=GetTotalPositions();
		s << "TotalPositions " << Total << endl;
		int x;
		for(x=0; x<Total; x++)
		{
			s << GetPosition(x);
			s << endl;
		}
		return true;
	}
	else
	{
		ostringstream ost;
		ost << "CPositionGroup2D<T>::Save() Failed opening file: " << pPathAndFileName << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
}

template<class T> 
bool CPositionGroup2D<T>::CopyToImage(COLORTYPE BackGround, CImage& Dest, bool Absolute)
{
	CPoint2D<INT16> P;
	if (GetTotalPositions()==0)
	{
		ostringstream ost;
		ost << "CPositionGroup2D<T>::CopyToImage() no points stored in PositionGroup" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	/* Allocate a binary image with correct dimensions */
	if (Absolute==true)
	{
		Dest.Alloc(m_Right.GetX()+1,m_Bottom.GetY()+1,1);
	}
	else
	{
		Dest.Alloc(m_Right.GetX()-m_Left.GetX()+1,m_Bottom.GetY()-m_Top.GetY()+1,1);
		Dest.SetOrigo(-m_Left.GetX(),-m_Top.GetY());
	}
	/* Initialise background color */
	Dest.Flush(BackGround);
	/* copy pixels to image */
	if (BackGround==HIGHCOLOR)
	{
		std::vector< T >::const_iterator it;
		for(it=m_Positions.begin(); it!=m_Positions.end(); ++it)
		{
			P.SetX(Round((*it).GetX()));
			P.SetY(Round((*it).GetY()));
			Dest.SetPixelFast(P,0);
			//r=pPixelGroup->pPos[i];
			//k_SetPixelFast(r.x,r.y,1,pDest);
		}
	}
	else
	{
		std::vector< T >::const_iterator it;
		for(it=m_Positions.begin(); it!=m_Positions.end(); ++it)
		{
			P.SetX(Round((*it).GetX()));
			P.SetY(Round((*it).GetY()));
			Dest.SetPixelFast(P,1);
			//r=pPixelGroup->pPos[i];
			//k_SetPixelFast(r.x,r.y,0,pDest);
		}
	}
	return true;
}

template<class T> 
bool CPositionGroup2D<T>::AddOffset(const T& Offset)
{
	if (GetTotalPositions()==0)
		return false;
	std::vector< T >::iterator it;
	for(it=m_Positions.begin(); it!=m_Positions.end(); ++it)
	{
		(*it) += Offset;
	}
	return true;
}

template<class T> 
void CPositionGroup2D<T>::Sort()
{
	std::sort(m_Positions.begin(),m_Positions.end());
}
