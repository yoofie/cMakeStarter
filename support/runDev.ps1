$installationPath = .\vswhere.exe -prerelease -latest -property installationPath
$xxxx = "$installationPath" + "\VC\Auxiliary\Build\vcvars64.bat"
if ($installationPath -and (test-path "$installationPath\VC\Auxiliary\Build\vcvars64.bat")) {
  & "${env:COMSPEC}" /s /c "`"$installationPath\VC\Auxiliary\Build\vcvars64.bat`" -no_logo && set" | foreach-object {
    $name, $value = $_ -split '=', 2
    set-content env:\"$name" $value
  }
} else {
	Write-host "Runnning... $xxxx" -f Green
}
