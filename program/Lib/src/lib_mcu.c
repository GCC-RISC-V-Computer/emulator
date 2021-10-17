#include "lib_mcu.h"

inline void vram_write_8b(uint32_t addr, const uint8_t data)
{
    uint8_t *vram_p = (uint8_t *)(VRAM_BASE_ADDRESS + addr);
    *vram_p = data;
}

inline void vram_write_32b(uint32_t addr, const uint32_t data)
{
    uint32_t *vram_p = (uint32_t *)(VRAM_BASE_ADDRESS + addr);
    *vram_p = data;
}

inline void delay(){
    for (int i = 0; i < 10000; i++){}
}

inline void VGA_clear(){
    for (int i = 0; i < 4950; i+=4) vram_write_32b(i, 0);
}

inline void VGA_power(const uint8_t state){
    if (state == 0 || state == 1) SR->VGA_POWER = state;
}