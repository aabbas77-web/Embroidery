unit ucompass;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, VrControls, VrCompass;

type
  TForm2 = class(TForm)
    VrCompass1: TVrCompass;
    ScrollBar1: TScrollBar;
    procedure ScrollBar1Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

{$R *.DFM}

procedure TForm2.ScrollBar1Change(Sender: TObject);
begin
  VrCompass1.Heading := ScrollBar1.Position;
end;

end.
