unit G32_Dsgn_Layers;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  DsgnIntf, DsgnWnds, LibIntf, G32_Layers, ComCtrls, Buttons, ExtCtrls;

const
  CM_DEFERUPDATE = WM_USER + 101;

type
  TLayerEditorForm = class(TDesignWindow)
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    Panel4: TPanel;
    Splitter1: TSplitter;
    Panel5: TPanel;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    SpeedButton5: TSpeedButton;
    RegList: TListView;
    ListView: TListView;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure SpeedButton1Click(Sender: TObject);
    procedure ListViewChange(Sender: TObject; Item: TListItem;
      Change: TItemChange);
  private
    FCollectionPropertyName: string;
    FSelectionError: Boolean;
    FStateLock: Integer;
    procedure CMDeferUpdate(var Msg: TMessage); message CM_DEFERUPDATE;
    procedure LockState;
    procedure SetCollectionPropertyName(const Value: string);
    procedure UnlockState;
  protected
    FCollectionClassName: string;
    FItemIDList: TList;
    procedure Activated; override;
    function UniqueName(Component: TComponent): string; override;
    procedure UpdateList;
  public
    Collection: TLayerCollection;
    Component: TComponent;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure ComponentDeleted(Component: IPersistent); override;
    procedure FormModified; override;
    procedure FormClosed(Form: TCustomForm); override;
    procedure GetSelection;
    procedure SelectAll(DoUpdate: Boolean);
    procedure SelectNone(DoUpdate: Boolean);
    procedure SelectionChanged(ASelection: TDesignerSelectionList); override;
    procedure SetSelection;
    property CollectionPropertyName: string read FCollectionPropertyName write SetCollectionPropertyName;
  end;

  TLayerCollectionProperty = class(TClassProperty)
    procedure Edit; override;
    function GetAttributes: TPropertyAttributes; override;
  end;

implementation

{$R *.DFM}
{$D-}

uses Consts;

type TPersistentAccess = class(TPersistent);

{ Layer Editor }

function FindEditorForm(ADesigner: IDesigner; ACollection: TLayerCollection): TLayerEditorForm;
var
  I: Integer;
begin
  Result := nil;
  for I := 0 to Screen.FormCount - 1 do
    if (Screen.Forms[I] is TLayerEditorForm) then
      with TLayerEditorForm(Screen.Forms[I]) do
        if (Designer = ADesigner) and (Collection = ACollection) then
          Result := TLayerEditorForm(Screen.Forms[I]);
end;

procedure ShowLayerEditorForm(ADesigner: IDesigner; AComponent: TComponent;
  ACollection: TLayerCollection; const PropertyName: string);
var
  Form: TLayerEditorForm;
begin
  if ACollection = nil then Exit;
  Form := FindEditorForm(ADesigner, ACollection);
  if Form <> nil then
  begin
    Form.Show;
    Form.BringToFront;
    if Form.WindowState = wsMinimized then Form.WindowState := wsNormal;
  end
  else
  begin
    Form := TLayerEditorForm.Create(Application);
    try
      Form.Designer := ADesigner as IFormDesigner;
      Form.Collection := ACollection;
      Form.Component := AComponent;
      Form.FCollectionClassName := ACollection.ClassName;
      Form.CollectionPropertyName := PropertyName;
      Form.UpdateList;
      Form.Show;
    except
      Form.Free;
      raise;
    end;
  end;
end;

{ TLayerEditorForm }

procedure TLayerEditorForm.Activated;
var
  Msg: TMessage;
begin
  Msg.Msg := WM_ACTIVATE;
  Msg.WParam := 1;
  Designer.IsDesignMsg(Designer.Form, Msg);
  SetSelection;
end;

procedure TLayerEditorForm.CMDeferUpdate(var Msg: TMessage);
begin
  if FStateLock = 0 then
  begin
    if Msg.WParam = 0 then SetSelection
    else FormModified;
  end
  else
    PostMessage(Handle, CM_DEFERUPDATE, Msg.WParam, Msg.LParam);
end;

procedure TLayerEditorForm.ComponentDeleted(Component: IPersistent);

  function IsOwnedBy(Owner, Child: TPersistent): Boolean;
  begin
    Result := False;
    if Owner = nil then Exit;
    while (Child <> nil) and (Child <> Owner) and not (Child is TComponent) do
      Child := TPersistentAccess(Child).GetOwner;
    Result := Child = Owner;
  end;

var
  Temp: TPersistent;
begin
  Temp := TryExtractPersistent(Component);
  if Temp = nil then Exit;
  if (Self.Component = nil) or (csDestroying in Self.Component.ComponentState) or
    (Temp = Self.Component) or IsOwnedBy(Temp, Collection) then
  begin
    Collection := nil;
    Self.Component := nil;
    Close;
  end
  else if IsOwnedBy(Collection, Temp) then
    PostMessage(Handle, CM_DEFERUPDATE, 1, 0);
end;

constructor TLayerEditorForm.Create(AOwner: TComponent);
begin
  inherited;
  FItemIDList := TList.Create;
end;

destructor TLayerEditorForm.Destroy;
begin
  FItemIDList.Free;
  inherited;
end;

procedure TLayerEditorForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if Component <> nil then Designer.SelectComponent(Component);
  Action := caFree;
  LockState;
end;

procedure TLayerEditorForm.FormClosed(Form: TCustomForm);
begin
  inherited;
  if Designer.Form = Form then
  begin
    Collection := nil;
    Component := nil;
    Close;
  end;
end;

procedure TLayerEditorForm.FormModified;
begin
  if Collection <> nil then
  begin
    UpdateList;
    if CompLib.GetActiveForm.Designer <> Designer then Exit;
    GetSelection;
  end;
end;

procedure TLayerEditorForm.GetSelection;
var
  I: Integer;
  Item: TCustomLayer;
  List: TDesignerSelectionList;
begin
  LockState;
  try
    ListView.Selected := nil;
  finally
    UnlockState;
  end;

  List := TDesignerSelectionList.Create;
  try
    Designer.GetSelections(List);
    if (List.Count = 0) or (List.Count > Collection.Count) then Exit;
    if not ((List[0] = Component) or (List[0] = Collection)
      or (TLayerEditorForm(List[0]).GetOwner = Collection)) then Exit;

    if List.Count > ListView.Items.Count then UpdateList;
  finally
    List.Free;
  end;

  LockState;
  try
    for I := FItemIDList.Count - 1 downto 0 do
    begin
      Item := Collection.FindItemID(Integer(FItemIDList[I]));
      if Item <> nil then
        ListView.Items[Item.Index].Selected := True
      else FItemIDList.Delete(I);
    end;
  finally
    UnlockState;
  end;
end;

procedure TLayerEditorForm.ListViewChange(Sender: TObject; Item: TListItem; Change: TItemChange);
var
  Msg: TMsg;
begin
  if (Change = ctState) and (FStateLock = 0) then
    if not PeekMessage(Msg, Handle, CM_DEFERUPDATE, CM_DEFERUPDATE, PM_NOREMOVE) then
      PostMessage(Handle, CM_DEFERUPDATE, 0, 0);
end;

procedure TLayerEditorForm.LockState;
begin
  Inc(FStateLock);
end;

procedure TLayerEditorForm.SelectAll(DoUpdate: Boolean);
var
  I: Integer;
begin
  LockState;
  ListView.Items.BeginUpdate;
  try
    for I := 0 to ListView.Items.Count - 1 do
      ListView.Items[I].Selected := True;
  finally
    ListView.Items.EndUpdate;
    UnlockState;
    if DoUpdate then SetSelection;
  end;
end;

procedure TLayerEditorForm.SelectionChanged(ASelection: TDesignerSelectionList);
begin
  // do nothing
end;

procedure TLayerEditorForm.SelectNone(DoUpdate: Boolean);
var
  I: Integer;
begin
  LockState;
  ListView.Items.BeginUpdate;
  try
    for I := 0 to ListView.Items.Count - 1 do
      ListView.Items[I].Selected := False;
  finally
    ListView.Items.EndUpdate;
    UnlockState;
    if DoUpdate then SetSelection;
  end;
end;

procedure TLayerEditorForm.SetCollectionPropertyName(const Value: string);
begin
  if Value <> FCollectionPropertyName then
  begin
    FCollectionPropertyName := Value;
    Caption := Format('%s.%s', [Component.Name, Value]);
  end;
end;

procedure TLayerEditorForm.SetSelection;
var
  I: Integer;
  List: TDesignerSelectionList;
begin
  if FSelectionError then Exit;
  try
    if ListView.SelCount > 0 then
    begin
      List := TDesignerSelectionList.Create;
      try
        FItemIDList.Clear;
        for I := 0 to ListView.Items.Count - 1 do
          if ListView.Items[I].Selected then
          begin
            List.Add(Collection.Items[I]);
            FItemIDList.Add(Pointer(Collection.Items[I].ID));
          end;
        Designer.SetSelections(List);
      finally
        List.Free;
      end;
    end
    else Designer.SelectComponent(Collection);
  except
    FSelectionError := True;
    Application.HandleException(ExceptObject);
    Close;
  end;
end;

procedure TLayerEditorForm.SpeedButton1Click(Sender: TObject);
var
  Item: TListItem;
begin
  SelectNone(False);
  Collection.BeginUpdate;
  try
    Collection.Add;
    UpdateList;
  finally
    Collection.EndUpdate;
  end;
  SetSelection;
  Designer.Modified;
  Assert(ListView.Items.Count > 0);
  Item := ListView.Items[ListView.Items.Count - 1];
  Item.Focused := True;
  Item.MakeVisible(False);
end;

function TLayerEditorForm.UniqueName(Component: TComponent): string;
begin
  Result := Designer.UniqueName(Component.ClassName);
end;

procedure TLayerEditorForm.UnlockState;
begin
  Dec(FStateLock);
end;

procedure TLayerEditorForm.UpdateList;
var
  I: Integer;
begin
  if Collection = nil then Exit;
  LockState;
  try
    ListView.Items.BeginUpdate;
    try
      ListView.Items.Clear;
      for I := 0 to Collection.Count - 1 do
        with ListView.Items.Add do
        begin
          Caption := Collection.Items[I].DisplayName;
        end;
    finally
      ListView.Items.EndUpdate;
    end;
  finally
    UnlockState;
  end;
end;

{ TLayerCollectionProperty }

procedure TLayerCollectionProperty.Edit;
var
  Obj: Tpersistent;
begin
  Obj := GetComponent(0);
  while (Obj <> nil) and not (Obj is TComponent) do
    Obj := TPersistentAccess(Obj).GetOwner;
  ShowLayerEditorForm(Designer, TComponent(Obj), TLayerCollection(GetOrdValue),
    GetName);
end;

function TLayerCollectionProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paDialog, paReadOnly];
end;

end.
