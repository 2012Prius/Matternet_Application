cmake_minimum_required(VERSION 3.22)
project(UART_Printf LANGUAGES C ASM)

set(example STM32CubeIDE/Application)
set(hal Drivers/STM32G4xx_HAL_Driver)
set(bsp Drivers/BSP/STM32G4xx_Nucleo)
set(linker_script "${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeIDE/STM32G474RETX_FLASH.ld")

add_executable(UART_Printf
    Src/main.c
    Src/stm32g4xx_hal_msp.c
    Src/stm32g4xx_it.c
    Src/system_stm32g4xx.c
    ${example}/Startup/startup_stm32g474retx.s
    ${example}/User/syscalls.c
    ${example}/User/sysmem.c
    ${bsp}/stm32g4xx_nucleo.c
    Inc/uart1.h
    Src/uart1.c
    Inc/rcc.h
    Src/rcc.c
    Inc/gpio.h
    Src/gpio.c
)

foreach(module IN ITEMS
    hal hal_cortex hal_dma hal_dma_ex hal_exti hal_flash hal_flash_ex
    hal_flash_ramfunc hal_gpio hal_pwr hal_pwr_ex hal_rcc hal_rcc_ex
    hal_tim hal_tim_ex hal_uart hal_uart_ex ll_pwr
)
    target_sources(UART_Printf PRIVATE ${hal}/Src/stm32g4xx_${module}.c)
endforeach()

target_include_directories(UART_Printf PRIVATE
    Inc
    ${hal}/Inc
    ${hal}/Inc/Legacy
    ${bsp}
    Drivers/CMSIS/Include
    Drivers/CMSIS/Device/ST/STM32G4xx/Include
)
target_compile_definitions(UART_Printf PRIVATE USE_HAL_DRIVER STM32G474xx USE_NUCLEO_64 $<$<CONFIG:Debug>:DEBUG>)
target_compile_features(UART_Printf PRIVATE c_std_11)
target_compile_options(UART_Printf PRIVATE -ffunction-sections -fdata-sections -Wall)
target_link_options(UART_Printf PRIVATE
    "LINKER:-T,${linker_script}"
    "LINKER:--gc-sections,-Map=${CMAKE_CURRENT_BINARY_DIR}/UART_Printf.map"
    "LINKER:--print-memory-usage"
    --specs=nano.specs
)
set_target_properties(UART_Printf PROPERTIES
    SUFFIX ".elf"
    LINK_DEPENDS "${linker_script}"
)

