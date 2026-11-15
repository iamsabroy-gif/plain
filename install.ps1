# Installs the 'plain' command on Windows. No compiler needed.
#
#   irm https://raw.githubusercontent.com/iamsabroy-gif/plain/main/install.ps1 | iex
#
# Paste that into PowerShell (press the Windows key, type "PowerShell", press Enter).
# It downloads a ready-made plain.exe, puts it in your user folder, and adds it to your PATH.
$ErrorActionPreference = "Stop"
$repo = if ($env:PLAIN_REPO) { $env:PLAIN_REPO } else { "iamsabroy-gif/plain" }
$base = if ($env:PLAIN_DOWNLOAD_URL) { $env:PLAIN_DOWNLOAD_URL } else { "https://github.com/$repo/releases/latest/download" }
$target = if ($env:PLAIN_INSTALL_DIR) { $env:PLAIN_INSTALL_DIR } else { Join-Path $env:LOCALAPPDATA "Plain\bin" }

function Stop-Here($message) {
    Write-Host ""
    Write-Host "Sorry, I could not finish: $message" -ForegroundColor Red
    return
}

try {
    if (-not [Environment]::Is64BitOperatingSystem) { Stop-Here "this needs a 64-bit Windows."; return }
    $name = "plain-windows-x86_64.exe"
    $work = Join-Path ([IO.Path]::GetTempPath()) ("plain-install-" + [guid]::NewGuid().ToString("N"))
    New-Item -ItemType Directory -Path $work | Out-Null
    $exe = Join-Path $work "plain.exe"
    Write-Host "Downloading Plain for Windows..."
    [Net.ServicePointManager]::SecurityProtocol = [Net.ServicePointManager]::SecurityProtocol -bor [Net.SecurityProtocolType]::Tls12
    try { Invoke-WebRequest -UseBasicParsing -Uri "$base/$name" -OutFile $exe }
    catch { Stop-Here "the download failed. Check your internet connection, then run the command again."; return }

    # check that it arrived whole
    $sumFile = Join-Path $work "sum"
    $haveSum = $true
    try { Invoke-WebRequest -UseBasicParsing -Uri "$base/$name.sha256" -OutFile $sumFile } catch { $haveSum = $false }
    if ($haveSum) {
        $want = ((Get-Content $sumFile -Raw).Trim() -split "\s+")[0].ToLower()
        $got = (Get-FileHash -Algorithm SHA256 $exe).Hash.ToLower()
        if ($got -ne $want) { Stop-Here "the downloaded file is damaged. Run the command again."; return }
    }

    New-Item -ItemType Directory -Force -Path $target | Out-Null
    Copy-Item -Force $exe (Join-Path $target "plain.exe")
    $version = & (Join-Path $target "plain.exe") --version
    if ($LASTEXITCODE -ne 0) { Stop-Here "Plain was installed but will not start on this computer."; return }
    Write-Host "Installed: $target\plain.exe  ($version)"

    $userPath = [Environment]::GetEnvironmentVariable("Path", "User")
    if (($userPath -split ";") -notcontains $target) {
        $newPath = if ([string]::IsNullOrEmpty($userPath)) { $target } else { "$userPath;$target" }
        [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
        Write-Host "I added $target to your PATH."
    }
    $env:Path = "$env:Path;$target"
    Write-Host ""
    Write-Host "Close this window and open a new PowerShell, then try:   plain -e `"say 6 * 7`""
}
finally {
    if ($work -and (Test-Path $work)) { Remove-Item -Recurse -Force $work -ErrorAction SilentlyContinue }
}
