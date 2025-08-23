program Editor;

uses
  Forms,
  api_VecApi in 'api_VecApi.pas',
  delphi_editor_Main in 'delphi_editor_Main.pas' {Form1},
  delphi_editor_DwgProc in 'delphi_editor_DwgProc.pas',
  delphi_editor_Funcs in 'delphi_editor_Funcs.pas',
  delphi_editor_Strings in 'delphi_editor_Strings.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
