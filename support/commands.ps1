
function generate_ninja_makefiles() {
	Write-host "Generating Ninja build files..." -f Blue
	$Env:PATH += ";$pwd"
	$Env:PATH += ";$pwd/support"
	# cmake -DCMAKE_TOOLCHAIN_FILE="./support/toolchain/tc39xx-tasking.cmake" -G "Ninja Multi-Config" .
	$cmd = ("cmake -G `"Ninja Multi-Config`" .")
	# Write-Host "cmd:" $cmd
	# Write-Host "Env:PATH:" $Env:PATH
	Invoke-Expression "& $cmd | out-null"
	Write-host "Generated Ninja build files" -f Green
}

function fmt() {
	Write-host "`n`nRunning code formatter..." -f Blue
	Write-Host "InvocationName:" $MyInvocation.InvocationName -f Yellow
	Write-Host "Script:" $PSCommandPath -f Yellow
	Write-Host "Path:" $PSScriptRoot -f Yellow
	Write-Host "PWD:" $pwd -f Yellow
	$Env:PATH += ";$pwd"
	$Env:PATH += ";$pwd/support"
	$cmd = (($PSScriptRoot) + "\clang-format-all.ps1 -RepoRoot 'src' -Include '*.h', '*.hpp', '*.cpp' -Exclude '*.g.*'")
	Invoke-Expression "& $cmd | out-null"
	Write-host "Code format done!`n" -f Green
}

function cleanProject() {
	$Directories = "bin", "build", "support/psClang", "psClang", "CMakeFiles", "CMakeCache.txt", "ninja.log", "cmake_install.cmake", ".ninja_log", ".ninja_deps", ".cache", "lib", "build.ninja", "build-Debug.ninja", "build-Release.ninja", "build-RelWithDebInfo.ninja"
 
	#Delete files in each directory
	ForEach ($Dir in $Directories) {
		
		If (Test-Path $Dir) {
			# Folder not exist, delete it!
			Remove-Item -Path $Dir -Recurse -Force
			Write-host "'$Dir'" -f Yellow -NoNewline
			Write-host " Deleted" -f Green
		}
		Else {
			Write-host "'$Dir'" -f Yellow -NoNewline
			Write-host " already deleted!" -f Green
		}
	}
	
	#Get-ChildItem *.sln | foreach { Remove-Item -Path $_.FullName }
	#Get-ChildItem *.vcxproj | foreach { Remove-Item -Path $_.FullName }
	#Get-ChildItem *.filters | foreach { Remove-Item -Path $_.FullName }
	#Get-ChildItem lib\*.lib | foreach { Remove-Item -Path $_.FullName }
	Write-host "Succesfully cleaned" -f Green

}


function exportCodeOnly([string]$name) {
	$theDate = Get-Date -Format "MM.dd.yyyy - hh.mm.ss tt"
	$export_name = "[" + $theDate + "] $name.zip"
	$archiveList = ".\src", ".\docs", ".\vendor", ".\support", ".\.vscode", ".\.clang-format", ".\.gitignore", ".\CMakeLists.txt", ".\clang-build.ps1", ".\justfile", ".\readme.md", ".\dev.bat", ".\nlohmann_json.natvis"
	$all_files_present = 1;
	$missingItem = 'None';

	# Ensure neccessary files/folders are present
	ForEach ($item in $archiveList) {
		
		If (Test-Path $item) {
			# Write-host "'$item'" -f Yellow -NoNewline
			# Write-host " present" -f Green
		}
		Else {
			Write-host "'$item'" -f Yellow -NoNewline
			Write-host " is missing!" -f Red
			$missingItem = $item
			$all_files_present = false
			#break
		}
	}
	If ($all_files_present) {
		$compress = @{
			Path             = $archiveList
			CompressionLevel = "Fastest"
			DestinationPath  = $export_name
		}
		Compress-Archive @compress -Force
		Write-host "Succesfully exported '$export_name'" -f Green
	}
 else {
		Write-host "Failed to export, '$missingItem' is missing!" -f Red
	}
	
	
	# https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.archive/compress-archive?view=powershell-7.3
}

function exportAll() {
	$theDate = Get-Date -Format "MM.dd.yyyy - hh.mm.ss tt"
	$export_name = "[" + $theDate + "] ARIES II Project Data.zip"
	$archiveList = ".\src", ".\docs", ".\vendor", ".\support", ".\bin", ".\.vscode", ".\.clang-format", ".\.gitignore", ".\CMakeLists.txt", ".\clang-build.ps1", ".\justfile", ".\readme.md", ".\dev.bat", ".\nlohmann_json.natvis", ".\justfile"
	$all_files_present = 1
	$missingItem = 'None'

	# Ensure neccessary files/folders are present
	ForEach ($item in $archiveList) {
		If (Test-Path $item) {
			# Write-host "'$item'" -f Yellow -NoNewline
			# Write-host " present" -f Green
		}
		Else {
			Write-host "'$item'" -f Yellow -NoNewline
			Write-host " is missing!" -f Red
			$missingItem = $item
			$all_files_present = false
			break
		}
	}

	if ($all_files_present) {
		$compress = @{
			Path             = $archiveList
			CompressionLevel = "Fastest"
			DestinationPath  = $export_name
		}
		Compress-Archive @compress -Force
		Write-host "Succesfully exported '$export_name'" -f Green
	}
 else {
		Write-host "Failed to export, '$missingItem' is missing!" -f Red
	}
}

function windowsTerminal() {
	#@%LOCALAPPDATA%\Microsoft\WindowsApps\wt.exe -d %cd%
	Write-host "Launched windows terminal" -f Green	
}

function vsWhere() {
	$vswhereLatest = "https://github.com/Microsoft/vswhere/releases/latest/download/vswhere.exe"
	$vswherePath = ".\support\vswhere.exe"
	If (Test-Path $vswherePath) {
		# Write-host "'$item'" -f Yellow -NoNewline
		Write-host "vswhere.exe not found" -f Red
		Write-host "downloading vswhere.exe..." -f Green
		invoke-webrequest $vswhereLatest -OutFile $vswherePath
	}

	Write-host "VS location:" -f Blue
	.\support\vswhere.exe -prerelease -latest -property installationPath
}

function clangBuild(){

	./clang-build -export-jsondb
	Write-host "Generated compile_commands.json" -f Green
}
# TEST FUNCTIONS
function Add-Path($Path) {
	$Path = [Environment]::GetEnvironmentVariable("PATH", "Machine") + [IO.Path]::PathSeparator + $Path
	[Environment]::SetEnvironmentVariable( "Path", $Path, "Machine" )
}

# From ./support folder, run following pecific function like so:
# powershell -command "& { . .\addPath.ps1; printSomething }"
function printSomething() {
	Write-host "PRINT SOMETHING TEST FUNCTION" -f Blue
	Write-host "USER DOMAIN: $Env:UserDomain"
	Write-host "COMPUTER NAME: $Env:ComputerName"

}

# Reference material
# https://stackoverflow.com/questions/1405750/calling-a-specific-powershell-function-from-the-command-line
# https://stackoverflow.com/questions/12850487/invoke-a-second-script-with-arguments-from-a-script
# https://devblogs.microsoft.com/cppblog/finding-the-visual-c-compiler-tools-in-visual-studio-2017/
# # https://superuser.com/questions/1091344/powershell-to-delete-all-files-with-a-certain-file-extension
