// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'G32_Transforms.pas' rev: 5.00

#ifndef G32_TransformsHPP
#define G32_TransformsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <G32_Blend.hpp>	// Pascal unit
#include <G32.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace G32_transforms
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ETransformError;
class PASCALIMPLEMENTATION ETransformError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ETransformError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETransformError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETransformError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETransformError(int Ident, const System::TVarRec * Args
		, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETransformError(const AnsiString Msg, int AHelpContext
		) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETransformError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETransformError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETransformError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETransformError(void) { }
	#pragma option pop
	
};


typedef float TFloatMatrix[3][3];

class DELPHICLASS TTransformation;
class PASCALIMPLEMENTATION TTransformation : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	G32::TFloaTRect FSrcRect;
	void __fastcall SetSrcRect(const G32::TFloaTRect &Value);
	virtual void __fastcall Transform(int DstX, int DstY, /* out */ int &SrcX, /* out */ int &SrcY) = 0 
		;
	virtual void __fastcall Transform256(int DstX, int DstY, /* out */ int &SrcX256, /* out */ int &SrcY256
		) = 0 ;
	
protected:
	bool TransformValid;
	virtual void __fastcall PrepareTransform(void) = 0 ;
	
public:
	virtual Windows::TRect __fastcall GetTransformedBounds(void) = 0 ;
	__property G32::TFloaTRect SrcRect = {read=FSrcRect, write=SetSrcRect};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TTransformation(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TTransformation(void) { }
	#pragma option pop
	
};


class DELPHICLASS TAffineTransformation;
class PASCALIMPLEMENTATION TAffineTransformation : public TTransformation 
{
	typedef TTransformation inherited;
	
protected:
	int A;
	int B;
	int C;
	int D;
	int E;
	int F;
	virtual void __fastcall PrepareTransform(void);
	virtual void __fastcall Transform(int DstX, int DstY, /* out */ int &SrcX, /* out */ int &SrcY);
	virtual void __fastcall Transform256(int DstX, int DstY, /* out */ int &SrcX256, /* out */ int &SrcY256
		);
	
public:
	float Matrix[3][3];
	__fastcall virtual TAffineTransformation(void);
	virtual Windows::TRect __fastcall GetTransformedBounds();
	void __fastcall Clear(void);
	void __fastcall Rotate(float Cx, float Cy, float Alpha);
	void __fastcall Skew(float Fx, float Fy);
	void __fastcall Scale(float Sx, float Sy);
	void __fastcall Translate(float Dx, float Dy);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TAffineTransformation(void) { }
	#pragma option pop
	
};


class DELPHICLASS TProjectiveTransformation;
class PASCALIMPLEMENTATION TProjectiveTransformation : public TTransformation 
{
	typedef TTransformation inherited;
	
private:
	float Wx0;
	float Wx1;
	float Wx2;
	float Wx3;
	float Wy0;
	float Wy1;
	float Wy2;
	float Wy3;
	void __fastcall SetX0(float Value);
	void __fastcall SetX1(float Value);
	void __fastcall SetX2(float Value);
	void __fastcall SetX3(float Value);
	void __fastcall SetY0(float Value);
	void __fastcall SetY1(float Value);
	void __fastcall SetY2(float Value);
	void __fastcall SetY3(float Value);
	
protected:
	float M[3][3];
	virtual void __fastcall PrepareTransform(void);
	virtual void __fastcall Transform(int DstX, int DstY, /* out */ int &SrcX, /* out */ int &SrcY);
	virtual void __fastcall Transform256(int DstX, int DstY, /* out */ int &SrcX256, /* out */ int &SrcY256
		);
	
public:
	virtual Windows::TRect __fastcall GetTransformedBounds();
	__property float X0 = {read=Wx0, write=SetX0};
	__property float X1 = {read=Wx1, write=SetX1};
	__property float X2 = {read=Wx2, write=SetX2};
	__property float X3 = {read=Wx3, write=SetX3};
	__property float Y0 = {read=Wy0, write=SetY0};
	__property float Y1 = {read=Wy1, write=SetY1};
	__property float Y2 = {read=Wy2, write=SetY2};
	__property float Y3 = {read=Wy3, write=SetY3};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TProjectiveTransformation(void) : TTransformation() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TProjectiveTransformation(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE float IdentityMatrix[3][3];
extern PACKAGE void __fastcall BlockTransfer(G32::TBitmap32* Dst, int DstX, int DstY, G32::TBitmap32* 
	Src, const Windows::TRect &SrcRect, G32::TDrawMode CombineOp, G32::TPixelCombineEvent CombineCallBack
	);
extern PACKAGE void __fastcall StretchTransfer(G32::TBitmap32* Dst, const Windows::TRect &DsTRect, G32::TBitmap32* 
	Src, const Windows::TRect &SrcRect, G32::TStretchFilter StretchFilter, G32::TDrawMode CombineOp, G32::TPixelCombineEvent 
	CombineCallBack);
extern PACKAGE void __fastcall Transform(G32::TBitmap32* Dst, G32::TBitmap32* Src, TTransformation* 
	Transformation);
extern PACKAGE void __fastcall SetBorderTransparent(G32::TBitmap32* ABitmap, const Windows::TRect &ARect
	);

}	/* namespace G32_transforms */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace G32_transforms;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// G32_Transforms
