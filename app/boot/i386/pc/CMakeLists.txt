project ("i386-pc")

# gcc 针对 .S 会做预处理, 对 .s 不做预处理
# -fno-builtin表示使用C语言的buildin函数时，需要带上前缀_builtin

set (LD_FLAGS -Os
        -Wall -W -Wshadow -Wpointer-arith -Wundef -Wchar-subscripts -Wcomment
        -Wdeprecated-declarations -Wdisabled-optimization -Wdiv-by-zero -Wfloat-equal
        -Wformat-extra-args -Wformat-security -Wformat-y2k -Wimplicit -Wimplicit-function-declaration
        -Wimplicit-int -Wmain -Wmissing-braces -Wmissing-format-attribute -Wmultichar -Wparentheses
        -Wreturn-type -Wsequence-point -Wshadow -Wsign-compare -Wswitch -Wtrigraphs -Wunknown-pragmas
        -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable
        -Wwrite-strings -Wnested-externs -Wstrict-prototypes -g -Wredundant-decls -Wmissing-prototypes
        -Wmissing-prototypes -Wmissing-declarations -Wextra -Wattributes -Wendif-labels -Winit-self
        -Wint-to-pointer-cast -Winvalid-pch -Wmissing-field-initializers -Wnonnull -Woverflow -Wvla
        -Wpointer-to-int-cast -Wstrict-aliasing -Wvariadic-macros -Wvolatile-register-var -Wpointer-sign
        -Wmissing-include-dirs -Wmissing-prototypes -Wmissing-declarations -Wformat=2
        -march=i386 -mrtd -mregparm=3
        -falign-jumps=1 -falign-loops=1 -falign-functions=1 -freg-struct-return -mno-mmx
        -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -msoft-float -fno-dwarf2-cfi-asm -mno-stack-arg-probe
        -fno-asynchronous-unwind-tables -Qn -fno-stack-protector -Wtrampolines -Werror -fno-builtin
        )

include_directories (${CMAKE_SOURCE_DIR}/app/)

FILE (GLOB I386_PC_BOOT_IMG_HDR ${CMAKE_SOURCE_DIR}/app/boot/i386/pc/boot.h)
FILE (GLOB I386_PC_BOOT_IMG_SRC ${CMAKE_SOURCE_DIR}/app/boot/i386/pc/boot.S)
source_group("i386-pc-boot" ${I386_PC_BOOT_IMG_SRC} ${I386_PC_BOOT_IMG_HDR})

exec_program (rm ARGS -rf "${CMAKE_BINARY_DIR}/.tmp/")
exec_program (mkdir ARGS -p "${CMAKE_BINARY_DIR}/.tmp/")

exec_program (rm ARGS -rf "${CMAKE_BINARY_DIR}/img/")
exec_program (mkdir ARGS -p "${CMAKE_BINARY_DIR}/img/")

# -DHYBRID_BOOT=1
add_custom_command (OUTPUT ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.o
        COMMAND gcc -g
        -DHYBRID_BOOT=1 -DASM_FILE=1 -D_FILE_OFFSET_BITS=64 -DGRACEFUL_BL_MACHINE=I386_PC
        -DHAVE_CONFIG_H -DGRACEFUL_BL_MACHINE_PCBIOS=1
        -m32 -nostdinc -isystem /usr/lib/gcc/x86_64-pc-linux-gnu/11.1.0/include
        -I${CMAKE_SOURCE_DIR} -I${CMAKE_SOURCE_DIR}/app/ -I${CMAKE_SOURCE_DIR}/app/boot/i386/pc
        -m32 -msoft-float -fno-PIE -fno-pie
        -c ${I386_PC_BOOT_IMG_SRC}
        -o ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.o)

add_custom_command (OUTPUT ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.img
        COMMAND gcc -std=gnu99 -Os -m32 # ${LD_FLAGS}
        -Wl,-melf_i386 -no-pie -Wl,--build-id=none -nostdlib
        -Wl,-N -Wl,-S -Wl,-N -Wl,-Ttext,0x7C00
        ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.o
        -o ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.img
        MAIN_DEPENDENCY ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.o
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/img/i386-pc-boot.img
        COMMAND objcopy --strip-unneeded -R .note -R .comment -R .note.gnu.build-id
        -R .MIPS.abiflags -R .reginfo -R .rel.dyn -R .note.gnu.gold-version -R .note.gnu.property -R .ARM.exidx
        ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.img -O binary
        ${CMAKE_BINARY_DIR}/img/i386-pc-boot.img
        DEPENDS ${CMAKE_BINARY_DIR}/.tmp/i386-pc-boot.img
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_custom_target (i386-pc-boot ALL DEPENDS ${CMAKE_BINARY_DIR}/img/i386-pc-boot.img)
