### JUSTFILE - PROJECT SPECIFIC COMMANDS ###########################
# Written by: @y00fie (http://yoofie.net)

# Justfile - https://github.com/casey/just
### SHELL ##########################################################
set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]
#set windows-shell := ["cmd.exe", "/c"]


### SETTINGS ######################################################
APP_NAME := "host_serial_csv"


### COMMANDS ######################################################
# Generates Ninja files only
gen: 
	@. .\support\commands.ps1; generate_ninja_makefiles

# Build Debug version of the software
build: gen
	@Write-host "Running build..." -f Blue
	@ninja -f build.ninja
	@Write-host "Succesfully built project" -f Green

# Build Release version of the SW
buildr: gen
	@Write-host "Running release build..." -f Blue
	@ninja -f build-Release.ninja
	@Write-host "Successfully built project`n`n" -f Green

# Build both release and debug versions of the software
buildall: gen
	@Write-host "`nRunning debug build..." -f Blue
	@ninja -f build-Debug.ninja
	@Write-host "`nRunning release build..." -f Cyan
	@ninja -f build-Release.ninja
	@Write-host "`nRunning release build (with debug info)..." -f Magenta
	@ninja -f build-RelWithDebInfo.ninja
	@Write-host "Succesfully built projects" -f Green

# Ninja Metadata that may be useful
ninja_stuff: gen
	@Write-host "`nGenerating extra Ninja files in 'bin/ninja_stuff'" -f Cyan
	@ninja -t deps > bin/ninja_stuff/file_deps.txt
	@ninja -t inputs > bin/ninja_stuff/inputs.txt
	@ninja -t commands > bin/ninja_stuff/commands.txt
	@ninja -t compdb > bin/ninja_stuff/compdb.txt
	@ninja -t targets > bin/ninja_stuff/targets.txt
	@Write-host "Done" -f Green

# Launch the MSVC dev console which is needed to build the SW
console:
	@dev.bat
	@Write-host "Launched the dev console" -f Green	

# Run clang-format on source & header files inside the 'src' directory
fmt:
	@. .\support\commands.ps1; fmt

# Clean/delete all generated files & directories
clean:
	@. .\support\commands.ps1; cleanProject

clang:
	@. .\support\commands.ps1; clangBuild

# Clean/delete all generated files & directories
rundev:
	@. .\support\commands.ps1; runDev

# Open the newer Windows Terminal 
wt:
	@%LOCALAPPDATA%\Microsoft\WindowsApps\wt.exe -d %cd% cmd '%comspec% /k %%i\Common7\Tools\vsdevcmd.bat %*'
	@Write-host "Launched windows terminal" -f Green	

# Locate Visual Studio Dev environment on your system
vswhere:
	@. .\support\commands.ps1; vsWhere

# Export the project source code to a zip file
export:
	@. .\support\commands.ps1; exportCodeOnly cMakeStarter

# Calculate stats about your code
stats:
	@Write-host "Code stats for ./src" -f Blue
	@. .\support\commands.ps1; stats
	@tokei .\src --files > bin\code_stats.txt
	@tokei .\src --files
	@Write-host "Code stats data generated: 'bin\code_stats.txt'" -f Green

default:
	@just --list

# Alternative names for the commands above
alias b := build
alias r := buildr
alias release := buildr
