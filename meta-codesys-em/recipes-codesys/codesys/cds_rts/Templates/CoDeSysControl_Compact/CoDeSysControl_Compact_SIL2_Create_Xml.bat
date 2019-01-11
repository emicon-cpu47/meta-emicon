@Echo OFF

REM Create SIL2 xml documentation from Commandline

set origin=%~dp0
REM echo %origin% 

set RTSCONFPath=%origin%\..\..\RtsConfigurator\Bin\
REM echo %RTSCONFPath%

set RCPPath=%origin%\CoDeSysControl_Compact_SIL2.rcp
REM echo %RCPPath%

cd %RTSCONFPath%

RtsConfigurator.exe %RCPPath% --createXmlOutput --closeAfterExecute

cd %origin%