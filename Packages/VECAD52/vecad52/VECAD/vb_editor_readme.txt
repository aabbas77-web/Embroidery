When you open the project where will be message about
not find module VecApi.bas. This module comes with 
VeCAD package in API subdirectory. Include this module
in the project.
In order not conflict with prevoius version of Vecad.dll
all function definitions in VecApi.bas refers to Vecad51.dll
You must copy file Vecad.dll that comes with this package
to Windows directory with name "Vecad51.dll" in order
VB projects can find it.


