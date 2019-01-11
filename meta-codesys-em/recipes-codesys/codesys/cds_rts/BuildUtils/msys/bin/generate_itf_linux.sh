#!/bin/sh
# **********************************************************************************************************
# * Usage:
# * genrate_itf.bat <File name> <bin path> <M4Defs path>
# * File name: File name and path without ending, e.g. D:\CoDeSys\CoDeSys_SP_3.0\Components\CMBasicChecksItf
# * bin path: Windows relative or absoulte path to bin directory, e.g. ..\BuildUtils\msys\bin
# * M4Defs path: Unix relative or absoulte path to M4Defs directory, e.g. ../BuildUtils/M4Defs
# **********************************************************************************************************
cp $1.m4 $1__.m4
fromdos $1__.m4
m4 -I$3 Exports.m4 - < "$1__.m4" > "$1.h"
fromdos $1.h
todos $1.h
rm $1__.m4
exit