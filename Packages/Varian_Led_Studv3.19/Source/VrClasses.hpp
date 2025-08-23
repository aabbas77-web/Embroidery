// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrClasses.pas' rev: 5.00

#ifndef VrClassesHPP
#define VrClassesHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrSysUtils.hpp>	// Pascal unit
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

namespace Vrclasses
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrPersistent;
class PASCALIMPLEMENTATION TVrPersistent : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FUpdateCount;
	Classes::TNotifyEvent FOnChange;
	
protected:
	void __fastcall Changed(void);
	
public:
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrPersistent(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TVrPersistent(void) : Classes::TPersistent() { }
	#pragma option pop
	
};


#pragma option push -b-
enum TVrBevelStyle { bsNone, bsLowered, bsRaised };
#pragma option pop

#pragma option push -b-
enum TVrBevelOutlineStyle { osOuter, osInner, osNone };
#pragma option pop

typedef int TVrBevelWidth;

typedef int TVrBorderWidth;

typedef int TVrBevelSpace;

class DELPHICLASS TVrBevel;
class PASCALIMPLEMENTATION TVrBevel : public TVrPersistent 
{
	typedef TVrPersistent inherited;
	
private:
	Graphics::TColor FInnerShadow;
	Graphics::TColor FInnerHighlight;
	TVrBevelWidth FInnerWidth;
	TVrBevelStyle FInnerStyle;
	TVrBevelOutlineStyle FInnerOutline;
	TVrBevelSpace FInnerSpace;
	Graphics::TColor FInnerColor;
	Graphics::TColor FOuterShadow;
	Graphics::TColor FOuterHighlight;
	TVrBevelWidth FOuterWidth;
	TVrBevelStyle FOuterStyle;
	TVrBevelOutlineStyle FOuterOutline;
	TVrBevelSpace FOuterSpace;
	Graphics::TColor FOuterColor;
	void __fastcall SetInnerShadow(Graphics::TColor Value);
	void __fastcall SetInnerHighlight(Graphics::TColor Value);
	void __fastcall SetInnerWidth(TVrBevelWidth Value);
	void __fastcall SetInnerStyle(TVrBevelStyle Value);
	void __fastcall SetInnerOutline(TVrBevelOutlineStyle Value);
	void __fastcall SetInnerSpace(TVrBevelSpace Value);
	void __fastcall SetInnerColor(Graphics::TColor Value);
	void __fastcall SetOuterShadow(Graphics::TColor Value);
	void __fastcall SetOuterHighlight(Graphics::TColor Value);
	void __fastcall SetOuterWidth(TVrBevelWidth Value);
	void __fastcall SetOuterStyle(TVrBevelStyle Value);
	void __fastcall SetOuterOutline(TVrBevelOutlineStyle Value);
	void __fastcall SetOuterSpace(TVrBevelSpace Value);
	void __fastcall SetOuterColor(Graphics::TColor Value);
	
public:
	__fastcall TVrBevel(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall GetVisibleArea(Windows::TRect &Rect);
	void __fastcall Paint(Graphics::TCanvas* Canvas, Windows::TRect &Rect);
	
__published:
	__property Graphics::TColor InnerShadow = {read=FInnerShadow, write=SetInnerShadow, nodefault};
	__property Graphics::TColor InnerHighlight = {read=FInnerHighlight, write=SetInnerHighlight, nodefault
		};
	__property TVrBevelWidth InnerWidth = {read=FInnerWidth, write=SetInnerWidth, nodefault};
	__property TVrBevelStyle InnerStyle = {read=FInnerStyle, write=SetInnerStyle, nodefault};
	__property TVrBevelOutlineStyle InnerOutline = {read=FInnerOutline, write=SetInnerOutline, nodefault
		};
	__property TVrBevelSpace InnerSpace = {read=FInnerSpace, write=SetInnerSpace, nodefault};
	__property Graphics::TColor InnerColor = {read=FInnerColor, write=SetInnerColor, nodefault};
	__property Graphics::TColor OuterShadow = {read=FOuterShadow, write=SetOuterShadow, nodefault};
	__property Graphics::TColor OuterHighlight = {read=FOuterHighlight, write=SetOuterHighlight, nodefault
		};
	__property TVrBevelWidth OuterWidth = {read=FOuterWidth, write=SetOuterWidth, nodefault};
	__property TVrBevelStyle OuterStyle = {read=FOuterStyle, write=SetOuterStyle, nodefault};
	__property TVrBevelOutlineStyle OuterOutline = {read=FOuterOutline, write=SetOuterOutline, nodefault
		};
	__property TVrBevelSpace OuterSpace = {read=FOuterSpace, write=SetOuterSpace, nodefault};
	__property Graphics::TColor OuterColor = {read=FOuterColor, write=SetOuterColor, nodefault};
public:
		
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrBevel(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrPalette;
class PASCALIMPLEMENTATION TVrPalette : public TVrPersistent 
{
	typedef TVrPersistent inherited;
	
private:
	Graphics::TColor FLow;
	Graphics::TColor FHigh;
	void __fastcall SetLow(Graphics::TColor Value);
	void __fastcall SetHigh(Graphics::TColor Value);
	virtual Graphics::TColor __fastcall GetColors(int Index);
	
public:
	__fastcall TVrPalette(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall ToBMP(Graphics::TBitmap* Bitmap, Graphics::TColor DarkColor, Graphics::TColor LightColor
		);
	__property Graphics::TColor Colors[int Index] = {read=GetColors/*, default*/};
	
__published:
	__property Graphics::TColor Low = {read=FLow, write=SetLow, nodefault};
	__property Graphics::TColor High = {read=FHigh, write=SetHigh, nodefault};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrPalette(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrMinMax;
class PASCALIMPLEMENTATION TVrMinMax : public TVrPersistent 
{
	typedef TVrPersistent inherited;
	
private:
	int FMinValue;
	int FMaxValue;
	int FPosition;
	void __fastcall SetMinValue(int Value);
	void __fastcall SetMaxValue(int Value);
	void __fastcall SetPosition(int Value);
	
public:
	__fastcall TVrMinMax(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	
__published:
	__property int MinValue = {read=FMinValue, write=SetMinValue, nodefault};
	__property int MaxValue = {read=FMaxValue, write=SetMaxValue, nodefault};
	__property int Position = {read=FPosition, write=SetPosition, nodefault};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrMinMax(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrTextOutline;
class PASCALIMPLEMENTATION TVrTextOutline : public TVrPersistent 
{
	typedef TVrPersistent inherited;
	
private:
	Graphics::TColor FColor;
	bool FVisible;
	void __fastcall SetColor(Graphics::TColor Value);
	void __fastcall SetVisible(bool Value);
	
public:
	__fastcall TVrTextOutline(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	
__published:
	__property Graphics::TColor Color = {read=FColor, write=SetColor, default=8388608};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrTextOutline(void) { }
	#pragma option pop
	
};


class DELPHICLASS TVrBitmaps;
class PASCALIMPLEMENTATION TVrBitmaps : public TVrPersistent 
{
	typedef TVrPersistent inherited;
	
private:
	Classes::TList* FItems;
	int __fastcall GetCount(void);
	Graphics::TBitmap* __fastcall GetBitmap(int Index);
	void __fastcall SetBitmap(int Index, Graphics::TBitmap* Value);
	void __fastcall ReadData(Classes::TStream* Stream);
	void __fastcall WriteData(Classes::TStream* Stream);
	
protected:
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	
public:
	__fastcall TVrBitmaps(void);
	__fastcall virtual ~TVrBitmaps(void);
	void __fastcall Clear(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	int __fastcall Add(Graphics::TBitmap* Value);
	void __fastcall Delete(int Index);
	void __fastcall Insert(int Index, Graphics::TBitmap* Value);
	void __fastcall Exchange(int Index1, int Index2);
	void __fastcall Move(int CurIndex, int NewIndex);
	int __fastcall IndexOf(Graphics::TBitmap* Bitmap);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall LoadFromFile(const AnsiString FileName);
	virtual void __fastcall SaveToFile(const AnsiString FileName);
	__property Graphics::TBitmap* Bitmaps[int Index] = {read=GetBitmap, write=SetBitmap/*, default*/};
	__property int Count = {read=GetCount, nodefault};
};


class DELPHICLASS TVrRect;
class PASCALIMPLEMENTATION TVrRect : public TVrPersistent 
{
	typedef TVrPersistent inherited;
	
private:
	int FLeft;
	int FTop;
	int FWidth;
	int FHeight;
	Windows::TRect __fastcall GetBoundsRect();
	void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	void __fastcall SetBoundsRect(const Windows::TRect &Rect);
	void __fastcall SetLeft(int Value);
	void __fastcall SetTop(int Value);
	void __fastcall SetWidth(int Value);
	void __fastcall SetHeight(int Value);
	
public:
	__fastcall TVrRect(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property Windows::TRect BoundsRect = {read=GetBoundsRect, write=SetBoundsRect};
	
__published:
	__property int Left = {read=FLeft, write=SetLeft, default=0};
	__property int Top = {read=FTop, write=SetTop, default=0};
	__property int Width = {read=FWidth, write=SetWidth, default=0};
	__property int Height = {read=FHeight, write=SetHeight, default=0};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrRect(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TVrFont3DStyle { f3dNone, f3dRaised, f3dSunken, f3dShadow };
#pragma option pop

class DELPHICLASS TVrFont3D;
class PASCALIMPLEMENTATION TVrFont3D : public TVrPersistent 
{
	typedef TVrPersistent inherited;
	
private:
	TVrFont3DStyle FStyle;
	Graphics::TColor FHighlightColor;
	Graphics::TColor FShadowColor;
	int FHighlightDepth;
	int FShadowDepth;
	void __fastcall SetStyle(TVrFont3DStyle Value);
	void __fastcall SetHighlightColor(Graphics::TColor Value);
	void __fastcall SetShadowColor(Graphics::TColor Value);
	void __fastcall SetHighlightDepth(int Value);
	void __fastcall SetShadowDepth(int Value);
	
public:
	__fastcall TVrFont3D(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall Paint(Graphics::TCanvas* Canvas, const Windows::TRect &R, const AnsiString Text, int 
		Flags);
	
__published:
	__property TVrFont3DStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property Graphics::TColor HighlightColor = {read=FHighlightColor, write=SetHighlightColor, default=-2147483628
		};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, default=-2147483632
		};
	__property int HighlightDepth = {read=FHighlightDepth, write=SetHighlightDepth, default=1};
	__property int ShadowDepth = {read=FShadowDepth, write=SetShadowDepth, default=1};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TVrFont3D(void) { }
	#pragma option pop
	
};


typedef int TVrIntArray[134217727];

typedef int *PVrIntArray;

class DELPHICLASS TVrIntList;
class PASCALIMPLEMENTATION TVrIntList : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FCount;
	int FCapacity;
	int *FItems;
	void __fastcall SetCapacity(int NewCapacity);
	void __fastcall SetCount(int NewCount);
	void __fastcall Grow(void);
	int __fastcall GetCount(void);
	int __fastcall GetItem(int Index);
	
public:
	__fastcall TVrIntList(void);
	__fastcall virtual ~TVrIntList(void);
	void __fastcall Clear(void);
	int __fastcall Add(int Value);
	void __fastcall Delete(int Index);
	__property int Count = {read=GetCount, nodefault};
	__property int Items[int Index] = {read=GetItem};
};


class DELPHICLASS TVrCollectionItem;
class DELPHICLASS TVrCollection;
class PASCALIMPLEMENTATION TVrCollection : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FItems;
	int FUpdateCount;
	int __fastcall GetCount(void);
	void __fastcall InsertItem(TVrCollectionItem* Item);
	void __fastcall RemoveItem(TVrCollectionItem* Item);
	
protected:
	void __fastcall Changed(void);
	TVrCollectionItem* __fastcall GetItem(int Index);
	virtual void __fastcall Update(TVrCollectionItem* Item);
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	
public:
	__fastcall TVrCollection(void);
	__fastcall virtual ~TVrCollection(void);
	virtual void __fastcall BeginUpdate(void);
	void __fastcall Clear(void);
	virtual void __fastcall EndUpdate(void);
	__property int Count = {read=GetCount, nodefault};
	__property TVrCollectionItem* Items[int Index] = {read=GetItem};
};


class PASCALIMPLEMENTATION TVrCollectionItem : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TVrCollection* FCollection;
	int FIndex;
	void __fastcall SetCollection(TVrCollection* Value);
	
protected:
	void __fastcall Changed(bool AllItems);
	
public:
	__fastcall virtual TVrCollectionItem(TVrCollection* Collection);
	__fastcall virtual ~TVrCollectionItem(void);
	__property TVrCollection* Collection = {read=FCollection, write=SetCollection};
	__property int Index = {read=FIndex, write=FIndex, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const int MaxIntListSize = 0x7ffffff;

}	/* namespace Vrclasses */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrclasses;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrClasses
