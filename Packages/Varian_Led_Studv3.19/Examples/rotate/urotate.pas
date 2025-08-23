unit urotate;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrSpinner, VrControls, VrLabel, VrSysUtils, VrBlotter;

type
  TForm1 = class(TForm)
    VrSpinner1: TVrSpinner;
    VrBlotter1: TVrBlotter;
    VrLabel1: TVrLabel;
    procedure VrSpinner1UpClick(Sender: TObject);
    procedure VrSpinner1DownClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.VrSpinner1UpClick(Sender: TObject);
begin
  VrLabel1.Angle := MinIntVal(VrLabel1.Angle + 10, 359);
end;

procedure TForm1.VrSpinner1DownClick(Sender: TObject);
begin
  VrLabel1.Angle := MaxIntVal(0, VrLabel1.Angle - 10);
end;

end.
