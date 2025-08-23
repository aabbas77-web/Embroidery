When you open the project at first time, you need to correct
path to file VecApi.pas. This file comes with VeCAD package 
in API subdirectory.
In order not conflict with prevoius version of Vecad.dll
all function definitions in VecApi.pas refers to Vecad51.dll
You must copy file Vecad.dll that comes with this package
to Windows directory with name "Vecad51.dll" in order
Delphi projects can find it.


