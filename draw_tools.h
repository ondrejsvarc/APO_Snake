#include <stdlib.h>
#include <stdio.h>

#include "font_types.h"

#define COLOR_RED 0xf800
#define COLOR_GREEN 0x7e0
#define COLOR_BLUE 0x1f
#define COLOR_WHITE 0xffff
#define COLOR_BLACK 0x0
#define COLOR_YELLOW 0xffe0


void draw_game_over ( int score1, int score2, unsigned short *fb );
void draw_score ( int score1, int score2, unsigned short *fb );
void draw_pixel ( int x, int y, unsigned short color, unsigned short *fb );
void drawTile ( int index, unsigned short color, unsigned short *fb );
void drawFruit ( int index, unsigned short *fb );
void toString ( char str[], int num );
void drawMenuChoice ( int choice,unsigned short color, unsigned short *fb );
void drawMenu(unsigned short *fb);
int char_width(int ch);
void draw_char(int x, int y, char ch, unsigned short color, unsigned short *fb, int scale );
void draw_pixel_big(int x, int y, unsigned short color, unsigned short *fb, int scale );
void drawDifficultyChoice ( int choice, unsigned short *fb );