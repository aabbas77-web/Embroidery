Attribute VB_Name = "Module1"

Function DwgProc(ByVal hDwg As Long, ByVal Msg As Long, ByVal Prm1 As Long, ByVal Prm2 As Long, ByVal Prm3 As Double, ByVal Prm4 As Double, Prm5 As String) As Long
  DwgProc = 0
  Select Case Msg
    Case VM_GETSTRING
      DwgProc = LoadString(Prm1)
     
    Case VM_OBJSELECT
      If (Prm1 = VL_OBJ_PAGE) Then
        UpdateMainTitle
      End If

    Case VM_DWGLOADED
      ' here filename can be saved to MRU list
      ' gMruList.Add( (LPCTSTR)Prm5 );
      UpdateMainTitle
      
    Case VM_DWGSAVED:
      ' here filename can be saved to MRU list
      ' gMruList.Add( (LPCTSTR)Prm5 );
      UpdateMainTitle
    
    Case VM_DWGSELECT
      UpdateMainTitle

    Case VM_DWGLOADING
    Case VM_DWGSAVING
      '_stprintf( szStr, _T("Loading: %d%%"), Prm1 );
      'vlStatBarSetText( VL_SB_COORD, szStr );
      
    Case VM_EXECUTE
      If (Prm2 <> 0 And (Prm1 = VC_FILE_NEW Or Prm1 = VC_FILE_OPEN)) Then
        Select Case Prm1
          Case VC_FILE_NEW
            FileNew
          Case VC_FILE_OPEN
            FileOpen
        End Select
      End If
  End Select
End Function


