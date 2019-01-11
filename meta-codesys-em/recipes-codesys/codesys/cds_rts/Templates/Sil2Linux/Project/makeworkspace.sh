#!/bin/sh

cd cmp;
ln -s ../../../../Components/SysTime/* .;
ln -s ../../../../Components/SysTimer/* .;
ln -s ../../../../Components/SysTarget/* .;
ln -s ../../../../Components/SysSocket/* .;
ln -s ../../../../Components/SysOut/* .;
ln -s ../../../../Components/SysMem/* .;
ln -s ../../../../Components/SysInternalLib/* .;
ln -s ../../../../Components/SysInt/* .;
ln -s ../../../../Components/SysFlash/* .;
ln -s ../../../../Components/SysFileFlash/* .;
ln -s ../../../../Components/SysExcept/* .;
ln -s ../../../../Components/SysCpuHandling/* .;
ln -s ../../../../Components/SysCom/* .;
ln -s ../../../../Components/IoDrvUnsafeBridge/* .;
ln -s ../../../../Components/CmpSrv/* .;
ln -s ../../../../Components/CmpSIL2/* .;
ln -s ../../../../Components/CmpSettingsEmbedded/* .;
ln -s ../../../../Components/CmpScheduleTimer/* .;
ln -s ../../../../Components/CmpRouterEmbedded/* .;
ln -s ../../../../Components/CmpNameServiceServer/* .;
ln -s ../../../../Components/CmpMonitor2/* .;
ln -s ../../../../Components/CmpMemPool/* .;
ln -s ../../../../Components/CmpLogEmbedded/* .;
ln -s ../../../../Components/CmpIoMgrEmbedded/* .;
ln -s ../../../../Components/CmpIoDrvIec/* .;
ln -s ../../../../Components/CmpIecTask/* .;
ln -s ../../../../Components/CmpEventMgrEmbedded/* .;
ln -s ../../../../Components/CmpDevice/* .;
ln -s ../../../../Components/CmpCommunicationLib/* .;
ln -s ../../../../Components/CmpChecksum/* .;
ln -s ../../../../Components/CmpChannelServerEmbedded/* .;
ln -s ../../../../Components/CmpChannelMgrEmbedded/* .;
ln -s ../../../../Components/CmpBlkDrvUdp/* .;
ln -s ../../../../Components/CmpBinTagUtil/* .;
ln -s ../../../../Components/CmpAppEmbedded/* .;
ln -s ../../../../Components/CmpAppBPEmbedded/* .;
ln -s ../../../../Components/ComponentManager/* .;
ln -s ../../../../Components/CmpCAACanL2/* .;
ln -s ../../../../Components/CmpCAAMemBlockMan/* .;
ln -s ../../../../Components/CmpCAASdoClient/* .;
ln -s ../../../../Components/CmpCAASdoServer/* .;
ln -s ../../../../Components/CmpCAATickUtil/* .;
ln -s ../../../../Components/CmpCAATick/* .;
ln -s ../../../../Components/CmpCAACallback/* .;
ln -s ../../../../Components/CmpCAATypes/* .;
ln -s ../../../../Components/CmpSocketCanDrv/* .;
ln -s ../../CmpSocketCanDrvSIL2/* .;
rm -f *Linux.c
rm -f *QNX.c
cd ../../Sys;
ln -s ../../../Platforms/Linux/Sys/SysComLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysCpuHandlingLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysExceptLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysFlashLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysMemLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysOutLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysSocketLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysTargetLinux.c . ;
ln -s ../../../Platforms/Linux/Sys/SysTimeLinux.c . ;


