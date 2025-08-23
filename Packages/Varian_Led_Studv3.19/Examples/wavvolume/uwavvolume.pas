unit uwavvolume;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ToolWin, ComCtrls, MMSystem, VrControls, VrJoypad, VrLcd,
  VrHyperLink, VrBlotter, VrShadow, VrSlider, VrLevelBar, VrTrackBar;

type
  TForm1 = class(TForm)
    VrBlotter1: TVrBlotter;
    VrJoypad1: TVrJoypad;
    VrNum1: TVrNum;
    VrTrackBar1: TVrTrackBar;
    VrLevelBar1: TVrLevelBar;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure VrShadowButton1Click(Sender: TObject);
    procedure VrSlider1Change(Sender: TObject);
  private
    PrevPos: dWord;
    pCurrentVolumeLevel: PDWord;
    CurrentVolumeLevel: DWord;
    VolumeControlHandle: hWnd;
    function GetTrackBarPos: Integer;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.FormCreate(Sender: TObject);
begin
  New(pCurrentVolumeLevel);
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  Dispose(pCurrentVolumeLevel);
end;

function TForm1.GetTrackBarPos: integer;
begin
  Result := 65535 div VrTrackBar1.Max;
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  VolumeControlHandle := FindWindow('Volume Control', nil);
  WaveOutGetVolume(VolumeControlHandle, pCurrentVolumeLevel);
  CurrentVolumeLevel := pCurrentVolumeLevel^;
  VrTrackBar1.Position := LoWord(CurrentVolumeLevel) div GetTrackBarPos;
end;

procedure TForm1.VrShadowButton1Click(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TForm1.VrSlider1Change(Sender: TObject);
begin
  CurrentVolumeLevel := VrTrackBar1.Position * GetTrackBarPos shl 16;
  CurrentVolumeLevel := CurrentVolumeLevel + dword(VrTrackBar1.Position * GetTrackBarPos);
  if WaveOutSetVolume(VolumeControlHandle, CurrentVolumeLevel) <> 0 then
    raise Exception.Create('Cannot adjust Volume.');
  VrNum1.Value := VrTrackBar1.Position;
  VrLevelBar1.Position := VrTrackBar1.Position;
  if CurrentVolumeLevel <> PrevPos then
  begin
    if CurrentVolumeLevel > PrevPos then
      VrJoyPad1.Direction := jdUp
    else VrJoyPad1.Direction := jdDown;
    PrevPos := CurrentVolumeLevel;
  end;
end;

end.
