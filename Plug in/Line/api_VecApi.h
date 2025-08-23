/********************************************************************
* VeCAD version 5.2.10
* Copyright (c) 1999-2001 by Oleg Kolbaskin.
* All rights reserved.
*
* This file must be included in C++ project 
* that used library VeCad.dll
********************************************************************/
#ifndef VECAPI_H
#define VECAPI_H

#define VL_FALSE   0
#define VL_TRUE    1

// VeCAD window styles (vlWndCreate)
#define VL_WS_CHILD   1
#define VL_WS_TILED   2
#define VL_WS_BORDER  4
#define VL_WS_SCROLL  8
#define VL_WS_DEFAULT VL_WS_CHILD|VL_WS_SCROLL

/////////////////////////////////////////////////
// VeCAD objects
#define VL_OBJ_PAGE      1
#define VL_OBJ_LAYER     2
#define VL_OBJ_STLINE    3
#define VL_OBJ_MLINE     4
#define VL_OBJ_STTEXT    5
#define VL_OBJ_STHATCH   6
#define VL_OBJ_STDIM     7
#define VL_OBJ_STPOINT   8
#define VL_OBJ_GRPOINT   9
#define VL_OBJ_VIEW      10
#define VL_OBJ_PRNRECT   11
#define VL_OBJ_BLOCK     12

#define VL_ENT_POINT     21   // Point
#define VL_ENT_LINE      22   // Line
#define VL_ENT_POLY      23   // Polyline
#define VL_ENT_POLYLINE  23   // 
#define VL_ENT_CIRCLE    24   // Circle
#define VL_ENT_ARC       25   // Circular Arc
#define VL_ENT_ARC2      26   // General Arc
#define VL_ENT_EARC      26   // Elliptical Arc
#define VL_ENT_ELLIPSE   27   // Ellipse
#define VL_ENT_TEXT      28   // Text
#define VL_ENT_BITMAP    29   // Raster image
#define VL_ENT_INSBLOCK  30   // Block's insertion
#define VL_ENT_BLOCKINS  30   //
#define VL_ENT_HATCH     31   // Hatch
#define VL_ENT_FLOOD     32   // Flood
#define VL_ENT_RECT      34   // Rectangle
#define VL_ENT_DIMLIN    35   // Dimension Linear
#define VL_ENT_DIMANG    36   //   Angular
#define VL_ENT_DIMRAD    37   //   Radius
#define VL_ENT_DIMDIAM   38   //   Diameter
#define VL_ENT_DIMORD    39   //   Ordinate
#define VL_ENT_INSDWG    41   // Drawing's insertion
#define VL_ENT_DWGINS    41   //
#define VL_ENT_CUSTOM    255  // Custom object

// Values for Mode argument of vlGetEntity
#define VL_EI_BYHANDLE   1   // Prm1=ID
#define VL_EI_BYKEY      2   // Prm1=Key
#define VL_EI_BYPOINT    3   // Prm1=X, Prm2=Y
#define VL_EI_BYCURSOR   4   //
#define VL_EI_FIRST      6   //
#define VL_EI_NEXT       7

// Filter type for VL_EI_FIRST
#define VL_DRAWING       0   // All visible entities on active page
#define VL_SELECTION     1   // Selection set

// Start page in "Drawing's Layout" dialog (vlDlgLayout)
#define VL_DPG_LAST     -1
#define VL_DPG_PAGE      0
#define VL_DPG_LAYER     1
#define VL_DPG_STLINE    2
#define VL_DPG_MLINE     3
#define VL_DPG_STTEXT    4
#define VL_DPG_STHATCH   5
#define VL_DPG_BLOCK     6
#define VL_DPG_STPOINT   7
#define VL_DPG_GRID      0
#define VL_DPG_OBJSNAP   1
#define VL_DPG_POLSNAP   2

// IO Indexes for vlLoad and vlSave functions
#define VL_FILE_VEC    1 
#define VL_FILE_DXF    2
#define VL_FILE_CNC    3
#define VL_FILE_HPGL   4 
#define VL_FILE_VDF    5
#define VL_FILE_DWG    6
#define VL_FILE_AVSHP  7
#define VL_FILE_ALL    100  // only for input
// only for output 
#define VL_FILE_CUSTOM 101  
#define VL_FILE_DROPS  102 
#define VL_FILE_LINES  103

// Parameters for vlZoom function
#define VL_ZOOM_ALL      -1
#define VL_ZOOM_IN       -2
#define VL_ZOOM_OUT      -3
#define VL_ZOOM_LEFT     -4
#define VL_ZOOM_RIGHT    -5
#define VL_ZOOM_UP       -6
#define VL_ZOOM_DOWN     -7
#define VL_ZOOM_PAGE     -8
#define VL_ZOOM_PREV     -9
#define VL_ZOOM_SEL      -10

// Color constants
#define VL_COL_BLACK       RGB(   0,   0,   0)  // 000000
#define VL_COL_DIMGRAY     RGB( 105, 105, 105)  // 696969
#define VL_COL_DARKGRAY    RGB( 128, 128, 128)  // 808080
#define VL_COL_GRAY        RGB( 169, 169, 169)  // A9A9A9
#define VL_COL_SILVER      RGB( 192, 192, 192)  // C0C0C0
#define VL_COL_LIGHTGRAY   RGB( 211, 211, 211)  // D3D3D3
#define VL_COL_GAINSBORO   RGB( 220, 220, 220)  // DCDCDC
#define VL_COL_WHITESMOKE  RGB( 245, 245, 245)  // F5F5F5
#define VL_COL_WHITE       RGB( 255, 255, 255)  // FFFFFF
#define VL_COL_RED         RGB( 255,   0,   0)  // FF0000
#define VL_COL_GREEN       RGB(   0, 128,   0)  // 008000
#define VL_COL_BLUE        RGB(   0,   0, 255)  // 0000FF
#define VL_COL_CYAN        RGB(   0, 255, 255)  // 00FFFF
#define VL_COL_MAGENTA     RGB( 255,   0, 255)  // FF00FF
#define VL_COL_YELLOW      RGB( 255, 255,   0)  // FFFF00
#define VL_COL_DARKRED     RGB( 139,   0,   0)  // 8B0000
#define VL_COL_DARKGREEN   RGB(   0, 100,   0)  // 006400
#define VL_COL_DARKBLUE    RGB(   0,   0, 139)  // 00008B
#define VL_COL_DARKCYAN    RGB(   0, 139, 139)  // 008B8B
#define VL_COL_DARKMAGENTA RGB( 139,   0, 139)  // 8B008B
#define VL_COL_BROWN       RGB( 165,  42,  42)  // A52A2A

// page paper size
#define VL_PAPER_UNLIMITED  0
#define VL_PAPER_A0         1
#define VL_PAPER_A1         2
#define VL_PAPER_A2         3
#define VL_PAPER_A3         4
#define VL_PAPER_A4         5
#define VL_PAPER_A5         6
#define VL_PAPER_A6         7
#define VL_PAPER_B0         11
#define VL_PAPER_B1         12
#define VL_PAPER_B2         13
#define VL_PAPER_B3         14
#define VL_PAPER_B4         15
#define VL_PAPER_B5         16
#define VL_PAPER_B6         17
#define VL_PAPER_C0         21
#define VL_PAPER_C1         22
#define VL_PAPER_C2         23
#define VL_PAPER_C3         24
#define VL_PAPER_C4         25
#define VL_PAPER_C5         26
#define VL_PAPER_C6         27
#define VL_PAPER_ANSI_A     31
#define VL_PAPER_ANSI_B     32
#define VL_PAPER_ANSI_C     33
#define VL_PAPER_ANSI_D     34
#define VL_PAPER_ANSI_E     35
#define VL_PAPER_LETTER     36
#define VL_PAPER_LEGAL      37
#define VL_PAPER_EXECUTIVE  38
#define VL_PAPER_LEDGER     39
#define VL_PAPER_USER       255

// paper orientation 
#define VL_PAPER_PORTRAIT     1
#define VL_PAPER_LANDSCAPE    2
#define VL_PAPER_BOOK         1
#define VL_PAPER_ALBUM        2

// Modes of Page select (vlPageIndex)
#define VL_PAGE_POS       0     // go to the page index 
#define VL_PAGE_NEXT      1     // view next page
#define VL_PAGE_PREV      2     // view previous page
#define VL_PAGE_FIRST     3     // go to the first page
#define VL_PAGE_LAST      4     // go to the last page
#define VL_PAGE_NAME      5     // go to page by name
#define VL_PAGE_DLG       6     // select page by dialog

// modes for vlSetTextParam
#define VL_TEXT_ALIGN      1
#define VL_TEXT_HEIGHT     2
#define VL_TEXT_ANGLE      3
#define VL_TEXT_WSCALE     4
#define VL_TEXT_OBLIQUE    5
#define VL_TEXT_HINTER     6
#define VL_TEXT_VINTER     7
#define VL_TEXT_STRIKEOUT  8
#define VL_TEXT_UNDERLINE  9

// text alignment types
#define VL_TA_LEFBOT    0     // to left bottom
#define VL_TA_CENBOT    1     // to center bottom
#define VL_TA_RIGBOT    2     // to right bottom
#define VL_TA_LEFCEN    3     // слева середина
#define VL_TA_CENCEN    4     // по центру базовой линии
#define VL_TA_RIGCEN    5     // по правому краю середина
#define VL_TA_LEFTOP    6     // по левому краю сверху
#define VL_TA_CENTOP    7     // по центру базовой линии сверху
#define VL_TA_RIGTOP    8     // по правому краю сверху

// measurement units
#define VL_UNIT_POINT   1
#define VL_UNIT_MM      2
#define VL_UNIT_CM      3
#define VL_UNIT_INCH    4
#define VL_UNIT_FOOT    5
#define VL_UNIT_YARD    6
#define VL_UNIT_MET     7
#define VL_UNIT_KM      8
#define VL_UNIT_MILE    9
#define VL_UNIT_SEAMILE 10
#define VL_ANG_DEGREE   21
#define VL_ANG_RADIAN   22

// view types for simple point (vlDrawPoint)
#define VL_PNT_DEFAULT  0
#define VL_PNT_CIRCLE   1
#define VL_PNT_RECT     2
#define VL_PNT_GRIP     2
#define VL_PNT_CROSS    3
#define VL_PNT_CROSS45  4
#define VL_PNT_POINT    5
#define VL_PNT_BPIXEL   6
#define VL_PNT_WPIXEL   7
#define VL_PNT_ROMB     8
#define VL_PNT_GRIPM    10
#define VL_PNT_GRIPR    11
#define VL_PNT_KNOT     12
#define VL_PNT_KNOT2    13

// Arrow types
#define VL_ARROW_NONE      0
#define VL_ARROW_2LINE     1
#define VL_ARROW_3LINE     2
#define VL_ARROW_3LINE_S   3
#define VL_ARROW_4LINE     4
#define VL_ARROW_4LINE_S   5
#define VL_ARROW_SLASH     6
#define VL_ARROW_CIRC      7
#define VL_ARROW_CIRC_S    8
#define VL_ARROW_COUNT     9       // count of arrows types

// Polyline flags
#define VL_POLY_LINE       0   // linear polyline (no smooth)
#define VL_POLY_BSPLINE2   1   // quadratic B-spline
#define VL_POLY_BSPLINE3   2   // cubic B-spline
#define VL_POLY_FITBSPL3   3   // fitted cubic B-spline
#define VL_POLY_LINBSPL2   4   // linear/quadratic curve
#define VL_POLY_BEZIER     5   // bezier curve
#define VL_POLY_AUTOBEZIER 6   // bezier curve with auto control points
#define VL_POLY_ROUNDED    7   // rounded vertexes
#define VL_POLY_MULTIRAD   8   // multi-rad curve
#define VL_POLY_BULGE      9   // bulge segments
#define VL_POLY_MAXSMTYPE  9   // max value for smooth type
#define VL_POLY_CUSTOM     128    // custom draw

// type of dimension
#define VL_DIM_HORZ        0  // horizontal
#define VL_DIM_VERT        1  // vertical
#define VL_DIM_PARAL       2  // parallel
#define VL_DIM_ANG         3  // Angular
#define VL_DIM_RAD         4  // Radius
#define VL_DIM_DIAM        5  // Diameter
#define VL_DIM_ORDX        6  // Ordinate X
#define VL_DIM_ORDY        7  // Ordinate Y
// dim. text alignment
#define VL_DIM_TA_ABOVE    0
#define VL_DIM_TA_CENTER   1
#define VL_DIM_TA_BELOW    2

// Coord. Grid types
#define VL_GRID_POINT      0   // point
#define VL_GRID_CROSS      1   // cross
#define VL_GRID_CROSS45    2   // cross 45 degree
#define VL_GRID_LINE       3   // solid line
#define VL_GRID_DOTLINE    4   // dot line
#define VL_GRID_DASHLINE   5   // dash line

// flags for accelerator keys (vlSetAccKey)
#define VL_KEY_CTRL     0x01
#define VL_KEY_SHIFT    0x02

// Object Snap flags 
#define VL_SNAP_END     0x0001
#define VL_SNAP_MID     0x0002
#define VL_SNAP_CENTER  0x0004
#define VL_SNAP_POINT   0x0008
#define VL_SNAP_INTER   0x0010
#define VL_SNAP_NEAR    0x0020
#define VL_SNAP_GRIPS   0x0040
#define VL_SNAP_PERP    0x0100
#define VL_SNAP_TANG    0x0200
#define VL_SNAP_GRID    0x1000
#define VL_SNAP_POLAR   0x2000
#define VL_SNAP_OBJECT  0x0FFF
#define VL_SNAP_REALTIME 0x8000

// Toolbars type (vlToolBarCreate)
#define VL_TB_MAIN      4861
#define VL_TB_DRAW      4862
#define VL_TB_EDIT      4863
#define VL_TB_SNAP      4864

// ComboBox type (for toolbar)
#define VL_CB_LAYER     4871
#define VL_CB_STLINE    4872
#define VL_CB_STTEXT    4873
#define VL_CB_COLOR     4874

// index of statusbar part (vlStatBarSetText)
#define VL_SB_COORD     0
#define VL_SB_CURCMD    1
#define VL_SB_PROMPT    2

// separator types
// used as value for VD_SDECIMAL property
#define VL_SEP_POINT    0
#define VL_SEP_COMMA    1

// constants for "glass piece" object
#define VL_GLASS_DWG_PROP    0x00  
#define VL_GLASS_DWG_STRETCH 0x10  
#define VL_GLASS_DWG_ORIG    0x20  
#define VL_GLASS_DWG_SIZE    0x30  

// Styles of "Navigator" window
#define VL_NAV_CHILD  0
#define VL_NAV_FLOAT  1

// Styles of "Layers manager" window
#define VL_LAYWIN_CHILD  0
#define VL_LAYWIN_FLOAT  1


/////////////////////////////////////////////////
// VeCAD messages, passed to drawing procedure
#define VM_GETSTRING      1
#define VM_ERROR          2
#define VM_ZOOM           3
#define VM_ZOOMMIN        4
#define VM_ZOOMMAX        5
#define VM_BEGINPAINT     6
#define VM_ENDPAINT       7
#define VM_LBPAINT        8
#define VM_OBJADD         11
#define VM_OBJDELETE      12
#define VM_OBJACTIVE      13
#define VM_ENTADD         14
#define VM_ENTDELETE      15
#define VM_ENTSELECT      16
#define VM_ENTUNSELECT    17
#define VM_ENTCOPY        20
#define VM_ENTMOVE        21
#define VM_ENTROTATE      22
#define VM_ENTSCALE       23
#define VM_ENTMIRROR      24
#define VM_ENTERASE       25
#define VM_ENTEXPLODE     26
#define VM_ENTPROPDLG     27
#define VM_ENTINDEX       28
#define VM_KEYDOWN        41
#define VM_MOUSEMOVE      42
#define VM_LBDOWN         43
#define VM_LBDBLCLK       44
#define VM_RBDOWN         45
#define VM_KEYUP          46
#define VM_LBUP           47
#define VM_RBUP           48
#define VM_MBDOWN         49
#define VM_MBUP           50
#define VM_TOOLCREATE     51
#define VM_CMD_CREATE     51
#define VM_TOOLOPEN       52
#define VM_CMD_OPEN       52
#define VM_TOOLCLOSE      53
#define VM_CMD_CLOSE      53
#define VM_TOOLCLICK      54
#define VM_CMD_CLICK      54
#define VM_TOOLDRAG       55
#define VM_CMD_DRAG       55
#define VM_TOOLREDRAW     56
#define VM_CMD_REDRAW     56
#define VM_CANCELTOOL     57
#define VM_CANCELCMD      57
#define VM_REPEATTOOL     58
#define VM_REPEATCMD      58
#define VM_MENUEDIT       61
#define VM_MENUVER        62
#define VM_EXECUTE        100
#define VM_EXECUTED       101  
#define VM_DWGCREATE      102
#define VM_DWGDELETE      103
#define VM_DWGCLEAR       104
#define VM_DWGSELECT      105
#define VM_DWGLOADING     106
#define VM_DWGLOADED      107
#define VM_DWGSAVING      108
#define VM_DWGSAVED       109
#define VM_DWGUPDATE      110
#define VM_PASSWORD       121
#define VM_TIMER          122
#define VM_RASTER         123
#define VM_CLOSEQUERY     124
#define VM_WINRESIZE      125
#define VM_WDWG_CLOSED    126
#define VM_WVIEW_CLOSED   127
#define VM_GRIPSELECT     161
#define VM_GRIPDRAG       162
#define VM_GRIPMOVE       163
#define VM_STATUSTEXT     171

#define VM_EXP___MIN      180
#define VM_EXP_BEGIN      181
#define VM_EXP_END        182
#define VM_EXP_ENTITY     183
#define VM_EXP_MOVETO     184
#define VM_EXP_LINETO     185
#define VM_EXP_ARCTO      186
#define VM_EXP_DROP       187
#define VM_EXP_DROPSIZE   188
#define VM_EXP_COLOR      189
#define VM_EXP_WIDTH      190
#define VM_EXP_LAYER      191
#define VM_EXP_PUMPOFF    192
#define VM_EXP_EXPLODE    193
#define VM_EXP_LINES      195
#define VM_EXP_FILLINGS   196
#define VM_EXP___MAX      200

#define VM_EXP_OPEN       181
#define VM_EXP_CLOSE      182
#define VM_EXP_ENT        183

#define VM_PROP_PRE       251
#define VM_PROP_POST      252

#define VM_NAV_CLOSE      261
#define VM_NAV_DIALOG     262

#define VM_MOUSEWHEEL     271


/////////////////////////////////////////////////
// VeCAD error codes, passed with the VM_ERROR message
#define VL_ERR_OBJADD       1  
#define VL_ERR_OBJDELETE    2  
//#define VL_ERR_OBJPAGEMAX      2
//#define VL_ERR_PAGENONE     3
#define VL_ERR_OBJSELECT    4
#define VL_ERR_LOADVEC      5



/********************************************************************
* VeCAD commands identifiers
********************************************************************/

// File
#define VC_FILE_NEW        17001
#define VC_FILE_OPEN       17002
#define VC_FILE_SAVE       17003
#define VC_FILE_SAVEAS     17004
#define VC_FILE_CLOSE      17005
#define VC_FILE_CLOSEALL   17006
#define VC_FILE_LIST       17007
#define VC_IMPORT_DXF      17011
#define VC_IMPORT_VDF      17012
#define VC_IMPORT_HPGL     17013
#define VC_IMPORT_CNC      17014
#define VC_IMPORT_DP1      17015
#define VC_IMPORT_AVSHP    17016
#define VC_EXPORT_DXF      17021
#define VC_EXPORT_HPGL     17022
#define VC_EXPORT_CNC      17023
#define VC_EXPORT_BMP      17024
#define VC_EXPORT_AVSHP    17025
#define VC_PRINT           17031

// View
#define VC_ZOOM_ALL        17051
#define VC_ZOOM_WIN        17052
#define VC_ZOOM_PAN        17053
#define VC_ZOOM_PAGE       17054
#define VC_ZOOM_IN         17055
#define VC_ZOOM_OUT        17056
#define VC_ZOOM_LEFT       17057
#define VC_ZOOM_RIGHT      17058
#define VC_ZOOM_UP         17059
#define VC_ZOOM_DOWN       17060
#define VC_ZOOM_PREV       17061
#define VC_ZOOM_SEL        17062
#define VC_PAGE_NEXT       17071
#define VC_PAGE_PREV       17072
#define VC_PAGE_FIRST      17073
#define VC_PAGE_LAST       17074
#define VC_PAGE_DLG        17075
#define VC_VIEW_SAVE       17081
#define VC_VIEW_LIST       17082

// Draw
#define VC_DRAW_POINT      17110
#define VC_DRAW_LINE       17120
#define VC_DRAW_POLYLINE   17130
#define VC_DRAW_SPLINE     17131
#define VC_DRAW_CIRC_CR    17140
#define VC_DRAW_CIRC_CD    17141
#define VC_DRAW_CIRC_2P    17142
#define VC_DRAW_CIRC_3P    17143
#define VC_DRAW_CIRC_TTT   17144
#define VC_DRAW_ARC_CSE    17150
#define VC_DRAW_ARC_CSA    17151
#define VC_DRAW_ARC_CSL    17152
#define VC_DRAW_ARC_SEM    17153
#define VC_DRAW_ARC_SME    17154
#define VC_DRAW_ARC_SCE    17155
#define VC_DRAW_ARC_SCA    17156
#define VC_DRAW_ARC_SCL    17157
#define VC_DRAW_ARC_SEA    17158
#define VC_DRAW_ARC_SED    17159
#define VC_DRAW_ARC_SER    17160
#define VC_DRAW_ARC_CONT   17161
#define VC_DRAW_SECTOR     17165
#define VC_DRAW_ELLIPSE    17170
#define VC_DRAW_RECT       17180
#define VC_DRAW_DIM_HOR    17230
#define VC_DRAW_DIM_VER    17231
#define VC_DRAW_DIM_PAR    17232
#define VC_DRAW_DIM_ANG    17233
#define VC_DRAW_DIM_RAD    17234
#define VC_DRAW_DIM_DIAM   17235
#define VC_DRAW_DIM_ORD    17236
#define VC_DRAW_HATCH      17240
#define VC_INS_TEXT        17250
#define VC_INS_SYMBOL      17260
#define VC_INS_BLOCK       17280
#define VC_INS_IMAGE       17290
#define VC_INS_RMAP        17300
#define VC_INS_GLASS       17301 
#define VC_INS_DRAWING     17302
#define VC_INS_AVSHP       17303
#define VC_INS_FLOOD       17304

// Edit
#define VC_EDIT_ENTPROP    17401
#define VC_EDIT_COPY       17402
#define VC_EDIT_MOVE       17403
#define VC_EDIT_ROTATE     17404
#define VC_EDIT_SCALE      17405
#define VC_EDIT_MIRROR     17406
#define VC_EDIT_ERASE      17407
#define VC_EDIT_EXPLODE    17408
#define VC_EDIT_CREBLOCK   17409
#define VC_EDIT_EXTEND     17410
#define VC_EDIT_TRIM       17411
#define VC_EDIT_FILLET     17412
#define VC_EDIT_ARRAY      17413
#define VC_EDIT_JOIN       17414
#define VC_EDIT_UNDO       17431
#define VC_EDIT_REDO       17432
#define VC_EDIT_CBCUT      17441
#define VC_EDIT_CBCOPY     17442
#define VC_EDIT_CBPASTE    17443

// Format
#define VC_FMT_LAYOUT      17451
#define VC_FMT_PAGE        17452
#define VC_FMT_LAYER       17453
#define VC_FMT_STLINE      17454
#define VC_FMT_STTEXT      17455
#define VC_FMT_STDIM       17456
#define VC_FMT_STPOINT     17457
#define VC_FMT_STHATCH     17458
#define VC_FMT_BLOCK       17459
#define VC_FMT_GRID        17461
#define VC_FMT_OSNAP       17462
#define VC_FMT_PSNAP       17463
#define VC_FMT_UNITS       17464
#define VC_FMT_PRIVATE     17465
#define VC_FMT_PREFERS     17466
#define VC_FMT_MLINE       17467

// Snap
#define VC_SNAP_DLG        17501
#define VC_SNAP_CLEAR      17502
#define VC_SNAP_GRID       17503
#define VC_SNAP_POLAR      17504
#define VC_SNAP_KNOT       17511
#define VC_SNAP_GRIP       17511
#define VC_SNAP_GRIPS      17511
#define VC_SNAP_POINT      17512
#define VC_SNAP_NEAR       17513
#define VC_SNAP_END        17514
#define VC_SNAP_MID        17515
#define VC_SNAP_INTER      17516
#define VC_SNAP_CEN        17517
#define VC_SNAP_PERP       17518
#define VC_SNAP_TANG       17519
#define VC_SNAP_REALTIME   17520

// Tools
#define VC_TOOL_DIST       18501
#define VC_TOOL_PRNRECT    18502
#define VC_TOOL_STAT       18503
#define VC_TOOL_NAVIGATOR  18504
#define VC_TOOL_LAYERS     18505
#define VC_ENT_SWAP        18511
#define VC_ENT_TOTOP       18512
#define VC_ENT_TOBOTTOM    18513
#define VC_SEL_BYPOINT     18531
#define VC_SEL_BYRECT      18532
#define VC_SEL_BYPOLYGON   18533
#define VC_SEL_BYPOLYLINE  18534
#define VC_SEL_BYDIST      18535
#define VC_SEL_BYHANDLE    18536
#define VC_SEL_BYKEY       18537
#define VC_SEL_BYLAYER     18538

// Misc
#define VC_RESET         18171
#define VC_REDRAW        18172
#define VC_SHOWLINEW     18173
#define VC_SHOWGRID      18174
#define VC_SHOWFILL      18175

// Offset for custom commands that use cursor
#define VC_CUSTOM        20000


/********************************************************************
* VeCAD data access keys for vlGetData/vlSetData functions
********************************************************************/

#define VD_WND___MIN         30001
#define VD_WND_EMPTYTEXT     30001
#define VD_WND_CURSOR_X      30002
#define VD_WND_CURSOR_Y      30003
#define VD_WND_CURSOR_CROSS  30004
#define VD_WND___MAX         30010

#define VD_PRJ___MIN         30011
#define VD_PRJ_WDWG_ON       30011
#define VD_PRJ_WDWG_LEFT     30012
#define VD_PRJ_WDWG_TOP      30013
#define VD_PRJ_WDWG_RIGHT    30014
#define VD_PRJ_WDWG_BOTTOM   30015
#define VD_PRJ_WVIEW_ON      30016
#define VD_PRJ_WVIEW_LEFT    30017
#define VD_PRJ_WVIEW_TOP     30018
#define VD_PRJ_WVIEW_RIGHT   30019
#define VD_PRJ_WVIEW_BOTTOM  30020
#define VD_PRJ_WDIST_LEFT    30021
#define VD_PRJ_WDIST_TOP     30022
#define VD_PRJ_VECAD         30098
#define VD_PRJ___MAX         30099

/*
#define VD_AVIEW___MIN       30101
#define VD_AVIEW_COLRECT     30101
#define VD_AVIEW_DWGDRAG     30102
#define VD_AVIEW___MAX       30130
*/

#define VD_PRN___MIN         30131
#define VD_PRN_NAME          30131
#define VD_PRN_DRIVER        30132
#define VD_PRN_PORT          30133
#define VD_PRN_USEDOC        30134
#define VD_PRN___MAX         30150

#define VD_MSG_STRING        30155
#define VD_MSG_DBL1          30156
#define VD_MSG_DBL2          30157
#define VD_SDECIMAL          30161
#define VD_KEYCTRL           30162
#define VD_KEYSHIFT          30163

#define VD_DWG___MIN         1
#define VD_DWG_ID            1
#define VD_DWG_INDEX         2
#define VD_DWG_FILENAME      3
#define VD_DWG_PATHNAME      4
#define VD_DWG_TITLE         5
#define VD_DWG_LEFT          6
#define VD_DWG_RIGHT         7
#define VD_DWG_TOP           8
#define VD_DWG_BOTTOM        9
#define VD_DWG_WIDTH         10
#define VD_DWG_HEIGHT        11
#define VD_DWG_WINLEFT       12
#define VD_DWG_WINRIGHT      13
#define VD_DWG_WINTOP        14  
#define VD_DWG_WINBOTTOM     15
#define VD_DWG_WINWIDTH      16
#define VD_DWG_WINHEIGHT     17
#define VD_DWG_WINSCALE      18
#define VD_DWG_WINSCALEY     19
#define VD_DWG_ZOOMVAL       20
#define VD_DWG_ZOOMHORZ      21
#define VD_DWG_ZOOMVERT      22
#define VD_DWG_ZOOMMIN       23
#define VD_DWG_ZOOMMAX       24
#define VD_DWG_SCROLLERS     25
#define VD_DWG_READONLY      26
#define VD_DWG_BLACKWHITE    27
#define VD_DWG_COLBKG        31  
#define VD_DWG_COLPAGE       32 
#define VD_DWG_COLPAGESHADOW 33
#define VD_DWG_COLCURSOR     34
#define VD_DWG_COLGRIP       35
#define VD_DWG_COLSELOBJ     36
#define VD_DWG_COLSELGRIP    37
#define VD_DWG_COLOR         38
#define VD_DWG_SHOWAPER      41 
#define VD_DWG_SHOWCROSS     42
#define VD_DWG_SHOWFILL      43 
#define VD_DWG_SHOWVEC       44  
#define VD_DWG_SHOWBMP       45  
#define VD_DWG_SHOWLINEW     46
#define VD_DWG_SHOWRMARK     47
#define VD_DWG_SHOWGRID      48
#define VD_DWG_AUTOSELPNT    61
#define VD_DWG_AUTOSELRECT   62
#define VD_DWG_AUTOUNSELECT  63
#define VD_DWG_USEGRIPS      71 
#define VD_DWG_LOCK          72     
#define VD_DWG_PASSWORD      73
#define VD_DWG_OWNER         74
#define VD_DWG_NOEXPORT      75
#define VD_DWG_NOPRINT       76
#define VD_DWG_PICKBOXSIZE   82 
#define VD_DWG_GRIPSIZE      83 
#define VD_DWG_DEFLINEW      84 
#define VD_DWG_ISDIRTY       85  
#define VD_DWG_EXDATASIZE    86
#define VD_DWG_EXDATA        87   
#define VD_DWG_CROSSSIZE     88
#define VD_DWG_TRACK_EXPORT  89
#define VD_DWG_SNAP          91
#define VD_DWG_SNAPSIZE      92
#define VD_DWG_PSNAPDIST     93
#define VD_DWG_PSNAPANGLE0   94
#define VD_DWG_PSNAPANGLE    95
#define VD_DWG_N_PAGES       101
#define VD_DWG_C_PAGE        102
#define VD_DWG_N_LAYERS      103
#define VD_DWG_C_LAYER       104
#define VD_DWG_N_STLINES     105
#define VD_DWG_C_STLINE      106
#define VD_DWG_N_STTEXTS     107
#define VD_DWG_C_STTEXT      108
#define VD_DWG_N_STHATCHS    109
#define VD_DWG_C_STHATCH     110
#define VD_DWG_N_VIEWS       111
#define VD_DWG_C_VIEW        112
#define VD_DWG_N_PRNRECTS    113
#define VD_DWG_C_PRNRECT     114
#define VD_DWG_N_STDIMS      115
#define VD_DWG_C_STDIM       116
#define VD_DWG_N_STPOINTS    117
#define VD_DWG_C_STPOINT     118
#define VD_DWG_N_GRPOINTS    119
#define VD_DWG_C_GRPOINT     120
#define VD_DWG_N_BLOCKS      121
#define VD_DWG_C_BLOCK       122
#define VD_DWG_N_ENTITIES    123
#define VD_DWG_N_ENT         123
#define VD_DWG_N_ENTSEL      124
#define VD_DWG_C_LEVEL       125
#define VD_DWG_BITMAP        126
#define VD_DWG_SELECTINSIDE  127
#define VD_DWG_FLATENDS      128
#define VD_DWG_SEGCURVE      129
#define VD_DWG_CHARFRAME     130
#define VD_DWG_SELACTLAYER   131
#define VD_DWG_SORTLAYERS    132      // WO
#define VD_DWG_PROPMESSAGES  133
#define VD_DWG_EXTOBJECT     134
#define VD_DWG_HWND          135
#define VD_DWG_INSBLOCKDLG   136
#define VD_DWG_NOINDICATOR   137

#define VD_GRID_X0           141      // grid origin X
#define VD_GRID_Y0           142      // grid origin Y
#define VD_GRID_DX           143      // grid step X
#define VD_GRID_DY           144      // grid step Y
#define VD_GRID_TYPE         145      // grid type
#define VD_GRID_COLOR        146      // grid color
#define VD_GRID_BSTEPX       147      // grid bold step
#define VD_GRID_BSTEPY       148      // grid bold step
#define VD_GRID_BTYPE        149      // grid bold type
#define VD_GRID_BCOLOR       150      // grid bold color
#define VD_UNITS_LIN         161   // coord units
#define VD_UNITS_ANG         162   // angle units
#define VD_UNITS_SCALE       163   // map scale
#define VD_UNITS_PAGELEFT    164   // coord for page origin
#define VD_UNITS_PAGEBOTTOM  165   //
#define VD_UNITS_GEO         166   // geodesic axises
#define VD_UNITS_FORMAT      167   // output format
#define VD_HPGL_X0           171   // origin for HPGL export
#define VD_HPGL_Y0           172
#define VD_HPGL_UNITX        173   // scale for HPGL export
#define VD_HPGL_UNITY        174
#define VD_HPGL_MINSTEP      175   // minimal step for coordinates
#define VD_HPGL_OFFDIST      176   // distance for VM_EXP_PUMPOFF
#define VD_EXP_X0          171
#define VD_EXP_Y0          172
#define VD_EXP_UNITX       173
#define VD_EXP_UNITY       174
#define VD_EXP_MINSTEP     175
#define VD_EXP_OFFDIST     176
#define VD_EXP_USEARCS     177
#define VD_EXP_DROPSIZE    178
#define VD_EXP_DROPSIZEMIN 179
#define VD_DWG___MAX         200

#define VD_PAGE___MIN         201
#define VD_PAGE_NAME          201   // page name
#define VD_PAGE_SIZE          202   // page size
#define VD_PAGE_ORIENT        203   // page orientation
#define VD_PAGE_WIDTH         204   // page width (if size=VD_PAPER_USER)
#define VD_PAGE_HEIGHT        205   // page height (if size=VD_PAPER_USER)
#define VD_PAGE_N_REF         208   // RO number of objects on the page
#define VD_PAGE_ID            209   // RO page ID
#define VD_PAGE_INDEX         210   // RO page index by name
#define VD_PAGE_EXTOBJECT     211
#define VD_PAGE___MAX         299

#define VD_LAYER___MIN        301
#define VD_LAYER_NAME         301      // layer name
#define VD_LAYER_COLOR        302      // layer color
#define VD_LAYER_FILLCOLOR    303      // layer fill color
#define VD_LAYER_LINEWIDTH    304      // layer line width
#define VD_LAYER_VISIBLE      305      // layer visible
#define VD_LAYER_LOCK         306      // layer locked
#define VD_LAYER_SELINSIDE    307      // layer enable select by inner part of object
#define VD_LAYER_NOPRINT      308      // non-printable layer
#define VD_LAYER_N_REF        309      // RO number of objects on the layer
#define VD_LAYER_ID           310      // RO layer ID
#define VD_LAYER_INDEX        311      // RO layer index by name
#define VD_LAYER_ENTSELECT    312      // WO select all entities on the layer
#define VD_LAYER_SELENT       312
#define VD_LAYER_LEVEL        313      
#define VD_LAYER_EXTOBJECT    314
#define VD_LAYER___MAX        399

#define VD_STTEXT___MIN       401  
#define VD_STTEXT_NAME        401      // text style name
#define VD_STTEXT_FONTNAME    402      // RO text style fontname
#define VD_STTEXT_WEIGHT      403      // RO font weight
#define VD_STTEXT_ITALIC      404      // RO font italic
#define VD_STTEXT_WIDTH       405      // text style chars width scale
#define VD_STTEXT_OBLIQUE     406      // text style chars horiz. shift
#define VD_STTEXT_PRECISION   407      // RO text style precision
#define VD_STTEXT_FILLED      408      // flag "filled text"
#define VD_STTEXT_N_REF       409      // RO number of references
#define VD_STTEXT_ID          410      // RO ID
#define VD_STTEXT_INDEX       411      // RO index by name
#define VD_STTEXT_BYLINES     412      // flag "draw texts by lines"
#define VD_STTEXT_EXTOBJECT   413
#define VD_STTEXT___MAX       499

#define VD_STLINE___MIN       501
#define VD_STLINE_NAME        501      // line type name
#define VD_STLINE_DESC        502      // line type description
#define VD_STLINE_DESCLEN     503      // RO length of line type description
#define VD_STLINE_N_REF       504      // RO number of references
#define VD_STLINE_ID          505      // RO ID
#define VD_STLINE_INDEX       506      // RO index by name
#define VD_STLINE_EXTOBJECT   507
#define VD_STLINE___MAX       599

#define VD_STDIM___MIN        601
#define VD_STDIM_NAME         601      // dim style name
#define VD_STDIM_ARR_TYPE     602
#define VD_STDIM_ARR_LENGTH   603
#define VD_STDIM_ARR_HEIGHT   604
#define VD_STDIM_EXT_OFFSET   605
#define VD_STDIM_EXT_EXTEND   606
#define VD_STDIM_TEXT_CONTENT 607
#define VD_STDIM_TEXT_STYLE   608
#define VD_STDIM_TEXT_ALIGN   609
#define VD_STDIM_TEXT_HEIGHT  610
#define VD_STDIM_TEXT_DEC     611
#define VD_STDIM_TEXT_HORIZ   612
#define VD_STDIM_TEXT_GAP     613
#define VD_STDIM_SCALE        614
#define VD_STDIM_OWNCOLORS    615
#define VD_STDIM_COL_DIM      616
#define VD_STDIM_COL_EXT      617
#define VD_STDIM_COL_TEXT     618
#define VD_STDIM_CEN_TYPE     619
#define VD_STDIM_CEN_SIZE     620
#define VD_STDIM_ROUND        621
#define VD_STDIM_N_REF        622
#define VD_STDIM_ID           623
#define VD_STDIM_INDEX        624
#define VD_STDIM_EXTOBJECT    625
#define VD_STDIM___MAX        699

#define VD_STHATCH___MIN      701
#define VD_STHATCH_NAME       701      // hatch style name
#define VD_STHATCH_DESC       702      // hatch style description
#define VD_STHATCH_DESCLEN    703      // RO length of description
#define VD_STHATCH_N_REF      704      // RO number of references
#define VD_STHATCH_ID         705      // RO ID
#define VD_STHATCH_INDEX      706      // RO index by name
#define VD_STHATCH_EXTOBJECT  707
#define VD_STHATCH___MAX      799

#define VD_STPOINT___MIN      801
#define VD_STPOINT_NAME       801      // point type name
#define VD_STPOINT_STATUS     802      // point type status
#define VD_STPOINT_BLOCK      803      // index of block
#define VD_STPOINT_LAYER      804      // layer for point type
#define VD_STPOINT_STTEXT     805      // text style
#define VD_STPOINT_BSCALE     806      // block scale
#define VD_STPOINT_TEXTH      807      // text height
#define VD_STPOINT_TEXTW      808      // text width scale
#define VD_STPOINT_SNAP       809      // snap to point
#define VD_STPOINT_FIXED      810      // non-movable point
#define VD_STPOINT_N_REF      811      // RO number of references
#define VD_STPOINT_ID         812      // RO ID
#define VD_STPOINT_INDEX      813      // RO index by name
#define VD_STPOINT_EXTOBJECT  814
#define VD_STPOINT___MAX      859

#define VD_GRPOINT___MIN      861
#define VD_GRPOINT_NAME       861      // point group name
#define VD_GRPOINT_N_REF      862      // RO number of references
#define VD_GRPOINT_ID         863      // RO ID
#define VD_GRPOINT_INDEX      864      // RO index by name
#define VD_GRPOINT_EXTOBJECT  865
#define VD_GRPOINT___MAX      899

#define VD_BLOCK___MIN      901
#define VD_BLOCK_NAME       901      // block name
#define VD_BLOCK_WIDTH      902      // RO width of the block
#define VD_BLOCK_HEIGHT     903      // RO height of the block
#define VD_BLOCK_XBASE      904      // x base point
#define VD_BLOCK_YBASE      905      // y base point
#define VD_BLOCK_N_REF      906      // RO number of references
#define VD_BLOCK_ID         907      // RO ID
#define VD_BLOCK_INDEX      908      // RO index by name
#define VD_BLOCK_EXTOBJECT  909
#define VD_BLOCK_N_ENT      910      // RO number of entities in block
#define VD_BLOCK___MAX      999

#define VD_PRNRECT___MIN    1001
#define VD_PRNRECT_INDEX    1001     // RO index by name
#define VD_PRNRECT_NAME     1002     // name
#define VD_PRNRECT_XCEN     1003     // x-center point
#define VD_PRNRECT_YCEN     1004     // y-center point
#define VD_PRNRECT_WIDTH    1005     // width of the rect
#define VD_PRNRECT_HEIGHT   1006     // height of the rect
#define VD_PRNRECT_ANGLE    1007     // rotation angle of the rect
#define VD_PRNRECT_EXTOBJECT 1008
#define VD_PRNRECT___MAX    1099

#define VD_VIEW___MIN       1101
#define VD_VIEW_ID          1101     // RO ID
#define VD_VIEW_NAME        1102     // name
#define VD_VIEW_EXTOBJECT   1103
#define VD_VIEW___MAX       1199

#define VD_ENT___MIN      20001
#define VD_ENT_TYPE       20001    // RO type of object
#define VD_ENT_HANDLE     20002    // RO handle
#define VD_ENT_ID         20002    // RO handle
#define VD_ENT_KEY        20003    // key
#define VD_ENT_LAYER      20004    // layer index
#define VD_ENT_LINETYPE   20005    // line type
#define VD_ENT_STLINE     20005    // line type
#define VD_ENT_PAGE       20006    // page
#define VD_ENT_LEVEL      20007    // level
#define VD_ENT_COLOR      20008    // own color
#define VD_ENT_FILLCOLOR  20009    // own fill color
#define VD_ENT_LINEWIDTH  20010    // own linewidth
#define VD_ENT_LEFT       20011    // RO left limit
#define VD_ENT_BOTTOM     20012    // RO bottom limit
#define VD_ENT_RIGHT      20013    // RO right limit
#define VD_ENT_TOP        20014    // RO top limit
#define VD_ENT_SELECT     20015    // select object
#define VD_ENT_ONSCREEN   20016    // RO object on screen
#define VD_ENT_INBLOCK    20017    // RO object is part of a block
#define VD_ENT_N_GRIPS    20018    // RO number of grips in the object
#define VD_ENT_DELETED    20019    // delete object
#define VD_ENT_FILLED     20020    // filled object
#define VD_ENT_BORDER     20021    // has border (for filled)
#define VD_ENT_OWNCOLOR   20022    // has own color (not by layer)
#define VD_ENT_OWNFCOLOR  20023    // has own fill color (not by layer)
#define VD_ENT_OWNLINEW   20024    // has own line width (not by layer)
#define VD_ENT_WIDTH      20025    // RO object width
#define VD_ENT_HEIGHT     20026    // RO object width
#define VD_ENT_UPDATE     20027    // WO update limits
#define VD_ENT_LENGTH     20028    // RO object's perimeter (for closed objects)
#define VD_ENT_PERIMETER  20028    // RO object's perimeter (for closed objects)
#define VD_ENT_AREA       20029    // RO object's area (for closed objects)
#define VD_ENT_INDEX      20030    // RO object's index
#define VD_ENT_MULTILINE  20031    // flag "line style is multiline"
#define VD_ENT_EXTOBJECT  20032    // pointer to external object
#define VD_ENT___MAX      20099

#define VD_LINE___MIN     20101
#define VD_LINE_X1        20101    // coordinate of 1st point
#define VD_LINE_Y1        20102    //
#define VD_LINE_X2        20103    // coordinate of 2nd point
#define VD_LINE_Y2        20104    //
#define VD_LINE_ARROW1    20105    // End arrows flags
#define VD_LINE_ARROW2    20106    // 
#define VD_LINE___MAX     20199

#define VD_POLY___MIN     20201    
#define VD_POLY_CLOSED    20201    // flag "closed polyline"
#define VD_POLY_SMOOTH    20202    // polyline smooth type
#define VD_POLY_ARROW1    20203    // type of start arrow (dim.style)
#define VD_POLY_ARROW2    20204    // type of end arrow (dim.style)
#define VD_POLY_R         20205    // radius for smooth=VL_POLY_ROUNDED
#define VD_POLY_N_VER     20206    // RO number of vertexes
#define VD_POLY_C_VER     20207    // current vertex
#define VD_POLY_GETVERS   20208    // RO Get vertexes array
#define VD_POLY_SETVERS   20209    // WO Set vertexes array
#define VD_POLY_VER_INS   20210    // WO Insert vertex
#define VD_POLY_VER_DEL   20211    // WO Delete vertex
#define VD_POLY_VER_X     20212    // vertex coordinate
#define VD_POLY_VER_Y     20213    //
#define VD_POLY_VER_R     20214    // vertex radius (for smooth=VL_POLY_MULTIRAD)
#define VD_POLY_VER_ON    20215    // vertex online flag (for smooth=VL_POLY_LINBSPL2)
#define VD_POLY_VER_BULGE 20216    // bulge coefficient (for smooth=VL_POLY_BULGE)
#define VD_POLY_VER_DATA  20217    // aux vertex data
#define VD_POLY_CUSTDATA  20231    // custom data (for smooth=POLY_CUSTOM)
#define VD_POLY___MAX     20299     

#define VD_CIRCLE___MIN   20301    
#define VD_CIRCLE_X       20301    // coordinate of circle's center
#define VD_CIRCLE_Y       20302    //
#define VD_CIRCLE_R       20303    // radius of circle
#define VD_CIRCLE___MAX   20399    

#define VD_ARC___MIN      20401    // coordinate of arc's center
#define VD_ARC_X          20401    // coordinate of arc's center
#define VD_ARC_Y          20402    //
#define VD_ARC_R          20403    // arc's radius
#define VD_ARC_START      20404    // start angle
#define VD_ARC_END        20405    // end angle
#define VD_ARC_ARROW1     20406    // index of dim style for start arrow type
#define VD_ARC_ARROW2     20407    // for end arrow
#define VD_ARC_RH         20411    // horizontal radius
#define VD_ARC_RV         20412    // vertical radius
#define VD_ARC_ANG0       20413    // start angle
#define VD_ARC_ANGARC     20414    // arc angle
#define VD_ARC_ANGROT     20415    // rotation angle
#define VD_ARC_SECTOR     20431    // draw as sector
#define VD_ARC_CHORD      20432    // draw arc with chord
#define VD_ARC_XS         20441    // RO start point
#define VD_ARC_YS         20442
#define VD_ARC_XE         20443    // RO end point
#define VD_ARC_YE         20444
#define VD_ARC___MAX      20499    // 

#define VD_ELLIPSE___MIN  20601
#define VD_ELLIPSE_X      20601    // coordinate of ellipse's center
#define VD_ELLIPSE_Y      20602    //
#define VD_ELLIPSE_RH     20603    // horizontal radius
#define VD_ELLIPSE_RV     20604    // vertical radius
#define VD_ELLIPSE_ANGLE  20605    // rotation angle of the ellipse
#define VD_ELLIPSE___MAX  20699

#define VD_TEXT___MIN     20701
#define VD_TEXT_X         20701    // coordinate of text's insertion
#define VD_TEXT_Y         20702    //
#define VD_TEXT_TEXT      20703    // text sting
#define VD_TEXT_LENGTH    20704    // RO text length (symbols)
#define VD_TEXT_STYLE     20705    // text style
#define VD_TEXT_HEIGHT    20706    // text height
#define VD_TEXT_WSCALE    20707    // text width scale
#define VD_TEXT_ALIGN     20708    // text align
#define VD_TEXT_ANGLE     20709    // text angle
#define VD_TEXT_OBLIQUE   20710    // text shift horiz.
#define VD_TEXT_INTER_H   20712    // interval between chars
#define VD_TEXT_INTER_V   20713    // interval between strings
#define VD_TEXT_PATH      20714    // flag "Path text"
#define VD_TEXT_STRIKEOUT 20715    // strikeout text
#define VD_TEXT_UNDERLINE 20716    // underlined text
#define VD_TEXT_N_LINES   20717    // RO number of text lines
#define VD_TEXTP_CURVE    20721    // handle of path curve object
#define VD_TEXTP_DX       20722    // origin along the curve
#define VD_TEXTP_DY       20723    // chars deviation from the curve
#define VD_TEXTP_BACKWARD 20724    // backward to curve direction
#define VD_TEXTP_ABSANGLE 20725    // absolute rotation angle
#define VD_TEXT___MAX     20799

#define VD_INSBLK___MIN   20801
#define VD_INSBLK_X       20801    // coordinate of block's insertion
#define VD_INSBLK_Y       20802    //
#define VD_INSBLK_BLOCK   20803    // block's index
#define VD_INSBLK_ANGLE   20804    // rotation angle
#define VD_INSBLK_SCALEX  20805    // horiz. scale
#define VD_INSBLK_SCALEY  20806    // vert. scale
#define VD_INSBLK_SCALE   20807    // scale
#define VD_INSBLK___MAX   20899

#define VD_HATCH___MIN    20901
#define VD_HATCH_STYLE    20901    // index of hatch style
#define VD_HATCH_SCALE    20902    // hatch's scale
#define VD_HATCH_ANGLE    20903    // hatch's angle
#define VD_HATCH___MAX    20999

#define VD_BMP___MIN      21001
#define VD_BMP_X          21001    // coordinate of bitmap's insertion
#define VD_BMP_Y          21002    //
#define VD_BMP_FILENAME   21003    // bitmap file name
#define VD_BMP_RESX       21004    // bitmap resolution by X
#define VD_BMP_RESY       21005    // bitmap resolution by Y
#define VD_BMP_RELOAD     21007    // WO reload bitmap
#define VD_BMP___MAX      21099

#define VD_POINT___MIN    21101  
#define VD_POINT_X        21101    // coordinate of point
#define VD_POINT_Y        21102    //
#define VD_POINT_STYLE    21103    // point type
#define VD_POINT_GROUP    21104    // point group
#define VD_POINT_TEXT     21105    // point text
#define VD_POINT_TEXTLEN  21106    // text length (symbols)
#define VD_POINT_TXTDX    21107    // point text offset by X
#define VD_POINT_TXTDY    21108    // point text offset by Y
#define VD_POINT_TXTANG   21109    // point text angle
#define VD_POINT_BLKANG   21110    // point block angle
#define VD_POINT_FIXED    21111    // non-movable point
#define VD_POINT___MAX    21199

#define VD_RECT___MIN     21201 
#define VD_RECT_XCEN      21201    // coordinate of rect's center
#define VD_RECT_YCEN      21202    //
#define VD_RECT_WIDTH     21203    // width
#define VD_RECT_HEIGHT    21204    // height
#define VD_RECT_ANGLE     21205    // rotation angle of the rect
#define VD_RECT_RADIUS    21206    // radius of corners
#define VD_RECT___MAX     21299

#define VD_DIM___MIN      22301 
#define VD_DIM_STYLE      22301    // dimension style
#define VD_DIM_TYPE       22302    // RO dimension type 
#define VD_DIM_STATIC     22303    // flag "static value"
#define VD_DIM_VALUE      22304    // value (if static)
#define VD_DIM_XTEXT      22305    // text point
#define VD_DIM_YTEXT      22306    //
#define VD_DIM___MAX      22319 

#define VD_DIM_L___MIN    22321    
#define VD_DIM_L_X1       22321    // first point
#define VD_DIM_L_Y1       22322    //
#define VD_DIM_L_X2       22323    // second point
#define VD_DIM_L_Y2       22324    //
#define VD_DIM_L_OFFSET   22325    // offset of dim. line
#define VD_DIM_L_XLINE    22325    
#define VD_DIM_L_YLINE    22325    
#define VD_DIM_L___MAX    22339    

#define VD_DIM_A___MIN    22341 
#define VD_DIM_A_XCEN     22341    // center point
#define VD_DIM_A_YCEN     22342    //
#define VD_DIM_A_X1       22343    // first point
#define VD_DIM_A_Y1       22344    //
#define VD_DIM_A_X2       22345    // second point
#define VD_DIM_A_Y2       22346    //
#define VD_DIM_A_RADIUS   22347    // radius for dimension arc
#define VD_DIM_A___MAX    22359 

#define VD_DIM_R___MIN    22361
#define VD_DIM_R_XCEN     22361    // center point
#define VD_DIM_R_YCEN     22362
#define VD_DIM_R_XRAD     22363    // radial point
#define VD_DIM_R_YRAD     22364
#define VD_DIM_R_OFFSET   22365    // offset of dim line start
#define VD_DIM_R___MAX    22369

#define VD_DIM_D___MIN    22371
#define VD_DIM_D_XCEN     22371    // center point
#define VD_DIM_D_YCEN     22372
#define VD_DIM_D_XRAD     22373    // radial point
#define VD_DIM_D_YRAD     22374
#define VD_DIM_D___MAX    22379

#define VD_DIM_O___MIN    22391
#define VD_DIM_O_X        22391    // ordinate point
#define VD_DIM_O_Y        22392
#define VD_DIM_O_ORDY     22393    // flag "Show Y ordinate"
#define VD_DIM_O___MAX    22399

#define VD_CE___MIN       22901    // custom entity
#define VD_CE_DATA        22901    // data block of the entity
#define VD_CE_DATASIZE    22901    // (RO) size of data block
#define VD_CE___MAX       22999

#define VD_INSDWG___MIN    23001
#define VD_INSDWG_FILENAME 23001
#define VD_INSDWG_X        23002
#define VD_INSDWG_Y        23003
#define VD_INSDWG_ANGLE    23004
#define VD_INSDWG_SCALEX   23005
#define VD_INSDWG_SCALEY   23006
#define VD_INSDWG_WIDTH    23007
#define VD_INSDWG_HEIGHT   23008
#define VD_INSDWG_RELOAD   23017   // WO
#define VD_INSDWG___MAX    23099

#define VD_GLASS___MIN    23101
#define VD_GLASS_X        23101
#define VD_GLASS_Y        23102
#define VD_GLASS_W        23103
#define VD_GLASS_H        23104
#define VD_GLASS_MLEF     23105
#define VD_GLASS_MTOP     23106
#define VD_GLASS_MRIG     23107
#define VD_GLASS_MBOT     23108
#define VD_GLASS_FILENAME 23109
#define VD_GLASS_KEEPPROP 23110
#define VD_GLASS_FITSIZE  23111
#define VD_GLASS_W2       23112
#define VD_GLASS_H2       23113
#define VD_GLASS_ANGLE    23114
#define VD_GLASS_DWGMODE  23115
#define VD_GLASS___MAX    23199

#define VD_FLOOD___MIN    23201  
#define VD_FLOOD_X        23201    // coordinate of point
#define VD_FLOOD_Y        23202    //
#define VD_FLOOD___MAX    23299



/********************************************************************
* VeCAD strings identifiers
********************************************************************/

#define VS_MSGTITLE            10501
#define VS_NONAME              10502
#define VS_UNDO_EMPTY          10503
#define VS_REDO_EMPTY          10504
#define VS_NO_FONT_FILE        10505
#define VS_DELETE_OBJ          10506
#define VS_SAVE_CHANGES        10507
#define VS_OLD_VEC_FORMAT      10508
#define VS_NEW_VEC_FORMAT      10509
#define VS_DWG_ALREADY_LOADED  10510
#define VS_NO_BLOCKS           10511
#define VS_LOAD_ERROR_SUM      10512
#define VS_LOADING             10513
#define VS_SAVING              10514
#define VS_EMPTYDWG            10515
#define VS_CANT_LOAD_FILE      10516 
#define VS_BEGIN_EDITBLOCK     10517
#define VS_EDITBLOCK_MODE      10518
#define VS_DIFFER_LAYERS       10519
#define VS_SEARCH_FILE         10520

#define VS_FILTER_VEC    10541
#define VS_FILTER_SHP    10542  // AutoCAD SHP
#define VS_FILTER_PAT    10543
#define VS_FILTER_BMP    10544
#define VS_FILTER_VDF    10545
#define VS_FILTER_HPGL   10546
#define VS_FILTER_DP1    10547
#define VS_FILTER_CNC    10548
#define VS_FILTER_DXF    10551
#define VS_FILTER_DWGDXF 10552
#define VS_FILTER_DWG    10553
#define VS_FILTER_AVSHP  10554   // ArcView SHP

#define VS_DEL_LAYER_ONE       10651
#define VS_DEL_LAYER_HAS_REF   10652
#define VS_DEL_PAGE_ONE        10653
#define VS_DEL_PAGE_HAS_REF    10654
#define VS_DEL_STLINE_ONE      10655
#define VS_DEL_STLINE_HAS_REF  10656
#define VS_DEL_STTEXT_ONE      10657
#define VS_DEL_STTEXT_HAS_REF  10658
#define VS_DEL_STDIM_ONE       10659
#define VS_DEL_STDIM_HAS_REF   10660
#define VS_DEL_STHATCH_ONE     10661
#define VS_DEL_STHATCH_HAS_REF 10662
#define VS_DEL_BLOCK_HAS_REF   10663
#define VS_DEL_STPOINT_ONE     10664
#define VS_DEL_STPOINT_HAS_REF 10665
#define VS_DEL_STPOINT_SIMPLE  10667
#define VS_DEL_GRPOINT_ONE     10668
#define VS_DEL_GRPOINT_HAS_REF 10669
#define VS_DEL_MLINE_HAS_REF   10670
#define VS_DEL_PRNRECT         10671

#define VS_DWGLIST_TITLE  10981
#define VS_DWGLIST_CLOSE  10982

#define VS_VIEW_TITLE     10985
#define VS_VIEW_EDIT      10986
#define VS_VIEW_DELETE    10987
#define VS_VIEW_SAVE      10988
#define VS_VIEW_NAME      10989


#define VS_BUT_OK         11201
#define VS_BUT_CANCEL     11202
#define VS_BUT_ADD        11203
#define VS_BUT_DELETE     11204
#define VS_BUT_CURRENT    11205
#define VS_BUT_SELECT     11206
#define VS_BUT_UNSELECT   11207
#define VS_N_REFS         11221
#define VS_OBJVIEW        11222

#define VS_SELPAGE          11301

#define VS_LAYOUT_TITLE     11302
#define VS_DAID_TITLE       11303
#define VS_ENTPROP_TITLE    11304
#define VS_ENTPROP_TITLE2   11305

#define VS_PAGE_TITLE       11401
#define VS_PAGE_BOOK        11402
#define VS_PAGE_ALBUM       11403
#define VS_PAGE_NAME        11405
#define VS_PAGE_NAME2       11406
#define VS_PAGE_SIZE        11407
#define VS_PAGE_W           11408
#define VS_PAGE_H           11409
#define VS_PAGE_ORIENT      11410
#define VS_PAGE_BTNFORALL   11419
#define VS_PAGE_FORALL      11420

#define VS_LAYER_TITLE      11501
#define VS_LAYER_NAME       11502
#define VS_LAYER_STATE      11503
#define VS_LAYER_NAME2      11504
#define VS_LAYER_LWIDTH2    11505
#define VS_LAYER_COLOR      11506
#define VS_LAYER_FCOLOR     11507
#define VS_LAYER_OFF        11508
#define VS_LAYER_RDONLY     11509
#define VS_LAYER_NOPRINT    11510
#define VS_LAYER_SELINS     11511
#define VS_LAYER_LEVEL      11512

#define VS_STLINE_TITLE     11601
#define VS_STLINE_NAME      11602
#define VS_STLINE_NAME2     11603
#define VS_STLINE_DESC      11604
#define VS_STLINE_APPLY     11605

#define VS_MLINE_TITLE      11631
#define VS_MLINE_NAME       11632
#define VS_MLINE_JOINTS     11633
#define VS_MLINE_CAPS       11634
#define VS_MLINE_START      11635
#define VS_MLINE_END        11636
#define VS_MLINE_LINE       11637
#define VS_MLINE_OUTARC     11638
#define VS_MLINE_INARC      11639
#define VS_MLINE_VIEW       11640
#define VS_MLINE_ELEMENTS   11641
#define VS_MLINE_OFFSET     11642
#define VS_MLINE_LINESTYLE  11643
#define VS_MLINE_OFFSET2    11644
#define VS_MLINE_LINESEL    11645
#define VS_MLINE_LINEADD    11646
#define VS_MLINE_LINEDEL    11647

#define VS_STTEXT_TITLE     11701
#define VS_STTEXT_CHFONT    11702
#define VS_STTEXT_RELOAD    11703
#define VS_STTEXT_NAME      11704
#define VS_STTEXT_NAME2     11705
#define VS_STTEXT_FILE      11706
#define VS_STTEXT_WIDTH     11707
#define VS_STTEXT_SHIFT     11708
#define VS_STTEXT_PRECISION 11709
#define VS_STTEXT_FILLED    11710
#define VS_STTEXT_FONTFILE  11711
#define VS_STTEXT_FONTSYS   11712
#define VS_STTEXT_BIGFONT   11713
#define VS_STTEXT_NCHARS    11714
#define VS_STTEXT_BYSYMBOLS 11715
#define VS_STTEXT_BYLINES   11716

#define VS_STDIM_TITLE      11801
#define VS_STDIM_TITLE1     11802
#define VS_STDIM_TITLE2     11803
#define VS_STDIM_TITLE3     11804
#define VS_STDIM_TA_ABOVE   11805
#define VS_STDIM_TA_CENTER  11806
#define VS_STDIM_TA_BELOW   11807
#define VS_STDIM_NAME       11811
#define VS_STDIM_NAME2      11812
#define VS_STDIM_INSLINE    11821  
#define VS_STDIM_ARRHEAD    11822
#define VS_STDIM_ARRTYPE	  11823
#define VS_STDIM_ARRLEN     11824
#define VS_STDIM_ARRH       11825
#define VS_STDIM_EXTLINE    11826
#define VS_STDIM_OFFSET     11827
#define VS_STDIM_EXTEND     11828
#define VS_STDIM_COLORS     11829
#define VS_STDIM_OWNCOL     11830
#define VS_STDIM_COLDIM     11831
#define VS_STDIM_COLEXL     11832
#define VS_STDIM_COLTXT     11833
#define VS_STDIM_CENTER     11834
#define VS_STDIM_CENMARK    11835
#define VS_STDIM_CENLINE    11836
#define VS_STDIM_CENNONE    11837
#define VS_STDIM_CENSIZE    11838
#define VS_STDIM_PREFIX     11851
#define VS_STDIM_TXTSTYLE   11852
#define VS_STDIM_TXTALIGN   11853
#define VS_STDIM_TXTH       11854
#define VS_STDIM_TXTGAP     11855
#define VS_STDIM_TXTDEC     11856
#define VS_STDIM_SCALE      11857
#define VS_STDIM_ROUND      11858
#define VS_STDIM_TOLER      11859
#define VS_STDIM_TPLUS      11860
#define VS_STDIM_TMINUS     11861
#define VS_STDIM_TXTHORZ    11862
#define VS_STDIM_TXTARC90   11863
#define VS_STDIM_TXTRECT    11864
#define VS_STDIM_ENDZERO    11865

#define VS_STHAT_TITLE      11901
#define VS_STHAT_TITLE2     11902
#define VS_STHAT_APPLY      11903
#define VS_STHAT_NAME       11904
#define VS_STHAT_NAME2      11905
#define VS_STHAT_DESC       11906
#define VS_STHAT_LOAD       11907

#define VS_BLOCKS_TITLE     12001
#define VS_BLOCKS_ADD       12002
#define VS_BLOCKS_DELETE    12003
#define VS_BLOCKS_NAME      12004
#define VS_BLOCKS_VIEW      12005
#define VS_BLOCKS_NAME2     12006
#define VS_BLOCKS_SIZE      12007
#define VS_BLOCKS_DX        12008
#define VS_BLOCKS_DY        12009
#define VS_BLOCKS_ENTS      12010
#define VS_BLOCKS_BYLAYER   12011
#define VS_BLOCKS_EDIT      12012

#define VS_SELBLK_TITLE     12031
#define VS_SELBLK_NSEL      12032
#define VS_SELBLK_SELALL    12033
#define VS_SELBLK_UNSELALL  12034

#define VS_NEWBLK_TITLE     12051
#define VS_NEWBLK_NAME      12052

#define VS_STPNT_TITLE      12101
#define VS_STPNT_SIMPLE     12102
#define VS_STPNT_NODRAW     12103
#define VS_STPNT_DRAWBLK    12104
#define VS_STPNT_DRAWTEXT   12105
#define VS_STPNT_DRAWALL    12106
#define VS_STPNT_NAME       12117
#define VS_STPNT_STAT       12118
#define VS_STPNT_LAYER      12119
#define VS_STPNT_TEXT       12120
#define VS_STPNT_TSTYLE     12121
#define VS_STPNT_THIGH      12122
#define VS_STPNT_TSCALE     12123
#define VS_STPNT_SYMBOL     12124
#define VS_STPNT_BLOCK      12125
#define VS_STPNT_BSCALE     12126
#define VS_STPNT_FIXED      12127
#define VS_STPNT_SNAP       12128

#define VS_GRID_TITLE       12401
#define VS_GRID_POINT       12402
#define VS_GRID_CROSS       12403
#define VS_GRID_CROSS45     12404
#define VS_GRID_LINE        12405
#define VS_GRID_DOTLINE     12406
#define VS_GRID_DASHLINE    12407
#define VS_GRID_ORIGIN      12411
#define VS_GRID_STEP        12412
#define VS_GRID_HORZ        12413
#define VS_GRID_VERT        12414
#define VS_GRID_BOLDSTEP    12415
#define VS_GRID_SNAP        12416
#define VS_GRID_SHOW        12417
#define VS_GRID_PRINT       12418
#define VS_GRID_MAIN        12419
#define VS_GRID_BOLD        12420
#define VS_GRID_TYPE        12421
#define VS_GRID_COLOR       12422

#define VS_OSNAP_TITLE      12431
#define VS_OSNAP_END        12432
#define VS_OSNAP_MID        12433
#define VS_OSNAP_CENTER     12434
#define VS_OSNAP_POINT      12435
#define VS_OSNAP_INTER      12436
#define VS_OSNAP_NEAR       12437
#define VS_OSNAP_GRIP       12438
#define VS_OSNAP_PERP       12439
#define VS_OSNAP_TANG       12440
#define VS_OSNAP_CLEAR      12441
#define VS_OSNAP_APERSIZE   12442
#define VS_OSNAP_SELECT     12443
#define VS_OSNAP_REALTIME   12444

#define VS_PSNAP_TITLE      12461
#define VS_PSNAP_ON         12462
#define VS_PSNAP_DIST       12463
#define VS_PSNAP_ANGLE      12464
#define VS_PSNAP_ANGLE_0    12465

#define VS_UNITS_TITLE      12501
#define VS_UNITS_UNITS      12502
#define VS_UNITS_SCALE      12503
#define VS_UNITS_X0         12504
#define VS_UNITS_Y0         12505
#define VS_UNITS_GEO        12506
#define VS_UNITS_PREC       12507
#define VS_UNIT_POINT       12511
#define VS_UNIT_MM          12512
#define VS_UNIT_CM          12513
#define VS_UNIT_MET         12514
#define VS_UNIT_KM          12515
#define VS_UNIT_INCH        12516
#define VS_UNIT_FOOT        12517
#define VS_UNIT_YARD        12518
#define VS_UNIT_MILE        12519
#define VS_UNIT_SEAMILE     12520
#define VS_ANG_DEGREE       12531
#define VS_ANG_RADIAN       12532

#define VS_PRIV_TITLE       12551
#define VS_PRIV_DWGTITLE    12552
#define VS_PRIV_OWNER       12553
#define VS_PRIV_COMMENT     12554
#define VS_PRIV_PSW         12555
#define VS_PRIV_INFO        12556
#define VS_PRIV_NOPSW       12557
#define VS_PRIV_NOLOAD      12558
#define VS_PRIV_VIEWONLY    12559
#define VS_PRIV_NOEXPORT    12560
#define VS_PRIV_NOPRINT     12561

#define VS_PSW_TITLE        12581
#define VS_PSW_WRONG        12582
#define VS_PSW_READONLY     12583
#define VS_PSW_WORD         12584

#define VS_PREF_TITLE       12601
#define VS_PREF_AUTOSELPNT  12602
#define VS_PREF_AUTOSELWIN  12603
#define VS_PREF_SHOWGRID    12604
#define VS_PREF_SHOWFILL    12605
#define VS_PREF_SHOWLINEW   12606
#define VS_PREF_SHOWVECT    12607
#define VS_PREF_SHOWBMP     12608
#define VS_PREF_PENW0       12609
#define VS_PREF_CURSOR      12613
#define VS_PREF_SIZECURS    12614
#define VS_PREF_COLCURS     12615
#define VS_PREF_GRIPS       12616
#define VS_PREF_GRIPSIZE    12617
#define VS_PREF_COLGRIP     12618
#define VS_PREF_COLSELGRIP  12619
#define VS_PREF_COLBKG      12620
#define VS_PREF_COLPAGE     12621
#define VS_PREF_COLSELOBJ   12622
#define VS_PREF_CCOLOR      12623
#define VS_PREF_BYLAYER     12624
#define VS_PREF_SEGCURVE    12625
#define VS_PREF_CHARFRAME   12626
#define VS_PREF_UNSELAFTER  12627
#define VS_PREF_SELINSIDE   12628
#define VS_PREF_SELACTLAYER 12629

#define VS_NAV_TITLE        12701
#define VS_NAV_ZRCOLOR      12702
#define VS_NAV_REALTIME     12703

#define VS_SELSTLINE        12801

#define VS_ENT_TITLE    13001
#define VS_ENT_LAYER    13002
#define VS_ENT_LTYPE    13003
#define VS_ENT_PAGE     13004
#define VS_ENT_LCOL     13005
#define VS_ENT_FCOL     13006
#define VS_ENT_BYLAY    13007
#define VS_ENT_FILLED   13008
#define VS_ENT_BORDER   13009
#define VS_ENT_LINEW    13010
#define VS_ENT_LEVEL    13011
#define VS_ENT_LIMITS   13012
#define VS_ENT_HANDLE   13013
#define VS_ENT_KEY      13014

#define VS_ARR_TITLE    13031
#define VS_ARR_DIMST0   13032
#define VS_ARR_DIMST1   13033

#define VS_LINE_TITLE       13101
#define VS_LINE_PNT1        13102
#define VS_LINE_PNT2        13103
#define VS_LINE_ARROW       13104
#define VS_LINE_NOARROW     13105
#define VS_LINE_LENGTH      13106
#define VS_LINE_ANGLE       13107

#define VS_TEXT_TITLE       13201
#define VS_TEXT_TITLE2      13202
#define VS_TEXT_TA_LEFBOT   13203
#define VS_TEXT_TA_MIDBOT   13204
#define VS_TEXT_TA_RIGBOT   13205
#define VS_TEXT_TA_LEFMID   13206
#define VS_TEXT_TA_MIDMID   13207
#define VS_TEXT_TA_RIGMID   13208
#define VS_TEXT_TA_LEFTOP   13209
#define VS_TEXT_TA_MIDTOP   13210
#define VS_TEXT_TA_RIGTOP   13211
#define VS_TEXT_NO_PATH     13212
#define VS_TEXT_POINT       13221
#define VS_TEXT_HEIGHT      13222
#define VS_TEXT_WIDTH       13223
#define VS_TEXT_ROTANG      13224
#define VS_TEXT_IVERT       13225
#define VS_TEXT_IHORZ       13226
#define VS_TEXT_ALIGN       13227
#define VS_TEXT_STYLE       13228
#define VS_TEXT_TEXT        13229
#define VS_TEXT_OBLIQUE     13230
#define VS_TEXT_STRIKEOUT   13231
#define VS_TEXT_UNDERLINE   13232
#define VS_TEXT_PTWRITE     13241
#define VS_TEXT_PTBACK      13242
#define VS_TEXT_PTABSANG    13243
#define VS_TEXT_PTHANDLE    13244
#define VS_TEXT_PTDY        13245
#define VS_TEXT_PTDX        13246

#define VS_CIRC_TITLE       13301
#define VS_CIRC_CENTER      13302
#define VS_CIRC_RADIUS      13303
#define VS_CIRC_LENGTH      13304
#define VS_CIRC_AREA        13305

#define VS_POLY_TITLE       13401
#define VS_POLY_LINE        13402
#define VS_POLY_BSPLINE2    13403
#define VS_POLY_BSPLINE3    13404
#define VS_POLY_FITBSPL3    13405
#define VS_POLY_LINBSPL2    13406
#define VS_POLY_AUTOBEZIER  13407
#define VS_POLY_BEZIER      13408
#define VS_POLY_ROUNDED     13409
#define VS_POLY_MULTIRAD    13410
#define VS_POLY_BULGE       13411
#define VS_POLY_CLOSED      13421
#define VS_POLY_SMOOTH      13422
#define VS_POLY_RAD         13423
#define VS_POLY_PERIM       13424
#define VS_POLY_AREA        13425
#define VS_POLY_DIMST0      13429
#define VS_POLY_DIMST1      13430
#define VS_POLY_NVER        13434
#define VS_POLY_VERTABLE    13435

#define VS_PVER_TITLE       13451
#define VS_PVER_ONLINE      13452
#define VS_PVER_OFFLINE     13453
#define VS_PVER_CLOSE       13454
#define VS_PVER_ADD         13455
#define VS_PVER_INSERT      13456
#define VS_PVER_DELETE      13457
#define VS_PVER_RADIUS      13458
#define VS_PVER_ONCURVE     13459
#define VS_PVER_BULGE       13460
#define VS_PVER_LENGTH      13461
#define VS_PVER_ANGLE       13462

#define VS_INSBLK_TITLE     13501
#define VS_INSBLK_NAME      13502
#define VS_INSBLK_POINT     13503
#define VS_INSBLK_ANGLE     13504
#define VS_INSBLK_SCX       13505
#define VS_INSBLK_SCY       13506
#define VS_INSBLK_WIDTH     13507
#define VS_INSBLK_HEIGHT    13508
#define VS_INSBLK_BYLAY     13509

#define VS_HATCH_TITLE      13601
#define VS_HATCH_NAME       13602
#define VS_HATCH_ANGLE      13603
#define VS_HATCH_SCALE      13604
#define VS_HATCH_SIZE       13605

#define VS_POINT_TITLE      13701
#define VS_POINT_TYPE       13703
#define VS_POINT_BLKANG     13704
#define VS_POINT_TEXT       13705
#define VS_POINT_TXTANG     13706
#define VS_POINT_TXTOFFSET  13707
#define VS_POINT_FIXED      13708

#define VS_BMP_TITLE        13801
#define VS_BMP_FILE         13802
#define VS_BMP_INS          13803
#define VS_BMP_RES          13804
#define VS_BMP_RESH         13805
#define VS_BMP_RESV         13806
#define VS_BMP_WIDTH        13807
#define VS_BMP_HEIGHT       13808
#define VS_BMP_RELOAD       13809

#define VS_ELL_TITLE        13901
#define VS_ELL_CENTER       13902
#define VS_ELL_RADIUS       13903
#define VS_ELL_RH           13904
#define VS_ELL_RV           13905
#define VS_ELL_ANGLE        13906
#define VS_ELL_LEN          13907
#define VS_ELL_AREA         13908

#define VS_ARC_TITLE        14001
#define VS_ARC_CENTER       14002
#define VS_ARC_TYPE         14007
#define VS_ARC_ARC          14008
#define VS_ARC_CHORD        14009
#define VS_ARC_SECTOR       14010
#define VS_ARC_LEN          14013
#define VS_ARC_AREA         14014
#define VS_ARC_RADIUS       14021
#define VS_ARC_RH           14022
#define VS_ARC_RV           14023
#define VS_ARC_ANG0         14024
#define VS_ARC_ANGARC       14025
#define VS_ARC_ANGROT       14026

#define VS_RECT_TITLE       14101
#define VS_RECT_CENTER      14102
#define VS_RECT_W           14103
#define VS_RECT_H           14104
#define VS_RECT_RAD         14105
#define VS_RECT_ANG         14106
#define VS_RECT_LEN         14107
#define VS_RECT_AREA        14108

#define VS_SYMB_TITLE       14201
#define VS_SYMB_HEIGHT      14202
#define VS_SYMB_FONT        14203

#define VS_DIM_TITLE        14401
#define VS_DIM_HORZ         14402
#define VS_DIM_VERT         14403
#define VS_DIM_PARAL        14404
#define VS_DIM_ANG          14405
#define VS_DIM_RAD          14406
#define VS_DIM_DIAM         14407
#define VS_DIM_ORD          14408
#define VS_DIM_OWN          14412
#define VS_DIM_TYPE         14413
#define VS_DIM_MEASURE      14414
#define VS_DIM_VALUE        14415
#define VS_DIM_STYLE        14416

#define VS_INSDWG_TITLE     14501
#define VS_INSDWG_FNAME     14502
#define VS_INSDWG_INSPNT    14503
#define VS_INSDWG_ANGLE     14504
#define VS_INSDWG_SCX       14505
#define VS_INSDWG_SCY       14506
#define VS_INSDWG_WIDTH     14507
#define VS_INSDWG_HEIGHT    14508
#define VS_INSDWG_RELOAD    14509

#define VS_PRINT_TITLE      16001
#define VS_PRINT_PRINTER    16002
#define VS_PRINT_PICK       16003
#define VS_PRINT_FIT        16004
#define VS_PRINT_ALL        16005
#define VS_PRINT_PAGE       16006
#define VS_PRINT_PRECT      16007
#define VS_PRINT_DISP       16008
#define VS_PRINT_WIN        16009
#define VS_PRINT_PGALL      16010
#define VS_PRINT_PGCUR      16011
#define VS_PRINT_PGNO       16012
#define VS_PRINT_CURPRN     16013
#define VS_PRINT_PAPERSIZE  16014
#define VS_PRINT_RES        16015
#define VS_PRINT_REGION     16016
#define VS_PRINT_WLEFBOT    16017
#define VS_PRINT_WRIGTOP    16018
#define VS_PRINT_REGSIZE    16019
#define VS_PRINT_SCALE      16020
#define VS_PRINT_ATX        16021
#define VS_PRINT_ATY        16022
#define VS_PRINT_ORIGIN     16023
#define VS_PRINT_COPIES     16024
#define VS_PRINT_PAGES      16025
#define VS_PRINT_PRECTS     16026
#define VS_PRINT_ALBUM      16027
#define VS_PRINT_BOOK       16028

#define VS_EXPBMP_TITLE     16101
#define VS_EXPBMP_FILE      16102
#define VS_EXPBMP_AREA      16103
#define VS_EXPBMP_ALL       16104
#define VS_EXPBMP_DISP      16105
#define VS_EXPBMP_WIN       16106
#define VS_EXPBMP_PICK      16107
#define VS_EXPBMP_LEFBOT    16108
#define VS_EXPBMP_RIGTOP    16109
#define VS_EXPBMP_SIZEMM    16110
#define VS_EXPBMP_RES       16111
#define VS_EXPBMP_SIZEPIX   16112

#define VS_EXPSHP_TITLE     16121
#define VS_EXPSHP_ENTITIES  16122
#define VS_EXPSHP_TYPE      16123
#define VS_EXPSHP_LAYER     16124
#define VS_EXPSHP_ALLLAYERS 16125
#define VS_EXPSHP_SELECTED  16126
#define VS_EXPSHP_CONVERT   16127
#define VS_EXPSHP_ARCS      16128
#define VS_EXPSHP_LATITUDE  16129
#define VS_EXPSHP_LONGITUDE 16130
#define VS_EXPSHP_POINT     16131
#define VS_EXPSHP_POLYLINE  16132
#define VS_EXPSHP_POLYGON   16133
#define VS_EXPSHP_LAYERS_DIFFER 16134

#define VS_PRR_TITLE        16201
#define VS_PRR_EXIT         16202
#define VS_PRR_ADD          16203
#define VS_PRR_DEL          16204
#define VS_PRR_FORALL       16205
#define VS_PRR_MOVE         16206
#define VS_PRR_COLOR        16207
#define VS_PRR_SHOW         16208
#define VS_PRR_HX           16209
#define VS_PRR_HY           16210
#define VS_PRR_HSIZE        16211
#define VS_PRR_HANGLE       16212
#define VS_PRR_CENTER       16213
#define VS_PRR_PRM          16214
#define VS_PRR_W            16215
#define VS_PRR_H            16216
#define VS_PRR_ANG          16217
#define VS_PRR_AUTOSPLIT    16218
#define VS_PRR_ALLDELETE    16219
#define VS_PRR_NOSIZE       16220

#define VS_DIST_TITLE       16301
#define VS_DIST_BYOBJ       16302
#define VS_DIST_START       16303
#define VS_DIST_RESET       16304
#define VS_DIST_DIST        16305
#define VS_DIST_PERIM       16306
#define VS_DIST_ANGLE       16307
#define VS_DIST_AREA        16308
#define VS_DIST_SUMAREA     16309

#define VS_STAT_DWGFILE     17001
#define VS_STAT_FILESIZE    17002
#define VS_STAT_DWGWIDTH    17003
#define VS_STAT_DWGHEIGHT   17004
#define VS_STAT_DWGLEFT     17005
#define VS_STAT_DWGBOTTOM   17006
#define VS_STAT_DWGRIGHT    17007
#define VS_STAT_DWGTOP      17008
#define VS_STAT_DRAWTIME    17009
#define VS_STAT_PAGES       17021
#define VS_STAT_LAYERS      17022
#define VS_STAT_STLINES     17023
#define VS_STAT_STTEXTS     17024
#define VS_STAT_STHATCHS    17025
#define VS_STAT_STDIMS      17026
#define VS_STAT_STPOINTS    17027
#define VS_STAT_BLOCKS      17028
#define VS_STAT_ENTS        17029
#define VS_STAT_POLYVERS    17030
#define VS_STAT_TEXTCHARS   17031
#define VS_STAT_ENTBYLAYER  17041
#define VS_STAT_ENTBYPAGE   17042
#define VS_STAT_ENTBYBLOCK  17043
#define VS_STAT_ENTBYTYPE   17050
#define VS_STAT_POINT       17051
#define VS_STAT_LINE        17052
#define VS_STAT_POLY        17053
#define VS_STAT_CIRCLE      17054
#define VS_STAT_ARC         17055
#define VS_STAT_ELLIPSE     17056
#define VS_STAT_TEXT        17057
#define VS_STAT_BITMAP      17058
#define VS_STAT_INSBLOCK    17059
#define VS_STAT_HATCH       17060
#define VS_STAT_RECT        17061
#define VS_STAT_DIMLIN      17062
#define VS_STAT_DIMANG      17063
#define VS_STAT_DIMRAD      17064
#define VS_STAT_DIMDIAM     17065
#define VS_STAT_DIMORD      17066
#define VS_STAT_FILEVECVER  17070
#define VS_STAT_CURVECVER   17071

#define VS_MENU_ENTPROP     18001
#define VS_MENU_COPY        18002
#define VS_MENU_MOVE        18003
#define VS_MENU_ROTATE      18004
#define VS_MENU_SCALE       18005
#define VS_MENU_MIRROR      18006
#define VS_MENU_CREBLOCK    18007
#define VS_MENU_EXPLODE     18008
#define VS_MENU_ERASE       18009
#define VS_MENU_UNSELALL    18010
#define VS_MENU_JOIN        18011
#define VS_MENU_VER_INS     18021
#define VS_MENU_VER_DEL     18022
#define VS_MENU_VER_RAD     18023
#define VS_MENU_VER_FIX     18024
#define VS_MENU_VER_EDIT    18025

#define VS_SEL_BY_HANDLE    18101
#define VS_ENTER_HANDLE     18102
#define VS_SEL_BY_KEY       18103
#define VS_ENTER_KEY        18104
#define VS_N_WAS_SELECTED   18105

#define VS_GRIDPLINE_TITLE  18151

// tooltips string
#define VS_TT_FILE_NEW      19001
#define VS_TT_FILE_OPEN     19002
#define VS_TT_FILE_SAVE     19003
#define VS_TT_PRINT         19004
#define VS_TT_TOOL_PRNRECT  19005
#define VS_TT_ZOOM_ALL      19006
#define VS_TT_ZOOM_WIN      19007
#define VS_TT_ZOOM_IN       19008
#define VS_TT_ZOOM_OUT      19009
#define VS_TT_ZOOM_PAN      19010
#define VS_TT_ZOOM_PREV     19011
#define VS_TT_ZOOM_SEL      19012
#define VS_TT_PAGE_DLG      19015
#define VS_TT_PAGE_PREV     19016
#define VS_TT_PAGE_NEXT     19017
#define VS_TT_RESET         19021
#define VS_TT_SHOWGRID      19022
#define VS_TT_SHOWLINEW     19023
#define VS_TT_SHOWFILL      19024
#define VS_TT_TOOL_DIST     19025
#define VS_TT_FMT_LAYOUT    19029
#define VS_TT_FMT_STDIM     19030
#define VS_TT_FMT_LAYER     19031
#define VS_TT_EDIT_UNDO     19032
#define VS_TT_EDIT_REDO     19033
#define VS_TT_EDIT_CBCUT    19034
#define VS_TT_EDIT_CBCOPY   19035
#define VS_TT_EDIT_CBPASTE  19036
#define VS_TT_EDIT_ENTPROP  19037
#define VS_TT_EDIT_COPY     19038
#define VS_TT_EDIT_MOVE     19039
#define VS_TT_EDIT_ROTATE   19040
#define VS_TT_EDIT_SCALE    19041
#define VS_TT_EDIT_MIRROR   19042
#define VS_TT_EDIT_ERASE    19043
#define VS_TT_EDIT_EXPLODE  19044
#define VS_TT_EDIT_CREBLOCK 19045
#define VS_TT_DRAW_POINT    19051
#define VS_TT_DRAW_LINE     19052
#define VS_TT_DRAW_POLYLINE 19053
#define VS_TT_DRAW_SPLINE   19054
#define VS_TT_DRAW_CIRC_CR  19055
#define VS_TT_DRAW_CIRC_3P  19056
#define VS_TT_DRAW_ARC_CSE  19057
#define VS_TT_DRAW_ARC_SME  19058
#define VS_TT_DRAW_ELLIPSE  19059
#define VS_TT_DRAW_RECT     19060
#define VS_TT_DRAW_HATCH    19061
#define VS_TT_DRAW_TEXT     19062
#define VS_TT_DRAW_SYMBOL   19063
#define VS_TT_DRAW_BLOCK    19064
#define VS_TT_DRAW_IMAGE    19065
#define VS_TT_DRAW_FLOOD    19066
#define VS_TT_DRAW_DIM_HOR  19071
#define VS_TT_DRAW_DIM_VER  19072
#define VS_TT_DRAW_DIM_PAR  19073
#define VS_TT_DRAW_DIM_ANG  19074
#define VS_TT_DRAW_DIM_RAD  19075
#define VS_TT_DRAW_DIM_DIAM 19076
#define VS_TT_DRAW_DIM_ORD  19077
#define VS_TT_SNAP_END      19101
#define VS_TT_SNAP_MID      19102
#define VS_TT_SNAP_INTER    19103
#define VS_TT_SNAP_CEN      19104
#define VS_TT_SNAP_KNOT     19105
#define VS_TT_SNAP_PERP     19106
#define VS_TT_SNAP_TANG     19107
#define VS_TT_SNAP_POINT    19108
#define VS_TT_SNAP_NEAR     19109
#define VS_TT_SNAP_GRID     19110
#define VS_TT_SNAP_POLAR    19111
#define VS_TT_SNAP_CLEAR    19112
#define VS_TT_SNAP_DLG      19113

#define VS_CC_ZOOMWIN      19201
#define VS_CC_ZOOMPAN      19202
#define VS_CC_PRINT        19203
#define VS_CC_PRNRECT      19204
#define VS_CC_EXPBMP       19205
#define VS_CC_POINT        19206
#define VS_CC_LINE         19207
#define VS_CC_CIRCLE       19208
#define VS_CC_ARC          19209
#define VS_CC_SECTOR       19210
#define VS_CC_ELLIPSE      19211
#define VS_CC_POLYLINE     19212
#define VS_CC_TEXT         19213
#define VS_CC_INSERT       19214
#define VS_CC_HATCH        19215
#define VS_CC_BITMAP       19216
#define VS_CC_SYMBOL       19217
#define VS_CC_RECT         19218
#define VS_CC_DIMHOR       19219
#define VS_CC_DIMVER       19220
#define VS_CC_DIMPAR       19221
#define VS_CC_DIMANG       19222
#define VS_CC_DIMRAD       19223
#define VS_CC_DIMDIAM      19224
#define VS_CC_DIMORD       19225
#define VS_CC_SELBYPOINT   19226
#define VS_CC_SELBYRECT    19227
#define VS_CC_SELBYPOLYGON 19228
#define VS_CC_SELBYPOLYLINE 19229
#define VS_CC_SELBYDIST    19230
#define VS_CC_MOVEGRIP     19231
#define VS_CC_ENTPROP      19232
#define VS_CC_MOVE         19233
#define VS_CC_COPY         19234
#define VS_CC_ROTATE       19235
#define VS_CC_SCALE        19236
#define VS_CC_MIRROR       19237
#define VS_CC_ERASE        19238
#define VS_CC_CREBLOCK     19239
#define VS_CC_EXPLODE      19240
#define VS_CC_SPLINE       19241
#define VS_CC_DIST         19242
#define VS_CC_INSVEC       19243
#define VS_CC_ENTSWAP      19244
#define VS_CC_ENTTOTOP     19245
#define VS_CC_ENTTOBOTTOM  19246

#define VS_SELOBJECTS   19301
#define VS_CORNER1      19302
#define VS_CORNER2      19303
#define VS_BASE_P       19304
#define VS_BASE_P1      19305
#define VS_BASE_P2      19306
#define VS_DISPLACE     19307
#define VS_POINT1       19308
#define VS_POINT2       19309
#define VS_POINT3       19310
#define VS_CENTER_P     19311
#define VS_RAD_P        19312
#define VS_START_P      19313
#define VS_END_P        19314
#define VS_RAD1ANG      19315
#define VS_RAD2         19316
#define VS_NEXT_P       19317
#define VS_INS_P        19318
#define VS_LEADER1      19319
#define VS_LEADER2      19320
#define VS_TEXT_P       19321
#define VS_ORD_P        19322
#define VS_ORD_X        19323
#define VS_ORD_Y        19324
#define VS_MOVE2        19325
#define VS_COPY2        19326
#define VS_ROTATE1      19327
#define VS_ROTATE2      19328
#define VS_ROTATE3      19329
#define VS_SCALE3       19330
#define VS_MIRROR1      19331
#define VS_MIRROR2      19332
#define VS_PICK_ENT     19333
#define VS_PICK_ENT1    19334
#define VS_PICK_ENT2    19335

#define VS_PAPER_UNLIMITED 19401
#define VS_PAPER_A0        19402
#define VS_PAPER_A1        19403
#define VS_PAPER_A2        19404
#define VS_PAPER_A3        19405
#define VS_PAPER_A4        19406
#define VS_PAPER_A5        19407
#define VS_PAPER_A6        19408
#define VS_PAPER_B0        19409
#define VS_PAPER_B1        19410
#define VS_PAPER_B2        19411
#define VS_PAPER_B3        19412
#define VS_PAPER_B4        19413
#define VS_PAPER_B5        19414
#define VS_PAPER_B6        19415
#define VS_PAPER_C0        19416
#define VS_PAPER_C1        19417
#define VS_PAPER_C2        19418
#define VS_PAPER_C3        19419
#define VS_PAPER_C4        19420
#define VS_PAPER_C5        19421
#define VS_PAPER_C6        19422
#define VS_PAPER_ANSI_A    19423
#define VS_PAPER_ANSI_B    19424
#define VS_PAPER_ANSI_C    19425
#define VS_PAPER_ANSI_D    19426
#define VS_PAPER_ANSI_E    19427
#define VS_PAPER_LETTER    19428
#define VS_PAPER_LEGAL     19429
#define VS_PAPER_EXECUTIVE 19430
#define VS_PAPER_LEDGER    19431
#define VS_PAPER_USER      19432



//-------------------------------------
// VeCAD point
//-------------------------------------
typedef struct tagVLPOINT {
  double x;
  double y;
}VLPOINT;


//-------------------------------------
// VeCAD Arc
//-------------------------------------
typedef struct tagVLARC {
  VLPOINT Cen;
  double  Rh;
  double  Rv;
  double  Ang0;
  double  AngArc;
  double  AngRot;
}VLARC;


//-------------------------------------
// used to pass parameters with VM_BEGINPAINT message
//-------------------------------------
typedef struct tagVLPAINTSTRUCT {
    HDC     hdc;         // output device context
    RECT    rcPaint;     // output window rectangle
    double  DwgLeft;     // drawing's limits for the window
    double  DwgBottom;
    double  DwgRight;
    double  DwgTop;
    double  ScaleX;      // horiz. scale, mm/pixel
    double  ScaleY;      // vert. scale, mm/pixel
}VLPAINTSTRUCT;

//-------------------------------------
// Properties of "Navigator" window (aerial view)
//-------------------------------------
typedef struct tagVLNAVIGATOR {
  int      Left;   
  int      Top; 
  int      Width; 
  int      Height;
  COLORREF ColorZoomRect;
  BOOL     Realtime;
}VLNAVIGATOR;

//-------------------------------------
// Properties of "Layers Manager" window
//-------------------------------------
typedef struct tagVLLAYWIN {
  int      Left;       
  int      Top;       
  int      Width;      
  int      Height;    
}VLLAYWIN;



/********************************************************************
*
*     VeCAD functions definitions
*
*********************************************************************/

// comment next definition if you use Vecad.dll with
// non Visual C++ compiler (for example Borland C++ or C++ Builder)
//#define MSVCPP_APP
/*
#ifdef VECDLL_EXPORTS
  #define VC_API _stdcall        // used 'vecdll.def' file
#else
  #ifdef MSVCPP_APP
    // for Visual C++ compiler
    #define VC_API _declspec(dllimport) _stdcall
  #else
    // works with any C/C++ compiler
    #define VC_API _stdcall
    // Load and free Vecad.dll
    BOOL vlStartup ();
    void vlCleanup ();
  #endif
#endif
*/

#define VC_API _stdcall

// Load and free Vecad.dll
BOOL vlStartup ();
void vlCleanup ();


// Drawing's callback function
typedef int (CALLBACK* DWGPROC)(int iDwg, UINT Msg, int Prm1, int Prm2, double Prm3, double Prm4, void* Prm5);

/*
#ifndef __cplusplus
  extern "C" {
#endif
*/

int  VC_API vlGetVersion ();

// Registration for user copy of VeCAD DLL
BOOL VC_API vlRegistration  (int RegCode);

// Set application-defined function that will receive messages from VeCAD
BOOL VC_API vlSetMsgHandler (DWGPROC pfDwgProc);

/////////////////////////////////////////////////
// VeCAD window functions
HWND VC_API vlWndCreate     (HWND hParent, int Style, int X, int Y, int W, int H);
BOOL VC_API vlWndResize     (HWND hVecWnd, int X, int Y, int W, int H);
BOOL VC_API vlWndSetTitle   (HWND hVecWnd, LPCTSTR pTitle);
BOOL VC_API vlWndSetMaxRect (HWND hVecWnd, const RECT* pRect);
BOOL VC_API vlWndSetCursor  (HWND hVecWnd, HCURSOR hCursor);

/////////////////////////////////////////////////
// Drawing object functions
int  VC_API vlDocCreate    (HWND hwVec);
BOOL VC_API vlDocDelete    (int iDwg);
int  VC_API vlDocSetActive (int iDwg);
int  VC_API vlDocGetActive ();
BOOL VC_API vlDocCopy      (int iDwgSrc,int iDwgDest,int Mode);


/////////////////////////////////////////////////
// All Next functions work with current drawing that 
// are set by vlDwgSetCurrent function

/////////////////////////////////////////////////
// Layout (pages,layers, text styles, etc...
// Parameters can be accessed via vlData...
int  VC_API vlPageAdd       (LPCTSTR szName, int Size, int Orient, int W, int H);
BOOL VC_API vlPageDelete    (int Index);
int  VC_API vlPageActive    (int Mode, int Index);
int  VC_API vlPageCount     ();
int  VC_API vlPageIndex     (LPCTSTR szName, int ID);

int  VC_API vlLayerAdd      (LPCTSTR szName, double LineWidth, COLORREF LineColor, COLORREF FillColor);
BOOL VC_API vlLayerDelete   (int Index);
int  VC_API vlLayerActive   (int Index);
int  VC_API vlLayerCount    ();
int  VC_API vlLayerIndex    (LPCTSTR szName, int ID);

int  VC_API vlStLineAdd     (LPCTSTR szName, LPCTSTR szDesc);
BOOL VC_API vlStLineDelete  (int Index);
int  VC_API vlStLineActive  (int Index);
int  VC_API vlStLineCount   ();
int  VC_API vlStLineIndex   (LPCTSTR szName, int ID);

int  VC_API vlStTextAdd     (LPCTSTR szName, LPCTSTR szFont, double Width, double Oblique, int Prec, BOOL Filled, BOOL Bold);
BOOL VC_API vlStTextDelete  (int Index);
int  VC_API vlStTextActive  (int Index);
int  VC_API vlStTextCount   ();
int  VC_API vlStTextIndex   (LPCTSTR szName, int ID);
BOOL VC_API vlStTextReload  ();

int  VC_API vlStHatchAdd    (LPCTSTR szName, LPCTSTR szDesc);
BOOL VC_API vlStHatchDelete (int Index);
int  VC_API vlStHatchActive (int Index);
int  VC_API vlStHatchCount  ();
int  VC_API vlStHatchIndex  (LPCTSTR szName, int ID);

int  VC_API vlStDimAdd      (LPCTSTR szName);
BOOL VC_API vlStDimDelete   (int Index);
int  VC_API vlStDimActive   (int Index);
int  VC_API vlStDimCount    ();
int  VC_API vlStDimIndex    (LPCTSTR szName, int ID);

int  VC_API vlStPointAdd    (LPCTSTR szName);
BOOL VC_API vlStPointDelete (int Index);
int  VC_API vlStPointActive (int Index);
int  VC_API vlStPointCount  ();
int  VC_API vlStPointIndex  (LPCTSTR szName, int ID);

int  VC_API vlGrPointAdd    (LPCTSTR szName);
BOOL VC_API vlGrPointDelete (int Index);
int  VC_API vlGrPointActive (int Index);
int  VC_API vlGrPointCount  ();
int  VC_API vlGrPointIndex  (LPCTSTR szName, int ID);

int  VC_API vlViewSave      (LPCTSTR szName);
BOOL VC_API vlViewDelete    (int Index);
int  VC_API vlViewRestore   (int Index);
int  VC_API vlViewCount     ();
int  VC_API vlViewIndex     (LPCTSTR szName, int ID);

int  VC_API vlPrnRectAdd    (double X, double Y, double W, double H, double Angle);
BOOL VC_API vlPrnRectDelete (int Index);
int  VC_API vlPrnRectCount  ();
BOOL VC_API vlPrnRectPrint  (int Index, HDC hPrintDC, double ScaleX, double ScaleY, double OriginX, double OriginY);
int  VC_API vlPrnRectAuto   (double Width, double Height);

BOOL VC_API vlBlockBegin    ();
int  VC_API vlBlockAdd      (LPCTSTR szName, double x, double y);
int  VC_API vlBlockAddF     (LPCTSTR szFileName, LPCTSTR szBlockName);
BOOL VC_API vlBlockDelete   (int Index);
int  VC_API vlBlockActive   (int Index);
int  VC_API vlBlockCount    ();
int  VC_API vlBlockIndex    (LPCTSTR szName, int ID);


/////////////////////////////////////////////////
// Add graphic objects to drawing database

int  VC_API vlAddPoint      (double X, double Y);
int  VC_API vlAddLine       (double X1, double Y1, double X2, double Y2);
int  VC_API vlAddCircle     (double X, double Y, double Rad);
int  VC_API vlAddCircle3P   (double X1, double Y1, double X2, double Y2, double X3, double Y3);
int  VC_API vlAddArc        (double X, double Y, double Rad, double Ang1, double Ang2);
int  VC_API vlAddArc3P      (double X1, double Y1, double X2, double Y2, double X3, double Y3);
int  VC_API vlAddEllipse    (double X, double Y, double Rh, double Rv, double Angle);
int  VC_API vlAddArcEx      (double X, double Y, double Rh, double Rv, double Ang0, double AngArc, double AngRot);
BOOL VC_API vlSetTextParam  (int Mode, double Var);
BOOL VC_API vlSetTextParams (int Align, double Height, double Angle, double ScaleW, double Oblique, double HInter, double VInter);
int  VC_API vlAddText       (double X, double Y, LPCTSTR szStr);
BOOL VC_API vlPolylineBegin ();
BOOL VC_API vlVertex        (double X, double Y);
BOOL VC_API vlVertexR       (double X, double Y, double Radius);
BOOL VC_API vlVertexF       (double X, double Y, BOOL bOnCurve);
BOOL VC_API vlVertexB       (double X, double Y, double Bulge);
int  VC_API vlAddPolyline   (int SmoothType, BOOL bClosed);
int  VC_API vlAddBlockIns   (int Index, double X, double Y, double Angle, double Xscale, double Yscale);
int  VC_API vlAddHatch      (int Index, double Scale, double Angle);
int  VC_API vlAddRaster     (LPCTSTR FileName, double X, double Y, double ResH, double ResV);
int  VC_API vlAddRect       (double X, double Y, double W, double H, double Ang, double Rad);
int  VC_API vlAddDimHor     (double X1, double Y1, double X2, double Y2, double Y);
int  VC_API vlAddDimVer     (double X1, double Y1, double X2, double Y2, double X);
int  VC_API vlAddDimPar     (double X1, double Y1, double X2, double Y2, double Off);
int  VC_API vlAddDimAng     (double Xcen, double Ycen, double X1, double Y1, double X2, double Y2, double Off);
int  VC_API vlAddDimRad     (double Xcen, double Ycen, double Xrad, double Yrad, double Off);
int  VC_API vlAddDimDiam    (double Xcen, double Ycen, double Xrad, double Yrad);
int  VC_API vlAddDimOrd     (double X, double Y, double Xtxt, double Ytxt, BOOL bYord);
int  VC_API vlAddDwgIns     (LPCTSTR FileName, double X, double Y, double Angle, double ScaleH, double ScaleV, int iPage);
int  VC_API vlAddCustom     (int Type, void* pData, int DataSize, int ElemSize);


/////////////////////////////////////////////////
// Drawing's storage
int  VC_API vlFileNew     (HWND hwVec, LPCTSTR szTemplate);
int  VC_API vlFileOpen    (HWND hwVec, LPCTSTR szFileName);
BOOL VC_API vlFileLoad    (int Mode, LPCTSTR szFileName);
BOOL VC_API vlFileSave    (int Mode, LPCTSTR szFileName);
BOOL VC_API vlFileList    (HWND hwParent);
BOOL VC_API vlFileLoadMem (void* pMem);
int  VC_API vlFileSaveMem (void* pMem, int MaxSize);

/////////////////////////////////////////////////
// Select objects for edit functions
int  VC_API vlGetEntity       (int Mode, int Prm1, int Prm2);
int  VC_API vlGetBlockEntity  (int iBlock, int Counter);
BOOL VC_API vlSelect          (BOOL bSelect, int Index);
int  VC_API vlSelectByPoint   (BOOL bSelect, double X, double Y, double Delta);
int  VC_API vlSelectByRect    (BOOL bSelect, double Left, double Bottom, double Right, double Top, BOOL Cross);
int  VC_API vlSelectByPolygon (BOOL bSelect, const VLPOINT* Ver, int nver, BOOL bCross);
int  VC_API vlSelectByPolyline(BOOL bSelect, const VLPOINT* Ver, int nver);
int  VC_API vlSelectByDist    (BOOL bSelect, double X, double Y, double Dist, BOOL bCross);

/////////////////////////////////////////////////
// Edit objects functions
// iObj - index of the object, 
// if iObj=-1 then operate with selected objects
BOOL VC_API vlCbCut         ();
BOOL VC_API vlCbCopy        ();
BOOL VC_API vlCbPaste       (double X, double Y);
int  VC_API vlCopy          (int iObj, double dx, double dy);
BOOL VC_API vlMove          (int iObj, double dx, double dy);
BOOL VC_API vlRotate        (int iObj, double X, double Y, double Angle);
BOOL VC_API vlScale         (int iObj, double X, double Y, double Scale);
BOOL VC_API vlMirror        (int iObj, double X1, double Y1, double X2, double Y2);
BOOL VC_API vlErase         (int iObj);
BOOL VC_API vlExplode       (int iObj);
BOOL VC_API vlJoin          (double Delta);
BOOL VC_API vlUndo          ();
BOOL VC_API vlRedo          ();
BOOL VC_API vlPolyVerInsert (int iEnt, int iVer);
BOOL VC_API vlPolyVerDelete (int iEnt, int iVer);
BOOL VC_API vlPolyVerGet    (int iEnt, int iVer, double* pX, double* pY, double* pPrm);
BOOL VC_API vlPolyVerSet    (int iEnt, int iVer, double X, double Y, double Prm);
BOOL VC_API vlGripGet       (int iObj, int iGrip, double* pX, double* pY);
BOOL VC_API vlGripSet       (int iObj, int iGrip, double X, double Y);
BOOL VC_API vlGripMove      (int iObj, int iGrip, double dx, double dy);

/////////////////////////////////////////////////
// Access to objects properties
int    VC_API vlPropGet    (int PropID, int iObj, void* pData);
int    VC_API vlPropGetInt (int PropID, int iObj);
double VC_API vlPropGetDbl (int PropID, int iObj);
int    VC_API vlPropPut    (int PropID, int iObj, void* pData);
int    VC_API vlPropPutInt (int PropID, int iObj, int Value);
int    VC_API vlPropPutDbl (int PropID, int iObj, double Value);


/////////////////////////////////////////////////
// Zooming drawing in a window
BOOL VC_API vlZoom     (double Scale);
BOOL VC_API vlZoomRect (double Left, double Bottom, double Right, double Top);
BOOL VC_API vlZoomPan  (double dx, double dy);

/////////////////////////////////////////////////
// Coordinates convertions
BOOL VC_API vlCoordWinToDwg (int Xwin, int Ywin, double* pXdwg, double* pYdwg);
BOOL VC_API vlCoordDwgToWin (double Xdwg, double Ydwg, int* pXwin, int* pYwin);
BOOL VC_API vlLenWinToDwg   (int Lwin, double* pLdwg);
BOOL VC_API vlLenDwgToWin   (double Ldwg, int* pLwin);


/////////////////////////////////////////////////
// draw graphics primitives
BOOL VC_API vlSetDrawPen   (double Width, COLORREF Color);
BOOL VC_API vlDrawPoint    (double X, double Y, int Type, int Size);
BOOL VC_API vlDrawLine     (double X1, double Y1, double X2, double Y2);
BOOL VC_API vlDrawPolyline (const VLPOINT* Ver, int n_ver, BOOL bClosed);
BOOL VC_API vlDrawPolygon  (const VLPOINT* Ver, int n_ver, BOOL bFill, BOOL bBorder, COLORREF FillColor);
BOOL VC_API vlDrawCircle   (double X, double Y, double Rad);
BOOL VC_API vlDrawArc      (double X, double Y, double Rad, double Angle1, double Angle2);
BOOL VC_API vlDrawEllipse  (double X, double Y, double Rh, double Rv, double Angle);
BOOL VC_API vlDrawText     (double X, double Y, LPCTSTR szText);
BOOL VC_API vlDrawBitmap   (HBITMAP hbm, int W, int H, double X, double Y, double ResX, double ResY);
BOOL VC_API vlDrawEntity   (int Index, double Xbase, double Ybase, double Xins, double Yins, double Angle, double ScaleX, double ScaleY);


/////////////////////////////////////////////////
// misc
BOOL VC_API vlExecute      (int IdCmd);   // VL_CM_...
BOOL VC_API vlSetAccKey    (int IdCmd, int VirtKey, int Flags);
BOOL VC_API vlClear        (BOOL bSetDefLayout);
BOOL VC_API vlSetFocus     ();
BOOL VC_API vlUpdate       ();
BOOL VC_API vlRedraw       ();
BOOL VC_API vlReset        ();
BOOL VC_API vlPrintSetup   (HWND hParent);
BOOL VC_API vlPrint        (HDC hPrintDC, double Left, double Bottom, double Right, double Top, double ScaleX, double ScaleY, double OriginX, double OriginY);
BOOL VC_API vlDoRaster     (LPCTSTR szFileName, double Left, double Bottom, double Right, double Top, double Res);
BOOL VC_API vlGetWinSize   (HWND hWnd, int* pWidth, int* pHeight);
BOOL VC_API vlSetTimer     (int ID, int Elapse);
BOOL VC_API vlKillTimer    (int ID);
BOOL VC_API vlPolyGetDist  (int iEnt, double X, double Y, double* pOff);
double VC_API vlGetArea    (double X, double Y);

/////////////////////////////////////////////////
// Additional VeCAD controls

// Toolbar
HWND VC_API vlToolBarCreate  (HWND hwParent, int Id, int X, int Y, int W, int H, int* pW, int* pH);
BOOL VC_API vlToolBarButton  (int Id);
// Statusbar
HWND VC_API vlStatBarCreate  (HWND hwParent, int* pH);
BOOL VC_API vlStatBarResize  ();
BOOL VC_API vlStatBarSetText (int iPart, LPCTSTR szText);
// Progress indicator
BOOL VC_API vlIndicCreate   (HWND Parent, LPCTSTR szTitle);
BOOL VC_API vlIndicDestroy  ();
BOOL VC_API vlIndicSetRange (int nFrom,int nTo);
BOOL VC_API vlIndicSetPos   (int iPos);
BOOL VC_API vlIndicSetText  (LPCTSTR szText);
BOOL VC_API vlIndicStep     ();
// "Navigator" window
HWND VC_API vlNavCreate     (HWND hWndParent, HWND hVecWnd, int wstyle, int X, int Y, int W, int H);
BOOL VC_API vlNavResize     (int X, int Y, int W, int H);
BOOL VC_API vlNavUpdate     ();
BOOL VC_API vlNavGetProp    (VLNAVIGATOR* pProp);
BOOL VC_API vlNavPutProp    (const VLNAVIGATOR* pProp);
// "Layers Manager" window
HWND VC_API vlLayWinCreate  (HWND hWndParent, int Style, int X, int Y, int W, int H);
BOOL VC_API vlLayWinResize  (int X, int Y, int W, int H);
BOOL VC_API vlLayWinGetProp (VLLAYWIN* pProp);
BOOL VC_API vlLayWinPutProp (const VLLAYWIN* pProp);
// Set order of entities
BOOL VC_API vlEntSwap       (int iEnt1, int iEnt2);
BOOL VC_API vlEntToTop      (int iEnt);
BOOL VC_API vlEntToBottom   (int iEnt);


BOOL VC_API gmPointRotate  (double X, double Y, double Xc, double Yc, double Angle, double* pXnew, double* pYnew);

LPCTSTR VC_API vuGetAppDir   (LPCTSTR szFileName);
LPCTSTR VC_API vuGetFileExt  (LPCTSTR szFileName, LPTSTR szExt);
LPCTSTR VC_API vuGetFileDir  (LPCTSTR szFileName);
LPCTSTR VC_API vuGetFileName (LPCTSTR szFileName);
BOOL    VC_API vuGetSaveFileName (HWND hParent, LPCTSTR szFilter, LPCTSTR szDefExt, LPCTSTR szDir, LPTSTR szFileName);
BOOL    VC_API vuGetOpenFileName (HWND hParent, LPCTSTR szFilter, LPCTSTR szDefExt, LPCTSTR szDir, LPTSTR szFileName);
int     VC_API vuSearchFile  (LPCTSTR szFileName, LPTSTR szFindName);

/*
#ifndef __cplusplus
  }
#endif
*/

#endif  // VECAPI_H
