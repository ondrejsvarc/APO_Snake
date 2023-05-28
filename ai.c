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


int generate_smart_AI_move ( Snake *snakeToMove, Snake *snake2, int fruitIndex ) {
    // Get initial information
    bool map[MAP_COLS][MAP_ROWS];
    bool mapTemp[MAP_COLS][MAP_ROWS];
    int fruitX = fruitIndex % MAP_COLS;
    int fruitY = ( fruitIndex - fruitX ) / MAP_COLS;
    int headX = snakeToMove->body[0] % MAP_COLS;
    int headY = ( snakeToMove->body[0] - headX ) / MAP_COLS;
    short headDirectionX = snakeToMove->heading[0];
    short headDirectionY = snakeToMove->heading[1];

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

    // 0 - left, 1 - up, 2 - right, 3 - down
    int distances[4];
    int areas[4];
    int grades[4];

    // Get distances
    distances[0] = get_fruit_distance( headX - 1, headY, fruitX, fruitY, map ); // left
    distances[1] = get_fruit_distance( headX, headY - 1, fruitX, fruitY, map ); // up
    distances[2] = get_fruit_distance( headX + 1, headY, fruitX, fruitY, map ); // right
    distances[3] = get_fruit_distance( headX, headY + 1, fruitX, fruitY, map ); // down

    // Get areas
    map_data_copy( mapTemp, map );
    areas[0] = count_area_size( headX - 1, headY, mapTemp ); // left
    map_data_copy( mapTemp, map );
    areas[1] = count_area_size( headX, headY - 1, mapTemp ); // up
    map_data_copy( mapTemp, map );
    areas[2] = count_area_size( headX + 1, headY, mapTemp ); // right
    map_data_copy( mapTemp, map );
    areas[3] = count_area_size( headX, headY + 1, mapTemp ); // down

    // Get grades
    for ( int i = 0; i < 4; ++i ) {
        grades[i] = distances[i];

        if ( areas[i] == 0 ) {
            grades[i] += 1000;
        }

        if ( areas[i] < snakeToMove->length ) {
            grades[i] += 200;
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
    grades[(heading + 2) % 4] += 5000;

    // Get the best move direction
    int bestMove = 0;
    int bestGrade = 10000;
    for ( int i = 0; i < 4; ++i ) {
        if ( grades[i] < bestGrade ) {
            bestGrade = grades[i];
            bestMove = i;
        }
    }
    
    // Translate move direction to direction change and return corresponding integer
    if ( bestMove == (heading + 1) % 4 ) {
        return 1;
    } else if ( bestMove == (heading + 3) % 4 ) {
        return -1;
    } else {
        return 0;
    }
}

int count_fruit_distance ( int x, int y, int fruitX, int fruitY ) {
    if ( x < 0 || x >= MAP_COLS || y < 0 || y >= MAP_ROWS ) {
        return 1000;
    }

    int deltaX = abs( x - fruitX );
    int deltaY = abs( y - fruitY );

    return deltaX + deltaY;
}

int count_area_size ( int x, int y, bool map[MAP_COLS][MAP_ROWS] ) {
    if ( x < 0 || x >= MAP_COLS || y < 0 || y >= MAP_ROWS || map[x][y] == true ) {
        return 0;
    }

    // Mark visited
    map[x][y] = true;

    int areaSize = 1;

    areaSize += count_area_size( x + 1, y, map ); // Right
    areaSize += count_area_size( x - 1, y, map ); // Left
    areaSize += count_area_size( x, y + 1, map ); // Down
    areaSize += count_area_size( x, y - 1, map ); // Up

    return areaSize;
}

void map_data_copy ( bool target[MAP_COLS][MAP_ROWS], bool source[MAP_COLS][MAP_ROWS] ) {
    for ( int i = 0; i < MAP_COLS; ++i ) {
        for ( int j = 0; j < MAP_ROWS; ++j ) {
            target[i][j] = source[i][j];
        }
    }
}

int get_fruit_distance ( int x, int y, int fruitX, int fruitY, bool map[MAP_COLS][MAP_ROWS] ) {
    // Create a queue
    Coordinate* queue = malloc( MAP_COLS * MAP_ROWS * sizeof(Coordinate) );
    int front = 0;
    int rear = 0;

    // Visited array
    bool visited[MAP_COLS][MAP_ROWS];
    for ( int i = 0; i < MAP_COLS; ++i ) {
        for ( int j = 0; j < MAP_ROWS; ++j ) {
            visited[i][j] = false;
        }
    }

    // Distances array
    bool distances[MAP_COLS][MAP_ROWS];
    for ( int i = 0; i < MAP_COLS; ++i ) {
        for ( int j = 0; j < MAP_ROWS; ++j ) {
            distances[i][j] = INT_MAX;
        }
    }

    Coordinate start;
    start.x = x;
    start.y = y;

    // Enqueue start
    queue[rear++] = start;
    visited[start.x][start.y] = true;
    distances[start.x][start.y] = 0;

    // Movements
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Get distances
    while ( front != rear ) {
        // Dequeue
        Coordinate current = queue[front++];

        // Is it fruit?
        if ( current.x == fruitX && current.y == fruitY ) {
            free( queue );
            return distances[current.x][current.y];
        }

        // Neighbors
        for ( int i = 0; i < 4; ++i ) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            // Is coordinate valid and is it not an obstacle?
            if ( newX >= 0 && newX < MAP_COLS && newY >= 0 && newY < MAP_ROWS && !map[newX][newY] && !visited[newX][newY] ) {
                Coordinate next;
                next.x = newX;
                next.y = newY;

                // Enqueue
                queue[rear++] = next;
                visited[next.x][next.y] = true;
                distances[next.x][next.y] = distances[current.x][current.y] + 1;
            }
        }
    }

    free( queue );
    return 1000; // Return 1000 if no path found
}