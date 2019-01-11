#!/bin/sh
# **********************************************************************************************************
# * Usage:
# * $0 <File name> <bin path> <M4Defs path> <Components path> 
# * File name: File name and path without ending, e.g. D:\CoDeSys\CoDeSys_SP_3.0\Components\CMBasicChecksItf
# * bin path: Windows relative or absoulte path to bin directory, e.g. ..\BuildUtils\msys\bin
# * M4Defs path: Unix relative or absoulte path to M4Defs directory, e.g. ../BuildUtils/M4Defs
# * Components path: Unix relative or absoulte path to Components directory, e.g. ../Components
# **********************************************************************************************************

cp $1.m4 $1__.m4
fromdos $1__.m4
m4 -I$3 -I $4 Implementation.m4 - < "$1__.m4" > "$1.h"
m4 -I$3 -I$4 C++Wrapper.m4 - < "$1__.m4" > "$1.cpp"
fromdos $1.h
todos $1.h
fromdos $1.cpp
 #%2\renamecpp %1.cpp
rm $1__.m4
exit
