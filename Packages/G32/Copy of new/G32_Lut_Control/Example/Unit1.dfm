object Form1: TForm1
  Left = 189
  Top = 105
  Width = 299
  Height = 369
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Anchors = [akLeft, akTop, akBottom]
  Caption = 'LUTControl Example'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 291
    Height = 214
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object lcRGB: TLUTControl
      Left = 104
      Top = 8
      Width = 180
      Height = 175
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = clSilver
      DoubleBuffered = True
      GridColor = -8421505
      GridCols = 8
      GridRows = 8
      LineColor = -16776961
      NodeColor = -16777089
      ParentColor = False
      OnChange = lcRGBChange
    end
    object imgInput: TImage32
      Left = 80
      Top = 9
      Width = 14
      Height = 173
      Anchors = [akLeft, akTop, akBottom]
      BitmapAlign = baTopLeft
      Scale = 1
      ScaleMode = smStretch
    end
    object imgOutput: TImage32
      Left = 105
      Top = 193
      Width = 178
      Height = 14
      Anchors = [akLeft, akRight, akBottom]
      BitmapAlign = baTopLeft
      Scale = 1
      ScaleMode = smStretch
      OnClick = imgOutputClick
    end
    object Combo: TComboBox
      Left = 8
      Top = 134
      Width = 65
      Height = 21
      Style = csDropDownList
      Anchors = [akLeft, akBottom]
      ItemHeight = 13
      TabOrder = 3
      OnChange = ComboChange
      Items.Strings = (
        'Grays'
        'RGB'
        'Greens')
    end
    object StaticText1: TStaticText
      Left = 8
      Top = 8
      Width = 34
      Height = 17
      Caption = 'Input:'
      TabOrder = 4
    end
    object StaticText2: TStaticText
      Left = 8
      Top = 192
      Width = 42
      Height = 17
      Anchors = [akLeft, akBottom]
      Caption = 'Output:'
      TabOrder = 5
    end
    object CheckBox: TCheckBox
      Left = 12
      Top = 160
      Width = 57
      Height = 17
      Anchors = [akLeft, akBottom]
      Caption = 'Display'
      TabOrder = 6
      OnClick = CheckBoxClick
    end
    object ResetRGB: TButton
      Left = 8
      Top = 32
      Width = 57
      Height = 17
      Caption = 'Reset'
      TabOrder = 7
      OnClick = ResetRGBClick
    end
    object StaticText5: TStaticText
      Left = 8
      Top = 72
      Width = 34
      Height = 17
      Caption = 'Mode:'
      TabOrder = 8
    end
    object ModeCombo: TComboBox
      Left = 8
      Top = 88
      Width = 65
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 9
      OnChange = ModeComboChange
      Items.Strings = (
        'lmNodes'
        'lmCustom')
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 214
    Width = 291
    Height = 128
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object lcAlpha: TLUTControl
      Left = 104
      Top = 8
      Width = 180
      Height = 81
      Anchors = [akLeft, akTop, akRight]
      Color = clSilver
      DefaultLeftEdge = 255
      DoubleBuffered = True
      GridColor = -8421505
      GridCols = 8
      GridRows = 4
      LineColor = -16776961
      NodeColor = -16777089
      Nodes = '(0, 191), (255, 191)'
      ParentColor = False
      OnChange = lcAlphaChange
    end
    object imgResult: TImage32
      Left = 105
      Top = 104
      Width = 178
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      BitmapAlign = baTopLeft
      Scale = 1
      ScaleMode = smNormal
    end
    object StaticText3: TStaticText
      Left = 8
      Top = 8
      Width = 45
      Height = 17
      Caption = 'Opacity:'
      TabOrder = 2
    end
    object StaticText4: TStaticText
      Left = 8
      Top = 104
      Width = 38
      Height = 17
      Caption = 'Result:'
      TabOrder = 3
    end
    object ResetAlpha: TButton
      Left = 8
      Top = 32
      Width = 57
      Height = 17
      Caption = 'Reset'
      TabOrder = 4
      OnClick = ResetAlphaClick
    end
  end
end
