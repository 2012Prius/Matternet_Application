set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(ARM_GCC NAMES arm-none-eabi-gcc
    HINTS "$ENV{LOCALAPPDATA}/stm32cube/bundles/gnu-tools-for-stm32/14.3.1+st.2/bin"
    REQUIRED
)
set(CMAKE_C_COMPILER "${ARM_GCC}")
set(CMAKE_ASM_COMPILER "${ARM_GCC}")

set(cpu_flags "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS_INIT "${cpu_flags}")
set(CMAKE_ASM_FLAGS_INIT "${cpu_flags}")

