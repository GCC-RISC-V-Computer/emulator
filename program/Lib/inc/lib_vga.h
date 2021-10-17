#ifndef INC_LIB_VGA_H
#define INC_LIB_VGA_H

// #include "lib_mcu.h"

#include <stdint.h>

typedef char string[300];

void writePixel(int x, int y);
void clearPixel(int x, int y);
void writeChar(int x, int y, char arr[]);

void ascii_table_init();
void display_terminal();

extern char ascii[130][8];

extern int cursor_delay;
extern int cursor_visible;
extern int CURSOR_DELAY;
// char keyboard_port;


#endif