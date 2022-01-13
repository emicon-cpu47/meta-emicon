$emu_folder_name = 'ememu'
$install_path = $([System.Environment]::GetFolderPath('LocalApplicationData'))
$link_path = "$([System.Environment]::GetFolderPath('Desktop'))\ememu.lnk"
$prg_install_path = $([System.Environment]::GetFolderPath('ProgramFiles'))
$reboot_required = $false
$os_ver = $([System.Environment]::OSVersion.Version.Major) + $([System.Environment]::OSVersion.Version.Minor)
#if ($os_ver -lt 8) {}

Write-Host "Путь установки: $install_path\$emu_folder_name"

if (Test-Path "$install_path\$emu_folder_name" -PathType Any){
	Write-Host
	Write-Host "Внимание!"
	Write-Host "Путь установки УЖЕ существует!"
	Write-Host "Повторная установка затрет все файлы включая файл дисковой системы эмулятора."
	Write-Host "Это приведет к безвозвратной потери данных ранее установленного эмулятора!"
	Write-Host
	Write-Host "Продолжить установку?" -ForegroundColor Green
	Write-Host "1. Да, переустановить" -ForegroundColor Green
	Write-Host "2. Нет, выйти" -ForegroundColor Green
	Write-Host
	$choice = Read-Host "Выберите пункт меню"
	Switch($choice){
	1 {	
		Write-Host "Продолжение установки..."
		Write-Host "Удаление $install_path\$emu_folder_name"
		Remove-Item "$install_path\$emu_folder_name" -Recurse
		Write-Host "Удаление $link_path"
		Remove-Item $link_path
	  }
	2 {Write-Host "Выход"; exit}
	default {Write-Host "Установка отменена" -ForegroundColor Red ; exit}
	}
}

# Установка ТАП
$tap = Get-WmiObject -Class Win32_NetworkAdapter -Filter "Name='TAP-Windows Adapter V9'"
if ($tap) {
    Write-Host "TAP-Windows Adapter V9 - найден"
} else {
    Write-Host "Установка: TAP-Windows Adapter V9 ..."
    if ($PSVersionTable.PSVersion.Major -lt 4) {
        Write-Host "В этой ОС не найден Windows Management Framework 4.0 (или младше)"
        Write-Host "Нет возможности автоматической утсановки драйвера TAP."
        Write-Host "Установку драйвера TAP-Windows Adapter V9 следует произвести вручную."
        Write-Host "Установите драйвер drivers\tap-Windows.exe с настройками по умолчанию и перегрузите систему."
        Write-Host "Затем запустите текущий установщик setup.bat повторно."
        exit
    }
    Start-Process -FilePath "drivers\tap-windows.exe" -ArgumentList '/S', '/D=$prg_install_path\TAP-Windows' -Wait
    Write-Host "Установка: TAP-Windows Adapter V9 - выполнена"
    $reboot_required = $true
}

# создаем файлы запуска
# еще раз запрашиваем интерфейс, тк он мог быть толко что установлен
$tap = Get-WmiObject -Class Win32_NetworkAdapter -Filter "Name='TAP-Windows Adapter V9'"

Write-Host
Write-Host "IP эмулятора: 192.168.67.2"  -ForegroundColor Yellow
Write-Host "Сетевые настройки подключения к эмулятору по умолчанию требуют статического IP"
Write-Host "диапазона 192.168.67.0/24 (например 192.168.67.1 255.255.255.0) сетевого интерфейса:"
Write-Host "$($tap.netconnectionid) [$($tap.Name)]" -ForegroundColor Yellow

Write-Host
Write-Host "Копирование..."
Copy-Item .\$emu_folder_name $install_path -Recurse
Write-Host "Копирование закончено."

$multistring =@"
"$install_path\$emu_folder_name\qemu\qemu-system-arm.exe" -M vexpress-a9 -cpu cortex-a8 ^
-dtb "$install_path\$emu_folder_name\system\emu.dtb" ^
-kernel "$install_path\$emu_folder_name\system\emu_kernel" ^
-sd "$install_path\$emu_folder_name\system\emufs.ext3" ^
-append "root=/dev/mmcblk0 console=ttyAMA0" ^
 --nographic -m 640  -nic tap,ifname=$($tap.netconnectionid),script=no,downscript=no,mac=02:ca:fe:f0:0d:01
@pause
"@
$multistring | out-file $install_path\$emu_folder_name\ememu.bat -encoding oem

$multistring = @"
@echo Net restart...
@PowerShell -ExecutionPolicy RemoteSigned -File ""$install_path\$emu_folder_name\netrestart.ps1""
"@

$multistring | out-file $install_path\$emu_folder_name\netrestart.bat -encoding oem

Write-Host "Создание ярлыка: $link_path"

$target =  "$install_path\$emu_folder_name\ememu.bat"
$shell = New-Object -ComObject WScript.Shell    
$lnk = $shell.CreateShortcut($link_path)
$lnk.TargetPath = $target
$lnk.Save()

Write-Host "Установка окончена."
if ($reboot_required){
    Write-Host "Требуется перезагрузка ситемы!" -ForegroundColor Green
    Write-Host "Для корректной работы сетевого интерфеса TAP требуется перезагрузка ОС."
    Write-Host
}
