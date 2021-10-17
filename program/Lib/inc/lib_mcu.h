#ifndef INC_LIB_MCU_H
#define INC_LIB_MCU_H

#include <stdint.h>

#define __I  volatile const         // Defines 'read only' permissions
#define __O  volatile               // Defines 'write only' permissions
#define __IO volatile               // Defines 'read / write' permissions

/******************************************************************************
 * SPECIAL REGISTERS
 *****************************************************************************/

#define SR_BASE_ADDRESS 0x80000000

typedef struct {
    __O uint8_t SEGMENT_DISPLAY;    // Base address register for controll segment display.
    __O uint8_t VGA_POWER;          // Base address register to control state of VGA diplay
    __O uint8_t RESERVED_1;         // Reserved; This address is not in use
    __O uint8_t RESERVED_2;         // Reserved; This address is not in use
    __I uint8_t INPUT_A;            // Base address for Port A (input)
    __I uint8_t INPUT_B;            // Base address for Port B (input)
    __O uint8_t OUTPUT_C;           // Base address for Port C (output)
    __O uint8_t OUTPUT_D;           // Base address for Port D (output)
} special_register_t;

#define SR ((special_register_t *) SR_BASE_ADDRESS) // Special IO registers

/******************************************************************************
 * VRAM
 *****************************************************************************/

#define VRAM_BASE_ADDRESS 0x40000000

void vram_write_8b(uint32_t addr, const uint8_t data);
void vram_write_32b(uint32_t addr, const uint32_t data);

/******************************************************************************
 * VGA
 *****************************************************************************/

void VGA_clear();
void VGA_power(const uint8_t state);

/******************************************************************************
 * OTHER
 *****************************************************************************/

void delay();

#endif