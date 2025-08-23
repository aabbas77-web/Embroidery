unit ucalendar;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, VrCalendar, VrControls, VrSysUtils, ImgList;

type
  TForm1 = class(TForm)
    VrCalendar1: TVrCalendar;
    VrCalendar2: TVrCalendar;
    ImageList1: TImageList;
    procedure FormCreate(Sender: TObject);
    procedure VrCalendar2Draw(Sender: TObject; Canvas: TCanvas;
      Rect: TRect; Index: Integer; State: Boolean);
  private
    { Private declarations }
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

procedure TForm1.VrCalendar2Draw(Sender: TObject; Canvas: TCanvas;
  Rect: TRect; Index: Integer; State: Boolean);
var
  X, Y: Integer;
begin
  Canvas.Brush.Color := clBlack;
  Canvas.FillRect(Rect);
  X := Rect.Left + (WidthOf(Rect) - ImageList1.Width) div 2;
  Y := Rect.Top + (HeightOf(Rect) - ImageList1.Height) div 2;
  ImageList1.Draw(Canvas, X, Y, ord(State));
end;

end.
