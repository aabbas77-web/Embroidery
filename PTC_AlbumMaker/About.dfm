object FormAbout: TFormAbout
  Left = 190
  Top = 190
  BiDiMode = bdLeftToRight
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'About'
  ClientHeight = 189
  ClientWidth = 202
  Color = 14145495
  Font.Charset = ARABIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 202
    Height = 189
    Align = alClient
    BevelOuter = bvNone
    Color = 14145495
    TabOrder = 0
    object Bevel2: TBevel
      Left = 4
      Top = 144
      Width = 194
      Height = 9
    end
    object Label1: TLabel
      Left = 5
      Top = 4
      Width = 194
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'WWPTC'
      Font.Charset = ARABIC_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 5
      Top = 24
      Width = 194
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Album Maker  V1.0'
    end
    object Label3: TLabel
      Left = 5
      Top = 44
      Width = 194
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Syria - Damascus'
    end
    object Label7: TLabel
      Left = 5
      Top = 64
      Width = 194
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Mazza - Vellat Sharkia'
    end
    object Label4: TLabel
      Left = 5
      Top = 84
      Width = 194
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'www.wwptc.com'
    end
    object Label5: TLabel
      Left = 5
      Top = 104
      Width = 194
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'E-Mail: mail@wwptc.com'
    end
    object Label6: TLabel
      Left = 5
      Top = 124
      Width = 194
      Height = 13
      Alignment = taCenter
      AutoSize = False
      Caption = 'Tel: +963 11 6120076'
    end
    object Button1: TButton
      Left = 64
      Top = 160
      Width = 75
      Height = 25
      Caption = '&Ok'
      Default = True
      TabOrder = 0
      OnClick = Button1Click
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 84
    Top = 64
  end
end
