// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrMeter.pas' rev: 5.00

#ifndef VrMeterHPP
#define VrMeterHPP

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

namespace Vrmeter
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrMeterScale;
class DELPHICLASS TVrMeter;
class PASCALIMPLEMENTATION TVrMeter : public Vrcontrols::TVrGraphicImageControl 
{
	typedef Vrcontrols::TVrGraphicImageControl inherited;
	
private:
	int FAngle;
	TVrMeterScale* FScale;
	int FMinValue;
	int FMaxValue;
	int FPosition;
	Graphics::TColor FNeedleColor;
	int FNeedleWidth;
	int FSpacing;
	int FLabels;
	int FLabelOffsetX;
	int FLabelOffsetY;
	Vrclasses::TVrBevel* FBevel;
	Graphics::TBitmap* FBackImage;
	Windows::TPoint FCenter;
	int FRadius;
	void __fastcall SetAngle(int Value);
	void __fastcall SetMinValue(int Value);
	void __fastcall SetMaxValue(int Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetNeedleColor(Graphics::TColor Value);
	void __fastcall SetNeedleWidth(int Value);
	void __fastcall SetBevel(Vrclasses::TVrBevel* Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetLabels(int Value);
	void __fastcall SetLabelOffsetX(int Value);
	void __fastcall SetLabelOffsetY(int Value);
	void __fastcall SetBackImage(Graphics::TBitmap* Value);
	void __fastcall BevelChanged(System::TObject* Sender);
	void __fastcall ScaleChanged(System::TObject* Sender);
	void __fastcall BackImageChanged(System::TObject* Sender);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	
protected:
	void __fastcall DrawScale(void);
	void __fastcall DrawNeedle(void);
	void __fastcall DrawLabels(void);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TVrMeter(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrMeter(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	
__published:
	__property int MaxValue = {read=FMaxValue, write=SetMaxValue, default=100};
	__property int MinValue = {read=FMinValue, write=SetMinValue, default=0};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property int Angle = {read=FAngle, write=SetAngle, default=40};
	__property TVrMeterScale* Scale = {read=FScale, write=FScale};
	__property Graphics::TColor NeedleColor = {read=FNeedleColor, write=SetNeedleColor, default=12632256
		};
	__property int NeedleWidth = {read=FNeedleWidth, write=SetNeedleWidth, default=1};
	__property Vrclasses::TVrBevel* Bevel = {read=FBevel, write=SetBevel};
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=20};
	__property int Labels = {read=FLabels, write=SetLabels, default=10};
	__property int LabelOffsetX = {read=FLabelOffsetX, write=SetLabelOffsetX, default=15};
	__property int LabelOffsetY = {read=FLabelOffsetY, write=SetLabelOffsetY, default=10};
	__property Graphics::TBitmap* BackImage = {read=FBackImage, write=SetBackImage};
	__property Align ;
	__property Anchors ;
	__property Constraints ;
	__property Caption ;
	__property Color ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Font ;
	__property Hint ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ParentFont ;
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


class PASCALIMPLEMENTATION TVrMeterScale : public Vrclasses::TVrPersistent 
{
	typedef Vrclasses::TVrPersistent inherited;
	
private:
	Graphics::TColor FColor1;
	Graphics::TColor FColor2;
	Graphics::TColor FColor3;
	int FEnlarge;
	int FPercent1;
	int FPercent2;
	int FTicks;
	int FHeightMax;
	int FHeightMin;
	bool FVisible;
	TVrMeter* Owner;
	void __fastcall SetColor1(Graphics::TColor Value);
	void __fastcall SetColor2(Graphics::TColor Value);
	void __fastcall SetColor3(Graphics::TColor Value);
	void __fastcall SetEnlarge(int Value);
	void __fastcall SetPercent1(int Value);
	void __fastcall SetPercent2(int Value);
	void __fastcall SetTicks(int Value);
	void __fastcall SetHeightMax(int Value);
	void __fastcall SetHeightMin(int Value);
	void __fastcall SetVisible(bool Value);
	
public:
	__fastcall TVrMeterScale(void);
	
__published:
	__property Graphics::TColor Color1 = {read=FColor1, write=SetColor1, default=32768};
	__property Graphics::TColor Color2 = {read=FColor2, write=SetColor2, default=65535};
	__property Graphics::TColor Color3 = {read=FColor3, write=SetColor3, default=255};
	__property int Enlarge = {read=FEnlarge, write=SetEnlarge, default=5};
	__property int Percent1 = {read=FPercent1, write=SetPercent1, default=61};
	__property int Percent2 = {read=FPercent2, write=SetPercent2, default=25};
	__property int Ticks = {read=FTicks, write=SetTicks, default=60};
	__property int HeightMax = {read=FHeightMax, write=SetHeightMax, default=8};
	__property int HeightMin = {read=FHeightMin, write=SetHeightMin, default=5};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrMeterScale(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrmeter */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrmeter;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrMeter
