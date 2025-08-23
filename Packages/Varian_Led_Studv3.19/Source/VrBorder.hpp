// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrBorder.pas' rev: 5.00

#ifndef VrBorderHPP
#define VrBorderHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrborder
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrBorderStyle { bsLowered, bsRaised };
#pragma option pop

#pragma option push -b-
enum TVrBorderShape { bsBox, bsFrame, bsTopLine, bsBottomLine, bsLeftLine, bsRightLine, bsSpacer };
#pragma option pop

class DELPHICLASS TVrBorder;
class PASCALIMPLEMENTATION TVrBorder : public Vrcontrols::TVrGraphicControl 
{
	typedef Vrcontrols::TVrGraphicControl inherited;
	
private:
	TVrBorderStyle FStyle;
	TVrBorderShape FShape;
	Graphics::TColor FShadowColor;
	Graphics::TColor FHighlightColor;
	void __fastcall SetStyle(TVrBorderStyle Value);
	void __fastcall SetShape(TVrBorderShape Value);
	void __fastcall SetShadowColor(Graphics::TColor Value);
	void __fastcall SetHighlightColor(Graphics::TColor Value);
	
protected:
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrBorder(Classes::TComponent* AOwner);
	
__published:
	__property TVrBorderShape Shape = {read=FShape, write=SetShape, default=1};
	__property TVrBorderStyle Style = {read=FStyle, write=SetStyle, default=1};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, default=32768};
		
	__property Graphics::TColor HighlightColor = {read=FHighlightColor, write=SetHighlightColor, default=65280
		};
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property ParentShowHint ;
	__property ShowHint ;
	__property Visible ;
public:
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TVrBorder(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrborder */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrborder;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrBorder
