// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'JAMAbout.pas' rev: 4.00

#ifndef JAMAboutHPP
#define JAMAboutHPP

#pragma delphiheader begin
#pragma option push -w-
#include <DsgnIntf.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Jamabout
{
//-- type declarations -------------------------------------------------------
typedef AnsiString TJamVersion;

class DELPHICLASS TJamVersionProperty;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TJamVersionProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual AnsiString __fastcall GetValue();
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TJamVersionProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TJamVersionProperty(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Jamabout */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Jamabout;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// JAMAbout
