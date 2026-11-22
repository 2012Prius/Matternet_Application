# NUCLEO-G474RE UART printf

This starter uses [STMicroelectronics' UART_Printf example](https://github.com/STMicroelectronics/STM32CubeG4/tree/140db648b016ba49b05ca790b5b66e3477807839/Projects/NUCLEO-G474RE/Examples/UART/UART_Printf) and its matching HAL, CMSIS, and Nucleo BSP. The CMake build uses the example's startup assembly and linker script. The firmware routes printf through USART1 to an external FTDI adapter.

## Build and run in VS Code

1. Open this folder in VS Code and trust the workspace when prompted.
2. Press **Ctrl+Shift+B** to build. The firmware is written to `build/debug/UART_Printf.elf`.
3. Connect the Nucleo to Windows through ST-LINK USB for programming. Connect FTDI RXD to Nucleo D1 (PC4), and connect the grounds. Use 3.3 V logic and leave FTDI VCC disconnected.
4. From the Command Palette, choose **Tasks: Run Task** → **Flash and run (ST-LINK)** to program and reset the board.
5. Open the FTDI COM port (COM4 on the original setup) in PuTTY at **115200 baud, 8 data bits, no parity, 1 stop bit, and no flow control**. The firmware prints **Hello, world!** about once a second.

With PuTTY closed, use **Monitor FTDI UART (115200, 8N1)** to watch the output in VS Code or **Flash and verify UART printf** to flash and check for the greeting automatically. USART1 uses PC4 for TX and PC5 (D0) for RX. RX is optional for this transmit-only example.

To step through startup, select **Debug UART Printf (ST-LINK)** and press **F5**. Execution stops at `main`. Continue execution to reach the two prints. Start editing in [Src/main.c](Src/main.c).

## Toolchain

Install **STM32CubeIDE for Visual Studio Code**. Bundle versions are recorded under `.settings/`. On another Windows machine, install the project's bundles from the STM32Cube Bundles Manager, or run `cube bundle --yes install --project` from this directory with STM32CubeCLI. The project uses ST's default per-user bundle installation directory. If Windows does not enumerate the ST-LINK virtual COM port, install ST's USB driver package with administrator rights.

