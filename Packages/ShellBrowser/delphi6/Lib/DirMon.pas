{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Component:    TDirMon
Description:  This component encapsulate the Win 32 API function
              FindFirstChangeNotification. The primary purpose of this
              component is to monitor changes in a given directory and fire
              an event when a change occurs (file creation, deletion, ...).
Version:      1.03 for ShellBrowser
Created:      March 27, 1997
Author:       François PIETTE
              Modified by Joachim Marder for ShellBrowser
Email:        francois.piette@ping.be  http://www.rtfm.be/fpiette
WebSite:      http://www.rtfm.be/fpiette/indexuk.htm
Support:      Use the mailing list twsocket@rtfm.be See website for details.
Legal issues: Copyright (C) 1997 by François PIETTE <francois.piette@ping.be>

              This software is provided 'as-is', without any express or
              implied warranty.  In no event will the author be held liable
              for any  damages arising from the use of this software.

              Permission is granted to anyone to use this software for any
              purpose, including commercial applications, and to alter it
              and redistribute it freely, subject to the following
              restrictions:

              1. The origin of this software must not be misrepresented,
                 you must not claim that you wrote the original software.
                 If you use this software in a product, an acknowledgment
                 in the product documentation would be appreciated but is
                 not required.

              2. Altered source versions must be plainly marked as such, and
                 must not be misrepresented as being the original software.

              3. This notice may not be removed or altered from any source
                 distribution.

Modification History:
Aug 07, 1997 V1.00 Added some comments
Feb 03, 1998 V1.01 Douglas R. Kraul <harmonysystems@mindspring.com>
             fixed problem with MUTEX immediately being available in monitor
             thread after creation.  NT only prblem?
             Also added new published property to allow nested directories
             to be monitored
Feb 04, 1998 V1.02 Beautified the source code.
             Removed unnecessary Set/GetNested function.
May 17, 1998 V1.03  Werner Lehmann <wl@bwl.uni-kiel.de> found that there is a
             bug in FindFirstChangeNotification which only accept 0/1 in the
             bWatchSubTree argument.


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit DirMon;

interface

{$I VER.INC}   // Added by J. Marder on 11 Feb 1999
{$BOOLEVAL OFF} // Added by J. Marder on 06 Nov 2001
{$IFDEF _CPPB_3_UP}
  {$ObjExportAll On}
{$ENDIF}

uses
    Windows,
    SysUtils,
    Messages,
    Classes,
    Graphics,
    Controls,
    Dialogs,
    Menus
{$ifndef _VCL_6_UP} ,Forms {$endif}; // Changed by J. Marder on 24 Jul 2001

const
    WM_DIRCHANGE= WM_USER + 1;

type
    TDirMonValue = (dmcFileName,
                    dmcDirName,
                    dmcAttributes,
                    dmcSize,
                    dmcLastWrite,
                    dmcSecurity);
    TDirMonType = set of TDirMonValue;

    TDirMon = class(TComponent)
    private
        FDirectory    : String;
        FNotifyFilter : DWORD;
        FWindowHandle : HWND;
        FParamPtr     : Pointer;
        FMutexHandle  : THandle;
        FNested       : Boolean;
        FThreadHandle : THandle;
        FThreadID     : DWORD;
        FOnDirChange  : TNotifyEvent;
        FOnStart      : TNotifyEvent;
        FOnStop       : TNotifyEvent;
        procedure WndProc(var MsgRec: TMessage);
        procedure WMDirChange(var aMsg: TMessage); message WM_DIRCHANGE;
    protected
        procedure SetNotifyFilter(newValue : TDirMonType);
        function  GetNotifyFilter : TDirMonType;
        procedure SetDirectory(newValue : String);
        procedure TriggerDirChangeEvent; virtual;
        procedure TriggerStartEvent; virtual;
        procedure TriggerStopEvent; virtual;
    public
        constructor Create(AOwner : TComponent); override;
        destructor  Destroy; override;
        procedure   Start;
        procedure   Stop;
        property    Handle : HWND               read  FWindowHandle;
    published
        { Published properties and events }
        property Directory : String             read  FDirectory
                                                write SetDirectory;
        property NotifyFilter : TDirMonType     read  GetNotifyFilter
                                                write SetNotifyFilter;
        property OnDirChange : TNotifyEvent     read  FOnDirChange
                                                write FOnDirChange;
        property Nested: Boolean                read  FNested
                                                write FNested;
        property OnStart : TNotifyEvent         read  FOnStart
                                                write FOnStart;
        property OnStop : TNotifyEvent          read  FOnStop
                                                write FOnStop;
    end;

procedure Register;

implementation

type
  TDirMonParams = record
      WindowHandle : HWND;
      hMutex       : THandle;
      Directory    : array [0..MAX_PATH] of char;
      NotifyFilter : DWORD;
      Nested       : boolean;
  end;
  PDirMonParams = ^TDirMonParams;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure Register;
begin
    //RegisterComponents('FPiette', [TDirMon]);//Changed 06 Feb 1999 by Joachim Marder
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.SetDirectory(newValue : String);
begin
    if (Length(newValue)>3) and (newValue[Length(newValue)]='\') then
      Delete(newValue, LEngth(newValue), 1); //Changed by J. Marder on 07 Feb 1999

    if newValue = FDirectory then
        Exit;

    if FThreadHandle <> 0 then Stop; //Changed by J. Marder on 06 Feb 1999
////        raise Exception.Create('Unable to change Directory ' +
//                               'when DirMon is running');
    FDirectory := newValue;
    Start;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.SetNotifyFilter(newValue : TDirMonType);
begin
    if FThreadHandle <> 0 then
        raise Exception.Create('Unable to change NotifyFilter ' +
                               'when DirMon is running');

    FNotifyFilter := 0;
    if dmcFileName in newValue then
        FNotifyFilter := (FNotifyFilter or FILE_NOTIFY_CHANGE_FILE_NAME);
    if dmcDirName in newValue then
        FNotifyFilter := (FNotifyFilter or FILE_NOTIFY_CHANGE_DIR_NAME);
    if dmcAttributes in newValue then
        FNotifyFilter := (FNotifyFilter or FILE_NOTIFY_CHANGE_ATTRIBUTES);
    if dmcSize in newValue then
        FNotifyFilter := (FNotifyFilter or FILE_NOTIFY_CHANGE_SIZE);
    if dmcLastWrite in newValue then
        FNotifyFilter := (FNotifyFilter or FILE_NOTIFY_CHANGE_LAST_WRITE);
    if dmcSecurity in newValue then
        FNotifyFilter := (FNotifyFilter or FILE_NOTIFY_CHANGE_SECURITY);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TDirMon.GetNotifyFilter : TDirMonType;
begin
    Result := [];
    if (FNotifyFilter and FILE_NOTIFY_CHANGE_FILE_NAME) <> 0 then
        Result := Result + [dmcFileName];
    if (FNotifyFilter and FILE_NOTIFY_CHANGE_DIR_NAME) <> 0 then
        Result := Result + [dmcDirName];
    if (FNotifyFilter and FILE_NOTIFY_CHANGE_ATTRIBUTES) <> 0 then
        Result := Result + [dmcAttributes];
    if (FNotifyFilter and FILE_NOTIFY_CHANGE_SIZE) <> 0 then
        Result := Result + [dmcSize];
    if (FNotifyFilter and FILE_NOTIFY_CHANGE_LAST_WRITE) <> 0 then
        Result := Result + [dmcLastWrite];
    if (FNotifyFilter and FILE_NOTIFY_CHANGE_SECURITY) <> 0 then
        Result := Result + [dmcSecurity];
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.TriggerDirChangeEvent;
begin
    if assigned(FOnDirChange) then begin
        try
            FOnDirChange(Self);
        except
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.TriggerStartEvent;
begin
    if assigned(FOnStart) then
        FOnStart(Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.TriggerStopEvent;
begin
    if assigned(FOnStop) then
        FOnStop(Self);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TDirMon.Create(AOwner : TComponent);
begin
    inherited Create(AOwner);
    FWindowHandle := AllocateHWnd(WndProc);
    FNotifyFilter := FILE_NOTIFY_CHANGE_FILE_NAME;
    FNested       := False;
    FMutexHandle  := 0;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TDirMon.Destroy;
begin
    if FThreadHandle <> 0 then begin
        ReleaseMutex(FMutexHandle);
        WaitForSingleObject(FThreadHandle, INFINITE);
        CloseHandle(FThreadHandle); // Added by J. Marder on 13 Jun 2000
    end;

    if FParamPtr <> nil then begin
        FreeMem(FParamPtr);
        FParamPtr := nil;
    end;

    if FMutexHandle <> 0 then begin
        CloseHandle(FMutexHandle);
        FMutexHandle := 0;
    end;

    DeallocateHWnd(FWindowHandle);
    inherited Destroy;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.WndProc(var MsgRec: TMessage);
begin
     with MsgRec do begin
         if Msg = WM_DIRCHANGE then
             WMDirChange(MsgRec)
         else
             Result := DefWindowProc(Handle, Msg, wParam, lParam);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.WMDirChange(var aMsg: TMessage);
begin
    TriggerDirChangeEvent;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function MonitorThread(Prm : Pointer) : DWORD; stdcall;
var
    pParams      : PDirMonParams;
    hObjects     : array [0..1] of THandle;
    Status       : integer;
const
    B : array [FALSE..TRUE] of integer = (0, 1);
begin
    if Prm = nil then
        ExitThread(1);

    pParams := PDirMonParams(Prm);

    // There appears to be a bug in win 95 where the bWatchSubTree parameter
    // of FindFirstChangeNotification which is a BOOL only accepts values of
    // 0 and 1 as valid, rather than 0 and any non-0 value as it should.
    // In D2 BOOL was defined as 0..1 so the code worked, in D3 it is 0..-1
    // so fails. The result is FindF... produces and error message.
    // This fix is needed to produce a 0,1 bool pair, rather that 0,-1 as
    // declared in D3.
    hObjects[1] := pParams^.hMutex;
    hObjects[0] := FindFirstChangeNotification(pParams^.Directory,
                                               LongBool(B[pParams^.Nested]),
                                               pParams^.NotifyFilter);
    if hObjects[0] = INVALID_HANDLE_VALUE then begin
        {Application.MessageBox('FindFirstChangeNotification() failed',
                               'Warning', mb_OK);}
        ExitThread(GetLastError);
    end;

    while (TRUE) do begin
        Status := WaitForMultipleObjects(2, @hObjects, FALSE, INFINITE);
        case Status of
        WAIT_OBJECT_0:
            begin
                PostMessage(pParams^.WindowHandle, WM_DIRCHANGE, 0, 0);
                if not FindNextChangeNotification(hObjects[0]) then begin
                    FindCloseChangeNotification(hObjects[0]);
                    ExitThread(GetLastError);
                end;
            end;
        WAIT_OBJECT_0+1:
            begin
                FindCloseChangeNotification(hObjects[0]);
                ReleaseMutex(pParams^.hMutex);
                ExitThread(0);
            end;
        end;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.Start;
var
    p : PDirMonParams;
begin
    if (FThreadHandle <> 0) or (FDirectory ='') then exit;  //Changed by J. Marder on 06 Feb 1999
        //raise Exception.Create('DirMon already started');

    // Create mutex for stopping thread when needed
    // the TRUE parameter for acquiring does not seem to work correctly
    // under NT so the WaitFor is added so that the host process
    // gets the MUTEX
    FMutexHandle := CreateMutex(nil, False, nil);
    if FMutexHandle = 0 then
        raise Exception.Create('CreateMutex failed');
    WaitForSingleObject(FMutexHandle, INFINITE);

    // Allocate some memory for thread parameters
    GetMem(p, SizeOf(TDirMonParams));
    FParamPtr       := p;
    p^.WindowHandle := FWindowHandle;
    p^.hMutex       := FMutexHandle;
    p^.NotifyFilter := FNotifyFilter;
    p^.Nested       := FNested;
    StrCopy(p^.Directory, PChar(FDirectory));

    // Start the working thread
    FThreadHandle := CreateThread(
               nil,               // pointer to thread security attributes
               0,                 // initial thread stack size, in bytes
               @MonitorThread,    // pointer to thread function
               FParamPtr,         // argument for new thread
               0,                 // creation flags
               FThreadId);        // pointer to returned thread identifier

    if FThreadHandle = 0 then
        raise Exception.Create('CreateThread failed');

    TriggerStartEvent;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TDirMon.Stop;
begin
    if FThreadHandle = 0 then
        raise Exception.Create('DirMon not started');

    if FMutexHandle <> 0 then
        ReleaseMutex(FMutexHandle);

    if FThreadHandle <> 0 then begin
        WaitForSingleObject(FThreadHandle, INFINITE);
        CloseHandle(FThreadHandle); // Added by J. Marder on 13 Jun 2000
        FThreadHandle := 0;
        FThreadID     := 0;
    end;

    if FMutexHandle <> 0 then begin
        CloseHandle(FMutexHandle);
        FMutexHandle := 0;
    end;

    if FParamPtr <> nil then begin
        FreeMem(FParamPtr);
        FParamPtr := nil;
    end;

    TriggerStopEvent;
end;

end.


