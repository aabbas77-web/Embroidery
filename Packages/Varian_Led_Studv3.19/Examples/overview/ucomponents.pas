unit ucomponents;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls, Buttons, VrClasses, VrGradient,
  VrTypes, VrMatrix, VrBlotter, VrSpectrum, VrLcd, VrLeds, VrScanner,
  VrCalendar, VrAnalog, VrRaster, VrLabel, VrControls, VrSysUtils,
  VrHyperLink, VrBanner, VrDeskTop, VrShadow, VrArrow, VrLights, VrImageLed,
  VrJoypad, VrProgressBar, VrSlider, VrDesign, VrThreads;

type
  TForm1 = class(TForm)
    Panel2: TPanel;
    ColorDialog: TColorDialog;
    VrLabel1: TVrLabel;
    PageControl: TPageControl;
    TabSheet1: TTabSheet;
    VrGradient1: TVrGradient;
    Label1: TLabel;
    VrHyperLink1: TVrHyperLink;
    VrHyperLink2: TVrHyperLink;
    VrHyperLink3: TVrHyperLink;
    TabSheet2: TTabSheet;
    Panel1: TPanel;
    Label2: TLabel;
    VrMatrix1: TVrMatrix;
    VrHyperLink4: TVrHyperLink;
    VrHyperLink5: TVrHyperLink;
    VrHyperLink6: TVrHyperLink;
    VrHyperLink7: TVrHyperLink;
    Label10: TLabel;
    Edit1: TEdit;
    TabSheet3: TTabSheet;
    Panel6: TPanel;
    VrSpectrum1: TVrSpectrum;
    TabSheet9: TTabSheet;
    Panel8: TPanel;
    VrBanner1: TVrBanner;
    VrHyperLink8: TVrHyperLink;
    Label11: TLabel;
    TabSheet4: TTabSheet;
    Panel3: TPanel;
    VrNum1: TVrNum;
    Label3: TLabel;
    VrIndicator1: TVrIndicator;
    TabSheet5: TTabSheet;
    Panel4: TPanel;
    VrCalendar1: TVrCalendar;
    Label5: TLabel;
    TabSheet6: TTabSheet;
    Panel5: TPanel;
    VrAnalogClock1: TVrAnalogClock;
    Label6: TLabel;
    Label7: TLabel;
    VrClock2: TVrClock;
    Label8: TLabel;
    VrClock3: TVrClock;
    Label9: TLabel;
    VrNum2: TVrNum;
    TabSheet7: TTabSheet;
    Panel9: TPanel;
    VrRaster1: TVrRaster;
    BitBtn7: TBitBtn;
    BitBtn8: TBitBtn;
    BitBtn9: TBitBtn;
    TabSheet8: TTabSheet;
    Panel7: TPanel;
    Memo1: TMemo;
    VrDeskTop1: TVrDeskTop;
    VrShadowButton1: TVrShadowButton;
    Button1: TButton;
    VrArrow1: TVrArrow;
    VrArrow2: TVrArrow;
    TabSheet10: TTabSheet;
    Panel10: TPanel;
    VrBlotter1: TVrBlotter;
    VrLed2: TVrLed;
    VrLed3: TVrLed;
    VrLed4: TVrLed;
    VrLed5: TVrLed;
    VrLed6: TVrLed;
    VrLed7: TVrLed;
    VrBlotter2: TVrBlotter;
    VrImageLed1: TVrImageLed;
    VrImageLed2: TVrImageLed;
    Label12: TLabel;
    Label4: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    VrBlotter3: TVrBlotter;
    VrLights3: TVrLights;
    Label13: TLabel;
    Label14: TLabel;
    VrLights4: TVrLights;
    VrLights1: TVrLights;
    VrLights2: TVrLights;
    Label17: TLabel;
    VrBlotter4: TVrBlotter;
    Label18: TLabel;
    VrUserLed1: TVrUserLed;
    VrUserLed2: TVrUserLed;
    VrUserLed3: TVrUserLed;
    VrUserLed4: TVrUserLed;
    VrBlotter5: TVrBlotter;
    VrArrow3: TVrArrow;
    VrJoypad1: TVrJoypad;
    VrArrow4: TVrArrow;
    VrJoypad2: TVrJoypad;
    VrProgressBar1: TVrProgressBar;
    VrProgressBar2: TVrProgressBar;
    VrProgressBar3: TVrProgressBar;
    VrNum3: TVrNum;
    VrClock1: TVrClock;
    VrSlider1: TVrSlider;
    VrSlider2: TVrSlider;
    RasterTimer: TVrTimer;
    SpectrumTimer: TVrTimer;
    procedure FormCreate(Sender: TObject);
    procedure BitBtn5Click(Sender: TObject);
    procedure SpectrumTimerTimer(Sender: TObject);
    procedure BitBtn6Click(Sender: TObject);
    procedure VrCalendar1Click(Sender: TObject);
    procedure VrClock3ClockTick(Sender: TObject; Seconds: Word);
    procedure BitBtn7Click(Sender: TObject);
    procedure BitBtn8Click(Sender: TObject);
    procedure BitBtn9Click(Sender: TObject);
    procedure RasterTimerTimer(Sender: TObject);
    procedure Memo1Enter(Sender: TObject);
    procedure VrHyperLink1Click(Sender: TObject);
    procedure VrHyperLink2Click(Sender: TObject);
    procedure VrHyperLink3Click(Sender: TObject);
    procedure VrHyperLink7Click(Sender: TObject);
    procedure VrHyperLink4Click(Sender: TObject);
    procedure VrMatrix1ScrollDone(Sender: TObject);
    procedure VrHyperLink8Click(Sender: TObject);
    procedure PageControlChange(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure VrArrow2Click(Sender: TObject);
    procedure VrSlider1Change(Sender: TObject);
    procedure VrSlider2Change(Sender: TObject);
    procedure VrClock3SecondsChanged(Sender: TObject; Seconds: Word);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

const
  MatrixText = 'Varian Led Studio...presents a new feature...'+
    '%16multi-colored %15text support %14for %13more %12flexibility...';

  StopRun: array[Boolean] of string = ('START', 'STOP');


procedure TForm1.FormCreate(Sender: TObject);
begin
  PageControl.ActivePage := TabSheet1;

  Caption := Format('%s, %s',
    [Application.Title, '(c) 1996-1999 Varian Software nl']);
  VrMatrix1.Text := MatrixText;
end;

procedure TForm1.BitBtn5Click(Sender: TObject);
begin
  VrSpectrum1.Reset(0);
  SpectrumTimer.Enabled := not SpectrumTimer.Enabled;
  VrShadowButton1.Caption := StopRun[SpectrumTimer.Enabled];
end;

procedure TForm1.SpectrumTimerTimer(Sender: TObject);
var
  I, Value: Integer;
begin
  with VrSpectrum1 do
    for I := 0 to Pred(Count) do
    begin
      Value := Random(Max + 1);
      Items[I].Position := Value;
    end;
end;

procedure TForm1.BitBtn6Click(Sender: TObject);
begin
  if coTrackMouse in VrCalendar1.Options then
    VrCalendar1.Options := VrCalendar1.Options - [coTrackMouse]
  else VrCalendar1.Options := VrCalendar1.Options + [coTrackMouse];
end;

procedure TForm1.VrCalendar1Click(Sender: TObject);
begin
  with VrCalendar1 do
    if ItemIndex <> -1 then
      Items[ItemIndex].Active := True;
end;

procedure TForm1.VrClock3ClockTick(Sender: TObject; Seconds: Word);
begin
  VrNum2.Value := VrClock3.Seconds;
end;

procedure TForm1.BitBtn7Click(Sender: TObject);
begin
  RasterTimer.Enabled := true;
end;

procedure TForm1.BitBtn8Click(Sender: TObject);
var
  I: Integer;
begin
  RasterTimer.Enabled := false;
  with VrRaster1 do
    for I := 0 to Pred(Count) do
      Items[I].Active := false;
end;

procedure TForm1.BitBtn9Click(Sender: TObject);
begin
  VrRaster1.MultiSelect := not VrRaster1.MultiSelect;
end;

procedure TForm1.RasterTimerTimer(Sender: TObject);
var
  I: Integer;
begin
  with VrRaster1 do
  begin
    I := Random(Count);
    if MultiSelect then
      Items[I].Active := not Items[I].Active
    else
      Items[I].Active := true;
  end;
end;

procedure TForm1.Memo1Enter(Sender: TObject);
begin
  TabSheet8.SetFocus;
end;

procedure TForm1.VrHyperLink1Click(Sender: TObject);
begin
  Colordialog.Color := VrGradient1.StartColor;
  if Colordialog.Execute then
     VrGradient1.StartColor := ColorDialog.Color;
end;

procedure TForm1.VrHyperLink2Click(Sender: TObject);
begin
  Colordialog.Color := VrGradient1.EndColor;
  if Colordialog.Execute then
    VrGradient1.EndColor := ColorDialog.Color;
end;

procedure TForm1.VrHyperLink3Click(Sender: TObject);
begin
  if VrGradient1.Orientation = voVertical then
    VrGradient1.Orientation := voHorizontal
  else VrGradient1.Orientation := voVertical;
end;

procedure TForm1.VrHyperLink7Click(Sender: TObject);
begin
  VrMatrix1.LedStyle := TVrMatrixLedStyle(TControl(Sender).Tag);
end;

procedure TForm1.VrHyperLink4Click(Sender: TObject);
begin
  VrMatrix1.AutoScroll := not VrMatrix1.AutoScroll;
  VrHyperLink4.Caption := StopRun[VrMatrix1.AutoScroll];
end;

procedure TForm1.VrMatrix1ScrollDone(Sender: TObject);
begin
  if Edit1.Text <> '' then
    VrMatrix1.Text := Edit1.Text;
end;

procedure TForm1.VrHyperLink8Click(Sender: TObject);
begin
  VrBanner1.AutoScroll := not VrBanner1.AutoScroll;
  VrHyperLink8.Caption := StopRun[VrBanner1.AutoScroll];
end;

procedure TForm1.PageControlChange(Sender: TObject);
begin
  if VrBanner1.AutoScroll then VrHyperLink8Click(nil);
  if RasterTimer.Enabled then BitBtn8Click(BitBtn8);
  if SpectrumTimer.Enabled then BitBtn5Click(nil);
  if VrMatrix1.AutoScroll then VrHyperLink4Click(nil);
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  VrCalendar1.Reset;
end;

procedure TForm1.VrArrow2Click(Sender: TObject);
begin
  VrArrow1.Active := false;
  VrArrow2.Active := false;
  case TComponent(Sender).Tag of
    0: begin
         VrBanner1.Direction := bdRightToLeft;
         VrArrow2.Active := True;
       end;
    1: begin
         VrBanner1.Direction := bdLeftToRight;
         VrArrow1.Active := True;
       end;
  end;
end;

procedure TForm1.VrSlider1Change(Sender: TObject);
begin
  VrNum1.Value := VrSlider1.Position;
  VrProgressBar1.Position := VrSlider1.Position;
  VrProgressBar2.Position := VrSlider1.Position;
  VrProgressBar3.Position := VrSlider1.Position;
end;

procedure TForm1.VrSlider2Change(Sender: TObject);
begin
  VrNum3.Value := VrSlider2.Position;
  VrIndicator1.Position := VrSlider2.Position;
end;

procedure TForm1.VrClock3SecondsChanged(Sender: TObject; Seconds: Word);
begin
  VrNum2.Value := Seconds;
end;

end.
