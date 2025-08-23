// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GraphicCompression.pas' rev: 5.00

#ifndef GraphicCompressionHPP
#define GraphicCompressionHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Graphiccompression
{
//-- type declarations -------------------------------------------------------
typedef Shortint TSmoothRange;

typedef Byte *PByte;

struct TLZWTableEntry
{
	Word Index;
	Word Prefix;
	Byte Suffix;
	Byte FirstByte;
} ;

struct TCluster;
typedef TCluster *PCluster;

struct TCluster
{
	Word Index;
	TCluster *Next;
} ;

typedef Byte TByteStream[1];

typedef Byte *PByteStream;

class DELPHICLASS TLZW;
class PASCALIMPLEMENTATION TLZW : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Byte *FCodeAddress;
	Byte *FDestination;
	Byte FCodeLength;
	Byte FBorrowedBits;
	Word FCode;
	Word FOldCode;
	Word FLastEntry;
	unsigned FBytesRead;
	TLZWTableEntry FLZWTable[4096];
	TCluster *FClusters[4096];
	Word __fastcall GetNextCode(void);
	void __fastcall Initialize(void);
	void __fastcall ReleaseClusters(void);
	void __fastcall WriteBytes(const TLZWTableEntry &Entry);
	void __fastcall AddEntry(const TLZWTableEntry &Entry);
	TLZWTableEntry __fastcall Concatenation(Word PPrefix, Byte LastByte, Word Index);
	void __fastcall AddTableEntry(const TLZWTableEntry &Entry);
	void __fastcall WriteCodeToStream(Word Code);
	Word __fastcall CodeFromString(const TLZWTableEntry &Str);
	
public:
	void __fastcall DecodeLZW(void * Source, void * Dest);
	void __fastcall EncodeLZW(void * Source, void * Dest, unsigned &FByteCounts);
	void __fastcall SmoothEncodeLZW(void * Source, void * Dest, TSmoothRange SmoothRange, unsigned &FByteCounts
		);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TLZW(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TLZW(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word ClearCode = 0x100;
static const Word EOICode = 0x101;
extern PACKAGE int __fastcall DecodeRLE(const void * Source, const void * Target, unsigned Count, unsigned 
	ColorDepth);
extern PACKAGE int __fastcall EncodeRLE(const void * Source, const void * Target, int Count, int BPP
	);

}	/* namespace Graphiccompression */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Graphiccompression;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GraphicCompression
