/* 
  From:
  https://interrupt.memfault.com/blog/how-to-write-linker-scripts-for-firmware
 */
 
ENTRY(_start)

/* Highest address of the user mode stack */
_estack = 0x7FFFC;    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x200;      /* required amount of heap  */
_Min_Stack_Size = 0x400;     /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
    RAM (rw)      : ORIGIN = 0x00000000, LENGTH = 512K /* KiB */
    FLASH (rx)      : ORIGIN = 0x0000000, LENGTH = 16384K /* KiB */
}


STACK_SIZE = 0x400;

/* Section Definitions */
SECTIONS
{
    .text :
    {
        KEEP(*(.vectors .vectors.*))
        *(.text*)
        *(.rodata*)
    } > FLASH

    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        *(.bss*)
        *(COMMON)
    } > RAM

    .data :
    {
        *(.data*);
    } > RAM AT >FLASH

    /* stack section */
    .stack (NOLOAD):
    {
        . = ALIGN(4);
        . = . + STACK_SIZE;
        . = ALIGN(4);
    } > RAM

    _end = . ;
}