unit uanimate;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrAnimate, StdCtrls, VrDeskTop, VrShadow, VrBorder, VrLabel,
  VrCheckLed;

type
  TForm1 = class(TForm)
    VrAnimate1: TVrAnimate;
    VrDeskTop1: TVrDeskTop;
    VrShadowButton1: TVrShadowButton;
    VrCheckLed1: TVrCheckLed;
    VrLabel1: TVrLabel;
    VrLabel2: TVrLabel;
    VrCheckLed2: TVrCheckLed;
    VrCheckLed3: TVrCheckLed;
    VrLabel3: TVrLabel;
    VrLabel4: TVrLabel;
    VrShadowButton2: TVrShadowButton;
    procedure Button1Click(Sender: TObject);
    procedure VrAnimate1Notify(Sender: TObject);
    procedure VrCheckLed1Change(Sender: TObject);
    procedure VrCheckLed2Change(Sender: TObject);
    procedure VrCheckLed3Change(Sender: TObject);
    procedure VrShadowButton2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.Button1Click(Sender: TObject);
begin
  VrShadowButton1.Enabled := false;
  VrAnimate1.Active := True;
end;

procedure TForm1.VrAnimate1Notify(Sender: TObject);
begin
  VrShadowButton1.Enabled := True;
end;

procedure TForm1.VrCheckLed1Change(Sender: TObject);
begin
  VrAnimate1.Loop := VrCheckLed1.Checked;
end;

procedure TForm1.VrCheckLed2Change(Sender: TObject);
begin
  VrAnimate1.Stretch := VrCheckLed2.Checked;
end;

procedure TForm1.VrCheckLed3Change(Sender: TObject);
begin
  VrAnimate1.Transparent := VrCheckLed3.Checked;
end;

procedure TForm1.VrShadowButton2Click(Sender: TObject);
begin
  VrAnimate1.CurrentFrame := 0;
end;

end.
