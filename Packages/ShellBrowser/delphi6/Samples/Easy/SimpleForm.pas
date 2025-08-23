unit SimpleForm;

// This is a simple demo application for the TShellBrowser component which
// shows, that there are only two lines of code necessary to show the context
// menu or the properties page. It also shows how to open the Windows
// BrowseForFolder dialog

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ShellBrowser;

type
  TMainForm = class(TForm)
    Edit: TEdit;
    Button1: TButton;
    ShellBrowser: TShellBrowser;
    Button2: TButton;
    Button3: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.DFM}

procedure TMainForm.Button1Click(Sender: TObject);
begin
  ShellBrowser.ObjectName := Edit.Text;
  ShellBrowser.ShowContextMenu(ClientToScreen(Point(24,105)), nil);
end;

procedure TMainForm.Button2Click(Sender: TObject);
begin
  ShellBrowser.BrowseForFolder('Please select a folder!');
  Edit.Text := ShellBrowser.Folder;
end;

procedure TMainForm.Button3Click(Sender: TObject);
begin
  ShellBrowser.ObjectName := Edit.Text;
  ShellBrowser.InvokeContextMenuCommand('Properties');
end;

end.
