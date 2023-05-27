/*******************************************************************
  rgb_tools.c containing function for updating the score.
 
  Created by Ondrej Svarc and Michal Komanec.
 
 *******************************************************************/

#include "draw_tools.h"
#include "snake.h"

/**
 * Updates the scores of both snakes and draws them on the framebuffer.
 *
 * @param snake1 A pointer to the first snake.
 * @param snake2 A pointer to the second snake.
 * @param fb The framebuffer to draw the scores on.
 */
void update_scores (Snake *snake1, Snake *snake2, unsigned short *fb );