#ifndef GRACEFUL_BT_I386_PC_BOOT_HEADER
#define GRACEFUL_BT_I386_PC_BOOT_HEADER

#include "common/offsets.h"

/* The signature for bootloader.  */
#define GRACEFUL_BL_BOOT_MACHINE_SIGNATURE	0xaa55

/* The offset of the start of BPB (BIOS Parameter Block).  */
#define GRACEFUL_BL_BOOT_MACHINE_BPB_START	0x3

/* The offset of the end of BPB (BIOS Parameter Block).  */
#define GRACEFUL_BL_BOOT_MACHINE_BPB_END	0x5a

/* The offset of KERNEL_SECTOR.  */
#define GRACEFUL_BL_BOOT_MACHINE_KERNEL_SECTOR	0x5c

/* The offset of BOOT_DRIVE.  */
#define GRACEFUL_BL_BOOT_MACHINE_BOOT_DRIVE	0x64

/* The offset of BOOT_DRIVE_CHECK.  */
#define GRACEFUL_BL_BOOT_MACHINE_DRIVE_CHECK	0x66

/* The offset of a magic number used by Windows NT.  */
#define GRACEFUL_BL_BOOT_MACHINE_WINDOWS_NT_MAGIC	0x1b8

/* The offset of the start of the partition table.  */
#define GRACEFUL_BL_BOOT_MACHINE_PART_START	0x1be

/* The offset of the end of the partition table.  */
#define GRACEFUL_BL_BOOT_MACHINE_PART_END	0x1fe

/* The stack segment.  */
#define GRACEFUL_BL_BOOT_MACHINE_STACK_SEG	0x2000

/* The segment of disk buffer. The disk buffer MUST be 32K long and
   cannot straddle a 64K boundary.  */
#define GRACEFUL_BL_BOOT_MACHINE_BUFFER_SEG	0x7000

/* The flag for BIOS drive number to designate a hard disk vs. a
   floppy.  */
#define GRACEFUL_BL_BOOT_MACHINE_BIOS_HD_FLAG	0x80

/* The address where the kernel is loaded.  */
#define GRACEFUL_BL_BOOT_MACHINE_KERNEL_ADDR	(GRACEFUL_BL_BOOT_MACHINE_KERNEL_SEG << 4)
#define GRACEFUL_BL_BOOT_I386_PC_KERNEL_ADDR    (GRACEFUL_BL_BOOT_I386_PC_KERNEL_SEG<<4)

/* The size of a block list used in the kernel startup code.  */
#define GRACEFUL_BL_BOOT_MACHINE_LIST_SIZE	12

#define GRACEFUL_BL_BOOT_MACHINE_PXE_DL	0x7f

#endif
