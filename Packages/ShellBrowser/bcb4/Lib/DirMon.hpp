// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DirMon.pas' rev: 4.00

#ifndef DirMonHPP
#define DirMonHPP

#pragma delphiheader begin
#pragma option push -w-
#include <Forms.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dirmon
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TDirMonValue { dmcFileName, dmcDirName, dmcAttributes, dmcSize, dmcLastWrite, dmcSecurity };
#pragma option pop

typedef Set<TDirMonValue, dmcFileName, dmcSecurity>  TDirMonType;

class DELPHICLASS TDirMon;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TDirMon : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FDirectory;
	unsigned FNotifyFilter;
	HWND FWindowHandle;
	void *FParamPtr;
	unsigned FMutexHandle;
	bool FNested;
	unsigned FThreadHandle;
	unsigned FThreadID;
	Classes::TNotifyEvent FOnDirChange;
	Classes::TNotifyEvent FOnStart;
	Classes::TNotifyEvent FOnStop;
	void __fastcall WndProc(Messages::TMessage &MsgRec);
	MESSAGE void __fastcall WMDirChange(Messages::TMessage &aMsg);
	
protected:
	void __fastcall SetNotifyFilter(TDirMonType newValue);
	TDirMonType __fastcall GetNotifyFilter(void);
	void __fastcall SetDirectory(AnsiString newValue);
	virtual void __fastcall TriggerDirChangeEvent(void);
	virtual void __fastcall TriggerStartEvent(void);
	virtual void __fastcall TriggerStopEvent(void);
	
public:
	__fastcall virtual TDirMon(Classes::TComponent* AOwner);
	__fastcall virtual ~TDirMon(void);
	void __fastcall Start(void);
	void __fastcall Stop(void);
	__property HWND Handle = {read=FWindowHandle, nodefault};
	
__published:
	__property AnsiString Directory = {read=FDirectory, write=SetDirectory};
	__property TDirMonType NotifyFilter = {read=GetNotifyFilter, write=SetNotifyFilter, nodefault};
	__property Classes::TNotifyEvent OnDirChange = {read=FOnDirChange, write=FOnDirChange};
	__property bool Nested = {read=FNested, write=FNested, nodefault};
	__property Classes::TNotifyEvent OnStart = {read=FOnStart, write=FOnStart};
	__property Classes::TNotifyEvent OnStop = {read=FOnStop, write=FOnStop};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Word WM_DIRCHANGE = 0x401;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Dirmon */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dirmon;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DirMon
