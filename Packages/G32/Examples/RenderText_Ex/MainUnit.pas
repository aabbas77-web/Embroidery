unit MainUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, G32_Image, ComCtrls;

type
  TForm1 = class(TForm)
    Image: TImage32;
    Panel1: TPanel;
    Edit1: TEdit;
    Edit2: TEdit;
    AALevel: TUpDown;
    Label1: TLabel;
    procedure Edit1Change(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ImageResize(Sender: TObject);
    procedure AALevelClick(Sender: TObject; Button: TUDBtnType);
  public
    procedure Draw;
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.Draw;
begin
  Image.Bitmap.Clear;
  Image.Bitmap.RenderText(10, 10, Edit1.Text, AALevel.Position, $FFFFFFFF);
end;

procedure TForm1.Edit1Change(Sender: TObject);
begin
  Draw;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  Image.SetupBitmap;
  with Image.Bitmap.Font do
  begin
    Name := 'Tahoma';
    Size := 20;
    Style := [fsBold, fsItalic];
  end;
end;

procedure TForm1.ImageResize(Sender: TObject);
begin
  Image.SetupBitmap;
  Draw;
end;

procedure TForm1.AALevelClick(Sender: TObject; Button: TUDBtnType);
begin
  Draw;
end;

end.
