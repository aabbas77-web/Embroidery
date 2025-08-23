unit ucdplayer;

interface

{ This program only provides an example of how to use some of the
  Varian Led Studio components.

  It is not intended to be a fully functional cd player.

  Correct drive letter in the Mediaplayer component to point
  to your cd-rom player device.}


uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  MPlayer, MMSystem, VrBlotter, VrClasses, VrGradient, VrNavigator, ExtCtrls,
  VrLeds, VrLabel, VrLcd, StdCtrls, VrGauge, VrImageLed, VrControls,
  VrDesign, VrThreads;

type
  TForm1 = class(TForm)
    MediaPlayer: TMediaPlayer;
    VrBlotter1: TVrBlotter;
    VrGradient: TVrGradient;
    VrNavigator: TVrNavigator;
    VrBlotter: TVrBlotter;
    VrLed: TVrLed;
    VrLabel1: TVrLabel;
    Label5: TLabel;
    VrNumTotalTracks: TVrNum;
    Label6: TLabel;
    VrClockDiskTime: TVrClock;
    Label7: TLabel;
    VrCurTrack: TVrNum;
    Label3: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label4: TLabel;
    VrGauge: TVrGauge;
    VrImageLed: TVrImageLed;
    VrClockCurTrackTime: TVrClock;
    VrClockTotalTrackTime: TVrClock;
    VrTimer: TVrTimer;
    VrLabel2: TVrLabel;
    procedure TimerTimer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure MediaPlayerNotify(Sender: TObject);
    procedure VrNavigatorButtonClick(Sender: TObject;
      ButtonType: TVrButtonType);
    procedure FormDestroy(Sender: TObject);
  private
    FOpen: Boolean;
    procedure OpenAudioDevice;
    procedure CheckDisk;
    procedure CheckPosition;
    procedure ResetControls;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

const
  Modes: array[TMPModes] of PChar = ('NOT READY', 'STOPPED', 'PLAYING',
    'RECORDING', 'SEEKING', 'PAUSED', 'OPEN');


{$R *.DFM}

procedure TForm1.FormCreate(Sender: TObject);
begin
  Left := 50;
  Top := 50;
  MediaPlayer.TimeFormat := tfTMSF;
  MediaPlayer.Notify := True;
  MediaPlayer.Wait := False;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  try
    MediaPlayer.Stop;
    MediaPlayer.Close;
  except
  end;
end;

procedure TForm1.OpenAudioDevice;
begin
  try
    MediaPlayer.Close;
    MediaPlayer.Open;
    FOpen := true;
  except
    FOpen := false;
  end;
  VrLed.Active := FOpen;
end;

procedure TForm1.TimerTimer(Sender: TObject);
begin
  if not FOpen then
    OpenAudioDevice
  else
  if MediaPlayer.Mode = mpPlaying then
    CheckPosition;
  MediaPlayerNotify(MediaPlayer);
end;

procedure TForm1.MediaPlayerNotify(Sender: TObject);
begin
  VrLabel1.Caption := Modes[MediaPlayer.Mode];
    case MediaPlayer.Mode of
    mpNotReady:;
    mpStopped:
      begin
        CheckDisk;
        VrImageLed.Active := False;
      end;
    mpPlaying:
      begin
        CheckDisk;
        VrImageLed.Active := True;
      end;
    mpSeeking:;
    mpPaused:;
    mpOpen: ResetControls;
  end;
end;

procedure TForm1.VrNavigatorButtonClick(Sender: TObject;
  ButtonType: TVrButtonType);
begin
  try
    case ButtonType of
      btPower: Application.Terminate;
      btPlay: MediaPlayer.Play;
      btStop: MediaPlayer.Stop;
      btPause: MediaPlayer.Pause;
      btNext: MediaPlayer.Next;
      btPrev: MediaPlayer.Previous;
      btEject: MediaPlayer.Eject;
    end;
    MediaPlayerNotify(MediaPlayer);
  except
  end;
end;

procedure TForm1.CheckDisk;
var
  NTracks, NLen: Integer;
begin
  NTracks := MediaPlayer.Tracks;
  NLen := MediaPlayer.Length;
  VrNumTotalTracks.Value := NTracks;
  VrClockDiskTime.Hours := MCI_MSF_MINUTE(NLen);
  VrClockDiskTime.Minutes := MCI_MSF_SECOND(NLen);
end;

procedure TForm1.CheckPosition;
var
  CurrentTrack, CurrentPos, TrackLen: Integer;
  Mt, Pt, M, S: Integer;
begin
  CurrentPos := MediaPlayer.Position;
  VrClockCurTrackTime.Hours := MCI_TMSF_MINUTE(CurrentPos);
  VrClockCurTrackTime.Minutes := MCI_TMSF_SECOND(CurrentPos);

  CurrentTrack := MCI_TMSF_TRACK (CurrentPos);
  VrCurTrack.Value := CurrentTrack;

  TrackLen := MediaPlayer.TrackLength [CurrentTrack];
  VrClockTotalTrackTime.Hours := MCI_MSF_MINUTE(TrackLen);
  VrClockTotalTrackTime.Minutes := MCI_MSF_SECOND(TrackLen);

  Application.ProcessMessages;

  M := MCI_MSF_MINUTE(TrackLen);
  S :=  MCI_MSF_SECOND(TrackLen);
  Mt := (M * 60) + S;

  M := MCI_TMSF_MINUTE(CurrentPos);
  S := MCI_TMSF_SECOND(CurrentPos);
  Pt := (M * 60) + S;

  VrGauge.Max := Mt;
  VrGauge.Position := Pt;
end;

procedure TForm1.ResetControls;
begin
  VrNumTotalTracks.Value := 0;
  VrClockDiskTime.Hours := 0;
  VrClockDiskTime.Minutes := 0;
  VrClockCurTrackTime.Hours := 0;
  VrClockCurTrackTime.Minutes := 0;
  VrCurTrack.Value := 0;
  VrClockTotalTrackTime.Hours := 0;
  VrClockTotalTrackTime.Minutes := 0;
  VrGauge.Position := 0;
end;


end.
