unit G32_Collections;

interface

uses
  Classes, SysUtils, TypInfo, DsgnIntf, Dialogs;

type
  TG32Collection = class;

  TG32CollectionItem = class(TComponent)
  private
    FCollection: TG32Collection;
    FID: Integer;
    function GetIndex: Integer;
    procedure SetCollection(Value: TG32Collection);
  protected
    procedure Changed(AllItems: Boolean);
    function GetOwner: TPersistent; override;
    function GetDisplayName: string; virtual;
    procedure SetIndex(Value: Integer); virtual;
    procedure SetDisplayName(const Value: string); virtual;
  public
    constructor Create(Collection: TG32Collection); reintroduce; virtual;
    destructor Destroy; override;
    function GetNamePath: string; override;
    property Collection: TG32Collection read FCollection write SetCollection;
    property DisplayName: string read GetDisplayName write SetDisplayName;
    property ID: Integer read FID;
    property Index: Integer read GetIndex write SetIndex;
  end;

  TG32CollectionItemClass = class of TG32CollectionItem;

  TG32Collection = class(TPersistent)
  private
    FItems: TList;
    FOwner: TComponent;
    FPropName: string;
    FUpdateCount: Integer;
    function Equals(C: TG32Collection): Boolean;
    function GetCount: Integer;
    function GetPropName: string;
    procedure InsertItem(Item: TG32CollectionItem);
    procedure RemoveItem(Item: TG32CollectionItem);
  protected
    NextID: Integer;
    procedure Changed;
    procedure DefineProperties(Filer: TFiler); override;
    function GetItem(Index: Integer): TG32CollectionItem;
    procedure ReadData(Reader: TReader);
    procedure SetItem(Index: Integer; Value: TG32CollectionItem);
    procedure SetItemName(Item: TG32CollectionItem); virtual;
    procedure Update(Item: TG32CollectionItem); virtual;
    procedure WriteData(Writer: TWriter);
    property PropName: string read GetPropName write FPropName;
    property UpdateCount: Integer read FUpdateCount;
  public
    constructor Create(AOwner: TComponent);
    destructor Destroy; override;
    procedure Add(AComponent: TG32CollectionItem); overload;
    function Add(ItemClass: TG32CollectionItemClass): TG32CollectionItem; overload;
    procedure Assign(Source: TPersistent); override;
    procedure BeginUpdate; virtual;
    procedure Clear;
    procedure Delete(Index: Integer);
    procedure EndUpdate; virtual;
    function FindItemID(ID: Integer): TG32CollectionItem;
    function GetNamePath: string; override;
    function Insert(Index: Integer; ItemClass: TG32CollectionItemClass): TG32CollectionItem;
    property Count: Integer read GetCount;
    property Items[Index: Integer]: TG32CollectionItem read GetItem write SetItem;
  end;

  TG32CollectionClass = class of TG32Collection;

  procedure RegisterG32CollectionItem(CollectionType: PTypeInfo;
    ItemName: string; const ItemClass: TG32CollectionItemClass);
  function GetG32CollectionCount(CollectionType: PTypeInfo): Integer;
  function GetG32CollectionItemClass(CollectionType: PTypeInfo; Index: Integer): TG32CollectionItemClass;
  function GetG32CollectionItemName(CollectionType: PTypeInfo; Index: Integer): string;

implementation

{ Design time support }

type
  TPersistentAccess = class(TPersistent);
  TComponentAccess = class(TComponent);

procedure GetDesigner(Obj: TPersistent; out Result: IDesignerNotify);
var
  Temp: TPersistent;
begin
  Result := nil;
  if Obj = nil then Exit;
  Temp := TPersistentAccess(Obj).GetOwner;
  if Temp = nil then
  begin
    if (Obj is TComponent) and (csDesigning in TComponent(Obj).ComponentState) then
      TComponentAccess(Obj).QueryInterface(IDesignerNotify, Result);
  end
  else
  begin
    if (Obj is TComponent) and
      not (csDesigning in TComponent(Obj).ComponentState) then Exit;
    GetDesigner(Temp, Result);
  end;
end;

procedure NotifyDesigner(Self, Item: TPersistent; Operation: TOperation);
var
  Designer: IDesignerNotify;
begin
  GetDesigner(Self, Designer);
  if Designer <> nil then Designer.Notification(Item, Operation);
end;

{ TG32CollectionItem }

procedure TG32CollectionItem.Changed(AllItems: Boolean);
begin
  if Assigned(Collection) and (Collection.UpdateCount = 0) then
    if AllItems then Collection.Update(nil)
    else Collection.Update(Self);
end;

constructor TG32CollectionItem.Create(Collection: TG32Collection);
begin
  inherited Create(Collection.FOwner);
  SetCollection(Collection);
end;

destructor TG32CollectionItem.Destroy;
begin
  SetCollection(nil);
  inherited;
end;

function TG32CollectionItem.GetDisplayName: string;
begin
  Result := ClassName;
end;

function TG32CollectionItem.GetIndex: Integer;
begin
  if Assigned(Collection) then Result := Collection.FItems.IndexOf(Self)
  else Result := -1;
end;

function TG32CollectionItem.GetNamePath: string;
begin
  if FCollection <> nil then
    Result := Format('%s[%d]', [FCollection.GetNamePath, Index])
  else
    Result := ClassName;
end;

function TG32CollectionItem.GetOwner: TPersistent;
begin
  Result := Collection;
end;

procedure TG32CollectionItem.SetCollection(Value: TG32Collection);
begin
  if Value <> Collection then
  begin
    if Assigned(Collection) then Collection.RemoveItem(Self);
    if Assigned(Value) then Value.InsertItem(Self);
  end;
end;

procedure TG32CollectionItem.SetDisplayName(const Value: string);
begin
  Changed(False);
end;

procedure TG32CollectionItem.SetIndex(Value: Integer);
var
  CurrentIndex: Integer;
begin
  CurrentIndex := GetIndex;
  if (CurrentIndex >= 0) and (Value <> CurrentIndex) then
  begin
    Collection.FItems.Move(CurrentIndex, Value);
    Changed(True);
  end;
end;

{ TG32Collection }

function TG32Collection.Add(ItemClass: TG32CollectionItemClass): TG32CollectionItem;
begin
  Result := ItemClass.Create(Self);
end;

procedure TG32Collection.Add(AComponent: TG32CollectionItem);
begin
  AComponent.SetCollection(Self);
end;

procedure TG32Collection.Assign(Source: TPersistent);
var
  I: Integer;
  ClassRef: TG32CollectionItemClass;
begin
  if Source is TG32Collection then
  begin
    BeginUpdate;
    try
      Clear;
      for I := 0 to TG32Collection(Source).Count - 1 do
        with TG32Collection(Source) do
        begin
          ClassRef := TG32CollectionItemClass(Items[I].ClassType);
          Self.Add(ClassRef).Assign(Items[I]);
        end;
    finally
      EndUpdate;
    end;
    Exit;
  end;
  inherited;
end;

procedure TG32Collection.BeginUpdate;
begin
  Inc(FUpdateCount);
end;

procedure TG32Collection.Changed;
begin
  if FUpdateCount = 0 then Update(nil);
end;

procedure TG32Collection.Clear;
begin
  if FItems.Count > 0 then
  begin
    BeginUpdate;
    try
      while FItems.Count > 0 do TCollectionItem(FItems.Last).Free;
    finally
      EndUpdate;
    end;
  end;
end;

constructor TG32Collection.Create(AOwner: TComponent);
begin
  FItems := TList.Create;
  FOwner := AOwner;
end;

procedure TG32Collection.DefineProperties(Filer: TFiler);

  function DoWrite: Boolean;
  begin
    if Filer.Ancestor <> nil then
    begin
      Result := True;
      if Filer.Ancestor is TG32Collection then
        Result := not Equals(TG32Collection(Filer.Ancestor))
    end
    else Result := Count > 0;
  end;

begin
  Filer.DefineProperty('G32CollectionData', ReadData, WriteData, DoWrite);
end;

procedure TG32Collection.Delete(Index: Integer);
begin
  TG32CollectionItem(Fitems[Index]).Free;
end;

destructor TG32Collection.Destroy;
begin
  FUpdateCount := 1;
  if Assigned(FItems) then Clear;
  FItems.Free;
  inherited;
end;

procedure TG32Collection.EndUpdate;
begin
  Dec(FUpdateCount);
  Changed;
end;

function TG32Collection.Equals(C: TG32Collection): Boolean;
var
  I: Integer;
begin
  Result := False;
  if C = nil then Exit;
  if C.ClassInfo <> ClassInfo then Exit;
  if C.Count <> Count then Exit;
  for I := 0 to Count - 1 do if Items[I].FID <> C.Items[I].FID then Exit;
  Result := True;
end;

function TG32Collection.FindItemID(ID: Integer): TG32CollectionItem;
var
  I: Integer;
begin
  for I := 0 to FItems.Count - 1 do
  begin
    Result := TG32CollectionItem(FItems[I]);
    if Result.ID = ID then Exit;
  end;
  Result := nil;
end;

function TG32Collection.GetCount: Integer;
begin
  Result := FItems.Count;
end;

function TG32Collection.GetItem(Index: Integer): TG32CollectionItem;
begin
  Result := FItems[Index];
end;

function TG32Collection.GetNamePath: string;
var
  S, P: string;
begin
  Result := ClassName;
  if GetOwner = nil then Exit;
  S := GetOwner.GetNamePath;
  if S = '' then Exit;
  P := PropName;
  if P = '' then Exit;
  Result := S + '.' + P;
end;

function TG32Collection.GetPropName: string;
var
  I: Integer;
  Props: PPropList;
  TypeData: PTypeData;
  Owner: TPersistent;
begin
  Result := FPropName;
  Owner := GetOwner;
  if (Length(Result) > 0) or (Owner = nil) or (Owner.ClassInfo = nil) then Exit;
  TypeData := GetTypeData(Owner.ClassInfo);
  if (TypeData = nil) or (TypeData^.PropCount = 0) then Exit;
  GetMem(Props, TypeData^.PropCount * SizeOf(Pointer));
  try
    GetPropInfos(Owner.ClassInfo, Props);
    for I := 0 to TypeData^.PropCount - 1 do
      with Props^[I]^ do
        if (PropType^^.Kind = tkClass) and
          (GetOrdProp(Owner, Props^[I]) = Integer(Self)) then
          FPropName := Name;
  finally
    FreeMem(Props);
  end;
  Result := FPropName;
end;

function TG32Collection.Insert(Index: Integer; ItemClass: TG32CollectionItemClass): TG32CollectionItem;
begin
  Result := Add(ItemClass);
  Result.Index := Index;
end;

procedure TG32Collection.InsertItem(Item: TG32CollectionItem);
begin
  FItems.Add(Item);
  Item.FCollection := Self;
  Item.FID := NextID;
  Inc(NextID);
  SetItemName(Item);
  Changed;
  NotifyDesigner(Self, Item, opInsert);
end;

type TReaderAccess = class(TReader);

procedure TG32Collection.ReadData(Reader: TReader);
var
  ItemClassName: string;
  ItemClass: TG32CollectionItemClass;
  Component: TComponent;
  Item: TG32CollectionItem;
begin
  Reader.ReadListBegin;
  BeginUpdate;
  with TReaderAccess(Reader) do
  try
    Clear;
    while not EndOfList do
    begin
      Component := ReadComponent(nil);
      Add(TG32CollectionItem(Component));
    {  ItemClassName := ReadIdent;
      ItemClass := TG32CollectionItemClass(FindClass(ItemClassName));
      Item := Add(ItemClass);
      try
        ReadListBegin;
        while not EndOfList do ReadProperty(Item);
        ReadListEnd;
      except
        on E: Exception do
        begin
          ShowMessage(E.Message);
          raise;
        end;
      end;   }
    end;
  finally
    EndUpdate;
  end;
  Reader.ReadListEnd;
end;

procedure TG32Collection.RemoveItem(Item: TG32CollectionItem);
begin
  NotifyDesigner(Self, Item, opRemove);
  FItems.Remove(Item);
  Item.FCollection := nil;
  Changed;
end;

procedure TG32Collection.SetItem(Index: Integer; Value: TG32CollectionItem);
begin
  TG32CollectionItem(FItems[Index]).ASsign(Value);
end;

procedure TG32Collection.SetItemName(Item: TG32CollectionItem);
begin
  // do nothing
end;

procedure TG32Collection.Update(Item: TG32CollectionItem);
begin
  // do nothing
end;

type TWriterAccess = class(TWriter);

procedure TG32Collection.WriteData(Writer: TWriter);
var
  I: Integer;
  Item: TG32CollectionItem;
begin
  with TWriterAccess(Writer) do
  begin
    WriteListBegin;
    for I := 0 to Count - 1 do
    begin
      WriteComponent(Items[I]);
      {WriteIdent(Items[I].ClassName);
      WriteListBegin;
      Item := Items[I];
      WriteProperties(Item);
      WriteListEnd; }
    end;
    WriteListEnd;
  end;
end;

{ TCollectionClassManager }

type
  PItemClassEntry = ^TItemClassEntry;
  TItemClassEntry = record
    Name: string[127];
    ItemClass: TG32CollectionItemClass;
  end;

  PCollectionEntry = ^TCollectionEntry;
  TCollectionEntry = record
    CollType: PTypeInfo;
    ItemClasses: array of TItemClassEntry;
  end;

  TCollectionClassManager = class
  protected
    List: array of TCollectionEntry;
  public
    destructor Destroy; override;
    function AddCollectionEntry(CollectionType: PTypeInfo): PCollectionEntry;
    procedure AddItemClass(CollectionType: PTypeInfo; const AName: string; const AItemClass : TG32CollectionItemClass);
    procedure Clear;
    function FindCollectionEntry(CollectionType: PTypeInfo): PCollectionEntry;
  end;

var
  CollectionClassManager: TCollectionClassManager;

function TCollectionClassManager.AddCollectionEntry(CollectionType: PTypeInfo): PCollectionEntry;
var
  L: Integer;
begin
  if FindCollectionEntry(CollectionType) <> nil then
    raise Exception.Create('Collection class is already registered');
  L := Length(List);
  SetLength(List, L + 1);
  Result := @List[L];
  Result^.CollType := CollectionType;
  Result^.ItemClasses := nil;
end;

procedure TCollectionClassManager.AddItemClass(
  CollectionType: PTypeInfo;
  const AName: string;
  const AItemClass: TG32CollectionItemClass);
var
  E: PCollectionEntry;
  I, L: Integer;
begin
  if Length(AName) = 0 then raise Exception.Create('Invalid Collection Class Tag');
  if AItemClass = nil then raise Exception.Create('Invalid Collection Class Type');
  E := FindCollectionEntry(CollectionType);
  if E = nil then raise Exception.Create('Unregistered Collection Class Type');
  with E^ do
  begin
    // check, that there is no classes registered with the same name/type
    for I := 0 to High(ItemClasses) do
      with ItemClasses[I] do
        if (Name = AName) or (ItemClass = AItemClass) then
          raise Exception.Create('Item class with the same name/type is already registered');
    L := Length(ItemClasses);
    SetLength(ItemClasses, L + 1);
    with ItemClasses[L] do
    begin
      Name := AName;
      ItemClass := AItemClass;
    end;
  end;
end;

procedure TCollectionClassManager.Clear;
var
  I: Integer;
begin
  for I := 0 to High(List) do List[I].ItemClasses := nil;
  List := nil;
end;

destructor TCollectionClassManager.Destroy;
begin
  Clear;
  inherited;
end;

function TCollectionClassManager.FindCollectionEntry(
  CollectionType: PTypeInfo): PCollectionEntry;
var
  I: Integer;
begin
  Result := nil;
  for I := 0 to High(List) do
    if List[I].CollType = CollectionType then
    begin
      Result := @List[I];
      Exit;
    end;
end;

procedure RegisterG32CollectionItem(CollectionType: PTypeInfo;
  ItemName: string; const ItemClass: TG32CollectionItemClass);
begin
  Assert(ItemName <> '');
  with CollectionClassManager do
  begin
    if FindCollectionEntry(CollectionType) = nil then
      AddCollectionEntry(CollectionType);
    AddItemClass(CollectionType, ItemName, ItemClass);
  end;
  RegisterNoIcon([ItemClass]);
end;

function GetG32CollectionCount(CollectionType: PTypeInfo): Integer;
var
  E: PCollectionEntry;
begin
  Result := 0;
  E := CollectionClassManager.FindCollectionEntry(CollectionType);
  if E <> nil then Result := Length(E^.ItemClasses);
end;

function GetG32CollectionItemClass(CollectionType: PTypeInfo; Index: Integer): TG32CollectionItemClass;
var
  E: PCollectionEntry;
begin
  Result := nil;
  E := CollectionClassManager.FindCollectionEntry(CollectionType);
  if (E <> nil) and (Index >= 0) and (Index < Length(E^.ItemClasses)) then
    Result := E^.ItemClasses[Index].ItemClass;
end;

function GetG32CollectionItemName(CollectionType: PTypeInfo; Index: Integer): string;
var
  E: PCollectionEntry;
begin
  Result := '';
  E := CollectionClassManager.FindCollectionEntry(CollectionType);
  if (E <> nil) and (Index >= 0) and (Index < Length(E^.ItemClasses)) then
    Result := E^.ItemClasses[Index].Name;
end;

initialization
  CollectionClassManager := TCollectionClassManager.Create;

finalization
  CollectionClassManager.Free;
  CollectionClassManager := nil;

end.
 