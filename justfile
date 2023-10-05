# Justfile - https://github.com/casey/just
# https://cheatography.com/linux-china/cheat-sheets/justfile/

# Set shell for Windows OSs:
# set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]
set windows-shell := ["cmd.exe", "/c"]

# Generates Ninja files only
gen: 
	@powershell.exe . .\support\commands.ps1; generate_ninja_makefiles

# Build Debug version of the software
build: gen
	@powershell.exe Write-host "Running build..." -f Blue
	@ninja -f build.ninja
	@powershell.exe Write-host "Succesfully built project" -f Green

# Build Release version of the SW
buildr: gen
	@powershell.exe Write-host "Running release build..." -f Blue
	@ninja -f build-Release.ninja
	@powershell.exe Write-host "Successfully built project`n`n" -f Green

# Build both release and debug versions of the software
buildall:
	@powershell.exe Write-host "Running debug build..." -f Blue
	@ninja -f build-Debug.ninja
	@powershell.exe Write-host "Running release build..." -f Cyan
	@ninja -f build-Release.ninja
	@powershell.exe Write-host "Running release build (with debug info)..." -f Magenta
	@ninja -f build-RelWithDebInfo.ninja
	@powershell.exe Write-host "Succesfully built project" -f Green

# Launch the MSVC dev console which is needed to build the SW
console:
	@dev.bat
	@powershell.exe Write-host "Launched the dev console" -f Green	

# Run clang-format on source & header files inside the 'src' directory
fmt:
	@powershell.exe . .\support\commands.ps1; fmt

# Clean/delete all generated files & directories
clean:
	@powershell.exe . .\support\commands.ps1; cleanProject

clang:
	powershell.exe ./clang-build -export-jsondb
	@powershell.exe Write-host "Generated compile_commands.json" -f Green	

wt:
	@%LOCALAPPDATA%\Microsoft\WindowsApps\wt.exe -d %cd% cmd '%comspec% /k %%i\Common7\Tools\vsdevcmd.bat %*'
	@powershell.exe Write-host "Launched windows terminal" -f Green	

vswhere:
	@powershell.exe . .\support\commands.ps1; vsWhere

export:
	@powershell.exe . .\support\commands.ps1; exportCodeOnly cMakeStarter

stats:
	@powershell.exe Write-host "Code stats for ./src" -f Green	
	@tokei .\src --files
## tokei .\src --files --output json > code_stats.json

# Alternative names for the commands above
alias b := build
alias r := buildr
alias release := buildr
