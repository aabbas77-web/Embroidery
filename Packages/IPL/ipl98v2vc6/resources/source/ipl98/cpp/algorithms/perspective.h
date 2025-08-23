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

#ifndef _IPL98_PERSPECTIVE_H
#define _IPL98_PERSPECTIVE_H

#include "../std_image.h"
#include "../corresponding_3d2d_points.h"
#include "../../kernel_c/algorithms/kernel_perspective.h"
#include "../../../points/point2d.h"
#include "../../../points/point3d.h"
#include <vector>

namespace ipl{ // use namespace if C++

using std::vector;

/** CPerspective Camera calibration and 3D->2D/2D->3D perspective methods, Last updated 1/11/2002.
	Contains a normal linear camera calibration, corresponding 3D-2D points must be
	available as input to the calibration routine. In addition to the normal linear calibration,
	a radial distortion	parameter k can be estimated by calling the method CalibrateWithRadialDist(). 
	The distortion is described as: Dx=kx(x^2+y^2) and Dy=ky(x^2+y^2), where the point (x,y) is
	according to the center of the image. It could be discussed if the optical center (xh,yh) should
	be used instead, but for various reasons we use the image center at the moment. A set of methods 
	is provided for dealing with the radial distortion after calibration, most important are:
	Calc3DTo2DRad(), RemoveRadialDistortion(), GetPosRadRemoved(), and GetPosInverseRad(). With these
	methods it is possible to find correspondance between image points and 3D points including the
	radial distortion parameter, when using the same camera. Example:

	\verbatim
	// The container holding the corresponding 3D-2D values.
	CCorresponding3D2DPoints PointSets;

	// Insert some code that fill out the PointSets variable with at least six sets
	// .... 

	// Creates a CPerspective object, setting image size
	CPerspective Persp(768,576);

	if (Persp.CalibrateWithRadialDist(PointSets)==false)
	{
		// print the calibration result
		cout << Persp << endl;
		cout << "Creating image without radial distortion..." << endl;
		CImage Source,Dest;
		Source.Load("a_source_image_to_be_interpreted.bmp");
		// Remove radial distortion from whole image
		// Note: It is a time consuming operation, if possible stay in original
		// image and use GetPosRadRemoved() to get positions without radial
		// distortion
		Persp.RemoveRadialDistortion(Dest,Img,false);
		// Dest now contains image without radial distortion
		Dest.Save("NoRadialDistortion.bmp");
		// let's say an algorithm finds a relevant point P in Dest
		CPoint2D<FLOAT32> P(100,200); // A point found in Dest
		// Can now get direction in 3D world coordinates
		CPoint3D<FLOAT32> Dir;
		Persp.Direction(P,Dir);
		// Position in original image (POriginal) can also be found
		CPoint2D<FLOAT32> POriginal;
		POriginal=Persp.GetPosInverseRad(P);
	}
	else
		cout << "Calibration failed" << endl;
	\endverbatim

	Note: Since version 1.34, this class has undergone a major rewrite. The image size is now given
	to the constructor. A bug fix means that the radial distortion parameter found is better, it is 
	highly recommended to use versions of this class later than 1.34. To preserve backward compatibility,
	the old methods are still available - but don't use them in your future	programs, stick to the new 
	ones. Documentation for old methods are only available in the header file, not on the web pages.

	This class is part of the Image Processing Library <a href="http://www.mip.sdu.dk/ipl98">IPL98</a>.
	\class CPerspective ipl98/cpp/algorithms/perspective.h
	@version 1.50
	@author Ivar Balslev (ivb@mip.sdu.dk), Brian Kirstein (kirstein@protana.com) and
		René Dencker Eriksen (edr@mip.sdu.dk) */
class CPerspective{
	public: // attributes
		/** True if camera parameters has been calculated by MatrixToParameters(). 
			@see MatrixToParameters */
        bool m_CamParametersAvailable; // added by kirstein@protana.com
		/** A C structure containing the camera parameters calculated by the method
			MatrixToParameters(), see the C-documentation for members of the structure. */
        TCameraParameters m_Par; // added by kirstein@protana.com
	protected: // attributes
		/** camera parameter containing the linear calibrated values. */
		TCameraMatrix m_Cam;
		/// set to true if any of the calibration methods or the load method succeeds.
		bool m_CamMatrixCalibrated;
		/** true if CalibrateWithRadialDist() succeded or the load method found a radial value. */
		bool m_RadCalibrationPerformed;
		/** the radial distortion parameter calculated by CalibrateWithRadialDist() */
		double m_k;
		/** Half image dimension in X-direction. Set by constructor. */
		FLOAT32 m_CenterX;
		/** Half image dimension in Y-direction. Set by constructor. */
		FLOAT32 m_CenterY;
		/** Current version of this class, defined in perspective.cpp. */
		static const double m_Version;
	public: // methods
		/** Constructor setting the image size to be used in this object.
			@param Img Must contain an image with dimensions to be used in this object,
				if image not available yet, call other constructor passing image dimensions
				as scalars. */
		CPerspective(const CStdImage& Img);
		/** Constructor setting the image size to be used in this object.
			@param Width Width of images to be used for this object.
			@param Height Height of images to be used for this object. */
		CPerspective(unsigned int Width, unsigned int Height);
		/** Same as constructor CPerspective(Width,Height), except
			image dimensions are given as a CPoint2D<unsigned int> type. */
		CPerspective(CPoint2D<unsigned int> Dimensions);
		/// default destructor
		~CPerspective();

		/** Overloading of assignment operator. All information is copied to the 
			destination. Previous data in this object are destroyed. An error is
			produced if both sides of the assignment operator is the same object. */
		CPerspective& operator=(const CPerspective& Source);

		/** Calibrates the camera matrix as given in Gonzalez & Woods page 67. This
			is a simple linear calibration, call CalibrateWithRadialDist() to get
			a calibration with radial distortion included. 3D world coordinates	and 
			corresponding 2D ccd coordinates are given in parameter in order to
			calibrate. If succesfull, parameters are calculated by calling
			MatrixToParameters().
			@param PointSets 3D and 2D corresponding coordinates, all entries must be
				complete, ie. an entry where either the 2D or 3D point is not used is
				not accepted.
			@return False, if corresponding point sets is less than 6, or if the
					PointSets contains non complete entries.
			@see CalibrateWithRadialDist
			@see MatrixToParameters */
		bool Calibrate(const CCorresponding3D2DPoints& PointSets);

		/** Sets all parameters in this class, previous values are destroyed. 
			The internal attributes m_CamMatrixCalibrated and
			m_RadCalibrationPerformed are set to true. Note: Camera parameters are
			not calculated, must call MatrixToParameters() to make them available. */
		bool Set(const TCameraMatrix& Cam, double k, unsigned int Width, unsigned Height);
		/** Sets the camera matrix attribute to the values suplied in Cam. Use this method
			if you want to provide an external camera matrix to this class. The internal
			attribute m_CamMatrixCalibrated is set to true and m_RadCalibrationPerformed is
			set to false.
			@param Cam Camera matrix, members are a11, a12, .... a44. */
		void SetCameraMatrix(const TCameraMatrix& Cam);

		/** Sets the camera matrix attribute to the values suplied in Cam and the radial
			distortion value m_k to the suplied k. Use this method
			if you want to provide an external camera matrix and radial distortion parameter
			to this class. The internal	attributes m_CamMatrixCalibrated and
			m_RadCalibrationPerformed are set to true.
			@param Cam Camera matrix, members are a11, a12, .... a44
			@param k Radial distortion parameter */
		void SetCameraMatrixAndRadDistortion(const TCameraMatrix& Cam, double k);

		/** Finds the 2D position in image with origo in upper left corner, from a given
			3D position and the precalculated camera matrix. The method Calibrate() must
			be called first.
			@param w World coordinate.
			@param Pnt Position in image returned in this parameter.
			@return False, if the camera matrix has not been calculated.
			@see Calc3DTo2DRad */
		bool Calc3DTo2D(const CPoint3D<FLOAT32>& w, CPoint2D<FLOAT32>& Pnt) const;

		/** Calculates direction from p through Pinhole.
			@param p Position in 2D image with origo in upper left corner. If radial
				distortion is included in the calibration, the user must ensure that
				p is a position without radial distortion.
			@param Dir 3D direction returned in this parameter. The vector
				is normalized, i.e. has length one.
			@return False, if the camera matrix has not been calculated. */
		bool Direction(const CPoint2D<FLOAT32>& p,CPoint3D<FLOAT32>& Dir) const;

		/** Same as Pinhole but here the 3D point is returned directly, the
			user must asure that the parameters are available.
			@return Pinhole world coordinate. */
		CPoint3D<FLOAT32> GetPinHole() const;

		/** Calculates the pinhole world coordinate.
			@param PinHole Pinhole world coordinate returned in this parameter.
			@return False, if camera parameters has not yet been calculated. */
		bool PinHole(CPoint3D<FLOAT32>& PinHole) const;

		/** Returns the radial distortion parameter contained in the attribute m_k.
			Note: If calibration with radial distortion has not yet been performed
			the value is undefined. Use RadCalibrationPerformed() to check if it is available.*/
		inline double GetRadDistParameter() const;

		/** Performs a normal calibration as the corresponding Calibrate() method.
			In addition to that a radial distortion parameter k is estimated, see general 
			comments for more information. Note: If you don't want
			distortion corrections just use the normal Calibrate() method.
			If succesfull, parameters are calculated by calling MatrixToParameters().
			@param PointSets Contains the sets of corresponding 2D and 3D coordinates,
				at least 6 must be present.
			@return False, if corresponding point sets is less than 6, or if the
					PointSets contains non complete entries.
			@see MatrixToParameters */
		bool CalibrateWithRadialDist(CCorresponding3D2DPoints& PointSets);

		/** Finds the 2D position in image from a given 3D position, the camera matrix and
			the distortion parameter k. Use this function when working with an image not
			corrected for the radial distortion and a camera matrix and k-value calculated
			by one of the functions CalibrateWithRadialDist() or FindMarksAutoGlobalThreshold().
			For a given 3D world position you will get the corresponding point in your
			original radial distorted image.
			@param w World coordinate.
			@param Pnt Position in image with origo in upper left corner, returned in this parameter.
			@return False, if calibration with radial distortion has not been performed.
			@see Calc3DTo2D */
		bool Calc3DTo2DRad(const CPoint3D<FLOAT32>& w, CPoint2D<FLOAT32>& Pnt) const;

		/**	Returns the maximum radial distortion displacement for a postion in image with
			given distortion parameter k. Done by displacing a corner position which is the
			position furthest away from center.
			@return Maximum displacement relative to center of image. */
		CPoint2D<int> GetMaxRadialDisplacement() const;

		/** Removes the radial distortion k from the image.
			@param Dest Destination of new image, may be the same as Source. Note:
				In case of same source and destination the algorithm is a bit slower.
			@param Source Source image, may be the same as Dest. Note:
				In case of same source and destination the algorithm is a bit slower.
			@param PreserveImageSize if true, the destination image has same dimensions as source.
				Otherwise the new image will have the dimension needed to represent the radial corrected
				image without loss of information.
			@return False, if Img is not an 8 bit gray tone image. */
		bool RemoveRadialDistortion(CStdImage& Dest, CStdImage& Source, bool PreserveImageSize);

		/** Removes the radial distortion from the image with an external calculated k value.
			When using this method, the camera need not be calibrated with the methods
			in this class.
			@param Dest Destination of new image, may be the same as Source. Note:
				In case of same source and destination the algorithm is a bit slower.
			@param Source Source image, may be the same as Dest. Note:
				In case of same source and destination the algorithm is a bit slower.
			@param k The radial distortion parameter. 
			@param PreserveImageSize if true, the destination image has same dimensions as source.
				Otherwise the new image will have the dimension needed to represent the radial corrected
				image without loss of information.
			@return False, if a radial calibration has not been performed yet. */
		bool RemoveRadialDistortionExtK(CStdImage& Dest, CStdImage& Source, double k, bool PreserveImageSize);

		/** Changes the image dimensions used in this class. When calling this, all previous
			calibration is canceled since the radial distortion parameter was found according
			to original image center, hence a new calibration is needed.
			@return False, if Width or Height is zero. Only available in C++. */
		bool SetImageDimensions(unsigned int Width, unsigned int Height);

		/** Same as SetImageDimensions(Width,Height), except width and height is given 
			as a CPoint2D type. */
		bool SetImageDimensions(CPoint2D<unsigned int> Dimensions);

		/** Returns the image dimensions set for this class. Only available in C++. */
		void GetImageDimensions(unsigned int &Width, unsigned int &Height) const;

		/** Returns the image dimensions set for this class. Only available in C++. */
		CPoint2D<unsigned int> GetImageDimensions() const;

		/** Check if a calibration has been performed, i.e. either Calibrate()
			or CalibrateWithRadialDist().
			@return true, if a calibration has been performed. */
		bool CalibrationPerformed() const;

		/** Check if a radial calibration has been performed.
			@return true, if a radial calibration has been performed */
		bool RadCalibrationPerformed() const;

		/** For a given position (x,y) a new radial corrected position is returned, that is the position
			in a corresponding image without radial distortions. The inverse correction is
			performed by InverseRadialMove.
			@param x The position in horisontal direction to be corrected. Origo in upper left corner.
			@param y The position in vertical direction to be corrected. Origo in upper left corner.
			@return Radial corrected 2d position.
			@see InverseRadialMove */
		CPoint2D<FLOAT32> GetPosRadRemoved(FLOAT32 x,FLOAT32 y) const;

		/** Same as GetPosRadRemoved, but here parameters are given as CPoint2D types.
			@param Pos The position to be corrected.
			@return Radial corrected 2d position. Origo in upper left corner.
			@see GetPosRadRemoved */
		CPoint2D<FLOAT32> GetPosRadRemoved(const CPoint2D<FLOAT32>& Pos) const;

		/** For a given position (x,y) a new inverse radial corrected position is returned, 
			that is the position in a corresponding image with radial distortions. Center of
			radial distortion is assumed to be center of image. This functionality is the
			opposite of GetPosRadRemoved().
			@param xr The position in horisontal direction. Origo in upper left corner.
			@param yr The position in vertical direction. Origo in upper left corner.
			@return Inverse radial corrected 2d position. Origo in upper left corner.
			@see GetPosRadRemoved */
		CPoint2D<FLOAT32> GetPosInverseRad(FLOAT32 xr, FLOAT32 yr) const;
		
		/** Same as GetPosInverseRad, but here parameters are given as CPoint2D types.
			@param Pos The position to be corrected. Origo in upper left corner.
			@return Inverse radial corrected 2d position. Origo in upper left corner.
			@see GetPosInverseRad */
		CPoint2D<FLOAT32> GetPosInverseRad(const CPoint2D<FLOAT32>& PosRad) const;

		/** Returns the camera matrix values contained in m_Cam at (i,j) starting in 
			upper left corner with index (1,1) as in Gonzales & Woods.
			@param i coloumn index.
			@param j row index.
			@return Value at (i,j) in camera matrix. */
		FLOAT32 GetCamMatrix(unsigned short i, unsigned short j) const;

		/** Gets the camera matrix pointer to the attribute m_Cam. Use this method to manipulate
			the camera matrix on your own. The fields starts from "a11" and goes to "a44".
			Note: Use RadCalibration() to check if it is available.
			@return The camera matrix.
			@see GetConstTCameraMatrixPtr */
		inline TCameraMatrix* GetTCameraMatrixPtr();

		/** Gets the constant camera matrix pointer to the attribute m_Cam. Use this method to access
			the camera matrix directly. The fields starts from "a11" and goes to "a44".
			Note: Use RadCalibration() to check if it is available.
			@return The camera matrix.
			@see GetTCameraMatrixPtr */
		inline const TCameraMatrix* GetConstTCameraMatrixPtr() const;

		/** Print the camera matrix contained in the m_Cam attribute to stdout.
			@param WithIndexes True to print indexes as given in Gonzalez & Woods p. 76 */
		void PrintCameraMatrix(bool WithIndexes) const;

		/** Prints the errors for each point to cout, done by calling the method ErrorsToStream().
			@return False, if a calibration has not been performed yet.
			@see ErrorsToStream
			@see GetErrors */
		bool PrintErrors(const CCorresponding3D2DPoints& PointSets) const;

		/** Prints the errors for each point to "stream" when the 3D world points are
			projected to image points using the camera matrix m_Cam (including radial
			distortion correction if it has been performed) and	compared to the found
			2D points in the parameter PointSets.
			@param PointSets Corresponding 3D-2D point sets.
			@param Stream The ostream to stream the output to.
			@return False, if a calibration has not been performed yet.
			@see GetErrors */
		bool ErrorsToStream(const CCorresponding3D2DPoints& PointSets, ostream& Stream) const;

		/** Returns a list of errors, in the Error parameter, for each point when the 3D world 
			points are projected to image points using the camera matrix and radial distortion
			parameter (if radial calibration has been performed. For visual inspection of errors
			call PrintErrors() or ErrorsToStream().
			@param PointSets Corresponding 3D-2D point sets.
			@param Errors A vector containing all errors, previous content of the vector is deleted.
			@return False, if no calibration is available.
			@see PrintErrors()
			@see ErrorsToStream()
			@version 0.8 */
		bool GetErrors(const CCorresponding3D2DPoints& PointSets, vector<CPoint2D<FLOAT32> >& Errors);

		/** Prints the camera parameters contined in the m_Par attribute to "stream".
			These parameters are calculated by the method MatrixToParameters(), if
			it has not yet been calculated an error is streamed instead.
			@param Stream The ostream to stream the output to.
			@return False, if a calibration and MatrixToParameters() has not been performed yet. */
		bool CamParametersToStream(ostream& Stream) const;

		/** writes the camera matrix data to stream and the camera parameters by calling
			CamParametersToStream.
			@see CamParametersToStream */
		friend ostream& operator<<(ostream& s,const CPerspective& Persp);

		/** Returns true, if MatrixToParameters has been successfully called. */
		bool ParametersAvailable() const;

        /** Derives the camera parameters from a precalculated camera
            matrix using the method presented in the PhD Thesis
            "Industrial Vision" by Ole Knudsen, 1997, chapter 2.2.
			The results are stored in the attribute m_Par. In addition the public attribute
			m_CamParametersAvailable is set to true.
	        @return False, if the camera matrix has not been calculated.
            @version 0.6
            @author Implementation by Brian Kirstein Ramsgaard (kirstein@protana.com).
			@see m_Par */
        virtual bool MatrixToParameters();

        /** Builds the camera matrix from the precalculated camera
            parameters using the method presented in the PhD Thesis
            "Industrial Vision" by Ole Knudsen, 1997, chapter 2.2.
            @return False, if camera parameters are not available.
            @version 0.6
            @author Implementation by Brian Kirstein Ramsgaard
                (kirstein@protana.com) */
        bool ParametersToMatrix();
		
		/** Load camera matrix and distortion parameter from file. Camera parameters are
			calculated, if loading succeeds, by calling MatrixToParameters. Tokens in file are:
			PerspectiveVersion, the perspective class version (double)
			Width, image width.
			Height, image heigh.
			CameraMatrix, the 4*4 camera matrix (12 doubles)
			k, distortion parameter (double). If not available the appropriate attributes
				is set in this class.
			If version of calibration file is different than this class version, a warning
			is given.
			Comment lines starts with a '#' character, can be placed everywhere.
			Note: This methods is only available for the C++ part.
			@param pPathAndFileName Name of file including extension and relative
				or absolute path.
			@return False, if file could not be opened or if the format is not correct.
			@version 0.9 */
		bool Load(const char* pPathAndFileName);

		/** Save camera matrix, distortion parameter and version number of this calibration
			class. If no calibration data available, a message is written to cerr. If radial
			distortion has not been calibrated, the distortion parameter is not written to file.
			Note: This methods is only available for the C++ part.
			@param pPathAndFileName Name of file and relative or absolute path. If no extension 
				is supplied in the filename a "cfg" extension is automatically added.
			@param Comments Extra comments to be added to the beginning of the file. No need
				to insert a leading '#', the method will do that. If you want more than one
				line use '\n' control character to split.
			@return False, if file could not be opened for writing or if no calibration
				data available.
			@version 0.9 */
		bool Save(const char* pPathAndFileName, const char* pComments=NULL) const;

		/** Returns the version of this class. */
		static double GetVersion();


		/** @name Old methods kept for backward compatibility.
			The following methods are only kept to ensure backward compatibility,
			it is strongly recommended to use other methods in this class. */
		//@{ 
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			default constructor */
		CPerspective();
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Calibrates the camera matrix given in Gonzalez & Woods page 67.
			@param np Number of 3D world cordinates given in the parameter array World.
			@param pWorld Array containing 3D world coordinates (must be same size as pCcd array).
			@param pCcd Array containing the 2D image points (must be same size as pWorld array).
			@return False, if np<6 or if one of the given parameters is a NULL pointer. */
		bool Calibrate(unsigned int np, const CPoint3D<FLOAT32>* pWorld, const CPoint2D<FLOAT32>* pCcd);
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Performs a normal calibration as the corresponding Calibrate() method.
			In addition to that a radial distortion parameter k is estimated, see general 
			comments for more information. Note: If you don't want
			distortion corrections just use the normal Calibrate() method.
			@param PointSets Contains the sets of corresponding 2D and 3D coordinates,
				at least 6 must be present.
			@param Img The method needs image to calculate the center (width/2, height/2).
			@return False, if corresponding point sets is less than 6, or if the
					PointSets contains non complete entries. */
		bool CalibrateWithRadialDist(CCorresponding3D2DPoints& PointSets, const CStdImage& Img);
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Finds the 2D position in image from a given 3D position, the camera matrix and
			the distortion parameter k. Use this function when working with an image not
			corrected for the radial distortion and a camera matrix and k-value calculated
			by one of the functions CalibrateWithRadialDist() or FindMarksAutoGlobalThreshold().
			For a given 3D world position you will get the corresponding point in your
			original radial distorted image.
			@param w World coordinate.
			@param Pnt Position in image returned in this parameter.
			@param Img The function needs the image to calculate the center (width/2, height/2).
			@return False, if calibration with radial distortion has not been performed.
			@see Calc3DTo2D */
		bool Calc3DTo2DRad(const CPoint3D<FLOAT32>& w, CPoint2D<FLOAT32>& Pnt, const CStdImage& Img) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Returns the maximum radial distortion displacement for a postion in image with
			given distortion parameter k. Done by displacing a corner position which is the
			position furthest away from center.
			@param Img The function needs the image to calculate the center (width/2, height/2).
			@return Maximum displacement relative to center of image. */
		CPoint2D<int> GetMaxRadialDisplacement(const CStdImage& Img) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			For a given position (x,y) a new radial corrected position is returned, that is the position
			in a corresponding image without radial distortions. The inverse correction is
			performed by InverseRadialMove.
			@param x The position in horisontal direction to be corrected.
			@param y The position in vertical direction to be corrected.
			@param Img The function needs the image to calculate the center (width/2, height/2).
			@return Radial corrected 2d position.
			@see InverseRadialMove */
		CPoint2D<FLOAT32> GetPosRadRemoved(FLOAT32 x,FLOAT32 y,const CStdImage& Img) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Same as GetPosRadRemoved, but here parameters are given as CPoint2D types.
			@param Pos The position to be corrected.
			@param Img The function needs the image to calculate the center (width/2, height/2).
			@return Radial corrected 2d position.
			@see GetPosRadRemoved */
		CPoint2D<FLOAT32> GetPosRadRemoved(const CPoint2D<FLOAT32>& Pos,const CStdImage& Img) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Same as GetPosRadRemoved, but here the center of image is given as parameters
			instead of an image.
			@param x The position in horisontal direction.
			@param y The position in vertical direction.
			@param CenterX Horisontal center (width/2 of image)
			@param CenterY Vertical center (height/2 of image).
			@return Radial corrected 2d position.
			@see GetPosRadRemoved */
		CPoint2D<FLOAT32> GetPosRadRemoved(FLOAT32 x,FLOAT32 y, FLOAT32 CenterX, FLOAT32 CenterY) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Same as GetPosRadRemoved, but here parameters are given as CPoint2D types.
			@param Pos The position to be corrected.
			@param Center Center of image.
			@return Radial corrected 2d position.
			@see GetPosRadRemoved */
		CPoint2D<FLOAT32> GetPosRadRemoved(const CPoint2D<FLOAT32>& Pos, const CPoint2D<FLOAT32>& Center) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			For a given position (x,y) a new inverse radial corrected position is returned, 
			that is the position in a corresponding image with radial distortions. Center of
			radial distortion is assumed to be center of image. This functionality is the
			opposite of GetPosRadRemoved().
			@param xr The position in horisontal direction.
			@param yr The position in vertical direction.
			@return Inverse radial corrected 2d position.
			@see GetPosRadRemoved */
		CPoint2D<FLOAT32> GetPosInverseRad(FLOAT32 xr, FLOAT32 yr, const CStdImage& Img) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Same as GetPosInverseRad, but here parameters are given as CPoint2D types.
			@param Pos The position to be corrected.
			@return Inverse radial corrected 2d position.
			@see GetPosInverseRad */
		CPoint2D<FLOAT32> GetPosInverseRad(const CPoint2D<FLOAT32>& PosRad, const CStdImage& Img) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Same as GetPosInverseRad, but here the center of image is given as parameters
			instead of an image.
			@param xr The position in horisontal direction.
			@param yr The position in vertical direction.
			@return Inverse radial corrected 2d position.
			@see GetPosInverseRad */
		CPoint2D<FLOAT32> GetPosInverseRad(FLOAT32 xr, FLOAT32 yr, FLOAT32 CenterX, FLOAT32 CenterY) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Same as GetPosInverseRad, but here parameters are given as CPoint2D types.
			@param Pos The position to be corrected.
			@return Inverse radial corrected 2d position.
			@see GetPosInverseRad */
		CPoint2D<FLOAT32> GetPosInverseRad(const CPoint2D<FLOAT32>& PosRad, const CPoint2D<FLOAT32>& Center) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Prints the errors for each point to cout, done by calling the method ErrorsToStream().
			@return False, if a calibration has not been performed yet.
			@see ErrorsToStream */
		bool PrintErrors(const CCorresponding3D2DPoints& PointSets, const CStdImage& Img) const;
		/* IMPORTANT: Only kept for backward compatibility, use other methods!
			Prints the errors for each point to "stream" when the 3D world points are
			projected to image points using the camera matrix m_Cam (including radial
			distortion correction if it has been performed) and	compared to the found
			2D points in the parameter PointSets.
			@param PointSets Corresponding 3D-2D point sets.
			@param Stream The ostream to stream the output to.
			@return False, if a calibration has not been performed yet. */
		bool ErrorsToStream(const CCorresponding3D2DPoints& PointSets, const CStdImage& Img, ostream& Stream) const;

		//@}

	private:
};

/////////////////////////////////////////////////
//// Inline methods
/////////////////////////////////////////////////

inline double CPerspective::GetRadDistParameter() const
{
	return m_k;
}

inline TCameraMatrix* CPerspective::GetTCameraMatrixPtr()
{
	return &m_Cam;
}

inline const TCameraMatrix* CPerspective::GetConstTCameraMatrixPtr() const
{
	return &m_Cam;
}

} // end namespace ipl

#endif //_IPL98_PERSPECTIVE_H
