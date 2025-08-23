unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls, Buttons, ShellBrowser;

// This sample application shows the use of the non visual TShellBrowser
// component. Use the TShellBrowser component if you want a maximum level of
// customization when using the Windows shell

type
  TMainForm = class(TForm)
    ListView: TListView;
    Panel1: TPanel;
    Label1: TLabel;
    Edit: TEdit;
    ListButton: TButton;
    PropertiesButton: TButton;
    ShellBrowser: TShellBrowser;
    ChooseFolderButton: TSpeedButton;
    JamSystemImageList1: TJamSystemImageList;
    procedure ListButtonClick(Sender: TObject);
    procedure ListViewDblClick(Sender: TObject);
    procedure PropertiesButtonClick(Sender: TObject);
    procedure ListViewMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ChooseFolderButtonClick(Sender: TObject);
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.DFM}

// Fill the ListView
procedure TMainForm.ListButtonClick(Sender: TObject);
begin
  ShellBrowser.Folder := Edit.Text; // Get Path from edit box
  ShellBrowser.FillListView(ListView, False); // and fill the list
end;

// execute default action after double click on an object
procedure TMainForm.ListViewDblClick(Sender: TObject);
begin
  if not Assigned(ListView.Selected) then exit;
  ShellBrowser.ObjectName := ListView.Selected.Caption;
  if ShellBrowser.IsFolder then begin // if Folder then show it
    ShellBrowser.BrowseObject; // Make object to new folder
    ShellBrowser.FillListView(ListView, False);
    Edit.Text := ShellBrowser.Folder; // Update edit field
  end else
    if not ShellBrowser.InvokeContextMenuCommand('Default') then
      ShowMessage('Error! Could not execute default action.');
end;

// OnClick event of the Properties button
procedure TMainForm.PropertiesButtonClick(Sender: TObject);
begin
  if not Assigned(ListView.Selected) then exit;
  ShellBrowser.ObjectName := ListView.Selected.Caption;
  if not ShellBrowser.InvokeContextMenuCommand('Properties') then
    ShowMessage('No Properties Available');
end;

// Use onMouseUp event for displaying the context menu
procedure TMainForm.ListViewMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var Item: TListItem;
begin
  if Button <> mbRight then exit;
  Item := ListView.GetItemAt(X,Y); // Get Item which was hit
  if not Assigned(Item) or not Assigned(ListView.Selected) then exit; // No Item hit -> exit
  ShellBrowser.ObjectName := ListView.Selected.Caption;
  ShellBrowser.ShowContextMenu(ListView.ClientToScreen(Point(x,y)), nil);
end;

// show the folder browser dialog
procedure TMainForm.ChooseFolderButtonClick(Sender: TObject);
begin
  ShellBrowser.BrowseForFolder(''); // You could also display a small messagr
  Edit.Text := ShellBrowser.Folder; // Update edit box
  ShellBrowser.FillListView(ListView, False); // Show objects in the folder
end;


end.

