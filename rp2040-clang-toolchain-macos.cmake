
# Toolchain file for using Clang with RP2040 on macOS

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Use Clang for compiling
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Target triple and architecture
set(CMAKE_C_FLAGS "-target arm-none-eabi -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft")
set(CMAKE_CXX_FLAGS "-target arm-none-eabi -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft")

# Use GNU linker and tools from ARM toolchain
find_program(ARM_NONE_EABI_AS arm-none-eabi-as)
find_program(ARM_NONE_EABI_LD arm-none-eabi-ld)
find_program(ARM_NONE_EABI_AR arm-none-eabi-ar)
find_program(ARM_NONE_EABI_OBJCOPY arm-none-eabi-objcopy)
find_program(ARM_NONE_EABI_OBJDUMP arm-none-eabi-objdump)

set(CMAKE_ASM_COMPILER clang)
set(CMAKE_LINKER ${ARM_NONE_EABI_LD})
set(CMAKE_AR ${ARM_NONE_EABI_AR})
set(CMAKE_OBJCOPY ${ARM_NONE_EABI_OBJCOPY})
set(CMAKE_OBJDUMP ${ARM_NONE_EABI_OBJDUMP})

# Avoid standard libraries
set(CMAKE_EXE_LINKER_FLAGS_INIT "-nostdlib")

# Skip default standard library search
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
