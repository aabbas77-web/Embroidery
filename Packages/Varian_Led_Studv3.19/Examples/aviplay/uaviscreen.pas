unit uaviscreen;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, VrControls, VrHyperLink;

type
  TForm_AviScreen = class(TForm)
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form_AviScreen: TForm_AviScreen;

implementation

{$R *.DFM}

procedure TForm_AviScreen.FormCreate(Sender: TObject);
begin
  Left := 0;
  Top := 0;
  Width := Screen.Width;
  Height := Screen.Height;
end;

procedure TForm_AviScreen.FormKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = #27 then Close;
end;


end.
