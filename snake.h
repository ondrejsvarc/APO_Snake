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

typedef struct {
    short heading[2];
    short body[MAP_COLS*MAP_ROWS];
    unsigned short length;
    int score;
    unsigned short color;
} Snake;

/**
 * Move the first snake, check for all types of collisions, write changes to frame buffer and possibly eat fruit.
 * 
 * If fruit is eaten, its position is set to -1.
 * If snake dies, its length is set to 0 and its body gets blacked out in the frame buffer
 * 
 * @param snake Snake to be moved.
 * @param other_snake Snake to be checked for collision.
 * @param direction The direction change, see function change_heading.
 * @param fruit_pos Pointer to the fruit position.
 * @param fb Pointer to the frame buffer.
 */
void move_snake(Snake *snake, Snake *other_snake, short direction, int * fruit_pos, unsigned short *fb);

/**
 * Change heading of the given snake with heading_change.
 * 
 * heading_change options: {-1 = turn left, 0 = keep straight, 1 = turn right}
 * 
 * @param snake The snake whose heading will be chaned.
 * @param heading_change The heading change direction.
*/
void change_heading(Snake *snake, short heading_change);
#endif