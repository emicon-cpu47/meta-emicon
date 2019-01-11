@echo off
rem **********************************************************************************************************
rem * Usage:
rem * genrate_itf.bat <File name> <bin path> <M4Defs path>
rem * File name: File name and path without ending, e.g. D:\CoDeSys\CoDeSys_SP_3.0\Components\CMBasicChecksItf
rem * bin path: Windows relative or absoulte path to bin directory, e.g. ..\BuildUtils\msys\bin
rem * M4Defs path: Unix relative or absoulte path to M4Defs directory, e.g. ../BuildUtils/M4Defs
rem **********************************************************************************************************
copy %1.m4 %1__.m4
%2\dos2unix %1__.m4
%2\m4 -I%3 Exports.m4 - < %1__.m4 > %1.h
%2\dos2unix %1.h
del %1__.m4
exit