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

#include "binary_image.h"
#include <algorithm>
#include "../../ipl98_general_functions.h"

namespace ipl {

using std::find;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBinaryImage::CBinaryImage() { ; }


CBinaryImage::CBinaryImage(int w, int h, CHoughBase::ORIGINTYPE OriginType) {
   m_width = w;
   m_height = h;
   this->SetOrigin(OriginType);
}


CBinaryImage::CBinaryImage(const CStdImage& Source, COLORTYPE Color, UINT8 Threshold, 
                           CHoughBase::ORIGINTYPE OriginType) {
   int x, y, p;

   m_width = Source.GetWidth();
   m_height = Source.GetHeight();

   this->SetOrigin(OriginType);
   bool color = false;
   if (Color == HIGHCOLOR) color = true;

   for (y=0; y<m_height; y++) {
      for (x=0; x<m_width; x++) {
         p = Source.GetPixelFast(x,y);
         if ((color)^(p>Threshold)) {
            CPoint2D<int> pixel(x,y);
            pixel.SetX(m_originOrientation.GetX()*(pixel.GetX()-m_originPosition.GetX()));
            pixel.SetY(m_originOrientation.GetY()*(pixel.GetY()-m_originPosition.GetY()));
            m_coord.push_back(pixel);
         }
      }
   }
}


CBinaryImage::~CBinaryImage() { ; }


//////////////////////////////////////////////////////////////////////
// Public methods
//////////////////////////////////////////////////////////////////////

int CBinaryImage::GetHeight() const { return m_height; }


int CBinaryImage::GetWidth() const { return m_width; }


int CBinaryImage::GetSize() const { return m_coord.size(); }


CPoint2D<int> CBinaryImage::GetPixel(int i) const { return m_coord[i]; }


void CBinaryImage::ToImage(CStdImage& image) {
   int n = m_coord.size();
   image.AllocFast(m_width, m_height, 8);
   image.Flush(255);
   CPoint2D<int> pixel;

   for (int i=0; i<n; i++) {
      pixel = m_coord[i];
      pixel.SetX(m_originOrientation.GetX()*pixel.GetX()+m_originPosition.GetX());
      pixel.SetY(m_originOrientation.GetY()*pixel.GetY()+m_originPosition.GetY());
      if (0<=pixel.GetX() && pixel.GetX()<m_width && 0<=pixel.GetY() && pixel.GetY()<m_height) {
         image.SetPixelFast(pixel.GetX(), pixel.GetY(), 0);
      }
   }
}


CPoint2D<int> CBinaryImage::OriginConvert(const CPoint2D<int>& pixel) {
   CPoint2D<int> outPixel;
   outPixel.SetX(m_originOrientation.GetX()*pixel.GetX()+m_originPosition.GetX());
   outPixel.SetY(m_originOrientation.GetY()*pixel.GetY()+m_originPosition.GetY());
   return outPixel;
}


void CBinaryImage::AddPixel(const CPoint2D<int>& pixel) {
	std::vector<CPoint2D<int> >::iterator p;
   p = find(m_coord.begin(), m_coord.end(), pixel);
   if (p == m_coord.end()) {
      m_coord.push_back(pixel);
   }
}


void CBinaryImage::AddPixelFast(const CPoint2D<int>& pixel) { m_coord.push_back(pixel); }


void CBinaryImage::RemovePixel(int i) {
   m_coord[i] = m_coord[m_coord.size()-1];
   m_coord.resize(m_coord.size()-1);
}


bool CBinaryImage::RemovePixel(const CParameter2D<int>& p) {
   if (m_coord.size() <= 0) return false;
   std::vector<CPoint2D<int> >::iterator pos = m_coord.begin();
   
   while (pos != m_coord.end()) {
      pos = find(pos, m_coord.end(), p);
      if (pos == m_coord.end()) return false;
      else {
         *pos = m_coord[m_coord.size()-1];
         m_coord.resize(m_coord.size()-1);
      }
   }
   return true;
}


bool CBinaryImage::RemovePixelFast(const CParameter2D<int>& p) {
   if (m_coord.size() <= 0) return false;
   std::vector<CPoint2D<int> >::iterator pos = find(m_coord.begin(), m_coord.end(), p);
   if (pos == m_coord.end()) return false;
   else {
      *pos = m_coord[m_coord.size()-1];
      m_coord.resize(m_coord.size()-1);
      return true;
   }
}


bool CBinaryImage::RemovePixelRange(CParameter2D<int>& p, int range) {
//   CPoint2D<int> newpixel = p;
   int x, y;
   int x_s = p.GetX(), y_s = p.GetY();
   // Horisontal
   for (x=x_s-range; x<=x_s+range; x++) {
      p.SetX(x);
      this->RemovePixelFast(p);
   }
   // Vertical
   p.SetX(x_s);
   for (y=y_s-range; y<=y_s+range; y++) {
      p.SetY(y);
      this->RemovePixelFast(p);
   }
   p.Set(x_s,y_s);

   return true;
}


void CBinaryImage::RemoveLine1(const CParameter2D<float>& p, int Thickness)
{
	float C = (float) cos(p.GetX());
	float S = (float) sin(p.GetX());
	float rho = p.GetY();
	int x, y;
	
	CParameter2D<int> pixel;
	
	if (p.GetX() == 0.0f)
	{
		for (y=-m_originPosition.GetY(); y<m_originPosition.GetY(); y++)
		{
			x = Round((rho - y*S) / C);
			if (-m_originPosition.GetX()<=x && x<m_originPosition.GetX()) 
			{
				pixel.Set(x,y);
				bool b = this->RemovePixelRange(pixel, Thickness);
			}
		}
	}
	else
	{
		for (x=-m_originPosition.GetX(); x<m_originPosition.GetX(); x++)
		{
			y = Round((rho - x*C) / S);
			if (-m_originPosition.GetY()<=y && y<m_originPosition.GetY())
			{
				pixel.Set(x,y);
				bool b = this->RemovePixelRange(pixel, Thickness);
			}
		}
	}
}


void CBinaryImage::RemoveLine2(const CParameter2D<float>& p, int Thickness) {
   float C = (float) cos(p.GetX());
   float S = (float) sin(p.GetX());
   float rho = p.GetY()-Thickness;;
   int x, y;
   CParameter2D<int> pixel;

   while (rho<=p.GetY()+Thickness) {

      if (p.GetX() == 0.0f) {
         for (y=-m_originPosition.GetY(); y<m_originPosition.GetY(); y++) {
            x = Round((rho - y*S) / C);
            if (-m_originPosition.GetX()<=x && x<m_originPosition.GetX()) {
               pixel.SetX(x);
               pixel.SetY(y);
               bool b = this->RemovePixelFast(pixel);
            }
         }
      } else {
         for (x=-m_originPosition.GetX(); x<m_originPosition.GetX(); x++) {
            y = Round((rho - x*C) / S);
            if (-m_originPosition.GetY()<=y && y<m_originPosition.GetY()) {
               pixel.SetX(x);
               pixel.SetY(y);
               bool b = this->RemovePixelFast(pixel);            
            }
         }
      }

      rho+=0.25;
   }
}


void CBinaryImage::AddLine(const CParameter2D<float>& p) {
   float C = (float) cos(p.GetX());
   float S = (float) sin(p.GetX());
   float rho = p.GetY();

   CParameter2D<int> pixel;
   vector<int> points = this->ComputeIntersectionPoints(p);
   int dist = (int) sqrt(pow(points[0]-points[2],2.0)+pow(points[1]-points[3],2.0));
   cout << "DIST: " << dist << endl;

   float xi, yi, dx, dy;

   xi = points[0]; 
   yi = points[1];
   dx = (1.0f*points[2]-points[0])/dist;
   dy = (1.0f*points[3]-points[1])/dist;

   while (dist > 0) {
      xi += dx;
      yi += dy;
      if (-m_originPosition.GetX()<=xi && xi<m_originPosition.GetX() && 
          -m_originPosition.GetY()<=yi && yi<m_originPosition.GetY()) {
         pixel.SetX((int) xi);
         pixel.SetY((int) yi);
         m_coord.push_back(pixel);
      }
      dist--;
   }
}


void CBinaryImage::AddCircle(const CPoint3D<float>& p) {
   int perimeter = (int) 2*PI*p.GetZ();
   float theta = 0.0f;
   float dt = 1/p.GetZ();
   int x, y, z, xi, yi;
   x = p.GetX();
   y = p.GetY();
   z = p.GetZ();

   for (int i=0; i<perimeter; i++) {
      xi = x + z*cos(theta);
      yi = y + z*sin(theta);
      theta+=dt;
      this->AddPixel(CParameter2D<int>(xi,yi));
   }
}


void CBinaryImage::RemoveCircle(const CPoint3D<float>& p) {
   int perimeter = (int) 2*PI*p.GetZ();
   float theta = 0.0f;
   float dt = 1/p.GetZ();
   int x, y, z, xi, yi;
   x = p.GetX();
   y = p.GetY();
   z = p.GetZ();

   for (int i=0; i<perimeter; i++) {
      xi = x + z*cos(theta);
      yi = y + z*sin(theta);
      theta+=dt;
      RemovePixel(CParameter2D<int>(xi,yi));
   }
}


void CBinaryImage::RemoveCircleRange(const CPoint3D<float>& p, int i) {
   CPoint3D<float> q(p);
   int r;
   for (r = p.GetZ()-i; r<=p.GetZ()+i; r++) {
      if (r > 0) {
         q.SetZ(r);
         this->RemoveCircle(q);
      }
   }
}


vector<int> CBinaryImage::ComputeIntersectionPoints(const CParameter2D<float>& p) {
   CParameter2D<float>  left_line(0.0f,  m_originPosition.GetX());
   CParameter2D<float> right_line((float) PI,   m_originPosition.GetX());
   CParameter2D<float> lower_line((float) PI/2, m_originPosition.GetY());
   CParameter2D<float> upper_line((float) PI*3/2, m_originPosition.GetY());

   CPoint2D<float> left_intersection = left_line.NormalLineIntersection(p);
   CPoint2D<float> right_intersection = right_line.NormalLineIntersection(p);
   CPoint2D<float> lower_intersection = lower_line.NormalLineIntersection(p);
   CPoint2D<float> upper_intersection = upper_line.NormalLineIntersection(p);

   CPoint2D<float> p1, p2;

   int left = 2;

   if(left_intersection.GetY()>=-m_originPosition.GetY() && 
      left_intersection.GetY()<=m_originPosition.GetY() && left>0) {
      p1 = left_intersection;
      left--;
      //cout << "found LEFT" << endl;
   }
   if(right_intersection.GetY()>=-m_originPosition.GetY() && 
      right_intersection.GetY()<=m_originPosition.GetY() && left>0) { 
      if (left == 2) {
         p1 = right_intersection;
      } else if (left == 1) {
         p2 = right_intersection;
      }
      left--;
      //cout << "found RIGHT" << endl;
   }
   if(lower_intersection.GetX()>=-m_originPosition.GetX() && 
      lower_intersection.GetX()<=m_originPosition.GetX() && left>0) {
      if (left == 2) {
         p1 = lower_intersection;
      } else if (left == 1) {
         p2 = lower_intersection;
      }
      left--;
      //cout << "found LOWER" << endl;
   }
   if(upper_intersection.GetX()>=-m_originPosition.GetX() && 
      upper_intersection.GetX()<=m_originPosition.GetX() && left>0) {
      p2 = upper_intersection;
      left--;
      //cout << "found UPPER" << endl;
   }

   //cout << "P1 " << p1 << endl;
   //cout << "P2 " << p2 << endl;

   vector<int> points;
   points.push_back((int) p1.GetX());
   points.push_back((int) p1.GetY());
   points.push_back((int) p2.GetX());
   points.push_back((int) p2.GetY());
   return points;
}


CHoughBase::ORIGINTYPE CBinaryImage::GetOrigin() const { return m_origin; }


//////////////////////////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////////////////////////


void CBinaryImage::SetOrigin(CHoughBase::ORIGINTYPE OriginType) {
   m_origin = OriginType;

   int x, y, xd, yd;
   switch(OriginType) {
   case CHoughBase::LEFT_UPPER:
      x = 0;
      y = 0;
      xd = 1;
      yd = 1;
      break;
   case CHoughBase::CENTER_UP:
      x = (int) m_width/2;
      y = (int) m_height/2;
      xd = 1;
      yd = -1;
      break;
   case CHoughBase::CENTER_DOWN:
      x = (int) m_width/2;
      y = (int) m_height/2;
      xd = 1;
      yd = 1;
      break;
   default:
      x = (int) m_width/2;
      y = (int) m_height/2;
      xd = 1;
      yd = -1;
      break;
   }
 
   m_originPosition.SetX(x);
   m_originPosition.SetY(y);
   m_originOrientation.SetX(xd);
   m_originOrientation.SetY(yd);
}

} // end namespace ipl
