Write-host "Attempting to install chocolatey..." -f Green	

Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

Write-host "Attempting to install Just command runner" -f Green	
choco install just

Write-host "Attempting to install cMake" -f Green	
choco install cmake

Write-host "Attempting to install Ninja build system..." -f Green	
choco install ninja

Write-host "Attempting to install tokei" -f Green	
choco install tokei
# winget install XAMPPRocky.tokei

Write-host "You can now run just commands" -f Green	
Set-Location ..
just --list
