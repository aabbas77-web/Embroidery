object FormMain: TFormMain
  Left = 190
  Top = 105
  Width = 544
  Height = 375
  Caption = 'IPL Demo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 536
    Height = 329
    HorzScrollBar.Tracking = True
    VertScrollBar.Tracking = True
    Align = alClient
    TabOrder = 0
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
    end
  end
  object MainMenu1: TMainMenu
    Left = 184
    Top = 140
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open'
        OnClick = Open1Click
      end
      object Save1: TMenuItem
        Caption = '&Save'
        OnClick = Save1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        ShortCut = 16472
        OnClick = Exit1Click
      end
    end
    object Imaging1: TMenuItem
      Caption = '&Imaging'
      object Negative1: TMenuItem
        Caption = '&Negative'
        OnClick = Negative1Click
      end
      object MyNegative1: TMenuItem
        Caption = '&My Negative'
        OnClick = MyNegative1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Flip1: TMenuItem
        Caption = '&Flip'
        object Horizontal1: TMenuItem
          Caption = '&Horizontal'
          OnClick = Horizontal1Click
        end
        object Vertical1: TMenuItem
          Caption = '&Vertical'
          OnClick = Vertical1Click
        end
      end
      object Rotate1: TMenuItem
        Caption = '&Rotate'
        OnClick = Rotate1Click
      end
      object ScaleIntensity1: TMenuItem
        Caption = '&Scale Intensity'
        OnClick = ScaleIntensity1Click
      end
      object ApplyBias1: TMenuItem
        Caption = 'Apply &Bias'
        OnClick = ApplyBias1Click
      end
      object Border1: TMenuItem
        Caption = 'Borde&r'
        OnClick = Border1Click
      end
      object Flush1: TMenuItem
        Caption = '&Flush'
        OnClick = Flush1Click
      end
    end
    object Morphology1: TMenuItem
      Caption = '&Morphology'
      object Thining1: TMenuItem
        Caption = '&Thining'
        OnClick = Thining1Click
      end
      object Erosion1: TMenuItem
        Caption = '&Erosion'
        OnClick = Erosion1Click
      end
      object Dilation1: TMenuItem
        Caption = '&Dilation'
        OnClick = Dilation1Click
      end
      object Skeleton1: TMenuItem
        Caption = '&Skeleton'
        OnClick = Skeleton1Click
      end
      object SkeletonZhou1: TMenuItem
        Caption = 'Skeleton Zhou with &Edges'
        OnClick = SkeletonZhou1Click
      end
      object SkeletonZhouwithoutEdges1: TMenuItem
        Caption = 'Skeleton Zhou with&out Edges'
        OnClick = SkeletonZhouwithoutEdges1Click
      end
    end
    object Segmentation1: TMenuItem
      Caption = '&Segmentation'
      object LowContours1: TMenuItem
        Caption = '&Low Contours'
        OnClick = LowContours1Click
      end
      object HighContours1: TMenuItem
        Caption = '&High Contours'
      end
      object DeriveBlobs1: TMenuItem
        Caption = 'Derive &Blobs'
        OnClick = DeriveBlobs1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Start1: TMenuItem
        Caption = '&Start'
        OnClick = Start1Click
      end
    end
    object Pol1: TMenuItem
      Caption = '&Pol'
      OnClick = Pol1Click
      object Save3: TMenuItem
        Caption = '&Save'
        OnClick = Save3Click
      end
    end
    object Emb1: TMenuItem
      Caption = '&Emb'
      object Save2: TMenuItem
        Caption = '&Save'
        OnClick = Save2Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object FillPattern1: TMenuItem
        Caption = 'Fill &Pattern'
        OnClick = FillPattern1Click
      end
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    DefaultExt = 'bmp'
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly]
    Left = 184
    Top = 64
  end
  object SavePictureDialog1: TSavePictureDialog
    DefaultExt = 'bmp'
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly]
    Left = 212
    Top = 96
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer1Timer
    Left = 222
    Top = 134
  end
  object OpenDialog1: TOpenDialog
    Left = 122
    Top = 178
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'dst'
    Filter = 'Embroidery DST (*.dst)|*.dst'
    Options = [ofOverwritePrompt, ofHideReadOnly]
    Left = 162
    Top = 186
  end
  object OpenDialog2: TOpenDialog
    DefaultExt = 'Pol'
    Filter = 'POL Files (*.pol)|*.pol'
    Options = [ofOverwritePrompt, ofHideReadOnly]
    Left = 314
    Top = 30
  end
  object SaveDialog2: TSaveDialog
    DefaultExt = 'pol'
    Filter = 'POL Files (*.pol)|*.pol'
    Options = [ofOverwritePrompt, ofHideReadOnly]
    Left = 342
    Top = 30
  end
end
