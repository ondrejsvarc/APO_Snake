#include "game.h"

void start_zero_players_game(unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base) {
    Snake ai_snake1 = {
        {1,0},
        {0},
        1,
        0
    };
    ai_snake1.body[0] = 8*16 + 12;

    drawTile(ai_snake1.body[0], COLOR_WHITE, fb);

    Snake ai_snake2 = {
        {-1,0},
        {0},
        1,
        0
    };
    ai_snake2.body[0] = 8*16 + 11;

    drawTile(ai_snake2.body[0], COLOR_WHITE, fb);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    int dead_snakes = 0;
    short ai_move1 = 0;
    short ai_move2 = 0;
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 1000000000};

    while(dead_snakes < 2) {
        //printf("before gen move\n");
        ai_move1 = generateAiMove(&ai_snake1, &ai_snake2, 0);
        ai_move2 = generateAiMove(&ai_snake2, &ai_snake1, 0);
        //printf("after gen move\n");
        printf("ai1: %d , ai2: %d\n", ai_move1, ai_move2);

        move_snake(&ai_snake1, ai_move1, fb);
        move_snake(&ai_snake2, ai_move2, fb);

        for (int i = 0; i < 320*480; i++) {
            parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        
        printf("before nanosleep\n");
        clock_nanosleep(1, 0, &loop_delay, NULL);
        printf("after nanosleep\n");

    }

}