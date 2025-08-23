unit uledstyles;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrJoypad, VrArrow, VrLeds, VrLights, VrImageLed, StdCtrls, VrControls,
  VrBlotter, ExtCtrls;

type
  TForm1 = class(TForm)
    Panel10: TPanel;
    VrBlotter1: TVrBlotter;
    VrLed2: TVrLed;
    VrLed3: TVrLed;
    VrLed4: TVrLed;
    VrLed5: TVrLed;
    VrLed6: TVrLed;
    VrLed7: TVrLed;
    Label16: TLabel;
    VrBlotter2: TVrBlotter;
    VrImageLed1: TVrImageLed;
    VrImageLed2: TVrImageLed;
    Label12: TLabel;
    Label4: TLabel;
    Label15: TLabel;
    VrBlotter3: TVrBlotter;
    VrLights2: TVrLights;
    VrLights1: TVrLights;
    VrLights3: TVrLights;
    Label13: TLabel;
    Label14: TLabel;
    VrLights4: TVrLights;
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
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

end.
