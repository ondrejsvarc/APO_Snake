#include "game.h"

void start_zero_players_game(unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base) {
    for (int i = 0; i < 320*480 ; i++) {
        fb[i] = 0;  
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    Snake ai_snake1 = {
        {1,0},
        {0},
        1,
        0
    };
    ai_snake1.body[0] = 3*16 + 2;
    drawTile(ai_snake1.body[0], COLOR_WHITE, fb);
    changeRedRGBLED(0, mem_base);

    Snake ai_snake2 = {
        {-1,0},
        {0},
        1,
        0
    };
    ai_snake2.body[0] = 8*16 + 11;
    drawTile(ai_snake2.body[0], COLOR_WHITE, fb);
    changeBlueRGBLED(0, mem_base);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    int dead_snakes = 0;
    short ai_move1 = 0;
    short ai_move2 = 0;
    int fruit_pos = generateFruitPosition(&ai_snake1, &ai_snake2);
    drawTile(fruit_pos, COLOR_RED, fb);
    struct timespec loop_delay = {.tv_sec = 1, .tv_nsec = 0};

    while(dead_snakes < 2) {
        //printf("before gen move\n");
        if (ai_snake1.length > 0) {
            ai_move1 = generateAiMove(&ai_snake1, &ai_snake2, fruit_pos);
            move_snake(&ai_snake1, ai_move1, &fruit_pos, fb);
            if (ai_snake1.length == 0) {
                dead_snakes++;
                changeRedRGBLED(2, mem_base);
            }
            if (fruit_pos == -1) {
                printf("Generating new fruit pos\n");
                fruit_pos = generateFruitPosition(&ai_snake1, &ai_snake2);
                printf("After generating new fruit pos\n");
                drawTile(fruit_pos, COLOR_RED, fb);
            }
        } 
        if (ai_snake2.length > 0) {
            ai_move2 = generateAiMove(&ai_snake2, &ai_snake1, fruit_pos);
            move_snake(&ai_snake2, ai_move2, &fruit_pos, fb);
            if (ai_snake2.length == 0) {
                dead_snakes++;
                changeBlueRGBLED(2, mem_base);
            }
            if (fruit_pos == -1) {
                printf("Generating new fruit pos\n");
                fruit_pos = generateFruitPosition(&ai_snake1, &ai_snake2);
                printf("After generating new fruit pos\n");
                drawTile(fruit_pos, COLOR_RED, fb);
            }
        }
        //printf("after gen move\n");
        printf("ai1: %d , ai2: %d, fruit_pos: %d\n", ai_move1, ai_move2, fruit_pos);


        for (int i = 0; i < 320*480; i++) {
            parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);

        changeLengthLed(ai_snake1.length, ai_snake2.length, mem_base);
        
        clock_nanosleep(1, 0, &loop_delay, NULL);
    }

}