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

template<class T>
CLine2D<T>::CLine2D()
{
	m_P.Set(0,0);
	m_Dir.Set(1,0);
}

template<class T>
CLine2D<T>::CLine2D(CPoint2D<T> P, CVector2D<T> Dir)
{
	m_P=P;
	m_Dir=Dir;
}

template <class T>
CLine2D<T>::CLine2D(const CLine2D<T>& Line2D)
{
	// copy constructor
	*this=Line2D;
}

template<class T>
CLine2D<T>& CLine2D<T>::operator=(const CLine2D<T>& Line2D)
{
	m_P=Line2D.m_P;
	m_Dir=Line2D.m_Dir;
	return *this;
}

template<class T>
bool CLine2D<T>::Intersect(const CLine2D<T>& L, CPoint2D<T>& Q)
{
	if (m_Dir==L.GetDir())
	{
		return false;
	}
	else
	{
		T x,y,f1,f2;
		if ((m_Dir.GetX()==0) && (L.GetDir().GetY()==0))
		{
			Q.Set(m_P.GetX(),L.GetPoint().GetY());
		}
		else if ((m_Dir.GetY()==0) && (L.GetDir().GetX()==0))
		{
			Q.Set(L.GetPoint().GetX(),m_P.GetY());
		}
		else 
		{
			T b1,b2;
			if (fabs(m_Dir.GetY())<fabs(m_Dir.GetX()))
			{
	//			f1=m_Dir.GetY()/m_Dir.GetX();
	//			f2=L.GetDir().GetY()/L.GetDir().GetX();
	//			x=((m_P.GetY()-L.GetPoint().GetY()-f2*L.GetPoint().GetX()+f1*m_P.GetX()))/(f1-f2);
	//			y=m_P.GetY()+f1*(x-m_P.GetX());
				f1=m_Dir.GetY()/m_Dir.GetX();
				f2=L.GetDir().GetY()/L.GetDir().GetX();
				b1=m_P.GetY()-f1*m_P.GetX();
				b2=L.GetPoint().GetY()-f2*L.GetPoint().GetX();
				x=(b2-b1)/(f1-f2);
				y=f2*x+b2;
			}
			else
			{
	//			f1=m_Dir.GetX()/m_Dir.GetY();
	//			f2=L.GetDir().GetX()/L.GetDir().GetY();
	//			y=((m_P.GetX()-L.GetPoint().GetX()-f2*L.GetPoint().GetY()+f1*m_P.GetY()))/(f1-f2);
	//			x=m_P.GetX()+f1*(y-m_P.GetY());
				f1=m_Dir.GetX()/m_Dir.GetY();
				f2=L.GetDir().GetX()/L.GetDir().GetY();
				b1=m_P.GetX()-f1*m_P.GetY();
				b2=L.GetPoint().GetX()-f2*L.GetPoint().GetY();
				y=(b2-b1)/(f1-f2);
				x=f2*y+b2;

			}
			Q.Set(x,y);
		}
		return true;
	}
}

//template <class T>
//bool CGeometry2D<T>::LineLineIntersect(const CLine2D<T>& L1, const CLine2D<T>& L2, CPoint2D<T>& Q)
//{
//	T x,y,f1,f2;
//	f1=L1.D.GetY()/L1.D.GetX();
//	f2=L2.D.GetY()/L2.D.GetX();
//	x=((L1.Q.GetY()-L2.Q.GetY()-f2*L2.Q.GetX()+f1*L1.Q.GetX()))/(f1-f2);
//	y=L1.Q.GetY()+f1*(x-L1.Q.GetX());
//	Q.SetX(x);
//	Q.SetY(y);
//	return true;
//}

template<class T>
bool CLine2D<T>::Set(const CPoint2D<T>& P, const CVector2D<T>& Dir)
{
	if (Dir.IsZero()==true)
		return false;
	m_P=P;
	m_Dir=Dir;
	return true;
}
