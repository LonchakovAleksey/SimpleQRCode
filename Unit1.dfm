object FormSimpleQRCode: TFormSimpleQRCode
  Left = 0
  Top = 0
  Caption = 'SimpleQRCode'
  ClientHeight = 473
  ClientWidth = 496
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 512
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Times New Roman'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 23
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 496
    Height = 243
    Align = alClient
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object ImageQR: TImage
      Left = 136
      Top = 16
      Width = 200
      Height = 200
      PopupMenu = PopupMenu1
      OnClick = ImageQRClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 243
    Width = 496
    Height = 230
    Align = alBottom
    BevelOuter = bvNone
    Caption = 'Panel2'
    Color = clWhite
    Ctl3D = True
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 1
    object Memo1: TMemo
      Left = 0
      Top = 0
      Width = 496
      Height = 211
      Align = alClient
      ScrollBars = ssBoth
      TabOrder = 0
      WordWrap = False
      OnChange = Memo1Change
    end
    object StatusBar1: TStatusBar
      Left = 0
      Top = 211
      Width = 496
      Height = 19
      Panels = <>
      SimplePanel = True
      ExplicitTop = 214
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 400
    Top = 56
    object pu_copy: TMenuItem
      Caption = 'Copy'
      OnClick = pu_copyClick
    end
  end
end
