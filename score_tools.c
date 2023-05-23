
#include "score_tools.h"
#include "snake.h"

void updateScores ( Snake *snake1, Snake *snake2, unsigned short *fb ) {
    snake1->score += snake1->length;
    snake2->score += snake2->length;

    // ToDo - drawScore( snake1->score, snake2->score, fb );
}