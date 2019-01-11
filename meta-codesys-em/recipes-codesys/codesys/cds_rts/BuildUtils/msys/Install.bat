@ echo off

echo Installs the GNU m4 Makroprocessor to C:\Programme\msys.
echo The m4 executable is part of the msys distribution of 
echo Unix tools ported to win32. 
echo The program is covered by the GPL

PAUSE

md C:\Programme\msys
xcopy *.* C:\Programme\msys\ /S /E 

PAUSE
