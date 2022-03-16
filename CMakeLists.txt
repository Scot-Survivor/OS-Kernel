cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_ASM_COMPILER_WORKS TRUE)
project(myos.kernel)


include_directories(./kernel/include)
include_directories(./kernel/include/arch/i386)
include_directories(./libc/include)
include_directories(./libc/arch/i386)

set(KERNEL_BIN "MyOS.kernel")
set(KERNEL_ISO "MyOs.iso")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra")
set(CMAKE_ASM_FLAGS "-felf32")


file(GLOB_RECURSE kernel_C_SOURCES "kernel/kernel/*.c")
file(GLOB_RECURSE kernel_CPP_SOURCES "kernel/kernel/*.cpp")
file(GLOB_RECURSE kernel_ASM_SOURCES "kernel/arch/i386/*.asm")
file(GLOB_RECURSE kernel_ARCH_C_SOURCES "kernel/arch/i386/*.c")
file(GLOB_RECURSE kernel_ARCH_CPP_SOURCES "kernel/arch/i386/*.cpp")
file(GLOB_RECURSE libc_C_SOURCES "libc/*.c")
file(GLOB_RECURSE libc_CPP_SOURCES "libc/*.cpp")


enable_language(ASM_NASM)

message("Sources:
 kernel_C_SOURCES: ${kernel_C_SOURCES}
 kernel_CPP_SOURCES: ${kernel_CPP_SOURCES}
 kernel_ASM_SOURCES: ${kernel_ASM_SOURCES}
 kernel_ARCH_C_SOURCES: ${kernel_ARCH_C_SOURCES}
 kernel_ARCH_CPP_SOURCES: ${kernel_ARCH_CPP_SOURCES}
 libc_C_SOURCES: ${libc_C_SOURCES}
 libc_CPP_SOURCES: ${libc_CPP_SOURCES}")

# libc library
add_library(libc STATIC
        ${libc_C_SOURCES}
        ${libc_CPP_SOURCES})
set_target_properties(libc PROPERTIES PREFIX "")
set_target_properties(libc PROPERTIES SUFFIX "")

add_executable(${KERNEL_BIN}
        ${kernel_C_SOURCES}
        ${kernel_CPP_SOURCES}
        ${kernel_ARCH_C_SOURCES}
        ${kernel_ARCH_CPP_SOURCES}
        ${kernel_ASM_SOURCES})

target_link_libraries(${KERNEL_BIN}
                        libc)


set_target_properties(${KERNEL_BIN} PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/kernel/arch/i386/linker.ld -ffreestanding -O2 -nostdlib -lgcc")

add_custom_command(TARGET ${KERNEL_BIN} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --only-keep-debug ${KERNEL_BIN} ${KERNEL_BIN}.dbg
        )

