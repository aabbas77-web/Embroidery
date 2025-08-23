(********************************************************************
* VeCAD version 5.2.10
* Copyright (c) 1999-2001 by Oleg Kolbaskin.
* All rights reserved.
*
* This file must be included in Delphi project 
* that used library VeCad.dll
*********************************************************************)
unit api_VecApi;

interface
uses
  Windows;

const

VL_FALSE = 0;
VL_TRUE = 1;

// VeCAD window styles (vlWndCreate)
VL_WS_CHILD   =  1;
VL_WS_TILED   =  2;
VL_WS_BORDER  =  4;
VL_WS_SCROLL  =  8;
VL_WS_DEFAULT = VL_WS_CHILD+VL_WS_SCROLL;

/////////////////////////////////////////////////
// VeCAD objects
VL_OBJ_PAGE      = 1;
VL_OBJ_LAYER     = 2;
VL_OBJ_STLINE    = 3;
VL_OBJ_MLINE     = 4;
VL_OBJ_STTEXT    = 5;
VL_OBJ_STHATCH   = 6;
VL_OBJ_STDIM     = 7;
VL_OBJ_STPOINT   = 8;
VL_OBJ_GRPOINT   = 9;
VL_OBJ_VIEW      = 10;
VL_OBJ_PRNRECT   = 11;
VL_OBJ_BLOCK     = 12;
VL_ENT_POINT     = 21;   // Point
VL_ENT_LINE      = 22;   // Line
VL_ENT_POLY      = 23;   // Polyline
VL_ENT_POLYLINE  = 23;   // 
VL_ENT_CIRCLE    = 24;   // Circle
VL_ENT_ARC       = 25;   // Arc
VL_ENT_ARC2      = 26;   // Arc 2 
VL_ENT_EARC      = 26;   // Arc elliptical
VL_ENT_ELLIPSE   = 27;   // Ellipse
VL_ENT_TEXT      = 28;   // Text
VL_ENT_BITMAP    = 29;   // Raster image
VL_ENT_INSBLOCK  = 30;   // Block's insertion
VL_ENT_BLOCKINS  = 30;   // 
VL_ENT_HATCH     = 31;   // Hatch
VL_ENT_FLOOD     = 32;   // Flood
VL_ENT_RECT      = 34;   // Rectangle
VL_ENT_DIMLIN    = 35;   // Dimension Linear
VL_ENT_DIMANG    = 36;   //   Angular
VL_ENT_DIMRAD    = 37;   //   Radius
VL_ENT_DIMDIAM   = 38;   //   Diameter
VL_ENT_DIMORD    = 39;   //   Ordinate
VL_ENT_INSDWG    = 41;   // Drawing's insertion
VL_ENT_DWGINS    = 41;   // 
VL_ENT_CUSTOM    = 255;  // Custom object

// Values for Mode argument of vlGetEntity
VL_EI_BYHANDLE   = 1;   // Prm1=ID
VL_EI_BYKEY      = 2;   // Prm1=Key
VL_EI_BYPOINT    = 3;   // Prm1=X, Prm2=Y
VL_EI_BYCURSOR   = 4;   //
VL_EI_FIRST      = 6;   //
VL_EI_NEXT       = 7;

// Filter type for VL_EI_FIRST
VL_DRAWING       = 0;   // All visible entities on active page
VL_SELECTION     = 1;   // Selection set

// Start page in "Drawing's Layout" dialog (vlDlgLayout)
VL_DPG_LAST     = -1;
VL_DPG_PAGE     = 0;
VL_DPG_LAYER    = 1;
VL_DPG_STLINE   = 2;
VL_DPG_MLINE    = 3;
VL_DPG_STTEXT   = 4;
VL_DPG_STHATCH  = 5;
VL_DPG_BLOCK    = 6;
VL_DPG_STPOINT  = 7;
VL_DPG_GRID     = 0;
VL_DPG_OBJSNAP  = 1;
VL_DPG_POLSNAP  = 2;

// IO Indexes for vlFileLoad and vlFileSave functions
VL_FILE_VEC    = 1;
VL_FILE_DXF    = 2;
VL_FILE_CNC    = 3;
VL_FILE_HPGL   = 4;
VL_FILE_PLT    = 4;
VL_FILE_VDF    = 5;
VL_FILE_DWG    = 6;
VL_FILE_AVSHP  = 7;
VL_FILE_ALL    = 100;
VL_FILE_CUSTOM = 101;
VL_FILE_DROPS  = 102;
VL_FILE_LINES  = 103;

// Parameters for vlZoom function
VL_ZOOM_ALL   = -1;
VL_ZOOM_IN    = -2;
VL_ZOOM_OUT   = -3;
VL_ZOOM_LEFT  = -4;
VL_ZOOM_RIGHT = -5;
VL_ZOOM_UP    = -6;
VL_ZOOM_DOWN  = -7;
VL_ZOOM_PAGE  = -8;
VL_ZOOM_PREV  = -9;
VL_ZOOM_SEL   = -10;

// Color constants
VL_COL_BLACK       = $00000000; // RGB(   0,   0,   0)
VL_COL_DIMGRAY     = $00696969; // RGB( 105, 105, 105)
VL_COL_DARKGRAY    = $00808080; // RGB( 128, 128, 128)
VL_COL_GRAY        = $00A9A9A9; // RGB( 169, 169, 169)
VL_COL_SILVER      = $00C0C0C0; // RGB( 192, 192, 192)
VL_COL_LIGHTGRAY   = $00D3D3D3; // RGB( 211, 211, 211)
VL_COL_GAINSBORO   = $00DCDCDC; // RGB( 220, 220, 220)
VL_COL_WHITESMOKE  = $00F5F5F5; // RGB( 245, 245, 245)
VL_COL_WHITE       = $00FFFFFF; // RGB( 255, 255, 255)
VL_COL_RED         = $000000FF; // RGB( 255,   0,   0)
VL_COL_GREEN       = $00008000; // RGB(   0, 128,   0)
VL_COL_BLUE        = $00FF0000; // RGB(   0,   0, 255)
VL_COL_CYAN        = $00FFFF00; // RGB(   0, 255, 255)
VL_COL_MAGENTA     = $00FF00FF; // RGB( 255,   0, 255)
VL_COL_YELLOW      = $0000FFFF; // RGB( 255, 255,   0)
VL_COL_DARKRED     = $0000008B; // RGB( 139,   0,   0)
VL_COL_DARKGREEN   = $00006400; // RGB(   0, 100,   0)
VL_COL_DARKBLUE    = $008B0000; // RGB(   0,   0, 139)
VL_COL_DARKCYAN    = $008B8B00; // RGB(   0, 139, 139)
VL_COL_DARKMAGENTA = $008B008B; // RGB( 139,   0, 139)
VL_COL_BROWN       = $002A2AA5; // RGB( 165,  42,  42)

// page paper size
VL_PAPER_UNLIMITED = 0;
VL_PAPER_A0        = 1;
VL_PAPER_A1        = 2;
VL_PAPER_A2        = 3;
VL_PAPER_A3        = 4;
VL_PAPER_A4        = 5;
VL_PAPER_A5        = 6;
VL_PAPER_A6        = 7;
VL_PAPER_B0        = 11;
VL_PAPER_B1        = 12;
VL_PAPER_B2        = 13;
VL_PAPER_B3        = 14;
VL_PAPER_B4        = 15;
VL_PAPER_B5        = 16;
VL_PAPER_B6        = 17;
VL_PAPER_C0        = 21;
VL_PAPER_C1        = 22;
VL_PAPER_C2        = 23;
VL_PAPER_C3        = 24;
VL_PAPER_C4        = 25;
VL_PAPER_C5        = 26;
VL_PAPER_C6        = 27;
VL_PAPER_ANSI_A    = 31;
VL_PAPER_ANSI_B    = 32;
VL_PAPER_ANSI_C    = 33;
VL_PAPER_ANSI_D    = 34;
VL_PAPER_ANSI_E    = 35;
VL_PAPER_LETTER    = 36;
VL_PAPER_LEGAL     = 37;
VL_PAPER_EXECUTIVE = 38;
VL_PAPER_LEDGER    = 39;
VL_PAPER_USER      = 255;

// paper orientation 
VL_PAPER_PORTRAIT   = 1;
VL_PAPER_LANDSCAPE  = 2;
VL_PAPER_BOOK       = 1;
VL_PAPER_ALBUM      = 2;

// Modes of Page select
VL_PAGE_POS   = 0;     // go to the page index
VL_PAGE_NEXT  = 1;     // view next page
VL_PAGE_PREV  = 2;     // view previous page
VL_PAGE_FIRST = 3;     // go to the first page
VL_PAGE_LAST  = 4;     // go to the last page
VL_PAGE_NAME  = 5;     // go to page by name
VL_PAGE_DLG   = 6;     // select page by dialog

// modes for vlSetTextParam
VL_TEXT_ALIGN     = 1;
VL_TEXT_HEIGHT    = 2;
VL_TEXT_ANGLE     = 3;
VL_TEXT_WSCALE    = 4;
VL_TEXT_OBLIQUE   = 5;
VL_TEXT_HINTER    = 6;
VL_TEXT_VINTER    = 7;
VL_TEXT_STRIKEOUT = 8;
VL_TEXT_UNDERLINE = 9;

// text alignment types
VL_TA_LEFBOT = 0;     // to left bottom
VL_TA_CENBOT = 1;     // to center bottom
VL_TA_RIGBOT = 2;     // to right bottom
VL_TA_LEFCEN = 3;     // to left center
VL_TA_CENCEN = 4;     // to center
VL_TA_RIGCEN = 5;     // to right center
VL_TA_LEFTOP = 6;     // to left top
VL_TA_CENTOP = 7;     // to center top
VL_TA_RIGTOP = 8;     // to right top

// measurement units
VL_UNIT_POINT    = 1;
VL_UNIT_MM       = 2;  // millimeter
VL_UNIT_CM       = 3;  // cantimeter
VL_UNIT_INCH     = 4;  // inch
VL_UNIT_FOOT     = 5;  // Foot
VL_UNIT_YARD     = 6;  // Yard
VL_UNIT_MET      = 7;  // meter
VL_UNIT_KM       = 8;  // kilometer
VL_UNIT_MILE     = 9;
VL_UNIT_SEAMILE  = 10;
VL_ANG_DEGREE    = 21;  // Angle °
VL_ANG_RADIAN    = 22;  // Angle rad.

// view types for simple point (vlDrawPoint)
VL_PNT_DEFAULT  = 0;
VL_PNT_CIRCLE   = 1;
VL_PNT_RECT     = 2;
VL_PNT_GRIP     = 2;
VL_PNT_CROSS    = 3;
VL_PNT_CROSS45  = 4;
VL_PNT_POINT    = 5;
VL_PNT_BPIXEL   = 6;
VL_PNT_WPIXEL   = 7;
VL_PNT_ROMB     = 8;
VL_PNT_GRIPM    = 10;
VL_PNT_GRIPR    = 11;
VL_PNT_KNOT     = 12;
VL_PNT_KNOT2    = 13;

// Arrow types
VL_ARROW_NONE     = 0;
VL_ARROW_2LINE    = 1;
VL_ARROW_3LINE    = 2;
VL_ARROW_3LINE_S  = 3;
VL_ARROW_4LINE    = 4;
VL_ARROW_4LINE_S  = 5;
VL_ARROW_SLASH    = 6;
VL_ARROW_CIRC     = 7;
VL_ARROW_CIRC_S   = 8;
VL_ARROW_COUNT    = 9;       // count of arrows types

// Polyline flags
VL_POLY_LINE        = 0;   // linear polyline (no smooth)
VL_POLY_BSPLINE2    = 1;   // quadratic B-spline
VL_POLY_BSPLINE3    = 2;   // cubic B-spline
VL_POLY_FITBSPL3    = 3;   // fitted cubic B-spline
VL_POLY_LINBSPL2    = 4;   // linear/quadratic curve
VL_POLY_BEZIER      = 5;   // bezier curve
VL_POLY_AUTOBEZIER  = 6;   // bezier curve with auto control points
VL_POLY_ROUNDED     = 7;   // rounded vertexes
VL_POLY_MULTIRAD    = 8;   // multi-rad curve
VL_POLY_BULGE       = 9;   // bulge segments
VL_POLY_MAXSMTYPE   = 9;   // max value for smooth type
VL_POLY_CUSTOM      = 128;    // custom draw

// type of dimension
VL_DIM_HORZ       = 0;  // horizontal
VL_DIM_VERT       = 1;  // vertical
VL_DIM_PARAL      = 2;  // parallel
VL_DIM_ANG        = 3;  // Angular
VL_DIM_RAD        = 4;  // Radius
VL_DIM_DIAM       = 5;  // Diameter
VL_DIM_ORDX       = 6;  // Ordinate X
VL_DIM_ORDY       = 7;  // Ordinate Y
// dim. text alignment
VL_DIM_TA_ABOVE   = 0;
VL_DIM_TA_CENTER  = 1;
VL_DIM_TA_BELOW   = 2;

// Coord. Grid types
VL_GRID_POINT     = 0;   // point
VL_GRID_CROSS     = 1;   // cross
VL_GRID_CROSS45   = 2;   // cross 45 degree
VL_GRID_LINE      = 3;   // solid line
VL_GRID_DOTLINE   = 4;   // dot line
VL_GRID_DASHLINE  = 5;   // dash line

// flags for accelerator keys (vlSetAccKey)
VL_KEY_CTRL   = 1;   //0x01;
VL_KEY_SHIFT  = 2;   //0x02;

// Object Snap flags
VL_SNAP_END     = 1;   // 0x0001
VL_SNAP_MID     = 2;   // 0x0002
VL_SNAP_CENTER  = 4;   // 0x0004
VL_SNAP_POINT   = 8;   // 0x0008
VL_SNAP_INTER   = 16;  // 0x0010
VL_SNAP_NEAR    = 32;  // 0x0020
VL_SNAP_GRIPS   = 64;  // 0x0040
VL_SNAP_PERP    = 256; // 0x0100
VL_SNAP_TANG    = 512; // 0x0200
VL_SNAP_GRID    = 4096;   // 0x1000
VL_SNAP_POLAR   = 8192;   // 0x2000
VL_SNAP_OBJECT  = 4095;   // 0x0FFF
VL_SNAP_REALTIME = 32768;

// Toolbars type (vlToolBarCreate)
VL_TB_MAIN  = 4861;
VL_TB_DRAW  = 4862;
VL_TB_EDIT  = 4863;
VL_TB_SNAP  = 4864;

// ComboBox type (for toolbar)
VL_CB_LAYER   = 4871;
VL_CB_STLINE  = 4872;
VL_CB_STTEXT  = 4873;
VL_CB_COLOR   = 4874;

// index of statusbar part (vlStatBarSetText)
VL_SB_COORD   = 0;
VL_SB_CURCMD  = 1;
VL_SB_PROMPT  = 2;

// separator types
// used as value for VD_SDECIMAL property
VL_SEP_POINT  = 0;
VL_SEP_COMMA  = 1;

// Styles of "Navigator" window
VL_NAV_CHILD = 0;
VL_NAV_FLOAT = 1;

// Styles of "Layers manager" window
VL_LAYWIN_CHILD = 0;
VL_LAYWIN_FLOAT = 1;


/////////////////////////////////////////////////
// VeCAD messages, passed to drawing procedure
VM_GETSTRING    = 1;
VM_ERROR        = 2;
VM_ZOOM         = 3;
VM_ZOOMMIN      = 4;
VM_ZOOMMAX      = 5;
VM_BEGINPAINT   = 6;
VM_ENDPAINT     = 7;
VM_LBPAINT      = 8;
VM_OBJADD       = 11;
VM_OBJDELETE    = 12;
VM_OBJACTIVE    = 13;
VM_ENTADD       = 14;
VM_ENTDELETE    = 15;
VM_ENTSELECT    = 16;
VM_ENTUNSELECT  = 17;
VM_ENTCOPY      = 20;
VM_ENTMOVE      = 21;
VM_ENTROTATE    = 22;
VM_ENTSCALE     = 23;
VM_ENTMIRROR    = 24;
VM_ENTERASE     = 25;
VM_ENTEXPLODE   = 26;
VM_ENTPROPDLG   = 27;
VM_ENTINDEX     = 28;
VM_KEYDOWN      = 41;
VM_MOUSEMOVE    = 42;
VM_LBDOWN       = 43;
VM_LBDBLCLK     = 44;
VM_RBDOWN       = 45;
VM_KEYUP        = 46;
VM_LBUP         = 47;
VM_RBUP         = 48;
VM_MBDOWN       = 49;
VM_MBUP         = 50;
VM_TOOLCREATE   = 51;
VM_CMD_CREATE   = 51;
VM_TOOLOPEN     = 52;
VM_CMD_OPEN     = 52;
VM_TOOLCLOSE    = 53;
VM_CMD_CLOSE    = 53;
VM_TOOLCLICK    = 54;
VM_CMD_CLICK    = 54;
VM_TOOLDRAG     = 55;
VM_CMD_DRAG     = 55;
VM_TOOLREDRAW   = 56;
VM_CMD_REDRAW   = 56;
VM_CANCELTOOL   = 57;
VM_CANCELCMD    = 57;
VM_REPEATTOOL   = 58;
VM_REPEATCMD    = 58;
VM_MENUEDIT     = 61;
VM_MENUVER      = 62;
VM_EXECUTE      = 100;
VM_EXECUTED     = 101;
VM_DWGCREATE    = 102;
VM_DWGDELETE    = 103;
VM_DWGCLEAR     = 104;
VM_DWGSELECT    = 105;
VM_DWGLOADING   = 106;
VM_DWGLOADED    = 107;
VM_DWGSAVING    = 108;
VM_DWGSAVED     = 109;
VM_DWGUPDATE    = 110;
VM_PASSWORD     = 121;
VM_TIMER        = 122;
VM_RASTER       = 123;
VM_CLOSEQUERY   = 124;
VM_WINRESIZE    = 125;
VM_WDWG_CLOSED  = 126;
VM_WVIEW_CLOSED = 127;
VM_GRIPSELECT   = 161;
VM_GRIPDRAG     = 162;
VM_GRIPMOVE     = 163;
VM_STATUSTEXT   = 171;

VM_EXP___MIN    = 180;
VM_EXP_BEGIN    = 181;
VM_EXP_END      = 182;
VM_EXP_ENTITY   = 183;
VM_EXP_MOVETO   = 184;
VM_EXP_LINETO   = 185;
VM_EXP_ARCTO    = 186;
VM_EXP_DROP     = 187;
VM_EXP_DROPSIZE = 188;
VM_EXP_COLOR    = 189;
VM_EXP_WIDTH    = 190;
VM_EXP_LAYER    = 191;
VM_EXP_PUMPOFF  = 192;
VM_EXP_EXPLODE  = 193;
VM_EXP_LINES    = 195;
VM_EXP_FILLINGS = 196;
VM_EXP___MAX    = 200;

VM_EXP_OPEN     = 181;
VM_EXP_CLOSE    = 182;
VM_EXP_ENT      = 183;

VM_PROP_PRE     = 251;
VM_PROP_POST    = 252;

VM_NAV_CLOSE    = 261;
VM_NAV_DIALOG   = 262;

VM_MOUSEWHEEL   = 271;


/////////////////////////////////////////////////
// VeCAD error codes, passed with the VM_ERROR message
VL_ERR_OBJADD     = 1;
VL_ERR_OBJDELETE  = 2;
VL_ERR_OBJSELECT  = 4;
VL_ERR_LOADVEC    = 5;



(********************************************************************
* VeCAD commands identifiers
*********************************************************************)

// File
VC_FILE_NEW      = 17001;
VC_FILE_OPEN     = 17002;
VC_FILE_SAVE     = 17003;
VC_FILE_SAVEAS   = 17004;
VC_FILE_CLOSE    = 17005;
VC_FILE_CLOSEALL = 17006;
VC_FILE_LIST     = 17007;
VC_IMPORT_DXF    = 17011;
VC_IMPORT_VDF    = 17012;
VC_IMPORT_HPGL   = 17013;
VC_IMPORT_CNC    = 17014;
VC_IMPORT_AVSHP  = 17016;
VC_EXPORT_DXF    = 17021;
VC_EXPORT_HPGL   = 17022;
VC_EXPORT_CNC    = 17023;
VC_EXPORT_BMP    = 17024;
VC_EXPORT_AVSHP  = 17025;
VC_PRINT         = 17031;

// View
VC_ZOOM_ALL   = 17051;
VC_ZOOM_WIN   = 17052;
VC_ZOOM_PAN   = 17053;
VC_ZOOM_PAGE  = 17054;
VC_ZOOM_IN    = 17055;
VC_ZOOM_OUT   = 17056;
VC_ZOOM_LEFT  = 17057;
VC_ZOOM_RIGHT = 17058;
VC_ZOOM_UP    = 17059;
VC_ZOOM_DOWN  = 17060;
VC_ZOOM_PREV  = 17061;
VC_ZOOM_SEL   = 17062;
VC_PAGE_NEXT  = 17071;
VC_PAGE_PREV  = 17072;
VC_PAGE_FIRST = 17073;
VC_PAGE_LAST  = 17074;
VC_PAGE_DLG   = 17075;
VC_VIEW_SAVE  = 17081;
VC_VIEW_LIST  = 17082;

// Draw
VC_DRAW_POINT     = 17110;
VC_DRAW_LINE      = 17120;
VC_DRAW_POLYLINE  = 17130;
VC_DRAW_SPLINE    = 17131;
VC_DRAW_CIRC_CR   = 17140;
VC_DRAW_CIRC_CD   = 17141;
VC_DRAW_CIRC_2P   = 17142;
VC_DRAW_CIRC_3P   = 17143;
VC_DRAW_CIRC_TTT  = 17144;
VC_DRAW_ARC_CSE   = 17150;
VC_DRAW_ARC_CSA   = 17151;
VC_DRAW_ARC_CSL   = 17152;
VC_DRAW_ARC_SEM   = 17153;
VC_DRAW_ARC_SME   = 17154;
VC_DRAW_ARC_SCE   = 17155;
VC_DRAW_ARC_SCA   = 17156;
VC_DRAW_ARC_SCL   = 17157;
VC_DRAW_ARC_SEA   = 17158;
VC_DRAW_ARC_SED   = 17159;
VC_DRAW_ARC_SER   = 17160;
VC_DRAW_ARC_CONT  = 17161;
VC_DRAW_SECTOR    = 17165;
VC_DRAW_ELLIPSE   = 17170;
VC_DRAW_RECT      = 17180;
VC_DRAW_DIM_HOR   = 17230;
VC_DRAW_DIM_VER   = 17231;
VC_DRAW_DIM_PAR   = 17232;
VC_DRAW_DIM_ANG   = 17233;
VC_DRAW_DIM_RAD   = 17234;
VC_DRAW_DIM_DIAM  = 17235;
VC_DRAW_DIM_ORD   = 17236;
VC_DRAW_HATCH     = 17240;
VC_INS_TEXT       = 17250;
VC_INS_SYMBOL     = 17260;
VC_INS_BLOCK      = 17280;
VC_INS_IMAGE      = 17290;
VC_INS_RMAP       = 17300;
VC_INS_DRAWING    = 17302;
VC_INS_AVSHP      = 17303;
VC_INS_FLOOD      = 17304;

// Edit
VC_EDIT_ENTPROP  = 17401;
VC_EDIT_COPY     = 17402;
VC_EDIT_MOVE     = 17403;
VC_EDIT_ROTATE   = 17404;
VC_EDIT_SCALE    = 17405;
VC_EDIT_MIRROR   = 17406;
VC_EDIT_ERASE    = 17407;
VC_EDIT_EXPLODE  = 17408;
VC_EDIT_CREBLOCK = 17409;
VC_EDIT_EXTEND   = 17410;
VC_EDIT_TRIM     = 17411;
VC_EDIT_FILLET   = 17412;
VC_EDIT_ARRAY    = 17413;
VC_EDIT_JOIN     = 17414;
VC_EDIT_UNDO     = 17431;
VC_EDIT_REDO     = 17432;
VC_EDIT_CBCUT    = 17441;
VC_EDIT_CBCOPY   = 17442;
VC_EDIT_CBPASTE  = 17443;

// Format
VC_FMT_LAYOUT  = 17451;
VC_FMT_PAGE    = 17452;
VC_FMT_LAYER   = 17453;
VC_FMT_STLINE  = 17454;
VC_FMT_STTEXT  = 17455;
VC_FMT_STDIM   = 17456;
VC_FMT_STPOINT = 17457;
VC_FMT_STHATCH = 17458;
VC_FMT_BLOCK   = 17459;
VC_FMT_GRID    = 17461;
VC_FMT_OSNAP   = 17462;
VC_FMT_PSNAP   = 17463;
VC_FMT_UNITS   = 17464;
VC_FMT_PRIVATE = 17465;
VC_FMT_PREFERS = 17466;
VC_FMT_MLINE   = 17467;

// Snap
VC_SNAP_DLG    = 17501;
VC_SNAP_CLEAR  = 17502;
VC_SNAP_GRID   = 17503;
VC_SNAP_POLAR  = 17504;
VC_SNAP_KNOT   = 17511;
VC_SNAP_GRIP   = 17511;
VC_SNAP_GRIPS  = 17511;
VC_SNAP_POINT  = 17512;
VC_SNAP_NEAR   = 17513;
VC_SNAP_END    = 17514;
VC_SNAP_MID    = 17515;
VC_SNAP_INTER  = 17516;
VC_SNAP_CEN    = 17517;
VC_SNAP_PERP   = 17518;
VC_SNAP_TANG   = 17519;
VC_SNAP_REALTIME = 17520;

// Tools
VC_TOOL_DIST      = 18501;
VC_TOOL_PRNRECT   = 18502;
VC_TOOL_STAT      = 18503;
VC_TOOL_NAVIGATOR = 18504;
VC_TOOL_LAYERS    = 18505;
VC_ENT_SWAP       = 18511;
VC_ENT_TOTOP      = 18512;
VC_ENT_TOBOTTOM   = 18513;
VC_SEL_BYPOINT    = 18531;
VC_SEL_BYRECT     = 18532;
VC_SEL_BYPOLYGON  = 18533;
VC_SEL_BYPOLYLINE = 18534;
VC_SEL_BYDIST     = 18535;
VC_SEL_BYHANDLE   = 18536;
VC_SEL_BYKEY      = 18537;
VC_SEL_BYLAYER    = 18538;

// Misc
VC_RESET      = 18171;
VC_REDRAW     = 18172;
VC_SHOWLINEW  = 18173;
VC_SHOWGRID   = 18174;
VC_SHOWFILL   = 18175;

// Offset for custom commands that use cursor
VC_CUSTOM     = 20000;



(********************************************************************
* VeCAD data access keys for vlGetData/vlSetData functions
********************************************************************)

VD_WND___MIN        = 30001;
VD_WND_EMPTYTEXT    = 30001;
VD_WND_CURSOR_X     = 30002;
VD_WND_CURSOR_Y     = 30003;
VD_WND_CURSOR_CROSS = 30004;
VD_WND___MAX        = 30010;

VD_PRJ___MIN        = 30011;
VD_PRJ_WDWG_ON      = 30011;
VD_PRJ_WDWG_LEFT    = 30012;
VD_PRJ_WDWG_TOP     = 30013;
VD_PRJ_WDWG_RIGHT   = 30014;
VD_PRJ_WDWG_BOTTOM  = 30015;
VD_PRJ_WVIEW_ON     = 30016;
VD_PRJ_WVIEW_LEFT   = 30017;
VD_PRJ_WVIEW_TOP    = 30018;
VD_PRJ_WVIEW_RIGHT  = 30019;
VD_PRJ_WVIEW_BOTTOM = 30020;
VD_PRJ_WDIST_LEFT   = 30021;
VD_PRJ_WDIST_TOP    = 30022;
VD_PRJ___MAX        = 30099;

// VD_AVIEW___MIN      = 30101;
// VD_AVIEW_COLRECT    = 30101;
// VD_AVIEW_DWGDRAG    = 30102;
// VD_AVIEW___MAX      = 30130;

VD_PRN___MIN  = 30131;
VD_PRN_NAME   = 30131;
VD_PRN_DRIVER = 30132;
VD_PRN_PORT   = 30133;
VD_PRN_USEDOC = 30134;
VD_PRN___MAX  = 30150;

VD_MSG_STRING = 30155;
VD_MSG_DBL1   = 30156;
VD_MSG_DBL2   = 30157;
VD_SDECIMAL   = 30161;
VD_KEYCTRL    = 30162;
VD_KEYSHIFT   = 30163;

VD_DWG___MIN         = 1;
VD_DWG_ID            = 1;
VD_DWG_INDEX         = 2;
VD_DWG_FILENAME      = 3;
VD_DWG_PATHNAME      = 4;
VD_DWG_TITLE         = 5;
VD_DWG_LEFT          = 6;
VD_DWG_RIGHT         = 7;
VD_DWG_TOP           = 8;
VD_DWG_BOTTOM        = 9;
VD_DWG_WIDTH         = 10;
VD_DWG_HEIGHT        = 11;
VD_DWG_WINLEFT       = 12;
VD_DWG_WINRIGHT      = 13;
VD_DWG_WINTOP        = 14;
VD_DWG_WINBOTTOM     = 15;
VD_DWG_WINWIDTH      = 16;
VD_DWG_WINHEIGHT     = 17;
VD_DWG_WINSCALE      = 18;
VD_DWG_WINSCALEY     = 19;
VD_DWG_ZOOMVAL       = 20;
VD_DWG_ZOOMHORZ      = 21;
VD_DWG_ZOOMVERT      = 22;
VD_DWG_ZOOMMIN       = 23;
VD_DWG_ZOOMMAX       = 24;
VD_DWG_SCROLLERS     = 25;
VD_DWG_READONLY      = 26;
VD_DWG_BLACKWHITE    = 27;
VD_DWG_COLBKG        = 31;
VD_DWG_COLPAGE       = 32;
VD_DWG_COLPAGESHADOW = 33;
VD_DWG_COLCURSOR     = 34;
VD_DWG_COLGRIP       = 35;
VD_DWG_COLSELOBJ     = 36;
VD_DWG_COLSELGRIP    = 37;
VD_DWG_COLOR         = 38;
VD_DWG_SHOWAPER      = 41;
VD_DWG_SHOWCROSS     = 42;
VD_DWG_SHOWFILL      = 43;
VD_DWG_SHOWVEC       = 44;
VD_DWG_SHOWBMP       = 45;
VD_DWG_SHOWLINEW     = 46;
VD_DWG_SHOWRMARK     = 47;
VD_DWG_SHOWGRID      = 48;
VD_DWG_AUTOSELPNT    = 61;
VD_DWG_AUTOSELRECT   = 62;
VD_DWG_AUTOUNSELECT  = 63;
VD_DWG_USEGRIPS      = 71;
VD_DWG_LOCK          = 72;
VD_DWG_PASSWORD      = 73;
VD_DWG_OWNER         = 74;
VD_DWG_NOEXPORT      = 75;
VD_DWG_NOPRINT       = 76;
VD_DWG_PICKBOXSIZE   = 82;
VD_DWG_GRIPSIZE      = 83;
VD_DWG_DEFLINEW      = 84;
VD_DWG_ISDIRTY       = 85;
VD_DWG_EXDATASIZE    = 86;
VD_DWG_EXDATA        = 87;
VD_DWG_CROSSSIZE     = 88;
VD_DWG_TRACK_EXPORT  = 89;
VD_DWG_SNAP          = 91;
VD_DWG_SNAPSIZE      = 92;
VD_DWG_PSNAPDIST     = 93;
VD_DWG_PSNAPANGLE0   = 94;
VD_DWG_PSNAPANGLE    = 95;
VD_DWG_N_PAGES       = 101;
VD_DWG_C_PAGE        = 102;
VD_DWG_N_LAYERS      = 103;
VD_DWG_C_LAYER       = 104;
VD_DWG_N_STLINES     = 105;
VD_DWG_C_STLINE      = 106;
VD_DWG_N_STTEXTS     = 107;
VD_DWG_C_STTEXT      = 108;
VD_DWG_N_STHATCHS    = 109;
VD_DWG_C_STHATCH     = 110;
VD_DWG_N_VIEWS       = 111;
VD_DWG_C_VIEW        = 112;
VD_DWG_N_PRNRECTS    = 113;
VD_DWG_C_PRNRECT     = 114;
VD_DWG_N_STDIMS      = 115;
VD_DWG_C_STDIM       = 116;
VD_DWG_N_STPOINTS    = 117;
VD_DWG_C_STPOINT     = 118;
VD_DWG_N_GRPOINTS    = 119;
VD_DWG_C_GRPOINT     = 120;
VD_DWG_N_BLOCKS      = 121;
VD_DWG_C_BLOCK       = 122;
VD_DWG_N_ENTITIES    = 123;
VD_DWG_N_ENT         = 123;
VD_DWG_N_ENTSEL      = 124;
VD_DWG_C_LEVEL       = 125;
VD_DWG_BITMAP        = 126;
VD_DWG_SELECTINSIDE  = 127;
VD_DWG_FLATENDS      = 128;
VD_DWG_SEGCURVE      = 129;
VD_DWG_CHARFRAME     = 130;
VD_DWG_SELACTLAYER   = 131;
VD_DWG_SORTLAYERS    = 132;
VD_DWG_PROPMESSAGES  = 133;
VD_DWG_EXTOBJECT     = 134;
VD_DWG_HWND          = 135;
VD_DWG_INSBLOCKDLG   = 136;
VD_DWG_NOINDICATOR   = 137;

VD_GRID_X0          = 141;   // grid origin X
VD_GRID_Y0          = 142;   // grid origin Y
VD_GRID_DX          = 143;   // grid step X
VD_GRID_DY          = 144;   // grid step Y
VD_GRID_TYPE        = 145;   // grid type
VD_GRID_COLOR       = 146;   // grid color
VD_GRID_BSTEPX      = 147;   // grid bold step
VD_GRID_BSTEPY      = 148;   // grid bold step
VD_GRID_BTYPE       = 149;   // grid bold type
VD_GRID_BCOLOR      = 150;   // grid bold color
VD_UNITS_LIN        = 161;   // coord units
VD_UNITS_ANG        = 162;   // angle units
VD_UNITS_SCALE      = 163;   // map scale
VD_UNITS_PAGELEFT   = 164;   // coord for page origin
VD_UNITS_PAGEBOTTOM = 165;   //
VD_UNITS_GEO        = 166;   // geodesic axises
VD_UNITS_FORMAT     = 167;
VD_HPGL_X0          = 171;   // origin for HPGL export
VD_HPGL_Y0          = 172;
VD_HPGL_UNITX       = 173;   // scale for HPGL export
VD_HPGL_UNITY       = 174;
VD_HPGL_MINSTEP     = 175;   // minimal step for coordinates
VD_HPGL_OFFDIST     = 176;   // distance for VM_EXP_PUMPOFF
VD_EXP_X0          = 171;
VD_EXP_Y0          = 172;
VD_EXP_UNITX       = 173;
VD_EXP_UNITY       = 174;
VD_EXP_MINSTEP     = 175;
VD_EXP_OFFDIST     = 176;
VD_EXP_USEARCS     = 177;
VD_EXP_DROPSIZE    = 178;
VD_EXP_DROPSIZEMIN = 179;
VD_DWG___MAX       = 200;

VD_PAGE___MIN  = 201;
VD_PAGE_NAME   = 201;   // page name
VD_PAGE_SIZE   = 202;   // page size
VD_PAGE_ORIENT = 203;   // page orientation
VD_PAGE_WIDTH  = 204;   // page width (if size=VD_PAPER_USER)
VD_PAGE_HEIGHT = 205;   // page height (if size=VD_PAPER_USER)
VD_PAGE_N_REF  = 208;   // RO number of objects on the page
VD_PAGE_ID     = 209;   // RO page ID
VD_PAGE_INDEX  = 210;   // RO page index by name
VD_PAGE_EXTOBJECT = 211;
VD_PAGE___MAX  = 299;

VD_LAYER___MIN     = 301;
VD_LAYER_NAME      = 301;      // layer name
VD_LAYER_COLOR     = 302;      // layer color
VD_LAYER_FILLCOLOR = 303;      // layer fill color
VD_LAYER_LINEWIDTH = 304;      // layer line width
VD_LAYER_VISIBLE   = 305;      // layer visible
VD_LAYER_LOCK      = 306;      // layer locked
VD_LAYER_SELINSIDE = 307;      // layer enable select by inner part of object
VD_LAYER_NOPRINT   = 308;      // non-printable layer
VD_LAYER_N_REF     = 309;      // RO number of objects on the layer
VD_LAYER_ID        = 310;      // RO layer ID
VD_LAYER_INDEX     = 311;      // RO layer index by name
VD_LAYER_ENTSELECT = 312;      // WO select all entities on the layer
VD_LAYER_SELENT    = 312;
VD_LAYER_LEVEL     = 313;      
VD_LAYER_EXTOBJECT = 314;
VD_LAYER___MAX     = 399;

VD_STTEXT___MIN     = 401;
VD_STTEXT_NAME      = 401;      // text style name
VD_STTEXT_FONTNAME  = 402;      // RO text style fontname
VD_STTEXT_WEIGHT    = 403;      // RO font weight
VD_STTEXT_ITALIC    = 404;      // RO font italic
VD_STTEXT_WIDTH     = 405;      // text style chars width scale
VD_STTEXT_OBLIQUE   = 406;      // text style chars horiz. shift
VD_STTEXT_PRECISION = 407;      // RO text style precision
VD_STTEXT_FILLED    = 408;      // flag "filled text"
VD_STTEXT_N_REF     = 409;      // RO number of references
VD_STTEXT_ID        = 410;      // RO ID
VD_STTEXT_INDEX     = 411;      // RO index by name
VD_STTEXT_BYLINES   = 412;      // flag "draw texts by lines"
VD_STTEXT_EXTOBJECT = 413;
VD_STTEXT___MAX     = 499;

VD_STLINE___MIN    = 501;
VD_STLINE_NAME     = 501;      // line type name
VD_STLINE_DESC     = 502;      // line type description
VD_STLINE_DESCLEN  = 503;      // RO length of line type description
VD_STLINE_N_REF    = 504;      // RO number of references
VD_STLINE_ID       = 505;      // RO ID
VD_STLINE_INDEX    = 506;      // RO index by name
VD_STLINE_EXTOBJECT = 507;
VD_STLINE___MAX    = 599;

VD_STDIM___MIN        = 601;
VD_STDIM_NAME         = 601;      // dim style name
VD_STDIM_ARR_TYPE     = 602;
VD_STDIM_ARR_LENGTH   = 603;
VD_STDIM_ARR_HEIGHT   = 604;
VD_STDIM_EXT_OFFSET   = 605;
VD_STDIM_EXT_EXTEND   = 606;
VD_STDIM_TEXT_CONTENT = 607;
VD_STDIM_TEXT_STYLE   = 608;
VD_STDIM_TEXT_ALIGN   = 609;
VD_STDIM_TEXT_HEIGHT  = 610;
VD_STDIM_TEXT_DEC     = 611;
VD_STDIM_TEXT_HORIZ   = 612;
VD_STDIM_TEXT_GAP     = 613;
VD_STDIM_SCALE        = 614;
VD_STDIM_OWNCOLORS    = 615;
VD_STDIM_COL_DIM      = 616;
VD_STDIM_COL_EXT      = 617;
VD_STDIM_COL_TEXT     = 618;
VD_STDIM_CEN_TYPE     = 619;
VD_STDIM_CEN_SIZE     = 620;
VD_STDIM_ROUND        = 621;
VD_STDIM_N_REF        = 622;
VD_STDIM_ID           = 623;
VD_STDIM_INDEX        = 624;
VD_STDIM_EXTOBJECT    = 625;
VD_STDIM___MAX        = 699;

VD_STHATCH___MIN   = 701;
VD_STHATCH_NAME    = 701;      // hatch style name
VD_STHATCH_DESC    = 702;      // hatch style description
VD_STHATCH_DESCLEN = 703;      // RO length of description
VD_STHATCH_N_REF   = 704;      // RO number of references
VD_STHATCH_ID      = 705;      // RO ID
VD_STHATCH_INDEX   = 706;      // RO index by name
VD_STHATCH_EXTOBJECT = 707;
VD_STHATCH___MAX   = 799;

VD_STPOINT___MIN   = 801;
VD_STPOINT_NAME    = 801;      // point type name 
VD_STPOINT_STATUS  = 802;      // point type status
VD_STPOINT_BLOCK   = 803;      // index of block
VD_STPOINT_LAYER   = 804;      // layer for point type
VD_STPOINT_STTEXT  = 805;      // text style
VD_STPOINT_BSCALE  = 806;      // block scale
VD_STPOINT_TEXTH   = 807;      // text height
VD_STPOINT_TEXTW   = 808;      // text width scale
VD_STPOINT_SNAP    = 809;      // snap to point
VD_STPOINT_FIXED   = 810;      // non-movable point
VD_STPOINT_N_REF   = 811;      // RO number of references
VD_STPOINT_ID      = 812;      // RO ID
VD_STPOINT_INDEX   = 813;      // RO index by name
VD_STPOINT_EXTOBJECT = 814;
VD_STPOINT___MAX   = 859;

VD_GRPOINT___MIN  = 861;
VD_GRPOINT_NAME   = 861;      // point group name
VD_GRPOINT_N_REF  = 862;      // RO number of references
VD_GRPOINT_ID     = 863;      // RO ID
VD_GRPOINT_INDEX  = 864;      // RO index by name
VD_GRPOINT_EXTOBJECT = 865;
VD_GRPOINT___MAX  = 899;

VD_BLOCK___MIN    = 901;
VD_BLOCK_NAME     = 901;      // block name 
VD_BLOCK_WIDTH    = 902;      // RO width of the block
VD_BLOCK_HEIGHT   = 903;      // RO height of the block
VD_BLOCK_XBASE    = 904;      // x base point
VD_BLOCK_YBASE    = 905;      // y base point
VD_BLOCK_N_REF    = 906;      // RO number of references
VD_BLOCK_ID       = 907;      // RO ID
VD_BLOCK_INDEX    = 908;      // RO index by name
VD_BLOCK_EXTOBJECT = 909;
VD_BLOCK_N_ENT    = 910;      // RO number of entities in block
VD_BLOCK___MAX    = 999;

VD_PRNRECT___MIN   = 1001;
VD_PRNRECT_INDEX   = 1001;     // RO index by name
VD_PRNRECT_NAME    = 1002;     // name
VD_PRNRECT_XCEN    = 1003;     // x-center point
VD_PRNRECT_YCEN    = 1004;     // y-center point
VD_PRNRECT_WIDTH   = 1005;     // width of the rect
VD_PRNRECT_HEIGHT  = 1006;     // height of the rect
VD_PRNRECT_ANGLE   = 1007;     // rotation angle of the rect
VD_PRNRECT_EXTOBJECT = 1008;
VD_PRNRECT___MAX   = 1099;

VD_VIEW___MIN   = 1101;
VD_VIEW_ID      = 1101;     // RO ID
VD_VIEW_NAME    = 1102;     // name
VD_VIEW_EXTOBJECT = 1103;
VD_VIEW___MAX   = 1199;

VD_ENT___MIN      = 20001;
VD_ENT_TYPE       = 20001;    // RO type of object
VD_ENT_HANDLE     = 20002;    // RO handle
VD_ENT_ID         = 20002;    // RO handle
VD_ENT_KEY        = 20003;    // key
VD_ENT_LAYER      = 20004;    // layer index
VD_ENT_LINETYPE   = 20005;    // line type
VD_ENT_STLINE     = 20005;    // line type
VD_ENT_PAGE       = 20006;    // page
VD_ENT_LEVEL      = 20007;    // level
VD_ENT_COLOR      = 20008;    // own color
VD_ENT_FILLCOLOR  = 20009;    // own fill color
VD_ENT_LINEWIDTH  = 20010;    // own linewidth
VD_ENT_LEFT       = 20011;    // RO left limit
VD_ENT_BOTTOM     = 20012;    // RO bottom limit
VD_ENT_RIGHT      = 20013;    // RO right limit
VD_ENT_TOP        = 20014;    // RO top limit
VD_ENT_SELECT     = 20015;    // select object
VD_ENT_ONSCREEN   = 20016;    // RO object on screen
VD_ENT_INBLOCK    = 20017;    // RO object is part of a block
VD_ENT_N_GRIPS    = 20018;    // RO number of grips in the object
VD_ENT_DELETED    = 20019;    // delete object
VD_ENT_FILLED     = 20020;    // filled object
VD_ENT_BORDER     = 20021;    // has border (for filled)
VD_ENT_OWNCOLOR   = 20022;    // has own color (not by layer)
VD_ENT_OWNFCOLOR  = 20023;    // has own fill color (not by layer)
VD_ENT_OWNLINEW   = 20024;    // has own line width (not by layer)
VD_ENT_WIDTH      = 20025;    // RO object width
VD_ENT_HEIGHT     = 20026;    // RO object width
VD_ENT_UPDATE     = 20027;    // WO update limits
VD_ENT_LENGTH     = 20028;    // RO object's perimeter (for closed objects)
VD_ENT_PERIMETER  = 20028;    // RO object's perimeter (for closed objects)
VD_ENT_AREA       = 20029;    // RO object's area (for closed objects)
VD_ENT_INDEX      = 20030;    // RO object's index
VD_ENT_MULTILINE  = 20031;    // flag "line style is multiline"
VD_ENT_EXTOBJECT  = 20032;    // pointer to external object
VD_ENT___MAX      = 20099;

VD_LINE___MIN     = 20101; 
VD_LINE_X1        = 20101;    // coordinate of 1st point
VD_LINE_Y1        = 20102;    //
VD_LINE_X2        = 20103;    // coordinate of 2nd point
VD_LINE_Y2        = 20104;    //
VD_LINE_ARROW1    = 20105;    // ends arrows flags
VD_LINE_ARROW2    = 20106;    //
VD_LINE___MAX     = 20199;   

VD_POLY___MIN     = 20201;
VD_POLY_CLOSED    = 20201;    // flag "closed polyline"
VD_POLY_SMOOTH    = 20202;    // polyline smooth type
VD_POLY_ARROW1    = 20203;    // type of start arrow (dim.style)
VD_POLY_ARROW2    = 20204;    // type of end arrow (dim.style)
VD_POLY_R         = 20205;    // radius for smooth=VL_POLY_ROUNDED
VD_POLY_N_VER     = 20206;    // RO number of vertexes
VD_POLY_C_VER     = 20207;    // current vertex
VD_POLY_GETVERS   = 20208;    // RO Get vertexes array
VD_POLY_SETVERS   = 20209;    // WO Set vertexes array
VD_POLY_VER_INS   = 20210;    // WO Insert vertex
VD_POLY_VER_DEL   = 20211;    // WO Delete vertex
VD_POLY_VER_X     = 20212;    // vertex coordinate
VD_POLY_VER_Y     = 20213;    //
VD_POLY_VER_R     = 20214;    // vertex radius (for smooth=VL_POLY_MULTIRAD)
VD_POLY_VER_ON    = 20215;    // vertex online flag (for smooth=VL_POLY_LINBSPL2)
VD_POLY_VER_BULGE = 20216;    // bulge coefficient (for smooth=VL_POLY_BULGE)
VD_POLY_VER_DATA  = 20217;    // aux vertex data
VD_POLY_CUSTDATA  = 20231;    // custom data (for smooth=POLY_CUSTOM)
VD_POLY___MAX     = 20299;

VD_CIRCLE___MIN  = 20301;
VD_CIRCLE_X      = 20301;    // coordinate of circle's center
VD_CIRCLE_Y      = 20302;    //
VD_CIRCLE_R      = 20303;    // radius of circle
VD_CIRCLE___MAX  = 20399;

VD_ARC___MIN     = 20401;
VD_ARC_X         = 20401;    // coordinate of arc's center
VD_ARC_Y         = 20402;    //
VD_ARC_R         = 20403;    // arc's radius
VD_ARC_START     = 20404;    // start angle
VD_ARC_END       = 20405;    // end angle
VD_ARC_ARROW1    = 20406;    // index of dim style for start arrow type
VD_ARC_ARROW2    = 20407;    // for end arrow
VD_ARC_RH        = 20411;    // horizontal radius
VD_ARC_RV        = 20412;    // vertical radius
VD_ARC_ANG0      = 20413;    // start angle
VD_ARC_ANGARC    = 20414;    // arc angle
VD_ARC_ANGROT    = 20415;    // rotation angle
VD_ARC_SECTOR    = 20431;    // draw as sector
VD_ARC_CHORD     = 20432;    // draw arc with chord
VD_ARC_XS        = 20441;    // RO start point
VD_ARC_YS        = 20442;
VD_ARC_XE        = 20443;    // RO end point
VD_ARC_YE        = 20444;
VD_ARC___MAX     = 20499;    //

VD_ELLIPSE___MIN  = 20601;
VD_ELLIPSE_X      = 20601;    // coordinate of ellipse's center
VD_ELLIPSE_Y      = 20602;    //
VD_ELLIPSE_RH     = 20603;    // horizontal radius
VD_ELLIPSE_RV     = 20604;    // vertical radius
VD_ELLIPSE_ANGLE  = 20605;    // rotation angle of the ellipse
VD_ELLIPSE___MAX  = 20699;

VD_TEXT___MIN     = 20701;
VD_TEXT_X         = 20701;    // coordinate of text's insertion
VD_TEXT_Y         = 20702;    //
VD_TEXT_TEXT      = 20703;    // text sting
VD_TEXT_LENGTH    = 20704;    // RO text length (symbols)
VD_TEXT_STYLE     = 20705;    // text style
VD_TEXT_HEIGHT    = 20706;    // text height
VD_TEXT_WSCALE    = 20707;    // text width scale
VD_TEXT_ALIGN     = 20708;    // text align
VD_TEXT_ANGLE     = 20709;    // text angle
VD_TEXT_OBLIQUE   = 20710;    // text shift horiz.
VD_TEXT_INTER_H   = 20712;    // interval between chars
VD_TEXT_INTER_V   = 20713;    // interval between strings
VD_TEXT_PATH      = 20714;    // flag "Path text"
VD_TEXT_STRIKEOUT = 20715;    // strikeout text
VD_TEXT_UNDERLINE = 20716;    // underlined text
VD_TEXT_N_LINES   = 20717;    // RO number of text lines
VD_TEXTP_CURVE    = 20721;    // handle of path curve object
VD_TEXTP_DX       = 20722;    // origin along the curve
VD_TEXTP_DY       = 20723;    // chars deviation from the curve
VD_TEXTP_BACKWARD = 20724;    // backward to curve direction
VD_TEXTP_ABSANGLE = 20725;    // absolute rotation angle
VD_TEXT___MAX     = 20799;

VD_INSBLK___MIN   = 20801;
VD_INSBLK_X       = 20801;    // coordinate of block's insertion
VD_INSBLK_Y       = 20802;    //
VD_INSBLK_BLOCK   = 20803;    // block's index
VD_INSBLK_ANGLE   = 20804;    // rotation angle
VD_INSBLK_SCALEX  = 20805;    // horiz. scale
VD_INSBLK_SCALEY  = 20806;    // vert. scale
VD_INSBLK_SCALE   = 20807;    // scale
VD_INSBLK___MAX   = 20899;

VD_HATCH___MIN   = 20901;
VD_HATCH_STYLE   = 20901;    // index of hatch style
VD_HATCH_SCALE   = 20902;    // hatch's scale
VD_HATCH_ANGLE   = 20903;    // hatch's angle
VD_HATCH___MAX   = 20999;

VD_BMP___MIN     = 21001;
VD_BMP_X         = 21001;    // coordinate of bitmap's insertion
VD_BMP_Y         = 21002;    //
VD_BMP_FILENAME  = 21003;    // bitmap file name
VD_BMP_RESX      = 21004;    // bitmap resolution by X
VD_BMP_RESY      = 21005;    // bitmap resolution by Y
VD_BMP_RELOAD    = 21007;    // WO reload bitmap
VD_BMP___MAX     = 21099;

VD_POINT___MIN   = 21101;
VD_POINT_X       = 21101;    // coordinate of point
VD_POINT_Y       = 21102;    //
VD_POINT_STYLE   = 21103;    // point type
VD_POINT_GROUP   = 21104;    // point group
VD_POINT_TEXT    = 21105;    // point text
VD_POINT_TEXTLEN = 21106;    // text length (symbols)
VD_POINT_TXTDX   = 21107;    // point text offset by X
VD_POINT_TXTDY   = 21108;    // point text offset by Y
VD_POINT_TXTANG  = 21109;    // point text angle
VD_POINT_BLKANG  = 21110;    // point block angle
VD_POINT_FIXED   = 21111;    // non-movable point
VD_POINT___MAX   = 21199;

VD_RECT___MIN    = 21201;
VD_RECT_XCEN     = 21201;    // coordinate of rect's center
VD_RECT_YCEN     = 21202;    //
VD_RECT_WIDTH    = 21203;    // width
VD_RECT_HEIGHT   = 21204;    // height
VD_RECT_ANGLE    = 21205;    // rotation angle of the rect
VD_RECT_RADIUS   = 21206;    // radius of corners
VD_RECT___MAX    = 21299;

VD_DIM___MIN     = 22301;
VD_DIM_STYLE     = 22301;    // dimension style
VD_DIM_TYPE      = 22302;    // RO dimension type
VD_DIM_STATIC    = 22303;    // flag "static value"
VD_DIM_VALUE     = 22304;    // value (if static)
VD_DIM_XTEXT     = 22305;    // text point
VD_DIM_YTEXT     = 22306;    //
VD_DIM___MAX     = 22319;

VD_DIM_L___MIN   = 22321;
VD_DIM_L_X1      = 22321;    // first point
VD_DIM_L_Y1      = 22322;    //
VD_DIM_L_X2      = 22323;    // second point
VD_DIM_L_Y2      = 22324;    //
VD_DIM_L_OFFSET  = 22325;    // offset of dim. line
VD_DIM_L_XLINE   = 22325;
VD_DIM_L_YLINE   = 22325;
VD_DIM_L___MAX   = 22339;

VD_DIM_A___MIN   = 22341;
VD_DIM_A_XCEN    = 22341;    // center point
VD_DIM_A_YCEN    = 22342;    //
VD_DIM_A_X1      = 22343;    // first point
VD_DIM_A_Y1      = 22344;    //
VD_DIM_A_X2      = 22345;    // second point
VD_DIM_A_Y2      = 22346;    //
VD_DIM_A_RADIUS  = 22347;    // radius for dimension arc
VD_DIM_A___MAX   = 22359;

VD_DIM_R___MIN   = 22361;
VD_DIM_R_XCEN    = 22361;    // center point
VD_DIM_R_YCEN    = 22362;
VD_DIM_R_XRAD    = 22363;    // radial point
VD_DIM_R_YRAD    = 22364;
VD_DIM_R_OFFSET  = 22365;    // offset of dim line start
VD_DIM_R___MAX   = 22369;

VD_DIM_D___MIN   = 22371;
VD_DIM_D_XCEN    = 22371;    // center point
VD_DIM_D_YCEN    = 22372;
VD_DIM_D_XRAD    = 22373;    // radial point
VD_DIM_D_YRAD    = 22374;
VD_DIM_D___MAX   = 22379;

VD_DIM_O___MIN   = 22391;
VD_DIM_O_X       = 22391;    // ordinate point
VD_DIM_O_Y       = 22392;
VD_DIM_O_ORDY    = 22393;    // flag "Show Y ordinate"
VD_DIM_O___MAX   = 22399;

VD_CE___MIN      = 22901;    // custom entity
VD_CE_DATA       = 22901;    // data block of the entity
VD_CE_DATASIZE   = 22901;    // (RO) size of data block
VD_CE___MAX      = 22999;

VD_INSDWG___MIN    = 23001;
VD_INSDWG_FILENAME = 23001;
VD_INSDWG_X        = 23002;
VD_INSDWG_Y        = 23003;
VD_INSDWG_ANGLE    = 23004;
VD_INSDWG_SCALEX   = 23005;
VD_INSDWG_SCALEY   = 23006;
VD_INSDWG_WIDTH    = 23007;
VD_INSDWG_HEIGHT   = 23008;
VD_INSDWG_RELOAD   = 23017;  // WO
VD_INSDWG___MAX    = 23099;

VD_FLOOD___MIN   = 23201;
VD_FLOOD_X       = 23201;
VD_FLOOD_Y       = 23202;
VD_FLOOD___MAX   = 23299;


(********************************************************************
* VeCAD strings identifiers
*********************************************************************)

VS_MSGTITLE              = 10501;
VS_NONAME                = 10502;
VS_UNDO_EMPTY            = 10503;
VS_REDO_EMPTY            = 10504;
VS_NO_FONT_FILE          = 10505;
VS_DELETE_OBJ            = 10506;
VS_SAVE_CHANGES          = 10507;
VS_OLD_VEC_FORMAT        = 10508;
VS_NEW_VEC_FORMAT        = 10509;
VS_DWG_ALREADY_LOADED    = 10510;
VS_NO_BLOCKS             = 10511;
VS_LOAD_ERROR_SUM        = 10512;
VS_LOADING               = 10513;
VS_SAVING                = 10514;
VS_EMPTYDWG              = 10515;
VS_CANT_LOAD_FILE        = 10516;
VS_BEGIN_EDITBLOCK       = 10517;
VS_EDITBLOCK_MODE        = 10518;
VS_DIFFER_LAYERS         = 10519;
VS_SEARCH_FILE           = 10520;

VS_FILTER_VEC    = 10541;
VS_FILTER_SHP    = 10542;  // AutoCAD SHP
VS_FILTER_PAT    = 10543;
VS_FILTER_BMP    = 10544;
VS_FILTER_VDF    = 10545;
VS_FILTER_HPGL   = 10546;
VS_FILTER_DP1    = 10547;
VS_FILTER_CNC    = 10548;
VS_FILTER_DXF    = 10551;
VS_FILTER_DWGDXF = 10552;
VS_FILTER_DWG    = 10553;
VS_FILTER_AVSHP  = 10554;  // ArcView SHP

VS_DEL_LAYER_ONE         = 10651;
VS_DEL_LAYER_HAS_REF     = 10652;
VS_DEL_PAGE_ONE          = 10653;
VS_DEL_PAGE_HAS_REF      = 10654;
VS_DEL_STLINE_ONE        = 10655;
VS_DEL_STLINE_HAS_REF    = 10656;
VS_DEL_STTEXT_ONE        = 10657;
VS_DEL_STTEXT_HAS_REF    = 10658;
VS_DEL_STDIM_ONE         = 10659;
VS_DEL_STDIM_HAS_REF     = 10660;
VS_DEL_STHATCH_ONE       = 10661;
VS_DEL_STHATCH_HAS_REF   = 10662;
VS_DEL_BLOCK_HAS_REF     = 10663;
VS_DEL_STPOINT_ONE       = 10664;
VS_DEL_STPOINT_HAS_REF   = 10665;
VS_DEL_STPOINT_SIMPLE    = 10667;
VS_DEL_GRPOINT_ONE       = 10668;
VS_DEL_GRPOINT_HAS_REF   = 10669;
VS_DEL_MLINE_HAS_REF     = 10670;
VS_DEL_PRNRECT           = 10671;

VS_DWGLIST_TITLE    = 10981;
VS_DWGLIST_CLOSE    = 10982;

VS_VIEW_TITLE       = 10985;
VS_VIEW_EDIT        = 10986;
VS_VIEW_DELETE      = 10987;
VS_VIEW_SAVE        = 10988;
VS_VIEW_NAME        = 10989;

VS_BUT_OK           = 11201;
VS_BUT_CANCEL       = 11202;
VS_BUT_ADD          = 11203;
VS_BUT_DELETE       = 11204;
VS_BUT_CURRENT      = 11205;
VS_BUT_SELECT       = 11206;
VS_BUT_UNSELECT     = 11207;
VS_N_REFS           = 11221;
VS_OBJVIEW          = 11222;

VS_SELPAGE          = 11301;

VS_LAYOUT_TITLE     = 11302;
VS_DAID_TITLE       = 11303;
VS_ENTPROP_TITLE    = 11304;
VS_ENTPROP_TITLE2   = 11305;

VS_PAGE_TITLE      = 11401;
VS_PAGE_BOOK       = 11402;
VS_PAGE_ALBUM      = 11403;
VS_PAGE_NAME       = 11405;
VS_PAGE_NAME2      = 11406;
VS_PAGE_SIZE       = 11407;
VS_PAGE_W          = 11408;
VS_PAGE_H          = 11409;
VS_PAGE_ORIENT     = 11410;
VS_PAGE_BTNFORALL  = 11419;
VS_PAGE_FORALL     = 11420;

VS_LAYER_TITLE      = 11501;
VS_LAYER_NAME       = 11502;
VS_LAYER_STATE      = 11503;
VS_LAYER_NAME2      = 11504;
VS_LAYER_LWIDTH2    = 11505;
VS_LAYER_COLOR      = 11506;
VS_LAYER_FCOLOR     = 11507;
VS_LAYER_OFF        = 11508;
VS_LAYER_RDONLY     = 11509;
VS_LAYER_NOPRINT    = 11510;
VS_LAYER_SELINS     = 11511;
VS_LAYER_LEVEL      = 11512;

VS_STLINE_TITLE     = 11601;
VS_STLINE_NAME      = 11602;
VS_STLINE_NAME2     = 11603;
VS_STLINE_DESC      = 11604;
VS_STLINE_APPLY     = 11605;

VS_MLINE_TITLE      = 11631;
VS_MLINE_NAME       = 11632;
VS_MLINE_JOINTS     = 11633;
VS_MLINE_CAPS       = 11634;
VS_MLINE_START      = 11635;
VS_MLINE_END        = 11636;
VS_MLINE_LINE       = 11637;
VS_MLINE_OUTARC     = 11638;
VS_MLINE_INARC      = 11639;
VS_MLINE_VIEW       = 11640;
VS_MLINE_ELEMENTS   = 11641;
VS_MLINE_OFFSET     = 11642;
VS_MLINE_LINESTYLE  = 11643;
VS_MLINE_OFFSET2    = 11644;
VS_MLINE_LINESEL    = 11645;
VS_MLINE_LINEADD    = 11646;
VS_MLINE_LINEDEL    = 11647;

VS_STTEXT_TITLE     = 11701;
VS_STTEXT_CHFONT    = 11702;
VS_STTEXT_RELOAD    = 11703;
VS_STTEXT_NAME      = 11704;
VS_STTEXT_NAME2     = 11705;
VS_STTEXT_FILE      = 11706;
VS_STTEXT_WIDTH     = 11707;
VS_STTEXT_SHIFT     = 11708;
VS_STTEXT_PRECISION = 11709;
VS_STTEXT_FILLED    = 11710;
VS_STTEXT_FONTFILE  = 11711;
VS_STTEXT_FONTSYS   = 11712;
VS_STTEXT_BIGFONT   = 11713;
VS_STTEXT_NCHARS    = 11714;
VS_STTEXT_BYSYMBOLS = 11715;
VS_STTEXT_BYLINES   = 11716;

VS_STDIM_TITLE     = 11801;
VS_STDIM_TITLE1    = 11802;
VS_STDIM_TITLE2    = 11803;
VS_STDIM_TITLE3    = 11804;
VS_STDIM_TA_ABOVE  = 11805;
VS_STDIM_TA_CENTER = 11806;
VS_STDIM_TA_BELOW  = 11807;
VS_STDIM_NAME      = 11811;
VS_STDIM_NAME2     = 11812;
VS_STDIM_INSLINE   = 11821;
VS_STDIM_ARRHEAD   = 11822;
VS_STDIM_ARRTYPE	 = 11823;
VS_STDIM_ARRLEN    = 11824;
VS_STDIM_ARRH      = 11825;
VS_STDIM_EXTLINE   = 11826;
VS_STDIM_OFFSET    = 11827;
VS_STDIM_EXTEND    = 11828;
VS_STDIM_COLORS    = 11829;
VS_STDIM_OWNCOL    = 11830;
VS_STDIM_COLDIM    = 11831;
VS_STDIM_COLEXL    = 11832;
VS_STDIM_COLTXT    = 11833;
VS_STDIM_CENTER    = 11834;
VS_STDIM_CENMARK   = 11835;
VS_STDIM_CENLINE   = 11836;
VS_STDIM_CENNONE   = 11837;
VS_STDIM_CENSIZE   = 11838;
VS_STDIM_PREFIX    = 11851;
VS_STDIM_TXTSTYLE  = 11852;
VS_STDIM_TXTALIGN  = 11853;
VS_STDIM_TXTH      = 11854;
VS_STDIM_TXTGAP    = 11855;
VS_STDIM_TXTDEC    = 11856;
VS_STDIM_SCALE     = 11857;
VS_STDIM_ROUND     = 11858;
VS_STDIM_TOLER     = 11859;
VS_STDIM_TPLUS     = 11860;
VS_STDIM_TMINUS    = 11861;
VS_STDIM_TXTHORZ   = 11862;
VS_STDIM_TXTARC90  = 11863;
VS_STDIM_TXTRECT   = 11864;
VS_STDIM_ENDZERO   = 11865;

VS_STHAT_TITLE     = 11901;
VS_STHAT_TITLE2    = 11902;
VS_STHAT_APPLY     = 11903;
VS_STHAT_NAME      = 11904;
VS_STHAT_NAME2     = 11905;
VS_STHAT_DESC      = 11906;
VS_STHAT_LOAD      = 11907;

VS_BLOCKS_TITLE    = 12001;
VS_BLOCKS_ADD      = 12002;
VS_BLOCKS_DELETE   = 12003;
VS_BLOCKS_NAME     = 12004;
VS_BLOCKS_VIEW     = 12005;
VS_BLOCKS_NAME2    = 12006;
VS_BLOCKS_SIZE     = 12007;
VS_BLOCKS_DX       = 12008;
VS_BLOCKS_DY       = 12009;
VS_BLOCKS_ENTS     = 12010;
VS_BLOCKS_BYLAYER  = 12011;
VS_BLOCKS_EDIT     = 12012;

VS_SELBLK_TITLE    = 12031;
VS_SELBLK_NSEL     = 12032;
VS_SELBLK_SELALL   = 12033;
VS_SELBLK_UNSELALL = 12034;

VS_NEWBLK_TITLE    = 12051;
VS_NEWBLK_NAME     = 12052;

VS_STPNT_TITLE     = 12101;
VS_STPNT_SIMPLE    = 12102;
VS_STPNT_NODRAW    = 12103;
VS_STPNT_DRAWBLK   = 12104;
VS_STPNT_DRAWTEXT  = 12105;
VS_STPNT_DRAWALL   = 12106;
VS_STPNT_NAME      = 12117;
VS_STPNT_STAT      = 12118;
VS_STPNT_LAYER     = 12119;
VS_STPNT_TEXT      = 12120;
VS_STPNT_TSTYLE    = 12121;
VS_STPNT_THIGH     = 12122;
VS_STPNT_TSCALE    = 12123;
VS_STPNT_SYMBOL    = 12124;
VS_STPNT_BLOCK     = 12125;
VS_STPNT_BSCALE    = 12126;
VS_STPNT_FIXED     = 12127;
VS_STPNT_SNAP      = 12128;

VS_GRID_TITLE      = 12401;
VS_GRID_POINT      = 12402;
VS_GRID_CROSS      = 12403;
VS_GRID_CROSS45    = 12404;
VS_GRID_LINE       = 12405;
VS_GRID_DOTLINE    = 12406;
VS_GRID_DASHLINE   = 12407;
VS_GRID_ORIGIN     = 12411;
VS_GRID_STEP       = 12412;
VS_GRID_HORZ       = 12413;
VS_GRID_VERT       = 12414;
VS_GRID_BOLDSTEP   = 12415;
VS_GRID_SNAP       = 12416;
VS_GRID_SHOW       = 12417;
VS_GRID_PRINT      = 12418;
VS_GRID_MAIN       = 12419;
VS_GRID_BOLD       = 12420;
VS_GRID_TYPE       = 12421;
VS_GRID_COLOR      = 12422;

VS_OSNAP_TITLE     = 12431;
VS_OSNAP_END       = 12432;
VS_OSNAP_MID       = 12433;
VS_OSNAP_CENTER    = 12434;
VS_OSNAP_POINT     = 12435;
VS_OSNAP_INTER     = 12436;
VS_OSNAP_NEAR      = 12437;
VS_OSNAP_GRIP      = 12438;
VS_OSNAP_PERP      = 12439;
VS_OSNAP_TANG      = 12440;
VS_OSNAP_CLEAR     = 12441;
VS_OSNAP_APERSIZE  = 12442;
VS_OSNAP_SELECT    = 12443;
VS_OSNAP_REALTIME  = 12444;

VS_PSNAP_TITLE     = 12461;
VS_PSNAP_ON        = 12462;
VS_PSNAP_DIST      = 12463;
VS_PSNAP_ANGLE     = 12464;
VS_PSNAP_ANGLE_0   = 12465;

VS_UNITS_TITLE     = 12501;
VS_UNITS_UNITS     = 12502;
VS_UNITS_SCALE     = 12503;
VS_UNITS_X0        = 12504;
VS_UNITS_Y0        = 12505;
VS_UNITS_GEO       = 12506;
VS_UNITS_PREC      = 12507;
VS_UNIT_POINT      = 12511;
VS_UNIT_MM         = 12512;
VS_UNIT_CM         = 12513;
VS_UNIT_MET        = 12514;
VS_UNIT_KM         = 12515;
VS_UNIT_INCH       = 12516;
VS_UNIT_FOOT       = 12517;
VS_UNIT_YARD       = 12518;
VS_UNIT_MILE       = 12519;
VS_UNIT_SEAMILE    = 12520;
VS_ANG_DEGREE      = 12531;
VS_ANG_RADIAN      = 12532;

VS_PRIV_TITLE      = 12551;
VS_PRIV_DWGTITLE   = 12552;
VS_PRIV_OWNER      = 12553;
VS_PRIV_COMMENT    = 12554;
VS_PRIV_PSW        = 12555;
VS_PRIV_INFO       = 12556;
VS_PRIV_NOPSW      = 12557;
VS_PRIV_NOLOAD     = 12558;
VS_PRIV_VIEWONLY   = 12559;
VS_PRIV_NOEXPORT   = 12560;
VS_PRIV_NOPRINT    = 12561;

VS_PSW_TITLE       = 12581;
VS_PSW_WRONG       = 12582;
VS_PSW_READONLY    = 12583;
VS_PSW_WORD        = 12584;

VS_PREF_TITLE      = 12601;
VS_PREF_AUTOSELPNT = 12602;
VS_PREF_AUTOSELWIN = 12603;
VS_PREF_SHOWGRID   = 12604;
VS_PREF_SHOWFILL   = 12605;
VS_PREF_SHOWLINEW  = 12606;
VS_PREF_SHOWVECT   = 12607;
VS_PREF_SHOWBMP    = 12608;
VS_PREF_PENW0      = 12609;
VS_PREF_CURSOR     = 12613;
VS_PREF_SIZECURS   = 12614;
VS_PREF_COLCURS    = 12615;
VS_PREF_GRIPS      = 12616;
VS_PREF_GRIPSIZE   = 12617;
VS_PREF_COLGRIP    = 12618;
VS_PREF_COLSELGRIP = 12619;
VS_PREF_COLBKG     = 12620;
VS_PREF_COLPAGE    = 12621;
VS_PREF_COLSELOBJ  = 12622;
VS_PREF_CCOLOR     = 12623;
VS_PREF_BYLAYER    = 12624;
VS_PREF_SEGCURVE   = 12625;
VS_PREF_CHARFRAME  = 12626;
VS_PREF_UNSELAFTER = 12627;
VS_PREF_SELINSIDE  = 12628;
VS_PREF_SELACTLAYER= 12629;

VS_NAV_TITLE       = 12701;
VS_NAV_ZRCOLOR     = 12702;
VS_NAV_REALTIME    = 12703;

VS_SELSTLINE       = 12801;

VS_ENT_TITLE       = 13001;
VS_ENT_LAYER       = 13002;
VS_ENT_LTYPE       = 13003;
VS_ENT_PAGE        = 13004;
VS_ENT_LCOL        = 13005;
VS_ENT_FCOL        = 13006;
VS_ENT_BYLAY       = 13007;
VS_ENT_FILLED      = 13008;
VS_ENT_BORDER      = 13009;
VS_ENT_LINEW       = 13010;
VS_ENT_LEVEL       = 13011;
VS_ENT_LIMITS      = 13012;
VS_ENT_HANDLE      = 13013;
VS_ENT_KEY         = 13014;

VS_ARR_TITLE   = 13031;
VS_ARR_DIMST0  = 13032;
VS_ARR_DIMST1  = 13033;

VS_LINE_TITLE      = 13101;
VS_LINE_PNT1       = 13102;
VS_LINE_PNT2       = 13103;
VS_LINE_ARROW      = 13104;
VS_LINE_NOARROW    = 13105;
VS_LINE_LENGTH     = 13106;
VS_LINE_ANGLE      = 13107;

VS_TEXT_TITLE      = 13201;
VS_TEXT_TITLE2     = 13202;
VS_TEXT_TA_LEFBOT  = 13203;
VS_TEXT_TA_MIDBOT  = 13204;
VS_TEXT_TA_RIGBOT  = 13205;
VS_TEXT_TA_LEFMID  = 13206;
VS_TEXT_TA_MIDMID  = 13207;
VS_TEXT_TA_RIGMID  = 13208;
VS_TEXT_TA_LEFTOP  = 13209;
VS_TEXT_TA_MIDTOP  = 13210;
VS_TEXT_TA_RIGTOP  = 13211;
VS_TEXT_NO_PATH    = 13212;
VS_TEXT_POINT      = 13221;
VS_TEXT_HEIGHT     = 13222;
VS_TEXT_WIDTH      = 13223;
VS_TEXT_ROTANG     = 13224;
VS_TEXT_IVERT      = 13225;
VS_TEXT_IHORZ      = 13226;
VS_TEXT_ALIGN      = 13227;
VS_TEXT_STYLE      = 13228;
VS_TEXT_TEXT       = 13229;
VS_TEXT_OBLIQUE    = 13230;
VS_TEXT_STRIKEOUT  = 13231;
VS_TEXT_UNDERLINE  = 13232;
VS_TEXT_PTWRITE    = 13241;
VS_TEXT_PTBACK     = 13242;
VS_TEXT_PTABSANG   = 13243;
VS_TEXT_PTHANDLE   = 13244;
VS_TEXT_PTDY       = 13245;
VS_TEXT_PTDX       = 13246;

VS_CIRC_TITLE      = 13301;
VS_CIRC_CENTER     = 13302;
VS_CIRC_RADIUS     = 13303;
VS_CIRC_LENGTH     = 13304;
VS_CIRC_AREA       = 13305;

VS_POLY_TITLE      = 13401;
VS_POLY_LINE       = 13402;
VS_POLY_BSPLINE2   = 13403;
VS_POLY_BSPLINE3   = 13404;
VS_POLY_FITBSPL3   = 13405;
VS_POLY_LINBSPL2   = 13406;
VS_POLY_AUTOBEZIER = 13407;
VS_POLY_BEZIER     = 13408;
VS_POLY_ROUNDED    = 13409;
VS_POLY_MULTIRAD   = 13410;
VS_POLY_BULGE      = 13411;
VS_POLY_CLOSED     = 13421;
VS_POLY_SMOOTH     = 13422;
VS_POLY_RAD        = 13423;
VS_POLY_PERIM      = 13424;
VS_POLY_AREA       = 13425;
VS_POLY_DIMST0     = 13429;
VS_POLY_DIMST1     = 13430;
VS_POLY_NVER       = 13434;
VS_POLY_VERTABLE   = 13435;

VS_PVER_TITLE      = 13451;
VS_PVER_ONLINE     = 13452;
VS_PVER_OFFLINE    = 13453;
VS_PVER_CLOSE      = 13454;
VS_PVER_ADD        = 13455;
VS_PVER_INSERT     = 13456;
VS_PVER_DELETE     = 13457;
VS_PVER_RADIUS     = 13458;
VS_PVER_ONCURVE    = 13459;
VS_PVER_BULGE      = 13460;
VS_PVER_LENGTH     = 13461;
VS_PVER_ANGLE      = 13462;

VS_INSBLK_TITLE    = 13501;
VS_INSBLK_NAME     = 13502;
VS_INSBLK_POINT    = 13503;
VS_INSBLK_ANGLE    = 13504;
VS_INSBLK_SCX      = 13505;
VS_INSBLK_SCY      = 13506;
VS_INSBLK_WIDTH    = 13507;
VS_INSBLK_HEIGHT   = 13508;
VS_INSBLK_BYLAY    = 13509;

VS_HATCH_TITLE     = 13601;
VS_HATCH_NAME      = 13602;
VS_HATCH_ANGLE     = 13603;
VS_HATCH_SCALE     = 13604;
VS_HATCH_SIZE      = 13605;

VS_POINT_TITLE     = 13701;
VS_POINT_TYPE      = 13703;
VS_POINT_BLKANG    = 13704;
VS_POINT_TEXT      = 13705;
VS_POINT_TXTANG    = 13706;
VS_POINT_TXTOFFSET = 13707;
VS_POINT_FIXED     = 13708;

VS_BMP_TITLE       = 13801;
VS_BMP_FILE        = 13802;
VS_BMP_INS         = 13803;
VS_BMP_RES         = 13804;
VS_BMP_RESH        = 13805;
VS_BMP_RESV        = 13806;
VS_BMP_WIDTH       = 13807;
VS_BMP_HEIGHT      = 13808;
VS_BMP_RELOAD      = 13809;

VS_ELL_TITLE       = 13901;
VS_ELL_CENTER      = 13902;
VS_ELL_RADIUS      = 13903;
VS_ELL_RH          = 13904;
VS_ELL_RV          = 13905;
VS_ELL_ANGLE       = 13906;
VS_ELL_LEN         = 13907;
VS_ELL_AREA        = 13908;

VS_ARC_TITLE       = 14001;
VS_ARC_CENTER      = 14002;
VS_ARC_TYPE        = 14007;
VS_ARC_ARC         = 14008;
VS_ARC_CHORD       = 14009;
VS_ARC_SECTOR      = 14010;
VS_ARC_LEN         = 14013;
VS_ARC_AREA        = 14014;
VS_ARC_RADIUS      = 14021;
VS_ARC_RH          = 14022;
VS_ARC_RV          = 14023;
VS_ARC_ANG0        = 14024;
VS_ARC_ANGARC      = 14025;
VS_ARC_ANGROT      = 14026;

VS_RECT_TITLE      = 14101;
VS_RECT_CENTER     = 14102;
VS_RECT_W          = 14103;
VS_RECT_H          = 14104;
VS_RECT_RAD        = 14105;
VS_RECT_ANG        = 14106;
VS_RECT_LEN        = 14107;
VS_RECT_AREA       = 14108;

VS_SYMB_TITLE      = 14201;
VS_SYMB_HEIGHT     = 14202;
VS_SYMB_FONT       = 14203;

VS_DIM_TITLE       = 14401;
VS_DIM_HORZ        = 14402;
VS_DIM_VERT        = 14403;
VS_DIM_PARAL       = 14404;
VS_DIM_ANG         = 14405;
VS_DIM_RAD         = 14406;
VS_DIM_DIAM        = 14407;
VS_DIM_ORD         = 14408;
VS_DIM_OWN         = 14412;
VS_DIM_TYPE        = 14413;
VS_DIM_MEASURE     = 14414;
VS_DIM_VALUE       = 14415;
VS_DIM_STYLE       = 14416;

VS_INSDWG_TITLE    = 14501;
VS_INSDWG_FNAME    = 14502;
VS_INSDWG_INSPNT   = 14503;
VS_INSDWG_ANGLE    = 14504;
VS_INSDWG_SCX      = 14505;
VS_INSDWG_SCY      = 14506;
VS_INSDWG_WIDTH    = 14507;
VS_INSDWG_HEIGHT   = 14508;
VS_INSDWG_RELOAD   = 14509;

VS_PRINT_TITLE     = 16001;
VS_PRINT_PRINTER   = 16002;
VS_PRINT_PICK      = 16003;
VS_PRINT_FIT       = 16004;
VS_PRINT_ALL       = 16005;
VS_PRINT_PAGE      = 16006;
VS_PRINT_PRECT     = 16007;
VS_PRINT_DISP      = 16008;
VS_PRINT_WIN       = 16009;
VS_PRINT_PGALL     = 16010;
VS_PRINT_PGCUR     = 16011;
VS_PRINT_PGNO      = 16012;
VS_PRINT_CURPRN    = 16013;
VS_PRINT_PAPERSIZE = 16014;
VS_PRINT_RES       = 16015;
VS_PRINT_REGION    = 16016;
VS_PRINT_WLEFBOT   = 16017;
VS_PRINT_WRIGTOP   = 16018;
VS_PRINT_REGSIZE   = 16019;
VS_PRINT_SCALE     = 16020;
VS_PRINT_ATX       = 16021;
VS_PRINT_ATY       = 16022;
VS_PRINT_ORIGIN    = 16023;
VS_PRINT_COPIES    = 16024;
VS_PRINT_PAGES     = 16025;
VS_PRINT_PRECTS    = 16026;
VS_PRINT_ALBUM     = 16027;
VS_PRINT_BOOK      = 16028;

VS_EXPBMP_TITLE    = 16101;
VS_EXPBMP_FILE     = 16102;
VS_EXPBMP_AREA     = 16103;
VS_EXPBMP_ALL      = 16104;
VS_EXPBMP_DISP     = 16105;
VS_EXPBMP_WIN      = 16106;
VS_EXPBMP_PICK     = 16107;
VS_EXPBMP_LEFBOT   = 16108;
VS_EXPBMP_RIGTOP   = 16109;
VS_EXPBMP_SIZEMM   = 16110;
VS_EXPBMP_RES      = 16111;
VS_EXPBMP_SIZEPIX  = 16112;

VS_EXPSHP_TITLE     = 16121;
VS_EXPSHP_ENTITIES  = 16122;
VS_EXPSHP_TYPE      = 16123;
VS_EXPSHP_LAYER     = 16124;
VS_EXPSHP_ALLLAYERS = 16125;
VS_EXPSHP_SELECTED  = 16126;
VS_EXPSHP_CONVERT   = 16127;
VS_EXPSHP_ARCS      = 16128;
VS_EXPSHP_LATITUDE  = 16129;
VS_EXPSHP_LONGITUDE = 16130;
VS_EXPSHP_POINT     = 16131;
VS_EXPSHP_POLYLINE  = 16132;
VS_EXPSHP_POLYGON   = 16133;
VS_EXPSHP_LAYERS_DIFFER = 16134;

VS_PRR_TITLE       = 16201;
VS_PRR_EXIT        = 16202;
VS_PRR_ADD         = 16203;
VS_PRR_DEL         = 16204;
VS_PRR_FORALL      = 16205;
VS_PRR_MOVE        = 16206;
VS_PRR_COLOR       = 16207;
VS_PRR_SHOW        = 16208;
VS_PRR_HX          = 16209;
VS_PRR_HY          = 16210;
VS_PRR_HSIZE       = 16211;
VS_PRR_HANGLE      = 16212;
VS_PRR_CENTER      = 16213;
VS_PRR_PRM         = 16214;
VS_PRR_W           = 16215;
VS_PRR_H           = 16216;
VS_PRR_ANG         = 16217;
VS_PRR_AUTOSPLIT   = 16218;
VS_PRR_ALLDELETE   = 16219;
VS_PRR_NOSIZE      = 16220;

VS_DIST_TITLE      = 16301;
VS_DIST_BYOBJ      = 16302;
VS_DIST_START      = 16303;
VS_DIST_RESET      = 16304;
VS_DIST_DIST       = 16305;
VS_DIST_PERIM      = 16306;
VS_DIST_ANGLE      = 16307;
VS_DIST_AREA       = 16308;
VS_DIST_SUMAREA    = 16309;

VS_STAT_DWGFILE    = 17001;
VS_STAT_FILESIZE   = 17002;
VS_STAT_DWGWIDTH   = 17003;
VS_STAT_DWGHEIGHT  = 17004;
VS_STAT_DWGLEFT    = 17005;
VS_STAT_DWGBOTTOM  = 17006;
VS_STAT_DWGRIGHT   = 17007;
VS_STAT_DWGTOP     = 17008;
VS_STAT_DRAWTIME   = 17009;
VS_STAT_PAGES      = 17021;
VS_STAT_LAYERS     = 17022;
VS_STAT_STLINES    = 17023;
VS_STAT_STTEXTS    = 17024;
VS_STAT_STHATCHS   = 17025;
VS_STAT_STDIMS     = 17026;
VS_STAT_STPOINTS   = 17027;
VS_STAT_BLOCKS     = 17028;
VS_STAT_ENTS       = 17029;
VS_STAT_POLYVERS   = 17030;
VS_STAT_TEXTCHARS  = 17031;
VS_STAT_ENTBYLAYER = 17041;
VS_STAT_ENTBYPAGE  = 17042;
VS_STAT_ENTBYBLOCK = 17043;
VS_STAT_ENTBYTYPE  = 17050;
VS_STAT_POINT      = 17051;
VS_STAT_LINE       = 17052;
VS_STAT_POLY       = 17053;
VS_STAT_CIRCLE     = 17054;
VS_STAT_ARC        = 17055;
VS_STAT_ELLIPSE    = 17056;
VS_STAT_TEXT       = 17057;
VS_STAT_BITMAP     = 17058;
VS_STAT_INSBLOCK   = 17059;
VS_STAT_HATCH      = 17060;
VS_STAT_RECT       = 17061;
VS_STAT_DIMLIN     = 17062;
VS_STAT_DIMANG     = 17063;
VS_STAT_DIMRAD     = 17064;
VS_STAT_DIMDIAM    = 17065;
VS_STAT_DIMORD     = 17066;
VS_STAT_FILEVECVER = 17070;
VS_STAT_CURVECVER  = 17071;

VS_MENU_ENTPROP    = 18001;
VS_MENU_COPY       = 18002;
VS_MENU_MOVE       = 18003;
VS_MENU_ROTATE     = 18004;
VS_MENU_SCALE      = 18005;
VS_MENU_MIRROR     = 18006;
VS_MENU_CREBLOCK   = 18007;
VS_MENU_EXPLODE    = 18008;
VS_MENU_ERASE      = 18009;
VS_MENU_UNSELALL   = 18010;
VS_MENU_JOIN       = 18011;
VS_MENU_VER_INS    = 18021;
VS_MENU_VER_DEL    = 18022;
VS_MENU_VER_RAD    = 18023;
VS_MENU_VER_FIX    = 18024;
VS_MENU_VER_EDIT   = 18025;

VS_SEL_BY_HANDLE   = 18101;
VS_ENTER_HANDLE    = 18102;
VS_SEL_BY_KEY      = 18103;
VS_ENTER_KEY       = 18104;
VS_N_WAS_SELECTED  = 18105;

VS_GRIDPLINE_TITLE = 18151;

// tooltips string
VS_TT_FILE_NEW        = 19001;
VS_TT_FILE_OPEN       = 19002;
VS_TT_FILE_SAVE       = 19003;
VS_TT_PRINT           = 19004;
VS_TT_TOOL_PRNRECT    = 19005;
VS_TT_ZOOM_ALL        = 19006;
VS_TT_ZOOM_WIN        = 19007;
VS_TT_ZOOM_IN         = 19008;
VS_TT_ZOOM_OUT        = 19009;
VS_TT_ZOOM_PAN        = 19010;
VS_TT_ZOOM_PREV       = 19011;
VS_TT_ZOOM_SEL        = 19012;
VS_TT_PAGE_DLG        = 19015;
VS_TT_PAGE_PREV       = 19016;
VS_TT_PAGE_NEXT       = 19017;
VS_TT_RESET           = 19021;
VS_TT_SHOWGRID        = 19022;
VS_TT_SHOWLINEW       = 19023;
VS_TT_SHOWFILL        = 19024;
VS_TT_TOOL_DIST       = 19025;
VS_TT_FMT_LAYOUT      = 19029;
VS_TT_FMT_STDIM       = 19030;
VS_TT_FMT_LAYER       = 19031;
VS_TT_EDIT_UNDO       = 19032;
VS_TT_EDIT_REDO       = 19033;
VS_TT_EDIT_CBCUT      = 19034;
VS_TT_EDIT_CBCOPY     = 19035;
VS_TT_EDIT_CBPASTE    = 19036;
VS_TT_EDIT_ENTPROP    = 19037;
VS_TT_EDIT_COPY       = 19038;
VS_TT_EDIT_MOVE       = 19039;
VS_TT_EDIT_ROTATE     = 19040;
VS_TT_EDIT_SCALE      = 19041;
VS_TT_EDIT_MIRROR     = 19042;
VS_TT_EDIT_ERASE      = 19043;
VS_TT_EDIT_EXPLODE    = 19044;
VS_TT_EDIT_CREBLOCK   = 19045;
VS_TT_DRAW_POINT      = 19051;
VS_TT_DRAW_LINE       = 19052;
VS_TT_DRAW_POLYLINE   = 19053;
VS_TT_DRAW_SPLINE     = 19054;
VS_TT_DRAW_CIRC_CR    = 19055;
VS_TT_DRAW_CIRC_3P    = 19056;
VS_TT_DRAW_ARC_CSE    = 19057;
VS_TT_DRAW_ARC_SME    = 19058;
VS_TT_DRAW_ELLIPSE    = 19059;
VS_TT_DRAW_RECT       = 19060;
VS_TT_DRAW_HATCH      = 19061;
VS_TT_DRAW_TEXT       = 19062;
VS_TT_DRAW_SYMBOL     = 19063;
VS_TT_DRAW_BLOCK      = 19064;
VS_TT_DRAW_IMAGE      = 19065;
VS_TT_DRAW_FLOOD      = 19066;
VS_TT_DRAW_DIM_HOR    = 19071;
VS_TT_DRAW_DIM_VER    = 19072;
VS_TT_DRAW_DIM_PAR    = 19073;
VS_TT_DRAW_DIM_ANG    = 19074;
VS_TT_DRAW_DIM_RAD    = 19075;
VS_TT_DRAW_DIM_DIAM   = 19076;
VS_TT_DRAW_DIM_ORD    = 19077;
VS_TT_SNAP_END        = 19101;
VS_TT_SNAP_MID        = 19102;
VS_TT_SNAP_INTER      = 19103;
VS_TT_SNAP_CEN        = 19104;
VS_TT_SNAP_KNOT       = 19105;
VS_TT_SNAP_PERP       = 19106;
VS_TT_SNAP_TANG       = 19107;
VS_TT_SNAP_POINT      = 19108;
VS_TT_SNAP_NEAR       = 19109;
VS_TT_SNAP_GRID       = 19110;
VS_TT_SNAP_POLAR      = 19111;
VS_TT_SNAP_CLEAR      = 19112;
VS_TT_SNAP_DLG        = 19113;

VS_CC_ZOOMWIN   = 19201;
VS_CC_ZOOMPAN   = 19202;
VS_CC_PRINT     = 19203;
VS_CC_PRNRECT   = 19204;
VS_CC_EXPBMP    = 19205;
VS_CC_POINT     = 19206;
VS_CC_LINE      = 19207;
VS_CC_CIRCLE    = 19208;
VS_CC_ARC       = 19209;
VS_CC_SECTOR    = 19210;
VS_CC_ELLIPSE   = 19211;
VS_CC_POLYLINE  = 19212;
VS_CC_TEXT      = 19213;
VS_CC_INSERT    = 19214;
VS_CC_HATCH     = 19215;
VS_CC_BITMAP    = 19216;
VS_CC_SYMBOL    = 19217;
VS_CC_RECT      = 19218;
VS_CC_DIMHOR    = 19219;
VS_CC_DIMVER    = 19220;
VS_CC_DIMPAR    = 19221;
VS_CC_DIMANG    = 19222;
VS_CC_DIMRAD    = 19223;
VS_CC_DIMDIAM   = 19224;
VS_CC_DIMORD    = 19225;
VS_CC_SELBYPOINT   = 19226;
VS_CC_SELBYRECT    = 19227;
VS_CC_SELBYPOLYGON = 19228;
VS_CC_SELBYPOLYLINE = 19229;
VS_CC_SELBYDIST = 19230;
VS_CC_MOVEGRIP  = 19231;
VS_CC_ENTPROP   = 19232;
VS_CC_MOVE      = 19233;
VS_CC_COPY      = 19234;
VS_CC_ROTATE    = 19235;
VS_CC_SCALE     = 19236;
VS_CC_MIRROR    = 19237;
VS_CC_ERASE     = 19238;
VS_CC_CREBLOCK  = 19239;
VS_CC_EXPLODE   = 19240;
VS_CC_SPLINE    = 19241;
VS_CC_DIST      = 19242;
VS_CC_INSVEC    = 19243;
VS_CC_ENTSWAP     = 19244;
VS_CC_ENTTOTOP    = 19245;
VS_CC_ENTTOBOTTOM = 19246;

VS_SELOBJECTS   = 19301;
VS_CORNER1      = 19302;
VS_CORNER2      = 19303;
VS_BASE_P       = 19304;
VS_BASE_P1      = 19305;
VS_BASE_P2      = 19306;
VS_DISPLACE     = 19307;
VS_POINT1       = 19308;
VS_POINT2       = 19309;
VS_POINT3       = 19310;
VS_CENTER_P     = 19311;
VS_RAD_P        = 19312;
VS_START_P      = 19313;
VS_END_P        = 19314;
VS_RAD1ANG      = 19315;
VS_RAD2         = 19316;
VS_NEXT_P       = 19317;
VS_INS_P        = 19318;
VS_LEADER1      = 19319;
VS_LEADER2      = 19320;
VS_TEXT_P       = 19321;
VS_ORD_P        = 19322;
VS_ORD_X        = 19323;
VS_ORD_Y        = 19324;
VS_MOVE2        = 19325;
VS_COPY2        = 19326;
VS_ROTATE1      = 19327;
VS_ROTATE2      = 19328;
VS_ROTATE3      = 19329;
VS_SCALE3       = 19330;
VS_MIRROR1      = 19331;
VS_MIRROR2      = 19332;
VS_PICK_ENT     = 19333;
VS_PICK_ENT1    = 19334;
VS_PICK_ENT2    = 19335;

VS_PAPER_UNLIMITED = 19401;
VS_PAPER_A0        = 19402;
VS_PAPER_A1        = 19403;
VS_PAPER_A2        = 19404;
VS_PAPER_A3        = 19405;
VS_PAPER_A4        = 19406;
VS_PAPER_A5        = 19407;
VS_PAPER_A6        = 19408;
VS_PAPER_B0        = 19409;
VS_PAPER_B1        = 19410;
VS_PAPER_B2        = 19411;
VS_PAPER_B3        = 19412;
VS_PAPER_B4        = 19413;
VS_PAPER_B5        = 19414;
VS_PAPER_B6        = 19415;
VS_PAPER_C0        = 19416;
VS_PAPER_C1        = 19417;
VS_PAPER_C2        = 19418;
VS_PAPER_C3        = 19419;
VS_PAPER_C4        = 19420;
VS_PAPER_C5        = 19421;
VS_PAPER_C6        = 19422;
VS_PAPER_ANSI_A    = 19423;
VS_PAPER_ANSI_B    = 19424;
VS_PAPER_ANSI_C    = 19425;
VS_PAPER_ANSI_D    = 19426;
VS_PAPER_ANSI_E    = 19427;
VS_PAPER_LETTER    = 19428;
VS_PAPER_LEGAL     = 19429;
VS_PAPER_EXECUTIVE = 19430;
VS_PAPER_LEDGER    = 19431;
VS_PAPER_USER      = 19432;


//-------------------------------------
// VeCAD point
//-------------------------------------
type
  RECT = record
    left : Integer;
    top : Integer;
    right : Integer;
    bottom : Integer;
  end;
  PRECT = ^RECT;

  VLPOINT = record
    x : Double;
    y : Double;
  end;
  PVLPOINT =^VLPOINT;

  VLARC = record
    Cen : VLPOINT;
    Rh : Double;
    Rv : Double;
    Ang0 : Double;
    AngArc : Double;
    AngRot : Double;
  end;
  PVLARC = ^VLARC;

//-------------------------------------
// used to pass parameters with VM_BEGINPAINT message
//-------------------------------------
  VLPAINTSTRUCT = record
    dc : HDC;
    rcPaint : RECT;
    DwgLeft : Double;
    DwgBottom : Double;
    DwgRight : Double;
    DwgTop : Double;
    ScaleX : Double;
    ScaleY : Double;
  end;
  PVLPAINTSTRUCT = ^VLPAINTSTRUCT;

//-------------------------------------
// Properties of "Navigator" window (aerial view)
//-------------------------------------
  VLNAVIGATOR = record
    Left : Integer;
    Top : Integer;
    Width : Integer;
    Height : Integer;
    ColorZoomRect : Integer;
    Realtime : Integer;
  end;
  PVLNAVIGATOR = ^VLNAVIGATOR;

//-------------------------------------
// Properties of "Layers Manager" window
//-------------------------------------
  VLLAYWIN = record
    Left : Integer;
    Top : Integer;
    Width : Integer;
    Height : Integer;
  end;
  PVLLAYWIN = ^VLLAYWIN;



/////////////////////////////////////////////////
// Vecad functions definitions

Function vlGetVersion :Integer; stdcall; external 'vecad52.dll';

// Registration for user copy of VeCAD DLL
Function vlRegistration  (RegCode: Integer): Boolean; stdcall; external 'vecad52.dll';

// Set application-defined function that will receive messages from VeCAD
Function vlSetMsgHandler (pfDwgProc: Pointer): Boolean; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// VeCAD window functions
Function vlWndCreate       (parent: HWND; style,x,y,w,h: Integer): HWND; stdcall; external 'vecad52.dll';
Function vlWndResize       (hWnd: HWND; X,Y,W,H: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlWndSetTitle     (hWnd: HWND; pTitle: Pchar): Boolean; stdcall; external 'vecad52.dll';
Function vlWndSetMaxRect   (hWnd: HWND; Rect: PRect): Boolean; stdcall; external 'vecad52.dll';
Function vlWndSetCursor    (hWnd: HWND; hCursor: HCURSOR): Boolean; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// Drawing object functions
Function vlDocCreate     (hwVec: HWND):Integer; stdcall; external 'vecad52.dll';
Function vlDocDelete     (iDwg: Integer):Boolean; stdcall; external 'vecad52.dll';
Function vlDocSetActive  (iDwg: Integer):Integer; stdcall; external 'vecad52.dll';
Function vlDocGetActive  :Integer; stdcall; external 'vecad52.dll';
Function vlDocCopy       (iDwgSrc, iDwgDest, Mode: Integer):Boolean; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// All Next functions work with current drawing that 
// are set by vlDwgSetCurrent function

/////////////////////////////////////////////////
// Layout (pages,layers, text styles, etc...
// Parameters can be accessed via vlData...

Function vlPageAdd       (Name: Pchar; Size, Orient, W, H: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlPageDelete    (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlPageActive    (Mode, Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlPageCount     : Integer; stdcall; external 'vecad52.dll';
Function vlPageIndex     (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlLayerAdd      (Name: Pchar; LineWidth: Double; LineColor, FillColor: COLORREF): Integer; stdcall; external 'vecad52.dll';
Function vlLayerDelete   (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlLayerActive   (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlLayerCount    : Integer; stdcall; external 'vecad52.dll';
Function vlLayerIndex    (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlStLineAdd     (Name, Desc: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlStLineDelete  (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlStLineActive  (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlStLineCount   : Integer; stdcall; external 'vecad52.dll';
Function vlStLineIndex   (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlStTextAdd     (Name, Font: Pchar; Width, Oblique: Double; Prec: Integer; Filled, Bold: Boolean): Integer; stdcall; external 'vecad52.dll';
Function vlStTextDelete  (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlStTextActive  (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlStTextCount   : Integer; stdcall; external 'vecad52.dll';
Function vlStTextIndex   (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlStTextReload  : Boolean; stdcall; external 'vecad52.dll';

Function vlStHatchAdd    (Name, Desc: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlStHatchDelete (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlStHatchActive (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlStHatchCount  : Integer; stdcall; external 'vecad52.dll';
Function vlStHatchIndex  (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlStDimAdd      (Name: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlStDimDelete   (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlStDimActive   (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlStDimCount    : Integer; stdcall; external 'vecad52.dll';
Function vlStDimIndex    (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlStPointAdd    (Name: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlStPointDelete (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlStPointActive (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlStPointCount  : Integer; stdcall; external 'vecad52.dll';
Function vlStPointIndex  (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlGrPointAdd    (Name: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlGrPointDelete (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlGrPointActive (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlGrPointCount  : Integer; stdcall; external 'vecad52.dll';
Function vlGrPointIndex  (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlViewSave      (Name: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlViewDelete    (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlViewRestore   (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlViewCount     : Integer; stdcall; external 'vecad52.dll';
Function vlViewIndex     (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';

Function vlPrnRectAdd    (X, Y, W, H, Angle: Double): Integer; stdcall; external 'vecad52.dll';
Function vlPrnRectDelete (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlPrnRectCount  : Integer; stdcall; external 'vecad52.dll';
Function vlPrnRectPrint  (Index: Integer; hPrintDC: HDC; ScaleX,ScaleY,OriginX,OriginY: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlPrnRectAuto   (Width, Height: Double): Integer; stdcall; external 'vecad52.dll';

Function vlBlockBegin    : Boolean; stdcall; external 'vecad52.dll';
Function vlBlockAdd      (Name: Pchar; X, Y: Double): Integer; stdcall; external 'vecad52.dll';
Function vlBlockAddF     (FileName, BlockName: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlBlockDelete   (Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlBlockActive   (Index: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlBlockCount    : Integer; stdcall; external 'vecad52.dll';
Function vlBlockIndex    (Name: Pchar; ID: Integer): Integer; stdcall; external 'vecad52.dll';


/////////////////////////////////////////////////
// Add Graphic objects to drawing
Function vlAddPoint        (X,Y: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddLine         (X1,Y1,X2,Y2: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddArcEx        (X, Y, Rh, Rv, Ang0, AngArc, AngRot: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddCircle       (X,Y: Double; Rad: Double): Integer;stdcall; external 'vecad52.dll';
Function vlAddCircle3P     (X1,Y1,X2,Y2,X3,Y3: Double): Integer;stdcall; external 'vecad52.dll';
Function vlAddArc          (X,Y,Rad,Ang1,Ang2: Double): Integer;stdcall; external 'vecad52.dll';
Function vlAddArc3P        (X1,Y1,X2,Y2,X3,Y3: Double): Integer;stdcall; external 'vecad52.dll';
Function vlAddEllipse      (X,Y: Double; Rh,Rv,Angle: Double): Integer;stdcall; external 'vecad52.dll';
Function vlSetTextParam    (Mode: Integer; data:Double): Boolean; stdcall; external 'vecad52.dll';
Function vlSetTextParams   (Align: Integer; Height,Angle,ScaleW,Oblique,HInter,VInter: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlAddText         (X,Y: Double; szStr:Pchar): Integer;stdcall; external 'vecad52.dll';
Function vlPolylineBegin   :Boolean; stdcall; external 'vecad52.dll';
Function vlVertex          (X,Y: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlVertexR         (X,Y,Radius: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlVertexF         (X,Y: Double; bOnCurve: Boolean): Boolean; stdcall; external 'vecad52.dll';
Function vlVertexB         (X,Y,Bulge: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlAddPolyline     (SmoothType: Integer; Closed: Boolean): Integer; stdcall; external 'vecad52.dll';
Function vlAddBlockIns     (Index: Integer; X,Y,Angle,Xscale,Yscale: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddHatch        (Index: Integer; Scale,Angle: Double):Integer;stdcall; external 'vecad52.dll';
Function vlAddRaster       (FileName: Pchar; X,Y,ResH,ResV: Double):Integer;stdcall; external 'vecad52.dll';
Function vlAddRect         (X,Y,W,H,Ang,Rad: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddDimHor       (X1,Y1,X2,Y2,Y: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddDimVer       (X1,Y1,X2,Y2,X: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddDimPar       (X1,Y1,X2,Y2,Off: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddDimAng       (Xcen,Ycen,X1,Y1,X2,Y2,Off: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddDimRad       (Xcen,Ycen,Xrad,Yrad,Off: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddDimDiam      (Xcen,Ycen,Xrad,Yrad: Double): Integer; stdcall; external 'vecad52.dll';
Function vlAddDimOrd       (X,Y,Xtxt,Ytxt: Double; bYord: Boolean): Integer; stdcall; external 'vecad52.dll';
Function vlAddDwgIns       (FileName: Pchar; X,Y,Angle,ScaleX,ScaleY: Double; iPage:Integer): Integer; stdcall; external 'vecad52.dll';
Function vlAddCustom       (ObjType:Integer; pData:Pointer; DataSize,ElemSize:Integer): Boolean; stdcall; external 'vecad52.dll';


/////////////////////////////////////////////////
// Drawing's storage
Function vlFileNew         (hwVec: HWND; Template: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlFileOpen        (hwVec: HWND; FileName: Pchar): Integer; stdcall; external 'vecad52.dll';
Function vlFileLoad        (Mode: Integer; FileName: Pchar): Boolean; stdcall; external 'vecad52.dll';
Function vlFileSave        (Mode: Integer; FileName: Pchar): Boolean; stdcall; external 'vecad52.dll';
Function vlFileList        (hwParent: HWND): Boolean; stdcall; external 'vecad52.dll';
Function vlFileLoadMem     (pMem: Pointer): Boolean; stdcall; external 'vecad52.dll';
Function vlFileSaveMem     (pMem: Pointer; MaxSize:Integer): Integer; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// Select objects for edit functions
Function vlGetEntity       (Mode, Prm1, Prm2: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlGetBlockEntity  (iBlock, Counter: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlSelect          (Select: Boolean; Index: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlSelectByPoint   (Select: Boolean; X, Y, Delta: Double): Integer; stdcall; external 'vecad52.dll';
Function vlSelectByRect    (Select: Boolean; Left, Bottom, Right, Top: Double; Cross: Boolean): Integer; stdcall; external 'vecad52.dll';
Function vlSelectByPolygon (Select: Boolean; Ver: PVLPOINT; Nver: Integer; Cross: Boolean): Integer; stdcall; external 'vecad52.dll';
Function vlSelectByPolyline(Select: Boolean; Ver: PVLPOINT; Nver: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlSelectByDist    (Select: Boolean; X, Y, Dist: Double; Cross: Boolean): Integer; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// Edit objects functions
// iObj - index of the object, 
// if iObj=-1 then operate with selected objects
Function vlCbCut         :Boolean;stdcall; external 'vecad52.dll';
Function vlCbCopy        :Boolean;stdcall; external 'vecad52.dll';
Function vlCbPaste       (X,Y: Double):Boolean;stdcall; external 'vecad52.dll';
Function vlCopy          (iObj: Integer; dx,dy: Double): Integer; stdcall; external 'vecad52.dll';
Function vlMove          (iObj: Integer; dx,dy: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlRotate        (iObj: Integer; X,Y,Angle: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlScale         (iObj: Integer; X,Y,Scale: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlMirror        (iObj: Integer; X1,Y1,X2,Y2: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlErase         (iObj: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlExplode       (iObj: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlJoin          (Delta: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlTrim          (iObj,iTrimEdge: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlExtend        (iObj,iExtEdge: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlFillet        (iObj1,iObj2: Integer; Radius: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlUndo          :Boolean; stdcall; external 'vecad52.dll';
Function vlRedo          :Boolean; stdcall; external 'vecad52.dll';
Function vlPolyVerInsert (iEnt, iVer: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlPolyVerDelete (iEnt, iVer: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlPolyVerGet    (iEnt, iVer: Integer; pX, pY, pPrm: PDouble): Boolean; stdcall; external 'vecad52.dll';
Function vlPolyVerSet    (iEnt, iVer: Integer; X, Y, Prm: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlGripGet       (iObj, iGrip: Integer; pX, pY: PDouble): Boolean; stdcall; external 'vecad52.dll';
Function vlGripSet       (iObj, iGrip: Integer; X,Y: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlGripMove      (iObj, iGrip: Integer; dx,dy: Double): Boolean; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// Access to objects properties
Function vlPropGet    (Key,iObj: Integer; pData: Pointer): Integer; stdcall; external 'vecad52.dll';
Function vlPropGetInt (Key,iObj: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlPropGetDbl (Key,iObj: Integer): Double; stdcall; external 'vecad52.dll';
Function vlPropPut    (Key,iObj: Integer; pData: Pointer): Integer; stdcall; external 'vecad52.dll';
Function vlPropPutInt (Key,iObj,Data: Integer): Integer; stdcall; external 'vecad52.dll';
Function vlPropPutDbl (Key,iObj: Integer; Data: Double): Integer; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// Zooming drawing in a window
Function vlZoom     (Scale: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlZoomRect (Left, Bottom, Right, Top: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlZoomPan  (dx, dy: Double): Boolean; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// Coordinates convertions
Function vlCoordWinToDwg  (Xwin,Ywin: Integer; pXdwg,pYdwg: PDouble):Boolean; stdcall; external 'vecad52.dll';
Function vlCoordDwgToWin  (X,Y: Double; pXwin,pYwin: PInteger):Boolean; stdcall; external 'vecad52.dll';
Function vlLenWinToDwg    (Lwin: Integer; pLdwg: PDouble):Boolean; stdcall; external 'vecad52.dll';
Function vlLenDwgToWin    (Ldwg: Double; pLwin: PInteger):Boolean; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// draw graphics primitives
Function vlSetDrawPen   (Width: Double; Color: COLORREF): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawPoint    (X,Y: Double; Ptype,Size: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawLine     (X1,Y1,X2,Y2: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawPolyline (Ver: PVLPOINT; Nver: Integer; bClosed: Boolean): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawPolygon  (Ver: PVLPOINT; Nver: Integer; bFill, bBorder: Boolean; FillColor: COLORREF): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawCircle   (X,Y,Rad: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawArc      (X,Y,Rad,Angle1,Angle2: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawEllipse  (X,Y,Rh,Rv,Angle: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawText     (X,Y: Double; szText: Pchar): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawBitmap   (hbm: HBITMAP; W, H: Integer; X, Y, ResX, ResY: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlDrawEntity   (Index: Integer; Xbase,Ybase,Xins,Yins,Angle,ScaleX,ScaleY: Double):Boolean; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// misc
Function vlExecute      (IdCmd: Integer): Boolean; stdcall; external 'vecad52.dll'; 
Function vlSetAccKey    (IdCmd, VirtKey,Flags: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlClear        (bSetDefLayout: Boolean): Boolean; stdcall; external 'vecad52.dll';
Function vlSetFocus     :Boolean; stdcall; external 'vecad52.dll';
Function vlUpdate       :Boolean; stdcall; external 'vecad52.dll';
Function vlRedraw       :Boolean; stdcall; external 'vecad52.dll';
Function vlReset        :Boolean; stdcall; external 'vecad52.dll';
Function vlPrintSetup   (hParent: HWND): Boolean; stdcall; external 'vecad52.dll';
Function vlPrint        (hPrintDC: HDC; Left,Bottom,Right,Top,ScaleX,ScaleY,OriginX,OriginY: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlDoRaster     (FileName: Pchar; Left, Bottom, Right, Top, Res: Double): Boolean; stdcall; external 'vecad52.dll';
Function vlGetWinSize   (hWnd: HWND; pWidth, pHeight: PInteger): Boolean; stdcall; external 'vecad52.dll';
Function vlSetTimer     (ID, Elapse: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlKillTimer    (ID: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlGetArea      (X, Y: Double): Double; stdcall; external 'vecad52.dll';

/////////////////////////////////////////////////
// Additional VeCAD controls

// Toolbar
Function vlToolBarCreate   (hwParent: HWND; Id,X,Y,W,H: Integer; pW,pH: PInteger):HWND; stdcall; external 'vecad52.dll';
Function vlToolBarButton   (Id: Integer):Boolean; stdcall; external 'vecad52.dll';
// Statusbar
Function vlStatBarCreate   (hwParent: HWND; pH: PInteger):HWND; stdcall; external 'vecad52.dll';
Function vlStatBarResize   :Boolean; stdcall; external 'vecad52.dll';
Function vlStatBarSetText  (iPart: Integer; szText :Pchar):Boolean; stdcall; external 'vecad52.dll';
// Progress indicator
Function vlIndicCreate   (parent:HWND; szTitle: Pchar):Boolean; stdcall; external 'vecad52.dll';
Function vlIndicDestroy  :Boolean; stdcall; external 'vecad52.dll';
Function vlIndicSetRange (nFrom,nTo: Integer):Boolean; stdcall; external 'vecad52.dll';
Function vlIndicSetPos   (iPos: Integer):Boolean; stdcall; external 'vecad52.dll';
Function vlIndicSetText  (szText: Pchar):Boolean; stdcall; external 'vecad52.dll';
Function vlIndicStep     :Boolean; stdcall; external 'vecad52.dll';
// "Navigator" window
Function vlNavCreate  (hWndParent, hVecWnd: HWND; Style, X, Y, W, H: Integer): HWND; stdcall; external 'vecad52.dll';
Function vlNavResize  (X, Y, W, H: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlNavUpdate  :Boolean; stdcall; external 'vecad52.dll';
Function vlNavGetProp (Prop: PVLNAVIGATOR): Boolean; stdcall; external 'vecad52.dll';
Function vlNavPutProp (Prop: PVLNAVIGATOR): Boolean; stdcall; external 'vecad52.dll';
// "Layers Manager" window
Function vlLayWinCreate  (hWndParent: HWND; Style, X, Y, W, H: Integer): HWND; stdcall; external 'vecad52.dll';
Function vlLayWinResize  (X, Y, W, H: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlLayWinGetProp (Prop: PVLLAYWIN): Boolean; stdcall; external 'vecad52.dll';
Function vlLayWinPutProp (Prop: PVLLAYWIN): Boolean; stdcall; external 'vecad52.dll';
// Set order of entities
Function vlEntSwap       (iEnt1, iEnt2: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlEntToTop      (iEnt: Integer): Boolean; stdcall; external 'vecad52.dll';
Function vlEntToBottom   (iEnt: Integer): Boolean; stdcall; external 'vecad52.dll';


implementation
end.




