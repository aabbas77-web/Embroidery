unit uspectrum;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrDesign, VrDeskTop, VrSpectrum, VrBlotter, Menus, VrThreads;

type
  TForm1 = class(TForm)
    VrBlotter1: TVrBlotter;
    VrDeskTop1: TVrDeskTop;
    VrSpectrum1: TVrSpectrum;
    VrTimer1: TVrTimer;
    PopupMenu1: TPopupMenu;
    Exit1: TMenuItem;
    procedure VrTimer1Timer(Sender: TObject);
    procedure Exit1Click(Sender: TObject);
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
var
  I, Value: Integer;
begin
  with VrSpectrum1 do
    for I := 0 to 20 do
    begin
      Value := Random(Max + 1);
      Items[random(VrSpectrum1.Columns)].Position := Value;
    end;
end;

procedure TForm1.Exit1Click(Sender: TObject);
begin
  Application.Terminate;
end;

end.
