program bgradient;

uses
  Forms,
  ubgradient in 'ubgradient.pas' {Form1};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'VrGradient Demo';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
