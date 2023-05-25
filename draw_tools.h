#include <stdlib.h>
#include <stdio.h>

#include "font_types.h"

#define COLOR_GREEN 0x7e0
#define COLOR_WHITE 0xffff


void draw_score ( int score1, int score2, unsigned short *fb );
void draw_pixel ( int x, int y, unsigned short color, unsigned short *fb );
void drawTile ( int index, unsigned short color, unsigned short *fb );
void drawFruit ( int index, unsigned short *fb );
void drawMenuChoice ( int choice,unsigned short color, unsigned short *fb );
void drawMenu(unsigned short *fb);