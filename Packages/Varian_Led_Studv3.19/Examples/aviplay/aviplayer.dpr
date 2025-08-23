program aviplayer;

uses
  Forms,
  uaviplayer in 'uaviplayer.pas' {Form_AviPlayer},
  uaviscreen in 'uaviscreen.pas' {Form_AviScreen};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'Varian AVI Player';
  Application.CreateForm(TForm_AviPlayer, Form_AviPlayer);
  Application.CreateForm(TForm_AviScreen, Form_AviScreen);
  Application.Run;
end.
