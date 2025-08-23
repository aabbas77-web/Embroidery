// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GraphicEx.pas' rev: 5.00

#ifndef GraphicExHPP
#define GraphicExHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <GraphicCompression.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Graphicex
{
//-- type declarations -------------------------------------------------------
typedef unsigned TCardinalVector[1];

typedef unsigned *PCardinalVector;

class DELPHICLASS TSGIGraphic;
class PASCALIMPLEMENTATION TSGIGraphic : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
private:
	unsigned FStartPosition;
	unsigned *FRowStart;
	unsigned *FRowSize;
	void *FRowBuffer;
	Word FImageType;
	unsigned __fastcall InitStructures(Classes::TStream* Stream);
	void __fastcall GetRow(Classes::TStream* Stream, void * Buffer, unsigned Line, unsigned Component);
		
	
public:
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
public:
	#pragma option push -w-inl
	/* TBitmap.Create */ inline __fastcall virtual TSGIGraphic(void) : Graphics::TBitmap() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TBitmap.Destroy */ inline __fastcall virtual ~TSGIGraphic(void) { }
	#pragma option pop
	
};


class DELPHICLASS TAutodeskGraphic;
class PASCALIMPLEMENTATION TAutodeskGraphic : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
public:
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
public:
	#pragma option push -w-inl
	/* TBitmap.Create */ inline __fastcall virtual TAutodeskGraphic(void) : Graphics::TBitmap() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TBitmap.Destroy */ inline __fastcall virtual ~TAutodeskGraphic(void) { }
	#pragma option pop
	
};


typedef unsigned *PCardinal;

class DELPHICLASS TTIFFGraphic;
class PASCALIMPLEMENTATION TTIFFGraphic : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
private:
	System::TObject* FIFD;
	int FInternalPalette;
	void __fastcall Depredict1(void * StartPtr, unsigned Count);
	void __fastcall Depredict3(void * StartPtr, unsigned Count);
	void __fastcall Depredict4(void * StartPtr, unsigned Count);
	void __fastcall ScrambleBitmapPalette(Byte BPS, int Mode, Windows::PBitmapInfo BMPInfo);
	void __fastcall ScramblePalette(Byte BPS, int Mode);
	
public:
	__fastcall virtual TTIFFGraphic(void);
	__fastcall virtual ~TTIFFGraphic(void);
	void __fastcall SaveToTifFile(AnsiString FileName, bool Compressing);
	void __fastcall SaveToTifFileSLZW(AnsiString FileName, Graphiccompression::TSmoothRange SmoothRange
		);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream)/* overload */;
	HIDESBASE void __fastcall SaveToStream(Classes::TStream* Stream, bool Compressed)/* overload */;
};


class DELPHICLASS TTargaGraphic;
class PASCALIMPLEMENTATION TTargaGraphic : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
private:
	AnsiString FImageID;
	
public:
	HIDESBASE void __fastcall LoadFromResourceName(unsigned Instance, const AnsiString ResName);
	HIDESBASE void __fastcall LoadFromResourceID(unsigned Instance, int ResID);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream)/* overload */;
	HIDESBASE void __fastcall SaveToStream(Classes::TStream* Stream, bool Compressed)/* overload */;
	__property AnsiString ImageID = {read=FImageID, write=FImageID};
public:
	#pragma option push -w-inl
	/* TBitmap.Create */ inline __fastcall virtual TTargaGraphic(void) : Graphics::TBitmap() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TBitmap.Destroy */ inline __fastcall virtual ~TTargaGraphic(void) { }
	#pragma option pop
	
};


class DELPHICLASS TPCXGraphic;
class PASCALIMPLEMENTATION TPCXGraphic : public Graphics::TBitmap 
{
	typedef Graphics::TBitmap inherited;
	
public:
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
public:
	#pragma option push -w-inl
	/* TBitmap.Create */ inline __fastcall virtual TPCXGraphic(void) : Graphics::TBitmap() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TBitmap.Destroy */ inline __fastcall virtual ~TPCXGraphic(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TResamplingFilter { sfBox, sfTriangle, sfHermite, sfBell, sfSpline, sfLanczos3, sfMitchell };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Stretch(unsigned NewWidth, unsigned NewHeight, TResamplingFilter Filter
	, float Radius, Graphics::TBitmap* Source, Graphics::TBitmap* Target)/* overload */;
extern PACKAGE void __fastcall Stretch(unsigned NewWidth, unsigned NewHeight, TResamplingFilter Filter
	, float Radius, Graphics::TBitmap* Source)/* overload */;

}	/* namespace Graphicex */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Graphicex;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GraphicEx
