/*******************************************************************
  snake.c containing struct and functions for moving Snake.
 
  Created by Michal Komanec and Ondrej Svarc.
 
 *******************************************************************/

#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "draw_tools.h"
#ifndef MAP_ROWS
#define MAP_ROWS 16
#endif

#ifndef  MAP_COLS
#define MAP_COLS 24
#endif

/**
 * @struct Snake
 * Represents a snake in the game.
 */
typedef struct {
    short heading[2];               // An array representing the heading direction of the snake.
                                    // Index 0 corresponds to the x-coordinate and 
                                    // index 1 corresponds to the y-coordinate.
    short body[MAP_COLS*MAP_ROWS];  // An array representing the positions of the snake's body.
    unsigned short length;          // The current length of the snake's body.
    int score;                      // The score accumulated by the snake during the game.
    unsigned short color;           // The color code used to represent the snake visually in the game.
} Snake;

/**
 * Move the first snake, check for all types of collisions, write changes to frame buffer and possibly eat fruit.
 * 
 * If fruit is eaten, its position is set to -1.
 * If snake dies, its length is set to 0 and its body gets blacked out in the frame buffer
 * 
 * @param snake Snake to be moved.
 * @param other_snake Snake to be checked for collision.
 * @param heading_change The heading change direction:
 *                        - -1: turn left
 *                        -  0: keep straight
 *                        -  1: turn right
 * @param fruit_pos Pointer to the fruit position.
 * @param fb Pointer to the frame buffer.
 */
void move_snake(Snake *snake, Snake *other_snake, short heading_change, int * fruit_pos, unsigned short *fb);

/**
 * Change heading of the given snake with heading_change.

 * 
 * @param snake The snake whose heading will be changed.
 * @param heading_change The heading change direction:
 *                        - -1: turn left
 *                        -  0: keep straight
 *                        -  1: turn right
*/
void change_heading(Snake *snake, short heading_change);
#endif