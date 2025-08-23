unit main;

// This sample project illustrates the use of the visual explorer controls
// TJamShellTree, TJammShellList and TJamShellCombo. These shell controls are
// connected with a TJamShellLink in order to synchronize them.

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, ShellBrowser, Menus, ShellApi, ComCtrls, ExtCtrls,
  ShellControls, ShellLink;

type
  TMainForm = class(TForm)
    Panel1: TPanel;
    PropertiesButton: TSpeedButton;
    LargeIconsButton: TSpeedButton;
    SmallIconsButton: TSpeedButton;
    DetailsButton: TSpeedButton;
    TreeViewPopup: TPopupMenu;
    FullExpand1: TMenuItem;
    FullCollapse1: TMenuItem;
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    Exit1: TMenuItem;
    Help1: TMenuItem;
    About1: TMenuItem;
    DeleteButton: TSpeedButton;
    ParentButton: TSpeedButton;
    NetworkButton: TSpeedButton;
    Splitter1: TSplitter;
    ShellListView: TJamShellList;
    ShellTree: TJamShellTree;
    JamShellLink: TJamShellLink;
    ImageList1: TImageList;
    JamShellCombo1: TJamShellCombo;
    StatusBar: TStatusBar;
    IconListButton: TSpeedButton;
    procedure PropertiesButtonClick(Sender: TObject);
    procedure LargeIconsButtonClick(Sender: TObject);
    procedure FullExpand1Click(Sender: TObject);
    procedure FullCollapse1Click(Sender: TObject);
    procedure Exit1Click(Sender: TObject);
    procedure About1Click(Sender: TObject);
    procedure ParentButtonClick(Sender: TObject);
    procedure DeleteButtonClick(Sender: TObject);
    procedure NetworkButtonClick(Sender: TObject);
    procedure ShellListViewOperation(Sender: TObject; Operation: TJamShellOperations;
      Files: TStrings; Destination: String);
    procedure ContextMenuSelect(const command: String; var execute: Boolean);
    procedure ShellTreeChange(Sender: TObject; Node: TTreeNode);
    procedure ShellListViewSelectItem(Sender: TObject; Item: TListItem;
      Selected: Boolean);
  private
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation
{$R *.DFM}

// OnClick of the Properties button
procedure TMainForm.PropertiesButtonClick(Sender: TObject);
begin
  if ShellListView.Focused then
    ShellListView.InvokeCommandOnSelected('properties');
  if ShellTree.Focused then
    ShellTree.InvokeCommandOnSelected('properties');
end;

// changes the ViewStyle of the TJamShellList according to the button pressed
procedure TMainForm.LargeIconsButtonClick(Sender: TObject);
begin
  ShellListView.ViewStyle := TViewStyle(Ord(vsIcon) + TComponent(Sender).Tag);
end;

// fully expands the file system structure below the selected folder
procedure TMainForm.FullExpand1Click(Sender: TObject);
begin
  ShellTree.Selected.Expand(True);
end;

// fully collapses the file system structure below the selected node
procedure TMainForm.FullCollapse1Click(Sender: TObject);
begin
  ShellTree.Selected.Collapse(True);
end;

// exit this application
procedure TMainForm.Exit1Click(Sender: TObject);
begin
  Close;
end;

// show about box
procedure TMainForm.About1Click(Sender: TObject);
begin
  ShellAbout(Application.Handle, 'Advanced Sample for ShellBrowser', 'Advanced sample for ShellBrowser'+#10+'More info at: http://www.jam-software.com', Application.Icon.Handle);
end;

// Go up one level in the file system structure
procedure TMainForm.ParentButtonClick(Sender: TObject);
begin
  ShellTree.GoUp;
end;

// Delete the selected object
procedure TMainForm.DeleteButtonClick(Sender: TObject);
begin
  if ShellListView.Focused then
    ShellListView.InvokeCommandOnSelected('delete');
  if ShellTree.Focused then
    ShellTree.InvokeCommandOnSelected('delete');
end;

// shows the system dialog box that allows to connect a network drive
procedure TMainForm.NetworkButtonClick(Sender: TObject);
begin
  ShellTree.ShowNetConnectionDialog;
end;

// sample code of how to track operations the user has performed
procedure TMainForm.ShellListViewOperation(Sender: TObject; Operation: TJamShellOperations;
  Files: TStrings; Destination: String);
var s: String;
    i: Integer;
begin
  exit; // remove this line to test this functionality
  if [sopPaste,sopCopy,sopMove] * Operation <> [] then
  begin
    if sopCopy in Operation then
      s := 'The following files have been copied to '
    else
      s := 'The following files have been moved to ';
    s := s + Destination+' :'#10#13;//linefeed
    for i:=0 to Files.Count-1 do
      s := s + '- ' + Files[i] + #10#13;//linefeed
  end;
  if sopRename in Operation then
    s := 'File ' + Files[0] + ' has been renamed to ' + ExtractFileName(Destination);
  if Length(s)>0 then ShowMessage(s);
end;

// sample of conditional execution of context menu commands
procedure TMainForm.ContextMenuSelect(const command: String; var execute: Boolean);
begin
  exit; // remove this line to test OnContextMenuSelect functionality
  if ShellListView.Focused then
    execute := mrYes = MessageDlg('Exexute command "'+command+'" on object: '+ShellListView.Selected.Caption+'?', mtConfirmation, [mbYes, mbNo], 0)
  else
    execute := mrYes = MessageDlg('Exexute command "'+command+'" on folder: '+ShellTree.GetFullPath(ShellTree.Selected)+'?', mtConfirmation, [mbYes, mbNo], 0);
end;

// OnChaneg event of the TJamShellTree, shows the currently selected path
procedure TMainForm.ShellTreeChange(Sender: TObject; Node: TTreeNode);
begin
  ShellTree.Selected := Node;
  StatusBar.SimpleText := ShellTree.SelectedFolder;
end;

// OnChange event of the TJamShellList, shows the number of currently selected objects
procedure TMainForm.ShellListViewSelectItem(Sender: TObject; Item: TListItem; Selected: Boolean);
begin
  StatusBar.SimpleText := IntToStr(ShellListView.SelectedFiles.Count) + ' item(s) selected.';
end;

end.
