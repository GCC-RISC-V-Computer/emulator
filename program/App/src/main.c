#include <stdio.h>
#include "lib_mcu.h"
#include "lib_math.h"
#include "lib_vga.h"

int main() {
    VGA_power(1);
    ascii_table_init();

    while (1) {
        char something = SR->INPUT_A;
        writeChar(0, 0, ascii[something]);
        delay();
    }
}

/*int row = 0;

// somehow division by 3 seems to fail...
// so this works instead
int32_t next(int32_t a) {
    if (a == 243) return 81;
    if (a == 81) return 27;
    if (a == 27) return 9;
    if (a == 9) return 3;
    if (a == 3) return 1;
    return 0;
}

void printNum(int32_t a) {
    const int length = 5;

    int rem;
    for (int i = 0; i < length; i++) {
        rem = a % 10;
        a = a / 10;
        writeChar(length - i, row, ascii[48 + rem]);
    }
    row = (row + 1) % 8;
}

void sierpinskiCarpet(int32_t width, int32_t x, int32_t y) {
    if (width <= 1) return;
    if ((y > 150) || (x > 200)) return;

    int32_t smallWidth = next(width);
    //printNum(smallWidth);
    //delay();

    for (int currX = x + smallWidth; currX < x + smallWidth*2; currX++) {
        for (int currY = y + smallWidth; currY < y + smallWidth*2; currY++) {
            writePixel(currX, currY);
        }
    }
    sierpinskiCarpet(smallWidth, x, y);
    sierpinskiCarpet(smallWidth, x, y + smallWidth);
    sierpinskiCarpet(smallWidth, x, y + 2*smallWidth);

    sierpinskiCarpet(smallWidth, x + smallWidth, y);
    sierpinskiCarpet(smallWidth, x + smallWidth, y + 2*smallWidth);

    sierpinskiCarpet(smallWidth, x + 2*smallWidth, y);
    sierpinskiCarpet(smallWidth, x + 2*smallWidth, y + smallWidth);
    sierpinskiCarpet(smallWidth, x + 2*smallWidth, y + 2*smallWidth);
}

int main(void){
    VGA_power(1);
    VGA_clear();

    ascii_table_init();
    writeChar(0,0, ascii['H']);
    writeChar(1,0, ascii['E']);
    writeChar(2,0, ascii['L']);
    writeChar(3,0, ascii['L']);
    writeChar(4,0, ascii['O']);
    writeChar(5,0, ascii[' ']);
    writeChar(6,0, ascii['4']);
    writeChar(7,0, ascii['4']);
    writeChar(8,0, ascii['1']);

    //printNum(42);
    writePixel(50, 100);
    delay();
    writePixel(0, 0);
    delay();
    writePixel(0, 100);
    something(243, 0, 0);
}

// -------------------------Experimentation--------------------------


#define MAX_ITER 10

struct Complex {
    int32_t real;
    int32_t imaginary;
};

int32_t absComplex(struct Complex c) {
    return lib_math_sqrt(lib_math_pow(c.real, 2) + lib_math_pow(c.imaginary, 2));
}

struct Complex addComplex(struct Complex a, struct Complex b) {
    struct Complex retVal = { a.real + b.real, a.imaginary + b.imaginary };
    return retVal;
}

struct Complex squareComplex(struct Complex c) {
    int32_t newReal = c.real*c.real - c.imaginary*c.imaginary;
    int32_t newImaginary = 2*c.real*c.imaginary;
    struct Complex retVal = {newReal, newImaginary};
    return retVal;
}

int mandlebrot(struct Complex c) {
    struct Complex z = {0, 0};

    int n = 0;
    while ((absComplex(z) <= 2) && (n < MAX_ITER)) {
        z = addComplex(squareComplex(z), c);
        n++;
    }
    return n;
}
*/