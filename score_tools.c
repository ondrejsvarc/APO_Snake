#include "score_tools.h"

void update_scores (Snake *snake1, Snake *snake2, unsigned short *fb ) {
    // Update scores
    snake1->score += snake1->length;
    snake2->score += snake2->length;

    // Draw the scores
    draw_score( snake1->score, snake2->score, fb );
}