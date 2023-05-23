#ifndef SNAKE_H

#include <stdbool.h>
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
} Snake;

/*Function that takes snake struct and heading of the snake and moves the snake*/
void move_snake(Snake *snake, short direction, unsigned short *fb);

void change_heading(Snake *snake, short heading_change);
#endif