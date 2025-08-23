unit umatrix;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrMatrix, VrSwitch, VrBorder;

type
  TForm1 = class(TForm)
    VrMatrix1: TVrMatrix;
    VrMatrix2: TVrMatrix;
    VrMatrix4: TVrMatrix;
    VrSwitch1: TVrSwitch;
    VrMatrix3: TVrMatrix;
    VrSwitch2: TVrSwitch;
    VrBorder1: TVrBorder;
    procedure VrSwitch1Change(Sender: TObject);
    procedure VrSwitch2Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.VrSwitch1Change(Sender: TObject);
begin
  case VrSwitch1.Offset of
    0: VrMatrix4.Text := '%1trackmode: %12enabled';
    1: VrMatrix4.Text := '%1trackmode: %12disabled';
  end;
end;

procedure TForm1.VrSwitch2Change(Sender: TObject);
begin
  case VrSwitch2.Offset of
    0: VrMatrix3.Text := '%1explorer : %12enabled';
    1: VrMatrix3.Text := '%1explorer : %12disabled';
  end;
end;

end.
