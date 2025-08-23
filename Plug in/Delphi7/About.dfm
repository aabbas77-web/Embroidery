object FormAbout: TFormAbout
  Left = 598
  Top = 124
  Width = 300
  Height = 200
  Caption = 'FormAbout'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 93
    Top = 48
    Width = 106
    Height = 13
    Caption = 'Ceated Using Delphi 7'
  end
  object Label2: TLabel
    Left = 99
    Top = 72
    Width = 93
    Height = 13
    Caption = 'By : Feras Al-Hayek'
  end
  object Label3: TLabel
    Left = 100
    Top = 24
    Width = 92
    Height = 13
    Caption = 'PolyArc Plugin v1.0'
  end
  object ButtonOK: TButton
    Left = 108
    Top = 112
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = ButtonOKClick
  end
end
