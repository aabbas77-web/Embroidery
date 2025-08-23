Attribute VB_Name = "VecApi"
'********************************************************************
'* VeCAD version 5.2.10
'* Copyright (c) 1999-2001 by Oleg Kolbaskin.
'* All rights reserved.
'*
'* This file must be included in the
'* Visual Basic project that used library VeCad.dll
'********************************************************************


Public Const VL_FALSE = 0
Public Const VL_TRUE = 1

' VeCAD window styles (vlWndCreate)
Public Const VL_WS_CHILD = 1
Public Const VL_WS_TILED = 2
Public Const VL_WS_BORDER = 4
Public Const VL_WS_SCROLL = 8
Public Const VL_WS_DEFAULT = VL_WS_CHILD + VL_WS_SCROLL

'/////////////////////////////////////////////////
'// VeCAD objects
Public Const VL_OBJ_PAGE = 1
Public Const VL_OBJ_LAYER = 2
Public Const VL_OBJ_STLINE = 3
Public Const VL_OBJ_MLINE = 4
Public Const VL_OBJ_STTEXT = 5
Public Const VL_OBJ_STHATCH = 6
Public Const VL_OBJ_STDIM = 7
Public Const VL_OBJ_STPOINT = 8
Public Const VL_OBJ_GRPOINT = 9
Public Const VL_OBJ_VIEW = 10
Public Const VL_OBJ_PRNRECT = 11
Public Const VL_OBJ_BLOCK = 12
Public Const VL_ENT_POINT = 21
Public Const VL_ENT_LINE = 22
Public Const VL_ENT_POLY = 23
Public Const VL_ENT_POLYLINE = 23
Public Const VL_ENT_CIRCLE = 24
Public Const VL_ENT_ARC = 25
Public Const VL_ENT_ARC2 = 26
Public Const VL_ENT_EARC = 26
Public Const VL_ENT_ELLIPSE = 27
Public Const VL_ENT_TEXT = 28
Public Const VL_ENT_BITMAP = 29
Public Const VL_ENT_INSBLOCK = 30
Public Const VL_ENT_BLOCKINS = 30
Public Const VL_ENT_HATCH = 31
Public Const VL_ENT_FLOOD = 32
Public Const VL_ENT_RECT = 34
Public Const VL_ENT_DIMLIN = 35
Public Const VL_ENT_DIMANG = 36
Public Const VL_ENT_DIMRAD = 37
Public Const VL_ENT_DIMDIAM = 38
Public Const VL_ENT_DIMORD = 39
Public Const VL_ENT_INSDWG = 41
Public Const VL_ENT_DWGINS = 41
Public Const VL_ENT_GLASS = 201

' Values for Mode argument of vlGetEntity
Public Const VL_EI_BYHANDLE = 1
Public Const VL_EI_BYKEY = 2
Public Const VL_EI_BYPOINT = 3
Public Const VL_EI_BYCURSOR = 4
Public Const VL_EI_FIRST = 6
Public Const VL_EI_NEXT = 7

' Filter type for VL_EI_FIRST
Public Const VL_DRAWING = 0
Public Const VL_SELECTION = 1

' Start page in "Drawing's Layout" dialog (vlDlgLayout)
Public Const VL_DPG_LAST = -1
Public Const VL_DPG_PAGE = 0
Public Const VL_DPG_LAYER = 1
Public Const VL_DPG_STLINE = 2
Public Const VL_DPG_MLINE = 3
Public Const VL_DPG_STTEXT = 4
Public Const VL_DPG_STHATCH = 5
Public Const VL_DPG_BLOCK = 6
Public Const VL_DPG_STPOINT = 7
Public Const VL_DPG_GRID = 0
Public Const VL_DPG_OBJSNAP = 1
Public Const VL_DPG_POLSNAP = 2

' IO Indexes for vlFileLoad and vlFileSave functions
Public Const VL_FILE_VEC = 1
Public Const VL_FILE_DXF = 2
Public Const VL_FILE_CNC = 3
Public Const VL_FILE_HPGL = 4
Public Const VL_FILE_PLT = 4
Public Const VL_FILE_VDF = 5
Public Const VL_FILE_DWG = 6
Public Const VL_FILE_AVSHP = 7
Public Const VL_FILE_ALL = 100
Public Const VL_FILE_CUSTOM = 101
Public Const VL_FILE_DROPS = 102
Public Const VL_FILE_LINES = 103

' Parameters for vlZoom function
Public Const VL_ZOOM_ALL = -1
Public Const VL_ZOOM_IN = -2
Public Const VL_ZOOM_OUT = -3
Public Const VL_ZOOM_LEFT = -4
Public Const VL_ZOOM_RIGHT = -5
Public Const VL_ZOOM_UP = -6
Public Const VL_ZOOM_DOWN = -7
Public Const VL_ZOOM_PAGE = -8
Public Const VL_ZOOM_PREV = -9
Public Const VL_ZOOM_SEL = -10

' Color constants
Public Const VL_COL_BLACK = &H80000000        'RGB(   0,   0,   0)
Public Const VL_COL_DIMGRAY = &H80696969      'RGB( 105, 105, 105)
Public Const VL_COL_DARKGRAY = &H80808080     'RGB( 128, 128, 128)
Public Const VL_COL_GRAY = &H80A9A9A9         'RGB( 169, 169, 169)
Public Const VL_COL_SILVER = &H80C0C0C0       'RGB( 192, 192, 192)
Public Const VL_COL_LIGHTGRAY = &H80D3D3D3    'RGB( 211, 211, 211)
Public Const VL_COL_GAINSBORO = &H80DCDCDC    'RGB( 220, 220, 220)
Public Const VL_COL_WHITESMOKE = &H80F5F5F5   'RGB( 245, 245, 245)
Public Const VL_COL_WHITE = &H80FFFFFF        'RGB( 255, 255, 255)
Public Const VL_COL_RED = &H800000FF          'RGB( 255,   0,   0)
Public Const VL_COL_GREEN = &H80008000        'RGB(   0, 128,   0)
Public Const VL_COL_BLUE = &H80FF0000         'RGB(   0,   0, 255)
Public Const VL_COL_CYAN = &H80FFFF00         'RGB(   0, 255, 255)
Public Const VL_COL_MAGENTA = &H80FF00FF      'RGB( 255,   0, 255)
Public Const VL_COL_YELLOW = &H8000FFFF       'RGB( 255, 255,   0)
Public Const VL_COL_DARKRED = &H8000008B      'RGB( 139,   0,   0)
Public Const VL_COL_DARKGREEN = &H80006400    'RGB(   0, 100,   0)
Public Const VL_COL_DARKBLUE = &H808B0000     'RGB(   0,   0, 139)
Public Const VL_COL_DARKCYAN = &H808B8B00     'RGB(   0, 139, 139)
Public Const VL_COL_DARKMAGENTA = &H808B008B  'RGB( 139,   0, 139)
Public Const VL_COL_BROWN = &H802A2AA5        'RGB( 165,  42,  42)

'Public Const VL_COL_BLACK = 0
'Public Const VL_COL_LTRED = 255
'Public Const VL_COL_LTGREEN = 65280
'Public Const VL_COL_LTBLUE = 16711680
'Public Const VL_COL_LTCYAN = 16776960
'Public Const VL_COL_LTMAGENTA = 16711935
'Public Const VL_COL_YELLOW = 65535
'Public Const VL_COL_RED = 128
'Public Const VL_COL_GREEN = 32768 '&H8000
'Public Const VL_COL_BLUE = 8388608  '&H800000
'Public Const VL_COL_CYAN = 8421376  '&H808000
'Public Const VL_COL_MAGENTA = 8388736  '&H800080
'Public Const VL_COL_BROWN = 32896
'Public Const VL_COL_DARKGRAY = &H404040
'Public Const VL_COL_GRAY = &H808080
'Public Const VL_COL_LTGRAY = &HC0C0C0
'Public Const VL_COL_WHITE = &HFFFFFF


' page paper size
Public Const VL_PAPER_UNLIMITED = 0
Public Const VL_PAPER_A0 = 1
Public Const VL_PAPER_A1 = 2
Public Const VL_PAPER_A2 = 3
Public Const VL_PAPER_A3 = 4
Public Const VL_PAPER_A4 = 5
Public Const VL_PAPER_A5 = 6
Public Const VL_PAPER_A6 = 7
Public Const VL_PAPER_B0 = 11
Public Const VL_PAPER_B1 = 12
Public Const VL_PAPER_B2 = 13
Public Const VL_PAPER_B3 = 14
Public Const VL_PAPER_B4 = 15
Public Const VL_PAPER_B5 = 16
Public Const VL_PAPER_B6 = 17
Public Const VL_PAPER_C0 = 21
Public Const VL_PAPER_C1 = 22
Public Const VL_PAPER_C2 = 23
Public Const VL_PAPER_C3 = 24
Public Const VL_PAPER_C4 = 25
Public Const VL_PAPER_C5 = 26
Public Const VL_PAPER_C6 = 27
Public Const VL_PAPER_ANSI_A = 31
Public Const VL_PAPER_ANSI_B = 32
Public Const VL_PAPER_ANSI_C = 33
Public Const VL_PAPER_ANSI_D = 34
Public Const VL_PAPER_ANSI_E = 35
Public Const VL_PAPER_LETTER = 36
Public Const VL_PAPER_LEGAL = 37
Public Const VL_PAPER_EXECUTIVE = 38
Public Const VL_PAPER_LEDGER = 39
Public Const VL_PAPER_USER = 255

' paper orientation
Public Const VL_PAPER_PORTRAIT = 1
Public Const VL_PAPER_LANDSCAPE = 2
Public Const VL_PAPER_BOOK = 1
Public Const VL_PAPER_ALBUM = 2

' Modes of Page select
Public Const VL_PAGE_POS = 0          ' go to the page index
Public Const VL_PAGE_NEXT = 1         ' view next page
Public Const VL_PAGE_PREV = 2         ' view previous page
Public Const VL_PAGE_FIRST = 3        ' go to the first page
Public Const VL_PAGE_LAST = 4         ' go to the last page
Public Const VL_PAGE_NAME = 5         ' go to page by name
Public Const VL_PAGE_DLG = 6          ' select page by dialog

' modes for vlSetTextParam
Public Const VL_TEXT_ALIGN = 1
Public Const VL_TEXT_HEIGHT = 2
Public Const VL_TEXT_ANGLE = 3
Public Const VL_TEXT_WSCALE = 4
Public Const VL_TEXT_OBLIQUE = 5
Public Const VL_TEXT_HINTER = 6
Public Const VL_TEXT_VINTER = 7
Public Const VL_TEXT_STRIKEOUT = 8
Public Const VL_TEXT_UNDERLINE = 9

' text alignment types
Public Const VL_TA_LEFBOT = 0       ' to left bottom
Public Const VL_TA_CENBOT = 1       ' to center bottom
Public Const VL_TA_RIGBOT = 2       ' to right bottom
Public Const VL_TA_LEFCEN = 3       ' слева середина
Public Const VL_TA_CENCEN = 4       ' по центру базовой линии
Public Const VL_TA_RIGCEN = 5       ' по правому краю середина
Public Const VL_TA_LEFTOP = 6       ' по левому краю сверху
Public Const VL_TA_CENTOP = 7       ' по центру базовой линии сверху
Public Const VL_TA_RIGTOP = 8       ' по правому краю сверху

' measurement units
Public Const VL_UNIT_POINT = 1
Public Const VL_UNIT_MM = 2
Public Const VL_UNIT_CM = 3
Public Const VL_UNIT_INCH = 4
Public Const VL_UNIT_FOOT = 5
Public Const VL_UNIT_YARD = 6
Public Const VL_UNIT_MET = 7
Public Const VL_UNIT_KM = 8
Public Const VL_UNIT_MILE = 9
Public Const VL_UNIT_SEAMILE = 10
Public Const VL_ANG_DEGREE = 21
Public Const VL_ANG_RADIAN = 22

' view types for simple point (vlDrawPoint)
Public Const VL_PNT_DEFAULT = 0
Public Const VL_PNT_CIRCLE = 1
Public Const VL_PNT_RECT = 2
Public Const VL_PNT_GRIP = 2
Public Const VL_PNT_CROSS = 3
Public Const VL_PNT_CROSS45 = 4
Public Const VL_PNT_POINT = 5
Public Const VL_PNT_BPIXEL = 6
Public Const VL_PNT_WPIXEL = 7
Public Const VL_PNT_ROMB = 8
Public Const VL_PNT_GRIPM = 10
Public Const VL_PNT_GRIPR = 11
Public Const VL_PNT_KNOT = 12
Public Const VL_PNT_KNOT2 = 13

' Arrow types
Public Const VL_ARROW_NONE = 0
Public Const VL_ARROW_2LINE = 1
Public Const VL_ARROW_3LINE = 2
Public Const VL_ARROW_3LINE_S = 3
Public Const VL_ARROW_4LINE = 4
Public Const VL_ARROW_4LINE_S = 5
Public Const VL_ARROW_SLASH = 6
Public Const VL_ARROW_CIRC = 7
Public Const VL_ARROW_CIRC_S = 8
Public Const VL_ARROW_COUNT = 9          ' count of arrows types

' Polyline flags
Public Const VL_POLY_LINE = 0        ' linear polyline (no smooth)
Public Const VL_POLY_BSPLINE2 = 1    ' quadratic B-spline
Public Const VL_POLY_BSPLINE3 = 2    ' cubic B-spline
Public Const VL_POLY_FITBSPL3 = 3    ' fitted cubic B-spline
Public Const VL_POLY_LINBSPL2 = 4    ' linear/quadratic curve
Public Const VL_POLY_BEZIER = 5      ' bezier curve
Public Const VL_POLY_AUTOBEZIER = 6  ' bezier curve with auto control points
Public Const VL_POLY_ROUNDED = 7     ' rounded vertexes
Public Const VL_POLY_MULTIRAD = 8    ' multi-rad curve
Public Const VL_POLY_BULGE = 9       ' bulge segments
Public Const VL_POLY_MAXSMTYPE = 9   ' max value for smooth type
Public Const VL_POLY_CUSTOM = 128       ' custom draw

' type of dimension
Public Const VL_DIM_HORZ = 0        ' horizontal
Public Const VL_DIM_VERT = 1        ' vertical
Public Const VL_DIM_PARAL = 2       ' parallel
Public Const VL_DIM_ANG = 3         ' Angular
Public Const VL_DIM_RAD = 4         ' Radius
Public Const VL_DIM_DIAM = 5        ' Diameter
Public Const VL_DIM_ORDX = 6        ' Ordinate X
Public Const VL_DIM_ORDY = 7        ' Ordinate Y
' dim. text alignment
Public Const VL_DIM_TA_ABOVE = 0
Public Const VL_DIM_TA_CENTER = 1
Public Const VL_DIM_TA_BELOW = 2

' Coord. Grid types
Public Const VL_GRID_POINT = 0       ' point
Public Const VL_GRID_CROSS = 1       ' cross
Public Const VL_GRID_CROSS45 = 2     ' cross 45 degree
Public Const VL_GRID_LINE = 3        ' solid line
Public Const VL_GRID_DOTLINE = 4     ' dot line
Public Const VL_GRID_DASHLINE = 5    ' dash line

' flags for accelerator keys (vlSetAccKey)
Public Const VL_KEY_CTRL = 1
Public Const VL_KEY_SHIFT = 2

' Object Snap flags
Public Const VL_SNAP_END = 1
Public Const VL_SNAP_MID = 2
Public Const VL_SNAP_CENTER = 4
Public Const VL_SNAP_POINT = 8
Public Const VL_SNAP_INTER = 16
Public Const VL_SNAP_NEAR = 32
Public Const VL_SNAP_GRIPS = 64
Public Const VL_SNAP_PERP = 256
Public Const VL_SNAP_TANG = 512
Public Const VL_SNAP_GRID = 4096
Public Const VL_SNAP_POLAR = 8192
Public Const VL_SNAP_OBJECT = 4095
Public Const VL_SNAP_REALTIME = 32768

' Toolbars type (vlToolBarCreate)
Public Const VL_TB_MAIN = 4861
Public Const VL_TB_DRAW = 4862
Public Const VL_TB_EDIT = 4863
Public Const VL_TB_SNAP = 4864

' ComboBox type (for toolbar)
Public Const VL_CB_LAYER = 4871
Public Const VL_CB_STLINE = 4872
Public Const VL_CB_STTEXT = 4873
Public Const VL_CB_COLOR = 4874

' index of statusbar part (vlStatBarSetText)
Public Const VL_SB_COORD = 0
Public Const VL_SB_CURCMD = 1
Public Const VL_SB_PROMPT = 2

' separator types
' used as value for VD_SDECIMAL property
Public Const VL_SEP_POINT = 0
Public Const VL_SEP_COMMA = 1

' constants for "glass piece" object
Public Const VL_GLASS_DWG_PROP = 0
Public Const VL_GLASS_DWG_STRETCH = 16
Public Const VL_GLASS_DWG_ORIG = 32
Public Const VL_GLASS_DWG_SIZE = 48

' Styles of "Navigator" window
Public Const VL_NAV_CHILD = 0
Public Const VL_NAV_FLOAT = 1

' Styles of "Layers manager" window
Public Const VL_LAYWIN_CHILD = 0
Public Const VL_LAYWIN_FLOAT = 1


'///////////////////////////////////////////////
'// VeCAD messages, passed to drawing procedure
Public Const VM_GETSTRING = 1
Public Const VM_ERROR = 2
Public Const VM_ZOOM = 3
Public Const VM_ZOOMMIN = 4
Public Const VM_ZOOMMAX = 5
Public Const VM_BEGINPAINT = 6
Public Const VM_ENDPAINT = 7
Public Const VM_LBPAINT = 8
Public Const VM_OBJADD = 11
Public Const VM_OBJDELETE = 12
Public Const VM_OBJACTIVE = 13
Public Const VM_ENTADD = 14
Public Const VM_ENTDELETE = 15
Public Const VM_ENTSELECT = 16
Public Const VM_ENTUNSELECT = 17
Public Const VM_ENTCOPY = 20
Public Const VM_ENTMOVE = 21
Public Const VM_ENTROTATE = 22
Public Const VM_ENTSCALE = 23
Public Const VM_ENTMIRROR = 24
Public Const VM_ENTERASE = 25
Public Const VM_ENTEXPLODE = 26
Public Const VM_ENTPROPDLG = 27
Public Const VM_ENTINDEX = 28
Public Const VM_KEYDOWN = 41
Public Const VM_MOUSEMOVE = 42
Public Const VM_LBDOWN = 43
Public Const VM_LBDBLCLK = 44
Public Const VM_RBDOWN = 45
Public Const VM_KEYUP = 46
Public Const VM_LBUP = 47
Public Const VM_RBUP = 48
Public Const VM_MBDOWN = 49
Public Const VM_MBUP = 50
Public Const VM_TOOLCREATE = 51
Public Const VM_CMD_CREATE = 51
Public Const VM_TOOLOPEN = 52
Public Const VM_CMD_OPEN = 52
Public Const VM_TOOLCLOSE = 53
Public Const VM_CMD_CLOSE = 53
Public Const VM_TOOLCLICK = 54
Public Const VM_CMD_CLICK = 54
Public Const VM_TOOLDRAG = 55
Public Const VM_CMD_DRAG = 55
Public Const VM_TOOLREDRAW = 56
Public Const VM_CMD_REDRAW = 56
Public Const VM_CANCELTOOL = 57
Public Const VM_CANCELCMD = 57
Public Const VM_REPEATTOOL = 58
Public Const VM_REPEATCMD = 58
Public Const VM_MENUEDIT = 61
Public Const VM_MENUVER = 62
Public Const VM_EXECUTE = 100
Public Const VM_EXECUTED = 101
Public Const VM_DWGCREATE = 102
Public Const VM_DWGDELETE = 103
Public Const VM_DWGCLEAR = 104
Public Const VM_DWGSELECT = 105
Public Const VM_DWGLOADING = 106
Public Const VM_DWGLOADED = 107
Public Const VM_DWGSAVING = 108
Public Const VM_DWGSAVED = 109
Public Const VM_DWGUPDATE = 110
Public Const VM_PASSWORD = 121
Public Const VM_TIMER = 122
Public Const VM_RASTER = 123
Public Const VM_CLOSEQUERY = 124
Public Const VM_WINRESIZE = 125
Public Const VM_WDWG_CLOSED = 126
Public Const VM_WVIEW_CLOSED = 127
Public Const VM_GRIPSELECT = 161
Public Const VM_GRIPDRAG = 162
Public Const VM_GRIPMOVE = 163
Public Const VM_STATUSTEXT = 171

Public Const VM_EXP___MIN = 180
Public Const VM_EXP_BEGIN = 181
Public Const VM_EXP_END = 182
Public Const VM_EXP_ENTITY = 183
Public Const VM_EXP_MOVETO = 184
Public Const VM_EXP_LINETO = 185
Public Const VM_EXP_ARCTO = 186
Public Const VM_EXP_DROP = 187
Public Const VM_EXP_DROPSIZE = 188
Public Const VM_EXP_COLOR = 189
Public Const VM_EXP_WIDTH = 190
Public Const VM_EXP_LAYER = 191
Public Const VM_EXP_PUMPOFF = 192
Public Const VM_EXP_EXPLODE = 193
Public Const VM_EXP_LINES = 195
Public Const VM_EXP_FILLINGS = 196
Public Const VM_EXP___MAX = 200

Public Const VM_EXP_OPEN = 181
Public Const VM_EXP_CLOSE = 182
Public Const VM_EXP_ENT = 183

Public Const VM_PROP_PRE = 251
Public Const VM_PROP_POST = 252

Public Const VM_NAV_CLOSE = 261
Public Const VM_NAV_DIALOG = 262

Public Const VM_MOUSEWHEEL = 271


'////////////////////////////////////////////////
'// VeCAD error codes, passed with the VM_ERROR message
Public Const VL_ERR_OBJADD = 1
Public Const VL_ERR_OBJDELETE = 2
Public Const VL_ERR_OBJSELECT = 4
Public Const VL_ERR_LOADVEC = 5



'********************************************************************
'* VeCAD commands (vlExecute)
'********************************************************************

' File
Public Const VC_FILE_NEW = 17001
Public Const VC_FILE_OPEN = 17002
Public Const VC_FILE_SAVE = 17003
Public Const VC_FILE_SAVEAS = 17004
Public Const VC_FILE_CLOSE = 17005
Public Const VC_FILE_CLOSEALL = 17006
Public Const VC_FILE_LIST = 17007
Public Const VC_IMPORT_DXF = 17011
Public Const VC_IMPORT_VDF = 17012
Public Const VC_IMPORT_HPGL = 17013
Public Const VC_IMPORT_CNC = 17014
Public Const VC_IMPORT_AVSHP = 17016
Public Const VC_EXPORT_DXF = 17021
Public Const VC_EXPORT_HPGL = 17022
Public Const VC_EXPORT_CNC = 17023
Public Const VC_EXPORT_BMP = 17024
Public Const VC_EXPORT_AVSHP = 17025
Public Const VC_PRINT = 17031

' View
Public Const VC_ZOOM_ALL = 17051
Public Const VC_ZOOM_WIN = 17052
Public Const VC_ZOOM_PAN = 17053
Public Const VC_ZOOM_PAGE = 17054
Public Const VC_ZOOM_IN = 17055
Public Const VC_ZOOM_OUT = 17056
Public Const VC_ZOOM_LEFT = 17057
Public Const VC_ZOOM_RIGHT = 17058
Public Const VC_ZOOM_UP = 17059
Public Const VC_ZOOM_DOWN = 17060
Public Const VC_ZOOM_PREV = 17061
Public Const VC_ZOOM_SEL = 17062
Public Const VC_PAGE_NEXT = 17071
Public Const VC_PAGE_PREV = 17072
Public Const VC_PAGE_FIRST = 17073
Public Const VC_PAGE_LAST = 17074
Public Const VC_PAGE_DLG = 17075
Public Const VC_VIEW_SAVE = 17081
Public Const VC_VIEW_LIST = 17082

' Draw
Public Const VC_DRAW_POINT = 17110
Public Const VC_DRAW_LINE = 17120
Public Const VC_DRAW_POLYLINE = 17130
Public Const VC_DRAW_SPLINE = 17131
Public Const VC_DRAW_CIRC_CR = 17140
Public Const VC_DRAW_CIRC_CD = 17141
Public Const VC_DRAW_CIRC_2P = 17142
Public Const VC_DRAW_CIRC_3P = 17143
Public Const VC_DRAW_CIRC_TTT = 17144
Public Const VC_DRAW_ARC_CSE = 17150
Public Const VC_DRAW_ARC_CSA = 17151
Public Const VC_DRAW_ARC_CSL = 17152
Public Const VC_DRAW_ARC_SEM = 17153
Public Const VC_DRAW_ARC_SME = 17154
Public Const VC_DRAW_ARC_SCE = 17155
Public Const VC_DRAW_ARC_SCA = 17156
Public Const VC_DRAW_ARC_SCL = 17157
Public Const VC_DRAW_ARC_SEA = 17158
Public Const VC_DRAW_ARC_SED = 17159
Public Const VC_DRAW_ARC_SER = 17160
Public Const VC_DRAW_ARC_CONT = 17161
Public Const VC_DRAW_SECTOR = 17165
Public Const VC_DRAW_ELLIPSE = 17170
Public Const VC_DRAW_RECT = 17180
Public Const VC_DRAW_DIM_HOR = 17230
Public Const VC_DRAW_DIM_VER = 17231
Public Const VC_DRAW_DIM_PAR = 17232
Public Const VC_DRAW_DIM_ANG = 17233
Public Const VC_DRAW_DIM_RAD = 17234
Public Const VC_DRAW_DIM_DIAM = 17235
Public Const VC_DRAW_DIM_ORD = 17236
Public Const VC_DRAW_HATCH = 17240
Public Const VC_INS_TEXT = 17250
Public Const VC_INS_SYMBOL = 17260
Public Const VC_INS_BLOCK = 17280
Public Const VC_INS_IMAGE = 17290
Public Const VC_INS_RMAP = 17300
Public Const VC_INS_GLASS = 17301
Public Const VC_INS_DRAWING = 17302
Public Const VC_INS_AVSHP = 17303
Public Const VC_INS_FLOOD = 17304

' Edit
Public Const VC_EDIT_ENTPROP = 17401
Public Const VC_EDIT_COPY = 17402
Public Const VC_EDIT_MOVE = 17403
Public Const VC_EDIT_ROTATE = 17404
Public Const VC_EDIT_SCALE = 17405
Public Const VC_EDIT_MIRROR = 17406
Public Const VC_EDIT_ERASE = 17407
Public Const VC_EDIT_EXPLODE = 17408
Public Const VC_EDIT_CREBLOCK = 17409
Public Const VC_EDIT_EXTEND = 17410
Public Const VC_EDIT_TRIM = 17411
Public Const VC_EDIT_FILLET = 17412
Public Const VC_EDIT_ARRAY = 17413
Public Const VC_EDIT_JOIN = 17414
Public Const VC_EDIT_UNDO = 17431
Public Const VC_EDIT_REDO = 17432
Public Const VC_EDIT_CBCUT = 17441
Public Const VC_EDIT_CBCOPY = 17442
Public Const VC_EDIT_CBPASTE = 17443

' Format
Public Const VC_FMT_LAYOUT = 17451
Public Const VC_FMT_PAGE = 17452
Public Const VC_FMT_LAYER = 17453
Public Const VC_FMT_STLINE = 17454
Public Const VC_FMT_STTEXT = 17455
Public Const VC_FMT_STDIM = 17456
Public Const VC_FMT_STPOINT = 17457
Public Const VC_FMT_STHATCH = 17458
Public Const VC_FMT_BLOCK = 17459
Public Const VC_FMT_GRID = 17461
Public Const VC_FMT_OSNAP = 17462
Public Const VC_FMT_PSNAP = 17463
Public Const VC_FMT_UNITS = 17464
Public Const VC_FMT_PRIVATE = 17465
Public Const VC_FMT_PREFERS = 17466
Public Const VC_FMT_MLINE = 17467

' Snap
Public Const VC_SNAP_DLG = 17501
Public Const VC_SNAP_CLEAR = 17502
Public Const VC_SNAP_GRID = 17503
Public Const VC_SNAP_POLAR = 17504
Public Const VC_SNAP_KNOT = 17511
Public Const VC_SNAP_GRIP = 17511
Public Const VC_SNAP_GRIPS = 17511
Public Const VC_SNAP_POINT = 17512
Public Const VC_SNAP_NEAR = 17513
Public Const VC_SNAP_END = 17514
Public Const VC_SNAP_MID = 17515
Public Const VC_SNAP_INTER = 17516
Public Const VC_SNAP_CEN = 17517
Public Const VC_SNAP_PERP = 17518
Public Const VC_SNAP_TANG = 17519
Public Const VC_SNAP_REALTIME = 17520

' Tools
Public Const VC_TOOL_DIST = 18501
Public Const VC_TOOL_PRNRECT = 18502
Public Const VC_TOOL_STAT = 18503
Public Const VC_TOOL_NAVIGATOR = 18504
Public Const VC_TOOL_LAYERS = 18505
Public Const VC_ENT_SWAP = 18511
Public Const VC_ENT_TOTOP = 18512
Public Const VC_ENT_TOBOTTOM = 18513
Public Const VC_SEL_BYPOINT = 18531
Public Const VC_SEL_BYRECT = 18532
Public Const VC_SEL_BYPOLYGON = 18533
Public Const VC_SEL_BYPOLYLINE = 18534
Public Const VC_SEL_BYDIST = 18535
Public Const VC_SEL_BYHANDLE = 18536
Public Const VC_SEL_BYKEY = 18537
Public Const VC_SEL_BYLAYER = 18538

' Misc
Public Const VC_RESET = 18171
Public Const VC_REDRAW = 18172
Public Const VC_SHOWLINEW = 18173
Public Const VC_SHOWGRID = 18174
Public Const VC_SHOWFILL = 18175

' Offset for custom commands that use cursor
Public Const VC_CUSTOM = 20000


'********************************************************************
'* VeCAD data access keys (vlData... functions)
'********************************************************************

Public Const VD_WND___MIN = 30001
Public Const VD_WND_EMPTYTEXT = 30001
Public Const VD_WND_CURSOR_X = 30002
Public Const VD_WND_CURSOR_Y = 30003
Public Const VD_WND_CURSOR_CROSS = 30004
Public Const VD_WND___MAX = 30010

Public Const VD_PRJ___MIN = 30011
Public Const VD_PRJ_WDWG_ON = 30011
Public Const VD_PRJ_WDWG_LEFT = 30012
Public Const VD_PRJ_WDWG_TOP = 30013
Public Const VD_PRJ_WDWG_RIGHT = 30014
Public Const VD_PRJ_WDWG_BOTTOM = 30015
Public Const VD_PRJ_WVIEW_ON = 30016
Public Const VD_PRJ_WVIEW_LEFT = 30017
Public Const VD_PRJ_WVIEW_TOP = 30018
Public Const VD_PRJ_WVIEW_RIGHT = 30019
Public Const VD_PRJ_WVIEW_BOTTOM = 30020
Public Const VD_PRJ_WDIST_LEFT = 30021
Public Const VD_PRJ_WDIST_TOP = 30022
Public Const VD_PRJ___MAX = 30099

Public Const VD_PRN___MIN = 30131
Public Const VD_PRN_NAME = 30131
Public Const VD_PRN_DRIVER = 30132
Public Const VD_PRN_PORT = 30133
Public Const VD_PRN_USEDOC = 30134
Public Const VD_PRN___MAX = 30150

Public Const VD_MSG_STRING = 30155
Public Const VD_MSG_DBL1 = 30156
Public Const VD_MSG_DBL2 = 30157
Public Const VD_SDECIMAL = 30161
Public Const VD_KEYCTRL = 30162
Public Const VD_KEYSHIFT = 30163

Public Const VD_DWG___MIN = 1
Public Const VD_DWG_ID = 1
Public Const VD_DWG_INDEX = 2
Public Const VD_DWG_FILENAME = 3
Public Const VD_DWG_PATHNAME = 4
Public Const VD_DWG_TITLE = 5
Public Const VD_DWG_LEFT = 6
Public Const VD_DWG_RIGHT = 7
Public Const VD_DWG_TOP = 8
Public Const VD_DWG_BOTTOM = 9
Public Const VD_DWG_WIDTH = 10
Public Const VD_DWG_HEIGHT = 11
Public Const VD_DWG_WINLEFT = 12
Public Const VD_DWG_WINRIGHT = 13
Public Const VD_DWG_WINTOP = 14
Public Const VD_DWG_WINBOTTOM = 15
Public Const VD_DWG_WINWIDTH = 16
Public Const VD_DWG_WINHEIGHT = 17
Public Const VD_DWG_WINSCALE = 18
Public Const VD_DWG_WINSCALEY = 19
Public Const VD_DWG_ZOOMVAL = 20
Public Const VD_DWG_ZOOMHORZ = 21
Public Const VD_DWG_ZOOMVERT = 22
Public Const VD_DWG_ZOOMMIN = 23
Public Const VD_DWG_ZOOMMAX = 24
Public Const VD_DWG_SCROLLERS = 25
Public Const VD_DWG_READONLY = 26
Public Const VD_DWG_BLACKWHITE = 27
Public Const VD_DWG_COLBKG = 31
Public Const VD_DWG_COLPAGE = 32
Public Const VD_DWG_COLPAGESHADOW = 33
Public Const VD_DWG_COLCURSOR = 34
Public Const VD_DWG_COLGRIP = 35
Public Const VD_DWG_COLSELOBJ = 36
Public Const VD_DWG_COLSELGRIP = 37
Public Const VD_DWG_COLOR = 38
Public Const VD_DWG_SHOWAPER = 41
Public Const VD_DWG_SHOWCROSS = 42
Public Const VD_DWG_SHOWFILL = 43
Public Const VD_DWG_SHOWVEC = 44
Public Const VD_DWG_SHOWBMP = 45
Public Const VD_DWG_SHOWLINEW = 46
Public Const VD_DWG_SHOWRMARK = 47
Public Const VD_DWG_SHOWGRID = 48
Public Const VD_DWG_AUTOSELPNT = 61
Public Const VD_DWG_AUTOSELRECT = 62
Public Const VD_DWG_AUTOUNSELECT = 63
Public Const VD_DWG_USEGRIPS = 71
Public Const VD_DWG_LOCK = 72
Public Const VD_DWG_PASSWORD = 73
Public Const VD_DWG_OWNER = 74
Public Const VD_DWG_NOEXPORT = 75
Public Const VD_DWG_NOPRINT = 76
Public Const VD_DWG_PICKBOXSIZE = 82
Public Const VD_DWG_GRIPSIZE = 83
Public Const VD_DWG_DEFLINEW = 84
Public Const VD_DWG_ISDIRTY = 85
Public Const VD_DWG_EXDATASIZE = 86
Public Const VD_DWG_EXDATA = 87
Public Const VD_DWG_CROSSSIZE = 88
Public Const VD_DWG_TRACK_EXPORT = 89
Public Const VD_DWG_SNAP = 91
Public Const VD_DWG_SNAPSIZE = 92
Public Const VD_DWG_PSNAPDIST = 93
Public Const VD_DWG_PSNAPANGLE0 = 94
Public Const VD_DWG_PSNAPANGLE = 95
Public Const VD_DWG_N_PAGES = 101
Public Const VD_DWG_C_PAGE = 102
Public Const VD_DWG_N_LAYERS = 103
Public Const VD_DWG_C_LAYER = 104
Public Const VD_DWG_N_STLINES = 105
Public Const VD_DWG_C_STLINE = 106
Public Const VD_DWG_N_STTEXTS = 107
Public Const VD_DWG_C_STTEXT = 108
Public Const VD_DWG_N_STHATCHS = 109
Public Const VD_DWG_C_STHATCH = 110
Public Const VD_DWG_N_VIEWS = 111
Public Const VD_DWG_C_VIEW = 112
Public Const VD_DWG_N_PRNRECTS = 113
Public Const VD_DWG_C_PRNRECT = 114
Public Const VD_DWG_N_STDIMS = 115
Public Const VD_DWG_C_STDIM = 116
Public Const VD_DWG_N_STPOINTS = 117
Public Const VD_DWG_C_STPOINT = 118
Public Const VD_DWG_N_GRPOINTS = 119
Public Const VD_DWG_C_GRPOINT = 120
Public Const VD_DWG_N_BLOCKS = 121
Public Const VD_DWG_C_BLOCK = 122
Public Const VD_DWG_N_ENTITIES = 123
Public Const VD_DWG_N_ENT = 123
Public Const VD_DWG_N_ENTSEL = 124
Public Const VD_DWG_C_LEVEL = 125
Public Const VD_DWG_BITMAP = 126
Public Const VD_DWG_SELECTINSIDE = 127
Public Const VD_DWG_FLATENDS = 128
Public Const VD_DWG_SEGCURVE = 129
Public Const VD_DWG_CHARFRAME = 130
Public Const VD_DWG_SELACTLAYER = 131
Public Const VD_DWG_SORTLAYERS = 132
Public Const VD_DWG_PROPMESSAGES = 133
Public Const VD_DWG_EXTOBJECT = 134
Public Const VD_DWG_HWND = 135
Public Const VD_DWG_INSBLOCKDLG = 136
Public Const VD_DWG_NOINDICATOR = 137

Public Const VD_GRID_X0 = 141
Public Const VD_GRID_Y0 = 142
Public Const VD_GRID_DX = 143
Public Const VD_GRID_DY = 144
Public Const VD_GRID_TYPE = 145
Public Const VD_GRID_COLOR = 146
Public Const VD_GRID_BSTEPX = 147
Public Const VD_GRID_BSTEPY = 148
Public Const VD_GRID_BTYPE = 149
Public Const VD_GRID_BCOLOR = 150
Public Const VD_UNITS_LIN = 161
Public Const VD_UNITS_ANG = 162
Public Const VD_UNITS_SCALE = 163
Public Const VD_UNITS_PAGELEFT = 164
Public Const VD_UNITS_PAGEBOTTOM = 165
Public Const VD_UNITS_GEO = 166
Public Const VD_UNITS_FORMAT = 167
Public Const VD_HPGL_X0 = 171
Public Const VD_HPGL_Y0 = 172
Public Const VD_HPGL_UNITX = 173
Public Const VD_HPGL_UNITY = 174
Public Const VD_HPGL_MINSTEP = 175
Public Const VD_HPGL_OFFDIST = 176
Public Const VD_EXP_X0 = 171
Public Const VD_EXP_Y0 = 172
Public Const VD_EXP_UNITX = 173
Public Const VD_EXP_UNITY = 174
Public Const VD_EXP_MINSTEP = 175
Public Const VD_EXP_OFFDIST = 176
Public Const VD_EXP_USEARCS = 177
Public Const VD_EXP_DROPSIZE = 178
Public Const VD_EXP_DROPSIZEMIN = 179
Public Const VD_DWG___MAX = 200

Public Const VD_PAGE___MIN = 201
Public Const VD_PAGE_NAME = 201
Public Const VD_PAGE_SIZE = 202
Public Const VD_PAGE_ORIENT = 203
Public Const VD_PAGE_WIDTH = 204
Public Const VD_PAGE_HEIGHT = 205
Public Const VD_PAGE_N_REF = 208
Public Const VD_PAGE_ID = 209
Public Const VD_PAGE_INDEX = 210
Public Const VD_PAGE_EXTOBJECT = 211
Public Const VD_PAGE___MAX = 299

Public Const VD_LAYER___MIN = 301
Public Const VD_LAYER_NAME = 301
Public Const VD_LAYER_COLOR = 302
Public Const VD_LAYER_FILLCOLOR = 303
Public Const VD_LAYER_LINEWIDTH = 304
Public Const VD_LAYER_VISIBLE = 305
Public Const VD_LAYER_LOCK = 306
Public Const VD_LAYER_SELINSIDE = 307
Public Const VD_LAYER_NOPRINT = 308
Public Const VD_LAYER_N_REF = 309
Public Const VD_LAYER_ID = 310
Public Const VD_LAYER_INDEX = 311
Public Const VD_LAYER_ENTSELECT = 312
Public Const VD_LAYER_SELENT = 312
Public Const VD_LAYER_LEVEL = 313
Public Const VD_LAYER_EXTOBJECT = 314
Public Const VD_LAYER___MAX = 399

Public Const VD_STTEXT___MIN = 401
Public Const VD_STTEXT_NAME = 401
Public Const VD_STTEXT_FONTNAME = 402
Public Const VD_STTEXT_WEIGHT = 403
Public Const VD_STTEXT_ITALIC = 404
Public Const VD_STTEXT_WIDTH = 405
Public Const VD_STTEXT_OBLIQUE = 406
Public Const VD_STTEXT_PRECISION = 407
Public Const VD_STTEXT_FILLED = 408
Public Const VD_STTEXT_N_REF = 409
Public Const VD_STTEXT_ID = 410
Public Const VD_STTEXT_INDEX = 411
Public Const VD_STTEXT_BYLINES = 412
Public Const VD_STTEXT_EXTOBJECT = 413
Public Const VD_STTEXT___MAX = 499

Public Const VD_STLINE___MIN = 501
Public Const VD_STLINE_NAME = 501
Public Const VD_STLINE_DESC = 502
Public Const VD_STLINE_DESCLEN = 503
Public Const VD_STLINE_N_REF = 504
Public Const VD_STLINE_ID = 505
Public Const VD_STLINE_INDEX = 506
Public Const VD_STLINE_EXTOBJECT = 507
Public Const VD_STLINE___MAX = 599

Public Const VD_STDIM___MIN = 601
Public Const VD_STDIM_NAME = 601
Public Const VD_STDIM_ARR_TYPE = 602
Public Const VD_STDIM_ARR_LENGTH = 603
Public Const VD_STDIM_ARR_HEIGHT = 604
Public Const VD_STDIM_EXT_OFFSET = 605
Public Const VD_STDIM_EXT_EXTEND = 606
Public Const VD_STDIM_TEXT_CONTENT = 607
Public Const VD_STDIM_TEXT_STYLE = 608
Public Const VD_STDIM_TEXT_ALIGN = 609
Public Const VD_STDIM_TEXT_HEIGHT = 610
Public Const VD_STDIM_TEXT_DEC = 611
Public Const VD_STDIM_TEXT_HORIZ = 612
Public Const VD_STDIM_TEXT_GAP = 613
Public Const VD_STDIM_SCALE = 614
Public Const VD_STDIM_OWNCOLORS = 615
Public Const VD_STDIM_COL_DIM = 616
Public Const VD_STDIM_COL_EXT = 617
Public Const VD_STDIM_COL_TEXT = 618
Public Const VD_STDIM_CEN_TYPE = 619
Public Const VD_STDIM_CEN_SIZE = 620
Public Const VD_STDIM_ROUND = 621
Public Const VD_STDIM_N_REF = 622
Public Const VD_STDIM_ID = 623
Public Const VD_STDIM_INDEX = 624
Public Const VD_STDIM_EXTOBJECT = 625
Public Const VD_STDIM___MAX = 699

Public Const VD_STHATCH___MIN = 701
Public Const VD_STHATCH_NAME = 701
Public Const VD_STHATCH_DESC = 702
Public Const VD_STHATCH_DESCLEN = 703
Public Const VD_STHATCH_N_REF = 704
Public Const VD_STHATCH_ID = 705
Public Const VD_STHATCH_INDEX = 706
Public Const VD_STHATCH_EXTOBJECT = 707
Public Const VD_STHATCH___MAX = 799

Public Const VD_STPOINT___MIN = 801
Public Const VD_STPOINT_NAME = 801
Public Const VD_STPOINT_STATUS = 802
Public Const VD_STPOINT_BLOCK = 803
Public Const VD_STPOINT_LAYER = 804
Public Const VD_STPOINT_STTEXT = 805
Public Const VD_STPOINT_BSCALE = 806
Public Const VD_STPOINT_TEXTH = 807
Public Const VD_STPOINT_TEXTW = 808
Public Const VD_STPOINT_SNAP = 809
Public Const VD_STPOINT_FIXED = 810
Public Const VD_STPOINT_N_REF = 811
Public Const VD_STPOINT_ID = 812
Public Const VD_STPOINT_INDEX = 813
Public Const VD_STPOINT_EXTOBJECT = 814
Public Const VD_STPOINT___MAX = 859

Public Const VD_GRPOINT___MIN = 861
Public Const VD_GRPOINT_NAME = 861
Public Const VD_GRPOINT_N_REF = 862
Public Const VD_GRPOINT_ID = 863
Public Const VD_GRPOINT_INDEX = 864
Public Const VD_GRPOINT_EXTOBJECT = 865
Public Const VD_GRPOINT___MAX = 899

Public Const VD_BLOCK___MIN = 901
Public Const VD_BLOCK_NAME = 901
Public Const VD_BLOCK_WIDTH = 902
Public Const VD_BLOCK_HEIGHT = 903
Public Const VD_BLOCK_XBASE = 904
Public Const VD_BLOCK_YBASE = 905
Public Const VD_BLOCK_N_REF = 906
Public Const VD_BLOCK_ID = 907
Public Const VD_BLOCK_INDEX = 908
Public Const VD_BLOCK_EXTOBJECT = 909
Public Const VD_BLOCK_N_ENT = 910
Public Const VD_BLOCK___MAX = 999

Public Const VD_PRNRECT___MIN = 1001
Public Const VD_PRNRECT_INDEX = 1001
Public Const VD_PRNRECT_NAME = 1002
Public Const VD_PRNRECT_XCEN = 1003
Public Const VD_PRNRECT_YCEN = 1004
Public Const VD_PRNRECT_WIDTH = 1005
Public Const VD_PRNRECT_HEIGHT = 1006
Public Const VD_PRNRECT_ANGLE = 1007
Public Const VD_PRNRECT_EXTOBJECT = 1008
Public Const VD_PRNRECT___MAX = 1099

Public Const VD_VIEW___MIN = 1101
Public Const VD_VIEW_ID    = 1101
Public Const VD_VIEW_NAME  = 1102
Public Const VD_VIEW_EXTOBJECT = 1103
Public Const VD_VIEW___MAX = 1199

Public Const VD_ENT___MIN = 20001
Public Const VD_ENT_TYPE = 20001
Public Const VD_ENT_HANDLE = 20002
Public Const VD_ENT_ID = 20002
Public Const VD_ENT_KEY = 20003
Public Const VD_ENT_LAYER = 20004
Public Const VD_ENT_LINETYPE = 20005
Public Const VD_ENT_STLINE = 20005
Public Const VD_ENT_PAGE = 20006
Public Const VD_ENT_LEVEL = 20007
Public Const VD_ENT_COLOR = 20008
Public Const VD_ENT_FILLCOLOR = 20009
Public Const VD_ENT_LINEWIDTH = 20010
Public Const VD_ENT_LEFT = 20011
Public Const VD_ENT_BOTTOM = 20012
Public Const VD_ENT_RIGHT = 20013
Public Const VD_ENT_TOP = 20014
Public Const VD_ENT_SELECT = 20015
Public Const VD_ENT_ONSCREEN = 20016
Public Const VD_ENT_INBLOCK = 20017
Public Const VD_ENT_N_GRIPS = 20018
Public Const VD_ENT_DELETED = 20019
Public Const VD_ENT_FILLED = 20020
Public Const VD_ENT_BORDER = 20021
Public Const VD_ENT_OWNCOLOR = 20022
Public Const VD_ENT_OWNFCOLOR = 20023
Public Const VD_ENT_OWNLINEW = 20024
Public Const VD_ENT_WIDTH = 20025
Public Const VD_ENT_HEIGHT = 20026
Public Const VD_ENT_UPDATE = 20027
Public Const VD_ENT_LENGTH = 20028
Public Const VD_ENT_PERIMETER = 20028
Public Const VD_ENT_AREA = 20029
Public Const VD_ENT_INDEX = 20030
Public Const VD_ENT_MULTILINE = 20031
Public Const VD_ENT_EXTOBJECT = 20032
Public Const VD_ENT___MAX = 20099

Public Const VD_LINE___MIN = 20101
Public Const VD_LINE_X1 = 20101
Public Const VD_LINE_Y1 = 20102
Public Const VD_LINE_X2 = 20103
Public Const VD_LINE_Y2 = 20104
Public Const VD_LINE_ARROW1 = 20105
Public Const VD_LINE_ARROW2 = 20106
Public Const VD_LINE___MAX = 20199

Public Const VD_POLY___MIN = 20201
Public Const VD_POLY_CLOSED = 20201
Public Const VD_POLY_SMOOTH = 20202
Public Const VD_POLY_ARROW1 = 20203
Public Const VD_POLY_ARROW2 = 20204
Public Const VD_POLY_R = 20205
Public Const VD_POLY_N_VER = 20206
Public Const VD_POLY_C_VER = 20207
Public Const VD_POLY_GETVERS = 20208
Public Const VD_POLY_SETVERS = 20209
Public Const VD_POLY_VER_INS = 20210
Public Const VD_POLY_VER_DEL = 20211
Public Const VD_POLY_VER_X = 20212
Public Const VD_POLY_VER_Y = 20213
Public Const VD_POLY_VER_R = 20214
Public Const VD_POLY_VER_ON = 20215
Public Const VD_POLY_VER_BULGE = 20216
Public Const VD_POLY_VER_DATA = 20217
Public Const VD_POLY_CUSTDATA = 20231
Public Const VD_POLY___MAX = 20299

Public Const VD_CIRCLE___MIN = 20301
Public Const VD_CIRCLE_X = 20301
Public Const VD_CIRCLE_Y = 20302
Public Const VD_CIRCLE_R = 20303
Public Const VD_CIRCLE___MAX = 20399

Public Const VD_ARC___MIN = 20401
Public Const VD_ARC_X = 20401
Public Const VD_ARC_Y = 20402
Public Const VD_ARC_R = 20403
Public Const VD_ARC_START = 20404
Public Const VD_ARC_END = 20405
Public Const VD_ARC_ARROW1 = 20406
Public Const VD_ARC_ARROW2 = 20407
Public Const VD_ARC_RH = 20411
Public Const VD_ARC_RV = 20412
Public Const VD_ARC_ANG0 = 20413
Public Const VD_ARC_ANGARC = 20414
Public Const VD_ARC_ANGROT = 20415
Public Const VD_ARC_SECTOR = 20431
Public Const VD_ARC_CHORD = 20432
Public Const VD_ARC_XS = 20441
Public Const VD_ARC_YS = 20442
Public Const VD_ARC_XE = 20443
Public Const VD_ARC_YE = 20444
Public Const VD_ARC___MAX = 20499

Public Const VD_ELLIPSE___MIN = 20601
Public Const VD_ELLIPSE_X = 20601
Public Const VD_ELLIPSE_Y = 20602
Public Const VD_ELLIPSE_RH = 20603
Public Const VD_ELLIPSE_RV = 20604
Public Const VD_ELLIPSE_ANGLE = 20605
Public Const VD_ELLIPSE___MAX = 20699

Public Const VD_TEXT___MIN = 20701
Public Const VD_TEXT_X = 20701
Public Const VD_TEXT_Y = 20702
Public Const VD_TEXT_TEXT = 20703
Public Const VD_TEXT_LENGTH = 20704
Public Const VD_TEXT_STYLE = 20705
Public Const VD_TEXT_HEIGHT = 20706
Public Const VD_TEXT_WSCALE = 20707
Public Const VD_TEXT_ALIGN = 20708
Public Const VD_TEXT_ANGLE = 20709
Public Const VD_TEXT_OBLIQUE = 20710
Public Const VD_TEXT_INTER_H = 20712
Public Const VD_TEXT_INTER_V = 20713
Public Const VD_TEXT_PATH = 20714
Public Const VD_TEXT_STRIKEOUT = 20715
Public Const VD_TEXT_UNDERLINE = 20716
Public Const VD_TEXT_N_LINES = 20717
Public Const VD_TEXTP_CURVE = 20721
Public Const VD_TEXTP_DX = 20722
Public Const VD_TEXTP_DY = 20723
Public Const VD_TEXTP_BACKWARD = 20724
Public Const VD_TEXTP_ABSANGLE = 20725
Public Const VD_TEXT___MAX = 20799

Public Const VD_INSBLK___MIN = 20801
Public Const VD_INSBLK_X = 20801
Public Const VD_INSBLK_Y = 20802
Public Const VD_INSBLK_BLOCK = 20803
Public Const VD_INSBLK_ANGLE = 20804
Public Const VD_INSBLK_SCALEX = 20805
Public Const VD_INSBLK_SCALEY = 20806
Public Const VD_INSBLK_SCALE = 20807
Public Const VD_INSBLK___MAX = 20899

Public Const VD_HATCH___MIN = 20901
Public Const VD_HATCH_STYLE = 20901
Public Const VD_HATCH_SCALE = 20902
Public Const VD_HATCH_ANGLE = 20903
Public Const VD_HATCH___MAX = 20999

Public Const VD_BMP___MIN = 21001
Public Const VD_BMP_X = 21001
Public Const VD_BMP_Y = 21002
Public Const VD_BMP_FILENAME = 21003
Public Const VD_BMP_RESX = 21004
Public Const VD_BMP_RESY = 21005
Public Const VD_BMP_RELOAD = 21007
Public Const VD_BMP___MAX = 21099

Public Const VD_POINT___MIN = 21101
Public Const VD_POINT_X = 21101
Public Const VD_POINT_Y = 21102
Public Const VD_POINT_STYLE = 21103
Public Const VD_POINT_GROUP = 21104
Public Const VD_POINT_TEXT = 21105
Public Const VD_POINT_TEXTLEN = 21106
Public Const VD_POINT_TXTDX = 21107
Public Const VD_POINT_TXTDY = 21108
Public Const VD_POINT_TXTANG = 21109
Public Const VD_POINT_BLKANG = 21110
Public Const VD_POINT_FIXED = 21111
Public Const VD_POINT___MAX = 21199

Public Const VD_RECT___MIN = 21201
Public Const VD_RECT_XCEN = 21201
Public Const VD_RECT_YCEN = 21202
Public Const VD_RECT_WIDTH = 21203
Public Const VD_RECT_HEIGHT = 21204
Public Const VD_RECT_ANGLE = 21205
Public Const VD_RECT_RADIUS = 21206
Public Const VD_RECT___MAX = 21299

Public Const VD_DIM___MIN = 22301
Public Const VD_DIM_STYLE = 22301
Public Const VD_DIM_TYPE = 22302
Public Const VD_DIM_STATIC = 22303
Public Const VD_DIM_VALUE = 22304
Public Const VD_DIM_XTEXT = 22305
Public Const VD_DIM_YTEXT = 22306
Public Const VD_DIM___MAX = 22319

Public Const VD_DIM_L___MIN = 22321
Public Const VD_DIM_L_X1 = 22321
Public Const VD_DIM_L_Y1 = 22322
Public Const VD_DIM_L_X2 = 22323
Public Const VD_DIM_L_Y2 = 22324
Public Const VD_DIM_L_OFFSET = 22325
Public Const VD_DIM_L_XLINE = 22325
Public Const VD_DIM_L_YLINE = 22325
Public Const VD_DIM_L___MAX = 22339

Public Const VD_DIM_A___MIN = 22341
Public Const VD_DIM_A_XCEN = 22341
Public Const VD_DIM_A_YCEN = 22342
Public Const VD_DIM_A_X1 = 22343
Public Const VD_DIM_A_Y1 = 22344
Public Const VD_DIM_A_X2 = 22345
Public Const VD_DIM_A_Y2 = 22346
Public Const VD_DIM_A_RADIUS = 22347
Public Const VD_DIM_A___MAX = 22359

Public Const VD_DIM_R___MIN = 22361
Public Const VD_DIM_R_XCEN = 22361
Public Const VD_DIM_R_YCEN = 22362
Public Const VD_DIM_R_XRAD = 22363
Public Const VD_DIM_R_YRAD = 22364
Public Const VD_DIM_R_OFFSET = 22365
Public Const VD_DIM_R___MAX = 22369

Public Const VD_DIM_D___MIN = 22371
Public Const VD_DIM_D_XCEN = 22371
Public Const VD_DIM_D_YCEN = 22372
Public Const VD_DIM_D_XRAD = 22373
Public Const VD_DIM_D_YRAD = 22374
Public Const VD_DIM_D___MAX = 22379

Public Const VD_DIM_O___MIN = 22391
Public Const VD_DIM_O_X = 22391
Public Const VD_DIM_O_Y = 22392
Public Const VD_DIM_O_ORDY = 22393
Public Const VD_DIM_O___MAX = 22399

Public Const VD_CE___MIN = 22901
Public Const VD_CE_DATA = 22901
Public Const VD_CE_DATASIZE = 22901
Public Const VD_CE___MAX = 22999

Public Const VD_INSDWG___MIN = 23001
Public Const VD_INSDWG_FILENAME = 23001
Public Const VD_INSDWG_X = 23002
Public Const VD_INSDWG_Y = 23003
Public Const VD_INSDWG_ANGLE = 23004
Public Const VD_INSDWG_SCALEX = 23005
Public Const VD_INSDWG_SCALEY = 23006
Public Const VD_INSDWG_WIDTH = 23007
Public Const VD_INSDWG_HEIGHT = 23008
Public Const VD_INSDWG_RELOAD = 23017
Public Const VD_INSDWG___MAX = 23099

Public Const VD_GLASS___MIN = 23101
Public Const VD_GLASS_X = 23101
Public Const VD_GLASS_Y = 23102
Public Const VD_GLASS_W = 23103
Public Const VD_GLASS_H = 23104
Public Const VD_GLASS_MLEF = 23105
Public Const VD_GLASS_MTOP = 23106
Public Const VD_GLASS_MRIG = 23107
Public Const VD_GLASS_MBOT = 23108
Public Const VD_GLASS_FILENAME = 23109
'Public Const VD_GLASS_KEEPPROP  = 23110
'Public Const VD_GLASS_FITSIZE   = 23111
Public Const VD_GLASS_W2 = 23112
Public Const VD_GLASS_H2 = 23113
Public Const VD_GLASS_ANGLE = 23114
Public Const VD_GLASS_DWGMODE = 23115
Public Const VD_GLASS___MAX = 23199

Public Const VD_FLOOD___MIN = 23201
Public Const VD_FLOOD_X = 23201
Public Const VD_FLOOD_Y = 23202
Public Const VD_FLOOD___MAX = 23299



'********************************************************************
'* VeCAD strings resources identifiers (message VM_GETSTRING)
'********************************************************************

Public Const VS_MSGTITLE = 10501
Public Const VS_NONAME = 10502
Public Const VS_UNDO_EMPTY = 10503
Public Const VS_REDO_EMPTY = 10504
Public Const VS_NO_FONT_FILE = 10505
Public Const VS_DELETE_OBJ = 10506
Public Const VS_SAVE_CHANGES = 10507
Public Const VS_OLD_VEC_FORMAT = 10508
Public Const VS_NEW_VEC_FORMAT = 10509
Public Const VS_DWG_ALREADY_LOADED = 10510
Public Const VS_NO_BLOCKS = 10511
Public Const VS_LOAD_ERROR_SUM = 10512
Public Const VS_LOADING = 10513
Public Const VS_SAVING = 10514
Public Const VS_EMPTYDWG = 10515
Public Const VS_CANT_LOAD_FILE = 10516
Public Const VS_BEGIN_EDITBLOCK = 10517
Public Const VS_EDITBLOCK_MODE = 10518
Public Const VS_DIFFER_LAYERS = 10519
Public Const VS_SEARCH_FILE = 10520

Public Const VS_FILTER_VEC    = 10541
Public Const VS_FILTER_SHP    = 10542 
Public Const VS_FILTER_PAT    = 10543
Public Const VS_FILTER_BMP    = 10544
Public Const VS_FILTER_VDF    = 10545
Public Const VS_FILTER_HPGL   = 10546
Public Const VS_FILTER_DP1    = 10547
Public Const VS_FILTER_CNC    = 10548
Public Const VS_FILTER_DXF    = 10551
Public Const VS_FILTER_DWGDXF = 10552
Public Const VS_FILTER_DWG    = 10553
Public Const VS_FILTER_AVSHP  = 10554

Public Const VS_DEL_LAYER_ONE = 10651
Public Const VS_DEL_LAYER_HAS_REF = 10652
Public Const VS_DEL_PAGE_ONE = 10653
Public Const VS_DEL_PAGE_HAS_REF = 10654
Public Const VS_DEL_STLINE_ONE = 10655
Public Const VS_DEL_STLINE_HAS_REF = 10656
Public Const VS_DEL_STTEXT_ONE = 10657
Public Const VS_DEL_STTEXT_HAS_REF = 10658
Public Const VS_DEL_STDIM_ONE = 10659
Public Const VS_DEL_STDIM_HAS_REF = 10660
Public Const VS_DEL_STHATCH_ONE = 10661
Public Const VS_DEL_STHATCH_HAS_REF = 10662
Public Const VS_DEL_BLOCK_HAS_REF = 10663
Public Const VS_DEL_STPOINT_ONE = 10664
Public Const VS_DEL_STPOINT_HAS_REF = 10665
Public Const VS_DEL_STPOINT_SIMPLE = 10667
Public Const VS_DEL_GRPOINT_ONE = 10668
Public Const VS_DEL_GRPOINT_HAS_REF = 10669
Public Const VS_DEL_MLINE_HAS_REF = 10670
Public Const VS_DEL_PRNRECT = 10671

Public Const VS_DWGLIST_TITLE = 10981
Public Const VS_DWGLIST_CLOSE = 10982

Public Const VS_VIEW_TITLE = 10985
Public Const VS_VIEW_EDIT = 10986
Public Const VS_VIEW_DELETE = 10987
Public Const VS_VIEW_SAVE = 10988
Public Const VS_VIEW_NAME = 10989

Public Const VS_BUT_OK = 11201
Public Const VS_BUT_CANCEL = 11202
Public Const VS_BUT_ADD = 11203
Public Const VS_BUT_DELETE = 11204
Public Const VS_BUT_CURRENT = 11205
Public Const VS_BUT_SELECT = 11206
Public Const VS_BUT_UNSELECT = 11207
Public Const VS_N_REFS = 11221
Public Const VS_OBJVIEW = 11222

Public Const VS_SELPAGE = 11301

Public Const VS_LAYOUT_TITLE = 11302
Public Const VS_DAID_TITLE = 11303
Public Const VS_ENTPROP_TITLE = 11304
Public Const VS_ENTPROP_TITLE2 = 11305

Public Const VS_PAGE_TITLE = 11401
Public Const VS_PAGE_BOOK = 11402
Public Const VS_PAGE_ALBUM = 11403
Public Const VS_PAGE_NAME = 11405
Public Const VS_PAGE_NAME2 = 11406
Public Const VS_PAGE_SIZE = 11407
Public Const VS_PAGE_W = 11408
Public Const VS_PAGE_H = 11409
Public Const VS_PAGE_ORIENT = 11410
Public Const VS_PAGE_BTNFORALL = 11419
Public Const VS_PAGE_FORALL = 11420

Public Const VS_LAYER_TITLE = 11501
Public Const VS_LAYER_NAME = 11502
Public Const VS_LAYER_STATE = 11503
Public Const VS_LAYER_NAME2 = 11504
Public Const VS_LAYER_LWIDTH2 = 11505
Public Const VS_LAYER_COLOR = 11506
Public Const VS_LAYER_FCOLOR = 11507
Public Const VS_LAYER_OFF = 11508
Public Const VS_LAYER_RDONLY = 11509
Public Const VS_LAYER_NOPRINT = 11510
Public Const VS_LAYER_SELINS = 11511
Public Const VS_LAYER_LEVEL = 11512

Public Const VS_STLINE_TITLE = 11601
Public Const VS_STLINE_NAME = 11602
Public Const VS_STLINE_NAME2 = 11603
Public Const VS_STLINE_DESC = 11604
Public Const VS_STLINE_APPLY = 11605

Public Const VS_MLINE_TITLE = 11631
Public Const VS_MLINE_NAME = 11632
Public Const VS_MLINE_JOINTS = 11633
Public Const VS_MLINE_CAPS = 11634
Public Const VS_MLINE_START = 11635
Public Const VS_MLINE_END = 11636
Public Const VS_MLINE_LINE = 11637
Public Const VS_MLINE_OUTARC = 11638
Public Const VS_MLINE_INARC = 11639
Public Const VS_MLINE_VIEW = 11640
Public Const VS_MLINE_ELEMENTS = 11641
Public Const VS_MLINE_OFFSET = 11642
Public Const VS_MLINE_LINESTYLE = 11643
Public Const VS_MLINE_OFFSET2 = 11644
Public Const VS_MLINE_LINESEL = 11645
Public Const VS_MLINE_LINEADD = 11646
Public Const VS_MLINE_LINEDEL = 11647

Public Const VS_STTEXT_TITLE = 11701
Public Const VS_STTEXT_CHFONT = 11702
Public Const VS_STTEXT_RELOAD = 11703
Public Const VS_STTEXT_NAME = 11704
Public Const VS_STTEXT_NAME2 = 11705
Public Const VS_STTEXT_FILE = 11706
Public Const VS_STTEXT_WIDTH = 11707
Public Const VS_STTEXT_SHIFT = 11708
Public Const VS_STTEXT_PRECISION = 11709
Public Const VS_STTEXT_FILLED = 11710
Public Const VS_STTEXT_FONTFILE = 11711
Public Const VS_STTEXT_FONTSYS = 11712
Public Const VS_STTEXT_BIGFONT = 11713
Public Const VS_STTEXT_NCHARS = 11714
Public Const VS_STTEXT_BYSYMBOLS = 11715
Public Const VS_STTEXT_BYLINES = 11716

Public Const VS_STDIM_TITLE = 11801
Public Const VS_STDIM_TITLE1 = 11802
Public Const VS_STDIM_TITLE2 = 11803
Public Const VS_STDIM_TITLE3 = 11804
Public Const VS_STDIM_TA_ABOVE = 11805
Public Const VS_STDIM_TA_CENTER = 11806
Public Const VS_STDIM_TA_BELOW = 11807
Public Const VS_STDIM_NAME = 11811
Public Const VS_STDIM_NAME2 = 11812
Public Const VS_STDIM_INSLINE = 11821
Public Const VS_STDIM_ARRHEAD = 11822
Public Const VS_STDIM_ARRTYPE = 11823
Public Const VS_STDIM_ARRLEN = 11824
Public Const VS_STDIM_ARRH = 11825
Public Const VS_STDIM_EXTLINE = 11826
Public Const VS_STDIM_OFFSET = 11827
Public Const VS_STDIM_EXTEND = 11828
Public Const VS_STDIM_COLORS = 11829
Public Const VS_STDIM_OWNCOL = 11830
Public Const VS_STDIM_COLDIM = 11831
Public Const VS_STDIM_COLEXL = 11832
Public Const VS_STDIM_COLTXT = 11833
Public Const VS_STDIM_CENTER = 11834
Public Const VS_STDIM_CENMARK = 11835
Public Const VS_STDIM_CENLINE = 11836
Public Const VS_STDIM_CENNONE = 11837
Public Const VS_STDIM_CENSIZE = 11838
Public Const VS_STDIM_PREFIX = 11851
Public Const VS_STDIM_TXTSTYLE = 11852
Public Const VS_STDIM_TXTALIGN = 11853
Public Const VS_STDIM_TXTH = 11854
Public Const VS_STDIM_TXTGAP = 11855
Public Const VS_STDIM_TXTDEC = 11856
Public Const VS_STDIM_SCALE = 11857
Public Const VS_STDIM_ROUND = 11858
Public Const VS_STDIM_TOLER = 11859
Public Const VS_STDIM_TPLUS = 11860
Public Const VS_STDIM_TMINUS = 11861
Public Const VS_STDIM_TXTHORZ = 11862
Public Const VS_STDIM_TXTARC90 = 11863
Public Const VS_STDIM_TXTRECT = 11864
Public Const VS_STDIM_ENDZERO = 11865

Public Const VS_STHAT_TITLE = 11901
Public Const VS_STHAT_TITLE2 = 11902
Public Const VS_STHAT_APPLY = 11903
Public Const VS_STHAT_NAME = 11904
Public Const VS_STHAT_NAME2 = 11905
Public Const VS_STHAT_DESC = 11906
Public Const VS_STHAT_LOAD = 11907

Public Const VS_BLOCKS_TITLE = 12001
Public Const VS_BLOCKS_ADD = 12002
Public Const VS_BLOCKS_DELETE = 12003
Public Const VS_BLOCKS_NAME = 12004
Public Const VS_BLOCKS_VIEW = 12005
Public Const VS_BLOCKS_NAME2 = 12006
Public Const VS_BLOCKS_SIZE = 12007
Public Const VS_BLOCKS_DX = 12008
Public Const VS_BLOCKS_DY = 12009
Public Const VS_BLOCKS_ENTS = 12010
Public Const VS_BLOCKS_BYLAYER = 12011
Public Const VS_BLOCKS_EDIT = 12012


Public Const VS_SELBLK_TITLE = 12031
Public Const VS_SELBLK_NSEL = 12032
Public Const VS_SELBLK_SELALL = 12033
Public Const VS_SELBLK_UNSELALL = 12034

Public Const VS_NEWBLK_TITLE = 12051
Public Const VS_NEWBLK_NAME = 12052

Public Const VS_STPNT_TITLE = 12101
Public Const VS_STPNT_SIMPLE = 12102
Public Const VS_STPNT_NODRAW = 12103
Public Const VS_STPNT_DRAWBLK = 12104
Public Const VS_STPNT_DRAWTEXT = 12105
Public Const VS_STPNT_DRAWALL = 12106
Public Const VS_STPNT_NAME = 12117
Public Const VS_STPNT_STAT = 12118
Public Const VS_STPNT_LAYER = 12119
Public Const VS_STPNT_TEXT = 12120
Public Const VS_STPNT_TSTYLE = 12121
Public Const VS_STPNT_THIGH = 12122
Public Const VS_STPNT_TSCALE = 12123
Public Const VS_STPNT_SYMBOL = 12124
Public Const VS_STPNT_BLOCK = 12125
Public Const VS_STPNT_BSCALE = 12126
Public Const VS_STPNT_FIXED = 12127
Public Const VS_STPNT_SNAP = 12128

Public Const VS_GRID_TITLE = 12401
Public Const VS_GRID_POINT = 12402
Public Const VS_GRID_CROSS = 12403
Public Const VS_GRID_CROSS45 = 12404
Public Const VS_GRID_LINE = 12405
Public Const VS_GRID_DOTLINE = 12406
Public Const VS_GRID_DASHLINE = 12407
Public Const VS_GRID_ORIGIN = 12411
Public Const VS_GRID_STEP = 12412
Public Const VS_GRID_HORZ = 12413
Public Const VS_GRID_VERT = 12414
Public Const VS_GRID_BOLDSTEP = 12415
Public Const VS_GRID_SNAP = 12416
Public Const VS_GRID_SHOW = 12417
Public Const VS_GRID_PRINT = 12418
Public Const VS_GRID_MAIN = 12419
Public Const VS_GRID_BOLD = 12420
Public Const VS_GRID_TYPE = 12421
Public Const VS_GRID_COLOR = 12422

Public Const VS_OSNAP_TITLE = 12431
Public Const VS_OSNAP_END = 12432
Public Const VS_OSNAP_MID = 12433
Public Const VS_OSNAP_CENTER = 12434
Public Const VS_OSNAP_POINT = 12435
Public Const VS_OSNAP_INTER = 12436
Public Const VS_OSNAP_NEAR = 12437
Public Const VS_OSNAP_GRIP = 12438
Public Const VS_OSNAP_PERP = 12439
Public Const VS_OSNAP_TANG = 12440
Public Const VS_OSNAP_CLEAR = 12441
Public Const VS_OSNAP_APERSIZE = 12442
Public Const VS_OSNAP_SELECT = 12443
Public Const VS_OSNAP_REALTIME = 12444

Public Const VS_PSNAP_TITLE = 12461
Public Const VS_PSNAP_ON = 12462
Public Const VS_PSNAP_DIST = 12463
Public Const VS_PSNAP_ANGLE = 12464
Public Const VS_PSNAP_ANGLE_0 = 12465

Public Const VS_UNITS_TITLE = 12501
Public Const VS_UNITS_UNITS = 12502
Public Const VS_UNITS_SCALE = 12503
Public Const VS_UNITS_X0 = 12504
Public Const VS_UNITS_Y0 = 12505
Public Const VS_UNITS_GEO = 12506
Public Const VS_UNITS_PREC = 12507
Public Const VS_UNIT_POINT = 12511
Public Const VS_UNIT_MM = 12512
Public Const VS_UNIT_CM = 12513
Public Const VS_UNIT_MET = 12514
Public Const VS_UNIT_KM = 12515
Public Const VS_UNIT_INCH = 12516
Public Const VS_UNIT_FOOT = 12517
Public Const VS_UNIT_YARD = 12518
Public Const VS_UNIT_MILE = 12519
Public Const VS_UNIT_SEAMILE = 12520
Public Const VS_ANG_DEGREE = 12531
Public Const VS_ANG_RADIAN = 12532

Public Const VS_PRIV_TITLE = 12551
Public Const VS_PRIV_DWGTITLE = 12552
Public Const VS_PRIV_OWNER = 12553
Public Const VS_PRIV_COMMENT = 12554
Public Const VS_PRIV_PSW = 12555
Public Const VS_PRIV_INFO = 12556
Public Const VS_PRIV_NOPSW = 12557
Public Const VS_PRIV_NOLOAD = 12558
Public Const VS_PRIV_VIEWONLY = 12559
Public Const VS_PRIV_NOEXPORT = 12560
Public Const VS_PRIV_NOPRINT = 12561

Public Const VS_PSW_TITLE = 12581
Public Const VS_PSW_WRONG = 12582
Public Const VS_PSW_READONLY = 12583
Public Const VS_PSW_WORD = 12584

Public Const VS_PREF_TITLE = 12601
Public Const VS_PREF_AUTOSELPNT = 12602
Public Const VS_PREF_AUTOSELWIN = 12603
Public Const VS_PREF_SHOWGRID = 12604
Public Const VS_PREF_SHOWFILL = 12605
Public Const VS_PREF_SHOWLINEW = 12606
Public Const VS_PREF_SHOWVECT = 12607
Public Const VS_PREF_SHOWBMP = 12608
Public Const VS_PREF_PENW0 = 12609
Public Const VS_PREF_CURSOR = 12613
Public Const VS_PREF_SIZECURS = 12614
Public Const VS_PREF_COLCURS = 12615
Public Const VS_PREF_GRIPS = 12616
Public Const VS_PREF_GRIPSIZE = 12617
Public Const VS_PREF_COLGRIP = 12618
Public Const VS_PREF_COLSELGRIP = 12619
Public Const VS_PREF_COLBKG = 12620
Public Const VS_PREF_COLPAGE = 12621
Public Const VS_PREF_COLSELOBJ = 12622
Public Const VS_PREF_CCOLOR = 12623
Public Const VS_PREF_BYLAYER = 12624
Public Const VS_PREF_SEGCURVE = 12625
Public Const VS_PREF_CHARFRAME = 12626
Public Const VS_PREF_UNSELAFTER = 12627
Public Const VS_PREF_SELINSIDE = 12628
Public Const VS_PREF_SELACTLAYER = 12629

Public Const VS_NAV_TITLE = 12701
Public Const VS_NAV_ZRCOLOR = 12702
Public Const VS_NAV_REALTIME = 12703

Public Const VS_SELSTLINE = 12801

Public Const VS_ENT_TITLE = 13001
Public Const VS_ENT_LAYER = 13002
Public Const VS_ENT_LTYPE = 13003
Public Const VS_ENT_PAGE = 13004
Public Const VS_ENT_LCOL = 13005
Public Const VS_ENT_FCOL = 13006
Public Const VS_ENT_BYLAY = 13007
Public Const VS_ENT_FILLED = 13008
Public Const VS_ENT_BORDER = 13009
Public Const VS_ENT_LINEW = 13010
Public Const VS_ENT_LEVEL = 13011
Public Const VS_ENT_LIMITS = 13012
Public Const VS_ENT_HANDLE = 13013
Public Const VS_ENT_KEY = 13014

Public Const VS_ARR_TITLE = 13031
Public Const VS_ARR_DIMST0 = 13032
Public Const VS_ARR_DIMST1 = 13033

Public Const VS_LINE_TITLE = 13101
Public Const VS_LINE_PNT1 = 13102
Public Const VS_LINE_PNT2 = 13103
Public Const VS_LINE_ARROW = 13104
Public Const VS_LINE_NOARROW = 13105
Public Const VS_LINE_LENGTH = 13106
Public Const VS_LINE_ANGLE = 13107

Public Const VS_TEXT_TITLE = 13201
Public Const VS_TEXT_TITLE2 = 13202
Public Const VS_TEXT_TA_LEFBOT = 13203
Public Const VS_TEXT_TA_MIDBOT = 13204
Public Const VS_TEXT_TA_RIGBOT = 13205
Public Const VS_TEXT_TA_LEFMID = 13206
Public Const VS_TEXT_TA_MIDMID = 13207
Public Const VS_TEXT_TA_RIGMID = 13208
Public Const VS_TEXT_TA_LEFTOP = 13209
Public Const VS_TEXT_TA_MIDTOP = 13210
Public Const VS_TEXT_TA_RIGTOP = 13211
Public Const VS_TEXT_NO_PATH = 13212
Public Const VS_TEXT_POINT = 13221
Public Const VS_TEXT_HEIGHT = 13222
Public Const VS_TEXT_WIDTH = 13223
Public Const VS_TEXT_ROTANG = 13224
Public Const VS_TEXT_IVERT = 13225
Public Const VS_TEXT_IHORZ = 13226
Public Const VS_TEXT_ALIGN = 13227
Public Const VS_TEXT_STYLE = 13228
Public Const VS_TEXT_TEXT = 13229
Public Const VS_TEXT_OBLIQUE = 13230
Public Const VS_TEXT_STRIKEOUT = 13231
Public Const VS_TEXT_UNDERLINE = 13232
Public Const VS_TEXT_PTWRITE = 13241
Public Const VS_TEXT_PTBACK = 13242
Public Const VS_TEXT_PTABSANG = 13243
Public Const VS_TEXT_PTHANDLE = 13244
Public Const VS_TEXT_PTDY = 13245
Public Const VS_TEXT_PTDX = 13246

Public Const VS_CIRC_TITLE = 13301
Public Const VS_CIRC_CENTER = 13302
Public Const VS_CIRC_RADIUS = 13303
Public Const VS_CIRC_LENGTH = 13304
Public Const VS_CIRC_AREA = 13305

Public Const VS_POLY_TITLE = 13401
Public Const VS_POLY_LINE = 13402
Public Const VS_POLY_BSPLINE2 = 13403
Public Const VS_POLY_BSPLINE3 = 13404
Public Const VS_POLY_FITBSPL3 = 13405
Public Const VS_POLY_LINBSPL2 = 13406
Public Const VS_POLY_AUTOBEZIER = 13407
Public Const VS_POLY_BEZIER = 13408
Public Const VS_POLY_ROUNDED = 13409
Public Const VS_POLY_MULTIRAD = 13410
Public Const VS_POLY_BULGE = 13411
Public Const VS_POLY_CLOSED = 13421
Public Const VS_POLY_SMOOTH = 13422
Public Const VS_POLY_RAD = 13423
Public Const VS_POLY_PERIM = 13424
Public Const VS_POLY_AREA = 13425
Public Const VS_POLY_DIMST0 = 13429
Public Const VS_POLY_DIMST1 = 13430
Public Const VS_POLY_NVER = 13434
Public Const VS_POLY_VERTABLE = 13435

Public Const VS_PVER_TITLE = 13451
Public Const VS_PVER_ONLINE = 13452
Public Const VS_PVER_OFFLINE = 13453
Public Const VS_PVER_CLOSE = 13454
Public Const VS_PVER_ADD = 13455
Public Const VS_PVER_INSERT = 13456
Public Const VS_PVER_DELETE = 13457
Public Const VS_PVER_RADIUS = 13458
Public Const VS_PVER_ONCURVE = 13459
Public Const VS_PVER_BULGE = 13460
Public Const VS_PVER_LENGTH = 13461
Public Const VS_PVER_ANGLE = 13462

Public Const VS_INSBLK_TITLE = 13501
Public Const VS_INSBLK_NAME = 13502
Public Const VS_INSBLK_POINT = 13503
Public Const VS_INSBLK_ANGLE = 13504
Public Const VS_INSBLK_SCX = 13505
Public Const VS_INSBLK_SCY = 13506
Public Const VS_INSBLK_WIDTH = 13507
Public Const VS_INSBLK_HEIGHT = 13508
Public Const VS_INSBLK_BYLAY = 13509

Public Const VS_HATCH_TITLE = 13601
Public Const VS_HATCH_NAME = 13602
Public Const VS_HATCH_ANGLE = 13603
Public Const VS_HATCH_SCALE = 13604
Public Const VS_HATCH_SIZE = 13605

Public Const VS_POINT_TITLE = 13701
Public Const VS_POINT_TYPE = 13703
Public Const VS_POINT_BLKANG = 13704
Public Const VS_POINT_TEXT = 13705
Public Const VS_POINT_TXTANG = 13706
Public Const VS_POINT_TXTOFFSET = 13707
Public Const VS_POINT_FIXED = 13708

Public Const VS_BMP_TITLE = 13801
Public Const VS_BMP_FILE = 13802
Public Const VS_BMP_INS = 13803
Public Const VS_BMP_RES = 13804
Public Const VS_BMP_RESH = 13805
Public Const VS_BMP_RESV = 13806
Public Const VS_BMP_WIDTH = 13807
Public Const VS_BMP_HEIGHT = 13808
Public Const VS_BMP_RELOAD = 13809

Public Const VS_ELL_TITLE = 13901
Public Const VS_ELL_CENTER = 13902
Public Const VS_ELL_RADIUS = 13903
Public Const VS_ELL_RH = 13904
Public Const VS_ELL_RV = 13905
Public Const VS_ELL_ANGLE = 13906
Public Const VS_ELL_LEN = 13907
Public Const VS_ELL_AREA = 13908

Public Const VS_ARC_TITLE = 14001
Public Const VS_ARC_CENTER = 14002
Public Const VS_ARC_TYPE = 14007
Public Const VS_ARC_ARC = 14008
Public Const VS_ARC_CHORD = 14009
Public Const VS_ARC_SECTOR = 14010
Public Const VS_ARC_LEN = 14013
Public Const VS_ARC_AREA = 14014
Public Const VS_ARC_RADIUS = 14021
Public Const VS_ARC_RH = 14022
Public Const VS_ARC_RV = 14023
Public Const VS_ARC_ANG0 = 14024
Public Const VS_ARC_ANGARC = 14025
Public Const VS_ARC_ANGROT = 14026

Public Const VS_RECT_TITLE = 14101
Public Const VS_RECT_CENTER = 14102
Public Const VS_RECT_W = 14103
Public Const VS_RECT_H = 14104
Public Const VS_RECT_RAD = 14105
Public Const VS_RECT_ANG = 14106
Public Const VS_RECT_LEN = 14107
Public Const VS_RECT_AREA = 14108

Public Const VS_SYMB_TITLE = 14201
Public Const VS_SYMB_HEIGHT = 14202
Public Const VS_SYMB_FONT = 14203

Public Const VS_DIM_TITLE = 14401
Public Const VS_DIM_HORZ = 14402
Public Const VS_DIM_VERT = 14403
Public Const VS_DIM_PARAL = 14404
Public Const VS_DIM_ANG = 14405
Public Const VS_DIM_RAD = 14406
Public Const VS_DIM_DIAM = 14407
Public Const VS_DIM_ORD = 14408
Public Const VS_DIM_OWN = 14412
Public Const VS_DIM_TYPE = 14413
Public Const VS_DIM_MEASURE = 14414
Public Const VS_DIM_VALUE = 14415
Public Const VS_DIM_STYLE = 14416

Public Const VS_INSDWG_TITLE = 14501
Public Const VS_INSDWG_FNAME = 14502
Public Const VS_INSDWG_INSPNT = 14503
Public Const VS_INSDWG_ANGLE = 14504
Public Const VS_INSDWG_SCX = 14505
Public Const VS_INSDWG_SCY = 14506
Public Const VS_INSDWG_WIDTH = 14507
Public Const VS_INSDWG_HEIGHT = 14508
Public Const VS_INSDWG_RELOAD = 14509

Public Const VS_PRINT_TITLE = 16001
Public Const VS_PRINT_PRINTER = 16002
Public Const VS_PRINT_PICK = 16003
Public Const VS_PRINT_FIT = 16004
Public Const VS_PRINT_ALL = 16005
Public Const VS_PRINT_PAGE = 16006
Public Const VS_PRINT_PRECT = 16007
Public Const VS_PRINT_DISP = 16008
Public Const VS_PRINT_WIN = 16009
Public Const VS_PRINT_PGALL = 16010
Public Const VS_PRINT_PGCUR = 16011
Public Const VS_PRINT_PGNO = 16012
Public Const VS_PRINT_CURPRN = 16013
Public Const VS_PRINT_PAPERSIZE = 16014
Public Const VS_PRINT_RES = 16015
Public Const VS_PRINT_REGION = 16016
Public Const VS_PRINT_WLEFBOT = 16017
Public Const VS_PRINT_WRIGTOP = 16018
Public Const VS_PRINT_REGSIZE = 16019
Public Const VS_PRINT_SCALE = 16020
Public Const VS_PRINT_ATX = 16021
Public Const VS_PRINT_ATY = 16022
Public Const VS_PRINT_ORIGIN = 16023
Public Const VS_PRINT_COPIES = 16024
Public Const VS_PRINT_PAGES = 16025
Public Const VS_PRINT_PRECTS = 16026
Public Const VS_PRINT_ALBUM = 16027
Public Const VS_PRINT_BOOK = 16028

Public Const VS_EXPBMP_TITLE = 16101
Public Const VS_EXPBMP_FILE = 16102
Public Const VS_EXPBMP_AREA = 16103
Public Const VS_EXPBMP_ALL = 16104
Public Const VS_EXPBMP_DISP = 16105
Public Const VS_EXPBMP_WIN = 16106
Public Const VS_EXPBMP_PICK = 16107
Public Const VS_EXPBMP_LEFBOT = 16108
Public Const VS_EXPBMP_RIGTOP = 16109
Public Const VS_EXPBMP_SIZEMM = 16110
Public Const VS_EXPBMP_RES = 16111
Public Const VS_EXPBMP_SIZEPIX = 16112

Public Const VS_EXPSHP_TITLE = 16121
Public Const VS_EXPSHP_ENTITIES = 16122
Public Const VS_EXPSHP_TYPE = 16123
Public Const VS_EXPSHP_LAYER = 16124
Public Const VS_EXPSHP_ALLLAYERS = 16125
Public Const VS_EXPSHP_SELECTED = 16126
Public Const VS_EXPSHP_CONVERT = 16127
Public Const VS_EXPSHP_ARCS = 16128
Public Const VS_EXPSHP_LATITUDE = 16129
Public Const VS_EXPSHP_LONGITUDE = 16130
Public Const VS_EXPSHP_POINT = 16131
Public Const VS_EXPSHP_POLYLINE = 16132
Public Const VS_EXPSHP_POLYGON =  16133
Public Const VS_EXPSHP_LAYERS_DIFFER = 16134

Public Const VS_PRR_TITLE = 16201
Public Const VS_PRR_EXIT = 16202
Public Const VS_PRR_ADD = 16203
Public Const VS_PRR_DEL = 16204
Public Const VS_PRR_FORALL = 16205
Public Const VS_PRR_MOVE = 16206
Public Const VS_PRR_COLOR = 16207
Public Const VS_PRR_SHOW = 16208
Public Const VS_PRR_HX = 16209
Public Const VS_PRR_HY = 16210
Public Const VS_PRR_HSIZE = 16211
Public Const VS_PRR_HANGLE = 16212
Public Const VS_PRR_CENTER = 16213
Public Const VS_PRR_PRM = 16214
Public Const VS_PRR_W = 16215
Public Const VS_PRR_H = 16216
Public Const VS_PRR_ANG = 16217
Public Const VS_PRR_AUTOSPLIT = 16218
Public Const VS_PRR_ALLDELETE = 16219
Public Const VS_PRR_NOSIZE = 16220

Public Const VS_DIST_TITLE = 16301
Public Const VS_DIST_BYOBJ = 16302
Public Const VS_DIST_START = 16303
Public Const VS_DIST_RESET = 16304
Public Const VS_DIST_DIST = 16305
Public Const VS_DIST_PERIM = 16306
Public Const VS_DIST_ANGLE = 16307
Public Const VS_DIST_AREA = 16308
Public Const VS_DIST_SUMAREA = 16309

Public Const VS_STAT_DWGFILE = 17001
Public Const VS_STAT_FILESIZE = 17002
Public Const VS_STAT_DWGWIDTH = 17003
Public Const VS_STAT_DWGHEIGHT = 17004
Public Const VS_STAT_DWGLEFT = 17005
Public Const VS_STAT_DWGBOTTOM = 17006
Public Const VS_STAT_DWGRIGHT = 17007
Public Const VS_STAT_DWGTOP = 17008
Public Const VS_STAT_DRAWTIME = 17009
Public Const VS_STAT_PAGES = 17021
Public Const VS_STAT_LAYERS = 17022
Public Const VS_STAT_STLINES = 17023
Public Const VS_STAT_STTEXTS = 17024
Public Const VS_STAT_STHATCHS = 17025
Public Const VS_STAT_STDIMS = 17026
Public Const VS_STAT_STPOINTS = 17027
Public Const VS_STAT_BLOCKS = 17028
Public Const VS_STAT_ENTS = 17029
Public Const VS_STAT_POLYVERS = 17030
Public Const VS_STAT_TEXTCHARS = 17031
Public Const VS_STAT_ENTBYLAYER = 17041
Public Const VS_STAT_ENTBYPAGE = 17042
Public Const VS_STAT_ENTBYBLOCK = 17043
Public Const VS_STAT_ENTBYTYPE = 17050
Public Const VS_STAT_POINT = 17051
Public Const VS_STAT_LINE = 17052
Public Const VS_STAT_POLY = 17053
Public Const VS_STAT_CIRCLE = 17054
Public Const VS_STAT_ARC = 17055
Public Const VS_STAT_ELLIPSE = 17056
Public Const VS_STAT_TEXT = 17057
Public Const VS_STAT_BITMAP = 17058
Public Const VS_STAT_INSBLOCK = 17059
Public Const VS_STAT_HATCH = 17060
Public Const VS_STAT_RECT = 17061
Public Const VS_STAT_DIMLIN = 17062
Public Const VS_STAT_DIMANG = 17063
Public Const VS_STAT_DIMRAD = 17064
Public Const VS_STAT_DIMDIAM = 17065
Public Const VS_STAT_DIMORD = 17066
Public Const VS_STAT_FILEVECVER = 17070
Public Const VS_STAT_CURVECVER = 17071

Public Const VS_MENU_ENTPROP = 18001
Public Const VS_MENU_COPY = 18002
Public Const VS_MENU_MOVE = 18003
Public Const VS_MENU_ROTATE = 18004
Public Const VS_MENU_SCALE = 18005
Public Const VS_MENU_MIRROR = 18006
Public Const VS_MENU_CREBLOCK = 18007
Public Const VS_MENU_EXPLODE = 18008
Public Const VS_MENU_ERASE = 18009
Public Const VS_MENU_UNSELALL = 18010
Public Const VS_MENU_JOIN = 18011
Public Const VS_MENU_VER_INS = 18021
Public Const VS_MENU_VER_DEL = 18022
Public Const VS_MENU_VER_RAD = 18023
Public Const VS_MENU_VER_FIX = 18024
Public Const VS_MENU_VER_EDIT = 18025

Public Const VS_SEL_BY_HANDLE = 18101
Public Const VS_ENTER_HANDLE = 18102
Public Const VS_SEL_BY_KEY = 18103
Public Const VS_ENTER_KEY = 18104
Public Const VS_N_WAS_SELECTED = 18105

Public Const VS_GRIDPLINE_TITLE = 18151

' tooltips string
Public Const VS_TT_FILE_NEW = 19001
Public Const VS_TT_FILE_OPEN = 19002
Public Const VS_TT_FILE_SAVE = 19003
Public Const VS_TT_PRINT = 19004
Public Const VS_TT_TOOL_PRNRECT = 19005
Public Const VS_TT_ZOOM_ALL = 19006
Public Const VS_TT_ZOOM_WIN = 19007
Public Const VS_TT_ZOOM_IN = 19008
Public Const VS_TT_ZOOM_OUT = 19009
Public Const VS_TT_ZOOM_PAN = 19010
Public Const VS_TT_ZOOM_PREV = 19011
Public Const VS_TT_ZOOM_SEL = 19012
Public Const VS_TT_PAGE_DLG = 19015
Public Const VS_TT_PAGE_PREV = 19016
Public Const VS_TT_PAGE_NEXT = 19017
Public Const VS_TT_RESET = 19021
Public Const VS_TT_SHOWGRID = 19022
Public Const VS_TT_SHOWLINEW = 19023
Public Const VS_TT_SHOWFILL = 19024
Public Const VS_TT_TOOL_DIST = 19025
Public Const VS_TT_FMT_LAYOUT = 19029
Public Const VS_TT_FMT_STDIM = 19030
Public Const VS_TT_FMT_LAYER = 19031
Public Const VS_TT_EDIT_UNDO = 19032
Public Const VS_TT_EDIT_REDO = 19033
Public Const VS_TT_EDIT_CBCUT = 19034
Public Const VS_TT_EDIT_CBCOPY = 19035
Public Const VS_TT_EDIT_CBPASTE = 19036
Public Const VS_TT_EDIT_ENTPROP = 19037
Public Const VS_TT_EDIT_COPY = 19038
Public Const VS_TT_EDIT_MOVE = 19039
Public Const VS_TT_EDIT_ROTATE = 19040
Public Const VS_TT_EDIT_SCALE = 19041
Public Const VS_TT_EDIT_MIRROR = 19042
Public Const VS_TT_EDIT_ERASE = 19043
Public Const VS_TT_EDIT_EXPLODE = 19044
Public Const VS_TT_EDIT_CREBLOCK = 19045
Public Const VS_TT_DRAW_POINT = 19051
Public Const VS_TT_DRAW_LINE = 19052
Public Const VS_TT_DRAW_POLYLINE = 19053
Public Const VS_TT_DRAW_SPLINE = 19054
Public Const VS_TT_DRAW_CIRC_CR = 19055
Public Const VS_TT_DRAW_CIRC_3P = 19056
Public Const VS_TT_DRAW_ARC_CSE = 19057
Public Const VS_TT_DRAW_ARC_SME = 19058
Public Const VS_TT_DRAW_ELLIPSE = 19059
Public Const VS_TT_DRAW_RECT = 19060
Public Const VS_TT_DRAW_HATCH = 19061
Public Const VS_TT_DRAW_TEXT = 19062
Public Const VS_TT_DRAW_SYMBOL = 19063
Public Const VS_TT_DRAW_BLOCK = 19064
Public Const VS_TT_DRAW_IMAGE = 19065
Public Const VS_TT_DRAW_FLOOD = 19066
Public Const VS_TT_DRAW_DIM_HOR = 19071
Public Const VS_TT_DRAW_DIM_VER = 19072
Public Const VS_TT_DRAW_DIM_PAR = 19073
Public Const VS_TT_DRAW_DIM_ANG = 19074
Public Const VS_TT_DRAW_DIM_RAD = 19075
Public Const VS_TT_DRAW_DIM_DIAM = 19076
Public Const VS_TT_DRAW_DIM_ORD = 19077
Public Const VS_TT_SNAP_END = 19101
Public Const VS_TT_SNAP_MID = 19102
Public Const VS_TT_SNAP_INTER = 19103
Public Const VS_TT_SNAP_CEN = 19104
Public Const VS_TT_SNAP_KNOT = 19105
Public Const VS_TT_SNAP_PERP = 19106
Public Const VS_TT_SNAP_TANG = 19107
Public Const VS_TT_SNAP_POINT = 19108
Public Const VS_TT_SNAP_NEAR = 19109
Public Const VS_TT_SNAP_GRID = 19110
Public Const VS_TT_SNAP_POLAR = 19111
Public Const VS_TT_SNAP_CLEAR = 19112
Public Const VS_TT_SNAP_DLG = 19113

Public Const VS_CC_ZOOMWIN = 19201
Public Const VS_CC_ZOOMPAN = 19202
Public Const VS_CC_PRINT = 19203
Public Const VS_CC_PRNRECT = 19204
Public Const VS_CC_EXPBMP = 19205
Public Const VS_CC_POINT = 19206
Public Const VS_CC_LINE = 19207
Public Const VS_CC_CIRCLE = 19208
Public Const VS_CC_ARC = 19209
Public Const VS_CC_SECTOR = 19210
Public Const VS_CC_ELLIPSE = 19211
Public Const VS_CC_POLYLINE = 19212
Public Const VS_CC_TEXT = 19213
Public Const VS_CC_INSERT = 19214
Public Const VS_CC_HATCH = 19215
Public Const VS_CC_BITMAP = 19216
Public Const VS_CC_SYMBOL = 19217
Public Const VS_CC_RECT = 19218
Public Const VS_CC_DIMHOR = 19219
Public Const VS_CC_DIMVER = 19220
Public Const VS_CC_DIMPAR = 19221
Public Const VS_CC_DIMANG = 19222
Public Const VS_CC_DIMRAD = 19223
Public Const VS_CC_DIMDIAM = 19224
Public Const VS_CC_DIMORD = 19225
Public Const VS_CC_SELBYPOINT = 19226
Public Const VS_CC_SELBYRECT = 19227
Public Const VS_CC_SELBYPOLYGON = 19228
Public Const VS_CC_SELBYPOLYLINE = 19229
Public Const VS_CC_SELBYDIST = 19230
Public Const VS_CC_MOVEGRIP = 19231
Public Const VS_CC_ENTPROP = 19232
Public Const VS_CC_MOVE = 19233
Public Const VS_CC_COPY = 19234
Public Const VS_CC_ROTATE = 19235
Public Const VS_CC_SCALE = 19236
Public Const VS_CC_MIRROR = 19237
Public Const VS_CC_ERASE = 19238
Public Const VS_CC_CREBLOCK = 19239
Public Const VS_CC_EXPLODE = 19240
Public Const VS_CC_SPLINE = 19241
Public Const VS_CC_DIST = 19242
Public Const VS_CC_INSVEC = 19243
Public Const VS_CC_ENTSWAP = 19244
Public Const VS_CC_ENTTOTOP = 19245
Public Const VS_CC_ENTTOBOTTOM = 19246

Public Const VS_SELOBJECTS = 19301
Public Const VS_CORNER1 = 19302
Public Const VS_CORNER2 = 19303
Public Const VS_BASE_P = 19304
Public Const VS_BASE_P1 = 19305
Public Const VS_BASE_P2 = 19306
Public Const VS_DISPLACE = 19307
Public Const VS_POINT1 = 19308
Public Const VS_POINT2 = 19309
Public Const VS_POINT3 = 19310
Public Const VS_CENTER_P = 19311
Public Const VS_RAD_P = 19312
Public Const VS_START_P = 19313
Public Const VS_END_P = 19314
Public Const VS_RAD1ANG = 19315
Public Const VS_RAD2 = 19316
Public Const VS_NEXT_P = 19317
Public Const VS_INS_P = 19318
Public Const VS_LEADER1 = 19319
Public Const VS_LEADER2 = 19320
Public Const VS_TEXT_P = 19321
Public Const VS_ORD_P = 19322
Public Const VS_ORD_X = 19323
Public Const VS_ORD_Y = 19324
Public Const VS_MOVE2 = 19325
Public Const VS_COPY2 = 19326
Public Const VS_ROTATE1 = 19327
Public Const VS_ROTATE2 = 19328
Public Const VS_ROTATE3 = 19329
Public Const VS_SCALE3 = 19330
Public Const VS_MIRROR1 = 19331
Public Const VS_MIRROR2 = 19332
Public Const VS_PICK_ENT = 19333
Public Const VS_PICK_ENT1 = 19334
Public Const VS_PICK_ENT2 = 19335

Public Const VS_PAPER_UNLIMITED = 19401
Public Const VS_PAPER_A0 = 19402
Public Const VS_PAPER_A1 = 19403
Public Const VS_PAPER_A2 = 19404
Public Const VS_PAPER_A3 = 19405
Public Const VS_PAPER_A4 = 19406
Public Const VS_PAPER_A5 = 19407
Public Const VS_PAPER_A6 = 19408
Public Const VS_PAPER_B0 = 19409
Public Const VS_PAPER_B1 = 19410
Public Const VS_PAPER_B2 = 19411
Public Const VS_PAPER_B3 = 19412
Public Const VS_PAPER_B4 = 19413
Public Const VS_PAPER_B5 = 19414
Public Const VS_PAPER_B6 = 19415
Public Const VS_PAPER_C0 = 19416
Public Const VS_PAPER_C1 = 19417
Public Const VS_PAPER_C2 = 19418
Public Const VS_PAPER_C3 = 19419
Public Const VS_PAPER_C4 = 19420
Public Const VS_PAPER_C5 = 19421
Public Const VS_PAPER_C6 = 19422
Public Const VS_PAPER_ANSI_A = 19423
Public Const VS_PAPER_ANSI_B = 19424
Public Const VS_PAPER_ANSI_C = 19425
Public Const VS_PAPER_ANSI_D = 19426
Public Const VS_PAPER_ANSI_E = 19427
Public Const VS_PAPER_LETTER = 19428
Public Const VS_PAPER_LEGAL = 19429
Public Const VS_PAPER_EXECUTIVE = 19430
Public Const VS_PAPER_LEDGER = 19431
Public Const VS_PAPER_USER = 19432


'********************************************************************
' VeCAD types
'********************************************************************

' VeCAD point
Type VLPOINT
  X As Double
  Y As Double
End Type


' VeCAD arc
Type VLARC
  Cen As VLPOINT
  Rh As Double
  Rv As Double
  Ang0 As Double
  AngArc As Double
  AngRot As Double
End Type


' Window Rectangle
Type RECT
    Left As Long
    Top As Long
    Right As Long
    Bottom As Long
End Type

' used to pass parameters with VM_BEGINPAINT message
Type VLPAINTSTRUCT
    dc As Object        ' output device context
    rcPaint As RECT     ' output window rectangle
    DwgLeft As Double   ' drawing's limits for the window
    DwgBottom As Double
    DwgRight As Double
    DwgTop As Double
    ScaleX As Double    ' horiz. scale, mm/pixel
    ScaleY As Double    ' vert. scale, mm/pixel
End Type

' Properties of "Navigator" window (aerial view)
Type VLNAVIGATOR
  Left As Long
  Top As Long
  Width As Long
  Height As Long
  ColorZoomRect As Long
  Realtime As Long
End Type

' Properties of "Layers Manager" window
Type VLLAYWIN
  Left As Long
  Top As Long
  Width As Long
  Height As Long
End Type


'********************************************************************
' VeCAD functions
'********************************************************************

Public Declare Function vlGetVersion Lib "vecad52.dll" () As Long

' Registration for user copy of VeCAD DLL
Public Declare Function vlRegistration Lib "vecad52.dll" (ByVal RegCode As Long) As Boolean

' Set application-defined function that will receive messages from VeCAD
Public Declare Function vlSetMsgHandler Lib "vecad52.dll" (ByVal pfDwgProc As Any) As Boolean

'/////////////////////////////////////////////////
'// VeCAD window functions
Public Declare Function vlWndCreate Lib "vecad52.dll" (ByVal hWndParent As Long, ByVal Style As Long, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long) As Long
Public Declare Function vlWndResize Lib "vecad52.dll" (ByVal hwnd As Long, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long) As Boolean
Public Declare Function vlWndSetTitle Lib "vecad52.dll" (ByVal hwnd As Long, ByVal Title As String) As Boolean
Public Declare Function vlWndSetMaxRect Lib "vecad52.dll" (ByVal hwnd As Long, ByRef pRect As RECT) As Boolean
Public Declare Function vlWndSetCursor Lib "vecad52.dll" (ByVal hwnd As Long, ByVal hCursor As Long) As Boolean

'/////////////////////////////////////////////////
'// Drawing object functions
Public Declare Function vlDocCreate Lib "vecad52.dll" (ByVal hwVec As Long) As Long
Public Declare Function vlDocDelete Lib "vecad52.dll" (ByVal iDwg As Long) As Boolean
Public Declare Function vlDocSetActive Lib "vecad52.dll" (ByVal iDwg As Long) As Long
Public Declare Function vlDocGetActive Lib "vecad52.dll" () As Long
Public Declare Function vlDocCopy Lib "vecad52.dll" (ByVal iDwgSrc As Long, ByVal iDwgDest As Long, ByVal Mode As Long) As Boolean


'/////////////////////////////////////////////////
'// All Next functions work with current drawing that
'// are set by vlDwgSetCurrent function

'/////////////////////////////////////////////////
'// Layout (pages,layers, text styles, etc...
'// Parameters can be accessed via vlData...

Public Declare Function vlPageAdd Lib "vecad52.dll" (ByVal Name As String, ByVal Size As Long, ByVal Orient As Long, ByVal W As Long, ByVal H As Long) As Long
Public Declare Function vlPageDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlPageActive Lib "vecad52.dll" (ByVal Mode As Long, ByVal Index As Long) As Long
Public Declare Function vlPageCount Lib "vecad52.dll" () As Long
Public Declare Function vlPageIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlLayerAdd Lib "vecad52.dll" (ByVal Name As String, ByVal LineWidth As Double, ByVal LineColor As Long, ByVal FillColor As Long) As Long
Public Declare Function vlLayerDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlLayerActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlLayerCount Lib "vecad52.dll" () As Long
Public Declare Function vlLayerIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlStLineAdd Lib "vecad52.dll" (ByVal Name As String, ByVal Desc As String) As Long
Public Declare Function vlStLineDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlStLineActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlStLineCount Lib "vecad52.dll" () As Long
Public Declare Function vlStLineIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlStTextAdd Lib "vecad52.dll" (ByVal Name As String, ByVal Font As String, ByVal Width As Double, ByVal Oblique As Double, ByVal Prec As Long, ByVal Filled As Boolean, ByVal Bold As Boolean) As Long
Public Declare Function vlStTextDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlStTextActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlStTextCount Lib "vecad52.dll" () As Long
Public Declare Function vlStTextIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long
Public Declare Function vlStTextReload Lib "vecad52.dll" () As Boolean

Public Declare Function vlStHatchAdd Lib "vecad52.dll" (ByVal Name As String, ByVal Desc As String) As Long
Public Declare Function vlStHatchDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlStHatchActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlStHatchCount Lib "vecad52.dll" () As Long
Public Declare Function vlStHatchIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlStDimAdd Lib "vecad52.dll" (ByVal Name As String) As Long
Public Declare Function vlStDimDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlStDimActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlStDimCount Lib "vecad52.dll" () As Long
Public Declare Function vlStDimIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlStPointAdd Lib "vecad52.dll" (ByVal Name As String) As Long
Public Declare Function vlStPointDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlStPointActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlStPointCount Lib "vecad52.dll" () As Long
Public Declare Function vlStPointIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlGrPointAdd Lib "vecad52.dll" (ByVal Name As String) As Long
Public Declare Function vlGrPointDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlGrPointActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlGrPointCount Lib "vecad52.dll" () As Long
Public Declare Function vlGrPointIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlViewSave Lib "vecad52.dll" (ByVal Name As String) As Long
Public Declare Function vlViewDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlViewRestore Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlViewCount Lib "vecad52.dll" () As Long
Public Declare Function vlViewIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long

Public Declare Function vlPrnRectAdd Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal W As Double, ByVal H As Double, ByVal Angle As Double) As Long
Public Declare Function vlPrnRectDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlPrnRectCount Lib "vecad52.dll" () As Long
Public Declare Function vlPrnRectPrint Lib "vecad52.dll" (ByVal Index As Long, ByVal hPrintDC As Long, ByVal ScaleX As Double, ByVal ScaleY As Double, ByVal OriginX As Double, ByVal OriginY As Double) As Boolean
Public Declare Function vlPrnRectAuto Lib "vecad52.dll" (ByVal Width As Double, ByVal Height As Double) As Long

Public Declare Function vlBlockBegin Lib "vecad52.dll" () As Boolean
Public Declare Function vlBlockAdd Lib "vecad52.dll" (ByVal Name As String, ByVal X As Double, ByVal Y As Double) As Long
Public Declare Function vlBlockAddF Lib "vecad52.dll" (ByVal FileName As String, ByVal BlockName As String) As Long
Public Declare Function vlBlockDelete Lib "vecad52.dll" (ByVal Index As Long) As Boolean
Public Declare Function vlBlockActive Lib "vecad52.dll" (ByVal Index As Long) As Long
Public Declare Function vlBlockCount Lib "vecad52.dll" () As Long
Public Declare Function vlBlockIndex Lib "vecad52.dll" (ByVal Name As String, ByVal ID As Long) As Long


'/////////////////////////////////////////////////
'// Add Graphic objects to drawing
Public Declare Function vlAddPoint Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double) As Long
Public Declare Function vlAddLine Lib "vecad52.dll" (ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double) As Long
Public Declare Function vlAddArcEx Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Rh As Double, ByVal Rv As Double, ByVal Ang0 As Double, ByVal AngArc As Double, ByVal AngRot As Double) As Long
Public Declare Function vlAddCircle Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Rad As Double) As Long
Public Declare Function vlAddCircle3P Lib "vecad52.dll" (ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double, ByVal X3 As Double, ByVal Y3 As Double) As Long
Public Declare Function vlAddArc Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Rad As Double, ByVal Ang1 As Double, ByVal Ang2 As Double) As Long
Public Declare Function vlAddArc3P Lib "vecad52.dll" (ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double, ByVal X3 As Double, ByVal Y3 As Double) As Long
Public Declare Function vlAddEllipse Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Rh As Double, ByVal Rv As Double, ByVal Ang As Double) As Long
Public Declare Function vlSetTextParam Lib "vecad52.dll" (ByVal Mode As Long, ByVal Var As Double) As Boolean
Public Declare Function vlSetTextParams Lib "vecad52.dll" (ByVal Align As Long, ByVal H As Double, ByVal Ang As Double, ByVal ScaleW As Double, ByVal Oblique As Double, ByVal HInter As Double, ByVal VInter As Double) As Boolean
Public Declare Function vlAddText Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Text As String) As Long
Public Declare Function vlPolylineBegin Lib "vecad52.dll" () As Boolean
Public Declare Function vlVertex Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double) As Boolean
Public Declare Function vlVertexR Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Radius As Double) As Boolean
Public Declare Function vlVertexF Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal bOnCurve As Boolean) As Boolean
Public Declare Function vlVertexB Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Bulge As Double) As Boolean
Public Declare Function vlAddPolyline Lib "vecad52.dll" (ByVal SmoothType As Long, ByVal bClosed As Boolean) As Long
Public Declare Function vlAddBlockIns Lib "vecad52.dll" (ByVal Index As Long, ByVal X As Double, ByVal Y As Double, ByVal Ang As Double, ByVal Xscale As Double, ByVal Yscale As Double) As Long
Public Declare Function vlAddHatch Lib "vecad52.dll" (ByVal Index As Long, ByVal Scal As Double, ByVal Ang As Double) As Long
Public Declare Function vlAddRaster Lib "vecad52.dll" (ByVal FileName As String, ByVal X As Double, ByVal Y As Double, ByVal ResH As Double, ByVal ResV As Double) As Long
Public Declare Function vlAddRect Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal W As Double, ByVal H As Double, ByVal Ang As Double, ByVal Rad As Double) As Long
Public Declare Function vlAddDimHor Lib "vecad52.dll" (ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double, ByVal Y As Double) As Long
Public Declare Function vlAddDimVer Lib "vecad52.dll" (ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double, ByVal X As Double) As Long
Public Declare Function vlAddDimPar Lib "vecad52.dll" (ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double, ByVal Off As Double) As Long
Public Declare Function vlAddDimAng Lib "vecad52.dll" (ByVal Xcen As Double, ByVal Ycen As Double, ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double, ByVal Off As Double) As Long
Public Declare Function vlAddDimRad Lib "vecad52.dll" (ByVal Xcen As Double, ByVal Ycen As Double, ByVal Xrad As Double, ByVal Yrad As Double, ByVal Off As Double) As Long
Public Declare Function vlAddDimDiam Lib "vecad52.dll" (ByVal Xcen As Double, ByVal Ycen As Double, ByVal Xrad As Double, ByVal Yrad As Double) As Long
Public Declare Function vlAddDimOrd Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Xtxt As Double, ByVal Ytxt As Double, ByVal bYord As Boolean) As Long
Public Declare Function vlAddDwgIns Lib "vecad52.dll" (ByVal FileName As String, ByVal X As Double, ByVal Y As Double, ByVal Angle As Double, ByVal ScaleX As Double, ByVal ScaleY As Double, ByVal iPage As Long) As Long
Public Declare Function vlAddCustom Lib "vecad52.dll" (ByVal ObjType As Long, ByVal pData As Any, ByVal DataSize As Long, ByVal ElemSize As Long) As Boolean


'/////////////////////////////////////////////////
'// Drawing's storage
Public Declare Function vlFileNew Lib "vecad52.dll" (ByVal hwVec As Long, ByVal Template As String) As Long
Public Declare Function vlFileOpen Lib "vecad52.dll" (ByVal hwVec As Long, ByVal FileName As String) As Long
Public Declare Function vlFileLoad Lib "vecad52.dll" (ByVal Mode As Long, ByVal FileName As String) As Boolean
Public Declare Function vlFileSave Lib "vecad52.dll" (ByVal Mode As Long, ByVal FileName As String) As Boolean
Public Declare Function vlFileList Lib "vecad52.dll" (ByVal hwParent As Long) As Boolean
Public Declare Function vlFileLoadMem Lib "vecad52.dll" (ByVal pData As Any) As Boolean
Public Declare Function vlFileSaveMem Lib "vecad52.dll" (ByVal pData As Any, ByVal MaxSize As Long) As Long

'/////////////////////////////////////////////////
'// Select objects for edit functions
Public Declare Function vlGetEntity Lib "vecad52.dll" (ByVal Mode As Long, ByVal Prm1 As Long, ByVal Prm2 As Long) As Long
Public Declare Function vlGetBlockEntity Lib "vecad52.dll" (ByVal iBlock As Long, ByVal Counter As Long) As Long
Public Declare Function vlSelect Lib "vecad52.dll" (ByVal Sel As Boolean, ByVal Index As Long) As Boolean
Public Declare Function vlSelectByPoint Lib "vecad52.dll" (ByVal Sel As Boolean, ByVal X As Double, ByVal Y As Double, ByVal Delta As Double) As Long
Public Declare Function vlSelectByRect Lib "vecad52.dll" (ByVal Sel As Boolean, ByVal Left As Double, ByVal Bottom As Double, ByVal Right As Double, ByVal Top As Double, ByVal Cross As Boolean) As Long
Public Declare Function vlSelectByPolygon Lib "vecad52.dll" (ByVal Sel As Boolean, Ver As VLPOINT, ByVal Nver As Long, ByVal Cross As Boolean) As Long
Public Declare Function vlSelectByPolyline Lib "vecad52.dll" (ByVal Sel As Boolean, Ver As VLPOINT, ByVal Nver As Long) As Long
Public Declare Function vlSelectByDist Lib "vecad52.dll" (ByVal Sel As Boolean, ByVal X As Double, ByVal Y As Double, ByVal Dist As Double, ByVal Cross As Boolean) As Long

'/////////////////////////////////////////////////
'// Edit functions
'// iObj - index of the object,
'// if iObj=-1 then operate with selected objects
Public Declare Function vlCbCut Lib "vecad52.dll" () As Boolean
Public Declare Function vlCbCopy Lib "vecad52.dll" () As Boolean
Public Declare Function vlCbPaste Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double) As Boolean
Public Declare Function vlCopy Lib "vecad52.dll" (ByVal iObj As Long, ByVal dx As Double, ByVal dy As Double) As Long
Public Declare Function vlMove Lib "vecad52.dll" (ByVal iObj As Long, ByVal dx As Double, ByVal dy As Double) As Boolean
Public Declare Function vlRotate Lib "vecad52.dll" (ByVal iObj As Long, ByVal X As Double, ByVal Y As Double, ByVal Ang As Double) As Boolean
Public Declare Function vlScale Lib "vecad52.dll" (ByVal iObj As Long, ByVal X As Double, ByVal Y As Double, ByVal Scal As Double) As Boolean
Public Declare Function vlMirror Lib "vecad52.dll" (ByVal iObj As Long, ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double) As Boolean
Public Declare Function vlErase Lib "vecad52.dll" (ByVal iObj As Long) As Boolean
Public Declare Function vlExplode Lib "vecad52.dll" (ByVal iObj As Long) As Boolean
Public Declare Function vlJoin Lib "vecad52.dll" (ByVal Delta As Double) As Boolean
Public Declare Function vlUndo Lib "vecad52.dll" () As Boolean
Public Declare Function vlRedo Lib "vecad52.dll" () As Boolean
Public Declare Function vlPolyVerInsert Lib "vecad52.dll" (ByVal iEnt As Long, ByVal iVer As Long) As Boolean
Public Declare Function vlPolyVerDelete Lib "vecad52.dll" (ByVal iEnt As Long, ByVal iVer As Long) As Boolean
Public Declare Function vlPolyVerGet Lib "vecad52.dll" (ByVal iEnt As Long, ByVal iVer As Long, ByRef pX As Double, ByRef pY As Double, ByRef pPrm As Double) As Boolean
Public Declare Function vlPolyVerSet Lib "vecad52.dll" (ByVal iEnt As Long, ByVal iVer As Long, ByVal X As Double, ByVal Y As Double, ByVal Prm As Double) As Boolean
Public Declare Function vlGripGet Lib "vecad52.dll" (ByVal iObj As Long, ByVal iGrip As Long, ByRef X As Double, ByRef Y As Double)
Public Declare Function vlGripSet Lib "vecad52.dll" (ByVal iObj As Long, ByVal iGrip As Long, ByVal X As Double, ByVal Y As Double)
Public Declare Function vlGripMove Lib "vecad52.dll" (ByVal iObj As Long, ByVal iGrip As Long, ByVal dx As Double, ByVal dy As Double) As Boolean

'/////////////////////////////////////////////////
'// Access to objects properties
Public Declare Function vlPropGet Lib "vecad52.dll" (ByVal Key As Long, ByVal iObj As Long, ByVal pData As Any) As Long
Public Declare Function vlPropGetInt Lib "vecad52.dll" (ByVal Key As Long, ByVal iObj As Long) As Long
Public Declare Function vlPropGetDbl Lib "vecad52.dll" (ByVal Key As Long, ByVal iObj As Long) As Double
Public Declare Function vlPropPut Lib "vecad52.dll" (ByVal Key As Long, ByVal iObj As Long, ByVal pData As Any) As Long
Public Declare Function vlPropPutInt Lib "vecad52.dll" (ByVal Key As Long, ByVal iObj As Long, ByVal Data As Long) As Long
Public Declare Function vlPropPutDbl Lib "vecad52.dll" (ByVal Key As Long, ByVal iObj As Long, ByVal Data As Double) As Long

'/////////////////////////////////////////////////
'// Zooming drawing in a window
Public Declare Function vlZoom Lib "vecad52.dll" (ByVal Scal As Double) As Boolean
Public Declare Function vlZoomRect Lib "vecad52.dll" (ByVal Left As Double, ByVal Bottom As Double, ByVal Right As Double, ByVal Top As Double) As Boolean
Public Declare Function vlZoomPan Lib "vecad52.dll" (ByVal dx As Double, ByVal dy As Double) As Boolean

'/////////////////////////////////////////////////
'// Coordinates convertions
Public Declare Function vlCoordWinToDwg Lib "vecad52.dll" (ByVal Xwin As Long, ByVal Ywin As Long, ByRef pXdwg As Double, ByRef pYdwg As Double) As Boolean
Public Declare Function vlCoordDwgToWin Lib "vecad52.dll" (ByVal Xdwg As Double, ByVal Ydwg As Double, ByRef pXwin As Long, ByRef pYwin As Long) As Boolean
Public Declare Function vlLenWinToDwg Lib "vecad52.dll" (ByVal Lwin As Long, ByRef pLdwg As Double) As Boolean
Public Declare Function vlLenDwgToWin Lib "vecad52.dll" (ByVal Ldwg As Double, ByRef pLwin As Long) As Boolean


'/////////////////////////////////////////////////
'// draw graphics primitives
Public Declare Function vlSetDrawPen Lib "vecad52.dll" (ByVal Width As Double, ByVal Color As Long) As Boolean
Public Declare Function vlDrawPoint Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Typ As Long, ByVal Size As Long) As Boolean
Public Declare Function vlDrawLine Lib "vecad52.dll" (ByVal X1 As Double, ByVal Y1 As Double, ByVal X2 As Double, ByVal Y2 As Double) As Boolean
Public Declare Function vlDrawPolyline Lib "vecad52.dll" (Ver As VLPOINT, ByVal Nver As Long, ByVal bClosed As Boolean) As Boolean
Public Declare Function vlDrawPolygon Lib "vecad52.dll" (Ver As VLPOINT, ByVal Nver As Long, ByVal Fill As Boolean, ByVal Border As Boolean, ByVal FillColor As Long) As Boolean
Public Declare Function vlDrawCircle Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Rad As Double) As Boolean
Public Declare Function vlDrawArc Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Rad As Double, ByVal Ang1 As Double, ByVal Ang2 As Double) As Boolean
Public Declare Function vlDrawEllipse Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Rh As Double, ByVal Rv As Double, ByVal Ang As Double) As Boolean
Public Declare Function vlDrawText Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double, ByVal Text As String) As Boolean
Public Declare Function vlDrawBitmap Lib "vecad52.dll" (ByVal HBitmap As Long, ByVal W As Long, ByVal H As Long, ByVal X As Double, ByVal Y As Double, ByVal ResX As Double, ByVal ResY As Double) As Boolean
Public Declare Function vlDrawEntity Lib "vecad52.dll" (ByVal Index As Long, ByVal Xbase As Double, ByVal Ybase As Double, ByVal Xins As Double, ByVal Yins As Double, ByVal Angle As Double, ByVal ScaleX As Double, ByVal ScaleY As Double) As Boolean


'/////////////////////////////////////////////////
'// misc
Public Declare Function vlExecute Lib "vecad52.dll" (ByVal IdCmd As Long) As Boolean
Public Declare Function vlSetAccKey Lib "vecad52.dll" (ByVal IdCmd As Long, ByVal VirtKey As Long, ByVal Flags As Long) As Boolean
Public Declare Function vlClear Lib "vecad52.dll" (ByVal bSetDefLayout As Boolean) As Boolean
Public Declare Function vlSetFocus Lib "vecad52.dll" () As Boolean
Public Declare Function vlUpdate Lib "vecad52.dll" () As Boolean
Public Declare Function vlRedraw Lib "vecad52.dll" () As Boolean
Public Declare Function vlReset Lib "vecad52.dll" () As Boolean
Public Declare Function vlPrintSetup Lib "vecad52.dll" (ByVal hParent As Long) As Boolean
Public Declare Function vlPrint Lib "vecad52.dll" (ByVal hPrintDC As Long, ByVal Left As Double, ByVal Bottom As Double, ByVal Right As Double, ByVal Top As Double, ByVal ScaleX As Double, ByVal ScaleY As Double, ByVal OriginX As Double, ByVal OriginY As Double) As Boolean
Public Declare Function vlDoRaster Lib "vecad52.dll" (ByVal FileName As String, ByVal Left As Double, ByVal Bottom As Double, ByVal Right As Double, ByVal Top As Double, ByVal Res As Double) As Boolean
Public Declare Function vlGetWinSize Lib "vecad52.dll" (ByVal hwnd As Long, ByRef pWidth As Long, ByRef pHeight As Long) As Boolean
Public Declare Function vlSetTimer Lib "vecad52.dll" (ByVal ID As Long, ByVal Elapse As Long) As Boolean
Public Declare Function vlKillTimer Lib "vecad52.dll" (ByVal ID As Long) As Boolean
Public Declare Function vlGetArea Lib "vecad52.dll" (ByVal X As Double, ByVal Y As Double) As Double

'/////////////////////////////////////////////////
' Additional VeCAD controls

' Toolbar
Public Declare Function vlToolBarCreate Lib "vecad52.dll" (ByVal hWndParent As Long, ByVal ID As Long, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long, ByRef pW As Long, ByRef pH As Long) As Long
Public Declare Function vlToolBarButton Lib "vecad52.dll" (ByVal ID As Long) As Boolean
' Statusbar
Public Declare Function vlStatBarCreate Lib "vecad52.dll" (ByVal hWndParent As Long, ByRef pH As Long) As Long
Public Declare Function vlStatBarResize Lib "vecad52.dll" () As Boolean
Public Declare Function vlStatBarSetText Lib "vecad52.dll" (ByVal iPart As Long, ByVal Text As String) As Boolean
' Progress indicator
Public Declare Function vlIndicCreate Lib "vecad52.dll" (ByVal hWndParent As Long, ByVal Title As String) As Boolean
Public Declare Function vlIndicDestroy Lib "vecad52.dll" () As Boolean
Public Declare Function vlIndicSetRange Lib "vecad52.dll" (ByVal nFrom As Long, ByVal nTo As Long) As Boolean
Public Declare Function vlIndicSetPos Lib "vecad52.dll" (ByVal iPos As Long) As Boolean
Public Declare Function vlIndicSetText Lib "vecad52.dll" (ByVal Text As String) As Boolean
Public Declare Function vlIndicStep Lib "vecad52.dll" () As Boolean
' "Navigator" window
Public Declare Function vlNavCreate Lib "vecad52.dll" (ByVal hWndParent As Long, ByVal hVecWnd As Long, ByVal Style As Long, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long) As Long
Public Declare Function vlNavResize Lib "vecad52.dll" (ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long) As Boolean
Public Declare Function vlNavUpdate Lib "vecad52.dll" () As Boolean
Public Declare Function vlNavGetProp Lib "vecad52.dll" (ByRef Prop As VLNAVIGATOR) As Boolean
Public Declare Function vlNavPutProp Lib "vecad52.dll" (ByRef Prop As VLNAVIGATOR) As Boolean
' "Layers Manager" window
Public Declare Function vlLayWinCreate Lib "vecad52.dll" (ByVal hWndParent As Long, ByVal Style As Long, ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long) As Long
Public Declare Function vlLayWinResize Lib "vecad52.dll" (ByVal X As Long, ByVal Y As Long, ByVal W As Long, ByVal H As Long) As Boolean
Public Declare Function vlLayWinGetProp Lib "vecad52.dll" (ByRef Prop As VLLAYWIN) As Boolean
Public Declare Function vlLayWinPutProp Lib "vecad52.dll" (ByRef Prop As VLLAYWIN) As Boolean
' Set order of entities
Public Declare Function vlEntSwap Lib "vecad52.dll" (ByVal iEnt1 As Long, ByVal iEnt2 As Long) As Boolean
Public Declare Function vlEntToTop Lib "vecad52.dll" (ByVal iEnt As Long) As Boolean
Public Declare Function vlEntToBottom Lib "vecad52.dll" (ByVal iEnt As Long) As Boolean

