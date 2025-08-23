object FormMain: TFormMain
  Left = 190
  Top = 105
  Width = 696
  Height = 480
  Caption = 'Spiral'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 61
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 12
      Width = 7
      Height = 13
      Caption = 'A'
    end
    object Label2: TLabel
      Left = 92
      Top = 12
      Width = 7
      Height = 13
      Caption = 'B'
    end
    object Label3: TLabel
      Left = 92
      Top = 36
      Width = 7
      Height = 13
      Caption = 'T'
    end
    object Label4: TLabel
      Left = 8
      Top = 36
      Width = 7
      Height = 13
      Caption = 'C'
    end
    object CSpinEditA: TCSpinEdit
      Left = 24
      Top = 8
      Width = 60
      Height = 22
      TabStop = True
      ParentColor = False
      TabOrder = 0
      Value = 1
      OnChange = CSpinEditAChange
    end
    object CSpinEditB: TCSpinEdit
      Left = 108
      Top = 8
      Width = 60
      Height = 22
      TabStop = True
      ParentColor = False
      TabOrder = 1
      Value = 100
      OnChange = CSpinEditAChange
    end
    object CSpinEditT: TCSpinEdit
      Left = 108
      Top = 32
      Width = 60
      Height = 22
      TabStop = True
      Increment = 10
      ParentColor = False
      TabOrder = 2
      Value = 1000
      OnChange = CSpinEditAChange
    end
    object CSpinEditC: TCSpinEdit
      Left = 24
      Top = 32
      Width = 60
      Height = 22
      TabStop = True
      Increment = 10
      ParentColor = False
      TabOrder = 3
      OnChange = CSpinEditAChange
    end
  end
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 61
    Width = 688
    Height = 392
    Align = alClient
    TabOrder = 1
    object Image: TImage
      Left = 0
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
    end
  end
end
