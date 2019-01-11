@echo on
setlocal ENABLEEXTENSIONS
setlocal ENABLEDELAYEDEXPANSION

set CWD=%~d0%~p0
set SAXON_PATH=\\server01\Development\Tools\saxon\saxon.jar

java -jar %SAXON_PATH% -xsl:Slotty.xsl "DeviceTemplate.devdesc.xml" Input="Slotty.input.xml" > Slotty.devdesc.xml

pause
