Attribute VB_Name = "Module3"
'-------------------------------------------------------------------
'  Overwrite VeCAD strings
'  Used to localize VeCAD to other languages
'-------------------------------------------------------------------
Function LoadString(ByVal Id As Long) As Long
  Dim str As String
  LoadString = 1
  ' assign new string according to string's identifier
  Select Case Id
    Case VS_PRINT_TITLE
      str = "Print2"
    Case VS_ENTPROP_TITLE
      str = "Objects properties 2"
    Case VS_LINE_TITLE
      str = "Line2"
    Case Else
      LoadString = 0  ' string will not overwritten
  End Select
  ' pass new string to VeCAD
  If (LoadString = 1) Then
    vlPropPut VD_DWG_STRING, 0, str
  End If
End Function

