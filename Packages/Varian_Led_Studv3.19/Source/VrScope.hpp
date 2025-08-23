// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrScope.pas' rev: 5.00

#ifndef VrScopeHPP
#define VrScopeHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
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

namespace Vrscope
{
//-- type declarations -------------------------------------------------------
typedef Shortint TVrBaseOffsetInt;

#pragma option push -b-
enum TVrScopeStyle { ssLines, ssBars };
#pragma option pop

class DELPHICLASS TVrScopePen;
class PASCALIMPLEMENTATION TVrScopePen : public Graphics::TPen 
{
	typedef Graphics::TPen inherited;
	
public:
	__fastcall TVrScopePen(void);
	
__published:
	__property Color ;
public:
	#pragma option push -w-inl
	/* TPen.Destroy */ inline __fastcall virtual ~TVrScopePen(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrScope;
class PASCALIMPLEMENTATION TVrScope : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FMin;
	int FMax;
	Vrclasses::TVrBevel* FBevel;
	TVrScopePen* FPen;
	int FGridSize;
	TVrBaseOffsetInt FBaseOffset;
	Graphics::TColor FLineColor;
	int FLineWidth;
	Graphics::TColor FBaseLineColor;
	int FFrequency;
	int FBufferSize;
	TVrScopeStyle FStyle;
	int BaseLineInt;
	int hStep;
	Windows::TRect ViewPort;
	Graphics::TBitmap* LineImage;
	Vrclasses::TVrIntList* LineData;
	void __fastcall SetMin(int Value);
	void __fastcall SetMax(int Value);
	void __fastcall SetGridSize(int Value);
	void __fastcall SetBaseOffset(TVrBaseOffsetInt Value);
	void __fastcall SetLineColor(Graphics::TColor Value);
	void __fastcall SetBaseLineColor(Graphics::TColor Value);
	void __fastcall SetLineWidth(int Value);
	void __fastcall SetFrequency(int Value);
	void __fastcall SetBufferSize(int Value);
	void __fastcall SetPen(TVrScopePen* Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetStyle(TVrScopeStyle Value);
	void __fastcall BevelChanged(System::TObject* Sender);
	void __fastcall PenChanged(System::TObject* Sender);
	
protected:
	void __fastcall StepIt(void);
	void __fastcall PaintGrid(void);
	void __fastcall PaintLineGraph(void);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrScope(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrScope(void);
	void __fastcall Clear(void);
	void __fastcall AddValue(int Value);
	
__published:
	__property int Max = {read=FMax, write=SetMax, default=100};
	__property int Min = {read=FMin, write=SetMin, default=0};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property TVrScopePen* Pen = {read=FPen, write=SetPen};
	__property int GridSize = {read=FGridSize, write=SetGridSize, default=16};
	__property TVrBaseOffsetInt BaseOffset = {read=FBaseOffset, write=SetBaseOffset, default=50};
	__property Graphics::TColor LineColor = {read=FLineColor, write=SetLineColor, default=32768};
	__property Graphics::TColor BaseLineColor = {read=FBaseLineColor, write=SetBaseLineColor, default=65280
		};
	__property int LineWidth = {read=FLineWidth, write=SetLineWidth, default=1};
	__property int Frequency = {read=FFrequency, write=SetFrequency, default=1};
	__property int BufferSize = {read=FBufferSize, write=SetBufferSize, default=999};
	__property TVrScopeStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property Align ;
	__property Anchors ;
	__property DragKind ;
	__property DragCursor ;
	__property DragMode ;
	__property Color ;
	__property Constraints ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopUpMenu ;
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

}	/* namespace Vrscope */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrscope;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrScope
