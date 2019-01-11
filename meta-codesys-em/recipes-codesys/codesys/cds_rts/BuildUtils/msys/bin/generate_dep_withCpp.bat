@echo off
rem **********************************************************************************************************
rem * Usage:
rem * genrate_dep.bat <File name> <bin path> <M4Defs path> <Components path> 
rem * File name: File name and path without ending, e.g. D:\CoDeSys\CoDeSys_SP_3.0\Components\CMBasicChecksItf
rem * bin path: Windows relative or absoulte path to bin directory, e.g. ..\BuildUtils\msys\bin
rem * M4Defs path: Unix relative or absoulte path to M4Defs directory, e.g. ../BuildUtils/M4Defs
rem * Components path: Unix relative or absoulte path to Components directory, e.g. ../Components
rem **********************************************************************************************************

set INCLUDES=

IF not '%3' == '' set INCLUDES=%INCLUDES% -I%3
IF not '%4' == '' set INCLUDES=%INCLUDES% -I%4
IF not '%5' == '' set INCLUDES=%INCLUDES% -I%5
IF not '%6' == '' set INCLUDES=%INCLUDES% -I%6
IF not '%7' == '' set INCLUDES=%INCLUDES% -I%7
IF not '%8' == '' set INCLUDES=%INCLUDES% -I%8
IF not '%9' == '' set INCLUDES=%INCLUDES% -I%9

echo includes %INCLUDES%

copy %1.m4 %1__.m4
%2\dos2unix %1__.m4
rem %2\m4 %INCLUDES% Implementation_v2.m4 - < %1__.m4 > %1.h
%2\m4 %INCLUDES% Implementation.m4 - < %1__.m4 > %1.h
%2\m4 %INCLUDES% C++Wrapper.m4 - < %1__.m4 > %1.cpp
%2\dos2unix %1.h
%2\unix2dos %1.h
%2\dos2unix %1.cpp
%2\renamecpp %1.cpp
del %1__.m4
exit
