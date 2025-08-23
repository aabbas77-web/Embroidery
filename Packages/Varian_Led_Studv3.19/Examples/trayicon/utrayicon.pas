unit utrayicon;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrSystem, ComCtrls, StdCtrls, VrBorder, Menus;

type
  TForm1 = class(TForm)
    StatusBar1: TStatusBar;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    VrBorder1: TVrBorder;
    PopupMenu1: TPopupMenu;
    pmExit: TMenuItem;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    pmShowApplication: TMenuItem;
    N1: TMenuItem;
    pmHideApplication: TMenuItem;
    CheckBox5: TCheckBox;
    VrTrayIcon1: TVrTrayIcon;
    procedure VrTrayIcon21MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure CheckBox1Click(Sender: TObject);
    procedure CheckBox2Click(Sender: TObject);
    procedure pmExitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure CheckBox3Click(Sender: TObject);
    procedure CheckBox4Click(Sender: TObject);
    procedure VrTrayIcon21Click(Sender: TObject);
    procedure VrTrayIcon21DblClick(Sender: TObject);
    procedure pmShowApplicationClick(Sender: TObject);
    procedure pmHideApplicationClick(Sender: TObject);
    procedure CheckBox5Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.FormCreate(Sender: TObject);
begin
  VrTrayIcon1.Hint := Application.Title;
end;

procedure TForm1.VrTrayIcon21MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  StatusBar1.Panels[0].Text := Format('X=%d, Y=%d', [X, Y]);
end;

procedure TForm1.pmExitClick(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TForm1.CheckBox1Click(Sender: TObject);
begin
  VrTrayIcon1.Enabled := CheckBox1.Checked;
end;

procedure TForm1.CheckBox2Click(Sender: TObject);
begin
  VrTrayIcon1.Visible := CheckBox2.Checked;
end;

procedure TForm1.CheckBox3Click(Sender: TObject);
begin
  VrTrayIcon1.ShowHint := CheckBox3.Checked;
end;

procedure TForm1.CheckBox4Click(Sender: TObject);
begin
  VrTrayIcon1.LeftBtnPopup := CheckBox4.Checked;
end;

procedure TForm1.VrTrayIcon21Click(Sender: TObject);
begin
  StatusBar1.Panels[1].Text := 'Click';
end;

procedure TForm1.VrTrayIcon21DblClick(Sender: TObject);
begin
  StatusBar1.Panels[1].Text := 'Double Click';
end;

procedure TForm1.pmShowApplicationClick(Sender: TObject);
begin
  VrTrayIcon1.ShowMainForm;
end;

procedure TForm1.pmHideApplicationClick(Sender: TObject);
begin
  VrTrayIcon1.HideMainForm;
end;

procedure TForm1.CheckBox5Click(Sender: TObject);
begin
  VrTrayIcon1.HideTaskBtn := CheckBox5.Checked;
end;

end.
