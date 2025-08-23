unit uscope;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, VrClasses, VrScope, StdCtrls, ComCtrls, VrScale, VrBorder,
  VrControls, VrDesign, VrShadow, VrLeds, VrBlotter, VrLcd, VrThreads;

type
  TForm1 = class(TForm)
    VrTimer1: TVrTimer;
    VrBlotter1: TVrBlotter;
    VrUserLed1: TVrUserLed;
    VrBlotter2: TVrBlotter;
    VrShadowButton1: TVrShadowButton;
    VrShadowButton2: TVrShadowButton;
    Label3: TLabel;
    UpDown3: TUpDown;
    Label1: TLabel;
    UpDown1: TUpDown;
    Label2: TLabel;
    UpDown2: TUpDown;
    VrBlotter3: TVrBlotter;
    VrScope1: TVrScope;
    VrScale1: TVrScale;
    VrNum1: TVrNum;
    VrNum2: TVrNum;
    VrNum3: TVrNum;
    VrNum4: TVrNum;
    procedure Button1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure UpDown3Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown1Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown2Click(Sender: TObject; Button: TUDBtnType);
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
const
  PS: array[boolean] of PChar = ('START', 'STOP');
begin
  VrTimer1.Enabled := not VrTimer1.Enabled;
  VrUserLed1.Active := VrTimer1.Enabled;
  VrShadowButton1.Caption := PS[VrTimer1.Enabled];
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
  Value: Integer;
begin
  Value := Random(VrScope1.Max);
  VrScope1.AddValue(Value);
  VrNum1.Value := Value;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  VrScope1.Clear;
end;

procedure TForm1.UpDown3Click(Sender: TObject; Button: TUDBtnType);
begin
  VrNum2.Value := UpDown3.Position;
  VrTimer1.Interval := VrNum2.Value;
end;

procedure TForm1.UpDown1Click(Sender: TObject; Button: TUDBtnType);
begin
  VrNum3.Value := UpDown1.Position;
  VrScope1.GridSize := VrNum3.Value;
end;

procedure TForm1.UpDown2Click(Sender: TObject; Button: TUDBtnType);
begin
  VrNum4.Value := UpDown2.Position;
  VrScope1.Frequency := VrNum4.Value;
end;

end.
