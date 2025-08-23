unit G32_ColnEdit;

interface

{$I G32.inc}

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, DsgnIntf, ToolIntf, ExptIntf, G32_Collections, ExtCtrls,
  ImgList, Buttons;

const
  AM_DEFER_UPDATE = WM_USER + 101;

type
  TG32CollectionEditor = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    AvailableList: TListView;
    Panel3: TPanel;
    Panel4: TPanel;
    AllocatedList: TListView;
    Splitter1: TSplitter;
    ImageList1: TImageList;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    Panel5: TPanel;
    procedure AvailableListDblClick(Sender: TObject);
    procedure AllocatedListChange(Sender: TObject; Item: TListItem;
      Change: TItemChange);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    procedure AMDeferUpdate(var Msg: TMessage); message AM_DEFER_UPDATE;
  protected
    CurrentDesigner: IFormDesigner;
    CurrentCollection: TG32Collection;
    CurrentComponent: TComponent;
    ItemIDList: TList;
    SelectionError: Boolean;
    StateLock: Integer;
    procedure FormModified;
    procedure ReadAvailableItems;
    procedure SelectAll(DoUpdate: Boolean = True);
    procedure SelectNone(DoUpdate: Boolean = True);
    procedure UpdateAllocatedItems;
  public
    procedure Add(AvailableIndex: Integer);
    procedure GetSelection;
    procedure LockState;
    procedure ReadCollection;
    procedure Reset;
    procedure SetCollection(Collection: TG32Collection; Designer: IFormDesigner;
      Component: TComponent; const PropertyName: string);
    procedure SetSelection;
    procedure UnlockState;
  end;

  TG32CollectionEditorClass = class of TG32CollectionEditor;

  TG32CollectionProperty = class(TClassProperty)
  public
    procedure Edit; override;
    function GetAttributes: TPropertyAttributes; override;
  end;

var
  G32CollectionEditor: TG32CollectionEditor;

implementation

{$R *.DFM}

uses
  LibIntf, Registry, TypInfo;

type
  TPersistentAccess = class(TPersistent);

{ TG32CollectionEditor }

procedure TG32CollectionEditor.ReadCollection;
begin
  ReadAvailableItems;
  UpdateAllocatedItems;
end;

procedure TG32CollectionEditor.SetCollection(Collection: TG32Collection;
  Designer: IFormDesigner; Component: TComponent; const PropertyName: string);
begin
  Reset;
  CurrentCollection := Collection;
  CurrentComponent := Component;
  CurrentDesigner := Designer;
  if Assigned(CurrentCollection) and Assigned(CurrentComponent) then
  begin
    ReadCollection;
    Caption := Component.Name + '.' + PropertyName;
  end
  else Caption := 'G32 Collection Editor';
end;

procedure TG32CollectionEditor.Reset;
begin
  with AvailableList do
  begin
    Items.BeginUpdate;
    Items.Clear;
    Items.EndUpdate;
  end;
  with AllocatedList do
  begin
    Items.BeginUpdate;
    Items.Clear;
    Items.EndUpdate;
  end;
end;

procedure TG32CollectionEditor.ReadAvailableItems;
var
  I, N: Integer;
begin
  N := GetG32CollectionCount(CurrentCollection.ClassInfo);
  with AvailableList.Items do
  begin
    BeginUpdate;
    try
      for I := 0 to N - 1 do
        with AvailableList.Items.Add do
          Caption := GetG32CollectionItemName(CurrentCollection.ClassInfo, I);
    finally
      EndUpdate;
    end;
  end;
end;

procedure TG32CollectionEditor.UpdateAllocatedItems;
var
  I: Integer;
begin
  if CurrentCollection = nil then Exit;

  with AllocatedList.Items do
  begin
    BeginUpdate;
    LockState;
    try
      Clear;
      for I := 0 to CurrentCollection.Count - 1 do
        with Add do
        begin
          Caption := CurrentCollection.Items[I].DisplayName;
        end;
    finally
      UnlockState;
      EndUpdate;
    end;
  end;
end;

procedure TG32CollectionEditor.Add(AvailableIndex: Integer);
var
  ItemClass: TG32CollectionItemClass;
  ListItem: TListItem;
  PrevCount: Integer;
begin
  SelectNone(False);
  if CurrentCollection = nil then Exit;
  ItemClass := GetG32CollectionItemClass(CurrentCollection.ClassInfo, AvailableIndex);
  Assert(ItemClass <> nil);
  CurrentCollection.BeginUpdate;
  try
    PrevCount := CurrentCollection.Count + 1;
    CurrentCollection.Add(ItemClass);
    if PrevCount <> CurrentCollection.Count then UpdateAllocatedItems
    else AllocatedList.Selected := AllocatedList.Items.Add;
  finally
    CurrentCollection.EndUpdate;
  end;
  SetSelection;
  CurrentDesigner.Modified;
  ListItem := AllocatedList.Items[AllocatedList.Items.Count - 1];
  ListItem.Focused := True;
  ListItem.MakeVisible(False);
  UpdateAllocatedItems;
end;

procedure TG32CollectionEditor.SetSelection;
var
  I: Integer;
  List: TDesignerSelectionList;
begin
  if SelectionError then Exit;
  try
    if AllocatedList.SelCount > 0 then
    begin
      List := TDesignerSelectionList.Create;
      try
        ItemIDList.Clear;
        for I := 0 to AllocatedList.Items.Count - 1 do
          if AllocatedList.Items[I].Selected then
          begin
            List.Add(CurrentCollection.Items[I]);
            ItemIDList.Add(Pointer(CurrentCollection.Items[I].ID));
          end;
        CurrentDesigner.SetSelections(List);
      finally
        List.Free;
      end;
    end
    else
      CurrentDesigner.SelectComponent(CurrentCollection);
  except
    SelectionError := True;
    Application.HandleException(ExceptObject);
    Close;
  end;
end;

procedure TG32CollectionEditor.LockState;
begin
  Inc(StateLock);
end;

procedure TG32CollectionEditor.UnlockState;
begin
  Dec(StateLock);
end;

procedure TG32CollectionEditor.SelectAll(DoUpdate: Boolean);
var
  I: Integer;
begin
  LockState;
  AllocatedList.Items.BeginUpdate;
  try
    for I := 0 to AllocatedList.Items.Count - 1 do
      AllocatedList.Items[I].Selected := True;
  finally
    AllocatedList.Items.EndUpdate;
    UnlockState;
    if DoUpdate then SetSelection;
  end;
end;

procedure TG32CollectionEditor.SelectNone(DoUpdate: Boolean);
var
  I: Integer;
begin
  LockState;
  AllocatedList.Items.BeginUpdate;
  try
    for I := 0 to AllocatedList.Items.Count - 1 do
      AllocatedList.Items[I].Selected := False;
  finally
    AllocatedList.Items.EndUpdate;
    UnlockState;
    if DoUpdate then SetSelection;
  end;
end;

procedure TG32CollectionEditor.AMDeferUpdate(var Msg: TMessage);
begin
  if StateLock = 0 then
  begin
    if TMessage(Msg).WParam = 0 then SetSelection else FormModified;
  end
  else
    PostMessage(Handle, AM_DEFER_UPDATE, TMessage(Msg).WParam, TMessage(Msg).LParam);
end;

procedure TG32CollectionEditor.FormModified;
begin
  if CurrentCollection <> nil then
  begin
    UpdateAllocatedItems;
    if CompLib.GetActiveForm.Designer <> Designer then Exit;
    GetSelection;
  end;
end;

procedure TG32CollectionEditor.GetSelection;
var
  I: Integer;
  Item: TG32CollectionItem;
  List: TDesignerSelectionList;
begin
  LockState;
  try
    AllocatedList.Selected := nil;
  finally
    UnlockState;
  end;

  List := TDesignerSelectionList.Create;
  try
    CurrentDesigner.GetSelections(List);
    if (List.Count = 0) or (List.Count > CurrentCollection.Count) then Exit;
    if not ((List[0] = CurrentComponent) or (List[0] = CurrentCollection) or
      (TG32CollectionEditor(List[0]).GetOwner = CurrentCollection)) then Exit;

    if List.Count > AllocatedList.Items.Count then UpdateAllocatedItems;
  finally
    List.Free;
  end;

  LockState;
  try
    for I := ItemIDList.Count downto 0 do
    begin
      Item := CurrentCollection.FIndItemID(Integer(ItemIDList[I]));
      if Item<> nil then
        AllocatedList.Items[Item.Index].Selected := True
        else ItemIDList.Delete(I);
    end;
  finally
    UnlockState;
  end;
end;

{ TG32CollectionProperty }

procedure TG32CollectionProperty.Edit;
var
  Obj: TPersistent;
begin
  Obj := GetComponent(0);
  while (Obj <> nil) and not (Obj is TComponent) do
    Obj := TPersistentAccess(Obj).GetOwner;
  if not Assigned(G32CollectionEditor) then
    G32CollectionEditor := TG32CollectionEditor.Create(Application);

  G32CollectionEditor.SetCollection(
    TG32Collection(GetOrdValue),
    IFormDesigner(Designer),
    TComponent(Obj),
    GetName);

  G32CollectionEditor.Show;
end;

function TG32CollectionProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paDialog, paReadOnly]
end;

procedure TG32CollectionEditor.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
  G32CollectionEditor := nil;
end;

procedure TG32CollectionEditor.AvailableListDblClick(Sender: TObject);
begin
  with AvailableList do
  begin
    if Selected <> nil then Add(Selected.Index);
  end;
end;

procedure TG32CollectionEditor.AllocatedListChange(Sender: TObject;
  Item: TListItem; Change: TItemChange);
var
  Msg: TMsg;
begin
  if (Change = ctState) and (StateLock = 0) then
    if not PeekMessage(Msg, Handle, AM_DEFER_UPDATE, AM_DEFER_UPDATE, PM_NOREMOVE) then
    PostMessage(Handle, AM_DEFER_UPDATE, 0, 0);
end;

procedure TG32CollectionEditor.FormCreate(Sender: TObject);
begin
  ItemIDList := TList.Create;
end;

procedure TG32CollectionEditor.FormDestroy(Sender: TObject);
begin
  ItemIDList.Free;
end;

initialization

finalization

  if Assigned(G32CollectionEditor) then G32CollectionEditor.Free;
  G32CollectionEditor := nil;

end.
