library DelphiPlugin;

uses
  SysUtils,
  Classes,
  About in 'About.pas' {FormAbout},
  UnitInterface in 'UnitInterface.pas' {FormInterface};

{$R *.res}

exports
  _plug_ShowModalInterface,
  _plug_ShowInterface,
  _plug_CloseInterface,
  _plug_GetIcon,
  _plug_About,
  _plug_GetName,
  _plug_GetHint,
  _plug_GetVersion,
  _plug_GetAuthorName,
  _plug_GetDate,
  _plug_GetGroup,
  _plug_GetShortCut,
  _plug_Initialize,
  _plug_Draw;

begin
  _plug_CreateInterface();
//_This_Should_Be_Called_Somewhere_  
//  _plug_DestroyInterface();
end.


