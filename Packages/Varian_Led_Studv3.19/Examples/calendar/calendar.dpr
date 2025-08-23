program calendar;

uses
  Forms,
  ucalendar in 'ucalendar.pas' {Form1};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'VrCalendar Owner Draw Demo';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
