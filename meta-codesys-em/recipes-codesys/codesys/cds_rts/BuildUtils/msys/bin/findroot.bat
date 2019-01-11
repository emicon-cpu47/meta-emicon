@echo off
set ppath=""
set m4defspath=BuildUtils\M4Defs

IF exist "..\%m4defspath%" set ppath=".."
IF NOT %ppath%=="" goto finish
IF exist "..\..\%m4defspath%" set ppath="../.."
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\%m4defspath%" set ppath="../../.."
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\%m4defspath%" set ppath="../../../.."
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\%m4defspath%" set ppath="../../../../.."
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\%m4defspath%" set ppath="../../../../../.."
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\..\%m4defspath%" set ppath="../../../../../../.."
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\..\..\%m4defspath%" set ppath="../../../../../../../.."
IF NOT %ppath%=="" goto finish

IF exist "..\CodesysSpV3\%m4defspath%" set ppath="../CodesysSpV3"
IF NOT %ppath%=="" goto finish
IF exist "..\..\CodesysSpV3\%m4defspath%" set ppath="../../CodesysSpV3"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\CodesysSpV3\%m4defspath%" set ppath="../../../CodesysSpV3"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\CodesysSpV3\%m4defspath%" set ppath="../../../../CodesysSpV3"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\CodesysSpV3\%m4defspath%" set ppath="../../../../../CodesysSpV3"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\CodesysSpV3\%m4defspath%" set ppath="../../../../../../CodesysSpV3"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\..\CodesysSpV3\%m4defspath%" set ppath="../../../../../../../CodesysSpV3"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\..\..\CodesysSpV3\%m4defspath%" set ppath="../../../../../../../../CodesysSpV3"
IF NOT %ppath%=="" goto finish

IF exist "..\CoDeSys-RT\%m4defspath%" set ppath="../CoDeSys-RT"
IF NOT %ppath%=="" goto finish
IF exist "..\..\CoDeSys-RT\%m4defspath%" set ppath="../../CoDeSys-RT"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\CoDeSys-RT\%m4defspath%" set ppath="../../../CoDeSys-RT"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\CoDeSys-RT\%m4defspath%" set ppath="../../../../CoDeSys-RT"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\CoDeSys-RT\%m4defspath%" set ppath="../../../../../CoDeSys-RT"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\CoDeSys-RT\%m4defspath%" set ppath="../../../../../../CoDeSys-RT"
IF NOT %ppath%=="" goto finish
IF exist "..\..\..\..\..\..\..\CoDeSys-RT\%m4defspath%" set ppath="../../../../../../../CoDeSys-RT"
IF NOT %ppath%=="" goto finish

:finish
echo Root path: %ppath%