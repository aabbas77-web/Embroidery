// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrControls.pas' rev: 5.00

#ifndef VrControlsHPP
#define VrControlsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrSysUtils.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <VrConst.hpp>	// Pascal unit
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

namespace Vrcontrols
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TGraphicControlCanvas;
class PASCALIMPLEMENTATION TGraphicControlCanvas : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
public:
	__property Canvas ;
public:
	#pragma option push -w-inl
	/* TGraphicControl.Create */ inline __fastcall virtual TGraphicControlCanvas(Classes::TComponent* AOwner
		) : Controls::TGraphicControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TGraphicControlCanvas(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCustomControlCanvas;
class PASCALIMPLEMENTATION TCustomControlCanvas : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
public:
	__property Canvas ;
public:
	#pragma option push -w-inl
	/* TCustomControl.Create */ inline __fastcall virtual TCustomControlCanvas(Classes::TComponent* AOwner
		) : Controls::TCustomControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TCustomControlCanvas(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TCustomControlCanvas(HWND ParentWindow) : Controls::TCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TVrComponent;
class PASCALIMPLEMENTATION TVrComponent : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Vrtypes::TVrVersion FVersion;
	
public:
	__fastcall virtual TVrComponent(Classes::TComponent* AOwner);
	
__published:
	__property Vrtypes::TVrVersion Version = {read=FVersion, write=FVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TVrComponent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrCustomControl;
class PASCALIMPLEMENTATION TVrCustomControl : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	Vrtypes::TVrVersion FVersion;
	int FUpdateCount;
	
protected:
	bool __fastcall Designing(void);
	bool __fastcall Loading(void);
	void __fastcall ClearClientCanvas(void);
	virtual void __fastcall UpdateControlCanvas(void);
	
public:
	__fastcall virtual TVrCustomControl(Classes::TComponent* AOwner);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	
__published:
	__property Vrtypes::TVrVersion Version = {read=FVersion, write=FVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TVrCustomControl(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrCustomControl(HWND ParentWindow) : Controls::TCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TVrCustomImageControl;
class PASCALIMPLEMENTATION TVrCustomImageControl : public TVrCustomControl 
{
	typedef TVrCustomControl inherited;
	
private:
	Graphics::TBitmap* FBitmapImage;
	Graphics::TCanvas* __fastcall GetBitmapCanvas(void);
	
protected:
	Graphics::TCanvas* DestCanvas;
	virtual void __fastcall ClearBitmapCanvas(void);
	virtual void __fastcall Paint(void);
	__property Graphics::TBitmap* BitmapImage = {read=FBitmapImage};
	__property Graphics::TCanvas* BitmapCanvas = {read=GetBitmapCanvas};
	
public:
	__fastcall virtual TVrCustomImageControl(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCustomImageControl(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TVrCustomImageControl(HWND ParentWindow) : TVrCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TVrGraphicControl;
class PASCALIMPLEMENTATION TVrGraphicControl : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Vrtypes::TVrVersion FVersion;
	int FUpdateCount;
	
protected:
	bool __fastcall Designing(void);
	bool __fastcall Loading(void);
	void __fastcall ClearClientCanvas(void);
	virtual void __fastcall UpdateControlCanvas(void);
	
public:
	__fastcall virtual TVrGraphicControl(Classes::TComponent* AOwner);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	
__published:
	__property Vrtypes::TVrVersion Version = {read=FVersion, write=FVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TVrGraphicControl(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrGraphicImageControl;
class PASCALIMPLEMENTATION TVrGraphicImageControl : public TVrGraphicControl 
{
	typedef TVrGraphicControl inherited;
	
private:
	Graphics::TBitmap* FBitmapImage;
	bool FTransparent;
	Graphics::TCanvas* __fastcall GetBitmapCanvas(void);
	void __fastcall SetTransparent(bool Value);
	
protected:
	Graphics::TCanvas* DestCanvas;
	virtual void __fastcall ClearBitmapCanvas(void);
	virtual void __fastcall Paint(void);
	__property Graphics::TBitmap* BitmapImage = {read=FBitmapImage};
	__property Graphics::TCanvas* BitmapCanvas = {read=GetBitmapCanvas};
	__property bool Transparent = {read=FTransparent, write=SetTransparent, nodefault};
	
public:
	__fastcall virtual TVrGraphicImageControl(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrGraphicImageControl(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
};


class DELPHICLASS TVrHyperLinkControl;
class PASCALIMPLEMENTATION TVrHyperLinkControl : public TVrGraphicImageControl 
{
	typedef TVrGraphicImageControl inherited;
	
private:
	Classes::TNotifyEvent FOnMouseEnter;
	Classes::TNotifyEvent FOnMouseLeave;
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall MouseEnter(void);
	virtual void __fastcall MouseLeave(void);
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
public:
	#pragma option push -w-inl
	/* TVrGraphicImageControl.Create */ inline __fastcall virtual TVrHyperLinkControl(Classes::TComponent* 
		AOwner) : TVrGraphicImageControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TVrGraphicImageControl.Destroy */ inline __fastcall virtual ~TVrHyperLinkControl(void) { }
	#pragma option pop
	
};


typedef Shortint TVrThumbStates;

class DELPHICLASS TVrCustomThumb;
class PASCALIMPLEMENTATION TVrCustomThumb : public TVrGraphicImageControl 
{
	typedef TVrGraphicImageControl inherited;
	
private:
	Graphics::TBitmap* FGlyph;
	TVrThumbStates FThumbStates;
	bool FDown;
	bool FHasMouse;
	void __fastcall SetGlyph(Graphics::TBitmap* Value);
	void __fastcall SetThumbStates(TVrThumbStates Value);
	void __fastcall SetDown(bool Value);
	virtual void __fastcall AdjustBoundsRect(void);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall Paint(void);
	void __fastcall LoadFromResourceName(const AnsiString ResName);
	virtual int __fastcall GetImageIndex(void);
	
public:
	__fastcall virtual TVrCustomThumb(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCustomThumb(void);
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph, stored=false};
	__property TVrThumbStates ThumbStates = {read=FThumbStates, write=SetThumbStates, nodefault};
	__property bool Down = {read=FDown, write=SetDown, nodefault};
	__property bool HasMouse = {read=FHasMouse, nodefault};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrcontrols */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrcontrols;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrControls
