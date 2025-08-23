program Easy;

uses 
  ExceptionLog,
  Forms,
  SimpleForm in 'SimpleForm.pas' {MainForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
