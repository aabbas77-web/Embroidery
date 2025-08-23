unit Funcs;

interface
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  OleCtnrs, StdCtrls, ExtCtrls, ComCtrls, Menus, Printers;


procedure CreateVecWindow (Handle:HWND);
procedure ResizeVecWindow (Handle:HWND);
procedure FileNew;
procedure FileOpen;
procedure UpdateMainTitle;
procedure TestLineStyles;

var
  ghwVec:HWND;   // VeCAD window to display draw
  VecX0:Integer;
  VecY0:Integer;
  SBarH:Integer;  // height of status bar

implementation

uses
  delphi_editor_Main, api_VecApi, delphi_editor_DwgProc;


//-------------------------------------------------------------------
procedure UpdateMainTitle;
var
  iPage, nPage : Integer;
//  buf : array[0..255] of char;
  FileName : array[0..255] of char;
  PageName : array[0..79] of char;
  Title, Pos, Pos1, Pos2 : string;
begin
  iPage := vlPageIndex( '', 0 );
  nPage := vlPageCount();
//  Pos := Str(iPage + 1)tr(nPage);
  Str(iPage+1, Pos1);
  Str(nPage, Pos2);
  Pos := Pos1 + '/' + Pos2;
  vlPropGet( VD_PAGE_NAME, iPage, @PageName );
  vlPropGet( VD_DWG_FILENAME, -1, @FileName );
  if (FileName='') then
  begin
    FileName := 'noname';
  end;
  Title := 'Editor - ['+FileName+'], page: ' + Pos + ' "' + PageName + '"';
//  Title := Title + ', Page:' + PageName;
  Form1.Caption := Title;
end;

//-------------------------------------------------------------------
procedure CreateVecWindow (Handle:HWND);
var
  x,y,w,h,h2:Integer;
  str: array[0..255] of char;
begin
  vlRegistration( 0 ); // enter your reg. code here

  // Register your copy of Vecad.dll
  vlRegistration( 0 );
  // Set function that will receive VeCAD messages
  vlSetMsgHandler( @MyDwgProc );
  // Create VeCAD toolbar
  w:=0;
  h:=0;
  x:=0;
  y:=-1;
  vlToolBarCreate( Handle, VL_TB_MAIN, x, y, -1, 1, @w, @h );
  y:=y+h;
  h2:=h;
  x:=0;
  vlToolBarCreate( Handle, VL_CB_LAYER, x, y, 210, h2, @w, @h );
  x:=x+w;
  vlToolBarCreate( Handle, VL_CB_COLOR, x, y, 90, h2, @w, @h );
  x:=x+w;
  vlToolBarCreate( Handle, VL_CB_STLINE, x, y, 200, h2, @w, @h );
  x:=x+w;
  vlToolBarCreate( Handle, VL_TB_SNAP, x, y, -1, 1, @w, @h );
  y:=y+h;
  vlToolBarCreate( Handle, VL_TB_DRAW, 0, y, 60, 500, @w, @h );
  y:=y+h;
  vlToolBarCreate( Handle, VL_TB_EDIT, 0, y, 60, -1, @w, @h );
  x:=w;
  y:=h2+h2-1;
  VecX0:=x;
  VecY0:=y;
  // Create VeCAD StatusBar
  vlStatBarCreate( Handle, @SBarH );
  // Create VeCAD window, size will be set in OnSize()
  ghwVec := vlWndCreate( Handle, VL_WS_CHILD+VL_WS_SCROLL+VL_WS_BORDER, 0,0,400,300 );
  if (ghwVec<>0) then
  begin
    str := 'Editor';
    vlPropPut( VD_WND_EMPTYTEXT, ghwVec, @str );
//    vlPropPutInt( VD_WND_CURSOR_CROSS, ghwVec, 0 );
  end
end;

//-------------------------------------------------------------------
procedure ResizeVecWindow (Handle:HWND);
var
  w,h:Integer;
begin
  vlGetWinSize( Handle, @w, @h );
  If ((w > 0) And (h > 0)) Then
  begin
    // Resize drawing window
    vlWndResize( ghwVec, VecX0, VecY0, w - VecX0, h - VecY0 - SBarH );
    // Resize statusbar
    vlStatBarResize();
  end
end;

//-------------------------------------------------------------------
procedure FileNew;
//var
//  iDwg:Integer;
begin
  vlFileNew( ghwVec, '' );
{
  iDwg := vlDocCreate( ghwVec );
  if (iDwg>=0) then
  begin
    vlClear( true );
    vlRedraw();
    vlSetFocus();
  end
}
end;

//-------------------------------------------------------------------
procedure FileOpen;
//var
//  iDwg:Integer;
begin
  vlFileOpen( ghwVec, '' );
{
  iDwg := vlDocCreate( ghwVec );
  if (iDwg>=0) then
  begin
    if (vlFileLoad( VL_FILE_VEC, '' )=false) then
    begin
      vlDwgDelete( iDwg );
    end
  end
}
end;

//-------------------------------------------------------------------
//  Test line styles
//-------------------------------------------------------------------
procedure TestLineStyles;
var
  ls1, ls2, i: Integer;
begin
  vlFileNew( ghwVec, '' );
  ls1 := vlStLineAdd( 'abc', '1, -1' );
  ls2 := vlStLineAdd( 'dash dot', '2, -0.5, 0, -0.5' );
  vlStLineAdd( 'T-line', '3., -1.5, L(0. -0.5 0. 0.5), L(-0.5 0.5 0.5 0.5), -1.5' );
  vlStLineActive( 0 );  // default solid line style
  vlAddLine( 0,0, 10,20 );
  vlStLineActive( ls1 );
  vlAddLine( 10,20, 30,10 );
  vlStLineActive( ls2 );
  vlAddLine( 30,10, 0,0 );
  i := vlStLineIndex( 'T-line', 0 );
  vlStLineActive( i );
  vlAddLine( 0,15, 30,0 );
  vlUpdate();
  vlZoom( VL_ZOOM_ALL );
  vlSetFocus();
end;


end.
