// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrLights.pas' rev: 5.00

#ifndef VrLightsHPP
#define VrLightsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vrlights
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrLightsState { lsGreen, lsYellow, lsRed };
#pragma option pop

typedef Set<TVrLightsState, lsGreen, lsRed>  TVrLightsStates;

typedef Set<TVrLightsState, lsGreen, lsRed>  TVrLightsVisible;

#pragma option push -b-
enum TVrLightsOrder { loGreenToRed, loRedToGreen };
#pragma option pop

#pragma option push -b-
enum TVrLightsType { ltGlassRounded, ltGlassRect, ltGlassSquare, ltGlassDiamond };
#pragma option pop

typedef Graphics::TBitmap* TVrLightsImages[2];

class DELPHICLASS TVrLights;
class PASCALIMPLEMENTATION TVrLights : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	TVrLightsStates FLedState;
	int FSpacing;
	TVrLightsOrder FOrder;
	Vrtypes::TVrOrientation FOrientation;
	TVrLightsType FLedType;
	int FNumLeds;
	TVrLightsVisible FLedsVisible;
	Graphics::TBitmap* FImages[2];
	int FImageWidth;
	int FImageHeight;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetLedState(TVrLightsStates Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetOrder(TVrLightsOrder Value);
	void __fastcall SetOrientation(Vrtypes::TVrOrientation Value);
	void __fastcall SetLedsVisible(TVrLightsVisible Value);
	void __fastcall SetLedType(TVrLightsType Value);
	
protected:
	virtual void __fastcall LoadBitmaps(void);
	void __fastcall DrawLed(int X, int Y, int Index, bool Active);
	void __fastcall DrawHori(void);
	void __fastcall DrawVert(void);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Change(void);
	
public:
	__fastcall virtual TVrLights(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrLights(void);
	
__published:
	__property TVrLightsStates LedState = {read=FLedState, write=SetLedState, default=0};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=5};
	__property TVrLightsOrder Order = {read=FOrder, write=SetOrder, default=0};
	__property Vrtypes::TVrOrientation Orientation = {read=FOrientation, write=SetOrientation, default=1
		};
	__property TVrLightsVisible LedsVisible = {read=FLedsVisible, write=SetLedsVisible, default=7};
	__property TVrLightsType LedType = {read=FLedType, write=SetLedType, default=1};
	__property Transparent ;
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Hint ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible ;
	__property OnClick ;
	__property OnContextPopup ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrlights */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrlights;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrLights
