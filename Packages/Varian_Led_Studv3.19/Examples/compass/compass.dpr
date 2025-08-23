program compass;

uses
  Forms,
  ucompass in 'ucompass.pas' {Form2};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm2, Form2);
  Application.Run;
end.
