program animate;

uses
  Forms,
  uanimate in 'uanimate.pas' {Form1};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
