@echo off

set cmppath=""
set pltfpath=""
set templpath=""
set testpath=""
set addonspath=""
set confpath=""
set upath=""

if "%1"=="" set cmppath="%CD%\..\..\..\Components"&goto check_utils
set cmppath="%1"

:check_utils
if "%2"=="" set upath="%CD%"&goto begin
set upath="%2"

:begin
echo Components path: %cmppath%
echo M4 utils path: %upath%

set pltfpath=%cmppath%\..\Platforms
set templpath=%cmppath%\..\Templates
set extpath=%cmppath%\..\..\CodesysSpExt
set testpath=%cmppath%\..\Test
set addonspath=%cmppath%\..\Components__AddOns__
set confpath=%cmppath%\..\Components__CONFIDENTIAL__

echo Platforms path: %pltfpath%
echo Templates path: %templpath%

if not exist "%cmppath%" echo Components path doesn't exist & goto failed


pushd %extpath%
echo %CD%
if exist m4list.lst del m4list.lst
dir *.m4 /b /S > m4list.lst
for /f "tokens=1" %%A in (m4list.lst) do (call %upath%\process_single_m4.bat %%A)
if exist m4list.lst del m4list.lst
popd

rem Get all m4 file paths in the Components folder and compile them

pushd %cmppath%
echo %CD%
if exist m4list.lst del m4list.lst
dir *.m4 /b /S > m4list.lst
for /f "tokens=1" %%A in (m4list.lst) do (call %upath%\process_single_m4.bat %%A)
if exist m4list.lst del m4list.lst
popd
 
if not exist %pltfpath% echo Platforms path doesn't exist! & goto failed
 
rem Get all m4 file paths in the Platforms folder and compile them
 
pushd %pltfpath%
echo %CD%
if exist m4list.lst del m4list.lst
dir *.m4 /b /S > m4list.lst
for /f "tokens=1" %%A in (m4list.lst) do (call %upath%\process_single_m4.bat %%A)
if exist m4list.lst del m4list.lst
popd

if not exist %templpath% echo Templates path doesn't exist! & goto failed

rem Get all m4 file paths in the Templates folder and compile them

pushd %templpath%
echo %CD%
if exist m4list.lst del m4list.lst
dir *.m4 /b /S > m4list.lst
for /f "tokens=1" %%A in (m4list.lst) do (call %upath%\process_single_m4.bat %%A)
if exist m4list.lst del m4list.lst
popd

if not exist %testpath% echo Test path doesn't exist! & goto failed

rem Get all m4 file paths in the Test folder and compile them

pushd %testpath%
echo %CD%
if exist m4list.lst del m4list.lst
dir *.m4 /b /S > m4list.lst
for /f "tokens=1" %%A in (m4list.lst) do (call %upath%\process_single_m4.bat %%A)
if exist m4list.lst del m4list.lst
popd

if not exist %addonspath% echo AddOns path doesn't exist! & goto failed

rem Get all m4 file paths in the AddOns folder and compile them

pushd %addonspath%
echo %CD%
if exist m4list.lst del m4list.lst
dir *.m4 /b /S > m4list.lst
for /f "tokens=1" %%A in (m4list.lst) do (call %upath%\process_single_m4.bat %%A)
if exist m4list.lst del m4list.lst
popd

if not exist %confpath% echo Templates path doesn't exist! & goto failed

rem Get all m4 file paths in the Confidential folder and compile them

pushd %confpath%
echo %CD%
if exist m4list.lst del m4list.lst
dir *.m4 /b /S > m4list.lst
for /f "tokens=1" %%A in (m4list.lst) do (call %upath%\process_single_m4.bat %%A)
if exist m4list.lst del m4list.lst
popd

goto finished

:failed
echo Sequence FAILED!
goto end

:finished
echo Sequence finished

:end