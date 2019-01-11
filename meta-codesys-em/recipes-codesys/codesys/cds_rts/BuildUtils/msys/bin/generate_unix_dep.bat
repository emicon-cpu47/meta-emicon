@echo off
rem **********************************************************************************************************
rem * Usage:
rem * genrate_dep.bat <File name> <bin path> <M4Defs path> <Components path> 
rem * File name: File name and path without ending, e.g. D:\CoDeSys\CoDeSys_SP_3.0\Components\CMBasicChecksItf
rem * bin path: Windows relative or absoulte path to bin directory, e.g. ..\BuildUtils\msys\bin
rem * M4Defs path: Unix relative or absoulte path to M4Defs directory, e.g. ../BuildUtils/M4Defs
rem * Components path: Unix relative or absoulte path to Components directory, e.g. ../Components
rem **********************************************************************************************************
copy %1.m4 %1__.m4
%2\dos2unix %1__.m4
%2\m4 -I%3 -I%4 Implementation.m4 - < %1__.m4 > %1.h
%2\dos2unix %1.h
del %1__.m4
exit
