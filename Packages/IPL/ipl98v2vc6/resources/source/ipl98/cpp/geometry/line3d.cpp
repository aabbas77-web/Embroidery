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
CLine3D<T>::CLine3D()
{
	m_P.Set(0,0,0);
	m_Dir.Set(1,0,0);
}

template<class T>
CLine3D<T>::CLine3D(const CPoint3D<T>& P, const CVector3D<T>& Dir)
{
	m_P=P;
	m_Dir=Dir;
}

template <class T>
CLine3D<T>::CLine3D(const CLine3D<T>& Line3D)
{
	// copy constructor
	*this=Line3D;
}

template<class T>
CLine3D<T>& CLine3D<T>::operator=(const CLine3D<T>& Line3D)
{
	m_P=Line3D.m_P;
	m_Dir=Line3D.m_Dir;
	return *this;
}

template<class T>
bool CLine3D<T>::Set(const CPoint3D<T>& P, const CVector3D<T>& Dir)
{
	if (Dir.IsZero()==true)
		return false;
	m_P=P;
	m_Dir=Dir;
	return true;
}

template <class T>
bool CLine3D<T>::PseudoIntersect(const CLine3D<T>& L, CPoint3D<T>& PseudoIntersectionPoint, T& MinDistance)
{
	T t1,t2,N,D1sq,D2sq,D1D2,D1Q21,D2Q21;
	CVector3D<T> Buf,P1,P2;
	CVector3D<T> Q21;
	D1sq=GetDir()*GetDir();
	D2sq=L.GetDir()*L.GetDir();
	D1D2=GetDir()*L.GetDir();
	Q21=CVector3D<T>(L.GetPoint()-GetPoint());
	D1Q21=GetDir()*Q21;
	D2Q21=L.GetDir()*Q21;
	N=D1sq*D2sq-D1D2*D1D2;
	if (N==0) 
		return false;//Linier parallelle
	
	t1=( D1Q21*D2sq-D1D2*D2Q21)/N;
	t2=(-D2Q21*D1sq+D1D2*D1Q21)/N;
	P1=CVector3D<T>(GetPoint())+GetDir()*t1;
	P2=CVector3D<T>(L.GetPoint())+L.GetDir()*t2;
	Buf=P2-P1;
	MinDistance=sqrt(Buf*Buf);
	Buf=P1+P2;
	PseudoIntersectionPoint=Buf*0.5;
	return true;
}

//template <class T>
//bool CLine3D<T>::PseudoIntersect(const CLine3D<T>& L, CPoint3D<T>& PseudoIntersectionPoint, T& MinDistance)
//{
//	T t1,t2,N,D1sq,D2sq,D1D2,D1Q21,D2Q21;
//	CPoint3D<T> Q21,Buf,P1,P2;
//	D1sq=ScalarProduct(L1.m_Direction,L1.m_Direction);
//	D2sq=ScalarProduct(L2.m_Direction,L2.m_Direction);
//	D1D2=ScalarProduct(L1.m_Direction,L2.m_Direction);
//	Q21=L2.Q-L1.Q;
//	D1Q21=ScalarProduct(L1.m_Direction,Q21);
//	D2Q21=ScalarProduct(L2.m_Direction,Q21);
//	N=D1sq*D2sq-D1D2*D1D2;
//	if (N==0) 
//		return false;//Linier parallelle
//	
//	t1=( D1Q21*D2sq-D1D2*D2Q21)/N;
//	t2=(-D2Q21*D1sq+D1D2*D1Q21)/N;
//	P1=L1.m_P+L1.m_Direction*t1;
//	P2=L2.m_P+L2.m_Direction*t2;
//	Buf=P2-P1;
//	MinimumLineLineDistance=sqrt(ScalarProduct(Buf,Buf));
//	Buf=P1+P2;
//	PseudoIntersectionPoint=Buf*0.5;
//	return true;
//}
