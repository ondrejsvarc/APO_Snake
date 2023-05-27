
#include "snake.h"

void move_snake(Snake *snake, Snake *other_snake, short direction, int *fruit_pos, unsigned short *fb) {
    change_heading(snake, direction);

    bool fruit_eaten = false;
    int new_head_posiion = snake->heading[0] + (-1)*snake->heading[1]*24 + snake->body[0];
    // if fruit has been eaten, lengthen snake (add a link, not incement length var), 
    // else black out last link
    if (new_head_posiion == *fruit_pos) {
        snake->body[snake->length] = snake->body[snake->length-1];
        fruit_eaten = true;
        *fruit_pos = -1;
    } else {
        drawTile(snake->body[snake->length-1], COLOR_BLACK, fb);
    }

    // check for collision with itself 
    for (int i = 0; i < snake->length; i++) {
        if (new_head_posiion == snake->body[i]) {
            for (int j = 0; j < snake->length; j++) {
                drawTile(snake->body[j], COLOR_BLACK, fb);
            }
            snake->length = 0;
            return;  
        }
    }

    // check for collision wih other snake
    int shorter_snake_length = snake->length < other_snake->length ? snake->length : other_snake->length;
    for (int i = 0; i < shorter_snake_length; i++) {
        if (new_head_posiion == other_snake->body[i]) {
            for (int j = 0; j < snake->length; j++) {
                drawTile(snake->body[j], COLOR_BLACK, fb);
            }
            snake->length = 0;
            return;  
        }
    }

    // check for collision with walls
    if ((snake->body[0]%24 == 0 && snake->heading[0] == -1) || (snake->body[0]%24 == 23 && snake->heading[0] == 1)) {
        for (int i = 0; i < snake->length; i++) {
            drawTile(snake->body[i], COLOR_BLACK, fb);
        }
        snake->length = 0;
        return;
    }
    
    // change positions of snake body parts
    for(int i = snake->length-1; i >= 0; i--) {
        if(i == 0) {
            snake->body[i] = snake->heading[0] + (-1)*snake->heading[1]*24 + snake->body[i];
        } else {
            snake->body[i] = snake->body[i-1];
        } 
    } 
    // check for collision with walls
    if (snake->body[0] < 0 || snake->body[0] >= 24*16) {
        for (int i = 1; i < snake->length; i++) {
            drawTile(snake->body[i], COLOR_BLACK, fb);
        }
        snake->length = 0;
        return;
    }
    // draw new head position
    drawTile(snake->body[0], snake->color, fb);

    // update snake length if fruit is eaten
    if (fruit_eaten) {
        snake->length++;
    }
}

void change_heading(Snake *snake, short heading_change) {
    short old_heading[2] = {snake->heading[0], snake->heading[1]};
    if (heading_change == -1) {
        snake->heading[0] = -1*snake->heading[1];
        snake->heading[1] = old_heading[0];
    } else if (heading_change == 1) {
        snake->heading[0] = snake->heading[1];
        snake->heading[1] = -1*old_heading[0];
    }
}