<?xml version='1.0' encoding='utf-8' ?>
<!-- C++Builder XML Project -->
<PROJECT>
  <MACROS>
    <VERSION value="BCB.05.03"/>
    <PROJECT value="demo.exe"/>
    <OBJFILES value="DEMO.obj Demo1.obj"/>
    <RESFILES value="Demo.res"/>
    <IDLFILES value=""/>
    <IDLGENFILES value=""/>
    <DEFFILE value=""/>
    <RESDEPEN value="$(RESFILES) Demo1.dfm"/>
    <LIBFILES value=""/>
    <LIBRARIES value="ToolBar97PK.lib vcldbx50.lib vclbde50.lib vcldb50.lib vclx50.lib vcl50.lib"/>
    <SPARELIBS value="vcl50.lib vclx50.lib vcldb50.lib vclbde50.lib vcldbx50.lib ToolBar97PK.lib"/>
    <PACKAGES value="VCL50.bpi VCLX50.bpi bcbsmp50.bpi VCLDB50.bpi ibsmp50.bpi VCLBDE50.bpi 
      dclocx50.bpi bcb97axserver50.bpi BeforeCompilePk.bpi VCLADO50.bpi 
      VCLDBX50.bpi TEEUI50.bpi TEEDB50.bpi TEE50.bpi DSS50.bpi TEEQR50.bpi 
      VCLIB50.bpi VCLMID50.bpi VCLIE50.bpi INETDB50.bpi INET50.bpi NMFAST50.bpi 
      WEBMID50.bpi bcbie50.bpi SINGLEAPPINSTANCE50.bpi QRPT50.bpi 
      MultiShapePK.bpi SplinesPk.bpi TTF2VecPk.bpi wmfeps_utils.bpi 
      RpnCompPk.bpi VarianPk.bpi JamShell.bpi SDLPK.bpi VirusPk.bpi TVidGrab.bpi 
      spl_DelphiBitsPk.bpi AFXPk.bpi CB5_G32_Pk.bpi En_C5.bpi GraphicExPk.bpi 
      CADSysPk.bpi ToolBar97PK.bpi"/>
    <PATHCPP value=".;"/>
    <PATHPAS value=".;"/>
    <PATHRC value=".;"/>
    <PATHASM value=".;"/>
    <DEBUGLIBPATH value="$(BCB)\lib\debug"/>
    <RELEASELIBPATH value="$(BCB)\lib\release"/>
    <LINKER value="ilink32"/>
    <USERDEFINES value=""/>
    <SYSDEFINES value="NO_STRICT"/>
    <MAINSOURCE value="DEMO.cpp"/>
    <INCLUDEPATH value="$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;.."/>
    <LIBPATH value="$(BCB)\Projects\Lib;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib"/>
    <WARNINGS value="-w-par -w-8027 -w-8026"/>
    <WARNOPTSTR value=""/>
  </MACROS>
  <OPTIONS>
    <IDLCFLAGS value="-I$(BCB)\projects -I$(BCB)\include -I$(BCB)\include\vcl -I.. -src_suffix 
      cpp -boa"/>
    <CFLAG1 value="-Od -H=d:\PROGRA~1\BORLAND\CBUILD~1\lib\vcld.csm -Hc -Vx -Ve -X- -r- -a4 
      -b- -k -y -v -vi- -c -tWM"/>
    <CFLAG2 value=""/>
    <CFLAG3 value=""/>
    <PFLAGS value="-AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE 
      -$YD -$W -$O- -v -JPHNV -M -JPHNE"/>
    <RFLAGS value=""/>
    <AFLAGS value="/mx /w2 /zd"/>
    <LFLAGS value="-D&quot;&quot; -aa -Tpe -x -v"/>
    <IFLAGS value=""/>
  </OPTIONS>
  <LINKER>
    <ALLOBJ value="c0w32.obj sysinit.obj $(OBJFILES)"/>
    <ALLRES value="$(RESFILES)"/>
    <ALLLIB value="$(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib "/>
  </LINKER>
  <IDEOPTIONS>
[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0
Locale=10241
CodePage=1256

[Excluded Packages]
$(BCB)\Bin\dclite50.bpl=Borland Integrated Translation Environment

[HistoryLists\hlIncludePath]
Count=2
Item0=$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl;E:\Digitizer\ToolBar97
Item1=$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl

[HistoryLists\hlLibraryPath]
Count=1
Item0=$(BCB)\Projects\Lib;$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib

[HistoryLists\hlUnitAliases]
Count=1
Item0=WinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE

[Debugging]
DebugSourceDirs=

[Parameters]
RunParams=
HostApplication=
RemoteHost=
RemotePath=
RemoteDebug=0

[Compiler]
ShowInfoMsgs=0
LinkDebugVcl=1
LinkCGLIB=0

[CORBA]
AddServerUnit=1
AddClientUnit=1
PrecompiledHeaders=1
  </IDEOPTIONS>
</PROJECT>