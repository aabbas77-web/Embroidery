unit Unit1;

{ LUTControl Example }

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  LUTControl, ExtCtrls, {FxButtons,} StdCtrls, G32, G32_Image;

type
  TForm1 = class(TForm)
    Combo: TComboBox;
    imgInput: TImage32;
    imgOutput: TImage32;
    imgResult: TImage32;
    lcRGB: TLUTControl;
    lcAlpha: TLUTControl;
    Panel1: TPanel;
    Panel2: TPanel;
    StaticText1: TStaticText;
    StaticText2: TStaticText;
    StaticText3: TStaticText;
    StaticText4: TStaticText;
    CheckBox: TCheckBox;
    ResetRGB: TButton;
    ResetAlpha: TButton;
    StaticText5: TStaticText;
    ModeCombo: TComboBox;
    procedure ComboChange(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure imgOutputClick(Sender: TObject);
    procedure lcRGBChange(Sender: TObject);
    procedure lcAlphaChange(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure CheckBoxClick(Sender: TObject);
    procedure ResetRGBClick(Sender: TObject);
    procedure ResetAlphaClick(Sender: TObject);
    procedure ModeComboChange(Sender: TObject);
  public
    RGB: TLUT256;
    Alpha: TLUT256;
    CurrentPalette: PPalette32;
    PaletteBW: TPalette32;
    PaletteRGB: TPalette32;
    PaletteGreens: TPalette32;
    procedure DrawResult;
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.FormCreate(Sender: TObject);
var
  I: Integer;
begin
  Combo.ItemIndex := 0;
  ModeCombo.ItemIndex := 0;

  { Define palettes }
  for I := 0 to 255 do PaletteBW[I] := Gray32(I);
  for I := 0 to 255 do PaletteRGB[I] := HSLtoRGB(I / 255, 1, 0.5);
  for I := 0 to 255 do PaletteGreens[I] := HSLtoRGB(I / 512 + 0.1, 1, I / 255);
  CurrentPalette := @PaletteBW;

  { Paint the 'Input' image }
  imgInput.Bitmap.SetSize(1, 256);
  for I := 0 to 255 do imgInput.Bitmap[0, 255 - I] := Color32(I, PaletteBW);
  imgInput.Repaint;

  { Setup the 'Output' image }
  imgOutput.Bitmap.SetSize(256, 1);

  { Update images and palettes }
  lcRGBChange(Self);
  lcAlphaChange(Self);
end;

procedure TForm1.lcRGBChange(Sender: TObject);
var
  I, J: Integer;
begin
  { Read and store the data from a LUTControl }
  lcRGB.CopyTo(RGB);

  { If necessary, update LUTControl's background }
  if not lcRGB.BackgndImage.Empty then
  begin
    for J := 0 to 255 do
      lcRGB.BackgndImage.HorzLineS(0, J, 255, Color32(255 - J, PaletteBW));
    for I := 0 to 255 do
      lcRGB.BackgndImage.VertLineS(I, 255 - RGB[I], 255, Color32(RGB[I], CurrentPalette^));
  end;

  { Update the output image }
  for I := 0 to 255 do imgOutput.Bitmap[I, 0] := Color32(RGB[I], CurrentPalette^);
  imgOutput.Invalidate;

  { Update the resulting image}
  DrawResult;
end;

procedure TForm1.lcAlphaChange(Sender: TObject);
begin
  lcAlpha.CopyTo(Alpha);
  DrawResult;
end;

procedure TForm1.DrawResult;
var
  I, X, Y: Integer;
  C: TColor32;
begin
  { Resize the contained bitmap to image control's dimensions }
  imgResult.SetupBitmap;

  { draw the backgrownd pattern }
  for Y := 0 to imgResult.Height - 1 do
    for X := 0 to imgResult.Width - 1 do
    begin
      if Odd(X div 4) = Odd(Y div 4) then
        imgResult.Bitmap[X, Y] := clBlack
      else
        imgResult.Bitmap[X, Y] := clWhite;
    end;

  { draw the result on top of the pattern }
  if imgResult.Width > 1 then
    for X := 0 to imgResult.Width - 1 do
    begin
      I := X * 255 div (imgResult.Width - 1);
      C := SetAlpha(CurrentPalette[RGB[I]], Alpha[I]);
      imgResult.Bitmap.VertLineTS(X, 0, imgResult.Bitmap.Height - 1, C);
    end;
  imgResult.Invalidate;
end;

procedure TForm1.ComboChange(Sender: TObject);
var
  I: Integer;
begin
  case Combo.ItemIndex of
    0: CurrentPalette := @PaletteBW;
    1: CurrentPalette := @PaletteRGB;
    2: CurrentPalette := @PaletteGreens;
  end;
  lcRGBChange(Self);
  lcRGB.Repaint;
  DrawResult;
end;

procedure TForm1.imgOutputClick(Sender: TObject);
begin
  Combo.ItemIndex := (1 + Combo.ItemIndex) mod Combo.Items.Count;
  ComboChange(Self);
end;

procedure TForm1.FormResize(Sender: TObject);
begin
  DrawResult;
end;

procedure TForm1.CheckBoxClick(Sender: TObject);
begin
  if CheckBox.Checked then lcRGB.BackgndImage.SetSize(256, 256)
  else lcRGB.BackgndImage.SetSize(0, 0);
  lcRGBChange(Sender);
  lcRGB.Invalidate;
end;

procedure TForm1.ResetRGBClick(Sender: TObject);
begin
  lcRGB.Nodes := '';
end;

procedure TForm1.ResetAlphaClick(Sender: TObject);
begin
  lcAlpha.Nodes := '(0, 191), (255, 191)';
end;

procedure TForm1.ModeComboChange(Sender: TObject);
begin
  if ModeCombo.ItemIndex = 0 then lcRGB.Mode := lmNodes
  else lcRGB.Mode := lmCustom;
end;

end.
