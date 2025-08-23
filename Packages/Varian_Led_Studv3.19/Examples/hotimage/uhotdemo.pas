unit uhotdemo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrControls, VrHotImage, VrBlotter, VrConst;

type
  TForm1 = class(TForm)
    VrBlotter1: TVrBlotter;
    VrHotImage1: TVrHotImage;
    VrHotImage2: TVrHotImage;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.FormCreate(Sender: TObject);
begin
  VrHotImage1.Cursor := VrCursorHandPoint;
  VrHotImage2.Cursor := VrCursorHandPoint;
end;

end.
