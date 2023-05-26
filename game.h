#include "snake.h"
#include "mzapo_parlcd.h"
#include "input_tools.h"
#include "draw_tools.h"
#include "ai.h"
#include "rgb_tools.h"
#include "led_tools.h"
#include "score_tools.h"

#include <time.h>

#define SPEED_EASY 800000000
#define SPEED_MEDIUM 500000000
#define SPEED_HARD 150000000


void start_zero_players_game(long int speed, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base);