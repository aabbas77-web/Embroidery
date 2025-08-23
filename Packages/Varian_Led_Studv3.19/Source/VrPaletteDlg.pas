{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrPaletteDlg;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, VrClasses;

type
  TVrPaletteDlg = class(TForm)
    OkButton: TButton;
    CancelButton: TButton;
    GroupBox1: TGroupBox;
    Shape1: TShape;
    Shape2: TShape;
    Shape3: TShape;
    Shape4: TShape;
    Shape5: TShape;
    Shape6: TShape;
    Shape7: TShape;
    Shape8: TShape;
    Shape9: TShape;
    Shape10: TShape;
    Shape11: TShape;
    Shape12: TShape;
    RadioButton1: TRadioButton;
    Button3: TButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    RadioButton5: TRadioButton;
    RadioButton6: TRadioButton;
    ColorDialog: TColorDialog;
    Label7: TLabel;
    Shape13: TShape;
    Button4: TButton;
    Label8: TLabel;
    Shape14: TShape;
    Button5: TButton;
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure CancelButtonClick(Sender: TObject);
    procedure OkButtonClick(Sender: TObject);
  private
    FCurPalette: TVrPalette;
    FOrgColorHigh: TColor;
    FOrgColorLow: TColor;
    FPaletteIndex: Integer;
    procedure SetPalette(Value: TVrPalette);
  public
    property EditorPalette: TVrPalette write SetPalette;
  end;


implementation

{$R *.DFM}

procedure TVrPaletteDlg.FormCreate(Sender: TObject);
begin
  FPaletteIndex := 1;
end;

procedure TVrPaletteDlg.Button4Click(Sender: TObject);
begin
  ColorDialog.Color := Shape13.Brush.Color;
  if ColorDialog.Execute then
    Shape13.Brush.Color := ColorDialog.Color;
end;

procedure TVrPaletteDlg.Button5Click(Sender: TObject);
begin
 ColorDialog.Color := Shape14.Brush.Color;
  if ColorDialog.Execute then
    Shape14.Brush.Color := ColorDialog.Color;
end;

procedure TVrPaletteDlg.Button3Click(Sender: TObject);
begin
  case FPaletteIndex of
    1: begin Shape13.Brush.Color := clGreen; Shape14.Brush.Color := clLime; end;
    2: begin Shape13.Brush.Color := clMaroon; Shape14.Brush.Color := clRed; end;
    3: begin Shape13.Brush.Color := clNavy; Shape14.Brush.Color := clBlue; end;
    4: begin Shape13.Brush.Color := clTeal; Shape14.Brush.Color := clAqua; end;
    5: begin Shape13.Brush.Color := clPurple; Shape14.Brush.Color := clFuchsia end;
    6: begin Shape13.Brush.Color := clOlive; Shape14.Brush.Color := clYellow; end;
  end;
end;

procedure TVrPaletteDlg.RadioButton1Click(Sender: TObject);
begin
  FPaletteIndex := (Sender as TRadioButton).Tag;
end;

procedure TVrPaletteDlg.CancelButtonClick(Sender: TObject);
begin
  FCurPalette.Low := FOrgColorLow;
  FCurPalette.High := FOrgColorHigh;
end;

procedure TVrPaletteDlg.OkButtonClick(Sender: TObject);
begin
  FCurPalette.Low := Shape13.Brush.Color;
  FCurPalette.High := Shape14.Brush.Color;
end;

procedure TVrPaletteDlg.SetPalette(Value: TVrPalette);
begin
  FCurPalette := Value;
  FOrgColorHigh := Value.High;
  FOrgColorLow := Value.Low;
  Shape13.Brush.Color := FCurPalette.Low;
  Shape14.Brush.Color := FCurPalette.High;
end;





end.
