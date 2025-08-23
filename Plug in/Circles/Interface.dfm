object FormInterface: TFormInterface
  Left = 190
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Circles Plug-in'
  ClientHeight = 147
  ClientWidth = 253
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001001010000001001800680300001600000028000000100000002000
    0000010018000000000000030000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    00000000000000000000000000000000000000000000007B7B7B000000FFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFF0000007B7B7B0000000000000000000000000000
    000000007B7B7B000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
    00007B7B7B000000000000000000000000000000000000FFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000
    00000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFFFFFF000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFF00007BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000
    00000000FFFFFFFFFFFFFFFFFFFFFFFF00007B00007B00007BFFFFFFFFFFFFFF
    FFFFFFFFFF000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFF00007B00007BFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000
    00000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00007BFFFFFFFF
    FFFFFFFFFF000000000000000000000000000000000000FFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFF00007BFFFFFF0000000000000000000000000000
    000000007B7B7B000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
    00007B7B7B0000000000000000000000000000000000007B7B7B000000FFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFF0000007B7B7B0000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    0000FFFF0000F83F0000E00F0000C0070000C007000080030000800300008003
    00008003000080030000C0070000C0070000E00F0000F83F0000FFFF0000}
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 106
    Width = 253
    Height = 41
    Align = alBottom
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 49
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 129
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 253
    Height = 106
    Align = alClient
    TabOrder = 1
    object SpeedButton1: TSpeedButton
      Left = 201
      Top = 6
      Width = 45
      Height = 22
      Caption = 'About'
      OnClick = SpeedButton1Click
    end
    object Label1: TLabel
      Left = 8
      Top = 12
      Width = 43
      Height = 13
      Caption = 'Radius X'
    end
    object Label2: TLabel
      Left = 8
      Top = 36
      Width = 43
      Height = 13
      Caption = 'Radius Y'
    end
    object Label3: TLabel
      Left = 8
      Top = 60
      Width = 40
      Height = 13
      Caption = 'Degrees'
    end
    object Label4: TLabel
      Left = 8
      Top = 84
      Width = 36
      Height = 13
      Caption = 'Extrude'
    end
    object CSpinEditRadiusX: TCSpinEdit
      Left = 56
      Top = 7
      Width = 60
      Height = 22
      TabStop = True
      MaxValue = 1000000
      ParentColor = False
      TabOrder = 0
      Value = 3
    end
    object CSpinEditRadiusY: TCSpinEdit
      Left = 56
      Top = 31
      Width = 60
      Height = 22
      TabStop = True
      MaxValue = 1000000
      ParentColor = False
      TabOrder = 1
      Value = 3
    end
    object CSpinEditDegrees: TCSpinEdit
      Left = 56
      Top = 55
      Width = 60
      Height = 22
      TabStop = True
      MaxValue = 1000000
      MinValue = 1
      ParentColor = False
      TabOrder = 2
      Value = 45
    end
    object CSpinEditExtrude: TCSpinEdit
      Left = 56
      Top = 79
      Width = 60
      Height = 22
      TabStop = True
      MaxValue = 1000000
      MinValue = -1000000
      ParentColor = False
      TabOrder = 3
      Value = 10
    end
  end
end
