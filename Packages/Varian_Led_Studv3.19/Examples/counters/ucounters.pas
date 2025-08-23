unit ucounters;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrDesign, VrSystem, VrBlotter, VrThreads;

type
  TForm1 = class(TForm)
    VrBlotter1: TVrBlotter;
    VrCounter1: TVrCounter;
    VrCounter3: TVrCounter;
    VrTimer1: TVrTimer;
    VrTimer2: TVrTimer;
    procedure VrTimer1Timer(Sender: TObject);
    procedure VrTimer2Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.VrTimer1Timer(Sender: TObject);
begin
  VrCounter1.Value := VrCounter1.Value + 1;
end;

procedure TForm1.VrTimer2Timer(Sender: TObject);
begin
  VrCounter3.Value := VrCounter3.Value - 1;
end;

end.
