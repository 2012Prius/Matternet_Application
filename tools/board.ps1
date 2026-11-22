param(
    [Parameter(Mandatory)]
    [ValidateSet('Flash', 'Monitor', 'Verify')]
    [string]$Action,
    [string]$Port
)

$ErrorActionPreference = 'Stop'
$project = Split-Path -Parent $PSScriptRoot
$programmer = Join-Path $env:LOCALAPPDATA 'stm32cube/bundles/programmer/2.23.0/bin/STM32_Programmer_CLI.exe'
$firmware = Join-Path $project 'build/debug/UART_Printf.elf'

function Write-Firmware {
    & $programmer -c port=SWD -w $firmware -v -rst
    if ($LASTEXITCODE -ne 0) {
        throw 'STM32CubeProgrammer failed. Check that the board is connected through the ST-LINK USB port.'
    }
}

if ($Action -eq 'Flash') {
    Write-Firmware
    exit
}

if (-not $Port) {
    $ports = @(Get-PnpDevice -PresentOnly -Class Ports -ErrorAction SilentlyContinue |
        Where-Object { $_.InstanceId -like 'FTDIBUS\VID_0403*' } |
        ForEach-Object {
            if ($_.FriendlyName -match '\((COM\d+)\)') { $Matches[1] }
        } | Sort-Object -Unique)

    if ($ports.Count -ne 1) {
        throw "Expected one FTDI COM port. Detected: $($ports -join ', '). Connect the FTDI adapter or pass -Port COM<number>."
    }
    $Port = $ports[0]
}

$serial = [System.IO.Ports.SerialPort]::new(
    $Port, 115200, [System.IO.Ports.Parity]::None, 8, [System.IO.Ports.StopBits]::One
)

try {
    try {
        $serial.Open()
    } catch [UnauthorizedAccessException] {
        throw "Could not open $Port. Close PuTTY or any other serial monitor using it and retry."
    }
    Write-Host "Listening on $Port at 115200 baud, 8 data bits, no parity, 1 stop bit."
    if ($Action -eq 'Verify') {
        $serial.DiscardInBuffer()
        Write-Firmware
        $received = ''
        $deadline = [DateTime]::UtcNow.AddSeconds(5)
        do {
            $received += $serial.ReadExisting()
            if ($received.Contains('Hello, world!')) {
                Write-Host $received
                Write-Host 'PASS: Hello, world! received from USART1.'
                exit
            }
            Start-Sleep -Milliseconds 50
        } while ([DateTime]::UtcNow -lt $deadline)
        throw "Expected Hello, world! from USART1. Check the FTDI RX-to-D1 and ground connections. Captured: $received"
    }

    Write-Host 'Listening for periodic Hello, world! output. Press Ctrl+C to close.'
    while ($true) {
        [Console]::Write($serial.ReadExisting())
        Start-Sleep -Milliseconds 50
    }
} finally {
    $serial.Dispose()
}

