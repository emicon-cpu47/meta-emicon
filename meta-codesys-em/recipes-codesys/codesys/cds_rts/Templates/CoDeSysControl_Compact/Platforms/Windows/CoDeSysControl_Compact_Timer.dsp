# Microsoft Developer Studio Project File - Name="CoDeSysControl_Compact_Timer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=CoDeSysControl_Compact_Timer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CoDeSysControl_Compact_Timer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CoDeSysControl_Compact_Timer.mak" CFG="CoDeSysControl_Compact_Timer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CoDeSysControl_Compact_Timer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "CoDeSysControl_Compact_Timer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CoDeSysControl_Compact_Timer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /I "..\..\CoDeSysControl_Compact_Timer_Header" /I "..\\" /I "..\..\\" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib winmm.lib wsock32.lib iphlpapi.lib setupapi.lib /nologo /subsystem:console /map /machine:I386

!ELSEIF  "$(CFG)" == "CoDeSysControl_Compact_Timer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\\" /I "..\..\..\..\Components" /I "..\..\\" /D "PATHS_RELATIVE" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "CODESYSCONTROL_COMPACT_TIMER" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib winmm.lib wsock32.lib iphlpapi.lib setupapi.lib advapi32.lib /nologo /subsystem:console /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CoDeSysControl_Compact_Timer - Win32 Release"
# Name "CoDeSysControl_Compact_Timer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Specific"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CoDeSysControl_Compact.h
# End Source File
# Begin Source File

SOURCE=..\..\CoDeSysControl_Compact_Timer_NotImpl.h
# End Source File
# Begin Source File

SOURCE=..\mainOS.c
# End Source File
# Begin Source File

SOURCE=..\sysdefines.h
# End Source File
# Begin Source File

SOURCE=..\sysspecific.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\Components\ComponentManager\CM.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\ComponentManager\CMBasicChecks.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpAppEmbedded\CmpAppEmbedded.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpAppEmbedded\CmpAppEmbeddedSrv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpBinTagUtil\CmpBinTagUtil.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpBlkDrvCom\CmpBlkDrvCom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpBlkDrvUdp\CmpBlkDrvUdp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpChannelMgrEmbedded\CmpChannelMgrEmbedded.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpChannelMgrEmbedded\CmpChannelMgrEmbeddedChecksum.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpChannelServerEmbedded\CmpChannelServerEmbedded.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpChecksum\CmpChecksum.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpChecksum\CmpChecksumCrc16.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpChecksum\CmpChecksumCrc32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpCommunicationLib\CmpCommunicationLib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpDevice\CmpDevice.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpDevice\CmpDeviceSrv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpEventMgr\CmpEventMgr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpIecTask\CmpIecTask.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpIoMgrEmbedded\CmpIoMgrEmbedded.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpLogEmbedded\CmpLogEmbedded.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpLogEmbedded\CmpLogEmbeddedSrv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpMemPool\CmpMemPool.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpMonitor\CmpMonitor.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpNameServiceServer\CmpNameServiceServer.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpRouterEmbedded\CmpRouterEmbedded.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpRouterEmbedded\CmpRouterEmbeddedAddrSrvc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpScheduleTimer\CmpScheduleTimer.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpSettingsEmbedded\CmpSettingsEmbedded.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpSettingsEmbedded\CmpSettingsEmbeddedSrv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\CmpSrv\CmpSrv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\ComponentManager\CMUtils.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysCom\SysCom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysComWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysCpuHandling\SysCpuHandling.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysCpuHandlingWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysExcept\SysExcept.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysExceptWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysFileFlash\SysFileFlash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysFlash\SysFlash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysFlashWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysInt\SysInt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysInternalLib\SysInternalLibDefault.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysIntWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysMem\SysMem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysMemWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysOut\SysOut.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysOutWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysSocket\SysSocket.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysSocketWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysTarget\SysTarget.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysTargetWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysTime\SysTime.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Components\SysTimer\SysTimer.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysTimerWin32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Platforms\Windows\Sys\SysTimeWin32.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
