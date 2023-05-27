
#include "snake.h"

void move_snake(Snake *snake, Snake *other_snake, short heading_change, int *fruit_pos, unsigned short *fb) {
    change_heading(snake, heading_change);

    bool fruit_eaten = false;
    int new_head_position = snake->heading[0] + (-1) * snake->heading[1] * MAP_COLS + snake->body[0];
    // if fruit has been eaten, lengthen snake (add a link, not increment length var),
    // else black out last link
    if (new_head_position == *fruit_pos) {
        snake->body[snake->length] = snake->body[snake->length-1];
        fruit_eaten = true;
        *fruit_pos = -1;
    } else {
        draw_tile(snake->body[snake->length - 1], COLOR_BLACK, fb);
    }

    // check for collision with itself 
    for (int i = 0; i < snake->length; i++) {
        if (new_head_position == snake->body[i]) {
            for (int j = 0; j < snake->length; j++) {
                draw_tile(snake->body[j], COLOR_BLACK, fb);
            }
            snake->length = 0;
            return;  
        }
    }

    // check for collision wih other snake
    int shorter_snake_length = snake->length < other_snake->length ? snake->length : other_snake->length;
    for (int i = 0; i < shorter_snake_length; i++) {
        if (new_head_position == other_snake->body[i]) {
            for (int j = 0; j < snake->length; j++) {
                draw_tile(snake->body[j], COLOR_BLACK, fb);
            }
            snake->length = 0;
            return;  
        }
    }

    // check for collision with walls
    if ((snake->body[0]%MAP_COLS == 0 && snake->heading[0] == -1) || (snake->body[0]%MAP_COLS == (MAP_COLS - 1) && snake->heading[0] == 1)) {
        for (int i = 0; i < snake->length; i++) {
            draw_tile(snake->body[i], COLOR_BLACK, fb);
        }
        snake->length = 0;
        return;
    }
    
    // change positions of snake body parts
    for(int i = snake->length-1; i >= 0; i--) {
        if(i == 0) {
            snake->body[i] = snake->heading[0] + (-1)*snake->heading[1]*MAP_COLS + snake->body[i];
        } else {
            snake->body[i] = snake->body[i-1];
        } 
    } 
    // check for collision with walls
    if (snake->body[0] < 0 || snake->body[0] >= MAP_COLS*MAP_ROWS) {
        for (int i = 1; i < snake->length; i++) {
            draw_tile(snake->body[i], COLOR_BLACK, fb);
        }
        snake->length = 0;
        return;
    }
    // draw new head position
    draw_tile(snake->body[0], snake->color, fb);

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