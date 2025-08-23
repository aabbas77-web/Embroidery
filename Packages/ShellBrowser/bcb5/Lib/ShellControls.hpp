// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ShellControls.pas' rev: 5.00

#ifndef ShellControlsHPP
#define ShellControlsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ImgList.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <ShellLink.hpp>	// Pascal unit
#include <Commctrl.hpp>	// Pascal unit
#include <ShlObj.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ShellBrowser.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------
typedef IDropTarget *_di_IDropTarget;

namespace Shellcontrols
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TJamShellOperation { sopCopy, sopMove, sopDrag, sopDrop, sopCut, sopPaste, sopDelete, sopRemove, 
	sopAdd, sopRename };
#pragma option pop

typedef Set<TJamShellOperation, sopCopy, sopRename>  TJamShellOperations;

typedef void __fastcall (__closure *TOnOperation)(System::TObject* Sender, TJamShellOperations Operation
	, Classes::TStrings* Files, AnsiString Destination);

class DELPHICLASS TJamComboItem;
class PASCALIMPLEMENTATION TJamComboItem : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	AnsiString Caption;
	AnsiString DisplayName;
	int Indent;
	int IconNumber;
	bool IsDrive;
	bool Persistent;
	_ITEMIDLIST *PIDL;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TJamComboItem(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TJamComboItem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TJamShellCombo;
class PASCALIMPLEMENTATION TJamShellCombo : public Stdctrls::TCustomComboBox 
{
	typedef Stdctrls::TCustomComboBox inherited;
	
private:
	bool FInitialized;
	bool FNotDrawingInComboboxEdit;
	Shelllink::TJamShellLink* FShellLink;
	Shellbrowser::TShellBrowser* FShellBrowser;
	Shellbrowser::TJamSystemImageList* FImageList;
	int fIndentPixels;
	HIDESBASE MESSAGE void __fastcall CNDrawItem(Messages::TWMDrawItem &Message);
	HIDESBASE MESSAGE void __fastcall WMRButtonDown(Messages::TWMMouse &Message);
	
protected:
	virtual void __fastcall Loaded(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation
		);
	void __fastcall DeleteNonPersistentFolders(int fromIndex);
	void __fastcall Delete(int Index);
	void __fastcall AddPathToCombo(AnsiString path);
	void __fastcall AddIdListToCombo(Shlobj::PItemIDList absIdList);
	void __fastcall JamSetItemIndex(int newValue);
	int __fastcall JamGetItemIndex(void);
	DYNAMIC void __fastcall Change(void);
	HIDESBASE MESSAGE void __fastcall CNCommand(Messages::TWMCommand &Message);
	void __fastcall AddToComboList(int aIndex, int aIndent);
	MESSAGE void __fastcall JAMPathChanged(Shelllink::TJAMPathChanged &Message);
	virtual void __fastcall DrawItem(int aIndex, const Windows::TRect &aRect, Windows::TOwnerDrawState 
		aState);
	virtual void __fastcall CreateWnd(void);
	void __fastcall SetShellLink(Shelllink::TJamShellLink* newValue);
	void __fastcall SetFileSystemOnly(bool aValue);
	bool __fastcall GetFileSystemOnly(void);
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(AnsiString s);
	
public:
	__fastcall virtual TJamShellCombo(Classes::TComponent* AOwner);
	__fastcall virtual ~TJamShellCombo(void);
	void __fastcall InsertItem(int aIndex, AnsiString aCaption, AnsiString aDisplayName, int aIconNumber
		, int aIndent, void * PIDL, bool Persistent);
	void __fastcall AddShellItem(AnsiString aCaption, AnsiString aDisplayName, int aIconNumber, int aIndent
		, void * PIDL, bool Persistent);
	void __fastcall AddFolder(AnsiString Path, int Indent, bool Persistent);
	__property Font ;
	
__published:
	__property ItemIndex  = {read=JamGetItemIndex, write=JamSetItemIndex};
	__property Shelllink::TJamShellLink* ShellLink = {read=FShellLink, write=SetShellLink};
	__property bool FileSystemOnly = {read=GetFileSystemOnly, write=SetFileSystemOnly, default=0};
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
	__property Align ;
	__property Color ;
	__property Ctl3D ;
	__property DragMode ;
	__property DragCursor ;
	__property DropDownCount ;
	__property Enabled ;
	__property ImeMode ;
	__property ImeName ;
	__property ItemHeight ;
	__property MaxLength ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PopupMenu ;
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
	__property OnDrawItem ;
	__property OnDropDown ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnStartDrag ;
	__property DragKind ;
	__property Anchors ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TJamShellCombo(HWND ParentWindow) : Stdctrls::TCustomComboBox(
		ParentWindow) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TOnAddItem)(Comctrls::TListItem* Item, bool &CanAdd);

class DELPHICLASS TJamShellListItem;
class PASCALIMPLEMENTATION TJamShellListItem : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	_ITEMIDLIST *RelativePIDL;
	void *Data;
	int Tag;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TJamShellListItem(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TJamShellListItem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TJamShellList;
class PASCALIMPLEMENTATION TJamShellList : public Comctrls::TCustomListView 
{
	typedef Comctrls::TCustomListView inherited;
	
private:
	bool FInitialized;
	Shellbrowser::TShellBrowser* fShellBrowser;
	Classes::TNotifyEvent fOnCreateColumns;
	TOnAddItem fOnAddItem;
	Classes::TNotifyEvent fOnPopulated;
	TOnOperation fOnOperation;
	Shelllink::TJamShellLink* FShellLink;
	int fColCount;
	bool fDetails;
	bool fShowFolders;
	bool fShowHidden;
	int fSortColumn;
	bool fReverseOrder;
	int ColumnWidth[256];
	bool FileSystemFolder;
	bool fContextMenu;
	bool fOleDragDrop;
	bool fIgnoreChanges;
	Classes::TStringList* fSelectedList;
	_di_IDataObject fDataObj;
	_di_IDropTarget fDropTarget;
	_di_IDropTarget fDropTarget2;
	Comctrls::TListItem* fDropItem;
	int fDragButton;
	int fDropButton;
	unsigned fLastAutoScroll;
	Extctrls::TTimer* fUpdateTimer;
	Menus::TPopupMenu* fBackgroundPopupMenu;
	int fNumShellColumns;
	HIDESBASE MESSAGE void __fastcall WMRButtonUp(Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMInitMenuPopup(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMMeasureItem(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMDrawItem(Messages::TMessage &Message);
	MESSAGE void __fastcall JAMPathChanged(Shelllink::TJAMPathChanged &Message);
	MESSAGE void __fastcall JAMSelectAll(Shelllink::TJAMPathChanged &Message);
	MESSAGE void __fastcall JAMRefresh(Shelllink::TJAMPathChanged &Message);
	MESSAGE void __fastcall JAMSmartRefresh(Shelllink::TJAMPathChanged &Message);
	MESSAGE void __fastcall JAMGoUp(Messages::TMessage &Message);
	int __fastcall IndexOfPIDL(Shlobj::PItemIDList pidl);
	void __fastcall HandleRenameEvent(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CNNotify(Messages::TWMNotify &Message);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation
		);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall DestroyWnd(void);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton aButton, Classes::TShiftState aShift, int 
		x, int y);
	DYNAMIC void __fastcall Change(Comctrls::TListItem* Item, int Change);
	void __fastcall PrepareMultiObjects(void);
	void __fastcall SetPath(AnsiString aPath);
	AnsiString __fastcall GetPath();
	void __fastcall AddShellItem(bool Details);
	DYNAMIC void __fastcall Delete(Comctrls::TListItem* Item);
	void __fastcall SetFileSystemOnly(bool aValue);
	bool __fastcall GetFileSystemOnly(void);
	void __fastcall SetFolderIdList(Shlobj::PItemIDList IdList);
	Shlobj::PItemIDList __fastcall GetFolderIdList(void);
	void __fastcall TimerChange(System::TObject* Sender);
	DYNAMIC bool __fastcall CanEdit(Comctrls::TListItem* Item);
	DYNAMIC void __fastcall Edit(const tagLVITEMA &Item);
	void __fastcall Operation(TJamShellOperations op, Classes::TStrings* files, AnsiString Destination)
		;
	DYNAMIC void __fastcall KeyDown(Word &key, Classes::TShiftState aShiftState);
	DYNAMIC void __fastcall KeyPress(char &key);
	DYNAMIC void __fastcall ColClick(Comctrls::TListColumn* Column);
	void __fastcall SetShellLink(Shelllink::TJamShellLink* newValue);
	void __fastcall SetDetails(bool aDetails);
	void __fastcall SetShowHidden(bool val);
	void __fastcall SetSortColumn(int col);
	void __fastcall SetReverseSortOrder(bool reverse);
	void __fastcall SetShowFolders(bool val);
	void __fastcall SetFilter(AnsiString Pattern);
	AnsiString __fastcall GetFilter();
	void __fastcall FileChange(System::TObject* Sender);
	void __fastcall SetSpecialFolder(Shellbrowser::TJamShellFolder folder);
	Shellbrowser::TJamShellFolder __fastcall GetSpecialFolder(void);
	void __fastcall SetOleDragDrop(bool val);
	void __fastcall BeginOleDrag(Controls::TMouseButton aButton);
	Classes::TStringList* __fastcall GetSelectedFiles(void);
	bool __fastcall ShowBackgroundMenu(const Windows::TPoint &p);
	Shellbrowser::TOnContextMenuSelectEvent __fastcall GetOnContextMenuSelect();
	void __fastcall SetOnContextMenuSelect(Shellbrowser::TOnContextMenuSelectEvent anEvent);
	void __fastcall SelectedListChange(System::TObject* Sender);
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(AnsiString s);
	HRESULT __stdcall DragEnter(const _di_IDataObject DataObj, int grfKeyState, const Windows::TPoint pt
		, int &dwEffect);
	HIDESBASE HRESULT __stdcall DragOver(int grfKeyState, const Windows::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragLeave(void);
	HRESULT __stdcall Drop(const _di_IDataObject dataObj, int grfKeyState, const Windows::TPoint pt, int 
		&dwEffect);
	virtual HRESULT __stdcall QueryContinueDrag(BOOL fEscapePressed, int grfKeyState);
	virtual HRESULT __stdcall GiveFeedback(int dwEffect);
	
public:
	__fastcall virtual TJamShellList(Classes::TComponent* AOwner);
	__fastcall virtual ~TJamShellList(void);
	HIDESBASE bool __fastcall Refresh(void);
	void __fastcall GoUp(void);
	bool __fastcall CreateDir(AnsiString Name, bool EditMode);
	bool __fastcall InvokeCommandOnSelected(AnsiString Command);
	bool __fastcall InvokeCommandOnFolder(AnsiString Command);
	AnsiString __fastcall ShowContextMenu(const Windows::TPoint &p);
	AnsiString __fastcall GetFullPath(Comctrls::TListItem* item);
	__property Shlobj::PItemIDList FolderIdList = {read=GetFolderIdList, write=SetFolderIdList};
	__property int SortColumn = {read=fSortColumn, write=SetSortColumn, nodefault};
	__property bool ReverseSortOrder = {read=fReverseOrder, write=SetReverseSortOrder, nodefault};
	__property Classes::TStringList* SelectedFiles = {read=GetSelectedFiles};
	__property Items ;
	void __fastcall SmartRefresh(void);
	__property Font ;
	__property Columns ;
	__property SmallImages ;
	__property LargeImages ;
	void __fastcall SelectAll(void);
	
__published:
	__property bool Details = {read=fDetails, write=SetDetails, default=1};
	__property bool ShowHidden = {read=fShowHidden, write=SetShowHidden, default=1};
	__property bool FileSystemOnly = {read=GetFileSystemOnly, write=SetFileSystemOnly, default=0};
	__property AnsiString Filter = {read=GetFilter, write=SetFilter};
	__property AnsiString Path = {read=GetPath, write=SetPath};
	__property Shellbrowser::TJamShellFolder SpecialFolder = {read=GetSpecialFolder, write=SetSpecialFolder
		, nodefault};
	__property Shelllink::TJamShellLink* ShellLink = {read=FShellLink, write=SetShellLink};
	__property bool OleDragDrop = {read=fOleDragDrop, write=SetOleDragDrop, nodefault};
	__property bool ShellContextMenu = {read=fContextMenu, write=fContextMenu, nodefault};
	__property Menus::TPopupMenu* BackgroundPopupMenu = {read=fBackgroundPopupMenu, write=fBackgroundPopupMenu
		};
	__property bool ShowFolders = {read=fShowFolders, write=SetShowFolders, default=1};
	__property TOnAddItem OnAddItem = {read=fOnAddItem, write=fOnAddItem};
	__property Classes::TNotifyEvent OnPopulated = {read=fOnPopulated, write=fOnPopulated};
	__property Classes::TNotifyEvent OnCreateColumns = {read=fOnCreateColumns, write=fOnCreateColumns};
		
	__property TOnOperation OnOperation = {read=fOnOperation, write=fOnOperation};
	__property Shellbrowser::TOnContextMenuSelectEvent OnContextMenuSelect = {read=GetOnContextMenuSelect
		, write=SetOnContextMenuSelect};
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
	__property Align ;
	__property BorderStyle ;
	__property Checkboxes ;
	__property HideSelection ;
	__property Color ;
	__property Ctl3D ;
	__property DragMode ;
	__property DragCursor ;
	__property Enabled ;
	__property Hint ;
	__property ImeMode ;
	__property ImeName ;
	__property IconOptions ;
	__property MultiSelect ;
	__property ParentColor ;
	__property ParentFont ;
	__property ParentCtl3D ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property ReadOnly ;
	__property RowSelect ;
	__property ShowHint ;
	__property ShowColumnHeaders ;
	__property StateImages ;
	__property TabOrder ;
	__property TabStop ;
	__property ViewStyle ;
	__property Visible ;
	__property OnChange ;
	__property OnClick ;
	__property OnColumnClick ;
	__property OnDblClick ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnEnter ;
	__property OnExit ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property OnMouseMove ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnStartDrag ;
	__property OnEndDrag ;
	__property OnDeletion ;
	__property OnEdited ;
	__property Anchors ;
	__property DragKind ;
	__property HotTrack ;
	__property OnCustomDraw ;
	__property OnCustomDrawItem ;
	__property OnSelectItem ;
	__property OnResize ;
	__property OnStartDock ;
	__property OnEndDock ;
	__property OnChanging ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TJamShellList(HWND ParentWindow) : Comctrls::TCustomListView(
		ParentWindow) { }
	#pragma option pop
	
private:
	void *__IDropTarget;	/* IDropTarget */
	void *__IDropSource;	/* IDropSource */
	
public:
	operator IDropSource*(void) { return (IDropSource*)&__IDropSource; }
	operator IDropTarget*(void) { return (IDropTarget*)&__IDropTarget; }
	
};


class DELPHICLASS TJamShellTreeItem;
class PASCALIMPLEMENTATION TJamShellTreeItem : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	void *RelativePIDL;
	void *AbsolutePIDL;
	int Tag;
	void *Data;
	_di_IShellFolder ParentShellFolder;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TJamShellTreeItem(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TJamShellTreeItem(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TOnAddNode)(Comctrls::TTreeNode* Node, AnsiString Path, bool &CanAdd
	);

class DELPHICLASS TJamShellTree;
class PASCALIMPLEMENTATION TJamShellTree : public Comctrls::TCustomTreeView 
{
	typedef Comctrls::TCustomTreeView inherited;
	
private:
	bool fInitialized;
	bool fAllowExpand;
	Shellbrowser::TShellBrowser* fShellBrowser;
	Shelllink::TJamShellLink* fShellLink;
	Shellbrowser::TJamShellFolder fRootedAt;
	TOnAddNode fOnAddFolder;
	TOnOperation fOnOperation;
	Extctrls::TTimer* fChangeTimer;
	bool fQuickSelect;
	bool fIsExpanding;
	AnsiString fRootedAtFileSystemFolder;
	bool fOleDragDrop;
	_di_IDataObject fDataObj;
	bool fContextMenu;
	bool fShowHidden;
	bool fShowFiles;
	bool fShowNetHood;
	_di_IDropTarget fDropTarget2;
	Comctrls::TTreeNode* fDropItem;
	Comctrls::TTreeNode* fDragNode;
	int fDragButton;
	int fDropButton;
	int fOldDragEffect;
	unsigned fLastAutoScroll;
	unsigned fAutoExpand;
	HIDESBASE MESSAGE void __fastcall WMRButtonUp(Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMInitMenuPopup(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMMeasureItem(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMDrawItem(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CNNotify(Messages::TWMNotify &Message);
	MESSAGE void __fastcall JAMRefresh(Shelllink::TJAMPathChanged &Message);
	MESSAGE void __fastcall JAMSmartRefresh(Shelllink::TJAMPathChanged &Message);
	MESSAGE void __fastcall JAMGoUp(Messages::TMessage &Message);
	void __fastcall AddItem(Comctrls::TTreeNode* Parent);
	void __fastcall HandleRenameEvent(System::TObject* Sender);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation operation
		);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DestroyWnd(void);
	void __fastcall TimerChange(System::TObject* Sender);
	DYNAMIC bool __fastcall CanExpand(Comctrls::TTreeNode* aNode);
	DYNAMIC void __fastcall Expand(Comctrls::TTreeNode* aNode);
	DYNAMIC void __fastcall Delete(Comctrls::TTreeNode* aNode);
	void __fastcall SetJAMShellLink(Shelllink::TJamShellLink* newValue);
	void __fastcall SetRootedAt(Shellbrowser::TJamShellFolder Root);
	DYNAMIC void __fastcall Change(Comctrls::TTreeNode* Node);
	MESSAGE void __fastcall JAMPathChanged(Shelllink::TJAMPathChanged &Message);
	bool __fastcall GotoFolderIdList(const Shlobj::PItemIDList ItemIdList);
	AnsiString __fastcall GetSelectedFolder();
	void __fastcall SetSelectedFolder(AnsiString aPath);
	DYNAMIC bool __fastcall CanEdit(Comctrls::TTreeNode* Node);
	DYNAMIC void __fastcall Edit(const tagTVITEMA &Item);
	void __fastcall Operation(TJamShellOperations op, Classes::TStrings* Folders, AnsiString Destination
		);
	DYNAMIC void __fastcall KeyDown(Word &key, Classes::TShiftState aShiftState);
	DYNAMIC void __fastcall KeyPress(char &key);
	void __fastcall SetSpecialFolder(Shellbrowser::TJamShellFolder folder);
	Shellbrowser::TJamShellFolder __fastcall GetSpecialFolder(void);
	void __fastcall SetRootedAtFileSystemFolder(AnsiString aPath);
	void __fastcall SetShowHidden(bool aValue);
	void __fastcall SetShowNetHood(bool aValue);
	void __fastcall SetShowFiles(bool aValue);
	void __fastcall SetFileSystemOnly(bool aValue);
	bool __fastcall GetFileSystemOnly(void);
	Shellbrowser::TOnContextMenuSelectEvent __fastcall GetOnContextMenuSelect();
	void __fastcall SetOnContextMenuSelect(Shellbrowser::TOnContextMenuSelectEvent anEvent);
	void __fastcall SetFilter(AnsiString Pattern);
	AnsiString __fastcall GetFilter();
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(AnsiString s);
	void __fastcall SetOleDragDrop(bool val);
	void __fastcall BeginOleDrag(Controls::TMouseButton aButton);
	HRESULT __stdcall DragEnter(const _di_IDataObject DataObj, int grfKeyState, const Windows::TPoint pt
		, int &dwEffect);
	HIDESBASE HRESULT __stdcall DragOver(int grfKeyState, const Windows::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragLeave(void);
	HRESULT __stdcall Drop(const _di_IDataObject dataObj, int grfKeyState, const Windows::TPoint pt, int 
		&dwEffect);
	virtual HRESULT __stdcall QueryContinueDrag(BOOL fEscapePressed, int grfKeyState);
	virtual HRESULT __stdcall GiveFeedback(int dwEffect);
	
public:
	__fastcall virtual TJamShellTree(Classes::TComponent* AOwner);
	__fastcall virtual ~TJamShellTree(void);
	bool __fastcall InvokeCommandOnSelected(AnsiString Command);
	void __fastcall GoUp(void);
	HIDESBASE void __fastcall Refresh(void);
	void __fastcall SmartRefresh(void);
	AnsiString __fastcall GetFullPath(Comctrls::TTreeNode* node);
	void __fastcall CreateDir(AnsiString path, AnsiString foldername, bool editmode);
	void __fastcall RefreshNode(Comctrls::TTreeNode* Node, bool Recursive);
	AnsiString __fastcall ShowContextMenu(const Windows::TPoint &p);
	bool __fastcall ShowNetConnectionDialog(void);
	__property Items ;
	__property Images ;
	__property Font ;
	
__published:
	__property Shelllink::TJamShellLink* ShellLink = {read=fShellLink, write=SetJAMShellLink};
	__property Shellbrowser::TJamShellFolder RootedAt = {read=fRootedAt, write=SetRootedAt, nodefault};
		
	__property AnsiString RootedAtFileSystemFolder = {read=fRootedAtFileSystemFolder, write=SetRootedAtFileSystemFolder
		};
	__property AnsiString SelectedFolder = {read=GetSelectedFolder, write=SetSelectedFolder};
	__property Shellbrowser::TJamShellFolder SpecialFolder = {read=GetSpecialFolder, write=SetSpecialFolder
		, nodefault};
	__property bool OleDragDrop = {read=fOleDragDrop, write=SetOleDragDrop, nodefault};
	__property bool ShellContextMenu = {read=fContextMenu, write=fContextMenu, nodefault};
	__property bool ShowHidden = {read=fShowHidden, write=SetShowHidden, default=1};
	__property bool ShowNetHood = {read=fShowNetHood, write=SetShowNetHood, default=1};
	__property bool FileSystemOnly = {read=GetFileSystemOnly, write=SetFileSystemOnly, default=0};
	__property bool ShowFiles = {read=fShowFiles, write=SetShowFiles, nodefault};
	__property AnsiString Filter = {read=GetFilter, write=SetFilter};
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
	__property TOnAddNode OnAddFolder = {read=fOnAddFolder, write=fOnAddFolder};
	__property TOnOperation OnOperation = {read=fOnOperation, write=fOnOperation};
	__property Shellbrowser::TOnContextMenuSelectEvent OnContextMenuSelect = {read=GetOnContextMenuSelect
		, write=SetOnContextMenuSelect};
	__property ShowButtons ;
	__property BorderStyle ;
	__property DragCursor ;
	__property ShowLines ;
	__property ShowRoot ;
	__property ReadOnly ;
	__property DragMode ;
	__property HideSelection ;
	__property Indent ;
	__property OnEditing ;
	__property OnEdited ;
	__property OnExpanding ;
	__property OnExpanded ;
	__property OnCollapsing ;
	__property OnCompare ;
	__property OnCollapsed ;
	__property OnChanging ;
	__property OnChange ;
	__property OnDeletion ;
	__property OnGetImageIndex ;
	__property OnGetSelectedIndex ;
	__property Align ;
	__property Enabled ;
	__property Color ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property Ctl3D ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnEnter ;
	__property OnExit ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnStartDrag ;
	__property OnEndDrag ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnDblClick ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property PopupMenu ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property ShowHint ;
	__property StateImages ;
	__property DragKind ;
	__property Anchors ;
	__property HotTrack ;
	__property OnStartDock ;
	__property OnEndDock ;
	__property OnCustomDraw ;
	__property OnCustomDrawItem ;
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TJamShellTree(HWND ParentWindow) : Comctrls::TCustomTreeView(
		ParentWindow) { }
	#pragma option pop
	
private:
	void *__IDropTarget;	/* IDropTarget */
	void *__IDropSource;	/* IDropSource */
	
public:
	operator IDropSource*(void) { return (IDropSource*)&__IDropSource; }
	operator IDropTarget*(void) { return (IDropTarget*)&__IDropTarget; }
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE unsigned AUTOSCROLL_DELAY_MS;
extern PACKAGE int AUTOSCROLL_THRESHOLD_X;
extern PACKAGE int AUTOSCROLL_THRESHOLD_Y;
extern PACKAGE unsigned AUTOEXPAND_DELAY_MS;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Shellcontrols */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Shellcontrols;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ShellControls
