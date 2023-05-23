#include <stdlib.h>
#include <stdio.h>


void draw_pixel ( int x, int y, unsigned short color, unsigned short *fb );
void drawTile ( int index, unsigned short color, unsigned short *fb );
void drawFruit ( int index, unsigned short *fb );
void drawMenuChoice ( int choice,unsigned short color, unsigned short *fb );
void drawMenu(unsigned char *parlcd_mem_base, unsigned short *fb);