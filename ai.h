/*******************************************************************
  ai.h containing functions that generates ai moves and generates
  new fruit positions.
 
  Created by Ondrej Svarc and Michal Komanec.
 
 *******************************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "snake.h"

/**
 * Generates a random position for the fruit on the game map that is not occupied by the snakes.
 *
 * @param snake1 A pointer to the first snake structure.
 * @param snake2 A pointer to the second snake structure.
 *
 * @return An integer representing the index of the generated fruit position on the game map.
 */
int generate_fruit_position (Snake *snake1, Snake *snake2 );

/**
 * Generates the AI's next move direction based on the current game state.
 *
 * @param snakeToMove A pointer to the snake structure that the AI controls.
 * @param snake2      A pointer to the second snake structure.
 * @param fruitIndex  The index of the fruit position on the game map.
 *
 * @return An integer representing the AI's next move direction:
 *         -1 for left, 0 for no change, 1 for right.
 */
int generate_AI_move (Snake *snakeToMove, Snake *snake2, int fruitIndex );

/**
 * Generates the AI's next move direction based on the current game state.
 *
 * @param snakeToMove A pointer to the snake structure that the AI controls.
 * @param snake2      A pointer to the second snake structure.
 * @param fruitIndex  The index of the fruit position on the game map.
 *
 * @return An integer representing the AI's next move direction:
 *         -1 for left, 0 for no change, 1 for right.
 */
int generate_smart_AI_move ( Snake *snakeToMove, Snake *snake2, int fruitIndex );

/**
 * Calculates absolute distance to fruit from coordinates given.
 * 
 * @param x       X coordinate.
 * @param y       Y coordinate.
 * @param fruitX  X fruit coordinate.
 * @param fruitY  Y fruit coordinate.
 * 
 * @return An integer representing the distance to the fruit.
*/
int count_fruit_distance ( int x, int y, int fruitX, int fruitY );

/**
 * Calculates reachable area size from the coordinates given.
 *
 * @param x   X coordinate.
 * @param y   Y coordinat.
 * @param map Map where true means obstacle and false means empty tile;
 *
 * @return An integer representing area size of area in which the coordinates are.
 */
int count_area_size ( int x, int y, bool map[MAP_COLS][MAP_ROWS] );

/**
 * Copies map data from source to target.
 * 
 * @param target  Map to copy the data to.
 * @param source  Map to copy the data from.
*/
void map_data_copy ( bool target[MAP_COLS][MAP_ROWS], bool source[MAP_COLS][MAP_ROWS] );