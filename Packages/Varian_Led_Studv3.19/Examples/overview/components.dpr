program components;

uses
  Forms,
  ucomponents in 'ucomponents.pas' {Form1};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'Varian Led studio';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
