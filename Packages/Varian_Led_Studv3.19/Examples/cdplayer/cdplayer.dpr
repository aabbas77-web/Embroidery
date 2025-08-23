program cdplayer;

uses
  Forms,
  ucdplayer in 'ucdplayer.pas' {Form1};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'VSS CD';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
