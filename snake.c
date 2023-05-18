
#include "snake.h"

void move_snake(Snake *snake, short direction) {
    change_heading(snake, direction);
    drawTile(snake->body[snake->length-1], 0, SOME_BUFFER);
    for(int i = snake->length-1; i >= 0; i--) {
        if(i == 0) {
            snake->body[i] == snake->heading[0] + snake->heading[1]*24 + snake->body[i];
        } else {
            snake->body[i] = snake->body[i-1];
        }  
    }
    drawTile(snake->body[0], HEAD_COLOR, SOME_BUFFER);
}

void change_heading(Snake *snake, short heading_change) {
    if (heading_change == -1) {
        snake->heading[0] = snake->heading[1];
        snake->heading[1] = -1*snake->heading[0];
    } else if (heading_change == 1) {
        snake->heading[0] = -1*snake->heading[1];
        snake->heading[1] = snake->heading[0];
    }
}