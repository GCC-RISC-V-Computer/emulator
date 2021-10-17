#include "lib_vga.h"

char ascii[130][8];
int cursor_delay;
int cursor_visible;
int CURSOR_DELAY;

inline void writePixel(int x, int y){

    int hor_word = x / 32;

    int *VRAM = 0x40000000 + (hor_word << 2) + ((y * 8) << 2);
    int data = *VRAM;

    data |= (1 << (x % 32));

    *VRAM = data;
}

inline void clearPixel(int x, int y){

    int hor_word = x / 32;

    int *VRAM = 0x40000000 + (hor_word << 2) + ((y * 8) << 2);
    int data = *VRAM;

    data &= ~(1 << (x % 32));

    *VRAM = data;
}

inline void writeChar(int x, int y, char arr[]){

    int hor_word = x;
    int precalc = 0x40000000 + hor_word + (y*256);

    for (int i = 0; i < 8; i++){
        char *VRAM = precalc + (i*32);
        *VRAM = arr[i];
    }
}

inline void ascii_table_init(){
    // space
    ascii[32][0]=0;ascii[32][1]=0;ascii[32][2]=0;ascii[32][3]=0;ascii[32][4]=0;ascii[32][5]=0;ascii[32][6]=0;ascii[32][7]=0;
    // special characters
    ascii[62][0]=0;ascii[62][1]=0;ascii[62][2]=0;ascii[62][3]=2;ascii[62][4]=4;ascii[62][5]=8;ascii[62][6]=4;ascii[62][7]=2;
    ascii[46][0]=0;ascii[46][1]=0;ascii[46][2]=0;ascii[46][3]=0;ascii[46][4]=0;ascii[46][5]=0;ascii[46][6]=0;ascii[46][7]=2;
    ascii[44][0]=0;ascii[44][1]=0;ascii[44][2]=0;ascii[44][3]=0;ascii[44][4]=0;ascii[44][5]=0;ascii[44][6]=0;ascii[44][7]=2;
    ascii[63][0]=0;ascii[63][1]=0;ascii[63][2]=0;ascii[63][3]=14;ascii[63][4]=16;ascii[63][5]=12;ascii[63][6]=0;ascii[63][7]=4;
    ascii[95][0]=0;ascii[95][1]=0;ascii[95][2]=0;ascii[95][3]=0;ascii[95][4]=0;ascii[95][5]=0;ascii[95][6]=0;ascii[95][7]=62;
    ascii[58][0]=0;ascii[58][1]=0;ascii[58][2]=0;ascii[58][3]=0;ascii[58][4]=0;ascii[58][5]=2;ascii[58][6]=0;ascii[58][7]=2;
    ascii[45][0]=0;ascii[45][1]=0;ascii[45][2]=0;ascii[45][3]=0;ascii[45][4]=0;ascii[45][5]=62;ascii[45][6]=0;ascii[45][7]=0;
    // numbers
    ascii[48][0]=0;ascii[48][1]=0;ascii[48][2]=0;ascii[48][3]=28;ascii[48][4]=34;ascii[48][5]=34;ascii[48][6]=34;ascii[48][7]=28;
    ascii[49][0]=0;ascii[49][1]=0;ascii[49][2]=0;ascii[49][3]=8;ascii[49][4]=12;ascii[49][5]=8;ascii[49][6]=8;ascii[49][7]=8;
    ascii[50][0]=0;ascii[50][1]=0;ascii[50][2]=0;ascii[50][3]=30;ascii[50][4]=32;ascii[50][5]=28;ascii[50][6]=2;ascii[50][7]=62;
    ascii[51][0]=0;ascii[51][1]=0;ascii[51][2]=0;ascii[51][3]=30;ascii[51][4]=32;ascii[51][5]=28;ascii[51][6]=32;ascii[51][7]=30;
    ascii[52][0]=0;ascii[52][1]=0;ascii[52][2]=0;ascii[52][3]=24;ascii[52][4]=20;ascii[52][5]=18;ascii[52][6]=62;ascii[52][7]=16;
    ascii[53][0]=0;ascii[53][1]=0;ascii[53][2]=0;ascii[53][3]=62;ascii[53][4]=2;ascii[53][5]=30;ascii[53][6]=32;ascii[53][7]=30;
    ascii[54][0]=0;ascii[54][1]=0;ascii[54][2]=0;ascii[54][3]=28;ascii[54][4]=2;ascii[54][5]=30;ascii[54][6]=34;ascii[54][7]=28;
    ascii[55][0]=0;ascii[55][1]=0;ascii[55][2]=0;ascii[55][3]=62;ascii[55][4]=32;ascii[55][5]=16;ascii[55][6]=8;ascii[55][7]=4;
    ascii[56][0]=0;ascii[56][1]=0;ascii[56][2]=0;ascii[56][3]=28;ascii[56][4]=34;ascii[56][5]=28;ascii[56][6]=34;ascii[56][7]=28;
    ascii[57][0]=0;ascii[57][1]=0;ascii[57][2]=0;ascii[57][3]=28;ascii[57][4]=34;ascii[57][5]=60;ascii[57][6]=32;ascii[57][7]=28;
    // uppercase
    ascii[65][0]=0;ascii[65][1]=0;ascii[65][2]=0;ascii[65][3]=28;ascii[65][4]=34;ascii[65][5]=62;ascii[65][6]=34;ascii[65][7]=34;
    ascii[66][0]=0;ascii[66][1]=0;ascii[66][2]=0;ascii[66][3]=30;ascii[66][4]=34;ascii[66][5]=30;ascii[66][6]=34;ascii[66][7]=30;
    ascii[67][0]=0;ascii[67][1]=0;ascii[67][2]=0;ascii[67][3]=28;ascii[67][4]=34;ascii[67][5]=2;ascii[67][6]=34;ascii[67][7]=28;
    ascii[68][0]=0;ascii[68][1]=0;ascii[68][2]=0;ascii[68][3]=30;ascii[68][4]=34;ascii[68][5]=34;ascii[68][6]=34;ascii[68][7]=30;
    ascii[69][0]=0;ascii[69][1]=0;ascii[69][2]=0;ascii[69][3]=28;ascii[69][4]=2;ascii[69][5]=14;ascii[69][6]=2;ascii[69][7]=28;
    ascii[70][0]=0;ascii[70][1]=0;ascii[70][2]=0;ascii[70][3]=60;ascii[70][4]=2;ascii[70][5]=62;ascii[70][6]=2;ascii[70][7]=2;
    ascii[71][0]=0;ascii[71][1]=0;ascii[71][2]=0;ascii[71][3]=60;ascii[71][4]=2;ascii[71][5]=58;ascii[71][6]=34;ascii[71][7]=60;
    ascii[72][0]=0;ascii[72][1]=0;ascii[72][2]=0;ascii[72][3]=34;ascii[72][4]=34;ascii[72][5]=62;ascii[72][6]=34;ascii[72][7]=34;
    ascii[73][0]=0;ascii[73][1]=0;ascii[73][2]=0;ascii[73][3]=8;ascii[73][4]=8;ascii[73][5]=8;ascii[73][6]=8;ascii[73][7]=8;
    ascii[74][0]=0;ascii[74][1]=0;ascii[74][2]=0;ascii[74][3]=56;ascii[74][4]=32;ascii[74][5]=32;ascii[74][6]=34;ascii[74][7]=28;
    ascii[75][0]=0;ascii[75][1]=0;ascii[75][2]=0;ascii[75][3]=34;ascii[75][4]=18;ascii[75][5]=14;ascii[75][6]=18;ascii[75][7]=34;
    ascii[76][0]=0;ascii[76][1]=0;ascii[76][2]=0;ascii[76][3]=2;ascii[76][4]=2;ascii[76][5]=2;ascii[76][6]=2;ascii[76][7]=30;
    ascii[77][0]=0;ascii[77][1]=0;ascii[77][2]=0;ascii[77][3]=34;ascii[77][4]=54;ascii[77][5]=42;ascii[77][6]=34;ascii[77][7]=34;
    ascii[78][0]=0;ascii[78][1]=0;ascii[78][2]=0;ascii[78][3]=34;ascii[78][4]=38;ascii[78][5]=42;ascii[78][6]=50;ascii[78][7]=34;
    ascii[79][0]=0;ascii[79][1]=0;ascii[79][2]=0;ascii[79][3]=28;ascii[79][4]=34;ascii[79][5]=34;ascii[79][6]=34;ascii[79][7]=28;
    ascii[80][0]=0;ascii[80][1]=0;ascii[80][2]=0;ascii[80][3]=30;ascii[80][4]=34;ascii[80][5]=30;ascii[80][6]=2;ascii[80][7]=2;
    ascii[81][0]=0;ascii[81][1]=0;ascii[81][2]=0;ascii[81][3]=28;ascii[81][4]=34;ascii[81][5]=34;ascii[81][6]=42;ascii[81][7]=28;
    ascii[82][0]=0;ascii[82][1]=0;ascii[82][2]=0;ascii[82][3]=30;ascii[82][4]=34;ascii[82][5]=30;ascii[82][6]=18;ascii[82][7]=34;
    ascii[83][0]=0;ascii[83][1]=0;ascii[83][2]=0;ascii[83][3]=60;ascii[83][4]=2;ascii[83][5]=28;ascii[83][6]=32;ascii[83][7]=30;
    ascii[84][0]=0;ascii[84][1]=0;ascii[84][2]=0;ascii[84][3]=62;ascii[84][4]=8;ascii[84][5]=8;ascii[84][6]=8;ascii[84][7]=8;
    ascii[85][0]=0;ascii[85][1]=0;ascii[85][2]=0;ascii[85][3]=34;ascii[85][4]=34;ascii[85][5]=34;ascii[85][6]=34;ascii[85][7]=28;
    ascii[86][0]=0;ascii[86][1]=0;ascii[86][2]=0;ascii[86][3]=34;ascii[86][4]=34;ascii[86][5]=34;ascii[86][6]=20;ascii[86][7]=8;
    ascii[87][0]=0;ascii[87][1]=0;ascii[87][2]=0;ascii[87][3]=42;ascii[87][4]=42;ascii[87][5]=42;ascii[87][6]=42;ascii[87][7]=20;
    ascii[88][0]=0;ascii[88][1]=0;ascii[88][2]=0;ascii[88][3]=34;ascii[88][4]=20;ascii[88][5]=8;ascii[88][6]=20;ascii[88][7]=34;
    ascii[89][0]=0;ascii[89][1]=0;ascii[89][2]=0;ascii[89][3]=62;ascii[89][4]=16;ascii[89][5]=8;ascii[89][6]=4;ascii[89][7]=62;
    ascii[90][0]=0;ascii[90][1]=0;ascii[90][2]=0;ascii[90][3]=34;ascii[90][4]=30;ascii[90][5]=24;ascii[90][6]=8;ascii[90][7]=8;
}

inline void display_terminal(){
    writeChar(0,0, ascii['P']);
    writeChar(1,0, ascii['I']);
    writeChar(2,0, ascii['N']);
    writeChar(3,0, ascii['E']);
    writeChar(4,0, ascii['S']);
    writeChar(5,0, ascii['H']);
    writeChar(6,0, ascii['E']);
    writeChar(7,0, ascii['L']);
    writeChar(8,0, ascii['L']);
    // writeChar(4,0, ascii['O']);
    // writeChar(5,0, ascii['S']);

    writeChar(10,0, ascii['V']);
    writeChar(11,0, ascii['6']);

    writeChar(0,1, ascii['>']);
    
    // set_cursor(1,1);
    CURSOR_DELAY = 5000;
    cursor_delay = 0;
    cursor_visible = 1;
}