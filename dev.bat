@if not defined _echo echo off
cd support

if exist vswhere.exe (
    rem file exists
	for /f "usebackq delims=" %%i in (`vswhere.exe -prerelease -latest -property installationPath`) do (
  	if exist "%%i\Common7\Tools\vsdevcmd.bat" (
		set mypath=%cd%
		cd ..	
		%LOCALAPPDATA%\Microsoft\WindowsApps\wt.exe -d "%cd%" cmd %comspec% /k "%%i\VC\Auxiliary\Build\vcvars64.bat"
		exit /b
    )
)
) else (
    just vswhere
)
ommand prompt not found

exit
