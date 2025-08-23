unit LUTPropertyEditor;

interface

uses
  LUTControl, Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, DsgnIntf;

type
  TLUTEditorDlg = class(TForm)
    OKButton: TButton;
    Cancel: TButton;
    Panel1: TPanel;
    Memo: TMemo;
    StaticText1: TStaticText;
    Reset: TButton;
    LUT: TLUTControl;
    Bevel1: TBevel;
    procedure FormCreate(Sender: TObject);
    procedure LUTChange(Sender: TObject);
    procedure MemoChange(Sender: TObject);
    procedure ResetClick(Sender: TObject);
  end;

  TLUTNodeStringEditor = class(TComponent)
  private
    FNodeString: TNodeString;
    FLUTForm: TLUTEditorDlg;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function Execute: Boolean;
    property NodeString: TNodeString read FNodeString write FNodeString;
  end;

  TNodeStringProperty = class(TStringProperty)
  public
    procedure Edit; override;
    function GetAttributes: TPropertyAttributes; override;
  end;

  TLUTControlEditor = class(TComponentEditor)
  public
    procedure ExecuteVerb(Index: Integer); override;
    function GetVerb(Index: Integer): string; override;
    function GetVerbCount: Integer; override;
  end;

var
  LUTEditorDlg: TLUTEditorDlg;

procedure Register;

implementation

{$R *.DFM}

procedure TLUTEditorDlg.FormCreate(Sender: TObject);
begin
  Memo.DoubleBuffered := True;
end;

procedure TLUTEditorDlg.LUTChange(Sender: TObject);
begin
  Memo.Text := LUT.Nodes;
end;

procedure TLUTEditorDlg.MemoChange(Sender: TObject);
begin
  try
    LUT.Nodes := Memo.Text
  except
    // do not report errors
  end;
end;

procedure TLUTEditorDlg.ResetClick(Sender: TObject);
begin
  LUT.Nodes := '';
end;

{ TLUTNodeStringEditor }

constructor TLUTNodeStringEditor.Create(AOwner: TComponent);
begin
  inherited;
  FLUTForm := TLUTEditorDlg.Create(Self);
end;

destructor TLUTNodeStringEditor.Destroy;
begin
  FLUTForm.Free;
  inherited;
end;

function TLUTNodeStringEditor.Execute: Boolean;
begin
  FLUTForm.LUT.Nodes := NodeString;
  FLutForm.LUTChange(Self);
  Result := FLutForm.ShowModal = mrOK;
  if Result then NodeString := FLUTForm.LUT.Nodes;
end;

{ TNodeStringProperty }

procedure TNodeStringProperty.Edit;
var
  NodeEditor: TLUTNodeStringEditor;
begin
  NodeEditor := TLUTNodeStringEditor.Create(nil);
  try
    NodeEditor.NodeString := GetStrValue;
    if NodeEditor.Execute then SetStrValue(NodeEditor.NodeString);
  finally
    NodeEditor.Free;
  end;
end;

function TNodeStringProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paDialog, paRevertable];
end;

{ TLUTControlEditor }

procedure TLUTControlEditor.ExecuteVerb(Index: Integer);
var
  Control: TLUTControl;
  NodeStringEditor: TLUTNodeStringEditor;
begin
  Control := Component as TLUTControl;
  if Index = 0 then
  begin
    NodeStringEditor := TLUTNodeStringEditor.Create(nil);
    try
      NodeStringEditor.NodeString := Control.Nodes;
      if NodeStringEditor.Execute then
        Control.Nodes := NodeStringEditor.NodeString;
    finally
      NodeStringEditor.Free;
    end;
  end;
end;

function TLUTControlEditor.GetVerb(Index: Integer): string;
begin
  if Index = 0 then Result := 'Nodes Editor...';
end;

function TLUTControlEditor.GetVerbCount: Integer;
begin
  Result := 1;
end;

procedure Register;
begin
  RegisterComponents('Samples', [TLUTControl]);
  RegisterPropertyEditor(TypeInfo(TNodeString), nil, '', TNodeStringProperty);
  RegisterComponentEditor(TLUTControl, TLUTControlEditor);
end;

end.
