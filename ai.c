#include "ai.h"

int generate_fruit_position (Snake *snake1, Snake *snake2 ) {
    // Get initial information
    int mapSize = MAP_COLS * MAP_ROWS;
    int options = ( mapSize ) - snake1->length - snake2->length;

    // Get random index
    srand(time(NULL));
    int index = rand() % options;

    int tiles[options];
    int k = 0;

    // Get all valid mp tiles
    for ( int i = 0; i < mapSize; ++i ) {
        bool occupied = false;
        for ( int j = 0; j < snake1->length; ++j ) {
            if ( i == snake1->body[j] ) {
                occupied = true;
                break;
            }
        }
        for ( int j = 0; j < snake2->length; ++j ) {
            if ( i == snake2->body[j] ) {
                occupied = true;
                break;
            }
        }

        if ( !occupied ) {
            tiles[k] = i;
            k++;
        }
    }

    // Return random empty map tile
    return tiles[index];
}

int generate_AI_move (Snake *snakeToMove, Snake *snake2, int fruitIndex ) {
    // Get initial information
    bool map[MAP_COLS][MAP_ROWS];
    int fruitX = fruitIndex % MAP_COLS;
    int fruitY = ( fruitIndex - fruitX ) / MAP_COLS;
    int headX = snakeToMove->body[0] % MAP_COLS;
    int headY = ( snakeToMove->body[0] - headX ) / MAP_COLS;
    short headDirectionX = snakeToMove->heading[0];
    short headDirectionY = snakeToMove->heading[1];

    // Get distance from fruit
    int distance = abs( headX - fruitX ) + abs( headY - fruitY );

    // Fill map with false ( empty space )
    for ( int i = 0; i < MAP_ROWS; ++i ) {
        for ( int j = 0; j < MAP_COLS; ++j ) {
            map[j][i] = false;
        }
    }

    // Fill tiles with snake in them with true ( obstacle )
    for ( int i = 0; i < snakeToMove->length; ++i ) {
        int x = snakeToMove->body[i] % MAP_COLS;
        int y = ( snakeToMove->body[i] - x ) / MAP_COLS;
        map[x][y] = true;
    }

    for ( int i = 0; i < snake2->length; ++i ) {
        int x = snake2->body[i] % MAP_COLS;
        int y = ( snake2->body[i] - x ) / MAP_COLS;
        map[x][y] = true;
    }

    // 0 - left, 1 - up, 2 - right, 3- down
    int moveGrades[4];

    // Grade all head directions
    for ( int i = 0; i < 4; ++i ) {
        int posX = 0, posY = 0;
        switch ( i )
        {
        case 0:
            posX = headX - 1;
            posY = headY;
            break;
        case 1:
            posX = headX;
            posY = headY - 1;
            break;
        case 2:
            posX = headX + 1;
            posY = headY;
            break;
        case 3:
            posX = headX;
            posY = headY + 1;
            break;
        default:
            break;
        }
        if ( posX < 0 || posY < 0 || posX >= 24 || posY >= 16 ) {
            moveGrades[i] = -1;
            continue;
        }
        int newDistance = abs( posX - fruitX ) + abs( posY - fruitY );

        if ( map[posX][posY] ) {
            moveGrades[i] = -1;
        } else if ( newDistance < distance ) {
            moveGrades[i] = 2;
        } else if ( newDistance == distance ) {
            moveGrades[i] = 1;
        } else {
            moveGrades[i] = 0;
        }
    }

    // Get the best and second best move direction
    int bestMove = 0;
    int secondBestMove = 0;
    int bestGrade = -2;
    for ( int i = 0; i < 4; ++i ) {
        if ( moveGrades[i] >= bestGrade ) {
            secondBestMove = bestMove;
            bestGrade = moveGrades[i];
            bestMove = i;
        }
    }
    
    // Get actual head direction
    int heading;
    if ( headDirectionX == - 1 ) {
        heading = 0;
    } else if ( headDirectionX == 1 ) {
        heading = 2;
    } else if ( headDirectionY == 1 ) {
        heading = 1;
    } else {
        heading = 3;
    }

    // If the best move is to go back use second best move direction
    if ( bestMove == (heading + 2) % 4 ) {
        bestMove = secondBestMove;
    }
    
    // Translate move direction to direction change and return corresponding integer
    if ( bestMove == (heading + 1) % 4 ) {
        return 1;
    } else if ( bestMove == (heading +3) % 4 ) {
        return -1;
    } else {
        return 0;
    }
}