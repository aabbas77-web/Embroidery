unit ubindigits;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Buttons, VrControls, VrDigit;

type
  TForm1 = class(TForm)
    VrDigit1: TVrDigit;
    SpeedButton1: TSpeedButton;
    SpeedButton5: TSpeedButton;
    SpeedButton7: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton6: TSpeedButton;
    SpeedButton4: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton8: TSpeedButton;
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure SpeedButton4Click(Sender: TObject);
    procedure SpeedButton5Click(Sender: TObject);
    procedure SpeedButton6Click(Sender: TObject);
    procedure SpeedButton7Click(Sender: TObject);
    procedure SpeedButton8Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $01;
end;

procedure TForm1.SpeedButton2Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $02;
end;

procedure TForm1.SpeedButton3Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $04;
end;

procedure TForm1.SpeedButton4Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $08;
end;

procedure TForm1.SpeedButton5Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $10;
end;

procedure TForm1.SpeedButton6Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $20;
end;

procedure TForm1.SpeedButton7Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $40;
end;

procedure TForm1.SpeedButton8Click(Sender: TObject);
begin
  VrDigit1.ValueBinary := VrDigit1.ValueBinary xor $80;
end;

end.
