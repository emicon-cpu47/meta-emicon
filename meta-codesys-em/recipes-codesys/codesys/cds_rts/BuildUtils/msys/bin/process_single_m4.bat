@echo off
echo Processing %1
pushd %~p1
echo Current dir: %CD% File: %~n1%~x1
call %upath%\compile_m4 %~n1%~x1
popd