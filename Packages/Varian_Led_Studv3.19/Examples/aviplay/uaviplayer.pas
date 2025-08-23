unit uaviplayer;

interface

{ This program only provides an example of how to use some of the
  Varian Led Studio components.

  It is not intended to be a fully functional avi player.}

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrShadow, VrBlotter, VrControls, VrProgressBar, MPlayer, VrNavigator,
  ExtCtrls, VrDeskTop, VrLcd, VrLabel;

type
  TForm_AviPlayer = class(TForm)
    MediaPlayer1: TMediaPlayer;
    VrNavigator1: TVrNavigator;
    VrBlotter1: TVrBlotter;
    OpenDialog: TOpenDialog;
    VrDeskTop1: TVrDeskTop;
    Panel1: TPanel;
    VrShadowButton1: TVrShadowButton;
    VrShadowButton2: TVrShadowButton;
    VrShadowButton3: TVrShadowButton;
    VrLabel1: TVrLabel;
    VrLabel2: TVrLabel;
    procedure VrShadowButton1Click(Sender: TObject);
    procedure VrNavigator1ButtonClick(Sender: TObject;
      Button: TVrButtonType);
    procedure FormDestroy(Sender: TObject);
    procedure VrShadowButton3Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure VrShadowButton2Click(Sender: TObject);
  private
    procedure FormClosed(Sender: TObject; var Action: TCloseAction);
  public
    { Public declarations }
  end;

var
  Form_AviPlayer: TForm_AviPlayer;

implementation

uses uaviscreen;

{$R *.DFM}

procedure TForm_AviPlayer.FormCreate(Sender: TObject);
begin
  Caption := Application.Title;
  Icon.Assign(Application.Icon);
end;

procedure TForm_AviPlayer.VrShadowButton1Click(Sender: TObject);
begin
  if OpenDialog.Execute then
  begin
    Application.ProcessMessages;
    try
      VrNavigator1.EnabledButtons := [];
      VrShadowButton2.Enabled := False;
      MediaPlayer1.Display := Panel1;
      MediaPlayer1.DisplayRect := Panel1.ClientRect;
      MediaPlayer1.FileName := OpenDialog.FileName;
      MediaPlayer1.Open;
      MediaPlayer1.Play;
      MediaPlayer1.Stop;
      VrNavigator1.EnabledButtons := [btPlay, btStop, btPause, btBack, btStep];
      VrShadowButton2.Enabled := True;
      Caption := Application.Title +
        Format(' - [%s]', [ExtractFileName(OpenDialog.FileName)]);
    except
      raise Exception.Create('Error loading requested avi file');
    end;
  end;
end;

procedure TForm_AviPlayer.VrNavigator1ButtonClick(Sender: TObject;
  Button: TVrButtonType);
begin
  try
    case Button of
      btPlay: MediaPlayer1.Play;
      btStop: begin
                MediaPlayer1.Previous;
                MediaPlayer1.Stop;
              end;
      btPause: MediaPlayer1.Pause;
      btBack: begin
                MediaPlayer1.Back;
                MediaPlayer1.Play;
              end;
      btStep: begin
                MediaPlayer1.Step;
                MediaPlayer1.Play;
              end;
    end;
  except end;
end;

procedure TForm_AviPlayer.FormDestroy(Sender: TObject);
begin
  try
    MediaPlayer1.Close;
  except end;
end;

procedure TForm_AviPlayer.VrShadowButton3Click(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TForm_AviPlayer.VrShadowButton2Click(Sender: TObject);
begin
  Visible := false;
  Form_AviScreen.OnClose := FormClosed;
  MediaPlayer1.Display := Form_AviScreen;
  MediaPlayer1.DisplayRect := Form_AviScreen.ClientRect;
  Form_AviScreen.Show;
end;

procedure TForm_AviPlayer.FormClosed(Sender: TObject; var Action: TCloseAction);
begin
  MediaPlayer1.Display := Panel1;
  MediaPlayer1.DisplayRect := Panel1.ClientRect;
  Visible := True;
end;


end.
