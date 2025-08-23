unit ShellStrings;

{$define ENGLISH}  // or GERMAN or whatever

interface

{$I VER.INC}
{$IFDEF _CPPB_3_UP}
  {$ObjExportAll On}
{$ENDIF}

uses Classes;

const

{$ifdef GERMAN}
{$define JAM_LANG}
  strNewFolder         = 'Neuer Ordner';

  // Die folgenden Strings werden normalerweise vom Betriebssystem bezogen.
  // Sollte dies aus irgendwelchen Gründen nicht möglich sein, greifen die
  // ShellBrowser Komponenten auf diese Definitionen zurück:
  ColData : Array [0..3] of record Title: String; Alignment: TAlignment; Width: Integer end =
    ( (Title:'Name'; Alignment:taLeftJustify; Width:150),
      (Title:'Größe'; Alignment:taRightJustify; Width:60),
      (Title:'Typ'; Alignment:taLeftJustify; Width:120),
      (Title:'Geändert am'; Alignment:taLeftJustify; Width:100));

  strKB                = 'KB';
{$endif}


{$ifdef ROMANIAN}
{$define JAM_LANG}
  strNewFolder = 'Fisier Nou';

  ColData : Array [0..3] of record Title: String; Alignment: TAlignment; Width: Integer end =
    ( (Title:'Nume'; Alignment:taLeftJustify; Width:150),
      (Title:'Marime'; Alignment:taRightJustify; Width:60),
      (Title:'Tip'; Alignment:taLeftJustify; Width:99),
      (Title:'Modificat'; Alignment:taLeftJustify; Width:120));

  strKB                = 'KB';
{$endif}


{$ifndef JAM_LANG}
  strNewFolder = 'New Folder';

  // The following strings are usually obtained from the operating system
  // If this fails for some reasons, the ShellBrowser falls back to these definitions:

  // Column information used if not provided by the system
  // You can Change the column titles to your language:
  ColData : Array [0..3] of record Title: String; Alignment: TAlignment; Width: Integer end =
    ( (Title:'Name'; Alignment:taLeftJustify; Width:150),
      (Title:'Size'; Alignment:taRightJustify; Width:60),
      (Title:'Type'; Alignment:taLeftJustify; Width:120),
      (Title:'Changed'; Alignment:taLeftJustify; Width:100));

  strKB = 'KB';
{$endif}

implementation

end.
