# Justfile - https://github.com/casey/just
# https://cheatography.com/linux-china/cheat-sheets/justfile/

# Set shell for Windows OSs:
# set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]
set windows-shell := ["cmd.exe", "/c"]


build: gen
	@powershell.exe Write-host "Running build..." -f Blue
	@ninja -f build.ninja
	@powershell.exe Write-host "Succesfully built project" -f Green

buildall:
	@powershell.exe Write-host "Running debug build..." -f Blue
	@ninja -f build-Debug.ninja
	@powershell.exe Write-host "Running release build..." -f Cyan
	@ninja -f build-Release.ninja
	@powershell.exe Write-host "Running release build (with debug info)..." -f Magenta
	@ninja -f build-RelWithDebInfo.ninja
	@powershell.exe Write-host "Succesfully built project" -f Green

gen: 
	@powershell.exe Write-host "Generating build files..." -f Blue
	@powershell.exe ./support/multi_ninja.ps1
	@cmake -B .
	@powershell.exe Write-host "Generated Ninja build files" -f Green

console:
	@dev.bat
	@powershell.exe Write-host "Launched the dev console" -f Green	

clean:
	@powershell.exe ./support/clean.ps1

clang:
	powershell.exe ./clang-build -export-jsondb
	@powershell.exe Write-host "Generated compile_commands.json" -f Green	

fmt:
	@powershell.exe .\support\clang-format-all.ps1 -RepoRoot '%cd%\src' -Include '*.h', '*.cpp' -Exclude '*.g.*'

wt:
	@%LOCALAPPDATA%\Microsoft\WindowsApps\wt.exe -d %cd% cmd '%comspec% /k %%i\Common7\Tools\vsdevcmd.bat %*'
	@powershell.exe Write-host "Launched windows terminal" -f Green	

vswhere:
	@powershell.exe ./support/vswhere.ps1

export:
	@powershell.exe ./support/zip.ps1

stats:
	@powershell.exe Write-host "Code stats for ./src" -f Green	
	@tokei .\src --files
## tokei .\src --files --output json > code_stats.json
