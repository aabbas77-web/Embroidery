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
CPlane<T>::CPlane()
{
	m_P.Set(0,0,0);
	m_DirA.Set(1,0,0);
	m_DirB.Set(0,1,0);
}

template<class T>
CPlane<T>::CPlane(const CPoint3D<T>& P, const CVector3D<T>& DirA, const CVector3D<T>& DirB)
{
	m_P=P;
	m_DirA=DirA;
	m_DirB=DirB;
}

template <class T>
CPlane<T>::CPlane(const CPlane<T>& Plane)
{
	// copy constructor
	*this=Plane;
}

template<class T>
CPlane<T>& CPlane<T>::operator=(const CPlane<T>& Plane)
{
	m_P=Plane.m_P;
	m_DirA=Plane.m_DirA;
	m_DirB=Plane.m_DirB;
	return *this;
}

template<class T>
bool CPlane<T>::Intersect(const CPlane<T>& P, CLine3D<T> &L) const
{
	CVector3D<T> N1,N2,N3;
	N1=GetPlaneNormal();
	N2=P.GetPlaneNormal();
	N3=N1.GetCross(N2);
	if (N3.IsZero()==true) 
		return false; // parallel planes
	else
	{
		CVector3D<T> N4(N3.GetCross(N1));
		CVector3D<T> Q;
		CLine3D<T> L1(GetPoint(),N4);
		if (P.Intersect(L1,Q)==true)
		{
			L.Set(Q,N3);
			return true;
		}
		else 
			return false;
	}
}
		
//template<class T>
//bool CPlane::Intersect(const CPlane<T>& P, CLine3D<T> &L)
//{
//	CLine3D<T> L1;
//	CPoint3D<T> N1,N2,N3,N4,Q;
//	N1=VectorProduct(P1.m_DirectionA,P1.m_DirectionB);
//	N2=VectorProduct(P2.m_DirectionA,P2.m_DirectionB);
//	N3=VectorProduct(N1,N2);
//	if (N3.GetX()*N3.GetX()+
//		N3.GetY()*N3.GetY()+
//		N3.GetZ()*N3.GetZ()==0) 
//	{
//		return false; //Planer parallelle
//	}
//	else
//	{
//		N4=VectorProduct(N3,N1);
//		L1.m_P=P1.m_P;
//		L1.m_Direction=N4;
//		if (LinePlaneIntersect(L1,P2,Q))
//		{
//			L.m_Direction=N3;
//			L.m_P=Q;
//			return true;
//		}
//		else 
//			return false;
//	}
//}

template<class T>
bool CPlane<T>::Intersect(const CLine3D<T>& L, CPoint3D<T>& Q) const
{
	const CVector3D<T>& D=L.GetDir();
	T F= m_DirA.GetX()*(-m_DirB.GetY()*D.GetZ()+m_DirB.GetZ()*D.GetY())
		 +m_DirA.GetY()*(-m_DirB.GetZ()*D.GetX()+m_DirB.GetX()*D.GetZ())
		 +m_DirA.GetZ()*(-m_DirB.GetX()*D.GetY()+m_DirB.GetY()*D.GetX());
	if (F!=0)
	{
		CVector3D<T> P(L.GetPoint()-GetPoint());
		T Tl=(m_DirA.GetX()*(m_DirB.GetY()*P.GetZ()-m_DirB.GetZ()*P.GetY())
			+m_DirA.GetY()*(m_DirB.GetZ()*P.GetX()-m_DirB.GetX()*P.GetZ())
			+m_DirA.GetZ()*(m_DirB.GetX()*P.GetY()-m_DirB.GetY()*P.GetX()))/F;
		Q=L.GetPoint()+D*Tl;
		//Q.Set(L.GetPoint()+D*Tl);
		return true;
	} 
	else 
		return false;//Linie parallel med plan
}

//template <class T>
//bool CGeometry3D<T>::LinePlaneIntersect(const CLine3D<T>& L, const CPlane<T>& P, CPoint3D<T>& Q)
//{ 
//	T DAx,DBx,DAy,DBy,DAz,DBz,Dx,Dy,Dz,Qx,Qy,Qz,D,Tl;
//	Qx=L.m_P.GetX()-P.m_P.GetX();
//	Qy=L.m_P.GetY()-P.m_P.GetY();
//	Qz=L.m_P.GetZ()-P.m_P.GetZ();
//	DAx=P.m_DirectionA.GetX();
//	DAy=P.m_DirectionA.GetY();
//	DAz=P.m_DirectionA.GetZ();
//	DBx=P.m_DirectionB.GetX();
//	DBy=P.m_DirectionB.GetY();
//	DBz=P.m_DirectionB.GetZ();
//	Dx=L.m_Direction.GetX();
//	Dy=L.m_Direction.GetY();
//	Dz=L.m_Direction.GetZ();
//	D= DAx*(-DBy*Dz+DBz*Dy)
//		+DAy*(-DBz*Dx+DBx*Dz)
//		+DAz*(-DBx*Dy+DBy*Dx);
//	if (D!=0)
//	{
//		Tl=(DAx*(DBy*Qz-DBz*Qy)
//			+DAy*(DBz*Qx-DBx*Qz)
//			+DAz*(DBx*Qy-DBy*Qx))/D;
//		Q.SetX(L.m_P.GetX()+Dx*Tl);
//		Q.SetY(L.m_P.GetY()+Dy*Tl);
//		Q.SetZ(L.m_P.GetZ()+Dz*Tl);
//		return true;
//	} 
//	else 
//		return false;//Linie parallel med plan
//}
