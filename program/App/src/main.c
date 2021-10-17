#include <stdio.h>
#include "lib_mcu.h"
#include "lib_math.h"
#include "lib_vga.h"

// somehow division by 3 seems to return incorrect answers
// so this works instead for this demo
int32_t next(int32_t a) {
    if (a == 243) return 81;
    if (a == 81) return 27;
    if (a == 27) return 9;
    if (a == 9) return 3;
    if (a == 3) return 1;
    return 0;
}

// Simple C demo figuring out how to write to the screen
void sierpinskiCarpet(int32_t width, int32_t x, int32_t y) {
    if (width <= 1) return;
    if ((y > 150) || (x > 200)) return;

    int32_t smallWidth = next(width);

    for (int currX = x + smallWidth; currX < x + smallWidth*2; currX++) {
        for (int currY = y + smallWidth; currY < y + smallWidth*2; currY++) {
            writePixel(currX, currY);
        }
    }

    for (int xAddition = 0; xAddition < 3; xAddition++) {
        for (int yAddition = 0; yAddition < 3; yAddition++) {
            if (!((xAddition == 1) && (yAddition == 1))) {
                sierpinskiCarpet(smallWidth, x + xAddition*smallWidth, y + yAddition*smallWidth);
            }
        }
    }
}

int main(void){
    VGA_power(1);

    ascii_table_init();

    sierpinskiCarpet(243, 0, 0);
}