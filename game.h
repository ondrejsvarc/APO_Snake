/**********************************************************************
  game.h containing functions for starting and running a game of Snake.
 
  Created by Michal Komanec and Ondrej Svarc.
 
 *********************************************************************/

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

/**
 * Start a game of snake with zero human players and two "AI" players.
 * 
 * @param speed The speed/difficulty of the game - defined in header file.
 * @param fb Pointer to the frame buffer.
 * @param mem_base Pointer to the mem_base.
 * @param parlcd_mem_base Pointer to the LCD mem_base.
 */
void start_zero_players_game(long int speed, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base);

/**
 * Start a game of snake with one human player and one "AI" player.
 * 
 * @param speed The speed/difficulty of the game - defined in header file.
 * @param fb Pointer to the frame buffer.
 * @param mem_base Pointer to the mem_base.
 * @param parlcd_mem_base Pointer to the LCD mem_base.
 */
void start_one_player_game(long int speed, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base);

/**
 * Start a game of snake with two human players.
 * 
 * @param speed The speed/difficulty of the game - defined in header file.
 * @param fb Pointer to the frame buffer.
 * @param mem_base Pointer to the mem_base.
 * @param parlcd_mem_base Pointer to the LCD mem_base.
 */
void start_two_players_game(long int speed, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base);

/**
 * Draw and show game over screen.
 * 
 * @param score1 The score of player1.
 * @param score2 The score of player2.
 * @param fb Pointer to the frame buffer.
 * @param mem_base Pointer to the mem_base.
 * @param parlcd_mem_base Pointer to the LCD mem_base.
 */
void game_over(int score1, int score2, unsigned short *fb, unsigned char *mem_base, unsigned char *parlcd_mem_base);