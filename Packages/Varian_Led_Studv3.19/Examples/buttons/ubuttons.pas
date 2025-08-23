unit ubuttons;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrDesign, VrGradient, VrDeskTop;

type
  TForm1 = class(TForm)
    VrBitmapButton1: TVrBitmapButton;
    VrBitmapButton2: TVrBitmapButton;
    VrBitmapButton3: TVrBitmapButton;
    VrBitmapButton4: TVrBitmapButton;
    VrDeskTop1: TVrDeskTop;
    VrBitmapButton5: TVrBitmapButton;
    procedure VrBitmapButton5Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.VrBitmapButton5Click(Sender: TObject);
begin
  Application.Terminate;
end;

end.
