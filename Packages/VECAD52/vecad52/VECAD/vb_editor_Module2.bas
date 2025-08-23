Attribute VB_Name = "Module2"
Public hwVec As Long   ' handle to drawing window
Public VecX0 As Long   ' top of drawing window
Public VecY0 As Long   ' left of drawing window
Public SBarH As Long   ' height of status bar

Sub CreateVecWindow(ByVal hwnd As Long)
  Dim W As Long, H As Long, h2 As Long
  Dim X As Long, Y As Long
  Dim WinStyle As Long
  
  ' Register your copy of Vecad.dll
  vlRegistration 0    'use your reg. code here
  ' Define the function that will receive VeCAD messages
  vlSetMsgHandler AddressOf DwgProc
  ' Create VeCAD toolbars
  W = 0
  H = 0
  h2 = 0
  X = 0
  Y = -1
  vlToolBarCreate hwnd, VL_TB_MAIN, X, Y, -1, 1, W, H
  Y = Y + H
  h2 = H
  X = 0
  vlToolBarCreate hwnd, VL_CB_LAYER, X, Y, 210, h2, W, H
  X = X + W
  vlToolBarCreate hwnd, VL_CB_COLOR, X, Y, 90, h2, W, H
  X = X + W
  vlToolBarCreate hwnd, VL_CB_STLINE, X, Y, 200, h2, W, H
  X = X + W
  vlToolBarCreate hwnd, VL_TB_SNAP, X, Y, -1, 1, W, H
  Y = Y + H
  vlToolBarCreate hwnd, VL_TB_DRAW, 0, Y, 60, 500, W, H
  Y = Y + H
  vlToolBarCreate hwnd, VL_TB_EDIT, 0, Y, 60, -1, W, H
  X = W
  Y = h2 + h2 - 1
  VecX0 = X
  VecY0 = Y
  
  ' Create VeCAD StatusBar
  vlStatBarCreate hwnd, SBarH
  
  ' Create VeCAD window, size will be set in OnSize()
  WinStyle = VL_WS_CHILD + VL_WS_SCROLL + VL_WS_BORDER
  hwVec = vlWndCreate(hwnd, WinStyle, 0, 0, 400, 300)
  
  If (hwVec >= 0) Then
    vlPropPut VD_WND_EMPTYTEXT, hwVec, "VeCAD 5.1; By Visual Basic;"
  End If
End Sub

Sub ResizeVecWindow(ByVal hwnd As Long)
  Dim W As Long, H As Long
  
  vlGetWinSize hwnd, W, H
  If (W > 0 And H > 0) Then
    ' Resize drawing window
    vlWndResize hwVec, VecX0, VecY0, W - VecX0, H - VecY0 - SBarH
    ' Resize statusbar
    vlStatBarResize
  End If
End Sub

Sub UpdateMainTitle()
  Dim iPage As Long, nPage As Long, n As Long
  Dim FileName As String, PageName As String, Pos As String

  FileName = Space(255)
  PageName = Space(128)
  iPage = vlPageIndex("", 0)
  nPage = vlPageCount()
  Pos = Format(iPage + 1, "0") + "/" + Format(nPage, "0")
  vlPropGet VD_DWG_FILENAME, -1, FileName
  vlPropGet VD_PAGE_NAME, iPage, PageName
  n = InStr(FileName, Chr(0)) - 1
  FileName = Left(FileName, n)
  n = InStr(PageName, Chr(0)) - 1
  PageName = Left(PageName, n)
  Form1.Caption = "Editor - [" + FileName + "], page: " + Pos + " """ + PageName + """"
End Sub

Sub FileNew()
  vlFileNew hwVec, ""
End Sub

Sub FileOpen()
  vlFileOpen hwVec, ""
End Sub

