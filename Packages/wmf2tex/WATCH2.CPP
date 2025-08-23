// WATCH2
// by Lucian Wischik
// This code is based heavily upon the MEMWATCH program by Terry Richards,
// and some sample code in the Microsoft Systems Journal vol12 num5
//
// This code monitors the following memory allocations:
//  - calls you make to new, new[], delete, delete[]
//  - The GetMem, ReallocMem, and FreeMem standard procedures.
//  - The New and Dispose standard procedures.
//  - Allocation and deallocation of objects through constructors and destructors,
//    including all VCL objects
//  - Allocation and deallocation of dynamic strings.
//  - Also it checks that you haven't overwritten or underwritten your memory blocks
//  - It does NOT monitor Window system calls, and does NOT check that you have
//    freed all Windows objects that you create.
//
// To use, simply add the file watch2.cpp to your project and rebuild.
// Watch2 does not work at all well with dynamic linking. I recommend
// that you turn it off.
// Configuration: there are a number of variables immediately below that you can change:
//
const bool ReportNulls=true; // do we report attempts to delete NULLs?
const bool NagScreen=true; // a dialog box that pops up if there was any leakage
const char* LogName="/watch.log"; // do we output a log to a file?
const int NumEnts = 5000; // biggest number of memory blocks that can be allocated
const char SafetyChar='!'; // Safety area is to check if you had memory
const int HiSafetySize=20; // overruns or underruns
const int LoSafetySize=20; // must be 0 if you use dynamic rtl
const int MaxCallstackDepth=50; // How much call-stack do we record?
const int CallstackEntrySize=60; // How long is the text describing each procedure call in the callstack?
const bool UseImagehlp=true; // Do we attempt to use Microsofts Imagehlp library, or do we roll our own?
//
// This is how it intercepts memory allocations
// - It provides its own version of operator new. This means that any time you
//   call a regular C++ new operator, it in fact calls the version in this code.
// - It installs a startup procedure with #pragma startup MyStartupProc 0.
//   This startup proc gets called right at the very start. In MyStartupProc,
//   it calls SetMemoryManager(...) This instructs the VCL to use the memory
//   allocation routines provided by Watch.
//
// This is how it keeps track of leaked memory
// - There is a large array of size NumEnts. Whenever new is called, a record is
//   made in this array. Whenever delete is called, it removes the record from the array
// - The large array records only the address of each memory block allocated, and its size.
// - We actually allocate more memory than is strictly needed. We allocate
//   LoSafetySize bytes beneath it, and HiSafetySize bytes above it, and we fill them with
//   SafetyChar. This is so that, when it comes time to delete the block, we can verify
//   that it hasn't accidentally been overwritten
// - In fact, we actually make each memory block even bigger. Extra space is reserved
//   at the top of the high safety block and this is filled with a record of the call-stack
//   at the time the block was allocated. That is, a TCallstackHeader structure followed
//   by some number of TLineOfCallstack structures.
// - An exit procedure is installed with #pragma exit MyExitProc 0. This gets called
//   right at the very end. At this stage we go through the large array and pick out
//   any blocks that have not yet been deleted. The user is informed.
//
// This is a note on how you should use the results
// - Watch displays the callstack how it was when a memory block was allocated.
//   The top entries are the most recent. The top three or four will probably
//   refer to routines within Watch itself, and not within your code.
// - Allocating VCL objects is kind of strange. Although you think you called
//   new TButton(..) from within your Form constructor, or from within
//   one of your methods, in fact the VCL call to memory allocation probably happened
//   at quite a different time. This can make it very difficult to track down
//   the exact reason for the call. I have no idea why this is so.
// - There's an extra function you can use. bool CheckSafetyAreas(void *)
//   If you want to use it in your own code you'll have to prototype it.
//   It ensures that the safety areas above and below a block of memory have
//   not been corrupted.
// - If you do use Watch, then your programs will run a bit slower
//   and will take a bit longer to start up. This is unavoidable.
//
// These are particular implementation notes
// - The RTL itself has some memory leaks, of about 1912 bytes. It would be a pain
//   if these were always reported. Hence, Watch does not take them seriously.
//   It does this my installing #pragma startup MyStartTakingSeriouslyProc 32.
//   If any memory blocks were allocated before startup-level-32, Watch does not
//   complain if they are not deleted. But if anything is allocated after startup-level-32
//   then Watch does complain.
// - The Windows IMAGEHLP routines are used to obtain the stack trace. We would also
//   like to use the routines to figure out the names of the functions at each of those
//   points, using SymGetSymFromAddr. Unfortunately, IMAGEHLP seems only to recognose
//   very few symbols: InitExceptDLL, and two others. SymGetSymFromAddr is therefore
//   useless, and has been commented out. I have no idea why this is so.
// - The routine SaveCallstack is used to save the current callstack. It
//   If Imagehlp could be loaded okay, then it uses the Imagehlp functions.
//   Otherwise, if the processor is an intel, it uses some intel-specific code
//   for walking the stack.
//



#include <windows.h>
#include <imagehlp.h>
#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include <malloc.h>
#include <vcl\system.hpp>


//---------------------------------------------------------------------------

bool UsesRtl=
#ifdef _RTLDLL
true;
#else
false;
#endif


typedef struct {char Caller[CallstackEntrySize]; void *stackp;} TLineOfCallstack;
typedef struct {int Depth; bool Serious;} TCallstackHeader;
typedef struct {TCallstackHeader h; TLineOfCallstack l[MaxCallstackDepth];} TCallstack;
typedef struct {void *Address; size_t Size;} TMemoryBlock;


TMemoryBlock Mems[NumEnts]; // The database of memory entries
bool MemsFull=false; // Have we ever exceeded the size of this?
int  MaxUsed=0,NumNew=0,NumDeletes=0,NumNullDeletes=0,NewCalled=0; // for log
bool LogFileInitialized=false; // have we attempted to open the log file?
FILE *LogFile; // log file handle
bool SymsInitialized=false; // have we attempted to initialize the symbol table?
bool SymsSucceeded=false; // and did it work?
bool InternalCall=false; // to prevent recursion
bool DontTakeSeriously=true; // the rtl doesn't free all of its memory: so, we don't take the first calls seriously
bool SymsIsIntel=true; // Are we an intel machine?

typedef BOOL (__stdcall *SYMINITIALIZEPROC)(HANDLE,LPSTR,BOOL);
typedef BOOL (__stdcall *SYMCLEANUPPROC)(HANDLE);
typedef BOOL (__stdcall *STACKWALKPROC)(DWORD,HANDLE,HANDLE,LPSTACKFRAME,LPVOID,PREAD_PROCESS_MEMORY_ROUTINE,PFUNCTION_TABLE_ACCESS_ROUTINE,PGET_MODULE_BASE_ROUTINE, PTRANSLATE_ADDRESS_ROUTINE );
typedef LPVOID (__stdcall *SYMFUNCTIONTABLEACCESSPROC)(HANDLE,DWORD);
typedef DWORD (__stdcall *SYMGETMODULEBASEPROC)(HANDLE,DWORD);
typedef BOOL (__stdcall *SYMGETSYMFROMADDRPROC)(HANDLE,DWORD,PDWORD,PIMAGEHLP_SYMBOL);
SYMINITIALIZEPROC pSymInitialize = 0;
SYMCLEANUPPROC pSymCleanup = 0;
STACKWALKPROC pStackWalk = 0;
SYMFUNCTIONTABLEACCESSPROC pSymFunctionTableAccess = 0;
SYMGETMODULEBASEPROC pSymGetModuleBase = 0;
SYMGETSYMFROMADDRPROC pSymGetSymFromAddr = 0;
HMODULE hImagehlp=NULL;

void Trace(char *);
void EnsureLogFileInitialized();
void EnsureSymsInitialized();
void EnsureLogFileClosed();
void EnsureSymsClosed();
void MyExitProc();
void SaveCallstack(CONTEXT &ctx,TCallstack *cs);
void PrintCallstack(TCallstack *cs);
void MyStartProc();
void MyStartTakingSeriouslyProc();
#pragma exit MyExitProc 0
#pragma startup MyStartProc 0
#pragma startup MyStartTakingSeriouslyProc 32


void* __fastcall MyGetMem(int i)
{ BYTE *real=new BYTE[4+i];
  *((int*)real)=i;
  return real+4;
}
int __fastcall MyFreeMem(void *p)
{ BYTE *fake=(BYTE*)p;
  BYTE *real=fake-4;
  delete[] real;
  return 0;
}
void* __fastcall MyReallocMem(void *p,int s)
{ BYTE *oldfake=(BYTE*)p;
  BYTE *oldreal=oldfake-4;
  int oldsize=*((int*)oldreal);
  BYTE *newreal=new BYTE[4+s];
  *((int*)newreal)=s;
  BYTE *newfake=newreal+4;
  int max=oldsize; if (max>s) max=s;
  for (int i=0; i<max; i++) *newfake++=*oldfake++;
  delete[] oldreal;
  return newreal+4;
}
TMemoryManager MyMemoryManager = {MyGetMem,MyFreeMem,MyReallocMem};
void MyStartProc()
{ SetMemoryManager(MyMemoryManager);
}
void MyStartTakingSeriouslyProc()
{ DontTakeSeriously=false;
}




void Trace(char *c)
{ OutputDebugString(c);
  EnsureLogFileInitialized();
  if (LogFile!=NULL) {fprintf(LogFile,c); fprintf(LogFile,"\n");}
}
void EnsureLogFileInitialized()
{ if (LogFileInitialized) return;
  LogFileInitialized=true; LogFile=NULL;
  bool islogged=true;
  if (LogName==NULL) islogged=false;
  if (strcmp(LogName,"")==0) islogged=false;
  if (islogged)
  { bool oldval=InternalCall;
    InternalCall=true;
    LogFile=fopen(LogName,"wt");
    InternalCall=oldval;
  }
  char c[1000];
  if (islogged) wsprintf(c,"******************* START OF LOG also logged to %s",LogName);
  else wsprintf(c,"******************* START OF LOG");
  Trace(c);
  struct date d; getdate(&d); struct time t; gettime(&t);
  wsprintf(c,"%s on %i:%i:%i:%i on %i/%i/%i",GetCommandLine(),(int)t.ti_hour,(int)t.ti_min,(int)t.ti_sec,(int)t.ti_hund,(int)d.da_day,(int)d.da_mon,(int)d.da_year);
  Trace(c);
}
void EnsureLogFileClosed()
{ if (!LogFileInitialized) return;
  bool oldval=InternalCall;
  InternalCall=true;
  if (LogFile!=NULL) fclose(LogFile); LogFile=NULL;
  InternalCall=oldval;
  LogFileInitialized=false;
}
void EnsureSymsInitialized()
{ if (SymsInitialized) return;
  if (UsesRtl && LoSafetySize>0) Trace("Warning! Lo safety size is >0, which is bad if you're using dynamic rtl");
  SymsInitialized=true; SymsSucceeded=false;
  SYSTEM_INFO si; GetSystemInfo(&si);
  SymsIsIntel = (HIWORD(si.dwOemId)==PROCESSOR_ARCHITECTURE_INTEL);
  #pragma option -w-ccc
  #pragma option -w-rch
  if (UseImagehlp)
  { HMODULE hImagehlp=LoadLibrary("IMAGEHLP.DLL");
    if (hImagehlp==NULL) return;
    pSymInitialize = (SYMINITIALIZEPROC)GetProcAddress(hImagehlp,"SymInitialize" );
    pSymCleanup = (SYMCLEANUPPROC)GetProcAddress( hImagehlp, "SymCleanup" );
    pStackWalk = (STACKWALKPROC)GetProcAddress( hImagehlp, "StackWalk" );
    pSymFunctionTableAccess = (SYMFUNCTIONTABLEACCESSPROC)GetProcAddress( hImagehlp, "SymFunctionTableAccess" );
    pSymGetModuleBase = (SYMGETMODULEBASEPROC)GetProcAddress( hImagehlp,"SymGetModuleBase");
    pSymGetSymFromAddr = (SYMGETSYMFROMADDRPROC)GetProcAddress( hImagehlp,"SymGetSymFromAddr" );
    if (!pSymInitialize||!pSymCleanup||!pStackWalk||!pSymFunctionTableAccess||!pSymGetModuleBase||!pSymGetSymFromAddr) SymsSucceeded=false;
    else SymsSucceeded=pSymInitialize(GetCurrentProcess(),NULL,TRUE);
  }
  #pragma option -w.
}
void EnsureSymsClosed()
{ if (!SymsInitialized) return;
  bool oldval=InternalCall;
  InternalCall=true;
  if (SymsSucceeded) pSymCleanup(GetCurrentProcess()); SymsSucceeded=false;
  if (hImagehlp!=NULL) FreeLibrary(hImagehlp); hImagehlp=NULL;
  InternalCall=oldval;
  SymsInitialized=false;
}



BOOL GetLogicalAddress (PVOID addr,PTSTR szModule,DWORD len,DWORD *section, DWORD *offset)
{ MEMORY_BASIC_INFORMATION mbi;
  if (!VirtualQuery(addr,&mbi,sizeof(mbi))) return FALSE;
  DWORD hMod = (DWORD)mbi.AllocationBase;
  //if (hMod==0) return FALSE; // bye LJW. I don't have a clue why this is needed
  if (!GetModuleFileName((HMODULE)hMod,szModule,len)) return FALSE;
  return FALSE; // don't want the rest
  /*
  // Point to the DOS header in memory
  PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;
  // From the DOS header, find the NT (PE) header
  PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod+pDosHdr->e_lfanew);
  PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHdr);
  DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address
  // Iterate through the section table, looking for the one thatencompasses
  // the linear address.
  for (int i=0; i<pNtHdr->FileHeader.NumberOfSections; i++, pSection++ )
  { DWORD sectionStart = pSection->VirtualAddress;
    DWORD sectionEnd = sectionStart+max(pSection->SizeOfRawData,pSection->Misc.VirtualSize);
    // Is the address in this section???
    if ((rva >= sectionStart) && (rva <= sectionEnd) )
    { // Yes, address is in the section.  Calculate section andoffset,
      // and store in the "section" & "offset" params, which were
      // passed by reference.
      *section = i+1;
      *offset = rva - sectionStart;
      return TRUE;
    }
  }
  return FALSE;   // Should never get here!
  */
}

void SaveCallstack(CONTEXT &ctx,TCallstack *cs)
{ int oldval=InternalCall; InternalCall=true;
  EnsureSymsInitialized();
  cs->h.Depth=0;
  cs->h.Serious=!DontTakeSeriously;
  HANDLE hThread=GetCurrentThread();
  if (SymsSucceeded)
  { STACKFRAME sf; ZeroMemory(&sf,sizeof(sf));
    sf.AddrPC.Offset=ctx.Eip;
    sf.AddrPC.Mode=AddrModeFlat;
    sf.AddrStack.Offset=ctx.Esp;
    sf.AddrStack.Mode=AddrModeFlat;
    sf.AddrFrame.Offset=ctx.Ebp;
    sf.AddrFrame.Mode=AddrModeFlat;
    while (cs->h.Depth<MaxCallstackDepth)
    { BYTE symbolBuffer[sizeof(IMAGEHLP_SYMBOL)+1024];
      IMAGEHLP_SYMBOL *pSymbol = (IMAGEHLP_SYMBOL*) symbolBuffer;
      BOOL res=pStackWalk(IMAGE_FILE_MACHINE_I386,GetCurrentProcess(),hThread,
                         &sf,&ctx,0,pSymFunctionTableAccess,pSymGetModuleBase,0);
      if (!res) break;
      if (sf.AddrFrame.Offset==0) break;
      if (sf.AddrPC.Offset==0) break;
      pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
      pSymbol->MaxNameLength = 1024;
      // Displacement of the input address, relative to the start of thesymbol
      DWORD symDisplacement = 0;
      BOOL GotSymbol=SymGetSymFromAddr(GetCurrentProcess(),sf.AddrPC.Offset,&symDisplacement,pSymbol);
      //BOOL GotSymbol=false;
      char *name=""; if (GotSymbol) name=pSymbol->Name; if (name==NULL) name="";
      TCHAR szModule[MAX_PATH]="";
      DWORD section=0, offset=0;
      GetLogicalAddress((PVOID)sf.AddrPC.Offset,szModule,sizeof(szModule),&section,&offset);
      char c[150];
      wsprintf(c,"0x%08lx: %s  %s",sf.AddrPC.Offset,name,szModule);
      c[CallstackEntrySize-1]=0; strcpy(cs->l[cs->h.Depth].Caller,c); cs->l[cs->h.Depth].stackp=(void*)sf.AddrStack.Offset;
      cs->h.Depth=cs->h.Depth+1;
    }
  }
  else if (SymsIsIntel)
  { DWORD pc = ctx.Eip;
    PDWORD pFrame, pPrevFrame;
    pFrame = (PDWORD)ctx.Ebp;
    do
    { char szModule[MAX_PATH] = "";
      DWORD section = 0, offset = 0;
      GetLogicalAddress((PVOID)pc, szModule,sizeof(szModule),&section,&offset );
      char c[150];
      wsprintf(c,"0x%08lx: %s  %s",pc,"",szModule);
      c[CallstackEntrySize-1]=0; strcpy(cs->l[cs->h.Depth].Caller,c); cs->l[cs->h.Depth].stackp=(void*)pFrame;
      cs->h.Depth=cs->h.Depth+1;
      pc = pFrame[1];
      pPrevFrame = pFrame;
      pFrame = (PDWORD)pFrame[0]; // precede to next higher frame on stack
      if ( (DWORD)pFrame & 3 ) break;   // Frame pointer must be aligned on a DWORD boundary
      if ( pFrame <= pPrevFrame ) break;
      // Can two DWORDs be read from the supposed frame address?
      if ( IsBadWritePtr(pFrame, sizeof(PVOID)*2) ) break;
    }
    while (true);
  }
  InternalCall=oldval;
}
void PrintCallstack(TCallstack *cs)
{ if (cs->h.Depth==0) {Trace("<no call stack>");return;}
  for (int i=0; i<cs->h.Depth; i++) Trace(cs->l[i].Caller);
}



void * operator new (size_t Size)
{ if (InternalCall) return malloc(Size);
  //
  CONTEXT ctx; ZeroMemory(&ctx,sizeof(ctx)); ctx.ContextFlags=CONTEXT_FULL; GetThreadContext(GetCurrentThread(),&ctx);
  TCallstack cs; SaveCallstack(ctx,&cs);
  char *RealMem = (char*)malloc(LoSafetySize+Size+HiSafetySize+sizeof(TCallstackHeader)+cs.h.Depth*sizeof(TLineOfCallstack));
  if (RealMem==NULL)
  { Trace("********* ERROR ****************");
    Trace("Out of memory");
    return RealMem;
  }
  //
  char *FakeMem = RealMem + LoSafetySize;
  if (MemsFull) return FakeMem;
  //
  FillMemory(RealMem,LoSafetySize,SafetyChar);
  FillMemory((LPBYTE)FakeMem+Size,HiSafetySize,SafetyChar);
  TCallstackHeader *memcsh=(TCallstackHeader*)(RealMem+LoSafetySize+Size+HiSafetySize);
  TLineOfCallstack *memcsl=(TLineOfCallstack*)(RealMem+LoSafetySize+Size+HiSafetySize+sizeof(TCallstackHeader));
  CopyMemory(memcsh,&cs.h,sizeof(TCallstackHeader));
  for (int i=0; i<cs.h.Depth; i++) CopyMemory(&memcsl[i],&cs.l[i],sizeof(TLineOfCallstack));
  //
  int i; for (i=0;i<NumEnts && Mems[i].Address;i++);
  if (i==NumEnts)
  { MemsFull=true;
    Trace("******** SERIOUS ERROR ***************");
    Trace("Memory database too small - increase NumEnts");
    Trace("All following messages may be incorrect");
    return FakeMem;
  }
  //
  if (i>MaxUsed) MaxUsed=i;
  if (!DontTakeSeriously) NumNew++;
  Mems[i].Address=FakeMem;
  Mems[i].Size=Size;
  return FakeMem;
}
void * operator new[] (size_t Size) {return operator new(Size);}


void operator delete (void *vFakeMem)
{ if (InternalCall) {if (vFakeMem) free(vFakeMem);return;}
  //int res=heapcheck();
  //if (res==_HEAPCORRUPT)
  //{ Trace("*************** ERROR ************************");
  //  Trace("The runtime library reported a corrupt heap");
  //  Trace("All bets are off");
  //}
  if (vFakeMem==NULL) NumNullDeletes++;
  else  NumDeletes++;
  if (vFakeMem==NULL && ReportNulls)
  { Trace("Warning... NULL pointer deleted... this is valid but suspicious");
    CONTEXT ctx; ZeroMemory(&ctx,sizeof(ctx)); ctx.ContextFlags=CONTEXT_FULL; GetThreadContext(GetCurrentThread,&ctx);
    TCallstack cs; SaveCallstack(ctx,&cs);
    Trace("It was deleted at");
    PrintCallstack(&cs);
  }
  if (vFakeMem==NULL) return;
  //
  // Check that pointer is in our database
  int i; for (i=0;i<NumEnts && Mems[i].Address!=vFakeMem;i++);
  if (i==NumEnts)
  { char c[100]; wsprintf(c,"Unknown pointer 0x%lx deleted",vFakeMem);
    Trace("******************* ERROR *******************");
    Trace(c);
    Trace("Either the pointer is corrupt or was deleted");
    Trace("multiple times.");
    CONTEXT ctx; ZeroMemory(&ctx,sizeof(ctx)); ctx.ContextFlags=CONTEXT_FULL; GetThreadContext(GetCurrentThread(),&ctx);
    TCallstack cs; SaveCallstack(ctx,&cs);
    Trace("It was deleted at");
    PrintCallstack(&cs);
    #pragma option -w-ccc
    if (NagScreen)
    { char c[200]; wsprintf(c,"An invalid pointer is being deleted. Pause now to look at the callstack.");
      if (LogFile!=NULL) {strcat(c,"\r\nA log is being written to ");strcat(c,LogName);}
      MessageBox(NULL,c,"*VERY* serious error",MB_OK);
    }
    #pragma option -w.
    free(vFakeMem);
    return;
  }
  //
  char *RealMem=(char*)vFakeMem - LoSafetySize;
  char *locheckmem=RealMem;
  char *FakeMem=RealMem+LoSafetySize;
  char *hicheckmem=RealMem+LoSafetySize+Mems[i].Size;
  TCallstackHeader *csh=(TCallstackHeader*)(RealMem+LoSafetySize+Mems[i].Size+HiSafetySize);
  // If it was in our database, and it wasn't serious, then we won't have
  // recorded it as a numnew in the first place. Just so the things tally,
  // we will now
  if (!csh->Serious) NumNew++;
  // Check safety areas
  bool UnderWritten=false, OverWritten=false;
  for (int i=0; i<LoSafetySize; i++) if (locheckmem[i]!=SafetyChar) UnderWritten=true;
  for (int i=0; i<HiSafetySize; i++) if (hicheckmem[i]!=SafetyChar) OverWritten=true;
  if (OverWritten || UnderWritten)
  { char c[100];
    wsprintf(c,"The memory block at 0x%lx is corrupt",FakeMem);
    Trace("****************** WARNING ******************");
    Trace(c);
    if (UnderWritten) Trace("The low safety area has been changed");
    if (OverWritten) Trace("The high safety area has been changed.");
    Trace("It was created at");
    PrintCallstack((TCallstack*)csh);
    CONTEXT ctx; ZeroMemory(&ctx,sizeof(ctx)); ctx.ContextFlags=CONTEXT_FULL; GetThreadContext(GetCurrentThread(),&ctx);
    TCallstack cs; SaveCallstack(ctx,&cs);
    Trace("It was deleted at");
    PrintCallstack(&cs);
    char *msg="";
    if (OverWritten && !UnderWritten) msg="Block had overrun";
    if (!OverWritten && UnderWritten) msg="Block had been underwritten";
    if (OverWritten && UnderWritten) msg="Block had overrun below and above";
    #pragma option -w-ccc
    if (NagScreen) MessageBox(NULL,msg,"This is terrible",MB_OK);
    #pragma option -w.
  }
  //
  Mems[i].Address = NULL;
  free(RealMem);
}
void operator delete[] (void * TheMem) {delete TheMem;}



void MyExitProc()
{ bool oldval=InternalCall;
  InternalCall=true;
  EnsureLogFileInitialized();
  int leakage=0;
  bool DoneAtLeastOne=false;
  for (int i=0;i<MaxUsed;i++)
  { char *FakeMem=(char*)Mems[i].Address;
    char *RealMem=FakeMem-LoSafetySize;
    TCallstackHeader *csh=NULL; if (FakeMem!=NULL) csh=(TCallstackHeader*)(RealMem+LoSafetySize+Mems[i].Size+HiSafetySize);
    if (FakeMem!=NULL && csh->Serious)
    { //We found an orphan block.
      if (!DoneAtLeastOne && UsesRtl)
      { Trace("******************* NOTE! *******************");
        Trace("Possible memory leaks detected. These may not");
        Trace("be accurate as the memory could have been");
        Trace("allocated by your program and freed by one of");
        Trace("the Borland DLLs. Also, this code cannot 'see'");
        Trace("memory leaks that are entirely within the DLLs.");
        Trace("Switch to static linking if you want to see all");
        Trace("the memory activity. You will probably need to");
        Trace("increase NumEnts if you do this");
      }
      char c[100]; wsprintf(c,"Memory block at 0x%lx not deleted",Mems[i].Address);
      char d[100]; wsprintf(d,"It is %i bytes long",Mems[i].Size);
      Trace("******************* ERROR *******************");
      Trace(c); Trace(d);
      Trace("It was created at");
      PrintCallstack((TCallstack*)csh);
      leakage=leakage+Mems[i].Size;
      DoneAtLeastOne=true;
    }
  }
  /*
  int res=_heapchk();
  if (res==_HEAPCORRUPT)
  { Trace("**************** ERROR *******************");
    Trace("run-time library reports that the heap is corrupt");
    Trace("All bets are off");
  }
  if (res==_HEAPOK)
  { Trace("************* ERROR ********************");
    Trace("run-time library reports that the heap is not empty");
    _HEAPINFO hi;
    hi._pentry=NULL;
    int res=_rtl_heapwalk(&hi);
    while (res==_HEAPOK)
    { char c[100]; wsprintf(c,"rtl: heap at 0x%lx, size %i",hi._pentry,hi._useflag);
      Trace(c);
      res=_rtl_heapwalk(&hi);
    }
  }
  */
  char c[100]; wsprintf(c,"Max database entries used: %i",MaxUsed+1);
  char d[100]; wsprintf(d,"Calls to new: %i",NumNew);
  char e[100]; wsprintf(e,"Calls to delete (non-null): %i",NumDeletes);
  char f[100]; wsprintf(f,"Calls to delete (null): %i",NumNullDeletes);
  char g[100]; wsprintf(g,"Memory leakage: %i",leakage);
  char h[100]; strcpy(h,g); if (LogFile!=NULL) {strcat(h,"\r\nLog written to ");strcat(h,LogName);}
  Trace("**************** INFORMATION ****************");
  #pragma option -w-ccc
  Trace(c); Trace(d); Trace(e); if (ReportNulls) Trace(f); Trace(g);
  #pragma option -w.
  if (leakage>0 && NagScreen) MessageBox(NULL,h,"This isn't too good...",MB_OK);
  EnsureLogFileClosed();
  EnsureSymsClosed();
  InternalCall=oldval;
}









bool CheckSafetyAreas(void *FakeMem)
{ if (FakeMem==NULL) return true;
  void *RealMem=(char*)FakeMem - LoSafetySize;
  //int res=heapcheck();
  //if (res==_HEAPCORRUPT)
  //{ Trace("*************** ERROR ************************");
  //  Trace("The runtime library reported a corrupt heap");
  //  Trace("All bets are off");
  //}
  //
  // Check that pointer is in our database
  int i; for (i=0;i<NumEnts && Mems[i].Address!=FakeMem;i++);
  if (i==NumEnts)
  { char c[100]; wsprintf(c,"CheckMem: Pointer 0x%lx couldn't be found",FakeMem);
    if (!MemsFull) Trace("******************* ERROR *******************");
    Trace(c);
    Trace("It's therefore not possible to check if its safety areas were corrupted");
    return false;
  }
  // Check safety areas
  LPBYTE locheckmem=(LPBYTE)RealMem;
  LPBYTE hicheckmem=(LPBYTE)FakeMem+Mems[i].Size;
  TCallstackHeader *csh=(TCallstackHeader*)((LPBYTE)hicheckmem+HiSafetySize);
  bool UnderWritten=false, OverWritten=false;
  for (int i=0; i<LoSafetySize; i++) if (locheckmem[i]!=SafetyChar) UnderWritten=true;
  for (int i=0; i<HiSafetySize; i++) if (hicheckmem[i]!=SafetyChar) OverWritten=true;
  if (!OverWritten && !UnderWritten) return true;
  //
  char c[100];
  wsprintf(c,"The memory block at 0x%lx is corrupt",FakeMem);
  Trace("****************** WARNING ******************");
  Trace(c);
  if (UnderWritten) Trace("The low safety area has been changed");
  if (OverWritten) Trace("The high safety area has been changed.");
  Trace("The memory block in question was created at");
  PrintCallstack((TCallstack*)csh);
  char *msg="";
  if (OverWritten && !UnderWritten) msg="Block had overrun";
  if (!OverWritten && UnderWritten) msg="Block had been underwritten";
  if (OverWritten && UnderWritten) msg="Block had overrun below and above";
  #pragma option -w-ccc
  if (NagScreen) MessageBox(NULL,msg,"This is terrible",MB_OK);
  #pragma option -w.
  return false;
}





