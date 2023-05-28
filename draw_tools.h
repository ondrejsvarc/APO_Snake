/*******************************************************************
  draw_tools.h containing functions for drawing to frame buffer.
 
  Created by Ondrej Svarc and Michal Komanec.
 
 *******************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "font_types.h"

#define COLOR_RED 0xf800
#define COLOR_GREEN 0x7e0
#define COLOR_BLUE 0x1f
#define COLOR_WHITE 0xffff
#define COLOR_BLACK 0x0
#define COLOR_YELLOW 0xffe0

#define PATH_TO_MENU_IMAGE "/tmp/komanmi1/snake.ppm"  // replace "/tmp/komanmi1" with path to target directory


/**
 * Fills the framebuffer with black color.
 *
 * @param fb The framebuffer pointer.
 */
void paint_it_black ( unsigned short *fb );

/**
 * Draws the "Game Over" screen with scores and instructions.
 *
 * @param score1 The score for player 1.
 * @param score2 The score for player 2.
 * @param fb     The framebuffer pointer.
 */
void draw_game_over ( int score1, int score2, unsigned short *fb );

/**
 * Draws the scores on the screen.
 *
 * @param score1 The score for player 1.
 * @param score2 The score for player 2.
 * @param fb     The framebuffer pointer.
 */
void draw_score ( int score1, int score2, unsigned short *fb );

/**
 * Draws a tile at the specified index on the screen.
 *
 * @param index The index of the tile position on the game map.
 * @param color The color of the tile.
 * @param fb    A pointer to the frame buffer.
 */
void draw_tile (int index, unsigned short color, unsigned short *fb );

/**
 * Draws a fruit at the specified index on the screen.
 *
 * @param index The index of the fruit position on the game map.
 * @param fb    A pointer to the frame buffer.
 */
void draw_fruit (int index, unsigned short *fb );

/**
 * Converts an integer to a string representation.
 * If the number is bigger than 99999 it fills sthe string with 9.
 *
 * @param str The character array to store the resulting string.
 * @param num The integer to be converted to a string.
 */
void to_string ( char str[], int num );

/**
 * Draws square next to the selected menu choice on the screen. 
 * Can be used to remove selection by giving it black color.
 *
 * @param choice The menu choice index (0 for 0 players, 1 for 1 player,
 *                  2 for 2 players, 3 for exit).
 * @param color  The color of the menu choice.
 * @param fb     A pointer to the frame buffer.
 */
void draw_menu_choice (int choice, unsigned short color, unsigned short *fb );

/**
 * Loads and displays a menu image on the screen, along with the initial game mode and difficulty choices.
 *
 * @param fb The framebuffer pointer.
 */
void draw_menu(unsigned short *fb);

/**
 * Draws the selected difficulty choice on the screen.
 *
 * @param choice The difficulty choice index (0 for easy, 1 for medium, 2 for hard).
 * @param fb     A pointer to the frame buffer.
 */
void draw_difficulty_choice (int choice, unsigned short *fb );

void draw_pixel ( int x, int y, unsigned short color, unsigned short *fb );
int char_width(int ch);
void draw_char(int x, int y, char ch, unsigned short color, unsigned short *fb, int scale );
void draw_pixel_big(int x, int y, unsigned short color, unsigned short *fb, int scale );
