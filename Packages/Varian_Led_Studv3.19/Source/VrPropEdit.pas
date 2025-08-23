{*****************************************************}
{                                                     }
{     Varian Led Studio Component Toolkit             }
{                                                     }
{     Varian Software NL (c) 1996-1999                }
{     All Rights Reserved                             }
{                                                     }
{ ****************************************************}

unit VrPropEdit;

{$I VRLIB.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  DsgnIntf, VrClasses, VrBitmapsDlg, VrPaletteDlg;


type
  TVrVersionProperty = class(TStringProperty)
  public
    function GetAttributes: TPropertyAttributes; override;
  end;

  TVrPaletteProperty = class(TClassProperty)
  public
    procedure Edit; override;
    function GetAttributes: TPropertyAttributes; override;
  end;

  TVrBitmapsProperty = class(TClassProperty)
  public
    procedure Edit; override;
    function GetAttributes: TPropertyAttributes; override;
  end;

  TVrBitmapListEditor = class(TDefaultEditor)
  protected
    procedure EditProperty(PropertyEditor: TPropertyEditor;
      var Continue, FreeEditor: Boolean); override;
  public
    procedure ExecuteVerb(Index: Integer); override;
    function GetVerb(Index: Integer): string; override;
    function GetVerbCount: Integer; override;
  end;

  TVrStringListEditor = class(TDefaultEditor)
  protected
    procedure EditProperty(PropertyEditor: TPropertyEditor;
      var Continue, FreeEditor: Boolean); override;
  public
    procedure ExecuteVerb(Index: Integer); override;
    function GetVerb(Index: Integer): string; override;
    function GetVerbCount: Integer; override;
  end;

  TVrFileNameProperty = class(TStringProperty)
  public
    procedure Edit; override;
    function GetAttributes: TPropertyAttributes; override;
  end;


implementation


{ TVrVersionProperty }

function TVrVersionProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paReadOnly];
end;

{ TVrBitmapsProperty }

function TVrBitmapsProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paDialog] - [paSubProperties];
end;

procedure TVrBitmapsProperty.Edit;
var
  List: TVrBitmaps;
  ListEditor: TVrBitmapListDialog;
  Res: TModalResult;
begin
  List := TVrBitmaps(GetOrdValue);
  ListEditor := TVrBitmapListDialog.Create(nil);
  try
    ListEditor.Bitmaps.Assign(List);
    Res := ListEditor.ShowModal;
    if Res = mrOk then
    begin
      List.Assign(ListEditor.Bitmaps);
      Designer.Modified;
    end;
  finally
    ListEditor.Free;
  end;
end;

{ TVrBitmapListEditor }

procedure TVrBitmapListEditor.EditProperty(PropertyEditor: TPropertyEditor;
  var Continue, FreeEditor: Boolean);
var
  PropName: string;
begin
  PropName := PropertyEditor.GetName;
  if (CompareText(PropName, 'Bitmaps') = 0) then
  begin
    PropertyEditor.Edit;
    Continue := False;
  end;
end;

function TVrBitmapListEditor.GetVerbCount: Integer;
begin
  Result := 1;
end;

function TVrBitmapListEditor.GetVerb(Index: Integer): string;
begin
  if Index = 0 then
    Result := 'Bitmaps Editor!'
  else Result := '';
end;

procedure TVrBitmapListEditor.ExecuteVerb(Index: Integer);
begin
  if Index = 0 then Edit;
end;

{ TVrStringListEditor }

procedure TVrStringListEditor.EditProperty(PropertyEditor: TPropertyEditor;
  var Continue, FreeEditor: Boolean);
var
  PropName: string;
begin
  PropName := PropertyEditor.GetName;
  if (CompareText(PropName, 'Strings') = 0) then
  begin
    PropertyEditor.Edit;
    Continue := False;
  end;
end;

function TVrStringListEditor.GetVerbCount: Integer;
begin
  Result := 1;
end;

function TVrStringListEditor.GetVerb(Index: Integer): string;
begin
  if Index = 0 then
    Result := 'StringList Editor!'
  else Result := '';
end;

procedure TVrStringListEditor.ExecuteVerb(Index: Integer);
begin
  if Index = 0 then Edit;
end;


{ TVrPaletteProperty }

procedure TVrPaletteProperty.Edit;
var
  Palette: TVrPalette;
  PaletteEditor: TVrPaletteDlg;
  Res: TModalResult;
begin
  Palette := TVrPalette(GetOrdValue);
  PaletteEditor := TVrPaletteDlg.Create(nil);
  try
    PaletteEditor.EditorPalette := Palette;
    Res := PaletteEditor.ShowModal;
    if Res = mrOk then
      Designer.Modified;
  finally
    PaletteEditor.Free;
  end;
end;

function TVrPaletteProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paDialog, paSubProperties];
end;

{ TVrFileNameProperty }

function TVrFileNameProperty.GetAttributes: TPropertyAttributes;
begin
  Result := [paDialog] - [paSubProperties];
end;

procedure TVrFileNameProperty.Edit;
var
  FileName: string;
  OpenDlg: TOpenDialog;
begin
  FileName := GetValue;
  OpenDlg := TOpenDialog.Create(nil);
  try
    OpenDlg.Title := 'Select';
    OpenDlg.FileName := '*.*';
    OpenDlg.Filter := 'All Files (*.*)|*.*';
    OpenDlg.InitialDir := ExtractFileDir(FileName);
    if OpenDlg.Execute then
      SetValue(OpenDlg.FileName);
  finally
    OpenDlg.Free;
  end;
end;



end.
