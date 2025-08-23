// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TB97.pas' rev: 5.00

#ifndef TB97HPP
#define TB97HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tb97
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TDockBoundLinesValues { blTop, blBottom, blLeft, blRight };
#pragma option pop

typedef Set<TDockBoundLinesValues, blTop, blRight>  TDockBoundLines;

#pragma option push -b-
enum TDockPosition { dpTop, dpBottom, dpLeft, dpRight };
#pragma option pop

#pragma option push -b-
enum TDockType { dtNotDocked, dtTopBottom, dtLeftRight };
#pragma option pop

class DELPHICLASS TToolbar97;
typedef void __fastcall (__closure *TInsertRemoveEvent)(System::TObject* Sender, bool Inserting, TToolbar97* 
	Bar);

class DELPHICLASS TDock97;
class PASCALIMPLEMENTATION TDock97 : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	TDockPosition FPosition;
	bool FAllowDrag;
	TDockBoundLines FBoundLines;
	Graphics::TBitmap* FBkg;
	Graphics::TBitmap* FBkgCache;
	bool FBkgTransparent;
	bool FFixAlign;
	bool FLimitToOneRow;
	TInsertRemoveEvent FOnInsertRemoveBar;
	Classes::TNotifyEvent FOnResize;
	int DisableArrangeToolbars;
	Classes::TList* DockList;
	Classes::TList* RowInfo;
	void __fastcall SetAllowDrag(bool Value);
	void __fastcall SetBackground(Graphics::TBitmap* Value);
	void __fastcall SetBackgroundTransparent(bool Value);
	void __fastcall SetBoundLines(TDockBoundLines Value);
	void __fastcall SetFixAlign(bool Value);
	void __fastcall SetPosition(TDockPosition Value);
	int __fastcall GetToolbarCount(void);
	TToolbar97* __fastcall GetToolbars(int Index);
	void __fastcall FreeRowInfo(void);
	int __fastcall GetRowOf(const int Y, bool &Before);
	int __fastcall GetDesignModeRowOf(const int Y);
	int __fastcall GetHighestRow(void);
	void __fastcall RemoveBlankRows(void);
	void __fastcall InsertRowBefore(const int BeforeRow);
	void __fastcall BuildRowInfo(void);
	void __fastcall ChangeDockList(const bool Insert, const TToolbar97* Bar, const bool IsVisible);
	void __fastcall ChangeWidthHeight(const bool IsClientWidthAndHeight, int NewWidth, int NewHeight);
	void __fastcall ArrangeToolbars(void);
	void __fastcall DrawBackground(const Graphics::TCanvas* Canvas, const Windows::TRect &ClippingRect, 
		const Windows::TRect &DrawRect);
	void __fastcall InvalidateBackgrounds(void);
	void __fastcall BackgroundChanged(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CMSysColorChange(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMMove(Messages::TWMMove &Message);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall WMNCCalcSize(Messages::TWMNCCalcSize &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall AlignControls(Controls::TControl* AControl, Windows::TRect &Rect);
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall SetParent(Controls::TWinControl* AParent);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall VisibleChanging(void);
	
public:
	__fastcall virtual TDock97(Classes::TComponent* AOwner);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	__fastcall virtual ~TDock97(void);
	__property int ToolbarCount = {read=GetToolbarCount, nodefault};
	__property TToolbar97* Toolbars[int Index] = {read=GetToolbars};
	
__published:
	__property bool AllowDrag = {read=FAllowDrag, write=SetAllowDrag, default=1};
	__property Graphics::TBitmap* Background = {read=FBkg, write=SetBackground};
	__property bool BackgroundTransparent = {read=FBkgTransparent, write=SetBackgroundTransparent, default=0
		};
	__property TDockBoundLines BoundLines = {read=FBoundLines, write=SetBoundLines, default=0};
	__property Color ;
	__property bool FixAlign = {read=FFixAlign, write=SetFixAlign, default=0};
	__property bool LimitToOneRow = {read=FLimitToOneRow, write=FLimitToOneRow, default=0};
	__property PopupMenu ;
	__property TDockPosition Position = {read=FPosition, write=SetPosition, default=0};
	__property TInsertRemoveEvent OnInsertRemoveBar = {read=FOnInsertRemoveBar, write=FOnInsertRemoveBar
		};
	__property Classes::TNotifyEvent OnResize = {read=FOnResize, write=FOnResize};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDock97(HWND ParentWindow) : Controls::TCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TToolbar97 : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	int FBarHeight;
	int FBarWidth;
	int FDockedTotalBarHeight;
	int FDockedTotalBarWidth;
	int FDockPos;
	int FDockRow;
	TDock97* FDefaultDock;
	Classes::TNotifyEvent FOnRecreating;
	Classes::TNotifyEvent FOnRecreated;
	Classes::TNotifyEvent FOnDockChanging;
	Classes::TNotifyEvent FOnDockChanged;
	Classes::TNotifyEvent FOnClose;
	bool FCanDockLeftRight;
	bool FCloseButton;
	Windows::TRect FFloatingRect;
	int FFloatingRightX;
	Classes::TList* SlaveInfo;
	Classes::TList* GroupInfo;
	Classes::TList* LineSeps;
	Classes::TList* OrderList;
	int UpdatingBounds;
	int DisableArrangeControls;
	int Hidden;
	Controls::TWinControl* FloatParent;
	Forms::TForm* MDIParentForm;
	bool NotOnScreen;
	int VirtualLeft;
	bool CloseButtonDown;
	void *OldFormWindowProc;
	void *OldChildFormWindowProc;
	void __fastcall SetCloseButton(bool Value);
	void __fastcall SetDefaultDock(TDock97* Value);
	TDock97* __fastcall GetDockedTo(void);
	void __fastcall SetDockedTo(TDock97* Value);
	void __fastcall SetDockPos(int Value);
	void __fastcall SetDockRow(int Value);
	int __fastcall GetOrderIndex(Controls::TControl* Control);
	void __fastcall SetOrderIndex(Controls::TControl* Control, int Value);
	void __fastcall FreeGroupInfo(const Classes::TList* List);
	void __fastcall BuildGroupInfo(const Classes::TList* List, const bool TranslateSlave, const TDockType 
		OldDockType, const TDockType NewDockType);
	void __fastcall MoveOnScreen(const bool OnlyIfFullyOffscreen);
	void __fastcall ShouldBeVisible(const Controls::TControl* Control, const TDockType DockType, const 
		bool SetIt, bool &AVisible);
	void __fastcall AutoArrangeControls(void);
	void __fastcall ArrangeControls(const bool CanMove, const bool CanResize, const TDockType OldDockType
		, const TDock97* DockingTo, int RightX, const Windows::PPoint NewClientSize);
	void __fastcall DrawDraggingOutline(const HDC DC, const Windows::PRect NewRect, const Windows::PRect 
		OldRect, const bool NewDocking, const bool OldDocking);
	void __fastcall NewFormWindowProc(Messages::TMessage &Message);
	void __fastcall NewChildFormWindowProc(Messages::TMessage &Message);
	bool __fastcall NewMainWindowHook(Messages::TMessage &Message);
	void __fastcall BeginMoving(const int InitX, const int InitY);
	void __fastcall BeginSizing(const int HitTestValue);
	void __fastcall DrawNCArea(const HRGN Clip, const bool RedrawBorder, const bool RedrawCaption, const 
		bool RedrawCloseButton);
	void __fastcall SetNotOnScreen(const bool Value);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMVisibleChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMControlListChange(Controls::TCMControlListChange &Message);
	HIDESBASE MESSAGE void __fastcall WMMove(Messages::TWMMove &Message);
	MESSAGE void __fastcall WMActivate(Messages::TWMActivate &Message);
	MESSAGE void __fastcall WMMouseActivate(Messages::TWMMouseActivate &Message);
	MESSAGE void __fastcall WMGetMinMaxInfo(Messages::TWMGetMinMaxInfo &Message);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Messages::TWMNCHitTest &Message);
	HIDESBASE MESSAGE void __fastcall WMNCLButtonDown(Messages::TWMNCHitMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMNCCalcSize(Messages::TWMNCCalcSize &Message);
	
protected:
	Windows::TRect __fastcall GetVirtualBoundsRect();
	void __fastcall SetVirtualBounds(int ALeft, int ATop, int AWidth, int AHeight);
	void __fastcall SetVirtualBoundsRect(const Windows::TRect &R);
	virtual void __fastcall AlignControls(Controls::TControl* AControl, Windows::TRect &Rect);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	virtual void __fastcall Paint(void);
	virtual void __fastcall SetParent(Controls::TWinControl* AParent);
	
public:
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	__property Windows::TRect FloatingRect = {read=FFloatingRect, write=FFloatingRect};
	__property int OrderIndex[Controls::TControl* Control] = {read=GetOrderIndex, write=SetOrderIndex};
		
	__fastcall virtual TToolbar97(Classes::TComponent* AOwner);
	__fastcall virtual ~TToolbar97(void);
	void __fastcall SetSlaveControl(const Controls::TControl* ATopBottom, const Controls::TControl* ALeftRight
		);
	
__published:
	__property bool CanDockLeftRight = {read=FCanDockLeftRight, write=FCanDockLeftRight, default=1};
	__property Caption ;
	__property Color ;
	__property bool CloseButton = {read=FCloseButton, write=SetCloseButton, default=1};
	__property TDock97* DefaultDock = {read=FDefaultDock, write=SetDefaultDock};
	__property TDock97* DockedTo = {read=GetDockedTo, write=SetDockedTo};
	__property int DockRow = {read=FDockRow, write=SetDockRow, default=0};
	__property int DockPos = {read=FDockPos, write=SetDockPos, default=-1};
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible ;
	__property Classes::TNotifyEvent OnClose = {read=FOnClose, write=FOnClose};
	__property Classes::TNotifyEvent OnRecreated = {read=FOnRecreated, write=FOnRecreated};
	__property Classes::TNotifyEvent OnRecreating = {read=FOnRecreating, write=FOnRecreating};
	__property Classes::TNotifyEvent OnDockChanged = {read=FOnDockChanged, write=FOnDockChanged};
	__property Classes::TNotifyEvent OnDockChanging = {read=FOnDockChanging, write=FOnDockChanging};
public:
		
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TToolbar97(HWND ParentWindow) : Controls::TCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


typedef int TToolbarSepSize;

class DELPHICLASS TToolbarSep97;
class PASCALIMPLEMENTATION TToolbarSep97 : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	bool FBlank;
	TToolbarSepSize FSizeHorz;
	TToolbarSepSize FSizeVert;
	void __fastcall SetBlank(bool Value);
	void __fastcall SetSizeHorz(TToolbarSepSize Value);
	void __fastcall SetSizeVert(TToolbarSepSize Value);
	
protected:
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	virtual void __fastcall Paint(void);
	virtual void __fastcall SetParent(Controls::TWinControl* AParent);
	
public:
	__fastcall virtual TToolbarSep97(Classes::TComponent* AOwner);
	
__published:
	__property bool Blank = {read=FBlank, write=SetBlank, default=0};
	__property TToolbarSepSize SizeHorz = {read=FSizeHorz, write=SetSizeHorz, default=6};
	__property TToolbarSepSize SizeVert = {read=FSizeVert, write=SetSizeVert, default=6};
public:
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TToolbarSep97(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TButtonDisplayMode { dmBoth, dmGlyphOnly, dmTextOnly };
#pragma option pop

#pragma option push -b-
enum TButtonState97 { bsUp, bsDisabled, bsDown, bsExclusive, bsMouseIn };
#pragma option pop

typedef Shortint TNumGlyphs97;

class DELPHICLASS TToolbarButton97;
class PASCALIMPLEMENTATION TToolbarButton97 : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	bool FAllowAllUp;
	TButtonDisplayMode FDisplayMode;
	bool FDown;
	bool FDropdownArrow;
	bool FDropdownCombo;
	Menus::TPopupMenu* FDropdownMenu;
	bool FFlat;
	void *FGlyph;
	int FGroupIndex;
	Buttons::TButtonLayout FLayout;
	int FMargin;
	bool FOldDisabledStyle;
	bool FOpaque;
	int FSpacing;
	bool FWordWrap;
	Classes::TNotifyEvent FOnMouseEnter;
	Classes::TNotifyEvent FOnMouseExit;
	bool FInClick;
	bool FMouseInControl;
	bool FMouseIsDown;
	bool FMenuIsDown;
	void __fastcall GlyphChanged(System::TObject* Sender);
	void __fastcall UpdateExclusive(void);
	void __fastcall SetAllowAllUp(bool Value);
	void __fastcall SetDown(bool Value);
	void __fastcall SetDisplayMode(TButtonDisplayMode Value);
	void __fastcall SetDropdownArrow(bool Value);
	void __fastcall SetDropdownCombo(bool Value);
	void __fastcall SetDropdownMenu(Menus::TPopupMenu* Value);
	void __fastcall SetFlat(bool Value);
	Graphics::TBitmap* __fastcall GetGlyph(void);
	void __fastcall SetGlyph(Graphics::TBitmap* Value);
	void __fastcall SetGroupIndex(int Value);
	void __fastcall SetLayout(Buttons::TButtonLayout Value);
	void __fastcall SetMargin(int Value);
	TNumGlyphs97 __fastcall GetNumGlyphs(void);
	void __fastcall SetNumGlyphs(TNumGlyphs97 Value);
	void __fastcall SetOldDisabledStyle(bool Value);
	void __fastcall SetOpaque(bool Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetWordWrap(bool Value);
	void __fastcall UpdateTracking(void);
	void __fastcall Redraw(const bool Erase);
	void __fastcall MouseEntered(void);
	void __fastcall MouseLeft(void);
	void __fastcall ButtonMouseTimerHandler(System::TObject* Sender);
	/*         class method */ static bool __fastcall DeactivateHook(TMetaClass* vmt, Messages::TMessage 
		&Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDblClk(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	MESSAGE void __fastcall CMButtonPressed(Messages::TMessage &Message);
	MESSAGE void __fastcall CMDialogChar(Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	MESSAGE void __fastcall CMTextChanged(Messages::TMessage &Message);
	MESSAGE void __fastcall CMSysColorChange(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	
protected:
	TButtonState97 FState;
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, 
		int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int 
		Y);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TToolbarButton97(Classes::TComponent* AOwner);
	__fastcall virtual ~TToolbarButton97(void);
	DYNAMIC void __fastcall Click(void);
	
__published:
	__property bool AllowAllUp = {read=FAllowAllUp, write=SetAllowAllUp, default=0};
	__property int GroupIndex = {read=FGroupIndex, write=SetGroupIndex, default=0};
	__property TButtonDisplayMode DisplayMode = {read=FDisplayMode, write=SetDisplayMode, default=0};
	__property bool Down = {read=FDown, write=SetDown, default=0};
	__property bool DropdownArrow = {read=FDropdownArrow, write=SetDropdownArrow, default=1};
	__property bool DropdownCombo = {read=FDropdownCombo, write=SetDropdownCombo, default=0};
	__property Menus::TPopupMenu* DropdownMenu = {read=FDropdownMenu, write=SetDropdownMenu};
	__property Caption ;
	__property Enabled ;
	__property bool Flat = {read=FFlat, write=SetFlat, default=1};
	__property Font ;
	__property Graphics::TBitmap* Glyph = {read=GetGlyph, write=SetGlyph};
	__property Buttons::TButtonLayout Layout = {read=FLayout, write=SetLayout, default=0};
	__property int Margin = {read=FMargin, write=SetMargin, default=-1};
	__property TNumGlyphs97 NumGlyphs = {read=GetNumGlyphs, write=SetNumGlyphs, default=1};
	__property bool OldDisabledStyle = {read=FOldDisabledStyle, write=SetOldDisabledStyle, default=0};
	__property bool Opaque = {read=FOpaque, write=SetOpaque, default=1};
	__property ParentFont ;
	__property ParentShowHint ;
	__property ShowHint ;
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=4};
	__property Visible ;
	__property bool WordWrap = {read=FWordWrap, write=SetWordWrap, default=0};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseDown ;
	__property Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseExit = {read=FOnMouseExit, write=FOnMouseExit};
	__property OnMouseMove ;
	__property OnMouseUp ;
};


class DELPHICLASS TEdit97;
class PASCALIMPLEMENTATION TEdit97 : public Stdctrls::TCustomEdit 
{
	typedef Stdctrls::TCustomEdit inherited;
	
private:
	bool MouseInControl;
	void __fastcall RedrawBorder(const HRGN Clip);
	void __fastcall NewAdjustHeight(void);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Messages::TWMKillFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMNCCalcSize(Messages::TWMNCCalcSize &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TEdit97(Classes::TComponent* AOwner);
	
__published:
	__property CharCase ;
	__property DragCursor ;
	__property DragMode ;
	__property Enabled ;
	__property Font ;
	__property HideSelection ;
	__property ImeMode ;
	__property ImeName ;
	__property MaxLength ;
	__property OEMConvert ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PasswordChar ;
	__property PopupMenu ;
	__property ReadOnly ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Text ;
	__property Visible ;
	__property OnChange ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TEdit97(HWND ParentWindow) : Stdctrls::TCustomEdit(
		ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TEdit97(void) { }
	#pragma option pop
	
};


typedef int __fastcall (*TPositionReadIntProc)(const AnsiString ToolbarName, const AnsiString Value, 
	const int Default, const void * ExtraData);

typedef AnsiString __fastcall (*TPositionReadStringProc)(const AnsiString ToolbarName, const AnsiString 
	Value, const AnsiString Default, const void * ExtraData);

typedef void __fastcall (*TPositionWriteIntProc)(const AnsiString ToolbarName, const AnsiString Value
	, const int Data, const void * ExtraData);

typedef void __fastcall (*TPositionWriteStringProc)(const AnsiString ToolbarName, const AnsiString Value
	, const AnsiString Data, const void * ExtraData);

//-- var, const, procedure ---------------------------------------------------
#define Toolbar97Version "1.52"
extern PACKAGE void __fastcall Register(void);
extern PACKAGE void __fastcall CustomLoadToolbarPositions(const Forms::TForm* Form, const TPositionReadIntProc 
	ReadIntProc, const TPositionReadStringProc ReadStringProc, const void * ExtraData);
extern PACKAGE void __fastcall CustomSaveToolbarPositions(const Forms::TForm* Form, const TPositionWriteIntProc 
	WriteIntProc, const TPositionWriteStringProc WriteStringProc, const void * ExtraData);
extern PACKAGE void __fastcall IniLoadToolbarPositions(const Forms::TForm* Form, const AnsiString Filename
	);
extern PACKAGE void __fastcall IniSaveToolbarPositions(const Forms::TForm* Form, const AnsiString Filename
	);
extern PACKAGE void __fastcall RegLoadToolbarPositions(const Forms::TForm* Form, const AnsiString BaseRegistryKey
	);
extern PACKAGE void __fastcall RegSaveToolbarPositions(const Forms::TForm* Form, const AnsiString BaseRegistryKey
	);

}	/* namespace Tb97 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Tb97;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TB97
