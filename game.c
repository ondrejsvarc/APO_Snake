#include "game.h"

void start_zero_players_game(long int speed, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base) {
    for (int i = 0; i < 320*480 ; i++) {
        fb[i] = 0;  
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    Snake ai_snake1 = {
        {1,0},
        {0},
        1,
        0,
        COLOR_RED
    };
    ai_snake1.body[0] = 3*16 + 2;
    drawTile(ai_snake1.body[0], ai_snake1.color, fb);
    changeRedRGBLED(0, mem_base);

    Snake ai_snake2 = {
        {-1,0},
        {0},
        1,
        0,
        COLOR_BLUE
    };
    ai_snake2.body[0] = 8*16 + 11;
    drawTile(ai_snake2.body[0], ai_snake2.color, fb);
    changeBlueRGBLED(0, mem_base);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    int dead_snakes = 0;
    short ai_move1 = 0;
    short ai_move2 = 0;
    int fruit_pos = generateFruitPosition(&ai_snake1, &ai_snake2);
    drawFruit(fruit_pos, fb);
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = speed};

    while(dead_snakes < 2) {
        if(abort_game(mem_base)) {
            game_over(ai_snake1.score, ai_snake2.score, fb, mem_base, parlcd_mem_base);
            return;
        }
        if (ai_snake1.length > 0) {
            changeRedRGBLED(0, mem_base);
            ai_move1 = generateAiMove(&ai_snake1, &ai_snake2, fruit_pos);
            move_snake(&ai_snake1, &ai_snake2, ai_move1, &fruit_pos, fb);
            if (ai_snake1.length == 0) {
                dead_snakes++;
                changeRedRGBLED(2, mem_base);
            }
            if (fruit_pos == -1) {
                changeRedRGBLED(1, mem_base);
                fruit_pos = generateFruitPosition(&ai_snake1, &ai_snake2);
                drawFruit(fruit_pos, fb);
            }
        } 
        if (ai_snake2.length > 0) {
            changeBlueRGBLED(0, mem_base);
            ai_move2 = generateAiMove(&ai_snake2, &ai_snake1, fruit_pos);
            move_snake(&ai_snake2, &ai_snake1, ai_move2, &fruit_pos, fb);
            if (ai_snake2.length == 0) {
                dead_snakes++;
                changeBlueRGBLED(2, mem_base);
            } 
            if (fruit_pos == -1) {
                changeBlueRGBLED(1, mem_base);
                fruit_pos = generateFruitPosition(&ai_snake1, &ai_snake2);
                drawFruit(fruit_pos, fb);
            }
        }


        for (int i = 0; i < 320*480; i++) {
            parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);

        changeLengthLed(ai_snake1.length, ai_snake2.length, mem_base);
        
        updateScores(&ai_snake1, &ai_snake2, fb);
        clock_nanosleep(1, 0, &loop_delay, NULL);
    }
    game_over(ai_snake1.score, ai_snake2.score, fb, mem_base, parlcd_mem_base);
}

void start_one_player_game(long int speed, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base) {
    for (int i = 0; i < 320*480 ; i++) {
        fb[i] = 0;  
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    Snake ai_snake = {
        {1,0},
        {0},
        1,
        0,
        COLOR_RED
    };
    ai_snake.body[0] = 3*16 + 2;
    drawTile(ai_snake.body[0], ai_snake.color, fb);
    changeRedRGBLED(0, mem_base);

    Snake player_snake = {
        {-1,0},
        {0},
        1,
        0,
        COLOR_BLUE
    };
    player_snake.body[0] = 8*16 + 11;
    drawTile(player_snake.body[0], player_snake.color, fb);
    changeBlueRGBLED(0, mem_base);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    int dead_snakes = 0;
    short ai_move = 0;
    short player_move = 0;
    short player_knob_value = getBlueValue(mem_base);
    int fruit_pos = generateFruitPosition(&ai_snake, &player_snake);
    drawFruit(fruit_pos, fb);
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = speed};

    while(dead_snakes < 2) {
        if(abort_game(mem_base)) {
            game_over(ai_snake.score, player_snake.score, fb, mem_base, parlcd_mem_base);
            return;
        }
        if (ai_snake.length > 0) {
            changeRedRGBLED(0, mem_base);
            ai_move = generateAiMove(&ai_snake, &player_snake, fruit_pos);
            move_snake(&ai_snake, &player_snake, ai_move, &fruit_pos, fb);
            if (ai_snake.length == 0) {
                dead_snakes++;
                changeRedRGBLED(2, mem_base);
            }
            if (fruit_pos == -1) {
                changeRedRGBLED(1, mem_base);
                fruit_pos = generateFruitPosition(&ai_snake, &player_snake);
                drawFruit(fruit_pos, fb);
            }
        } 
        if (player_snake.length > 0) {
            changeBlueRGBLED(0, mem_base);
            player_move = getBlueMovement(mem_base, player_knob_value);
            if (player_move != 0) {
                player_knob_value = getBlueValue(mem_base);
            }
            move_snake(&player_snake, &ai_snake, player_move, &fruit_pos, fb);
            if (player_snake.length == 0) {
                dead_snakes++;
                changeBlueRGBLED(2, mem_base);
            }
            if (fruit_pos == -1) {
                changeBlueRGBLED(1, mem_base);
                fruit_pos = generateFruitPosition(&ai_snake, &player_snake);
                drawFruit(fruit_pos, fb);
            }
        }


        for (int i = 0; i < 320*480; i++) {
            parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);

        changeLengthLed(ai_snake.length, player_snake.length, mem_base);
        
        updateScores(&ai_snake, &player_snake, fb);
        clock_nanosleep(1, 0, &loop_delay, NULL);
    }
    game_over(ai_snake.score, player_snake.score, fb, mem_base, parlcd_mem_base);
}

void start_two_players_game(long int speed, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base) {
    for (int i = 0; i < 320*480 ; i++) {
        fb[i] = 0;  
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    Snake player1_snake = {
        {1,0},
        {0},
        1,
        0,
        COLOR_RED
    };
    player1_snake.body[0] = 3*16 + 2;
    drawTile(player1_snake.body[0], player1_snake.color, fb);
    changeRedRGBLED(0, mem_base);

    Snake player2_snake = {
        {-1,0},
        {0},
        1,
        0,
        COLOR_BLUE
    };
    player2_snake.body[0] = 8*16 + 11;
    drawTile(player2_snake.body[0], player2_snake.color, fb);
    changeBlueRGBLED(0, mem_base);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    int dead_snakes = 0;
    short player1_move = 0;
    short player2_move = 0;
    short player1_knob_value = getRedValue(mem_base);
    short player2_knob_value = getBlueValue(mem_base);
    int fruit_pos = generateFruitPosition(&player1_snake, &player2_snake);
    drawFruit(fruit_pos, fb);
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = speed};

    while(dead_snakes < 2) {
        if(abort_game(mem_base)) {
            game_over(player1_snake.score, player2_snake.score, fb, mem_base, parlcd_mem_base);
            return;
        }
        if (player1_snake.length > 0) {
            changeRedRGBLED(0, mem_base);
            player1_move = getRedMovement(mem_base, player1_knob_value);
            if (player1_move != 0) {
                player1_knob_value = getRedValue(mem_base);
            }
            move_snake(&player1_snake, &player2_snake, player1_move, &fruit_pos, fb);
            if (player1_snake.length == 0) {
                dead_snakes++;
                changeRedRGBLED(2, mem_base);
            }
            if (fruit_pos == -1) {
                changeRedRGBLED(1, mem_base);
                fruit_pos = generateFruitPosition(&player1_snake, &player2_snake);
                drawFruit(fruit_pos, fb);
            }
        } 
        if (player2_snake.length > 0) {
            changeBlueRGBLED(0, mem_base);
            player2_move = getBlueMovement(mem_base, player2_knob_value);
            if (player2_move != 0) {
                player2_knob_value = getBlueValue(mem_base);
            }
            move_snake(&player2_snake, &player1_snake, player2_move, &fruit_pos, fb);
            if (player2_snake.length == 0) {
                dead_snakes++;
                changeBlueRGBLED(2, mem_base);
            }
            if (fruit_pos == -1) {
                changeBlueRGBLED(1, mem_base);
                fruit_pos = generateFruitPosition(&player1_snake, &player2_snake);
                drawFruit(fruit_pos, fb);
            }
        }


        for (int i = 0; i < 320*480; i++) {
            parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);

        changeLengthLed(player1_snake.length, player2_snake.length, mem_base);
        
        updateScores(&player1_snake, &player2_snake, fb);
        clock_nanosleep(1, 0, &loop_delay, NULL);
    }
    game_over(player1_snake.score, player2_snake.score, fb, mem_base, parlcd_mem_base);
}

void game_over(int score1, int score2, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base) {
    draw_game_over(score1, score2, fb);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    while (1) {
        if (pressGreen(mem_base)) {
            break;
        }
    }

    return;
}
