unit MainUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls, ComCtrls, Math, Clipbrd, ExtDlgs, G32, G32_ByteMaps,
  G32_RangeBars, G32_Image;

type
  TForm1 = class(TForm)
    Button1: TButton;
    PaletteCombo: TComboBox;
    CheckBox1: TCheckBox;
    Button2: TButton;
    Button3: TButton;
    SavePictureDialog: TSavePictureDialog;
    StaticText1: TStaticText;
    ScaleBar: TGaugeBar;
    Panel1: TPanel;
    Image: TImgView32;
    procedure PaletteComboChange(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure ScaleChange(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  public
    DataSet: TByteMap;
    palGrayscale: TPalette32;
    palGreens: TPalette32;
    palReds: TPalette32;
    palRainbow: TPalette32;
    procedure GenPalettes;
    procedure GenSampleData(W, H: Integer);
    procedure PaintData;
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

{ TForm1 }

procedure TForm1.FormCreate(Sender: TObject);
begin
  PaletteCombo.ItemIndex := 0;
  GenPalettes;
  DataSet := TByteMap.Create;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  DataSet.Free;
end;

procedure TForm1.GenPalettes;
var
  i: Integer;
  f: Single;
begin
  for i := 0 to 255 do
  begin
    f := i / 255;
    palGrayscale[i] := HSLtoRGB(0, 0, f * 0.9 + 0.1);
    palGreens[i] := HSLtoRGB(f * 0.4, 0.5, f * 0.4 + 0.2);
    palReds[i] := HSLtoRGB(0.8 + f * 0.3 , 0.7 + f * 0.3, f * 0.85 + 0.1);
    palRainbow[i] := HSLtoRGB(f * 1.2, 0.6, f * 0.8 + 0.2);
  end;
end;

procedure TForm1.GenSampleData(W, H: Integer);
var
  i, j: Integer;

  function Clamp(FloatVal: Extended): Byte;
  begin
    if FloatVal <= 0 then Result := 0
    else if FloatVal >= 1 then Result := 255
    else Result := Round(FloatVal * 255);
  end;

begin
  DataSet.SetSize(W, H);
  for j := 0 to H - 1 do
    for i := 0 to W - 1 do
    begin
      // just some noise
      DataSet[i, j] := Clamp(0.5 + 0.5 *
        (Sin((i + Random(10)) / 100) +
        0.5 * Cos(j / 11) +
        0.2 * Sin((i + j) / 3)));
    end;
end;

procedure TForm1.PaintData;
var
  P: PPalette32;
begin
  case PaletteCombo.ItemIndex of
    0: P := @palGrayScale;
    1: P := @palGreens;
    2: P := @palReds;
  else
    P := @palRainbow;
  end;
  DataSet.WriteTo(Image.Bitmap, P^);
end;

procedure TForm1.PaletteComboChange(Sender: TObject);
begin
  PaintData;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  GenSampleData(300, 220);
  PaintData;
end;

procedure TForm1.ScaleChange(Sender: TObject);
var
  NewScale: Single;
begin
  NewScale := Power(10, -(ScaleBar.Position) / 100);
  ScaleBar.Repaint;
  Image.Scale := NewScale;
end;

procedure TForm1.CheckBox1Click(Sender: TObject);
begin
  if Checkbox1.Checked then Image.Bitmap.StretchFilter := sfLinear
  else Image.Bitmap.StretchFilter := sfNearest;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  Clipboard.Assign(Image.Bitmap);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  with SavePictureDialog do
    if Execute then
      Image.Bitmap.SaveToFile(FileName);
end;

end.
