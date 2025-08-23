program Easy;

uses 
  Forms,
  SimpleForm in 'SimpleForm.pas' {MainForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
