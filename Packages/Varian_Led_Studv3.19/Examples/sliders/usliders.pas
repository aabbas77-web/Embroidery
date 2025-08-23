unit usliders;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrSlider, VrProgressBar, VrScanner, StdCtrls, VrLcd, ExtCtrls;

type
  TForm1 = class(TForm)
    VrNum1: TVrNum;
    VrIndicator1: TVrIndicator;
    VrProgressBar1: TVrProgressBar;
    VrProgressBar2: TVrProgressBar;
    VrProgressBar3: TVrProgressBar;
    VrNum3: TVrNum;
    VrSlider1: TVrSlider;
    VrSlider2: TVrSlider;
    procedure VrSlider1Change(Sender: TObject);
    procedure VrSlider2Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.VrSlider1Change(Sender: TObject);
begin
  VrNum1.Value := VrSlider1.Position;
  VrProgressBar1.Position := VrSlider1.Position;
  VrProgressBar2.Position := VrSlider1.Position;
  VrProgressBar3.Position := VrSlider1.Position;
end;

procedure TForm1.VrSlider2Change(Sender: TObject);
begin
  VrNum3.Value := VrSlider2.Position;
  VrIndicator1.Position := VrSlider2.Position;
end;

end.
