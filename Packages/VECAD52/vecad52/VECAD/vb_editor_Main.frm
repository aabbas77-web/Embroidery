VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "VeCAD"
   ClientHeight    =   5730
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   8250
   LinkTopic       =   "Form1"
   ScaleHeight     =   286.5
   ScaleMode       =   2  'Point
   ScaleWidth      =   412.5
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.Menu File 
      Caption         =   "File"
      Index           =   1
      WindowList      =   -1  'True
      Begin VB.Menu New 
         Caption         =   "New..."
      End
      Begin VB.Menu Open 
         Caption         =   "Open..."
      End
      Begin VB.Menu Save 
         Caption         =   "Save"
      End
      Begin VB.Menu SaveAs 
         Caption         =   "SaveAs..."
      End
      Begin VB.Menu fsep1 
         Caption         =   "-"
      End
      Begin VB.Menu Close 
         Caption         =   "Close"
      End
      Begin VB.Menu CloseAll 
         Caption         =   "Close All"
      End
      Begin VB.Menu DwgList 
         Caption         =   "List..."
      End
      Begin VB.Menu fsep2 
         Caption         =   "-"
      End
      Begin VB.Menu import 
         Caption         =   "Import from"
         Begin VB.Menu impdxf 
            Caption         =   "AutoCAD DXF"
         End
      End
      Begin VB.Menu exp 
         Caption         =   "Export to"
         Begin VB.Menu expdxf 
            Caption         =   "AutoCAD DXF"
         End
         Begin VB.Menu exphpgl 
            Caption         =   "HPGL (PLT)"
         End
         Begin VB.Menu expbmp 
            Caption         =   "Raster Image"
         End
      End
      Begin VB.Menu sv1 
         Caption         =   "-"
      End
      Begin VB.Menu Print 
         Caption         =   "Print..."
      End
      Begin VB.Menu A 
         Caption         =   "-"
      End
      Begin VB.Menu Exit 
         Caption         =   "Exit"
      End
   End
   Begin VB.Menu Edit 
      Caption         =   "Edit"
      Index           =   2
      Begin VB.Menu undo 
         Caption         =   "Undo"
         Shortcut        =   ^Z
      End
      Begin VB.Menu redo 
         Caption         =   "Redo"
      End
      Begin VB.Menu edsep1 
         Caption         =   "-"
      End
      Begin VB.Menu objprop 
         Caption         =   "Properties..."
      End
      Begin VB.Menu edsep2 
         Caption         =   "-"
      End
      Begin VB.Menu Copy 
         Caption         =   "Copy"
      End
      Begin VB.Menu Move 
         Caption         =   "Move"
      End
      Begin VB.Menu Rotate 
         Caption         =   "Rotate"
      End
      Begin VB.Menu scale 
         Caption         =   "Scale"
      End
      Begin VB.Menu mirror 
         Caption         =   "Mirror"
      End
      Begin VB.Menu explode 
         Caption         =   "Explode"
      End
      Begin VB.Menu edsep3 
         Caption         =   "-"
      End
      Begin VB.Menu creblock 
         Caption         =   "Create Block"
      End
      Begin VB.Menu edsep4 
         Caption         =   "-"
      End
      Begin VB.Menu erase 
         Caption         =   "Erase"
      End
   End
   Begin VB.Menu View 
      Caption         =   "View"
      Index           =   3
      Begin VB.Menu ZoomWin 
         Caption         =   "Zoom Window"
         Shortcut        =   ^W
      End
      Begin VB.Menu zoomall 
         Caption         =   "Zoom All"
         Shortcut        =   ^A
      End
      Begin VB.Menu ZoomPan 
         Caption         =   "Zoom Pan"
      End
      Begin VB.Menu ZoomIn 
         Caption         =   "Zoom In"
      End
      Begin VB.Menu ZoomOut 
         Caption         =   "Zoom Out"
      End
      Begin VB.Menu vsep1 
         Caption         =   "-"
      End
      Begin VB.Menu PageFirst 
         Caption         =   "Page First"
      End
      Begin VB.Menu PageLast 
         Caption         =   "Page Last"
      End
      Begin VB.Menu PageNext 
         Caption         =   "Page Next"
      End
      Begin VB.Menu PagePrevious 
         Caption         =   "Page Previous"
      End
      Begin VB.Menu vsep2 
         Caption         =   "-"
      End
      Begin VB.Menu selpage 
         Caption         =   "Select Page"
         Shortcut        =   ^P
      End
      Begin VB.Menu vsep3 
         Caption         =   "-"
      End
      Begin VB.Menu SaveCurrentView 
         Caption         =   "Save Current View..."
      End
      Begin VB.Menu ViewsList 
         Caption         =   "Views List..."
      End
   End
   Begin VB.Menu Format 
      Caption         =   "Format"
      Index           =   4
      Begin VB.Menu Page 
         Caption         =   "Page..."
      End
      Begin VB.Menu Layer 
         Caption         =   "Layer..."
      End
      Begin VB.Menu Linetype 
         Caption         =   "Linetype..."
      End
      Begin VB.Menu TextStyle 
         Caption         =   "Text Style..."
      End
      Begin VB.Menu PointStyle 
         Caption         =   "Point Style..."
      End
      Begin VB.Menu HatchStyle 
         Caption         =   "Hatch Style..."
      End
      Begin VB.Menu Blocks 
         Caption         =   "Blocks..."
      End
      Begin VB.Menu fmtsep1 
         Caption         =   "-"
      End
      Begin VB.Menu DimStyle 
         Caption         =   "Dimension Style..."
      End
      Begin VB.Menu fmtsep2 
         Caption         =   "-"
      End
      Begin VB.Menu Grid 
         Caption         =   "Grid..."
      End
      Begin VB.Menu ObjectSnap 
         Caption         =   "Object Snap..."
      End
      Begin VB.Menu AngleSnap 
         Caption         =   "Angle Snap..."
      End
      Begin VB.Menu fmtsep3 
         Caption         =   "-"
      End
      Begin VB.Menu Units 
         Caption         =   "Units..."
      End
      Begin VB.Menu Private 
         Caption         =   "Private..."
      End
      Begin VB.Menu Preferences 
         Caption         =   "Preferences..."
      End
   End
   Begin VB.Menu Draw 
      Caption         =   "Draw"
      Index           =   5
      Begin VB.Menu point 
         Caption         =   "Point"
      End
      Begin VB.Menu Line 
         Caption         =   "Line"
      End
      Begin VB.Menu Polyline 
         Caption         =   "Polyline"
      End
      Begin VB.Menu Spline 
         Caption         =   "Spline"
      End
      Begin VB.Menu Circle 
         Caption         =   "Circle"
         Begin VB.Menu CenterRadius 
            Caption         =   "Center, Radius"
         End
         Begin VB.Menu CenterDiameter 
            Caption         =   "Center, Diameter"
         End
         Begin VB.Menu Points2 
            Caption         =   "2 Points"
         End
         Begin VB.Menu Points3 
            Caption         =   "3 Points"
         End
      End
      Begin VB.Menu arc 
         Caption         =   "Arc"
         Begin VB.Menu CenterStartEnd 
            Caption         =   "Center, Start, End"
         End
         Begin VB.Menu StartEndMiddle 
            Caption         =   "Start, End, Middle"
         End
         Begin VB.Menu StartMiddleEnd 
            Caption         =   "Start, Middle, End"
         End
      End
      Begin VB.Menu ellipse 
         Caption         =   "Ellipse"
      End
      Begin VB.Menu Rectangle 
         Caption         =   "Rectangle"
      End
      Begin VB.Menu Dimension 
         Caption         =   "Dimension"
         Begin VB.Menu DimHor 
            Caption         =   "Horizontal"
         End
         Begin VB.Menu DimVer 
            Caption         =   "Verical"
         End
         Begin VB.Menu DimPar 
            Caption         =   "Parallel"
         End
         Begin VB.Menu DimAng 
            Caption         =   "Angular"
         End
         Begin VB.Menu DimRad 
            Caption         =   "Radial"
         End
         Begin VB.Menu DimDiam 
            Caption         =   "Diametric"
         End
         Begin VB.Menu DimOrd 
            Caption         =   "Ordinate"
         End
      End
      Begin VB.Menu Hatch 
         Caption         =   "Hatch"
      End
      Begin VB.Menu drsep1 
         Caption         =   "-"
      End
      Begin VB.Menu Text 
         Caption         =   "Text..."
      End
      Begin VB.Menu Symbol 
         Caption         =   "TTF Symbol..."
      End
      Begin VB.Menu Block 
         Caption         =   "Block..."
      End
      Begin VB.Menu bitmap 
         Caption         =   "Raster Image..."
      End
      Begin VB.Menu RMap 
         Caption         =   "Mosaic Raster Map..."
      End
   End
   Begin VB.Menu tools 
      Caption         =   "Tools"
      Begin VB.Menu DistArea 
         Caption         =   "Distance / Area"
      End
      Begin VB.Menu prnrect 
         Caption         =   "Split drawing for print"
      End
      Begin VB.Menu Stat 
         Caption         =   "Statistics..."
      End
   End
   Begin VB.Menu Help 
      Caption         =   "Help"
      Begin VB.Menu About 
         Caption         =   "About..."
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub Command1_Click()
End Sub

Private Sub About_Click()
'  About.Show
End Sub

Private Sub AngleSnap_Click()
  vlExecute VC_FMT_PSNAP
End Sub

Private Sub bitmap_Click()
  vlExecute VC_INS_IMAGE
End Sub

Private Sub block_Click()
  vlExecute VC_INS_BLOCK
End Sub

Private Sub Blocks_Click()
  vlExecute VC_FMT_BLOCK
End Sub

Private Sub CenterDiameter_Click()
  vlExecute VC_DRAW_CIRC_CD
End Sub

Private Sub CenterRadius_Click()
  vlExecute VC_DRAW_CIRC_CR
End Sub

Private Sub CenterStartEnd_Click()
  vlExecute VC_DRAW_ARC_CSE
End Sub


Private Sub Command3_Click()
End Sub

Private Sub Close_Click()
  vlExecute VC_FILE_CLOSE
End Sub

Private Sub CloseAll_Click()
  vlExecute VC_FILE_CLOSEALL
End Sub

Private Sub Copy_Click()
  vlExecute VC_EDIT_COPY
End Sub

Private Sub creblock_Click()
  vlExecute VC_EDIT_CREBLOCK
End Sub

Private Sub DimAng_Click()
  vlExecute VC_DRAW_DIM_ANG
End Sub

Private Sub DimDiam_Click()
  vlExecute VC_DRAW_DIM_DIAM
End Sub

Private Sub DimHor_Click()
  vlExecute VC_DRAW_DIM_HOR
End Sub

Private Sub DimOrd_Click()
  vlExecute VC_DRAW_DIM_ORD
End Sub

Private Sub DimPar_Click()
  vlExecute VC_DRAW_DIM_PAR
End Sub

Private Sub DimRad_Click()
  vlExecute VC_DRAW_DIM_RAD
End Sub

Private Sub DimStyle_Click()
  vlExecute VC_FMT_STDIM
End Sub

Private Sub DimVer_Click()
  vlExecute VC_DRAW_DIM_VER
End Sub

Private Sub DistArea_Click()
  vlExecute VC_TOOL_DIST
End Sub

Private Sub DwgList_Click()
  vlFileList hwnd
End Sub

Private Sub ellipse_Click()
  vlExecute VC_DRAW_ELLIPSE
End Sub

Private Sub erase_Click()
  vlExecute VC_EDIT_ERASE
End Sub

Private Sub Exit_Click()
  Unload Form1
End Sub

Private Sub expbmp_Click()
  vlExecute VC_EXPORT_BMP
End Sub

Private Sub expdxf_Click()
  vlExecute VC_EXPORT_DXF
End Sub

Private Sub exphpgl_Click()
  vlExecute VC_EXPORT_HPGL
End Sub

Private Sub explode_Click()
  vlExecute VC_EDIT_EXPLODE
End Sub

Private Sub FileProp_Click()
End Sub

Private Sub Form_Initialize()
  CreateVecWindow hwnd
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  Dim ret As Boolean
  ret = vlExecute(VC_FILE_CLOSEALL)
  If (ret = False) Then
    Cancel = 1   ' don't close window
  End If
End Sub

Private Sub Form_Resize()
  ResizeVecWindow hwnd
End Sub

Private Sub menu1_Click()
End Sub

Private Sub Grid_Click()
  vlExecute VC_FMT_GRID
End Sub

Private Sub hatch_Click()
  vlExecute VC_DRAW_HATCH
End Sub

Private Sub HatchStyle_Click()
  vlExecute VC_FMT_STHATCH
End Sub

Private Sub impdxf_Click()
  vlExecute VC_IMPORT_DXF
End Sub

Private Sub Layer_Click()
  vlExecute VC_FMT_LAYER
End Sub

Private Sub Line_Click()
  vlExecute VC_DRAW_LINE
End Sub

Private Sub Linetype_Click()
  vlExecute VC_FMT_STLINE
End Sub

Private Sub mirror_Click()
  vlExecute VC_EDIT_MIRROR
End Sub

Private Sub Move_Click()
  vlExecute VC_EDIT_MOVE
End Sub

Private Sub New_Click()
  FileNew
End Sub

Private Sub ObjectSnap_Click()
  vlExecute VC_FMT_OSNAP
End Sub

Private Sub objprop_Click()
  vlExecute VC_EDIT_ENTPROP
End Sub

Private Sub Open_Click()
  FileOpen
End Sub

Private Sub Page_Click()
  vlExecute VC_FMT_PAGE
End Sub

Private Sub PageFirst_Click()
  vlExecute VC_PAGE_FIRST
End Sub

Private Sub PageLast_Click()
  vlExecute VC_PAGE_LAST
End Sub

Private Sub PageNext_Click()
  vlExecute VC_PAGE_NEXT
End Sub

Private Sub PagePrevious_Click()
  vlExecute VC_PAGE_PREV
End Sub

Private Sub point_Click()
  vlExecute VC_DRAW_POINT
End Sub

Private Sub Points2_Click()
  vlExecute VC_DRAW_CIRC_2P
End Sub

Private Sub Points3_Click()
  vlExecute VC_DRAW_CIRC_3P
End Sub

Private Sub PointStyle_Click()
  vlExecute VC_FMT_STPOINT
End Sub

Private Sub Polyline_Click()
  vlExecute VC_DRAW_POLYLINE
End Sub

Private Sub Preferences_Click()
  vlExecute VC_FMT_PREFERS
End Sub

Private Sub Print_Click()
  vlExecute VC_PRINT
End Sub

Private Sub Private_Click()
  vlExecute VC_FMT_PRIVATE
End Sub

Private Sub prnrect_Click()
  vlExecute VC_TOOL_PRNRECT
End Sub

Private Sub rectangle_Click()
  vlExecute VC_DRAW_RECT
End Sub

Private Sub redo_Click()
  vlExecute VC_EDIT_REDO
End Sub

Private Sub RMap_Click()
  vlExecute VC_INS_RMAP
End Sub

Private Sub Rotate_Click()
  vlExecute VC_EDIT_ROTATE
End Sub

Private Sub Save_Click()
  vlExecute VC_FILE_SAVE
End Sub

Private Sub SaveAs_Click()
  vlExecute VC_FILE_SAVEAS
End Sub

Private Sub SaveCurrentView_Click()
  vlExecute VC_VIEW_SAVE
End Sub

Private Sub scale_Click()
  vlExecute VC_EDIT_SCALE
End Sub


Private Sub selpage_Click()
  vlExecute VC_PAGE_DLG
End Sub


Private Sub Spline_Click()
  vlExecute VC_DRAW_SPLINE
End Sub

Private Sub StartEndMiddle_Click()
  vlExecute VC_DRAW_ARC_SEM
End Sub

Private Sub StartMiddleEnd_Click()
  vlExecute VC_DRAW_ARC_SME
End Sub

Private Sub Stat_Click()
  vlExecute VC_TOOL_STAT
End Sub

Private Sub symbol_Click()
  vlExecute VC_INS_SYMBOL
End Sub

Private Sub text_Click()
  vlExecute VC_INS_TEXT
End Sub

Private Sub TextStyle_Click()
  vlExecute VC_FMT_STTEXT
End Sub

Private Sub undo_Click()
  vlExecute VC_EDIT_UNDO
End Sub

Private Sub Units_Click()
  vlExecute VC_FMT_UNITS
End Sub

Private Sub ViewsList_Click()
  vlExecute VC_VIEW_LIST
End Sub

Private Sub zoomall_Click()
  vlExecute VC_ZOOM_ALL
End Sub

Private Sub ZoomIn_Click()
  vlExecute VC_ZOOM_IN
End Sub

Private Sub ZoomOut_Click()
  vlExecute VC_ZOOM_OUT
End Sub

Private Sub ZoomWin_Click()
  vlExecute VC_ZOOM_WIN
End Sub
