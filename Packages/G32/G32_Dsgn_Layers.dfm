object LayerEditorForm: TLayerEditorForm
  Left = 474
  Top = 94
  AutoScroll = False
  Caption = 'LayerEditorForm'
  ClientHeight = 259
  ClientWidth = 170
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 89
    Width = 170
    Height = 4
    Cursor = crVSplit
    Align = alTop
    AutoSnap = False
    MinSize = 48
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 170
    Height = 89
    Align = alTop
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    object Panel2: TPanel
      Left = 0
      Top = 0
      Width = 168
      Height = 16
      Align = alTop
      Caption = 'Registered Layer Types'
      TabOrder = 0
    end
    object RegList: TListView
      Left = 0
      Top = 16
      Width = 168
      Height = 71
      Align = alClient
      BorderStyle = bsNone
      Color = 15790320
      Columns = <
        item
          AutoSize = True
          Caption = 'Type'
        end>
      Ctl3D = True
      HideSelection = False
      ReadOnly = True
      ParentShowHint = False
      ShowColumnHeaders = False
      ShowHint = True
      TabOrder = 1
      ViewStyle = vsReport
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 93
    Width = 170
    Height = 166
    Align = alClient
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 1
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 168
      Height = 32
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object SpeedButton1: TSpeedButton
        Left = 0
        Top = 16
        Width = 32
        Height = 16
        Caption = 'Add'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Tahoma'
        Font.Style = []
        Layout = blGlyphBottom
        ParentFont = False
        OnClick = SpeedButton1Click
      end
      object SpeedButton2: TSpeedButton
        Left = 32
        Top = 16
        Width = 32
        Height = 16
        Caption = 'Del.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Tahoma'
        Font.Style = []
        Layout = blGlyphBottom
        ParentFont = False
      end
      object SpeedButton3: TSpeedButton
        Left = 64
        Top = 16
        Width = 32
        Height = 16
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Tahoma'
        Font.Style = []
        Glyph.Data = {
          96000000424D9600000000000000760000002800000007000000080000000100
          0400000000002000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFF0FF00
          0FF0FF000FF0FF000FF000000000F00000F0FF000FF0FFF0FFF0}
        ParentFont = False
      end
      object SpeedButton4: TSpeedButton
        Left = 96
        Top = 16
        Width = 32
        Height = 16
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Tahoma'
        Font.Style = []
        Glyph.Data = {
          96000000424D9600000000000000760000002800000007000000080000000100
          0400000000002000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFF0FFF0FF00
          0FF0F00000F000000000FF000FF0FF000FF0FF000FF0FFFFFFF0}
        ParentFont = False
      end
      object SpeedButton5: TSpeedButton
        Left = 128
        Top = 16
        Width = 41
        Height = 16
        Caption = 'Types'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -9
        Font.Name = 'Tahoma'
        Font.Style = []
        Layout = blGlyphBottom
        ParentFont = False
      end
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 168
        Height = 16
        Align = alTop
        Caption = 'Layers'
        TabOrder = 0
      end
    end
    object ListView: TListView
      Left = 0
      Top = 32
      Width = 168
      Height = 132
      Align = alClient
      BorderStyle = bsNone
      Color = 15790320
      Columns = <
        item
          Caption = 'Names'
          Width = 100
        end
        item
          AutoSize = True
          Caption = 'Types'
        end>
      Ctl3D = True
      HideSelection = False
      MultiSelect = True
      ShowColumnHeaders = False
      TabOrder = 1
      ViewStyle = vsReport
      OnChange = ListViewChange
    end
  end
end
