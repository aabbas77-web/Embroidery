unit ubgradient;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, ComCtrls, VrTypes, VrClasses, VrControls, VrSysUtils,
  VrGradient, VrHyperLink, VrBlotter, VrLcd;

type
  TForm1 = class(TForm)
    VrGradient1: TVrGradient;
    ColorDialog1: TColorDialog;
    VrBlotter1: TVrBlotter;
    VrHyperLink1: TVrHyperLink;
    VrHyperLink2: TVrHyperLink;
    VrHyperLink3: TVrHyperLink;
    VrNum1: TVrNum;
    VrHyperLink4: TVrHyperLink;
    UpDown2: TUpDown;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure VrHyperLink3Click(Sender: TObject);
    procedure UpDown2Click(Sender: TObject; Button: TUDBtnType);
  private
    procedure WMEraseBkgnd(var Message: TWMEraseBkgnd); message WM_ERASEBKGND;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.FormCreate(Sender: TObject);
begin
  Caption := Application.Title;
end;

procedure TForm1.WMEraseBkgnd(var Message: TWMEraseBkgnd);
begin
  Message.Result := LRESULT(False);
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  ColorDialog1.Color := VrGradient1.StartColor;
  if ColorDialog1.Execute then
    VrGradient1.StartColor := ColorDialog1.Color;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  ColorDialog1.Color := VrGradient1.EndColor;
  if ColorDialog1.Execute then
    VrGradient1.EndColor := ColorDialog1.Color;
end;

procedure TForm1.VrHyperLink3Click(Sender: TObject);
begin
  if VrGradient1.Orientation = voVertical then
    VrGradient1.Orientation := voHorizontal
  else VrGradient1.Orientation := voVertical;
end;

procedure TForm1.UpDown2Click(Sender: TObject; Button: TUDBtnType);
begin
  VrNum1.Value := UpDown2.Position;
  VrGradient1.ColorWidth := VrNum1.Value;
end;

end.
