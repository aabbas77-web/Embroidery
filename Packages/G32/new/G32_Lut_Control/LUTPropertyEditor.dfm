object LUTEditorDlg: TLUTEditorDlg
  Left = 195
  Top = 103
  Width = 209
  Height = 339
  Caption = 'LUT Editor'
  Color = clBtnFace
  Constraints.MinHeight = 310
  Constraints.MinWidth = 182
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 0
    Width = 201
    Height = 3
    Align = alTop
    Shape = bsTopLine
  end
  object OKButton: TButton
    Left = 68
    Top = 281
    Width = 59
    Height = 23
    Anchors = [akRight, akBottom]
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object Cancel: TButton
    Left = 132
    Top = 281
    Width = 61
    Height = 23
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 185
    Height = 180
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvLowered
    TabOrder = 2
    object LUT: TLUTControl
      Left = 1
      Top = 1
      Width = 183
      Height = 178
      Align = alClient
      Color = clInfoBk
      DoubleBuffered = True
      GridColor = -4210753
      GridCols = 8
      GridRows = 8
      LineColor = -16777216
      NodeColor = -16776961
      Nodes = '(0, 0), (255, 255)'
      ParentColor = False
      OnChange = LUTChange
    end
  end
  object Memo: TMemo
    Left = 8
    Top = 216
    Width = 184
    Height = 57
    Anchors = [akLeft, akRight, akBottom]
    TabOrder = 3
    OnChange = MemoChange
  end
  object StaticText1: TStaticText
    Left = 8
    Top = 197
    Width = 38
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = 'Nodes:'
    TabOrder = 4
  end
  object Reset: TButton
    Left = 8
    Top = 275
    Width = 41
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = 'Reset'
    TabOrder = 5
    OnClick = ResetClick
  end
end
