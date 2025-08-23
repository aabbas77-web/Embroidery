// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrSystem.pas' rev: 5.00

#ifndef VrSystemHPP
#define VrSystemHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
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

namespace Vrsystem
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TVrBitmapList;
class PASCALIMPLEMENTATION TVrBitmapList : public Vrcontrols::TVrComponent 
{
	typedef Vrcontrols::TVrComponent inherited;
	
private:
	Vrclasses::TVrBitmaps* FBitmaps;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetBitmaps(Vrclasses::TVrBitmaps* Value);
	void __fastcall BitmapsChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall Changed(void);
	
public:
	__fastcall virtual TVrBitmapList(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrBitmapList(void);
	
__published:
	__property Vrclasses::TVrBitmaps* Bitmaps = {read=FBitmaps, write=SetBitmaps};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


class DELPHICLASS TVrStringList;
class PASCALIMPLEMENTATION TVrStringList : public Vrcontrols::TVrComponent 
{
	typedef Vrcontrols::TVrComponent inherited;
	
private:
	Classes::TStrings* FItems;
	Classes::TNotifyEvent FOnChange;
	Classes::TNotifyEvent FOnChanging;
	int __fastcall GetCount(void);
	bool __fastcall GetSorted(void);
	void __fastcall SetItems(Classes::TStrings* Value);
	void __fastcall SetSorted(bool Value);
	void __fastcall Change(System::TObject* Sender);
	void __fastcall Changing(System::TObject* Sender);
	
public:
	__fastcall virtual TVrStringList(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrStringList(void);
	__property int Count = {read=GetCount, nodefault};
	
__published:
	__property Classes::TStrings* Strings = {read=FItems, write=SetItems};
	__property bool Sorted = {read=GetSorted, write=SetSorted, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
};


#pragma option push -b-
enum TVrKeyStateType { ksNUM, ksCAPS, ksSCROLL };
#pragma option pop

typedef Set<TVrKeyStateType, ksNUM, ksSCROLL>  TVrKeyStateTypes;

class DELPHICLASS TVrKeyStatus;
class PASCALIMPLEMENTATION TVrKeyStatus : public Vrcontrols::TVrComponent 
{
	typedef Vrcontrols::TVrComponent inherited;
	
private:
	HWND FHandle;
	bool FMonitorEvents;
	TVrKeyStateTypes FKeys;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetKeys(TVrKeyStateTypes Value);
	void __fastcall SetMonitorEvents(bool Value);
	void __fastcall ChangeState(Word Key, bool Active);
	void __fastcall UpdateTimer(void);
	void __fastcall WndProc(Messages::TMessage &Msg);
	
protected:
	void __fastcall Timer(void);
	DYNAMIC void __fastcall Changed(void);
	
public:
	__fastcall virtual TVrKeyStatus(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrKeyStatus(void);
	
__published:
	__property TVrKeyStateTypes Keys = {read=FKeys, write=SetKeys, default=0};
	__property bool MonitorEvents = {read=FMonitorEvents, write=SetMonitorEvents, default=0};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


class DELPHICLASS TVrCustomTrayIcon;
class PASCALIMPLEMENTATION TVrCustomTrayIcon : public Vrcontrols::TVrComponent 
{
	typedef Vrcontrols::TVrComponent inherited;
	
private:
	_NOTIFYICONDATAA FIconData;
	Graphics::TIcon* FIcon;
	bool FEnabled;
	AnsiString FHint;
	bool FShowHint;
	bool FVisible;
	Menus::TPopupMenu* FPopupMenu;
	bool FExists;
	bool FClicked;
	bool FHideTaskBtn;
	bool FLeftBtnPopup;
	Classes::TNotifyEvent FOnClick;
	Classes::TNotifyEvent FOnDblClick;
	Controls::TMouseEvent FOnMouseDown;
	Controls::TMouseEvent FOnMouseUp;
	Controls::TMouseMoveEvent FOnMouseMove;
	void *OldAppProc;
	void *NewAppProc;
	void __fastcall SetIcon(Graphics::TIcon* Value);
	void __fastcall SetVisible(bool Value);
	void __fastcall SetHint(const AnsiString Value);
	void __fastcall SetShowHint(bool Value);
	void __fastcall SetPopupMenu(Menus::TPopupMenu* Value);
	void __fastcall ShowMenu(void);
	void __fastcall UpdateHint(void);
	void __fastcall UpdateSystemTray(void);
	void __fastcall IconChanged(System::TObject* Sender);
	void __fastcall HookApp(void);
	void __fastcall UnhookApp(void);
	void __fastcall HookAppProc(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall WndProc(Messages::TMessage &Msg);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	void __fastcall DoHideTaskBtn(void);
	DYNAMIC void __fastcall Click(void);
	DYNAMIC void __fastcall DblClick(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	__property Graphics::TIcon* Icon = {read=FIcon, write=SetIcon};
	__property bool Visible = {read=FVisible, write=SetVisible, default=0};
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
	__property AnsiString Hint = {read=FHint, write=SetHint};
	__property bool ShowHint = {read=FShowHint, write=SetShowHint, default=0};
	__property Menus::TPopupMenu* PopupMenu = {read=FPopupMenu, write=SetPopupMenu};
	__property bool HideTaskBtn = {read=FHideTaskBtn, write=FHideTaskBtn, default=0};
	__property bool LeftBtnPopup = {read=FLeftBtnPopup, write=FLeftBtnPopup, default=0};
	__property Classes::TNotifyEvent OnClick = {read=FOnClick, write=FOnClick};
	__property Classes::TNotifyEvent OnDblClick = {read=FOnDblClick, write=FOnDblClick};
	__property Controls::TMouseEvent OnMouseDown = {read=FOnMouseDown, write=FOnMouseDown};
	__property Controls::TMouseEvent OnMouseUp = {read=FOnMouseUp, write=FOnMouseUp};
	__property Controls::TMouseMoveEvent OnMouseMove = {read=FOnMouseMove, write=FOnMouseMove};
	
public:
	__fastcall virtual TVrCustomTrayIcon(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrCustomTrayIcon(void);
	void __fastcall HideMainForm(void);
	void __fastcall ShowMainForm(void);
};


class DELPHICLASS TVrTrayIcon;
class PASCALIMPLEMENTATION TVrTrayIcon : public TVrCustomTrayIcon 
{
	typedef TVrCustomTrayIcon inherited;
	
__published:
	__property Icon ;
	__property Visible ;
	__property Enabled ;
	__property Hint ;
	__property ShowHint ;
	__property PopupMenu ;
	__property HideTaskBtn ;
	__property LeftBtnPopup ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnMouseMove ;
public:
	#pragma option push -w-inl
	/* TVrCustomTrayIcon.Create */ inline __fastcall virtual TVrTrayIcon(Classes::TComponent* AOwner) : 
		TVrCustomTrayIcon(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TVrCustomTrayIcon.Destroy */ inline __fastcall virtual ~TVrTrayIcon(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Word WM_TOOLTRAYNOTIFY = 0x444;

}	/* namespace Vrsystem */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrsystem;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrSystem
