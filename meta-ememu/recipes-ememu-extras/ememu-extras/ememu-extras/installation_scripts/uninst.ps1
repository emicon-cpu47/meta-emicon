$emu_folder_name = 'ememu'
$install_path = $([System.Environment]::GetFolderPath('LocalApplicationData'))
$link_path = "$([System.Environment]::GetFolderPath('Desktop'))\ememu.lnk"
$prg_install_path = $([System.Environment]::GetFolderPath('ProgramFiles'))

Write-Host
Write-Host "Внимание!"
Write-Host "При удалении эмулятора будут удалены файлы дисковой системы эмулятора."
Write-Host "Это приведет к безвозвратной потере данных сохраненных в дисковой системе"
Write-Host "эмулятора таких, как настройки, проекты выгруженные в RTS CODESYS, логи."
Write-Host
Write-Host "Продолжить удаление?" -ForegroundColor Green
Write-Host "1. Да" -ForegroundColor Green
Write-Host "2. Нет" -ForegroundColor Green
Write-Host

$choice = Read-Host "Выберите пункт меню"
Switch($choice){
1 {
  Write-Host "Удаление $install_path\$emu_folder_name"
  Remove-Item "$install_path\$emu_folder_name" -Recurse
  Write-Host "Удаление $link_path"
  Remove-Item $link_path
}
2 {Write-Host "Выход"; exit}
   default {Write-Host "Удаление отменено" -ForegroundColor Red ; exit}
}
