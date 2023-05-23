#include <stdlib.h>
#include <stdio.h>

#define COLOR_GREEN 0x7e0


void draw_pixel ( int x, int y, unsigned short color, unsigned short *fb );
void drawTile ( int index, unsigned short color, unsigned short *fb );
void drawFruit ( int index, unsigned short *fb );
void drawMenuChoice ( int choice,unsigned short color, unsigned short *fb );
void drawMenu(unsigned short *fb);