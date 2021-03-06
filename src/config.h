#ifndef __CONFIG_H
#define __CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define KERNEL_TOTAL_INTERRUPTS 512
#define KERNEL_HEAP_SIZE 104857600
#define KERNEL_HEAP_BLOCK_SIZE 4096
#define KERNEL_HEAP_ADDRESS 0x01000000
#define KERNEL_HEAP_TABLE_ADDRESS 0x00007e00

#define MAX_PATH_LEN 250
#define MAX_FILESYSTEMS 5
#define MAX_OPEN_FILES 100

#define GDT_SEGMENTS 6

#define  PROGRAM_BASE_VIRT_ADDR 0x400000
#define  PROGRAM_STACK_SIZE 4096 * 4
#define  PROGRAM_STACK_BASE_VIRT_ADDR 0x3FFF000
#define  PROGRAM_STACK_END PROGRAM_STACK_BASE_VIRT_ADDR - PROGRAM_STACK_SIZE

#define USER_DATA_SEGMENT 0x23
#define USER_CODE_SEGMENT 0x1b
#define MAX_PROCESSES 1024

#endif /* __CONFIG_H */
