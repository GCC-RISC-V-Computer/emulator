.global _start

.word _estack

.section .text.prologue, "ax"

_start:  
        /* set stack pointer */
        lui sp, %hi(_estack)
        addi sp,sp, %lo(_estack)

        jal  ra, main
        j _exit

_exit:  j _exit