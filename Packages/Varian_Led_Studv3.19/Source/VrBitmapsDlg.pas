{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}


unit VrBitmapsDlg;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  VrClasses, Buttons, StdCtrls, ExtCtrls, ExtDlgs, VrControls, VrShadow,
  VrDeskTop;

type
  TVrBitmapListDialog = class(TForm)
    Panel1: TPanel;
    ListBox: TListBox;
    SaveDialog: TSaveDialog;
    OpenDialog: TOpenDialog;
    OpenPictureDialog: TOpenPictureDialog;
    VrShadowButton1: TVrShadowButton;
    VrShadowButton2: TVrShadowButton;
    VrShadowButton3: TVrShadowButton;
    VrShadowButton4: TVrShadowButton;
    VrShadowButton5: TVrShadowButton;
    VrShadowButton6: TVrShadowButton;
    VrShadowButton7: TVrShadowButton;
    VrShadowButton8: TVrShadowButton;
    VrShadowButton9: TVrShadowButton;
    VrDeskTop1: TVrDeskTop;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ButtonAddClick(Sender: TObject);
    procedure ListBoxDrawItem(Control: TWinControl; Index: Integer;
      Rect: TRect; State: TOwnerDrawState);
    procedure ButtonDeleteClick(Sender: TObject);
    procedure ButtonClearClick(Sender: TObject);
    procedure ButtonLoadClick(Sender: TObject);
    procedure ButtonSaveClick(Sender: TObject);
    procedure ButtonMoveUpClick(Sender: TObject);
    procedure ButtonMoveDownClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure VrShadowButton9Click(Sender: TObject);
  private
    procedure BitmapsChanged(Sender: TObject);
  public
    Bitmaps: TVrBitmaps;
  end;


implementation

{$R *.DFM}


procedure TVrBitmapListDialog.FormCreate(Sender: TObject);
begin
  Bitmaps := TVrBitmaps.Create;
  Bitmaps.OnChange := BitmapsChanged;
end;

procedure TVrBitmapListDialog.FormDestroy(Sender: TObject);
begin
  Bitmaps.Free;
end;

procedure TVrBitmapListDialog.ButtonAddClick(Sender: TObject);
var
  Bitmap: TBitmap;
begin
  if OpenPictureDialog.Execute then
  begin
    Bitmap := TBitmap.Create;
    try
      Bitmap.LoadFromFile(OpenPictureDialog.FileName);
      Bitmaps.Add(Bitmap);
    finally
      Bitmap.Free;
    end;
  end;
end;

procedure TVrBitmapListDialog.ListBoxDrawItem(Control: TWinControl; Index: Integer;
  Rect: TRect; State: TOwnerDrawState);
var
  ImgRect: TRect;
  MidY: Integer;
  S: string;
begin
  with TListBox(Control) do
  begin
    Canvas.FillRect(Rect);
    ImgRect := Rect;
    ImgRect.Right := 62;
    OffsetRect(ImgRect, 2, 0);
    InflateRect(ImgRect, 0, -2);
    Canvas.StretchDraw(ImgRect, Bitmaps[Index]);
    S := Format('%d - %d x %d', [Index, Bitmaps[Index].Width, Bitmaps[Index].Height]);
    MidY := ((Rect.Bottom - Rect.Top) - Canvas.TextHeight(S)) div 2;
    Canvas.TextOut(ImgRect.Right + 20, Rect.Top + MidY, S);
  end;
end;

procedure TVrBitmapListDialog.ButtonDeleteClick(Sender: TObject);
var
  Index: Integer;
begin
  Index := ListBox.ItemIndex;
  if Index <> -1 then
    Bitmaps.Delete(Index);
end;

procedure TVrBitmapListDialog.ButtonClearClick(Sender: TObject);
begin
  if MessageDlg('Clear list?', mtConfirmation,
    [mbOk, mbCancel], 0) = mrOk then Bitmaps.Clear;
end;

procedure TVrBitmapListDialog.ButtonLoadClick(Sender: TObject);
begin
  if OpenDialog.Execute then
    Bitmaps.LoadFromFile(OpenDialog.FileName);
end;

procedure TVrBitmapListDialog.ButtonSaveClick(Sender: TObject);
begin
  if SaveDialog.Execute then
    Bitmaps.SaveToFile(SaveDialog.FileName);
end;

procedure TVrBitmapListDialog.ButtonMoveUpClick(Sender: TObject);
var
  Index: Integer;
begin
  Index := ListBox.ItemIndex;
  if Index - 1 >= 0 then
  begin
    Bitmaps.Move(Index, Index - 1);
    ListBox.ItemIndex := Index - 1;
  end;
end;

procedure TVrBitmapListDialog.ButtonMoveDownClick(Sender: TObject);
var
  Index: Integer;
begin
  Index := ListBox.ItemIndex;
  if (Index <> -1) and (Index + 1 < ListBox.Items.Count) then
  begin
    Bitmaps.Move(Index, Index + 1);
    ListBox.ItemIndex := Index + 1;
  end;
end;

procedure TVrBitmapListDialog.SpeedButton1Click(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TVrBitmapListDialog.BitmapsChanged(Sender: TObject);
var
  I: Integer;
begin
  ListBox.Items.BeginUpdate;
  try
    ListBox.Items.Clear;
    for I := 0 to Bitmaps.Count - 1 do
      ListBox.Items.Add('XXX');
  finally
    ListBox.Items.EndUpdate;
  end;
end;

procedure TVrBitmapListDialog.VrShadowButton9Click(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

end.
