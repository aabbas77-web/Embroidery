unit JAMAbout;

interface
{$I VER.INC}
{$IFDEF _CPPB_3_UP}
  {$ObjExportAll On}
{$ENDIF}

uses DsgnIntf;

type
  TJamVersion = string;

  TJamVersionProperty = class(TStringProperty)
  public
    procedure Edit; override;
    function GetValue: string; override;
    function GetAttributes: TPropertyAttributes; override;
  end;

  procedure Register;


implementation

uses  Dialogs, SysUtils, ShellBrowser, ShellControls, ShellLink, JamControls;

procedure TJamVersionProperty.Edit;
const
  ABOUT_TEXT = '%s'#13#13 +
     'Copyright 1998-2000 by Joachim Marder, All Rights Reserved.'#13 +
     'This component is shareware.'#13#13 +
     'The latest version of this component can be found on'#13 +
     'our web site at:'#13#13 +
     '  http://www.jam-software.com/delphi/'#13;
begin
  MessageDlg(Format(ABOUT_TEXT, [GetStrValue]), mtInformation, [mbOK], 0);
end;

function TJamVersionProperty.GetValue: string;
var
  i: integer;
begin
  i := Pos(' V', GetStrValue);
  Result := Copy(GetStrValue, i + 2, Length(GetStrValue)-i);
end;

function TJamVersionProperty.GetAttributes: TPropertyAttributes;
begin
  Result := inherited GetAttributes + [paDialog, paReadOnly];
end;

procedure Register;
begin
  RegisterPropertyEditor(TypeInfo(String), TShellBrowser, 'Version', TJamVersionProperty);
  RegisterPropertyEditor(TypeInfo(String), TJamShellList, 'Version', TJamVersionProperty);
  RegisterPropertyEditor(TypeInfo(String), TJamShellTree, 'Version', TJamVersionProperty);
  RegisterPropertyEditor(TypeInfo(String), TJamShellCombo, 'Version', TJamVersionProperty);
  RegisterPropertyEditor(TypeInfo(String), TJamShellLink, 'Version', TJamVersionProperty);
  RegisterPropertyEditor(TypeInfo(String), TJamFolderCombo, 'Version', TJamVersionProperty);
end;//Register

end.
