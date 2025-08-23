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

#include "perspective.h"
#include "../ipl98_general_functions.h"
#include <fstream>
#include <iomanip>
#include <ios>

namespace ipl{

using std::ios;
using std::ios_base;
using std::scientific;
using std::setprecision;
using std::setiosflags;
using std::setw;
using std::ofstream;
using std::cout;
using std::endl;

const double CPerspective::m_Version=1.50;

CPerspective::CPerspective(const CStdImage& Img)
{
	m_CamMatrixCalibrated=false;
    m_CamParametersAvailable=false;
	m_RadCalibrationPerformed=false;
	m_CenterX=Img.GetWidth()/2.0;
	m_CenterY=Img.GetHeight()/2.0;
}

CPerspective::CPerspective(unsigned int Width, unsigned int Height)
{
	m_CamMatrixCalibrated=false;
    m_CamParametersAvailable=false;
	m_RadCalibrationPerformed=false;
	m_CenterX=Width/2.0;
	m_CenterY=Height/2.0;
}

CPerspective::CPerspective(CPoint2D<unsigned int> Dimensions)
{
	m_CamMatrixCalibrated=false;
    m_CamParametersAvailable=false;
	m_RadCalibrationPerformed=false;
	m_CenterX=Dimensions.GetX()/2.0;
	m_CenterY=Dimensions.GetY()/2.0;
}

CPerspective::~CPerspective()
{
}

CPerspective& CPerspective::operator=(const CPerspective& Source)
{
	// overloading of assignment operator
	if (this != &Source)
	{
		// ok to do assignment
		m_CamParametersAvailable=Source.m_CamParametersAvailable;
		if (m_CamParametersAvailable==true)
			m_Par=Source.m_Par; // only need to copy Par structure if data available
		m_Cam=Source.m_Cam;
		m_CamMatrixCalibrated=Source.m_CamMatrixCalibrated;
		m_RadCalibrationPerformed=Source.m_RadCalibrationPerformed;
		m_k=Source.m_k;
		m_CenterX=Source.m_CenterX;
		m_CenterY=Source.m_CenterY;
	}
	else
	{
		ostringstream ost;
		ost << "CPerspective::operator=() Cannot assign CPerspective object to itself" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	return *this;
}

bool CPerspective::Calibrate(const CCorresponding3D2DPoints& PointSets)
{
	if (!k_CalibrateCamera(PointSets.GetConstT3D2DPointsPtr(), &m_Cam))
	{
		ostringstream ost;
		ost << "CPerspective::Calibrate() Calibration failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		m_CamMatrixCalibrated=true;
		MatrixToParameters();
		return true;
	}
}

bool CPerspective::Set(const TCameraMatrix& Cam, double k, unsigned int Width, unsigned Height)
{
	m_Cam=Cam;
	m_k=k;
	m_CenterX=Width/2.0;
	m_CenterY=Height/2.0;
	m_CamMatrixCalibrated=true;
	m_RadCalibrationPerformed=true;
	m_CamParametersAvailable=false;
	return true;
}

void CPerspective::SetCameraMatrix(const TCameraMatrix& Cam)
{
	m_Cam=Cam;
	m_CamMatrixCalibrated=true;
	m_RadCalibrationPerformed=false;
	m_CamParametersAvailable=false;
}

void CPerspective::SetCameraMatrixAndRadDistortion(const TCameraMatrix& Cam, double k)
{
	m_Cam=Cam;
	m_k=k;
	m_CamMatrixCalibrated=true;
	m_RadCalibrationPerformed=true;
	m_CamParametersAvailable=false;
}

bool CPerspective::Calc3DTo2D(const CPoint3D<FLOAT32>& w, CPoint2D<FLOAT32>& Pnt) const
{
	if (m_CamMatrixCalibrated==false)
	{
		ostringstream ost;
		ost << "CPerspective::Calc3DTo2D() Camera matrix not yet calculated" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		T3DFloat AnsiW;
		AnsiW.x=w.GetX();
		AnsiW.y=w.GetY();
		AnsiW.z=w.GetZ();
		T2DFloat AnsiPnt;
		k_Calc3DTo2D(AnsiW,&m_Cam,&AnsiPnt);
		Pnt.Set(AnsiPnt.x,AnsiPnt.y);
		return true;
	}
}

bool CPerspective::Direction(const CPoint2D<FLOAT32>& p,CPoint3D<FLOAT32>& Dir) const
{
	if (m_CamMatrixCalibrated==false)
	{
		ostringstream ost;
		ost << "CPerspective::Direction() Camera matrix not yet calculated" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		T3DFloat AnsiDir;
		T2DFloat AnsiP;
		AnsiP.x=p.GetX();
		AnsiP.y=p.GetY();
		k_Direction(AnsiP,&m_Cam,&AnsiDir);
		Dir.Set(AnsiDir.x,AnsiDir.y,AnsiDir.z);
		return true;
	}
}

bool CPerspective::PinHole(CPoint3D<FLOAT32>& PinHole) const
{
	if (m_CamMatrixCalibrated==false)
	{
		ostringstream ost;
		ost << "CPerspective::PinHole() Camera matrix not yet calculated" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		T3DFloat AnsiPH;
		k_PinHole(&m_Cam, &AnsiPH);
		PinHole.Set(AnsiPH.x,AnsiPH.y,AnsiPH.z);
		return true;
	}
}

CPoint3D<FLOAT32> CPerspective::GetPinHole() const
{
	CPoint3D<FLOAT32> P;
	PinHole(P);
	return P;
}

bool CPerspective::CalibrateWithRadialDist(CCorresponding3D2DPoints& PointSets)
{
	bool ReturnValue;
	ReturnValue=k_CalibrateWithRadialDist(PointSets.GetT3D2DPointsPtr(),&m_Cam,&m_k,m_CenterX,m_CenterY);
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CPerspective::CalibrateWithRadialDist() Failed calibration with radial distortion correction" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	else
	{
		m_RadCalibrationPerformed=true;
		m_CamMatrixCalibrated=true;
		MatrixToParameters();
	}
	return ReturnValue;
}

bool CPerspective::Calc3DTo2DRad(const CPoint3D<FLOAT32>& w, CPoint2D<FLOAT32>& Pnt) const
{
	if (m_RadCalibrationPerformed==false)
	{
		ostringstream ost;
		ost << "CCalibration::Calc3DTo2DRad() Need to calibrate system first by calling CalibrateWithRadialDist()" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		T2DFloat P;
		T3DFloat wc;
		wc.x=w.GetX();
		wc.y=w.GetY();
		wc.z=w.GetZ();
		k_Calc3DTo2DRad(wc,&m_Cam,m_k,&P,m_CenterX,m_CenterY);
		Pnt.Set(P.x,P.y);
		return true;
	}
}

bool CPerspective::CalibrationPerformed() const
{
	return m_CamMatrixCalibrated;
}

bool CPerspective::RadCalibrationPerformed() const
{
	return m_RadCalibrationPerformed;
}

CPoint2D<int> CPerspective::GetMaxRadialDisplacement() const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::MaxRadialDisplacement() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<int>(-1,-1);
	}
	else
	{
		T2DInt Pos;
		Pos=k_GetMaxRadialDisplacement(m_k,m_CenterX,m_CenterY);
		return CPoint2D<int>(Pos.x,Pos.y);
	}
}

bool CPerspective::RemoveRadialDistortion(CStdImage& Dest, CStdImage& Source, bool PreserveImageSize)
{
	bool ReturnValue;
	if (m_RadCalibrationPerformed==false)
	{
		ostringstream ost;
		ost << "CPerspective::RemoveRadialDistortion() Need to calibrate system first by calling CalibrateWithRadialDist()" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		ReturnValue=false;
	}
	else
	{
		ReturnValue=k_RemoveRadialDistortion(Dest.GetTImagePtr(),Source.GetTImagePtr(),m_k,PreserveImageSize);
		if (ReturnValue==false)
		{
			ostringstream ost;
			ost << "CPerspective::RemoveRadialDistortion() Failed removing radial distortion" << IPLAddFileAndLine;
			CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		}
	}
	return ReturnValue;
}

bool CPerspective::RemoveRadialDistortionExtK(CStdImage& Dest, CStdImage& Source, double k, bool PreserveImageSize)
{
	bool ReturnValue;
	if (m_CamMatrixCalibrated==false)
	{
		ostringstream ost;
		ost << "CPerspective::RemoveRadialDistortionExtK() Need to calibrate system first by calling CalibrateWithRadialDist() or Calibrate()" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		ReturnValue=false;
	}
	else
	{
		ReturnValue=k_RemoveRadialDistortion(Dest.GetTImagePtr(),Source.GetTImagePtr(),k,PreserveImageSize);
		if (ReturnValue==false)
		{
			ostringstream ost;
			ost << "CPerspective::RemoveRadialDistortionExtK() Failed removing radial distortion" << IPLAddFileAndLine;
			CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		}
	}
	return ReturnValue;
}

bool CPerspective::SetImageDimensions(unsigned int Width, unsigned Height)
{
	if ((Width==0) || (Height==0))
	{
		ostringstream ost;
		ost << "CPerspective::SetImageDimensions() Width or Height parameters is 0" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	m_CamMatrixCalibrated=false;
    m_CamParametersAvailable=false;
	m_RadCalibrationPerformed=false;
	m_CenterX=Width/2.0;
	m_CenterY=Height/2.0;
	return true;
}

bool CPerspective::SetImageDimensions(CPoint2D<unsigned int> Dimensions)
{
	return SetImageDimensions(Dimensions.GetX(), Dimensions.GetY());
}

void CPerspective::GetImageDimensions(unsigned int &Width, unsigned int &Height) const
{
	Width = (unsigned int)(2*m_CenterX);
	Height = (unsigned int)(2*m_CenterY);
}

CPoint2D<unsigned int> CPerspective::GetImageDimensions() const
{
	return CPoint2D<unsigned int>((unsigned int)(2*m_CenterX),(unsigned int)(2*m_CenterY));
}

CPoint2D<FLOAT32> CPerspective::GetPosRadRemoved(FLOAT32 x,FLOAT32 y) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosRadRemoved() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosRadRemoved(x,y,m_k,m_CenterX,m_CenterY);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosRadRemoved(const CPoint2D<FLOAT32>& Pos) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosRadRemoved() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos1;
		Pos1=k_GetPosRadRemoved(Pos.GetX(),Pos.GetY(),m_k,m_CenterX,m_CenterY);
		return CPoint2D<FLOAT32>(Pos1.x,Pos1.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosInverseRad(FLOAT32 xr, FLOAT32 yr) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosInverseRad() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosInverseRad(xr,yr,m_k,m_CenterX,m_CenterY);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosInverseRad(const CPoint2D<FLOAT32>& PosRad) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosInverseRad() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosInverseRad(PosRad.GetX(),PosRad.GetY(),m_k,m_CenterX,m_CenterY);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

FLOAT32 CPerspective::GetCamMatrix(unsigned short i, unsigned short j) const
{
	if ((i>4) || (j>4) || (i==0) || (j==0))
	{
		ostringstream ost;
		ost << "CPerspective::GetCamMatrix() Indexes out of range" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return 0;
	}

	if ((i==1) && (j==1))
		return m_Cam.a11;
	else if ((i==1) && (j==2))
		return m_Cam.a12;
	else if ((i==1) && (j==3))
		return m_Cam.a13;
	else if ((i==1) && (j==4))
		return m_Cam.a14;
	else if ((i==2) && (j==1))
		return m_Cam.a21;
	else if ((i==2) && (j==2))
		return m_Cam.a22;
	else if ((i==2) && (j==3))
		return m_Cam.a23;
	else if ((i==2) && (j==4))
		return m_Cam.a24;
	else if ((i==3) && (j==1))
		return m_Cam.a31;
	else if ((i==3) && (j==2))
		return m_Cam.a32;
	else if ((i==3) && (j==3))
		return m_Cam.a33;
	else if ((i==3) && (j==4))
		return m_Cam.a34;
	else if ((i==4) && (j==1))
		return m_Cam.a41;
	else if ((i==4) && (j==2))
		return m_Cam.a42;
	else if ((i==4) && (j==3))
		return m_Cam.a43;
	else if ((i==4) && (j==4))
		return m_Cam.a44;
	else
		return 0; // should not be possible!
}

void CPerspective::PrintCameraMatrix(bool WithIndexes) const
{
	k_PrintCameraMatrix(&m_Cam,WithIndexes);
}

bool CPerspective::PrintErrors(const CCorresponding3D2DPoints& PointSets) const
{
	return ErrorsToStream(PointSets,cout);
}

bool CPerspective::ErrorsToStream(const CCorresponding3D2DPoints& PointSets, ostream& Stream) const
{
	if (m_CamMatrixCalibrated!=true)
	{
		ostringstream ost;
		ost << "CPerspective::ErrorsToStream() Calibration not performet yet" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else if (PointSets.GetTotalPointSetsInUse()!=PointSets.GetTotalPointSets())
	{
		ostringstream ost;
		ost << "CPerspective::ErrorsToStream() Some of the point sets are not complete" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		float TotalErrorX=0;
		float TotalErrorY=0;
		if (m_RadCalibrationPerformed==true)
		{
			Stream << "**************** CPerspective errors (with radial correction) ******************\n";
		}
		else
		{
			Stream << "**************** CPerspective errors (no radial correction) ******************\n";
		}
		unsigned int i;
		for(i=0;i<PointSets.GetTotalPointSets();i++)
		{
			CPoint3D<FLOAT32> pnt3d=PointSets.GetPoint3D(i);
			CPoint2D<FLOAT32> pnt2d;
			if (m_RadCalibrationPerformed==true)
				Calc3DTo2DRad(pnt3d,pnt2d);
			else
				Calc3DTo2D(pnt3d,pnt2d);
			float xerror=pnt2d.GetX()-PointSets.GetPoint2D(i).GetX();
			float yerror=pnt2d.GetY()-PointSets.GetPoint2D(i).GetY();
			Stream.width(8); 
			Stream.setf(ios::left,ios::adjustfield);
			Stream << " Point " << i << " at " << PointSets.GetPoint2D(i);
			//cout.width(13); cout.setf(ios::left,ios::adjustfield);
			Stream << " Error: (" << xerror << "," << yerror << ")" << endl;
			TotalErrorX+=fabs(xerror);
			TotalErrorY+=fabs(yerror);
		}
		Stream << "Total mean error: (" << TotalErrorX/i << "," << TotalErrorY/i << ")" << endl;
		return true;
	}
}

bool CPerspective::CamParametersToStream(ostream& Stream) const
{
	Stream << endl << "**************** TCameraParameters info ********************" << endl;
	if (m_CamParametersAvailable==false)
	{
		Stream << " not available" << endl;
		return false;
	}
	else
	{
		Stream << " x coordinate of focal centre (dx) = " << m_Par.dx << endl;
		Stream << " y coordinate of focal centre (dy) = " << m_Par.dy << endl;
		Stream << " z coordinate of focal centre (dz) = " << m_Par.dz << endl;
		Stream << " rotation of camera around the x-axis (a) = " << m_Par.a << "[rad] = " << m_Par.a*180/PI << " [deg]"<< endl;
		Stream << " rotation of camera around the y-axis (b) = " << m_Par.b << "[rad] = " << m_Par.b*180/PI << " [deg]"<< endl;
		Stream << " rotation of camera around the z-axis (c) = " << m_Par.c << "[rad] = " << m_Par.c*180/PI << " [deg]"<< endl;
		Stream << " focal length = " << m_Par.FocalLength << " [pixels] " << endl;
		Stream << " x-coordinate of origin of the focal centre on the CCD chip (xh) = " << m_Par.xh << " [pixels]" << endl;
		Stream << " y-coordinate of origin of the focal centre on the CCD chip (yh) = " << m_Par.yh << " [pixels]" << endl;
		Stream << " aspect ratio, scale of V relative to U (p) = " << m_Par.p << endl;
		Stream << " skewness of V relative to U (beta) = " << m_Par.beta << " [rad] = " << m_Par.beta*180/PI << " [deg]"<< endl;
		return true;
	}		
}

ostream& operator<<(ostream& s,const CPerspective& Persp)
{
	ios_base::fmtflags Flags=s.flags();
	s << scientific << setprecision(6) << setiosflags(ios_base::right);
	s << "**************** TCameraMatrix info ********************" << endl;
	s << setw(15) << Persp.GetCamMatrix(1,1);
	s << setw(15) << Persp.GetCamMatrix(1,2); 
	s << setw(15) << Persp.GetCamMatrix(1,3);
	s << setw(15) << Persp.GetCamMatrix(1,4) << endl;
	s << setw(15) << Persp.GetCamMatrix(2,1);
	s << setw(15) << Persp.GetCamMatrix(2,2);
	s << setw(15) << Persp.GetCamMatrix(2,3);
	s << setw(15) << Persp.GetCamMatrix(2,4) << endl;
	s << setw(15) << Persp.GetCamMatrix(3,1);
	s << setw(15) << Persp.GetCamMatrix(3,2);
	s << setw(15) << Persp.GetCamMatrix(3,3);
	s << setw(15) << Persp.GetCamMatrix(3,4) << endl;
	s << setw(15) << Persp.GetCamMatrix(4,1);
	s << setw(15) << Persp.GetCamMatrix(4,2);
	s << setw(15) << Persp.GetCamMatrix(4,3);
	s << setw(15) << Persp.GetCamMatrix(4,4) << endl;
	s.flags(Flags);

	if (Persp.RadCalibrationPerformed()==true)
	{
		s << "  Radial distortion parameter: k=" << Persp.GetRadDistParameter() << endl;
	}
	else
	{
		s << "  No radial distortion parameter available" << endl;
	}

	Persp.CamParametersToStream(s);
	return s;
}


bool CPerspective::ParametersAvailable() const
{
	return m_CamParametersAvailable;
}

bool CPerspective::MatrixToParameters()
{
	if (m_CamMatrixCalibrated==false)
	{
		ostringstream ost;
		ost << "CPerspective::MatrixToParameters() Camera matrix not yet calculated" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
        if (k_MatrixToParameters(&m_Cam, &m_Par)==false)
			return false;
        m_CamParametersAvailable=true;
		return true;
	}

}


bool CPerspective::ParametersToMatrix()
{
	if (m_CamParametersAvailable==false)
	{
		ostringstream ost;
		ost << "CPerspective::ParametersToMatrix() Camera parameters not yet calculated" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		k_ParametersToMatrix(&m_Par, &m_Cam);
		m_CamMatrixCalibrated=true;
		return true;
	}
}

bool CPerspective::Load(const char* pPathAndFileName)
{
	/* booleans to check if necessary tokens were found */
	bool PerspectiveVersionFund=false;
	bool CameraMatrixFound=false;
	bool kFound=false, WidthFound=false, HeightFound=false;
	bool returnValue=true;
	TString str;
	k_InitString(&str);
	FILE* fp=fopen(pPathAndFileName,"rb"); /* open file */
	if (fp==NULL)
	{
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() Could not open file");
		returnValue=false;
	}
	else
	{
		/* read from file */
		char c;
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
					k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() Failed reading token");
					returnValue=false;
				}
				else
				{
					k_StringToUpper(Token);
					if (strcmp(Token,"PERSPECTIVEVERSION")==0)
					{
						PerspectiveVersionFund=true;
						double FileVersion;
						if (fscanf(fp,"%lf",&FileVersion)!=1)
						{
							k_EmptyString(&str);
							k_AddFileAndLine(str);
							k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() Failed reading calibration version");
							returnValue=false;
						}
						else if (m_Version!=FileVersion)
						{
							k_EmptyString(&str);
							k_AddFileAndLine(str);
							k_ShowMessage(IPL_WARNING,&str,"CPerspective::Load() File version not same as this class version");
						}
					}
					else if (strcmp(Token,"CAMERAMATRIX")==0)
					{
						CameraMatrixFound=true;
						/* The following 16 values must be the camera parameters */
						if (fscanf(fp,"%f %f %f %f"
									  "%f %f %f %f"
									  "%f %f %f %f"
									  "%f %f %f %f"
									  ,&m_Cam.a11,&m_Cam.a12, &m_Cam.a13, &m_Cam.a14
									  ,&m_Cam.a21,&m_Cam.a22, &m_Cam.a23, &m_Cam.a24
									  ,&m_Cam.a31,&m_Cam.a32, &m_Cam.a33, &m_Cam.a34
									  ,&m_Cam.a41,&m_Cam.a42, &m_Cam.a43, &m_Cam.a44) != 16)
						{
							k_EmptyString(&str);
							k_AddFileAndLine(str);
							k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() Failed reading camera matrix values");
							returnValue=false;
						}
					}
					else if (strcmp(Token,"K")==0)
					{
						kFound=true;
						if (fscanf(fp,"%lf",&m_k) != 1)
						{
							k_EmptyString(&str);
							k_AddFileAndLine(str);
							k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() Failed reading k radial dist parameter");
							returnValue=false;
						}
					}
					else if (strcmp(Token,"WIDTH")==0)
					{
						int CenterX;
						WidthFound=true;
						if (fscanf(fp,"%d",&CenterX) != 1)
						{
							k_EmptyString(&str);
							k_AddFileAndLine(str);
							k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() Failed reading width parameter");
							returnValue=false;
						}
						m_CenterX = (FLOAT32)CenterX/2.0; // convert from image dimension to center
					}
					else if (strcmp(Token,"HEIGHT")==0)
					{
						int CenterY;
						HeightFound=true;
						if (fscanf(fp,"%d",&CenterY) != 1)
						{
							k_EmptyString(&str);
							k_AddFileAndLine(str);
							k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() Failed reading height parameter");
							returnValue=false;
						}
						m_CenterY = (FLOAT32)CenterY/2.0; // convert from image dimension to center
					}
					free(Token);
				}
			}
			k_SkipWhiteSpace(fp);
		}
		if ((PerspectiveVersionFund==false) || (CameraMatrixFound==false) || (kFound==false))
		{
			k_EmptyString(&str);
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_ERROR,&str,"CPerspective::Load() One of the necessary tokens not found");
			returnValue=false;
		}
		if ((WidthFound==false) || (HeightFound==false))
		{
			k_EmptyString(&str);
			k_AddFileAndLine(str);
			k_ShowMessage(IPL_WARNING,&str,"CPerspective::Load() Width and/or height not found - using "
				"image dimensions (%d,%d)", (int)(m_CenterX*2.0), (int)(m_CenterY*2.0));
		}
		if (returnValue==true)
		{
			m_CamMatrixCalibrated=true;
			if (kFound==true)
				m_RadCalibrationPerformed=true;
			MatrixToParameters();
		}
	}
	k_EmptyString(&str);
	return returnValue;
}

bool CPerspective::Save(const char* pPathAndFileName,const char* pComments) const
{
	TString str;
	k_InitString(&str);
	if (m_CamMatrixCalibrated==false)
	{
		k_AddFileAndLine(str);
		k_ShowMessage(IPL_ERROR,&str,"CPerspective::Save() Need to calibrate camera first");
	    k_EmptyString(&str);
		return false;
	}
	else
	{
		// check for extension, if no extension add ".cfg"
		string FilePathName(pPathAndFileName); // resulting filename
		TFileInfo FileInfo;
		k_InitFileInfo(&FileInfo);
		char* Path=NULL,*FileNameExt=NULL,*Ext=NULL;
		if (k_SplitFileName(pPathAndFileName,&Path, &FileNameExt, &Ext)==true)
		{
			if (strcmp(Ext,"")==0)
				FilePathName.append(".cfg");

			ofstream OutStream(FilePathName.c_str());
			if (!OutStream)
			{
				k_AddFileAndLine(str);
				k_ShowMessage(IPL_ERROR,&str,"CPerspective::Save() Failed to write file");
				k_EmptyString(&str);
				return false;
			}
			else
			{
				OutStream << "# Calibration data file written by the CPerspective class from IPL98" << endl;
				// output comments given in the parameter "Comments"
				if (pComments!=NULL)
				{
					int Pos=0;
					string ComStr(pComments);
					while((Pos=ComStr.find_first_of("\n"))!=-1)
					{
						OutStream << "# " << ComStr.substr(0,Pos) << endl;
						ComStr=ComStr.substr(Pos+1,ComStr.size()-Pos-1);
					}
					OutStream << "# " << ComStr.c_str() << endl;
				}				
				OutStream << "#\n# CPerspective class version" << endl;
				OutStream << "PerspectiveVersion " <<  m_Version << endl << endl;
				OutStream << "# Image dimensions " << endl;
				OutStream << "Width " << m_CenterX*2 << endl << "Height " << m_CenterY*2 << endl << endl;
				OutStream << "# Camera matrix" << endl;
				OutStream << "CameraMatrix" << endl;
				OutStream << m_Cam.a11 << "   " << m_Cam.a12 << "   " << m_Cam.a13 << "   " << m_Cam.a14 << endl;
				OutStream << m_Cam.a21 << "   " << m_Cam.a22 << "   " << m_Cam.a23 << "   " << m_Cam.a24 << endl;
				OutStream << m_Cam.a31 << "   " << m_Cam.a32 << "   " << m_Cam.a33 << "   " << m_Cam.a34 << endl;
				OutStream << m_Cam.a41 << "   " << m_Cam.a42 << "   " << m_Cam.a43 << "   " << m_Cam.a44 << endl;
				if (m_RadCalibrationPerformed==true)
				{
					OutStream << "\n# k distortion parameter" << endl;
					OutStream << "k " << m_k << endl;
				}
			}		
		}
		k_EmptyFileInfo(&FileInfo);
		k_EmptyString(&str);
		if (Path!=NULL)
			free(Path);
		if (FileNameExt!=NULL)
			free(FileNameExt);
		if (Ext!=NULL)
			free(Ext);
		return true;
	}	
}

double CPerspective::GetVersion()
{
	return m_Version;
}

/************************************************/
/********          Old methods           ********/
/***** only kept for backward compatibility *****/
/************************************************/

CPerspective::CPerspective()// : m_Version(1.50)
{
	ostringstream ost;
	ost << "CPerspective::CPerspective() Image size not initialized - old constructor" << IPLAddFileAndLine;
	CError::ShowMessage(IPL_WARNING,ost.str().c_str());
	m_CamMatrixCalibrated=false;
    m_CamParametersAvailable=false;
	m_RadCalibrationPerformed=false;
}

bool CPerspective::Calibrate(unsigned int np, const CPoint3D<FLOAT32>* pWorld, 
							 const CPoint2D<FLOAT32>* pCcd)
{
	T3DFloat* pAnsiWorld=(T3DFloat*)calloc(np,sizeof(T3DFloat));
	T2DFloat* pAnsiCcd=(T2DFloat*)calloc(np,sizeof(T2DFloat));
	for(unsigned int count=0; count<np; count++)
	{
		pAnsiWorld[count].x=pWorld[count].GetX();
		pAnsiWorld[count].y=pWorld[count].GetY();
		pAnsiWorld[count].z=pWorld[count].GetZ();
		pAnsiCcd[count].x=pCcd[count].GetX();
		pAnsiCcd[count].y=pCcd[count].GetY();
	}
	if (!k_Calibrate(np,pAnsiWorld,pAnsiCcd,&m_Cam))
	{
		ostringstream ost;
		ost << "CPerspective::Calibrate() Calibration failed" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		free(pAnsiWorld);
		free(pAnsiCcd);
		return false;
	}
	else
	{
		m_CamMatrixCalibrated=true;
		free(pAnsiWorld);
		free(pAnsiCcd);
		return true;
	}
}

bool CPerspective::CalibrateWithRadialDist(CCorresponding3D2DPoints& PointSets, const CStdImage& Img)
{
	bool ReturnValue;
	ReturnValue=k_CalibrateWithRadialDistOld(PointSets.GetT3D2DPointsPtr(),&m_Cam,&m_k,Img.GetConstTImagePtr());
//	ReturnValue=k_CalibrateWithRadialDist(m_np,pWorld,pCcd,&m_Mat,&m_k,Img.GetConstTImagePtr());
	if (ReturnValue==false)
	{
		ostringstream ost;
		ost << "CPerspective::CalibrateWithRadialDist() Failed calibration with radial distortion correction" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
	}
	else
	{
		m_RadCalibrationPerformed=true;
		m_CamMatrixCalibrated=true;
	}
	return ReturnValue;
}

bool CPerspective::Calc3DTo2DRad(const CPoint3D<FLOAT32>& w, CPoint2D<FLOAT32>& Pnt, const CStdImage& Img) const
{
	if (m_RadCalibrationPerformed==false)
	{
		ostringstream ost;
		ost << "CCalibration::Calc3DTo2DRad() Need to calibrate system first by calling CalibrateWithRadialDist()" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		T2DFloat P;
		T3DFloat wc;
		wc.x=w.GetX();
		wc.y=w.GetY();
		wc.z=w.GetZ();
		k_Calc3DTo2DRadOld(wc,&m_Cam,m_k,&P,Img.GetConstTImagePtr());
		Pnt.Set(P.x,P.y);
		return true;
	}
}

CPoint2D<int> CPerspective::GetMaxRadialDisplacement(const CStdImage& Img) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::MaxRadialDisplacement() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<int>(-1,-1);
	}
	else
	{
		T2DInt Pos;
		Pos=k_GetMaxRadialDisplacementOld(Img.GetConstTImagePtr(),m_k);
		return CPoint2D<int>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosRadRemoved(FLOAT32 x,FLOAT32 y,const CStdImage& Img) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosRadRemoved() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosRadRemovedOld(x,y,Img.GetConstTImagePtr(),m_k);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosRadRemoved(const CPoint2D<FLOAT32>& Pos,const CStdImage& Img) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosRadRemoved() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos1;
		Pos1=k_GetPosRadRemovedOld(Pos.GetX(),Pos.GetY(),Img.GetConstTImagePtr(),m_k);
		return CPoint2D<FLOAT32>(Pos1.x,Pos1.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosRadRemoved(FLOAT32 x, FLOAT32 y, FLOAT32 CenterX, FLOAT32 CenterY) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosRadRemovedC() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosRadRemovedCOld(x,y,CenterX,CenterY,m_k);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosRadRemoved(const CPoint2D<FLOAT32>& Pos, const CPoint2D<FLOAT32>& Center) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosRadRemovedC() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos1;
		Pos1=k_GetPosRadRemovedCOld(Pos.GetX(),Pos.GetY(),Center.GetX(),Center.GetY(),m_k);
		return CPoint2D<FLOAT32>(Pos1.x,Pos1.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosInverseRad(FLOAT32 xr, FLOAT32 yr, const CStdImage& Img) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosInverseRad() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosInverseRadOld(xr,yr,Img.GetConstTImagePtr(),m_k);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosInverseRad(const CPoint2D<FLOAT32>& PosRad, const CStdImage& Img) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosInverseRad() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosInverseRadOld(PosRad.GetX(),PosRad.GetY(),Img.GetConstTImagePtr(),m_k);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosInverseRad(FLOAT32 xr, FLOAT32 yr, FLOAT32 CenterX, FLOAT32 CenterY) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosInverseRad() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosInverseRadCOld(xr,yr,CenterX,CenterY,m_k);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

CPoint2D<FLOAT32> CPerspective::GetPosInverseRad(const CPoint2D<FLOAT32>& PosRad, const CPoint2D<FLOAT32>& Center) const
{
	if (m_RadCalibrationPerformed!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetPosInverseRad() Calibration not performet yet, call CalibrateWithRadialDist() first" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return CPoint2D<FLOAT32>(-1,-1);
	}
	else
	{
		T2DFloat Pos;
		Pos=k_GetPosInverseRadCOld(PosRad.GetX(),PosRad.GetY(),Center.GetX(),Center.GetY(),m_k);
		return CPoint2D<FLOAT32>(Pos.x,Pos.y);
	}
}

bool CPerspective::PrintErrors(const CCorresponding3D2DPoints& PointSets, const CStdImage& Img) const
{
	return ErrorsToStream(PointSets,Img,cout);
}

bool CPerspective::ErrorsToStream(const CCorresponding3D2DPoints& PointSets, const CStdImage& Img, ostream& Stream) const
{
	if (m_CamMatrixCalibrated!=true)
	{
		ostringstream ost;
		ost << "CPerspective::ErrorsToStream() Calibration not performet yet" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else if (PointSets.GetTotalPointSetsInUse()!=PointSets.GetTotalPointSets())
	{
		ostringstream ost;
		ost << "CPerspective::ErrorsToStream() Some of the point sets are not complete" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		float TotalErrorX=0;
		float TotalErrorY=0;
		if (m_RadCalibrationPerformed==true)
		{
			Stream << "**************** CPerspective errors (with radial correction) ******************\n";
		}
		else
		{
			Stream << "**************** CPerspective errors (no radial correction) ******************\n";
		}
		unsigned int i;
		for(i=0;i<PointSets.GetTotalPointSets();i++)
		{
			CPoint3D<FLOAT32> pnt3d=PointSets.GetPoint3D(i);
			CPoint2D<FLOAT32> pnt2d;
			if (m_RadCalibrationPerformed==true)
				Calc3DTo2DRad(pnt3d,pnt2d);
			else
				Calc3DTo2D(pnt3d,pnt2d);
			float xerror=pnt2d.GetX()-PointSets.GetPoint2D(i).GetX();
			float yerror=pnt2d.GetY()-PointSets.GetPoint2D(i).GetY();
			Stream.width(8); 
			Stream.setf(ios::left,ios::adjustfield);
			Stream << " Point " << i << " at " << PointSets.GetPoint2D(i);
			//cout.width(13); cout.setf(ios::left,ios::adjustfield);
			Stream << " Error: (" << xerror << "," << yerror << ")" << endl;
			TotalErrorX+=fabs(xerror);
			TotalErrorY+=fabs(yerror);
		}
		Stream << "Total mean error: (" << TotalErrorX/i << "," << TotalErrorY/i << ")" << endl;
		return true;
	}
}

bool CPerspective::GetErrors(const CCorresponding3D2DPoints& PointSets, vector<CPoint2D<FLOAT32> >& Errors)
{
	if (m_CamMatrixCalibrated!=true)
	{
		ostringstream ost;
		ost << "CPerspective::GetErrors() Calibration not performet yet" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else if (PointSets.GetTotalPointSetsInUse()!=PointSets.GetTotalPointSets())
	{
		ostringstream ost;
		ost << "CPerspective::GetErrors() Some of the point sets are not complete" << IPLAddFileAndLine;
		CError::ShowMessage(IPL_ERROR,ost.str().c_str());
		return false;
	}
	else
	{
		Errors.clear();
		unsigned int i;
		for(i=0;i<PointSets.GetTotalPointSets();i++)
		{
			CPoint3D<FLOAT32> pnt3d=PointSets.GetPoint3D(i);
			CPoint2D<FLOAT32> pnt2d;
			if (m_RadCalibrationPerformed==true)
				Calc3DTo2DRad(pnt3d,pnt2d);
			else
				Calc3DTo2D(pnt3d,pnt2d);
			float xerror=pnt2d.GetX()-PointSets.GetPoint2D(i).GetX();
			float yerror=pnt2d.GetY()-PointSets.GetPoint2D(i).GetY();
			Errors.push_back(CPoint2D<FLOAT32>(xerror,yerror));
		}
		return true;
	}
}

} // end ipl namespace
