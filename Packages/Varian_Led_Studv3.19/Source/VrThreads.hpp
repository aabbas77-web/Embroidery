// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VrThreads.pas' rev: 5.00

#ifndef VrThreadsHPP
#define VrThreadsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <VrControls.hpp>	// Pascal unit
#include <VrClasses.hpp>	// Pascal unit
#include <VrTypes.hpp>	// Pascal unit
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

namespace Vrthreads
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TVrTimerType { ttThread, ttSystem };
#pragma option pop

class DELPHICLASS TVrTimer;
class PASCALIMPLEMENTATION TVrTimer : public Vrcontrols::TVrComponent 
{
	typedef Vrcontrols::TVrComponent inherited;
	
private:
	bool FEnabled;
	unsigned FInterval;
	Classes::TNotifyEvent FOnTimer;
	HWND FWindowHandle;
	bool FSyncEvent;
	TVrTimerType FTimerType;
	Classes::TThread* FTimerThread;
	Classes::TThreadPriority FPriority;
	bool FAllocated;
	void __fastcall SetTimerType(TVrTimerType Value);
	void __fastcall SetPriority(Classes::TThreadPriority Value);
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetInterval(unsigned Value);
	void __fastcall CreateTimer(void);
	void __fastcall DestroyTimer(void);
	void __fastcall UpdateTimer(void);
	void __fastcall WndProc(Messages::TMessage &Msg);
	
protected:
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall Timer(void);
	
public:
	__fastcall virtual TVrTimer(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrTimer(void);
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property unsigned Interval = {read=FInterval, write=SetInterval, default=1000};
	__property bool SyncEvent = {read=FSyncEvent, write=FSyncEvent, default=1};
	__property TVrTimerType TimerType = {read=FTimerType, write=SetTimerType, default=0};
	__property Classes::TThreadPriority Priority = {read=FPriority, write=SetPriority, default=3};
	__property Classes::TNotifyEvent OnTimer = {read=FOnTimer, write=FOnTimer};
};


class DELPHICLASS TVrSystemThread;
class DELPHICLASS TVrThread;
class PASCALIMPLEMENTATION TVrThread : public Vrcontrols::TVrComponent 
{
	typedef Vrcontrols::TVrComponent inherited;
	
private:
	bool FEnabled;
	bool FSyncEvent;
	Classes::TThreadPriority FPriority;
	Classes::TNotifyEvent FOnExecute;
	TVrSystemThread* FSystemThread;
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetPriority(Classes::TThreadPriority Value);
	void __fastcall ExecuteEvent(System::TObject* Sender);
	
protected:
	void __fastcall UpdateThreadParams(void);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TVrThread(Classes::TComponent* AOwner);
	__fastcall virtual ~TVrThread(void);
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property Classes::TThreadPriority Priority = {read=FPriority, write=SetPriority, default=3};
	__property bool SyncEvent = {read=FSyncEvent, write=FSyncEvent, default=1};
	__property Classes::TNotifyEvent OnExecute = {read=FOnExecute, write=FOnExecute};
};


class PASCALIMPLEMENTATION TVrSystemThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	TVrThread* FOwner;
	Classes::TNotifyEvent FOnExecute;
	
protected:
	void __fastcall CallExecute(void);
	virtual void __fastcall Execute(void);
	
public:
	__fastcall TVrSystemThread(TVrThread* AOwner, bool Enabled);
	__property Classes::TNotifyEvent OnExecute = {read=FOnExecute, write=FOnExecute};
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TVrSystemThread(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Vrthreads */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Vrthreads;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// VrThreads
